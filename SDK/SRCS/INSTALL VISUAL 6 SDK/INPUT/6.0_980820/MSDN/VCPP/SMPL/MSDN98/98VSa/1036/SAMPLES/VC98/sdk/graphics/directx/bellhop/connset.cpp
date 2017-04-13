/*==========================================================================
 *
 *  Copyright (C) 1997 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       ConnSet.cpp
 *  Content:	A dialog to set and get Group connection settings for a lobby
 *
 ***************************************************************************/

#include "Bellhop.h"

HRESULT	GetConnectionSPGuid(HWND hWnd, int idCombo, GUID *lpGuidSP);
HRESULT	GetComboBoxGuid(HWND hWnd, LONG iDialogItem, LPGUID lpguidReturn);
HRESULT SetGroupConnection(HWND hWnd, LPLOBBYGROUPCONTEXT lpContext);
BOOL CALLBACK LobbyGroupWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL InitConnectionSettingsDialog(  HWND hWnd, LPLOBBYGROUPCONTEXT lpContext);
BOOL FAR PASCAL	EnumApp(LPCDPLAPPINFO lpAppInfo, LPVOID lpContext, DWORD dwFlags);
BOOL FAR PASCAL DirectPlayEnumConnectionsCallback(
						LPCGUID			lpguidSP,
						LPVOID			lpConnection,
						DWORD			dwSize,
						LPCDPNAME		lpName,
						DWORD			dwFlags,
						LPVOID			lpContext);


///////////////////////////////////////////////////////////////////////////////////////
BOOL InitConnectionSettingsDialog( HWND hWnd, LPLOBBYGROUPCONTEXT lpContext)
{
	BOOL				bRet	= FALSE,
						bFound;
	int					iNum	= 0,
						i,
						lParam;
	LPCONNECTIONINFO	lpci	= NULL;
	LPGUID				lpGuid	= NULL;
	LPDPLCONNECTION		lpdpconn = NULL;
	HRESULT				hr;
	ENUMCONNSTRUCT		enStruct;
	DWORD				dwSize;

	HWND	hSPComboBox = GetDlgItem( hWnd, IDC_GROUPCONNECTIONSPCOMBO ); 
	HWND	hAppComboBox = GetDlgItem( hWnd, IDC_APPCOMBO ); 

	// put all the DirectPlay applications in a combo box
	lpContext->lpDPInfo->lpDirectPlayLobby2A->EnumLocalApplications(EnumApp, hWnd, 0);

	// put all the available connections in a combo box
	enStruct.hWnd = hWnd;
	enStruct.idCombo = IDC_GROUPCONNECTIONSPCOMBO;

	hr = IDirectPlay3_EnumConnections(	lpContext->lpDPInfo->lpDirectPlay3A, 
										&BELLHOP_GUID, 
										DirectPlayEnumConnectionsCallback,
										&enStruct, DPCONNECTION_DIRECTPLAY );
	if (FAILED(hr))
		goto FAILURE;

	dwSize = 0;
	hr = IDirectPlay3_GetGroupConnectionSettings( lpContext->lpDPInfo->lpDirectPlay3A, 
													0, lpContext->dpidRoom, lpdpconn, &dwSize );

	if (DPERR_BUFFERTOOSMALL != hr)
		goto FAILURE;

	lpdpconn = (LPDPLCONNECTION) GlobalAllocPtr( GHND, dwSize );
	if (NULL == lpdpconn)
		goto FAILURE;

	hr = IDirectPlay3_GetGroupConnectionSettings( lpContext->lpDPInfo->lpDirectPlay3A, 
													0, lpContext->dpidRoom, lpdpconn, &dwSize );

	if (FAILED(hr))
		goto FAILURE;


	iNum = ComboBox_GetCount( hSPComboBox );

	bFound = FALSE;
	for (i=0; i<iNum; i++)
	{
		lParam =  ComboBox_GetItemData( hSPComboBox, i );

		if ((lParam) && (CB_ERR != lParam))
		{
			lpci = (LPCONNECTIONINFO) lParam;
			if (IsEqualGUID( lpci->guidSP, lpdpconn->guidSP ))
			{
				bFound = TRUE;
				ComboBox_SetCurSel( hSPComboBox, i );
				break;
			}
			lpci = NULL;
		}

		lParam = NULL;
	}

	if (FALSE == bFound)
	{
		//No match.
		ComboBox_AddString( hSPComboBox, "<Unknown Service Provider>");
		ComboBox_SetItemData( hSPComboBox, 0, 0);
		ComboBox_SetCurSel( hSPComboBox, 0 );
	}

	iNum = ComboBox_GetCount( hAppComboBox );

	bFound = FALSE;
	for (i=0; i<iNum; i++)
	{
		lParam = ComboBox_GetItemData( hAppComboBox, i );

		if ((lParam) && (CB_ERR != lParam))
		{
			lpGuid = (LPGUID) lParam;
			if (IsEqualGUID( *lpGuid, lpdpconn->lpSessionDesc->guidApplication ))
			{
				bFound = TRUE;
				ComboBox_SetCurSel( hAppComboBox, i );
				break;
			}
			lpGuid = NULL;
		}

		lParam = NULL;

	}

	if (FALSE == bFound)
	{
		//No match.
		ComboBox_AddString( hAppComboBox, "<Unknown Application>");
		ComboBox_SetItemData( hAppComboBox, 0, 0);
		ComboBox_SetCurSel( hAppComboBox, 0 );
	}

	bRet = TRUE;

	// initialize max players
	SetDlgItemInt(hWnd, IDC_MAXPLAYERSEDIT, 0, FALSE);
	SetDlgItemText( hWnd, IDC_PASSWORDEDIT,lpdpconn->lpSessionDesc->lpszPasswordA );

FAILURE:
	return bRet;
}


