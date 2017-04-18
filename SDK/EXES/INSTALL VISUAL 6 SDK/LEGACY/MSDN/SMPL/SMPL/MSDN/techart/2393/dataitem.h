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
// dataitem.h : header file for the CDataItem class
//

#ifndef _DATAITEM_H_
#define _DATAITEM_H_
/////////////////////////////////////////////////////////////////////////////
// CDataItem command target
class CProperties ;
class CDataObject ;
class CDataItemServerItem ;
class CRequest ;

// CDataItem
//
class CDataItem : public CCmdTarget
{   
    DECLARE_SERIAL(CDataItem)
public:
    CDataItem( CDataObject* pDataObject = NULL, CProperties* pProps = NULL );            // protected constructor used by dynamic creation

// Attributes
public:
    CDataObject*    m_pDataObject ;         // Pointer to the DataObject that is
                                            // responsible for us
           
    CProperties*    m_pRequestProps ;       // Pointer to request properties object
                                            // responsible for this dataitem.  One or
                                            // more CRequest objects will also
                                            // point to this same CProperties object.
                                                                                        
    CProperties*    m_pValueProps ;         // Properties object contianing the
                                            // 'values' for this item
                                            // When a VBA user says 
                                            // "DataItem.Properites" he get's
                                            // a pointer to this object.

    DWORD           m_dwID ;

	// BUGFIX:  9/19/94 cek  
	DWORD           m_dwRequestID ;         // Each data item needs to know which request was responsible for                                 
											// it.                                                            
    
    // the following support linking to DataItems
    CDataItemServerItem* m_pServerItem;     // pointer to active item (may be NULL)
    
// Operations
public:
    void CalcDisplaySize( CDC* pDC, CSize& sizeItem ) ;  // get bounding rect
    int Draw( CDC* pDC, CPoint ptStart, int n = -1 ) ;
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
    void SaveAsText(CArchive& ar, BOOL fIncludeNames = TRUE);
    void NotifyLinks();

// Implementation
public:
    virtual ~CDataItem();
    virtual void OnFinalRelease();

protected:
    // Generated message map functions
    //{{AFX_MSG(CDataItem)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

public:
    // Generated OLE dispatch map functions
    //{{AFX_DISPATCH(CDataItem)
    afx_msg VARIANT GetProperties(const VARIANT FAR& item );
    afx_msg void Copy();
    //}}AFX_DISPATCH
    DECLARE_DISPATCH_MAP()

    friend class CDataItemServerItem;   
};

// We support linking to DataItem objects.  The CDataItemServerItem class 
// provides linking support
//
class CDataItemServerItem : public COleServerItem
{
// Constructors
    DECLARE_DYNAMIC(CDataItemServerItem)
public:
    CDataItemServerItem(CDataObject* pContainerDoc = NULL, CDataItem* pReqeust = NULL);

// Attributes
    CDataItem*   m_pDataItem ;
    CDataObject* GetDocument() const
        { return (CDataObject*)COleServerItem::GetDocument(); }
        
// Operations
public:        
                          
// Implementation
public:
    ~CDataItemServerItem();

#if (_MFC_VER <= 0x250)
    BEGIN_INTERFACE_PART(BugFixDataObject, IDataObject)
        STDMETHOD(GetData)(LPFORMATETC, LPSTGMEDIUM);
        STDMETHOD(GetDataHere)(LPFORMATETC, LPSTGMEDIUM);
        STDMETHOD(QueryGetData)(LPFORMATETC);
        STDMETHOD(GetCanonicalFormatEtc)(LPFORMATETC, LPFORMATETC);
        STDMETHOD(SetData)(LPFORMATETC, LPSTGMEDIUM, BOOL);
        STDMETHOD(EnumFormatEtc)(DWORD, LPENUMFORMATETC FAR*);
        STDMETHOD(DAdvise)(LPFORMATETC, DWORD, LPADVISESINK, LPDWORD);
        STDMETHOD(DUnadvise)(DWORD);
        STDMETHOD(EnumDAdvise)(LPENUMSTATDATA FAR*);
    END_INTERFACE_PART(BugFixDataObject)

    DECLARE_INTERFACE_MAP()
#endif // BUGFIX DADVISE

#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
    virtual void OnOpen() ;
    virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
    virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
    virtual BOOL OnRenderFileData( LPFORMATETC lpFormatEtc, CFile* pFile);
    virtual COleDataSource* OnGetClipboardData(BOOL bIncludeLink,
        LPPOINT lpOffset, LPSIZE lpSize);

protected:
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
};


/////////////////////////////////////////////////////////////////////////////
#endif //_DATAITEM_H_

