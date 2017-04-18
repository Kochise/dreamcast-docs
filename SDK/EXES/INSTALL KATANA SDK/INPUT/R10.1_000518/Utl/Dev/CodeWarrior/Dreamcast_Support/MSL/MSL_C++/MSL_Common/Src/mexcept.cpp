/*  Metrowerks Standard Library  */

/*  $Date: 1999/01/23 00:26:07 $ 
 *  $Revision: 1.6 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */

/**
 **  Lib++  : The Modena C++ Standard Library,
 **           Version 2.4, October 1997
 **
 **  Copyright (c) 1995-1997 Modena Software Inc.
 **/

#include <mcompile.h>

#ifdef MSIPL_ANSI_HEADER
#include <stdexcept> // hh 971220 fixed MOD_INCLUDE
#else
#include <mexcept.h> // hh 971220 fixed MOD_INCLUDE
#endif

#ifdef MSIPL_EXCEPT
#ifdef __EDG_EXCEPT_CLASSES
#include <typeinfo>  // hh 971220 fixed MOD_INCLUDE
#endif
#endif

#include <cstring>   // hh 971220 fixed MOD_C_INCLUDE

#ifdef MSIPL_EXCEPT
#ifndef __EDG_EXCEPT_CLASSES
#ifdef MSIPL_ANSI_HEADER
#include <string>    // hh 971220 fixed MOD_INCLUDE
#else
#include <bstring>   // hh 971220 fixed MOD_INCLUDE
#endif
#endif
#endif

MSIPL_STD_BEGIN

#ifdef MSIPL_EXCEPT
#ifndef __EDG_EXCEPT_CLASSES
/*   // hh 971226 redesigned exception in a fit of common sense
exception::exception (const string& what_arg) MSIPL_THROW
{
    desc = new string (what_arg);
    alloced = true;
}

exception::exception (const exception& exarg) MSIPL_THROW
{
    desc = ((alloced = exarg.alloced) ?
             new string (exarg.what ()) : 0);
}

exception&
exception::operator= (const exception& exarg) MSIPL_THROW
{
    if (this != &exarg)
    {
        if (alloced) delete (string*)desc;
        desc = ((alloced = exarg.alloced) ?
                 new string (exarg.what ()) : 0);
    }
    return *this;
}

exception::~exception () MSIPL_THROW
{
    if (alloced) delete (string*)desc;
}

const char*
exception::what () const MSIPL_THROW
{
    if (alloced && desc->size ()) return desc->data ();
    else return "";  // unnamedException
}
*/

/*
const char*  bad_alloc::alloc_msg = "Allocation Failure";    // hh 971226 used to be a string

const char*
bad_alloc::what () const MSIPL_THROW { return alloc_msg.data (); }
*/
/*
bad_typeid::bad_typeid () MSIPL_THROW
: exception (string ()) { }

bad_cast::~bad_cast () MSIPL_THROW { }

bad_typeid::~bad_typeid () MSIPL_THROW { }
*/
#else

msipl_exception::msipl_exception (const char* what_arg) MSIPL_THROW
{
   size_t len = (what_arg ? strlen (what_arg) : 0);
   ptr = (len ? new (__FILE, __LINE__) char[len+1] : 0);
   if (ptr) strcpy (ptr, what_arg);
}

msipl_exception::msipl_exception (const msipl_exception& exarg) MSIPL_THROW
{
   ptr = (exarg.ptr ? new (__FILE, __LINE__) char[strlen (exarg.ptr)+1] : 0);
   if (ptr) strcpy (ptr, exarg.ptr);
}

msipl_exception&
msipl_exception::operator= (const msipl_exception& exarg) MSIPL_THROW
{
   if (this != &exarg)
   {
      if (ptr) delete[] ptr;
      ptr = (exarg.ptr ? new (__FILE, __LINE__) char[strlen (exarg.ptr)+1] : 0);
      if (ptr) strcpy (ptr, exarg.ptr);
   }
   return *this;
}

const char*
msipl_exception::what () const MSIPL_THROW
{
    return (ptr ? ptr : "");
}

msipl_exception::~msipl_exception () MSIPL_THROW
{
   if (ptr) delete[] ptr;
}

#endif

// The follwoing code is common, whether EDG
// exception classes are used or not.
/*
logic_error::~logic_error () MSIPL_THROW { }

domain_error::~domain_error () MSIPL_THROW { }

invalid_argument::~invalid_argument () MSIPL_THROW { }

length_error::~length_error () MSIPL_THROW { }

out_of_range::~out_of_range () MSIPL_THROW { }

runtime_error::~runtime_error () MSIPL_THROW { }

range_error::~range_error () MSIPL_THROW { }

overflow_error::~overflow_error () MSIPL_THROW { }
*/
#ifndef __EDG_EXCEPT_CLASSES
/*     // hh 971229 commented out.  Everything is inlined
bad_alloc&
bad_alloc::operator= (const bad_alloc& ) MSIPL_THROW
{
   return *this;
}

bad_alloc::~bad_alloc () MSIPL_THROW { }
*/
#endif

#endif /* MSIPL_EXCEPT */

MSIPL_STD_END

// hh 971220 fixed MOD_INCLUDE and MOD_C_INCLUDE
// hh 971226 redesigned exception to not be dependent on string
// hh 971226 bad_alloc inlined
// hh 971229 commented out just about everything.  Is inlined.
