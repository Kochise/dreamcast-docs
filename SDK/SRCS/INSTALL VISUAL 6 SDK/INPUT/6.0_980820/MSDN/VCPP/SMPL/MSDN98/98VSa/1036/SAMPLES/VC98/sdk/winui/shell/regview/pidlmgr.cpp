/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          PidlMgr.cpp
   
   Description:   Implements CPidlMgr.

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "PidlMgr.h"
#include "ShlFldr.h"
#include "resource.h"

/**************************************************************************

   CPidlMgr::CPidlMgr

**************************************************************************/

CPidlMgr::CPidlMgr()
{
//get the shell's IMalloc pointer
//we'll keep this until we get destroyed
if(FAILED(SHGetMalloc(&m_pMalloc)))
   {
   delete this;
   }

g_DllRefCount++;
}

/**************************************************************************

   CPidlMgr::~CPidlMgr

**************************************************************************/

CPidlMgr::~CPidlMgr()
{
if(m_pMalloc)
   m_pMalloc->Release();

g_DllRefCount--;
}

/**************************************************************************

   CPidlMgr::Create(DWORD, LPVOID, DWORD)

   Creates a new PIDL
   
**************************************************************************/

LPITEMIDLIST CPidlMgr::Create(PIDLTYPE type, LPVOID pIn, USHORT uInSize)
{
LPITEMIDLIST   pidlOut;
USHORT         uSize;

pidlOut = NULL;

/*
Calculate the size. This consists of the ITEMIDLIST, the PIDL structure plus 
the size of the data. We subtract the size of an HKEY because that is included 
in uInSize.
*/
uSize = sizeof(ITEMIDLIST) + (sizeof(PIDLDATA) - sizeof(HKEY)) + uInSize;

/*
Allocate the memory, adding an additional ITEMIDLIST for the NULL terminating 
ID List.
*/
pidlOut = (LPITEMIDLIST)m_pMalloc->Alloc(uSize + sizeof(ITEMIDLIST));

if(pidlOut)
   {
   LPITEMIDLIST   pidlTemp = pidlOut;
   LPPIDLDATA     pData;

   //set the size of this item
   pidlTemp->mkid.cb = uSize;

   //set the data for this item
   pData = GetDataPointer(pidlTemp);
   pData->type = type;
   switch(type)
      {
      case PT_ROOTKEY:
         pData->hRootKey = *(HKEY*)pIn;
         break;

      case PT_SUBKEY:
      case PT_VALUE:
         CopyMemory(pData->szText, pIn, uInSize);
         break;
      }
   
   //set the NULL terminator to 0
   pidlTemp = GetNextItem(pidlTemp);
   pidlTemp->mkid.cb = 0;
   pidlTemp->mkid.abID[0] = 0;
   }

return pidlOut;
}

/**************************************************************************

   CPidlMgr::Delete(HKEY)

   Deletes a PIDL
   
**************************************************************************/

void CPidlMgr::Delete(LPITEMIDLIST pidl)
{
m_pMalloc->Free(pidl);
}

/**************************************************************************

   CPidlMgr::CreateRootKey()

   Creates a root key PIDL
   
**************************************************************************/

LPITEMIDLIST CPidlMgr::CreateRootKey(HKEY hKeyRoot)
{
return Create(PT_ROOTKEY, (LPVOID)&hKeyRoot, sizeof(hKeyRoot));
}

/**************************************************************************

   CPidlMgr::CreateSubKey()

   Creates a sub key PIDL
   
**************************************************************************/

LPITEMIDLIST CPidlMgr::CreateSubKey(LPCTSTR lpszNew)
{
return Create(PT_SUBKEY, (LPVOID)lpszNew, (lstrlen(lpszNew) + 1) * sizeof(TCHAR));
}

/**************************************************************************

   CPidlMgr::CreateValue()

   Creates a value PIDL
   
**************************************************************************/

LPITEMIDLIST CPidlMgr::CreateValue(LPCTSTR lpszNew)
{
return Create(PT_VALUE, (LPVOID)lpszNew, (lstrlen(lpszNew) + 1) * sizeof(TCHAR));
}

