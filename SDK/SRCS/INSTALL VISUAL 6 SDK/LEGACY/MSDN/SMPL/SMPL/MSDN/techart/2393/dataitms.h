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
// dataitms.h : header file
//

#ifndef _DATAITEMS_H_
#define _DATAITEMS_H_

/////////////////////////////////////////////////////////////////////////////
// CDataItems command target
class CDataObject ;
class CDataItems : public CCmdTarget
{   
    DECLARE_DYNCREATE(CDataItems)
public:
    CDataItems(CDataObject * pDataObject = NULL) ;

// Attributes
public:
    CDataObject*   m_pDataObject ;

// Operations
public:

// Implementation
public:
    virtual ~CDataItems();
    virtual void OnFinalRelease();


    // Generated message map functions
    //{{AFX_MSG(CDataItems)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
public:  

    // Generated OLE dispatch map functions
    //{{AFX_DISPATCH(CDataItems)
    afx_msg short GetCount();
    afx_msg LPDISPATCH GetDataObject();
    afx_msg LPDISPATCH GetItem(const VARIANT FAR& item);
    //}}AFX_DISPATCH
    afx_msg LPUNKNOWN _NewEnum() ;
    DECLARE_DISPATCH_MAP()
};

// Declaraction of the class that implements IEnumVARIANT
//
class CEnumDataItems : public CCmdTarget
{   
public:
    CEnumDataItems();         // protected constructor used by dynamic creation
    CEnumDataItems( CDataObject* pObject ) ;

// Attributes
private:
    CDataObject *m_pDataObject ;
    
// Operations
public:

// Implementation
public:
    virtual ~CEnumDataItems();
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
#endif //_DATAITEMS_H_
