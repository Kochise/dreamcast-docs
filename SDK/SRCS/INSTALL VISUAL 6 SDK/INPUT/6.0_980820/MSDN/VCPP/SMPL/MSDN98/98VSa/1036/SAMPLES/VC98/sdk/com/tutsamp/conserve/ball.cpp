/*+==========================================================================
  File:      BALL.CPP

  Summary:   Implementation file for the COBall COM Object Class (for
             connectable COBall COM Objects). This module provides a
             thread-safe virtual Ball object. The ball has internal
             algorithms that determine its position within a bounded two
             dimensional area. No display or other GUI behavior is done in
             this object.  It is a mathematical entity. Clients of this
             ball can command it to reset, move, and reveal its current
             position, size, and color. These last are used by a client
             that displays images of this ball. The color in particular is
             an internal property maintained by the ball that indicates
             the thread of execution that last moved this ball.

             COBall offers a main standard IUnknown interface (basic COM
             object features), the standard IConnectionPointContainer
             interface (connectable COM object features), and the custom
             IBall interface (Moving Ball related features). This multiple
             interface COM Object Class is achieved via the technique of
             nested classes.  The implementations of the
             IConnectionPointContainer and IBall interfaces are nested
             inside the COBall Class.

             This file also implements some internal C++ classes (CXForm
             and CBallThread) that provide internal support for the custom
             IBall interface.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial CONSERVE.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   CXForm, CBallThread, COBall.

  Functions: none.

  Origin:    12-28-96: atrent - Editor-inheritance from BALL.CPP in
             the FRESERVE Tutorial Code Sample.

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
  We include SERVER.H because it has internal class declarations and
    resource ID definitions specific for this DLL.
  We include CONNECT.H for object class declarations for the various
    connection point and connection COM objects used in CONSERVE.
  We include BALL.H because it has the class COBall declarations.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <apputil.h>
#include <iball.h>
#include <ballguid.h>
#include "server.h"
#include "connect.h"
#include "ball.h"


/*---------------------------------------------------------------------------
  COBall's implementation of its internal utility class CXForm.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CXForm::Clear

  Summary:  Clears and initializes the transformation matrix.

  Args:     void

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CXForm::Clear(void)
{
  int Row,Col;

  for(Row=0; Row < 3; Row++)
    for(Col=0; Col < 3; Col++)
      if(Row == Col)
        XForm[Row][Col] = 1;
      else
        XForm[Row][Col] = 0;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CXForm::Scale

  Summary:  Method to allow setting the transformation to multiply
            by a scale factor.

  Args:     int xScale
              x Scale factor.
            int yScale
              y Scale factor.

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CXForm::Scale(int xScale, int yScale)
{
  int idx;

  for(idx=0; idx < 3; idx++)
  {
    XForm[idx][0] = XForm[idx][0] * xScale;
    XForm[idx][1] = XForm[idx][1] * yScale;
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CXForm::Trans

  Summary:  Perform the transform uing the internal matrix.

  Args:     int xTrans
              x coordinate.
            int yTrans
              y coordinate.

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CXForm::Trans(int xTrans, int yTrans)
{
  XForm[2][0] = XForm[2][0] + xTrans;
  XForm[2][1] = XForm[2][1] + yTrans;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CXForm::Point

  Summary:  Transform a point.

  Args:     POINT* pPoint
              Pointer to the point.

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CXForm::Point(POINT* pPoint)
{
  int x,y;

  x = (XForm[0][0] * pPoint->x) + (XForm[1][0] * pPoint->y) + XForm[2][0];
  y = (XForm[0][1] * pPoint->x) + (XForm[1][1] * pPoint->y) + XForm[2][1];

  pPoint->x = x;
  pPoint->y = y;

  return;
}


/*---------------------------------------------------------------------------
  COBall's implementation of its main COM object class including
  Constructor, Destructor, QueryInterface, AddRef, and Release.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::COBall

  Summary:  COBall Constructor. Note the member initializer:
            "m_ImpIBall(this, pUnkOuter)" which is used to pass the 'this'
            and pUnkOuter pointers of the constructor function to the
            constructor in the instantiation of the implementation of the
            CImpIBall interface (which is nested inside this present
            COBall Object Class). Same technique is used for the
            m_ImpIConnectionPointContainer nested interface
            implementation.

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
COBall::COBall(
  IUnknown* pUnkOuter,
  CServer* pServer) :
  m_ImpIBall(this, pUnkOuter),
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

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::~COBall

  Summary:  COBall Destructor.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COBall::~COBall(void)
{
  UINT i;
  IConnectionPoint* pIConnectionPoint;

  // Do final release of the connection point objects.
  // If this isn't the final release, then the client has an outstanding
  // unbalanced reference to a connection point and a memory leak may
  // likely result because the host COBall object is now going away yet
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
  Method:   COBall::Init

  Summary:  COBall initialization method.  Create any necessary arrays,
            structures, and subordinate objects.

  Args:     void

  Modifies: m_aConnectionPoints.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COBall::Init(void)
{
  HRESULT hr = NOERROR;
  COConnectionPoint* pCOConnPt;

  // Rig this COBall COM object to be connectable. Assign the connection
  // point array. This object's connection points are determined at
  // compile time--it currently has only one connection point:
  // the CONNPOINT_BALLSINK connection point. Create a connection
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
    hr = pCOConnPt->Init(IID_IBallSink);

    // If the init succeeded then use QueryInterface to obtain the
    // IConnectionPoint interface on the new connection point object.
    // The interface pointer is assigned directly into the
    // connection point array. The QI also does the needed AddRef.
    if (SUCCEEDED(hr))
      hr = pCOConnPt->QueryInterface(
                        IID_IConnectionPoint,
                        (PPVOID)&m_aConnectionPoints[CONNPOINT_BALLSINK]);
  }
  else
    hr = E_OUTOFMEMORY;

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::QueryInterface

  Summary:  QueryInterface of the COBall non-delegating IUnknown
            implementation.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Modifies: .

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COBall::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  HRESULT hr = E_NOINTERFACE;

  *ppv = NULL;

  if (IID_IUnknown == riid)
    *ppv = this;
  else if (IID_IBall == riid)
    *ppv = &m_ImpIBall;
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
  Method:   COBall::AddRef

  Summary:  AddRef of the COBall non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COBall::AddRef(void)
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
  Method:   COBall::Release

  Summary:  Release of the COBall non-delegating IUnknown implementation.

  Args:     void

  Modifies: m_cRefs.

  Returns:  ULONG
              New value of m_cRefs (COM object's reference count).
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COBall::Release(void)
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
      // COBall but a good practice because we are aggregatable and
      // may at some point in the future add something entertaining like
      // some Releases to the COBall destructor. Relinquish thread
      // ownership of this object before deleting it--a good practice.
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
  Method:   COBall::NotifySinks

  Summary:  Internal utility method of this COM object used to fire event
            notification calls to all listening connection sinks in the
            client.

  Args:     DWORD dwEvent
              Type of notification event.

  Modifies: ...

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT COBall::NotifySinks(
       DWORD dwEvent)
{
  HRESULT hr = NOERROR;
  IConnectionPoint* pIConnectionPoint;
  IEnumConnections* pIEnum;
  CONNECTDATA ConnData;

  // If there was a bounce event, broadcast appropriate notifications to
  // all Sinks connected to each connection point.
  if (BOUNCE_NONE != dwEvent)
  {
    // Here is the section for the BallSink connection point--currently
    // this is the only connection point offered by COBall objects.
    pIConnectionPoint = m_aConnectionPoints[CONNPOINT_BALLSINK];
    if (NULL != pIConnectionPoint)
    {
      pIConnectionPoint->AddRef();
      hr = pIConnectionPoint->EnumConnections(&pIEnum);
      if (SUCCEEDED(hr))
      {
        // Loop thru the connection point's connections and if the listening
        // connection supports IBallSink (ie, BallSink events) then dispatch
        // the dwEvent event notification to that sink.
        while (NOERROR == pIEnum->Next(1, &ConnData, NULL))
        {
          IBallSink* pIBallSink;

          hr = ConnData.pUnk->QueryInterface(
                                IID_IBallSink,
                                (PPVOID)&pIBallSink);
          if (SUCCEEDED(hr))
          {
            switch (dwEvent)
            {
              case BOUNCE_BOTTOM:
                pIBallSink->BounceBottom();
                break;
              case BOUNCE_LEFT:
                pIBallSink->BounceLeft();
                break;
              case BOUNCE_RIGHT:
                pIBallSink->BounceRight();
                break;
              case BOUNCE_TOP:
                pIBallSink->BounceTop();
                break;
              default:
                break;
            }
            pIBallSink->Release();
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
  COBall's nested implementation of the COM standard
  IConnectionPointContainer interface including Constructor, Destructor,
  QueryInterface, AddRef, Release, FindConnectionPoint, and
  EnumConnectionPoints.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIConnectionPointContainer
              ::CImpIConnectionPointContainer

  Summary:  Constructor for the CImpIConnectionPointContainer interface
            instantiation.

  Args:     COBall* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_pBackObj, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COBall::CImpIConnectionPointContainer::CImpIConnectionPointContainer(
  COBall* pBackObj,
  IUnknown* pUnkOuter)
{
  // Init the Back Object Pointer to point to the parent object.
  m_pBackObj = pBackObj;

  // Init the CImpIConnectionPointContainer interface's delegating Unknown
  // pointer.  We use the Back Object pointer for IUnknown delegation here if
  // we are not being aggregated.  If we are being aggregated we use the
  // supplied pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpIConnectionPointContainer
  // lifetime is quaranteed by the lifetime of the parent object in which
  // CImpIConnectionPointContainer is nested.
  if (NULL == pUnkOuter)
    m_pUnkOuter = pBackObj;
  else
    m_pUnkOuter = pUnkOuter;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIConnectionPointContainer
              ::~CImpIConnectionPointContainer

  Summary:  Destructor for the CImpIConnectionPointContainer interface
            instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COBall::CImpIConnectionPointContainer::~CImpIConnectionPointContainer(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIConnectionPointContainer::QueryInterface

  Summary:  The QueryInterface IUnknown member of this IBall interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Modifies: .

  Returns:  HRESULT
              Standard result code. NOERROR for success.
              Returned by the delegated outer QueryInterface call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COBall::CImpIConnectionPointContainer::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIConnectionPointContainer::AddRef

  Summary:  The AddRef IUnknown member of this IBall interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COBall::CImpIConnectionPointContainer::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIConnectionPointContainer::Release

  Summary:  The Release IUnknown member of this IBall interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COBall::CImpIConnectionPointContainer::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIConnectionPointContainer::FindConnectionPoint

  Summary:  Given an IID for a connection point sink find and return the
            interface pointer for that connection point sink.

  Args:     REFIID riid
              Reference to an IID
            IConnectionPoint** ppConnPt
              Pointer to the caller's Connection Point pointer variable.

  Modifies: .

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COBall::CImpIConnectionPointContainer::FindConnectionPoint(
               REFIID riid,
               IConnectionPoint** ppConnPt)
{
  HRESULT hr = E_NOINTERFACE;
  IConnectionPoint* pIConnPt;

  if (OwnThis())
  {
    // NULL the output variable.
    *ppConnPt = NULL;

    pIConnPt = m_pBackObj->m_aConnectionPoints[CONNPOINT_BALLSINK];
    if (NULL != pIConnPt)
    {
      // This connectable COBall object currently has only the Ball Sink
      // connection point. If the associated interface is requested,
      // use QI to get the Connection Point interface and perform the
      // needed AddRef.
      if (IID_IBallSink == riid)
        hr = pIConnPt->QueryInterface(
                         IID_IConnectionPoint,
                         (PPVOID)ppConnPt);
    }

    UnOwnThis();
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIConnectionPointContainer::EnumConnectionPoints

  Summary:  Return Enumerator for the connectable object's contained
            connection points.

  Args:     IEnumConnectionPoints** ppIEnum
              Pointer to the caller's Enumerator pointer variable.
              An output variable that will receive a pointer to the
              connection point enumerator COM object.

  Modifies: .

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COBall::CImpIConnectionPointContainer::EnumConnectionPoints(
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

    // Make a copy on the stack of the array of connection point interfaces.
    // The copy is used below in the creation of the new Enumerator object.
    for (i=0; i<MAX_CONNECTION_POINTS; i++)
      aConnPts[i] = (IConnectionPoint*)m_pBackObj->m_aConnectionPoints[i];

    // Create a Connection Point enumerator COM object for the connection
    // points offered by this COBall object. Pass 'this' to be used to
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
  COBall's nested implementation of the custom IBall interface including
  Constructor, Destructor, QueryInterface, AddRef, Release, Reset, Move,
  and GetBall. This interface implementation also has internal methods
  that are not particulary intended for outside clients: GetDimensions,
  SetDimensions, GetDirection, SetDirection, GetPosition, SetPostion,
  CheckBounce, and FindThread. The IBall interface only provides client
  access to the IUnknown methods and the Reset, Move, and GetBall methods.
---------------------------------------------------------------------------*/

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIBall::CImpIBall

  Summary:  Constructor for the CImpIBall interface instantiation.

  Args:     COBall* pBackObj,
              Back pointer to the parent outer object.
            IUnknown* pUnkOuter
              Pointer to the outer Unknown.  For delegation.

  Modifies: m_pBackObj, m_pUnkOuter.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COBall::CImpIBall::CImpIBall(
  COBall* pBackObj,
  IUnknown* pUnkOuter)
{
  size_t i;
  BYTE r=128, g=128, b=128;

  // Init the Back Object Pointer to point to the parent object.
  m_pBackObj = pBackObj;

  // Init the CImpIBall interface's delegating Unknown pointer.  We use
  // the Back Object pointer for IUnknown delegation here if we are not
  // being aggregated.  If we are being aggregated we use the supplied
  // pUnkOuter for IUnknown delegation.  In either case the pointer
  // assignment requires no AddRef because the CImpIBall lifetime is
  // quaranteed by the lifetime of the parent object in which
  // CImpIBall is nested.
  if (NULL == pUnkOuter)
    m_pUnkOuter = pBackObj;
  else
    m_pUnkOuter = pUnkOuter;

  // Now initialize the living heart of the COBall object.
  m_bAlive       = TRUE;
  m_xDirection   = 0;
  m_yDirection   = 0;
  m_bNewPosition = FALSE;
  m_xPosition    = 0;
  m_yPosition    = 0;
  m_nWidth       = 30;
  m_nHeight      = 30;
  m_xSkew        = BALL_MOVE_SKEW;
  m_ySkew        = BALL_MOVE_SKEW;
  m_crColor      = RGB(0,0,0);

  // Clear point transformation array.
  m_XForm.Clear();

  // Init BallThread array--init colors and clear thread Ids.
  // The BallThreads are the threads that contend to move and/or
  // paint the Ball object.
  for (i = 0; i < MAX_BALLTHREADS; i++)
    m_aBallThreads[i].Id = 0;
  m_aBallThreads[0].Color = RGB(0  ,  0,255);  // Blue
  m_aBallThreads[1].Color = RGB(0  ,255,  0);  // Green
  m_aBallThreads[2].Color = RGB(255,  0,  0);  // Red
  m_aBallThreads[3].Color = RGB(255,  0,255);  // Purple
  m_aBallThreads[4].Color = RGB(0  ,255,255);  // Aqua
  m_aBallThreads[5].Color = RGB(255,255,  0);  // Brown
  m_aBallThreads[6].Color = RGB(0  ,  0,  0);  // Black
  if (MAX_BALLTHREADS > 8)
    for (i=7; i<MAX_BALLTHREADS; i++)
    {
      // Fill the remainder with some random colors.
      m_aBallThreads[i].Color = RGB(r,g,b);
      r = (BYTE) lRandom() % 255;
      g = (BYTE) lRandom() % 255;
      b = (BYTE) lRandom() % 255;
    }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIBall::~CImpIBall

  Summary:  Destructor for the CImpIBall interface instantiation.

  Args:     void

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COBall::CImpIBall::~CImpIBall(void)
{
  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIBall::GetDimensions

  Summary:  Internal private utility method to get the Ball x,y dimensions.

  Args:     POINT* pDimension
              Pointer to the point that will contain the dimensions.

  Modifies: *pDimension.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void COBall::CImpIBall::GetDimensions(POINT* pDimension)
{
  pDimension->x = m_nWidth;
  pDimension->y = m_nHeight;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIBall::SetDimensions

  Summary:  Internal private utility method to set the Ball x,y dimensions.

  Args:     int nWidth
              New Ball width.
            int nHeight
              New Ball Height.

  Modifies: .

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void COBall::CImpIBall::SetDimensions(int nWidth, int nHeight)
{
  m_nWidth  = nWidth;
  m_nHeight = nHeight;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIBall::GetDirection

  Summary:  Internal private utility method to get the Ball direction.

  Args:     POINT* pDirection
              Pointer to the Point that will contain the x,y direction
              data.

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void COBall::CImpIBall::GetDirection(POINT* pDirection)
{
  pDirection->x = m_xDirection;
  pDirection->y = m_yDirection;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIBall::SetDirection

  Summary:  Internal private utility method to set the Ball direction.

  Args:     int xDirection
              x coordinate of the new direction.
            int yDirection
              y coordinate of the new direction.

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void COBall::CImpIBall::SetDirection(int xDirection, int yDirection)
{
  m_xDirection = xDirection;
  m_yDirection = yDirection;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIBall::GetPosition

  Summary:  Internal private utility method to get current the Ball
            position.

  Args:     POINT* pPosition
              Pointer to the Point that is the position.

  Modifies: *pPostion.

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void COBall::CImpIBall::GetPosition(POINT* pPosition)
{
  POINT Org;

  Org.x = 0;
  Org.y = 0;
  m_XForm.Point(&Org);

  pPosition->x = Org.x;
  pPosition->y = Org.y;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIBall::SetPosition

  Summary:  Internal private utility method to set current the Ball
            position.

  Args:     int x
              x-coordinate of new position.
            int y
              y-coordinate of new position.

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void COBall::CImpIBall::SetPosition(int x, int y)
{
  m_bNewPosition = TRUE;
  m_xPosition    = x;
  m_yPosition    = y;

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIBall::CheckBounce

  Summary:  Internal private utility method to check the current Ball
            position, dimension, and direction data and determine if the
            Ball has hit the internal WinRect bounding rectangle. If it
            has then the Ball data is recalculated to achieve a "bounce"
            effect for the Ball as it moves. Returns a DWORD indicating
            the type of bounce event that happened.

  Args:     void

  Modifies: ...

  Returns:  DWORD
              Type of bounce: BOUNCE_NONE, BOUNCE_BOTTOM, BOUNCE_LEFT,
              BOUNCE_RIGHT, or BOUNCE_TOP.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
DWORD COBall::CImpIBall::CheckBounce(void)
{
  DWORD dwBounceType = BOUNCE_NONE;
  POINT Pos, Dir, Dim;
  int   xNewPos, yNewPos, xNewDir, yNewDir;

  GetPosition(&Pos);
  GetDirection(&Dir);
  GetDimensions(&Dim);

  // Check each edge of the client rectangle.  If the Ball goes past the
  // boundries, reset its position and direction to give it a "bounce"
  // effect the next time it is displayed.
  xNewDir = Dir.x;
  yNewDir = Dir.y;
  xNewPos = Pos.x + Dir.x;
  yNewPos = Pos.y + Dir.y;

  if(xNewPos < m_WinRect.left)
  {
    xNewDir = ((lRandom() % m_xSkew) + m_xSkew);
    SetPosition(m_WinRect.left, Pos.y);
    dwBounceType = BOUNCE_LEFT;
  }
  if((xNewPos + Dim.x) > m_WinRect.right)
  {
    xNewDir = -(((int)lRandom() % m_xSkew) + m_xSkew);
    SetPosition(m_WinRect.right - Dim.x, Pos.y);
    dwBounceType = BOUNCE_RIGHT;
  }
  if(yNewPos < m_WinRect.top)
  {
    yNewDir = ((lRandom() % m_ySkew) + m_ySkew);
    SetPosition(Pos.x, m_WinRect.top);
    dwBounceType = BOUNCE_TOP;
  }
  if((yNewPos + Dim.y) > m_WinRect.bottom)
  {
    yNewDir = -(((int)lRandom() % m_ySkew) + m_ySkew);
    SetPosition(Pos.x, m_WinRect.bottom - Dim.y);
    dwBounceType = BOUNCE_BOTTOM;
  }

  SetDirection(xNewDir, yNewDir);

  return dwBounceType;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIBall::FindThread

  Summary:  Internal private utility method to Find the thread that is now
            executing this code. If the executing thread is not already in
            the Thread array, remember the new Thread's Id and add it to
            the array. This in effect assigns the thread a color that can
            be used for tutorial display of which thread is executing on
            the Ball object.

  Args:     void

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void COBall::CImpIBall::FindThread(void)
{
  BOOL bFound = FALSE;
  DWORD dwTId = GetCurrentThreadId();
  size_t i = 0;

  while(!bFound && i<MAX_BALLTHREADS)
  {
    if (m_aBallThreads[i].Id == 0)
    {
      // Found empty slot. This simple array logic allows no empty holes.
      m_aBallThreads[i].Id = dwTId;
      bFound = TRUE;
    }
    else
    {
      if (m_aBallThreads[i].Id == dwTId)
      {
        // Found previous visiting thread--use its assigned color.
        m_crColor = m_aBallThreads[i].Color;
        bFound = TRUE;
      }
      else
      {
        i++;
        if (i >= MAX_BALLTHREADS)
        {
          // Thread array is full--use a gray color for all other
          // excess visiting threads.
          m_crColor = RGB(127,127,127);
          bFound = TRUE;
        }
      }
    }
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIBall::QueryInterface

  Summary:  The QueryInterface IUnknown member of this IBall interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     REFIID riid,
              [in] GUID of the Interface being requested.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Modifies: .

  Returns:  HRESULT
              Standard result code. NOERROR for success.
              Returned by the delegated outer QueryInterface call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COBall::CImpIBall::QueryInterface(
               REFIID riid,
               PPVOID ppv)
{
  // Delegate this call to the outer object's QueryInterface.
  return m_pUnkOuter->QueryInterface(riid, ppv);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIBall::AddRef

  Summary:  The AddRef IUnknown member of this IBall interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer AddRef call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COBall::CImpIBall::AddRef(void)
{
  // Delegate this call to the outer object's AddRef.
  return m_pUnkOuter->AddRef();
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIBall::Release

  Summary:  The Release IUnknown member of this IBall interface
            implementation that delegates to m_pUnkOuter, whatever it is.

  Args:     void

  Modifies: .

  Returns:  ULONG
              Returned by the delegated outer Release call.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP_(ULONG) COBall::CImpIBall::Release(void)
{
  // Delegate this call to the outer object's Release.
  return m_pUnkOuter->Release();
}




/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIBall::Reset

  Summary:  The Reset member method of the IBall interface implementation.
            Called by outside clients of a COBall object to reset the
            virtual Ball. The ball is restored to the upper left corner.

  Args:     RECT* pNewRect,
              Pointer to a RECT structure. Tells the COBall the bounding
              rectangle within which the Ball can move.
            short nBallSize,
              The size of the ball in pixels. nBallSize == Width == Height
              meaning that a circle is assumed.

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COBall::CImpIBall::Reset(
               RECT* pNewRect,
               short nBallSize)
{
  HRESULT hr = E_FAIL;
  int nDim, xDirection, yDirection;

  if (OwnThis())
  {
    // Find the thread who is executing this and remember its color.
    FindThread();

    m_xSkew = m_ySkew = BALL_MOVE_SKEW;
    m_WinRect.left = pNewRect->left;
    m_WinRect.top = pNewRect->top;
    m_WinRect.right = pNewRect->right;
    m_WinRect.bottom = pNewRect->bottom;
    nDim = nBallSize ? nBallSize : max(5, m_WinRect.right / 13);
    SetDimensions(nDim, nDim);
    SetPosition(0, 0);
    xDirection = ((lRandom() % m_xSkew) + m_xSkew);
    yDirection = ((lRandom() % m_ySkew) + m_ySkew);
    SetDirection(xDirection, yDirection);

    hr = NOERROR;

    UnOwnThis();
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIBall::Move

  Summary:  The Move member method of this IBall interface implementation.
            Called by outside clients of a COBall object to advance the
            "motion" of this COBall virtual Ball entity.

  Args:     BOOL bAlive
              TRUE means stay alive; FALSE means don't move but die.

  Modifies: m_bAlive.

  Returns:  HRESULT
              Standard result code. NOERROR for success and means the move
              was done and the ball is still alive. E_FAIL means the move
              was not done and the ball has been killed.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COBall::CImpIBall::Move(
               BOOL bAlive)
{
  HRESULT hr = E_FAIL;
  DWORD dwEvent;

  if (OwnThis())
  {
    if (bAlive && m_bAlive)
    {
      // Find thread that is now executing this code. Remember its Id and
      // assign it a color. If this thread previously visited here then
      // use its remembered values. In any case, set a color value in
      // m_crColor of its existing or newly assigned color.
      FindThread();

      // Ask the Ball if it has hit any of the edges of the current window
      // rectangle. If so, it will recalculate its position and direction
      // to achieve a "bounce" effect in its motion the next time it is
      // painted. CheckBounce also determines and returns any notification
      // events.
      dwEvent = CheckBounce();

      // Send notification of each bounce event to any listening sinks.
      m_pBackObj->NotifySinks(dwEvent);

      // Calculate and set new Ball position.
      if(m_bNewPosition)
      {
        m_bNewPosition = FALSE;
        m_XForm.Clear();
        m_XForm.Trans(m_xPosition, m_yPosition);
      }
      else
        m_XForm.Trans(m_xDirection, m_yDirection);
    }
    else
      m_bAlive = FALSE;

    hr = m_bAlive ? NOERROR : E_FAIL;

    UnOwnThis();
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COBall::CImpIBall::GetBall

  Summary:  The GetBall member method of this IBall interface
            implementation. Called by outside clients of a COBall object
            to get the necessary data on the moving Ball to enable GUI
            display of an actual image of this virtual Ball. This COBall
            is a data entity only that is kept alive by client threads
            that call Move. A GUI client can independently call GetBall
            to allow it to display some visual representation of the Ball.

  Args:     POINT* pNewOrg,
              Pointer to a point that will contain the new origin
              position of the Ball.
            POINT* pNewExt,
              Pointer to a point that will contain the new extent
              size of the Ball.
            COLORREF* pcrColor)
              Pointer to a COLORREF that will contain the current color
              of the Ball. This color is determined by the last thread
              that was executing in the Ball before this call is made.

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP COBall::CImpIBall::GetBall(
       POINT* pNewOrg,
       POINT* pNewExt,
       COLORREF* pcrColor)
{
  HRESULT hr = E_FAIL;

  if (OwnThis())
  {
    pNewOrg->x = 0;
    pNewOrg->y = 0;
    m_XForm.Point(pNewOrg);
    pNewExt->x = m_nWidth;
    pNewExt->y = m_nHeight;
    m_XForm.Point(pNewExt);

    *pcrColor = m_crColor;

    hr = NOERROR;

    UnOwnThis();
  }

  return hr;
}
