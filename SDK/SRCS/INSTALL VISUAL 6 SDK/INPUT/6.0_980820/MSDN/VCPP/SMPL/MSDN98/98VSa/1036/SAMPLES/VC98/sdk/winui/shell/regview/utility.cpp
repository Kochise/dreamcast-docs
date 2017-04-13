/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          Utility.cpp
   
   Description:   

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "Utility.h"
#include "ShlFldr.h"
#include "resource.h"

/**************************************************************************
   private function prototypes
**************************************************************************/

/**************************************************************************
   global variables
**************************************************************************/

extern HIMAGELIST g_himlLarge;
extern HIMAGELIST g_himlSmall;

#define MAIN_KEY_STRING       (TEXT("Software\\RegView"))
#define VALUE_STRING          (TEXT("Display Settings"))
#define INITIAL_COLUMN_SIZE   100

/**************************************************************************

   GetKeyName()
   
**************************************************************************/

DWORD GetKeyName( HKEY hKeyRoot, 
                  LPCTSTR pszSubKey, 
                  DWORD dwIndex, 
                  LPTSTR pszOut, 
                  DWORD dwSize)
{
HKEY     hKey;
LONG     lResult;
FILETIME ft;

if(!pszOut)
   return 0;

if(!pszSubKey)
   pszSubKey = TEXT("");

//open the specified key
lResult = RegOpenKeyEx( hKeyRoot,
                        pszSubKey,
                        0,
                        KEY_ENUMERATE_SUB_KEYS,
                        &hKey);

if(ERROR_SUCCESS != lResult)
   return 0;

//try to get the specified subkey
lResult = RegEnumKeyEx( hKey,
                        dwIndex,
                        pszOut,
                        &dwSize,
                        NULL,
                        NULL,
                        NULL,
                        &ft);

RegCloseKey(hKey);

if(ERROR_SUCCESS == lResult)
   return dwSize;

return 0;
}

/**************************************************************************

   GetValueName()
   
**************************************************************************/

BOOL GetValueName(   HKEY hKeyRoot, 
                     LPCTSTR pszSubKey, 
                     DWORD dwIndex, 
                     LPTSTR pszOut, 
                     DWORD dwSize)
{
HKEY     hKey;
LONG     lResult;
DWORD    dwType;

if(!pszOut)
   return 0;

if(!pszSubKey)
   pszSubKey = TEXT("");

//open the specified key
lResult = RegOpenKeyEx( hKeyRoot,
                        pszSubKey,
                        0,
                        KEY_QUERY_VALUE,
                        &hKey);

if(ERROR_SUCCESS != lResult)
   return 0;

//try to get the specified subkey
lResult = RegEnumValue( hKey,
                        dwIndex,
                        pszOut,
                        &dwSize,
                        NULL,
                        &dwType,
                        NULL,
                        NULL);

RegCloseKey(hKey);

return BOOL(ERROR_SUCCESS == lResult);

if(ERROR_SUCCESS == lResult)
   return dwSize;

return 0;
}


/**************************************************************************

   GetRootKeyText()
   
**************************************************************************/

DWORD GetRootKeyText(HKEY hKeyRoot, LPTSTR lpszOut, DWORD dwOutSize)
{
*lpszOut = 0;

if(hKeyRoot == HKEY_CLASSES_ROOT)
   {
   lstrcpyn(lpszOut, TEXT("HKEY_CLASSES_ROOT"), dwOutSize);
   }

else if(hKeyRoot == HKEY_CURRENT_USER)
   {
   lstrcpyn(lpszOut, TEXT("HKEY_CURRENT_USER"), dwOutSize);
   }

else if(hKeyRoot == HKEY_LOCAL_MACHINE)
   {
   lstrcpyn(lpszOut, TEXT("HKEY_LOCAL_MACHINE"), dwOutSize);
   }

else if(hKeyRoot == HKEY_USERS)
   {
   lstrcpyn(lpszOut, TEXT("HKEY_USERS"), dwOutSize);
   }

else if(hKeyRoot == HKEY_PERFORMANCE_DATA)
   {
   lstrcpyn(lpszOut, TEXT("HKEY_PERFORMANCE_DATA"), dwOutSize);
   }

else if(hKeyRoot == HKEY_CURRENT_CONFIG)
   {
   lstrcpyn(lpszOut, TEXT("HKEY_CURRENT_CONFIG"), dwOutSize);
   }

else if(hKeyRoot == HKEY_DYN_DATA)
   {
   lstrcpyn(lpszOut, TEXT("HKEY_DYN_DATA"), dwOutSize);
   }
   
return lstrlen(lpszOut) + 1;
}

