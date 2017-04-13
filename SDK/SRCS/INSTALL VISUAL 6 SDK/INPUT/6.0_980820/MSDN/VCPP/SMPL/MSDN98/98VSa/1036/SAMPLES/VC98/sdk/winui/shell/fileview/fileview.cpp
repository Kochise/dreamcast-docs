//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright  1994-1996  Microsoft Corporation.  All Rights Reserved.
//
//    PROGRAM: FILEVIEW.CPP    
//
//    PURPOSE:   File Viewer Component Object to work with Windows 95 Explorer.
// This file contains functions not specific to the nature of
// the data to view but contains the non-file-specific DLL
// and component object structure.  This can be used for a
// custom viewer by making modifications marked with //MODIFY
// comments.
//
//    PLATFORMS:    Windows 95
//
//    SPECIAL INSTRUCTIONS: N/A
//

//Define INITGUIDS once in entire module build
#define INITGUIDS
#include "fileview.h"

#include <initguid.h>
#include <shlguid.h>
#include "fvtext.h"     //FileViewer specifics

//Count number of objects and number of locks.
ULONG       g_cObj=0;
ULONG       g_cLock=0;

//Save this from LibMain
HINSTANCE   g_hInst;


//
//   FUNCTION:     LibMain
//
//   PURPOSE:   Entry point for a Win32 DLL
//
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG ulReason
    , PVOID pvReserved)
    {
    if (DLL_PROCESS_DETACH==ulReason)
        {
        return TRUE;
        }
    else
        {
        if (DLL_PROCESS_ATTACH!=ulReason)
            return TRUE;
        }

    g_hInst=hInstance;
    return TRUE;
    }
//
//   FUNCTION:     DllGetClassObject
//
//   PURPOSE:  Provides an IClassFactory for a given CLSID that this DLL is
//  registered to support.  This DLL is placed under the CLSID
//  in the registration database as the InProcServer.  
//
//   PARAMETERS: 
//       clsID           REFCLSID that identifies the class factory
//                  desired.  Since this parameter is passed this
//                  DLL can handle any number of objects simply
//                 by returning different class factories here
//                  for different CLSIDs.
//
//  riid            REFIID specifying the interface the caller wants
//                  on the class object, usually IID_ClassFactory.
//
//  ppv             PPVOID in which to return the interface pointer.
//
//   RETURN VALUE:
//        HRESULT         NOERROR on success, otherwise an error code.
//
HRESULT PASCAL DllGetClassObject(REFCLSID rclsid, REFIID riid
    , PPVOID ppv)
    {
    // Warning:: The shell may not have initialized OLE so
    // do it here to be sure...
    OleInitialize(NULL);

    //MODIFY:  Change CLSID_FileViewerText to your own CLSID
    if (!IsEqualCLSID(rclsid, CLSID_FileViewerText))
        return ResultFromScode(E_FAIL);

    //Check that we can provide the interface
    if (!IsEqualIID(riid, IID_IUnknown)
        && !IsEqualIID(riid, IID_IClassFactory))
        return ResultFromScode(E_NOINTERFACE);

    //Return our IClassFactory for our viewer objects
    *ppv=(LPVOID)new CFVClassFactory();

    if (NULL==*ppv)
        return ResultFromScode(E_OUTOFMEMORY);

    //AddRef the object through any interface we return
    ((LPUNKNOWN)*ppv)->AddRef();

    return NOERROR;
    }
//
//   FUNCTION: DllCanUnloadNow    
//
//   PURPOSE:  Answers if the DLL can be freed, that is, if there are no
//    references to anything this DLL provides.  
//
//   RETURN VALUE:
//       BOOL            TRUE if nothing is using us, FALSE otherwise.
//
STDAPI DllCanUnloadNow(void)
    {
    SCODE   sc;

    //Our answer is whether there are any object or locks
    sc=(0L==g_cObj && 0L==g_cLock) ? S_OK : S_FALSE;
    return ResultFromScode(sc);
    }
//
//   FUNCTION:     ObjectDestroyed
//
//   PURPOSE:  Function for the FileViewer object to call when it gets
//  destroyed. Since we're in a DLL we only track the number of
//  objects here, letting DllCanUnloadNow take care of the rest. 
//
void PASCAL ObjectDestroyed(void)
    {
    g_cObj--;
    return;
    }
