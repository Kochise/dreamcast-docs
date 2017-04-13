/*+==========================================================================
  File:      TEXTPAGE.H

  Summary:   Include file for the connectable COTextPage COM object class.

             COTextPage offers a main standard IUnknown interface (basic
             COM object features), an implementation of the standard
             IConnectionPointContainer interface (connectable object
             features), an implementation of the standard
             IPersistStreamInit interface (stream persistent object
             features), and an implementation of the custom ITextPage
             interface (editable TextPage features). This multiple
             interface COM Object Class is achieved via the technique of
             nested classes.  The implementation of the various interfaces
             are nested inside of the COTextPage Class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial PERTEXT.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source code.

  Functions: .

  Classes:   COTextPage.

  Origin:    5-20-97: atrent - Editor-inheritance from PAPER.H in
             the STOSERVE Tutorial Code Sample.

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

#if !defined(TEXTPAGE_H)
#define TEXTPAGE_H

#ifdef __cplusplus


// Current format version of TextPage is 1.0. Thus, the format version
// is a compile-time constant.
#define TEXTPAGE_VERSION10 MAKELONG(0,1)

// TextPage allocation sizes for the TextPage.
enum
{
  TEXTPAGE_V10_MAX = 32000
};

// Properties of the TextPage.
typedef struct _TEXTPROPS
{
  ULONG ulVersion;
  ULONG ulMaxLength;
  ULONG ulLength;
  WCHAR wszTitle[PAGE_TITLE_SIZE];
} TEXTPROPS;


// TextPage event constants.
enum TEXTPAGE_EVENT
{
  TEXTPAGE_EVENT_NONE = 0,
  TEXTPAGE_EVENT_LOADED,
  TEXTPAGE_EVENT_SAVED,
  TEXTPAGE_EVENT_PUT,
  TEXTPAGE_EVENT_CLEARED
};


/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: COTextPage

  Summary:     COM object class for COTextPage COM objects.  COM objects
               of this class offer custom ITextPage interface features,
               GetLength, GetText, PutText, and Clear. To make COTextPage
               objects connectable, the standard IConnectionPointContainer
               interface features, FindConnectionPoint and
               EnumConnectionPoints are also implemented. The mulitple
               interfaces on this COM object are constructed via the
               nested interface classes technique.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               IConnectionPointContainer
                 Standard Connection Point container features rendering
                 COTextPage objects connectable objects.
               IPersistStreamInit
                 Standard Stream Persistance features rendering
                 COTextPage objects persistent objects.
               ITextPage
                 Custom interface providing basic TextPage features.

  Aggregation: Yes, COTextPage COM Objects are aggregatable by passing
               a non-NULL pUnkOuter IUnknown pointer into the constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class COTextPage : public IUnknown
{
  public:
    // Main COM Object Constructor & Destructor.
    COTextPage(IUnknown* pUnkOuter, CServer* pServer);
    ~COTextPage(void);

    // A general public method for initializing this newly created
    // object. Creates any subordinate arrays, structures, or objects.
    // Not exposed as part of an interface. Used by Class Factory.
    HRESULT Init(void);

    // Main COM Object IUnknown interface. Non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

  private:
    // We declare nested class interface implementations here.

    // Standard Connectable Object features.
    class CImpIConnectionPointContainer : public IConnectionPointContainer
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIConnectionPointContainer(COTextPage* pCO, IUnknown* pUnkOuter);
        ~CImpIConnectionPointContainer(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // IConnectionPointContainer methods.
        STDMETHODIMP         FindConnectionPoint(REFIID, IConnectionPoint**);
        STDMETHODIMP         EnumConnectionPoints(IEnumConnectionPoints**);

      private:
        // Data private to this interface implementation.
        COTextPage*   m_pCO;          // Parent Object back pointer.
        IUnknown*     m_pUnkOuter;    // Outer unknown for Delegation.
    };

    // Standard Object Persistence (in Streams) features.
    class CImpIPersistStreamInit : public IPersistStreamInit
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIPersistStreamInit(COTextPage* pCO, IUnknown* pUnkOuter);
        ~CImpIPersistStreamInit(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // IPersistStreamInit methods.
        STDMETHODIMP         GetClassID(CLSID* pClassID);
        STDMETHODIMP         IsDirty(void);
        STDMETHODIMP         Load(IStream* pIStream);
        STDMETHODIMP         Save(IStream* pIStream, BOOL bClearDirty);
        STDMETHODIMP         GetSizeMax(ULARGE_INTEGER* pcbSize);
        STDMETHODIMP         InitNew(void);

      private:
        // Data private to this interface implementation.
        COTextPage*   m_pCO;          // Parent Object back pointer.
        IUnknown*     m_pUnkOuter;    // Outer unknown for Delegation.
    };

    // Custom Text Entry/Edit page features.
    class CImpITextPage : public ITextPage
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpITextPage(COTextPage* pCO, IUnknown* pUnkOuter);
        ~CImpITextPage(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // ITextPage methods.
        STDMETHODIMP         GetLength(INT* piLength);
        STDMETHODIMP         GetText(WCHAR* pwszText);
        STDMETHODIMP         PutText(WCHAR* pwszText, INT iLength);
        STDMETHODIMP         Clear(BOOL bSaveNeeded);

      private:
        // Data private to this interface implementation of ITextPage.
        COTextPage*   m_pCO;          // Parent Object back pointer.
        IUnknown*     m_pUnkOuter;    // Outer unknown for Delegation.
    };

    // Make the otherwise private and nested interface implementations
    // friends to instantiations of this COTextPage COM object class.
    friend CImpIConnectionPointContainer;
    friend CImpIPersistStreamInit;
    friend CImpITextPage;

    // Private Methods of COTextPage COM objects.

    // Method to clear the COTextPage's current page text and reset
    // the page properties appropriately.
    HRESULT Clear(BOOL bSaveNeeded);

    // Method of main connectable COTextPage COM object to broadcast
    // event notifications to all connected listening sinks.
    HRESULT NotifySinks(TEXTPAGE_EVENT TextPageEvent);

    // Private Data of COTextPage COM objects.

    // Nested IConnectionPointContainer implementation instantiation.
    CImpIConnectionPointContainer m_ImpIConnectionPointContainer;

    // Nested IPersistStreamInit implementation instantiation.
    CImpIPersistStreamInit m_ImpIPersistStreamInit;

    // Nested ITextPage implementation instantiation. This ITextPage
    // interface is instantiated as a native interface of COTextPage.
    CImpITextPage     m_ImpITextPage;

    // Main Object reference count.
    ULONG             m_cRefs;

    // Outer unknown (aggregation & delegation).
    IUnknown*         m_pUnkOuter;

    // Pointer to this component server's control object.
    CServer*          m_pServer;

    // The array of connection points for this connectable COM object.
    IConnectionPoint* m_aConnectionPoints[MAX_CONNECTION_POINTS];

    // The following private data and methods constitute the working
    // heart of COTextPage as an actual application object.
    TEXTPROPS         m_TextProps;    // For saving properties in stream.
    CLSID             m_ClassID;      // CLSID of this COM Object.
    WCHAR*            m_pwszPageText; // The text to edit.
    BOOL              m_bInitNew;     // TRUE=>obj newly initialized in RAM.
    BOOL              m_bDirty;       // RAM no match file--save needed.
};

#endif // __cplusplus


#endif // TEXTPAGE_H
