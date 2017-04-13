/*+==========================================================================
  File:      DRAWSINK.H

  Summary:   Include file for the CODrawPageSink COM object class.

             CODrawPageSink offers a main IUnknown interface and the
             custom IDrawPageSink interface (outgoing connection events
             from CODrawPage DrawPage objects). This multiple interface
             COM Object Class is achieved via the technique of nested
             classes.  The implementation of the IDrawPageSink interface
             is nested inside of the CODrawPageSink Class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial PERCLIEN.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Functions: .

  Classes:   CODrawPageSink.

  Origin:    5-24-97: atrent - Editor-inheritance from TEXTSINK.H in the
             PERCLIEN Tutorial Code Sample.

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

#if !defined(DRAWSINK_H)
#define DRAWSINK_H

#ifdef __cplusplus


/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: CODrawPageSink

  Summary:     The main Sink COM object class for CODrawPageSink COM
               objects. COM objects of this class offer the IDrawPageSink
               sink interface supporting various DrawPage events. The
               mulitple interfaces on this COM object are constructed via
               the nested interface classes technique.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               IDrawPageSink
                 Sink interface for DrawPage events.

  Aggregation: Yes, CODrawPageSink COM Objects are aggregatable by passing
               a non-NULL pUnkOuter IUnknown pointer into the constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class CODrawPageSink : public IUnknown
{
  public:
    // Main Object Constructor & Destructor.
    CODrawPageSink(IUnknown* pUnkOuter, CGuiDraw* pGuiDraw);
    ~CODrawPageSink(void);

    // IUnknown methods. Main object, non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

  private:
    // We declare nested class interface implementations here.

    class CImpIDrawPageSink : public IDrawPageSink
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIDrawPageSink(CODrawPageSink* pCO, IUnknown* pUnkOuter);
        ~CImpIDrawPageSink(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // IDrawPageSink methods.
        STDMETHODIMP         Loaded(void);
        STDMETHODIMP         Saved(void);
        STDMETHODIMP         Cleared(void);
        STDMETHODIMP         Resized(SHORT nWidth, SHORT nHeight);
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

      private:
        // Data private to this interface implementation of IDrawPage.
        CODrawPageSink*  m_pCO;          // Parent Object back pointer.
        IUnknown*        m_pUnkOuter;    // Outer unknown for Delegation.
    };

    // Make the otherwise private and nested IDrawPageSink interface
    // implementation a friend to COM object instantiations of this
    // CODrawPageSink COM object class.
    friend CImpIDrawPageSink;

    // Private data of CODrawPageSink COM objects.

    // Nested IDrawPageSink implementation instantiation.  This
    // IDrawPageSink interface is instantiated inside this CODrawPageSink
    // object as a native interface.
    CImpIDrawPageSink    m_ImpIDrawPageSink;

    // Main Object reference count.
    ULONG                m_cRefs;

    // Outer unknown (aggregation delegation). Used when this COM object
    // is being aggregated.
    IUnknown*            m_pUnkOuter;

    // Pointer to the main object that can service the Sink events.
    CGuiDraw*            m_pGuiDraw;
};

#endif // __cplusplus


#endif // DRAWSINK_H
