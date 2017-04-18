
/*****************************************************************************
*
*  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
*  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
*  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR
*  A PARTICULAR PURPOSE.
*
*  Copyright (C) 1993 - 1997 Microsoft Corporation. All Rights Reserved.
*
*****************************************************************************/

/*+
 *  drawstr.h
 *
 *  structures & define & prototypes for the structure dumper
 *
 *
 *-==================================================================*/

#if !defined DRAWSTR_H
#define DRAWSTR_H

typedef struct _dsfield {
   LPTSTR psz;
   UINT   off;
   UINT   siz;
   UINT   fmt;
   UINT   aux;
   UINT   array;
   } DSFIELD, * PDSFIELD;

typedef struct _dsfieldtbl {
   PDSFIELD pFields;
   LPCTSTR  pszName;
   UINT     cbSize;
   } DSFIELDTBL, * PDSFIELDTBL;

typedef struct _dsbuff {
   LPTSTR  ptr;
   UINT    cch;
   } DSBUFF, *PDSBUFF;

typedef struct _dslineinfo {
   UINT   nMaxLine;
   UINT   nCurLine;
   UINT   nMaxDepth;
   UINT   nCurDepth;
   int    cyLine;
   struct _dsline {
      LPVOID lpv;
      UINT   uStruct;
      UINT   uField;
      WORD   uDepth;
      WORD   uMember;
      } aLine[10];
   } DSLINEINFO, * PDSLINEINFO;

typedef struct _viewinit {
   PDSFIELDTBL pTable;
   UINT        uStruct;
   UINT        uRepeat;
   LPVOID      lpData;
   } VIEWINIT, *PVIEWINIT;

// global preferences.
//
typedef struct _dspref {
    BOOL bShowAddresses;
    } DSPREF;
extern DSPREF dspref;

#if !defined FIELDOFF
#define FIELDSIZ(st,field)  (unsigned int) (sizeof(((st *)0)->field))
#define FIELDREFSIZ(st,field)  (unsigned int) (sizeof(*(((st *)0)->field)))
#define FIELDOFF(st,field)  (unsigned int) (&(((st *)0)->field))
#define FLD(st,field)  FIELDOFF(st,field), FIELDSIZ(st,field)
#define PFLD(st,field) FIELDOFF(st,field), FIELDREFSIZ(st,field)
#endif

#ifndef NUMELMS
#define NUMELMS(aa) (sizeof(aa)/sizeof((aa)[0]))
#endif

#define AS_NONE         0
#define AS_SZ           1
#define AS_ACH          2
#define AS_INT          3
#define AS_UINT         4
#define AS_HEX          5
#define AS_BITFIELD     6
#define AS_HANDLE       7
#define AS_HWND         8
#define AS_MODE         9
#define AS_ERROR        10
#define AS_XMODE        11

#define AS_RECT         16
#define AS_POINT        17
#define AS_POINTS       18
#define AS_SIZE         19
#define AS_FLOAT        20
#define AS_BYTES        21
#define AS_DUMP         22

#define AS_STRUCT      0x0100
#define IS_EDIT        0x0200
#define AS_REF         0x1000
#define AS_ARRAY       0x4000


VOID FAR PASCAL DrawDsLabels (
   HDC          hDC,
   PDSFIELDTBL  pTable,
   PDSLINEINFO  lpLineInfo,
   LPRECT       lpRect,
   POINT        ptOffset);

VOID FAR PASCAL DrawDsData (
   HDC          hDC,
   PDSFIELDTBL  pTable,     // info used to label and format fields in struct
   PDSLINEINFO  lpLineInfo, //
   LPRECT       lpRect,     // rectangle to clip drawing to
   POINT        ptOffset);  // scrolling offset for upper left corner

int FAR PASCAL GetDsLabelWidth (
   HDC          hDC,
   PDSFIELDTBL  pTable,      // info used to label and format fields in struct
   PDSLINEINFO  lpLineInfo); //

PDSLINEINFO WINAPI AllocDsLineInfo (
   UINT         nMax);

VOID FAR PASCAL BuildDsLineInfo (
   PDSFIELDTBL pTable,      //in:
   UINT        uStruct,     //in:
   LPVOID      lpData,      //in:
   WORD        nMember,     //in: index into lpData
   WORD        nLastMember, //in: index into lpData
   PDSLINEINFO pLineInfo);  //in,out:

BOOL WINAPI ExpandDsLineInfo (
   PDSFIELDTBL pTable,     // info used to label and format fields in struct
   UINT        nLine,      // line to expand (if possible)
   PDSLINEINFO pLineInfo);

BOOL WINAPI ContractDsLineInfo (
   PDSFIELDTBL pTable,     // info used to label and format fields in struct
   UINT        nLine,      // line to expand (if possible)
   PDSLINEINFO pLineInfo);

LRESULT WINAPI ViewWndProc (
   HWND    hWnd,           // handle of spy window
   UINT    wMsgID,         // id of current message
   WPARAM  wParam,         // word argument, depends on message id
   LPARAM  lParam);        // long argument, depends on message id

VOID WINAPI DrawDragEdge(
   HWND    hWnd, 
   LPPOINT lppt, 
   LPPOINT lpptLastEdge);

#define VM_GETDATA   (WM_USER + 100)
#define View_GetData(hWnd) (LPVOID)SendMessage(hWnd, VM_GETDATA, 0, 0)
#define VM_SETDATA   (WM_USER + 101)
#define View_SetData(hWnd,lpv) (LPVOID)SendMessage(hWnd, VM_SETDATA, 0, (LPARAM)lpv)

#define VM_INVALIDATE (WM_USER + 102)
#define View_InvalidateLine(hWnd,nLine) SendMessage(hWnd, VM_INVALIDATE, 0, (LPARAM)nLine)
#define View_InvalidateLines(hWnd,nLine,nCount) SendMessage(hWnd, VM_INVALIDATE, (WPARAM)nCount, (LPARAM)nLine)

#define VM_SETSEL    (WM_USER + 103)
#define View_SetSel(hWnd, nLine) SendMessage (hWnd, VM_SETSEL, 0, (LPARAM)nLine);

#define VM_EDITNEXT  (WM_USER + 104)
#define View_EditNext(hWnd,bPrev) SendMessage (hWnd, VM_EDITNEXT, (WPARAM)bPrev, 0);

// notifications
//
#define VN_CHANGE  (0U-800U)

#endif // drawstr_h
