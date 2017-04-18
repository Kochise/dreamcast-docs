/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


#include "stdafx.h"
#include "WndTabs.h"
#include "AddInComm\AddInComm.h"
#include "..\WndTabsSDK\WTSDKDefs.h"
#include "..\WndTabsSDK\WTSDKDefs_Priv.h"
#include "TabManagerWindow.h"
#include "Config.h"
#include "SDK_Supp.h"
#include "MainFrame.h"
#include "TabsWindow.h"
#include "DontShowAgainDlg.h"

struct ActiveAddonInfo
{
    ActiveAddonInfo() : iCacheID(-1) {}

    WTSDK_AddonInfo sdk_aoi;
    int iCacheID;
    HADDIN hAddinCached;
};

static CList<ActiveAddonInfo, ActiveAddonInfo&> s_ActiveAddons;
static CMap<CString, LPCTSTR, POSITION, POSITION&> s_ActiveAddonsMap;
static CMap<int, int, ImportedCommand*, ImportedCommand* &> s_ImportedCmdsXlate;
CMap<CString, LPCTSTR, PermanentAddonInfo, PermanentAddonInfo&> g_PermanentAddons;

static int s_iCurrCacheID;


void RefreshActiveAddonsList()
{
    HADDIN  *pAddins;
    int      i, addins, ires;

    addins = AICGetAddInCount();
    pAddins = new HADDIN[addins];
    AICGetAddInList(pAddins);

    s_ActiveAddons.RemoveAll();
    s_ActiveAddonsMap.RemoveAll();

    for (i = 0; i < addins; i++)
    {
        ires = AICSendCommand(pAddins[i], WTSDK_CMD_QUERY_ADDON);
        if (ires < -10  ||  ires > 0)
        {
            AddAddonToList((WTSDK_AddonInfo *)ires);
        }
    }

    delete [] pAddins;
}

void RemoveAddonFromActiveList(CString sAddonName)
{
    PermanentAddonInfo& paoi = g_PermanentAddons[sAddonName];
    if (paoi.bIsValid)
    {
        ImportedCommand *pICmd;
        POSITION p = s_ImportedCmdsXlate.GetStartPosition();
        int idCmd;
        while (p)
        {
            s_ImportedCmdsXlate.GetNextAssoc(p, idCmd, pICmd);
            if (pICmd->pOwner == &paoi)
            {
                s_ImportedCmdsXlate.RemoveKey(idCmd);
            }
        }
        paoi.bIsValid = false;
    }

    POSITION pos;
    if (s_ActiveAddonsMap.Lookup(sAddonName, pos))
    {
        s_ActiveAddons.RemoveAt(pos);
        s_ActiveAddonsMap.RemoveKey(sAddonName);
    }
    pGlobalActiveManager->PostUpdateMessage();
}


void ResetPermanentAddonList()
{
    g_pMainFrame->m_wndAddOnToolbar.RemoveAllButtons();
    CBCGCommandManager *pCmdMgr = GetCmdMgr();
    for (int i = iAddOnCmdsStart; i <= iAddOnCmdsEnd; i++)
    {
        pCmdMgr->ClearCmdImage(i);
    }
    s_ActiveAddons.RemoveAll();
    g_PermanentAddons.RemoveAll();
    s_ImportedCmdsXlate.RemoveAll();    
    RefreshActiveAddonsList();

    return;
}

