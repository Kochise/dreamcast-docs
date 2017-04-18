/*
 * CLASSRES.H
 * Sample Code Class Libraries
 *
 * Definitions specifically pertaining to resources for the default
 * class libraries.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _CLASSRES_H_
#define _CLASSRES_H_

#include <bttncur.h>

//Position of Window menu and number of menus.
#define WINDOW_MENU                         2
#define CMENUS                              3



//Resource identifiers.
#define IDR_MENU                            1
#define IDR_ACCELERATORS                    1
#define IDR_DOCUMENTICON                    1
#define IDD_ABOUT                           1

#define IDR_STATMESSAGEMAP                  1

//Dialog control identifiers
#define ID_NULL                             99

//Image identifiers in the standard bmp file.
#define ID_STDGIZMOFILECLOSE                0
#define ID_STDGIZMOEDITUNDO                 1



//Menu command identifiers.
#define IDM_FILENEW                         100
#define IDM_FILEOPEN                        101
#define IDM_FILECLOSE                       102
#define IDM_FILESAVE                        103
#define IDM_FILESAVEAS                      104
#define IDM_FILEEXIT                        105
#define IDM_CUSTOMFILEMIN                   106

#define IDM_EDITUNDO                        200
#define IDM_EDITCUT                         201
#define IDM_EDITCOPY                        202
#define IDM_EDITPASTE                       203
#define IDM_CUSTOMEDITMIN                   204

#define IDM_WINDOWCASCADE                   300
#define IDM_WINDOWTILEHORZ                  301
#define IDM_WINDOWTILEVERT                  302
#define IDM_WINDOWICONS                     303
#define IDM_CUSTOMWINDOWMIN                 304

#define IDM_HELPABOUT                       400
#define IDM_CUSTOMHELPMIN                   401

//Where derivations can start using IDs.
#define IDM_CUSTOMMIN                       500


//IDs for StatStrip handling of popup menus:  must be in order of menu
#define ID_MENUSYS                          1000
#define ID_MESSAGEEMPTY                     1001
#define ID_MESSAGEREADY                     1002
#define ID_STANDARDMAX                      1002


#define ID_MENUFILE                         (ID_STANDARDMAX+1)
#define ID_MENUEDIT                         (ID_STANDARDMAX+2)
#define ID_MENUWINDOW                       (ID_STANDARDMAX+3)
#define ID_MENUHELP                         (ID_STANDARDMAX+4)
#define ID_MENUCUSTOMMIN                    (ID_STANDARDMAX+5)


/*
 * Stringtable IDs.  Keep sequential for each group.  Strings
 * are limited by CCHSTRINGMAX (see classlib.h).
 */

//Frame window junk
#define IDS_STANDARDFRAMEMIN                0
#define IDS_CAPTION                         0
#define IDS_UNTITLED                        1
#define IDS_FILEDIRTY                       2
#define IDS_DEFEXT                          3
#define IDS_DOTEXT                          4
#define IDS_FILEOPENFILTER                  5
#define IDS_FILESAVEFILTER                  6
#define IDS_FILEOPEN                        7
#define IDS_FILESAVEAS                      8
#define IDS_STANDARDFRAMEMAX                8
#define IDS_CUSTOMFRAMEMIN                  9


//Document window junk
#define IDS_STANDARDDOCMIN                  128
#define IDS_CLIPBOARDFORMAT                 128
#define IDS_DOCUMENTCAPTION                 129
#define IDS_VERSIONMISMATCH                 130
#define IDS_FILELOADERROR                   131
#define IDS_FILESAVEERROR                   132
#define IDS_FILEDOESNOTEXIST                133
#define IDS_FILEOPENERROR                   134
#define IDS_UNKNOWNERROR                    135
#define IDS_STANDARDDOCMAX                  135
#define IDS_CUSTOMDOCMIN                    136




//These are specifically for the StatStrip
#define IDS_STANDARDSTATMESSAGEMIN          1024

#define IDS_EMPTYMESSAGE                    1024
#define IDS_READYMESSAGE                    1025

#define IDS_MENUMESSAGESYSTEM               1026
#define IDS_SYSMESSAGESIZE                  1027
#define IDS_SYSMESSAGEMOVE                  1028
#define IDS_SYSMESSAGEMINIMIZE              1029
#define IDS_SYSMESSAGEMAXIMIZE              1030
#define IDS_SYSMESSAGENEXTWINDOW            1031
#define IDS_SYSMESSAGEPREVWINDOW            1032
#define IDS_SYSMESSAGECLOSE                 1033
#define IDS_SYSMESSAGERESTORE               1034
#define IDS_SYSMESSAGETASKLIST              1035

#define IDS_MENUMESSAGEFILE                 1036
#define IDS_ITEMMESSAGEFILENEW              1037
#define IDS_ITEMMESSAGEFILEOPEN             1038
#define IDS_ITEMMESSAGEFILECLOSE            1039
#define IDS_ITEMMESSAGEFILESAVE             1040
#define IDS_ITEMMESSAGEFILESAVEAS           1041
#define IDS_ITEMMESSAGEFILEEXIT             1042

#define IDS_MENUMESSAGEEDIT                 1043
#define IDS_ITEMMESSAGEEDITUNDO             1044
#define IDS_ITEMMESSAGEEDITCUT              1045
#define IDS_ITEMMESSAGEEDITCOPY             1046
#define IDS_ITEMMESSAGEEDITPASTE            1047

#define IDS_MENUMESSAGEWINDOW               1048
#define IDS_ITEMMESSAGEWINDOWCASCADE        1049
#define IDS_ITEMMESSAGEWINDOWTILEHORZ       1050
#define IDS_ITEMMESSAGEWINDOWTILEVERT       1051
#define IDS_ITEMMESSAGEWINDOWICONS          1052

#define IDS_MENUMESSAGEHELP                 1053
#define IDS_ITEMMESSAGEHELPABOUT            1054

#define IDS_STANDARDSTATMESSAGEMAX          1054
#define IDS_CUSTOMSTATMESSAGEMIN            1055


#define CCHMESSAGEMAX                       128


#endif //_CLASSRES_H_
