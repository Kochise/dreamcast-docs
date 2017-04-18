/*
 * RESOURCE.H
 * Patron Chapter 22
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

//Position of the "Object" item on the Edit menu.
#define MENUPOS_OBJECT              8
#define MENUPOS_OBJECTONPOPUP       5

//Popup menu
#define IDR_RIGHTPOPUPMENU          2

//CHAPTER22MOD
//In-place accelerators
#define IDR_INPLACEACCELERATORS     2
#define CINPLACEACCELERATORS        11  //See patron.rc
//End CHAPTER22MOD

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

#define IDM_EDITPASTESPECIAL        (IDM_CUSTOMEDITMIN)
#define IDM_EDITDELETEOBJECT        (IDM_CUSTOMEDITMIN+1)
#define IDM_EDITINSERTOBJECT        (IDM_CUSTOMEDITMIN+2)
#define IDM_EDITOBJECT              (IDM_CUSTOMEDITMIN+3)
#define IDM_EDITCONVERT             (IDM_CUSTOMEDITMIN+4)
#define IDM_EDITLINKS               (IDM_CUSTOMEDITMIN+5)

#define IDM_PAGENEWPAGE             (IDM_CUSTOMMIN)
#define IDM_PAGEDELETEPAGE          (IDM_CUSTOMMIN+1)
#define IDM_PAGENEXTPAGE            (IDM_CUSTOMMIN+2)
#define IDM_PAGEPREVIOUSPAGE        (IDM_CUSTOMMIN+3)
#define IDM_PAGEFIRSTPAGE           (IDM_CUSTOMMIN+4)
#define IDM_PAGELASTPAGE            (IDM_CUSTOMMIN+5)
#define IDM_PAGESHOWOBJECTS         (IDM_CUSTOMMIN+6)


//This special item is for the dynamic verbs on the Edit/Object item.
#define IDM_VERBMIN                 (IDM_CUSTOMMIN+100)
#define IDM_VERBMAX                 (IDM_CUSTOMMIN+200)

//CHAPTER22MOD
#define IDM_OPENOBJECT              (IDM_CUSTOMMIN+201)
#define IDM_ENTERCONTEXTHELP        (IDM_CUSTOMMIN+202)
#define IDM_ESCAPECONTEXTHELP       (IDM_CUSTOMMIN+203)
//End CHAPTER22MOD

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
//CHAPTER22MOD
#define IDS_FILEMENU                (IDS_CUSTOMFRAMEMIN+0)
#define IDS_PAGEMENU                (IDS_CUSTOMFRAMEMIN+1)
#define IDS_WINDOWMENU              (IDS_CUSTOMFRAMEMIN+2)
#define IDS_IPFRAMECAPTION          (IDS_CUSTOMFRAMEMIN+3)
#define IDS_FRAMEMAX                (IDS_CUSTOMFRAMEMIN+4)
//End CHAPTER22MOD

#define IDS_DOCUMENTMIN             IDS_STANDARDDOCMIN
#define IDS_PRINTERROR              (IDS_CUSTOMDOCMIN+0)
#define IDS_DOCUMENTNAME            (IDS_CUSTOMDOCMIN+1)
#define IDS_PASTEASPATRON           (IDS_CUSTOMDOCMIN+2)
#define IDS_PASTEMETAFILE           (IDS_CUSTOMDOCMIN+3)
#define IDS_PASTEASMETAFILE         (IDS_CUSTOMDOCMIN+4)
#define IDS_PASTEDIB                (IDS_CUSTOMDOCMIN+5)
#define IDS_PASTEASDIB              (IDS_CUSTOMDOCMIN+6)
#define IDS_PASTEBITMAP             (IDS_CUSTOMDOCMIN+7)
#define IDS_PASTEASBITMAP           (IDS_CUSTOMDOCMIN+8)
#define IDS_PASTEOBJECT             (IDS_CUSTOMDOCMIN+9)
#define IDS_PASTEASOBJECT           (IDS_CUSTOMDOCMIN+10)
#define IDS_PASTELINK               (IDS_CUSTOMDOCMIN+11)
#define IDS_PASTEASLINK             (IDS_CUSTOMDOCMIN+12)
#define IDS_EXTENSION               (IDS_CUSTOMDOCMIN+13)
//CHAPTER22MOD
#define IDS_UNTITLEDDOC             (IDS_CUSTOMDOCMIN+14)
#define IDS_IPDOCCAPTION            (IDS_CUSTOMDOCMIN+15)
#define IDS_DOCUMENTMAX             (IDS_CUSTOMDOCMIN+15)
//End CHAPTER22MOD


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
#define IDS_ITEMMESSAGEEDITPASTESPECIAL     (IDS_CUSTOMSTATMESSAGEMIN+9)
#define IDS_ITEMMESSAGEEDITDELETEOBJECT     (IDS_CUSTOMSTATMESSAGEMIN+10)
#define IDS_ITEMMESSAGEEDITINSERTOBJECT     (IDS_CUSTOMSTATMESSAGEMIN+11)
#define IDS_ITEMMESSAGEEDITOBJECT           (IDS_CUSTOMSTATMESSAGEMIN+12)
#define IDS_ITEMMESSAGEEDITCONVERT          (IDS_CUSTOMSTATMESSAGEMIN+13)
#define IDS_ITEMMESSAGEEDITLINKS            (IDS_CUSTOMSTATMESSAGEMIN+14)
#define IDS_ITEMMESSAGEPAGESHOWOBJECTS      (IDS_CUSTOMSTATMESSAGEMIN+15)
#define IDS_STATMESSAGEMAX                  (IDS_CUSTOMSTATMESSAGEMIN+15)


//Definitions for the printing dialog.

#define IDD_PRINTING                2

#define ID_CURRENTPAGE              101
#define ID_CURRENTCOPY              102
#define ID_COPYSTRING               103
#define ID_PAGESTRING               104

#define PRINTM_PAGEUPDATE           (WM_USER+100)
#define PRINTM_COPYUPDATE           (WM_USER+101)

#endif //_RESOURCE_H_
