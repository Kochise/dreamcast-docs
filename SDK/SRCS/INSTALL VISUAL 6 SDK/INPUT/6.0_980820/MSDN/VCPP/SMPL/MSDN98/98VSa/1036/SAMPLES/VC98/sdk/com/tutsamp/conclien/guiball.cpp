/*+==========================================================================
  File:      GUIBALL.CPP

  Summary:   Implementation file for the CGuiBall C++ class. A GuiBall is
             a C++ object that displays a moving and bouncing ball in the
             client area of a designated window.  It is anchored to the
             Windows GUI (Graphical User Interface) environment. This
             GuiBall object continuously paints a ball image based on data
             it obtains from a virtual ball object. This virtual ball
             object is instantiated as a COM object (a COBall) in a
             separate thread-safe In-process server, CONSERVE.

             GuiBall relies on the system timer to send periodic WM_TIMER
             messages to a window procedure designated in the
             CGuiBall::Init call. When these messages are received, the
             window procedure calls the CGuiBall::PaintBall method which
             both moves and displays the ball image.

             For a comprehensive tutorial code tour of GUIBALL's contents
             and offerings see the tutorial CONCLIEN.HTM file. For more
             specific technical details on the internal workings see the
             comments dispersed throughout the GUIBALL source code.

  Classes:   CGuiBall.

  Origin:    5-30-96: atrent - Editor inheritance from GUIBALL.CPP in the
             FRECLIEN source.

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

/*--------------------------------------------------------------------------
  We include WINDOWS.H for all Win32 applications.
  We include OLE2.H because we will be calling the COM/OLE libraries.
  We include OLECTL.H because it has definitions for connectable objects.
  We include APPUTIL.H because we will be building this application using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include IBALL.H and BALLGUID.H for the common Ball-related Interface
    class, GUID, and CLSID specifications.
  We include GUIBALL.H because it has the C++ class used for GUI display
    of the moving ball.
  We include CONCLIEN.H because it has class and resource definitions
    specific to this CONCLIEN application.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <apputil.h>
#include <iball.h>
#include <ballguid.h>
#include "guiball.h"
#include "sink.h"
#include "conclien.h"


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiBall::CGuiBall

  Summary:  Constructor.

  Args:     void

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CGuiBall::CGuiBall(void)
{
  m_hWnd       = 0;
  m_pIBall     = NULL;
  m_crColor    = RGB(0,0,0);
  m_OldPos.x   = 0;
  m_OldPos.y   = 0;
  m_OldExt.x   = 0;
  m_OldExt.y   = 0;
  m_pCOBallSink = NULL;
  m_dwBallSink = 0;
  m_dwBounceSndDur = BOUNCE_SOUND_DURATION;
  m_dwBounceBotFreq = BOUNCE_BOTTOM_FREQUENCY;
  m_dwBounceSideFreq = BOUNCE_SIDE_FREQUENCY;
  m_dwBounceTopFreq = BOUNCE_TOP_FREQUENCY;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiBall::~CGuiBall

  Summary:  Destructor.

  Args:     void

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CGuiBall::~CGuiBall(void)
{
  BOOL bOk = TRUE;

  // Kill the client's app timer that drives repaints. Stops the WM_TIMER
  // messages to the display window.
  KillTimer(m_hWnd, 1);

  if (m_pIBall)
  {
    // Call down to the server's COBall and tell it about the shutdown.
    // This sets COBall's m_bAlive to FALSE, neutralizes all
    // subsequent Move calls, and thus prevents any more NotifySinks calls
    // from within the Move method.
    m_pIBall->Move(FALSE);

    // Disconnect all Sinks--currently only one: BallSink. This officially
    // stops all BallSink notifications.
    DisconnectBallSink();

    // Release the reference to the BallSink object.
    RELEASE_INTERFACE(m_pCOBallSink);

    // Release the main interface pointer copy held in CGuiBall.
    RELEASE_INTERFACE(m_pIBall);
  }
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiBall::Init

  Summary:  Get everything related to CGuiBall started. Make any
            subordinate objects, like COBall, and get it started. Starts
            the system timer that keeps the virtual ball moving with GUI
            painted images.

  Args:     HWND hWnd
              Handle of the display window. Part of what makes CGuiBall
              a GUI kind of thing.

  Modifies: ...

  Returns:  BOOL
              TRUE for success; FALSE for fail.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CGuiBall::Init(
       HWND hWnd)
{
  BOOL bOk = FALSE;
  HRESULT hr;
  COBallSink* pCob = NULL;

  if (hWnd)
  {
    m_hWnd = hWnd;

    // Call COM service to create a COBall instance. We are not
    // aggregating it so we ask for its IBall interface directly.
    hr = CoCreateInstance(
           CLSID_DllSndBall,
           NULL,
           CLSCTX_INPROC_SERVER,
           IID_IBall,
           (PPVOID)&m_pIBall);
    if (SUCCEEDED(hr))
    {
      // Create the COBallSink Sink object to receive COBall events.
      pCob = new COBallSink(NULL, this);
      if (NULL != pCob)
      {
        // Save a pointer to the COBall IUnknown interface. AddRef
        // because of this saved copy.
        m_pCOBallSink = pCob;
        m_pCOBallSink->AddRef();
      }
      else
        hr = E_OUTOFMEMORY;

      if (SUCCEEDED(hr))
      {
        // Set up the client process to periodically move & paint the ball
        // thru WM_TIMER messages to the specified hWnd's Window proc.
        SetTimer(hWnd, 1, BALL_PAINT_DELAY, NULL);
        bOk = TRUE;
      }
    }
  }

  return (bOk);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiBall::PaintBall

  Summary:  Tell CGuiBall to move one increment and paint one image of the
            GuiBall.

  Args:     void

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CGuiBall::PaintBall(void)
{
  HDC       hDC;
  HBRUSH    hBrush;
  POINT     Org, Ext;
  HRGN      hTmp, hOld, hNew;

  if (m_pIBall)
  {
    // Move the ball before painting it. By placing this Move call here
    // we link moving with painting in synchronized lock step.
    m_pIBall->Move(TRUE);

    // Ask the COBall for its current ball (location, region, and color).
    m_pIBall->GetBall(&Org, &Ext, &m_crColor);

    // Create the old ball image/region.
    hOld = CreateEllipticRgn(m_OldPos.x, m_OldPos.y, m_OldExt.x, m_OldExt.y);

    // Create the new ball image/region.
    hNew = CreateEllipticRgn(Org.x, Org.y, Ext.x, Ext.y);

    // Remember the new Pos and Ext as the next old set of Pos and Ext.
    m_OldPos.x = Org.x;
    m_OldPos.y = Org.y;
    m_OldExt.x = Ext.x;
    m_OldExt.y = Ext.y;

    if(hDC = GetDC(m_hWnd))
    {
      // Erase old ball image.
      hTmp = CreateRectRgn(1, 1, 2, 2);
      if (NULL != hOld)
      CombineRgn(hTmp, hOld, hNew, RGN_DIFF);
      FillRgn(hDC, hTmp, GETCLASSBRUSH(m_hWnd));

      // Make a paint brush, dip it in pixel paint, and paint the
      // new Ball image. Destroy brush after use.
      hBrush = CreateSolidBrush(m_crColor);
      FillRgn(hDC, hNew, hBrush);
      DeleteObject(hBrush);
      ReleaseDC(m_hWnd, hDC);
      DeleteObject(hTmp);
    }

    // Delete the region objects.
    if (NULL != hOld)
      DeleteObject(hOld);
  if (NULL != hNew)
      DeleteObject(hNew);
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiBall::Restart

  Summary:  Restart the display process. Places Ball in start position
            in a clean window.

  Args:     void.

  Modifies: ...

  Returns:  void.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CGuiBall::Restart(void)
{
  RECT  WinRect;
  HDC   hDC = GetDC(m_hWnd);

  if(hDC && m_pIBall)
  {
    // Clear the window.
    // Get our window's client area rectangle.
    GetClientRect(m_hWnd, &WinRect);
    // Fill that rectangle with pixels of white paint.
    FillRect(hDC, &WinRect, GETCLASSBRUSH(m_hWnd));

    // Tell the COBall to reset itself.
    m_pIBall->Reset(&WinRect, 0);

    // Call our own CGuiBall method to paint an initial image of the ball.
    PaintBall();

    // Release the Device Context.
    ReleaseDC(m_hWnd, hDC);
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiBall::PaintWin

  Summary:  Clears window background and paints the GuiBall at its
            current location.

  Args:     void

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CGuiBall::PaintWin(void)
{
  HDC         hDC;
  PAINTSTRUCT ps;
  RECT        WinRect;

  if(hDC = BeginPaint(m_hWnd, &ps))
    EndPaint(m_hWnd, &ps);

  if(hDC = GetDC(m_hWnd))
  {
    // Get our window's client area rectangle.
    GetClientRect(m_hWnd, &WinRect);
    // Fill that rectangle with pixels of white paint.
    FillRect(hDC, &WinRect, GETCLASSBRUSH(m_hWnd));

    // Paint a current image of the ball wherever it is.
    PaintBall();

    ReleaseDC(m_hWnd, hDC);
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiBall::BounceBottom

  Summary:  Produce a sound for the ball bounce against the Bottom
            boundary.

  Args:     void

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CGuiBall::BounceBottom(void)
{
  // Use the Win32 Beep call.
  Beep(m_dwBounceBotFreq, m_dwBounceSndDur);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiBall::BounceSide

  Summary:  Produce a sound for the ball bounce against a Side boundary.

  Args:     void

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CGuiBall::BounceSide(void)
{
  // Use the Win32 Beep call.
  Beep(m_dwBounceSideFreq, m_dwBounceSndDur);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiBall::BounceTop

  Summary:  Produce a sound for the ball bounce against the Top boundary.

  Args:     void

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CGuiBall::BounceTop(void)
{
  // Use the Win32 Beep call.
  Beep(m_dwBounceTopFreq, m_dwBounceSndDur);

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiBall::GetConnectionPoint

  Summary:  Internal private method to obtain a connection point interface.

  Args:     REFIID riid
              IID of the requested connection point Interface.

  Modifies: ...

  Returns:  IConnectionPoint*
              Requested IConnectionPoint interface pointer. NULL if none.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
IConnectionPoint* CGuiBall::GetConnectionPoint(
                    REFIID riid)
{
  IConnectionPointContainer* pConnPointContainer = NULL;
  IConnectionPoint* pConnPoint = NULL;
  IConnectionPoint* pConnPt = NULL;
  HRESULT hr;

  // First query the object for its Connection Point Container. This
  // essentially asks the object in the server if it is connectable.
  hr = m_pIBall->QueryInterface(
         IID_IConnectionPointContainer,
         (PPVOID)&pConnPointContainer);
  if SUCCEEDED(hr)
  {
    // Find the requested Connection Point. This AddRef's the
    // returned pointer.
    hr = pConnPointContainer->FindConnectionPoint(riid, &pConnPt);
    if (SUCCEEDED(hr))
      pConnPoint = pConnPt;

    // Release the connection point container. We're done with it.
    RELEASE_INTERFACE(pConnPointContainer);
  }

  return pConnPoint;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiBall::ConnectBallSink

  Summary:  Connect the BallSink to the server COBall source.

  Args:     void

  Modifies: ...

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiBall::ConnectBallSink(void)
{
  HRESULT hr = E_FAIL;
  DWORD dwKey;
  IConnectionPoint* pConnPoint = NULL;

  if (!m_dwBallSink)
  {
    // Get the Ball Sink connection point.
    pConnPoint = GetConnectionPoint(IID_IBallSink);
    if (NULL != pConnPoint)
    {
      // Connect the object in the server to the Ball Sink in this client.
      hr = pConnPoint->Advise(m_pCOBallSink, &dwKey);
      if (SUCCEEDED(hr))
        m_dwBallSink = dwKey;

      // Release the connection point. We're done with it.
      RELEASE_INTERFACE(pConnPoint);
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiBall::DisconnectBallSink

  Summary:  Disconnect the BallSink from the server COBall source.

  Args:     void.

  Modifies: ...

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiBall::DisconnectBallSink(void)
{
  HRESULT hr = E_FAIL;
  IConnectionPoint* pConnPoint;

  if (m_dwBallSink)
  {
    // Get the Ball Sink connection point.
    pConnPoint = GetConnectionPoint(IID_IBallSink);
    if (NULL != pConnPoint)
    {
      // Disconnect the object in the server from the Ball Sink in
      // this client.
      hr = pConnPoint->Unadvise(m_dwBallSink);
      if (SUCCEEDED(hr))
        m_dwBallSink = 0;

      // Release the connection point. We're done with it.
      RELEASE_INTERFACE(pConnPoint);
    }
  }

  return hr;
}
