/*+==========================================================================
  File:      UTCRUCAR.CPP

  Summary:   Implementation file for the aggregatable COUtilityCruiseCar
             COM object class.

             UTCRUCAR showcases the construction of the COUtilityCruiseCar
             COM object class with the IUnknown, ICar, ICruise, and
             IUtility interfaces.  This is done through Aggregation reuse
             of COCruiseCar's ICar and ICruise interface features.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial DLLCLIEN.HTM
             file.  For more specific technical details on the internal
             workings see the comments dispersed throughout the
             module's source code.

  Classes:   COUtilityCruiseCar

  Functions: CreateUtilityCruiseCar.

  Origin:    9-20-95: atrent - Editor inheritance from COMUSER source.

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
  We include OLE2.H because we will be calling the COM/OLE Libraries.
  We include APPUTIL.H because we will be building this application using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include ICARS.H and CARGUIDS.H for the common car-related Interface
    class, GUID, and CLSID specifications.
  We include UTCRUCAR.H because it has the COUtilityCruiseCar declarations.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <apputil.h>
#include <icars.h>
#include <carguids.h>
#include "dllclien.h"
#include "utcrucar.h"


/*---------------------------------------------------------------------------
  COUtilityCruiseCar's implementation of its main COM object class including
  Constructor, Destructor, QueryInterface, AddRef, and Release.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::COUtilityCruiseCar

  Summary:  COUtilityCruiseCar Constructor. Note the member initializer:
            "m_ImpIUtility(this, pUnkOuter)" which is used to pass the 'this'
            and pUnkOuter pointers of this constructor function to the
            constructor in the instantiation of the implementation of
            the CImpIUtility interface (which is nested inside this present
            COUtilityCruiseCar Object Class).

  Args:     IUnknown* pUnkOuter)
              Pointer to the the outer Unknown.  NULL means this COM Object
              is not being Aggregated.  Non NULL means it is being created
              on behalf of an outside COM object that is reusing it via
              aggregation.

  Modifies: m_cRefs, m_pUnkOuter, m_pUnkCruiseCar.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COUtilityCruiseCar::COUtilityCruiseCar(
  IUnknown* pUnkOuter) :
  m_ImpIUtility(this, pUnkOuter)
{
  // Zero the COM object's reference count.
  m_cRefs = 0;

  // No AddRef necessary if non-NULL, as this COM object's lifetime
  // is totally coupled with the controlling Outer object's lifetime.
  m_pUnkOuter = pUnkOuter;

  // Zero the pointer to the aggregated COCruiseCar object's IUnknown
  // interface (for delegation of IUnknown calls to it).
  m_pUnkCruiseCar = NULL;

  LOGF1("C: COUtilityCruiseCar Constructor. m_pUnkOuter=0x%X.", m_pUnkOuter);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::~COUtilityCruiseCar

  Summary:  COUtilityCruiseCar Destructor.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COUtilityCruiseCar::~COUtilityCruiseCar(void)
{
  LOG("C: COUtilityCruiseCar::Destructor.");

  RELEASE_INTERFACE(m_pUnkCruiseCar);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::Init

  Summary:  COUtilityCruiseCar Initialization method.

  Args:     void

  Modifies: m_pUnkCruiseCar, m_pICar, m_pICruise, m_cRefs.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COUtilityCruiseCar::Init(void)
{
  HRESULT hr;
  IClassFactory* pICFCruiseCar;

  // Set up the right pIUnknown for delegation.  If we are being
  // aggregated then we pass the pUnkOuter in turn to any COM objects
  // that we are aggregating.  m_pUnkOuter was set in the Constructor.
  IUnknown* pUnkOuter = (NULL == m_pUnkOuter) ? this : m_pUnkOuter;

  LOG("C: COUtilityCruiseCar::Init.");

  // Get a class factory for DllCruiseCar and issue IClassFactory's
  // CreateInstance method to manufacture a COCruiseCar COM object.
  hr = CoGetClassObject(
         CLSID_DllCruiseCar,
         CLSCTX_INPROC_SERVER,
         NULL,
         IID_IClassFactory,
         (PPVOID)&pICFCruiseCar);
  if (SUCCEEDED(hr))
  {
    hr = pICFCruiseCar->CreateInstance(
                          pUnkOuter,
                          IID_IUnknown,
                          (PPVOID)&m_pUnkCruiseCar);
    pICFCruiseCar->Release();
  }

  if (SUCCEEDED(hr))
  {
    LOG("C: COUtilityCruiseCar::Init Succeeded.");
  }
  else
  {
    LOG("C: COUtilityCruiseCar::Init Failed.");
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::QueryInterface

  Summary:  QueryInterface of the COUtilityCruiseCar non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Modifies: .

  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCruiseCar::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;
  *ppv = NULL;

  if (IID_IUnknown == riid)
  {
    *ppv = this;
    LOG("C: COUtilityCruiseCar::QueryInterface. 'this' pIUnknown returned.");
  }
  else if (IID_IUtility == riid)
  {
    // This IUtility interface is implemented in this COUtilityCruiseCar
    // object as a native interface of COUtilityCruiseCar.
    *ppv = &m_ImpIUtility;
    LOG("C: COUtilityCruiseCar::QueryInterface. pIUtility returned.");
  }

  if (NULL != *ppv)
  {
    // We've handed out a pointer to an interface so obey the COM rules
    //   and AddRef its reference count.
    ((LPUNKNOWN)*ppv)->AddRef();
    hr = NOERROR;
  }
  else if (IID_ICar == riid)
  {
    LOG("C: COUtilityCruiseCar::QueryInterface. ICar delegating.");
    // We didn't implement the ICar interface in this COUtilityCruiseCar
    // object.  The aggregated inner object (CruiseCar) is contributing
    // the ICar interface to this present composite or aggregating
    // UtilityCruiseCar object.  So, to satisfy a QI request for the ICar
    // interface, we delegate the QueryInterface to the inner
    // object's IUnknown.
    hr = m_pUnkCruiseCar->QueryInterface(riid, ppv);
  }
  else if (IID_ICruise == riid)
  {
    LOG("C: COUtilityCruiseCar::QueryInterface. ICruise delegating.");
    // We didn't implement the ICruise interface in this COUtilityCruiseCar
    // object.  The aggregated inner object (CruiseCar) is contributing
    // the ICruise interface to this present composite or aggregating
    // UtilityCruiseCar object.  As above we delegate this QI to the
    // aggregated object's IUnknown.
    hr = m_pUnkCruiseCar->QueryInterface(riid, ppv);
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::AddRef

  Summary:  AddRef of the COUtilityCruiseCar non-delegating
            IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COUtilityCruiseCar::AddRef(void)
{
  m_cRefs++;

  LOGF1("C: COUtilityCruiseCar::AddRef. New cRefs=%i.", m_cRefs);

  return m_cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::Release

  Summary:  Release of the COUtilityCruiseCar non-delegating IUnknown
            implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COUtilityCruiseCar::Release(void)
{
  ULONG ulCount = --m_cRefs;

  LOGF1("C: COUtilityCruiseCar::Release. New cRefs=%i.", m_cRefs);

  if (0 == m_cRefs)
  {
    // We artificially bump the main ref count.  Thie fulfills one of
    // the rules of aggregated objects and ensures that an indirect
    // recursive call to this release won't occur because of other
    // delegating releases that might happen in our own destructor.
    m_cRefs++;
    delete this;
  }

  return ulCount;
}


/*---------------------------------------------------------------------------
  COUtilityCruiseCar's nested implementation of the IUtility interface
  including methods: Constructor, Destructor, QueryInterface, AddRef,
  Release, Offroad, and Winch.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpIUtility::CImpIUtility

  Summary:  Constructor for the CImpIUtility interface instantiation.

  Args:     COUtilityCruiseCar* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter)
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_cRefI, m_pBackObj, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COUtilityCruiseCar::CImpIUtility::CImpIUtility(
  COUtilityCruiseCar* pBackObj,
  IUnknown* pUnkOuter)
{
  // Init the Interface Ref Count (used for debugging only).
  m_cRefI = 0;

  // Init the Back Object Pointer to point to the outer object.
  m_pBackObj = pBackObj;

  // Init the CImpIUtility interface's delegating IUnknown pointer.  We use
  // the Back Object pointer for IUnknown delegation here if we are not
  // being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpIUtility lifetime is
  // quaranteed by the lifetime of the parent object in which
  // CImpIUtility is nested.
  if (NULL == pUnkOuter)
  {
    m_pUnkOuter = pBackObj;
    LOG("C: COUtilityCruiseCar::CImpIUtility Constructor. Non-Aggregating.");
  }
  else
  {
    m_pUnkOuter = pUnkOuter;
    LOG("C: COUtilityCruiseCar::CImpIUtility Constructor. Aggregating.");
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpIUtility::~CImpIUtility

  Summary:  Destructor for the CImpIUtility interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COUtilityCruiseCar::CImpIUtility::~CImpIUtility(void)
{
  LOG("C: COUtilityCruiseCar::CImpIUtility Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpIUtility::QueryInterface

  Summary:  The QueryInterface IUnknown member of this IUtility interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Modifies: .

  Returns:  HRESULT
              Returned by the delegated outer QueryInterface call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCruiseCar::CImpIUtility::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  LOG("C: COUtilityCruiseCar::CImpIUtility::QueryInterface. Delegating.");

  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpIUtility::AddRef

  Summary:  The AddRef IUnknown member of this IUtility interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COUtilityCruiseCar::CImpIUtility::AddRef(void)
{
  // Increment the Interface Reference Count.
  ++m_cRefI;

  LOGF1("C: COUtilityCruiseCar::CImpIUtility::Addref. Delegating. New cI=%i.", m_cRefI);

  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpIUtility::Release

  Summary:  The Release IUnknown member of this IUtility interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COUtilityCruiseCar::CImpIUtility::Release(void)
{
  // Decrement the Interface Reference Count.
  --m_cRefI;

  LOGF1("C: COUtilityCruiseCar::CImpIUtility::Release. Delegating. New cI=%i.", m_cRefI);

  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpIUtility::Offroad

  Summary:  The Offroad member method of this IUtility interface
            implementation.  A simple empty method on a COUtilityCruiseCar
            COM object for tutorial purposes.  Presumably if this
            UtilityCruise Car object were modeling a real Car then the
            Offroad method would function the 4-wheel drive transfer case
            and shift it to the specified 4-wheel drive mode.

  Args:     short nGear
              0 = 2H or regular 2-wheel drive;
              1 = 4H or 4-wheel drive high speed;
              2 = neutral; and
              3 = 4L or 4-wheel drive low speed).

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCruiseCar::CImpIUtility::Offroad(
               short nGear)
{
  HRESULT hr;
  ICar* pICar = NULL;

  // In our fantasy Sport-Utility Car world we may need to stop the car
  // before switching to 4-Wheel drive low (nGear == 3 for 4L). Let's
  // assume so because it's a convenient excuse to show this aggregating
  // COUtilityCruiseCar outer object using one of the interfaces (ICar)
  // of its aggregated COCruiseCar inner object.  DLLCLIEN gracefully
  // cooperates in this by invoking this Offroad method from the
  // UtilityCruiseCar menu with nGear == 3.
  if (3 == nGear)
  {
    hr = m_pBackObj->m_pUnkCruiseCar->QueryInterface(
                                        IID_ICar,
                                        (PPVOID)&pICar);
    if (SUCCEEDED(hr))
    {
      m_pUnkOuter->Release();
      pICar->Speed(0);
      m_pUnkOuter->AddRef();
      pICar->Release();
    }
  }

  LOGF1("C: COUtilityCruiseCar::CImpIUtility::Offroad. Called. nGear=%i.",nGear);

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCruiseCar::CImpIUtility::Winch

  Summary:  The Adjust member method of this IUtility interface
            implementation.  A simple empty method on a COUtilityCruiseCar
            COM object for tutorial purposes.  Presumably if this
            UtilityCruiseCar object were modeling a real Car then the
            Winch method would turn on/off the front-mounted Winch to the
            specified RPMs.

  Args:     short nRpm
              0 = off; 1 - 50 RPM.

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCruiseCar::CImpIUtility::Winch(
               short nRpm)
{
  LOGF1("C: COUtilityCruiseCar::CImpIUtility::Winch. Called. nRpm=%i.",nRpm);

  return NOERROR;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: CreateUtilityCruiseCar

  Summary:  Creates an instance of the COUtilityCruiseCar COM object class
            returning a requested interface pointer. COUtilityCruiseCar
            uses the Aggregation reuse technique to incorporate
            COCruiseCar features (ie, ICar and ICruise implementations)
            into its Interface offerings (ie, IUnknown, and IUtility).
            With this aggregation, the ICar and ICruise interfaces are
            not implemented in COUtilityCruiseCar.  They are instead
            solely implemented in a COCruiseCar object that
            CreateUtilityCruiseCar instantiates.  That COCruiseCar's ICar
            and ICruise implementations are used directly in this
            aggregation.  COCruiseCar is provided by the outside DLLSERVE.DLL.

  Args:     IUnknown* pUnkOuter,
              Pointer the outer Unknown interface.  Non NULL implies
              that the new COM object is being created via an
              aggregation with an Outer object.  NULL implies that the
              object is not being created via aggregation.
            REFIID riid,
              The GUID of the interface requested on the new COM Object.
            PPVOID ppv)
              Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              NOERROR if successful, CLASS_E_NOAGREGATION if IUnknown is
              not requested with non-NULL pUnkOuter, or other errors as
              appropriate.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
HRESULT CreateUtilityCruiseCar(
          IUnknown* pUnkOuter,
          REFIID riid,
          PPVOID ppv)
{
  HRESULT hr;
  COUtilityCruiseCar* pCob;

  LOGF1("C: CreateUtilityCruiseCar. pUnkOuter=0x%X.",pUnkOuter);

  // If the creation call is requesting aggregation (pUnkOuter != NULL),
  // the COM rules state the IUnknown interface MUST also be concomitantly
  // requested.  If it is not so requested ( riid != IID_IUnknown) then
  // an error must be returned indicating that no aggregate creation of
  // the COUtilityCruiseCar COM Object can be performed using anything
  // other than a controlling IUnknown interface.
  if (NULL != pUnkOuter && riid != IID_IUnknown)
    hr = CLASS_E_NOAGGREGATION;
  else
  {
    // Instantiate a COUtilityCruiseCar COM Object.
    pCob = new COUtilityCruiseCar(pUnkOuter);
    if (NULL != pCob)
    {
      // If we have succeeded in instantiating the COUtilityCruiseCar object
      // we initialize it to offer it's interfaces.
      hr = pCob->Init();
      if (SUCCEEDED(hr))
      {
        // We QueryInterface this new COM Object not only to deposit the
        // main interface pointer to the caller's pointer variable, but to
        // also automatically bump the Reference Count on the new COM
        // Object after handing out this *ppv reference to it.
        hr = pCob->QueryInterface(riid, (PPVOID)ppv);
      }
    }
    else
      hr = E_OUTOFMEMORY;
  }

  if (SUCCEEDED(hr))
    LOGF1("C: CreateUtilityCruiseCar Succeeded. *ppv=0x%X.",*ppv);

  return hr;
}