/**************************************************************************

   RootKeyExists()
   
**************************************************************************/

BOOL RootKeyExists(HKEY hKeyRoot)
{
LONG  lResult;
HKEY  hKey;

//open the specified key
lResult = RegOpenKeyEx( hKeyRoot,
                        NULL,
                        0,
                        KEY_ENUMERATE_SUB_KEYS,
                        &hKey);

if(ERROR_SUCCESS != lResult)
   return FALSE;

RegCloseKey(hKey);

return TRUE;
}

/**************************************************************************

   SaveGlobalSettings()
   
**************************************************************************/

BOOL SaveGlobalSettings(void)
{
HKEY  hKey;
LONG  lResult;
DWORD dwDisp;

lResult = RegCreateKeyEx(  HKEY_CURRENT_USER,
                           MAIN_KEY_STRING,
                           0,
                           NULL,
                           REG_OPTION_NON_VOLATILE, 
                           KEY_ALL_ACCESS,
                           NULL, 
                           &hKey,
                           &dwDisp);

if(lResult != ERROR_SUCCESS)
   return FALSE;

//create an array to put our data in
DWORD dwArray[4];
dwArray[0] = g_nColumn1;
dwArray[1] = g_nColumn2;
dwArray[2] = g_bViewKeys;
dwArray[3] = g_bShowIDW;

//save the last printer selected
lResult = RegSetValueEx(   hKey,
                           VALUE_STRING,
                           0,
                           REG_BINARY,
                           (LPBYTE)dwArray,
                           sizeof(dwArray));

RegCloseKey(hKey);

if(lResult != ERROR_SUCCESS)
   return FALSE;

return TRUE;
}

/**************************************************************************

   GetGlobalSettings()
   
**************************************************************************/

BOOL GetGlobalSettings(void)
{
HKEY  hKey;
LONG  lResult;

//set up the default data
g_nColumn1 = INITIAL_COLUMN_SIZE;
g_nColumn2 = INITIAL_COLUMN_SIZE;
g_bViewKeys = TRUE;
g_bShowIDW = FALSE;

lResult = RegOpenKeyEx( HKEY_CURRENT_USER,
                        MAIN_KEY_STRING,
                        0,
                        KEY_ALL_ACCESS,
                        &hKey);

if(lResult != ERROR_SUCCESS)
   return FALSE;

//create an array to put our data in
DWORD dwArray[4];
DWORD dwType;
DWORD dwSize = sizeof(dwArray);

//save the last printer selected
lResult = RegQueryValueEx( hKey,
                           VALUE_STRING,
                           NULL,
                           &dwType,
                           (LPBYTE)dwArray,
                           &dwSize);

RegCloseKey(hKey);

if(lResult != ERROR_SUCCESS)
   return FALSE;

g_nColumn1 = dwArray[0];
g_nColumn2 = dwArray[1];
g_bViewKeys = dwArray[2];
g_bShowIDW = dwArray[3];

return TRUE;
}

/**************************************************************************

   CompareItems()
   
**************************************************************************/

