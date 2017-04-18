// --convregh.h-----------------------------------------------------------------
//
//  Conversion registry helper routines.
// 
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
//
// -----------------------------------------------------------------------------

#ifndef _CONVREGH_H
#define _CONVREGH_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//$--HrGetArbSizeValue---------------------------------------------------------
//
//  DESCRIPTION: Allocate sufficient memory to read a value from the the registry 
//  and read it.  
//
//  INPUT:  hk  --  key that contains value
//          lpszValueName   --  name of value
//       
//  OUTPUT: pValue  --  pointer to key's value
//          cbSize  --  size of value (including null)
//          nType   --  type of value
//
//  RETURNS:    HRESULT -   NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_EOF if key not found,
//                          E_FAIL otherwise.
//
//------------------------------------------------------------------------------
HRESULT HrGetArbSizeValue(       // RETURNS: HRESULT
    IN HKEY hk,                 // key that contains the value
    IN LPWSTR lpszValueName,    // name of the value
    OUT PVOID & pValue,         // pointer to its value
    OUT DWORD & cbSize,         // how big is it (including trailing null(s)
    OUT DWORD & nType);         // what type

//$--HrStrstriW-------------------------------------------------------
//
// DESCRIPTION: determines whether one string is a prefix of another.
// case sensitive.
//
// INPUT:   pszSubString   --  the sub-string to check for
//          pszString   --  the string
//
// RETURNS: HRESULT --  NOERROR if sub-string exists in string,
//                      E_FAIL otherwise.
//
//---------------------------------------------------------------------
HRESULT HrStrstriW( 
    IN LPCWSTR pszSubString,    // the candidate sub-string
    IN LPCWSTR pszString);      // the string.

#ifdef __cplusplus
}
#endif

#endif
