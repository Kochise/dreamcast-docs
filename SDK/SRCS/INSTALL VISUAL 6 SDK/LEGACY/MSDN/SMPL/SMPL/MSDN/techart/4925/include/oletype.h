// OleType.H

#ifndef _OLETYPE_H_
#define _OLETYPE_H_

#include <ole2.h>
#include <tchar.h>
#include <iostream.h>

// Syncronize UNICODE options
#if defined(_UNICODE) && !defined(UNICODE)
        #define UNICODE
#endif
#if defined(UNICODE) && !defined(_UNICODE)
        #define _UNICODE
#endif

// Give Basic names to OLE types
//@B SimpleType
typedef unsigned char   Byte;
typedef short           Integer;
typedef long            Long;
typedef float           Single;
typedef double          Double;
//@E SimpleType
//@B Currency
typedef LONGLONG        Currency;
//@E Currency
//@B Date
typedef double          Date;
//@E Date
//@B Object
typedef IDispatch*      Object;
//@E Object
//@B Boolean
typedef VARIANT_BOOL	Boolean;
const Boolean True = VARIANT_TRUE;
const Boolean False = VARIANT_FALSE;
//@E Boolean

//@B BCSTR
typedef const wchar_t * const BCSTR;
//@E BCSTR

//@B boolVal
#if _MSC_VER < 1010
#define boolVal bool
#endif
//@E boolVal

#include "BString.H"
#include "Variant.H"
#include "SafeArray.H"

typedef SafeArray<Variant, VT_VARIANT>      ParamArray;
typedef SafeArray<Variant, VT_VARIANT>      ArrayVariant;
typedef SafeArray<Byte, VT_UI1>             ArrayByte;
typedef SafeArray<Integer, VT_I2>           ArrayInteger;
typedef SafeArray<Long, VT_I4>              ArrayLong;
typedef SafeArray<Single, VT_R4>            ArraySingle;
typedef SafeArray<Double, VT_R8>            ArrayDouble;
typedef SafeArray<Currency, VT_CY>          ArrayCurrency;
typedef SafeArray<Date, VT_DATE>            ArrayDate;
//@B ArrayString
typedef SafeArray<BSTR, VT_BSTR>            ArrayString;
//@E ArrayString
typedef SafeArray<Boolean, VT_BOOL>         ArrayBoolean;
typedef SafeArray<Object, VT_DISPATCH>      ArrayObject;


#endif // _OLETYPE_H_