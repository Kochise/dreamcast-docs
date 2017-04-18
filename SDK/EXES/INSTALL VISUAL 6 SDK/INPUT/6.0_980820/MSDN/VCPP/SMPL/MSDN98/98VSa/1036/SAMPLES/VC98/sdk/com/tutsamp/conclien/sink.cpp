/*+==========================================================================
  File:      SINK.CPP

  Summary:   Implementation file for the COBallSink COM Object Class.

             COBallSink offers a main IUnknown interface and the IBallSink
             interface (with the Moving Ball related event features).
             This multiple interface COM Object Class is achieved via the
             technique of nested classes.  The implementation of the
             IBallSink interface is nested inside the COBallSink Class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial CONCLIEN.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   COBallSink.

  Functions: none.

  Origin:    6-3-96: atrent - Editor-inheritance from BALL.CPP in
             the CONSERVE Tutorial Code Sample.

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
  We include OLECTL.H because it has definitions for connectable objects.
  We include APPUTIL.H because we will be building this application using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include IBALL.H and BALLGUID.H for the common Ball-related Interface
    class, GUID, and CLSID specifications.
  We include GUIBALL.H because it declares the class for the main C++
    object that can service the Sink events.
  We include SINK.H because it has the class COBallSink declarations.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <apputil.h>
#include <iball.h>
#include <ballguid.h>
#include "guiball.h"
#include "sink.h"


/*---------------------------------------------------------------------------
  COBallSink's implementation of its main COM object class including
  Constructor, Destructor, QueryInterface, AddRef, and Release.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBallSink::COBallSink

  Summary:  COBallSink Constructor. Note the member initializer:
            "m_ImpIBallSink(this, pUnkOuter)" which is used to pass the
            'this' and pUnkOuter pointers of this constructor function to
            the constructor in the instantiation of the implementation of
            the CImpIBallSink interface (which is nested inside this
            present COBallSink Object Class).

  Args:     IUnknown* pUnkOuter,
              Pointer to the the outer Unknown.  NULL means this COM Object
              is not being Aggregated.  Non NULL means it is being created
              on behalf of an outside COM object that is reusing it via
              aggregation.
            CGuiBall* pGuiBall)
              Pointer to the main C++ object that can service the BallSink
              events.

  Modifies: m_cRefs, m_pUnkOuter, m_pGuiBall.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COBallSink::COBallSink(
  IUnknown* pUnkOuter,
  CGuiBall* pGuiBall) :
  m_ImpIBallSink(this, pUnkOuter)
{
  // Zero the COM object's reference count.
  m_cRefs = 0;

  // No AddRef necessary if non-NULL, as we're nested.
  m_pUnkOuter = pUnkOuter;

  // Assign the pointer to the Sink service C++ object.
  m_pGuiBall = pGuiBall;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBallSink::~COBallSink

  Summary:  COBallSink Destructor.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COBallSink::~COBallSink(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBallSink::QueryInterface

  Summary:  QueryInterface of the COBallSink non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Modifies: .

  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COBallSink::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;

  *ppv = NULL;

  if (IID_IUnknown == riid)
    *ppv = this;
  else if (IID_IBallSink == riid)
    *ppv = &m_ImpIBallSink;

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
  Method:   COBallSink::AddRef

  Summary:  AddRef of the COBallSink non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COBallSink::AddRef(void)
{
  ULONG cRefs;

  cRefs = ++m_cRefs;

  return cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBallSink::Release

  Summary:  Release of the COBallSink non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COBallSink::Release(void)
{
  ULONG cRefs;

  cRefs = --m_cRefs;

  if (0 == cRefs)
  {
    // We artificially bump the main ref count to prevent reentrancy
    // via the main object destructor.  Not really needed in this
    // COBallSink but a good practice because we are aggregatable and
    // may at some point in the future add something entertaining like
    // some Releases to the COBallSink destructor.
    m_cRefs++;
    delete this;
  }

  return cRefs;
}


/*---------------------------------------------------------------------------
  COBallSink's nested implementation of the IBallSink interface including
  Constructor, Destructor, QueryInterface, AddRef, Release, Reset, Move,
  and GetBall. This interface implementation also has internal methods
  that are not particulary intended for outside clients: GetDimensions,
  SetDimensions, GetDirection, SetDirection, GetPosition, SetPostion,
  CheckBounce, and FindThread. The IBallSink interface only provides client
  access to the IUnknown methods and the Reset, Move, and GetBall methods.
  Some or all of these internal methods could be exposed by the IBallSink
  interface by adding them to the IBallSink declaration in IBALL.H.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBallSink::CImpIBallSink::CImpIBallSink

  Summary:  Constructor for the CImpIBallSink interface instantiation.

  Args:     COBallSink* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_pBackObj, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COBallSink::CImpIBallSink::CImpIBallSink(
  COBallSink* pBackObj,
  IUnknown* pUnkOuter)
{
  // Init the Back Object Pointer to point to the parent object.
  m_pBackObj = pBackObj;

  // Init the CImpIBallSink interface's delegating Unknown pointer.  We
  // use the Back Object pointer for IUnknown delegation here if we are
  // not being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpIBallSink lifetime is
  // quaranteed by the lifetime of the parent object in which
  // CImpIBallSink is nested.
  if (NULL == pUnkOuter)
    m_pUnkOuter = pBackObj;
  else
    m_pUnkOuter = pUnkOuter;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBallSink::CImpIBallSink::~CImpIBallSink

  Summary:  Destructor for the CImpIBallSink interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COBallSink::CImpIBallSink::~CImpIBallSink(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBallSink::CImpIBallSink::QueryInterface

  Summary:  The QueryInterface IUnknown member of this IBallSink interface
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
STDMETHODIMP COBallSink::CImpIBallSink::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBallSink::CImpIBallSink::AddRef

  Summary:  The AddRef IUnknown member of this IBallSink interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COBallSink::CImpIBallSink::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBallSink::CImpIBallSink::Release

  Summary:  The Release IUnknown member of this IBallSink interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COBallSink::CImpIBallSink::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBallSink::CImpIBallSink::BounceBottom

  Summary:  Perform actions appropriate for when the ball bounces against
            the bottom boundary. For example, ask GUI to make a sound.

  Args:     void

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COBallSink::CImpIBallSink::BounceBottom(
               void)
{
  HRESULT hr = NOERROR;

  // Ask the GUI Ball to issue an appropriate sound indicating the ball
  // bouncing off the Bottom boundary.
  m_pBackObj->m_pGuiBall->BounceBottom();

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBallSink::CImpIBallSink::BounceLeft

  Summary:  Perform actions appropriate for when the ball bounces against
            the Left boundary. For example, ask GUI to make a sound.

  Args:     void

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COBallSink::CImpIBallSink::BounceLeft(
               void)
{
  HRESULT hr = NOERROR;

  // Ask the GUI Ball to issue an appropriate sound indicating the ball
  // bouncing off the Side boundary.
  m_pBackObj->m_pGuiBall->BounceSide();

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBallSink::CImpIBallSink::BounceRight

  Summary:  Perform actions appropriate for when the ball bounces against
            the right boundary. For example, ask GUI to make a sound.

  Args:     void

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COBallSink::CImpIBallSink::BounceRight(
               void)
{
  HRESULT hr = NOERROR;

  // Ask the GUI Ball to issue an appropriate sound indicating the ball
  // bouncing off the Side boundary.
  m_pBackObj->m_pGuiBall->BounceSide();

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBallSink::CImpIBallSink::BounceTop

  Summary:  Perform actions appropriate for when the ball bounces against
            the Top boundary. For example, ask GUI to make a sound.

  Args:     void

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COBallSink::CImpIBallSink::BounceTop(
               void)
{
  HRESULT hr = NOERROR;

  // Ask the GUI Ball to issue an appropriate sound indicating the ball
  // bouncing off the Top boundary.
  m_pBackObj->m_pGuiBall->BounceTop();

  return hr;
}
