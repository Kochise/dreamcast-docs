/*+==========================================================================
  File:      TEXTSINK.H

  Summary:   Include file for the COTextPageSink COM object class.

             COTextPageSink offers a main IUnknown standard interface and
             the custom ITextPageSink interface (outgoing connection
             events from COTextPage objects). This multiple interface COM
             Object Class is achieved via the technique of nested classes.
             The implementation of the ITextPageSink interface is nested
             inside of the COTextPageSink Class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial PERCLIEN.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Functions: .

  Classes:   COTextPageSink.

  Origin:    5-25-96: atrent - Editor-inheritance from SINK.H in the
             STOCLIEN Tutorial Code Sample.

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

#if !defined(TEXTSINK_H)
#define TEXTSINK_H

#ifdef __cplusplus


/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: COTextPageSink

  Summary:     The main Sink COM object class for COTextPageSink COM
               objects. COM objects of this class offer the ITextPageSink
               sink interface supporting various TextPage events. The
               mulitple interfaces on this COM object are constructed via
               the nested interface classes technique.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               ITextPageSink
                 Sink interface for TextPage events.

  Aggregation: Yes, COTextPageSink COM Objects are aggregatable by passing
               a non-NULL pUnkOuter IUnknown pointer into the constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class COTextPageSink : public IUnknown
{
  public:
    // Main Object Constructor & Destructor.
    COTextPageSink(IUnknown* pUnkOuter, CGuiText* pGuiText);
    ~COTextPageSink(void);

    // IUnknown methods. Main object, non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

  private:
    // We declare nested class interface implementations here.

    class CImpITextPageSink : public ITextPageSink
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpITextPageSink(COTextPageSink* pCO, IUnknown* pUnkOuter);
        ~CImpITextPageSink(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // ITextPageSink methods.
        STDMETHODIMP         Loaded(void);
        STDMETHODIMP         Saved(void);
        STDMETHODIMP         Put(void);
        STDMETHODIMP         Cleared(void);

      private:
        // Data private to this interface implementation of ITextPage.
        COTextPageSink*  m_pCO;          // Parent Object back pointer.
        IUnknown*        m_pUnkOuter;    // Outer unknown for Delegation.
    };

    // Make the otherwise private and nested ITextPageSink interface
    // implementation a friend to COM object instantiations of this
    // COTextPageSink COM object class.
    friend CImpITextPageSink;

    // Private data of COTextPageSink COM objects.

    // Nested ITextPageSink implementation instantiation.  This
    // ITextPageSink interface is instantiated inside this COTextPageSink
    // object as a native interface.
    CImpITextPageSink    m_ImpITextPageSink;

    // Main Object reference count.
    ULONG                m_cRefs;

    // Outer unknown (aggregation delegation). Used when this COM object
    // is being aggregated.
    IUnknown*            m_pUnkOuter;

    // Pointer to the main object that can service the Sink events.
    CGuiText*            m_pGuiText;
};

#endif // __cplusplus


#endif // TEXTSINK_H
