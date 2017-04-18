/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// AddInInt.cpp : implementation file

/*  Commands Exported By WndTabs Through AddInComm
    ==============================================

    Commands are case-insensitive.


    === IsSubclassed

        Syntax:  IsSubclassed hwnd_in_hex

        Params:  hwnd_in_hex is a window handle in hex.

        Returns:  1  subclassed by WndTabs
                  0  not subclassed by WndTabs
                 -5  error
                 
        Use this command to check if a certain window is currently subclassed
        by WndTabs.


    === Subclass

        Syntax:  Subclass hwnd_in_hex

        Params:  hwnd_in_hex is the handle of the window to subclass, in hex.

        Returns:  1  subclassing was successful
                  0  no subclassing occurred (no error)
                 -2  already subclassed
                 -3  subclassing failed
                 -4  illegal window
                 -5  general error
                 
        Use this command to re-subclass windows that were unsubclassed using 
        the "Unsubclass" command.  No other windows should be used.


    === Unsubclass

        Syntax:  Unsubclass hwnd_in_hex

        Params:  hwnd_in_hex is the handle of the window to unsubclass, in 
                    hex.

        Returns:  1  unsubclassing was successful
                  0  no unsubclassing occurred (no error)
                 -2  already unsubclassed
                 -3  unsubclassing failed
                 -4  illegal window
                 -5  general error
                 
        Use this command to unsubclass windows that were subclassed by 
        WndTabs.  You should then re-subclass the windows using the 
        "Subclass" command.  Leaving a window unsubclassed can cause 
        instability, so re-subclass before DevStudio regains control.
*/

#include "stdafx.h"
#include "WndTabs.h"
#include "TabManagerWindow.h"
#include "DSWindow.h"
#include "DevStudioWnd.h"
#include "..\WndTabsSDK\WndTabsInt.h"
#include "..\WndTabsSDK\WTSDKDefs_Priv.h"
#include "DS_MDIWnd.h"
#include "SDK_Supp.h"
#include "TabsWindow.h"
#include "Extensions.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// notice that -1 isn't used, becuase this is the error code AddInComm uses
// to indicate that a command was not found
#define ERR_SUCCESS             1
#define ERR_PARVE               0
#define ERR_ALREADYCLASSED     -2
#define ERR_CLASSINGFAILED     -3
#define ERR_ILLEGALWIN         -4
#define ERR_GENERR             -5

static CSubclassWnd **ppSubclassed[] =
{
    (CSubclassWnd **)(&pGlobalActiveDSWindow), 
    (CSubclassWnd **)(&pGlobalActiveManager), 
    (CSubclassWnd **)(&g_pDevStudioWnd)
};


int OnIsSubclassed(LPCTSTR pParams)
{
    HWND hWnd;

    if (sscanf(pParams, "%x", &hWnd) != 1)
        return ERR_GENERR;

    if (hWnd)
    {
        for (int i = 0; i < countof(ppSubclassed); i++)
        {
            if (*ppSubclassed[i]  &&  hWnd == (**ppSubclassed[i]).m_hWnd)
            {
                ASSERT_VALID(*ppSubclassed[i]);
                return 1;
            }
        }
    }

    return 0;
}

int SubclassFns(LPCTSTR pParams, bool bDoSubclass)
{
    int             iRetVal = ERR_PARVE;
    HWND            hWnd;
    CSubclassWnd *  pWnd = NULL;

    if (sscanf(pParams, "%x", &hWnd) != 1)
        return ERR_GENERR;

    if (hWnd)
    {
        for (int i = 0; i < countof(ppSubclassed); i++)
        {
            if (*ppSubclassed[i]  &&  
                hWnd == (**ppSubclassed[i]).m_Saved_hWnd)
            {
                pWnd = *ppSubclassed[i];
                break;
            }
        }
        if (!pWnd)
        {
            iRetVal = ERR_ILLEGALWIN;
            WT_L1_TRACE(
                "WndTabs: Unknown window handle passed to On%subclass, "
                "HWND=%p", (bDoSubclass? "S" : "Uns"), hWnd);
        }
    }

    if (pWnd)
    {
        ASSERT_VALID(pWnd);
        if (pWnd->m_bIsSubclassed == bDoSubclass)
        {
            iRetVal = ERR_ALREADYCLASSED;
        }
        else
        {
            if (bDoSubclass)
                pWnd->DoSubclass();
            else
                pWnd->DoUnsubclass();

            iRetVal = (pWnd->m_bIsSubclassed == bDoSubclass)? 
                ERR_SUCCESS : ERR_CLASSINGFAILED;
        }
    }

    return iRetVal;
}

