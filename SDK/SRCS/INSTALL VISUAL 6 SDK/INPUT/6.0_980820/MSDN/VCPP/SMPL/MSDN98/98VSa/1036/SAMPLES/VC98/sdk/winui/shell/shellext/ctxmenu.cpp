// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   ctxmenu.cpp
//
//  PURPOSE:   Implements the IContextMenu member functions necessary to support
//             the context menu portioins of this shell extension.  Context menu
//             shell extensions are called when the user right clicks on a file
//             (of the type registered for the shell extension--see SHELLEXT.REG
//             for details on the registry entries.  In this sample, the relevant
//             files are of type .GAK) in the Explorer, or selects the File menu 
//             item.
//

#include "priv.h"
#include "shellext.h"


//
//  FUNCTION: CShellExt::QueryContextMenu(HMENU, UINT, UINT, UINT, UINT)
//
//  PURPOSE: Called by the shell just before the context menu is displayed.
//           This is where you add your specific menu items.
//
//  PARAMETERS:
//    hMenu      - Handle to the context menu
//    indexMenu  - Index of where to begin inserting menu items
//    idCmdFirst - Lowest value for new menu ID's
//    idCmtLast  - Highest value for new menu ID's
//    uFlags     - Specifies the context of the menu event
//
//  RETURN VALUE:
//
//
//  COMMENTS:
//

STDMETHODIMP CShellExt::QueryContextMenu(HMENU hMenu,
                                         UINT indexMenu,
                                         UINT idCmdFirst,
                                         UINT idCmdLast,
                                         UINT uFlags)
{
    ODS("CShellExt::QueryContextMenu()\r\n");

    UINT idCmd = idCmdFirst;
    char szMenuText[64];
    char szMenuText2[64];
    char szMenuText3[64];
    char szMenuText4[64];
    BOOL bAppendItems=TRUE;

    if ((uFlags & 0x000F) == CMF_NORMAL)  //Check == here, since CMF_NORMAL=0
    {
        ODS("CMF_NORMAL...\r\n");
        lstrcpy(szMenuText, "&New .GAK menu 1, Normal File");
        lstrcpy(szMenuText2, "&New .GAK menu 2, Normal File");
        lstrcpy(szMenuText3, "&New .GAK menu 3, Normal File");
        lstrcpy(szMenuText4, "&New .GAK menu 4, Normal File");
    }
    else
        if (uFlags & CMF_VERBSONLY)
        {
            ODS("CMF_VERBSONLY...\r\n");
            lstrcpy(szMenuText, "&New .GAK menu 1, Shortcut File");
            lstrcpy(szMenuText2, "N&ew .GAK menu 2, Shortcut File");
            lstrcpy(szMenuText3, "&New .GAK menu 3, Shortcut File");
            lstrcpy(szMenuText4, "&New .GAK menu 4, Shortcut File");
        }
    else
        if (uFlags & CMF_EXPLORE)
        {
            ODS("CMF_EXPLORE...\r\n");
            lstrcpy(szMenuText, "&New .GAK menu 1, Normal File right click in Explorer");
            lstrcpy(szMenuText2, "N&ew .GAK menu 2, Normal File right click in Explorer");
            lstrcpy(szMenuText3, "&New .GAK menu 3, Normal File right click in Explorer");
            lstrcpy(szMenuText4, "&New .GAK menu 4, Normal File right click in Explorer");
        }
    else
        if (uFlags & CMF_DEFAULTONLY)
        {
            ODS("CMF_DEFAULTONLY...\r\n");
            bAppendItems = FALSE;
        }
    else
        {
            char szTemp[32];

            wsprintf(szTemp, "uFlags==>%d\r\n", uFlags);
            ODS("CMF_default...\r\n");
            ODS(szTemp);
            bAppendItems = FALSE;
        }

    if (bAppendItems)
    {
        InsertMenu(hMenu, indexMenu++, MF_SEPARATOR|MF_BYPOSITION, 0, NULL);
        
        InsertMenu(hMenu,
                   indexMenu++,
                   MF_STRING|MF_BYPOSITION,
                   idCmd++,
                   szMenuText);
        
        InsertMenu(hMenu, indexMenu++, MF_SEPARATOR|MF_BYPOSITION, 0, NULL);

        InsertMenu(hMenu,
                   indexMenu++,
                   MF_STRING|MF_BYPOSITION,
                   idCmd++,
                   szMenuText2);
        
        InsertMenu(hMenu, indexMenu++, MF_SEPARATOR|MF_BYPOSITION, 0, NULL);

        InsertMenu(hMenu,
                   indexMenu++,
                   MF_STRING|MF_BYPOSITION,
                   idCmd++,
                   szMenuText3);

        InsertMenu(hMenu,
                   indexMenu++,
                   MF_STRING|MF_BYPOSITION,
                   idCmd++,
                   szMenuText4);

        return ResultFromShort(idCmd-idCmdFirst); //Must return number of menu
												  //items we added.
   }

   return NOERROR;
}

