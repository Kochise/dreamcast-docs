/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

// WNDTABS SDK - Primary Functionality

#include "stdafx.h"

#include "WndTabsInt.h"
#include "WTSDKDefs_Priv.h"

// This will grab the AddInComm header off the WndTabs sources if you have
// them installed in the following directory structure:
// +-+-- WndTabsSDK
//   |
//   +-- Source (WndTabs Sources)
// If not, correct this line to point at your local copy of AddInComm
#include "..\Source\AddInComm\AddInComm.h"


// This number will be used by WndTabs to identify addons and their SDK
// versions.  In case the SDK changes dramatically (breaking backward 
// compatibility), the number will be incremented.
const int SDK_COMPATIBILITY_ID = 1; 


static WTSDK_AddonInfo          s_AddonInfo;
static CString                  s_sAddInName;
static WTSDK_ExportedCommand ** s_ppExportedCommands;
static WTSDK_TabUpdateEvFn *    s_pTabUpdateEvFn;
static bool                     s_bInited = false;
static WTSDK_ExportedCommand *  s_pExpCmd;

static LONG   s_hAddinCacheRef = 0;
static HADDIN s_hAddinCached   = NULL;

int SendCmdToWndTabs(LPCTSTR pszCmd);

void InitWndTabsIntegration(LPCTSTR pszAddOnName,
                            WTSDK_TabUpdateEvFn *   pTabUpdateEvFn,
                            WTSDK_CmdEvFn *         pCmdEvFn,
                            WTSDK_UIUpdateEvFn *    pUIEvFn,
                            WTSDK_CommandDef *      pCmdArray,
                            int                     iNumCmds,
                            WTSDK_EvNotificationFn *pEvNotificationFn,
                            unsigned int            event_mask)
{
    // must either be looking for tab updates or adding commands!
    ASSERT(pTabUpdateEvFn != NULL  ||  pCmdEvFn != NULL);

    // event_mask must be 0 if not asking for event notifications, and
    ASSERT(!(pEvNotificationFn != NULL  &&  event_mask == 0));

    int i;

    s_pExpCmd = NULL;

    int iVerMaj, iVerMin, iVerExtra;
    AICGetDllVersion(iVerMaj, iVerMin, iVerExtra);

    // needs AIC ver >= 1.4.0
    if (iVerMaj <= 1  &&  iVerMin < 4)
    {
        _RPTF3(_CRT_ASSERT, 
            "\n\n"
            "==================================================\n"
            "\n"
            "WndTabs Integration requires AIC 1.4.0 or above.\n"
            "The version detected on your system was: %d.%d.%d\n"
            "Press \"Ignore\" to continue execution with WndTabs "
            "integration disabled.\n"
            "\n"
            "(Note: this message only appears on debug builds.)\n"
            "\n"
            "=================================================\n",
            iVerMaj, iVerMin, iVerExtra);
        return;
    }

    s_AddonInfo.CompatibilityID   = SDK_COMPATIBILITY_ID;
    s_AddonInfo.pszAddOnName      = pszAddOnName;
    s_AddonInfo.pTabUpdateEvFn    = pTabUpdateEvFn;
    s_AddonInfo.pCmdEvFn          = pCmdEvFn;
    s_AddonInfo.pUIUpdateEvFn     = pUIEvFn;
    s_AddonInfo.pEvNotificationFn = pEvNotificationFn;
    s_AddonInfo.event_mask        = event_mask;

    if (pCmdEvFn)
    {
        ASSERT(iNumCmds != 0);  // must have commands if pCmdEvFn != NULL

        s_pExpCmd = new WTSDK_ExportedCommand[iNumCmds];

        s_AddonInfo.iNumberOfCommands = iNumCmds;
        s_AddonInfo.pExportedCommands = s_pExpCmd;
        
        for (i = 0; i < iNumCmds; i++, pCmdArray++)
        {
            WTSDK_ExportedCommand& cmdexp = s_pExpCmd[i];
            WTSDK_CommandDef&      cmddef = *pCmdArray;

            cmdexp.cbSize = sizeof(cmdexp);
            cmdexp.UIUpdateFlags = cmddef.UIUpdateFlags;
            cmdexp.iCmd          = cmddef.iCmd;
            cmdexp.pszName       = cmddef.pszName;
            if (cmddef.idBmpRes != -1)
            {
                cmdexp.hBmp = (HBITMAP)::LoadImage(AfxGetResourceHandle(), 
                    MAKEINTRESOURCE(cmddef.idBmpRes), IMAGE_BITMAP, 16, 16, 
                    LR_DEFAULTCOLOR);
            }
            else
                cmdexp.hBmp = NULL;
        }
    }

    char cmd[128];
    sprintf(cmd, WTSDK_WT_CMD_REGISTER_ADDON " %x", &s_AddonInfo);
    s_hAddinCached = AICGetAddIn("WndTabs");
    if (s_hAddinCached)
    {
        AICSendCommand(s_hAddinCached, cmd);
    }

    s_bInited = true;
}


