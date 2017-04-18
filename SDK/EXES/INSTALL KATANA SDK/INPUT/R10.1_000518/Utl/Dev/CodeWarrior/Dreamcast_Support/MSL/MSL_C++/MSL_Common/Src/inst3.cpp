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

#include <mcompile.h>

#include <valarray>    // hh 971220 fixed MOD_INCLUDE

#ifdef MSIPL_EXPLICIT_INSTANTIATION

MSIPL_USING_STD

template class valarray <int>;
template class valarray <long>;
template class valarray <size_t>;
template class valarray <short>;

template class mask_array <short>;
template class mask_array <long>;
template class mask_array <int>;
template class mask_array <unsigned int>;

template class slice_array <short>;
template class slice_array <long>;
template class slice_array <int>;
template class slice_array <unsigned int>;

template class gslice_array <short>;
template class gslice_array <long>;
template class gslice_array <int>;
template class gslice_array <unsigned int>;

template class indirect_array <short>;
template class indirect_array <long>;
template class indirect_array <int>;
template class indirect_array <unsigned int>;

#ifndef MSIPL_EDG232

template void __unguarded_linear_insert (unsigned int*, unsigned int);
template void __final_insertion_sort (unsigned int*, unsigned int*);
template void __quick_sort_loop_aux (unsigned int*, unsigned int*,
                                     unsigned int);

template short* __msipl_copy_value (short*, short*, const short&, short*,
                                    __msipl_shift_right<short>);
template short* __msipl_copy_array (short*, short*, const short*, short*,
                                    __msipl_shift_right<short>);

template short* __msipl_copy_value (const short*, const short*, short*,
                                    __msipl_not<short>);
template short* __msipl_copy_value (const short*,const  short*, short*,
                                    __msipl_complement<short>);

template short* __msipl_copy_value (short*, short*, const short&, short*,
                                    __msipl_shift_left<short>);
template short* __msipl_copy_array (short*, short*, const short*, short*,
                                    __msipl_shift_left<short>);

template short* __msipl_copy_value (short*, short*, const short&, short*,
                                    __msipl_caret<short>);
template short* __msipl_copy_array (short*, short*, const short*, short*,
                                    __msipl_caret<short>);

template short* __msipl_copy_value (short*, short*, const short&, short*,
                                    modulus<short>);
template short* __msipl_copy_array (short*, short*, const short*, short*,
                                    modulus<short>);
template short* __msipl_copy_value (short*, short*, const short&, short*,
                                    divides<short>);
template short* __msipl_copy_array (short*, short*, const short*, short*,
                                    divides<short>);

template short* __msipl_copy_value (short*, short*, const short&, short*,
                                    __msipl_bitwise_and<short>);
template short* __msipl_copy_array (short*, short*, const short*, short*,
                                    __msipl_bitwise_and<short>);

template short* __msipl_copy_value (short*, short*, const short&, short*,
                                    __msipl_bitwise_or<short>);
template short* __msipl_copy_array (short*, short*, const short*, short*,
                                    __msipl_bitwise_or<short>);

template short* __msipl_copy_value (short*, short*, const short&, short*,
                                   minus<short>);
template short* __msipl_copy_array (short*, short*, const short*, short*,
                                   minus<short>);

template short* __msipl_copy_value (short*, short*, const short&, short*,
                                   plus<short>);
template short* __msipl_copy_array (short*, short*, const short*, short*,
                                   plus<short>);

template short* __msipl_copy_value (short*, short*, const short&, short*,
                                   multiplies<short>);
template short* __msipl_copy_array (short*, short*, const short*, short*,
                                   multiplies<short>);

template long* __msipl_copy_value (long*, long*, const long&, long*,
                                    __msipl_shift_right<long>);
template long* __msipl_copy_array (long*, long*, const long*, long*,
                                    __msipl_shift_right<long>);

template long* __msipl_copy_value (const long*, const long*, long*,
                                  __msipl_not<long>);
