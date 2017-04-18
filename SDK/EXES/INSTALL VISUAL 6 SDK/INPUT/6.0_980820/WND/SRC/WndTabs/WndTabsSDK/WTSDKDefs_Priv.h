/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

// WNDTABS SDK - Internal Definitions

#ifndef __WTSDKDEFS_PRIV_H
#define __WTSDKDEFS_PRIV_H

// Commands implemented by the SDK
#define WTSDK_CMD_QUERY_ADDON         "WTSDK_Query_WT_Addon"
#define WTSDK_CMD_TAB_EVENT           "WTSDK_Tab_Event"
#define WTSDK_CMD_EXEC_COMMAND        "WTSDK_Exec_Command"
#define WTSDK_CMD_UI_UPDATE           "WTSDK_UI_Update"
#define WTSDK_CMD_WT_EVENT            "WTSDK_WT_Event"

// SDK support commands implemented by Wndtabs
#define WTSDK_WT_CMD_REGISTER_ADDON   "Register_WT_Addon"
#define WTSDK_WT_CMD_UNREGISTER_ADDON "Unregister_WT_Addon"
#define WTSDK_WT_CMD_GET_CMD_CONTEXT  "Get_Cmd_Context"
#define WTSDK_WT_CMD_FORCE_UPDATE     "Force_Tab_Update"
#define WTSDK_WT_CMD_GET_TAB_GROUP    "Get_Tab_Group"

// SDK error codes
#define WTSDK_ERR_NOTSUPPORTED        -1
#define WTSDK_ERR_GENERALERR          -2
#define WTSDK_ERR_BADPARAM            -3


struct WTSDK_ExportedCommand
{
    UINT    cbSize;     /* set to size of this structure */

    HBITMAP hBmp;
    LPCSTR  pszName;
    int     iCmd;
    WTSDK_UIUpadateFlags UIUpdateFlags;
};


struct WTSDK_AddonInfo
{
public:
    WTSDK_AddonInfo() 
    {   
        memset(this, sizeof(*this), 0); 
        cbSize = sizeof(*this);
    };

    int cbSize;
    int CompatibilityID;

    // name of addin
    const char *                pszAddOnName;

    // == Tab Update Notifiation ==

    // pointer of a function to recieve tab update notifications or NULL
    WTSDK_TabUpdateEvFn *       pTabUpdateEvFn;


    // == Event Notification ==
    WTSDK_EvNotificationFn *    pEvNotificationFn;
    int                         event_mask;

    // == Adding Commands To WndTabs ==

    // command event handler or NULL
    WTSDK_CmdEvFn *             pCmdEvFn;

    // array of pointer to commands (can be NULL if pCmdUpdateEvFn is NULL)
    WTSDK_ExportedCommand *     pExportedCommands;
    int                         iNumberOfCommands;

    // optional function used for UI update notifications (or NULL)
    WTSDK_UIUpdateEvFn *        pUIUpdateEvFn;
};




#endif // __WTSDKDEFS_PRIV_H
