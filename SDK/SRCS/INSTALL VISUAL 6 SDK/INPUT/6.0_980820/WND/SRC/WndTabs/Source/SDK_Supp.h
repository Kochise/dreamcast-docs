/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


#ifndef __SDK_SUPP_H
#define __SDK_SUPP_H

#include "..\WndTabsSDK\WTSDKDefs.h"

struct WTSDK_AddonInfo;
struct WTSDK_TabUpdateInfo;

const iAddOnCmdsStart = 5000;
const iAddOnCmdsEnd   = 5499;

struct ImportedCommand
{
    ImportedCommand() : uiAssignedCmdID(0) {};

//    wt_auto_icon hIcon;
    CString      sName;
    unsigned     uiAssignedCmdID;
    int          iAddOnCmdNum;
    WTSDK_UIUpadateFlags UIUpdateFlags;

    struct PermanentAddonInfo *pOwner;
};

struct AssignedCommand
{
    int              iNumber;
    ImportedCommand *pCmdRec;
};

struct PermanentAddonInfo
{
    PermanentAddonInfo() : bIsValid(FALSE) {}

    bool                                      bIsValid;
    CString                                   sAddOnName;
    CArray<ImportedCommand, ImportedCommand&> Commands;

    PermanentAddonInfo& operator = (const PermanentAddonInfo& rhs)
    {
        bIsValid = rhs.bIsValid;
        sAddOnName = rhs.sAddOnName;
        Commands.Copy(rhs.Commands);
        return *this;
    }
};


extern CMap<CString, LPCTSTR, PermanentAddonInfo, PermanentAddonInfo&> g_PermanentAddons;


void RefreshActiveAddonsList();
void ResetPermanentAddonList();
void AddAddonToList(WTSDK_AddonInfo *pInfo);
void RemoveAddonFromActiveList(CString sAddonName);

const ImportedCommand* GetImportedCommand(int iCmdID);
int ImportedCommandToWndTabsCommand(const char *pszAddonName, int iCmdID);
void ExecuteImportedCommand(int iCmdID);
void ExecuteUIUpdate(int iCmdID, CCmdUI *pCmdUI);
void SendWndTabsEvent(WndTabsEvents event, int ExtraInfo);

void LoadAddonConfiguration();
void WriteAddonConfiguration();

void ResetTabEventAddinCache();
void DoTabEvent(WTSDK_TabUpdateInfo* pTabUpdateInfo);

#endif // __SDK_SUPP_H