template long* __msipl_copy_value (const long*, const long*, long*,
                                  __msipl_complement<long>);

template long* __msipl_copy_value (long*, long*, const long&, long*,
                                    __msipl_shift_left<long>);
template long* __msipl_copy_array (long*, long*, const long*, long*,
                                    __msipl_shift_left<long>);

template long* __msipl_copy_value (long*, long*, const long&, long*,
                                    __msipl_caret<long>);
template long* __msipl_copy_array (long*, long*, const long*, long*,
                                    __msipl_caret<long>);

template long* __msipl_copy_value (long*, long*, const long&, long*,
                                    modulus<long>);
template long* __msipl_copy_array (long*, long*, const long*, long*,
                                    modulus<long>);
template long* __msipl_copy_value (long*, long*, const long&, long*,
                                    divides<long>);
template long* __msipl_copy_array (long*, long*, const long*, long*,
                                    divides<long>);

template long* __msipl_copy_value (long*, long*, const long&, long*,
                                    __msipl_bitwise_and<long>);
template long* __msipl_copy_array (long*, long*, const long*, long*,
                                    __msipl_bitwise_and<long>);

template long* __msipl_copy_value (long*, long*, const long&, long*,
                                    __msipl_bitwise_or<long>);
template long* __msipl_copy_array (long*, long*, const long*, long*,
                                    __msipl_bitwise_or<long>);

template long* __msipl_copy_value (long*, long*, const long&, long*,
                                   minus<long>);
template long* __msipl_copy_array (long*, long*, const long*, long*,
                                   minus<long>);

template long* __msipl_copy_value (long*, long*, const long&, long*,
                                   plus<long>);
template long* __msipl_copy_array (long*, long*, const long*, long*,
                                   plus<long>);

template long* __msipl_copy_value (long*, long*, const long&, long*,
                                   multiplies<long>);
template long* __msipl_copy_array (long*, long*, const long*, long*,
                                   multiplies<long>);

template int* __msipl_copy_value (int*, int*, const int&, int*,
                                    __msipl_shift_right<int>);
template int* __msipl_copy_array (int*, int*, const int*, int*,
                                    __msipl_shift_right<int>);

template int* __msipl_copy_value (const int*, const int*, int*,
                                 __msipl_not<int>);
template int* __msipl_copy_value (const int*, const int*, int*,
                                 __msipl_complement<int>);

template int* __msipl_copy_value (int*, int*, const int&, int*,
                                    __msipl_shift_left<int>);
template int* __msipl_copy_array (int*, int*, const int*, int*,
                                    __msipl_shift_left<int>);

template int* __msipl_copy_value (int*, int*, const int&, int*,
                                    __msipl_caret<int>);
template int* __msipl_copy_array (int*, int*, const int*, int*,
                                    __msipl_caret<int>);

template int* __msipl_copy_value (int*, int*, const int&, int*,
                                    modulus<int>);
template int* __msipl_copy_array (int*, int*, const int*, int*,
                                    modulus<int>);
template int* __msipl_copy_value (int*, int*, const int&, int*,
                                    divides<int>);
template int* __msipl_copy_array (int*, int*, const int*, int*,
                                    divides<int>);

template int* __msipl_copy_value (int*, int*, const int&, int*,
                                    __msipl_bitwise_and<int>);
template int* __msipl_copy_array (int*, int*, const int*, int*,
                                    __msipl_bitwise_and<int>);

template int* __msipl_copy_value (int*, int*, const int&, int*,
                                    __msipl_bitwise_or<int>);
template int* __msipl_copy_array (int*, int*, const int*, int*,
                                    __msipl_bitwise_or<int>);

template int* __msipl_copy_value (int*, int*, const int&, int*,
                                   minus<int>);
template int* __msipl_copy_array (int*, int*, const int*, int*,
                                   minus<int>);

template int* __msipl_copy_value (int*, int*, const int&, int*,
                                   plus<int>);
