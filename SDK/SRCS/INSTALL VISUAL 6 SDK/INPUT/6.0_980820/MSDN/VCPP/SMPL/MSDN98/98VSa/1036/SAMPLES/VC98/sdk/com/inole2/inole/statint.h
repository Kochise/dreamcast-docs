/*
 * STATINT.H
 *
 * Internal definitions and function prototypes for the StatStrip
 * control.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _STATINT_H_
#define _STATINT_H_

#ifdef __cplusplus
extern "C"
    {
#endif



//For loading the RCDATA mapping menu item IDs to string IDs
typedef struct tagSTATMESSAGEMAP
    {
    USHORT      uID;
    USHORT      idsMsg;
    } STATMESSAGEMAP, *PSTATMESSAGEMAP;

//Array mapping menu handles to menu item IDs
typedef struct tagPOPUPMENUMAP
    {
    HMENU       hMenu;
    USHORT      uID;
    } POPUPMENUMAP, * PPOPUPMENUMAP;




typedef struct tagSTATSTRIP
    {
    HFONT               hFont;      //Current control font
    BOOL                fMyFont;

    BOOL                fMapped;    //StatStripMessageMap called?
    HWND                hWndOwner;

    USHORT              cMessages;  //Total number of messages
    UINT                idsMin;     //Starting string ID
    UINT                idsMax;

    USHORT              uIDStatic;  //Quiescent message ID
    USHORT              uIDBlank;   //Blank message ID
    USHORT              uIDSysMenu; //System menu message ID

    HGLOBAL             hMemSMM;    //Handle to STATMESSAGEMAP data
    PSTATMESSAGEMAP     pSMM;       //Memory holding STATMESSAGEMAP

    HGLOBAL             hMemSzStat; //Memory for Stat strings
    LPTSTR *            ppsz;       //Stat string pointers

    USHORT              cPopups;
    USHORT              uIDPopupMin;
    USHORT              uIDPopupMax;
    PPOPUPMENUMAP       pPMM;
    } STATSTRIP, *PSTATSTRIP;


#define CBSTATSTRIP             sizeof(STATSTRIP)

#define CBEXTRASTATSTRIP        sizeof(PSTATSTRIP)
#define STATWL_STRUCTURE        0


//STASTRIP.C
LRESULT APIENTRY StatStripWndProc(HWND, UINT, WPARAM, LPARAM);
void             StatStripPaint(HWND, PSTATSTRIP);
USHORT           IDFromHMenu(PSTATSTRIP, HMENU);
UINT             IStringFromID(PSTATMESSAGEMAP, USHORT, USHORT);

void             StatStripClean(PSTATSTRIP, BOOL);
HGLOBAL          HStringCache(HINSTANCE, UINT, UINT, UINT, LPTSTR *);
void             HStringCacheFree(HGLOBAL);
void             StatMessageMapSort(PSTATMESSAGEMAP, USHORT);

#ifdef __cplusplus
    }
#endif


#endif //_STATINT_H_
