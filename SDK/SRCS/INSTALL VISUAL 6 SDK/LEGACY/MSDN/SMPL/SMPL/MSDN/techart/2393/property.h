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
// property.h : header file
//

#ifndef _PROPERTY_H_
#define _PROPERTY_H_

/////////////////////////////////////////////////////////////////////////////
// CProperty command target
class CDataObject ;
class CPropertyServerItem ;

class CProperty : public CCmdTarget
{   
    DECLARE_SERIAL(CProperty)
public:    
    CProperty( CDataObject* pDataObject  = NULL);           

// Attributes
public:
    CString     m_strName ;
    VARIANT     m_varValue ;
    DWORD       m_dwID ;
    CDataObject*            m_pDataObject ;
    CPropertyServerItem*    m_pServerItem ;
    
// Operations
public:
    void CalcDisplaySize( CDC* pDC, CSize& sizeItem ) ;  // get bounding rect
    int Draw( CDC* pDC, CPoint ptStart, int n = -1 ) ;
    void NotifyLinks();

// Implementation
public:
    virtual ~CProperty();
    virtual void OnFinalRelease();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
    void SaveAsText(CArchive& ar);

protected:
    // Generated message map functions
    //{{AFX_MSG(CProperty)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    // Generated OLE dispatch map functions
    //{{AFX_DISPATCH(CProperty)
    afx_msg BSTR GetName();
    afx_msg void SetName(LPCSTR lpszNewValue);
    afx_msg VARIANT GetValue();
    afx_msg void SetValue(const VARIANT FAR& newValue);
    //}}AFX_DISPATCH
    DECLARE_DISPATCH_MAP()
    friend class CPropertyServerItem;   // CXRTFrameServerItem is an extension of a CReqeust
};

class CPropertyServerItem : public COleServerItem
{
    DECLARE_DYNAMIC(CPropertyServerItem)
// Constructors
public:
    CPropertyServerItem(CDataObject* pContainerDoc, CProperty* pReqeust);

// Attributes
    CProperty*   m_pProperty ;
    CDataObject* GetDocument() const
        { return (CDataObject*)COleServerItem::GetDocument(); }

// Implementation
public:
    ~CPropertyServerItem();

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
#endif // _PROPERTY_H_
