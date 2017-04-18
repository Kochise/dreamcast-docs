/*+==========================================================================
  File:      SINK.CPP

  Summary:   Implementation file for the COPaperSink COM Object Class.
             Connectable object notifications are handled by COPaperSink.

             COPaperSink offers a main IUnknown interface and the custom
             IPaperSink interface (with the drawing Paper related event
             features). This multiple interface COM Object Class is
             achieved via the technique of nested classes.  The
             implementation of the IPaperSink interface is nested inside
             the COPaperSink Class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial DCOMDRAW.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   COPaperSink.

  Functions: none.

  Origin:    8-23-97: atrent - Editor-inheritance from BALL.CPP in
             the CONSERVE Tutorial Code Sample. [Revised]

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
  We include PAPINT.H and PAPGUIDS.H for the common paper-related
    Interface class, GUID, and CLSID specifications.
  We include GUIPAPER.H because it declares the class for the main C++
    object that can service the Sink events.
  We include SINK.H because it has the class COPaperSink declarations.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <apputil.h>
#include <papint.h>
#include <papguids.h>
#include "guipaper.h"
#include "sink.h"


/*---------------------------------------------------------------------------
  COPaperSink's implementation of its main COM object class including
  Constructor, Destructor, QueryInterface, AddRef, and Release.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaperSink::COPaperSink

  Summary:  COPaperSink Constructor. Note the member initializer:
            "m_ImpIPaperSink(this, pUnkOuter)" which is used to pass the
            'this' and pUnkOuter pointers of this constructor function to
            the constructor in the instantiation of the implementation of
            the CImpIPaperSink interface (which is nested inside this
            present COPaperSink Object Class).

  Args:     IUnknown* pUnkOuter,
              Pointer to the the outer Unknown.  NULL means this COM Object
              is not being Aggregated.  Non NULL means it is being created
              on behalf of an outside COM object that is reusing it via
              aggregation.
            CGuiPaper* pGuiPaper)
              Pointer to the main C++ object that can service the PaperSink
              events.

  Modifies: m_cRefs, m_pUnkOuter, m_pGuiPaper.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPaperSink::COPaperSink(
  IUnknown* pUnkOuter,
  CGuiPaper* pGuiPaper) :
  m_ImpIPaperSink(this, pUnkOuter)
{
  // Zero the COM object's reference count.
  m_cRefs = 0;

  // No AddRef necessary if non-NULL, as we're nested.
  m_pUnkOuter = pUnkOuter;

  // Assign the pointer to the Sink service C++ object.
  m_pGuiPaper = pGuiPaper;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaperSink::~COPaperSink

  Summary:  COPaperSink Destructor.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPaperSink::~COPaperSink(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaperSink::QueryInterface

  Summary:  QueryInterface of the COPaperSink non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaperSink::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;

  *ppv = NULL;

  if (IID_IUnknown == riid)
    *ppv = this;
  else if (IID_IPaperSink == riid)
    *ppv = &m_ImpIPaperSink;

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
  Method:   COPaperSink::AddRef

  Summary:  AddRef of the COPaperSink non-delegating IUnknown
            implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPaperSink::AddRef(void)
{
  ULONG cRefs;

  cRefs = ++m_cRefs;

  return cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaperSink::Release

  Summary:  Release of the COPaperSink non-delegating IUnknown
            implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPaperSink::Release(void)
{
  ULONG cRefs;

  cRefs = --m_cRefs;

  if (0 == cRefs)
  {
    // We artificially bump the main ref count to prevent reentrancy
    // via the main object destructor.  Not really needed in this
    // COPaperSink but a good practice because we are aggregatable and
    // may at some point in the future add something entertaining like
    // some Releases to the COPaperSink destructor.
    m_cRefs++;
    delete this;
  }

  return cRefs;
}


/*---------------------------------------------------------------------------
  COPaperSink's nested implementation of the IPaperSink interface
  including Constructor, Destructor, QueryInterface, AddRef, Release,
  Locked, Unlocked, Loaded, Saved, InkStart, InkDraw, InkStop, Erased,
  and Resized. Methods in this interface are called by COM objects on
  the server side to send notifications to the client.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaperSink::CImpIPaperSink::CImpIPaperSink

  Summary:  Constructor for the CImpIPaperSink interface instantiation.

  Args:     COPaperSink* pCO,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_pCO, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPaperSink::CImpIPaperSink::CImpIPaperSink(
  COPaperSink* pCO,
  IUnknown* pUnkOuter)
{
  // Init the Back Object Pointer to point to the parent object.
  m_pCO = pCO;

  // Init the CImpIPaperSink interface's delegating Unknown pointer.  We
  // use the Back Object pointer for IUnknown delegation here if we are
  // not being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpIPaperSink lifetime is
  // quaranteed by the lifetime of the parent object in which
  // CImpIPaperSink is nested.
  if (NULL == pUnkOuter)
    m_pUnkOuter = pCO;
  else
    m_pUnkOuter = pUnkOuter;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaperSink::CImpIPaperSink::~CImpIPaperSink

  Summary:  Destructor for the CImpIPaperSink interface instantiation.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPaperSink::CImpIPaperSink::~CImpIPaperSink(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaperSink::CImpIPaperSink::QueryInterface

  Summary:  The QueryInterface IUnknown member of this IPaperSink interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Returned by the delegated outer QueryInterface call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaperSink::CImpIPaperSink::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaperSink::CImpIPaperSink::AddRef

  Summary:  The AddRef IUnknown member of this IPaperSink interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPaperSink::CImpIPaperSink::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaperSink::CImpIPaperSink::Release

  Summary:  The Release IUnknown member of this IPaperSink interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPaperSink::CImpIPaperSink::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaperSink::CImpIPaperSink::Locked

  Summary:  The COPaper object was locked by a client.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaperSink::CImpIPaperSink::Locked(
               void)
{
  HRESULT hr = E_NOTIMPL;

  // For future evolution.

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaperSink::CImpIPaperSink::Unlocked

  Summary:  The COPaper object was Unlocked by a client.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaperSink::CImpIPaperSink::Unlocked(
               void)
{
  HRESULT hr = E_NOTIMPL;

  // For future evolution.

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaperSink::CImpIPaperSink::Loaded

  Summary:  The COPaper object's ink drawing data was loaded from a
            client's compound file.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaperSink::CImpIPaperSink::Loaded(
               void)
{
  HRESULT hr;

  // We have been notified that a load was done. Thus, a whole new array
  // of ink data must be displayed in a cleared window of this client.
  m_pCO->m_pGuiPaper->ClearWin();
  hr = m_pCO->m_pGuiPaper->PaintWin();

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaperSink::CImpIPaperSink::Saved

  Summary:  The COPaper object's drawing paper data was saved to a
            client's compound file.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaperSink::CImpIPaperSink::Saved(
               void)
{
  HRESULT hr = E_NOTIMPL;

  // For future evolution.

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaperSink::CImpIPaperSink::InkStart

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
STDMETHODIMP COPaperSink::CImpIPaperSink::InkStart(
                                            SHORT nX,
                                            SHORT nY,
                                            SHORT nWidth,
                                            COLORREF crInkColor)
{
  // Only echo drawing action if we are not the current Master.
  if (!m_pCO->m_pGuiPaper->Master())
  {
    // Play the data back to the CGuiPaper for display only.
    m_pCO->m_pGuiPaper->InkWidth(nWidth);
    m_pCO->m_pGuiPaper->InkColor(crInkColor);
    m_pCO->m_pGuiPaper->InkStart(nX, nY);
  }

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaperSink::CImpIPaperSink::InkDraw

  Summary:  Client is being told to draw/display ink drawing sequence data.

  Args:     SHORT nX,
              X coordinate of the start point.
            SHORT nY,
              Y coordinate of the start point.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaperSink::CImpIPaperSink::InkDraw(
                                            SHORT nX,
                                            SHORT nY)
{
  // Only echo drawing action if we are not the current Master.
  if (!m_pCO->m_pGuiPaper->Master())
  {
    // Play the data back to the CGuiPaper for display only.
    m_pCO->m_pGuiPaper->InkDraw(nX, nY);
  }

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaperSink::CImpIPaperSink::InkStop

  Summary:  Client is being told to stop an ink drawing sequence.

  Args:     SHORT nX,
              X coordinate of the start point.
            SHORT nY,
              Y coordinate of the start point.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaperSink::CImpIPaperSink::InkStop(
                                            SHORT nX,
                                            SHORT nY)
{
  // Only echo drawing action if we are not the current Master.
  if (!m_pCO->m_pGuiPaper->Master())
  {
    // Stop the play of the data back to the CGuiPaper for display.
    m_pCO->m_pGuiPaper->InkStop(nX, nY);
  }

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaperSink::CImpIPaperSink::Erased

  Summary:  The COPaper object's drawing paper data was erased by a client.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaperSink::CImpIPaperSink::Erased(
               void)
{
  HRESULT hr = E_FAIL;

  // Only echo drawing action if we are not the current Master.
  if (!m_pCO->m_pGuiPaper->Master())
    hr = m_pCO->m_pGuiPaper->Erase();

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaperSink::CImpIPaperSink::Resized

  Summary:  The COPaper object's drawing rectangle was resized by a client.

  Args:     LONG lWidth,
              Rectangle width in pixels.
            LONG lHeight)
              Rectangle height in pixels.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaperSink::CImpIPaperSink::Resized(
               LONG lWidth,
               LONG lHeight)
{
  HRESULT hr = E_FAIL;

  // Only echo drawing action if we are not the current Master.
  if (!m_pCO->m_pGuiPaper->Master())
    hr = m_pCO->m_pGuiPaper->Resize(lWidth, lHeight);

  return hr;
}
