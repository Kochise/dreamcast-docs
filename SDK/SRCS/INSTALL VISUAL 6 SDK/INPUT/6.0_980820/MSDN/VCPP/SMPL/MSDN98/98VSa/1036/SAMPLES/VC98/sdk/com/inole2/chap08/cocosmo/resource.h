/*
 * RESOURCE.H
 * Component Cosmo Chapter 8
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
#define WINDOW_MENU             4


//Total number of menus
#undef  CMENUS
#define CMENUS                  5



//Menu command identifiers.

#define IDM_FILEIMPORT          (IDM_CUSTOMFILEMIN)

#define IDM_COLORBACKGROUND     (IDM_CUSTOMMIN)
#define IDM_COLORLINE           (IDM_CUSTOMMIN+1)

#define IDM_LINEMIN             (IDM_CUSTOMMIN+100)
#define IDM_LINESOLID           (IDM_LINEMIN+0)         //PS_SOLID       0
#define IDM_LINEDASH            (IDM_LINEMIN+1)         //PS_DASH        1
#define IDM_LINEDOT             (IDM_LINEMIN+2)         //PS_DOT         2
#define IDM_LINEDASHDOT         (IDM_LINEMIN+3)         //PS_DASHDOT     3
#define IDM_LINEDASHDOTDOT      (IDM_LINEMIN+4)         //PS_DASHDOTDOT  4
#define IDM_LINEMAX             IDM_LINEDASHDOTDOT


/*
 * IDs for StatStrip handling of popup menus:  must be in order of menu
 * CLASSRES.H already defines ID_MENUFILE and ID_MENUEDIT for us.
 */

#undef  ID_MENUWINDOW
#undef  ID_MENUHELP

#define ID_MENUCOLOR            (ID_MENUCUSTOMMIN+0)
#define ID_MENULINE             (ID_MENUCUSTOMMIN+1)
#define ID_MENUWINDOW           (ID_MENUCUSTOMMIN+2)
#define ID_MENUHELP             (ID_MENUCUSTOMMIN+3)


//Stringtable IDs.  Keep sequential for each group.
#define IDS_FRAMEMIN            IDS_STANDARDFRAMEMIN
#define IDS_FILEIMPORT          (IDS_CUSTOMFRAMEMIN+0)
#define IDS_FRAMEMAX            (IDS_CUSTOMFRAMEMIN+0)

#define IDS_DOCUMENTMIN         IDS_STANDARDDOCMIN
#define IDS_NOPOLYLINE          (IDS_CUSTOMDOCMIN+0)
#define IDS_DOCUMENTMAX         (IDS_CUSTOMDOCMIN+0)



//These are specifically for the StatStrip
#define IDS_STATMESSAGEMIN                  IDS_STANDARDSTATMESSAGEMIN

#define IDS_ITEMMESSAGEFILEIMPORT           (IDS_CUSTOMSTATMESSAGEMIN+0)

#define IDS_MENUMESSAGECOLOR                (IDS_CUSTOMSTATMESSAGEMIN+1)
#define IDS_ITEMMESSAGECOLORBACKGROUND      (IDS_CUSTOMSTATMESSAGEMIN+2)
#define IDS_ITEMMESSAGECOLORLINE            (IDS_CUSTOMSTATMESSAGEMIN+3)

#define IDS_MENUMESSAGELINE                 (IDS_CUSTOMSTATMESSAGEMIN+4)
#define IDS_ITEMMESSAGELINESOLID            (IDS_CUSTOMSTATMESSAGEMIN+5)
#define IDS_ITEMMESSAGELINEDASH             (IDS_CUSTOMSTATMESSAGEMIN+6)
#define IDS_ITEMMESSAGELINEDOT              (IDS_CUSTOMSTATMESSAGEMIN+7)
#define IDS_ITEMMESSAGELINEDASHDOT          (IDS_CUSTOMSTATMESSAGEMIN+8)
#define IDS_ITEMMESSAGELINEDASHDOTDOT       (IDS_CUSTOMSTATMESSAGEMIN+9)

#define IDS_STATMESSAGEMAX                  (IDS_CUSTOMSTATMESSAGEMIN+9)


#endif //_RESOURCE_H_
