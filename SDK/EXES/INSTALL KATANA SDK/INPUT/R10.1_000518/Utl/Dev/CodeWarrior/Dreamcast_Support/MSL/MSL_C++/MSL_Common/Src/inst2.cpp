/*  Metrowerks Standard Library  */

/*  $Date: 1999/01/23 00:26:06 $ 
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
/*
#include <mcompile.h>


#include <complex>      // hh 971220 fixed MOD_INCLUDE
#include <locale>    // hh 971220 fixed MOD_INCLUDE, changed from mlocale.h
#include <vector>       // hh 971220 fixed MOD_INCLUDE
#include <deque>        // hh 971220 fixed MOD_INCLUDE
#include <list>         // hh 971220 fixed MOD_INCLUDE
#include <slist.h>      // hh 971220 fixed MOD_INCLUDE

#ifdef MSIPL_INSTANTIATE_ALL
#include <map>          // hh 971220 fixed MOD_INCLUDE
#include <set>          // hh 971220 fixed MOD_INCLUDE
#include <hashfun.h>    // hh 971220 fixed MOD_INCLUDE
#include <hashmap.h>    // hh 971220 fixed MOD_INCLUDE
#include <hashset.h>    // hh 971220 fixed MOD_INCLUDE
#include <hashmset.h>   // hh 971220 fixed MOD_INCLUDE
#include <hashmmap.h>   // hh 971220 fixed MOD_INCLUDE
#endif

#ifdef MSIPL_EXPLICIT_INSTANTIATION

MSIPL_USING_STD

template class deque<int, allocator<int> >;
template class deque<char, allocator<char> >;

template class list<int, allocator<int> >;
template class list<char, allocator<char> >;

template class slist<int, allocator<int> >;
template class slist<char, allocator<char> >;
//
// Containers
//
template class vector<void*, allocator<void*> >;
template class vector<long, allocator<long> >;
template class vector<char, allocator<char> >;
#ifdef MSIPL_PARTIAL_SPECIALIZATION
template class vector<bool, allocator<int> >;
template class vector<bool, allocator<unsigned int> >;
template class vector<bool, allocator<long> >;
template class vector<bool, allocator<unsigned long> >;
#endif
template class vector<locale::facet*, allocator<locale::facet*> >;

template vector<char, allocator<char> >::iterator 
  copy (vector<char, allocator<char> >::iterator,
        vector<char, allocator<char> >::iterator,
        vector<char, allocator<char> >::iterator);

template vector<bool, DefAllocator<unsigned int> >::iterator 
  copy (vector<bool, DefAllocator<unsigned int> >::iterator,
        vector<bool, DefAllocator<unsigned int> >::iterator,
        vector<bool, DefAllocator<unsigned int> >::iterator);
template vector<bool, DefAllocator<unsigned int> >::iterator 
  copy (const bool*, const bool*,
        vector<bool, DefAllocator<unsigned int> >::iterator);
template vector<bool, DefAllocator<unsigned int> >::iterator 
  copy (vector<bool, DefAllocator<unsigned int> >::const_iterator,
        vector<bool, DefAllocator<unsigned int> >::const_iterator,
        vector<bool, DefAllocator<unsigned int> >::iterator);
template vector<locale::facet*, allocator<locale::facet*> >::iterator 
  copy (vector<locale::facet*, allocator<locale::facet*> >::iterator,
        vector<locale::facet*, allocator<locale::facet*> >::iterator,
        vector<locale::facet*, allocator<locale::facet*> >::iterator);

template back_insert_iterator<deque<int, allocator<int> > >
  copy(deque<int, allocator<int> >::const_iterator,
       deque<int, allocator<int> >::const_iterator,
       back_insert_iterator<deque<int, allocator<int> > >);
template insert_iterator<deque<int, allocator<int> > >
  copy(deque<int, allocator<int> >::const_iterator,
       deque<int, allocator<int> >::const_iterator,
       insert_iterator<deque<int, allocator<int> > >);
template back_insert_iterator<deque<char, allocator<char> > >
  copy(deque<char, allocator<char> >::const_iterator,
       deque<char, allocator<char> >::const_iterator,
       back_insert_iterator<deque<char, allocator<char> > >);
template insert_iterator<deque<char, allocator<char> > >
  copy(deque<char, allocator<char> >::const_iterator,
       deque<char, allocator<char> >::const_iterator,
       insert_iterator<deque<char, allocator<char> > >);
template deque<int, allocator<int> >::iterator
  copy(deque<int, allocator<int> >::iterator,
       deque<int, allocator<int> >::iterator,
       deque<int, allocator<int> >::iterator);
template deque<int, allocator<int> >::iterator
  copy(deque<int, allocator<int> >::const_iterator,
       deque<int, allocator<int> >::const_iterator,
       deque<int, allocator<int> >::iterator);
template deque<char, allocator<char> >::iterator
  copy(deque<char, allocator<char> >::iterator,
       deque<char, allocator<char> >::iterator,
       deque<char, allocator<char> >::iterator);
template deque<char, allocator<char> >::iterator
  copy(deque<char, allocator<char> >::const_iterator,
       deque<char, allocator<char> >::const_iterator,
       deque<char, allocator<char> >::iterator);
template back_insert_iterator<deque<int, allocator<int> > >
  copy (const int*, const int*,
        back_insert_iterator<deque<int, allocator<int> > >);
template back_insert_iterator<deque<char, allocator<char> > >
  copy (const char*, const char*,
        back_insert_iterator<deque<char, allocator<char> > >);
template deque<int, allocator<int> >::iterator
  copy (const int*, const int*, deque<int, allocator<int> >::iterator);
template deque<char, allocator<char> >::iterator
  copy (const char*, const char*, deque<char, allocator<char> >::iterator);

template deque<int, allocator<int> >::iterator
  copy_backward(deque<int, allocator<int> >::iterator,
                deque<int, allocator<int> >::iterator,
                deque<int, allocator<int> >::iterator);
template deque<char, allocator<char> >::iterator
  copy_backward(deque<char, allocator<char> >::iterator,
                deque<char, allocator<char> >::iterator,
                deque<char, allocator<char> >::iterator);

template void
  fill(deque<int, allocator<int> >::iterator,
       deque<int, allocator<int> >::iterator, const int &);
template void
  fill(deque<char, allocator<char> >::iterator,
       deque<char, allocator<char> >::iterator, const char &);

template insert_iterator <deque<int, allocator<int> > >
  inserter(deque<int, allocator<int> > &,
           deque<int, allocator<int> >::iterator);
template insert_iterator <deque<char,allocator<char> > >
  inserter(deque<char, allocator<char> > &,
           deque<char, allocator<char> >::iterator);

template back_insert_iterator <deque<int, allocator<int> > >
  back_inserter(deque<int, allocator<int> > &);
template back_insert_iterator <deque<char, allocator<char> > >
  back_inserter(deque<char, allocator<char> > &);

#ifndef MSIPL_EDG232

template bool 
  operator!= (const complex<int>&, const complex<int>&);
#ifndef _No_Floating_Point
template bool 
  operator!= (const complex<double>&, const complex<double>&);
#endif

#else

template bool 
  MSIPLSTD::operator!= (const complex<int>&, const complex<int>&);
#ifndef _No_Floating_Point
template bool 
  MSIPLSTD::operator!= (const complex<double>&, const complex<double>&);
#endif

#endif


// Containers: maps, sets. hash_maps & hash_msets.
#ifdef MSIPL_INSTANTIATE_ALL
template class rb_tree<int, pair<int, int>, select1st<pair<int, int>, int>,
                          less<int>,  allocator<pair<int, int> > >;
template class rb_tree<string, pair<string, string>, select1st<pair<string,
         string>, string>, less<string>,  allocator<pair<string, string> > >;

template class hash_table<int, int, ident<int, int>, hash_fun0,
                             equal_to<int>, allocator<int> >;
template class hash_table<char, char, ident<char, char>, hash_fun0,
                             equal_to<char>, allocator<char> >;
template class hash_table<string, string, ident<string, string>, hash_fun1,
                             equal_to<string>, allocator<string> >;

template class hash_multimap<int, int, hash_fun0, equal_to<int> >;
template class hash_multiset<int, hash_fun0, equal_to<int> >;

template class hash_map<int, int, hash_fun0, equal_to<int> >;
template class hash_set<int, hash_fun0, equal_to<int> >;


template class multimap<int, int, less<int>, allocator<pair<int, int> > >;
template class map<int, int, less<int>, allocator<pair<int, int> > >;

template class multimap<int, string, less<int>, allocator<pair<int, string> > >;
template class map<int, string, less<int>, allocator<pair<int, string> > >;

template class set<int, less<int>, allocator<int> >;
template class multiset<int, less<int>, allocator<int> >;

#endif /* MSIPL_INSTANTIATE_ALL */

//#endif /* MSIPL_EXPLICIT_INSTANTIATION */

// hh 971220 fixed MOD_INCLUDE
// hh 980408 wrapped up in #ifndef _No_Floating_Point
