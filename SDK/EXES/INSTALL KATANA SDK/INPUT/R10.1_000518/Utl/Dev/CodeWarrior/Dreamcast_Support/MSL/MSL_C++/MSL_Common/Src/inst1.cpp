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

#include <memory>     // hh 971220 fixed MOD_INCLUDE

#include <string>  // hh 971220 fixed MOD_INCLUDE, changed from bstring.h

#include <locale>  // hh 971220 fixed MOD_INCLUDE, changed from mlocale.h
#include <mtools.h>   // hh 971220 fixed MOD_INCLUDE

#include <ios>        // hh 971220 fixed MOD_INCLUDE
#include <streambuf>  // hh 971220 fixed MOD_INCLUDE
#include <fstream>    // hh 971220 fixed MOD_INCLUDE
#include <sstream>    // hh 971220 fixed MOD_INCLUDE

#ifdef MSIPL_EXPLICIT_INSTANTIATION

MSIPL_USING_STD

template locale::facet**
  copy(locale::facet *const *, locale::facet *const *, locale::facet **);
template void**
  copy(void **, void **, void **);
template int**
  copy (int**, int**, int**);
template char**
  copy (char**, char**, char**);
template long*
  copy (long*, long* , long*);
template long*
  copy (const long*, const long* , long*);
template char*
  copy (const char*, const char* , char*);
template basic_string<char, char_traits<char>, allocator<char> > *
  copy(const basic_string<char, char_traits<char>, allocator<char> > *,
       const basic_string<char, char_traits<char>, allocator<char> > *,
       basic_string<char, char_traits<char>, allocator<char> > *);
template basic_string<char, char_traits<char>, allocator<char> > *
  copy(basic_string<char, char_traits<char>, allocator<char> > *,
       basic_string<char, char_traits<char>, allocator<char> > *,
       basic_string<char, char_traits<char>, allocator<char> > *);
template void**
  copy(void *const *, void *const *, void **);

template long*
  copy_backward (long*, long* , long*);
#ifndef _No_Floating_Point
template long double*
  copy_backward (long double*, long double* , long double*);
#endif
template void**
  copy_backward (void **, void **, void **);
template char*
  copy_backward (char *, char* , char*);
template vector<bool, allocator<unsigned int> >::iterator 
  copy_backward (vector<bool, allocator<unsigned int> >::iterator,
                 vector<bool, allocator<unsigned int> >::iterator,
                 vector<bool, allocator<unsigned int> >::iterator);
template locale::facet**
  copy_backward (locale::facet **, locale::facet **, locale::facet **);

template void
  fill (long*, long*, const long&);
template void
  fill (char*, char*, const char&);
template void
  fill (unsigned int*, unsigned int*, const int&);
template void
  fill (vector<bool, allocator<unsigned int> >::iterator,
        vector<bool, allocator<unsigned int> >::iterator, const bool&);
template void
  fill(void **, void **, void *const &);
template void
  fill(locale::facet **, locale::facet **, locale::facet *const &);
template void
  fill(basic_string<char, char_traits<char>, allocator<char> > *,
       basic_string<char, char_traits<char>, allocator<char> > *,
       const basic_string<char, char_traits<char>, allocator<char> > &);

template vector<bool, allocator<unsigned int> >::iterator
  fill_n (vector<bool, allocator<unsigned int> >::iterator,
          unsigned int, const bool&);
template char*
  fill_n (char*, unsigned int, const char&);

template void
  uninitialized_fill_n (long*, unsigned int, const long&);
#ifndef _No_Floating_Point
template void 
  uninitialized_fill_n (long double*, unsigned int, const long double&);
#endif
template void
  uninitialized_fill_n(void **, unsigned int, void *const &);
template void 
  uninitialized_fill_n(locale::facet **, unsigned int,
                       locale::facet *const &);
template void  
  uninitialized_fill_n(basic_string<char, char_traits<char>,
                                    allocator<char> > *,
                       unsigned int,
                       const basic_string<char, char_traits<char>,
                                          allocator<char> > &);

template long*
  uninitialized_copy (long*, long* , long*);
#ifndef _No_Floating_Point
template long double*
  uninitialized_copy (long double*, long double* , long double*);
#endif
template char*
  uninitialized_copy (const char *, const char* , char*);
template long*
  uninitialized_copy (const long*, const long* , long*);
template void**
  uninitialized_copy(void **, void **, void **);
template void**
  uninitialized_copy(void *const *, void *const *, void **);
template locale::facet**
  uninitialized_copy(locale::facet **, locale::facet **, 
                     locale::facet **);
template basic_string<char, char_traits<char>, allocator<char> > *
  uninitialized_copy(basic_string<char, char_traits<char>, allocator<char> >*,
                     basic_string<char, char_traits<char>, allocator<char> >*,
                     basic_string<char, char_traits<char>, allocator<char> >*);
template basic_string<char, char_traits<char>, allocator<char> > *
  uninitialized_copy(const basic_string<char, char_traits<char>,
                                        allocator<char> > *,
                     const basic_string<char, char_traits<char>,
                                        allocator<char> > *,
                     basic_string<char, char_traits<char>,
                                        allocator<char> > *);

#ifdef MSIPL_MULTITHREAD
#ifndef MSIPL_LINUX
template class mutex_arith<int, mutex>;
template class mutex_arith<size_t, mutex>;
template class mutex_block<mutex>;
template class mutex_block<rw_mutex>;
#endif
#endif

template class basic_streambuf<char, char_traits<char> >;
template class basic_stringbuf<char, char_traits<char>, allocator<char> >;

