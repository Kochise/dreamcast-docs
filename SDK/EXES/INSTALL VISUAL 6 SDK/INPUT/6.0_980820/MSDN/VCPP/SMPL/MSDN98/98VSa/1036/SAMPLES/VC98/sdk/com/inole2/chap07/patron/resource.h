/*
 * RESOURCE.H
 * Patron Chapter 7
 *
 * Definitions specifically pertaining to resources.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _RESOURCE_H_
#define _RESOURCE_H_

//Note that we augment classlib.h which we include before this.


//Position of Window menu.
#undef  WINDOW_MENU
#define WINDOW_MENU                 3


//Total number of menus
#undef  CMENUS
#ifdef MDI
#define CMENUS                      5
#else
#define CMENUS                      4
#endif


//Menu command identifiers.

#define IDM_FILEPRINT               (IDM_CUSTOMFILEMIN)
#define IDM_FILEPRINTERSETUP        (IDM_CUSTOMFILEMIN+1)

#define IDM_PAGENEWPAGE             (IDM_CUSTOMMIN)
#define IDM_PAGEDELETEPAGE          (IDM_CUSTOMMIN+1)
#define IDM_PAGENEXTPAGE            (IDM_CUSTOMMIN+2)
#define IDM_PAGEPREVIOUSPAGE        (IDM_CUSTOMMIN+3)
#define IDM_PAGEFIRSTPAGE           (IDM_CUSTOMMIN+4)
#define IDM_PAGELASTPAGE            (IDM_CUSTOMMIN+5)



/*
 * IDs for StatStrip handling of popup menus:  must be in order of menu
 * CLASSRES.H already defines ID_MENUFILE and ID_MENUEDIT for us.
 */

#undef ID_MENUWINDOW
#undef ID_MENUHELP

#define ID_MENUPAGE                 (ID_MENUCUSTOMMIN+0)
#define ID_MENUWINDOW               (ID_MENUCUSTOMMIN+1)
#define ID_MENUHELP                 (ID_MENUCUSTOMMIN+2)


//Stringtable IDs.  Keep sequential for each group.
#define IDS_FRAMEMIN                IDS_STANDARDFRAMEMIN
#define IDS_FRAMEMAX                IDS_STANDARDFRAMEMAX

#define IDS_DOCUMENTMIN             IDS_STANDARDDOCMIN
#define IDS_PRINTERROR              (IDS_CUSTOMDOCMIN+0)
#define IDS_DOCUMENTNAME            (IDS_CUSTOMDOCMIN+1)
#define IDS_DOCUMENTMAX             (IDS_CUSTOMDOCMIN+1)


//These are specifically for the StatStrip
#define IDS_STATMESSAGEMIN                  IDS_STANDARDSTATMESSAGEMIN

#define IDS_ITEMMESSAGEFILEPRINT            (IDS_CUSTOMSTATMESSAGEMIN+0)
#define IDS_ITEMMESSAGEFILEPRINTERSETUP     (IDS_CUSTOMSTATMESSAGEMIN+1)

#define IDS_MENUMESSAGEPAGE                 (IDS_CUSTOMSTATMESSAGEMIN+2)
#define IDS_ITEMMESSAGEPAGENEWPAGE          (IDS_CUSTOMSTATMESSAGEMIN+3)
#define IDS_ITEMMESSAGEPAGEDELETEPAGE       (IDS_CUSTOMSTATMESSAGEMIN+4)
#define IDS_ITEMMESSAGEPAGENEXTPAGE         (IDS_CUSTOMSTATMESSAGEMIN+5)
#define IDS_ITEMMESSAGEPAGEPREVIOUSPAGE     (IDS_CUSTOMSTATMESSAGEMIN+6)
#define IDS_ITEMMESSAGEPAGEFIRSTPAGE        (IDS_CUSTOMSTATMESSAGEMIN+7)
#define IDS_ITEMMESSAGEPAGELASTPAGE         (IDS_CUSTOMSTATMESSAGEMIN+8)

#define IDS_STATMESSAGEMAX                  (IDS_CUSTOMSTATMESSAGEMIN+8)



//Definitions for the printing dialog.

#define IDD_PRINTING                2

#define ID_CURRENTPAGE              101
#define ID_CURRENTCOPY              102
#define ID_COPYSTRING               103
#define ID_PAGESTRING               104

#define PRINTM_PAGEUPDATE           (WM_USER+100)
#define PRINTM_COPYUPDATE           (WM_USER+101)

#endif //_RESOURCE_H_
