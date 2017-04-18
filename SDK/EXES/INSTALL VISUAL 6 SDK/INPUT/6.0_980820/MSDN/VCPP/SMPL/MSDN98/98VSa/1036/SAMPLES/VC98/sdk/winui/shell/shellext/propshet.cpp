// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   propshet.cpp
//
//  PURPOSE:   Implements the IShellPropSheetExt member functions necessary to 
//             support the property sheet page of this shell extension.  This
//             page is displayed when the user selects "Properties..." after
//             right clicking on a .GAK file
//

#include "priv.h"
#include "shellext.h"
#include "resource.h"

extern UINT g_cRefThisDll;         // Reference count of this DLL.
extern HINSTANCE g_hmodThisDll; // Handle to this DLL itself.

//
//  FUNCTION: GAKPageCallback(HWND, UINT, LPPROPSHEETPAGE)
//
//  PURPOSE: Callback  procedure for the property page
//
//  PARAMETERS:
//    hWnd      - Reserved (will always be NULL)
//    uMessage  - Action flag: Are we being created or released
//    ppsp      - The page that is being created or destroyed
//
//  RETURN VALUE:
//
//    Depends on message. 
//
//    For PSPCB_CREATE it's TRUE to let the page be created
//    or false to prevent it from being created.  
//    For PSPCB_RELEASE the return value is ignored.
//
//  COMMENTS:
//
UINT CALLBACK
GAKPageCallback(HWND hWnd,
                UINT uMessage,
                LPPROPSHEETPAGE  ppsp)
{
    switch(uMessage)
    {
        case PSPCB_CREATE:
            return TRUE;

        case PSPCB_RELEASE:
            if (ppsp->lParam) 
            {
               ((LPCSHELLEXT)(ppsp->lParam))->Release();
            }
            return TRUE; 
    }
    return TRUE;
}

//
//  FUNCTION: GAKPageDlgProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Callback dialog procedure for the property page
//
//  PARAMETERS:
//    hDlg      - Dialog box window handle
//    uMessage  - current message
//    wParam    - depends on message
//    lParam    - depends on message
//
//  RETURN VALUE:
//
//    Depends on message.  In general, return TRUE if we process it.
//
//  COMMENTS:
//

BOOL CALLBACK GAKPageDlgProc(HWND hDlg, 
                             UINT uMessage, 
                             WPARAM wParam, 
                             LPARAM lParam)
{
    LPPROPSHEETPAGE psp=(LPPROPSHEETPAGE)GetWindowLong(hDlg, DWL_USER);
    UINT iIndex=0;
    int  iID;
    LPCSHELLEXT lpcs;
	 char szTemp[4];

    switch (uMessage)
    {
        //
        // When the shell creates a dialog box for a property sheet page,
        // it passes the pointer to the PROPSHEETPAGE data structure as
        // lParam. The dialog procedures of extensions typically store it
        // in the DWL_USER of the dialog box window.
        //
        case WM_INITDIALOG:
            SetWindowLong(hDlg, DWL_USER, lParam);

            psp = (LPPROPSHEETPAGE)lParam;

            lpcs = (LPCSHELLEXT)psp->lParam;

			if (*(lpcs->m_szPropSheetFileUserClickedOn))
            	iIndex = (UINT)GetPrivateProfileInt("IconImage", 
	            	                                "Index", 
	                	                            0, 
	                    	                        lpcs->m_szPropSheetFileUserClickedOn);

            //Note that the following line assumes that IDC_RED, IDC_GREEN,
            //and IDC_BLUE are in sequential order, with IDC_RED having the
            //smallest value.
            SendDlgItemMessage(hDlg, iIndex + IDC_RED, BM_SETCHECK, TRUE, 0L);

            break;

        case WM_DESTROY:
            RemoveProp(hDlg, "ID");
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDC_RED:
                case IDC_GREEN:
                case IDC_BLUE:
                    SetProp(hDlg, "ID", (HANDLE)lParam);
                    break;

                default:
                    break;
            }
            break;

        case WM_NOTIFY:
            switch (((NMHDR FAR *)lParam)->code)
            {
                case PSN_SETACTIVE:
                    break;

                case PSN_APPLY:
                    //User has clicked the OK or Apply button so we'll
                    //update the icon information in the .GAK file
                    lpcs = (LPCSHELLEXT)psp->lParam;
                    iID  = GetDlgCtrlID((HWND)GetProp(hDlg, "ID"));
                    iID -= IDC_RED;
                    wsprintf(szTemp, "%i", iID);
				    WritePrivateProfileString("IconImage",
                                              "Index",
                                               szTemp,
                                               lpcs->m_szPropSheetFileUserClickedOn);
                    //Ask the shell to refresh the icon list...
                    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_FLUSHNOWAIT, 0, 0);
                    break;
            
                default:
                    break;
            }
            break;

        default:
            return FALSE;
    }

    return TRUE;
}


