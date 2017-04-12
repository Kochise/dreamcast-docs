// --newpst.h-----------------------------------------------------------------
//
// Header file for the newpst library.
//
// Copyright 1986 - 1998 Microsoft Corporation.  All rights reserved.
//
//-----------------------------------------------------------------------------

#ifndef	_NEWPST_H
#define _NEWPST_H

#ifdef  __cplusplus
extern "C" {
#endif

// $--HrCreatePersonalStore----------------------------------------------------------
//
// DESCRIPTION: Create a New PST with properties determined by the input
//				parameters in a temporary profile.  The name and password
//				of the temporary PST are returned to the user.
//
// INPUT:
//
//	[lpszPSTPath]			-- Value for PR_PST_PATH (new PST path).
//	[dwEncryption]			-- Value for PR_PST_ENCRYPTION (TBS).
//	[lpszPSTDisplayName]	-- Value for PR_DISPLAY_NAME (new PST display name).
//	[lpszPSTPassword]		-- Value for PR_PST_PW_SZ_NEW (new PST password,
//							   NULL not accepted).
//
// OUTPUT:
//
//	[lppszProfileName]		-- Ptr that will be set to point at temporary
//							   profile name on return; this may be used to
//							   establish a MAPI session.
//	[lppszProfilePassword]	-- Ptr that will be set to point at temporary
//							   profile password on return; this may be used to
//							   establish a MAPI session.
//
// RETURNS:     NOERROR on success,
//              E_INVALIDARG if bad input,
//              E_ACCESSDENIED if can't access profile,
//              E_FAIL if general failure
//
// Notes:		Successive calls to CreateNewPST() should not be made without
//				intervening calls to NewPSTCleanup().  Due to use of internal
//				static storage for objects and profile strings, only one new
//				PST may be created and used at a time.
//
//---------------------------------------------------------------------------

HRESULT HrCreatePersonalStore(                         // RETURNS: HRESULT
	IN	LPSTR	lpszPSTPath,            // PST fully-pathed file name
	IN	DWORD	dwEncryption,           // encryption method
	IN	LPSTR	lpszPSTDisplayName,     // PR_DISPLAY_NAME value
	IN	LPSTR	lpszPSTPassword,        // PST password
	OUT	LPSTR *	lppszProfileName,       // Temporary profile name
	OUT	LPSTR *	lppszProfilePassword    // Temporary profile password
	);

// $--HrCleanupPSTGlobals---------------------------------------------------------
//
// DESCRIPTION: Release objects involved in creation of a new PST.
//
// INPUT:       temporary profile name
//
// RETURNS:     NOERROR on success
//              E_FAIL on failure
//
// Notes:		This should be called after Logoff() and Release() are called
//				for the LPSESSION and before MAPIUninitialize() is called.
//---------------------------------------------------------------------------

HRESULT HrCleanupPSTGlobals(         // RETURNS: HRESULT
        IN LPSTR lpszProfileName);  // temporary profile name

#ifdef  __cplusplus
}       /*  extern "C" */
#endif

#endif	// _NEWPST_H
