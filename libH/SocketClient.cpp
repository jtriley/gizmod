    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  SocketClient.cpp
*** \brief SocketClient class body
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

#include "SocketClient.hpp"
#include "SocketException.hpp"
#include "Debug.hpp"

using namespace H;
using namespace std;

////////////////////////////////////////////////////////////////////////////
// Defines / Type Defs
///////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Construction / Deconstruction
///////////////////////////////////////

/**
 * \brief Default Constructor
**/
SocketClient::SocketClient() {
	mConnected = false;
	setEventWatcher(this);
}

/**
 * \brief Destructor
**/
SocketClient::~SocketClient() {
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief  Connect to a server
 * \param  Host Hostname of the server to connect to
 * \param  Port Port of the server to connect to
**/
void SocketClient::connectToServer(std::string Host, int Port) {
	createSocket(SOCKET_INTERNET, SOCKET_STREAM);
	connect(Host, Port);
}

/**
 * \brief  Are we connected to the server?
 * \return True if yes
**/
bool SocketClient::isClientConnected() {
	return mConnected;
}

/**
 * \brief  Event triggered on socket connect
 * \param  socket The socket 
**/
void SocketClient::onSocketClientConnect(Socket const & socket) {
	// override me
	cdbg << "SocketClient :: Socket Connect Detected" << endl;
}

/**
 * \brief  Event triggered on socket disconnect
 * \param  socket The socket 
**/
void SocketClient::onSocketClientDisconnect(Socket const & socket) {
	// override me
	cdbg << "SocketClient :: Socket Disconnect Detected" << endl;
}

/** 
 * \brief  Event triggered on a socket client message
 * \param  socket The Socket that triggered the event
 * \param  Message The message
**/
void SocketClient::onSocketClientMessage(Socket const & socket, std::string const & Message) {
	// override me
	cdbg << "SocketClient :: Socket Message [" << Message.length() << "] Bytes -- " << Message << endl;
}

/**
 * \brief  Event triggered on socket read
 * \param  socket The socket 
 * \param  ReadBuffer The data
**/
void SocketClient::onSocketClientRead(Socket const & socket, DynamicBuffer<char> & ReadBuffer) {
	// override me
	cdbg << "SocketClient :: Socket Read [" << ReadBuffer.length() << "] Bytes" << endl;
}

/**
 * \brief  Handle a socket Connect
 * \param  iSocket The Socket that triggered the event
 *
 * SocketEventWatcher triggers this event
**/
void SocketClient::onSocketConnect(SocketInterface const & iSocket) {
	mConnected = true;
	onSocketClientConnect(static_cast<Socket const &>(iSocket));
	processEvents();
}

/**
 * \brief  Handle a socket Disconnect
 * \param  iSocket The Socket that triggered the event
 *
 * SocketEventWatcher triggers this event
**/
void SocketClient::onSocketDisconnect(SocketInterface const & iSocket) {
	mConnected = false;
	onSocketClientDisconnect(static_cast<Socket const &>(iSocket));
}

/** 
 * \brief  Handle a socket message
 * \param  iSocket The Socket that triggered the event
 * \param  Message The message
 *
 * SocketEventWatcher triggers this event
**/
void SocketClient::onSocketMessage(SocketInterface const & iSocket, std::string const & Message) {
	onSocketClientMessage(static_cast<Socket const &>(iSocket), Message);
}

/**
 * \brief  Handle a socket read
 * \param  iSocket The Socket that triggered the event
 * \param  ReadBuffer The Buffer
 *
 * SocketEventWatcher triggers this event
**/
void SocketClient::onSocketRead(SocketInterface const & iSocket, DynamicBuffer<char> & ReadBuffer) {
	onSocketClientRead(static_cast<Socket const &>(iSocket), ReadBuffer);
}

/**
 * \brief  Send a formatted message to the server
 * \param  Message The message to send
**/
void SocketClient::sendToServer(std::string const & Message) {
	writeMessage(Message);
}