/**************************************************************************

   CPidlMgr::GetNextItem()
   
**************************************************************************/

LPITEMIDLIST CPidlMgr::GetNextItem(LPCITEMIDLIST pidl)
{
if(pidl)
   return (LPITEMIDLIST)(LPBYTE)(((LPBYTE)pidl) + pidl->mkid.cb);
else
   return (NULL);
}

/**************************************************************************

   CPidlMgr::GetSize()
   
**************************************************************************/

UINT CPidlMgr::GetSize(LPCITEMIDLIST pidl)
{
UINT cbTotal = 0;
LPITEMIDLIST pidlTemp = (LPITEMIDLIST) pidl;

if(pidlTemp)
   {
   while(pidlTemp->mkid.cb)
      {
      cbTotal += pidlTemp->mkid.cb;
      pidlTemp = GetNextItem(pidlTemp);
      }  

   //add the size of the NULL terminating ITEMIDLIST
   cbTotal += sizeof(ITEMIDLIST);
   }

return (cbTotal);
}

/**************************************************************************

   CPidlMgr::GetData(PIDLTYPE, LPCITEMIDLIST, LPVOID, USHORT)
   
**************************************************************************/

DWORD CPidlMgr::GetData(PIDLTYPE type, LPCITEMIDLIST pidl, LPVOID pOut, USHORT uOutSize)
{
if(!pidl)
   return 0;

LPPIDLDATA  pData = GetDataPointer(pidl);
DWORD       dwReturn = 0;

//copy the data
switch(type)
   {
   case PT_ROOTKEY:
      if(uOutSize < sizeof(HKEY))
         return 0;
      
      if(PT_ROOTKEY != pData->type)
         return 0;
      
      *(HKEY*)pOut = pData->hRootKey;
      dwReturn = sizeof(pData->hRootKey);
      break;

   case PT_SUBKEY:
   case PT_VALUE:
   case PT_TEXT:
      *(LPTSTR)pOut = 0;
      lstrcpyn((LPTSTR)pOut, pData->szText, uOutSize);
      dwReturn = lstrlen((LPTSTR)pOut);
      break;
   }

return dwReturn;
}

/**************************************************************************

   CPidlMgr::GetRootKey()
   
**************************************************************************/

BOOL CPidlMgr::GetRootKey(LPCITEMIDLIST pidl, HKEY *phKeyRoot)
{
return (BOOL)GetData(PT_ROOTKEY, pidl, (LPVOID)phKeyRoot, sizeof(HKEY));
}

/**************************************************************************

   CPidlMgr::GetLastItem()

   Gets the last item in the list
   
**************************************************************************/

LPITEMIDLIST CPidlMgr::GetLastItem(LPCITEMIDLIST pidl)
{
LPITEMIDLIST   pidlLast = NULL;

//get the PIDL of the last item in the list
if(pidl)
   {
   while(pidl->mkid.cb)
      {
      pidlLast = (LPITEMIDLIST)pidl;
      pidl = GetNextItem(pidl);
      }  
   }

return pidlLast;
}

/**************************************************************************

   CPidlMgr::GetItemText()

   Gets the text for only this item
   
**************************************************************************/

DWORD CPidlMgr::GetItemText(LPCITEMIDLIST pidl, LPTSTR lpszText, USHORT uSize)
{
//if this is a root key, it needs to be handled specially
if(IsRootKey(pidl))
   {
   HKEY  hKey;

   if(!GetRootKey(pidl, &hKey))
      return 0;

   return GetRootKeyText(hKey, lpszText, uSize);
   }

return GetData(PT_TEXT, pidl, (LPVOID)lpszText, uSize);
}

/**************************************************************************

   CPidlMgr::GetSubKeyText()

   Creates a sub key string from a PIDL, filtering out the root key and 
   value, if either is present.
   
**************************************************************************/

