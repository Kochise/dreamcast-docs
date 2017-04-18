/*+==========================================================================
  File:      DRAWSINK.CPP

  Summary:   Implementation file for the CODrawPageSink COM Object Class.
             Connectable object notifications for drawing-related
             events are handled by CODrawPageSink.

             CODrawPageSink offers a main IUnknown standard interface and
             the IDrawPageSink custom interface (with the DrawPage related
             event features). This multiple interface COM Object Class is
             achieved via the technique of nested classes.  The
             implementation of the various interfaces are nested
             inside the CODrawPageSink Class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial PERCLIEN.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   CODrawPageSink.

  Functions: none.

  Origin:    5-24-97: atrent - Editor-inheritance from TEXTSINK.CPP in
             the PERCLIEN Tutorial Code Sample.

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
  We include IPAGES.H and PAGEGUID.H for the common Page-related
    Interface class, GUID, and CLSID specifications.
  We include GUIDRAW.H because it declares the class for the main C++
    object that can service the Sink events.
  We include DRAWSINK.H because it has the class CODrawPageSink
    declarations.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <apputil.h>
#include <ipages.h>
#include <pageguid.h>
#include "guidraw.h"
#include "drawsink.h"


/*---------------------------------------------------------------------------
  CODrawPageSink's implementation of its main COM object class including
  Constructor, Destructor, QueryInterface, AddRef, and Release.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPageSink::CODrawPageSink

  Summary:  CODrawPageSink Constructor. Note the member initializer:
            "m_ImpIDrawPageSink(this, pUnkOuter)" which is used to pass
            the 'this' and pUnkOuter pointers of this constructor function
            to the constructor in the instantiation of the implementation
            of the CImpIDrawPageSink interface (which is nested inside
            this present CODrawPageSink Object Class).

  Args:     IUnknown* pUnkOuter,
              Pointer to the the outer Unknown.  NULL means this COM Object
              is not being Aggregated.  Non NULL means it is being created
              on behalf of an outside COM object that is reusing it via
              aggregation.
            CGuiDraw* pGuiDraw)
              Pointer to the main C++ object that can service the
              DrawPageSink events.

  Modifies: m_cRefs, m_pUnkOuter, m_pGuiList.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CODrawPageSink::CODrawPageSink(
  IUnknown* pUnkOuter,
  CGuiDraw* pGuiDraw) :
  m_ImpIDrawPageSink(this, pUnkOuter)
{
  // Zero the COM object's reference count.
  m_cRefs = 0;

  // No AddRef necessary if non-NULL, as we're nested.
  m_pUnkOuter = pUnkOuter;

  // Assign the pointer to the Sink service C++ object.
  m_pGuiDraw = pGuiDraw;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPageSink::~CODrawPageSink

  Summary:  CODrawPageSink Destructor.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CODrawPageSink::~CODrawPageSink(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPageSink::QueryInterface

  Summary:  QueryInterface of the CODrawPageSink non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPageSink::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;

  *ppv = NULL;

  if (IID_IUnknown == riid)
    *ppv = this;
  else if (IID_IDrawPageSink == riid)
    *ppv = &m_ImpIDrawPageSink;

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
  Method:   CODrawPageSink::AddRef

  Summary:  AddRef of the CODrawPageSink non-delegating IUnknown
            implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CODrawPageSink::AddRef(void)
{
  ULONG cRefs;

  cRefs = ++m_cRefs;

  return cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPageSink::Release

  Summary:  Release of the CODrawPageSink non-delegating IUnknown
            implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CODrawPageSink::Release(void)
{
  ULONG cRefs;

  cRefs = --m_cRefs;

  if (0 == cRefs)
  {
    // We artificially bump the main ref count to prevent reentrancy
    // via the main object destructor.  Not really needed in this
    // CODrawPageSink but a good practice because we are aggregatable and
    // may at some point in the future add something entertaining like
    // some Releases to the CODrawPageSink destructor.
    m_cRefs++;
    delete this;
  }

  return cRefs;
}


/*---------------------------------------------------------------------------
  CODrawPageSink's nested implementation of the IDrawPageSink interface
  including Constructor, Destructor, QueryInterface, AddRef, Release,
  Loaded, Saved, Cleared, Resized, InkStart, InkDraw, and InkStop. Methods
  in this interface are called by COM objects on the server side to send
  notifications to the client.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPageSink::CImpIDrawPageSink::CImpIDrawPageSink

  Summary:  Constructor for the CImpIDrawPageSink interface instantiation.

  Args:     CODrawPageSink* pCO,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_pCO, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CODrawPageSink::CImpIDrawPageSink::CImpIDrawPageSink(
  CODrawPageSink* pCO,
  IUnknown* pUnkOuter)
{
  // Init the main object Pointer to point to the parent object.
  m_pCO = pCO;

  // Init the CImpIDrawPageSink interface's delegating Unknown pointer. We
  // use the main object pointer for IUnknown delegation here if we are
  // not being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpIDrawPageSink lifetime
  // is quaranteed by the lifetime of the parent object in which
  // CImpIDrawPageSink is nested.
  if (NULL == pUnkOuter)
    m_pUnkOuter = pCO;
  else
    m_pUnkOuter = pUnkOuter;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPageSink::CImpIDrawPageSink::~CImpIDrawPageSink

  Summary:  Destructor for the CImpIDrawPageSink interface instantiation.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CODrawPageSink::CImpIDrawPageSink::~CImpIDrawPageSink(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPageSink::CImpIDrawPageSink::QueryInterface

  Summary:  The QueryInterface IUnknown member of this IDrawPageSink
            interface implementation that delegates to m_pUnkOuter,
            whatever it is.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Returned by the delegated outer QueryInterface call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPageSink::CImpIDrawPageSink::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPageSink::CImpIDrawPageSink::AddRef

  Summary:  The AddRef IUnknown member of this IDrawPageSink interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CODrawPageSink::CImpIDrawPageSink::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPageSink::CImpIDrawPageSink::Release

  Summary:  The Release IUnknown member of this IDrawPageSink interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CODrawPageSink::CImpIDrawPageSink::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPageSink::CImpIDrawPageSink::Loaded

  Summary:  The CODrawPage object's ink drawing data was loaded from
            its storage.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPageSink::CImpIDrawPageSink::Loaded(
               void)
{
  HRESULT hr;

  // We have been notified that a load was done. Thus, a whole new array
  // of ink data must be displayed in a cleared window of this client.
  m_pCO->m_pGuiDraw->ClearWin();
  hr = m_pCO->m_pGuiDraw->PaintWin();

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPageSink::CImpIDrawPageSink::Saved

  Summary:  The CODrawPage object's drawing DrawPage data was saved to
            its persistent storage.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPageSink::CImpIDrawPageSink::Saved(
               void)
{
  HRESULT hr = E_NOTIMPL;

  // For future evolution.

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPageSink::CImpIDrawPageSink::Cleared

  Summary:  The CODrawPage was cleared of all content.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPageSink::CImpIDrawPageSink::Cleared(
               void)
{
  HRESULT hr = E_NOTIMPL;

  // For future evolution.

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPageSink::CImpIDrawPageSink::Resized

  Summary:  CODrawPage's drawing rectangle was resized by a client.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPageSink::CImpIDrawPageSink::Resized(
               SHORT nWidth,
               SHORT nHeight)
{
  HRESULT hr = E_NOTIMPL;

  // For future evolution.

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPageSink::CImpIDrawPageSink::InkStart

  Summary:  Client is being told to start a display ink drawing sequence.

  Args:     SHORT nX,
              X coordinate of the start point.
            SHORT nY,
              Y coordinate of the start point.
            SHORT nWidth,
              Ink Width in pixels.
            COLORREF crInkColor)
              RGB Ink color to be used in the subsequent inking sequence.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPageSink::CImpIDrawPageSink::InkStart(
               SHORT nX,
               SHORT nY,
               SHORT nWidth,
               COLORREF crInkColor)
{
  // Turn off ink saving to the CODrawPage object.
  m_pCO->m_pGuiDraw->InkSaving(FALSE);

  // Play the data back to the CGuiDraw for display only.
  m_pCO->m_pGuiDraw->InkWidth(nWidth);
  m_pCO->m_pGuiDraw->InkColor(crInkColor);
  m_pCO->m_pGuiDraw->InkStart(nX, nY);

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPageSink::CImpIDrawPageSink::InkDraw

  Summary:  Client is being told to draw/display ink drawing sequence data.

  Args:     SHORT nX,
              X coordinate of the start point.
            SHORT nY,
              Y coordinate of the start point.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPageSink::CImpIDrawPageSink::InkDraw(
               SHORT nX,
               SHORT nY)
{
  // Play the data back to the CGuiDraw for display only.
  m_pCO->m_pGuiDraw->InkDraw(nX, nY);

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPageSink::CImpIDrawPageSink::InkStop

  Summary:  Client is being told to stop an ink drawing sequence.

  Args:     SHORT nX,
              X coordinate of the start point.
            SHORT nY,
              Y coordinate of the start point.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPageSink::CImpIDrawPageSink::InkStop(
               SHORT nX,
               SHORT nY)
{
  // Stop the display play back of the data to the CGuiDraw.
  m_pCO->m_pGuiDraw->InkStop(nX, nY);

  // Turn Ink Data saving back on.
  m_pCO->m_pGuiDraw->InkSaving(TRUE);

  return NOERROR;
}