void EndWndTabsIntegration()
{
    if (s_bInited)
    {
        CString cmd;
        cmd.Format(WTSDK_WT_CMD_UNREGISTER_ADDON " %s", 
            s_AddonInfo.pszAddOnName);
        SendCmdToWndTabs(cmd);

        if (s_pExpCmd)
        {
            for (int i = 0; i < s_AddonInfo.iNumberOfCommands; i++)
            {
                WTSDK_ExportedCommand& cmdexp = s_pExpCmd[i];
                if (cmdexp.hBmp)
                    ::DeleteObject(cmdexp.hBmp);
            }
            delete [] s_pExpCmd;
        }

    }
}

int OnQueryAddon(LPCTSTR pParams)
{
    s_hAddinCached = AICGetAddIn("WndTabs");
    return (int)&s_AddonInfo;    
}

int OnTabEvent(LPCTSTR pParams)
{
    WTSDK_CommandContext *pCmdContext;
    WTSDK_TabUpdateInfo *pTabUpdateInfo;
    if (sscanf(pParams, "%x %x", &pTabUpdateInfo, &pCmdContext) != 2)
        return WTSDK_ERR_BADPARAM;

    if (s_AddonInfo.pTabUpdateEvFn  &&  pTabUpdateInfo)
    {
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
    
        (*s_AddonInfo.pTabUpdateEvFn)(pTabUpdateInfo, pCmdContext);
        return 1;
    }

    return 0;
}

int OnWTEvent(LPCTSTR pParams)
{
    WndTabsEvents event;
    int extraParam;
    if (sscanf(pParams, "%x %x", &event, &extraParam) != 2)
        return WTSDK_ERR_BADPARAM;

    if (s_AddonInfo.pEvNotificationFn)
    {
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
    
        (*s_AddonInfo.pEvNotificationFn)(event, extraParam);
        return 1;
    }

    return 0;
}

int OnExecCmd(LPCTSTR pParams)
{
    int iCmd;
    WTSDK_CommandContext *pCmdContext;

    if (sscanf(pParams, "%d %x", &iCmd, &pCmdContext) != 2)
    {
        return WTSDK_ERR_BADPARAM;
    }

    if (s_AddonInfo.pCmdEvFn  &&  pCmdContext)
    {
        AFX_MANAGE_STATE(AfxGetStaticModuleState());
        
        s_AddonInfo.pCmdEvFn(iCmd, pCmdContext);
    }

    return 0;    
}

int OnUIUpdate(LPCTSTR pParams)
{
    int     iCmd;
    CCmdUI *pCmdUI;
    WTSDK_CommandContext *pCmdContext;

    if (sscanf(pParams, "%d %x %x", &iCmd, &pCmdUI, &pCmdContext) != 3)
    {
        AFX_MANAGE_STATE(AfxGetStaticModuleState());

        return WTSDK_ERR_BADPARAM;
    }

    if (s_AddonInfo.pUIUpdateEvFn  &&  pCmdContext  &&  pCmdUI)
    {
        s_AddonInfo.pUIUpdateEvFn(iCmd, pCmdUI, pCmdContext);
    }

    return 0;    
}

struct command_t
{
    LPCTSTR pName;
    int (*pFn)(LPCTSTR pParams);
};

static command_t commands[] = 
{
    // most recently used commands first!
    { WTSDK_CMD_TAB_EVENT,     OnTabEvent   },
    { WTSDK_CMD_WT_EVENT,      OnWTEvent    },
    { WTSDK_CMD_UI_UPDATE,     OnUIUpdate   },
    { WTSDK_CMD_EXEC_COMMAND,  OnExecCmd    },
    { WTSDK_CMD_QUERY_ADDON,   OnQueryAddon }
};

int WndTabsInt_Callback(LPCTSTR pCmd)
{
    if (!s_bInited) return -1;

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
            AFX_MANAGE_STATE(AfxGetStaticModuleState());

            // trim white space from beginning of params
            while (isspace(pCmd[p])) p++;
   
            InterlockedIncrement(&s_hAddinCacheRef);
            const int iRetVal = (commands[i].pFn(pCmd + p));
            InterlockedDecrement(&s_hAddinCacheRef);
            return iRetVal;
        }
    }

    return -1;
}

void ForceTabUpdate()
{
    SendCmdToWndTabs(WTSDK_WT_CMD_FORCE_UPDATE);
}

bool GetCommandContext(int iTab, WTSDK_CommandContext& ctx)
{
    char cmd[128];
    sprintf(cmd, WTSDK_WT_CMD_GET_CMD_CONTEXT " %d %x", iTab, &ctx);
    
    return (SendCmdToWndTabs(cmd) > 0);
}

int GetTabGroup(int iTab, group_array& tabs)
{
    char cmd[128];
    sprintf(cmd, WTSDK_WT_CMD_GET_TAB_GROUP " %d %x", iTab, &tabs);
    
    return SendCmdToWndTabs(cmd);
}


int SendCmdToWndTabs(LPCTSTR pszCmd)
{
    const HADDIN hAddIn =
        (s_hAddinCacheRef == 0)? AICGetAddIn("WndTabs") : s_hAddinCached;

    if (hAddIn)
    {
        return AICSendCommand(hAddIn, pszCmd);
    } 

    return -1;
}