//
//   FUNCTION: CFVClassFactory::CFVClassFactory    
//
//   PURPOSE:  Constructor
//
CFVClassFactory::CFVClassFactory(void)
    {
    m_cRef=0L;
    return;
    }

//
//   FUNCTION: CFVClassFactory::~CFVClassFactory    
//
//   PURPOSE:   Destructor
//
CFVClassFactory::~CFVClassFactory(void)
    {
    return;
    }

//
//   FUNCTION:     CFVClassFactory::QueryInterface
//
STDMETHODIMP CFVClassFactory::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    *ppv=NULL;

    //Any interface on this object is the object pointer.
    if (IsEqualIID(riid, IID_IUnknown)
        || IsEqualIID(riid, IID_IClassFactory))
        *ppv=(LPVOID)this;

     // If we actually assign an interface to ppv we need to AddRef
     // it since we're returning a new pointer.
    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }
//
//   FUNCTION:     CFVClassFactory::AddRef
//
STDMETHODIMP_(ULONG) CFVClassFactory::AddRef(void)
    {
    return ++m_cRef;
    }

//
//   FUNCTION:     CFVClassFactory::Release
//
STDMETHODIMP_(ULONG) CFVClassFactory::Release(void)
    {
    ULONG           cRefT;

    cRefT=--m_cRef;

    if (0L==m_cRef)
        delete this;

    return cRefT;
    }

//
//   FUNCTION:     CFVClassFactory::CreateInstance
//
//   PURPOSE:    Instantiates a CFileViewer object that will provide the
//  IPersistFile and IFileViewer interfaces for use with the Windows 95 Explorer.
//
//   PARAMETERS: 
//  pUnkOuter       LPUNKNOWN to the controlling IUnknown if we are being used in an aggregation.
//  riid            REFIID identifying the interface the caller desires to have for the new object.
//  ppvObj          PPVOID in which to store the desired interface pointer for the new object.
//
//   RETURN VALUE:
//   HRESULT         NOERROR if successful, otherwise E_NOINTERFACE
//                  if we cannot support the requested interface.
//
STDMETHODIMP CFVClassFactory::CreateInstance(LPUNKNOWN pUnkOuter
    , REFIID riid, PPVOID ppvObj)
    {
    PCFileViewer        pObj;
    HRESULT             hr;

    *ppvObj=NULL;
    hr=ResultFromScode(E_OUTOFMEMORY);

    //Verify that a controlling unknown asks for IUnknown
    if (NULL!=pUnkOuter && !IsEqualIID(riid, IID_IUnknown))
        return ResultFromScode(E_NOINTERFACE);

     // MODIFY:  If you use a different object than CFileViewer
    // be sure to change the name and parameters here.  I do
    // recommend that you continue to follow this model, however,
    // and just modify CFileViewer as necessary.
    //Create the object passing function to notify on destruction.
    pObj=new CFileViewer(pUnkOuter, g_hInst, ObjectDestroyed);

    if (NULL==pObj)
        return hr;

    //MODIFY:  Add other parameters to Init as necessary.
    hr=pObj->Init();

    if (SUCCEEDED(hr))
        {
        //Return the requested interface
        hr=pObj->QueryInterface(riid, ppvObj);

        if (SUCCEEDED(hr))
            {
            //Everything worked:  count the object
            g_cObj++;
            return NOERROR;
            }
        }

    //Kill the object if anything failed after creation.
    delete pObj;

    return hr;
    }
//
//   FUNCTION: CFVClassFactory::LockServer    
//
//   PURPOSE:  Increments or decrements the lock count of the DLL.  If the
//  lock count goes to zero and there are no objects, the DLL
//  is allowed to unload.  See DllCanUnloadNow.
//
//   PARAMETERS: 
//    fLock           BOOL specifying whether to increment or decrement the lock count.
//
//   RETURN VALUE:
//     HRESULT         NOERROR always
//
STDMETHODIMP CFVClassFactory::LockServer(BOOL fLock)
    {
    if (fLock)
        g_cLock++;
    else
        g_cLock--;

    return NOERROR;
    }
