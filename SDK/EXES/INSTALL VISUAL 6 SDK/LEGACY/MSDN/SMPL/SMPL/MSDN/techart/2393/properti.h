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
// properti.h : header file
//

#ifndef _PROPERTI_H_
#define _PROPERTI_H_


// CProperties command target
class CDataObject ;
class CProperty ;

class CProperties : public CCmdTarget
{   
    DECLARE_SERIAL(CProperties)

public:    
    CProperties( CDataObject* pDataObject = NULL ) ;
    
// Attributes
public:
    CDataObject*    m_pDataObject ;
    CObList         m_lstProps ;
    DWORD           m_dwID ;
    
// Operations
public:
    CProperty* Add( const CString& rstr) ;
    CProperty* Add( const VARIANT FAR& properties );
    CProperty* Find( CProperty* pProp ) ;
    CProperty* Find( const CString& rstr ) ;

// Implementation
public:
    virtual ~CProperties();
    virtual void OnFinalRelease();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
    void SaveAsText(CArchive& ar, BOOL fIncludeNames = TRUE);

protected:
    // Generated message map functions
    //{{AFX_MSG(CProperties)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

public:
    // Generated OLE dispatch map functions
    //{{AFX_DISPATCH(CProperties)
    afx_msg short GetCount();
    afx_msg LPDISPATCH GetDataObject();
    afx_msg VARIANT _Add(const VARIANT FAR& properties);
    afx_msg LPDISPATCH Item(const VARIANT FAR& item);
    //}}AFX_DISPATCH
    afx_msg LPUNKNOWN _NewEnum() ;
    DECLARE_DISPATCH_MAP()
};


class CEnumProperties : public CCmdTarget
{   
public:
    CEnumProperties( CProperties* pObject = NULL) ;

// Attributes
private:
    CProperties* m_pProperties ;
    
// Operations
public:

// Implementation
public:
    virtual ~CEnumProperties();
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


/////////////////////////////////////////////////////////////////////////////
#endif // _PROPERTI_H_
