/*+==========================================================================
  File:      TEXTPAGE.CPP

  Summary:   Implementation file for the COTextPage COM Object Class (for
             connectable COTextPage COM Objects). COTextPage encapsulates
             into a COM object the behavior of a page of editable text.
             The client can use the native ITextPage interface to get and
             put the text of the text page into the object. No GUI
             behavior is provided within COTextPage--it only provides a
             persistent data management for the text page.

             Connectable object technology is used in COTextPage to notify
             connected clients of various events like when a load of new
             text data is completed.

             COTextPage offers a main standard IUnknown interface (basic
             COM object features), the standard IConnectionPointContainer
             interface (connectable COM object features), the standard
             IPersistStreamInit (Stream persistent object features), and
             the custom ITextPage interface (TextPage related features).
             This multiple interface COM Object Class is achieved via the
             technique of nested classes.  The implementations of the
             various interfaces are nested inside the COTextPage Class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial PERTEXT.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   COTextPage.

  Functions: none.

  Origin:    5-18-97: atrent - Editor-inheritance from PAPER.CPP in
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
  We include IPAGES.H and PAGEGUID.H for the common TextPage-related
    Interface class, GUID, and CLSID specifications.
  We include SERVER.H because it has internal class declarations for
    the server's control object.
  We include CONNECT.H for object class declarations for the various
    connection point and connection COM objects used in PERSERVE.
  We include TEXTPAGE.H because it has the COTextPage class declarations.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <apputil.h>
#include <ipages.h>
#include <pageguid.h>
#include "server.h"
#include "connect.h"
#include "textpage.h"


/*---------------------------------------------------------------------------
  COTextPage's implementation of its main COM object class including
  Constructor, Destructor, QueryInterface, AddRef, and Release.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::COTextPage

  Summary:  COTextPage Constructor. Note the member initializers like:
            "m_ImpITextPage(this, pUnkOuter)" which is used to pass the
            'this' and pUnkOuter pointers of the constructor function to
            the constructor in the instantiation of the implementation of
            the CImpITextPage interface (which is nested inside this present
            COTextPage Object Class). Same technique is used for the other
            nested interface implementations.

  Args:     IUnknown* pUnkOuter,
              Pointer to the the outer Unknown.  NULL means this COM Object
              is not being Aggregated.  Non-NULL means it is being created
              on behalf of an outside COM object that is reusing it via
              aggregation.
            CServer* pServer)
              Pointer to the server's control object.

  Modifies: m_cRefs, m_pUnkOuter, m_pServer.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COTextPage::COTextPage(
  IUnknown* pUnkOuter,
  CServer* pServer) :
  m_ImpITextPage(this, pUnkOuter),
  m_ImpIPersistStreamInit(this, pUnkOuter),
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

  // Now initialize the TextPage itself.
  m_pwszPageText = NULL;
  m_ClassID = CLSID_TextPage;
  m_bInitNew = FALSE;
  m_bDirty = TRUE;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::~COTextPage

  Summary:  COTextPage Destructor.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COTextPage::~COTextPage(void)
{
  UINT i;
  IConnectionPoint* pIConnectionPoint;

  // Do final release of the connection point objects.
  for (i=0; i<MAX_CONNECTION_POINTS; i++)
  {
    pIConnectionPoint = m_aConnectionPoints[i];
    RELEASE_INTERFACE(pIConnectionPoint);
  }

  DELETE_POINTER(m_pwszPageText);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::Init

  Summary:  COTextPage initialization method.  Create any necessary
            arrays, structures, and subordinate objects. Rig connectivity.

  Args:     void

  Modifies: m_aConnectionPoints.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COTextPage::Init(void)
{
  HRESULT hr = NOERROR;
  COConnectionPoint* pCOConnPt;

  // Rig this new COTextPage COM object to be connectable. Assign the
  // connection point array. This object's connection points are
  // determined at compile time--it currently has only one connection
  // point: the CONNPOINT_TEXTPAGESINK connection point. Create a
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
    hr = pCOConnPt->Init(IID_ITextPageSink);

    // If the init succeeded then use QueryInterface to obtain the
    // IConnectionPoint interface on the new connection point object.
    // The interface pointer is assigned directly into the
    // connection point array. The QI also does the needed AddRef.
    if (SUCCEEDED(hr))
    {
      hr = pCOConnPt->QueryInterface(
             IID_IConnectionPoint,
             (PPVOID)&m_aConnectionPoints[CONNPOINT_TEXTPAGESINK]);
    }

    if (FAILED(hr))
      delete pCOConnPt;
  }
  else
    hr = E_OUTOFMEMORY;

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::QueryInterface

  Summary:  QueryInterface of the COTextPage non-delegating IUnknown
            implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COTextPage::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;

  *ppv = NULL;

  if (IID_IUnknown == riid)
    *ppv = this;
  else if (IID_IConnectionPointContainer == riid)
    *ppv = &m_ImpIConnectionPointContainer;
  else if (IID_IPersistStreamInit == riid)
    *ppv = &m_ImpIPersistStreamInit;
  else if (IID_ITextPage == riid)
    *ppv = &m_ImpITextPage;

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
  Method:   COTextPage::AddRef

  Summary:  AddRef of the COTextPage non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COTextPage::AddRef(void)
{
  ULONG cRefs;

  cRefs = ++m_cRefs;

  return cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::Release

  Summary:  Release of the COTextPage non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COTextPage::Release(void)
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
    // COTextPage but a good practice because we are aggregatable and
    // may at some point in the future add something entertaining like
    // some Releases to the COTextPage destructor. We relinquish thread
    // ownership of this object prior to deleting it--a good practice.
    m_cRefs++;
    delete this;
  }

  return cRefs;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::Clear

  Summary:  Internal private utility method of this COM object used to
            clear the content of the text page.

  Args:     BOOL bSaveNeeded
              Specifies whether the cleared text page should later be
              saved to file. TRUE=>later save needed; FALSE=>later save
              not needed.

  Modifies: m_pwszPageText.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COTextPage::Clear(
          BOOL bSaveNeeded)
{
  HRESULT hr = NOERROR;

  // Zero the text string array.
  if (NULL != m_pwszPageText)
    memset(m_pwszPageText, 0, TEXTPAGE_V10_MAX * sizeof(WCHAR));

  // Set the Page Properties for this version of TextPages.
  m_TextProps.ulVersion = TEXTPAGE_VERSION10;
  m_TextProps.ulMaxLength = TEXTPAGE_V10_MAX;
  m_TextProps.ulLength = 0;

  // Mark TextPage as dirty (ie, needs to be saved to file) if specified.
  m_bDirty = bSaveNeeded;

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::NotifySinks

  Summary:  Internal utility method of this COM object used to fire event
            notification calls to all listening connection sinks in the
            client.

  Args:     TEXTPAGE_EVENT TextPageEvent
              Type of TextPage notification event.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COTextPage::NotifySinks(
       TEXTPAGE_EVENT TextPageEvent)
{
  HRESULT hr = NOERROR;
  IConnectionPoint* pIConnectionPoint;
  IEnumConnections* pIEnum;
  CONNECTDATA ConnData;

  // If there was a TextPage event, broadcast appropriate notifications to
  // all Sinks connected to each connection point.
  if (TEXTPAGE_EVENT_NONE != TextPageEvent)
  {
    // Here is the section for the TextPageSink connection point--currently
    // this is the only connection point offered by COTextPage objects.
    pIConnectionPoint = m_aConnectionPoints[CONNPOINT_TEXTPAGESINK];
    if (NULL != pIConnectionPoint)
    {
      pIConnectionPoint->AddRef();
      hr = pIConnectionPoint->EnumConnections(&pIEnum);
      if (SUCCEEDED(hr))
      {
        // Loop thru the connection point's connections and if the
        // listening connection supports ITextPageSink (ie, TextPageSink
        // events) then dispatch the TextPageEvent event notification to
        // that sink.
        while (NOERROR == pIEnum->Next(1, &ConnData, NULL))
        {
          ITextPageSink* pITextPageSink;

          hr = ConnData.pUnk->QueryInterface(
                                IID_ITextPageSink,
                                (PPVOID)&pITextPageSink);
          if (SUCCEEDED(hr))
          {
            switch (TextPageEvent)
            {
              case TEXTPAGE_EVENT_LOADED:
                pITextPageSink->Loaded();
                break;
              case TEXTPAGE_EVENT_SAVED:
                pITextPageSink->Saved();
                break;
              case TEXTPAGE_EVENT_PUT:
                pITextPageSink->Put();
                break;
              case TEXTPAGE_EVENT_CLEARED:
                pITextPageSink->Cleared();
                break;
              default:
                break;
            }
            pITextPageSink->Release();
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
  COTextPage's nested implementation of the COM standard
  IConnectionPointContainer interface including Constructor, Destructor,
  QueryInterface, AddRef, Release, FindConnectionPoint, and
  EnumConnectionPoints.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpIConnectionPointContainer
              ::CImpIConnectionPointContainer

  Summary:  Constructor for the CImpIConnectionPointContainer interface
            instantiation.

  Args:     COTextPage* pCO,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_pCO, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COTextPage::CImpIConnectionPointContainer::CImpIConnectionPointContainer(
  COTextPage* pCO,
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
  Method:   COTextPage::CImpIConnectionPointContainer
              ::~CImpIConnectionPointContainer

  Summary:  Destructor for the CImpIConnectionPointContainer interface
            instantiation.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COTextPage::CImpIConnectionPointContainer::~CImpIConnectionPointContainer(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpIConnectionPointContainer::QueryInterface

  Summary:  The QueryInterface IUnknown member of this ITextPage interface
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
STDMETHODIMP COTextPage::CImpIConnectionPointContainer::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpIConnectionPointContainer::AddRef

  Summary:  The AddRef IUnknown member of this ITextPage interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COTextPage::CImpIConnectionPointContainer::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpIConnectionPointContainer::Release

  Summary:  The Release IUnknown member of this ITextPage interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COTextPage::CImpIConnectionPointContainer::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpIConnectionPointContainer::FindConnectionPoint

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
STDMETHODIMP COTextPage::CImpIConnectionPointContainer::FindConnectionPoint(
               REFIID riid,
               IConnectionPoint** ppConnPt)
{
  HRESULT hr = E_NOINTERFACE;
  IConnectionPoint* pIConnPt;

  // NULL the output variable.
  *ppConnPt = NULL;

  pIConnPt = m_pCO->m_aConnectionPoints[CONNPOINT_TEXTPAGESINK];
  if (NULL != pIConnPt)
  {
    // This connectable COTextPage object currently has only the
    // TextPage Sink connection point. If the associated interface is
    // requested, use QI to get the Connection Point interface and
    // perform the needed AddRef.
    if (IID_ITextPageSink == riid)
      hr = pIConnPt->QueryInterface(
                       IID_IConnectionPoint,
                       (PPVOID)ppConnPt);
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpIConnectionPointContainer::EnumConnectionPoints

  Summary:  Return Enumerator for the connectable object's contained
            connection points.

  Args:     IEnumConnectionPoints** ppIEnum
              Address of the caller's Enumerator interface pointer
              variable. An output variable that will receive a pointer to
              the connection point enumerator COM object.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COTextPage::CImpIConnectionPointContainer::EnumConnectionPoints(
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
  // points offered by this COTextPage object. Pass 'this' to be used to
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
  COTextPage's nested implementation of the COM standard
  IPersistStreamInit interface including Constructor, Destructor,
  QueryInterface, AddRef, Release, GetClassID, IsDirty, Load, Save,
  GetSizeMax, and InitNew.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpIPersistStreamInit::CImpIPersistStreamInit

  Summary:  Constructor for the CImpIPersistStreamInit interface
            instantiation.

  Args:     COTextPage* pCO,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_pCO, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COTextPage::CImpIPersistStreamInit::CImpIPersistStreamInit(
  COTextPage* pCO,
  IUnknown* pUnkOuter)
{
  // Init the Main Object Pointer to point to the parent object.
  m_pCO = pCO;

  // Init the CImpIPersistStreamInit interface's delegating IUnknown
  // pointer.  We use the Main Object pointer for IUnknown delegation here
  // if we are not being aggregated.  If we are being aggregated we use
  // the supplied pUnkOuter for IUnknown delegation.  In either case the
  // pointer assignment requires no AddRef because the
  // pIPersistStreamInit lifetime is quaranteed by the lifetime of the
  // parent object in which CImpIPersistStreamInit is nested.
  if (NULL == pUnkOuter)
    m_pUnkOuter = pCO;
  else
    m_pUnkOuter = pUnkOuter;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpIPersistStreamInit::~CImpIPersistStreamInit

  Summary:  Destructor for the CImpIPersistStreamIint interface
            instantiation.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COTextPage::CImpIPersistStreamInit::~CImpIPersistStreamInit(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpIPersistStreamInit::QueryInterface

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
STDMETHODIMP COTextPage::CImpIPersistStreamInit::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpIPersistStreamInit::AddRef

  Summary:  The AddRef IUnknown member of this interface implementation
            that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COTextPage::CImpIPersistStreamInit::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpIPersistStreamInit::Release

  Summary:  The Release IUnknown member of this interface implementation
            that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COTextPage::CImpIPersistStreamInit::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpIPersistStreamInit::GetClassID

  Summary:  A method inherited from IPersist. Get the Class ID of this
            COM object.

  Args:     CLSID* pClassID
              [out] Address of variable to hold Class ID.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COTextPage::CImpIPersistStreamInit::GetClassID(
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
  Method:   COTextPage::CImpIPersistStreamInit::IsDirty

  Summary:  Called to determine if changes were made to this COM object
            since it was last loaded or initialized.

  Args:     none.

  Returns:  HRESULT
              Standard result code. S_OK if dirty; S_FALSE if not.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COTextPage::CImpIPersistStreamInit::IsDirty(
               void)
{
  HRESULT hr;

  hr = m_pCO->m_bDirty ? S_OK : S_FALSE;

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpIPersistStreamInit::Load

  Summary:  Asks this COM object to load its persistent data from the
            specified stream at the current seek pointer. This function
            assumes the seek pointer is the same as it was before Save
            was last called. This function must leave the seek pointer
            the same as it was after Save was last completed regardless
            of success or failure. This function should not keep a copy
            of pIStream in the COM object after it completes.

            Load is called INSTEAD of InitNew when this COM object already
            has a persistent state stored in a stream. Notifies all other
            connected clients when the load is complete.

  Args:     IStream* pIStream
              IStream interface pointer for stream to load from. This
              COM object must NOT retain a copy of this IStream pointer
              after this call completes.

  Returns:  HRESULT
              Standard result code. NOERROR for success. E_UNEXPECTED if
              an InitNew or Load has already been called.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COTextPage::CImpIPersistStreamInit::Load(
               IStream* pIStream)
{
  HRESULT hr = E_POINTER;
  ULONG ulToRead, ulReadIn;
  TEXTPROPS NewProps;
  WCHAR* pwszPageText;

  if (NULL != pIStream)
  {
    if (!m_pCO->m_bInitNew)
    {
      // We have the TextPage data stream. First read the TextPage
      // Properties.
      ulToRead = sizeof(TEXTPROPS);
      hr = pIStream->Read(
                       &NewProps,
                       ulToRead,
                       &ulReadIn);
      if (SUCCEEDED(hr) && ulToRead != ulReadIn)
        hr = E_FAIL;
      if (SUCCEEDED(hr))
      {
        // Deal with the different versions.
        switch (NewProps.ulVersion)
        {
          case TEXTPAGE_VERSION10:
            if (NewProps.ulMaxLength <= TEXTPAGE_V10_MAX)
            {
              // Allocate an page text array big enough for the largest
              // text page.
              pwszPageText = new WCHAR[(ULONG) NewProps.ulMaxLength];
              if (NULL != pwszPageText)
              {
                m_pCO->m_pwszPageText = pwszPageText;
                // First zero the page text area.
                memset(
                  pwszPageText,
                  0,
                  NewProps.ulMaxLength * sizeof(WCHAR));
                ulToRead = NewProps.ulLength * sizeof(WCHAR);
                if (ulToRead >= 0 && ulToRead < (ULONG)NewProps.ulMaxLength)
                {
                  // Now read in the complete text page.
                  hr = pIStream->Read(
                         pwszPageText,
                         ulToRead,
                         &ulReadIn);
                  if (SUCCEEDED(hr) && ulToRead != ulReadIn)
                    hr = E_FAIL;
                  if (SUCCEEDED(hr))
                  {
                    // Copy the new properties into current properties.
                    memcpy(
                      &m_pCO->m_TextProps,
                      &NewProps,
                      sizeof(TEXTPROPS));

                    // We are loaded and clean (ie, COTextPage data
                    // matches file data). Clear dirty flag.
                    m_pCO->m_bDirty = FALSE;
                  }
                }
                else
                  hr = E_FAIL;
              }
              else
                hr = E_OUTOFMEMORY;
            }
            break;
          default:
            hr = E_FAIL;  // Bad version.
            break;
        }
      }
    }
    else
      hr = E_UNEXPECTED;
  }

  // Notify all other connected clients that TextPage is now loaded.
  // If we didn't load then clear to a safe, empty text page.
  if (SUCCEEDED(hr))
    m_pCO->NotifySinks(TEXTPAGE_EVENT_LOADED);
  else
    m_pCO->Clear(TRUE);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpIPersistStreamInit::Save

  Summary:  Called to save the persistent data of this COM object to a
            stream using the specified IStream interface. This call stores
            data from the current seek pointer offset. On exit from this
            method the seek pointer is assumed to be just past the end of
            the data saved. This allows a series of contiguous persistent
            objects to be saved into the same stream. Notifies all other
            connected clients when the save is complete.

  Args:     IStream* pIStream
              IStream interface pointer for stream to load from. This
              COM object must NOT retain a copy of this IStream pointer
              after the function completes.
            BOOL bClearDirty
              Determines if this method should clear the COM object's
              dirty flag. If bClearDirty is TRUE then clear the dirty
              flag.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COTextPage::CImpIPersistStreamInit::Save(
               IStream* pIStream,
               BOOL bClearDirty)
{
  HRESULT hr = E_POINTER;
  ULONG ulToWrite, ulWritten;

  if (NULL != pIStream)
  {
    // Got a stream. Now write data into it.

    // First write TEXTPROPS structure.
    ulToWrite = sizeof(TEXTPROPS);
    hr = pIStream->Write(&m_pCO->m_TextProps, ulToWrite, &ulWritten);
    if (SUCCEEDED(hr) && ulToWrite != ulWritten)
      hr = STG_E_CANTSAVE;
    if (SUCCEEDED(hr))
    {
      // Now write the complete page text data.
      ulToWrite = m_pCO->m_TextProps.ulLength * sizeof(WCHAR);
      hr = pIStream->Write(m_pCO->m_pwszPageText, ulToWrite, &ulWritten);
      if (SUCCEEDED(hr) && ulToWrite != ulWritten)
        hr = STG_E_CANTSAVE;
      if (SUCCEEDED(hr))
      {
        // Clear this COM object's dirty flag if instructed.
        if (bClearDirty)
          m_pCO->m_bDirty = FALSE;
      }
    }
  }

  // Notify all other connected clients that TextPage is now saved.
  if (SUCCEEDED(hr))
    m_pCO->NotifySinks(TEXTPAGE_EVENT_SAVED);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpIPersistStreamInit::GetSizeMax

  Summary:  Called to obtain the maximum possible total size of the
            chunks of data that could be saved when Save is next called.

  Args:     ULARGE_INTEGER* pcbSize
              Address of the caller's variable to receive the size (bytes).

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COTextPage::CImpIPersistStreamInit::GetSizeMax(
               ULARGE_INTEGER* pcbSize)
{
  HRESULT hr = E_POINTER;
  ULONG ulMax = m_pCO->m_TextProps.ulMaxLength;

  if (NULL != pcbSize)
  {
    ULISet32(*pcbSize, sizeof(TEXTPROPS) + (ulMax * sizeof(WCHAR)));
    hr = NOERROR;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpIPersistStreamInit::InitNew

  Summary:  Called to tell the object that it has been newly created and
            has no existing persistent state already stored.

            InitNew is called INSTEAD of Load when the new object instance
            must be initialized with brand new data rather than with
            persistent data previously saved in a stream.

  Args:     none.

  Modifies: m_pwszPageText, m_aConnectionPoints.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COTextPage::CImpIPersistStreamInit::InitNew(
               void)
{
  HRESULT hr = E_FAIL;
  WCHAR* pwszPageText;

  if (!m_pCO->m_bInitNew)
  {
    // There is no previous persistent data for this COTextPage object.
    // Create and init a new set of persistence data for an empty text page.

    // Allocate an page text array big enough for the largest text page.
    // This maximum is hard-coded here for this Version 1.0 of Text Pages.
    pwszPageText = new WCHAR[(LONG) TEXTPAGE_V10_MAX];
    if (NULL != pwszPageText)
    {
      m_pCO->m_pwszPageText = pwszPageText;
      // Use the private Clear method to clear the new text array and to
      // set the Page Properties structure appropriately. Also sets dirty.
      hr = m_pCO->Clear(TRUE);
      m_pCO->m_bInitNew = TRUE;
    }
    else
      hr = E_OUTOFMEMORY;
  }
  else
    hr = E_UNEXPECTED;

  return hr;
}


/*---------------------------------------------------------------------------
  COTextPage's nested implementation of the custom ITextPage interface
  including Constructor, Destructor, QueryInterface, AddRef, Release,
  GetFirst, GetNext, Add, Delete, and Clear.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpITextPage::CImpITextPage

  Summary:  Constructor for the CImpITextPage interface instantiation.

  Args:     COTextPage* pCO,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_pCO, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COTextPage::CImpITextPage::CImpITextPage(
  COTextPage* pCO,
  IUnknown* pUnkOuter)
{
  // Init the Main Object Pointer to point to the parent object.
  m_pCO = pCO;

  // Init the CImpITextPage interface's delegating IUnknown pointer.  We
  // use the Main Object pointer for IUnknown delegation here if we are
  // not being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpITextPage lifetime is
  // quaranteed by the lifetime of the parent object in which
  // CImpITextPage is nested.
  if (NULL == pUnkOuter)
    m_pUnkOuter = pCO;
  else
    m_pUnkOuter = pUnkOuter;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpITextPage::~CImpITextPage

  Summary:  Destructor for the CImpITextPage interface instantiation.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COTextPage::CImpITextPage::~CImpITextPage(void)
{

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpITextPage::QueryInterface

  Summary:  The QueryInterface IUnknown member of this ITextPage interface
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
STDMETHODIMP COTextPage::CImpITextPage::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpITextPage::AddRef

  Summary:  The AddRef IUnknown member of this ITextPage interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COTextPage::CImpITextPage::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpITextPage::Release

  Summary:  The Release IUnknown member of this ITextPage interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COTextPage::CImpITextPage::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpITextPage::GetLength

  Summary:  Get the current length (in WCHARs) of the text page.

  Args:     INT* piLength
              Address of the caller's variable that is assigned the length.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COTextPage::CImpITextPage::GetLength(
               INT* piLength)
{
  HRESULT hr = E_POINTER;

  if (NULL != piLength)
  {
    *piLength = (INT) m_pCO->m_TextProps.ulLength;
    hr = NOERROR;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpITextPage::GetText

  Summary:  Get the current page text held in this object.

  Args:     WCHAR* pwszPageText
              Address of a wide character string to receive the text
              data of the text page.

  Returns:  HRESULT
              Standard result code. NOERROR for success. E_POINTER if
              NULL passed for the output string pointer.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COTextPage::CImpITextPage::GetText(
               WCHAR* pwszPageText)
{
  HRESULT hr = E_POINTER;

  if (NULL != pwszPageText && NULL != m_pCO->m_pwszPageText)
  {
    // Copy the Text Page's text to the caller.
    memcpy(
      pwszPageText,
      m_pCO->m_pwszPageText,
      m_pCO->m_TextProps.ulLength * sizeof(WCHAR));
    hr = NOERROR;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpITextPage::PutText

  Summary:  Put specified text into the Text Page COM object. This does
            not save the text persistently.

  Args:     WCHAR* pwszPageText,
              Address of the wide character string to put into the text
              page.
            INT iLength)
              Length in wide characters of the string.

  Returns:  HRESULT
              Standard result code. NOERROR for success. E_POINTER if
              NULL passed for the input string.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COTextPage::CImpITextPage::PutText(
               WCHAR* pwszPageText,
               INT iLength)
{
  HRESULT hr = E_POINTER;

  if (NULL != pwszPageText && NULL != m_pCO->m_pwszPageText)
  {
    if (iLength < (INT) m_pCO->m_TextProps.ulMaxLength)
    {
      // Copy the Caller's text into the text page.
      memcpy(
        m_pCO->m_pwszPageText,
        pwszPageText,
        iLength * sizeof(WCHAR));

      // Set the new current length.
      m_pCO->m_TextProps.ulLength = (ULONG)iLength;

      // Mark TextPage as dirty. Subsequent save to file is needed.
      m_pCO->m_bDirty = TRUE;

      // Notify all other connected clients that the new text was
      // put into the COTextPage object.
      m_pCO->NotifySinks(TEXTPAGE_EVENT_PUT);

      hr = NOERROR;
    }
    else
      hr = E_FAIL;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COTextPage::CImpITextPage::Clear

  Summary:  Clears the entire text page. Sets dirty flag if specified.
            Reassigns the page properties as appropriate. Notifies clients
            of this event.

  Args:     BOOL bSaveNeeded
              Specifies whether the cleared text page should later be
              saved to file. TRUE=>later save needed; FALSE=>later save
              not needed.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COTextPage::CImpITextPage::Clear(
               BOOL bSaveNeeded)
{
  HRESULT hr = E_FAIL;

  hr = m_pCO->Clear(bSaveNeeded);

  // Notify all other connected clients that the list was cleared.
  if (SUCCEEDED(hr))
    m_pCO->NotifySinks(TEXTPAGE_EVENT_CLEARED);

  return hr;
}
