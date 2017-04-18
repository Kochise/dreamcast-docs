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
// properti.cpp : implementation file
//
// This file implements CProperites, which provides OLE Automation
// support for the WOSA/XRT "Properties" collection.
//
// CDataObject has a member variable of type CObList which contains
// a list of the CProperties objects that have been created to support
// Request objects.
//
// Both CRequest and CDataItem have member variables that point to
// CProperties objects.
//
#include "stdafx.h"
#include "xrtframe.h"
#include "doc.h"

#include "property.h"
#include "properti.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// When a CDataObject is serialized, it serializes all of the
// CProperties objects.
//
IMPLEMENT_SERIAL(CProperties, CCmdTarget, 1 )
#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// CProperties
CProperties::CProperties( CDataObject* pDataObject )
{
    m_pDataObject = pDataObject ;
    if (m_pDataObject)
        m_dwID = m_pDataObject->GeneratePropertySetID() ;
    else
        m_dwID = 0 ;
    EnableAutomation();
}

CProperties::~CProperties()
{
    // Release all our props
    CProperty* pProp ;
    POSITION pos ;
    for ( pos = m_lstProps.GetHeadPosition() ; pos != NULL ;)
    {
        pProp = (CProperty*)m_lstProps.GetNext( pos ) ;
        ASSERT(pProp) ;
        #ifdef USERELEASETODELETE
        if (pProp)
            pProp->ExternalRelease() ;
        #else 
        delete pProp ;
        #endif
    }
}

void CProperties::OnFinalRelease()
{
    // When the last reference for an automation object is released
    //  OnFinalRelease is called.  This implementation deletes the 
    //  object.  Add additional cleanup required for your object before
    //  deleting it from memory.

    delete this;
}

void CProperties::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        m_lstProps.Serialize(ar) ;
    }
    else
    {
        m_pDataObject = (CDataObject*)ar.m_pDocument ;
        m_dwID = m_pDataObject->GeneratePropertySetID() ;
        m_lstProps.Serialize(ar) ;
    }
}    

// When a CDataItem is being rendered to the clipboard in CF_TEXT
// format it simply calls the SaveAsText method of it's
// contained CProperties object...
//
static char BASED_CODE szTAB[] = "\t" ;
void CProperties::SaveAsText(CArchive& ar, BOOL fIncludeNames)
{
    ASSERT(ar.IsStoring());

    CProperty* p = NULL ;   
    POSITION pos = m_lstProps.GetHeadPosition() ;
    if (pos)
        p = (CProperty*)m_lstProps.GetNext( pos ) ;
    if (p && fIncludeNames)
    {
        p->SaveAsText(ar) ;
        if (pos != NULL)
            ar.Write( szTAB, sizeof(szTAB)-1 ) ;        
    }
                
    for ( ; pos != NULL ;)
    {
        p = (CProperty*)m_lstProps.GetNext( pos ) ;
        ASSERT(p) ;
        p->SaveAsText(ar) ;
        if (pos != NULL)
            ar.Write( szTAB, sizeof(szTAB)-1 ) ;        
    }
}

// Add a new property to the list
CProperty* CProperties::Add( const CString& rstr) 
{
    CProperty*  pProp = new CProperty( m_pDataObject ) ;
    ASSERT( pProp ) ;
    
    pProp->m_strName = rstr ;
    m_lstProps.AddTail( pProp ) ;
    
    return pProp ;
}


CProperty* CProperties::Add( const VARIANT FAR& properties )
{
    // BUGBUG: For now assume properties is not an array
    //
    CProperty* pProp = new CProperty( m_pDataObject ) ;
    if (pProp != NULL)
    {
        if (properties.vt == VT_BSTR)
            pProp->m_strName = properties.bstrVal ;
        else
        {
            VARIANT vTemp ;
            if (SUCCEEDED(VariantChangeType( &vTemp, (LPVARIANT)&properties, 0, VT_BSTR )))
            {
                pProp->m_strName = vTemp.bstrVal ;
                VariantClear( &vTemp ) ;
            }
            else
            {
                delete pProp ;
                return NULL ;
            }
        }
        m_lstProps.AddTail( pProp ) ;        
    }    
    return pProp ;
}

