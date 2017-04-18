// WOSA/XRT XRTFrame Sample Application Version 1.01
//
// Copyright (c) 1993-94 Microsoft Corporation, All Rights Reserved.
//
//      This is a part of the Microsoft Source Code Samples. 
//      This source code is only intended as a supplement to 
//      Microsoft Development Tools and/or WinHelp documentation.
//      See these sources for detailed information regarding the 
//      Microsoft samples programs.
//
// doc.h : interface of the CDocument derived class
//
// CDataObject definition
//
// Revisions:
//  December 8, 1993   cek     First implementation.
//
#ifndef _DOC_H_
#define _DOC_H_

#include "collist.h"
#include "simobj.h"
#include "wosaxrt.h"

// forward references
class CDataObject ;
class CRequestsServerItem;
class CDataObjectSvrItem;
class CRequest ;
class CProperties ;
class CSimulation ;   

/////////////////////////////////////////////////////////////////////////////
// CTimerWnd window
// Provides WM_TIMER support to CDataObject (since CDataObject is not
// derived from CWnd it can't directly recieve WM_TIMER messages).
//
class CTimerWnd : public CWnd
{
// Construction
public:
    CTimerWnd( );

// Attributes
public:
    CDataObject*    m_pDataObject ;
    
// Operations
public:
    void SetFrequency( UINT uiFreq = 0 ) ;
    BOOL IsRunning() ;

// Implementation
public:
    virtual ~CTimerWnd();

protected:
    UINT            m_uiIDTimerEvent ;

    // Generated message map functions
protected:
    //{{AFX_MSG(CTimerWnd)
    afx_msg void OnDestroy();
    afx_msg void OnTimer(UINT nIDEvent);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

// CDataObject impelemnts the WOSA/XRT "Data Object" for XRTFrame.
// COleServerDoc provides OLE 2.0 linking and embedding support
// that minimizes the amount of OLE 2.0 code we need to write.  We
// also get OLE Automation support 'for free'.
//
// CDataObject is obviously the center piece of XRTFrame.
// 
class CDataObject : public COleServerDoc
{
protected: // create from serialization only
    CDataObject();
    DECLARE_DYNCREATE(CDataObject)

public:
    CDataObjectSvrItem* GetEmbeddedItem()
        { return (CDataObjectSvrItem*)COleServerDoc::GetEmbeddedItem(); }

public:
// Attributes
    // The 'contents' of the document
    // These members are serialized in the order given
    LOGFONT         m_logfont ;         // Font used in visual display
    
    CObList         m_lstRequests ;     // list of Request objects (CRequest*)
    CObList         m_lstPropSets ;     // list of Properties (property sets)
                                        // objects (CProperties*)
    CObList         m_lstDataItems ;    // list of DataItem objects (CDataItem*)
    
    // View (as in Document/View) state information
    // Request listbox state information
    // (saved to persistant store)
    int             m_nRequestsCols ;       // number of columns
    COLINFO*        m_rgRequestsColInfo ;   // column widths    
    CString         m_strRequestsTitle ;    // column titles

    // DataItem listbox state information
    // (saved to persistant store)
    int             m_nDataCols ;       // number of columns
    COLINFO*        m_rgDataColInfo ;   // column widths    
    CString         m_strDataViewTitle ;    // column titles

    // private clipboard format ("WOSA/XRT (Market Data)")
    static CLIPFORMAT m_cfPrivate;
                                  
    CSimulation *   m_pSimulation ;                                      
    UINT            m_uiSimID    ; 

    BOOL            m_fMostRecentOnly ;
    char            m_cColumnDelimiter ;
                           
    CString         m_strName ;
    CString         m_strUsername ;
    CString         m_strPassword ;
                              
    // these members support the UpdateFrequency timer
    UINT            m_nIDTimerEvent ;
    UINT            m_uiUpdateFrequency ;
    CTimerWnd       m_wndTimer ;
    
    // We create a COleServerItem derived object whenever
    // a link or embedding is needed.  It does the hard OLE 2.0
    // work.
    //
    CDataObjectSvrItem*  m_pServerItem ;

    DWORD           m_dwRequestID ;
    DWORD           m_dwPropertySetID ;
    DWORD           m_dwDataItemID ;

