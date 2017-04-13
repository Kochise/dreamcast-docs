/*+==========================================================================
  File:      FACTORY.CPP

  Summary:   Implementation file for the Class Factories of the LICSERVE
             server.  This server provides a licensed factory for the
             LicCruiseCar COM component. Thus this COM object factory
             implements IClassFactory2. In addition, a non-licensed
             CFLicCarSample class factory is included to provide a
             component with the Code Sample utility interface ISample.
             This interface is primarily for use within the code samples
             for the purposes of setting them up as samples (eg, setting
             up the server so that it trace logs to the client's trace log
             facility).  The COM Components that can be manufactured by
             this server are known outside the server by their respective
             CLSIDs: CLSID_LicCruiseCar and CLSID_LicCarSample.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial LICSERVE.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source code.

  Classes:   CFLicCruiseCar, CFLicCarSample.

  Functions: .

  Origin:    10-5-95: atrent - Editor-inheritance from FACTORY.CPP in
               the DLLSERVE Tutorial Code Sample.

----------------------------------------------------------------------------
  This file is part of the Microsoft COM Tutorial Code Samples.

  Copyright (C) Microsoft Corporation, 1997.  All rights reserved.

  This source code is intended only as a supplement to Microsoft
  Development Tools and/or on-line documentation.  See these other
  materials for detailed information regarding Microsoft code samples.

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
==========================================================================+*/

