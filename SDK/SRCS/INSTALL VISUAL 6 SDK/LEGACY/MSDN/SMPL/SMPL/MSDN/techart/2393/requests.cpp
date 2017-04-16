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
// requests.cpp : implementation file
//
// This class (CRequests) implements the WOSA/XRT Requests collection object.
//
// It works by iterating over the m_listRequest member of CDataObject.  
//
#include "stdafx.h"
#include "xrtframe.h"
#include "requests.h"
#include "request.h"
#include "property.h"
#include "properti.h"

#include "doc.h"
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRequests

IMPLEMENT_DYNCREATE(CRequests, CCmdTarget)
#define new DEBUG_NEW 

CRequests::CRequests( CDataObject * pDataObject)
{
    m_pDataObject = pDataObject ;
    EnableAutomation();
}

CRequests::~CRequests()
{
}

void CRequests::OnFinalRelease()
{
    // When the last reference for an automation object is released
    //  OnFinalRelease is called.  This implementation deletes the 
    //  object.  Add additional cleanup required for your object before
    //  deleting it from memory.

    delete this;
}

BEGIN_MESSAGE_MAP(CRequests, CCmdTarget)
    //{{AFX_MSG_MAP(CRequests)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CRequests, CCmdTarget)
    //{{AFX_DISPATCH_MAP(CRequests)
    DISP_PROPERTY_EX(CRequests, "Count", GetCount, SetNotSupported, VT_I2)
    DISP_PROPERTY_EX(CRequests, "DataObject", GetDataObject, SetNotSupported, VT_DISPATCH)
    DISP_FUNCTION(CRequests, "Add", Add, VT_DISPATCH, VTS_VARIANT VTS_VARIANT)
    DISP_FUNCTION(CRequests, "Remove", Remove, VT_EMPTY, VTS_VARIANT)
    DISP_FUNCTION(CRequests, "CreateProperties", CreateProperties, VT_DISPATCH, VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT)
    //}}AFX_DISPATCH_MAP
    DISP_FUNCTION(CRequests, "Item", GetItem, VT_DISPATCH, VTS_VARIANT)
    DISP_DEFVALUE(CRequests, "Item")
    DISP_PROPERTY_EX_ID(CRequests, "_NewEnum", DISPID_NEWENUM, _NewEnum, SetNotSupported, VT_UNKNOWN)
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRequests message handlers
short CRequests::GetCount()
{
    if (m_pDataObject) 
        return (short)m_pDataObject->GetRequestCount() ;
    else
        return 0 ;
}

LPDISPATCH CRequests::Add(const VARIANT FAR& name, const VARIANT FAR& properties)
{
    CRequest* pItem ;

    pItem = new CRequest( m_pDataObject ) ;
    
    if (pItem != NULL)
    {
        VARIANT vTemp ;
        VariantInit( &vTemp ) ;
        if (SUCCEEDED(VariantChangeType( &vTemp, (LPVARIANT)&name, 0, VT_BSTR )))
        {
            pItem->m_strRequest = vTemp.bstrVal ;
            VariantClear( &vTemp ) ;
        }
        else
            pItem->m_strRequest = "" ;
        
        CProperties* pProps = NULL ;

        // VBA passes objects as VT_VARAINT | VT_BYREF
        //
        if (properties.vt == (VT_VARIANT | VT_BYREF) && properties.pvarVal->vt == VT_DISPATCH)   // it's an object
            pProps = (CProperties*)CCmdTarget::FromIDispatch(properties.pvarVal->pdispVal) ;            
        else if (properties.vt == VT_DISPATCH)
            pProps = (CProperties*)CCmdTarget::FromIDispatch(properties.pdispVal) ;            

        if (pProps != NULL)
        {
            if (pProps->IsKindOf(RUNTIME_CLASS(CProperties)))
                pProps->ExternalAddRef() ;  // We're keeping a pointer
            else
            {
                TRACE("FromIDispatch failed to return a CProperties object\r\n") ;
                pProps = NULL ;
            }
            ASSERT(pProps->IsKindOf(RUNTIME_CLASS(CProperties)));
        }
        else if (properties.vt != VT_EMPTY && properties.vt != VT_ERROR)
        {
            pProps = new CProperties( m_pDataObject ) ;
            pProps->Add( "Name" );
            pProps->Add( properties ) ;
            
            if (pProps->GetCount() == 1)
            {
                // the 2nd add didn't work, so leave him with the
                // shared "Name" one
                delete pProps ;
                pProps = NULL ;
            }
        }

        if (pProps != NULL)
        {   
            if (pItem->m_pProperties) pItem->m_pProperties->ExternalRelease() ;
            pItem->m_pProperties = pProps ;
            m_pDataObject->AddPropertySet( pProps ) ;
        }
                
        m_pDataObject->AddRequest( pItem ) ;

        return pItem->GetIDispatch(TRUE) ;
    }    
    
    return NULL ;
}

