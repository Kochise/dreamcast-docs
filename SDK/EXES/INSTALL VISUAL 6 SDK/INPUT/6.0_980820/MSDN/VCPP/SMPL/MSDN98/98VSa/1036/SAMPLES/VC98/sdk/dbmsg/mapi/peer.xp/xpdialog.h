/*
 -  X P T L O G O N . H
 -
 *  Purpose:
 *      Definitions, typedefs and prototypes used by the Sample Transport
 *      Provider logon UI.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

/* Size of largest possible text edit in our logon dialog. */

#define MAX_TEXTFIELD   255

/* Structure passed into the logon dialog code from TransportLogon
   and propagated in/out through LPARAM at WM_INITDIALOG time. */

typedef struct _XPDLG
{
    HINSTANCE           hInst;          /* Instance of my DLL           */
    HWND                hwnd;           /* Handle of my parent window   */
    LPSPropValue        *lppPropArray;  /* Property array pointer       */
    LPSPropTagArray     lpPTArray;      /* List of property tags        */
    LPALLOCATEBUFFER    AllocateBuffer; /* MAPIAllocateBuffer function  */
    LPALLOCATEMORE      AllocateMore;   /* MAPIAllocateMore function    */
    LPFREEBUFFER        FreeBuffer;     /* MAPIFreeBuffer function      */
    LPMALLOC            lpMalloc;       /* IMalloc object               */
    LPMAPISUP           lpMAPISup;      /* Transport support object     */
    BOOL                fLogon;         /* Called at Logon time         */
    ULONG               ulFlags;        /* 0 or UI_READONLY             */
} XPDLG, * LPXPDLG;

/* Create a logon dialog. Return an error if unable to do so. Any
   other result from the dialog is communicated through XPDLG. */

SCODE ScDoLogonDlg (LPXPDLG lpXPDialog);
