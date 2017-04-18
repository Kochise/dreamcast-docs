//************************************************************************
//**
//**  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//**  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//**  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR
//**  A PARTICULAR PURPOSE.
//**
//**  Copyright (C) 1993 - 1997 Microsoft Corporation. All Rights Reserved.
//**
//**  res.h
//**
//**  DESCRIPTION:
//**
//**
//**  HISTORY:
//**     04/22/93       created.
//**
//************************************************************************

#ifndef RES_H
#define RES_H

#define IDR_MAIN             1
#define IDR_INSTRUM          2

#define IDC_EDGE             3

#define IDD_LINEEDIT         97
#define IDD_IDFEDITDLG       98
#define IDD_ABOUT            99

//
// MENU DEFINITIONS
//
#define  IDM_FILE_BASE        (100)
#define  IDM_FILENEW          (IDM_FILE_BASE)
#define  IDM_FILEOPEN         (IDM_FILE_BASE + 1)
#define  IDM_FILESAVE         (IDM_FILE_BASE + 2)
#define  IDM_FILESAVEAS       (IDM_FILE_BASE + 3)
#define  IDM_NEW_INSTRUMENT   (IDM_FILE_BASE + 6)
#define  IDM_FILEEXIT         (IDM_FILE_BASE + 9)

#define  IDM_EDIT_BASE        (200)
#define  IDM_EDITUNDO         (IDM_EDIT_BASE + 1)
#define  IDM_EDITCUT          (IDM_EDIT_BASE + 2)
#define  IDM_EDITCOPY         (IDM_EDIT_BASE + 3)
#define  IDM_EDITPASTE        (IDM_EDIT_BASE + 4)
#define  IDM_EDITDELETE       (IDM_EDIT_BASE + 5)
#define  IDM_EDITSELECTALL    (IDM_EDIT_BASE + 6)


#define  IDM_WINDOW_BASE      (300)
#define  IDM_TILE             (IDM_WINDOW_BASE)
#define  IDM_CASCADE          (IDM_WINDOW_BASE + 1)
#define  IDM_ARRANGEICONS     (IDM_WINDOW_BASE + 2)
#define  IDM_MDIFIRSTCHILD    (IDM_WINDOW_BASE + 10)

#define  IDM_OPTIONS_BASE     (700)

#define  IDM_OBJECT_BASE      (800)
#define  IDM_OBJEDIT          (IDM_OBJECT_BASE)

#define  IDM_HELP_BASE        (900)
#define  IDM_HELP             (IDM_HELP_BASE)
#define  IDM_ABOUT            (IDM_HELP_BASE + 9)

//
// jmk
//
#define  IDS_ERR_REGCLASSES   64
#define  IDS_ERR_CREATEMAIN   65
#define  IDS_ERR_MDICLIENT    66
#define  IDS_ERR_NOHELP       67
#define  IDS_ERR_SAVE         68
#define  IDS_ERR_READONLY     69

//
// STRING TABLE DEFINITIONS
//
#define  STRINGTABLE_BASE           (0)
#define  IDS_APPNAME                (STRINGTABLE_BASE + 1)
#define  IDS_OFN_EXT_DEF            (STRINGTABLE_BASE + 2)
#define  IDS_OFN_EXT_FILTER         (STRINGTABLE_BASE + 3)
#define  IDS_DEF_FILE_NAME          (STRINGTABLE_BASE + 4)
#define  IDS_SAVE_CHANGES           (STRINGTABLE_BASE + 5)
#define  IDS_MESSAGE_BOX_TITLE      (STRINGTABLE_BASE + 6)
#define  IDS_CHANNEL                (STRINGTABLE_BASE + 7)
#define  IDS_CAPTION_BAR            (STRINGTABLE_BASE + 8)
#define  IDS_QUERY_SAVE             (STRINGTABLE_BASE + 9)

