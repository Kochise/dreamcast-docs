/*  Metrowerks Standard Library  */

/*  $Date: 1999/01/23 00:25:41 $ 
 *  $Revision: 1.6 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */

/**
 **  mtools.h
 **
 **  Lib++  : The Modena C++ Standard Library,
 **           Version 2.4, October 1997
 **
 **  Copyright (c) 1995-1997 Modena Software Inc.
 **/

#ifndef MSIPL_TOOLS_H
#define MSIPL_TOOLS_H

#include <mcompile.h>

#include <iosfwd>     // hh 971220 fixed MOD_INCLUDE

#ifdef MSIPL_ANSI_HEADER
#include <string>     // hh 971220 fixed MOD_INCLUDE
#include <limits>     // hh 971220 fixed MOD_INCLUDE
#else
#include <bstring.h>  // hh 971220 fixed MOD_INCLUDE
#include <mlimits.h>  // hh 971220 fixed MOD_INCLUDE
#endif

#include <ctime>      // hh 971220 fixed MOD_C_INCLUDE
#include <cerrno>     // hh 971220 fixed MOD_C_INCLUDE

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
	namespace std {
#endif

class ios_base;

template <class charT>
struct __numeric_digits {
   typedef basic_string<charT, char_traits<charT>,
                        allocator<charT> >              string_type;
};

null_template
struct __numeric_digits<char> {
   typedef basic_string<char, char_traits<char>,
                        allocator<char> >              string_type;
   static bool is_digit (char c, int radix);
   static int  value  (const char c, int radix);

private :
   static bool is_dec_digit (char c);
   static bool is_hex_digit (char c);
   static bool is_oct_digit (char c);
   static int  dec_value  (char c);
   static int  hex_value  (char c);
   static int  oct_value  (char c);
};

#ifdef MSIPL_WCHART

null_template
struct __numeric_digits<wchar_t> {

   typedef basic_string<wchar_t, char_traits<wchar_t>,
                        allocator<wchar_t> >            string_type;
   static bool is_digit (wchar_t c, int radix);
   static int  value  (const wchar_t c, int radix);

private :
   static bool is_dec_digit (wchar_t c);
   static bool is_hex_digit (wchar_t c);
   static bool is_oct_digit (wchar_t c);
   static int  dec_value  (wchar_t c);
   static int  hex_value  (wchar_t c);
   static int  oct_value  (wchar_t c);
};

#endif /* MSIPL_WCHART */

#ifndef _No_Floating_Point
template <class charT>
inline double __msipl_strtod (const charT* ptr, charT** end_ptr)
{ return strtod (ptr, end_ptr); }
#endif

template <class charT, class T>
inline int __msipl_sprintf (charT* buf, size_t /* n */, const charT* fmt, T val)
{
#ifndef MSIPL_SOL1
    return sprintf (buf, fmt, val);
#else
    sprintf(buf, fmt, val);
    return char_traits<charT>::length(buf);
#endif
}

template <class T>
inline int __msipl_ssprintf (char* buf, const char* fmt, T val)
{
#ifndef MSIPL_SOL1
    return sprintf (buf, fmt, val);
#else
    sprintf(buf, fmt, val);
    return strlen(buf);
#endif
}

template <class T, class T1>
inline int __msipl_ssprintf (char* buf, const char* fmt, T val, T1 val1)
{
#ifndef MSIPL_SOL1
    return sprintf (buf, fmt, val, val1);
#else
    sprintf(buf, fmt, val, val1);
    return strlen(buf);
#endif
}


template <class charT, class T>
inline int __msipl_sscanf (charT* buf, const charT* fmt, T val)
{ return sscanf (buf, fmt, val); }

template <class charT>
inline size_t __msipl_strftime (charT* buf, size_t n, const charT* fmt,
                  const tm* time_ptr)
{ return strftime (buf, n, fmt, (tm*)time_ptr); }

#ifdef MSIPL_WCHART

#ifndef _No_Floating_Point
null_template
inline double __msipl_strtod (const wchar_t* ptr, wchar_t** end_ptr)
{ return wcstod (ptr, end_ptr); }
#endif

null_template
inline int __msipl_sscanf (wchar_t* buf, const wchar_t* fmt, void* val)
{ return swscanf (buf, fmt, val); }

null_template
inline int __msipl_sscanf (wchar_t* buf, const wchar_t* fmt, long val)
{ return swscanf (buf, fmt, val); }

#ifndef _No_Floating_Point
null_template
inline int __msipl_sscanf (wchar_t* buf, const wchar_t* fmt, long double val)
{ return swscanf (buf, fmt, val); }
#endif

null_template
inline int __msipl_sscanf (wchar_t* buf, const wchar_t* fmt, unsigned long val)
{ return swscanf (buf, fmt, val); }

#ifndef _No_Floating_Point
null_template
inline int __msipl_sscanf (wchar_t* buf, const wchar_t* fmt, double val)
{ return swscanf (buf, fmt, val); }
#endif

null_template
inline int __msipl_sprintf (wchar_t* buf, size_t n, const wchar_t* fmt, 
                 long val)
{ return swprintf (buf, n, fmt, val); }

#ifndef _No_Floating_Point
null_template
inline int __msipl_sprintf (wchar_t* buf, size_t n, const wchar_t* fmt, 
                 long double val)
{ return swprintf (buf, n, fmt, val); }
#endif

null_template
inline int __msipl_sprintf (wchar_t* buf, size_t n, const wchar_t* fmt, 
                 unsigned long val)
{ return swprintf (buf, n, fmt, val); }

#ifndef _No_Floating_Point
null_template
inline int __msipl_sprintf (wchar_t* buf, size_t n, const wchar_t* fmt, 
                 double val)
{ return swprintf (buf, n, fmt, val); }
#endif

null_template
inline size_t __msipl_strftime (wchar_t* buf, size_t n, const wchar_t* fmt,
                  const tm* time_ptr)
{ return wcsftime (buf, n, fmt, (tm*)time_ptr); }

#endif /* MSIPL_WCHART */

bool
__msipl_check_grouping (int digits_seen, int num_seps, 
                        const int* seps, const string& grp) ;



template <class charT>
inline bool __msipl_strtoul (const charT* str, unsigned long& ul, int base = 10)
{
#ifndef MSIPL_SOL1
    bool ret = true;
    unsigned long temp = 0ul;
    int errno_sav = errno;
    errno = 0;
    temp = strtoul (str, NULL, base);
    if (errno == ERANGE)
        ret = false;
    ul = temp;
    errno = errno_sav;
    return ret;
#else
    char sign = 0;
    bool ret  = true;

    unsigned long temp = 0ul;
    unsigned long sum = 0ul;

    const charT *cur = str;
    const charT *s1, *s2;

    sign = (*cur == '-') || (*cur == '+') ? (char)*cur++ : '+';

    int ndig = 0;

    switch (base)
    {
       case  8 : ndig = 11; break;
       case 10 : ndig = 10; break;
       case 16 : ndig =  9; break;
    }

    for (s1 = cur; *cur == '0'; ++cur) ;

    for (s2 = cur; *cur; ++cur)
    {
         temp = sum;
         sum = sum * base + __numeric_digits<charT>::value (*cur, base);
    }
    if (s1 == cur) { ul = 0ul; return true; }

    int n =  cur - s2 - ndig;
    if (n < 0)
      ;
    else if (n > 0 ||
       sum < sum - __numeric_digits<charT>::value (cur[-1], base) ||
       (sum - __numeric_digits<charT>::value (cur[-1], base))/base != temp)
    {
        sum = ULONG_MAX; ret = false;
    }

    if (sign == '-')
      sum = -sum;

    ul = sum;

    return ret;
#endif
}

inline unsigned long __msipl_sstrtoul (const char* str, char** p, int base = 10)
{
#ifndef MSIPL_SOL1
    return strtoul(str, p, base);
#else
    unsigned long ul;
    if(!__msipl_strtoul (str, ul, base)) str = *p;
    return ul;
#endif
}

template <class charT>
inline bool __msipl_strtol (const charT* str, long& l, int radix = 10)
{
    unsigned long x;
    bool minus = false;
    if (*str == '-')
    {
        minus = true;
        str++;
    }
                                                
    bool ret = __msipl_strtoul (str, x, radix);
                                              
    if (minus && !ret)
        l = LONG_MIN;
    else if (!ret)
        l = LONG_MAX;
    else if (minus && x > LONG_MAX)
    {
        l = LONG_MIN;
        ret =  false;
    }
    else if (!minus && x > LONG_MAX)
    {
        l = LONG_MAX;
        ret =  false;
    }
    else
    {
        if (minus)
            l = -(long)x;
        else
            l = (long)x;
        ret =  true;
    }
    return ret;
}

template <class charT>
inline charT* __msipl_fmt (const ios_base& io, charT* buf, int idx)
{
    //
    // Size of buf is atleast 16.

    // idx - 1 ==> long
    // idx - 2 ==> unsigned long
    // idx - 3 ==> double
    // idx - 4 ==> long double
    typedef basic_string<charT, char_traits<charT>,
                         allocator<charT> >             string_type;

    charT* cur = buf;

    *cur++ = '%';

    //
    // __msipl_pad will take care of adjustfield: left,right, internal.
    if (io.flags () & ios_base::showpos)
    {
        *cur++ = '+';
    }

    int radix = 10;
    radix = (io.flags () & ios_base::oct) ? 8 :
           (io.flags () & ios_base::hex) ? 16 : 10;

    // handle showbase and showpoint
    // for integral, # goes for showbase (only for oct and hex)
    // for float   , # goes for showpoint
    if (((idx < 3) && (radix != 10) && (io.flags () & ios_base::showbase)) ||
       ((idx > 2) && (io.flags () & ios_base::showpoint)))
    {
        *cur++ = '#';
    }

    if (idx > 2)  // for floating point types only
    {
        charT  tmp[4];
        *cur++ = '.';

        tmp[0] = '%';
        tmp[1] = 'l';
        tmp[2] = 'u';
        tmp[3] = charT();  // hh 981013

        __msipl_sprintf (cur, (size_t) 16+(buf-cur), tmp, io.precision ());
        cur   += string_type::traits_type::length (cur);
    }
    if (idx < 3)  // integral quantities
    {
        *cur++ = 'l';
        switch (radix)
        {
           case 8  :
                *cur++ = 'o';
                break;
           case 16 :
                if (io.flags () & ios_base::uppercase)
                    *cur++ = 'X';
                else
                    *cur++ = 'x';
                break;
           case 10 : default :
                if (idx == 1)
                {
                    *cur++ = 'd';
                }
                else   // unsigned long
                    *cur++ = 'u';
                break;
         }
     }   
#ifndef _No_Floating_Point
     else  // for floating point output.
     {
          if ((io.flags () & ios_base::floatfield) &&
            (idx == 4)) // long double
          {
              *cur++ = 'L';
          }
          switch (io.flags () & ios_base::floatfield)
          {
              case ios_base::scientific:
                *cur++ = ((io.flags() & ios_base::uppercase) ? 'E' : 'e');
                break;
              case ios_base::fixed:
                *cur++ = 'f';
                break;
              default:
                *cur++ = ((io.flags () & ios_base::uppercase) ? 'G' : 'g');
              break;
          }
      }
#endif /* #ifndef _No_Floating_Point */
      *cur = charT();  // hh 981013
      return cur;
}
 

template <class charT>
inline basic_string<charT, char_traits<charT>, allocator<charT> >
__msipl_insert_thsep (basic_string<charT, char_traits<charT>, 
                                   allocator<charT> > str,
                      const string& grp, charT sep, charT pt)
{
    typedef  basic_string<charT, char_traits<charT>,
                          allocator<charT> >                  string_type;
    typedef  string_type::traits_type                         traits_type;

    // Should search for localeconv ()->decimal_pt
    size_t  pos = str.rfind (string (localeconv ()->decimal_point));

    if (pos != string_type::npos)
       str.replace (pos, 1, 1, pt);
    else
       pos = str.size ();
    if (!str.empty ())
    {
        int     shift;
        int     limit = 0;
        size_t  count = 0;

        if (__numeric_digits<charT>::value (str[0], 10) == 0)
        {
            ++limit;
            if ((str.size () >= 2) &&
              (traits_type::eq (str[1], 'X') ||
                 traits_type::eq (str[1], 'x')))
            {
               ++limit;
            }
        }
        else if ((traits_type::eq (str[0], '+') ||
                 traits_type::eq (str[0], '-')))
        {
               ++limit;
        }

        while ((count < grp.size ()) && 
              (grp[count] != numeric_limits<char>::max ()))
        {
            shift  = grp[count] & 0xf;
            if (pos-limit <= shift)
                break;
            pos -= shift;
            str.insert (pos, 1, sep);
            count++;
        }
        if ((count == grp.size ()) && (count != 0))
        {
           while (pos-limit > shift)
           {
             pos -= shift;
             str.insert (pos, 1, sep);
           }
        }
     }
     return str;
}

template <class charT>
inline basic_string<charT, char_traits<charT>, allocator<charT> >&
__msipl_pad (const ios_base& io, charT fill,
             basic_string<charT, char_traits<charT>, allocator<charT> >& str,
             int idx)
{
   // idx - 0 : long
   // idx - 1 : unsigned long
   // idx - 2 : double
   // idx - 3 : long double
   //
   typedef  basic_string<charT, char_traits<charT>,
                         allocator<charT> >                  string_type;
   typedef  string_type::traits_type                         traits_type;

   if (io.width () <= str.size ())
      return str;

   size_t pos = 0;
   // RAM : Need this be changed : See Issue No 53
   switch (io.flags () & ios_base::adjustfield)
   {
      case ios_base::left :
           pos = str.size ();
           break;
      case ios_base::internal :
           if (str.size () >= 2)
           {
             if (traits_type::eq(str[0], '+') ||
                 traits_type::eq(str[0], '-'))
             {
                ++pos;
             }
             else if (idx < 3)
             {
                if (__numeric_digits<charT>::value (str[0], 10) == 0)
                {
                  ++pos;  // is octal
                  if ((traits_type::eq (str[1], 'x')) ||
                    (traits_type::eq (str[1], 'X')))
                  {
                     ++pos;  // is hexadecimal
                  }
                }
             }
           }
           break;
      case ios_base::right :
      default :
           pos = 0;
           break;
   }  
   str.insert (pos, io.width () - str.size (), fill);
   return str;
}

#ifdef MSIPL_USING_NAMESPACE
	} // namespace std
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_TOOLS_H */

// 970723 SCM	wrapped floating point code in #ifndef _No_Floating_Point
// hh 971220 fixed MOD_INCLUDE and MOD_C_INCLUDE
// hh 971223 added alignment wrapper
// hh 980408 wrapped in #ifndef _No_Floating_Point
