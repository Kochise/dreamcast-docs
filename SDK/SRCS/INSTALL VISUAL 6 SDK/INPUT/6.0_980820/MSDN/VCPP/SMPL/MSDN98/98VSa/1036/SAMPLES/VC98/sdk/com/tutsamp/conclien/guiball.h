/*+==========================================================================
  File:      GUIBALL.H

  Summary:   Include file for the CGuiBall C++ class. A GuiBall is a C++
             object that moves and displays a bouncing ball in the client
             area of a designated window. GuiBall is anchored to the
             Windows GUI (Graphical User Interface) environment. This
             GuiBall object continuously paints a ball image based on data
             it obtains from a virtual ball object. This virtual ball
             object is instantiated as a COM object (a COBall) in a
             separate In-process server, CONSERVE.

             GuiBall uses the system timer to issue WM_TIMER messages that
             cause a continuous moving and displaying of the ball. GuiBall
             provides methods to initialize the GuiBall, paint the ball
             image, and restart the motion.

             For a comprehensive tutorial code tour of GUIBALL's contents
             and offerings see the tutorial CONCLIEN.HTM file. For more
             specific technical details on the internal workings see the
             comments dispersed throughout the GUIBALL source code.

  Classes:   CGuiBall

  Origin:    5-30-96: atrent - Editor inheritance from GUIBALL.H in the
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

#if !defined(GUIBALL_H)
#define GUIBALL_H

#if defined(__cplusplus)


// Here are constants for the delays in milliseconds that control
// the incremental motion of the ball and how often a snapshot of
// the ball image is painted. Other constants are for the ball's
// bounce sound.
enum
{
  BALL_PAINT_DELAY  = 30,
  BALL_MOVE_DELAY = 100,
  BOUNCE_SOUND_DURATION = 30,
  BOUNCE_BOTTOM_FREQUENCY = 800,
  BOUNCE_SIDE_FREQUENCY = 2400,
  BOUNCE_TOP_FREQUENCY = 4800
};


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CGuiBall

  Summary:  Class to encapsulate the displayable Graphical User
            Interface GUI Ball object.

  Methods:  CGuiBall
              Constructor.
            ~CGuiBall
              Destructor.
            BOOL Init(HWND hWnd);
              Initialize the GuiBall.
            void PaintBall(void);
              Paint one image of the Ball.
            void Restart(void);
              Restart the process including clear window, move ball to
              start position, restart motion.
            void PaintWin(void);
              Repaint the window but don't restart motion.
            void BounceBottom(void);
            void BounceSide(void);
            void BounceTop(void);
              Perform GUI acton associated with these bounce events.
            HRESULT ConnectBallSink(void);
              Connect the BallSink to the server COBall source.
            HRESULT DisconnectBallSink(void);
              Disconnect the BallSink from the server COBall source.
            IConnectionPoint* GetConnectionPoint(REFIID riid);
              Private method to obtain a connection point interface.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CGuiBall
{
  public:
    CGuiBall(void);
    ~CGuiBall(void);
    BOOL Init(HWND hWnd);
    void PaintBall(void);
    void Restart(void);
    void PaintWin(void);
    void BounceBottom(void);
    void BounceSide(void);
    void BounceTop(void);
    HRESULT ConnectBallSink(void);
    HRESULT DisconnectBallSink(void);

  private:
    HWND       m_hWnd;
    IBall*     m_pIBall;
    COLORREF   m_crColor;
    POINT      m_OldPos;
    POINT      m_OldExt;
    IUnknown*  m_pCOBallSink;
    DWORD      m_dwBallSink;
    DWORD      m_dwBounceSndDur;
    DWORD      m_dwBounceBotFreq;
    DWORD      m_dwBounceSideFreq;
    DWORD      m_dwBounceTopFreq;

    IConnectionPoint* GetConnectionPoint(REFIID riid);
};


#endif // __cplusplus

#endif