LPDISPATCH CRequests::GetItem(const VARIANT FAR& item)
{
    CRequest* pItem = NULL ;  
    LPDISPATCH lpDisp = NULL ;
    
    if (item.vt == VT_BSTR)
    {
        pItem = m_pDataObject->GetRequest( CString(item.bstrVal) ) ;
    }
    else
    {
        // coerce to VT_I4
        VARIANT va ;
        VariantInit( &va );
        if (SUCCEEDED(VariantChangeType( &va, (VARIANT FAR*)&item, 0, VT_I4 )))
        {
            pItem = m_pDataObject->GetRequest( (int)va.lVal ) ;
        }
    }                 
    
    if (pItem != NULL)
        lpDisp = pItem->GetIDispatch(TRUE) ;        // AddRef
    

    // BUGBUG:  Implement dispatch exception if lpDisp == NULL
    return lpDisp ;

}

void CRequests::Remove(const VARIANT FAR& item)
{
    CRequest* pItem = NULL ;

    // Find by VT_DISPATCH, VT_I4, or VT_BSTR...
    //
    if (item.vt == VT_DISPATCH || item.vt == VT_UNKNOWN)
    {
        CRequest* pNewItem ;
        pNewItem = (CRequest*)CCmdTarget::FromIDispatch( item.pdispVal ) ;
        if (pNewItem != NULL && pNewItem->IsKindOf(RUNTIME_CLASS(CRequest)))
        {
            pItem = m_pDataObject->RemoveRequest( pNewItem ) ;
        }
    }
    else if (item.vt == VT_BSTR)
    {
        pItem = m_pDataObject->RemoveRequest( CString( item.bstrVal ) ) ;
    }
    else
    {
        // coerce to VT_I4
        VARIANT va ;
        VariantInit( &va );
        if (SUCCEEDED(VariantChangeType( &va, (VARIANT FAR*)&item, 0, VT_I4 )))
        {
            pItem = m_pDataObject->RemoveRequest( (int)va.lVal ) ;
        }
    }
    
    if (pItem)
        pItem->ExternalRelease() ;

}

LPDISPATCH CRequests::CreateProperties(const VARIANT FAR& p1, const VARIANT FAR& p2, const VARIANT FAR& p3, const VARIANT FAR& p4, const VARIANT FAR& p5, const VARIANT FAR& p6, const VARIANT FAR& p7, const VARIANT FAR& p8)
{   
    VARIANT va ;
    VariantInit( &va ) ;
    
    CProperties* pProps = new CProperties(m_pDataObject) ;
    pProps->Add("Name") ;

    // This is a temporary way of doing it...just to get it working...
    if (p1.vt != VT_EMPTY) pProps->Add( p1 ) ;
    if (p2.vt != VT_EMPTY) pProps->Add( p2 ) ;
    if (p3.vt != VT_EMPTY) pProps->Add( p3 ) ;
    if (p4.vt != VT_EMPTY) pProps->Add( p4 ) ;
    if (p5.vt != VT_EMPTY) pProps->Add( p5 ) ;
    if (p6.vt != VT_EMPTY) pProps->Add( p6 ) ;
    if (p7.vt != VT_EMPTY) pProps->Add( p7 ) ;
    if (p8.vt != VT_EMPTY) pProps->Add( p8 ) ;
    
    m_pDataObject->AddPropertySet( pProps ) ;

    va.vt = VT_DISPATCH ;
    va.pdispVal = pProps->GetIDispatch(FALSE) ;

    return va.pdispVal ;
}

