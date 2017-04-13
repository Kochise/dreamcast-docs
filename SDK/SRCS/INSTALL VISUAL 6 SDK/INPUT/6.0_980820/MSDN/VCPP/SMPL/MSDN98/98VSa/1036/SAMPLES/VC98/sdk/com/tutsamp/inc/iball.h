/*+==========================================================================
  File:      IBALL.H

  Summary:   This is the common include file for the Ball-related COM
             Interfaces.  The Interface abstract base classes are
             declared.

             This file is global to all the Tutorial Code Samples (kept in
             the ..\INC directory).  It is a good practice to factor out
             Interface and GUID specifications to reduce the possibility
             of GUID or interface conflicts.

  Classes:   IBall, IBallSink.

  Functions: none

  Origin:    5-30-96: atrent - Revised for the COM Tutorial Samples.

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

#if !defined(IBALL_H)
#define IBALL_H

#if !defined(RC_INCLUDE)


/*I+I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I
  Interface: IBall

  Summary:   Interface for moving Ball-like COM Objects.

  Methods:   Reset
               Init and reset the ball.
             Move
               Move the ball.
             GetBall
               Obtain the ball's current position, extent, and color.
I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I-I*/
DECLARE_INTERFACE_(IBall, IUnknown)
{
  // IUnknown methods.
  STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
  STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
  STDMETHOD_(ULONG,Release) (THIS) PURE;

  // IBall methods.
  STDMETHOD(Reset)      (THIS_ RECT*, SHORT) PURE;
  STDMETHOD(Move)       (THIS_ BOOL) PURE;
  STDMETHOD(GetBall)    (THIS_ POINT*, POINT*, COLORREF*) PURE;
};


/*I+I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I
  Interface: IBallSink

  Summary:   Sink Connection Interface for Ball-like COM Objects that
             communicate events back to the client.

  Methods:   BounceBottom
               The virtual ball hit the bottom edge of its bounding
               rectangle and bounced.
             BounceLeft
               The virtual ball hit the left edge of its bounding
               rectangle and bounced.
             BounceRight
               The virtual ball hit the right edge of its bounding
               rectangle and bounced.
             BounceTop
               The virtual ball hit the top edge of its bounding
               rectangle and bounced.
I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I-I*/
DECLARE_INTERFACE_(IBallSink, IUnknown)
{
  // IUnknown methods.
  STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
  STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
  STDMETHOD_(ULONG,Release) (THIS) PURE;

  // IBallSink methods.
  STDMETHOD(BounceBottom)   (THIS) PURE;
  STDMETHOD(BounceLeft)     (THIS) PURE;
  STDMETHOD(BounceRight)    (THIS) PURE;
  STDMETHOD(BounceTop)      (THIS) PURE;
};


#endif // RC_INCLUDE

#endif // IBALL_H
