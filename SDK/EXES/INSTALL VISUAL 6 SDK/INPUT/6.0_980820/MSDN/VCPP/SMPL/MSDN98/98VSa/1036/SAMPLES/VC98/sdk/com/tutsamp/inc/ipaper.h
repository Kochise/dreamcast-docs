/*+==========================================================================
  File:      IPAPER.H

  Summary:   This is the common include file for the drawing paper-related
             COM Interfaces.  The Interface abstract base classes are
             declared.

             This file is global to all the Tutorial Code Samples (kept in
             the ..\INC directory).  It is a good practice to factor out
             Interface and GUID specifications to reduce the possibility
             of GUID or interface conflicts.

  Classes:   IPaper, IPaperSink.

  Functions: .

  Origin:    6-10-96: atrent - Revised for the COM Tutorial Samples.

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

#if !defined(IPAPER_H)
#define IPAPER_H

#if !defined(RC_INCLUDE)


/*I+I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I
  Interface: IPaper

  Summary:   Interface for free-form drawing on scratch-pad electronic
             paper-like COM Objects.

  Methods:   InitPaper
               Init Paper object. Create Ink Data array.
             Lock
               Client takes control of the Paper. Locks out other clients.
             Unlock
               Client relinquishes control of the Paper.
             Load
               Load Paper content from client's compound file. Does Redraw.
             Save
               Save Paper content to client's compound file.
             InkStart
               Client starts color ink drawing to the Paper surface.
             InkDraw
               Client puts ink data points on the electronic Paper surface.
             InkStop
               Client stops ink drawing to the Paper surface.
             Erase
               Erase the current Paper content. Notify Sinks.
             Resize
               Resize the drawing paper rectangle size.
             Redraw
               Redraw content of Paper object. Notify sinks.
I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I-I*/
DECLARE_INTERFACE_(IPaper, IUnknown)
{
  // IUnknown methods.
  STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
  STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
  STDMETHOD_(ULONG,Release) (THIS) PURE;

  // IPaper methods.
  STDMETHOD(InitPaper)  (THIS_ RECT*, BOOL*) PURE;
  STDMETHOD(Lock)       (THIS_ SHORT*) PURE;
  STDMETHOD(Unlock)     (THIS_ SHORT) PURE;
  STDMETHOD(Load)       (THIS_ SHORT, IStorage*) PURE;
  STDMETHOD(Save)       (THIS_ SHORT, IStorage*) PURE;
  STDMETHOD(InkStart)   (THIS_ SHORT, SHORT, SHORT, SHORT, COLORREF) PURE;
  STDMETHOD(InkDraw)    (THIS_ SHORT, SHORT, SHORT) PURE;
  STDMETHOD(InkStop)    (THIS_ SHORT, SHORT, SHORT) PURE;
  STDMETHOD(Erase)      (THIS_ SHORT) PURE;
  STDMETHOD(Resize)     (THIS_ SHORT, SHORT, SHORT) PURE;
  STDMETHOD(Redraw)     (THIS_ SHORT) PURE;
};


/*I+I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I
  Interface: IPaperSink

  Summary:   Sink Connection Interface for use by drawing paper-like COM
             Objects that communicate events back to the client.

  Methods:   Locked
               A client has taken control and locked its use of the Paper.
             Unlocked
               A client has relinquished control of the Paper.
             Loaded
               A client has loaded Paper content from its own compound file.
             Saved
               A client has saved Paper content to its own compound file.
             InkStart
               A client started a color ink drawing sequence to the Paper.
             InkDraw
               A client is putting ink data points on the Paper surface.
             InkStop
               A client stopped its ink drawing sequence to the Paper.
             Erased
               A client has erased all ink data from the Paper.
             Resized
               A client has resized the Paper.
I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I-I*/
DECLARE_INTERFACE_(IPaperSink, IUnknown)
{
  // IUnknown methods.
  STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
  STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
  STDMETHOD_(ULONG,Release) (THIS) PURE;

  // IPaperSink methods.
  STDMETHOD(Locked)     (THIS) PURE;
  STDMETHOD(Unlocked)   (THIS) PURE;
  STDMETHOD(Loaded)     (THIS) PURE;
  STDMETHOD(Saved)      (THIS) PURE;
  STDMETHOD(InkStart)   (THIS_ SHORT, SHORT, SHORT, COLORREF) PURE;
  STDMETHOD(InkDraw)    (THIS_ SHORT, SHORT) PURE;
  STDMETHOD(InkStop)    (THIS_ SHORT, SHORT) PURE;
  STDMETHOD(Erased)     (THIS) PURE;
  STDMETHOD(Resized)    (THIS_ SHORT, SHORT) PURE;
};


#endif // RC_INCLUDE

#endif // IPAPER_H
