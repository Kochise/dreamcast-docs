/*  Metrowerks Standard Library  */

/*  $Date: 1999/01/23 00:25:39 $ 
 *  $Revision: 1.6 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */
 
/**
 **  hashfun.h
 **
 **  Lib++  : The Modena C++ Standard Library,
 **           Version 2.4, October 1997
 **
 **  Copyright (c) 1995-1997 Modena Software Inc.
 **/

#ifndef MSIPL_HASH_FUNCTIONS
#define MSIPL_HASH_FUNCTIONS

#include <mcompile.h>

#ifdef MSIPL_ANSI_HEADER
#  include <string>     // hh 971220 fixed MOD_INCLUDE
#else
#  include <bstring.h>  // hh 971220 fixed MOD_INCLUDE
#endif

#include <cstdio>       // hh 971220 fixed MOD_C_INCLUDE

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

MSIPL_STD_BEGIN

class hash_fun0 {
protected:
    long prime;
public:
    hash_fun0 (long p = 1073741827) : prime (p) {}
    long operator () (const int& c) const;
};
      
long hash_fun0::operator() (const int& c) const
{
    char str[50];
    sprintf (str, "%d", c);
    const char* d = str;
    int n = strlen(str);
    long h = 0; 
    
    for (int i = 0; i < n; ++i, ++d)
        h = (h << 2) + *d;

    return ((h >= 0) ? (h % prime) : (-h % prime)); 
}

class hash_fun1 {
protected:
    long prime;
public:
    hash_fun1 (long p = 1073741827) : prime (p) {}
    long operator () (const string& c) const;
};
      
long hash_fun1::operator () (const string& c) const
{
    int n = c.size ();
    const char* d = c.data ();
    long h = 0; 
    
    for (int i = 0; i < n; ++i, ++d)
        h = (h << 2) + *d;

    return ((h >= 0) ? (h % prime) : (-h % prime)); 
}

class hash_fun2 {
protected:
    long prime;

public:
    hash_fun2 (long p = 1073741827) : prime (p) {}
    long operator () (const string& c) const;
};

long hash_fun2::operator () (const string& c) const
{
    int n = c.size ();
    const char* d = c.data ();
    long h = n; 
    
    for (int i = 0; i < n; ++i, ++d)
        h = 613*h + *d;

    return ((h >= 0) ? (h % prime) : (-h % prime)); 
}
      
#ifndef _No_Floating_Point

class hash_fun3 {
protected:
    long prime;

public:
    hash_fun3 (long p = 1073741827) : prime (p) {}
    long operator () (const string& c) const;
};

long hash_fun3::operator () (const string& c) const 
{
    int n = c.size ();
    long h = n; 
    const char* d = c.data ();
    const float A = 0.6125423371;
    
    for (int i = 0; i < n; ++i, ++d)
        h = (h ^ ((int) (*d) << (i + 8)));
    
    return ((h >= 0) ? (h*A) : (-h*A)); 
}

#endif // _No_Floating_Point

MSIPL_STD_END

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_HASH_FUNCTIONS */

// hh 971220 fixed MOD_INCLUDE and MOD_C_INCLUDE
// hh 971222 added alignment wraper
// hh 980408 wrapped up in #ifndef _No_Floating_Point
