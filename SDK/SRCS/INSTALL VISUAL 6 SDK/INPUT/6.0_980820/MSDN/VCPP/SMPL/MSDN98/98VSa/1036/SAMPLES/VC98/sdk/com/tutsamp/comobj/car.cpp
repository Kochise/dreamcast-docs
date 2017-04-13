/*+==========================================================================
  File:      CAR.CPP

  Summary:   Implementation file for the COCar COM Object Class (for
             aggregatable Car COM Objects).

             Of particular interest for an COM application, CAR
             showcases a COM Object Class offering a main IUnknown
             interface and the ICar interface of Car-related features.
             This multiple interface COM Object Class is achieved via
             the technique of nested classes: the implementation of the
             ICar interface is nested inside of the COCar COM
             Object Class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial COMOBJ.HTM
             file.  For more specific technical details on the internal
             workings see the comments dispersed throughout the
             module's source code.

  Classes:   COCar

  Functions: none.

  Origin:    8-19-95: atrent - Created.

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
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <apputil.h>
#include <icars.h>
#include <carguids.h>
#include "comobji.h"
#include "comobj.h"
#include "car.h"


/*---------------------------------------------------------------------------
  COCar's implementation of its main COM object class including
  Constructor, Destructor, QueryInterface, AddRef, and Release.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCar::COCar

  Summary:  COCar Constructor. Note the member initializer:
            "m_ImpICar(this, pUnkOuter)" which is used to pass the 'this'
            and pUnkOuter pointers of this constructor function to the
            constructor in the instantiation of the implementation of
            the CImpICar interface (which is nested inside this present
            COCar Object Class).

  Args:     IUnknown* pUnkOuter)
              Pointer to the the outer Unknown.  NULL means this COM Object
              is not being Aggregated.  Non NULL means it is being created
              on behalf of an outside COM object that is reusing it via
              aggregation.

  Modifies: m_cRefs, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COCar::COCar(
  IUnknown* pUnkOuter) :
  m_ImpICar(this, pUnkOuter)
{
  // Zero the COM object's reference count.
  m_cRefs = 0;

  // No AddRef necessary if non-NULL, as we're nested.
  m_pUnkOuter = pUnkOuter;

  LOGF1("D: COCar Constructor. m_pUnkOuter=0x%X.", m_pUnkOuter);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCar::~COCar

  Summary:  COCar Destructor.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COCar::~COCar(void)
{
  LOG("D: COCar::Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCar::QueryInterface

  Summary:  QueryInterface of the COCar non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Modifies: .

  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COCar::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;
  *ppv = NULL;

  if (IID_IUnknown == riid)
  {
    *ppv = this;
    LOG("D: COCar::QueryInterface. 'this' pIUnknown returned.");
  }
  else if (IID_ICar == riid)
  {
    *ppv = &m_ImpICar;
    LOG("D: COCar::QueryInterface. pICar returned.");
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
  Method:   COCar::AddRef

  Summary:  AddRef of the COCar non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COCar::AddRef(void)
{
  m_cRefs++;

  LOGF1("D: COCar::AddRef. New cRefs=%i.", m_cRefs);

  return m_cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCar::Release

  Summary:  Release of the COCar non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COCar::Release(void)
{
  m_cRefs--;

  LOGF1("D: COCar::Release. New cRefs=%i.", m_cRefs);

  if (0 == m_cRefs)
  {
    // We artificially bump the main ref count to prevent reentrancy
    // via the main object destructor.  Not really needed in this
    // COCar but a good practice because we are aggregatable and
    // may at some point in the future add something entertaining like
    // some Releases to the COCar destructor.
    m_cRefs++;
    delete this;
  }

  return m_cRefs;
}


/*---------------------------------------------------------------------------
  COCar's nested implementation of the ICar interface including
  Constructor, Destructor, QueryInterface, AddRef, Release,
  Shift, Clutch, Speed, and Steer.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCar::CImpICar::CImpICar

  Summary:  Constructor for the CImpICar interface instantiation.

  Args:     COCar* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter)
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_cRefI, m_pBackObj, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COCar::CImpICar::CImpICar(
  COCar* pBackObj,
  IUnknown* pUnkOuter)
{
  // Init the Interface Ref Count (used for debugging only).
  m_cRefI = 0;

  // Init the Back Object Pointer to point to the parent object.
  m_pBackObj = pBackObj;

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
    LOG("D: COCar::CImpICar Constructor. Non-Aggregating.");
  }
  else
  {
    m_pUnkOuter = pUnkOuter;
    LOG("D: COCar::CImpICar Constructor. Aggregating.");
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCar::CImpICar::~CImpICar

  Summary:  Destructor for the CImpICar interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COCar::CImpICar::~CImpICar(void)
{
  LOG("D: COCar::CImpICar Destructor.");

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCar::CImpICar::QueryInterface

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
STDMETHODIMP COCar::CImpICar::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  LOG("D: COCar::CImpICar::QueryInterface. Delegating.");

  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCar::CImpICar::AddRef

  Summary:  The AddRef IUnknown member of this ICar interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: m_cRefI.

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COCar::CImpICar::AddRef(void)
{
  // Increment the Interface Reference Count.
  ++m_cRefI;

  LOGF1("D: COCar::CImpICar::Addref. Delegating. New cI=%i.", m_cRefI);

  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCar::CImpICar::Release

  Summary:  The Release IUnknown member of this ICar interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COCar::CImpICar::Release(void)
{
  // Decrement the Interface Reference Count.
  --m_cRefI;

  LOGF1("D: COCar::CImpICar::Release. Delegating. New cI=%i.", m_cRefI);

  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCar::CImpICar::Shift

  Summary:  The Shift member method of this ICar interface implementation.
            A simple empty method on a COCar COM object for tutorial
            purposes.  Presumably if this Car object were modeling
            a real Car then the Shift method would shift to the specified
            gear.

  Args:     short nGear
              0 - Neutral; 1 - 5 First 5 forward gears; 6 - Reverse.

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COCar::CImpICar::Shift(
               short nGear)
{
  LOGF1("D: COCar::CImpICar::Shift. Called. nGear=%i.",nGear);

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCar::CImpICar::Clutch

  Summary:  The Clutch member method of this ICar interface implementation.
            A simple empty method on a COCar COM object for tutorial
            purposes.  Presumably if this Car object were modeling
            a real Car then the Clutch method would engage the clutch the
            specified amount.

  Args:     short nEngaged)
              Percent clutch is engaged (0 to 100%).

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COCar::CImpICar::Clutch(
               short nEngaged)
{
  LOGF1("D: COCar::CImpICar::Clutch. Called. nEngaged=%i.",nEngaged);

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCar::CImpICar::Speed

  Summary:  The Speed member method of this ICar interface implementation.
            A simple empty method on a COCar COM object for tutorial
            purposes.  Presumably if this Car object were modeling
            a real Car then this method would accelerate/brake to bring
            the car to the specified speed.

  Args:     short nMph
              New speed in miles per hour.

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COCar::CImpICar::Speed(
               short nMph)
{
  LOGF1("D: COCar::CImpICar::Speed. Called. nMph=%i.",nMph);

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COCar::CImpICar::Steer

  Summary:  The Steer member method of this ICar interface implementation.
            A simple empty method on a COCar COM object for tutorial
            purposes.  Presumably if this Car object were modeling
            a real Car then the Steer method would set the steering
            angle of the Car.

  Args:     short nAngle)
              0 degrees straight ahead, -45 Full left, +45 Full right.

  Modifies: .

  Returns:  HRESULT
              NOERROR
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COCar::CImpICar::Steer(
               short nAngle)
{
  LOGF1("D: COCar::CImpICar::Steer. Called. nAngle=%i.",nAngle);

  return NOERROR;
}