    // wosaxrt.h defines some helpful structures and helper
    // functions that faciliate dealing with the WOSA/XRT 
    // clipboard format.  
    //
    // m_pXRTData points to the current WOSA/XRT data buffer
    //
    #ifdef _DEBUG
    DWORD           m_cItems ;
    #endif
    LPMARKETDATA    m_pXRTData ;

// Operations
    COLINFO*    GetRequestsColInfo( int *pnCols, CString& rstrTitle ) ;
    void        SetRequestsColInfo( int nCols, const COLINFO* pColInfo, const CString &rstrTitle, BOOL fDirty = TRUE ) ;

    COLINFO*    GetDataColInfo( int *pnCols, CString& rstrTitle ) ;
    void        SetDataColInfo( int nCols, const COLINFO* pColInfo, const CString &rstrTitle, BOOL fDirty = TRUE ) ;

    CFont*      SelectDocFont(CDC* pDC, CFont& font) ;
    int         GetWidth( CDC* pDC, BOOL fLinked = FALSE ) ;
    void        CalcDisplaySize( CDC* pDC, CSize& sizeItem, BOOL fLinked = FALSE) ;        
    int         Draw( CDC* pDC, CPoint ptStart, BOOL fLinked = FALSE ) ;
     
    // Request Management
    //
    int GetRequestCount( void ) ;
    CRequest* GetRequest( int index ) ;
    CRequest* GetRequest( const CString& rstrRequest ) ;
    BOOL AddRequest(  CRequest* pItem ) ;
    BOOL ChangeRequest( CRequest* pItem, const CString& rstrRequest );
    CRequest* RemoveRequest( const CString& str ) ;
    CRequest* RemoveRequest( CRequest* pItem ) ;
    CRequest* RemoveRequest( int index ) ;
    DWORD GenerateRequestID() ;

    // Property set managment
    //
    BOOL AddPropertySet( CProperties* pProps ) ;
    CProperties* GetNamePropertySet() ;
    CProperties* FindPropertySet( CProperties* pProps ) ;
    CProperties* FindPropertySet( int index ) ;
    int GetPropertySetIndex( CProperties* pProperties ) ;
    DWORD GeneratePropertySetID() ;

    // Data Items 
    void OnStockChange( PSIMSTOCK pStock ) ;
    // BUGFIX:  10/2/94 cek
    // Added lHint parameter to UpdateDataItems.  Pass UPDATE_ALL
    // to force the entire data item to be sent to the client
    // (instead of just the changed properties).  Pass UPDATE_ADDREQUEST
    // whenever a request is being added.
    //
    void UpdateDataItems( CRequest* pRequest, PSIMSTOCK pStock, LPARAM lHint ) ;
    void ForceOnDataChange( LPARAM lHint ) ;
    void ClearDataItems() ;
    BOOL RenderToGlobal( HGLOBAL * phGlobal ) ;
    BOOL RenderToStream( CArchive& ar ) ;
    DWORD GenerateDataItemID() ;

    
// Implementation
public:
    virtual ~CDataObject();

    void SerializeMiscInfo(CArchive& ar) ;
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
    