LPDISPATCH CRequests::GetDataObject()
{
    ASSERT(m_pDataObject);
    return m_pDataObject->GetIDispatch(TRUE) ;
}
  
  
LPUNKNOWN CRequests::_NewEnum()
{
    CEnumRequests* pIEV = NULL ;

    pIEV = new CEnumRequests( m_pDataObject ) ;
    
    if (pIEV)
    {
        pIEV->m_xEnumVARIANT.Reset() ;
        return &pIEV->m_xEnumVARIANT ;
    }
    
    return NULL ;
}

//----------------------------------------------------------------------------
// Implementation of CEnumRequests which implements the IEnumVARIANT interface
// used by _NewEnum
//
BEGIN_INTERFACE_MAP(CEnumRequests, CCmdTarget)
    INTERFACE_PART(CEnumRequests, IID_IEnumVARIANT, EnumVARIANT)
END_INTERFACE_MAP()

CEnumRequests::CEnumRequests()
{
    m_pDataObject = NULL ;
    
    AfxOleLockApp();
}

CEnumRequests::CEnumRequests( CDataObject *pDataObject )
{
    m_pDataObject = pDataObject ;
    
    AfxOleLockApp();
}

CEnumRequests::~CEnumRequests()
{
    AfxOleUnlockApp();
}

void CEnumRequests::OnFinalRelease()
{
    // When the last reference for an automation object is released
    //  OnFinalRelease is called.  This implementation deletes the 
    //  object.  Add additional cleanup required for your object before
    //  deleting it from memory.
    //TRACE("CEnumRequests::OnFinalRelease\r\n" ) ;
    delete this;
}

//----------------------------------------------------------------------------
// Implementation of the nested class XEnumVARIANT (declared through the
// BEGIN/END_INTERFACE_PART macros in the declaration of CEnumRequests)
//
// This class implements the IEnumVARIANT interface requried by the 
// _NewEnum property of the collection
//
CEnumRequests::XEnumVARIANT::XEnumVARIANT()
{
    m_posCurrent = NULL ;
}

STDMETHODIMP_(ULONG) CEnumRequests::XEnumVARIANT::AddRef()
{   
    METHOD_PROLOGUE(CEnumRequests, EnumVARIANT)
    return pThis->ExternalAddRef() ;
}   

STDMETHODIMP_(ULONG) CEnumRequests::XEnumVARIANT::Release()
{   
    METHOD_PROLOGUE(CEnumRequests, EnumVARIANT)
    return pThis->ExternalRelease() ;
}   

STDMETHODIMP CEnumRequests::XEnumVARIANT::QueryInterface( REFIID iid, void FAR* FAR* ppvObj )
{   
    METHOD_PROLOGUE(CEnumRequests, EnumVARIANT)
    return (HRESULT)pThis->ExternalQueryInterface( (void FAR*)&iid, ppvObj) ;
}   

