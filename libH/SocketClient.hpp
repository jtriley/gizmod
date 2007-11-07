    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  SocketClient.hpp
*** \brief SocketClient class header file
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

#ifndef __SocketClient_h
#define __SocketClient_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "Socket.hpp"
#include "SocketEventWatcher.hpp"
#include <cstdlib>

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
 * \class SocketClient
 * \brief Main SocketClient class
 *
 * This is an interface for classes wishing to receive socket events
**/
class SocketClient : public Socket, private SocketEventWatcher {
public:
	// Public Member Functions
	void				connectToServer(std::string Host, int Port); ///< Connect to a server
	bool				isClientConnected();		///< Are we connected to the server
	virtual void			onSocketClientConnect(Socket const & socket); ///< Event triggered on a socket connection
	virtual void 			onSocketClientDisconnect(Socket const & socket); ///< Event triggered on a socket read
	virtual void 			onSocketClientMessage(Socket const & socket, std::string const & Message); ///< Event triggered on a socket message
	virtual void			onSocketClientRead(Socket const & socket, DynamicBuffer<char> & ReadBuffer); ///< Event triggered on a socket read
	void				sendToServer(std::string const & Message); ///< Send a message to the server
	
	// Construction / Deconstruction
	SocketClient();							///< Default Constructor
	virtual ~SocketClient();					///< Destructor

private:
	// Private Member Functions
	void 				onSocketConnect(SocketInterface const & iSocket); ///< Handle a socket connection
	void 				onSocketDisconnect(SocketInterface const & iSocket); ///< Handle a socket read
	void 				onSocketMessage(SocketInterface const & iSocket, std::string const & Message); ///< Handle a socket message
	void 				onSocketRead(SocketInterface const & iSocket, DynamicBuffer<char> & ReadBuffer); ///< Handle a socket read

	// Private Member Variables
	bool				mConnected;
};

//////////////////////////////////////////////////////////////////////////////

} // H namespace

#endif // __SocketClient_h
