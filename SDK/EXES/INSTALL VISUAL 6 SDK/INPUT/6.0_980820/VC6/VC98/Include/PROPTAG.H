//--proptag.h--------------------------------------------------------------------------
//
// Header file for the proptag library.
//
// Copyright (C) Microsoft Corp., 1986-1996.  All rights reserved.
//
//-----------------------------------------------------------------------------

#ifndef	_PROPTAG_H
#define _PROPTAG_H

#ifdef  __cplusplus
extern "C" {
#endif

// $--HrGetPropTagName------------------------------------------------------------------------
//
// DESCRIPTION: Get a property tag name string ("PR_*") given a property tag
//				value.
//
// INPUT:
//
//	[ulPropTag]		-- Property tag value.
//
// OUTPUT:
//
//	[lppszPropName]	-- Ptr to ptr which will be set to returned property tag
//					   name string on success.
//
// RETURNS:     NOERROR on success; E_INVALIDARG if bad input,
//              E_NOT_ENOUGH_MEMORY if memory problems.
//				Note that if the value is not found in the property tag
//				string table, then a string of the following form is returned:
//				- For PT_STRING8,   "[S " <HexNumber> "]"
//				- For PT_LONG,		"[N " <HexNumber> "]"
//				- For all others,	"["   <HexNumber> "]"
//
// Notes:		When it is no longer needed, the user should free
//				*lppszPropName using MAPIFREEBUFFER().
//				To avoid setting up a second table, this function was
//				implemented using linear search, so performance is not
//				great in the current implementation.
//---------------------------------------------------------------------------

HRESULT HrGetPropTagName(      // RETURNS: HRESULT
	IN		ULONG		ulPropTag,      // property tag value
	OUT		LPSTR FAR *	lppszPropName   // property tag name pointer
	);

// $--HrGetPropTagValue------------------------------------------------------------------------
//
// DESCRIPTION: Get a property tag value given a property tag name
//				string ("PR_*").
//
// INPUT:
//
//	[lpszPropName]	-- Ptr to property tag name string.
//
// OUTPUT:
//
//	[pulPropTag]	-- Ptr to ULONG which will be set to returned property
//					   tag value on success;
//
// RETURNS:     NOERROR on success; MAPI_E_NOT_FOUND if not found,
//              E_INVALIDARG if bad input.
//
// Notes:		We use binary search of a table, so performance for this
//				function is pretty good.
//---------------------------------------------------------------------------

HRESULT HrGetPropTagValue(      // RETURNS: HRESULT
	IN		LPSTR		lpszPropName,   // property tag name
	OUT		ULONG *		pulPropTag      // property tag
	);

#ifdef  __cplusplus
}       /*  extern "C" */
#endif

#endif	// _PROPTAG_H
