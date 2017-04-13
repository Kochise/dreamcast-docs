/*+==========================================================================
  File:      GUIBALL.CPP

  Summary:   Implementation file for the CGuiBall C++ class. A GuiBall is
             a C++ object that uses three independent worker threads to
             display a moving and bouncing ball in the client area of a
             designated window.  It is anchored to the Windows GUI
             (Graphical User Interface) environment. This GuiBall object
             continuously paints a ball image based on data it obtains
             from a virtual ball object. This virtual ball object is
             instantiated as a COM object (a COBall) in a separate
             thread-safe In-process server.

             GuiBall launches three threads which all continuously and
             asynchronously command the ball to move. GuiBall itself
             provides methods to initialize the GuiBall, paint the ball
             image, and restart the motion. The cool thing about this
             arrangement between client and server is that the ball
             changes color as it moves. The ball color indicates the
             thread that last moved the ball. This gives a visual
             impact to multi-threading.

             For a comprehensive tutorial code tour of GUIBALL's contents
             and offerings see the tutorial FRECLIEN.HTM file. For more
             specific technical details on the internal workings see the
             comments dispersed throughout the GUIBALL source code.

  Classes:   CThreadInitData, CGuiBall

  Origin:    4-5-96: atrent - Created for COM Tutorial Code Samples.
             Also benefits from the GDIDEMO sample in the Win32 samples of
             the Win32 SDK.

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
  We include OLE2.H because we will be calling the COM/OLE Libraries.
  We include APPUTIL.H because we will be building this application using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include IBALL.H and BALLGUID.H for the common Ball-related Interface
    class, GUID, and CLSID specifications.
  We include GUIBALL.H because it has the C++ class used for GUI display
    of the moving ball.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <apputil.h>
#include <iball.h>
#include <ballguid.h>
#include "guiball.h"
#include "freclien.h"


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiBall::CGuiBall

  Summary:  Constructor.

  Args:     void

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CGuiBall::CGuiBall(void)
{
  m_hWnd    = 0;
  m_pIBall  = NULL;
  m_crColor = RGB(0,0,0);
  m_dwBallThread1 = 0;
  m_dwBallThread2 = 0;
  m_dwBallThread3 = 0;
  m_hBallThreads[0] = 0;
  m_hBallThreads[1] = 0;
  m_hBallThreads[2] = 0;
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

  if (m_pIBall)
  {
    // Kill the client's app timer for its repaints.
    KillTimer(m_hWnd, 1);

    // Call down to the server's COBall and tell it to shutdown.
    m_pIBall->Move(FALSE);

    // Wait for the threads to terminate before closing their thread handles.
    WaitForMultipleObjects(3, m_hBallThreads, TRUE, INFINITE);
    for (size_t i = 0; i<3; i++)
      CloseHandle(m_hBallThreads[i]);

    // Release for each of the thread copies handed out.
    m_pIBall->Release();
    m_pIBall->Release();
    m_pIBall->Release();
    // Do final Release for the main copy held in CGuiBall.
    RELEASE_INTERFACE(m_pIBall);
  }
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: BallThreadProc

  Summary:  The common thread procedure for all Ball-moving free threads.

  Args:     LPARAM lparam
              Standard Window Proc parameter.

  Modifies: .

  Returns:  DWORD
              Thread procedure return (usually msg.wParam).
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
DWORD WINAPI BallThreadProc(
               LPARAM lparam)
{
  CThreadInitData* pInitData = (CThreadInitData*) lparam;
  DWORD nEndCount = 0;
  HRESULT hr;
  BOOL bAlive;

  // Initialize COM for use by this thread. Tell COM this new thread
  // is another free-threaded thread in the multi-threaded apartment.
  hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
  bAlive = SUCCEEDED(hr);

  if (bAlive)
  {
    // Continuously move the ball while it is still alive.
    while (bAlive)
    {
      // Use system timer to slow down the ball motion to the range
      // of the humanly perceptible.
      if (GetTickCount() > nEndCount)
      {
        // After the delay, call from this thread thru IBall interface
        // to move the ball that lives in the single COBall COM object.
        // Set bAlive flag FALSE if the COBall can no longer move.
        hr = pInitData->m_pIBall->Move(TRUE);
        bAlive = (NOERROR == hr);

        // Set new timer end count.
        nEndCount = GetTickCount() + pInitData->m_nDelay;
      }
    }

    // UnInitialize COM for use by this thread.
    CoUninitialize();
  }

  return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiBall::Init

  Summary:  Get everything related to CGuiBall started. Make any
            subordinate objects, like COBall, and get it started. Starts
            the worker move-threads that breathe life into the COBall COM
            object.

  Args:     HWND hWnd
              Handle of the main window. Part of what makes CGuiBall
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

  if (hWnd)
  {
    m_hWnd = hWnd;

    // Call COM service to create the single COBall instance.
    // We are not aggregating it so we ask for its IBall interface
    // directly.
    hr = CoCreateInstance(
           CLSID_DllBall,
           NULL,
           CLSCTX_INPROC_SERVER,
           IID_IBall,
           (PPVOID)&m_pIBall);
    if (SUCCEEDED(hr))
    {
      // Now start up 3 client BallThreads that will all try to move the
      // Ball concurrently. They will bring independent asynchronous life
      // to the ball. The separate main process thread displays the ball.
      // These threads (including the main display thread) will all
      // comprise the multi-threaded apartment of the main process.

      // Create Structures for thread initialization.
      m_BallThreadData1.m_hWnd = hWnd;
      m_BallThreadData1.m_nDelay = BALL_MOVE_DELAY;
      m_BallThreadData1.m_pIBall = m_pIBall;
      m_BallThreadData2.m_hWnd = hWnd;
      m_BallThreadData2.m_nDelay = BALL_MOVE_DELAY;
      m_BallThreadData2.m_pIBall = m_pIBall;
      m_BallThreadData3.m_hWnd = hWnd;
      m_BallThreadData3.m_nDelay = BALL_MOVE_DELAY;
      m_BallThreadData3.m_pIBall = m_pIBall;

      // Create the ball-moving thread #1.
      m_hBallThreads[0] = CreateThread(
                            0,
                            0,
                            (LPTHREAD_START_ROUTINE) BallThreadProc,
                            (LPVOID) &m_BallThreadData1,
                            0,
                            &m_dwBallThread1);

      bOk = (NULL != m_hBallThreads[0]);
      if (bOk)
      {
        // AddRef for the copy handed out to free-thread1.
        m_pIBall->AddRef();

        // Create the Ball Moving Thread #2.
        m_hBallThreads[1] = CreateThread(
                              0,
                              0,
                              (LPTHREAD_START_ROUTINE) BallThreadProc,
                              (LPVOID) &m_BallThreadData2,
                              0,
                              &m_dwBallThread2);

        bOk = (NULL != m_hBallThreads[1]);
        if (bOk)
        {
          // AddRef for the copy handed out to free-thread2.
          m_pIBall->AddRef();

          // Create the Ball Moving Thread #3.
          m_hBallThreads[2] = CreateThread(
                                0,
                                0,
                                (LPTHREAD_START_ROUTINE) BallThreadProc,
                                (LPVOID) &m_BallThreadData3,
                                0,
                                &m_dwBallThread3);

          bOk = (NULL != m_hBallThreads[2]);
          if (bOk)
          {
            // AddRef for the copy handed out to free-thread3.
            m_pIBall->AddRef();
          }
        }
      }
    }
    else
      HrMsg(hWnd, TEXT(NOCOMOBJ_ERROR_STR), hr);

    if (!bOk)
    {
      hr = GetLastError();
      if (FAILED(hr))
        HrMsg(hWnd, TEXT(NOTHREAD_ERROR_STR), hr);
    }
  }

  if (bOk)
  {
    // Set up the client process to periodically paint the ball
    // thru WM_TIMER messages to the main Window proc.
    SetTimer(hWnd, 1, BALL_PAINT_DELAY, NULL);
  }

  return (bOk);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiBall::PaintBall

  Summary:  Tell CGuiBall to paint one image of the GuiBall.

  Args:     void

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CGuiBall::PaintBall(void)
{
  HDC       hDC;
  HBRUSH    hBrush;
  POINT     Org, Ext;
  HRGN      hNew;

  if (m_pIBall)
  {
    // Ask the COBall for its current ball (location, region, and color).
    m_pIBall->GetBall(&Org, &Ext, &m_crColor);

    // Create the new ball image/region.
    hNew = CreateEllipticRgn(Org.x, Org.y, Ext.x, Ext.y);

    if(hDC = GetDC(m_hWnd))
    {
      // Make a paint brush, dip it in pixel paint, and paint the
      // ball image.
      hBrush = CreateSolidBrush(m_crColor);
      FillRgn(hDC, hNew, hBrush);
      DeleteObject(hBrush);
      ReleaseDC(m_hWnd, hDC);
    }

    // Delete the region object.
    DeleteObject(hNew);
  }

  return;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiBall::Restart

  Summary:  Restart the display process. Places ball in start position
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
    GetClientRect(m_hWnd, &WinRect);
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

    // Paint a current  image of the ball wherever it is.
    PaintBall();

    ReleaseDC(m_hWnd, hDC);
  }

  return;
}