//
//  FUNCTION: CShellExt::AddPages(LPFNADDPROPSHEETPAGE, LPARAM)
//
//  PURPOSE: Called by the shell just before the property sheet is displayed.
//
//  PARAMETERS:
//    lpfnAddPage -  Pointer to the Shell's AddPage function
//    lParam      -  Passed as second parameter to lpfnAddPage
//
//  RETURN VALUE:
//
//    NOERROR in all cases.  If for some reason our pages don't get added,
//    the Shell still needs to bring up the Properties... sheet.
//
//  COMMENTS:
//

STDMETHODIMP CShellExt::AddPages(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
{
    PROPSHEETPAGE psp;
    HPROPSHEETPAGE hpage;

    ODS("CShellExt::AddPages()\r\n");

    FORMATETC fmte = {CF_HDROP,
        	          (DVTARGETDEVICE FAR *)NULL,
        	          DVASPECT_CONTENT,
        	          -1,
        	          TYMED_HGLOBAL 
        	         };
    STGMEDIUM medium;
	HRESULT hres = 0;

    if (m_pDataObj)  //Paranoid check, m_pDataObj should have something by now...
       hres = m_pDataObj->GetData(&fmte, &medium);

    if (SUCCEEDED(hres))
    {
        //Find out how many files the user has selected...
        UINT cbFiles = 0;
        LPCSHELLEXT lpcsext = this;

        if (medium.hGlobal)
            cbFiles = DragQueryFile((HDROP)medium.hGlobal, (UINT)-1, 0, 0);

        if (cbFiles < 2)
        {
            //OK, the user has only selected a single file, so lets go ahead
            //and add the property sheet.  Note that it doesn't HAVE to be this
            //way, but for simplicity and educational reasons, I'll only add
            //the property sheet if a single .GAK file is selected.

            //Get the name of the file the user has clicked on
			if (cbFiles)
               DragQueryFile((HDROP)medium.hGlobal, 
                             0, 
                             m_szPropSheetFileUserClickedOn,
                             sizeof(m_szPropSheetFileUserClickedOn));

			//
			// Create a property sheet page object from a dialog box.
			//
			// We store a pointer to our class in the psp.lParam, so we
            // can access our class members from within the GAKPageDlgProc
			//
			// If the page needs more instance data, you can append
			// arbitrary size of data at the end of this structure,
			// and pass it to the CreatePropSheetPage. In such a case,
			// the size of entire data structure (including page specific
			// data) must be stored in the dwSize field.   Note that in
            // general you should NOT need to do this, as you can simply
            // store a pointer to date in the lParam member.
			//
        
            psp.dwSize      = sizeof(psp);	// no extra data.
            psp.dwFlags     = PSP_USEREFPARENT | PSP_USETITLE | PSP_USECALLBACK;
            psp.hInstance   = g_hmodThisDll;
            psp.pszTemplate = MAKEINTRESOURCE(IDD_GAKPAGE);
            psp.hIcon       = 0;
            psp.pszTitle    = "GAK Color";
            psp.pfnDlgProc  = GAKPageDlgProc;
            psp.pcRefParent = &g_cRefThisDll;
            psp.pfnCallback = GAKPageCallback;
            psp.lParam      = (LPARAM)lpcsext;
            
            AddRef();
            hpage = CreatePropertySheetPage(&psp);
            
            if (hpage) 
            {
                if (!lpfnAddPage(hpage, lParam)) 
                {
                    DestroyPropertySheetPage(hpage);
                    Release();
                }
            }
        }
    }

    return NOERROR;
}

//
//  FUNCTION: CShellExt::ReplacePage(UINT, LPFNADDPROPSHEETPAGE, LPARAM)
//
//  PURPOSE: Called by the shell only for Control Panel property sheet 
//           extensions
//
//  PARAMETERS:
//    uPageID         -  ID of page to be replaced
//    lpfnReplaceWith -  Pointer to the Shell's Replace function
//    lParam          -  Passed as second parameter to lpfnReplaceWith
//
//  RETURN VALUE:
//
//    E_FAIL, since we don't support this function.  It should never be
//    called.

//  COMMENTS:
//

STDMETHODIMP CShellExt::ReplacePage(UINT uPageID, 
                                    LPFNADDPROPSHEETPAGE lpfnReplaceWith, 
                                    LPARAM lParam)
{
    ODS("CShellExt::ReplacePage()\r\n");

    return E_FAIL;
}
