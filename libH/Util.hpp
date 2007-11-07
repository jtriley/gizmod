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

#include "Debug.hpp"
#include <cstdlib>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////
// Namespace
///////////////////////////////////////

namespace H {

//////////////////////////////////////////////////////////////////////////////
// Global Algorithms
///////////////////////////////////////
	
/**
 * \def    foreach
 * \brief  rename BOOST_FOREACH to foreach for nice readability
**/
#define foreach BOOST_FOREACH
		
/**
 * \brief  Apply function f to all elements in Object o
 * \param  object The object to apply functor to
 * \param  functor The function that modifies each object
 * \return result of std::for_each (unary_function)
 *
 * This is essentially a short cut for std::for_each
**/
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
**/
#define apply_func(object, functor, functee) \
	for_all(object, boost::bind(functor, functee, _1))
	
/**
 * \def    apply_func_args
 * \brief  Apply a function to a set or collection of items with arguments
 * \param  object  The object to apply functor to
 * \param  functor The function object that modifies each object
 * \param  functee The object that the functor belongs to
 * \param  ...     User argument N to pass to Functor
 * \return result of for_all()
 *
 * This is a short cut for H::for_all
**/
#define apply_func_args(object, functor, functee, ...) \
	for_all(object, boost::bind(functor, functee, _1, ## __VA_ARGS__))
	
/**
 * \def    apply_static_func_args
 * \brief  Apply a static function to a set or collection of items with arguments
 * \param  object  The object to apply functor to
 * \param  functor The function object that modifies each object
 * \param  ...     User argument N to pass to Functor
 * \return result of for_all()
 *
 * This is a short cut for H::for_all
**/
#define apply_static_func_args(object, functor, ...) \
	for_all(object, boost::bind(functor, _1, ## __VA_ARGS__))

/**
 * \def    sort_all
 * \brief  Sort all elements
 * \param  object  The object to sort
**/
#define sort_all(object) \
	sort(object.begin(), object.end())

//////////////////////////////////////////////////////////////////////////////
// Global Functors
///////////////////////////////////////
	
/**
 * \brief  Functor that prints an item using the H:cdbg class
 * \param  object  The item to print
**/
inline void dbg_print_item(std::string & object) {
	H::dbg0 << object << std::endl;
}
	
/**
 * \brief  Functor that prints an item
 * \param  object  The item to print
**/
inline void print_item(std::string & object) {
	std::cout << object << std::endl;
}
	
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
**/
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