template int* __msipl_copy_array (int*, int*, const int*, int*,
                                   plus<int>);

template int* __msipl_copy_value (int*, int*, const int&, int*,
                                   multiplies<int>);
template int* __msipl_copy_array (int*, int*, const int*, int*,
                                   multiplies<int>);


template unsigned int* __lower_bound (unsigned int*, unsigned int*,
                                      const unsigned int&, int*,
                                      random_access_iterator_tag);

template unsigned int* __msipl_copy_value (const unsigned int*, 
         const unsigned int*, unsigned int*,  __msipl_not<unsigned int>);
template unsigned int* __msipl_copy_value (const unsigned int*,
         const unsigned int*, unsigned int*, __msipl_complement<unsigned int>);

template unsigned int* __msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*,__msipl_shift_right<unsigned int>);
template unsigned int* __msipl_copy_array (unsigned int*, unsigned int*,
                     const unsigned int*, unsigned int*, 
                      __msipl_shift_right<unsigned int>);

template unsigned int* __msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*, __msipl_shift_left<unsigned int>);
template unsigned int* __msipl_copy_array (unsigned int*, unsigned int*,
                     const unsigned int*, unsigned int*, 
                      __msipl_shift_left<unsigned int>);

template unsigned int* __msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*,__msipl_bitwise_and<unsigned int>);
template unsigned int* __msipl_copy_array (unsigned int*, unsigned int*,
                      const unsigned int*, unsigned int*,
                      __msipl_bitwise_and<unsigned int>);

template unsigned int* __msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*, __msipl_bitwise_or<unsigned int>);
template unsigned int* __msipl_copy_array (unsigned int*, unsigned int*,
                      const unsigned int*, unsigned int*,
                      __msipl_bitwise_or<unsigned int>);

template unsigned int* __msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*, minus<unsigned int>);
template unsigned int* __msipl_copy_array (unsigned int*, unsigned int*,
         const unsigned int*, unsigned int*, minus<unsigned int>);

template unsigned int* __msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*, plus<unsigned int>);
template unsigned int* __msipl_copy_array (unsigned int*, unsigned int*,
         const unsigned int*, unsigned int*, plus<unsigned int>);

template unsigned int* __msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*, multiplies<unsigned int>);
template unsigned int* __msipl_copy_array (unsigned int*, unsigned int*,
         const unsigned int*, unsigned int*, multiplies<unsigned int>);

template unsigned int* __msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*, modulus<unsigned int>);
template unsigned int* __msipl_copy_array (unsigned int*, unsigned int*,
         const unsigned int*, unsigned int*, modulus<unsigned int>);

template unsigned int* __msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*, divides<unsigned int>);
template unsigned int* __msipl_copy_array (unsigned int*, unsigned int*,
         const unsigned int*, unsigned int*, divides<unsigned int>);

template unsigned int* __msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*, __msipl_caret<unsigned int>);
template unsigned int* __msipl_copy_array (unsigned int*, unsigned int*,
         const unsigned int*, unsigned int*, __msipl_caret<unsigned int>);


template short* __msipl_copy_value (short*, short*,
                                    short*, short (*)(short)); 
template short* __msipl_copy_value (short*, short*,
                                    short*, short (*)(const short&)); 
template long* __msipl_copy_value (long*, long*, long*,
                                  long (*)(long)); 
template long* __msipl_copy_value (long*, long*, long*,
                                  long (*)(const long&)); 
template int* __msipl_copy_value (int*, int*, int*,
                                 int (*)(int)); 
template int* __msipl_copy_value (int*, int*, int*,
                                 int (*)(const int&)); 
template unsigned int* __msipl_copy_value (unsigned int*, unsigned int*, 
         unsigned int*, unsigned int (*)(const unsigned int&)); 
template unsigned int* __msipl_copy_value (unsigned int*, unsigned int*, 
         unsigned int*, unsigned int (*)(unsigned int)); 

