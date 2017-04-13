/*
 * R O U T E . H
 *
 * Routing fuctions called outside of route.c
 *
 *Copyright 1995, Microsoft Corporation. All Rights Reserved.
 */

/*put a name for your own message class here*/
#define lpszSmplRTMsgClass "IPM.Note.SampleRoutingForm"


LPADRBOOK  OpenAddressBook(HWND hwnd);
BOOL CALLBACK RouteNoteDlgProc (HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL HasRoutingSlip (LPMESSAGE lpMsg);
BOOL OpenOutFolder(HWND hWnd, LPMAPIFOLDER FAR * lppF);
BOOL CreateOutMessage(LPMESSAGE FAR * lpmSrcMsgI);
