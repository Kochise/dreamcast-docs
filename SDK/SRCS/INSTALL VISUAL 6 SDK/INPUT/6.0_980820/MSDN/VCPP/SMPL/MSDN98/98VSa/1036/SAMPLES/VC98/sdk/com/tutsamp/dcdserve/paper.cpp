/*+==========================================================================
  File:      PAPER.CPP

  Summary:   Implementation file for the COPaper COM Object Class (for
             connectable COPaper COM Objects). This module provides a
             thread-safe virtual drawing Paper object. COPaper
             encapsulates into a COM object the behavior of an electronic
             sheet of white drawing paper. The client can use the native
             ISharePaper interface to draw free-form ink lines on the paper
             surface. No GUI behavior is provided within COPaper--it only
             provides the semantics of the virtual paper sheet and manages
             the ink data for the drawing done there.

             APPUTIL's CThreaded OwnThis technology is used in COPaper to
             ensure mutually exclusive access by contending multiple
             client threads.

             Connectable object technology is used in COPaper to notify
             connected clients of various events like when a load of new
             data is completed.

             COPaper offers a main standard IUnknown interface (basic COM
             object features), the standard IConnectionPointContainer
             interface (connectable COM object features), and the custom
             ISharePaper interface (shared drawing Paper related
             features). This multiple interface COM Object Class is
             achieved via the technique of nested classes.  The
             implementations of the IConnectionPointContainer and
             ISharePaper interfaces are nested inside the COPaper Class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial DCDSERVE.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   COPaper.

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
  We include PAPINT.H and PAPGUIDS.H for the common Paper-related
    Interface class, GUID, and CLSID specifications.
  We include SERVER.H because it has internal class declarations for
    the server's control object.
  We include CONNECT.H for object class declarations for the various
    connection point and connection COM objects used in DCDSERVE.
  We include PAPER.H because it has the COPaper class declarations.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <apputil.h>
#include <papint.h>
#include <papguids.h>
#include "server.h"
#include "connect.h"
#include "paper.h"


/*---------------------------------------------------------------------------
  COPaper's implementation of its main COM object class including
  Constructor, Destructor, and the QueryInterface, AddRef, and Release
  methods of the principal IUnknown interface.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::COPaper

  Summary:  COPaper Constructor. Note the member initializer:
            "m_ImpISharePaper(this, pUnkOuter)" which is used to pass the
            'this' and pUnkOuter pointers of the constructor function to
            the constructor in the instantiation of the implementation of
            the CImpISharePaper interface (which is nested inside this
            present COPaper Object Class). Same technique is used for the
            m_ImpIConnectionPointContainer nested interface
            implementation.

  Args:     IUnknown* pUnkOuter,
              Pointer to the the outer IUnknown.  NULL means this COM Object
              is not being Aggregated.  Non NULL means it is being created
              on behalf of an outside COM object that is reusing it via
              aggregation.
            CServer* pServer)
              Pointer to the server's control object.

  Modifies: m_cRefs, m_pUnkOuter, m_pServer.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPaper::COPaper(
  IUnknown* pUnkOuter,
  CServer* pServer) :
  m_ImpISharePaper(this, pUnkOuter),
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

  // Init the storage file name to empty.
  m_szPapFile[0] = 0;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::~COPaper

  Summary:  COPaper Destructor.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPaper::~COPaper(void)
{
  UINT i;
  IConnectionPoint* pIConnectionPoint;

  // Do final release of the connection point objects.
  // If this isn't the final release, then the client has an outstanding
  // unbalanced reference to a connection point and a memory leak may
  // likely result because the host COPaper object is now going away yet
  // a connection point for this host object will not end up deleting
  // itself (and its connections array).
  for (i=0; i<MAX_CONNECTION_POINTS; i++)
  {
    pIConnectionPoint = m_aConnectionPoints[i];
    RELEASE_INTERFACE(pIConnectionPoint);
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::Init

  Summary:  COPaper initialization method.  Create any necessary arrays,
            structures, and subordinate objects.

  Args:     void

  Modifies: m_aConnectionPoints.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COPaper::Init(void)
{
  HRESULT hr = NOERROR;
  COConnectionPoint* pCOConnPt;

  // Rig this COPaper COM object to be connectable. Assign the connection
  // point array. This object's connection points are determined at
  // compile time--it currently has only one connection point:
  // the CONNPOINT_PAPERSINK connection point. Create a connection
  // point object for this and assign it into the array. This array could
  // easily grow to support additional connection points in the future.

  // First try creating a new connection point object. Pass 'this' as the
  // pHostObj pointer used by the connection point to pass its AddRef and
  // Release calls back to the host connectable object.
  pCOConnPt = new COConnectionPoint(this);
  if (NULL != pCOConnPt)
  {
    // If creation succeeded then initialize it (including creating
    // its initial dynamic connection array).
    hr = pCOConnPt->Init(IID_IPaperSink);

    // If the init succeeded then use QueryInterface to obtain the
    // IConnectionPoint interface on the new connection point object.
    // The interface pointer is assigned directly into the
    // connection point array. The QI also does the needed AddRef.
    if (SUCCEEDED(hr))
      hr = pCOConnPt->QueryInterface(
                        IID_IConnectionPoint,
                        (PPVOID)&m_aConnectionPoints[CONNPOINT_PAPERSINK]);
  }
  else
    hr = E_OUTOFMEMORY;

  // Build a path to where the default shared drawing .PAP file
  // should be. It is assumed to be in the same directory as the
  // EXE server. The file name is the exename with a .PAP extension.
  MakeFamilyPath(
    m_pServer->m_hInstServer,
    m_szPapFile,
    TEXT(PAP_FILE_EXT));

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::QueryInterface

  Summary:  QueryInterface of the COPaper non-delegating IUnknown
            implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaper::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;

  *ppv = NULL;

  if (IID_IUnknown == riid)
    *ppv = this;
  else if (IID_ISharePaper == riid)
    *ppv = &m_ImpISharePaper;
  else if (IID_IConnectionPointContainer == riid)
    *ppv = &m_ImpIConnectionPointContainer;

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
  Method:   COPaper::AddRef

  Summary:  AddRef of the COPaper non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPaper::AddRef(void)
{
  ULONG cRefs;

  if (OwnThis())
  {
    cRefs = ++m_cRefs;

    UnOwnThis();
  }

  return cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::Release

  Summary:  Release of the COPaper non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPaper::Release(void)
{
  ULONG cRefs;

  if (OwnThis())
  {
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
      // COPaper but a good practice because we are aggregatable and
      // may at some point in the future add something entertaining like
      // some Releases to the COPaper destructor. We relinquish thread
      // ownership of this object prior to deleting it--a good practice.
      m_cRefs++;
      UnOwnThis();
      delete this;
    }
    else
      UnOwnThis();
  }

  return cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::NotifySinks

  Summary:  Internal utility method of this COM object used to fire event
            notification calls to all listening connection sinks in the
            client(s).

  Args:     PAPER_EVENT PaperEvent
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
HRESULT COPaper::NotifySinks(
       PAPER_EVENT PaperEvent,
       SHORT nX,
       SHORT nY,
       SHORT nInkWidth,
       COLORREF crInkColor)
{
  HRESULT hr = NOERROR;
  IConnectionPoint* pIConnectionPoint;
  IEnumConnections* pIEnum;
  CONNECTDATA ConnData;

  // If there was a paper event, broadcast appropriate notifications to
  // all Sinks connected to each connection point.
  if (PAPER_EVENT_NONE != PaperEvent)
  {
    // Here is the section for the PaperSink connection point--currently
    // this is the only connection point offered by COPaper objects.
    pIConnectionPoint = m_aConnectionPoints[CONNPOINT_PAPERSINK];
    if (NULL != pIConnectionPoint)
    {
      pIConnectionPoint->AddRef();
      hr = pIConnectionPoint->EnumConnections(&pIEnum);
      if (SUCCEEDED(hr))
      {
        // Loop thru the connection point's connections and if the
        // listening connection supports IPaperSink (ie, PaperSink events)
        // then dispatch the PaperEvent event notification to that sink.
        while (NOERROR == pIEnum->Next(1, &ConnData, NULL))
        {
          IPaperSink* pIPaperSink;

          hr = ConnData.pUnk->QueryInterface(
                                IID_IPaperSink,
                                (PPVOID)&pIPaperSink);
          if (SUCCEEDED(hr))
          {
            switch (PaperEvent)
            {
              case PAPER_EVENT_LOCKED:
                pIPaperSink->Locked();
                break;
              case PAPER_EVENT_UNLOCKED:
                pIPaperSink->Unlocked();
                break;
              case PAPER_EVENT_LOADED:
                pIPaperSink->Loaded();
                break;
              case PAPER_EVENT_SAVED:
                pIPaperSink->Saved();
                break;
              case PAPER_EVENT_INKSTART:
                pIPaperSink->InkStart(nX, nY, nInkWidth, crInkColor);
                break;
              case PAPER_EVENT_INKDRAW:
                pIPaperSink->InkDraw(nX, nY);
                break;
              case PAPER_EVENT_INKSTOP:
                pIPaperSink->InkStop(nX, nY);
                break;
              case PAPER_EVENT_ERASED:
                pIPaperSink->Erased();
                break;
              case PAPER_EVENT_RESIZED:
                pIPaperSink->Resized(nX, nY);
                break;
              default:
                break;
            }
            pIPaperSink->Release();
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
  COPaper's nested implementation of the COM standard
  IConnectionPointContainer interface including Constructor, Destructor,
  QueryInterface, AddRef, Release, FindConnectionPoint, and
  EnumConnectionPoints.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpIConnectionPointContainer
              ::CImpIConnectionPointContainer

  Summary:  Constructor for the CImpIConnectionPointContainer interface
            instantiation.

  Args:     COPaper* pCO,
              Back pointer to the parent outer COM object.
            IUnknown* pUnkOuter
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_pCO, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPaper::CImpIConnectionPointContainer::CImpIConnectionPointContainer(
  COPaper* pCO,
  IUnknown* pUnkOuter)
{
  // Init the Back Object Pointer to point to the parent object.
  m_pCO = pCO;

  // Init the CImpIConnectionPointContainer interface's delegating Unknown
  // pointer.  We use the Back Object pointer for IUnknown delegation here
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
  Method:   COPaper::CImpIConnectionPointContainer
              ::~CImpIConnectionPointContainer

  Summary:  Destructor for the CImpIConnectionPointContainer interface
            instantiation.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPaper::CImpIConnectionPointContainer::~CImpIConnectionPointContainer(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpIConnectionPointContainer::QueryInterface

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
STDMETHODIMP COPaper::CImpIConnectionPointContainer::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpIConnectionPointContainer::AddRef

  Summary:  The AddRef IUnknown member of this interface implementation
            that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPaper::CImpIConnectionPointContainer::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpIConnectionPointContainer::Release

  Summary:  The Release IUnknown member of this interface implementation
            that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPaper::CImpIConnectionPointContainer::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpIConnectionPointContainer::FindConnectionPoint

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
STDMETHODIMP COPaper::CImpIConnectionPointContainer::FindConnectionPoint(
               REFIID riid,
               IConnectionPoint** ppConnPt)
{
  HRESULT hr = E_NOINTERFACE;
  IConnectionPoint* pIConnPt;

  if (OwnThis())
  {
    // NULL the output variable.
    *ppConnPt = NULL;

    pIConnPt = m_pCO->m_aConnectionPoints[CONNPOINT_PAPERSINK];
    if (NULL != pIConnPt)
    {
      // This connectable COPaper object currently has only the Paper Sink
      // connection point. If the associated interface is requested,
      // use QI to get the Connection Point interface and perform the
      // needed AddRef.
      if (IID_IPaperSink == riid)
        hr = pIConnPt->QueryInterface(
                         IID_IConnectionPoint,
                         (PPVOID)ppConnPt);
    }

    UnOwnThis();
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpIConnectionPointContainer::EnumConnectionPoints

  Summary:  Return Enumerator for the connectable object's contained
            connection points.

  Args:     IEnumConnectionPoints** ppIEnum
              Address of the caller's Enumerator interface pointer
              variable. An output variable that will receive a pointer to
              the connection point enumerator COM object.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaper::CImpIConnectionPointContainer::EnumConnectionPoints(
                       IEnumConnectionPoints** ppIEnum)
{
  HRESULT hr = NOERROR;
  IConnectionPoint* aConnPts[MAX_CONNECTION_POINTS];
  COEnumConnectionPoints* pCOEnum;
  UINT i;

  if (OwnThis())
  {
    // Zero the output interface pointer.
    *ppIEnum = NULL;

    // Make a copy on the stack of the array of connection point
    // interfaces. The copy is used below in the creation of the new
    // Enumerator object.
    for (i=0; i<MAX_CONNECTION_POINTS; i++)
      aConnPts[i] = (IConnectionPoint*)m_pCO->m_aConnectionPoints[i];

    // Create a Connection Point enumerator COM object for the connection
    // points offered by this COPaper object. Pass 'this' to be used to
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

    UnOwnThis();
  }

  return hr;
}


/*---------------------------------------------------------------------------
  COPaper's nested implementation of the custom ISharePaper interface
  including Constructor, Destructor, QueryInterface, AddRef, Release,
  Init, Lock, InkStart, InkDraw, InkStop, GetInk, Erase, and Resize.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpISharePaper::CImpISharePaper

  Summary:  Constructor for the CImpISharePaper interface instantiation.

  Args:     COPaper* pCO,
              Back pointer to the parent outer COM object.
            IUnknown* pUnkOuter
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_pCO, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPaper::CImpISharePaper::CImpISharePaper(
  COPaper* pCO,
  IUnknown* pUnkOuter)
{
  // Init the Back Object Pointer to point to the parent object.
  m_pCO = pCO;

  // Init the CImpISharePaper interface's delegating Unknown pointer. We
  // use the main object pointer for IUnknown delegation here if we are not
  // being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpISharePaper lifetime is
  // quaranteed by the lifetime of the parent object in which
  // CImpISharePaper is nested.
  if (NULL == pUnkOuter)
    m_pUnkOuter = pCO;
  else
    m_pUnkOuter = pUnkOuter;

  // Now initialize the living heart of this virtual Paper entity.
  m_ClipBdFmt    = 0;
  m_bLocked      = FALSE;
  m_crWinColor   = RGB(255,255,255); // White
  m_crInkColor   = RGB(0,0,0);       // Black
  m_nInkWidth    = 2;                // 2 pixels wide (thin).
  m_lInkDataEnd  = 0;                // Current drawing data end.
  m_lInkDataMax  = 0;                // Upper bound to m_lInkDataEnd.
  m_paInkData    = NULL;             // Points to Ink data array.

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpISharePaper::~CImpISharePaper

  Summary:  Destructor for the CImpISharePaper interface instantiation.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COPaper::CImpISharePaper::~CImpISharePaper(void)
{
  INKDATA* paInkData;

  // NULL the pointer first and then delete the entire ink data array.
  paInkData = m_paInkData;
  m_paInkData = NULL;
  if (NULL != paInkData)
    delete [] paInkData;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpISharePaper::QueryInterface

  Summary:  The QueryInterface IUnknown member of this ISharePaper
            interface implementation that delegates to m_pUnkOuter,
            whatever it is.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
              Returned by the delegated outer QueryInterface call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaper::CImpISharePaper::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpISharePaper::AddRef

  Summary:  The AddRef IUnknown member of this ISharePaper interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPaper::CImpISharePaper::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpISharePaper::Release

  Summary:  The Release IUnknown member of this ISharePaper interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COPaper::CImpISharePaper::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpISharePaper::InitPaper

  Summary:  The InitPaper member method of the ISharePaper interface
            implementation. Called by outside clients of a COPaper object
            to initialize this shared electronic paper object.

  Args:     RECT* pWinRect
              The initial drawing window rectangle. An [in,out] argument.
            BOOL* pbFirst
              A return value indicating TRUE if this the first client;
              FALSE otherwise. If FALSE caller should set its window
              size to the value pointed to by the returned *pWinRect.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaper::CImpISharePaper::InitPaper(
               RECT* pWinRect,
               BOOL* pbFirst)
{
  HRESULT hr = E_FAIL;
  INKDATA* paInkData;
  BOOL bFirst = (NULL == m_paInkData);

  // Tell caller if this is first ink data array instance to Init.
  if (NULL != pbFirst)
    *pbFirst = bFirst;

  if (OwnThis())
  {
    if (bFirst)
    {
      // Build the initial dynamic array of InkData.
      paInkData = new INKDATA[(LONG) INKDATA_ALLOC_INIT];
      if (NULL != paInkData)
      {
        // Zero the array.
        memset(paInkData, 0, INKDATA_ALLOC_INIT * sizeof(INKDATA));

        // Rig this Paper object so that it can use the Ink Data array.
        m_lInkDataMax = INKDATA_ALLOC_INIT;
        m_paInkData = paInkData;

        // Zero the Paper Properties structure. Init the ink data version.
        memset(&m_PaperProperties, 0, sizeof(PAPER_PROPERTIES));
        m_PaperProperties.lInkDataVersion = INKDATA_VERSION10;

        // Register a clipboard format for these COPaper things.
        m_ClipBdFmt = RegisterClipboardFormat(TEXT(CLIPBDFMT_STR));

        // Assign window rect values from master client.
        m_WinRect.left = 0;
        m_WinRect.top = 0;
        m_WinRect.right = pWinRect->right;
        m_WinRect.bottom = pWinRect->bottom;
        m_PaperProperties.WinRect.right = m_WinRect.right;
        m_PaperProperties.WinRect.bottom = m_WinRect.bottom;
        hr = NOERROR;
      }
      else
        hr = E_OUTOFMEMORY;
    }
    else
    {
      // If not the first init, assign slave client's output rect values.
      pWinRect->left = m_WinRect.left = 0;
      pWinRect->top = m_WinRect.top = 0;
      pWinRect->right = m_WinRect.right = m_PaperProperties.WinRect.right;
      pWinRect->bottom = m_WinRect.bottom = m_PaperProperties.WinRect.bottom;
      hr = NOERROR;
    }

    UnOwnThis();
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpISharePaper::Lock

  Summary:  The Lock member method of the ISharePaper interface
            implementation. Called by outside clients of a COPaper object
            to lock their ownership of the Paper object. COPaper is coded
            for eventual use in a multi-threaded multi- client situation
            where the Lock and Unlock methods permit a client to lock its
            use of a single COPaper object.

  Args:     SHORT* pnLockKey
              Address of a short variable to receive the LockKey.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaper::CImpISharePaper::Lock(
               BOOL bLock)
{
  HRESULT hr = E_FAIL;

  if (OwnThis())
  {
    if (bLock)
    {
      if (!m_bLocked)
      {
        // If the paper is not currently locked then lock it.
        m_bLocked = TRUE;
        hr = NOERROR;
      }
    }
    else
    {
      if (m_bLocked)
      {
        // If the paper is currently locked then set to unlocked state.
        m_bLocked = FALSE;
        hr = NOERROR;
      }
    }

    UnOwnThis();
  }

  // Notify all other connected clients that Paper is now locked/unlocked.
  if (SUCCEEDED(hr))
  {
    if (bLock)
      m_pCO->NotifySinks(PAPER_EVENT_LOCKED, 0, 0, 0, 0);
    else
      m_pCO->NotifySinks(PAPER_EVENT_UNLOCKED, 0, 0, 0, 0);
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpISharePaper::Load

  Summary:  The Load member method of the ISharePaper interface
            implementation. Called by outside clients of a COPaper object
            to Load a new set of ink drawing data onto the Paper surface
            from the current structured storage compound file. Notifies
            all other connected clients when the load is complete.

  Args:     RECT* pWinRect)
              [out] Pointer to RECT that receives the loaded window rect.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaper::CImpISharePaper::Load(
               RECT* pWinRect)
{
  HRESULT hr = E_FAIL;
  IStorage* pIStorage;
  IStream* pIStream;
  INKDATA* paInkData;
  ULONG ulToRead, ulReadIn;
  LONG lNewArraySize;
  PAPER_PROPERTIES NewProps;

  if (OwnThis())
  {
    if (m_bLocked)
    {
      // Use COM service to next check if the file is there and actually
      // a valid compound file.
      hr = StgIsStorageFile(m_pCO->m_szPapFile);
      if (SUCCEEDED(hr))
      {
        // We're go. Use COM service to open the compound file and
        // obtain a IStorage interface.
        hr = StgOpenStorage(
               m_pCO->m_szPapFile,
               NULL,
               STGM_DIRECT | STGM_READ | STGM_SHARE_EXCLUSIVE,
               NULL,
               0,
               &pIStorage);
        if (SUCCEEDED(hr))
        {
          // Open the "PAPERDATA" stream where the paper data is stored.
          hr = pIStorage->OpenStream(
                 STREAM_PAPERDATA_USTR,
                 0,
                 STGM_READ | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
                 0,
                 &pIStream);
          if (SUCCEEDED(hr))
          {
            // We have the paper data stream. First read the Paper
            // Properties.
            ulToRead = sizeof(PAPER_PROPERTIES);
            hr = pIStream->Read(
                             &NewProps,
                             ulToRead,
                             &ulReadIn);
            if (SUCCEEDED(hr) && ulToRead != ulReadIn)
              hr = E_FAIL;
            if (SUCCEEDED(hr))
            {
              // Deal with the different versions of ink data format.
              switch (NewProps.lInkDataVersion)
              {
                case INKDATA_VERSION10:
                  // Allocate an ink data array big enough--add some
                  // extra for user drawing.
                  lNewArraySize = NewProps.lInkArraySize + INKDATA_ALLOC;
                  paInkData = new INKDATA[(LONG) lNewArraySize];
                  if (NULL != paInkData)
                  {
                    // Delete the entire old ink data array.
                    delete [] m_paInkData;

                    // Assign the new array.
                    m_paInkData = paInkData;
                    m_lInkDataMax = lNewArraySize;

                    // Now read the complete array of Ink Data.
                    ulToRead = NewProps.lInkArraySize * sizeof(INKDATA);
                    hr = pIStream->Read(m_paInkData, ulToRead, &ulReadIn);
                    if (SUCCEEDED(hr) && ulToRead != ulReadIn)
                      hr = E_FAIL;
                    if (SUCCEEDED(hr))
                    {
                      // Rig COPaper to use the PAPER_PROPERTIES info.
                      m_lInkDataEnd = NewProps.lInkArraySize-1;
                      m_crWinColor = NewProps.crWinColor;
                      m_WinRect.right = NewProps.WinRect.right;
                      m_WinRect.bottom = NewProps.WinRect.bottom;

                      // Copy the newly loaded drawing's window rectangle
                      // size for use by the caller.
                      pWinRect->left = NewProps.WinRect.left;
                      pWinRect->top = NewProps.WinRect.top;
                      pWinRect->right = NewProps.WinRect.right;
                      pWinRect->bottom = NewProps.WinRect.bottom;

                      // Copy the new properties into current properties.
                      memcpy(
                        &m_PaperProperties,
                        &NewProps,
                        sizeof(PAPER_PROPERTIES));
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

            // We are done with the stream so release it.
            pIStream->Release();
          }

          // We are done with the storage so release it.
          // We don't hold the file open. We reopen it as needed.
          pIStorage->Release();
        }
      }
      else
      {
        // Erase();
        hr = Save();
      }
    }

    UnOwnThis();
  }

  // Notify all other connected clients that Paper is now loaded.
  // If we didn't load then erase to a safe, empty ink data array.
  if (SUCCEEDED(hr))
    m_pCO->NotifySinks(PAPER_EVENT_LOADED, 0, 0, 0, 0);
  else
    Erase();

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpISharePaper::Save

  Summary:  The Save member method of the ISharePaper interface
            implementation. Called by outside clients of a COPaper object
            to Save the current set of ink drawing data from the Paper
            surface to the current compound file storage. Notifies all
            other connected clients when the save is complete.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaper::CImpISharePaper::Save(
               void)
{
  HRESULT hr = E_FAIL;
  IStorage* pIStorage;
  IStream* pIStream;
  ULONG ulToWrite, ulWritten;

  if (OwnThis())
  {
    if (m_bLocked)
    {
      // Use COM service to re-open (or newly create) the compound file.
      hr = StgCreateDocfile(
             m_pCO->m_szPapFile,
             STGM_CREATE | STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
             0,
             &pIStorage);
      if (SUCCEEDED(hr))
      {
        // First use COM service to mark this compound file as one that is
        // handled by our server component, SharePaper.
        WriteClassStg(pIStorage, CLSID_SharePaper);

        // Use COM Service to write user-readable clipboard format into
        // the compound file.
        WriteFmtUserTypeStg(pIStorage, m_ClipBdFmt, TEXT(CLIPBDFMT_STR));

        // Create the stream to be used for the actual paper data.
        // Call it "PAPERDATA".
        hr = pIStorage->CreateStream(
               STREAM_PAPERDATA_USTR,
               STGM_CREATE | STGM_WRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
               0,
               0,
               &pIStream);
        if (SUCCEEDED(hr))
        {
          // Got a stream. Now write data into it.
          // First write PAPER_PROPERTIES structure.
          m_PaperProperties.lInkArraySize = m_lInkDataEnd+1;
          m_PaperProperties.crWinColor = m_crWinColor;
          m_PaperProperties.WinRect.right = m_WinRect.right;
          m_PaperProperties.WinRect.bottom = m_WinRect.bottom;
          ulToWrite = sizeof(PAPER_PROPERTIES);
          hr = pIStream->Write(&m_PaperProperties, ulToWrite, &ulWritten);
          if (SUCCEEDED(hr) && ulToWrite != ulWritten)
            hr = STG_E_CANTSAVE;
          if (SUCCEEDED(hr))
          {
            // Now write the complete array of Ink Data.
            ulToWrite = m_PaperProperties.lInkArraySize * sizeof(INKDATA);
            hr = pIStream->Write(m_paInkData, ulToWrite, &ulWritten);
            if (SUCCEEDED(hr) && ulToWrite != ulWritten)
              hr = STG_E_CANTSAVE;
          }

          // We are done with the stream so release it.
          pIStream->Release();
        }

        // We are done with the storage so release it.
        // We don't hold the file open. We reopen it as needed.
        pIStorage->Release();
      }
    }

    UnOwnThis();
  }

  // Notify all other connected clients that Paper is now saved.
  if (SUCCEEDED(hr))
    m_pCO->NotifySinks(PAPER_EVENT_SAVED, 0, 0, 0, 0);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpISharePaper::NextSlot

  Summary:  An internal private utility member method to increment to the
            next slot in the dynamic Ink Data array. NextSlot will expand
            the dynamic array for more entries if needed. To guarantee
            thread safety, this private method should always be called
            within the protection of a bracketed OwnThis, UnOwnThis pair.

  Args:     void

  Modifies: m_lInkDataEnd, m_lInkDataMax, m_paInkData.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COPaper::CImpISharePaper::NextSlot(
                               void)
{
  HRESULT hr = NOERROR;
  LONG lInkDataEnd = m_lInkDataEnd + 1;
  INKDATA* paInkData;

  if (lInkDataEnd >= m_lInkDataMax)
  {
    // No more room in Ink Data array. Allocate new space.
    paInkData = new INKDATA[(LONG) (m_lInkDataMax + INKDATA_ALLOC)];
    if (NULL != paInkData)
    {
      // Copy the content of the old full array to the new larger array.
      memcpy(paInkData, m_paInkData, lInkDataEnd * sizeof(INKDATA));

      // Zero (& mark as empty) the expanded portion of the new array.
      memset(&paInkData[lInkDataEnd], 0, INKDATA_ALLOC * sizeof(INKDATA));

      // New larger array is ready--delete the old array.
      delete [] m_paInkData;

      // Rig the to use the new larger array.
      m_paInkData = paInkData;

      // Calculate the new max index.
      m_lInkDataMax += INKDATA_ALLOC;
    }
    else
      hr = E_OUTOFMEMORY;
  }

  if (SUCCEEDED(hr))
    m_lInkDataEnd = lInkDataEnd;

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpISharePaper::InkStart

  Summary:  The InkStart member method of the ISharePaper interface
            implementation. Called by outside clients of a COPaper object
            to start an ink drawing sequence.

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
STDMETHODIMP COPaper::CImpISharePaper::InkStart(
               SHORT nX,
               SHORT nY,
               SHORT nInkWidth,
               COLORREF crInkColor)
{
  HRESULT hr = E_FAIL;

  if (OwnThis())
  {
    if (m_bLocked)
    {
      hr = NextSlot();
      if (SUCCEEDED(hr))
      {
        // Add the new item to the Ink Data Array.
        m_paInkData[m_lInkDataEnd].nType = INKTYPE_START;
        m_paInkData[m_lInkDataEnd].nX = nX;
        m_paInkData[m_lInkDataEnd].nY = nY;
        m_paInkData[m_lInkDataEnd].nWidth = nInkWidth;
        m_paInkData[m_lInkDataEnd].crColor = crInkColor;
        m_nInkWidth = nInkWidth;
        m_crInkColor = crInkColor;
        m_pCO->NotifySinks(
          PAPER_EVENT_INKSTART,
          nX,
          nY,
          nInkWidth,
          crInkColor);
      }
    }

    UnOwnThis();
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpISharePaper::InkDraw

  Summary:  The InkDraw member method of the ISharePaper interface
            implementation. Called by outside clients of a COPaper object
            to "draw" ink data into an inking sequence.

  Args:     SHORT nX,
              The X coordinate of the ink point.
            SHORT nY,
              The Y coordinate of the ink point.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaper::CImpISharePaper::InkDraw(
               SHORT nX,
               SHORT nY)
{
  HRESULT hr = E_FAIL;

  if (OwnThis())
  {
    if (m_bLocked)
    {
      hr = NextSlot();
      if (SUCCEEDED(hr))
      {
        // Add the new item to the Ink Data Array.
        m_paInkData[m_lInkDataEnd].nType = INKTYPE_DRAW;
        m_paInkData[m_lInkDataEnd].nX = nX;
        m_paInkData[m_lInkDataEnd].nY = nY;
        m_paInkData[m_lInkDataEnd].nWidth = m_nInkWidth;
        m_paInkData[m_lInkDataEnd].crColor = m_crInkColor;
        m_pCO->NotifySinks(PAPER_EVENT_INKDRAW, nX, nY, 0, 0);
      }
    }

    UnOwnThis();
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpISharePaper::InkStop

  Summary:  The InkStop member method of the ISharePaper interface
            implementation. Called by outside clients of a COPaper object
            to stop the current ink drawing sequence.

  Args:     SHORT nX,
              The X coordinate of the ink point.
            SHORT nY,
              The Y coordinate of the ink point.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaper::CImpISharePaper::InkStop(
               SHORT nX,
               SHORT nY)
{
  HRESULT hr = E_FAIL;

  if (OwnThis())
  {
    if (m_bLocked)
    {
      hr = NextSlot();
      if (SUCCEEDED(hr))
      {
        // Add the new item to the Ink Data Array.
        m_paInkData[m_lInkDataEnd].nType = INKTYPE_STOP;
        m_paInkData[m_lInkDataEnd].nX = nX;
        m_paInkData[m_lInkDataEnd].nY = nY;
        m_paInkData[m_lInkDataEnd].nWidth = m_nInkWidth;
        m_paInkData[m_lInkDataEnd].crColor = m_crInkColor;
        m_pCO->NotifySinks(PAPER_EVENT_INKSTOP, nX, nY, 0, 0);
      }
    }

    UnOwnThis();
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpISharePaper::GetInk

  Summary:  The GetInk member method of the ISharePaper interface
            implementation. Called by outside clients of a COPaper object
            to obtain all content of the ink data array for redisplay.

  Args:     LONG iIndex
              Array index starting at 0.
            SHORT* pnInkType,
              Address of the type of the ink item.
            SHORT* pnX,
              Address of the The X coordinate of the ink point.
            SHORT* pnY,
              Address of the The Y coordinate of the ink point.
            SHORT* pnInkWidth,
              Address of the width of the ink in pixels.
            COLORREF* pcrInkColor)
              Address of the new ink color--an RGB COLORREF color.

  Returns:  HRESULT
              Standard result code. NOERROR for success. E_FAIL when
              no ink data for the index.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaper::CImpISharePaper::GetInk(
               LONG iIndex,
               SHORT* pnInkType,
               SHORT* pnX,
               SHORT* pnY,
               SHORT* pnInkWidth,
               COLORREF* pcrInkColor)
{
  HRESULT hr = NOERROR;

  if (OwnThis())
  {
    if (iIndex < m_lInkDataEnd+1)
    {
      *pnInkType = m_paInkData[iIndex].nType;
      *pnX = m_paInkData[iIndex].nX;
      *pnY = m_paInkData[iIndex].nY;
      *pnInkWidth = m_paInkData[iIndex].nWidth;
      *pcrInkColor = m_paInkData[iIndex].crColor;
    }
    else
      hr = E_FAIL;

    UnOwnThis();
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpISharePaper::Erase

  Summary:  The Erase member method of the ISharePaper interface
            implementation. Called by outside clients of a COPaper object
            to erase the drawn ink content of the paper object. Notifies
            all connected clients of the event.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaper::CImpISharePaper::Erase(
               void)
{
  HRESULT hr = E_FAIL;
  LONG i;

  if (OwnThis())
  {
    if (m_bLocked)
    {
      if (m_lInkDataEnd > 0 && NULL != m_paInkData)
      {
        // Loop thru the current Ink Data array and mark each
        // item as erased.
        for (i=0; i<m_lInkDataMax; i++)
          m_paInkData[i].nType = INKTYPE_NONE;

        // Reset the Ink Data End index to 0.
        m_lInkDataEnd = 0;
        hr = NOERROR;
      }
    }

    UnOwnThis();
  }

  // Notify all other connected clients of the erase.
  if (SUCCEEDED(hr))
    m_pCO->NotifySinks(PAPER_EVENT_ERASED, 0, 0, 0, 0);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COPaper::CImpISharePaper::Resize

  Summary:  The Resize member method of the ISharePaper interface
            implementation. Called by outside clients of a COPaper object
            to resize the drawing rectangle of the paper object. Notifies
            all connected clients of the event and passes them the new
            rectangle size.

  Args:     LONG lWidth,
              The new rectangle width in pixels.
            LONG lHeight
              The new rectangle height in pixels.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COPaper::CImpISharePaper::Resize(
               LONG lWidth,
               LONG lHeight)
{
  HRESULT hr = E_FAIL;

  if (OwnThis())
  {
    if (m_bLocked)
    {
      m_WinRect.top = 0;
      m_WinRect.left = 0;
      m_WinRect.right = lWidth;
      m_WinRect.bottom = lHeight;
      m_PaperProperties.WinRect.top = 0;
      m_PaperProperties.WinRect.left = 0;
      m_PaperProperties.WinRect.right = lWidth;
      m_PaperProperties.WinRect.bottom = lHeight;
      hr = NOERROR;
    }

    UnOwnThis();
  }

  // Notify all other connected clients of the resize.
  if (SUCCEEDED(hr))
    m_pCO->NotifySinks(
             PAPER_EVENT_RESIZED,
             (SHORT)lWidth,
             (SHORT)lHeight,
             0,
             0);

  return hr;
}
