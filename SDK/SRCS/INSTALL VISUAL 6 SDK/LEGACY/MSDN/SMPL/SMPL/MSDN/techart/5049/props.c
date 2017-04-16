/*
 *  Copyright (C) 1995, 1996, 1997 Microsoft Corporation. 
 *  All Rights Reserved.
 *
 *  File:    props.c
 *  Purpose: Property Sheet Sample
 */
 
#include <windows.h>    // includes basic windows functionality
#include <commctrl.h>   // includes the common control header
#include <stdio.h>
#include <string.h>
#include "props.h"
#include "resource.h"
#include <d3drmwin.h>
#include "rmtex.h"

typedef struct mytagNMHDR
{
    HWND  hwndFrom;
    UINT  idFrom;
    UINT  code;         // NM_ code
}   MYNMHDR;
typedef MYNMHDR FAR * LPMYNMHDR;

HINSTANCE hInst;
HWND hwApply;
HWND hwPageVal;
static char szBuf[128];
static char szWBuf[128];
static char szHBuf[128];
static char szDBuf[128];
static char szODBuf[256];
HWND hwSWOx,hwSWOy,hwSWOz;
HWND hwSWZx,hwSWZy,hwSWZz;
HWND hwSWYx,hwSWYy,hwSWYz;
HWND hwSTOx,hwSTOy;
HWND hwSTSx,hwSTSy;

//
LONG MapRBCtlIDtoWID(LONG id)
{
   if ( id == IDC_FLAT )
      return MENU_WRAP_FLAT;
   if ( id == IDC_CYL )
      return MENU_WRAP_CYL;
   if ( id == IDC_SPH )
      return MENU_WRAP_SPHR;
   if ( id == IDC_CHROME )
      return MENU_WRAP_CHROME;
}
//
static int oldWrapID = IDC_CYL;
static LONG lwrapType = MENU_WRAP_CYL;
//
BOOL APIENTRY WrapType(
	HWND hDlg,
	UINT message,
	UINT wParam,
	LONG lParam)
{
	static PROPSHEETPAGE * psT;
    MYNMHDR n;
    UINT code, cntrl;
	switch (message)
	{
	case WM_INITDIALOG:
        CheckRadioButton(hDlg,IDC_FLAT,IDC_CHROME,oldWrapID);
		// save off the PROPSHEETPAGE information
		psT = (PROPSHEETPAGE *)lParam;
	    return (TRUE);

   	// on any command notification, tell the property sheet to enable the Apply button
   	case WM_COMMAND:
   		PropSheet_Changed(GetParent(hDlg), hDlg);
   		code = HIWORD(wParam);
	    cntrl = LOWORD(wParam);
        switch(code)
        {
           LONG id;
           HWND hwRB;
           case BN_CLICKED:
              id   = cntrl;
              hwRB = (HWND)lParam;
              SendMessage(GetDlgItem(hDlg,oldWrapID),BM_SETCHECK,FALSE,0);
              oldWrapID = id;
              SendMessage(GetDlgItem(hDlg,oldWrapID),BM_SETCHECK,TRUE,0);
              lwrapType = MapRBCtlIDtoWID(id);			  
              break;
		}
   		break;

	case WM_NOTIFY:
		n = *((MYNMHDR *) lParam);
    	switch (n.code) //((NMHDR FAR *) lParam)->code) 
    	{

			case PSN_QUERYCANCEL:
				PostMessage(win,WM_COMMAND,MENU_WRAP_VALS_KILL,TRUE);
 	        	SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
				break;

			case PSN_SETACTIVE:
				// initialize the controls
				SendMessage(GetDlgItem(hDlg,oldWrapID),BM_SETCHECK,TRUE,0);
				break;

			case PSN_APPLY:
				PostMessage(win,WM_COMMAND,lwrapType,TRUE);
 	        	SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
				break;

			case PSN_KILLACTIVE:
	        	SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
				return 1;
				break;

			case PSN_RESET:
				// rest to the original values
	        	SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
				break;
    	}
	}
	return (FALSE);   
}
/****************************************************************************
* 
*    FUNCTION: WrapValues(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for "WrapValues" dialog box
*
****************************************************************************/
BOOL APIENTRY WrapValues(
	HWND hDlg,
	UINT message,
	UINT wParam,
	LONG lParam)
{
	static PROPSHEETPAGE * psV;
    MYNMHDR n;

	switch (message)
	{
	case WM_INITDIALOG:
		hwPageVal = hDlg;
		// save off the PROPSHEETPAGE information
		psV = (PROPSHEETPAGE *)lParam;
		return (TRUE);

   	// on any command notification, tell the property sheet to enable the Apply button
   	case WM_COMMAND:
   		PropSheet_Changed(GetParent(hDlg), hDlg);
   		break;

	case WM_NOTIFY:
		n = *((MYNMHDR *) lParam);
		switch (n.code) //((NMHDR FAR *) lParam)->code) 
    	{

			case PSN_QUERYCANCEL:
				PostMessage(win,WM_COMMAND,MENU_WRAP_VALS_KILL,TRUE);
 				SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
				break;
			case PSN_SETACTIVE:
				// initialize the controls
				SetDlgItemText(hDlg, IDE_WOX, floatToText(wOx));
				SetDlgItemText(hDlg, IDE_WOY, floatToText(wOy));
				SetDlgItemText(hDlg, IDE_WOZ, floatToText(wOz));
				SetDlgItemText(hDlg, IDE_WZX, floatToText(wZx));
				SetDlgItemText(hDlg, IDE_WZY, floatToText(wZy));
				SetDlgItemText(hDlg, IDE_WZZ, floatToText(wZz));
				SetDlgItemText(hDlg, IDE_WYX, floatToText(wYx));
				SetDlgItemText(hDlg, IDE_WYY, floatToText(wYy));
				SetDlgItemText(hDlg, IDE_WYZ, floatToText(wYz));
				SetDlgItemText(hDlg, IDE_TOY, floatToText(tOy));
				SetDlgItemText(hDlg, IDE_TOX, floatToText(tOx));
				SetDlgItemText(hDlg, IDE_TSX, floatToText(tSx));
				SetDlgItemText(hDlg, IDE_TSY, floatToText(tSy));
				sprintf(szWBuf,"w:%s",floatToText(width));
				sprintf(szHBuf," h:%s",floatToText(height));
				sprintf(szDBuf," d:%s",floatToText(depth));
				sprintf(szODBuf,"%s%s%s",szWBuf,szHBuf,szDBuf);
				SetDlgItemText(hDlg, IDE_OBJDIMS,   szODBuf);
				break;

			case PSN_APPLY:
				GetDlgItemText(hDlg, IDE_WOX, szBuf,sizeof(szBuf));
				wOx = textToFloat(szBuf);
				GetDlgItemText(hDlg, IDE_WOY, szBuf,sizeof(szBuf));
				wOy = textToFloat(szBuf);
				GetDlgItemText(hDlg, IDE_WOZ, szBuf,sizeof(szBuf));
				wOz = textToFloat(szBuf);
				GetDlgItemText(hDlg, IDE_WZX, szBuf,sizeof(szBuf));
				wZx = textToFloat(szBuf);
				GetDlgItemText(hDlg, IDE_WZY, szBuf,sizeof(szBuf));
				wZy = textToFloat(szBuf);
				GetDlgItemText(hDlg, IDE_WZZ, szBuf,sizeof(szBuf));
				wZz = textToFloat(szBuf);
				GetDlgItemText(hDlg, IDE_WYX, szBuf,sizeof(szBuf));
				wYx = textToFloat(szBuf);
				GetDlgItemText(hDlg, IDE_WYY, szBuf,sizeof(szBuf));
				wYy = textToFloat(szBuf);
				GetDlgItemText(hDlg, IDE_WYZ, szBuf,sizeof(szBuf));
				wYz = textToFloat(szBuf);
				GetDlgItemText(hDlg, IDE_TOX, szBuf,sizeof(szBuf));
				tOx = textToFloat(szBuf);
				GetDlgItemText(hDlg, IDE_TOY, szBuf,sizeof(szBuf));
				tOy = textToFloat(szBuf);
				GetDlgItemText(hDlg, IDE_TSX, szBuf,sizeof(szBuf));
				tSx = textToFloat(szBuf);
				GetDlgItemText(hDlg, IDE_TSY, szBuf,sizeof(szBuf));
				tSy = textToFloat(szBuf);
//
				PostMessage(win,WM_COMMAND,wrapType,TRUE);
 	           	SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
				break;

			case PSN_KILLACTIVE:
	           	SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
				return 1;
				break;

			case PSN_RESET:
					// rest to the original values
	           	SetWindowLong(hDlg,	DWL_MSGRESULT, FALSE);
				break;
    	   }
	}
	return (FALSE);   
}

