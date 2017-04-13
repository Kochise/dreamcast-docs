/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       dsenum.h        
 *  Content:    Direct Sound Enumeration defines
 *
 *
 ***************************************************************************/

#ifndef __DSENUM_INCLUDED__
#define __DSENUM_INCLUDED__


// Function declarations

BOOL DoDSoundEnumerate( LPGUID );

BOOL CALLBACK DSEnumProc( LPGUID, LPSTR, LPSTR, LPVOID );
BOOL CALLBACK DSEnumDlgProc( HWND, UINT, WPARAM, LPARAM );


#endif


