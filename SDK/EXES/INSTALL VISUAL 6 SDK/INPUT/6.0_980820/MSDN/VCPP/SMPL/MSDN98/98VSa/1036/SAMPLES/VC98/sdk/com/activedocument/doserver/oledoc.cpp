/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          OleDoc.cpp
   
   Description:   COleDocument implementation.

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "OleDoc.h"
#include "comcat.h"

/**************************************************************************
   global variables
**************************************************************************/

extern DWORD   g_DllRefCount;

/**************************************************************************

   COleDocument::COleDocument()

**************************************************************************/

COleDocument::COleDocument()
{
OutputDebugString(TEXT("COleDocument's constructor\n"));

m_ObjRefCount = 0;

m_fDirty = FALSE;
m_fNoScribbleMode = FALSE;
m_pOleAdviseHolder = NULL;
m_pOleClientSite = NULL;
m_dwRegister = 0;
m_pOleDocView = NULL;
m_Color = DEFAULT_COLOR;
m_fCreated = FALSE;

m_pOleObject = new COleObject(this);

m_pDataObject = new CDataObject(this);

m_pOleInPlaceObject = new COleInPlaceObject(this);

m_pOleInPlaceActiveObject = new COleInPlaceActiveObject(this);

m_pPersistStorage = new CPersistStorage(this);

m_pPersistFile = new CPersistFile(this, m_pPersistStorage);

m_pOleDocView = new COleDocumentView(this);

g_DllRefCount++;
}

/**************************************************************************

   COleDocument::~COleDocument()

**************************************************************************/

COleDocument::~COleDocument()
{
OutputDebugString(TEXT("COleDocument's destructor\n"));

if(m_pOleAdviseHolder)
   m_pOleAdviseHolder->Release();

if(m_pOleClientSite)
   m_pOleClientSite->Release();

delete m_pOleDocView;

delete m_pPersistFile;

delete m_pPersistStorage;

delete m_pOleInPlaceActiveObject;

delete m_pOleInPlaceObject;

delete m_pDataObject;

delete m_pOleObject;

g_DllRefCount--;

PostQuitMessage(0);
}

///////////////////////////////////////////////////////////////////////////
//
// IUnknown Implementation
//

/**************************************************************************

   COleDocument::QueryInterface

**************************************************************************/

STDMETHODIMP COleDocument::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
OutputDebugString(TEXT("COleDocument::QueryInterface - "));

HRESULT  hr = E_NOINTERFACE;
*ppReturn = NULL;

if(riid == IID_IUnknown)
   {
   *ppReturn = this;
   OutputDebugString(TEXT("IUnknown requested - "));
   }
else if (riid == IID_IOleDocument)
   {
   *ppReturn = this;
   OutputDebugString(TEXT("IOleDocument requested - "));
   }
else if (riid == IID_IOleDocumentView)
   {
   *ppReturn = m_pOleDocView;
   OutputDebugString(TEXT("IOleDocumentView requested - "));
   }
else if (riid == IID_IOleObject)
   {
   *ppReturn = m_pOleObject;
   OutputDebugString(TEXT("IOleObject requested - "));
   }
else if (riid == IID_IDataObject)
   {
   *ppReturn = m_pDataObject;
   OutputDebugString(TEXT("IDataObject requested - "));
   }
else if (riid == IID_IOleInPlaceObject)
   {
   *ppReturn = m_pOleInPlaceObject;
   OutputDebugString(TEXT("IOleInPlaceObject requested - "));
   }
else if (riid == IID_IOleInPlaceActiveObject)
   {
   *ppReturn = m_pOleInPlaceActiveObject;
   OutputDebugString(TEXT("IOleInPlaceActiveObject requested - "));
   }
else if((riid == IID_IPersistStorage) || (riid == IID_IPersist))
   {
   *ppReturn = m_pPersistStorage;
   OutputDebugString(TEXT("IPersistStorage requested - "));
   }
else if(riid == IID_IPersistFile)
   {
   *ppReturn = m_pPersistFile;
   OutputDebugString(TEXT("IPersistFile requested - "));
   }

if (*ppReturn)
   {
   OutputDebugString(TEXT("Interface Found\n"));
   ((LPUNKNOWN)*ppReturn)->AddRef();
   hr = S_OK;
   }