//
//  FUNCTION: CShellExt::InvokeCommand(LPCMINVOKECOMMANDINFO)
//
//  PURPOSE: Called by the shell after the user has selected on of the
//           menu items that was added in QueryContextMenu().
//
//  PARAMETERS:
//    lpcmi - Pointer to an CMINVOKECOMMANDINFO structure
//
//  RETURN VALUE:
//
//
//  COMMENTS:
//

STDMETHODIMP CShellExt::InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi)
{
    ODS("CShellExt::InvokeCommand()\r\n");

	HRESULT hr = E_INVALIDARG;

    //If HIWORD(lpcmi->lpVerb) then we have been called programmatically
    //and lpVerb is a command that should be invoked.  Otherwise, the shell
    //has called us, and LOWORD(lpcmi->lpVerb) is the menu ID the user has
    //selected.  Actually, it's (menu ID - idCmdFirst) from QueryContextMenu().
	if (!HIWORD(lpcmi->lpVerb))
    {
        UINT idCmd = LOWORD(lpcmi->lpVerb);

        switch (idCmd)
        {
            case 0:
                hr = DoGAKMenu1(lpcmi->hwnd,
                                lpcmi->lpDirectory,
                                lpcmi->lpVerb,
                                lpcmi->lpParameters,
                                lpcmi->nShow);
                break;

            case 1:
                hr = DoGAKMenu2(lpcmi->hwnd,
                                lpcmi->lpDirectory,
                                lpcmi->lpVerb,
                                lpcmi->lpParameters,
                                lpcmi->nShow);
                break;

            case 2:
                hr = DoGAKMenu3(lpcmi->hwnd,
                                lpcmi->lpDirectory,
                                lpcmi->lpVerb,
                                lpcmi->lpParameters,
                                lpcmi->nShow);
                break;

            case 3:
                hr = DoGAKMenu4(lpcmi->hwnd,
                                lpcmi->lpDirectory,
                                lpcmi->lpVerb,
                                lpcmi->lpParameters,
                                lpcmi->nShow);
                break;
        }
    }
    return hr;
}


//
//  FUNCTION: CShellExt::InvokeCommand(LPCMINVOKECOMMANDINFO)
//
//  PURPOSE: Called by the shell after the user has selected on of the
//           menu items that was added in QueryContextMenu().
//
//  PARAMETERS:
//    lpcmi - Pointer to an CMINVOKECOMMANDINFO structure
//
//  RETURN VALUE:
//
//
//  COMMENTS:
//

STDMETHODIMP CShellExt::GetCommandString(UINT idCmd,
                                         UINT uFlags,
                                         UINT FAR *reserved,
                                         LPSTR pszName,
                                         UINT cchMax)
{
    ODS("CShellExt::GetCommandString()\r\n");

    switch (idCmd)
    {
        case 0:
            lstrcpy(pszName, "New menu item number 1");
            break;

        case 1:
            lstrcpy(pszName, "New menu item number 2");
            break;

        case 2:
            lstrcpy(pszName, "New menu item number 3");
            break;

        case 3:
            lstrcpy(pszName, "New menu item number 4");
            break;
    }

    return NOERROR;
}

STDMETHODIMP CShellExt::DoGAKMenu1(HWND hParent,
                                   LPCSTR pszWorkingDir,
                                   LPCSTR pszCmd,
                                   LPCSTR pszParam,
                                   int iShowCmd)
{
    ODS("CShellExt::DoGAKMenu1()\r\n");

    MessageBox(hParent, "Menu item 1!", "Shell Extension Sample", MB_OK);

    return NOERROR;
}

STDMETHODIMP CShellExt::DoGAKMenu2(HWND hParent,
                                   LPCSTR pszWorkingDir,
                                   LPCSTR pszCmd,
                                   LPCSTR pszParam,
                                   int iShowCmd)
{
    ODS("CShellExt::DoGAKMenu2()\r\n");

    MessageBox(hParent, "Menu item 2!", "Shell Extension Sample", MB_OK);

    return NOERROR;
}

STDMETHODIMP CShellExt::DoGAKMenu3(HWND hParent,
                                   LPCSTR pszWorkingDir,
                                   LPCSTR pszCmd,
                                   LPCSTR pszParam,
                                   int iShowCmd)
{
    ODS("CShellExt::DoGAKMenu3()\r\n");

    MessageBox(hParent, "Menu item 3!", "Shell Extension Sample", MB_OK);

    return NOERROR;
}

STDMETHODIMP CShellExt::DoGAKMenu4(HWND hParent,
                                   LPCSTR pszWorkingDir,
                                   LPCSTR pszCmd,
                                   LPCSTR pszParam,
                                   int iShowCmd)
{
    ODS("CShellExt::DoGAKMenu4()\r\n");

    MessageBox(hParent, "Menu item 4!", "Shell Extension Sample", MB_OK);

    return NOERROR;
}
