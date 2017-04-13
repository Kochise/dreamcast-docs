/*+==========================================================================
  File:      SINK.H

  Summary:   Include file for the COPaperSink COM object class.

             COPaperSink offers a main IUnknown interface and the custom
             IPaperSink interface (outgoing connection events from COPaper
             drawing paper objects). This multiple interface COM Object
             Class is achieved via the technique of nested classes.  The
             implementation of the IPaperSink interface is nested inside
             of the COPaperSink Class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial SSOCLIEN.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Functions: .

  Classes:   COPaperSink.

  Origin:    8-23-97: atrent - Editor-inheritance from BALL.H in the
             CONSERVE Tutorial Code Sample. [Revised]

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

#if !defined(SINK_H)
#define SINK_H

#ifdef __cplusplus


/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: COPaperSink

  Summary:     The main Sink COM object class for COPaperSink COM objects.
               COM objects of this class offer the IPaperSink sink
               interface supporting various drawing paper events. The
               mulitple interfaces on this COM object are constructed via
               the nested interface classes technique.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               IPaperSink
                 Sink interface for Paper events.

  Aggregation: Yes, COPaperSink COM Objects are aggregatable by passing
               a non-NULL pUnkOuter IUnknown pointer into the constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class COPaperSink : public IUnknown
{
  public:
    // Main Object Constructor & Destructor.
    COPaperSink(IUnknown* pUnkOuter, CGuiPaper* pGuiPaper);
    ~COPaperSink(void);

    // IUnknown methods. Main object, non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

  private:
    // We declare nested class interface implementations here.

    class CImpIPaperSink : public IPaperSink
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIPaperSink(COPaperSink* pCO, IUnknown* pUnkOuter);
        ~CImpIPaperSink(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // IPaperSink methods.
        STDMETHODIMP         Locked(void);
        STDMETHODIMP         Unlocked(void);
        STDMETHODIMP         Loaded(void);
        STDMETHODIMP         Saved(void);
        STDMETHODIMP         InkStart(
                               SHORT nX,
                               SHORT nY,
                               SHORT nWidth,
                               COLORREF crInkColor);
        STDMETHODIMP         InkDraw(
                               SHORT nX,
                               SHORT nY);
        STDMETHODIMP         InkStop(
                               SHORT nX,
                               SHORT nY);
        STDMETHODIMP         Erased(void);
        STDMETHODIMP         Resized(LONG lWidth, LONG lHeight);

      private:
        // Data private to this interface implementation of IPaper.
        COPaperSink* m_pCO;          // Parent Object back pointer.
        IUnknown*    m_pUnkOuter;    // Outer unknown for Delegation.
    };

    // Make the otherwise private and nested IPaperSink interface
    // implementation a friend to COM object instantiations of this
    // COPaperSink COM object class.
    friend CImpIPaperSink;

    // Private data of COPaperSink COM objects.

    // Nested IPaperSink implementation instantiation.  This IPaperSink
    // interface is instantiated inside this COPaperSink object as a
    // native interface.
    CImpIPaperSink   m_ImpIPaperSink;

    // Main Object reference count.
    ULONG            m_cRefs;

    // Outer unknown (aggregation delegation). Used when this COM object
    // is being aggregated.
    IUnknown*        m_pUnkOuter;

    // Pointer to the main object that can service the Sink events.
    CGuiPaper*       m_pGuiPaper;
};

typedef COPaperSink* PCOPaperSink;

#endif // __cplusplus


#endif // SINK_H
