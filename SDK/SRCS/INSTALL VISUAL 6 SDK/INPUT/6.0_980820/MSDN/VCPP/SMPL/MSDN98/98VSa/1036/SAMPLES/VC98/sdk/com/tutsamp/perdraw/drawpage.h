/*+==========================================================================
  File:      DRAWPAGE.H

  Summary:   Include file for the connectable CODrawPage COM object class.

             CODrawPage offers an implementation of a main standard
             IUnknown interface (basic COM object features), an
             implementation of the standard IConnectionPointContainer
             interface (connectable object features), an implementation of
             the standard IPersistStorage interface (storage-based
             persistent object features), and an implementation of the
             custom IDrawPage interface (free-form drawing page features).

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial PERDRAW.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source code.

  Functions: .

  Classes:   CODrawPage.

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

#if !defined(DRAWPAGE_H)
#define DRAWPAGE_H

#ifdef __cplusplus


// Current format version of Ink Data is 1.0. Thus, the format version
// is a compile-time constant.
#define INKDATA_VERSION20 MAKELONG(0,2)

// InkData allocation sizes for the Dynamic InkData array.
enum
{
  INKDATA_ALLOC_INIT = 3200,
  INKDATA_ALLOC = 800
};

// The types of Ink Data.
#define INKTYPE_NONE  0
#define INKTYPE_START 1
#define INKTYPE_DRAW  2
#define INKTYPE_STOP  3

// The Ink Data structure.
typedef struct _INKDATA
{
  SHORT nType;            // Ink Type.
  SHORT nX;               // X-coordinate of ink point.
  SHORT nY;               // Y-coordinate of ink point.
  SHORT nWidth;           // Ink line width.
  COLORREF crColor;       // Ink color.
} INKDATA;


// Properties of our electronic DrawPage.
typedef struct _DRAWPROPS
{
  LONG lInkDataVersion;
  LONG lInkArraySize;
  COLORREF crWinColor;
  RECT WinRect;
  WCHAR wszTitle[PAGE_TITLE_SIZE];
  WCHAR wszAuthor[PAGE_TITLE_SIZE];
  WCHAR wszReserved1[PAGE_TITLE_SIZE];
} DRAWPROPS;


// Drawing DrawPage event constants.
enum DRAWPAGE_EVENT
{
  DRAWPAGE_EVENT_NONE = 0,
  DRAWPAGE_EVENT_LOADED,
  DRAWPAGE_EVENT_SAVED,
  DRAWPAGE_EVENT_INKSTART,
  DRAWPAGE_EVENT_INKDRAW,
  DRAWPAGE_EVENT_INKSTOP,
  DRAWPAGE_EVENT_CLEARED,
  DRAWPAGE_EVENT_RESIZED
};

// Some strings used in compound file storage.

// Name of the stream containing the DrawPage properties.
#define WSZ_DRAWPROPS L"DRAWPROPS"

// Name of the stream containing the DrawPage ink data.
#define WSZ_DRAWDATA L"DRAWDATA"

// User type name for DrawPages.
#define SZ_CLIPUSERTYPE "DrawPage1.0 Drawing"


/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: CODrawPage

  Summary:     CODrawPage COM objects expose functionality to support
               drawing pages. This multiple interface COM Object Class is
               achieved via the technique of nested classes.  The
               implementation of the various interfaces are nested inside
               of the CODrawPage Class.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               IConnectionPointContainer
                 Standard Connection Point container features rendering
                 CODrawPage objects connectable objects.
               IPersistStorage
                 Standard interface providing features for object
                 persistence in compound file storages. Renders
                 CODrawPage objects persistent objects.
               IDrawPage
                 Custom interface providing free-form drawing
                 page features.

  Aggregation: Yes, CODrawPage COM Objects are aggregatable by passing
               a non-NULL pUnkOuter IUnknown pointer into the constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class CODrawPage : public IUnknown
{
  public:
    // Main Object Constructor & Destructor.
    CODrawPage(IUnknown* pUnkOuter, CServer* pServer);
    ~CODrawPage(void);

    // A general public method for initializing this newly created
    // object. Creates any subordinate arrays, structures, or objects.
    // Not exposed as part of an interface. Used in Class Factory.
    HRESULT Init(void);

    // IUnknown methods. Main object, non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

  private:
    // We declare nested class interface implementations here.

    class CImpIConnectionPointContainer : public IConnectionPointContainer
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIConnectionPointContainer(CODrawPage* pCO, IUnknown* pUnkOuter);
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
        CODrawPage*   m_pCO;          // Parent COM Object back pointer.
        IUnknown*     m_pUnkOuter;    // Outer unknown for Delegation.
    };

    class CImpIPersistStorage : public IPersistStorage
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIPersistStorage(CODrawPage* pCO, IUnknown* pUnkOuter);
        ~CImpIPersistStorage(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // IPersistStorage methods.
        STDMETHODIMP         GetClassID(CLSID* pClassID);
        STDMETHODIMP         IsDirty(void);
        STDMETHODIMP         InitNew(IStorage* pIStorage);
        STDMETHODIMP         Load(IStorage* pIStorage);
        STDMETHODIMP         Save(IStorage* pIStorage, BOOL bSameAsLoad);
        STDMETHODIMP         SaveCompleted(IStorage* pIStorage);
        STDMETHODIMP         HandsOffStorage(void);

      private:
        // Data private to this interface implementation.
        CODrawPage*   m_pCO;            // Parent COM Object back pointer.
        IUnknown*     m_pUnkOuter;      // Outer unknown for Delegation.
        IStorage*     m_pIStorage;      // Main DrawPage storage.
        IStream*      m_pIStream_Props; // Stream for Drawing Properties.
        IStream*      m_pIStream_Data;  // Stream for Drawing Ink Data.
    };

    class CImpIDrawPage : public IDrawPage
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIDrawPage(CODrawPage* pCO, IUnknown* pUnkOuter);
        ~CImpIDrawPage(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // IDrawPage methods.
        STDMETHODIMP         InkStart(
                               SHORT nX,
                               SHORT nY,
                               SHORT nWidth,
                               COLORREF crInkColor);
        STDMETHODIMP         InkDraw(SHORT nX, SHORT nY);
        STDMETHODIMP         InkStop(SHORT nX, SHORT nY);
        STDMETHODIMP         Clear(BOOL bSaveNeeded);
        STDMETHODIMP         Resize(SHORT nWidth, SHORT nHeight);
        STDMETHODIMP         Redraw(void);

      private:
        // Private utility methods of this interface implementation.
        HRESULT NextSlot(void);

        // Data private to this interface implementation of IDrawPage.
        CODrawPage*   m_pCO;          // Parent COM Object back pointer.
        IUnknown*     m_pUnkOuter;    // Outer unknown for Delegation.
    };

    // Make the otherwise private and nested interface implementations
    // friends to COM object instantiations of this CODrawPage
    // COM object class.
    friend CImpIConnectionPointContainer;
    friend CImpIPersistStorage;
    friend CImpIDrawPage;

    // Private Methods of CODrawPage COM objects.

    // Private method of main connectable CODrawPage COM object to
    // broadcast event notifications to all connected listening sinks.
    HRESULT NotifySinks(
              DRAWPAGE_EVENT DrawPageEvent,
              SHORT nX,
              SHORT nY,
              SHORT nInkWidth,
              COLORREF crInkColor);

    // Private data of CODrawPage COM objects.

    // Nested IConnectionPointContainer implementation instantiation.
    CImpIConnectionPointContainer m_ImpIConnectionPointContainer;

    // Nested IPersistStorage implementation instantiation.
    CImpIPersistStorage m_ImpIPersistStorage;

    // Nested IDrawPage implementation instantiation. Custom interface.
    CImpIDrawPage     m_ImpIDrawPage;

    // Main Object reference count.
    ULONG             m_cRefs;

    // Outer unknown (aggregation & delegation).
    IUnknown*         m_pUnkOuter;

    // Pointer to this component server's control object.
    CServer*          m_pServer;

    // The array of connection points for this connectable COM object.
    IConnectionPoint* m_aConnectionPoints[MAX_CONNECTION_POINTS];

    // The following private data is the working heart of DrawPage objects.
    RECT              m_WinRect;        // Current window rectangle.
    COLORREF          m_crWinColor;     // Current window background color.
    COLORREF          m_crInkColor;     // Current ink color.
    SHORT             m_nInkWidth;      // Current ink width.
    LONG              m_lInkDataEnd;    // Current end of the ink data.
    LONG              m_lInkDataMax;    // Current max end of the ink data.
    INKDATA*          m_paInkData;      // Dynamic Ink data array pointer.
    DRAWPROPS         m_DrawProps;      // Drawing Page properties.
    CLSID             m_ClassID;        // CLSID of this COM Object.
    UINT              m_ClipFmt;        // ClipBoard format.
    PERSTGSTATE       m_StgState;       // Persistent Storage State.
    BOOL              m_bDirty;         // RAM no match file--save needed.
};

#endif // __cplusplus


#endif // DRAWPAGE_H
