/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          PidlMgr.h
   
   Description:   CPidlMgr definitions.

**************************************************************************/

#ifndef PIDLMGR_H
#define PIDLMGR_H

#include <windows.h>
#include <shlobj.h>

/**************************************************************************
   data types
**************************************************************************/

typedef enum tagPIDLTYPE
   {
   PT_ROOTKEY = 0x00000000,
   PT_SUBKEY = 0x00000001,
   PT_VALUE = 0x00000002,
   PT_TEXT = PT_SUBKEY | PT_VALUE
   }PIDLTYPE;

typedef struct tagPIDLDATA
   {
   PIDLTYPE type;
   union{
      HKEY     hRootKey;
      TCHAR    szText[1];
      };
   }PIDLDATA, FAR *LPPIDLDATA;

/**************************************************************************
   global variables
**************************************************************************/

extern HINSTANCE  g_hInst;
extern UINT       g_DllRefCount;

/**************************************************************************

   CPidlMgr class definition

**************************************************************************/

class CPidlMgr
{
public:
   CPidlMgr();
   ~CPidlMgr();
   LPITEMIDLIST CreateRootKey(HKEY);
   LPITEMIDLIST CreateSubKey(LPCTSTR);
   LPITEMIDLIST CreateValue(LPCTSTR);
   void Delete(LPITEMIDLIST);
   LPITEMIDLIST GetNextItem(LPCITEMIDLIST);
   LPITEMIDLIST Copy(LPCITEMIDLIST);
   UINT GetSize(LPCITEMIDLIST);
   BOOL GetRootKey(LPCITEMIDLIST, HKEY*);
   LPITEMIDLIST GetLastItem(LPCITEMIDLIST);
   DWORD GetItemText(LPCITEMIDLIST, LPTSTR, USHORT);
   BOOL IsRootKey(LPCITEMIDLIST);
   BOOL IsSubKey(LPCITEMIDLIST);
   BOOL IsValue(LPCITEMIDLIST);
   BOOL HasSubKeys(HKEY, LPCTSTR, LPCITEMIDLIST);
   DWORD GetSubKeyText(LPCITEMIDLIST, LPTSTR, DWORD);
   DWORD GetValueText(LPCITEMIDLIST, LPTSTR, DWORD);
   
   BOOL GetValueType(LPCITEMIDLIST, LPDWORD);
   BOOL GetValueType(LPCITEMIDLIST, LPCITEMIDLIST, LPDWORD);
   
   DWORD GetDataText(LPCITEMIDLIST, LPTSTR, DWORD);
   DWORD GetDataText(LPCITEMIDLIST, LPCITEMIDLIST, LPTSTR, DWORD);
   
   DWORD GetPidlPath(LPCITEMIDLIST, LPTSTR, DWORD);
   LPITEMIDLIST Concatenate(LPCITEMIDLIST, LPCITEMIDLIST);
   
private:
   LPMALLOC m_pMalloc;

   LPITEMIDLIST Create(PIDLTYPE, LPVOID, USHORT);
   DWORD GetData(PIDLTYPE, LPCITEMIDLIST, LPVOID, USHORT);
   LPPIDLDATA GetDataPointer(LPCITEMIDLIST);
   BOOL SeparateKeyAndValue(LPCITEMIDLIST, LPITEMIDLIST*, LPITEMIDLIST*);
};

typedef CPidlMgr FAR *LPPIDLMGR;

#endif   //PIDLMGR_H