else
   {
   OutputDebugString(TEXT("No Interface - "));

   LPWSTR   pwsz;
   TCHAR    szString[MAX_PATH] = TEXT("");
   
   StringFromIID(riid, &pwsz);

   if(pwsz)
      {
#ifdef UNICODE
      lstrcpy(szString, pwsz);
#else
      WideCharToMultiByte( CP_ACP,
                           0,
                           pwsz,
                           -1,
                           szString,
                           ARRAYSIZE(szString),
                           NULL,
                           NULL);
#endif
      OutputDebugString(szString);
      OutputDebugString(TEXT("\n"));

      //free the string
      LPMALLOC pMalloc;
      CoGetMalloc(1, &pMalloc);
      pMalloc->Free(pwsz);
      pMalloc->Release();
      }
   }

return hr;
}                                             

/**************************************************************************

   COleDocument::AddRef

**************************************************************************/

STDMETHODIMP_(DWORD) COleDocument::AddRef()
{
//OutputDebugString("COleDocument::AddRef\n");
TCHAR szText[MAX_PATH];
wsprintf(szText, TEXT("COleDocument::AddRef - ref count will be %d\n"), m_ObjRefCount + 1);
OutputDebugString(szText);

return ++m_ObjRefCount;
}


/**************************************************************************

   COleDocument::Release

**************************************************************************/

STDMETHODIMP_(DWORD) COleDocument::Release()
{
//OutputDebugString("COleDocument::Release\n");
TCHAR szText[MAX_PATH];
wsprintf(szText, TEXT("COleDocument::Release - ref count will be %d\n"), m_ObjRefCount - 1);
OutputDebugString(szText);

if(0 == --m_ObjRefCount)
   {
   delete this;
   return 0;
   }
   
return m_ObjRefCount;
}

/**************************************************************************

   COleDocument::CreateView()
   
**************************************************************************/

STDMETHODIMP COleDocument::CreateView( IOleInPlaceSite *pInPlaceSite, 
                                       IStream *pStream, 
                                       DWORD dwReserved, 
                                       IOleDocumentView **ppOleDocumentView)
{
OutputDebugString(TEXT("COleDocument::CreateView\n"));

HRESULT  hr = E_FAIL;

//NULL the view pointer
*ppOleDocumentView = NULL;

//we only support one view, so fail if the view already exists
if(!m_fCreated)
   {
   //AddRef since we are giving away the pointer
   m_pOleDocView->AddRef();

   // if we were given a site, set this as the site for the view we just created
   if(pInPlaceSite) 
      {
      m_pOleDocView->SetInPlaceSite(pInPlaceSite);
      }

   // if given a stream to initialize from, initialize our view state
   if(pStream) 
      {
      m_pOleDocView->ApplyViewState(pStream);
      }

   *ppOleDocumentView = m_pOleDocView;

   m_fCreated = TRUE;
   
   hr = S_OK;
   }
   
return hr;
}

/**************************************************************************

   COleDocument::GetDocMiscStatus()
   
**************************************************************************/

STDMETHODIMP COleDocument::GetDocMiscStatus(DWORD *pdwStatus)
{
OutputDebugString(TEXT("COleDocument::GetDocMiscStatus\n"));

if(!pdwStatus)
   return E_INVALIDARG;

*pdwStatus = 0;

return S_OK;
}

/**************************************************************************

   COleDocument::EnumViews()
   
**************************************************************************/

STDMETHODIMP COleDocument::EnumViews(  IEnumOleDocumentViews **ppEnum, 
                                       IOleDocumentView **ppView)
{
OutputDebugString(TEXT("COleDocument::EnumViews\n"));

*ppEnum = NULL;
*ppView = NULL;

return E_NOTIMPL;
}

/**************************************************************************

   COleDocument::GetWindow()
   
**************************************************************************/

STDMETHODIMP COleDocument::GetWindow(HWND *phwnd)
{
OutputDebugString(TEXT("COleDocument::GetWindow\n"));

if(!phwnd)
   return E_INVALIDARG;

*phwnd = NULL;

if(m_pOleDocView)
   *phwnd = m_pOleDocView->m_hwndView;

return S_OK;
}

/**************************************************************************

   COleDocument::UIDeactivate()
   
**************************************************************************/

STDMETHODIMP COleDocument::DeactivateUI()
{
OutputDebugString(TEXT("COleInPlaceObject::DeactivateUI\n"));

if(m_pOleDocView)
   return m_pOleDocView->DeactivateUI();

return E_FAIL;
}

/**************************************************************************

   COleDocumentView::DeactivateInPlace()
   
**************************************************************************/

STDMETHODIMP COleDocument::DeactivateInPlace()
{
OutputDebugString(TEXT("COleDocument::DeactivateInPlace\n"));

if(m_pOleDocView)
   return m_pOleDocView->DeactivateInPlace();

return E_FAIL;
}