CProperty* CProperties::Find( CProperty* pProp ) 
{    
    POSITION pos = m_lstProps.Find( pProp ) ;
    if (pos)
        pProp = (CProperty*)m_lstProps.GetAt(pos) ;
    else
        return NULL ;
        
    return pProp ;
}

// Find a CProperty given a string
CProperty* CProperties::Find( const CString& rstr ) 
{    
    CProperty* p = NULL ;   
    POSITION pos ;
    for ( pos = m_lstProps.GetHeadPosition() ; pos != NULL ;)
    {
        p = (CProperty*)m_lstProps.GetNext( pos ) ;
        if (p->m_strName == rstr)
            return p ;
    }
    return NULL ;
}

BEGIN_MESSAGE_MAP(CProperties, CCmdTarget)
    //{{AFX_MSG_MAP(CProperties)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProperties, CCmdTarget)
    //{{AFX_DISPATCH_MAP(CProperties)
    DISP_PROPERTY_EX(CProperties, "Count", GetCount, SetNotSupported, VT_I2)
    DISP_PROPERTY_EX(CProperties, "DataObject", GetDataObject, SetNotSupported, VT_DISPATCH)
    DISP_FUNCTION(CProperties, "Add", _Add, VT_VARIANT, VTS_VARIANT)
    //}}AFX_DISPATCH_MAP
    DISP_FUNCTION(CProperties, "Item", Item, VT_DISPATCH, VTS_VARIANT)
    DISP_DEFVALUE(CProperties, "Item")
    DISP_PROPERTY_EX_ID(CProperties, "_NewEnum", DISPID_NEWENUM, _NewEnum, SetNotSupported, VT_UNKNOWN)
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProperties message handlers
short CProperties::GetCount()
{
    return (short)m_lstProps.GetCount() ;
}

LPDISPATCH CProperties::GetDataObject()
{
    ASSERT(m_pDataObject);
    return m_pDataObject->GetIDispatch(TRUE) ;
}

VARIANT CProperties::_Add(const VARIANT FAR& properties)
{
    VARIANT va;
    VariantInit( &va ) ;
    CProperty* pProp = Add( properties ) ;
    if (pProp) 
    {
        va.vt = VT_DISPATCH ;
        va.pdispVal = pProp->GetIDispatch(TRUE) ;
    }    
    return va;
}

LPDISPATCH CProperties::Item(const VARIANT FAR& item)
{
    CProperty* pItem = NULL ;  
    LPDISPATCH lpDisp = NULL ;
    
    if (item.vt == VT_BSTR)
    {
        POSITION pos ;
        for (pos = m_lstProps.GetHeadPosition() ; pos != NULL ;)
        {
            pItem = (CProperty*)m_lstProps.GetNext(pos) ;
            if (pItem && (pItem->m_strName == item.bstrVal))
            {
                break ;
            }
            else
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
            POSITION pos = m_lstProps.FindIndex( (int)va.lVal ) ;
            if (pos)
                pItem = (CProperty*)m_lstProps.GetAt(pos) ;
        }
    }                 
    
    if (pItem != NULL)
        lpDisp = pItem->GetIDispatch(TRUE) ;        // AddRef

    // BUGBUG:  Implement dispatch exception if lpDisp == NULL
    return lpDisp ;

}

LPUNKNOWN CProperties::_NewEnum()
{
    CEnumProperties* pIEV = NULL ;

    pIEV = new CEnumProperties( this ) ;
    
    if (pIEV)
    {
        pIEV->m_xEnumVARIANT.Reset() ;
        return &pIEV->m_xEnumVARIANT ;
    }
    
    return NULL ;
}

//----------------------------------------------------------------------------
// Implementation of CEnumProperties which implements the IEnumVARIANT interface
// used by _NewEnum
//
BEGIN_INTERFACE_MAP(CEnumProperties, CCmdTarget)
    INTERFACE_PART(CEnumProperties, IID_IEnumVARIANT, EnumVARIANT)
END_INTERFACE_MAP()

CEnumProperties::CEnumProperties( CProperties *pProps )
{
    m_pProperties = pProps ;
    
    AfxOleLockApp();
}

CEnumProperties::~CEnumProperties()
{
    AfxOleUnlockApp();
}

