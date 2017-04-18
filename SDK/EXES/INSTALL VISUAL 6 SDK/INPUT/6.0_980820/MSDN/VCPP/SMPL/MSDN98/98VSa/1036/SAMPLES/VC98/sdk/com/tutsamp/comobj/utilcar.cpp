/*+==========================================================================
  File:      UTILCAR.CPP

  Summary:   Implementation file for the aggregatable COUtilityCar COM
             object class.

             UTILCAR showcases the construction of the COUtilityCar COM
             object class with the IUnknown, ICar, and IUtility interfaces.
             This is done through Containment reuse of COCar's ICar
             interface features.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the accompanying COMOBJ.TXT
             file.  For more specific technical details on the internal
             workings see the comments dispersed throughout the
             module's source code.

  Classes:   COUtilityCar

  Functions: none.

  Origin:    10-3-97: atrent - Created. [Revised]

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
  We include OLE2.H because we will make calls to the COM/OLE Libraries.
  We include APPUTIL.H because we will be building this application using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include ICARS.H and CARGUIDS.H for the common car-related Interface
    class, GUID, and CLSID specifications.
  We include COMOBJI.H because it has internal class declarations and
    resource ID definitions specific for this DLL.
  We include COMOBJ.H because it has the interface declarations.
  We include CAR.H because it has the class COCar declarations.
  We include UTILCAR.H because it has the class COUtilityCar declarations.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <apputil.h>
#include <icars.h>
#include <carguids.h>
#include "comobji.h"
#define _LOCALCALLS_
#include "comobj.h"
#include "car.h"
#include "utilcar.h"


/*---------------------------------------------------------------------------
  COUtilityCar's implementation of its main COM object class including
  Constructor, Destructor, QueryInterface, AddRef, and Release.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::COUtilityCar

  Summary:  COUtilityCar Constructor. Note the member initializers:
            "m_ImpICar(this, pUnkOuter)" and "m_ImpIUtility(this,
            pUnkOuter)" which are used to pass the 'this' and
            pUnkOuter pointers of this constructor function to the
            constructors that instantiate the implementations of
            the CImpICar and CImpIUtility interfaces (which are both
            nested inside this present COUtilityCar Object Class.

  Args:     IUnknown* pUnkOuter)
              Pointer to the the outer Unknown.  NULL means this COM Object
              is not being Aggregated.  Non NULL means it is being created
              on behalf of an outside COM object that is reusing it via
              aggregation.

  Modifies: m_cRefs, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COUtilityCar::COUtilityCar(
  IUnknown* pUnkOuter) :
  m_ImpICar(this, pUnkOuter),
  m_ImpIUtility(this, pUnkOuter)
{
  // Zero the COM object's reference count.
  m_cRefs = 0;

  // No AddRef necessary if non-NULL, as we're nested.
  m_pUnkOuter = pUnkOuter;

  // Zero the pointer to the contained COCar object's ICar interface.
  m_pICar = NULL;

  LOGF1("D: COUtilityCar Constructor. m_pUnkOuter=0x%X.", m_pUnkOuter);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::~COUtilityCar

  Summary:  COUtilityCar Destructor.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COUtilityCar::~COUtilityCar(void)
{
  LOG("D: COUtilityCar::Destructor.");

  m_pICar->Release();

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::Init

  Summary:  COUtilityCar Initialization method.

  Args:     void

  Modifies: m_pUnkCar, m_pICar, m_cRefs.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COUtilityCar::Init(void)
{
  HRESULT hr;

  LOG("D: COUtilityCar::Init.");

  // Create an instance of the COCar object and ask for its ICar
  // interface directly.  We pass NULL for the pUnkOuter because we
  // are not aggregating.  It is here that we are reusing the COCar
  // COM Object through the Containment technique.  We cache the
  // pointer to the ICar interface for later delegation use.  We
  // don't need to AddRef it here because CreateCar does that for us.
  hr = CreateCar(NULL, IID_ICar, (PPVOID) &m_pICar);

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::QueryInterface

  Summary:  QueryInterface of the COUtilityCar non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Modifies: .

  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCar::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;
  *ppv = NULL;

  if (IID_IUnknown == riid)
  {
    *ppv = this;
    LOG("D: COUtilityCar::QueryInterface. 'this' pIUnknown returned");
  }
  else if (IID_ICar == riid)
  {
    *ppv = &m_ImpICar;
    LOG("D: COUtilityCar::QueryInterface. pICar returned");
  }
  else if (IID_IUtility == riid)
  {
    *ppv = &m_ImpIUtility;
    LOG("D: COUtilityCar::QueryInterface. pIUtility returned");
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
  Method:   COUtilityCar::AddRef

  Summary:  AddRef of the COUtilityCar non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COUtilityCar::AddRef(void)
{
  m_cRefs++;

  LOGF1("D: COUtilityCar::AddRef. New cRefs=%i.", m_cRefs);

  return m_cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::Release

  Summary:  Release of the COUtilityCar non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COUtilityCar::Release(void)
{
  m_cRefs--;

  LOGF1("D: COUtilityCar::Release. New cRefs=%i.", m_cRefs);

  if (0 == m_cRefs)
  {
    // We artificially bump the main ref count to prevent reentrancy
    // via the main object destructor.
    m_cRefs++;
    delete this;
  }

  return m_cRefs;;
}


/*---------------------------------------------------------------------------
  COUtilityCar's nested implementation of the ICar interface including
  Constructor, Destructor, QueryInterface, AddRef, Release,
  Shift, Clutch, Speed, and Steer.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::CImpICar::CImpICar

  Summary:  Constructor for the CImpICar interface instantiation.

  Args:     COUtilityCar* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter)
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_cRefI, m_pBackObj, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COUtilityCar::CImpICar::CImpICar(
  COUtilityCar* pBackObj,
  IUnknown* pUnkOuter)
{
  // Init the Interface Ref Count (used for debugging only).
  m_cRefI=0;

  // Init the Back Object Pointer to point to the outer object.
  m_pBackObj=pBackObj;

  // Init the CImpICar interface's delegating Unknown pointer.  We use
  // the Back Object pointer for IUnknown delegation here if we are not
  // being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpICar lifetime is
  // quaranteed by the lifetime of the parent object in which
  // CImpICar is nested.
  if (NULL == pUnkOuter)
  {
    m_pUnkOuter = pBackObj;
    LOG("D: COUtilityCar::CImpICar Constructor. Non-Aggregating");
  }
  else
  {
    m_pUnkOuter = pUnkOuter;
    LOG("D: COUtilityCar::CImpICar Constructor. Aggregating");
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::CImpICar::~CImpICar

  Summary:  Destructor for the CImpICar interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COUtilityCar::CImpICar::~CImpICar(void)
{
  LOG("D: COUtilityCar::CImpICar Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::CImpICar::QueryInterface

  Summary:  The QueryInterface IUnknown member of this ICar interface
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
STDMETHODIMP COUtilityCar::CImpICar::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  LOG("D: COUtilityCar::CImpICar::QueryInterface. Delegating.");

  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::CImpICar::AddRef

  Summary:  The AddRef IUnknown member of this ICar interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COUtilityCar::CImpICar::AddRef(void)
{
  // Increment the Interface Reference Count.
  ++m_cRefI;

  LOGF1("D: COUtilityCar::CImpICar::Addref. Delegating. New cI=%i.", m_cRefI);

  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::CImpICar::Release

  Summary:  The Release IUnknown member of this ICar interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COUtilityCar::CImpICar::Release(void)
{
  // Decrement the Interface Reference Count.
  --m_cRefI;

  LOGF1("D: COUtilityCar::CImpICar::Release. Delegating. New cI=%i.", m_cRefI);

  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::CImpICar::Shift

  Summary:  The Shift member method of this ICar interface implementation.
            A simple empty method on a COUtilityCar COM object for tutorial
            purposes.  Presumably if this Car object were modeling
            a real Car then the Shift method would shift to the specified
            gear.

  Args:     short nGear
              0 - Neutral; 1 - 5 First 5 forward gears; 6 - Reverse.

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCar::CImpICar::Shift(
               short nGear)
{
  LOGF1("D: COUtilityCar::CImpICar::Shift. Delegating. nGear=%i.",nGear);

  m_pBackObj->m_pICar->Shift(nGear);

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::CImpICar::Clutch

  Summary:  The Clutch member method of this ICar interface implementation.
            A simple empty method on a COUtilityCar COM object for tutorial
            purposes.  Presumably if this Car object were modeling
            a real Car then the Clutch method would engage the clutch the
            specified amount.

  Args:     short nEngaged)
              Percent clutch is engaged (0 to 100%).

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCar::CImpICar::Clutch(
               short nEngaged)
{
  LOGF1("D: COUtilityCar::CImpICar::Clutch. Delegating. nEngaged=%i.",nEngaged);

  m_pBackObj->m_pICar->Clutch(nEngaged);

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::CImpICar::Speed

  Summary:  The Propel member method of this ICar interface implementation.
            A simple empty method on a COUtilityCar COM object for tutorial
            purposes.  Presumably if this Car object were modeling
            a real Car then this method would accelerate/brake to bring
            the car to the specified speed.

  Args:     short nMph
              New speed in miles per hour.

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCar::CImpICar::Speed(
               short nMph)
{
  LOGF1("D: COUtilityCar::CImpICar::Speed. Delegating. nMph=%i.",nMph);

  m_pBackObj->m_pICar->Speed(nMph);

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::CImpICar::Steer

  Summary:  The Steer member method of this ICar interface implementation.
            A simple empty method on a COUtilityCar COM object for tutorial
            purposes.  Presumably if this Car object were modeling
            a real Car then the Steer method would set the steering
            angle of the Car.

  Args:     short nAngle)
              0 degrees straight ahead, -45 Full left, +45 Full right.

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCar::CImpICar::Steer(
               short nAngle)
{
 LOGF1("D: COUtilityCar::CImpICar::Steer. Delegating. nAngle=%i.",nAngle);

  m_pBackObj->m_pICar->Steer(nAngle);

  return NOERROR;
}


/*---------------------------------------------------------------------------
  COUtilityCar's nested implementation of the IUtility interface including
  Constructor, Destructor, QueryInterface, AddRef, Release,
  Offroad, and Winch.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::CImpIUtility::CImpIUtility

  Summary:  Constructor for the CImpIUtility interface instantiation.

  Args:     COUtilityCar* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter)
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_cRefI, m_pBackObj, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COUtilityCar::CImpIUtility::CImpIUtility(
  COUtilityCar* pBackObj,
  IUnknown* pUnkOuter)
{
  // Init the Interface Ref Count (used for debugging only).
  m_cRefI = 0;

  // Init the Back Object Pointer to point to the outer object.
  m_pBackObj = pBackObj;

  // Init the CImpIUtility interface's delegating Unknown pointer.  We use
  // the Back Object pointer for IUnknown delegation here if we are not
  // being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpIUtility lifetime is
  // quaranteed by the lifetime of the parent object in which
  // CImpIUtility is nested.
  if (NULL == pUnkOuter)
  {
    m_pUnkOuter = pBackObj;
    LOG("D: COUtilityCar::CImpIUtility Constructor. Non-Aggregating.");
  }
  else
  {
    m_pUnkOuter = pUnkOuter;
    LOG("D: COUtilityCar::CImpIUtility Constructor. Aggregating.");
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::CImpIUtility::~CImpIUtility

  Summary:  Destructor for the CImpIUtility interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COUtilityCar::CImpIUtility::~CImpIUtility(void)
{
  LOG("D: COUtilityCar::CImpIUtility Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::CImpIUtility::QueryInterface

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
STDMETHODIMP COUtilityCar::CImpIUtility::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  LOG("D: COUtilityCar::CImpIUtility::QueryInterface. Delegating.");

  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::CImpIUtility::AddRef

  Summary:  The AddRef IUnknown member of this IUtility interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COUtilityCar::CImpIUtility::AddRef(void)
{
  // Increment the Interface Reference Count.
  ++m_cRefI;

  LOGF1("D: COUtilityCar::CImpIUtility::Addref. Delegating. New cI=%i.", m_cRefI);

  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::CImpIUtility::Release

  Summary:  The Release IUnknown member of this IUtility interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COUtilityCar::CImpIUtility::Release(void)
{
  // Decrement the Interface Reference Count.
  --m_cRefI;

  LOGF1("D: COUtilityCar::CImpIUtility::Release. Delegating. New cI=%i.", m_cRefI);

  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::CImpIUtility::Offroad

  Summary:  The Offroad member method of this IUtility interface
            implementation.  A simple empty method on a COUtilityCar
            COM object for tutorial purposes.  Presumably if this
            UtilityCar object were modeling a real Car then the Offroad
            method would function the 4-wheel drive transfer case and
            shift it to the specified 4-wheel drive mode.

  Args:     short nGear
              0 = 2H or regular 2-wheel drive;
              1 = 4H or 4-wheel drive high speed;
              2 = neutral; and
              3 = 4L or 4-wheel drive low speed).

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCar::CImpIUtility::Offroad(
               short nGear)
{
  LOGF1("D: COUtilityCar::CImpIUtility::Offroad. Called. nGear=%i.",nGear);

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COUtilityCar::CImpIUtility::Winch

  Summary:  The Winch member method of this IUtility interface
            implementation.  A simple empty method on a COUtilityCar COM
            object for tutorial purposes.  Presumably if this UtilityCar
            object were modeling a real Car then the Winch method would
            turn on/off the front-mounted Winch to the specified RPMs.

  Args:     short nRpm
              0 = off; 1 - 50 RPM.

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COUtilityCar::CImpIUtility::Winch(
               short nRpm)
{
  LOGF1("D: COUtilityCar::CImpIUtility::Winch. Called. nRpm=%i.",nRpm);

  return NOERROR;
}
