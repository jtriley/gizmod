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

Copyright (c) 2006, Tim Burrell
All rights reserved.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

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
 * This class belongs to libH
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
inline const Debug& operator << (const Debug & dbg, const int i) {
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
