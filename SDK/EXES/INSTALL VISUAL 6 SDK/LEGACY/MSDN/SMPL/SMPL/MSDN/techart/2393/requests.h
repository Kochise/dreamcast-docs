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
// requests.h : header file
//

#ifndef _REQUESTS_H_
#define _REQUESTS_H_

/////////////////////////////////////////////////////////////////////////////
// CRequests command target
class CDataObject ;
class CRequests : public CCmdTarget
{   
    DECLARE_DYNCREATE(CRequests)
public:
    CRequests( CDataObject * pDataObject = NULL) ;
    
// Attributes
public:
    CDataObject*   m_pDataObject ;

// Operations
public:

// Implementation
public:
    virtual ~CRequests();
    virtual void OnFinalRelease();

    // Generated message map functions
    //{{AFX_MSG(CRequests)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

public:

    // Generated OLE dispatch map functions
    //{{AFX_DISPATCH(CRequests)
    afx_msg short GetCount();
    afx_msg LPDISPATCH GetDataObject();
    afx_msg LPDISPATCH Add(const VARIANT FAR& name, const VARIANT FAR& properties);
    afx_msg LPDISPATCH GetItem(const VARIANT FAR& item);
    afx_msg void Remove(const VARIANT FAR& item);
    afx_msg LPDISPATCH CreateProperties(const VARIANT FAR& p1, const VARIANT FAR& p2, const VARIANT FAR& p3, const VARIANT FAR& p4, const VARIANT FAR& p5, const VARIANT FAR& p6, const VARIANT FAR& p7, const VARIANT FAR& p8);
    //}}AFX_DISPATCH
    afx_msg LPUNKNOWN _NewEnum() ;
    DECLARE_DISPATCH_MAP()
};


// Declaraction of the class that implements IEnumVARIANT
//
class CEnumRequests : public CCmdTarget
{   
public:
    CEnumRequests();         // protected constructor used by dynamic creation
    CEnumRequests( CDataObject* pObject ) ;

// Attributes
private:
    CDataObject *m_pDataObject ;
    
// Operations
public:

// Implementation
public:
    virtual ~CEnumRequests();
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
#endif //_REQUESTS_H_