DWORD CPidlMgr::GetSubKeyText(LPCITEMIDLIST pidl, LPTSTR lpszSubKey, DWORD dwSize)
{
if(!pidl)
   return 0;

LPITEMIDLIST   pidlTemp;
DWORD          dwCopied = 0;

/*
This may be a list of items, so if the first item is a key rather than a 
string, skip the first item because it contains the root key.
*/
if(IsRootKey(pidl))
   pidlTemp = GetNextItem(pidl);
else
   pidlTemp = (LPITEMIDLIST)pidl;

//if this is NULL, return the required size of the buffer
if(!lpszSubKey)
   {
   while(pidlTemp->mkid.cb)
      {
      LPPIDLDATA  pData = GetDataPointer(pidlTemp);
      
      //add the length of this item plus one for the backslash
      dwCopied += lstrlen(pData->szText) + 1;

      pidlTemp = GetNextItem(pidlTemp);
      }

   //add one for the NULL terminator
   return dwCopied + 1;
   }

*lpszSubKey = 0;

while(pidlTemp->mkid.cb && (dwCopied < dwSize))
   {
   LPPIDLDATA  pData = GetDataPointer(pidlTemp);

   //if this item is a value, then skip it and finish
   if(PT_VALUE == pData->type)
      break;
   
   lstrcat(lpszSubKey, pData->szText);
   lstrcat(lpszSubKey, TEXT("\\"));

   dwCopied += lstrlen(pData->szText) + 1;

   pidlTemp = GetNextItem(pidlTemp);
   }

//remove the last backslash if necessary
if(dwCopied)
   {
   if(*(lpszSubKey + lstrlen(lpszSubKey) - 1) == '\\')
      {
      *(lpszSubKey + lstrlen(lpszSubKey) - 1) = 0;
      dwCopied--;
      }
   }

return dwCopied;
}

/**************************************************************************

   CPidlMgr::GetValueText()

   Gets the text for the last item in the list
   
**************************************************************************/

DWORD CPidlMgr::GetValueText(LPCITEMIDLIST pidl, LPTSTR lpszValue, DWORD dwSize)
{
if(!pidl)
   return 0;

LPCITEMIDLIST  pidlTemp = pidl;
TCHAR          szText[MAX_PATH];

/*
This may be a list of items, so search through the list looking for an item 
that is a value. There should be only one, and it should be the last one, but 
we will assume it can be anywhere and only copy the first one.
*/
while(pidlTemp->mkid.cb && !IsValue(pidlTemp))
   {
   pidlTemp = GetNextItem(pidlTemp);
   }

//we didn't find a value pidl
if(!pidlTemp->mkid.cb)
   return 0;

//get the item's text
GetItemText(pidlTemp, szText, sizeof(szText));

//if this is NULL, return the required size of the buffer
if(!lpszValue)
   {
   return lstrlen(szText) + 1;
   }

lstrcpy(lpszValue, szText);

return lstrlen(lpszValue);
}

/**************************************************************************

   CPidlMgr::Copy()
   
**************************************************************************/

LPITEMIDLIST CPidlMgr::Copy(LPCITEMIDLIST pidlSource)
{
LPITEMIDLIST pidlTarget = NULL;
UINT cbSource = 0;

if(NULL == pidlSource)
   return (NULL);

// Allocate the new pidl
cbSource = GetSize(pidlSource);
pidlTarget = (LPITEMIDLIST)m_pMalloc->Alloc(cbSource);
if(!pidlTarget)
   return (NULL);

// Copy the source to the target
CopyMemory(pidlTarget, pidlSource, cbSource);

return pidlTarget;
}

/**************************************************************************

   CPidlMgr::IsRootKey()
   
**************************************************************************/

BOOL CPidlMgr::IsRootKey(LPCITEMIDLIST pidl)
{
LPPIDLDATA  pData = GetDataPointer(pidl);

return (PT_ROOTKEY == pData->type);
}

/**************************************************************************

   CPidlMgr::IsSubKey()
   
**************************************************************************/

BOOL CPidlMgr::IsSubKey(LPCITEMIDLIST pidl)
{
LPPIDLDATA  pData = GetDataPointer(pidl);

return (PT_SUBKEY == pData->type);
}

/**************************************************************************

   CPidlMgr::IsValue()
   
**************************************************************************/