///////////////////////////////////////////////////////////////////////////////////////
HRESULT SetGroupConnection(HWND hWnd, LPLOBBYGROUPCONTEXT lpContext)
{
	CHAR				szPassword[MAXSTRLEN];
	DWORD				dwMaxPlayers;
	LPDPLCONNECTION		lp = NULL;
	HRESULT				hr;
	GUID				guidApplication,
						guidSP;
	DWORD				dwSize = 0;

	//Pull the info from the dialog
	GetDlgItemText(hWnd, IDC_PASSWORDEDIT, szPassword, MAXSTRLEN);
	dwMaxPlayers = GetDlgItemInt(hWnd, IDC_MAXPLAYERSEDIT, NULL, FALSE);
	hr = GetComboBoxGuid(hWnd, IDC_APPCOMBO, &guidApplication);

	if (FAILED( hr))
	{
		ErrorBox( "Please select a different application.", hr );
		return hr;
	}

	GetConnectionSPGuid(hWnd, IDC_GROUPCONNECTIONSPCOMBO, &guidSP);

	if (FAILED( hr))
	{
		ErrorBox( "Please select a different service provider.", hr );
		return hr;
	}


	//Get the old connection settings.
	hr = IDirectPlay3_GetGroupConnectionSettings(lpContext->lpDPInfo->lpDirectPlay3A,
												 0, lpContext->dpidRoom, NULL, &dwSize );

	lp = (LPDPLCONNECTION) GlobalAllocPtr( GHND, dwSize );

	if (lp)
	{
		hr = IDirectPlay3_GetGroupConnectionSettings(lpContext->lpDPInfo->lpDirectPlay3A,
													 0, lpContext->dpidRoom, (LPVOID) lp, &dwSize );

		lp->lpSessionDesc->dwMaxPlayers = dwMaxPlayers;
		lp->lpSessionDesc->lpszPasswordA = szPassword;
		lp->lpSessionDesc->guidApplication = guidApplication;
		lp->guidSP = guidSP;

		hr = IDirectPlay3_SetGroupConnectionSettings(lpContext->lpDPInfo->lpDirectPlay3A,
													 0, lpContext->dpidRoom, lp );
	}
	else
	{
		hr = DPERR_OUTOFMEMORY;
	}

	return (hr);
}


///////////////////////////////////////////////////////////////////////////////////////
BOOL CALLBACK ConnectionSettingsDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LPLOBBYGROUPCONTEXT	lpContext = (LPLOBBYGROUPCONTEXT) GetWindowLong(hWnd, DWL_USER);
	HRESULT	hr;

    switch(uMsg)
    {
        case WM_INITDIALOG:

			// context passed in lParam
			lpContext = (LPLOBBYGROUPCONTEXT) lParam;

            // save the globals with the window
			SetWindowLong(hWnd, DWL_USER, (LONG) lpContext);
			InitConnectionSettingsDialog( hWnd, lpContext );  
            break;

        case WM_DESTROY:
			{
				WPARAM	index;
				LRESULT	lpData;

				// destroy the GUID's stored with each app name
				index = 0;
				while (TRUE)
				{
					lpData = SendDlgItemMessage(hWnd, IDC_APPCOMBO, CB_GETITEMDATA, (WPARAM) index, 0);
					if ((lpData == CB_ERR) || (lpData == 0))
						break;

					GlobalFreePtr((LPVOID) lpData);
					index += 1;
				}

				// destroy the connection info in the combo box.
				index = 0;
				while (TRUE)
				{
					lpData = SendDlgItemMessage(hWnd, IDC_GROUPCONNECTIONSPCOMBO, CB_GETITEMDATA, (WPARAM) index, 0);
					if ((lpData == CB_ERR) || (lpData == 0))
						break;

					GlobalFreePtr((LPVOID) lpData);
					index += 1;
				}
			}
            break;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
				case IDOK:
					// save changes they made
					hr = SetGroupConnection( hWnd, lpContext);

					if (SUCCEEDED(hr))
					{
						// Return success
						EndDialog(hWnd, TRUE);
					}
                    break;

				case IDCANCEL:
                    // Return failure
                    EndDialog(hWnd, FALSE);

                    break;

				case IDC_STAGINGAREA:
					{
						int i = SendDlgItemMessage( hWnd, IDC_STAGINGAREA, BM_GETCHECK, 0, 0 );
						EnableWindow( GetDlgItem( hWnd, IDC_PASSWORDEDIT ), (BST_CHECKED==i));
						EnableWindow( GetDlgItem( hWnd, IDC_APPCOMBO ), (BST_CHECKED==i));
						EnableWindow( GetDlgItem( hWnd, IDC_MAXPLAYERSEDIT ), (BST_CHECKED==i));
						EnableWindow( GetDlgItem( hWnd, IDC_GROUPCONNECTIONSPCOMBO ), (BST_CHECKED==i));
					}
					break;

            }

            break;
    }

    // Allow for default processing
    return FALSE;
}