/**************************************************************************

   COleDocument::RegisterServer

**************************************************************************/

typedef struct{
   HKEY  hRootKey;
   TCHAR szSubKey[MAX_PATH];
   TCHAR szValue[MAX_PATH];
}DOREGSTRUCT, *LPDOREGSTRUCT;

BOOL COleDocument::RegisterServer(void)
{
OutputDebugString("COleDocument::RegisterServer\n");

int      i;
HKEY     hKey;
LRESULT  lResult;
DWORD    dwDisp;
TCHAR    szSubKey[MAX_PATH];
TCHAR    szCLSID[MAX_PATH];
TCHAR    szApp[MAX_PATH];
LPWSTR   pwsz;
CLSID    clsid;

//get this app's CLSID in string form
m_pPersistStorage->GetClassID(&clsid);
StringFromIID(clsid, &pwsz);

if(pwsz)
   {
#ifdef UNICODE
   lstrcpy(szCLSID, pwsz);
#else
   WideCharToMultiByte( CP_ACP,
                        0,
                        pwsz,
                        -1,
                        szCLSID,
                        ARRAYSIZE(szCLSID),
                        NULL,
                        NULL);
#endif

   //free the string
   LPMALLOC pMalloc;
   CoGetMalloc(1, &pMalloc);
   pMalloc->Free(pwsz);
   pMalloc->Release();
   }

//get this app's path and file name
GetModuleFileName(NULL, szApp, ARRAYSIZE(szApp));

//register the file extension entries
{
DOREGSTRUCT FileEntries[] = { HKEY_CLASSES_ROOT,   TEXT("%s"),                         PROG_ID,
                              0,                   TEXT(""),                           TEXT("")};

for(i = 0; FileEntries[i].hRootKey; i++)
   {
   //create the sub key string - for this case, insert the file extension
   wsprintf(szSubKey, FileEntries[i].szSubKey, FILE_EXT);

   lResult = RegCreateKeyEx(  FileEntries[i].hRootKey,
                              szSubKey,
                              0,
                              NULL,
                              REG_OPTION_NON_VOLATILE,
                              KEY_WRITE,
                              NULL,
                              &hKey,
                              &dwDisp);
   
   if(NOERROR == lResult)
      {
      lResult = RegSetValueEx(   hKey,
                                 NULL,
                                 0,
                                 REG_SZ,
                                 (LPBYTE)FileEntries[i].szValue,
                                 lstrlen(FileEntries[i].szValue) + 1);
      
      RegCloseKey(hKey);
      }
   else
      return FALSE;
   }
}

{
DOREGSTRUCT ProgEntries[] = { HKEY_CLASSES_ROOT,   TEXT("%s"),                         DOC_NAME,
                              HKEY_CLASSES_ROOT,   TEXT("%s\\CLSID"),                  TEXT("%s"),
                              HKEY_CLASSES_ROOT,   TEXT("%s\\DocObject"),			   TEXT(""),
                              0,                   TEXT(""),                           TEXT("")};

//register the ProgID entries
for(i = 0; ProgEntries[i].hRootKey; i++)
   {
   //create the sub key string - for this case, insert the ProgID
   wsprintf(szSubKey, ProgEntries[i].szSubKey, PROG_ID);

   lResult = RegCreateKeyEx(  ProgEntries[i].hRootKey,
                              szSubKey,
                              0,
                              NULL,
                              REG_OPTION_NON_VOLATILE,
                              KEY_WRITE,
                              NULL,
                              &hKey,
                              &dwDisp);
   
   if(NOERROR == lResult)
      {
      TCHAR szValue[MAX_PATH];

      //if necessary, create the value string
      wsprintf(szValue, ProgEntries[i].szValue, szCLSID);
   
      lResult = RegSetValueEx(   hKey,
                                 NULL,
                                 0,
                                 REG_SZ,
                                 (LPBYTE)szValue,
                                 lstrlen(szValue) + 1);
      
      RegCloseKey(hKey);
      }
   else
      return FALSE;
   }
}

{
DOREGSTRUCT ClsidEntries[] = {HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s"),                  DOC_NAME,
                              HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\LocalServer32"),   TEXT("%s"),
                              HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\InprocHandler32"), TEXT("ole32.dll"),
                              HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\DefaultIcon"),     TEXT("%s,0"),
                              HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\DocObject"),	   TEXT("0"),
                              HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\ProgID"),		   PROG_ID,
                              0,                   TEXT(""),                           TEXT("")};

//register the CLSID entries
for(i = 0; ClsidEntries[i].hRootKey; i++)
   {
   //create the sub key string - for this case, insert the file extension
   wsprintf(szSubKey, ClsidEntries[i].szSubKey, szCLSID);

   lResult = RegCreateKeyEx(  ClsidEntries[i].hRootKey,
                              szSubKey,
                              0,
                              NULL,
                              REG_OPTION_NON_VOLATILE,
                              KEY_WRITE,
                              NULL,
                              &hKey,
                              &dwDisp);
   
   if(NOERROR == lResult)
      {
      TCHAR szValue[MAX_PATH];

      //if necessary, create the value string
      wsprintf(szValue, ClsidEntries[i].szValue, szApp);
   
      lResult = RegSetValueEx(   hKey,
                                 NULL,
                                 0,
                                 REG_SZ,
                                 (LPBYTE)szValue,
                                 lstrlen(szValue) + 1);
      
      RegCloseKey(hKey);
      }
   else
      return FALSE;
   }
}

//register the component as insertable and a document object
ICatRegister   *pcr;
HRESULT        hr = S_OK ;
    
CoInitialize(NULL);

hr = CoCreateInstance(  CLSID_StdComponentCategoriesMgr, 
                        NULL, 
                        CLSCTX_INPROC_SERVER, 
                        IID_ICatRegister, 
                        (LPVOID*)&pcr);

if(SUCCEEDED(hr))
   {
   CATID rgcatid[2];
   
   rgcatid[0] = CATID_Insertable;
   rgcatid[1] = CATID_DocObject;

   hr = pcr->RegisterClassImplCategories(clsid, 2, rgcatid);

   pcr->Release();
   }
        
CoUninitialize();

return SUCCEEDED(hr);
}