template class basic_istream<char, char_traits<char> >;
template class basic_ostream<char, char_traits<char> >;
template class basic_iostream<char, char_traits<char> >;

template class basic_istringstream<char, char_traits<char>, allocator<char> >;
template class basic_ostringstream<char, char_traits<char>, allocator<char> >;
template class basic_stringstream<char, char_traits<char>, allocator<char> >;

template basic_ostream<char, char_traits<char> >&
    endl(basic_ostream<char, char_traits<char> >&);
template basic_ostream<char, char_traits<char> >&
    ends(basic_ostream<char, char_traits<char> >&);

template class basic_filebuf<char, char_traits<char> >;
template class basic_ifstream<char, char_traits<char> >;
template class basic_ofstream<char, char_traits<char> >;
template class basic_fstream<char, char_traits<char> >;

template class numpunct<char>;
template class timepunct<char>;
template class moneypunct<char, true>;
template class moneypunct<char, false>;

template class
  num_get<char, istreambuf_iterator<char, char_traits<char> > >;
template class
  num_put<char, ostreambuf_iterator<char, char_traits<char> > >;

template class num_get<char, char*>;
template class num_put<char, char*>;

template class
  time_get<char, istreambuf_iterator<char, char_traits<char> > >;
template class
  time_put<char, ostreambuf_iterator<char, char_traits<char> > >;

template class
  money_get<char, istreambuf_iterator<char, char_traits<char> > >;
template class
  money_put<char, ostreambuf_iterator<char, char_traits<char> > >;

template class money_get<char,  char*>;
template class money_put<char,  char*>;

template const moneypunct<char, false>&
  use_facet(const locale &, moneypunct<char, false> *);
template const moneypunct<char, true>&
  use_facet(const locale &, moneypunct<char, true> *);
template const numpunct<char>&
  use_facet(const locale &, numpunct<char> *);
template const collate<char>&
  use_facet(const locale &, collate<char> *);
template const codecvt<char, char, int>&
  use_facet(const locale &, codecvt<char, char, int> *);

template const
  num_get<char, istreambuf_iterator<char, char_traits<char> > >&
  use_facet(const locale &, num_get<char,
               istreambuf_iterator<char, char_traits<char> > >*);
template const
  num_put<char, ostreambuf_iterator<char, char_traits<char> > >&
  use_facet(const locale &, num_put<char,
               ostreambuf_iterator<char, char_traits<char> > >*);

template const
  ctype<char>& use_facet(const locale &, ctype<char>*);


template bool
  has_facet (const locale &, num_get<char,
             istreambuf_iterator<char, char_traits<char> > >*);
template bool
  has_facet (const locale &, num_put<char,
             ostreambuf_iterator<char, char_traits<char> > >*);
template bool
  has_facet(const locale &, ctype<char>*);
template bool
  has_facet(const locale &, moneypunct<char, false> *);
template bool
  has_facet(const locale &, moneypunct<char, true> *);
template bool
  has_facet(const locale &, numpunct<char> *);
template bool
  has_facet(const locale &, collate<char> *);
template bool
  has_facet(const locale &, codecvt<char, char, int> *);

template 
  bool isdigit(char, const locale&);
template 
  bool isupper(char, const locale&);
template 
  bool isspace(char, const locale&);


template class basic_string <char, char_traits<char>, allocator<char> >;

template class basic_ios<char, char_traits<char> >;

template basic_string<char, char_traits<char>, allocator<char> >&
  __msipl_pad(const ios_base&, char,
              basic_string<char, char_traits<char>, allocator<char> > &,
              int);

template int
  __msipl_sprintf(char*, size_t, const char*, unsigned int);
template int
  __msipl_sprintf(char*, size_t, const char*, unsigned long);
#ifndef _No_Floating_Point
template int
  __msipl_sprintf(char*, size_t, const char*, double);
#endif
template int
  __msipl_sprintf(char*, size_t, const char*, long);
#ifndef _No_Floating_Point
template int
  __msipl_sprintf(char*, size_t, const char*, long double);
#endif
template int
  __msipl_sprintf(char*, size_t, const char*, int);
template int
  __msipl_sprintf(char*, size_t, const char*, void*);

#ifndef _No_Floating_Point
template int
  __msipl_sscanf(char*, const char*, float*); 
#endif
template int
  __msipl_sscanf(char*, const char*, void**); 
#ifndef _No_Floating_Point
template int
  __msipl_sscanf(char*, const char*, long double*); 
#endif

#ifndef _No_Floating_Point
template double __msipl_strtod(const char *, char **);
#endif
template bool __msipl_strtol(const char *, long&, int);
template bool __msipl_strtoul(const char *, unsigned long&, int);

template size_t
  __msipl_strftime(char *, size_t, const char *, const tm *);

template basic_string<char, char_traits<char>, allocator<char> >
  __msipl_insert_thsep(basic_string<char, char_traits<char>, allocator<char> >,
                       const basic_string<char, char_traits<char>,
                                          allocator<char> > &,
                       char, char); 

template char*
  __msipl_fmt(const ios_base&, char *, int);

template basic_ostream<char, char_traits<char> >&
  MSIPLSTD::operator<< (basic_ostream<char, char_traits<char> >&,
                   const basic_string<char, char_traits<char>,
                                      allocator<char> >&);

#endif /* MSIPL_EXPLICIT_INSTANTIATION */

// hh 971220 fixed MOD_INCLUDE
// hh 980408 wrapped up in #ifndef _No_Floating_Point
