    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  Socket.cpp
*** \brief Socket class body
***
*****************************************
  *****************************************
    **/
    
/*
  
  Copyright (c) 2007, Tim Burrell
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at 

	http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and 
  limitations under the License. 
  
*/

#include "Socket.hpp"
#include "SocketException.hpp"
#include "Debug.hpp"
#include "UtilTime.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/thread/thread.hpp>
#include <errno.h>
#include <signal.h>
#include <poll.h>

using namespace H;
using namespace boost;
using namespace std;

////////////////////////////////////////////////////////////////////////////
// Defines / Type Defs
///////////////////////////////////////

/**
 * \def    DEFAULT_BACKLOG
 * \brief  Default backlog setting for listen sockets
 */
#define DEFAULT_BACKLOG	64

/**
 * \def    PACKET_SIZE
 * \brief  Size of the buffer when reading from a socket
 */
#define PACKET_SIZE	4096

/**
 * \def    POLL_TIMEOUT
 * \brief  Poll timeout in milliseconds
 */
#define POLL_TIMEOUT	1000

////////////////////////////////////////////////////////////////////////////
// Construction / Deconstruction
///////////////////////////////////////

/**
 * \brief Default Constructor
 */
Socket::Socket() : mThreadProcRead(this) {
	init();
}

/**
 * \brief Default Constructor
 */
Socket::Socket(Socket const & InitFrom) : mThreadProcRead(this) {
	init();
	setTo(InitFrom);
}


/**
 * \brief Destructor
 */