void CEnumProperties::OnFinalRelease()
{
    // When the last reference for an automation object is released
    //  OnFinalRelease is called.  This implementation deletes the 
    //  object.  Add additional cleanup required for your object before
    //  deleting it from memory.
    //TRACE("CEnumProperties::OnFinalRelease\r\n" ) ;
    delete this;
}

//----------------------------------------------------------------------------
// Implementation of the nested class XEnumVARIANT (declared through the
// BEGIN/END_INTERFACE_PART macros in the declaration of CEnumProperties)
//
// This class implements the IEnumVARIANT interface requried by the 
// _NewEnum property of the collection
//
CEnumProperties::XEnumVARIANT::XEnumVARIANT()
{
    m_posCurrent = NULL ;
}

STDMETHODIMP_(ULONG) CEnumProperties::XEnumVARIANT::AddRef()
{   
    METHOD_PROLOGUE(CEnumProperties, EnumVARIANT)
    return pThis->ExternalAddRef() ;
}   

STDMETHODIMP_(ULONG) CEnumProperties::XEnumVARIANT::Release()
{   
    METHOD_PROLOGUE(CEnumProperties, EnumVARIANT)
    return pThis->ExternalRelease() ;
}   

STDMETHODIMP CEnumProperties::XEnumVARIANT::QueryInterface( REFIID iid, void FAR* FAR* ppvObj )
{   
    METHOD_PROLOGUE(CEnumProperties, EnumVARIANT)
    return (HRESULT)pThis->ExternalQueryInterface( (void FAR*)&iid, ppvObj) ;
}   

// IEnumVARIANT::Next
// 
STDMETHODIMP CEnumProperties::XEnumVARIANT::Next( ULONG celt, VARIANT FAR* rgvar, ULONG FAR* pceltFetched)
{
    // This sets up the "pThis" pointer so that it points to our
    // containing CProperties instance
    //
    METHOD_PROLOGUE(CEnumProperties, EnumVARIANT)

    HRESULT hr;
    ULONG   l ;
    CProperty*  pItem = NULL ;

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
        pItem = (CProperty*)pThis->m_pProperties->m_lstProps.GetNext( m_posCurrent ) ;
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
STDMETHODIMP CEnumProperties::XEnumVARIANT::Skip(unsigned long celt) 
{
    METHOD_PROLOGUE(CEnumProperties, EnumVARIANT)

    ASSERT( pThis->m_pProperties ) ;
    if (pThis->m_pProperties == NULL) return ResultFromScode( E_UNEXPECTED ) ;

    //TRACE("XEnumVARIANT::Skip( %l )\r\n", celt ) ;
    
    while (m_posCurrent != NULL && celt--)
        pThis->m_pProperties->m_lstProps.GetNext( m_posCurrent ) ;
    
    return (celt == 0 ? NOERROR : ResultFromScode( S_FALSE )) ;
}

STDMETHODIMP CEnumProperties::XEnumVARIANT::Reset()
{
    METHOD_PROLOGUE(CEnumProperties, EnumVARIANT)

    ASSERT( pThis->m_pProperties ) ;
    if (pThis->m_pProperties == NULL) return ResultFromScode( E_UNEXPECTED ) ;

    //TRACE("XEnumVARIANT::Reset()\r\n") ;
    
    m_posCurrent = pThis->m_pProperties->m_lstProps.GetHeadPosition() ;
    
    return NOERROR ;
}

STDMETHODIMP CEnumProperties::XEnumVARIANT::Clone(IEnumVARIANT FAR* FAR* ppenum) 
{
    METHOD_PROLOGUE(CEnumProperties, EnumVARIANT)   

    ASSERT( pThis->m_pProperties ) ;
    if (pThis->m_pProperties == NULL) return ResultFromScode( E_UNEXPECTED ) ;
    
    //TRACE("XEnumVARIANT::Clone()\r\n" ) ;

    CEnumProperties* p = new CEnumProperties( pThis->m_pProperties ) ;
    if (p)
    {
        p->m_xEnumVARIANT.m_posCurrent = m_posCurrent ;
        return NOERROR ;    
    }
    else
        return ResultFromScode( E_OUTOFMEMORY ) ;
}

  
