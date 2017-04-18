/*
 * RESOURCE.H
 * Document Objects Framer
 *
 * Definitions specifically pertaining to resources for the application.
 *
 * Copyright (c)1995-1997 Microsoft Corporation, All Rights Reserved
 */


#ifndef _RESOURCE_H_
#define _RESOURCE_H_

//Number of menus.
#define CMENUS                              2

//Resource identifiers.
#define IDR_MENU                            1
#define IDR_MENUHELP                        2
#define IDR_ACCELERATORS                    1
#define IDD_ABOUT                           1

//Number of items on IDR_MENUHELP
#define CHELPITEMS                          1

//Menu command identifiers.
#define IDM_FILEOPEN                        101
#define IDM_FILECLOSE                       102
#define IDM_FILEEXIT                        105

#define IDM_HELPABOUT                       200
#define IDM_CUSTOMHELPMIN                   201


//Enters context help in in-place mode
#define IDM_ENTERCONTEXTHELP                300
#define IDM_ESCAPECONTEXTHELP               301

#define CACCELERATORS                       2

#endif //_RESOURCE_H_