BOOL CPidlMgr::IsValue(LPCITEMIDLIST pidl)
{
LPPIDLDATA  pData = GetDataPointer(pidl);

return (PT_VALUE == pData->type);
}

/**************************************************************************

   CPidlMgr::HasSubKeys()
   
**************************************************************************/

BOOL CPidlMgr::HasSubKeys(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCITEMIDLIST pidl)
{
HKEY     hKey;
LONG     lResult = !ERROR_SUCCESS;
FILETIME ft;
LPTSTR   lpszTemp;

if(!pszSubKey)
   pszSubKey = TEXT("");

if(!hKeyRoot)
   GetRootKey(pidl, &hKeyRoot);

DWORD dwSize = GetSubKeyText(pidl, NULL, 0) + lstrlen(pszSubKey) + 2;

lpszTemp = new TCHAR[dwSize];
if(!lpszTemp)
   return FALSE;

lstrcpy(lpszTemp, pszSubKey);
if(*lpszTemp)
   lstrcat(lpszTemp, TEXT("\\"));
GetSubKeyText(pidl, lpszTemp + lstrlen(lpszTemp), dwSize - lstrlen(lpszTemp));

//open the specified key
lResult = RegOpenKeyEx( hKeyRoot,
                        lpszTemp,
                        0,
                        KEY_ENUMERATE_SUB_KEYS,
                        &hKey);

if(ERROR_SUCCESS == lResult)
   {
   TCHAR szTemp[MAX_PATH];
   DWORD dwSize = sizeof(szTemp);

   //try to get the specified subkey
   lResult = RegEnumKeyEx( hKey,
                           0,
                           szTemp,
                           &dwSize,
                           NULL,
                           NULL,
                           NULL,
                           &ft);

   RegCloseKey(hKey);
   }

delete lpszTemp;

return (BOOL)(ERROR_SUCCESS == lResult);
}

/**************************************************************************

   CPidlMgr::GetDataPointer()
   
**************************************************************************/

LPPIDLDATA CPidlMgr::GetDataPointer(LPCITEMIDLIST pidl)
{
if(!pidl)
   return NULL;

return (LPPIDLDATA)(pidl->mkid.abID);
}

/**************************************************************************

   CPidlMgr::GetValueType()
   
**************************************************************************/

BOOL CPidlMgr::GetValueType(  LPCITEMIDLIST pidlFQ, 
                              LPDWORD pdwType)
{
BOOL  bReturn;
LPITEMIDLIST   pidlKey;
LPITEMIDLIST   pidlValue;

if(!SeparateKeyAndValue(pidlFQ, &pidlKey, &pidlValue))
   return 0;

bReturn = GetValueType(pidlKey, pidlValue, pdwType);

Delete(pidlKey);
Delete(pidlValue);

return bReturn;
}

/**************************************************************************

   CPidlMgr::GetValueType()
   
**************************************************************************/

BOOL CPidlMgr::GetValueType(  LPCITEMIDLIST pidlKey, 
                              LPCITEMIDLIST pidlValue, 
                              LPDWORD pdwType)
{
if(!pidlKey)
   return FALSE;

if(!pidlValue)
   return FALSE;

if(!pdwType)
   return FALSE;

HKEY     hKey,
         hRootKey;
LPTSTR   lpszSubKey,
         lpszValueName;
DWORD    dwNameSize;
LONG     lResult;

//get the root key
GetRootKey(pidlKey, &hRootKey);

//assemble the key string
dwNameSize = GetSubKeyText(pidlKey, NULL, 0);
lpszSubKey = new TCHAR[dwNameSize];
if(!lpszSubKey)
   return FALSE;
GetSubKeyText(pidlKey, lpszSubKey, dwNameSize);

//assemble the value name
dwNameSize = GetValueText(pidlValue, NULL, 0);
lpszValueName = new TCHAR[dwNameSize];
if(!lpszValueName)
   {
   delete lpszSubKey;
   return FALSE;
   }
GetValueText(pidlValue, lpszValueName, dwNameSize);

//open the key
lResult = RegOpenKeyEx( hRootKey,
                        lpszSubKey,
                        0,
                        KEY_QUERY_VALUE,
                        &hKey);

if(ERROR_SUCCESS != lResult)
   return FALSE;

//get the value type
lResult = RegQueryValueEx( hKey,
                           lpszValueName,
                           NULL,
                           pdwType,
                           NULL,
                           NULL);

RegCloseKey(hKey);

delete lpszSubKey;

delete lpszValueName;

return TRUE;
}

