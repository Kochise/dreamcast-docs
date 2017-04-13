/*+==========================================================================
  File:      LISTSINK.H

  Summary:   Include file for the COPageListSink COM object class.

             COPageListSink offers a main IUnknown standard interface and
             the custom IPageListSink interface (outgoing connection
             events from COPageList objects). This multiple interface COM
             Object Class is achieved via the technique of nested classes.
             The implementation of the IPageListSink interface is nested
             inside of the COPageListSink Class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial PERCLIEN.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Functions: .

  Classes:   COPageListSink.

  Origin:    5-25-97: atrent - Editor-inheritance from SINK.H in the
             STOCLIEN Tutorial Code Sample. [Revised]

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

#if !defined(LISTSINK_H)
#define LISTSINK_H

#ifdef __cplusplus


/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: COPageListSink

  Summary:     The main Sink COM object class for COPageListSink COM
               objects. COM objects of this class offer the IPageListSink
               sink interface supporting various PageList events. The
               mulitple interfaces on this COM object are constructed via
               the nested interface classes technique.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               IPageListSink
                 Sink interface for PageList events.

  Aggregation: Yes, COPageListSink COM Objects are aggregatable by passing
               a non-NULL pUnkOuter IUnknown pointer into the constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class COPageListSink : public IUnknown
{
  public:
    // Main Object Constructor & Destructor.
    COPageListSink(IUnknown* pUnkOuter, CGuiList* pGuiList);
    ~COPageListSink(void);

    // IUnknown methods. Main object, non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

  private:
    // We declare nested class interface implementations here.

    class CImpIPageListSink : public IPageListSink
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIPageListSink(COPageListSink* pCO, IUnknown* pUnkOuter);
        ~CImpIPageListSink(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // IPageListSink methods.
        STDMETHODIMP         Loaded(void);
        STDMETHODIMP         Saved(void);
        STDMETHODIMP         Cleared(void);
        STDMETHODIMP         PageAdded(INT iPage);
        STDMETHODIMP         PageDeleted(INT iPage);
        STDMETHODIMP         PageSet(INT iPage);

      private:
        // Data private to this interface implementation of IPageList.
        COPageListSink*  m_pCO;          // Parent Object back pointer.
        IUnknown*        m_pUnkOuter;    // Outer unknown for Delegation.
    };

    // Make the otherwise private and nested IPageListSink interface
    // implementation a friend to COM object instantiations of this
    // COPageListSink COM object class.
    friend CImpIPageListSink;

    // Private data of COPageListSink COM objects.

    // Nested IPageListSink implementation instantiation.  This
    // IPageListSink interface is instantiated inside this COPageListSink
    // object as a native interface.
    CImpIPageListSink    m_ImpIPageListSink;

    // Main Object reference count.
    ULONG                m_cRefs;

    // Outer unknown (aggregation delegation). Used when this COM object
    // is being aggregated.
    IUnknown*            m_pUnkOuter;

    // Pointer to the main object that can service the Sink events.
    CGuiList*            m_pGuiList;
};

#endif // __cplusplus


#endif // LISTSINK_H
