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
#include <limits>      // hh 971220 fixed MOD_INCLUDE
#else
#include <mlimits.h>   // hh 971220 fixed MOD_INCLUDE
#endif

MSIPL_STD_BEGIN
/* hh 980108 Everything inlined
// VENDOR specific information : modify

//
// float
//
const bool numeric_limits<float>::is_specialized  = true;

const int  numeric_limits<float>::radix           = FLT_RADIX;
const int  numeric_limits<float>::digits          = FLT_MANT_DIG;
const int  numeric_limits<float>::digits10        = FLT_DIG;
const int  numeric_limits<float>::min_exponent    = FLT_MIN_EXP;
const int  numeric_limits<float>::max_exponent    = FLT_MAX_EXP;
const int  numeric_limits<float>::min_exponent10  = FLT_MIN_10_EXP;
const int  numeric_limits<float>::max_exponent10  = FLT_MAX_10_EXP;

const bool numeric_limits<float>::is_signed          = true;
const bool numeric_limits<float>::is_integer         = false;
const bool numeric_limits<float>::is_exact           = false;

const bool numeric_limits<float>::has_infinity       = true;
const bool numeric_limits<float>::has_quiet_NaN      = true;

const bool numeric_limits<float>::has_signaling_NaN = true;

const bool numeric_limits<float>::has_denorm         = false;

const bool numeric_limits<float>::has_denorm_loss    = false;


const bool numeric_limits<float>::is_iec559          = true;

const bool numeric_limits<float>::is_bounded         = true;

const bool numeric_limits<float>::is_modulo          = false;

const bool numeric_limits<float>::traps              = true;

const bool numeric_limits<float>::tinyness_before    = true;
 

const float_round_style numeric_limits<float>::round_style = round_to_nearest;

//
// double
//

const bool numeric_limits<double>::is_specialized  = true;


const int  numeric_limits<double>::radix           = FLT_RADIX;

const int  numeric_limits<double>::digits          = DBL_MANT_DIG;

const int  numeric_limits<double>::digits10        = DBL_DIG;

const int  numeric_limits<double>::min_exponent    = DBL_MIN_EXP;

const int  numeric_limits<double>::max_exponent    = DBL_MAX_EXP;

const int  numeric_limits<double>::min_exponent10  = DBL_MIN_10_EXP;

const int  numeric_limits<double>::max_exponent10  = DBL_MAX_10_EXP;


const bool numeric_limits<double>::is_signed          = true;

const bool numeric_limits<double>::is_integer         = false;

const bool numeric_limits<double>::is_exact           = false;


const bool numeric_limits<double>::has_infinity       = true;

const bool numeric_limits<double>::has_quiet_NaN      = true;

const bool numeric_limits<double>::has_signaling_NaN = true;

const bool numeric_limits<double>::has_denorm         = false;

const bool numeric_limits<double>::has_denorm_loss    = false;


const bool numeric_limits<double>::is_iec559          = true;

const bool numeric_limits<double>::is_bounded         = true;

const bool numeric_limits<double>::is_modulo          = false;

const bool numeric_limits<double>::traps              = true;

const bool numeric_limits<double>::tinyness_before    = true;
 

const float_round_style numeric_limits<double>::round_style = round_to_nearest;

//
// long double
//

const bool numeric_limits<long double>::is_specialized  = true;


const int  numeric_limits<long double>::radix           = FLT_RADIX;

const int  numeric_limits<long double>::digits          = LDBL_MANT_DIG;

const int  numeric_limits<long double>::digits10        = LDBL_DIG;

const int  numeric_limits<long double>::min_exponent    = LDBL_MIN_EXP;

const int  numeric_limits<long double>::max_exponent    = LDBL_MAX_EXP;

const int  numeric_limits<long double>::min_exponent10  = LDBL_MIN_10_EXP;

const int  numeric_limits<long double>::max_exponent10  = LDBL_MAX_10_EXP;


const bool numeric_limits<long double>::is_signed          = true;

const bool numeric_limits<long double>::is_integer         = false;

const bool numeric_limits<long double>::is_exact           = false;


const bool numeric_limits<long double>::has_infinity       = true;

const bool numeric_limits<long double>::has_quiet_NaN      = true;

const bool numeric_limits<long double>::has_signaling_NaN = true;

const bool numeric_limits<long double>::has_denorm         = false;

const bool numeric_limits<long double>::has_denorm_loss    = false;


const bool numeric_limits<long double>::is_iec559          = true;

const bool numeric_limits<long double>::is_bounded         = true;

const bool numeric_limits<long double>::is_modulo          = false;

const bool numeric_limits<long double>::traps              = true;

const bool numeric_limits<long double>::tinyness_before    = true;
 

const float_round_style numeric_limits<long double>::round_style = round_to_nearest;

//
// int
//

const bool numeric_limits<int>::is_specialized  = true;


const int  numeric_limits<int>::radix           = 2;         

const int  numeric_limits<int>::digits          = 31;       

const int  numeric_limits<int>::digits10        = 10;       

const int  numeric_limits<int>::min_exponent    = 0;     

const int  numeric_limits<int>::max_exponent    = 0;    

const int  numeric_limits<int>::min_exponent10  = 0;   

const int  numeric_limits<int>::max_exponent10  = 0;  


const bool numeric_limits<int>::is_signed          = true;

const bool numeric_limits<int>::is_integer         = true;

const bool numeric_limits<int>::is_exact           = true;


const bool numeric_limits<int>::has_infinity       = false;

const bool numeric_limits<int>::has_quiet_NaN      = false;

const bool numeric_limits<int>::has_signaling_NaN = false;

const bool numeric_limits<int>::has_denorm         = false;

const bool numeric_limits<int>::has_denorm_loss    = false;


const bool numeric_limits<int>::is_iec559          = false;

const bool numeric_limits<int>::is_bounded         = true;

const bool numeric_limits<int>::is_modulo          = true;

const bool numeric_limits<int>::traps              = false;    

const bool numeric_limits<int>::tinyness_before    = false;
 

const float_round_style numeric_limits<int>::round_style = round_toward_zero;

//
// unsigned int
//

const bool numeric_limits<unsigned int>::is_specialized  = true;


const int  numeric_limits<unsigned int>::radix           = 2;         

const int  numeric_limits<unsigned int>::digits          = 32;       

const int  numeric_limits<unsigned int>::digits10        = 10;       

const int  numeric_limits<unsigned int>::min_exponent    = 0;     

const int  numeric_limits<unsigned int>::max_exponent    = 0;    

const int  numeric_limits<unsigned int>::min_exponent10  = 0;   

const int  numeric_limits<unsigned int>::max_exponent10  = 0;  


const bool numeric_limits<unsigned int>::is_signed          = false;

const bool numeric_limits<unsigned int>::is_integer         = true;

const bool numeric_limits<unsigned int>::is_exact           = true;


const bool numeric_limits<unsigned int>::has_infinity       = false;

const bool numeric_limits<unsigned int>::has_quiet_NaN      = false;

const bool numeric_limits<unsigned int>::has_signaling_NaN = false;

const bool numeric_limits<unsigned int>::has_denorm         = false;

const bool numeric_limits<unsigned int>::has_denorm_loss    = false;


const bool numeric_limits<unsigned int>::is_iec559          = false;

const bool numeric_limits<unsigned int>::is_bounded         = true;

const bool numeric_limits<unsigned int>::is_modulo          = true;

const bool numeric_limits<unsigned int>::traps              = false;    

const bool numeric_limits<unsigned int>::tinyness_before    = false;
 

const float_round_style numeric_limits<unsigned int>::round_style = round_toward_zero;

//
// long
//

const bool numeric_limits<long>::is_specialized  = true;


const int  numeric_limits<long>::radix           = 2;         

const int  numeric_limits<long>::digits          = 31;       

const int  numeric_limits<long>::digits10        = 10;       

const int  numeric_limits<long>::min_exponent    = 0;     

const int  numeric_limits<long>::max_exponent    = 0;    

const int  numeric_limits<long>::min_exponent10  = 0;   

const int  numeric_limits<long>::max_exponent10  = 0;  


const bool numeric_limits<long>::is_signed          = true;

const bool numeric_limits<long>::is_integer         = true;

const bool numeric_limits<long>::is_exact           = true;


const bool numeric_limits<long>::has_infinity       = false;

const bool numeric_limits<long>::has_quiet_NaN      = false;

const bool numeric_limits<long>::has_signaling_NaN = false;

const bool numeric_limits<long>::has_denorm         = false;

const bool numeric_limits<long>::has_denorm_loss    = false;


const bool numeric_limits<long>::is_iec559          = false;

const bool numeric_limits<long>::is_bounded         = true;

const bool numeric_limits<long>::is_modulo          = true;

const bool numeric_limits<long>::traps              = false;    

const bool numeric_limits<long>::tinyness_before    = false;
 

const float_round_style numeric_limits<long>::round_style = round_toward_zero;

//
// unsigned long
//

const bool numeric_limits<unsigned long>::is_specialized  = true;


const int  numeric_limits<unsigned long>::radix           = 2;         

const int  numeric_limits<unsigned long>::digits          = 32;       

const int  numeric_limits<unsigned long>::digits10        = 10;       

const int  numeric_limits<unsigned long>::min_exponent    = 0;     

const int  numeric_limits<unsigned long>::max_exponent    = 0;    

const int  numeric_limits<unsigned long>::min_exponent10  = 0;   

const int  numeric_limits<unsigned long>::max_exponent10  = 0;  


const bool numeric_limits<unsigned long>::is_signed          = false;

const bool numeric_limits<unsigned long>::is_integer         = true;

const bool numeric_limits<unsigned long>::is_exact           = true;


const bool numeric_limits<unsigned long>::has_infinity       = false;

const bool numeric_limits<unsigned long>::has_quiet_NaN      = false;

const bool numeric_limits<unsigned long>::has_signaling_NaN = false;

const bool numeric_limits<unsigned long>::has_denorm         = false;

const bool numeric_limits<unsigned long>::has_denorm_loss    = false;


const bool numeric_limits<unsigned long>::is_iec559          = false;

const bool numeric_limits<unsigned long>::is_bounded         = true;

const bool numeric_limits<unsigned long>::is_modulo          = true;

const bool numeric_limits<unsigned long>::traps              = false;    

const bool numeric_limits<unsigned long>::tinyness_before    = false;
 

const float_round_style numeric_limits<unsigned long>::round_style = round_toward_zero;

//
// short
//

const bool numeric_limits<short>::is_specialized  = true;


const int  numeric_limits<short>::radix           = 2;         

const int  numeric_limits<short>::digits          = 15;       

const int  numeric_limits<short>::digits10        = 5;       

const int  numeric_limits<short>::min_exponent    = 0;     

const int  numeric_limits<short>::max_exponent    = 0;    

const int  numeric_limits<short>::min_exponent10  = 0;   

const int  numeric_limits<short>::max_exponent10  = 0;  


const bool numeric_limits<short>::is_signed          = true;

const bool numeric_limits<short>::is_integer         = true;

const bool numeric_limits<short>::is_exact           = true;


const bool numeric_limits<short>::has_infinity       = false;

const bool numeric_limits<short>::has_quiet_NaN      = false;

const bool numeric_limits<short>::has_signaling_NaN = false;

const bool numeric_limits<short>::has_denorm         = false;

const bool numeric_limits<short>::has_denorm_loss    = false;


const bool numeric_limits<short>::is_iec559          = false;

const bool numeric_limits<short>::is_bounded         = true;

const bool numeric_limits<short>::is_modulo          = true;

const bool numeric_limits<short>::traps              = false;    

const bool numeric_limits<short>::tinyness_before    = false;


const float_round_style numeric_limits<short>::round_style = round_toward_zero;

//
// unsigned short
//

const bool numeric_limits<unsigned short>::is_specialized  = true;


const int  numeric_limits<unsigned short>::radix           = 2;         

const int  numeric_limits<unsigned short>::digits          = 16;       

const int  numeric_limits<unsigned short>::digits10        = 5;       

const int  numeric_limits<unsigned short>::min_exponent    = 0;     

const int  numeric_limits<unsigned short>::max_exponent    = 0;    

const int  numeric_limits<unsigned short>::min_exponent10  = 0;   

const int  numeric_limits<unsigned short>::max_exponent10  = 0;  


const bool numeric_limits<unsigned short>::is_signed          = false;

const bool numeric_limits<unsigned short>::is_integer         = true;

const bool numeric_limits<unsigned short>::is_exact           = true;


const bool numeric_limits<unsigned short>::has_infinity       = false;

const bool numeric_limits<unsigned short>::has_quiet_NaN      = false;

const bool numeric_limits<unsigned short>::has_signaling_NaN = false;

const bool numeric_limits<unsigned short>::has_denorm         = false;

const bool numeric_limits<unsigned short>::has_denorm_loss    = false;


const bool numeric_limits<unsigned short>::is_iec559          = false;

const bool numeric_limits<unsigned short>::is_bounded         = true;

const bool numeric_limits<unsigned short>::is_modulo          = true;

const bool numeric_limits<unsigned short>::traps              = false;    

const bool numeric_limits<unsigned short>::tinyness_before    = false;
 

const float_round_style numeric_limits<unsigned short>::round_style = round_toward_zero;

//
// char
//

const bool numeric_limits<char>::is_specialized  = true;


const int  numeric_limits<char>::radix           = 2;         

const int  numeric_limits<char>::digits          = 7;       

const int  numeric_limits<char>::digits10        = 3;       

const int  numeric_limits<char>::min_exponent    = 0;     

const int  numeric_limits<char>::max_exponent    = 0;    

const int  numeric_limits<char>::min_exponent10  = 0;   

const int  numeric_limits<char>::max_exponent10  = 0;  


const bool numeric_limits<char>::is_signed          = true;

const bool numeric_limits<char>::is_integer         = true;

const bool numeric_limits<char>::is_exact           = true;


const bool numeric_limits<char>::has_infinity       = false;

const bool numeric_limits<char>::has_quiet_NaN      = false;

const bool numeric_limits<char>::has_signaling_NaN = false;

const bool numeric_limits<char>::has_denorm         = false;

const bool numeric_limits<char>::has_denorm_loss    = false;


const bool numeric_limits<char>::is_iec559          = false;

const bool numeric_limits<char>::is_bounded         = true;

const bool numeric_limits<char>::is_modulo          = true;

const bool numeric_limits<char>::traps              = false;    

const bool numeric_limits<char>::tinyness_before    = false;
 

const float_round_style numeric_limits<char>::round_style = round_toward_zero;

//
// signed char
//

const bool numeric_limits<signed char>::is_specialized  = true;


const int  numeric_limits<signed char>::radix           = 2;         

const int  numeric_limits<signed char>::digits          = 7;       

const int  numeric_limits<signed char>::digits10        = 3;       

const int  numeric_limits<signed char>::min_exponent    = 0;     

const int  numeric_limits<signed char>::max_exponent    = 0;    

const int  numeric_limits<signed char>::min_exponent10  = 0;   

const int  numeric_limits<signed char>::max_exponent10  = 0;  


const bool numeric_limits<signed char>::is_signed          = true;

const bool numeric_limits<signed char>::is_integer         = true;

const bool numeric_limits<signed char>::is_exact           = true;


const bool numeric_limits<signed char>::has_infinity       = false;

const bool numeric_limits<signed char>::has_quiet_NaN      = false;

const bool numeric_limits<signed char>::has_signaling_NaN = false;

const bool numeric_limits<signed char>::has_denorm         = false;

const bool numeric_limits<signed char>::has_denorm_loss    = false;


const bool numeric_limits<signed char>::is_iec559          = false;

const bool numeric_limits<signed char>::is_bounded         = true;

const bool numeric_limits<signed char>::is_modulo          = true;

const bool numeric_limits<signed char>::traps              = false;    

const bool numeric_limits<signed char>::tinyness_before    = false;
 

const float_round_style numeric_limits<signed char>::round_style = round_toward_zero;

//
// unsigned char
//

const bool numeric_limits<unsigned char>::is_specialized  = true;


const int  numeric_limits<unsigned char>::radix           = 2;         

const int  numeric_limits<unsigned char>::digits          = 8;       

const int  numeric_limits<unsigned char>::digits10        = 3;       

const int  numeric_limits<unsigned char>::min_exponent    = 0;     

const int  numeric_limits<unsigned char>::max_exponent    = 0;    

const int  numeric_limits<unsigned char>::min_exponent10  = 0;   

const int  numeric_limits<unsigned char>::max_exponent10  = 0;  


const bool numeric_limits<unsigned char>::is_signed          = false;

const bool numeric_limits<unsigned char>::is_integer         = true;

const bool numeric_limits<unsigned char>::is_exact           = true;


const bool numeric_limits<unsigned char>::has_infinity       = false;

const bool numeric_limits<unsigned char>::has_quiet_NaN      = false;

const bool numeric_limits<unsigned char>::has_signaling_NaN = false;

const bool numeric_limits<unsigned char>::has_denorm         = false;

const bool numeric_limits<unsigned char>::has_denorm_loss    = false;


const bool numeric_limits<unsigned char>::is_iec559          = false;

const bool numeric_limits<unsigned char>::is_bounded         = true;

const bool numeric_limits<unsigned char>::is_modulo          = true;

const bool numeric_limits<unsigned char>::traps              = false;    

const bool numeric_limits<unsigned char>::tinyness_before    = false;
 

const float_round_style numeric_limits<unsigned char>::round_style = round_toward_zero;

#ifdef MSIPL_WCHART
//
// wchar_t
//

const bool numeric_limits<wchar_t>::is_specialized  = true;


const int  numeric_limits<wchar_t>::radix           = 2;         

const int  numeric_limits<wchar_t>::digits          = 16;       

const int  numeric_limits<wchar_t>::digits10        = 5;       

const int  numeric_limits<wchar_t>::min_exponent    = 0;     

const int  numeric_limits<wchar_t>::max_exponent    = 0;    

const int  numeric_limits<wchar_t>::min_exponent10  = 0;   

const int  numeric_limits<wchar_t>::max_exponent10  = 0;  


const bool numeric_limits<wchar_t>::is_signed          = false;

const bool numeric_limits<wchar_t>::is_integer         = true;

const bool numeric_limits<wchar_t>::is_exact           = true;


const bool numeric_limits<wchar_t>::has_infinity       = false;

const bool numeric_limits<wchar_t>::has_quiet_NaN      = false;

const bool numeric_limits<wchar_t>::has_signaling_NaN = false;

const bool numeric_limits<wchar_t>::has_denorm         = false;

const bool numeric_limits<wchar_t>::has_denorm_loss    = false;


const bool numeric_limits<wchar_t>::is_iec559          = false;

const bool numeric_limits<wchar_t>::is_bounded         = true;

const bool numeric_limits<wchar_t>::is_modulo          = true;

const bool numeric_limits<wchar_t>::traps              = false;    

const bool numeric_limits<wchar_t>::tinyness_before    = false;
 

const float_round_style numeric_limits<wchar_t>::round_style = round_toward_zero;

#endif // MSIPL_WCHART

#ifdef MSIPL_BOOL_BUILTIN

const bool numeric_limits<bool>::is_specialized       = true;

const int  numeric_limits<bool>::digits10             = 1;

const bool numeric_limits<bool>::is_signed            = false;

const bool numeric_limits<bool>::is_integer           = false;

const bool numeric_limits<bool>::is_exact             = true;

const bool numeric_limits<bool>::is_bounded           = true;

const bool numeric_limits<bool>::is_modulo            = false;

const bool numeric_limits<bool>::traps                = false;

#endif // MSIPL_BOOL_BUILTIN
*/
MSIPL_STD_END

// hh 971220 fixed MOD_INCLUDE
// hh 980108 Commented out everything.  Is inlined.