void AddAddonToList(WTSDK_AddonInfo *pInfo)
{
    POSITION pos;
    CString sName = pInfo->pszAddOnName;
    int iImage;

//    WT_ASSERT(pInfo->cbSize == 40);
    if (pInfo->cbSize < 40)
    {   
        // bad structure
        return;
    }
    if (pInfo->CompatibilityID != 1)
    {
        // incompatible
        return;
    }

    // already in list?
    if (s_ActiveAddonsMap.Lookup(sName, pos) == FALSE)
    {
        // no - add it
        ActiveAddonInfo aaoi;
        aaoi.sdk_aoi = *pInfo;
        s_ActiveAddonsMap[sName] = s_ActiveAddons.AddTail(aaoi);

        // add to perminant map if needed

        PermanentAddonInfo paoi;        

        if (pInfo->pTabUpdateEvFn  &&  !g_bUseWndTabsExt  &&
            g_PermanentAddons.Lookup(sName, paoi) == FALSE)
        {
            WT_MANAGE_STATE();
            CString msg;
            AfxFormatString1(msg, IDS_ADDON_FOR_WTX, pInfo->pszAddOnName);
            CDontShowAgainDlg::DoMessageBox(msg, cfg_bShowAddonWTXInfo,
                MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
        }

        // "permanent" commands aren't supported yet

//        if (g_PermanentAddons.Lookup(sName, paoi) == FALSE)
        {
            PermanentAddonInfo& refPaoi = g_PermanentAddons[sName];

            refPaoi.Commands.RemoveAll();

            refPaoi.sAddOnName = sName;
            refPaoi.bIsValid = true;
            if (pInfo->pUIUpdateEvFn && pInfo->iNumberOfCommands)
            {
                refPaoi.Commands.SetSize(pInfo->iNumberOfCommands);
                for (int i = 0; i < pInfo->iNumberOfCommands; i++)
                {
                    WTSDK_ExportedCommand& xcmd = pInfo->pExportedCommands[i];
                    ImportedCommand& icmd = refPaoi.Commands[i];

                    icmd.sName = xcmd.pszName;
                    icmd.UIUpdateFlags = xcmd.UIUpdateFlags;
                    icmd.iAddOnCmdNum = xcmd.iCmd;
                    icmd.pOwner = &refPaoi;
                    for (icmd.uiAssignedCmdID = iAddOnCmdsStart;
                         GetImportedCommand(icmd.uiAssignedCmdID) != NULL;
                         icmd.uiAssignedCmdID++);
                    s_ImportedCmdsXlate[icmd.uiAssignedCmdID] = &icmd;

                    if (xcmd.hBmp)                    
                    {
                        iImage = theApp.AddUserImageUnique(xcmd.hBmp);
                        g_pMainFrame->m_wndAddOnToolbar.InsertButton(
                            CBCGToolbarButton(icmd.uiAssignedCmdID,
                                iImage, icmd.sName, TRUE));
                    }
					else
					{
						CBCGCommandManager *pCmdMgr = GetCmdMgr();
						pCmdMgr->ClearCmdImage(icmd.uiAssignedCmdID);
					}
                }
            }
        }
    }
    pGlobalActiveManager->PostUpdateMessage();
}


void LoadAddonConfiguration()
{
    // reset this stuff between sessions
    s_ActiveAddonsMap.RemoveAll();
    s_ActiveAddons.RemoveAll();
    s_ImportedCmdsXlate.RemoveAll();
    g_PermanentAddons.RemoveAll();

    // permanent commands aren't supported yet, but when they will be, their
    // info will be loaded here
}


void WriteAddonConfiguration()
{
    // permanent commands aren't supported yet
}

void ResetTabEventAddinCache()
{
    ++s_iCurrCacheID;
}

void DoTabEvent(WTSDK_TabUpdateInfo* pTabUpdateInfo)
{
    char msg[128];
    HADDIN hAddin;

    if (s_ActiveAddons.GetCount() == 0)
    {
        return;
    }

    WTSDK_CommandContext ctx;
    ctx.cbSize = sizeof(ctx);
    pGlobalTabs->GetCommandContext(pTabUpdateInfo->iTabNumber, ctx);
    sprintf(msg, WTSDK_CMD_TAB_EVENT " %x %x", pTabUpdateInfo, &ctx);

    WT_L4_TRACE("Dispatching Tab Event: Cmd=\"%s\"\n", msg);

    for (int iStages = 0; iStages < 2; ++iStages)
    {
        if (iStages == 0)
        {
            pTabUpdateInfo->stage = WTSDK_TabUpdateInfo::change;
        }
        else
        {
            pTabUpdateInfo->stage = WTSDK_TabUpdateInfo::modify;
        }

        POSITION p = s_ActiveAddons.GetHeadPosition();
        while (p)
        {
            ActiveAddonInfo& aaoi = s_ActiveAddons.GetNext(p);

            if (aaoi.sdk_aoi.pTabUpdateEvFn != NULL)
            {
                // the function isn't called directly because the addon 
                // might have been unloaded by the user.  the user can then 
                // load an older version of the addin that doesn't support 
                // the function or a whole bunch of other things.  we'll let 
                // AddInComm resolve these issues...
                if (aaoi.iCacheID != s_iCurrCacheID)
                {
                    aaoi.iCacheID = s_iCurrCacheID;
                    aaoi.hAddinCached = 
                        AICGetAddIn(aaoi.sdk_aoi.pszAddOnName);
                }
                hAddin = aaoi.hAddinCached;
                if (hAddin)
                {
                    WT_L3_TRACE("Tab event to addon %s\n", 
                        aaoi.sdk_aoi.pszAddOnName);
                    AICSendCommand(hAddin, msg);
                }
                else
                {
                    WT_L1_TRACE("Removing obsolete addon %s", 
                        aaoi.sdk_aoi.pszAddOnName);
                    RemoveAddonFromActiveList(aaoi.sdk_aoi.pszAddOnName);
                }
            }
        }
    }
}


void SendWndTabsEvent(WndTabsEvents event, int ExtraInfo)
{
    WT_FN_TRACE_PARAMS("SendWndTabsEvent", "%d, %d", event);
    char msg[128];
    HADDIN hAddin;

    if (s_ActiveAddons.GetCount() == 0)
    {
        return;
    }

    sprintf(msg, WTSDK_CMD_WT_EVENT " %x %x", event, ExtraInfo);

    POSITION p = s_ActiveAddons.GetHeadPosition();
    while (p)
    {
        ActiveAddonInfo& aaoi = s_ActiveAddons.GetNext(p);

        if (aaoi.sdk_aoi.pEvNotificationFn != NULL   &&
            (aaoi.sdk_aoi.event_mask & event) == event)
        {
            if (aaoi.iCacheID != s_iCurrCacheID)
            {
                aaoi.iCacheID = s_iCurrCacheID;
                aaoi.hAddinCached = 
                    AICGetAddIn(aaoi.sdk_aoi.pszAddOnName);
            }
            hAddin = aaoi.hAddinCached;
            if (hAddin)
            {
                WT_L3_TRACE("Event sent to addon %s\n", 
                    aaoi.sdk_aoi.pszAddOnName);
                AICSendCommand(hAddin, msg);
            }
            else
            {
                WT_L1_TRACE("Removing obsolete addon %s", 
                    aaoi.sdk_aoi.pszAddOnName);
                RemoveAddonFromActiveList(aaoi.sdk_aoi.pszAddOnName);
            }
        }
    }
}


const ImportedCommand* GetImportedCommand(int iCmdID)
{
    ImportedCommand *pICmd;
    if (s_ImportedCmdsXlate.Lookup(iCmdID, pICmd))
    {
        return pICmd;
    }

    return NULL;
}

int ImportedCommandToWndTabsCommand(const char *pszAddonName, int iCmdID)
{
    ImportedCommand *pICmd;
    int iWTCmd;
    POSITION p = s_ImportedCmdsXlate.GetStartPosition();
    while (p)
    {
        s_ImportedCmdsXlate.GetNextAssoc(p, iWTCmd, pICmd);
        if (pICmd->iAddOnCmdNum == iCmdID  &&
            strcmp(pszAddonName, pICmd->pOwner->sAddOnName) == 0)
        {
            return iWTCmd;
        }
    }
    return -1;
}


void ExecuteImportedCommand(int iCmdID)
{
    const ImportedCommand * const pICmd = GetImportedCommand(iCmdID);

    if (!pICmd) return;

    WT_ASSERT(pICmd->pOwner);
    WT_ASSERT(pICmd->pOwner->bIsValid);
    WT_ASSERT(CMainFrame::m_pCmdCtx);

    CString sCmd;

    sCmd.Format("%s %d %x", WTSDK_CMD_EXEC_COMMAND, pICmd->iAddOnCmdNum,
        CMainFrame::m_pCmdCtx);
    AICSendCommand(AICGetAddIn(pICmd->pOwner->sAddOnName), sCmd);
}

void ExecuteUIUpdate(int iCmdID, CCmdUI *pCmdUI)
{
    const ImportedCommand * const pICmd = GetImportedCommand(iCmdID);

    if (!pICmd) return;

    WT_ASSERT(pICmd->pOwner);
    WT_ASSERT(pICmd->pOwner->bIsValid);
    WT_ASSERT(CMainFrame::m_pCmdCtx);
    WT_ASSERT(pCmdUI != NULL);

    const WTSDK_UIUpadateFlags UIUpdateFlags = pICmd->UIUpdateFlags;

    if (UIUpdateFlags == UI_AlwaysAvailable)
    {
        return;
    }

    bool bAvailable = true;
    const WTSDK_CommandContext * const pCtx = CMainFrame::m_pCmdCtx;

    if (UIUpdateFlags & UI_MustHaveFile)
    {
        bAvailable &= (pCtx  &&  pCtx->bHasFile);
    }

    if (UIUpdateFlags & UI_MustHaveDoc)
    {
        bAvailable &= (pCtx  &&  pCtx->bHasDoc);
    }

    if (UIUpdateFlags & UI_MustHaveTextDoc)
    {
        bAvailable &= (pCtx  &&  pCtx->bHasDoc  && pCtx->bIsTextWindow);
    }

    if (UIUpdateFlags & UI_MustHaveOpenWindows)
    {
        bAvailable &= (pCtx  &&  pCtx->hWnd);
    }

    if (UIUpdateFlags & UI_MustBeActiveWindow)
    {
        bAvailable &= (pCtx  &&  pCtx->bIsActiveWindow);
    }

    if (!bAvailable)
    {
        pCmdUI->Enable(FALSE);
    }

    if (UIUpdateFlags & UI_UseCallback)
    {
        CString sCmd;

        sCmd.Format("%s %d %x %x", WTSDK_CMD_UI_UPDATE, pICmd->iAddOnCmdNum,
            pCmdUI, pCtx);

    	VERIFY_OK(pGlobalTabs->m_pApplication->EnableModeless(VARIANT_FALSE));

        AICSendCommand(AICGetAddIn(pICmd->pOwner->sAddOnName), sCmd);

    	VERIFY_OK(pGlobalTabs->m_pApplication->EnableModeless(VARIANT_TRUE));
    }
}