int CALLBACK CompareItems(LPARAM lParam1, LPARAM lParam2, LPARAM lpData)
{
CShellFolder  *pFolder = (CShellFolder*)lpData;

if(!pFolder)
   return 0;

return (int)pFolder->CompareIDs(0, (LPITEMIDLIST)lParam1, (LPITEMIDLIST)lParam2);
}

/**************************************************************************

   CreateImageLists()
   
**************************************************************************/

VOID CreateImageLists(VOID)
{
int   cx;
int   cy;

cx = GetSystemMetrics(SM_CXSMICON);
cy = GetSystemMetrics(SM_CYSMICON);

cx = 16;
cy = 16;

if(g_himlSmall)
   ImageList_Destroy(g_himlSmall);

//set the small image list
g_himlSmall = ImageList_Create(cx, cy, ILC_COLORDDB | ILC_MASK, 4, 0);

if(g_himlSmall)
   {
   HICON hIcon;
   
   hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_BINARY), IMAGE_ICON, cx, cy, LR_DEFAULTCOLOR);
   ImageList_AddIcon(g_himlSmall, hIcon);

   hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_STRING), IMAGE_ICON, cx, cy, LR_DEFAULTCOLOR);
   ImageList_AddIcon(g_himlSmall, hIcon);

   hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_FOLDER), IMAGE_ICON, cx, cy, LR_DEFAULTCOLOR);
   ImageList_AddIcon(g_himlSmall, hIcon);

   hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_FOLDEROPEN), IMAGE_ICON, cx, cy, LR_DEFAULTCOLOR);
   ImageList_AddIcon(g_himlSmall, hIcon);
   }

if(g_himlLarge)
   ImageList_Destroy(g_himlLarge);

cx = GetSystemMetrics(SM_CXICON);
cy = GetSystemMetrics(SM_CYICON);

cx = 32;
cy = 32;

//set the large image list
g_himlLarge = ImageList_Create(cx, cy, ILC_COLORDDB | ILC_MASK, 4, 0);

if(g_himlSmall)
   {
   HICON hIcon;
   
   hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_BINARY), IMAGE_ICON, cx, cy, LR_DEFAULTCOLOR);
   ImageList_AddIcon(g_himlLarge, hIcon);

   hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_STRING), IMAGE_ICON, cx, cy, LR_DEFAULTCOLOR);
   ImageList_AddIcon(g_himlLarge, hIcon);

   hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_FOLDER), IMAGE_ICON, cx, cy, LR_DEFAULTCOLOR);
   ImageList_AddIcon(g_himlLarge, hIcon);

   hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_FOLDEROPEN), IMAGE_ICON, cx, cy, LR_DEFAULTCOLOR);
   ImageList_AddIcon(g_himlLarge, hIcon);
   }

}

/**************************************************************************

   DestroyImageLists()
   
**************************************************************************/

VOID DestroyImageLists(VOID)
{
if(g_himlSmall)
   ImageList_Destroy(g_himlSmall);

if(g_himlLarge)
   ImageList_Destroy(g_himlLarge);
}

/**************************************************************************

   WideCharToLocal()
   
**************************************************************************/

int WideCharToLocal(LPTSTR pLocal, LPWSTR pWide, DWORD dwChars)
{
*pLocal = 0;

#ifdef UNICODE
lstrcpyn(pLocal, pWide, dwChars);
#else
WideCharToMultiByte( CP_ACP, 
                     0, 
                     pWide, 
                     -1, 
                     pLocal, 
							dwChars, 
                     NULL, 
                     NULL);
#endif

return lstrlen(pLocal);
}

/**************************************************************************

   LocalToWideChar()
   
**************************************************************************/

int LocalToWideChar(LPWSTR pWide, LPTSTR pLocal, DWORD dwChars)
{
*pWide = 0;

#ifdef UNICODE
lstrcpyn(pWide, pLocal, dwChars);
#else
MultiByteToWideChar( CP_ACP, 
                     0, 
                     pLocal, 
                     -1, 
                     pWide, 
                     dwChars); 
#endif

return lstrlenW(pWide);
}