/****************************************************************************
*    FUNCTION: CreatePropertySheet(HWND)
*
*    PURPOSE:  Creates a property sheet
*
****************************************************************************/
HWND CreatePropertySheet(HWND hwndOwner)
{
    PROPSHEETPAGE psp[2];
    PROPSHEETHEADER psh;

    psp[0].dwSize = sizeof(PROPSHEETPAGE);
    psp[0].dwFlags = PSP_USETITLE;
    psp[0].hInstance = hInst;
    psp[0].pszTemplate = MAKEINTRESOURCE(IDD_VALUES);
    psp[0].pszIcon = NULL;
    psp[0].pfnDlgProc = WrapValues;
    psp[0].pszTitle = "Wrap Values";
    psp[0].lParam = 0;
    
    psp[1].dwSize = sizeof(PROPSHEETPAGE);
    psp[1].dwFlags = PSP_USETITLE;
    psp[1].hInstance = hInst;
    psp[1].pszTemplate = MAKEINTRESOURCE(IDD_TYPE);
    psp[1].pszIcon = NULL;
    psp[1].pfnDlgProc = WrapType;
    psp[1].pszTitle = "Wrap Type";
    psp[1].lParam = 0;

    psh.dwSize = sizeof(PROPSHEETHEADER);
    psh.dwFlags = PSH_PROPSHEETPAGE|PSH_MODELESS;
    psh.hwndParent = hwndOwner;
    psh.hInstance = hInst;
    psh.pszIcon = NULL;
    psh.pszCaption = (LPSTR) "Wrap Properties";
    psh.nPages = sizeof(psp) / sizeof(PROPSHEETPAGE);
    psh.nStartPage = 0;
    psh.ppsp = (LPCPROPSHEETPAGE) &psp;

    return ((HWND)PropertySheet(&psh));
}


