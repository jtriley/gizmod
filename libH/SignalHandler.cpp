    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  SignalHandler.cpp
*** \brief SignalHandler class body
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

#include "SignalHandler.hpp"
#include "Debug.hpp"
#include "Exception.hpp"
#include <signal.h>
#include <boost/bind.hpp>

using namespace H;
using namespace boost;
using namespace std;

////////////////////////////////////////////////////////////////////////////
// Defines / Type Defs
///////////////////////////////////////

SignalHandler * SignalHandler::mpThis = NULL;

////////////////////////////////////////////////////////////////////////////
// Construction
///////////////////////////////////////

/**
 * \brief Default Constructor
**/
SignalHandler::SignalHandler() {
	if (mpThis)
		throw H::Exception("There can only be one SignalHandler!", __FILE__, __FUNCTION__, __LINE__);
	mpThis = this;
}

/**
 * \brief Destructor
**/
SignalHandler::~SignalHandler() {
	if (mpThis)
		mpThis = NULL;
}

////////////////////////////////////////////////////////////////////////////
// Class Body
///////////////////////////////////////

/**
 * \brief Initialize the signal handler
**/
void SignalHandler::initSignals() {
	signal(SIGINT,   signalHandler);
	signal(SIGHUP,   signalHandler);
	signal(SIGQUIT,  signalHandler);
	signal(SIGKILL,  signalHandler);
	signal(SIGTERM,  signalHandler);
	signal(SIGSTOP,  signalHandler);
}

/**
 * \brief Signal handler for SEGV
**/
void SignalHandler::onSignalSegv() {
	// override me
	cerr << "Unhandled SEGV Signal" << endl;
}

/**
 * \brief Signal handler for INT
**/
void SignalHandler::onSignalInt() {
	// override me
	cerr << "Unhandled INT Signal" << endl;
}

/**
 * \brief Signal handler for HUP
**/
void SignalHandler::onSignalHup() {
	// override me
	cerr << "Unhandled HUP Signal" << endl;
}

/**
 * \brief Signal handler for QUIT
**/
void SignalHandler::onSignalQuit() {
	// override me
	cerr << "Unhandled QUIT Signal" << endl;
}

/**
 * \brief Signal handler for KILL
**/
void SignalHandler::onSignalKill() {
	// override me
	cerr << "Unhandled KILL Signal" << endl;
}

/**
 * \brief Signal handler for TERM
**/
void SignalHandler::onSignalTerm() {
	// override me
	cerr << "Unhandled TERM Signal" << endl;
}

/**
 * \brief Signal handler for STOP
**/
void SignalHandler::onSignalStop() {
	// override me
	cerr << "Unhandled STOP Signal" << endl;
}

/**
 * \brief Signal handler for Unknown Signals
**/
void SignalHandler::onSignalUnknown(int Signal) {
	// override me
	cerr << "Unhandled Unknown Signal" << endl;
}

/**
 * \brief Signal handler
**/
void SignalHandler::signalHandler(int Signal) {
	if (!mpThis) {
		cerr << "Unhandled Signal Caught!" << endl;
		return;
	}
	
	switch (Signal) {
	case SIGSEGV:
		mpThis->onSignalSegv();
		break;		
	case SIGINT:
		mpThis->onSignalInt();
		break;
	case SIGHUP:
		mpThis->onSignalHup();
		break;
	case SIGQUIT:
		mpThis->onSignalQuit();
		break;
	case SIGKILL:
		mpThis->onSignalKill();
		break;
	case SIGTERM:
		mpThis->onSignalTerm();
		break;
	case SIGSTOP:
		mpThis->onSignalStop();
		break;		
	default:
		mpThis->onSignalUnknown(Signal);
	}

	signal(Signal, &signalHandler);	
}
