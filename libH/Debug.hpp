    /**   
  *********************************************************************
*************************************************************************
*** 
*** \file  Debug.hpp
*** \brief Debug class header file
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

#ifndef __Debug_h
#define __Debug_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "Exception.hpp"
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace H {
	
//////////////////////////////////////////////////////////////////////////////
// Define's, typedefs
///////////////////////////////////////

/**
 * \def   debugOutput
 * \brief Macro to test and output the requested data
**/
#define debugOutput(out) \
	std::cout << out; \
	if (Debug::mLogToFile) { \
		Debug::mLogFile.open(Debug::mLogPath.c_str(), std::ios::app); \
		if (Debug::mLogFile.is_open()) { \
			Debug::mLogFile << out; \
			Debug::mLogFile.close(); \
		} \
	} \
	return dbg

//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class Debug
 * \brief Debug stream class
 *
 * Debug stream class that implements cdbg (with varying verbosity levels)
 * Use cdbg1 to send a debug message that will only be seen if the user has set
 * debug level 1 or higher.  The default is level 0.
**/
class Debug {
public:
	/// Get whether or not debug is enabled
	inline static bool	 	getEnabled() { return mDebug; };
	
	/// Get the verbosity level
	inline static int	 	getVerbosity() { return mVerbosity; };
	
	/// Set whether or not debug is enabled
	inline static void 		setEnabled(bool Enable) { mDebug = Enable; };
	
	/// Set whether or not debug is enabled
	inline static void 		setLog(std::string const & LogFile);
	
	/// Set the verbosity level
	inline static void 		setVerbosity(int Verbosity) { mVerbosity = Verbosity; };
	
	inline friend const Debug& 	operator << (const Debug & dbg, const char * s);
	inline friend const Debug& 	operator << (const Debug & dbg, const std::string & s);
	inline friend const Debug& 	operator << (const Debug & dbg, const char c);
	inline friend const Debug& 	operator << (const Debug & dbg, const int d);
	inline friend const Debug& 	operator << (const Debug & dbg, const unsigned int d);
	inline friend const Debug& 	operator << (const Debug & dbg, const long l);
	inline friend const Debug& 	operator << (const Debug & dbg, const long long ll);
	inline friend const Debug& 	operator << (const Debug & dbg, const bool b);
	inline friend const Debug& 	operator << (const Debug & dbg, const unsigned long l);
	inline friend const Debug& 	operator << (const Debug & dbg, const unsigned long long ll);
	inline friend const Debug& 	operator << (const Debug & dbg, const double lf);
	inline friend const Debug& 	operator << (const Debug & dbg, std::ostream&(*f)(std::ostream&)); // for endl

	inline static bool		testPrint(const Debug& dbg) { return ((dbg.mDebug) && (dbg.mVerbosity >= dbg.mThisVerbosity)); };
	
	Debug(int ThisVerbosity);
	virtual ~Debug();
	
private:
	static bool			mDebug;			///< is debug mode enabled?
	static std::ofstream		mLogFile;		///< the log file
	static std::string		mLogPath;		///< the log's path
	static bool			mLogToFile;		///< log to a file?
	int				mThisVerbosity;		///< verbosity level of this debug object
	static int			mVerbosity;		///< global verbosity level set by the user
};

//////////////////////////////////////////////////////////////////////////////

/**
 * \brief  Set the debug log
**/
inline void Debug::setLog(std::string const & LogFile) {
	Debug::mLogFile.open(LogFile.c_str(), std::ios::app);
	if (!Debug::mLogFile.is_open()) {
		Debug::mLogPath = "";
		Debug::mLogToFile = false;
		throw H::Exception("Invalid Debug Log [" + LogFile + "] Specified! -- Logging to File Disabled", __FILE__, __FUNCTION__, __LINE__);
	}
	Debug::mLogPath = LogFile;
	Debug::mLogToFile = true;
	Debug::mLogFile.close();
}

/**
 * \brief  Debug insertion operator for string
**/
inline const Debug& operator << (const Debug & dbg, const std::string & out) {
	debugOutput(out);
}

/**
 * \brief  Debug insertion operator for const char *
**/
inline const Debug& operator << (const Debug & dbg, const char * out) {
	debugOutput(out);
}

/**
 * \brief  Debug insertion operator for char
**/
inline const Debug& operator << (const Debug & dbg, const char out) {
	debugOutput(out);
}

/**
 * \brief  Debug insertion operator for int
**/
inline const Debug& operator << (const Debug & dbg, const int out) {
	debugOutput(out);
}

/**
 * \brief  Debug insertion operator for uint
**/
inline const Debug& operator << (const Debug & dbg, const unsigned int out) {
	debugOutput(out);
}

/**
 * \brief  Debug insertion operator for long
**/
inline const Debug& operator << (const Debug & dbg, const long out) {
	debugOutput(out);
}

/**
 * \brief  Debug insertion operator for long
**/
inline const Debug& operator << (const Debug & dbg, const long long out) {
	debugOutput(out);
}

/**
 * \brief  Debug insertion operator for bool
**/
inline const Debug& operator << (const Debug & dbg, const bool out) {
	debugOutput(out);
}

/**
 * \brief  Debug insertion operator for ulong
**/
inline const Debug& operator << (const Debug & dbg, const unsigned long out) {
	debugOutput(out);
}

/**
 * \brief  Debug insertion operator for ulong
**/
inline const Debug& operator << (const Debug & dbg, const unsigned long long out) {
	debugOutput(out);
}

/**
 * \brief  Debug insertion operator for double
**/
inline const Debug& operator << (const Debug & dbg, const double out) {
	debugOutput(out);
}

/**
 * \brief  Debug insertion operator for endl et al
**/
inline const Debug& operator << (const Debug & dbg, std::ostream&(* out)(std::ostream &)) {
	debugOutput(out);
}

static const Debug dbg0(0); ///< Instantiation of cdbg level 0
static const Debug dbg1(1); ///< Instantiation of cdbg level 1
static const Debug dbg2(2); ///< Instantiation of cdbg level 2
static const Debug dbg3(3); ///< Instantiation of cdbg level 3
static const Debug dbg4(4); ///< Instantiation of cdbg level 4
static const Debug dbg5(5); ///< Instantiation of cdbg level 5

#define cdbg	if (H::Debug::testPrint(dbg0)) H::dbg0
#define cdbg1	if (H::Debug::testPrint(dbg1)) H::dbg1
#define cdbg2	if (H::Debug::testPrint(dbg2)) H::dbg2
#define cdbg3	if (H::Debug::testPrint(dbg3)) H::dbg3
#define cdbg4	if (H::Debug::testPrint(dbg4)) H::dbg4
#define cdbg5	if (H::Debug::testPrint(dbg5)) H::dbg5
				
} // H namespace

//////////////////////////////////////////////////////////////////////////////

#endif // __Debug_h