int OnSubclass(LPCTSTR pParams)
{
    return SubclassFns(pParams, true);
}

int OnUnsubclass(LPCTSTR pParams)
{
    return SubclassFns(pParams, false);
}

int OnRegisterAddon(LPCTSTR pParams)
{
    WTSDK_AddonInfo *pAOI;

    if (sscanf(pParams, "%x", &pAOI) != 1)
    {
        ASSERT(0);
        return WTSDK_ERR_BADPARAM;
    }

    AddAddonToList(pAOI);
    return 1;
}

int OnUnregisterAddon(LPCTSTR pParams)
{
    RemoveAddonFromActiveList(pParams);
    return 1;
}

int OnGetCmdContext(LPCTSTR pParams)
{
    int iTab;
    WTSDK_CommandContext *pCtx;
    if (sscanf(pParams, "%d %x", &iTab, &pCtx) != 2)
    {
        ASSERT(0);
        return WTSDK_ERR_BADPARAM;
    }
    const int cTabs = pGlobalTabs->m_pTabCtrl->GetItemCount();
    if (iTab < 0  ||  iTab > cTabs)
    {
        ASSERT(0);
        return WTSDK_ERR_BADPARAM;
    }
    return (int)pGlobalTabs->GetCommandContext(iTab, *pCtx);
}

int OnGetTabGroup(LPCTSTR pParams)
{
    int iTab;
    unsigned char *pTabs;
    if (sscanf(pParams, "%d %x", &iTab, &pTabs) != 2)
    {
        ASSERT(0);
        return WTSDK_ERR_BADPARAM;
    }
    
    const int cTabs = pGlobalTabs->m_pTabCtrl->GetItemCount();
    
    if (iTab < 0  ||  iTab > cTabs)
    {
        ASSERT(0);
        return WTSDK_ERR_BADPARAM;
    }
    
    if (pGlobalTabs == NULL  ||  !pGlobalTabs->m_hWnd)
    {
        return WTSDK_ERR_GENERALERR;
    }

    int iGroupCount = 0;
    if (pGlobalTabs->m_bIsWTTab)
    {
        int *pInfo = new int[cTabs];
        WTTabCtrlGetGroupInfo(pGlobalTabs->m_pTabCtrl, pInfo);
        const int iGroupID = pInfo[iTab];
        int j = 0;
        for (int i = 0; i < cTabs; ++i)
        {
            if (pInfo[i] == iGroupID)
            {
                pTabs[iGroupCount] = (unsigned char)i;
                ++iGroupCount;
            }
        }
        delete [] pInfo;
    }
    else
    {
        ++iGroupCount;
        pTabs[0] = iTab;
    }

    return iGroupCount;
}


int OnForceTabUpdate(LPCTSTR pParams)
{
    pGlobalMDIManager->PostUpdateMessage();
    return 1;
}


struct command_t
{
    LPCTSTR pName;
    int (*pFn)(LPCTSTR pParams);
};


static command_t commands[] = 
{
    // most recently used commands first!

    // SDK support
    { WTSDK_WT_CMD_GET_CMD_CONTEXT,  OnGetCmdContext   },
    { WTSDK_WT_CMD_FORCE_UPDATE,     OnForceTabUpdate  },
    { WTSDK_WT_CMD_GET_TAB_GROUP,    OnGetTabGroup     },
    { WTSDK_WT_CMD_REGISTER_ADDON,   OnRegisterAddon   },
    { WTSDK_WT_CMD_UNREGISTER_ADDON, OnUnregisterAddon },

    // misc commands
    { "IsSubclassed",   OnIsSubclassed },
    { "Subclass",       OnSubclass     },
    { "Unsubclass",     OnUnsubclass   }
};


// callback for AddInComm
int AddInCallback(LPCTSTR pCmd)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    int i, p;

    // isolate command string (command string -> buf)
    p = 0;
    while (isspace(*pCmd)) ++pCmd;
    while (pCmd[p]  &&  !isspace(pCmd[p])) p++;
    const int len = p;

    // see if it's a known command
    for (i = 0; i < countof(commands); i++)
    {
        if (_tcsnicmp(pCmd, commands[i].pName, len) == 0  &&
            commands[i].pName[len] == '\0')
        {
            // trim white space from beginning of params
            while (isspace(pCmd[p])) p++;
   
            return (commands[i].pFn(pCmd + p));
        }
    }

    return -1;
}
