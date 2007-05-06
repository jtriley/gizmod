    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  Socket.hpp
*** \brief Socket class header file
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

#ifndef __Socket_h
#define __Socket_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "SocketInterface.hpp"
#include "SocketEventWatcher.hpp"
#include "DynamicBuffer.hpp"
#include <cstdlib>
#include <boost/shared_ptr.hpp>
#include <sys/types.h>
#ifndef WIN32
#include <sys/socket.h>
#include <netinet/in.h>	// Internet address structures
#else
#include <winsock.h>
#endif
#ifdef HAVE_OPENSSL
#include <openssl/ssl.h>
#endif

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace H {

//////////////////////////////////////////////////////////////////////////////
// Typedef's / Defines
///////////////////////////////////////
	
/**
 * \enum   SocketDomain
 * \brief  Domain of the socket
 */
typedef enum {
#ifndef WIN32
	SOCKET_INTERNET 		= PF_INET,
	SOCKET_UNIX 			= PF_UNIX,
	SOCKET_INTERNET2 		= PF_INET6
#else
	SOCKET_INTERNET 		= AF_INET,
	SOCKET_UNIX 			= AF_UNIX,
	#ifdef AF_INET	6
	SOCKET_INTERNET2 		= AF_INET6
	#endif
#endif
} SocketDomain;

/**
 * \enum   SocketType
 * \brief  Type of the socket
 */
typedef enum {
	SOCKET_STREAM 			= SOCK_STREAM,
	SOCKET_DGRAM 			= SOCK_DGRAM,
	SOCKET_RAW 			= SOCK_RAW,
	SOCKET_SEQPACKET 		= SOCK_SEQPACKET,
	SOCKET_RDM 			= SOCK_RDM
} SocketType;

/**
 * \enum   SocketProtocol
 * \brief  Protocol of the socket
 */
typedef enum {
	SOCKET_PROTO_TCP 		= IPPROTO_TCP,
	SOCKET_PROTO_UDP	 	= IPPROTO_UDP
} SocketProtocol;


/**
 * \def    SOCKET_ERROR
 * \brief  Constant used to indicate a socket is in an error state
 */
#ifndef SOCKET_ERROR
	#define SOCKET_ERROR	-1
#endif
		
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class Socket
 * \brief Main Socket class
 *
 * This class represents an abstraction to the BSD socket interface
 */
class Socket : public SocketInterface {
public:
	// Public Member Functions
	boost::shared_ptr<Socket> 	accept();			///< Accept a connection on a socket
	void 				bind(int Port);			///< Bind a socket to a port
	void 				closeSocket();			///< Close the socket
	void 				connect(std::string Host, int Port); ///< Connect to a server 
	void 				createSocket(SocketDomain Domain = SOCKET_INTERNET, SocketType Type = SOCKET_STREAM); ///< Create a socket
	std::string			getAddress() const;		///< Get the socket's address
	int				getOldSocket() const;		///< Get the old socket (what it was before disconnect)
	int				getSocket() const;		///< Get the socket
	bool 				isSocketValid() const;		///< Test if a socket is valid or not
	void 				listen();			///< Listen on a socket
	void				processEvents();		///< Process events on the socket
	int 				readIntoBuffer(DynamicBuffer<char> & Buffer); ///< Read from the socket into a buffer
	void				setEventWatcher(SocketEventWatcher * pWatcher); ///< Set the event watcher
	void				setMessageMode(bool Enabled);	///< Enable automatic message handling mode?
	void 				setTo(Socket const & SocketToBecome); ///< Initialize from another socket
	void 				shutdown();			///< Shutdown socket processing
	int 				write(const char * Buffer, int BufLen); ///< Write date to the socket
	void				writeMessage(std::string const & Message, bool FormatMessage = true); ///< Write message to socket
	
	// Construction / Deconstruction
	Socket();							///< Default Constructor
	Socket(Socket const & InitFrom);				///< Init Constructor
	virtual ~Socket();						///< Destructor

protected:
	// Private Member Functions
	void 				addToMessageBuffer(char * Data, int BufLen); ///< Add data to the message buffer
	void				handleSocketDisconnect();	///< Handle a socket disconnect
	void 				handleSocketRead(DynamicBuffer<char> & ReadBuffer); ///< Handle a socket read
	void				init();				///< Initialize the socket
	int 				read(char * Buffer, int BufLen);///< Read from a socket
	void				setAddress();			///< Set the socket's address
	void				threadProcRead();		///< Thread procedure for reading from the socket

	// Private Member Variables
	std::string			mAddress;			///< The socket's address
	int				mBacklog;			///< Listen with backlog enabled?
	SocketDomain			mDomain;			///< Socket domain
	SocketEventWatcher *		mpEventWatcher;			///< Object that listens for events on this socket
	int				mOldSocket;			///< The old socket
	int				mPort;				///< Socket port
	bool				mProcessing;			///< Keep processing?
	SocketProtocol			mProtocol;			///< Socket protocol
	DynamicBuffer<char>		mMessageBuffer;			///< Buffer that holds messages
	bool				mMessageMode;			///< Do automatic message processing?
	struct sockaddr_in 		mSockAddr;			///< The socket addres structure
	socklen_t			mSockAddrLen;			///< Length of the socket address
	int				mSocket;			///< The socket
	SocketType			mType;				///< Socket type
	
private:	
	/**
	 * Thread callback procedure struct
	 */
	struct SocketReadThreadProc {
		SocketReadThreadProc(Socket * pSocketRead) : mpSocketRead(pSocketRead) {
			mpSocketRead->mThreading = false;
		};
		
		/// Thread proc
		void operator()() {
			mpSocketRead->mThreading = true;
			mpSocketRead->threadProcRead();
			mpSocketRead->mThreading = false;
		}
		
		Socket * 		mpSocketRead;			///< The associated SoundCard
	};		
	bool				mThreading;			///< Variable to keep track if we're threading or not
	SocketReadThreadProc		mThreadProcRead;		///< The thread procedure instance		
};

//////////////////////////////////////////////////////////////////////////////

} // H namespace

#endif // __Socket_h