template unsigned int* __msipl_copy_iter_backward (unsigned int**,
                                                  unsigned int**,
                                                  unsigned int*);
template short* __msipl_copy_iter_backward (short**, short**, short*);
template int* __msipl_copy_iter_backward (int**, int**, int*);
template long* __msipl_copy_iter_backward (long**, long**, long*);

template unsigned int* __msipl_copy_iter (unsigned int**, unsigned int**,
                                         unsigned int*);
template short* __msipl_copy_iter (short**, short**, short*);
template long* __msipl_copy_iter (long**, long**, long*);
template int* __msipl_copy_iter (int**, int**, int*);


template unsigned int* __msipl_copy_value (const unsigned int*,
         const unsigned int*, unsigned int*, negate<unsigned int>);
template  int* __msipl_copy_value (const  int*, const  int*,
                                  int*, negate< int>);
template  short* __msipl_copy_value (const  short*, const  short*,
                                    short*, negate< short>);
template  long* __msipl_copy_value (const  long*, const  long*,
                                   long*, negate< long>);

#else

template void MSIPLSTD::__unguarded_linear_insert (unsigned int*, unsigned int);
template void MSIPLSTD::__final_insertion_sort (unsigned int*, unsigned int*);
template void MSIPLSTD::__quick_sort_loop_aux (unsigned int*, unsigned int*,
                                     unsigned int*);

template short* MSIPLSTD::__msipl_copy_value (short*, short*, const short&, short*,
                                    __msipl_shift_right<short>);
template short* MSIPLSTD::__msipl_copy_array (short*, short*, const short*, short*,
                                    __msipl_shift_right<short>);

template short* MSIPLSTD::__msipl_copy_value (const short*, const short*, short*,
                                    __msipl_not<short>);
template short* MSIPLSTD::__msipl_copy_value (const short*, const short*, short*,
                                    __msipl_complement<short>);

template short* MSIPLSTD::__msipl_copy_value (short*, short*, const short&, short*,
                                    __msipl_shift_left<short>);
template short* MSIPLSTD::__msipl_copy_array (short*, short*, const short*, short*,
                                    __msipl_shift_left<short>);

template short* MSIPLSTD::__msipl_copy_value (short*, short*, const short&, short*,
                                    __msipl_caret<short>);
template short* MSIPLSTD::__msipl_copy_array (short*, short*, const short*, short*,
                                    __msipl_caret<short>);

template short* MSIPLSTD::__msipl_copy_value (short*, short*, const short&, short*,
                                    modulus<short>);
template short* MSIPLSTD::__msipl_copy_array (short*, short*, const short*, short*,
                                    modulus<short>);
template short* MSIPLSTD::__msipl_copy_value (short*, short*, const short&, short*,
                                    divides<short>);
template short* MSIPLSTD::__msipl_copy_array (short*, short*, const short*, short*,
                                    divides<short>);

template short* MSIPLSTD::__msipl_copy_value (short*, short*, const short&, short*,
                                    __msipl_bitwise_and<short>);
template short* MSIPLSTD::__msipl_copy_array (short*, short*, const short*, short*,
                                    __msipl_bitwise_and<short>);

template short* MSIPLSTD::__msipl_copy_value (short*, short*, const short&, short*,
                                    __msipl_bitwise_or<short>);
template short* MSIPLSTD::__msipl_copy_array (short*, short*, const short*, short*,
                                    __msipl_bitwise_or<short>);

template short* MSIPLSTD::__msipl_copy_value (short*, short*, const short&, short*,
                                   minus<short>);
template short* MSIPLSTD::__msipl_copy_array (short*, short*, const short*, short*,
                                   minus<short>);

template short* MSIPLSTD::__msipl_copy_value (short*, short*, const short&, short*,
                                   plus<short>);
template short* MSIPLSTD::__msipl_copy_array (short*, short*, const short*, short*,
                                   plus<short>);

