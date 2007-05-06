    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  SocketServer.cpp
*** \brief SocketServer class body
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

#include "SocketServer.hpp"
#include "SocketException.hpp"
#include "UtilTime.hpp"
#include "Debug.hpp"
#include <string>
#include <boost/thread/thread.hpp>
#include <errno.h>

using namespace H;
using namespace boost;
using namespace std;

////////////////////////////////////////////////////////////////////////////
// Defines / Type Defs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction / Deconstruction
///////////////////////////////////////

/**
 * \brief Default Constructor
 */
SocketServer::SocketServer() : mThreadProc(this) {
}

/**
 * \brief Destructor
 */
SocketServer::~SocketServer() {
	shutdown();
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Start accepting incoming connections
 * \param  ListenPort Port to listen on
 * \param  Domain Socket domain
 * \param  Type Socket type
 */
void SocketServer::acceptConnections(int ListenPort, SocketDomain Domain, SocketType Type) {
	if (mSocket != SOCKET_ERROR)
		throw SocketException("Socket Already Created!", __FILE__, __FUNCTION__, __LINE__);
	
	// create the listen socket
	createSocket(Domain, Type);

	// bind to a specified port
	bind(mPort = ListenPort);

	// listen for connections!
	listen();
	
	// initialize the listen thread
	thread thrd(mThreadProc);
}

/**
 * \brief Handle a socket Connect
 * \param iSocket The Socket that triggered the event
 *
 * SocketEventWatcher triggers this event
 */
void SocketServer::onSocketConnect(SocketInterface const & iSocket) {
	// this is only for client socket connections
}

/**
 * \brief Handle a socket Disconnect
 * \param iSocket The Socket that triggered the event
 *
 * SocketEventWatcher triggers this event
 */
void SocketServer::onSocketDisconnect(SocketInterface const & iSocket) {
	shared_ptr<Socket> pSocket = mSockets[iSocket.getOldSocket()];
	if (!pSocket) {
		cdbg << "SocketServer :: Socket Disconnect from Unhandled Socket Detected" << endl;
	} else {
		onSocketServerDisconnect(*pSocket);
		mSockets.erase(iSocket.getOldSocket());
	}
}

/** 
 * \brief  Handle a socket message
 * \param  iSocket The Socket that triggered the event
 * \param  Message The message
 *
 * SocketEventWatcher triggers this event
 */
void SocketServer::onSocketMessage(SocketInterface const & iSocket, std::string const & Message) {
	onSocketServerMessage(static_cast<Socket const &>(iSocket), Message);
}

/**
 * \brief Handle a socket read
 * \param iSocket The Socket that triggered the event
 * \param ReadBuffer The Buffer
 *
 * SocketEventWatcher triggers this event
 */
void SocketServer::onSocketRead(SocketInterface const & iSocket, DynamicBuffer<char> & ReadBuffer) {
	onSocketServerRead(static_cast<Socket const &>(iSocket), ReadBuffer);
}

/**
 * \brief  Event triggered when a new connection is detected
 * \param  pSocket The new socket
 */
void SocketServer::onSocketServerConnect(boost::shared_ptr<Socket> pSocket) {
	// override me
	cdbg << "SocketServer :: New Socket Connection Detected" << endl;
}

/**
 * \brief  Event triggered on a socket disconnect
 * \param  socket The socket
 */
void SocketServer::onSocketServerDisconnect(Socket const & socket) {
	// override me
	cdbg << "SocketServer :: Socket Disconnect Detected" << endl;
}

/** 
 * \brief  Event triggered on a socket server message
 * \param  socket The Socket that triggered the event
 * \param  Message The message
 */
void SocketServer::onSocketServerMessage(Socket const & socket, std::string const & Message) {
	// override me
	cdbg << "SocketServer :: Socket Message [" << Message.length() << "] Bytes -- " << Message << endl;
}

/**
 * \brief  Event triggered on a socket read
 * \param  socket The socket
 * \param  ReadBuffer The data
 */
void SocketServer::onSocketServerRead(Socket const & socket, DynamicBuffer<char> & ReadBuffer) {
	// override me
	cdbg << "SocketServer :: Socket Read [" << ReadBuffer.length() << "] Bytes" << endl;
}

/**
 * \brief  Shutdown all socket processing
 */
void SocketServer::shutdown() {
	// wait until thead finishes done 
	mProcessing = false;
	while (mThreading) {
		cdbg5 << "Waiting on SocketServer Thread to Finish..." << endl;
		UtilTime::sleep(0.1f);
	}
}

/**
 * \brief  The thread procedure loop
 */
void SocketServer::threadProc() {
	cdbg << "Listening for connections on port [" << mPort << "]..." << endl;
	mProcessing = true;
	while (mProcessing) {
		shared_ptr<Socket> pSocket = accept();
		if ( (!pSocket) || (pSocket->getSocket() == SOCKET_ERROR) )
			continue;
		
		// configure the socket
		pSocket->setEventWatcher(this);
		pSocket->setMessageMode(true);
		
		// add the socket to the map
		mSockets.insert(make_pair(pSocket->getSocket(), pSocket));
		
		// fire the event
		onSocketServerConnect(pSocket);
		
		// start processing events on the new socket
		pSocket->processEvents();
	}
	cdbg5 << "No longer accepting connections" << endl;
}