/**************************************************************************

   COleDocument::CreateFile(HWND)

**************************************************************************/

BOOL COleDocument::CreateFile(HWND hwndParent)
{
OutputDebugString("COleDocument::CreateFile(HWND)\n");

OPENFILENAME   ofn;
TCHAR          szFilter[MAX_PATH];
TCHAR          szFile[MAX_PATH] = TEXT("");
LPTSTR         pTemp;

//build the filter string
pTemp = szFilter;
lstrcpy(pTemp, DOC_NAME);
pTemp += lstrlen(pTemp) + 1;
lstrcpy(pTemp, TEXT("*"));
lstrcat(pTemp, FILE_EXT);
pTemp += lstrlen(pTemp) + 1;
*pTemp = 0;

ZeroMemory(&ofn, sizeof(ofn));
ofn.lStructSize         = sizeof(ofn);
ofn.hwndOwner           = hwndParent;
ofn.hInstance           = g_hInst;
ofn.lpstrFilter         = szFilter;
ofn.lpstrCustomFilter   = NULL;
ofn.nMaxCustFilter      = 0;
ofn.nFilterIndex        = 1;
ofn.lpstrFile           = szFile;
ofn.nMaxFile            = ARRAYSIZE(szFile);
ofn.lpstrFileTitle      = NULL;
ofn.nMaxFileTitle       = 0;
ofn.lpstrInitialDir     = NULL;
ofn.lpstrTitle          = NULL;
ofn.lpTemplateName      = MAKEINTRESOURCE(IDD_COLOR_DIALOG);
ofn.lpfnHook            = (LPOFNHOOKPROC)ColorHookProc;
ofn.lCustData           = (DWORD)this;
ofn.Flags               = OFN_EXPLORER |
                           OFN_OVERWRITEPROMPT |
                           OFN_HIDEREADONLY |
                           OFN_ENABLEHOOK | 
                           OFN_ENABLETEMPLATE |
                           0;

if(GetSaveFileName(&ofn))
   {
   //if the extension isn't attached, attach it
   pTemp = szFile + lstrlen(szFile) - 4;
   if(lstrcmpi(pTemp, FILE_EXT))
      {
      lstrcat(szFile, FILE_EXT);
      }

   return CreateFile(szFile);
   }

return FALSE;
}


/**************************************************************************

   COleDocument::CreateFile(LPTSTR)

**************************************************************************/

BOOL COleDocument::CreateFile(LPTSTR pszFile)
{
OutputDebugString("COleDocument::CreateFile(LPTSTR)\n");

WCHAR szwFile[MAX_PATH];

#ifdef UNICODE
lstrcpy(szwFile, pszFile);
#else
MultiByteToWideChar( CP_ACP, 
                     MB_PRECOMPOSED, 
                     pszFile, 
                     -1, 
                     szwFile,
                     ARRAYSIZE(szwFile));
#endif

m_pPersistFile->Save(szwFile, FALSE);

return TRUE;
}