/**************************************************************************

   CPidlMgr::GetDataText()
   
**************************************************************************/

DWORD CPidlMgr::GetDataText(  LPCITEMIDLIST pidlFQ, 
                              LPTSTR lpszOut, 
                              DWORD dwOutSize)
{
DWORD dwReturn;
LPITEMIDLIST   pidlKey;
LPITEMIDLIST   pidlValue;

if(!SeparateKeyAndValue(pidlFQ, &pidlKey, &pidlValue))
   return 0;

dwReturn = GetDataText(pidlKey, pidlValue, lpszOut, dwOutSize);

Delete(pidlKey);
Delete(pidlValue);

return dwReturn;
}

/**************************************************************************

   CPidlMgr::GetDataText()
   
**************************************************************************/

DWORD CPidlMgr::GetDataText(  LPCITEMIDLIST pidlKey, 
                              LPCITEMIDLIST pidlValue, 
                              LPTSTR lpszOut, 
                              DWORD dwOutSize)
{
HKEY     hKey,
         hRootKey;
LPTSTR   lpszSubKey,
         lpszValueName;
DWORD    dwNameSize,
         dwType,
         dwSize,
         dwReturn = 0;
LONG     lResult;
TCHAR    szData[MAX_PATH];

if(!lpszOut)
   return dwReturn;

if(!pidlKey)
   return dwReturn;

if(!pidlValue)
   return dwReturn;

//get the root key
GetRootKey(pidlKey, &hRootKey);

//assemble the key string
dwNameSize = GetSubKeyText(pidlKey, NULL, 0);
lpszSubKey = new TCHAR[dwNameSize];
if(!lpszSubKey)
   return dwReturn;
GetSubKeyText(pidlKey, lpszSubKey, dwNameSize);

//assemble the value name
dwNameSize = GetValueText(pidlValue, NULL, 0);
lpszValueName = new TCHAR[dwNameSize];
if(!lpszValueName)
   {
   delete lpszSubKey;
   return dwReturn;
   }
GetValueText(pidlValue, lpszValueName, dwNameSize);

//open the key
lResult = RegOpenKeyEx( hRootKey,
                        lpszSubKey,
                        0,
                        KEY_QUERY_VALUE,
                        &hKey);

if(ERROR_SUCCESS != lResult)
   return 0;

//get the value
dwSize = sizeof(szData);
lResult = RegQueryValueEx( hKey,
                           lpszValueName,
                           NULL,
                           &dwType,
                           (LPBYTE)szData,
                           &dwSize);

/*
If this fails, then there is no default value set, so go ahead and add the 
empty default value.
*/
if(ERROR_SUCCESS == lResult)
   {
   //format the data
   switch(dwType)
      {
      case REG_BINARY:
      case REG_DWORD:
      case REG_DWORD_BIG_ENDIAN:
         {
         LPTSTR   lpszBuffer,
                  lpszTemp;
         LPBYTE   pData = (LPBYTE)szData;
                  
         lpszBuffer = lpszTemp = new TCHAR[dwSize * sizeof(TCHAR) * 3 + sizeof(TCHAR)];

         if(lpszTemp)
            {
            DWORD dwTemp;

            for(dwTemp = 0; dwTemp < dwSize; dwTemp++)
               {
               wsprintf(lpszTemp, TEXT("%02x"), *(pData + dwTemp));
               lstrcat(lpszTemp, TEXT(" "));
               lpszTemp = lpszBuffer + lstrlen(lpszBuffer);
               }

            lstrcpyn(lpszOut, lpszBuffer, dwOutSize);
            
            delete lpszBuffer;
            }
         }
         break;

      default:
         lstrcpyn(lpszOut, szData, dwOutSize);
         break;
      }
   dwReturn = lstrlen(lpszOut);
   }

RegCloseKey(hKey);

delete lpszSubKey;

delete lpszValueName;

return dwReturn;
}