// IEnumVARIANT::Next
// 
STDMETHODIMP CEnumRequests::XEnumVARIANT::Next( ULONG celt, VARIANT FAR* rgvar, ULONG FAR* pceltFetched)
{
    // This sets up the "pThis" pointer so that it points to our
    // containing CRequests instance
    //
    METHOD_PROLOGUE(CEnumRequests, EnumVARIANT)

    ASSERT( pThis->m_pDataObject ) ;
    if (pThis->m_pDataObject == NULL) return ResultFromScode( E_UNEXPECTED ) ;

    HRESULT hr;
    ULONG   l ;
    CRequest*  pItem = NULL ;

    // pceltFetched can legally == 0
    //                                           
    if (pceltFetched != NULL)
        *pceltFetched = 0;
    else if (celt > 1)
    {   
        TRACE("XEnumVARIANT::Next() celt > 1 and pceltFetched == NULL!\r\n", celt ) ;
        return ResultFromScode( E_INVALIDARG ) ;   
    }

    for (l=0; l < celt; l++)
        VariantInit( &rgvar[l] ) ;

    // Retrieve the next celt elements.
    hr = NOERROR ;
    for (l = 0 ; m_posCurrent != NULL && celt != 0 ; l++)
    {   
        pItem = (CRequest*)pThis->m_pDataObject->m_lstRequests.GetNext( m_posCurrent ) ;
        celt-- ;
        if (pItem)
        {
            //TRACE( "   Setting rgvar[%d]\r\n", (int)l ) ;
            rgvar[l].vt = VT_DISPATCH ;
            rgvar[l].pdispVal = pItem->GetIDispatch( TRUE ) ;
            if (pceltFetched != NULL)
                (*pceltFetched)++ ;
        }
        else 
        {
            TRACE("GetNext failed in IEnumVARIANT::Next\r\n" ) ;
            return ResultFromScode( E_UNEXPECTED ) ;
        }
    }
    
    if (celt != 0)
    {
        //TRACE( "   End of list...celt == %d\r\n", (int)celt ) ;
        hr = ResultFromScode( S_FALSE ) ;
    }
    
    return hr ;
}

// IEnumVARIANT::Skip
//
STDMETHODIMP CEnumRequests::XEnumVARIANT::Skip(unsigned long celt) 
{
    METHOD_PROLOGUE(CEnumRequests, EnumVARIANT)

    ASSERT( pThis->m_pDataObject ) ;
    if (pThis->m_pDataObject == NULL) return ResultFromScode( E_UNEXPECTED ) ;

    //TRACE("XEnumVARIANT::Skip( %l )\r\n", celt ) ;
    
    while (m_posCurrent != NULL && celt--)
        pThis->m_pDataObject->m_lstRequests.GetNext( m_posCurrent ) ;
    
    return (celt == 0 ? NOERROR : ResultFromScode( S_FALSE )) ;
}

STDMETHODIMP CEnumRequests::XEnumVARIANT::Reset()
{
    METHOD_PROLOGUE(CEnumRequests, EnumVARIANT)

    ASSERT( pThis->m_pDataObject ) ;
    if (pThis->m_pDataObject == NULL) return ResultFromScode( E_UNEXPECTED ) ;

    //TRACE("XEnumVARIANT::Reset()\r\n") ;
    
    m_posCurrent = pThis->m_pDataObject->m_lstRequests.GetHeadPosition() ;
    
    return NOERROR ;
}

STDMETHODIMP CEnumRequests::XEnumVARIANT::Clone(IEnumVARIANT FAR* FAR* ppenum) 
{
    METHOD_PROLOGUE(CEnumRequests, EnumVARIANT)   

    ASSERT( pThis->m_pDataObject ) ;
    if (pThis->m_pDataObject == NULL) return ResultFromScode( E_UNEXPECTED ) ;
    
    //TRACE("XEnumVARIANT::Clone()\r\n" ) ;

    CEnumRequests* p = new CEnumRequests( pThis->m_pDataObject ) ;
    if (p)
    {
        p->m_xEnumVARIANT.m_posCurrent = m_posCurrent ;
        return NOERROR ;    
    }
    else
        return ResultFromScode( E_OUTOFMEMORY ) ;
}

  