    virtual COleServerItem* OnGetEmbeddedItem();
    virtual COleServerItem* OnGetLinkedItem(LPCSTR lpszItemName);

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
    CDumpContext* m_pdbgDump ;
#endif

protected:
    virtual BOOL OnNewDocument();
    virtual BOOL OnOpenDocument( const char* szFile) ;
    virtual void OnFinalRelease();

// Generated message map functions
protected:
    //{{AFX_MSG(CDataObject)
    afx_msg void OnOptionsActive();
    afx_msg void OnUpdateOptionsActive(CCmdUI* pCmdUI);
    afx_msg void OnEditCopyAll();
    afx_msg void OnUpdateEditCopyAll(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

public:
    // Generated OLE dispatch map functions
    //{{AFX_DISPATCH(CDataObject)
    CString m_ColumnDelimiter;
    BOOL m_fIncludeNamesOnClipboard;
    afx_msg LPDISPATCH GetApplication();
    afx_msg BOOL GetVisible();
    afx_msg void SetVisible(BOOL bNewValue);
    afx_msg BSTR GetTitle();
    afx_msg void SetTitle(LPCSTR lpszNewValue);
    afx_msg BSTR GetFullName();
    afx_msg BSTR GetName();
    afx_msg BSTR GetPath();
    afx_msg BOOL GetSaved();
    afx_msg BOOL GetActive();
    afx_msg void SetActive(BOOL bNewValue);
    afx_msg long GetUpdateFrequency();
    afx_msg void SetUpdateFrequency(long nNewValue);
    afx_msg BOOL GetMostRecentOnly();
    afx_msg void SetMostRecentOnly(BOOL bNewValue);
    afx_msg BSTR GetUsername();
    afx_msg void SetUsername(LPCSTR lpszNewValue);
    afx_msg BSTR GetPassword();
    afx_msg void SetPassword(LPCSTR lpszNewValue);
    afx_msg long GetStatus();
    afx_msg void Activate();
    afx_msg VARIANT Close(const VARIANT FAR& saveChanges, const VARIANT FAR& fileName);
    afx_msg VARIANT Save();
    afx_msg VARIANT SaveAs(const VARIANT FAR& fileName);
    afx_msg void Copy();
    //}}AFX_DISPATCH
    // BUGFIX: 9/29/94 cek 
    // Changed .Requests and .DataItems from DISP_FUNCTION to 
    // DISP_PROPERTY_PARAM (and changed return type to VARIANT)
    // so that xrt.Requests("Foo") works.
    //
    afx_msg VARIANT Requests(const VARIANT FAR& item);
    afx_msg VARIANT DataItems(const VARIANT FAR& item);
    DECLARE_DISPATCH_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CDataObjects command target
//
// This class implements the "Documents collection object"
//
class CDataObjects : public CCmdTarget
{   
    DECLARE_DYNCREATE(CDataObjects)
public:
    CDataObjects();           

// Attributes
public:

// Operations
public:

// Implementation
public:
    virtual ~CDataObjects();
    virtual void OnFinalRelease();

protected:
    // Generated message map functions
    //{{AFX_MSG(CDataObjects)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

public:
    // Generated OLE dispatch map functions
    //{{AFX_DISPATCH(CDataObjects)
    afx_msg short GetCount();
    afx_msg VARIANT Add(const VARIANT FAR& name);
    afx_msg LPDISPATCH GetItem(const VARIANT FAR& ItemNameOrIndex);
    afx_msg VARIANT Open(const VARIANT FAR& fileName);
    //}}AFX_DISPATCH
    afx_msg LPUNKNOWN _NewEnum();

    DECLARE_DISPATCH_MAP()
};

// Declaraction of the class that implements IEnumVARIANT
//
class CEnumDocs : public CCmdTarget
{   
public:
    CEnumDocs();         // protected constructor used by dynamic creation

// Attributes
private:
    
// Operations
public:

// Implementation
public:
    virtual ~CEnumDocs();
    virtual void OnFinalRelease();

protected:
    DECLARE_INTERFACE_MAP()

public:    
    // The following block get's expanded by the C++ preprocessor to this:
    //
    //  class FAR XEnumVARIANT : public IEnumVARIANT
    //  {
    //  public:
    //      STDMETHOD_(ULONG, AddRef)(); 
    //      STDMETHOD_(ULONG, Release)();
    //      STDMETHOD(QueryInterface)(REFIID iid, LPVOID far* ppvObj); 
    //      XEnumVARIANT() ;      
    //      POSITION   m_posCurrent ; 
    //      ...
    //
    //  } m_xEnumVARIANT ;
    //  friend class XEnumVARIANT ;
    //      
    BEGIN_INTERFACE_PART(EnumVARIANT, IEnumVARIANT)
        XEnumVARIANT() ;        // constructor to set m_posCurrent
        POSITION   m_posCurrent ; // Next() requires that we keep track of our current item

        STDMETHOD(Next)(THIS_ unsigned long celt, VARIANT FAR* rgvar, unsigned long FAR* pceltFetched);
        STDMETHOD(Skip)(THIS_ unsigned long celt) ;
        STDMETHOD(Reset)(THIS) ;
        STDMETHOD(Clone)(THIS_ IEnumVARIANT FAR* FAR* ppenum) ;
    END_INTERFACE_PART(EnumVARIANT)    

} ;

#ifdef _DEBUG
CDumpContext* WINAPI xrtStartDebugDump( CString s ) ;
void WINAPI xrtStopDebugDump( CDumpContext* par ) ;
void WINAPI xrtDebugDump( CDumpContext& ar, LPMARKETDATA pMD );
void WINAPI xrtDebugDumpPropSets( CDumpContext& ar, LPMARKETDATA pMD ) ;
#endif 

/////////////////////////////////////////////////////////////////////////////
#endif // _DOC_H_
