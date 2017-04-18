/*+==========================================================================
  File:      TEXTSINK.CPP

  Summary:   Implementation file for the COTextPageSink COM Object Class.
             Connectable object notifications for textpage-related
             events are handled by COTextPageSink.

             COTextPageSink offers a main IUnknown standard interface and
             the ITextPageSink custom interface (with the TextPage related
             event features). This multiple interface COM Object Class is
             achieved via the technique of nested classes.  The
             implementation of the ITextPageSink interface is nested
             inside the COTextPageSink Class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial PERCLIEN.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   COTextPageSink.

  Functions: none.

  Origin:    5-24-97: atrent - Editor-inheritance from SINK.CPP in
             the STOCLIEN Tutorial Code Sample. [Revised]

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
  We include TEXTWIN.H because CGuiText creates and uses a CTextWin to
    encapsulate the multiline text edit control.
  We include GUITEXT.H because it declares the class for the main C++
    object that can service the text page Sink events.
  We include TEXTSINK.H because it has the COTextPageSink class declaration.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <apputil.h>
#include <ipages.h>
#include <pageguid.h>
#include "textwin.h"
#include "guitext.h"
#include "textsink.h"


/*---------------------------------------------------------------------------
  COTextPageSink's implementation of its main COM object class including
  Constructor, Destructor, QueryInterface, AddRef, and Release.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPageSink::COTextPageSink

  Summary:  COTextPageSink Constructor. Note the member initializer:
            "m_ImpITextPageSink(this, pUnkOuter)" which is used to pass
            the 'this' and pUnkOuter pointers of this constructor function
            to the constructor in the instantiation of the implementation
            of the CImpITextPageSink interface (which is nested inside
            this present COTextPageSink Object Class).

  Args:     IUnknown* pUnkOuter,
              Pointer to the the outer Unknown.  NULL means this COM Object
              is not being Aggregated.  Non NULL means it is being created
              on behalf of an outside COM object that is reusing it via
              aggregation.
            CGuiList* pGuiList)
              Pointer to the main C++ object that can service the
              TextPageSink events.

  Modifies: m_cRefs, m_pUnkOuter, m_pGuiList.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COTextPageSink::COTextPageSink(
  IUnknown* pUnkOuter,
  CGuiText* pGuiText) :
  m_ImpITextPageSink(this, pUnkOuter)
{
  // Zero the COM object's reference count.
  m_cRefs = 0;

  // No AddRef necessary if non-NULL, as we're nested.
  m_pUnkOuter = pUnkOuter;

  // Assign the pointer to the Sink service C++ object.
  m_pGuiText = pGuiText;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPageSink::~COTextPageSink

  Summary:  COTextPageSink Destructor.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COTextPageSink::~COTextPageSink(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPageSink::QueryInterface

  Summary:  QueryInterface of the COTextPageSink non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COTextPageSink::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;

  *ppv = NULL;

  if (IID_IUnknown == riid)
    *ppv = this;
  else if (IID_ITextPageSink == riid)
    *ppv = &m_ImpITextPageSink;

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
  Method:   COTextPageSink::AddRef

  Summary:  AddRef of the COTextPageSink non-delegating IUnknown
            implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COTextPageSink::AddRef(void)
{
  ULONG cRefs;

  cRefs = ++m_cRefs;

  return cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPageSink::Release

  Summary:  Release of the COTextPageSink non-delegating IUnknown
            implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COTextPageSink::Release(void)
{
  ULONG cRefs;

  cRefs = --m_cRefs;

  if (0 == cRefs)
  {
    // We artificially bump the main ref count to prevent reentrancy
    // via the main object destructor.  Not really needed in this
    // COTextPageSink but a good practice because we are aggregatable and
    // may at some point in the future add something entertaining like
    // some Releases to the COTextPageSink destructor.
    m_cRefs++;
    delete this;
  }

  return cRefs;
}


/*---------------------------------------------------------------------------
  COTextPageSink's nested implementation of the ITextPageSink interface
  including Constructor, Destructor, QueryInterface, AddRef, Release,
  Loaded, Saved, Put, and Cleared. Methods in this interface are called by
  COM objects on the server side to send notifications to the client.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPageSink::CImpITextPageSink::CImpITextPageSink

  Summary:  Constructor for the CImpITextPageSink interface instantiation.

  Args:     COTextPageSink* pCO,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_pCO, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COTextPageSink::CImpITextPageSink::CImpITextPageSink(
  COTextPageSink* pCO,
  IUnknown* pUnkOuter)
{
  // Init the main object pointer to point to the parent object.
  m_pCO = pCO;

  // Init the CImpITextPageSink interface's delegating Unknown pointer. We
  // use the main object pointer for IUnknown delegation here if we are
  // not being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpITextPageSink lifetime
  // is quaranteed by the lifetime of the parent object in which
  // CImpITextPageSink is nested.
  if (NULL == pUnkOuter)
    m_pUnkOuter = pCO;
  else
    m_pUnkOuter = pUnkOuter;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPageSink::CImpITextPageSink::~CImpITextPageSink

  Summary:  Destructor for the CImpITextPageSink interface instantiation.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COTextPageSink::CImpITextPageSink::~CImpITextPageSink(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPageSink::CImpITextPageSink::QueryInterface

  Summary:  The QueryInterface IUnknown member of this ITextPageSink
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
STDMETHODIMP COTextPageSink::CImpITextPageSink::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPageSink::CImpITextPageSink::AddRef

  Summary:  The AddRef IUnknown member of this ITextPageSink interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COTextPageSink::CImpITextPageSink::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPageSink::CImpITextPageSink::Release

  Summary:  The Release IUnknown member of this ITextPageSink interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COTextPageSink::CImpITextPageSink::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPageSink::CImpITextPageSink::Loaded

  Summary:  The COTextPage object's text data was loaded from a client's
            compound file.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COTextPageSink::CImpITextPageSink::Loaded(
               void)
{
  HRESULT hr = E_NOTIMPL;

  // For future evolution.

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPageSink::CImpITextPageSink::Saved

  Summary:  The COTextPage object's text data was saved to a client's
            compound file.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COTextPageSink::CImpITextPageSink::Saved(
               void)
{
  HRESULT hr = E_NOTIMPL;

  // For future evolution.

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPageSink::CImpITextPageSink::Put

  Summary:  A client put new text data into the shared COTextPage.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COTextPageSink::CImpITextPageSink::Put(
               void)
{
  HRESULT hr = E_NOTIMPL;

  // For future evolution.

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPageSink::CImpITextPageSink::Cleared

  Summary:  A client cleared all text data in the shared COTextPage.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COTextPageSink::CImpITextPageSink::Cleared(
               void)
{
  HRESULT hr = E_NOTIMPL;

  // For future evolution.

  return hr;
}
