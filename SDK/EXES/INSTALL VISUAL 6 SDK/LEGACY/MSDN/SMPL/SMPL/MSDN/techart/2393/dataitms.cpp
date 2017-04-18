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
// dataitms.cpp : implementation file
//

#include "stdafx.h"
#include "xrtframe.h"
#include "dataitms.h"
#include "dataitem.h"
#include "doc.h"
#include "property.h"
#include "properti.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataItems

IMPLEMENT_DYNCREATE(CDataItems, CCmdTarget)
#define new DEBUG_NEW

CDataItems::CDataItems( CDataObject* pDataObject )
{
    m_pDataObject = pDataObject ;
    EnableAutomation();
}

CDataItems::~CDataItems()
{
}

void CDataItems::OnFinalRelease()
{
    // When the last reference for an automation object is released
    //  OnFinalRelease is called.  This implementation deletes the 
    //  object.  Add additional cleanup required for your object before
    //  deleting it from memory.

    delete this;
}

BEGIN_MESSAGE_MAP(CDataItems, CCmdTarget)
    //{{AFX_MSG_MAP(CDataItems)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDataItems, CCmdTarget)
    //{{AFX_DISPATCH_MAP(CDataItems)
    DISP_PROPERTY_EX(CDataItems, "Count", GetCount, SetNotSupported, VT_I2)
    DISP_PROPERTY_EX(CDataItems, "DataObject", GetDataObject, SetNotSupported, VT_DISPATCH)
    //}}AFX_DISPATCH_MAP
    // BUGFIX: 9/29/94 cek 
    // Changed .Item from DISP_FUNCTION to DISP_PROPERTY_PARAM
    // so that dataitems works correctly.
    //
    DISP_FUNCTION(CDataItems, "Item", GetItem, VT_DISPATCH, VTS_VARIANT)
    DISP_DEFVALUE(CDataItems, "Item")
    DISP_PROPERTY_EX_ID(CDataItems, "_NewEnum", DISPID_NEWENUM, _NewEnum, SetNotSupported, VT_UNKNOWN)
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataItems message handlers
short CDataItems::GetCount()
{
    if (m_pDataObject) 
        return (short)m_pDataObject->m_lstDataItems.GetCount() ;
    else
        return 0 ;
}

LPDISPATCH CDataItems::GetItem(const VARIANT FAR& item)
{
    CDataItem* pItem = NULL ;  
    LPDISPATCH lpDisp = NULL ;
    
    if (item.vt == VT_BSTR)
    {
        POSITION pos;
        // BUGFIX:  9/14/94 CEK
        // pItem is declared above.  Declaring it here is a bug.
        //
        //CDataItem* pItem = NULL ;
        for( pos = m_pDataObject->m_lstDataItems.GetHeadPosition(); pos != NULL; )
        {
            pItem = (CDataItem*)m_pDataObject->m_lstDataItems.GetNext( pos ) ;
            if (pItem)
            {
                CProperty*  pProp = (CProperty*)pItem->m_pValueProps->m_lstProps.GetHead() ;
                if (pProp->m_varValue.vt == VT_BSTR && 
                    (lstrcmp( pProp->m_varValue.bstrVal, item.bstrVal ) == 0))
                    break ;
            }
            pItem = NULL ;
        }
    }
    else
    {
        // coerce to VT_I4
        VARIANT va ;
        VariantInit( &va );
        if (SUCCEEDED(VariantChangeType( &va, (VARIANT FAR*)&item, 0, VT_I4 )))
        {
            POSITION pos = m_pDataObject->m_lstDataItems.FindIndex( (int)va.lVal ) ;
            if (pos != NULL)
                pItem = (CDataItem*)m_pDataObject->m_lstDataItems.GetAt( pos ) ;
        }
    }                 
    
    if (pItem != NULL)
        lpDisp = pItem->GetIDispatch(TRUE) ;        // AddRef
    

    // BUGBUG:  Implement dispatch exception if lpDisp == NULL
    return lpDisp ;

}

LPDISPATCH CDataItems::GetDataObject()
{
    ASSERT(m_pDataObject);
    return m_pDataObject->GetIDispatch(TRUE) ;
}
  
  
LPUNKNOWN CDataItems::_NewEnum()
{
    CEnumDataItems* pIEV = NULL ;

    pIEV = new CEnumDataItems( m_pDataObject ) ;
    
    if (pIEV)
    {
        pIEV->m_xEnumVARIANT.Reset() ;
        return &pIEV->m_xEnumVARIANT ;
    }
    
    return NULL ;
}

//----------------------------------------------------------------------------
// Implementation of CEnumDataItems which implements the IEnumVARIANT interface
// used by _NewEnum
//
BEGIN_INTERFACE_MAP(CEnumDataItems, CCmdTarget)
    INTERFACE_PART(CEnumDataItems, IID_IEnumVARIANT, EnumVARIANT)
