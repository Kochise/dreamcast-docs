/*+==========================================================================
  File:      PAPER.H

  Summary:   Include file for the connectable COPaper COM object class.

             COPaper offers a main standard IUnknown interface (basic COM
             object features), an implementation of the standard
             IConnectionPointContainer interface (connectable object
             features), and an implementation of the custom ISharePaper
             interface (shared drawing Paper-related features). This
             multiple interface COM Object Class is achieved via the
             technique of nested classes.  The implementation of the
             IConnectionPointContainer and ISharePaper interfaces are
             nested inside of the COPaper Class.

             APPUTIL's CThreaded OwnThis technology is used in COPaper to
             ensure mutually exclusive access by contending multiple
             client threads.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial DCDSERVE.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source code.

  Functions: .

  Classes:   COPaper.

  Origin:    8-23-97: atrent - Editor-inheritance from BALL.H in
             the CONSERVE Tutorial Code Sample. [Revised]

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

#if !defined(PAPER_H)
#define PAPER_H

#ifdef __cplusplus


// Current format version of Ink Data is 1.0. Thus, the format version
// is a compile-time constant.
#define INKDATA_VERSION10 MAKELONG(0,1)

// InkData allocation sizes for the Dynamic InkData array.
enum
{
  INKDATA_ALLOC_INIT = 3200,
  INKDATA_ALLOC = 800
};

// The Ink Data structure.
typedef struct _INKDATA
{
  SHORT nType;            // Ink Type.
  SHORT nX;               // X-coordinate of ink point.
  SHORT nY;               // Y-coordinate of ink point.
  SHORT nWidth;           // Ink line width.
  COLORREF crColor;       // Ink color.
} INKDATA;


// Properties of our electronic paper.
#define PAPER_TITLE_SIZE 64
typedef struct _PAPER_PROPERTIES
{
  LONG lInkDataVersion;
  LONG lInkArraySize;
  COLORREF crWinColor;
  RECT WinRect;
  WCHAR wszTitle[PAPER_TITLE_SIZE];
  WCHAR wszAuthor[PAPER_TITLE_SIZE];
  WCHAR wszReserved1[PAPER_TITLE_SIZE];
  WCHAR wszReserved2[PAPER_TITLE_SIZE];
} PAPER_PROPERTIES;


// Drawing Paper event constants.
enum PAPER_EVENT
{
  PAPER_EVENT_NONE = 0,
  PAPER_EVENT_LOCKED,
  PAPER_EVENT_UNLOCKED,
  PAPER_EVENT_LOADED,
  PAPER_EVENT_SAVED,
  PAPER_EVENT_INKSTART,
  PAPER_EVENT_INKDRAW,
  PAPER_EVENT_INKSTOP,
  PAPER_EVENT_ERASED,
  PAPER_EVENT_RESIZED
};

// Some strings used in file storage.
#define STREAM_PAPERDATA_USTR L"PAPERDATA"
#define CLIPBDFMT_STR "CTS.SharePaper.1"
#define PAP_FILE_EXT ".PAP"


/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: COPaper

  Summary:     COM object class for COPaper COM objects.  COM objects of
               this class offer custom ISharePaper interface features,
               InitPaper, Lock, InkStart, InkDraw, InkStop, GetInk, Erase,
               Resize. To make COPaper objects connectable, the standard
               IConnectionPointContainer interface features,
               FindConnectionPoint and EnumConnectionPoints are also
               implemented. The mulitple interfaces on this COM object are
               constructed via the nested interface classes technique.
               COPaper is also derived from APPUTIL's CThreaded to provide
               the OwnThis thread safety mechanism.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               IConnectionPointContainer
                 Standard Connection Point container features rendering
                 COPaper objects connectable objects.
               ISharePaper
                 Custom interface providing basic electronic drawing paper
                 features for a shared drawing.

  Aggregation: Yes, COPaper COM Objects are aggregatable by passing
               a non-NULL pUnkOuter IUnknown pointer into the constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class COPaper : public IUnknown, public CThreaded
{
  public:
    // Main Object Constructor & Destructor.
    COPaper(IUnknown* pUnkOuter, CServer* pServer);
    ~COPaper(void);

    // A general method for initializing this newly created object.
    // Creates any subordinate arrays, structures, or objects.
    HRESULT Init(void);

    // IUnknown methods. Main object, non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

  private:
    // We declare nested class interface implementations here.

    class CImpIConnectionPointContainer : public IConnectionPointContainer,
                                          public CThreaded
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIConnectionPointContainer(COPaper* pCO, IUnknown* pUnkOuter);
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
        COPaper*      m_pCO;          // Parent Object back pointer.
        IUnknown*     m_pUnkOuter;    // Outer unknown for Delegation.
    };

    class CImpISharePaper : public ISharePaper, public CThreaded
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpISharePaper(COPaper* pCO, IUnknown* pUnkOuter);
        ~CImpISharePaper(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // ISharePaper methods.
        STDMETHODIMP         InitPaper(RECT* pWinRect, BOOL* pbFirst);
        STDMETHODIMP         Lock(BOOL bLock);
        STDMETHODIMP         Load(RECT* pWinRect);
        STDMETHODIMP         Save(void);
        STDMETHODIMP         InkStart(
                               SHORT nX,
                               SHORT nY,
                               SHORT nWidth,
                               COLORREF crInkColor);
        STDMETHODIMP         InkDraw(SHORT nX, SHORT nY);
        STDMETHODIMP         InkStop(SHORT nX, SHORT nY);
        STDMETHODIMP         GetInk(
                               LONG lIndex,
                               SHORT* pnInkType,
                               SHORT* pnX,
                               SHORT* pnY,
                               SHORT* pnInkWidth,
                               COLORREF* pcrInkColor);
        STDMETHODIMP         Erase(void);
        STDMETHODIMP         Resize(
                               LONG lWidth,
                               LONG lHeight);

      private:
        // Data private to this interface implementation of ISharePaper.
        COPaper*      m_pCO;          // Parent Object back pointer.
        IUnknown*     m_pUnkOuter;    // Outer unknown for Delegation.

        // The following private data and methods constitute the working
        // heart of COPaper as an actual application object.
        PAPER_PROPERTIES m_PaperProperties; // For file storage.
        UINT          m_ClipBdFmt;    // ClipBoard Format.
        BOOL          m_bLocked;      // Paper lock state.
        RECT          m_WinRect;      // Current Window rectangle.
        COLORREF      m_crWinColor;   // Current window background color.
        COLORREF      m_crInkColor;   // Current ink color.
        SHORT         m_nInkWidth;    // Current ink width.
        LONG          m_lInkDataEnd;  // Current end of the ink data.
        LONG          m_lInkDataMax;  // Current end of the ink data array.
        INKDATA*      m_paInkData;    // Dynamic Ink data array pointer.

        // Private utility methods of this interface implementation.
        HRESULT NextSlot(void);
    };

    // Make the otherwise private and nested ISharePaper and
    // IConnectionPointContainer interface implementations a friend to
    // COM object instantiations of this COPaper COM object class.
    friend CImpIConnectionPointContainer;
    friend CImpISharePaper;

    // Private method of main connectable COPaper COM object to broadcast
    // event notifications to all connected listening sinks.
    HRESULT NotifySinks(
              PAPER_EVENT PaperEvent,
              SHORT nX,
              SHORT nY,
              SHORT nInkWidth,
              COLORREF crInkColor);

    // Private data of COPaper COM objects.

    // Nested ISharePaper implementation instantiation. This interface
    // is instantiated inside this COPaper object as a native interface.
    CImpISharePaper   m_ImpISharePaper;

    // Nested IConnectionPointContainer implementation instantiation.
    CImpIConnectionPointContainer m_ImpIConnectionPointContainer;

    // Main Object reference count.
    ULONG             m_cRefs;

    // Outer unknown (aggregation & delegation).
    IUnknown*         m_pUnkOuter;

    // Pointer to this component server's control object.
    CServer*          m_pServer;

    // The file path name for the paper file containing the shared drawing.
    TCHAR             m_szPapFile[MAX_PATH];

    // The array of connection points for this connectable COM object.
    IConnectionPoint* m_aConnectionPoints[MAX_CONNECTION_POINTS];
};

#endif // __cplusplus


#endif // PAPER_H
