/*+==========================================================================
  File:      PAGELIST.H

  Summary:   Include file for the connectable COPageList COM object class.

             COPageList offers a main standard IUnknown interface (basic
             COM object features), an implementation of the standard
             IConnectionPointContainer interface (connectable object
             features), an implementation of the standard IPersistStream
             interface (stream persistence features), and an
             implementation of the custom IPageList interface (drawing
             PageList-related features). This multiple interface COM
             Object Class is achieved via the technique of nested classes.
             The implementation of the various interfaces are nested
             inside of the COPageList Class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial PERSERVE.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source code.

  Functions: .

  Classes:   COPageList.

  Origin:    2-4-97: atrent - Editor-inheritance from PAPER.H in
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

#if !defined(PAGELIST_H)
#define PAGELIST_H

#ifdef __cplusplus


// Current format version of PageList is 1.0. Thus, the format version
// is a compile-time constant.
#define PAGELIST_VERSION10 MAKELONG(0,1)

// PageList allocation sizes for the Dynamic PageList array.
enum
{
  PAGELIST_ALLOC_INIT = 30,
  PAGELIST_ALLOC = 20
};

// Strings used for assembling IStorage/IStream names.
#define DRAWING_STR "Drawing"
#define TEXT_STR    "Text"

// The PageList item structure.
typedef struct _PAGEITEM
{
  SHORT     nType;                       // Page Type.
  BOOL      bOpen;                       // Page Open status.
  INT       iPage;                       // Page Number.
  WCHAR     wszDataName[PAGE_NAME_SIZE]; // Page Storage/Stream Data Name.
  WCHAR     wszTitle[PAGE_TITLE_SIZE];   // Page Title.
} PAGEITEM;


// Properties of the PageList.
typedef struct _PAGELISTPROPS
{
  LONG lPageListVersion;
  LONG lPageListSize;
  LONG lPageNameCounter;
  WCHAR wszTitle[PAGE_TITLE_SIZE];
  WCHAR wszAuthor[PAGE_TITLE_SIZE];
  WCHAR wszReserved1[PAGE_TITLE_SIZE];
} PAGELISTPROPS;


// PageList event constants.
enum PAGELIST_EVENT
{
  PAGELIST_EVENT_NONE = 0,
  PAGELIST_EVENT_LOADED,
  PAGELIST_EVENT_SAVED,
  PAGELIST_EVENT_CLEARED,
  PAGELIST_EVENT_PAGEADDED,
  PAGELIST_EVENT_PAGEDELETED,
  PAGELIST_EVENT_PAGESET
};


/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: COPageList

  Summary:     COM object class for COPageList COM objects.  COM objects
               of this class encapsulate management of a page list. The
               list has items representing user editable pages. The
               mulitple interfaces on this COM object are constructed via
               the nested interface classes technique.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               IConnectionPointContainer
                 Standard Connection Point container features rendering
                 COPageList objects connectable objects.
               IPersistStream
                 Standard Stream Persistance features.
               IPageList
                 Custom interface providing basic PageList features.

  Aggregation: Yes, COPageList COM Objects are aggregatable by passing
               a non-NULL pUnkOuter IUnknown pointer into the constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class COPageList : public IUnknown
{
  public:
    // Main Object Constructor & Destructor.
    COPageList(IUnknown* pUnkOuter, CServer* pServer);
    ~COPageList(void);

    // A general public method for initializing this newly created
    // object. Creates any subordinate arrays, structures, or objects.
    // Not exposed as part of an interface. Used by Class Factory.
    HRESULT Init(void);

    // Main object IUnknown methods. Non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

  private:
    // We declare nested class interface implementations here.

    class CImpIConnectionPointContainer : public IConnectionPointContainer
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIConnectionPointContainer(COPageList* pCO, IUnknown* pUnkOuter);
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
        COPageList*   m_pCO;          // Parent Object back pointer.
        IUnknown*     m_pUnkOuter;    // Outer unknown for Delegation.
    };

    class CImpIPersistStream : public IPersistStream
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIPersistStream(COPageList* pCO, IUnknown* pUnkOuter);
        ~CImpIPersistStream(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // IPersistStream methods.
        STDMETHODIMP         GetClassID(CLSID* pClassID);
        STDMETHODIMP         IsDirty(void);
        STDMETHODIMP         Load(IStream* pIStream);
        STDMETHODIMP         Save(IStream* pIStream, BOOL bClearDirty);
        STDMETHODIMP         GetSizeMax(ULARGE_INTEGER* pcbSize);

      private:
        // Data private to this interface implementation.
        COPageList*   m_pCO;          // Parent Object back pointer.
        IUnknown*     m_pUnkOuter;    // Outer unknown for Delegation.
    };

    class CImpIPageList : public IPageList
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIPageList(COPageList* pCO, IUnknown* pUnkOuter);
        ~CImpIPageList(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // IPageList methods.
        STDMETHODIMP         Get(
                                 INT     iPage,
                                 BOOL*   pbOpen,
                                 SHORT*  pnType,
                                 WCHAR*  pwszTitle,
                                 WCHAR*  pwszDataName);
        STDMETHODIMP         Set(
                                 INT     iPage,
                                 SHORT   nOpenStatus,
                                 WCHAR*  pwszNewTitle);
        STDMETHODIMP         Add(
                                 INT   iPage,
                                 SHORT nType,
                                 WCHAR* pwszTitle,
                                 INT* piNewPage);
        STDMETHODIMP         Delete(INT iPage);
        STDMETHODIMP         Clear(void);

      private:
        // Private utility methods of this interface implementation.
        HRESULT FindSlot(INT iPage, LONG* plSlot);
        HRESULT NextSlot(INT iPage, LONG* plSlot);
        HRESULT NextName(SHORT nType, WCHAR* pwszDataName);

        // Data private to this interface implementation of IPageList.
        COPageList*   m_pCO;          // Parent Object back pointer.
        IUnknown*     m_pUnkOuter;    // Outer unknown for Delegation.
    };

    // Make the otherwise private and nested interface implementations
    // friends to COM object instantiations of this COM object class.
    friend CImpIConnectionPointContainer;
    friend CImpIPersistStream;
    friend CImpIPageList;

    // Private method of main connectable COPageList COM object to
    // broadcast event notifications to all connected listening sinks.
    HRESULT NotifySinks(PAGELIST_EVENT PageListEvent, INT iPage);

    // Private method to Clear entire page list array.
    HRESULT Clear(void);

    // Private data of COPageList COM objects.

    // Nested IConnectionPointContainer implementation instantiation.
    CImpIConnectionPointContainer m_ImpIConnectionPointContainer;

    // Nested IPersistStream implementation instantiation.
    CImpIPersistStream m_ImpIPersistStream;

    // Nested IPageList implementation instantiation. This IPageList
    // interface is instantiated as a native interface of COPageList.
    CImpIPageList     m_ImpIPageList;

    // Main Object reference count.
    ULONG             m_cRefs;

    // Outer unknown (aggregation & delegation).
    IUnknown*         m_pUnkOuter;

    // Pointer to this component server's control object.
    CServer*          m_pServer;

    // The array of connection points for this connectable COM object.
    IConnectionPoint* m_aConnectionPoints[MAX_CONNECTION_POINTS];

    // The following private data and methods constitute the working
    // heart of COPageList as an actual application object.
    PAGELISTPROPS     m_PageListProps;// For file storage.
    PAGEITEM*         m_paPageList;   // Dynamic page list array pointer.
    LONG              m_lPageListEnd; // Current end of the page list.
    LONG              m_lPageListMax; // Current end of the page list array.
    BOOL              m_bDirty;       // RAM doesn't match file--save needed.
    CLSID             m_ClassID;      // CLSID of this COM Object.
};

#endif // __cplusplus


#endif // PAGELIST_H
