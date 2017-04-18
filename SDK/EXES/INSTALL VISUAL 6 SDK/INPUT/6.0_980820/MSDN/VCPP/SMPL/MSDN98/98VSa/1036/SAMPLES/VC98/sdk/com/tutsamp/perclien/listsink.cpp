/*+==========================================================================
  File:      LISTSINK.CPP

  Summary:   Implementation file for the COPageListSink COM Object Class.
             Connectable object notifications of PageList events are
             handled by COPageListSink.

             COPageListSink offers a main IUnknown standard interface and
             the IPageListSink custom interface (with the PageList related
             event features). This multiple interface COM Object Class is
             achieved via the technique of nested classes.  The
             implementation of the IPageListSink interface is nested
             inside the COPageListSink Class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial PERCLIEN.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   COPageListSink.

  Functions: none.

  Origin:    5-20-97: atrent - Editor-inheritance from SINK.CPP in
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
  We include PAGFILE.H because it has the C++ class used for compound file
    storage of PageList data.
  We include LISTWIN.H because CGuiList creates and uses a CListWin to
    encapsulate the standard list box control.
  We include GUILIST.H because it declares the class for the main C++
    object that can service the Sink events.
  We include LISTSINK.H because of the class COPageListSink declarations.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <apputil.h>
#include <ipages.h>
#include <pageguid.h>
#include "pagefile.h"
#include "listwin.h"
#include "guilist.h"
#include "listsink.h"


/*---------------------------------------------------------------------------
  COPageListSink's implementation of its main COM object class including
  Constructor, Destructor, QueryInterface, AddRef, and Release.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageListSink::COPageListSink

  Summary:  COPageListSink Constructor. Note the member initializer:
            "m_ImpIPageListSink(this, pUnkOuter)" which is used to pass
            the 'this' and pUnkOuter pointers of this constructor function
            to the constructor in the instantiation of the implementation
            of the CImpIPageListSink interface (which is nested inside
            this present COPageListSink Object Class).

  Args:     IUnknown* pUnkOuter,
              Pointer to the the outer Unknown.  NULL means this COM Object
              is not being Aggregated.  Non NULL means it is being created
              on behalf of an outside COM object that is reusing it via
              aggregation.
            CGuiList* pGuiList)
              Pointer to the main C++ object that can service the
              PageListSink events.

  Modifies: m_cRefs, m_pUnkOuter, m_pGuiList.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPageListSink::COPageListSink(
  IUnknown* pUnkOuter,
  CGuiList* pGuiList) :
  m_ImpIPageListSink(this, pUnkOuter)
{
  // Zero the COM object's reference count.
  m_cRefs = 0;

  // No AddRef necessary if non-NULL, as we're nested.
  m_pUnkOuter = pUnkOuter;

  // Assign the pointer to the Sink service C++ object.
  m_pGuiList = pGuiList;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageListSink::~COPageListSink

  Summary:  COPageListSink Destructor.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPageListSink::~COPageListSink(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageListSink::QueryInterface

  Summary:  QueryInterface of the COPageListSink non-delegating
            IUnknown implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageListSink::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;

  *ppv = NULL;

  if (IID_IUnknown == riid)
    *ppv = this;
  else if (IID_IPageListSink == riid)
    *ppv = &m_ImpIPageListSink;

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
  Method:   COPageListSink::AddRef

  Summary:  AddRef of the COPageListSink non-delegating IUnknown
            implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPageListSink::AddRef(void)
{
  ULONG cRefs;

  cRefs = ++m_cRefs;

  return cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageListSink::Release

  Summary:  Release of the COPageListSink non-delegating IUnknown
            implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPageListSink::Release(void)
{
  ULONG cRefs;

  cRefs = --m_cRefs;

  if (0 == cRefs)
  {
    // We artificially bump the main ref count to prevent reentrancy
    // via the main object destructor.  Not really needed in this
    // COPageListSink but a good practice because we are aggregatable and
    // may at some point in the future add something entertaining like
    // some Releases to the COPageListSink destructor.
    m_cRefs++;
    delete this;
  }

  return cRefs;
}


/*---------------------------------------------------------------------------
  COPageListSink's nested implementation of the IPageListSink interface
  including Constructor, Destructor, QueryInterface, AddRef, Release,
  Loaded, Saved, Cleared, PageAdded, PageDeleted, and PageSet. Methods in
  this interface are called by COM objects on the server side to send
  event notifications to the client.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageListSink::CImpIPageListSink::CImpIPageListSink

  Summary:  Constructor for the CImpIPageListSink interface instantiation.

  Args:     COPageListSink* pCO,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_pCO, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPageListSink::CImpIPageListSink::CImpIPageListSink(
  COPageListSink* pCO,
  IUnknown* pUnkOuter)
{
  // Init the main object Pointer to point to the parent object.
  m_pCO = pCO;

  // Init the CImpIPageListSink interface's delegating Unknown pointer. We
  // use the main object pointer for IUnknown delegation here if we are
  // not being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpIPageListSink lifetime
  // is quaranteed by the lifetime of the parent object in which
  // CImpIPageListSink is nested.
  if (NULL == pUnkOuter)
    m_pUnkOuter = pCO;
  else
    m_pUnkOuter = pUnkOuter;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageListSink::CImpIPageListSink::~CImpIPageListSink

  Summary:  Destructor for the CImpIPageListSink interface instantiation.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPageListSink::CImpIPageListSink::~CImpIPageListSink(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageListSink::CImpIPageListSink::QueryInterface

  Summary:  The QueryInterface IUnknown member of this IPageListSink
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
STDMETHODIMP COPageListSink::CImpIPageListSink::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageListSink::CImpIPageListSink::AddRef

  Summary:  The AddRef IUnknown member of this IPageListSink interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPageListSink::CImpIPageListSink::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageListSink::CImpIPageListSink::Release

  Summary:  The Release IUnknown member of this IPageListSink interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPageListSink::CImpIPageListSink::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageListSink::CImpIPageListSink::Loaded

  Summary:  The COPageList object's list data was loaded from a
            client's compound file.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageListSink::CImpIPageListSink::Loaded(
               void)
{
  HRESULT hr;

  // We have been notified that a load was done. A whole new array of
  // PageList data must be displayed in the ListWin window of this client.
  hr = m_pCO->m_pGuiList->Show(0);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageListSink::CImpIPageListSink::Saved

  Summary:  The COPageList object's PageList data was saved to a
            client's compound file.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageListSink::CImpIPageListSink::Saved(
               void)
{
  HRESULT hr = E_NOTIMPL;

  // For future evolution.

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageListSink::CImpIPageListSink::Cleared

  Summary:  Another client has cleared the content of the PageList.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageListSink::CImpIPageListSink::Cleared(
               void)
{
  HRESULT hr;

  // We have been notified that a clear was done. An empty array of
  // PageList data must be displayed in the ListWin window of this client.
  hr = m_pCO->m_pGuiList->Show(0);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageListSink::CImpIPageListSink::PageAdded

  Summary:  A page was added to the page list.

  Args:     INT iPage
              The page number of the newly added page.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageListSink::CImpIPageListSink::PageAdded(
               INT iPage)
{
  HRESULT hr;

  // We have been notified that a new page was added. In this simple
  // sample app the entire array is reshown. A more efficient action
  // would be to call CListWin::InsertFmt to insert/add only the
  // list item that was added to the list.
  hr = m_pCO->m_pGuiList->Show(iPage);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageListSink::CImpIPageListSink::PageDeleted

  Summary:  A page was deleted from the page list.

  Args:     INT iPage
              Page number of the page that was deleted.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageListSink::CImpIPageListSink::PageDeleted(
               INT iPage)
{
  HRESULT hr;

  // We have been notified that a page was deleted. In this simple
  // sample app the entire array is reshown. A more efficient action
  // would be to explicitly call CListWin (using the LB_DELETESTRING
  // message) to only the delete the display line for the item
  // that was deleted in COPageList.
  hr = m_pCO->m_pGuiList->Show(iPage);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageListSink::CImpIPageListSink::PageSet

  Summary:  An existing page was retitled.

  Args:     INT iPage
              Page number of the page that was retitled.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageListSink::CImpIPageListSink::PageSet(
               INT iPage)
{
  HRESULT hr;

  // We have been notified that the current page was retitled.
  // In this simple sample app the entire array is reshown. A more
  // efficient action would be to explicitly call CListWin (using the
  // iPage given) to only re-display the display line that was changed.
  hr = m_pCO->m_pGuiList->Show(iPage);

  return hr;
}
