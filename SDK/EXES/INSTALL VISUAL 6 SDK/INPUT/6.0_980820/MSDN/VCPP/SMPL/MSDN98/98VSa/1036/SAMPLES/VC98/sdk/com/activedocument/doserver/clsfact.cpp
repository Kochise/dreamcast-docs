/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          ClsFact.cpp
   
   Description:   CClassFactory implementation

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "ClsFact.h"

/**************************************************************************
   global variables
**************************************************************************/

extern DWORD   g_DllRefCount;

/**************************************************************************

   CClassFactory::CClassFactory

**************************************************************************/

CClassFactory::CClassFactory()
{
OutputDebugString(TEXT("CClassFactory's constructor\n"));

m_ObjRefCount = 0;
}

/**************************************************************************

   CClassFactory::~CClassFactory

**************************************************************************/

CClassFactory::~CClassFactory()
{
OutputDebugString(TEXT("CClassFactory's destructor\n"));
}

/**************************************************************************

   CClassFactory::QueryInterface

**************************************************************************/

STDMETHODIMP CClassFactory::QueryInterface(  REFIID riid, 
                                             LPVOID *ppReturn)
{
OutputDebugString(TEXT("CClassFactory::QueryInterface\n"));

if(IsEqualIID(riid, IID_IUnknown))
   {
   *ppReturn = (LPUNKNOWN)(LPCLASSFACTORY)this;
   m_ObjRefCount++;
   return ResultFromScode(S_OK);
   }
   
if(IsEqualIID(riid, IID_IClassFactory))
   {
   *ppReturn = (LPCLASSFACTORY)this;
   m_ObjRefCount++;
   return ResultFromScode(S_OK);
   }   

*ppReturn = NULL;
return ResultFromScode(E_NOINTERFACE);
}                                             

/**************************************************************************

   CClassFactory::AddRef

**************************************************************************/

STDMETHODIMP_(DWORD) CClassFactory::AddRef()
{
OutputDebugString(TEXT("CClassFactory::AddRef\n"));

return ++m_ObjRefCount;
}


/**************************************************************************

   CClassFactory::Release

**************************************************************************/

STDMETHODIMP_(DWORD) CClassFactory::Release()
{
TCHAR szText[MAX_PATH];
wsprintf(szText, TEXT("CClassFactory::Release - ref count will be %d\n"), m_ObjRefCount - 1);
OutputDebugString(szText);

if(--m_ObjRefCount == 0)
   delete this;
   
return m_ObjRefCount;
}

/**************************************************************************

   CClassFactory::CreateInstance

**************************************************************************/

STDMETHODIMP CClassFactory::CreateInstance(  LPUNKNOWN pUnknown, 
                                             REFIID riid, 
                                             LPVOID *ppObject)
{
OutputDebugString(TEXT("CClassFactory::CreateInstance\n"));

*ppObject = NULL;

if(pUnknown != NULL)
   return ResultFromScode(CLASS_E_NOAGGREGATION);

COleDocument *pOleDoc = new COleDocument;
if(NULL == pOleDoc)
   return ResultFromScode(E_OUTOFMEMORY);
  
//get the QueryInterface return for our return value
HRESULT hr = pOleDoc->QueryInterface(riid, ppObject);

//return the result from QueryInterface
return hr;
}

/**************************************************************************

   CClassFactory::LockServer

**************************************************************************/

STDMETHODIMP CClassFactory::LockServer(BOOL fLock)
{
OutputDebugString(TEXT("CClassFactory::LockServer - "));

if(fLock)
   {
   OutputDebugString(TEXT("Lock\n"));
   g_DllRefCount++;
   }
else
   {
   OutputDebugString(TEXT("Unlock\n"));
   g_DllRefCount--;
   }

return S_OK;
}

