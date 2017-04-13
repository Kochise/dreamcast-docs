/*+==========================================================================
  File:      PAGELIST.CPP

  Summary:   Implementation file for the COPageList COM Object Class (for
             connectable COPageList COM Objects). COPageList encapsulates
             into a persistent COM object the management of a page list.
             The list holds items that represent pages of user-editable
             information. Currently, two page types are supported in this
             sample: Text pages and Drawing pages. The client can use the
             custom IPageList interface to perform such operations on the
             list as: Get a list item, Set a list item, Add an item to the
             list, Delete an item from the list, and Clear the list.
             COPageList objects expose the IPersistStream interface and
             thus support its method of stream persistence for the list
             data. This persistence support is covered in detail in
             PERSERVE.HTM.

             Connectable object technology is used in COPageList to notify
             connected clients of various events like when a page item is
             added to the list.

             COPageList offers a main standard IUnknown interface (basic
             COM object features), the standard IConnectionPointContainer
             interface (connectable COM object features), the standard
             IPersistStream interface (stream persistence features), and
             the custom IPageList interface (PageList related features).
             This multiple interface COM Object Class is achieved via the
             technique of nested classes.  The implementations of the
             various interfaces are nested inside the COPageList Class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial PERSERVE.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   COPageList.

  Functions: none.

  Origin:    2-5-97: atrent - Editor-inheritance from PAPER.CPP in
             the STOSERVE Tutorial Code Sample.

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
  We include IPAGES.H and PAGEGUID.H for the common PageList-related
    Interface class, GUID, and CLSID specifications.
  We include SERVER.H because it has internal class declarations for
    the server's control object.
  We include CONNECT.H for object class declarations for the various
    connection point and connection COM objects used in PERSERVE.
  We include PAGELIST.H because it has the COPageList class declarations.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <apputil.h>
#include <ipages.h>
#include <pageguid.h>
#include "server.h"
#include "connect.h"
#include "pagelist.h"


/*---------------------------------------------------------------------------
  COPageList's implementation of its main COM object class including
  Constructor, Destructor, QueryInterface, AddRef, and Release.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::COPageList

  Summary:  COPageList Constructor. Note the member initializer:
            "m_ImpIPageList(this, pUnkOuter)" which is used to pass the
            'this' and pUnkOuter pointers of the constructor function to
            the constructor in the instantiation of the implementation of
            the CImpIPageList interface (which is nested inside this
            present COPageList Object Class). Same technique is used for
            the other nested interface implementations.

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
COPageList::COPageList(
  IUnknown* pUnkOuter,
  CServer* pServer) :
  m_ImpIPageList(this, pUnkOuter),
  m_ImpIPersistStream(this, pUnkOuter),
  m_ImpIConnectionPointContainer(this, pUnkOuter)
{
  UINT i;

  // Zero the COM object's reference count.
  m_cRefs = 0;

  // No AddRef necessary if non-NULL, as we're nested.
  m_pUnkOuter = pUnkOuter;

  // Assign the pointer to the server control object.
  m_pServer = pServer;

  // Null all entries in the connection point array.
  for (i=0; i<MAX_CONNECTION_POINTS; i++)
    m_aConnectionPoints[i] = NULL;

  // Now initialize the PageList itself.
  m_lPageListEnd = 0;
  m_lPageListMax = 0;
  m_paPageList   = NULL;
  m_bDirty       = TRUE;
  m_ClassID      = CLSID_PageList;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::~COPageList

  Summary:  COPageList Destructor.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPageList::~COPageList(void)
{
  UINT i;
  IConnectionPoint* pIConnectionPoint;
  PAGEITEM* paPageList;

  // Do final release of the connection point objects.
  // If this isn't the final release, then the client has an outstanding
  // unbalanced reference to a connection point and a memory leak may
  // likely result because the host COPageList object is now going away yet
  // a connection point for this host object will not end up deleting
  // itself (and its connections array).
  for (i=0; i<MAX_CONNECTION_POINTS; i++)
  {
    pIConnectionPoint = m_aConnectionPoints[i];
    RELEASE_INTERFACE(pIConnectionPoint);
  }

  // NULL the pointer first and then delete the entire PageList array.
  paPageList = m_paPageList;
  m_paPageList = NULL;
  if (NULL != paPageList)
    delete [] paPageList;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::Init

  Summary:  COPageList initialization method.  Create any necessary
            arrays, structures, and subordinate objects. In this case the
            COM object is initialized as a connectable object.

  Args:     void

  Modifies: m_aConnectionPoints.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COPageList::Init(void)
{
  HRESULT hr = NOERROR;
  COConnectionPoint* pCOConnPt;

  // Rig this COPageList COM object to be connectable. Assign the
  // connection point array. This object's connection points are
  // determined at compile time--it currently has only one connection
  // point: the CONNPOINT_PAGELISTSINK connection point. Create a
  // connection point object for this and assign it into the array. This
  // array could easily grow to support additional connection points in
  // the future.

  // First try creating a new connection point object. Pass 'this' as the
  // pHostObj pointer used by the connection point to pass its AddRef and
  // Release calls back to the host connectable object.
  pCOConnPt = new COConnectionPoint(this);
  if (NULL != pCOConnPt)
  {
    // If creation succeeded then initialize it (including creating
    // its initial dynamic connection array).
    hr = pCOConnPt->Init(IID_IPageListSink);

    // If the init succeeded then use QueryInterface to obtain the
    // IConnectionPoint interface on the new connection point object.
    // The interface pointer is assigned directly into the
    // connection point array. The QI also does the needed AddRef.
    if (SUCCEEDED(hr))
    {
      hr = pCOConnPt->QueryInterface(
             IID_IConnectionPoint,
             (PPVOID)&m_aConnectionPoints[CONNPOINT_PAGELISTSINK]);
      if (SUCCEEDED(hr))
      {
        // Build the initial empty dynamic array of PageList Items.
        hr = Clear();

        // Mark new empty Page List as clean.
        m_bDirty = FALSE;
      }
    }

    if (FAILED(hr))
      delete pCOConnPt;
  }
  else
    hr = E_OUTOFMEMORY;

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::QueryInterface

  Summary:  QueryInterface of the COPageList non-delegating IUnknown
            implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageList::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;

  *ppv = NULL;

  if (IID_IUnknown == riid)
    *ppv = this;
  else if (IID_IConnectionPointContainer == riid)
    *ppv = &m_ImpIConnectionPointContainer;
  else if (IID_IPersistStream == riid)
    *ppv = &m_ImpIPersistStream;
  else if (IID_IPageList == riid)
    *ppv = &m_ImpIPageList;

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
  Method:   COPageList::AddRef

  Summary:  AddRef of the COPageList non-delegating IUnknown implementation.

  Args:     void

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPageList::AddRef(void)
{
  ULONG cRefs;

  cRefs = ++m_cRefs;

  return cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::Release

  Summary:  Release of the COPageList non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPageList::Release(void)
{
  ULONG cRefs;

  cRefs = --m_cRefs;

  if (0 == cRefs)
  {
    // We've reached a zero reference count for this COM object.
    // So we tell the server housing to decrement its global object
    // count so that the server will be unloaded if appropriate.
    if (NULL != m_pServer)
      m_pServer->ObjectsDown();

    // We artificially bump the main ref count to prevent reentrancy
    // via the main object destructor.  Not really needed in this
    // COPageList but a good practice because we are aggregatable and
    // may at some point in the future add something entertaining like
    // some Releases to the COPageList destructor. We relinquish thread
    // ownership of this object prior to deleting it--a good practice.
    m_cRefs++;
    delete this;
  }

  return cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::NotifySinks

  Summary:  Internal utility method of this COM object used to fire event
            notification calls to all listening connection sinks in the
            clients.

  Args:     PAGELIST_EVENT PageListEvent
              Type of notification event.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COPageList::NotifySinks(
       PAGELIST_EVENT PageListEvent,
       INT iPage)
{
  HRESULT hr = NOERROR;
  IConnectionPoint* pIConnectionPoint;
  IEnumConnections* pIEnum;
  CONNECTDATA ConnData;

  // If there was a PageList event, broadcast appropriate notifications to
  // all Sinks connected to each connection point.
  if (PAGELIST_EVENT_NONE != PageListEvent)
  {
    // Here is the section for the PageListSink connection point--currently
    // this is the only connection point offered by COPageList objects.
    pIConnectionPoint = m_aConnectionPoints[CONNPOINT_PAGELISTSINK];
    if (NULL != pIConnectionPoint)
    {
      pIConnectionPoint->AddRef();
      hr = pIConnectionPoint->EnumConnections(&pIEnum);
      if (SUCCEEDED(hr))
      {
        // Loop thru the connection point's connections and if the
        // listening connection supports IPageListSink (ie, PageListSink
        // events) then dispatch the PageListEvent event notification to
        // that sink.
        while (NOERROR == pIEnum->Next(1, &ConnData, NULL))
        {
          IPageListSink* pIPageListSink;

          hr = ConnData.pUnk->QueryInterface(
                                IID_IPageListSink,
                                (PPVOID)&pIPageListSink);
          if (SUCCEEDED(hr))
          {
            switch (PageListEvent)
            {
              case PAGELIST_EVENT_LOADED:
                pIPageListSink->Loaded();
                break;
              case PAGELIST_EVENT_SAVED:
                pIPageListSink->Saved();
                break;
              case PAGELIST_EVENT_CLEARED:
                pIPageListSink->Cleared();
                break;
              case PAGELIST_EVENT_PAGEADDED:
                pIPageListSink->PageAdded(iPage);
                break;
              case PAGELIST_EVENT_PAGEDELETED:
                pIPageListSink->PageDeleted(iPage);
                break;
              case PAGELIST_EVENT_PAGESET:
                pIPageListSink->PageSet(iPage);
                break;
              default:
                break;
            }
            pIPageListSink->Release();
          }
          ConnData.pUnk->Release();
        }
        pIEnum->Release();
      }
      pIConnectionPoint->Release();
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::Clear

  Summary:  Internal utility method of this COM object used to clear
            the PageList array.

  Args:     none.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COPageList::Clear(
          void)
{
  HRESULT hr = E_FAIL;
  PAGEITEM* paPageList;

  // Allocate new array space for a fresh empty Page List array.
  paPageList = new PAGEITEM[(LONG)(PAGELIST_ALLOC_INIT)];
  if (NULL != paPageList)
  {
    // Zero the array.
    memset(paPageList, 0, PAGELIST_ALLOC_INIT * sizeof(PAGEITEM));

    // New array is ready--delete the old array.
    if (NULL != m_paPageList)
      delete [] m_paPageList;

    // Rig the PageList to use the new array.
    m_paPageList = paPageList;
    m_lPageListMax = PAGELIST_ALLOC_INIT;
    m_lPageListEnd = 0;

    // Zero the PageList Properties structure. Init the PageList version.
    memset(&m_PageListProps, 0, sizeof(PAGELISTPROPS));
    m_PageListProps.lPageListVersion = PAGELIST_VERSION10;

    // Mark PageList as dirty.
    m_bDirty = TRUE;
    hr = NOERROR;
  }
  else
    hr = E_OUTOFMEMORY;

  return hr;
}


/*---------------------------------------------------------------------------
  COPageList's nested implementation of the COM standard
  IConnectionPointContainer interface including Constructor, Destructor,
  QueryInterface, AddRef, Release, FindConnectionPoint, and
  EnumConnectionPoints.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIConnectionPointContainer
              ::CImpIConnectionPointContainer

  Summary:  Constructor for the CImpIConnectionPointContainer interface
            instantiation.

  Args:     COPageList* pCO,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_pCO, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPageList::CImpIConnectionPointContainer::CImpIConnectionPointContainer(
  COPageList* pCO,
  IUnknown* pUnkOuter)
{
  // Init the Main Object Pointer to point to the parent object.
  m_pCO = pCO;

  // Init the CImpIConnectionPointContainer interface's delegating Unknown
  // pointer.  We use the Main Object pointer for IUnknown delegation here
  // if we are not being aggregated.  If we are being aggregated we use
  // the supplied pUnkOuter for IUnknown delegation.  In either case the
  // pointer assignment requires no AddRef because the
  // CImpIConnectionPointContainer lifetime is quaranteed by the lifetime
  // of the parent object in which CImpIConnectionPointContainer is
  // nested.
  if (NULL == pUnkOuter)
    m_pUnkOuter = pCO;
  else
    m_pUnkOuter = pUnkOuter;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIConnectionPointContainer
              ::~CImpIConnectionPointContainer

  Summary:  Destructor for the CImpIConnectionPointContainer interface
            instantiation.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPageList::CImpIConnectionPointContainer::~CImpIConnectionPointContainer(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIConnectionPointContainer::QueryInterface

  Summary:  The QueryInterface IUnknown member of this interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
              Returned by the delegated outer QueryInterface call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageList::CImpIConnectionPointContainer::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIConnectionPointContainer::AddRef

  Summary:  The AddRef IUnknown member of this IPageList interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPageList::CImpIConnectionPointContainer::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIConnectionPointContainer::Release

  Summary:  The Release IUnknown member of this interface implementation
            that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPageList::CImpIConnectionPointContainer::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIConnectionPointContainer::FindConnectionPoint

  Summary:  Given an IID for a connection point sink find and return the
            interface pointer for that connection point sink.

  Args:     REFIID riid
              Reference to an IID
            IConnectionPoint** ppConnPt
              Address of the caller's IConnectionPoint interface pointer
              variable that will receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageList::CImpIConnectionPointContainer::FindConnectionPoint(
               REFIID riid,
               IConnectionPoint** ppConnPt)
{
  HRESULT hr = E_NOINTERFACE;
  IConnectionPoint* pIConnPt;

  // NULL the output variable.
  *ppConnPt = NULL;

  pIConnPt = m_pCO->m_aConnectionPoints[CONNPOINT_PAGELISTSINK];
  if (NULL != pIConnPt)
  {
    // This connectable COPageList object currently has only the
    // PageList Sink connection point. If the associated interface is
    // requested, use QI to get the Connection Point interface and
    // perform the needed AddRef.
    if (IID_IPageListSink == riid)
      hr = pIConnPt->QueryInterface(
                       IID_IConnectionPoint,
                       (PPVOID)ppConnPt);
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIConnectionPointContainer::EnumConnectionPoints

  Summary:  Return Enumerator for the connectable object's contained
            connection points.

  Args:     IEnumConnectionPoints** ppIEnum
              Address of the caller's Enumerator interface pointer
              variable. An output variable that will receive a pointer to
              the connection point enumerator COM object.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageList::CImpIConnectionPointContainer::EnumConnectionPoints(
               IEnumConnectionPoints** ppIEnum)
{
  HRESULT hr = NOERROR;
  IConnectionPoint* aConnPts[MAX_CONNECTION_POINTS];
  COEnumConnectionPoints* pCOEnum;
  UINT i;

  // Zero the output interface pointer.
  *ppIEnum = NULL;

  // Make a copy on the stack of the array of connection point
  // interfaces. The copy is used below in the creation of the new
  // Enumerator object.
  for (i=0; i<MAX_CONNECTION_POINTS; i++)
    aConnPts[i] = (IConnectionPoint*)m_pCO->m_aConnectionPoints[i];

  // Create a Connection Point enumerator COM object for the connection
  // points offered by this COPageList object. Pass 'this' to be used to
  // hook the lifetime of the host object to the life time of this
  // enumerator object.
  pCOEnum = new COEnumConnectionPoints(this);
  if (NULL != pCOEnum)
  {
    // Use the array copy to Init the new Enumerator COM object.
    // Set the initial Enumerator index to 0.
    hr = pCOEnum->Init(MAX_CONNECTION_POINTS, aConnPts, 0);
    if (SUCCEEDED(hr))
    {
      // QueryInterface to return the requested interface pointer.
      // An AddRef will be conveniently done by the QI.
      if (SUCCEEDED(hr))
        hr = pCOEnum->QueryInterface(
                        IID_IEnumConnectionPoints,
                        (PPVOID)ppIEnum);
    }
  }
  else
    hr = E_OUTOFMEMORY;

  return hr;
}


/*---------------------------------------------------------------------------
  COPageList's nested implementation of the COM standard
  IPersistStream interface including Constructor, Destructor,
  QueryInterface, AddRef, Release, GetClassID, IsDirty, Load, Save,
  and GetSizeMax.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPersistStream::CImpIPersistStream

  Summary:  Constructor for the CImpIPersistStream interface
            instantiation.

  Args:     COPageList* pCO,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_pCO, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPageList::CImpIPersistStream::CImpIPersistStream(
  COPageList* pCO,
  IUnknown* pUnkOuter)
{
  // Init the Back Object Pointer to point to the parent object.
  m_pCO = pCO;

  // Init the CImpIPersistStream interface's delegating Unknown
  // pointer.  We use the Main Object pointer for IUnknown delegation here
  // if we are not being aggregated.  If we are being aggregated we use
  // the supplied pUnkOuter for IUnknown delegation.  In either case the
  // pointer assignment requires no AddRef because the
  // pIPersistStream lifetime is quaranteed by the lifetime of the
  // parent object in which CImpIPersistStream is nested.
  if (NULL == pUnkOuter)
    m_pUnkOuter = pCO;
  else
    m_pUnkOuter = pUnkOuter;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPersistStream::~CImpIPersistStream

  Summary:  Destructor for the CImpIPersistStreamIint interface
            instantiation.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPageList::CImpIPersistStream::~CImpIPersistStream(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPersistStream::QueryInterface

  Summary:  The QueryInterface IUnknown member of this interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
              Returned by the delegated outer QueryInterface call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageList::CImpIPersistStream::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPersistStream::AddRef

  Summary:  The AddRef IUnknown member of this interface implementation
            that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPageList::CImpIPersistStream::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPersistStream::Release

  Summary:  The Release IUnknown member of this interface implementation
            that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPageList::CImpIPersistStream::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPersistStream::GetClassID

  Summary:  A method inherited from IPersist. Get the Class ID of this
            COM object.

  Args:     CLSID* pClassID
              [out] Address of caller's CLSID variable to hold Class ID.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageList::CImpIPersistStream::GetClassID(
               CLSID* pClassID)
{
  HRESULT hr = E_POINTER;

  if (NULL != pClassID)
  {
    // Use overloaded '=' operator to copy the Class ID.
    *pClassID = m_pCO->m_ClassID;
    hr = NOERROR;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPersistStream::IsDirty

  Summary:  Called to determine if changes were made to this COM object's
            data since it was last loaded, initialized, or saved.

  Args:     none.

  Returns:  HRESULT
              Standard result code. S_OK if dirty; S_FALSE if not.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageList::CImpIPersistStream::IsDirty(
               void)
{
  HRESULT hr = E_FAIL;

  hr = m_pCO->m_bDirty ? S_OK : S_FALSE;

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPersistStream::Load

  Summary:  Asks this COM object to load its persistent data from the
            specified stream at the current seek pointer. This function
            assumes the seek pointer is the same as it was before Save
            was last called. This function must leave the seek pointer
            the same as it was when Save was last completed regardless
            of success or failure. This function should not store a copy
            of pIStream in the COM object and should release it when done.

            Load is called when this COM object already has a persistent
            state stored in a stream. Notifies all other connected clients
            when the load is complete.

  Args:     IStream* pIStream
              IStream interface pointer for stream to load from.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageList::CImpIPersistStream::Load(
               IStream* pIStream)
{
  HRESULT hr = E_POINTER;
  PAGEITEM* paPageList;
  ULONG ulToRead, ulReadIn;
  LONG lNewArraySize;
  PAGELISTPROPS NewProps;

  if (NULL != pIStream)
  {
    // We have the PageList data stream. First read the
    // PageList Properties.
    ulToRead = sizeof(PAGELISTPROPS);
    hr = pIStream->Read(
                     &NewProps,
                     ulToRead,
                     &ulReadIn);
    if (SUCCEEDED(hr) && ulToRead != ulReadIn)
      hr = E_FAIL;
    if (SUCCEEDED(hr))
    {
      // Deal with the different PageList versions.
      switch (NewProps.lPageListVersion)
      {
        case PAGELIST_VERSION10:
          // Allocate a page list array big enough--add some extra
          // for later expansion by user.
          lNewArraySize = NewProps.lPageListSize + PAGELIST_ALLOC;
          paPageList = new PAGEITEM[(LONG) lNewArraySize];
          if (NULL != paPageList)
          {
            // Delete the entire old Page List array.
            if (NULL != m_pCO->m_paPageList)
              delete [] m_pCO->m_paPageList;

            // Assign the new array.
            m_pCO->m_paPageList = paPageList;
            m_pCO->m_lPageListMax = lNewArraySize;

            // Now read the complete array of Page List items.
            ulToRead = NewProps.lPageListSize * sizeof(PAGEITEM);
            hr = pIStream->Read(m_pCO->m_paPageList, ulToRead, &ulReadIn);
            if (SUCCEEDED(hr) && ulToRead != ulReadIn)
              hr = E_FAIL;
            if (SUCCEEDED(hr))
            {
              // Rig COPageList to use the PAGELISTPROPS info.
              m_pCO->m_lPageListEnd = NewProps.lPageListSize - 1;

              // Copy the new properties into current properties.
              memcpy(
                &m_pCO->m_PageListProps,
                &NewProps,
                sizeof(PAGELISTPROPS));
            }
          }
          else
            hr = E_OUTOFMEMORY;
          break;
        default:
          hr = E_FAIL;  // Bad version.
          break;
      }
    }
  }

  // Notify all other connected clients that PageList is now loaded.
  // If we didn't load then clear to a safe, empty Page List array.
  if (SUCCEEDED(hr))
    m_pCO->NotifySinks(PAGELIST_EVENT_LOADED,0);
  else
    m_pCO->Clear();

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPersistStream::Save

  Summary:  Called to save the persistent data of this COM object to a
            stream using the specified IStream interface. This call stores
            data from the current seek pointer offset. On exit from this
            method the seek pointer is assumed to be at the end of the
            data saved. This allows a series of contiguous persistent
            objects to be saved into the same stream. Notifies all other
            connected clients when the save is complete.

  Args:     IStream* pIStream
              IStream interface pointer for stream to load from.
            BOOL bClearDirty
              Determines if this method should clear the COM object's
              dirty flag. If bClearDirty is TRUE then clear the dirty
              flag.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageList::CImpIPersistStream::Save(
               IStream* pIStream,
               BOOL bClearDirty)
{
  HRESULT hr = E_POINTER;
  ULONG ulToWrite, ulWritten;

  if (NULL != pIStream)
  {
    // Got a stream. Now write data into it.
    // First write PAGELISTPROPS structure.
    m_pCO->m_PageListProps.lPageListSize = m_pCO->m_lPageListEnd + 1;
    ulToWrite = sizeof(PAGELISTPROPS);
    hr = pIStream->Write(&m_pCO->m_PageListProps, ulToWrite, &ulWritten);
    if (SUCCEEDED(hr) && ulToWrite != ulWritten)
      hr = STG_E_CANTSAVE;
    if (SUCCEEDED(hr))
    {
      // Now write the complete array of Page List Data.
      ulToWrite = m_pCO->m_PageListProps.lPageListSize * sizeof(PAGEITEM);
      hr = pIStream->Write(m_pCO->m_paPageList, ulToWrite, &ulWritten);
      if (SUCCEEDED(hr) && ulToWrite != ulWritten)
        hr = STG_E_CANTSAVE;
      if (SUCCEEDED(hr))
      {
        // Clear this COM object's dirty flag if instructed. Otherwise,
        // preserve its content.
        if (bClearDirty)
          m_pCO->m_bDirty = FALSE;
      }
    }
  }

  // Notify all other connected clients that PageList is now saved.
  if (SUCCEEDED(hr))
    m_pCO->NotifySinks(PAGELIST_EVENT_SAVED,-1);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPersistStream::GetSizeMax

  Summary:  Called to obtain the maximum size of the chunk of data that
            could be saved when Save is next called.

  Args:     ULARGE_INTEGER* pcbSize
              Address of the caller's ULARGE_INTEGER variable to receive
              the data size that Save would next write into the stream.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageList::CImpIPersistStream::GetSizeMax(
               ULARGE_INTEGER* pcbSize)
{
  HRESULT hr = E_POINTER;
  DWORD dwProps, dwData;

  if (NULL != pcbSize)
  {
    dwProps = sizeof(PAGELISTPROPS);
    dwData = (m_pCO->m_lPageListEnd+1) * sizeof(PAGEITEM);
    ULISet32(*pcbSize, dwProps+dwData);
    hr = NOERROR;
  }

  return hr;
}


/*---------------------------------------------------------------------------
  COPageList's nested implementation of the custom IPageList interface
  including Constructor, Destructor, QueryInterface, AddRef, Release,
  Get, Set, Add, Delete, and Clear.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPageList::CImpIPageList

  Summary:  Constructor for the CImpIPageList interface instantiation.

  Args:     COPageList* pCO,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_pCO, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPageList::CImpIPageList::CImpIPageList(
  COPageList* pCO,
  IUnknown* pUnkOuter)
{
  // Init the Main Object Pointer to point to the parent object.
  m_pCO = pCO;

  // Init the CImpIPageList interface's delegating Unknown pointer.  We
  // use the Main Object pointer for IUnknown delegation here if we are
  // not being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpIPageList lifetime is
  // quaranteed by the lifetime of the parent object in which
  // CImpIPageList is nested.
  if (NULL == pUnkOuter)
    m_pUnkOuter = pCO;
  else
    m_pUnkOuter = pUnkOuter;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPageList::~CImpIPageList

  Summary:  Destructor for the CImpIPageList interface instantiation.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPageList::CImpIPageList::~CImpIPageList(void)
{

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPageList::QueryInterface

  Summary:  The QueryInterface IUnknown member of this IPageList interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
              Returned by the delegated outer QueryInterface call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageList::CImpIPageList::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPageList::AddRef

  Summary:  The AddRef IUnknown member of this IPageList interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPageList::CImpIPageList::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPageList::Release

  Summary:  The Release IUnknown member of this IPageList interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPageList::CImpIPageList::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPageList::FindSlot

  Summary:  An internal private utility member method to find the PageList
            array slot index of a specified page sequence number.

  Args:     INT iPage
              Requested Page number of the item to find.
            LONG* plSlot
              Address of variable to receive slot index of found page.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COPageList::CImpIPageList::FindSlot(
          INT iPage,
          LONG* plSlot)
{
  HRESULT hr = E_FAIL;
  LONG i;

  // Loop thru the current PageList array and find the requested
  // page number.
  for (i=0; i<=m_pCO->m_lPageListEnd; i++)
  {
    if (PAGETYPE_NONE != m_pCO->m_paPageList[i].nType &&
        iPage == m_pCO->m_paPageList[i].iPage)
    {
      *plSlot = i;
      hr = NOERROR;
      break;
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPageList::NextSlot

  Summary:  An internal private utility member method to obtain the next
            slot in the dynamic PageList array. If the requested page
            number lies within the existing ordered sequence, it is
            inserted before the current item of the same page number. If
            the requested page number is < 0 then the new item is assumed
            to be a new last page number. This method pre-assigns the
            expected page number of the item. NextSlot will expand the
            dynamic array for more entries if needed.

  Args:     INT iPage
              Requested Page order number of the new addition. If this
              page number is < 0 then add new item to end of list.
            LONG* plSlot
              Address of slot variable to receive index of new slot.

  Modifies: m_lPageListEnd, m_lPageListMax, m_paPageList.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COPageList::CImpIPageList::NextSlot(
          INT iPage,
          LONG* plSlot)
{
  HRESULT hr = E_FAIL;
  PAGEITEM* paPgList;
  LONG i, lNewEnd = m_pCO->m_lPageListEnd;
  LONG lSlot = 0;
  SHORT nLastPage;

  // Loop thru the current PageList array and find first empty slot.
  for (i=0; i<=lNewEnd; i++)
  {
    if (PAGETYPE_NONE == m_pCO->m_paPageList[i].nType)
    {
      // Assign new slot number as first empty slot found.
      lSlot = i;
      hr = NOERROR;
      break;
    }
  }

  if (FAILED(hr))
  {
    hr = NOERROR;
    lNewEnd++;

    // No empty slots so expand the array.
    if (lNewEnd >= m_pCO->m_lPageListMax)
    {
      // No more room in PageList array. Allocate new array space.
      paPgList = new PAGEITEM[(LONG)(m_pCO->m_lPageListMax+PAGELIST_ALLOC)];
      if (NULL != paPgList)
      {
        // Copy the content of the old full array to the new larger array.
        memcpy(paPgList, m_pCO->m_paPageList, lNewEnd * sizeof(PAGEITEM));

        // Zero (& mark as empty) the expanded portion of the new array.
        memset(
          &(paPgList[lNewEnd]),
          0,
          PAGELIST_ALLOC * sizeof(PAGEITEM));

        // New larger array is ready--delete the old array.
        if (NULL != m_pCO->m_paPageList)
          delete [] m_pCO->m_paPageList;

        // Rig the PageList to use the new larger array.
        m_pCO->m_paPageList = paPgList;

        // Calculate the new max index.
        m_pCO->m_lPageListMax += PAGELIST_ALLOC;
      }
      else
        hr = E_OUTOFMEMORY;
    }

    if (SUCCEEDED(hr))
    {
      // Assign new List End.
      m_pCO->m_lPageListEnd = lNewEnd;

      // Assign new slot number as last item of new item list.
      lSlot = lNewEnd;
    }
  }

  if (SUCCEEDED(hr))
  {
    if (iPage < 0)
    {
      nLastPage = -1;

      // Find the last page number.
      for (i=0; i<=lNewEnd; i++)
      {
        if (PAGETYPE_NONE != m_pCO->m_paPageList[i].nType
            && m_pCO->m_paPageList[i].iPage > nLastPage)
          nLastPage = m_pCO->m_paPageList[i].iPage;
      }

      // Assign the Page Number of the new last entry.
      m_pCO->m_paPageList[lSlot].iPage = nLastPage + 1;
    }
    else
    {
      // Renumber the existing page items to make room for the new one.
      for (i=0; i<=lNewEnd; i++)
      {
        if (PAGETYPE_NONE != m_pCO->m_paPageList[i].nType
            && iPage >= m_pCO->m_paPageList[i].iPage)
          m_pCO->m_paPageList[i].iPage += 1;
      }

      // Assign the Page Number.
      m_pCO->m_paPageList[lSlot].iPage = iPage;
    }

    // Assign the output slot number.
    *plSlot = lSlot;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPageList::NextName

  Summary:  An internal private utility member method to generate the next
            internal name for the storage or stream that will be used to
            store pages.

  Args:     SHORT nType,
              Page Type of the new page.
            WCHAR* pwszName
              Pointer to the wide char string to receive the new name.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COPageList::CImpIPageList::NextName(
          SHORT nType,
          WCHAR* pwszName)
{
  HRESULT hr = E_POINTER;
  TCHAR szName[PAGE_NAME_SIZE];
  TCHAR szNameCount[PAGE_NAME_SIZE];

  if (NULL != pwszName)
  {
    hr = NOERROR;

    // Assign the page type string.
    switch (nType)
    {
      case PAGETYPE_DRAWING:
        lstrcpy(szName, TEXT(DRAWING_STR));
        break;
      case PAGETYPE_TEXT:
        lstrcpy(szName, TEXT(TEXT_STR));
        break;
      default:
        hr = E_FAIL;
        break;
    }

    if (SUCCEEDED(hr))
    {
      // Calculate the next name count and make a name string.

      // Bump the page name counter.
      m_pCO->m_PageListProps.lPageNameCounter += 1;

      // This change means we should mark the PageList as dirty.
      // A save to file of the PageList object is now needed.
      m_pCO->m_bDirty = TRUE;

#ifdef UNICODE
      _ltow(m_pCO->m_PageListProps.lPageNameCounter, szNameCount, 10);
      lstrcat(szName, szNameCount);
      lstrcpy(pwszName, szName);
#else
      _ltoa(m_pCO->m_PageListProps.lPageNameCounter, szNameCount, 10);
      lstrcat(szName, szNameCount);
      // Convert to WideChar if we are NOT compiled for Unicode.
      AnsiToUc(szName, pwszName, PAGE_NAME_SIZE);
#endif
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPageList::Get

  Summary:  Get a Page List Item for a given page number. Get back
            open status, page type, page title, and page data name.

  Args:     INT iPage,
              Page sequence number of the item to get (0-based).
            BOOL* pbOpen,
              Address of a boolean variable to receive the page open status.
              If NULL then don't get this value.
            SHORT* pnType,
              Address of a PageType variable to receive the page type.
              If NULL then don't get this value.
            WCHAR* pwszTitle,
              Address of a wide character string to receive the page title.
              If NULL then don't get this value.
            WCHAR* pwszDataName)
              Address of a wide character string to receive the data name.
              If NULL then don't get this value.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageList::CImpIPageList::Get(
               INT     iPage,
               BOOL*   pbOpen,
               SHORT*  pnType,
               WCHAR*  pwszTitle,
               WCHAR*  pwszDataName)
{
  HRESULT hr = E_POINTER;
  LONG lSlot;

  hr = FindSlot(iPage, &lSlot);
  if (SUCCEEDED(hr))
  {
    // Assign the caller's open status variable.
    if (NULL != pbOpen)
      *pbOpen = m_pCO->m_paPageList[lSlot].bOpen;

    // Assign the caller's page type variable.
    if (NULL != pnType)
      *pnType = m_pCO->m_paPageList[lSlot].nType;

    // Copy the page title to the caller's variable.
    if (NULL != pwszTitle)
      memcpy(
        pwszTitle,
        m_pCO->m_paPageList[lSlot].wszTitle,
        PAGE_TITLE_SIZE*sizeof(WCHAR));

    // Copy the page data name to the caller's variable.
    if (NULL != pwszDataName)
      memcpy(
        pwszDataName,
        m_pCO->m_paPageList[lSlot].wszDataName,
        PAGE_NAME_SIZE*sizeof(WCHAR));
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPageList::Set

  Summary:  Set a Page List Item of specified page number with a
            new Title and the page's current open status.

  Args:     INT iPage
              Page sequence number of the item to put (0-based).
            SHORT   nOpenStatus,
              Status of whether the page is open or not.
            WCHAR* pwszNewTitle);
              New Title for the page.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageList::CImpIPageList::Set(
               INT     iPage,
               SHORT   nOpenStatus,
               WCHAR*  pwszNewTitle)
{
  HRESULT hr = E_FAIL;
  LONG lSlot;

  if (NULL != pwszNewTitle || OPENSTATE_NONE != nOpenStatus)
  {
    hr = FindSlot(iPage, &lSlot);
    if (SUCCEEDED(hr))
    {
      switch (nOpenStatus)
      {
        case OPENSTATE_YES:
          m_pCO->m_paPageList[lSlot].bOpen = TRUE;
          break;
        case OPENSTATE_NO:
          m_pCO->m_paPageList[lSlot].bOpen = FALSE;
          break;
        default:
          break;
      }

      if (NULL != pwszNewTitle)
      {
        // Copy the caller's new title into the specified list item.
        memcpy(
          m_pCO->m_paPageList[lSlot].wszTitle,
          pwszNewTitle,
          PAGE_TITLE_SIZE*sizeof(WCHAR));
      }

      // Mark PageList as dirty. Save to file is needed.
      m_pCO->m_bDirty = TRUE;

      // Notify all other connected clients that a page list
      // item was set/changed.
      m_pCO->NotifySinks(PAGELIST_EVENT_PAGESET, iPage);
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPageList::Add

  Summary:  Add/Insert a new Page List Item of specified type with
            specified title. Inserts before the entry with the
            specified page number. If iPage < 0 then add the new item
            to the end of the list.

  Args:     INT     iPage,
              Page sequence number to insert. If < 0 then add to end of
              page number sequence and assign *piNewPage with the new
              page number.
            SHORT   nType,
              Page Type of the new page.
            WCHAR*  pwszTitle,
              Pointer to the wide character string that will be the new
              page's title.
            INT* piNewPage
              Address of integer variable to receive new Page number.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageList::CImpIPageList::Add(
               INT iPage,
               SHORT nType,
               WCHAR* pwszTitle,
               INT* piNewPage)
{
  HRESULT hr = E_POINTER;
  LONG lSlot;

  if (NULL != pwszTitle && PAGETYPE_NONE != nType)
  {
    // Find the next slot and assign its page number.
    hr = NextSlot(iPage, &lSlot);
    if (SUCCEEDED(hr))
    {
      // Create and assign a new storage/stream name.
      hr = NextName(nType, m_pCO->m_paPageList[lSlot].wszDataName);
      if (SUCCEEDED(hr))
      {
        // Copy the caller's new title into the specified page list item.
        memcpy(
          m_pCO->m_paPageList[lSlot].wszTitle,
          pwszTitle,
          PAGE_TITLE_SIZE*sizeof(WCHAR));

        // Assign the new page type.
        m_pCO->m_paPageList[lSlot].nType = nType;

        // Inform the caller of the new page number.
        *piNewPage = m_pCO->m_paPageList[lSlot].iPage;

        // Mark PageList as dirty. Save to file is needed.
        m_pCO->m_bDirty = TRUE;

        // Notify all other connected clients that a new page list
        // item was added.
        m_pCO->NotifySinks(
                  PAGELIST_EVENT_PAGEADDED,
                  m_pCO->m_paPageList[lSlot].iPage);
      }
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPageList::Delete

  Summary:  Delete a Page List Item for the specified page number.

  Args:     INT iPage
              Page number of the page item to delete (0-based).

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageList::CImpIPageList::Delete(
               INT iPage)
{
  HRESULT hr = E_FAIL;
  INT iLastPage = iPage;
  INT iPg;
  LONG lSlot, i;

  hr = FindSlot(iPage, &lSlot);
  if (SUCCEEDED(hr))
  {
    // Mark item as empty.
    m_pCO->m_paPageList[lSlot].nType = PAGETYPE_NONE;

    // Renumber the remaining pages to account for the missing page.
    for (i=0; i<=m_pCO->m_lPageListEnd; i++)
    {
      iPg = m_pCO->m_paPageList[i].iPage;
      if (PAGETYPE_NONE != m_pCO->m_paPageList[i].nType
          && iPg >= 0 && iPg > iPage)
      {
        if (iPg > 0)
          iPg--;
        m_pCO->m_paPageList[i].iPage = iPg;
        if (iPg > iLastPage)
          iLastPage = iPg;
      }
    }

    // Mark PageList as dirty.
    m_pCO->m_bDirty = TRUE;

    // Notify all other connected clients that a page list
    // item was deleted.
    iPg = (iPage <= iLastPage) ? iPage : iLastPage;
    m_pCO->NotifySinks(PAGELIST_EVENT_PAGEDELETED, iPg);
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPageList::CImpIPageList::Clear

  Summary:  Clears the entire page list. Removes all entries.

  Args:     none.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPageList::CImpIPageList::Clear(
               void)
{
  HRESULT hr = E_FAIL;

  hr = m_pCO->Clear();

  // Notify all other connected clients that the list was cleared.
  if (SUCCEEDED(hr))
    m_pCO->NotifySinks(PAGELIST_EVENT_CLEARED,0);

  return hr;
}