template short* MSIPLSTD::__msipl_copy_value (short*, short*, const short&, short*,
                                   multiplies<short>);
template short* MSIPLSTD::__msipl_copy_array (short*, short*, const short*, short*,
                                   multiplies<short>);

template long* MSIPLSTD::__msipl_copy_value (long*, long*, const long&, long*,
                                    __msipl_shift_right<long>);
template long* MSIPLSTD::__msipl_copy_array (long*, long*, const long*, long*,
                                    __msipl_shift_right<long>);

template long* MSIPLSTD::__msipl_copy_value (const long*, const long*, long*,
                                  __msipl_not<long>);
template long* MSIPLSTD::__msipl_copy_value (const long*, const long*, long*,
                                  __msipl_complement<long>);

template long* MSIPLSTD::__msipl_copy_value (long*, long*, const long&, long*,
                                    __msipl_shift_left<long>);
template long* MSIPLSTD::__msipl_copy_array (long*, long*, const long*, long*,
                                    __msipl_shift_left<long>);

template long* MSIPLSTD::__msipl_copy_value (long*, long*, const long&, long*,
                                    __msipl_caret<long>);
template long* MSIPLSTD::__msipl_copy_array (long*, long*, const long*, long*,
                                    __msipl_caret<long>);

template long* MSIPLSTD::__msipl_copy_value (long*, long*, const long&, long*,
                                    modulus<long>);
template long* MSIPLSTD::__msipl_copy_array (long*, long*, const long*, long*,
                                    modulus<long>);
template long* MSIPLSTD::__msipl_copy_value (long*, long*, const long&, long*,
                                    divides<long>);
template long* MSIPLSTD::__msipl_copy_array (long*, long*, const long*, long*,
                                    divides<long>);

template long* MSIPLSTD::__msipl_copy_value (long*, long*, const long&, long*,
                                    __msipl_bitwise_and<long>);
template long* MSIPLSTD::__msipl_copy_array (long*, long*, const long*, long*,
                                    __msipl_bitwise_and<long>);

template long* MSIPLSTD::__msipl_copy_value (long*, long*, const long&, long*,
                                    __msipl_bitwise_or<long>);
template long* MSIPLSTD::__msipl_copy_array (long*, long*, const long*, long*,
                                    __msipl_bitwise_or<long>);

template long* MSIPLSTD::__msipl_copy_value (long*, long*, const long&, long*,
                                   minus<long>);
template long* MSIPLSTD::__msipl_copy_array (long*, long*, const long*, long*,
                                   minus<long>);

template long* MSIPLSTD::__msipl_copy_value (long*, long*, const long&, long*,
                                   plus<long>);
template long* MSIPLSTD::__msipl_copy_array (long*, long*, const long*, long*,
                                   plus<long>);

template long* MSIPLSTD::__msipl_copy_value (long*, long*, const long&, long*,
                                   multiplies<long>);
template long* MSIPLSTD::__msipl_copy_array (long*, long*, const long*, long*,
                                   multiplies<long>);

template int* MSIPLSTD::__msipl_copy_value (int*, int*, const int&, int*,
                                    __msipl_shift_right<int>);
template int* MSIPLSTD::__msipl_copy_array (int*, int*, const int*, int*,
                                    __msipl_shift_right<int>);

template int* MSIPLSTD::__msipl_copy_value (const int*, const int*, int*,
                                 __msipl_not<int>);
template int* MSIPLSTD::__msipl_copy_value (const int*, const int*, int*,
                                 __msipl_complement<int>);

template int* MSIPLSTD::__msipl_copy_value (int*, int*, const int&, int*,
                                    __msipl_shift_left<int>);
template int* MSIPLSTD::__msipl_copy_array (int*, int*, const int*, int*,
                                    __msipl_shift_left<int>);

template int* MSIPLSTD::__msipl_copy_value (int*, int*, const int&, int*,
                                    __msipl_caret<int>);