#define  IDS_CHANNEL_TYPE_BASE      (STRINGTABLE_BASE + 10)
#define  IDS_CHANNEL_TYPE_GENERAL   (IDS_CHANNEL_TYPE_BASE + 0)
#define  IDS_CHANNEL_TYPE_DRUM      (IDS_CHANNEL_TYPE_BASE + 1)
#define  IDS_CHANNEL_TYPE_LIGHTING  (IDS_CHANNEL_TYPE_BASE + 2)

#define  IDS_TREE_LABEL             (STRINGTABLE_BASE + 16)
#define  IDS_VIEW_LABEL             (STRINGTABLE_BASE + 17)

#define  IDS_YES                    (STRINGTABLE_BASE + 20)
#define  IDS_NO                     (STRINGTABLE_BASE + 21)

#define  IDS_GENERAL_INIT           (STRINGTABLE_BASE + 22)
#define  IDS_DRUM_INIT              (STRINGTABLE_BASE + 23)
#define  IDS_IS_RTL                 (STRINGTABLE_BASE + 24)
//
// ERROR VALUES
//
#define  IDFERR_BASE                (STRINGTABLE_BASE + 50)
#define  IDFERR_BADREAD             (IDFERR_BASE + 0)
#define  IDFERR_NOMEM               (IDFERR_BASE + 1)
#define  IDFERR_BADCHUNK            (IDFERR_BASE + 2)
#define  IDFERR_CANNOTCREATEFILE    (IDFERR_BASE + 3)
#define  IDFERR_CANNOTFINDCHUNK     (IDFERR_BASE + 4)
#define  IDFERR_BADWRITE            (IDFERR_BASE + 5)
#define  IDFERR_BADNUMBER           (IDFERR_BASE + 6)
#define  IDFERR_CANNOTCREATECHUNK   (IDFERR_BASE + 7)

#define  IDS_BAD_HEX_INPUT          (IDFERR_BASE+30)

#define  IDS_SECTION_NAME_BASE   (STRINGTABLE_BASE + 100)

#define  IDS_TITLE_BAR_BASE      (STRINGTABLE_BASE + 150)
#define  IDS_TITLE_BAR_HEADER    (IDS_TITLE_BAR_BASE + 0)
#define  IDS_TITLE_BAR_INSTINFO  (IDS_TITLE_BAR_BASE + 1)
#define  IDS_TITLE_BAR_INSTCAPS  (IDS_TITLE_BAR_BASE + 2)
#define  IDS_TITLE_BAR_CHANNELS  (IDS_TITLE_BAR_BASE + 3)
#define  IDS_TITLE_BAR_PATCHES   (IDS_TITLE_BAR_BASE + 4)
#define  IDS_TITLE_BAR_KEYMAPS   (IDS_TITLE_BAR_BASE + 5)

#define  IDS_HEADER_BASE         (STRINGTABLE_BASE + 200)

#define  IDS_INST_BASE           (STRINGTABLE_BASE + 300)

#define  IDS_CAPS_BASE           (STRINGTABLE_BASE + 400)


#define  GENERAL_PATCH           (STRINGTABLE_BASE + 500)
#define  DRUM_KEY                (STRINGTABLE_BASE + 700)

// 
// DIALOG INCLUDE FILE's
//
#define  IDL_INSTRUMENTS         1001
#define  IDC_CURRENT_INSTRUM     1002

// drawstr's editing dialog
//
#define IDE_VALUE            11
#define IDC_VALUELABEL       12


// obsolete
//
#define ID_CURRENT_INSTRUMENT       1102
#define ID_PREVIOUS_INSTRUMENT      1103
#define ID_NEXT_INSTRUMENT          1104
#define ID_IDF_CURRENT_SECTION      1101
#define ID_EDIT_BOX                 1106
#define ID_HEADER_TEXT_LEFT         1107
#define ID_LIST_BOX                 1109
#define ID_HEADER_TEXT_RIGHT        1108
#define ID_INSTRUMENT_SCROLL        1110
#define ID_DRUM_CHANNELS            1111
#define ID_EDIT_ENTER               1105

#endif