Socket::~Socket() {
	shutdown();
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Accept connections
 * \return The new socket
 *
 * Note: blocking
 */
boost::shared_ptr<Socket> Socket::accept() {
	// error checking
	if (mSocket == SOCKET_ERROR)
		throw SocketException("Accept on Invalid Socket!" + lexical_cast<string>(mPort), __FILE__, __FUNCTION__, __LINE__);
	
	// set up the poll structure
	struct pollfd PollFD;
	PollFD.fd = mSocket;
	PollFD.events = POLLIN | POLLOUT;
	PollFD.revents = 0;
	
	// create the new socket
	shared_ptr<Socket> pSocket = shared_ptr<Socket>(new Socket(*this));
	
	// wait until there's a connection on the socket
	int ret;
	do {
		if ((ret = poll(&PollFD, 1, POLL_TIMEOUT)) < 0) {
			// error
			cdbg1 << "Poll error: " << strerror(errno) << endl;
			return pSocket;
		}
	} while (mProcessing && (ret <= 0));
	
	// don't try to accept if we're quitting
	if (!mProcessing)
		return pSocket;
	
	// accept the connection
	pSocket->mSocket = ::accept(mSocket, (struct sockaddr *) &pSocket->mSockAddr, &pSocket->mSockAddrLen);
	pSocket->mOldSocket = pSocket->mSocket;

	return pSocket;
}

/**
 * \brief  Bind a socket to a port
 * \param  Port The port to bind to
 */
void Socket::bind(int Port) {
	mPort = Port;
	memset(&mSockAddr, 0, sizeof(mSockAddr));
	mSockAddr.sin_family = mType;
	mSockAddr.sin_port = htons(mPort);
	mSockAddr.sin_addr.s_addr = INADDR_ANY;
	
	/* bind the socket to the newly formed address */
	if (::bind(mSocket, (struct sockaddr *) &mSockAddr, sizeof(mSockAddr)))
		throw SocketException("Failed to Bind to Port" + lexical_cast<string>(mPort), __FILE__, __FUNCTION__, __LINE__);
}

/**
 * \brief  Close the socket
 */
void Socket::closeSocket() {
	if (mSocket != SOCKET_ERROR) {
		#ifndef WIN32
		if (::close(mSocket) == SOCKET_ERROR)
		#else
		if (::closesocket(mSocket) == SOCKET_ERROR)
		#endif
			throw SocketException("Failed to Close Socket [" + lexical_cast<string>(mSocket) + "]", __FILE__, __FUNCTION__, __LINE__);
	}
	
	#ifdef HAVE_OPENSSL
	if (mSSL) {
		SSL_free(mSSL);
		mSSL = NULL;
	}
	#endif
		
	init();
}


/**
 * \brief  Create a socket
 */
void Socket::createSocket(SocketDomain Domain, SocketType Type) {
	mDomain = Domain;
	mType = Type;
	
	#ifdef HAVE_OPENSSL
	if ( (mSSLMode) && (!initializeCTX()) )
		throw SocketException("Failed to Initialize OpenSSL", __FILE__, __FUNCTION__, __LINE__);
	#endif

	if ((mSocket = socket(mDomain, mType, mProtocol)) == -1)
		throw SocketException(string("Failed to Create Socket -- ") + strerror(errno), __FILE__, __FUNCTION__, __LINE__);

	mOldSocket = mSocket;
}

/**
 * \brief  Get the socket
 * \return The socket
 */
int Socket::getSocket() const {
	return mSocket;
}

/**
 * \brief Handle a socket disconnect
 */
void Socket::handleSocketDisconnect() {
	if (mpEventWatcher)
		mpEventWatcher->onSocketDisconnect(*this);
	closeSocket();
}

/**
 * \brief Handle a socket read
 */
void Socket::handleSocketRead(DynamicBuffer<char> & ReadBuffer) {
	if (mpEventWatcher)
		mpEventWatcher->onSocketRead(*this, ReadBuffer);
}


/**
 * \brief  Init the socket
 */
void Socket::init() {
	mBacklog = DEFAULT_BACKLOG;
	mDomain = SOCKET_INTERNET;
	mpEventWatcher = NULL;
	mPort = 0;
	mProcessing = false;
	mProtocol = SOCKET_PROTO_TCP;
	mSockAddrLen = sizeof(struct sockaddr);
	mSocket = SOCKET_ERROR;
	mType = SOCKET_STREAM;
}

/**
 * \brief  Test if a socket is valid or not
 * \return True if valid
 */
bool Socket::isSocketValid() const {
	return (mSocket != SOCKET_ERROR);
}

/**
 * \brief  Listen on a socket
 */
void Socket::listen() {
	if (::listen(mSocket, mBacklog) == -1)
		throw SocketException(string("Failed to Listen on Socket -- ") + strerror(errno), __FILE__, __FUNCTION__, __LINE__);
}

/**
 * \brief  Process events on the socket
 */
void Socket::processEvents() {
	// initialize the read thread
	thread thrd(mThreadProcRead);
}

/**
 * \brief  Read from a socket
 * \param  Buffer The buffer to read into
 * \param  BufLen The length of the buffer
 */
int Socket::read(char * Buffer, int BufLen) {
	int ret;
	
	#ifdef HAVE_OPENSSL
		if (m_SSLMode) {
			SSL_set_bio(m_SSL, m_SSLbio, m_SSLbio);
			ret = SSL_read(m_SSL, Buffer, BufLen);
		} else
			ret = ::recv(m_Socket, Buffer, sizeof(char) * BufLen, 0);
	#else
		ret = ::recv(mSocket, Buffer, sizeof(char) * BufLen, 0);
	#endif

	// value is 0 if socket has disconnected
	if (ret == 0)
		handleSocketDisconnect();

	return ret;
}

/**
 * \brief  Read from the socket, info a buffer
 * \param  Buffer The buffer to read into
 * \return Number of bytes read from socket
 */
int Socket::readIntoBuffer(DynamicBuffer<char> & Buffer) {
	char Packet[PACKET_SIZE];
	int TotalBytesRead = 0;
	int BytesRead;
	do {
	 	if ((BytesRead = read(Packet, PACKET_SIZE)) == -1) {
			#ifndef WIN32
	 		switch (errno) {
				case EINPROGRESS:
				case EALREADY:
				case EAGAIN:
			#else
			switch (WSAGetLastError()) {
				case WSAEINPROGRESS:
				case WSAEALREADY:
				case WSAEWOULDBLOCK:
			#endif
				// this is just fine
				return TotalBytesRead;
			default:
				cdbg << "Socket Read Error -- " << strerror(errno) << endl;
				handleSocketDisconnect();
				return TotalBytesRead;
	 		}
		}
		
		if (BytesRead > 0) {
			Buffer.addToBuffer(Packet, BytesRead);
			TotalBytesRead += BytesRead;
		}
	} while ( (BytesRead == PACKET_SIZE) && (BytesRead > 0) );
	
	return TotalBytesRead;
}

/**
 * \brief  Set the event watcher
 * \param  pWatcher The event watcher
 */
void Socket::setEventWatcher(SocketEventWatcher * pWatcher) {
	mpEventWatcher = pWatcher;
}

/**
 * \brief  Set the current socket to another socket
 * \param  SocketToBecome The socket to copy from
 */
void Socket::setTo(Socket const & SocketToBecome) {
	mProtocol = SocketToBecome.mProtocol;
	mDomain = SocketToBecome.mDomain;
	mType = SocketToBecome.mType;
	mPort = SocketToBecome.mPort;
	mBacklog = SocketToBecome.mBacklog;
	
	#ifdef HAVE_OPENSSL
	mSSL = SocketToBecome.mSSL;
	mSSLMode = SocketToBecome.mSSLMode;
	#endif
}

/**
 * \brief  Shutdown all socket processing
 */
void Socket::shutdown() {
	mProcessing = false;
	while (mThreading) {
		cdbg5 << "Waiting on Socket [" << mSocket << "] Thread to Finish..." << endl;
		UtilTime::sleep(0.1f);
	}
}

/**
 * \brief  Thread procedure for reading from the socket
 */
void Socket::threadProcRead() {
	// set up the poll structure
	struct pollfd PollFD;
	PollFD.fd = mSocket;
	PollFD.events = POLLIN | POLLOUT;
	PollFD.revents = 0;
	
	// loop
	mProcessing = true;
	while ( mProcessing && isSocketValid() ) {
		// wait until there's data on the socket
		int ret;
		do {
			if ((ret = poll(&PollFD, 1, POLL_TIMEOUT)) < 0) {
				// error
				cdbg1 << "Poll error: " << strerror(errno) << endl;
				break;
			}		
		} while (mProcessing && (ret <= 0));		
		
		DynamicBuffer<char> ReadBuffer;
		if (readIntoBuffer(ReadBuffer) > 0)
			handleSocketRead(ReadBuffer);
	}
	
	// done
	cdbg << "No longer handling events on Socket [" << mSocket << "]" << endl;
}
