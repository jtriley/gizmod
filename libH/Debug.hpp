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

#include <iostream>
#include <string>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

/**
 * \namespace H
 * \brief     H namespace
 *
 * All code in the H namespace gets its inspiration from the best movie ever made:
 *    Hackers
 */
namespace H {
	
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
 */
class Debug {
public:
	/// Get whether or not debug is enabled
	inline static bool	 	getDebugEnabled() { return mDebug; };
	
	/// Get the verbosity level
	inline static bool	 	getDebugVerbosity() { return mVerbosity; };
	
	/// Set whether or not debug is enabled
	inline static void 		setDebugEnabled(bool Enable) { mDebug = Enable; };
	
	/// Set the verbosity level
	inline static void 		setDebugVerbosity(int Verbosity) { mVerbosity = Verbosity; };
	
	inline friend const Debug& 	operator << (const Debug & dbg, const char * s);
	inline friend const Debug& 	operator << (const Debug & dbg, const std::string & s);
	inline friend const Debug& 	operator << (const Debug & dbg, const char c);
	inline friend const Debug& 	operator << (const Debug & dbg, const int d);
	inline friend const Debug& 	operator << (const Debug & dbg, const long l);
	inline friend const Debug& 	operator << (const Debug & dbg, const bool b);
	inline friend const Debug& 	operator << (const Debug & dbg, const size_t d);
	inline friend const Debug& 	operator << (const Debug & dbg, const double lf);
	inline friend const Debug& 	operator << (const Debug & dbg, std::ostream&(*f)(std::ostream&)); // for endl

	Debug(int ThisVerbosity);
	virtual ~Debug();
	
private:
	inline static bool		testPrint(const Debug& dbg) { return ((dbg.mDebug) && (dbg.mVerbosity >= dbg.mThisVerbosity)); };

	static bool			mDebug;			///< is debug mode enabled?
	int				mThisVerbosity;		///< verbosity level of this debug object
	static int			mVerbosity;		///< global verbosity level set by the user
};

//////////////////////////////////////////////////////////////////////////////

/**
 * Debug insertion operator for string
 */
inline const Debug& operator << (const Debug & dbg, const std::string & s) {
	if (Debug::testPrint(dbg))
		std::cout << s;
	return dbg;
}

/**
 * Debug insertion operator for const char *
 */
inline const Debug& operator << (const Debug & dbg, const char * s) {
	if (Debug::testPrint(dbg))
		std::cout << s;
	return dbg;
}

/**
 * Debug insertion operator for char
 */
inline const Debug& operator << (const Debug & dbg, const char c) {
	if (Debug::testPrint(dbg))
		std::cout << c;
	return dbg;
}

/**
 * Debug insertion operator for int
 */
inline const Debug& operator << (const Debug & dbg, const int d) {
	if (Debug::testPrint(dbg))
		std::cout << d;
	return dbg;
}

/**
 * Debug insertion operator for long
 */
inline const Debug& operator << (const Debug & dbg, const long l) {
	if (Debug::testPrint(dbg))
		std::cout << l;
	return dbg;
}

/**
 * Debug insertion operator for bool
 */
inline const Debug& operator << (const Debug & dbg, const bool b) {
	if (Debug::testPrint(dbg))
		std::cout << b;
	return dbg;
}

/**
 * Debug insertion operator for size_t
 */
inline const Debug& operator << (const Debug & dbg, const size_t i) {
	if (Debug::testPrint(dbg))
		std::cout << i;
	return dbg;
}

/**
 * Debug insertion operator for double
 */
inline const Debug& operator << (const Debug & dbg, const double lf) {
	if (Debug::testPrint(dbg))
		std::cout << lf;
	return dbg;
}

/**
 * Debug insertion operator for endl et al
 */
inline const Debug& operator << (const Debug & dbg, std::ostream&(* f)(std::ostream &)) {
	if (Debug::testPrint(dbg))
		std::cout << f;
	return dbg;
}

static const Debug cdbg(0);
static const Debug cdbg1(1);
static const Debug cdbg2(2);
static const Debug cdbg3(3);
static const Debug cdbg4(4);
static const Debug cdbg5(5);

} // H namespace

//////////////////////////////////////////////////////////////////////////////

#endif // __Debug_h