END_INTERFACE_MAP()

CEnumDataItems::CEnumDataItems()
{
    m_pDataObject = NULL ;
    
    AfxOleLockApp();
}

CEnumDataItems::CEnumDataItems( CDataObject *pDataObject )
{
    m_pDataObject = pDataObject ;
    
    AfxOleLockApp();
}

CEnumDataItems::~CEnumDataItems()
{
    AfxOleUnlockApp();
}

void CEnumDataItems::OnFinalRelease()
{
    // When the last reference for an automation object is released
    //  OnFinalRelease is called.  This implementation deletes the 
    //  object.  Add additional cleanup required for your object before
    //  deleting it from memory.
    //TRACE("CEnumDataItems::OnFinalRelease\r\n" ) ;
    delete this;
}

//----------------------------------------------------------------------------
// Implementation of the nested class XEnumVARIANT (declared through the
// BEGIN/END_INTERFACE_PART macros in the declaration of CEnumDataItems)
//
// This class implements the IEnumVARIANT interface requried by the 
// _NewEnum property of the collection
//
CEnumDataItems::XEnumVARIANT::XEnumVARIANT()
{
    m_posCurrent = NULL ;
}

STDMETHODIMP_(ULONG) CEnumDataItems::XEnumVARIANT::AddRef()
{   
    METHOD_PROLOGUE(CEnumDataItems, EnumVARIANT)
    return pThis->ExternalAddRef() ;
}   

STDMETHODIMP_(ULONG) CEnumDataItems::XEnumVARIANT::Release()
{   
    METHOD_PROLOGUE(CEnumDataItems, EnumVARIANT)
    return pThis->ExternalRelease() ;
}   

STDMETHODIMP CEnumDataItems::XEnumVARIANT::QueryInterface( REFIID iid, void FAR* FAR* ppvObj )
{   
    METHOD_PROLOGUE(CEnumDataItems, EnumVARIANT)
    return (HRESULT)pThis->ExternalQueryInterface( (void FAR*)&iid, ppvObj) ;
}   

// IEnumVARIANT::Next
// 
STDMETHODIMP CEnumDataItems::XEnumVARIANT::Next( ULONG celt, VARIANT FAR* rgvar, ULONG FAR* pceltFetched)
{
    // This sets up the "pThis" pointer so that it points to our
    // containing CDataItems instance
    //
    METHOD_PROLOGUE(CEnumDataItems, EnumVARIANT)

    ASSERT( pThis->m_pDataObject ) ;
    if (pThis->m_pDataObject == NULL) return ResultFromScode( E_UNEXPECTED ) ;

    HRESULT hr;
    ULONG   l ;
    CDataItem*  pItem = NULL ;

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
        pItem = (CDataItem*)pThis->m_pDataObject->m_lstDataItems.GetNext( m_posCurrent ) ;
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
STDMETHODIMP CEnumDataItems::XEnumVARIANT::Skip(unsigned long celt) 
{
    METHOD_PROLOGUE(CEnumDataItems, EnumVARIANT)

    ASSERT( pThis->m_pDataObject ) ;
    if (pThis->m_pDataObject == NULL) return ResultFromScode( E_UNEXPECTED ) ;

    //TRACE("XEnumVARIANT::Skip( %l )\r\n", celt ) ;
    
    while (m_posCurrent != NULL && celt--)
        pThis->m_pDataObject->m_lstDataItems.GetNext( m_posCurrent ) ;
    
    return (celt == 0 ? NOERROR : ResultFromScode( S_FALSE )) ;
}

STDMETHODIMP CEnumDataItems::XEnumVARIANT::Reset()
{
    METHOD_PROLOGUE(CEnumDataItems, EnumVARIANT)

    ASSERT( pThis->m_pDataObject ) ;
    if (pThis->m_pDataObject == NULL) return ResultFromScode( E_UNEXPECTED ) ;

    //TRACE("XEnumVARIANT::Reset()\r\n") ;
    
    m_posCurrent = pThis->m_pDataObject->m_lstDataItems.GetHeadPosition() ;
    
    return NOERROR ;
}

STDMETHODIMP CEnumDataItems::XEnumVARIANT::Clone(IEnumVARIANT FAR* FAR* ppenum) 
{
    METHOD_PROLOGUE(CEnumDataItems, EnumVARIANT)   

    ASSERT( pThis->m_pDataObject ) ;
    if (pThis->m_pDataObject == NULL) return ResultFromScode( E_UNEXPECTED ) ;
    
    //TRACE("XEnumVARIANT::Clone()\r\n" ) ;

    CEnumDataItems* p = new CEnumDataItems( pThis->m_pDataObject ) ;
    if (p)
    {
        p->m_xEnumVARIANT.m_posCurrent = m_posCurrent ;
        return NOERROR ;    
    }
    else
        return ResultFromScode( E_OUTOFMEMORY ) ;
}

  