/**************************************************************************

   CPidlMgr::GetPidlPath()

   Create a string that includes the root key name, the sub key text and 
   the value text.
   
**************************************************************************/

DWORD CPidlMgr::GetPidlPath(LPCITEMIDLIST pidl, LPTSTR lpszOut, DWORD dwOutSize)
{
LPTSTR   lpszTemp;

if(!lpszOut)
   return 0;

*lpszOut = 0;
lpszTemp = lpszOut;

//add the root key text if necessary
if(IsRootKey(pidl))
   {
   HKEY  hKey;

   GetRootKey(pidl, &hKey);
   dwOutSize -= GetRootKeyText(hKey, lpszOut, dwOutSize);

   lpszTemp = lpszOut + lstrlen(lpszOut);
   }

//add a backslash if necessary
if(*lpszOut && (*(lpszOut + lstrlen(lpszOut) - 1) != '\\'))
   lstrcat(lpszOut, TEXT("\\"));

//add the subkey string
dwOutSize -= GetSubKeyText(pidl, lpszTemp, dwOutSize);

//add a backslash if necessary
if(*lpszOut && (*(lpszOut + lstrlen(lpszOut) - 1) != '\\'))
   lstrcat(lpszOut, TEXT("\\"));

lpszTemp = lpszOut + lstrlen(lpszOut);

//add the value string
GetValueText(pidl, lpszTemp, dwOutSize);

//remove the last backslash if necessary
if(*(lpszOut + lstrlen(lpszOut) - 1) == '\\')
   {
   *(lpszOut + lstrlen(lpszOut) - 1) = 0;
   }

return lstrlen(lpszOut);
}

/**************************************************************************

   CPidlMgr::Concatenate()

   Create a new PIDL by combining two existing PIDLs.
   
**************************************************************************/

LPITEMIDLIST CPidlMgr::Concatenate(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
{
LPITEMIDLIST   pidlNew;
UINT           cb1 = 0, 
               cb2 = 0;

//are both of these NULL?
if(!pidl1 && !pidl2)
   return NULL;

//if pidl1 is NULL, just return a copy of pidl2
if(!pidl1)
   {
   pidlNew = Copy(pidl2);

   return pidlNew;
   }

//if pidl2 is NULL, just return a copy of pidl1
if(!pidl2)
   {
   pidlNew = Copy(pidl1);

   return pidlNew;
   }

cb1 = GetSize(pidl1) - sizeof(ITEMIDLIST);

cb2 = GetSize(pidl2);

//create the new PIDL
pidlNew = (LPITEMIDLIST)m_pMalloc->Alloc(cb1 + cb2);

if(pidlNew)
   {
   //copy the first PIDL
   CopyMemory(pidlNew, pidl1, cb1);
   
  //copy the second PIDL
   CopyMemory(((LPBYTE)pidlNew) + cb1, pidl2, cb2);
   }

return pidlNew;
}

/**************************************************************************

   CPidlMgr::SeparateKeyAndValue()

   Creates a separate key and value PIDL from a fully qualified PIDL.
   
**************************************************************************/

BOOL CPidlMgr::SeparateKeyAndValue( LPCITEMIDLIST pidlFQ, 
                                    LPITEMIDLIST *ppidlKey, 
                                    LPITEMIDLIST*ppidlValue)
{
if(!pidlFQ)
   return FALSE;

*ppidlValue = GetLastItem(pidlFQ);
if(!IsValue(*ppidlValue))
   return FALSE;

//make a copy of the value pidl
*ppidlValue = Copy(*ppidlValue);

//make a copy of the fully qualified PIDL
*ppidlKey = Copy(pidlFQ);

//truncate the last item of the key PIDL
LPITEMIDLIST   pidlTemp = GetLastItem(*ppidlKey);
pidlTemp->mkid.cb = 0;
pidlTemp->mkid.abID[0] = 0;

return TRUE;
}

