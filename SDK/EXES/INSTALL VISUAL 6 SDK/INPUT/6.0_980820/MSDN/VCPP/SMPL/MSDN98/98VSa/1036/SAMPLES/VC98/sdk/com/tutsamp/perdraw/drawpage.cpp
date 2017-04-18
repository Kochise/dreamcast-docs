/*+==========================================================================
  File:      DRAWPAGE.CPP

  Summary:   Implementation file for the CODrawPage COM Object Class (for
             connectable, persistent CODrawPage COM Objects). CODrawPage
             encapsulates into a COM object the behavior of an persistent
             electronic page of white drawing paper. The client can use
             the native IDrawPage interface to draw free-form ink lines on
             a virtual paper surface. No GUI behavior is provided within
             CODrawPage--it only provides the semantics of the virtual
             drawing paper and manages the ink data for the drawing done
             there by clients. CODrawPages are self-persistent in compound
             file storages and can can thus store and load the DrawPage
             data contents to and from an IStorage given by the client
             (using the standard IPersistStorage interface).

             CODrawPage offers a main standard IUnknown interface (basic
             COM object features), an implementation of the standard
             IConnectionPointContainer interface (connectable object
             features), an implementation of the standard IPersistStorage
             interface (features for object persistence in compound file
             storages), and an implementation of the custom IDrawPage
             interface (drawing page related features). This multiple
             interface COM Object Class is achieved via the technique of
             nested classes.  The implementation of the various
             interfaces are nested inside of the CODrawPage Class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial PERDRAW.HTM file. For
             more specific technical details on the internal workings see
             the comments dispersed throughout the module's source code.

  Classes:   CODrawPage.

  Functions: none.

  Origin:    5-20-97: atrent - Editor-inheritance from PAPER.CPP in
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
  We include IPAGES.H and PAGEGUID.H for the common DrawPage-related
    Interface classes, GUID, and CLSID specifications.
  We include SERVER.H because it has internal class declarations for
    the server's control object.
  We include CONNECT.H for object class declarations for the various
    connection point and connection COM objects used in PERDRAW.
  We include DRAWPAGE.H because it has the CODrawPage class declarations.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <apputil.h>
#include <ipages.h>
#include <pageguid.h>
#include "server.h"
#include "connect.h"
#include "drawpage.h"


/*---------------------------------------------------------------------------
  CODrawPage's implementation of its main COM object class including
  Constructor, Destructor, and the QueryInterface, AddRef, and Release
  methods of the principal IUnknown interface.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CODrawPage

  Summary:  CODrawPage Constructor. Note the member initializers like:
            "m_ImpIDrawPage(this, pUnkOuter)" which is used to pass the
            'this' and pUnkOuter pointers of the constructor function to
            the constructor in the instantiation of the implementation of
            the CImpIDrawPage interface (which is nested inside this
            present CODrawPage Object Class). Same initializer technique
            is used for the other nested interface implementations.

  Args:     IUnknown* pUnkOuter,
              Pointer to the the outer IUnknown.  NULL means this COM Object
              is not being Aggregated.  Non-NULL means it is being created
              on behalf of an outside COM object that is reusing it via
              aggregation.
            CServer* pServer)
              Pointer to the server's control object.

  Modifies: m_cRefs, m_pUnkOuter, m_pServer.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CODrawPage::CODrawPage(
  IUnknown* pUnkOuter,
  CServer* pServer) :
  m_ImpIConnectionPointContainer(this, pUnkOuter),
  m_ImpIPersistStorage(this, pUnkOuter),
  m_ImpIDrawPage(this, pUnkOuter)
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

  // Now initialize the living heart of this virtual DrawPage entity.
  m_crWinColor   = RGB(255,255,255); // White window background color.
  m_crInkColor   = RGB(0,0,0);       // Black ink drawing color.
  m_nInkWidth    = 2;                // 2 pixels wide (thin) for ink.
  m_lInkDataEnd  = 0;                // Current drawing data end.
  m_lInkDataMax  = 0;                // Upper bound to m_lInkDataEnd.
  m_paInkData    = NULL;             // Points to the Ink data array.
  m_ClassID      = CLSID_DrawPage;   // ClassID. Copy w/ overloaded '='.
  m_ClipFmt      = 0;                // Registered clipboard format ID.
  m_StgState     = PERS_UNINIT;      // Persistent Storage State.
  m_bDirty       = TRUE;             // File initially doesn't match RAM.

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::~CODrawPage

  Summary:  CODrawPage Destructor.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CODrawPage::~CODrawPage(void)
{
  UINT i;
  IConnectionPoint* pIConnectionPoint;

  // Do final release of the connection point objects.
  for (i=0; i<MAX_CONNECTION_POINTS; i++)
  {
    pIConnectionPoint = m_aConnectionPoints[i];
    RELEASE_INTERFACE(pIConnectionPoint);
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::Init

  Summary:  CODrawPage initialization method.  Create any necessary arrays,
            structures, and subordinate objects. Rigs for connectivity.

  Args:     void

  Modifies: m_aConnectionPoints.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CODrawPage::Init(void)
{
  HRESULT hr = NOERROR;
  INKDATA* paInkData;
  COConnectionPoint* pCOConnPt;

  // Zero the Properties structure. Init the ink data version.
  memset(&m_DrawProps, 0, sizeof(DRAWPROPS));
  m_DrawProps.lInkDataVersion = INKDATA_VERSION20;

  // Register a clipboard format for DrawPages.
  m_ClipFmt = RegisterClipboardFormat(TEXT(SZ_CLIPUSERTYPE));

  // Build the initial dynamic array of InkData.
  paInkData = new INKDATA[(LONG) INKDATA_ALLOC_INIT];
  if (NULL != paInkData)
  {
    // Zero the array.
    memset(paInkData, 0, INKDATA_ALLOC_INIT * sizeof(INKDATA));

    // Rig this object so that it can use the Ink Data array.
    m_lInkDataMax = INKDATA_ALLOC_INIT;
    m_paInkData = paInkData;
  }
  else
    hr = E_OUTOFMEMORY;

  if (SUCCEEDED(hr))
  {
    // Rig this CODrawPage COM object to be connectable. Assign the
    // connection point array. This object's connection points are
    // determined at compile time--it currently has only one connection
    // point: the CONNPOINT_DRAWPAGESINK connection point. Create a
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
      hr = pCOConnPt->Init(IID_IDrawPageSink);

      // If the init succeeded then use QueryInterface to obtain the
      // IConnectionPoint interface on the new connection point object.
      // The interface pointer is assigned directly into the
      // connection point array. The QI also does the needed AddRef.
      if (SUCCEEDED(hr))
        hr = pCOConnPt->QueryInterface(
               IID_IConnectionPoint,
               (PPVOID)&m_aConnectionPoints[CONNPOINT_DRAWPAGESINK]);
    }
    else
      hr = E_OUTOFMEMORY;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::QueryInterface

  Summary:  QueryInterface of the CODrawPage main non-delegating IUnknown
            implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPage::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;

  *ppv = NULL;

  if (IID_IUnknown == riid)
    *ppv = this;
  else if (IID_IConnectionPointContainer == riid)
    *ppv = &m_ImpIConnectionPointContainer;
  else if (IID_IPersistStorage == riid)
    *ppv = &m_ImpIPersistStorage;
  else if (IID_IDrawPage == riid)
    *ppv = &m_ImpIDrawPage;

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
  Method:   CODrawPage::AddRef

  Summary:  AddRef of the CODrawPage non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CODrawPage::AddRef(void)
{
  ULONG cRefs;

  cRefs = ++m_cRefs;

  return cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::Release

  Summary:  Release of the CODrawPage non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CODrawPage::Release(void)
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
    // via the main object destructor.
    m_cRefs++;
    delete this;
  }

  return cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::NotifySinks

  Summary:  Internal utility method of this COM object used to fire event
            notification calls to all listening connection sinks in the
            client.

  Args:     DRAWPAGE_EVENT DrawPageEvent
              Type of notification event.
            SHORT nX
              X cordinate. Value is 0 unless event needs it.
            SHORT nY
              Y cordinate. Value is 0 unless event needs it.
            SHORT nInkWidth
              Ink Width. Value is 0 unless event needs it.
            SHORT crInkColor
              COLORREF RGB color value. Value is 0 unless event needs it.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CODrawPage::NotifySinks(
       DRAWPAGE_EVENT DrawPageEvent,
       SHORT nX,
       SHORT nY,
       SHORT nInkWidth,
       COLORREF crInkColor)
{
  HRESULT hr = NOERROR;
  IConnectionPoint* pIConnectionPoint;
  IEnumConnections* pIEnum;
  CONNECTDATA ConnData;

  // If there was a DrawPage event, broadcast appropriate notifications to
  // all Sinks connected to each connection point.
  if (DRAWPAGE_EVENT_NONE != DrawPageEvent)
  {
    // Here is the section for the DrawPageSink connection point--currently
    // this is the only connection point offered by CODrawPage objects.
    pIConnectionPoint = m_aConnectionPoints[CONNPOINT_DRAWPAGESINK];
    if (NULL != pIConnectionPoint)
    {
      pIConnectionPoint->AddRef();
      hr = pIConnectionPoint->EnumConnections(&pIEnum);
      if (SUCCEEDED(hr))
      {
        // Loop thru the connection point's connections and if the
        // listening connection supports IDrawPageSink (ie, DrawPageSink
        // events) then dispatch the DrawPageEvent event notification to
        // that sink.
        while (NOERROR == pIEnum->Next(1, &ConnData, NULL))
        {
          IDrawPageSink* pIDrawPageSink;

          hr = ConnData.pUnk->QueryInterface(
                                IID_IDrawPageSink,
                                (PPVOID)&pIDrawPageSink);
          if (SUCCEEDED(hr))
          {
            switch (DrawPageEvent)
            {
              case DRAWPAGE_EVENT_INKDRAW:
                pIDrawPageSink->InkDraw(nX, nY);
                break;
              case DRAWPAGE_EVENT_INKSTART:
                pIDrawPageSink->InkStart(nX, nY, nInkWidth, crInkColor);
                break;
              case DRAWPAGE_EVENT_INKSTOP:
                pIDrawPageSink->InkStop(nX, nY);
                break;
              case DRAWPAGE_EVENT_RESIZED:
                pIDrawPageSink->Resized(nX, nY);
                break;
              case DRAWPAGE_EVENT_CLEARED:
                pIDrawPageSink->Cleared();
                break;
              case DRAWPAGE_EVENT_LOADED:
                pIDrawPageSink->Loaded();
                break;
              case DRAWPAGE_EVENT_SAVED:
                pIDrawPageSink->Saved();
                break;
              default:
                break;
            }
            pIDrawPageSink->Release();
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


/*---------------------------------------------------------------------------
  CODrawPage's nested implementation of the COM standard
  IConnectionPointContainer interface including Constructor, Destructor,
  QueryInterface, AddRef, Release, FindConnectionPoint, and
  EnumConnectionPoints.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIConnectionPointContainer
              ::CImpIConnectionPointContainer

  Summary:  Constructor for the CImpIConnectionPointContainer interface
            instantiation.

  Args:     CODrawPage* pCO,
              Back pointer to the parent outer COM object.
            IUnknown* pUnkOuter
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_pCO, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CODrawPage::CImpIConnectionPointContainer::CImpIConnectionPointContainer(
  CODrawPage* pCO,
  IUnknown* pUnkOuter)
{
  // Init the interface's object pointer to point to the parent COM object.
  m_pCO = pCO;

  // Init the CImpIConnectionPointContainer interface's delegating Unknown
  // pointer.  We use the main Object pointer for IUnknown delegation here
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
  Method:   CODrawPage::CImpIConnectionPointContainer
              ::~CImpIConnectionPointContainer

  Summary:  Destructor for the CImpIConnectionPointContainer interface
            instantiation.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CODrawPage::CImpIConnectionPointContainer::~CImpIConnectionPointContainer(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIConnectionPointContainer::QueryInterface

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
STDMETHODIMP CODrawPage::CImpIConnectionPointContainer::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIConnectionPointContainer::AddRef

  Summary:  The AddRef IUnknown member of this interface implementation
            that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CODrawPage::CImpIConnectionPointContainer::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIConnectionPointContainer::Release

  Summary:  The Release IUnknown member of this interface implementation
            that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CODrawPage::CImpIConnectionPointContainer::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIConnectionPointContainer::FindConnectionPoint

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
STDMETHODIMP CODrawPage::CImpIConnectionPointContainer::FindConnectionPoint(
               REFIID riid,
               IConnectionPoint** ppConnPt)
{
  HRESULT hr = E_NOINTERFACE;
  IConnectionPoint* pIConnPt;

  // NULL the output variable.
  *ppConnPt = NULL;

  pIConnPt = m_pCO->m_aConnectionPoints[CONNPOINT_DRAWPAGESINK];
  if (NULL != pIConnPt)
  {
    // This connectable CODrawPage object currently has only the DrawPage
    // Sink connection point. If the associated interface is requested,
    // use QI to get the Connection Point interface and perform the needed
    // AddRef.
    if (IID_IDrawPageSink == riid)
      hr = pIConnPt->QueryInterface(
                       IID_IConnectionPoint,
                       (PPVOID)ppConnPt);
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIConnectionPointContainer::EnumConnectionPoints

  Summary:  Return Enumerator for the connectable object's contained
            connection points.

  Args:     IEnumConnectionPoints** ppIEnum
              Address of the caller's Enumerator interface pointer
              variable. An output variable that will receive a pointer to
              the connection point enumerator COM object.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPage::CImpIConnectionPointContainer::EnumConnectionPoints(
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
  // points offered by this CODrawPage object. Pass 'this' to be used to
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
  CODrawPage's nested implementation of the COM standard IPersistStorage
  interface including Constructor, Destructor, QueryInterface, AddRef,
  Release, GetClassID, IsDirty, InitNew, Load, Save, SaveCompleted, and
  HandsOffStorage.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIPersistStorage::CImpIPersistStorage

  Summary:  Constructor for the CImpIPersistStorage interface
            implementation.

  Args:     CODrawPage* pCO,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_pCO, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CODrawPage::CImpIPersistStorage::CImpIPersistStorage(
  CODrawPage* pCO,
  IUnknown* pUnkOuter)
{
  // Init the interface's object pointer to point to the parent COM object.
  m_pCO = pCO;

  // Init the CImpIPersistStorage interface's delegating IUnknown
  // pointer.  We use the main object pointer for IUnknown delegation here
  // if we are not being aggregated.  If we are being aggregated we use
  // the supplied pUnkOuter for IUnknown delegation.  In either case the
  // pointer assignment requires no AddRef because the
  // CImpIPersistStorage lifetime is quaranteed by the lifetime
  // of the parent object in which CImpIPersistStorage is
  // nested.
  if (NULL == pUnkOuter)
    m_pUnkOuter = pCO;
  else
    m_pUnkOuter = pUnkOuter;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIPersistStorage::~CImpIPersistStorage

  Summary:  Destructor for the CImpIPersistStorage interface
            instantiation.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CODrawPage::CImpIPersistStorage::~CImpIPersistStorage(void)
{
  // Release the current stream elements and the main storage.
  // This NULLs these interface pointers (via the release macro).
  RELEASE_INTERFACE(m_pIStream_Props);
  RELEASE_INTERFACE(m_pIStream_Data);
  RELEASE_INTERFACE(m_pIStorage);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIPersistStorage::QueryInterface

  Summary:  The QueryInterface IUnknown member of this IDrawPage interface
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
STDMETHODIMP CODrawPage::CImpIPersistStorage::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIPersistStorage::AddRef

  Summary:  The AddRef IUnknown member of this IDrawPage interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CODrawPage::CImpIPersistStorage::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIPersistStorage::Release

  Summary:  The Release IUnknown member of this IDrawPage interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CODrawPage::CImpIPersistStorage::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIPersistStorage::GetClassID

  Summary:  A method inherited from IPersist. Get the Class ID of this
            COM object.

  Args:     CLSID* pClassID
              [out] Address of variable to hold Class ID.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPage::CImpIPersistStorage::GetClassID(
               CLSID* pClassID)
{
  HRESULT hr = E_POINTER;

  if (NULL != pClassID)
  {
    // Use overloaded '=' operator to copy the Class ID to caller.
    *pClassID = m_pCO->m_ClassID;
    hr = NOERROR;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIPersistStorage::IsDirty

  Summary:  Called to determine if changes were made to this COM object
            since it was last loaded or initialized.

  Args:     none.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPage::CImpIPersistStorage::IsDirty(
               void)
{
  HRESULT hr;

  hr = m_pCO->m_bDirty ? S_OK : S_FALSE;

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIPersistStorage::InitNew

  Summary:  Called to tell the object that it has been newly created. The
            object has no existing persistent state already stored and
            must create it anew to initialize the object.

            InitNew is called INSTEAD of Load when the new object instance
            must be initialized with brand new data rather than with
            persistent data previously saved. Creates and opens all
            storage and stream elements that it needs (including any
            elements that it would need in a low-memory save situation).
            Pre-allocates any stream space that it will need in a later
            save operation.

  Args:     IStorage* pIStorage
              Interface of the substorage within which the DrawPage stores
              its persistent state. The object should hold a copy of the
              pStorage reference and any other references it would later
              need in a low-memory save operation.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPage::CImpIPersistStorage::InitNew(
               IStorage* pIStorage)
{
  HRESULT hr = E_UNEXPECTED;
  ULONG ulToWrite, ulWritten;

  // There is no previous persistent data for this CODrawPage object.
  // Create and init new persistence data for an empty drawing page.

  // Return E_UNEXPECTED error if not in the UNINIT state.
  if (PERS_UNINIT == m_pCO->m_StgState)
  {
    if (NULL != pIStorage)
    {
      // Create the Properties stream.
      hr = pIStorage->CreateStream(
             WSZ_DRAWPROPS,
             STGM_CREATE | STGM_DIRECT
               | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
             0,
             0,
             &m_pIStream_Props);
      if (SUCCEEDED(hr))
      {
        // Create the Ink Data stream.
        hr = pIStorage->CreateStream(
                WSZ_DRAWDATA,
                STGM_CREATE | STGM_DIRECT
                  | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
                0,
                0,
                &m_pIStream_Data);
        if (SUCCEEDED(hr))
        {
          // Write the clipboard format and User Type Name info.
          hr = WriteFmtUserTypeStg(
                 pIStorage,
                 m_pCO->m_ClipFmt,
                 TEXT(SZ_CLIPUSERTYPE));
        }
      }
    }
    else
      hr = E_POINTER;

    if (SUCCEEDED(hr))
    {
      // Preallocate stream space by writing the DRAWPROPS structure.
      m_pCO->m_DrawProps.lInkArraySize = m_pCO->m_lInkDataEnd+1;
      m_pCO->m_DrawProps.crWinColor = m_pCO->m_crWinColor;
      m_pCO->m_DrawProps.WinRect.right = m_pCO->m_WinRect.right;
      m_pCO->m_DrawProps.WinRect.bottom = m_pCO->m_WinRect.bottom;
      ulToWrite = sizeof(DRAWPROPS);
      hr = m_pIStream_Props->Write(
             &m_pCO->m_DrawProps,
             ulToWrite,
             &ulWritten);
      if (SUCCEEDED(hr) && ulToWrite != ulWritten)
        hr = STG_E_CANTSAVE;
      if (SUCCEEDED(hr))
      {
        // Preallocate stream space by writing the initial Ink Data array.
        ulToWrite = m_pCO->m_DrawProps.lInkArraySize * sizeof(INKDATA);
        hr = m_pIStream_Data->Write(
               m_pCO->m_paInkData,
               ulToWrite,
               &ulWritten);
        if (SUCCEEDED(hr) && ulToWrite != ulWritten)
          hr = STG_E_CANTSAVE;
        if (FAILED(hr))
        {
          // Release ink data stream if error writing.
          m_pIStream_Data->Release();
        }
      }
      else
      {
        // Release property stream if error writing.
        m_pIStream_Props->Release();
      }

      if (SUCCEEDED(hr))
      {
        // Keep open storage pointer around for use in later incremental or
        // low-memory calls of Save. AddRef the interface pointer copy.
        m_pIStorage = pIStorage;
        m_pIStorage->AddRef();

        // Switch the persistent storage state to the scribble state.
        m_pCO->m_StgState = PERS_SCRIBBLE;
      }
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIPersistStorage::Load

  Summary:  Load the object's persistent data from the specified storage
            where the persistent data was previously saved in a prior
            object lifetime. During/after Load the object should hold any
            elements it later needs for scribbling or for low-memory
            saves. This includes the pStorage reference. Load is always
            called INSTEAD of InitNew when the object is initialized with
            its previously stored persistent data.

  Args:     IStorage* pIStorage
              Interface of the substorage from which the DrawPage loads
              its persistent state. The object should hold on to this
              pIStorage (and all subordinate storage element pointers)
              for later use in incremental or low-memory calls to Save.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPage::CImpIPersistStorage::Load(
               IStorage* pIStorage)
{
  HRESULT hr = E_UNEXPECTED;
  ULONG ulToRead, ulReadIn;
  LONG lNewArraySize;
  INKDATA* paInkData;
  DRAWPROPS NewProps;

  // Return E_UNEXPECTED error if not in the UNINIT state.
  if (PERS_UNINIT == m_pCO->m_StgState)
  {
    if (NULL != pIStorage)
    {
      // Open the existing DrawPage properties stream.
      hr = pIStorage->OpenStream(
             WSZ_DRAWPROPS,
             0,
             STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
             0,
             &m_pIStream_Props);
      if (SUCCEEDED(hr))
      {
        // Open the existing DrawPage ink data stream.
        hr = pIStorage->OpenStream(
               WSZ_DRAWDATA,
               0,
               STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
               0,
               &m_pIStream_Data);
        if (SUCCEEDED(hr))
        {
          // Read the DrawPage properties from the their stream.
          ulToRead = sizeof(DRAWPROPS);
          hr = m_pIStream_Props->Read(&NewProps, ulToRead, &ulReadIn);
          if (SUCCEEDED(hr) && ulToRead != ulReadIn)
            hr = STG_E_READFAULT;
          if (SUCCEEDED(hr))
          {
            // Read the Ink Data of the drawing from its stream.
            // Deal with the different versions of ink data format.
            switch (NewProps.lInkDataVersion)
            {
              case INKDATA_VERSION20:
                // Allocate an ink data array big enough--add some extra too.
                lNewArraySize = NewProps.lInkArraySize + INKDATA_ALLOC;
                paInkData = new INKDATA[(LONG) lNewArraySize];
                if (NULL != paInkData)
                {
                  // Delete the entire old ink data array.
                  delete [] m_pCO->m_paInkData;

                  // Assign the new array.
                  m_pCO->m_paInkData = paInkData;
                  m_pCO->m_lInkDataMax = lNewArraySize;

                  // Now read the complete array of Ink Data.
                  ulToRead = NewProps.lInkArraySize * sizeof(INKDATA);
                  hr = m_pIStream_Data->Read(
                         m_pCO->m_paInkData,
                         ulToRead,
                         &ulReadIn);
                  if (SUCCEEDED(hr) && ulToRead != ulReadIn)
                    hr = STG_E_READFAULT;
                  if (SUCCEEDED(hr))
                  {
                    // Rig CODrawPage to use the DRAWPROPS info.
                    m_pCO->m_lInkDataEnd = NewProps.lInkArraySize-1;
                    m_pCO->m_crWinColor = NewProps.crWinColor;
                    m_pCO->m_WinRect.right = NewProps.WinRect.right;
                    m_pCO->m_WinRect.bottom = NewProps.WinRect.bottom;

                    // Copy the new properties into current properties.
                    memcpy(
                      &m_pCO->m_DrawProps,
                      &NewProps,
                      sizeof(DRAWPROPS));

                    // We are loaded and clean (ie, CODrawPage data
                    // matches file data). Clear dirty flag.
                    m_pCO->m_bDirty = FALSE;
                  }
                  else
                  {
                    // Release data stream if error reading.
                    m_pIStream_Data->Release();
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
          else
          {
            // Release property stream if error reading.
            m_pIStream_Props->Release();
          }
        }
      }

      if (SUCCEEDED(hr))
      {
        // Keep open storage pointer around for use in later incremental or
        // low-memory calls of Save. AddRef the interface pointer copy.
        m_pIStorage = pIStorage;
        m_pIStorage->AddRef();

        // Switch the persistent storage state to the scribble state.
        m_pCO->m_StgState = PERS_SCRIBBLE;
      }
    }
    else
      hr = E_POINTER;
  }

  // Notify all other connected clients that DrawPage is now loaded.
  if (SUCCEEDED(hr))
    m_pCO->NotifySinks(DRAWPAGE_EVENT_LOADED, 0, 0, 0, 0);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIPersistStorage::Save

  Summary:  Save the object's persistent state data to the currently open
            storage or to a newly specified storage depending on
            bSameAsLoad. Regardless of bSameAsLoad, and during/after Save,
            the object continues to hold its present pointers to opened
            elements. But the object cannot scribble on its data until the
            SaveCompleted method is called. Save clears the object's
            m_bDirty flag.

            Save must not fail if an out-of-memory condition is
            encountered. This relies on either InitNew or Load to open and
            hold pointers to any elements later needed by Save.

  Args:     IStorage* pIStorage
              Interface of the substorage into which the DrawPage saves
              its persistent state. Always non-NULL.
            BOOL bSameAsLoad
              TRUE  =>Save to opened storage (ie, the same one previously
                passed to Load or InitNew). Saves only items that need
                saving in the current storage (which could be all)
                without using any extra memory and without opening or
                creating any storages or streams.
              FALSE =>Save to the specified storage as a new storage.
                A complete write of all persistent data is done to the
                newly specified storage. The object's currently open
                storage remains open and unaffected.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPage::CImpIPersistStorage::Save(
               IStorage* pIStorage,
               BOOL bSameAsLoad)
{
  HRESULT hr = E_UNEXPECTED;
  IStream* pIStream_Props;
  IStream* pIStream_Data;

  // Return E_UNEXPECTED error if not in the Scribble state.
  if (PERS_SCRIBBLE == m_pCO->m_StgState)
  {
    if (bSameAsLoad)
    {
      LARGE_INTEGER li;

      // If SameAsLoad use copies of the existing open stream pointers.
      pIStream_Props = m_pIStream_Props;
      pIStream_Data = m_pIStream_Data;

      // AddRef these copies; they are released below.
      pIStream_Props->AddRef();
      pIStream_Data->AddRef();

      // We're going to do a fresh save to existing open elements.
      // So recue the stream seek pointers to their start.
      LISet32(li, 0);
      pIStream_Props->Seek(li, STREAM_SEEK_SET, NULL);
      pIStream_Data->Seek(li, STREAM_SEEK_SET, NULL);

      hr = NOERROR;
    }
    else
    {
      // If not SameAsLoad (save to a different storage) then return the
      // E_POINTER error if a NULL pIStroage was passed.
      if (NULL != pIStorage)
      {
        // If we are saving new persistent image of the object to a
        // different storage then create all the necessary persistent
        // storage elements.

        // Create the Properties stream.
        hr = pIStorage->CreateStream(
               WSZ_DRAWPROPS,
               STGM_CREATE | STGM_DIRECT
                 | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
               0,
               0,
               &pIStream_Props);
        if (SUCCEEDED(hr))
        {
          // Create the Ink Data stream.
          hr = pIStorage->CreateStream(
                  WSZ_DRAWDATA,
                  STGM_CREATE | STGM_DIRECT
                    | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
                  0,
                  0,
                  &pIStream_Data);
          if (SUCCEEDED(hr))
          {
            // Write the clipboard format and User Type Name info.
            hr = WriteFmtUserTypeStg(
                   pIStorage,
                   m_pCO->m_ClipFmt,
                   TEXT(SZ_CLIPUSERTYPE));
          }
        }
      }
      else
        hr = E_POINTER;
    }

    // Now perform the saves of the persistent data elements.
    if (SUCCEEDED(hr))
    {
      ULONG ulToWrite, ulWritten;

      // Save the DrawPage properties in a dedicated stream.
      m_pCO->m_DrawProps.lInkArraySize = m_pCO->m_lInkDataEnd+1;
      m_pCO->m_DrawProps.crWinColor = m_pCO->m_crWinColor;
      m_pCO->m_DrawProps.WinRect.right = m_pCO->m_WinRect.right;
      m_pCO->m_DrawProps.WinRect.bottom = m_pCO->m_WinRect.bottom;
      ulToWrite = sizeof(DRAWPROPS);
      hr = pIStream_Props->Write(&m_pCO->m_DrawProps, ulToWrite, &ulWritten);
      if (SUCCEEDED(hr) && ulToWrite != ulWritten)
        hr = STG_E_CANTSAVE;
      if (SUCCEEDED(hr))
      {
        // Save the DrawPage ink data in a dedicated stream.
        ulToWrite = m_pCO->m_DrawProps.lInkArraySize * sizeof(INKDATA);
        hr = pIStream_Data->Write(m_pCO->m_paInkData, ulToWrite, &ulWritten);
        if (SUCCEEDED(hr) && ulToWrite != ulWritten)
          hr = STG_E_CANTSAVE;
      }

      // Release any temporary streams used.
      pIStream_Props->Release();
      pIStream_Data->Release();

      if (SUCCEEDED(hr))
      {
        // Since the persistent save is now done for this object the
        // file matches the object. So set object's dirty flag to FALSE.
        if (bSameAsLoad)
          m_pCO->m_bDirty = FALSE;

        // Switch the persistent storage state to the NoScribble state.
        // After this Save this object cannot scribble to its persistent
        // storage again until the client grants this freedom by calling
        // SaveCompleted which switches this object to the Scribble state.
        m_pCO->m_StgState = PERS_NOSCRIBBLE;
      }
    }
  }

  // Notify all other connected clients that DrawPage is now saved.
  if (SUCCEEDED(hr))
    m_pCO->NotifySinks(DRAWPAGE_EVENT_SAVED, 0, 0, 0, 0);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIPersistStorage::SaveCompleted

  Summary:  Called by client to inform this COM object that the client has
            completed its overall save operations. Restores the object to
            a state where it is free to write  (ie, scribble) to its
            persistent data elements.

  Args:     IStorage* pIStorage
              Interface of the storage for which the object must release
              its held interface pointers and reopen its persistent data
              elements within that specified storage. If NULL then the
              release/reopen is not needed and the object can once again
              scribble to its expected elements under the currently open
              storage.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPage::CImpIPersistStorage::SaveCompleted(
               IStorage* pIStorage)
{
  HRESULT hr = E_UNEXPECTED;
  IStream* pIStream_Props;
  IStream* pIStream_Data;
  BOOL bOk;
  PERSTGSTATE StgState = m_pCO->m_StgState;

  // Return E_UNEXPECTED error if storage is NOT in either the
  // No-scribble or Hands-off state.
  bOk = (StgState == PERS_NOSCRIBBLE || StgState == PERS_HANDSOFF);
  if (bOk)
  {
    // Return E_UNEXPECTED if in Hands-off state but pIStorage is NULL.
    if (StgState == PERS_HANDSOFF && NULL == pIStorage)
      bOk = FALSE;
    else
      hr = NOERROR;
  }

  if (bOk)
  {
    if (NULL != pIStorage)
    {
      // If specified storage is non-NULL, release all storage elements
      // and use the specified pIStorage to re-open those elements.
      // If pIStorage == NULL then we need do nothing since we already
      // have all the pointers to storage elements needed for Save.

      // First ensure we can open the property and data streams
      hr = pIStorage->OpenStream(
             WSZ_DRAWPROPS,
             0,
             STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
             0,
             &pIStream_Props);
      if (SUCCEEDED(hr))
      {
        hr = pIStorage->OpenStream(
               WSZ_DRAWDATA,
               0,
               STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
               0,
               &pIStream_Data);
        if (SUCCEEDED(hr))
        {
          // Release the current stream elements and the main storage.
          RELEASE_INTERFACE(m_pIStream_Props);
          RELEASE_INTERFACE(m_pIStream_Data);
          RELEASE_INTERFACE(m_pIStorage);

          // Reassign the storage and stream interface pointers.
          m_pIStorage = pIStorage;
          m_pIStorage->AddRef();
          m_pIStream_Props = pIStream_Props;
          m_pIStream_Data = pIStream_Data;
        }
      }
    }

    if (SUCCEEDED(hr))
    {
      // Switch the persistent storage state back to the scribble state.
      m_pCO->m_StgState = PERS_SCRIBBLE;

      // Since save is completed, no save is needed. So set object's
      // dirty flag to FALSE.
      m_pCO->m_bDirty = FALSE;
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIPersistStorage::HandsOffStorage

  Summary:  Directs object to release the pointers it holds to all
            persistent data elements and, until further notice, NOT to
            write to its persistent data elements. A subsequent call to
            SaveCompleted restores the object's freedom to write to its
            persistent data elements.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPage::CImpIPersistStorage::HandsOffStorage(
               void)
{
  HRESULT hr = E_UNEXPECTED;
  PERSTGSTATE StgState = m_pCO->m_StgState;

  // Return E_UNEXPECTED error if NOT in scribble or no-scribble state.
  if (StgState == PERS_NOSCRIBBLE || StgState == PERS_SCRIBBLE)
  {
    // Release the current stream elements and the main storage.
    // This NULLs these interface pointers (via the release macro).
    RELEASE_INTERFACE(m_pIStream_Props);
    RELEASE_INTERFACE(m_pIStream_Data);
    RELEASE_INTERFACE(m_pIStorage);

    // Switch the persistent storage state to the Hands-off state.
    m_pCO->m_StgState = PERS_HANDSOFF;
    hr = NOERROR;
  }

  return hr;
}


/*---------------------------------------------------------------------------
  CODrawPage's nested implementation of the custom IDrawPage interface
  including Constructor, Destructor, QueryInterface, AddRef, Release,
  InkStart, InkDraw, InkStop, Clear, Resize, and Redraw.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIDrawPage::CImpIDrawPage

  Summary:  Constructor for the CImpIDrawPage interface instantiation.

  Args:     CODrawPage* pCO,
              Back pointer to the parent outer COM object.
            IUnknown* pUnkOuter
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_pCO, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CODrawPage::CImpIDrawPage::CImpIDrawPage(
  CODrawPage* pCO,
  IUnknown* pUnkOuter)
{
  // Init the interface's COM object pointer to point to the parent object.
  m_pCO = pCO;

  // Init the CImpIDrawPage interface's delegating IUnknown pointer.  We
  // use the main Object pointer for IUnknown delegation here if we are
  // not being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpIDrawPage lifetime is
  // quaranteed by the lifetime of the parent object in which
  // CImpIDrawPage is nested.
  if (NULL == pUnkOuter)
    m_pUnkOuter = pCO;
  else
    m_pUnkOuter = pUnkOuter;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIDrawPage::~CImpIDrawPage

  Summary:  Destructor for the CImpIDrawPage interface instantiation.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CODrawPage::CImpIDrawPage::~CImpIDrawPage(void)
{
  INKDATA* paInkData;

  // NULL the pointer first and then delete the entire ink data array.
  paInkData = m_pCO->m_paInkData;
  m_pCO->m_paInkData = NULL;
  if (NULL != paInkData)
    delete [] paInkData;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIDrawPage::QueryInterface

  Summary:  The QueryInterface IUnknown member of this IDrawPage interface
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
STDMETHODIMP CODrawPage::CImpIDrawPage::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIDrawPage::AddRef

  Summary:  The AddRef IUnknown member of this IDrawPage interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CODrawPage::CImpIDrawPage::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIDrawPage::Release

  Summary:  The Release IUnknown member of this IDrawPage interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) CODrawPage::CImpIDrawPage::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIDrawPage::NextSlot

  Summary:  An internal private utility member method to increment to the
            next slot in the dynamic Ink Data array. NextSlot will expand
            the dynamic array for more entries if needed.

  Args:     void

  Modifies: m_lInkDataEnd, m_lInkDataMax, m_paInkData.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CODrawPage::CImpIDrawPage::NextSlot(
                               void)
{
  HRESULT hr = NOERROR;
  LONG lInkDataEnd = m_pCO->m_lInkDataEnd + 1;
  INKDATA* paInkData;

  if (lInkDataEnd >= m_pCO->m_lInkDataMax)
  {
    // No more room in Ink Data array. Allocate new space.
    paInkData = new INKDATA[(LONG) (m_pCO->m_lInkDataMax + INKDATA_ALLOC)];
    if (NULL != paInkData)
    {
      // Copy the content of the old full array to the new larger array.
      memcpy(paInkData, m_pCO->m_paInkData, lInkDataEnd * sizeof(INKDATA));

      // Zero (& mark as empty) the expanded portion of the new array.
      memset(&paInkData[lInkDataEnd], 0, INKDATA_ALLOC * sizeof(INKDATA));

      // New larger array is ready--delete the old array.
      delete [] m_pCO->m_paInkData;

      // Rig the to use the new larger array.
      m_pCO->m_paInkData = paInkData;

      // Calculate the new max index.
      m_pCO->m_lInkDataMax += INKDATA_ALLOC;
    }
    else
      hr = E_OUTOFMEMORY;
  }

  if (SUCCEEDED(hr))
  {
    m_pCO->m_lInkDataEnd = lInkDataEnd;
    // NextSlot always preceeds the addition of new drawing data.
    // So use this convenient common place to set the dirty flag.
    m_pCO->m_bDirty = TRUE;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIDrawPage::InkStart

  Summary:  The InkStart member method of the IDrawPage interface
            implementation. Called by outside clients of a CODrawPage
            object to start an ink drawing sequence (ie, a stroke).

  Args:     SHORT nX,
              The X coordinate of the ink point.
            SHORT nY,
              The Y coordinate of the ink point.
            SHORT nInkWidth,
              The width of the ink in pixels.
            COLORREF crInkColor);
              The new ink color--an RGB COLORREF color.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPage::CImpIDrawPage::InkStart(
               SHORT nX,
               SHORT nY,
               SHORT nInkWidth,
               COLORREF crInkColor)
{
  HRESULT hr = E_FAIL;

  hr = NextSlot();
  if (SUCCEEDED(hr))
  {
    // Add the new item to the Ink Data Array.
    m_pCO->m_paInkData[m_pCO->m_lInkDataEnd].nType = INKTYPE_START;
    m_pCO->m_paInkData[m_pCO->m_lInkDataEnd].nX = nX;
    m_pCO->m_paInkData[m_pCO->m_lInkDataEnd].nY = nY;
    m_pCO->m_paInkData[m_pCO->m_lInkDataEnd].nWidth = nInkWidth;
    m_pCO->m_paInkData[m_pCO->m_lInkDataEnd].crColor = crInkColor;
    m_pCO->m_nInkWidth = nInkWidth;
    m_pCO->m_crInkColor = crInkColor;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIDrawPage::InkDraw

  Summary:  The InkDraw member method of the IDrawPage interface
            implementation. Called by outside clients of a CODrawPage
            object to "draw" ink data into an inking sequence. Adds
            ink points to the current stroke.

  Args:     SHORT nX,
              The X coordinate of the ink point.
            SHORT nY,
              The Y coordinate of the ink point.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPage::CImpIDrawPage::InkDraw(
               SHORT nX,
               SHORT nY)
{
  HRESULT hr = E_FAIL;

  hr = NextSlot();
  if (SUCCEEDED(hr))
  {
    // Add the new item to the Ink Data Array.
    m_pCO->m_paInkData[m_pCO->m_lInkDataEnd].nType = INKTYPE_DRAW;
    m_pCO->m_paInkData[m_pCO->m_lInkDataEnd].nX = nX;
    m_pCO->m_paInkData[m_pCO->m_lInkDataEnd].nY = nY;
    m_pCO->m_paInkData[m_pCO->m_lInkDataEnd].nWidth = m_pCO->m_nInkWidth;
    m_pCO->m_paInkData[m_pCO->m_lInkDataEnd].crColor = m_pCO->m_crInkColor;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIDrawPage::InkStop

  Summary:  The InkStop member method of the IDrawPage interface
            implementation. Called by outside clients of a CODrawPage
            object to stop the current ink drawing sequence. Ends the
            current stroke.

  Args:     SHORT nX,
              The X coordinate of the ink point.
            SHORT nY,
              The Y coordinate of the ink point.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPage::CImpIDrawPage::InkStop(
               SHORT nX,
               SHORT nY)
{
  HRESULT hr = E_FAIL;

  hr = NextSlot();
  if (SUCCEEDED(hr))
  {
    // Add the new item to the Ink Data Array.
    m_pCO->m_paInkData[m_pCO->m_lInkDataEnd].nType = INKTYPE_STOP;
    m_pCO->m_paInkData[m_pCO->m_lInkDataEnd].nX = nX;
    m_pCO->m_paInkData[m_pCO->m_lInkDataEnd].nY = nY;
    m_pCO->m_paInkData[m_pCO->m_lInkDataEnd].nWidth = m_pCO->m_nInkWidth;
    m_pCO->m_paInkData[m_pCO->m_lInkDataEnd].crColor = m_pCO->m_crInkColor;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIDrawPage::Clear

  Summary:  The Clear member method of the IDrawPage interface
            implementation. Called by outside clients of a CODrawPage
            object to clear the drawn ink content of the DrawPage object.
            Notifies all connected clients of the event.

  Args:     BOOL bSaveNeeded
              Specifies whether the cleared draw page should later be
              saved to file. TRUE=>later save needed; FALSE=>later save
              not needed.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPage::CImpIDrawPage::Clear(
               BOOL bSaveNeeded)
{
  HRESULT hr = NOERROR;
  LONG i;

  if (m_pCO->m_lInkDataEnd > 0 && NULL != m_pCO->m_paInkData)
  {
    // Loop thru the current Ink Data array and mark each
    // item as erased.
    for (i=0; i<m_pCO->m_lInkDataMax; i++)
      m_pCO->m_paInkData[i].nType = INKTYPE_NONE;

    // Reset the Ink Data End index to 0.
    m_pCO->m_lInkDataEnd = 0;
  }

  // Specify if a later save to file is needed.
  m_pCO->m_bDirty = bSaveNeeded;

  // Notify all other connected clients of the clear.
  if (SUCCEEDED(hr))
    m_pCO->NotifySinks(DRAWPAGE_EVENT_CLEARED, 0, 0, 0, 0);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIDrawPage::Resize

  Summary:  The Resize member method of the IDrawPage interface
            implementation. Called by outside clients of a CODrawPage
            object to resize the drawing rectangle of the DrawPage object.
            Notifies all connected clients of the event and passes them
            the new rectangle size.

  Args:     SHORT nWidth,
              The new rectangle width in pixels.
            SHORT nHeight
              The new rectangle height in pixels.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPage::CImpIDrawPage::Resize(
               SHORT nWidth,
               SHORT nHeight)
{
  HRESULT hr = NOERROR;

  if (m_pCO->m_WinRect.right != nWidth
      || m_pCO->m_WinRect.bottom != nHeight)
  {
    m_pCO->m_WinRect.top = 0;
    m_pCO->m_WinRect.left = 0;
    m_pCO->m_WinRect.right = nWidth;
    m_pCO->m_WinRect.bottom = nHeight;

    // For future evolution.
    // m_pCO->m_bDirty = TRUE;
  }

  // Notify all other connected clients of the Resize.
  m_pCO->NotifySinks(
           DRAWPAGE_EVENT_RESIZED,
           nWidth,
           nHeight,
           0,
           0);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CODrawPage::CImpIDrawPage::Redraw

  Summary:  The Redraw member method of the IDrawPage interface
            implementation. Called by outside clients of a CODrawPage
            object to resend all of the DrawPage object's current ink data
            to all connected clients for a redraw of the content in each.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CODrawPage::CImpIDrawPage::Redraw(
               void)
{
  HRESULT hr = E_FAIL;
  IConnectionPoint* pIConnectionPoint;
  IEnumConnections* pIEnum;
  CONNECTDATA ConnData;
  SHORT nInkType;
  LONG i;

  // Broadcast InkData notifications to all Sinks connected to
  // each connection point.

  // Here is the section for the DrawPageSink connection point--currently
  // this is the only connection point offered by CODrawPage objects.
  pIConnectionPoint = m_pCO->m_aConnectionPoints[CONNPOINT_DRAWPAGESINK];
  if (NULL != pIConnectionPoint)
  {
    pIConnectionPoint->AddRef();
    hr = pIConnectionPoint->EnumConnections(&pIEnum);
    if (SUCCEEDED(hr))
    {
      // Loop thru the connection point's connections and if the
      // listening connection supports IDrawPageSink (ie, DrawPageSink
      // events) then send all the current DrawPage's Ink Data to it.
      while (NOERROR == pIEnum->Next(1, &ConnData, NULL))
      {
        IDrawPageSink* pIDrawPageSink = NULL;

        hr = ConnData.pUnk->QueryInterface(
                              IID_IDrawPageSink,
                              (PPVOID)&pIDrawPageSink);
        if (SUCCEEDED(hr))
        {
          // Loop thru all the Ink Data and send it to this connected
          // client sink.
          for (i=0; i<m_pCO->m_lInkDataEnd+1; i++)
          {
            nInkType = m_pCO->m_paInkData[i].nType;
            switch (nInkType)
            {
              case INKTYPE_DRAW:
                pIDrawPageSink->InkDraw(
                                  m_pCO->m_paInkData[i].nX,
                                  m_pCO->m_paInkData[i].nY);
                break;
              case INKTYPE_START:
                pIDrawPageSink->InkStart(
                                  m_pCO->m_paInkData[i].nX,
                                  m_pCO->m_paInkData[i].nY,
                                  m_pCO->m_paInkData[i].nWidth,
                                  m_pCO->m_paInkData[i].crColor);
                break;
              case INKTYPE_STOP:
                pIDrawPageSink->InkStop(
                                  m_pCO->m_paInkData[i].nX,
                                  m_pCO->m_paInkData[i].nY);
                break;
              default:
                break;
            }
          }
          pIDrawPageSink->Release();
        }
        ConnData.pUnk->Release();
      }
      pIEnum->Release();
    }
    pIConnectionPoint->Release();
  }

  return hr;
}
