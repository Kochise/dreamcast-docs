/***************************************************************************
 *
 *  Copyright (C) 2000 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       AboutBox.cpp
 *  Content:    About dialog class for SRSlog
 *
 ***************************************************************************/
#include <stdio.h>
#include "AboutBox.h"
#include "resource.h"
#include "Registry.h"

//
// Save IP Address.
//
void WriteIPAddress( HWND hDlg )
{
	char str[MAX_PATH];
	int bi1, bi2, bi3, bi4;
	bi1 = bi2 = bi3 = bi4 = 0;
	ZeroMemory( str, MAX_PATH );
	GetDlgItemText( hDlg, IDC_IPEDIT, str, MAX_PATH );
	sscanf( str, "%d.%d.%d.%d", &bi1, &bi2, &bi3, &bi4 );
	SRSLog_IPSave( ((bi1 & 0xff) | ((bi2 & 0xff) << 8) | ((bi3 & 0xff) << 16) | ((bi4 & 0xff) << 24)) );
}

//
// load IP Address.
//
void ReadIPAddress( HWND hDlg )
{
	char str[MAX_PATH];
	int ip;
	ZeroMemory( str, MAX_PATH );
	ip = SRSLog_IPLoad();
	if ( ip == 0 )
	{
	    PHOSTENT lphostent;
		char cServerName[32] = "";
		SOCKADDR_IN ServerAddr;
	    gethostname( cServerName, sizeof(cServerName) );
	    lphostent = gethostbyname(cServerName);
		if ( lphostent )
		{
			memcpy( (char *)&ServerAddr.sin_addr.s_addr, *lphostent->h_addr_list, 4);
			ip = ServerAddr.sin_addr.s_addr;
		}
	}
	sprintf( str, "%d.%d.%d.%d", (ip & 0xff), ((ip >> 8) & 0xff), ((ip >> 16) & 0xff), ((ip >> 24) & 0xff) );
	SetDlgItemText( hDlg, IDC_IPEDIT, str );
}

//
// About Box procedure
//
LRESULT CALLBACK AboutDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_INITDIALOG:
		ReadIPAddress( hDlg );
		return FALSE;
	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case IDOK:
			WriteIPAddress( hDlg );
			EndDialog( hDlg, IDOK );
			break;
		case IDCANCEL:
			EndDialog( hDlg, IDCANCEL );
			break;
		default:
			return FALSE;
		}
	default:
		return FALSE;
	}
	return TRUE;
}
