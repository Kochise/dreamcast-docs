/*
 * RESOURCE.H
 * Polyline Component Chapter 23
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


//Object stringtable IDs
#define IDS_POLYLINEMIN     0
#define IDS_STORAGEFORMAT   0
#define IDS_USERTYPE        1

#define IDS_CLOSECAPTION    2
#define IDS_CLOSEPROMPT     3
#define IDS_POLYLINEMAX     3

#define IDR_ICON            1

#define IDD_EDITDIALOG      1

#define ID_UNDO             100
#define ID_COLORBACK        101
#define ID_COLORLINE        102
#define ID_GROUPCOLORS      103
#define ID_GROUPPREVIEW     104
#define ID_GROUPSTYLES      105
#define ID_GROUPFIGURE      106
#define ID_POLYLINERECT     107
#define ID_POLYLINE         108

#define ID_LINEMIN          200
#define ID_LINESOLID        200     //(ID_LINEMIN+PS_SOLID)
#define ID_LINEDASH         201     //(ID_LINEMIN+PS_DASH)
#define ID_LINEDOT          202     //(ID_LINEMIN+PS_DOT)
#define ID_LINEDASHDOT      203     //(ID_LINEMIN+PS_DASHDOT)
#define ID_LINEDASHDOTDOT   204     //(ID_LINEMIN+PS_DASHDOTDOT)

//Message to close the dialog
#define POLYM_CLOSE         (WM_USER+1000)


#endif //_RESOURCE_H_
