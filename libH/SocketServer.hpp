    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  SocketServer.hpp
*** \brief SocketServer class header file
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

#ifndef __SocketServer_h
#define __SocketServer_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "Socket.hpp"
#include "SocketEventWatcher.hpp"
#include <cstdlib>
#include <map>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace H {

//////////////////////////////////////////////////////////////////////////////
// Typedef's / Defines
///////////////////////////////////////
		
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class SocketServer
 * \brief Main SocketServer class
 *
 * This creates generic a threaded network server
 */
class SocketServer : public Socket, private SocketEventWatcher {
public:
	// Public Member Functions
	void				acceptConnections(int ListenPort, SocketDomain Domain = SOCKET_INTERNET, SocketType Type = SOCKET_STREAM); ///< Start accepting incoming connections
	virtual void			onSocketServerConnect(boost::shared_ptr<Socket> pSocket); ///< Event triggered when a new connection is detected
	virtual void 			onSocketServerDisconnect(Socket const & socket); ///< Event triggered on a socket disconnect
	virtual void 			onSocketServerMessage(Socket const & socket, std::string const & Message); ///< Event triggered on a socket message
	virtual void 			onSocketServerRead(Socket const & socket, DynamicBuffer<char> & ReadBuffer); ///< Event triggered on a socket read
	void 				shutdown();			///< Shutdown socket processing
	void				threadProc();			///< The thread procedure loop
	
	// Construction / Deconstruction
	SocketServer();							///< Default Constructor
	virtual ~SocketServer();					///< Destructor

private:
	// private member functions
	void 				onSocketDisconnect(SocketInterface const & iSocket); ///< Handle a socket disconnect
	void 				onSocketConnect(SocketInterface const & iSocket); ///< Handle a socket connection
	void 				onSocketMessage(SocketInterface const & iSocket, std::string const & Message); ///< Handle a socket message
	void 				onSocketRead(SocketInterface const & iSocket, DynamicBuffer<char> & ReadBuffer); ///< Handle a socket read
	
	// Private Member Variables
	std::map< int, boost::shared_ptr<Socket> > mSockets;		///< Map of the currently connected sockets

	/**
	 * Thread callback procedure struct
	 */
	struct SocketServerThreadProc {
		SocketServerThreadProc(SocketServer * pSocketServer) : mpSocketServer(pSocketServer) {
			mpSocketServer->mThreading = false;
		};
		
		/// Thread proc
		void operator()() {
			mpSocketServer->mThreading = true;
			mpSocketServer->threadProc();
			mpSocketServer->mThreading = false;
		}
		
		SocketServer * 		mpSocketServer;			///< The associated SoundCard
	};		
	bool				mThreading;			///< Variable to keep track if we're threading or not
	SocketServerThreadProc		mThreadProc;			///< The thread procedure instance	
};

//////////////////////////////////////////////////////////////////////////////

} // H namespace

#endif // __SocketServer_h
