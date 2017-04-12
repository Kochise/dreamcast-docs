/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

// WNDTABS SDK - Primary Interface Header

#ifndef __WNDTABSINT_H
#define __WNDTABSINT_H

#include "WTSDKDefs.h"

// Call this function to initialize the SDK (usually called during 
// DSAddIn::OnConnection())
void InitWndTabsIntegration(
    LPCTSTR pszAddOnName,                             // addin name
    WTSDK_TabUpdateEvFn *   pTabUpdateEvFn = NULL,    // tab update fn (or NULL)
    WTSDK_CmdEvFn *         pCmdEvFn = NULL,          // command handler (or NULL)
    WTSDK_UIUpdateEvFn *    pUIEvFn = NULL,           // ui handler (or NULL)
    WTSDK_CommandDef *      pCmdArray = NULL,         // command array
    int                     iNumCmds = 0,             // entries in commands array
    WTSDK_EvNotificationFn *pEvNotificationFn = NULL, // event handler (or NULL)
    unsigned int            event_mask = 0            // event mask (e.g. WndTabs_Ev_WindowChanged | WndTabs_Ev_TabClicked)
);

// Call this function to disconnect from WndTabs (usually called during 
// DSAddIn::OnDisconnection())
void EndWndTabsIntegration();

// The SDK message processing function for AddInComm commands
int WndTabsInt_Callback(LPCTSTR pCmd);

// Call this function to force the tabs to update.
void ForceTabUpdate();

// Call this function to retrieve information about any tab.  Returns 'true'
// for success, 'false' for failure.
// Warning: Very slow function - use sparingly.
bool GetCommandContext(int iTab, WTSDK_CommandContext& ctx);

// Call this function to retrieve all the tabs in a sepecific tab's group.
// Returns:
//      <0: Error (see WTSDK_ERR_xxxx constants)
//      >0: Number of tabs in group
// 
// The tabs[] array is filled with indexes of tabs in the group.  There will
// be at least one tab (iTab).  You can use GetCommandContext() to retrieve
// information about the tabs.
// 
// NOTE: If the user isn't using WndTabsExt, the group size will always be 1.
typedef unsigned char group_array[256];

int GetTabGroup(int iTab, group_array& tabs);


#endif // __WNDTABSINT_H
