/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:   dstrenum.c
 *  Content:   Illustrates enumerating DirectSound drivers
 *
 ***************************************************************************/
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <dsound.h>
#include <memory.h>

#include "dsenum.h"
#include "resource.h"

extern HINSTANCE hInst;
extern HWND      hWndMain;



/****************************************************************************/
/* DoDSoundEnumerate()                                                      */
/*                                                                          */
/*   This function takes care of handling the DirectSound enumeration, which*/
/* simply means creating a dialog box, at this point...                     */
/****************************************************************************/
BOOL DoDSoundEnumerate( LPGUID lpGUID )
    {
    if( DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DSENUMBOX), hWndMain,
                        DSEnumDlgProc, (LPARAM)lpGUID ))
        return( TRUE );

    return( FALSE );
    }

/****************************************************************************/
/* DSEnumDlgProc()                                                          */
/*                                                                          */
/*   Dialog procedure for the DSound enumeration choice dialog. Allows the  */
/* user to choose from installed drivers.  Returns TRUE on error.           */
/****************************************************************************/
BOOL CALLBACK DSEnumDlgProc( HWND hDlg, UINT msg,
                                WPARAM wParam, LPARAM lParam )
    {
    static HWND   hCombo;
    static LPGUID lpGUID;
    LPGUID        lpTemp;
    int           i;

    switch( msg )
        {
        case WM_INITDIALOG:
            hCombo = GetDlgItem( hDlg, IDC_DSENUM_COMBO );
            lpGUID = (LPGUID)lParam;

            if( DirectSoundEnumerate( (LPDSENUMCALLBACK)DSEnumProc, &hCombo ) != DS_OK )
                {
                EndDialog( hDlg, TRUE );
                return( TRUE );
                }
            if( ComboBox_GetCount( hCombo ))
                ComboBox_SetCurSel( hCombo, 0 );
            else
                {
                EndDialog( hDlg, TRUE );
                return( TRUE );
                }
            return( TRUE );


        case WM_COMMAND:
            switch( LOWORD( wParam ))
                {
                case IDOK:
                    for( i = 0; i < ComboBox_GetCount( hCombo ); i++ )
                        {
                        lpTemp = (LPGUID)ComboBox_GetItemData( hCombo, i );
                        if( i == ComboBox_GetCurSel( hCombo ))
                            {
                            if( lpTemp != NULL )
                                memcpy( lpGUID, lpTemp, sizeof(GUID));
			    else
			        lpGUID = NULL;
			    }
                        if( lpTemp )
                            LocalFree( lpTemp );
                        }
                    // If we got the NULL GUID, then we want to open the default
                    // sound driver, so return with an error and the init code
		    // will know not to pass in the guID and will send NULL
		    // instead.
                    if( lpGUID == NULL )
		        EndDialog( hDlg, TRUE );
                    else
                        EndDialog( hDlg, FALSE );
                    return( TRUE );

                case IDCANCEL:
                    // Force a NULL GUID
                    EndDialog( hDlg, TRUE );
                    return( TRUE );
                }
            break;


        default:
            return( FALSE );
        }

    return( FALSE );
    }


/****************************************************************************/
/* DSEnumProc()                                                             */
/*                                                                          */
/*   This is the Enumeration procedure called by DirectSoundEnumerate with  */
/* the parameters of each DirectSound Object available in the system.       */
/****************************************************************************/
BOOL CALLBACK DSEnumProc( LPGUID lpGUID, LPSTR lpszDesc,
                                LPSTR lpszDrvName, LPVOID lpContext )
    {
    HWND   hCombo = *(HWND *)lpContext;
    LPGUID lpTemp = NULL;

    if( lpGUID != NULL )
        {
        if(( lpTemp = LocalAlloc( LPTR, sizeof(GUID))) == NULL )
	    return( TRUE );

        memcpy( lpTemp, lpGUID, sizeof(GUID));
	}

    ComboBox_AddString( hCombo, lpszDesc );
    ComboBox_SetItemData( hCombo,
    			ComboBox_FindString( hCombo, 0, lpszDesc ),
    			lpTemp );
    return( TRUE );
    }
