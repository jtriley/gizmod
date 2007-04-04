    /**
  *********************************************************************
*************************************************************************
*** 
*** \file  Util.hpp
*** \brief Util class header file
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

#ifndef __Util_h
#define __Util_h

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <cstdlib>
#include <boost/any.hpp>
#include <boost/function.hpp>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace H {

//////////////////////////////////////////////////////////////////////////////
// Global Functions
///////////////////////////////////////
	
/**
 * \brief  Apply function f to all elements in Object o
 * \param  object The object to apply functor to
 * \param  functor The function that modifies each object
 * \return result of std::for_each (unary_function)
 *
 * This is essentially a short cut for std::for_each
 */
template<class Object, class Functor>
inline Functor for_all(Object & object, Functor functor) {
	return std::for_each(object.begin(), object.end(), functor);
}

/**
 * \def    apply_func
 * \brief  Apply a function to a set or collection of items
 * \param  object  The object to apply functor to
 * \param  functor The function object that modifies each object
 * \param  functee The object that the functor belongs to
 * \return result of for_all()
 *
 * This is a short cut for H::for_all
 */
#define apply_func(object, functor, functee) \
	for_all(object, boost::bind(functor, functee, _1))
	
//////////////////////////////////////////////////////////////////////////////
// Class Definition
///////////////////////////////////////

/**
 * \class Util
 * \brief Main Util class
 *
 * This class provides static time routines for sleeping and finding the current time
 *
 * It also can be instantiated to provide a time duration watcher
 */
class Util {
public:
	// Public Member Functions
	
	// Construction / Deconstruction
	Util();
	virtual ~Util();

private:
	// Private Member Functions

	// Private Member Variables
};

} // H namespace

#endif // __Util_h
