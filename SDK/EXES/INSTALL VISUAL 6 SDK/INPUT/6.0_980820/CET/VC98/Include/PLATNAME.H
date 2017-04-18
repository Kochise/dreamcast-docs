/////////////////////////////////////////////////////////
//
// Module:  PLATNAME.H
//
// Copyright (c) 1997 Microsoft Corporation. All rights reserved
//
// Purpose: Public header file for PLATNAME.CPP, listing the
//          exported functions of PLATNAME.DLL
//


#ifndef _PLATNAME_H
#define _PLATNAME_H

/////////////////////////////////////////////////////////
//
// Function:    Load_PegGetPlatformName
//
// Purpose:     To retrieve the "Platform Name" string of the currently-connected device
//
// Parameters:  LPTSTR pszPlatformName
//                  In/out pointer to a string that will be filled with the "Platform Name" if successful.
//                  This string must be of size MAX_PATH
//
// Returns:     BOOL:   TRUE    - successfully retrieved the "Platform Name"
//                      FALSE   - device is not connected, or an error occurred
//
// Notes:       - an HPC must be currently connected
//              - the "pszPlatformName" parameter must be user-allocated of size MAX_PATH
//

BOOL WINAPI
Load_PegGetPlatformName (
    LPTSTR  pszPlatformName // IN/OUT ptr to a string to contain the "platform name" - buffer must be of size MAX_PATH
);

BOOL WINAPI
Load_PegGetPlatformInfo (
	LPDWORD	lpdwProcessorType,
	LPDWORD	lpdwPageSize,
	LPDWORD	lpdwLCID,
	LPDWORD	lpdwMajorVersion,
	LPDWORD	lpdwMinorVersion,
	LPDWORD	lpdwPlatformId
);


#endif  // _PLATNAME_H