template int* MSIPLSTD::__msipl_copy_array (int*, int*, const int*, int*,
                                    __msipl_caret<int>);

template int* MSIPLSTD::__msipl_copy_value (int*, int*, const int&, int*,
                                    modulus<int>);
template int* MSIPLSTD::__msipl_copy_array (int*, int*, const int*, int*,
                                    modulus<int>);
template int* MSIPLSTD::__msipl_copy_value (int*, int*, const int&, int*,
                                    divides<int>);
template int* MSIPLSTD::__msipl_copy_array (int*, int*, const int*, int*,
                                    divides<int>);

template int* MSIPLSTD::__msipl_copy_value (int*, int*, const int&, int*,
                                    __msipl_bitwise_and<int>);
template int* MSIPLSTD::__msipl_copy_array (int*, int*, const int*, int*,
                                    __msipl_bitwise_and<int>);

template int* MSIPLSTD::__msipl_copy_value (int*, int*, const int&, int*,
                                    __msipl_bitwise_or<int>);
template int* MSIPLSTD::__msipl_copy_array (int*, int*, const int*, int*,
                                    __msipl_bitwise_or<int>);

template int* MSIPLSTD::__msipl_copy_value (int*, int*, const int&, int*,
                                   minus<int>);
template int* MSIPLSTD::__msipl_copy_array (int*, int*, const int*, int*,
                                   minus<int>);

template int* MSIPLSTD::__msipl_copy_value (int*, int*, const int&, int*,
                                   plus<int>);
template int* MSIPLSTD::__msipl_copy_array (int*, int*, const int*, int*,
                                   plus<int>);

template int* MSIPLSTD::__msipl_copy_value (int*, int*, const int&, int*,
                                   multiplies<int>);
template int* MSIPLSTD::__msipl_copy_array (int*, int*, const int*, int*,
                                   multiplies<int>);


template unsigned int* MSIPLSTD::__lower_bound (unsigned int*, unsigned int*,
                                      const unsigned int&, int*,
                                      random_access_iterator_tag);

template unsigned int* MSIPLSTD::__msipl_copy_value (const unsigned int*,
         const unsigned int*, unsigned int*,  __msipl_not<unsigned int>);
template unsigned int* MSIPLSTD::__msipl_copy_value (const unsigned int*, 
         const unsigned int*, unsigned int*, __msipl_complement<unsigned int>);

template unsigned int* MSIPLSTD::__msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*,__msipl_shift_right<unsigned int>);
template unsigned int* MSIPLSTD::__msipl_copy_array (unsigned int*, unsigned int*,
                     const unsigned int*, unsigned int*, 
                      __msipl_shift_right<unsigned int>);

template unsigned int* MSIPLSTD::__msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*, __msipl_shift_left<unsigned int>);
template unsigned int* MSIPLSTD::__msipl_copy_array (unsigned int*, unsigned int*,
                     const unsigned int*, unsigned int*, 
                      __msipl_shift_left<unsigned int>);

template unsigned int* MSIPLSTD::__msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*,__msipl_bitwise_and<unsigned int>);
template unsigned int* MSIPLSTD::__msipl_copy_array (unsigned int*, unsigned int*,
                      const unsigned int*, unsigned int*,
                      __msipl_bitwise_and<unsigned int>);

template unsigned int* MSIPLSTD::__msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*, __msipl_bitwise_or<unsigned int>);
template unsigned int* MSIPLSTD::__msipl_copy_array (unsigned int*, unsigned int*,
                      const unsigned int*, unsigned int*,
                      __msipl_bitwise_or<unsigned int>);

template unsigned int* MSIPLSTD::__msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*, minus<unsigned int>);
template unsigned int* MSIPLSTD::__msipl_copy_array (unsigned int*, unsigned int*,
         const unsigned int*, unsigned int*, minus<unsigned int>);