/*---------------------------------------------------------------------------
  We include WINDOWS.H for all Win32 applications.
  We include OLE2.H because we will be calling the COM/OLE Libraries
    in future exploitation of this DLL skeleton.
  We include OLECTL.H because we will be using IClassFactory2.
  We include APPUTIL.H because we will be building this DLL using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include ICARS.H and CARGUIDS.H for the common car-related Interface
    class, GUID, and CLSID specifications.
  We include SERVER.H because it has the necessary internal class and
    resource definitions for this DLL.
  We include FACTORY.H because it has the necessary internal class factory
    declarations for this DLL component server.  Those factories we will be
    implementing in this module.
  We include CRUCAR.H for the object class declarations for the
    COLicCruiseCar COM object.
  We include SAMPLE.H for the utility Sample class COLicCarSample.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <apputil.h>
#include <icars.h>
#include <carguids.h>
#include "server.h"
#include "factory.h"
#include "crucar.h"
#include "sample.h"


/*---------------------------------------------------------------------------
  Implementation the CFLicCruiseCar Class Factory.  CFLicCruiseCar is the
  COM object class for the Class Factory that can manufacture
  COLicCruiseCar COM Components.  As part of the LICSERVE code sample
  CFLicCruiseCar implements the IClassFactory2 interface to provide
  licensing services.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCruiseCar::CFLicCruiseCar

  Summary:  CFLicCruiseCar Constructor. Note the member initializer:
            "m_ImpIClassFactory(this, pUnkOuter, pServer)" which is used
            to pass the 'this', pUnkOuter, and pServer pointers of this
            constructor function to the constructor executed in the
            instantiation of the CImpIClassFactory interface whose
            implementation is nested inside this present object class.

  Args:     IUnknown* pUnkOuter,
              Pointer to the the outer Unknown.  NULL means this COM Object
              is not being Aggregated.  Non NULL means it is being created
              on behalf of an outside COM object that is reusing it via
              aggregation.
            CServer* pServer)
              Pointer to the server's control object.

  Modifies: m_cRefs, m_pUnkOuter, m_pServer.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFLicCruiseCar::CFLicCruiseCar(
  IUnknown* pUnkOuter,
  CServer* pServer) :
  m_ImpIClassFactory(this, pUnkOuter, pServer)
{
  // Zero the COM object's reference count.
  m_cRefs = 0;

  // No AddRef necessary if non-NULL, as we're nested.
  m_pUnkOuter = pUnkOuter;

  // Init the pointer to the server control object.
  m_pServer = pServer;

  LOGF1("P: CFLicCruiseCar Constructor. m_pUnkOuter=0x%X.", m_pUnkOuter);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCruiseCar::~CFLicCruiseCar

  Summary:  CFLicCruiseCar Destructor.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFLicCruiseCar::~CFLicCruiseCar(void)
{
  LOG("P: CFLicCruiseCar::Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCruiseCar::QueryInterface

  Summary:  QueryInterface of the CFLicCruiseCar non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFLicCruiseCar::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;
  *ppv = NULL;

  if (IID_IUnknown == riid)
  {
    *ppv = this;
    LOG("P: CFLicCruiseCar::QueryInterface. 'this' pIUnknown returned.");
  }
  else if (IID_IClassFactory == riid)
  {
    *ppv = &m_ImpIClassFactory;
    LOG("P: CFLicCruiseCar::QueryInterface. pIClassFactory returned.");
  }
  else if (IID_IClassFactory2 == riid)
  {
    *ppv = &m_ImpIClassFactory;
    LOG("P: CFLicCruiseCar::QueryInterface. pIClassFactory2 returned.");
  }

  if (NULL != *ppv)
  {
    // We've handed out a pointer to the interface so obey the COM rules
    // and AddRef the reference count.
    ((LPUNKNOWN)*ppv)->AddRef();
    hr = NOERROR;
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCruiseCar::AddRef

  Summary:  AddRef of the CFLicCruiseCar non-delegating IUnknown
            implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFLicCruiseCar::AddRef(void)
{
  m_cRefs++;

  LOGF1("P: CFLicCruiseCar::AddRef. New cRefs=%i.", m_cRefs);

  return m_cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCruiseCar::Release

  Summary:  Release of the CFLicCruiseCar non-delegating IUnknown
            implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFLicCruiseCar::Release(void)
{
  m_cRefs--;

  LOGF1("P: CFLicCruiseCar::Release. New cRefs=%i.", m_cRefs);

  if (0 == m_cRefs)
  {
    // We've reached a zero reference count for this COM object.
    // So we tell the server housing to decrement its global object
    // count so that the server will be unloaded if appropriate.
    if (NULL != m_pServer)
      m_pServer->ObjectsDown();

    // We artificially bump the main ref count to prevent reentrancy
    // via the main object destructor.  Not really needed in this
    // CFLicCruiseCar but a good practice because we are aggregatable and
    // may at some point in the future add something entertaining like
    // some Releases to the CFLicCruiseCar destructor.
    m_cRefs++;
    delete this;
  }

  return m_cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCruiseCar::CreateLicCruiseCar

  Summary:  Unconditionally create a LicCruiseCar COM object.  Called
            internally in this class from CreateInstance and
            CreateInstanceLic.

  Args:     IUnknown* pUnkOuter,
              [in] Pointer to the aggregation controlling outer IUnknown.
            REFIID riid,
              [in] The GUID of the interface that is being requested.
            PPVOID ppvCob)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
              Returned by a QueryInterface call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFLicCruiseCar::CreateLicCruiseCar(
               IUnknown* pUnkOuter,
               REFIID riid,
               PPVOID ppvCob)
{
  HRESULT hr = E_FAIL;
  COLicCruiseCar* pCob = NULL;

  LOGF1("P: CFLicCruiseCar::CreateLicCruiseCar. pUnkOuter=0x%X.",pUnkOuter);

  // If the creation call is requesting aggregation (pUnkOuter != NULL),
  // the COM rules state the IUnknown interface MUST also be concomitantly
  // be requested.  If it is not so requested ( riid != IID_IUnknown) then
  // an error must be returned indicating that no aggregate creation of
  // the COLicCruiseCarFactory COM Object can be performed.
  if (NULL != pUnkOuter && riid != IID_IUnknown)
    hr = CLASS_E_NOAGGREGATION;
  else
  {
    // Instantiate a COLicCruiseCar COM Object.
    pCob = new COLicCruiseCar(pUnkOuter, m_pServer);
    if (NULL != pCob)
    {
      // We initially created the new COM object so tell the server
      // to increment its global server object count to help ensure
      // that the server remains loaded until this partial creation
      // of a COM component is completed.
      m_pServer->ObjectsUp();

      // If we have succeeded in instantiating the COM object we
      // initialize it to set up any subordinate objects.
      hr = pCob->Init();
      if (SUCCEEDED(hr))
      {
        // We QueryInterface this new COM Object not only to deposit the
        // main interface pointer to the caller's pointer variable, but to
        // also automatically bump the Reference Count on the new COM
        // Object after handing out this reference to it.
        hr = pCob->QueryInterface(riid, (PPVOID)ppvCob);
      }

      if (FAILED(hr))
      {
        m_pServer->ObjectsDown();
        delete pCob;
      }
    }
    else
      hr = E_OUTOFMEMORY;
  }

  if (SUCCEEDED(hr))
  {
    LOGF1("P: CFLicCruiseCar::CreateLicCruiseCar Succeeded. *ppv=0x%X.",*ppvCob);
  }
  else
  {
    LOG("P: CFLicCruiseCar::CreateLicCruiseCar Failed.");
  }

  return hr;
}


/*---------------------------------------------------------------------------
  CFLicCruiseCar's nested implementation of the IClassFactory2 interface
  including Constructor, Destructor, QueryInterface, AddRef, Release,
  CreateInstance, LockServer, CreateInstanceLic, RequestLicKey, and
  GetLicInfo methods.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCruiseCar::CImpIClassFactory::CImpIClassFactory

  Summary:  Constructor for the CImpIClassFactory interface instantiation.

  Args:     CFLicCruiseCar* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter,
              Pointer to the outer Unknown.  For delegation.
            CServer* pServer)
              Pointer to the server's control object.

  Modifies: m_cRefI, m_pBackObj, m_pUnkOuter, m_pServer.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFLicCruiseCar::CImpIClassFactory::CImpIClassFactory(
  CFLicCruiseCar* pBackObj,
  IUnknown* pUnkOuter,
  CServer* pServer)
{
  // Init the Interface Ref Count (used for debugging only).
  m_cRefI = 0;

  // Init the Back Object Pointer to point to the parent object.
  m_pBackObj = pBackObj;

  // Init the pointer to the server control object.
  m_pServer = pServer;

  // Init the CImpIClassFactory interface's delegating Unknown pointer.
  // We use the Back Object pointer for IUnknown delegation here if we are
  // not being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpIClassFactory lifetime
  // is quaranteed by the lifetime of the parent object in which
  // CImpIClassFactory is nested.
  if (NULL == pUnkOuter)
  {
    m_pUnkOuter = pBackObj;
    LOG("P: CFLicCruiseCar::CImpIClassFactory Constructor. Non-Aggregating.");
  }
  else
  {
    m_pUnkOuter = pUnkOuter;
    LOG("P: CFLicCruiseCar::CImpIClassFactory Constructor. Aggregating.");
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCruiseCar::CImpIClassFactory::~CImpIClassFactory

  Summary:  Destructor for the CImpIClassFactory interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFLicCruiseCar::CImpIClassFactory::~CImpIClassFactory(void)
{
  LOG("P: CFLicCruiseCar::CImpIClassFactory Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCruiseCar::CImpIClassFactory::QueryInterface

  Summary:  The QueryInterface IUnknown member of this IClassFactory
            interface implementation that delegates to m_pUnkOuter,
            whatever it is.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
              Returned by the delegated outer QueryInterface call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFLicCruiseCar::CImpIClassFactory::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  LOG("P: CFLicCruiseCar::CImpIClassFactory::QueryInterface. Delegating.");

  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCruiseCar::CImpIClassFactory::AddRef

  Summary:  The AddRef IUnknown member of this IClassFactory interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFLicCruiseCar::CImpIClassFactory::AddRef(void)
{
  // Increment the Interface Reference Count.
  ++m_cRefI;

  LOGF1("P: CFLicCruiseCar::CImpIClassFactory::Addref. Delegating. New cI=%i.",m_cRefI);

  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCruiseCar::CImpIClassFactory::Release

  Summary:  The Release IUnknown member of this IClassFactory interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFLicCruiseCar::CImpIClassFactory::Release(void)
{
  // Decrement the Interface Reference Count.
  --m_cRefI;

  LOGF1("P: CFLicCruiseCar::CImpIClassFactory::Release. Delegating. New cI=%i.",m_cRefI);

  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCruiseCar::CImpIClassFactory::CreateInstance

  Summary:  The CreateInstance member method of this IClassFactory
            interface implementation.  Creates an instance of the
            COLicCruiseCar COM component.  Pays due heed to licensing and
            only completes the create if the server was confirmed as
            licensed.

  Args:     IUnknown* pUnkOuter,
              [in] Pointer to the controlling IUnknown.
            REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppvCob)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFLicCruiseCar::CImpIClassFactory::CreateInstance(
               IUnknown* pUnkOuter,
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = CLASS_E_NOTLICENSED;

  LOGF1("P: CFLicCruiseCar::CImpIClassFactory::CreateInstance. pUnkOuter=0x%X.",pUnkOuter);

  if (g_pServer->m_bLicensed)
    hr = m_pBackObj->CreateLicCruiseCar(pUnkOuter, riid, ppv);
  else
  {
    LOG("P: CFLicCruiseCar::CImpIClassFactory::CreateInstance. No Machine License.");
  }

  if (SUCCEEDED(hr))
  {
    LOGF1("P: CFLicCruiseCar::CImpIClassFactory::CreateInstance Succeeded. *ppv=0x%X.",*ppv);
  }
  else
  {
    LOG("P: CFLicCruiseCar::CImpIClassFactory::CreateInstance Failed.");
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCruiseCar::CImpIClassFactory::LockServer

  Summary:  The LockServer member method of this IClassFactory interface
            implementation.

  Args:     BOOL fLock)
              [in] Flag determining whether to Lock or Unlock the server.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFLicCruiseCar::CImpIClassFactory::LockServer(
               BOOL fLock)
{
  HRESULT hr = NOERROR;

  LOG("P: CFLicCruiseCar::CImpIClassFactory::LockServer.");

  if (fLock)
    m_pServer->Lock();
  else
    m_pServer->Unlock();

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCruiseCar::CImpIClassFactory::GetLicInfo


  Summary:  The GetLicInfo member method of the IClassFactory2 interface
            implementation.

  Args:     LPLICINFO lpLicInfo
              Pointer to the license info structure to fill.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFLicCruiseCar::CImpIClassFactory::GetLicInfo(
               LPLICINFO pLicInfo)
{
  HRESULT hr = NOERROR;

  LOG("P: CFLicCruiseCar::CImpIClassFactory::GetLicInfo.");

  if (NULL != pLicInfo)
  {
    pLicInfo->cbLicInfo = sizeof(LICINFO);

    // Inform whether RequestLicKey will work.
    pLicInfo->fRuntimeKeyAvail = g_pServer->m_bLicensed;

    // Inform whether the standard CreateInstance will work.
    pLicInfo->fLicVerified = g_pServer->m_bLicensed;
  }
  else
    hr = E_POINTER;

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCruiseCar::CImpIClassFactory::RequestLicKey


  Summary:  The RequestLicKey member method of the IClassFactory2
            interface implementation.  Returns a license key string
            for this Class Factory.  The key string is used in calls
            to the CreateInstanceLic IClassFactory2 method.

  Args:     DWORD dwReserved,
              Reserved for future use with multiple licenses.
            BSTR* pbstrKey
              Pointer to the buffer in which to return the key string.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFLicCruiseCar::CImpIClassFactory::RequestLicKey(
               DWORD dwReserved,
               BSTR* pbstrKey)
{
  HRESULT hr = CLASS_E_NOTLICENSED;
  OLECHAR szLicKey[MAX_LICENSEKEY];

  LOG("P: CFLicCruiseCar::CImpIClassFactory::RequestLicKey.");

  // Only return the license key if the server machine license was verified.
  if (g_pServer->m_bLicensed)
  {
    // Convert our ANSI license string to Wide Char and then alloc as BSTR.
    mbstowcs(szLicKey, g_pServer->m_szLicenseKey, g_pServer->m_cLicenseLen);
    *pbstrKey = SysAllocString(szLicKey);
    hr = (NULL != *pbstrKey) ? NOERROR : E_OUTOFMEMORY;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCruiseCar::CImpIClassFactory::CreateInstanceLic

  Summary:  The CreateInstanceLic member method of the IClassFactory2
            interface implementation.  Creates an instance of the managed
            COM object given a proper license key string.

  Args:     IUnknown* pUnkOuter,
              Pointer to the aggregation controlling IUnknown.
            IUnknown* pUnkReserved,
              Reserved.
            REFIID riid,
              A reference to the GUID of the interface requested on the
              new object.
            BSTR bstrKey,
              The license key string.
            PPVOID ppvCob
              Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFLicCruiseCar::CImpIClassFactory::CreateInstanceLic(
               IUnknown* pUnkOuter,
               IUnknown* pUnkReserved,
               REFIID riid,
               BSTR bstrKey,
               PPVOID ppvCob)
{
  HRESULT hr;
  BOOL    bMatch = FALSE;
  BSTR    bstrTemp;
  UINT    cch = g_pServer->m_cLicenseLen;
  OLECHAR szLicKey[MAX_LICENSEKEY];

  LOG("P: CFLicCruiseCar::CImpIClassFactory::CreateInstanceLic.");

  *ppvCob = NULL;

  // Convert our ANSI license string to Wide Char and then alloc as BSTR.
  mbstowcs(szLicKey, g_pServer->m_szLicenseKey, cch);
  bstrTemp = SysAllocString(szLicKey);
  if (NULL != bstrTemp)
  {
    if (NULL != bstrKey)
      bMatch = (0 == memcmp(bstrTemp, bstrKey, cch * sizeof(OLECHAR)));

    SysFreeString(bstrTemp);

    if (bMatch)
      hr = m_pBackObj->CreateLicCruiseCar(pUnkOuter, riid, ppvCob);
    else
    {
      LOG("P: CFLicCruiseCar::CImpIClassFactory::CreateInstanceLic. No Runtime License.");
      hr = CLASS_E_NOTLICENSED;
    }
  }
  else
    hr = E_OUTOFMEMORY;

  return hr;
}


/*---------------------------------------------------------------------------
  Implementation the CFLicCarSample Class Factory (IClassFactory).
  CFLicCarSample is the COM object class for the Class Factory that can
  manufacture COLicCarSample COM Components.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCarSample::CFLicCarSample

  Summary:  CFLicCruiseCar Constructor. Note the member initializer:
            "m_ImpIClassFactory(this, pUnkOuter, pServer)" which is used
            to pass the 'this', pUnkOuter, and pServer pointers of this
            constructor function to the constructor executed in the
            instantiation of the CImpIClassFactory interface whose
            implementation is nested inside this present object class.

  Args:     IUnknown* pUnkOuter,
              Pointer to the the outer Unknown.  NULL means this COM Object
              is not being Aggregated.  Non NULL means it is being created
              on behalf of an outside COM object that is reusing it via
              aggregation.
            CServer* pServer)
              Pointer to the server's control object.

  Modifies: m_cRefs, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFLicCarSample::CFLicCarSample(
  IUnknown* pUnkOuter,
  CServer* pServer) :
  m_ImpIClassFactory(this, pUnkOuter, pServer)
{
  // Zero the COM object's reference count.
  m_cRefs = 0;

  // No AddRef necessary if non-NULL, as we're nested.
  m_pUnkOuter = pUnkOuter;

  // Init the pointer to the server control object.
  m_pServer = pServer;

  LOGF1("P: CFLicCarSample Constructor. m_pUnkOuter=0x%X.", m_pUnkOuter);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCarSample::~CFLicCarSample

  Summary:  CFLicCarSample Destructor.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFLicCarSample::~CFLicCarSample(void)
{
  LOG("P: CFLicCarSample::Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCarSample::QueryInterface

  Summary:  QueryInterface of the CFLicCarSample non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFLicCarSample::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;
  *ppv = NULL;

  if (IID_IUnknown == riid)
  {
    *ppv = this;
    LOG("P: CFLicCarSample::QueryInterface. 'this' pIUnknown returned.");
  }
  else if (IID_IClassFactory == riid)
  {
    *ppv = &m_ImpIClassFactory;
    LOG("P: CFLicCarSample::QueryInterface. pIClassFactory returned.");
  }

  if (NULL != *ppv)
  {
    // We've handed out a pointer to the interface so obey the COM rules
    //   and AddRef the reference count.
    ((LPUNKNOWN)*ppv)->AddRef();
    hr = NOERROR;
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCarSample::AddRef

  Summary:  AddRef of the CFLicCarSample non-delegating IUnknown
            implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFLicCarSample::AddRef(void)
{
  m_cRefs++;

  LOGF1("P: CFLicCarSample::AddRef. New cRefs=%i.", m_cRefs);

  return m_cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCarSample::Release

  Summary:  Release of the CFLicCarSample non-delegating IUnknown
            implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFLicCarSample::Release(void)
{
  m_cRefs--;

  LOGF1("P: CFLicCarSample::Release. New cRefs=%i.", m_cRefs);

  if (0 == m_cRefs)
  {
    // We've reached a zero reference count for this COM object.
    // So we tell the server housing to decrement its global object
    // count so that the server will be unloaded if appropriate.
    if (NULL != m_pServer)
      m_pServer->ObjectsDown();

    // We artificially bump the main ref count to prevent reentrancy
    // via the main object destructor.  Not really needed in this
    // CFLicCarSample but a good practice because we are aggregatable and
    // may at some point in the future add something entertaining like
    // some Releases to the CFLicCarSample destructor.
    m_cRefs++;
    delete this;
  }

  return m_cRefs;
}


/*---------------------------------------------------------------------------
  CFLicCarSample's nested implementation of the IClassFactory interface
  including Constructor, Destructor, QueryInterface, AddRef, Release,
  CreateInstance, and LockServer methods.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCarSample::CImpIClassFactory::CImpIClassFactory

  Summary:  Constructor for the CImpIClassFactory interface instantiation.

  Args:     CFLicCarSample* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter,
              Pointer to the outer Unknown.  For delegation.
            CServer* pServer)
              Pointer to the server's control object.

  Modifies: m_cRefI, m_pBackObj, m_pUnkOuter, m_pServer.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFLicCarSample::CImpIClassFactory::CImpIClassFactory(
  CFLicCarSample* pBackObj,
  IUnknown* pUnkOuter,
  CServer* pServer)
{
  // Init the Interface Ref Count (used for debugging only).
  m_cRefI = 0;

  // Init the Back Object Pointer to point to the parent object.
  m_pBackObj = pBackObj;

  // Init the pointer to the server control object.
  m_pServer = pServer;

  // Init the CImpIClassFactory interface's delegating Unknown pointer.
  // We use the Back Object pointer for IUnknown delegation here if we are
  // not being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpIClassFactory lifetime
  // is quaranteed by the lifetime of the parent object in which
  // CImpIClassFactory is nested.
  if (NULL == pUnkOuter)
  {
    m_pUnkOuter = pBackObj;
    LOG("P: CFLicCarSample::CImpIClassFactory Constructor. Non-Aggregating.");
  }
  else
  {
    m_pUnkOuter = pUnkOuter;
    LOG("P: CFLicCarSample::CImpIClassFactory Constructor. Aggregating.");
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCarSample::CImpIClassFactory::~CImpIClassFactory

  Summary:  Destructor for the CImpIClassFactory interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CFLicCarSample::CImpIClassFactory::~CImpIClassFactory(void)
{
  LOG("P: CFLicCarSample::CImpIClassFactory Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCarSample::CImpIClassFactory::QueryInterface

  Summary:  The QueryInterface IUnknown member of this IClassFactory
            interface implementation that delegates to m_pUnkOuter,
            whatever it is.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
              Returned by the delegated outer QueryInterface call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFLicCarSample::CImpIClassFactory::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  LOG("P: CFLicCarSample::CImpIClassFactory::QueryInterface. Delegating.");

  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCarSample::CImpIClassFactory::AddRef

  Summary:  The AddRef IUnknown member of this IClassFactory interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFLicCarSample::CImpIClassFactory::AddRef(void)
{
  // Increment the Interface Reference Count.
  ++m_cRefI;

  LOGF1("P: CFLicCarSample::CImpIClassFactory::Addref. Delegating. New cI=%i.",m_cRefI);

  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCarSample::CImpIClassFactory::Release

  Summary:  The Release IUnknown member of this IClassFactory interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CFLicCarSample::CImpIClassFactory::Release(void)
{
  // Decrement the Interface Reference Count.
  --m_cRefI;

  LOGF1("P: CFLicCarSample::CImpIClassFactory::Release. Delegating. New cI=%i.",m_cRefI);

  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCarSample::CImpIClassFactory::CreateInstance

  Summary:  The CreateInstance member method of this IClassFactory
            interface implementation.  Creates an instance of the
            COLicCarSample COM component.

  Args:     IUnknown* pUnkOuter,
              [in] Pointer to the controlling IUnknown.
            REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFLicCarSample::CImpIClassFactory::CreateInstance(
               IUnknown* pUnkOuter,
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_FAIL;
  COLicCarSample* pCob = NULL;

  LOGF1("P: CFLicCarSample::CImpIClassFactory::CreateInstance. pUnkOuter=0x%X.",pUnkOuter);

  // If the creation call is requesting aggregation (pUnkOuter != NULL),
  // the COM rules state the IUnknown interface MUST also be concomitantly
  // be requested.  If it is not so requested ( riid != IID_IUnknown) then
  // an error must be returned indicating that no aggregate creation of
  // the CFLicCarSample COM Object can be performed.
  if (NULL != pUnkOuter && riid != IID_IUnknown)
    hr = CLASS_E_NOAGGREGATION;
  else
  {
    // Instantiate a COLicCarSample COM Object.
    pCob = new COLicCarSample(pUnkOuter, m_pServer);
    if (NULL != pCob)
    {
      // We initially created the new COM object so tell the server
      // to increment its global server object count to help ensure
      // that the server remains loaded until this partial creation
      // of a COM component is completed.
      m_pServer->ObjectsUp();

      // We QueryInterface this new COM Object not only to deposit the
      // main interface pointer to the caller's pointer variable, but to
      // also automatically bump the Reference Count on the new COM
      // Object after handing out this reference to it.
      hr = pCob->QueryInterface(riid, (PPVOID)ppv);
      if (FAILED(hr))
      {
        m_pServer->ObjectsDown();
        delete pCob;
      }
    }
    else
      hr = E_OUTOFMEMORY;
  }

  if (SUCCEEDED(hr))
  {
    LOGF1("P: CFLicCarSample::CImpIClassFactory::CreateInstance Succeeded. *ppv=0x%X.",*ppv);
  }
  else
  {
    LOG("P: CFLicCarSample::CImpIClassFactory::CreateInstance Failed.");
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFLicCarSample::CImpIClassFactory::LockServer

  Summary:  The LockServer member method of this IClassFactory interface
            implementation.

  Args:     BOOL fLock)
              [in] Flag determining whether to Lock or Unlock the server.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CFLicCarSample::CImpIClassFactory::LockServer(
               BOOL fLock)
{
  HRESULT hr = NOERROR;

  LOG("P: CFLicCarSample::CImpIClassFactory::LockServer.");

  if (fLock)
    m_pServer->Lock();
  else
    m_pServer->Unlock();

  return hr;
}
