/*+==========================================================================
  File:      RESDEF.H

  Summary:   Resource include file for the PERCLIEN code sample
             application. Contains definitions of the application's menu,
             string, and other resource IDs.

             For a comprehensive tutorial code tour of PERCLIEN's contents
             and offerings see the tutorial PERCLIEN.HTM file. For more
             specific technical details on the internal workings see the
             comments dispersed throughout the PERCLIEN source code.

  Classes:   none.

  Functions: none.

  Origin:    5-25-97: atrent - Editor-inheritance from STOCLIEN source.

----------------------------------------------------------------------------
  This file is part of the Microsoft COM Tutorial Code Samples.

  Copyright (C) Microsoft Corporation, 1997.  All rights reserved.

  This source code is intended only as a supplement to Microsoft
  Development Tools and/or on-line documentation.  See these other
  materials for detailed information regarding Microsoft code samples.

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
==========================================================================+*/

#if !defined(RESDEF_H)
#define RESDEF_H

// Main Window Class String Macros.
#define MAIN_APP_NAME_STR           "PERCLIEN: "
#define MAIN_WINDOW_TITLE_STR       "PERCLIEN: perclien.pag"
#define MAIN_WINDOW_CLASS_NAME_STR  "PERCLIENWindow"
#define MAIN_WINDOW_CLASS_MENU_STR  "PERCLIENMenu"
#define NOFILE_STR                  "No File Open"

// File Name String Macros.
#define SERVER_PERSERVE_STR          "perserve.htm"
#define SERVER_PERTEXT_STR           "pertext.htm"
#define SERVER_PERDRAW_STR           "perdraw.htm"

// OpenFile-related String Macros.
#define OFN_DEFAULTFILES_STR "All Files (*.*)\0*.*\0"
#define OFN_DEFAULTTITLE_STR "Open File"

// Main Page List Client Application Menu Command Identifiers.
// File Menu.
#define IDM_FILE_NEW                1000
#define IDM_FILE_OPEN               1001
#define IDM_FILE_SAVE               1002
#define IDM_FILE_SAVEAS             1003
#define IDM_FILE_EXIT               1004
// Page Menu.
#define IDM_PAGE_OPEN               1100
#define IDM_PAGE_TITLE              1101
#define IDM_PAGE_DELETE             1102
#define IDM_PAGE_NEWTEXT            1103
#define IDM_PAGE_NEWDRAW            1104
// Help Menu.
#define IDM_HELP_CONTENTS           1900
#define IDM_HELP_TUTORIAL           1901
#define IDM_HELP_PERSERVE           1902
#define IDM_HELP_PERTEXT            1903
#define IDM_HELP_PERDRAW            1904
#define IDM_HELP_READSOURCE         1905
#define IDM_HELP_ABOUT              1906

// Dialog and Control IDs.
#define IDD_PAGE_PROPS              5000
#define IDC_STATIC_PGTITLE          5001
#define IDC_EDIT_PGTITLE            5002

// Error-related String Identifiers.
#define IDS_COMINITFAILED           9000
#define IDS_APPINITFAILED           9001
#define IDS_NOUNICODE               9002
#define IDS_NOSERVER                9003
#define IDS_OUTOFMEMORY             9004
#define IDS_TOOMANYOPEN             9005
#define IDS_PAGEFULL                9006
#define IDS_OPENTEXTPAGE            9007
#define IDS_OPENDRAWPAGE            9008
#define IDS_NOTIMPLEMENTED          9009

#define IDS_ASSERT_FAIL             9300

// Notice-related String Identifiers.
#define IDS_TEXT_PAGE               9500
#define IDS_DRAW_PAGE               9501
#define IDS_FILE_CHANGED            9502
#define IDS_ASK_SAVE                9503
#define IDS_OFN_PAGFILES            9504
#define IDS_OFN_PAGOPEN             9505
#define IDS_OFN_PAGSAVE             9506

// Text Window definitions.

#define TEXT_WINDOW_NAME_STR        "PERCLIEN Text: "
#define TEXT_WINDOW_CLASS_NAME_STR  "TextWindow"
#define TEXT_WINDOW_CLASS_MENU_STR  "TextMenu"

// Text Window Text Menu.
#define IDM_TEXT_SAVE               2200
#define IDM_TEXT_CLEAR              2201
#define IDM_TEXT_EXIT               2202

// Text Window Edit Menu.
#define IDM_EDIT_UNDO               2300
#define IDM_EDIT_SELECTALL          2301
#define IDM_EDIT_CUT                2302
#define IDM_EDIT_COPY               2303
#define IDM_EDIT_PASTE              2304
#define IDM_EDIT_DELETE             2305

// Text Window Help Menu.
#define IDM_THELP_CONTENTS          2400
#define IDM_THELP_TUTORIAL          2401
#define IDM_THELP_TUTSERVER         2402
#define IDM_THELP_READSOURCE        2403
#define IDM_THELP_ABOUT             2404

// Draw Window definitions.

#define DRAW_WINDOW_NAME_STR        "PERCLIEN Drawing: "
#define DRAW_WINDOW_CLASS_NAME_STR  "DrawWindow"
#define DRAW_WINDOW_CLASS_MENU_STR  "DrawMenu"

// Draw Menu Command Identifiers.
#define IDM_DRAW_SAVE               2700
#define IDM_DRAW_CLEAR              2701
#define IDM_DRAW_EXIT               2702
// Pen Menu.
#define IDM_PEN_COLOR               2800
#define IDM_PEN_THIN                2801
#define IDM_PEN_MEDIUM              2802
#define IDM_PEN_THICK               2803
// Help Menu.
#define IDM_DHELP_CONTENTS          2900
#define IDM_DHELP_TUTORIAL          2901
#define IDM_DHELP_TUTSERVER         2962
#define IDM_DHELP_READSOURCE        2903
#define IDM_DHELP_ABOUT             2904


#endif // RESDEF_H