template unsigned int* MSIPLSTD::__msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*, plus<unsigned int>);
template unsigned int* MSIPLSTD::__msipl_copy_array (unsigned int*, unsigned int*,
         const unsigned int*, unsigned int*, plus<unsigned int>);

template unsigned int* MSIPLSTD::__msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*, multiplies<unsigned int>);
template unsigned int* MSIPLSTD::__msipl_copy_array (unsigned int*, unsigned int*,
         const unsigned int*, unsigned int*, multiplies<unsigned int>);

template unsigned int* MSIPLSTD::__msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*, modulus<unsigned int>);
template unsigned int* MSIPLSTD::__msipl_copy_array (unsigned int*, unsigned int*,
         const unsigned int*, unsigned int*, modulus<unsigned int>);

template unsigned int* MSIPLSTD::__msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*, divides<unsigned int>);
template unsigned int* MSIPLSTD::__msipl_copy_array (unsigned int*, unsigned int*,
         const unsigned int*, unsigned int*, divides<unsigned int>);

template unsigned int* MSIPLSTD::__msipl_copy_value (unsigned int*, unsigned int*,
         const unsigned int&, unsigned int*, __msipl_caret<unsigned int>);
template unsigned int* MSIPLSTD::__msipl_copy_array (unsigned int*, unsigned int*,
         const unsigned int*, unsigned int*, __msipl_caret<unsigned int>);


template short* MSIPLSTD::__msipl_copy_value (short*, short*,
                                    short*, short (*)(short)); 
template short* MSIPLSTD::__msipl_copy_value (short*, short*,
                                    short*, short (*)(const short&)); 
template long* MSIPLSTD::__msipl_copy_value (long*, long*, long*,
                                  long (*)(long)); 
template long* MSIPLSTD::__msipl_copy_value (long*, long*, long*,
                                  long (*)(const long&)); 
template int* MSIPLSTD::__msipl_copy_value (int*, int*, int*,
                                 int (*)(int)); 
template int* MSIPLSTD::__msipl_copy_value (int*, int*, int*,
                                 int (*)(const int&)); 
template unsigned int* MSIPLSTD::__msipl_copy_value (unsigned int*, unsigned int*, 
         unsigned int*, unsigned int (*)(const unsigned int&)); 
template unsigned int* MSIPLSTD::__msipl_copy_value (unsigned int*, unsigned int*, 
         unsigned int*, unsigned int (*)(unsigned int)); 

template unsigned int* MSIPLSTD::__msipl_copy_iter_backward (unsigned int**,
                                                  unsigned int**,
                                                  unsigned int*);
template short* MSIPLSTD::__msipl_copy_iter_backward (short**, short**, short*);
template int* MSIPLSTD::__msipl_copy_iter_backward (int**, int**, int*);
template long* MSIPLSTD::__msipl_copy_iter_backward (long**, long**, long*);

template unsigned int* MSIPLSTD::__msipl_copy_iter (unsigned int**, unsigned int**,
                                         unsigned int*);
template short* MSIPLSTD::__msipl_copy_iter (short**, short**, short*);
template long* MSIPLSTD::__msipl_copy_iter (long**, long**, long*);
template int* MSIPLSTD::__msipl_copy_iter (int**, int**, int*);


template unsigned int* MSIPLSTD::__msipl_copy_value (const unsigned int*,
         const unsigned int*, unsigned int*, negate<unsigned int>);
template  int* MSIPLSTD::__msipl_copy_value (const  int*, const  int*,
                                  int*, negate< int>);
template  short* MSIPLSTD::__msipl_copy_value (const  short*, const  short*,
                                    short*, negate< short>);
template  long* MSIPLSTD::__msipl_copy_value (const  long*, const  long*,
                                   long*, negate< long>);

#endif  /* MSIPL_EDG232  */

#endif /* MSIPL_EXPLICIT_INSTANTIATION */

// hh 971220 fixed MOD_INCLUDE
