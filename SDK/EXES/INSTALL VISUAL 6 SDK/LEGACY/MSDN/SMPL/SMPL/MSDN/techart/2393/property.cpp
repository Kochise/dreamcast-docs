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
// property.cpp : implementation file
//
// This file implents CProperty and CPropertyServerItem.
//
// CProperty represents the WOSA/XRT "Property" object.  
//
// Property objects have two data points associated with them:
//    A name and a value
//
//      The name is stored in CString m_strName and the value is stored
//      in VARIANT m_varValue.
//
// Through CPropertyServerItem CProperty objects can be 'linked' into
// container applications.  However, XRTFrame currently provides
// no user interface to allow this.
//
// Ideally, the user would be able to click on a property within
// a DataItem in the data item list and hit "Copy Property".  But this
// UI is not included in this sample.
//
#include "stdafx.h"
#include <afxpriv.h>
#include "xrtframe.h"

#include "doc.h"
#include "view.h"
#include "property.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CProperty, CCmdTarget,1)
IMPLEMENT_DYNAMIC(CPropertyServerItem, COleServerItem)
#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// CProperty
CProperty::CProperty( CDataObject* pDataObject)
{
    m_pDataObject = pDataObject ;
    m_pServerItem = NULL ;
    VariantInit( &m_varValue ) ;
    EnableAutomation();
}

CProperty::~CProperty()
{
    VariantClear( &m_varValue ) ;
    // If we are attached to a server item, detach from it
    //
    if (m_pServerItem != NULL)
        m_pServerItem->m_pProperty = NULL ;
}

void CProperty::OnFinalRelease()
{
    // When the last reference for an automation object is released
    //  OnFinalRelease is called.  This implementation deletes the 
    //  object.  Add additional cleanup required for your object before
    //  deleting it from memory.

    delete this;
}

void CProperty::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        ar << m_strName ;
        // TODO:  Serialize m_varValue
        // (why?  We only really serialize Request objects and
        // Request objects don't care what the value part
        // of their properties are.  And besides, trying to
        // serialize a VARIANT would be a pain.)
    }
    else
    {
        m_pDataObject = (CDataObject*)ar.m_pDocument ;
        ar >> m_strName ;   
        // TODO:  Serialize m_varValue
    }
}    

// When a CProperties object is being rendered in CF_TEXT format 
// (because it's DataItem was copied to the clipboard for example)
// it simply calls each CProperty's SaveAsText method to do the
// dirty work
//
void CProperty::SaveAsText(CArchive& ar)
{
    ASSERT(ar.IsStoring());
    VARIANT va ;
    VariantInit(&va) ;
    
    if (SUCCEEDED(VariantChangeType( &va, &m_varValue, 0, VT_BSTR )))
    {
        ar.Write( va.bstrVal, SysStringLen(va.bstrVal) ) ;
        VariantClear( &va ) ;
    }
    else
    {
        ar.Write( "<type!>", lstrlen("<type!>") ) ;
    }
}

// Isn't OO design neat?   Everyone has their own Draw method
// and only the smallest objects actually do any work.
//
int CProperty::Draw( CDC* pDC, CPoint ptStart, int n ) 
{
    CSize sizeItem ;
    VARIANT va ;
    VariantInit(&va) ;
    
    CFont   font ;
    CFont*  pOldFont ;
    if (m_pDataObject) 
        pOldFont = m_pDataObject->SelectDocFont(pDC, font);
        
    if (SUCCEEDED(VariantChangeType( &va, &m_varValue, 0, VT_BSTR)))
    {                        
        sizeItem = pDC->GetTextExtent( va.bstrVal, SysStringLen( va.bstrVal ) ) ;
    }
    else
    {
        sizeItem = pDC->GetTextExtent( "<type!>", lstrlen( "<type!>") ) ;
    }

    RECT rc ;                             
    rc.left = ptStart.x ;
    rc.top = ptStart.y ;
    rc.bottom = ptStart.y + sizeItem.cy ;
    rc.right = rc.left + sizeItem.cx ;

    pDC->ExtTextOut( ptStart.x, ptStart.y, ETO_OPAQUE, &rc, m_strName, m_strName.GetLength(), NULL ) ;

    if (m_pDataObject && pOldFont != NULL)
        pDC->SelectObject(pOldFont);

    VariantClear( &va ) ;
    return sizeItem.cy ;
}

void CProperty::CalcDisplaySize( CDC* pDC, CSize& sizeItem ) 
{  
    VARIANT va ;
    VariantInit(&va) ;

    CFont   font ;
    CFont*  pOldFont ;
    if (m_pDataObject) 
        pOldFont = m_pDataObject->SelectDocFont(pDC, font);

    if (SUCCEEDED(VariantChangeType( &va, &m_varValue, 0, VT_BSTR)))
    {                        
        sizeItem = pDC->GetTextExtent( va.bstrVal, SysStringLen( va.bstrVal ) ) ;
        VariantClear( &va ) ;
    }
    else
    {
        sizeItem = pDC->GetTextExtent( "<type!>", lstrlen( "<type!>") ) ;
    }
    if (m_pDataObject && pOldFont != NULL)
        pDC->SelectObject(pOldFont);
}

// This is called whenever something else in XRTFrame thinks a 
// property should notify it's link clients that it is changed.
// by doing this, we can optimize how XRTFrame works when there
// are tons of Properties linked into containers
//
void CProperty::NotifyLinks()
{
    if (m_pServerItem)
        m_pServerItem->NotifyChanged() ;
}

BEGIN_MESSAGE_MAP(CProperty, CCmdTarget)
    //{{AFX_MSG_MAP(CProperty)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProperty, CCmdTarget)
    //{{AFX_DISPATCH_MAP(CProperty)
    DISP_PROPERTY_EX(CProperty, "Name", GetName, SetName, VT_BSTR)
    DISP_PROPERTY_EX(CProperty, "Value", GetValue, SetValue, VT_VARIANT)
    //}}AFX_DISPATCH_MAP
    // BUGFIX: 9/29/94 cek
    // made "Value" be the default property for a CProperty.
    DISP_DEFVALUE(CProperty, "Value")
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProperty message handlers
BSTR CProperty::GetName()
{
    return m_strName.AllocSysString();
}

void CProperty::SetName(LPCSTR lpszNewValue)
{
    m_strName = lpszNewValue ;
    if (m_pDataObject)
       m_pDataObject->UpdateAllViews( NULL, UPDATE_CHANGEPROP, this ) ;
}

VARIANT CProperty::GetValue()
{
    VARIANT va;
    VariantInit( &va ) ;
    VariantCopy( &va, &m_varValue ) ;
    return va;
}

void CProperty::SetValue(const VARIANT FAR& newValue)
{
    VariantClear( &m_varValue ) ;
    VariantCopy( &m_varValue, (LPVARIANT)&newValue ) ;
    if (m_pDataObject)
    {
        m_pDataObject->UpdateAllViews( NULL, UPDATE_CHANGEPROP, this ) ;
        m_pDataObject->UpdateAllItems( NULL, UPDATE_CHANGEPROP, this ) ;
    }
}


// CPropertyServerItem implementation
//
CPropertyServerItem::CPropertyServerItem(CDataObject* pContainerDoc, CProperty* pProperty)
    : COleServerItem(pContainerDoc, TRUE)
{
    // need to attach this server item to the node in the document
    ASSERT_VALID(pProperty);
    m_pProperty = pProperty;
    pProperty->m_pServerItem = this;

    BSTR    bstr ;
    bstr = SysAllocStringLen( NULL, pProperty->m_strName.GetLength() + 1 ) ;
    wsprintf( bstr, "%s", (LPCSTR)pProperty->m_strName ) ;
    SetItemName( bstr );
    SysFreeString(bstr) ;

    // support CF_TEXT format
    GetDataSource()->DelayRenderFileData(CF_TEXT);    
}

CPropertyServerItem::~CPropertyServerItem()
{
    if (m_pProperty != NULL)
    {
        m_pProperty->m_pServerItem = NULL ;
    }
}

// We override OnGetClipboardData so that we can prevent it from putting
// the "embedding" clipboard formats (CF_EMBEDDEDOBJECT and CF_OBJECTDESCRIPTOR)
// on the clipboard.  The default impelementation calls 
// COleServerItem::GetClipboardData.  
//
COleDataSource* CPropertyServerItem::OnGetClipboardData(BOOL bIncludeLink,
    LPPOINT lpOffset, LPSIZE lpSize)
{
    ASSERT_VALID(this);
    
    COleDataSource* pDataSource = new COleDataSource;
    TRY
    {
        // add CF_EMBEDDEDOBJECT by creating memory storage copy of the object
        STGMEDIUM stgMedium;
        //GetEmbedSourceData(&stgMedium);
        //pDataSource->CacheData(_oleData.cfEmbedSource, &stgMedium);
            
        // add CF_OBJECTDESCRIPTOR
        //GetObjectDescriptorData(lpOffset, lpSize, &stgMedium);
        //pDataSource->CacheData(RegisterClipboardFormat("Object Descriptor"), &stgMedium);
            
        // add any presentation entries/conversion formats that the item
        //  can produce.
        AddOtherClipboardData(pDataSource);
            
        // add CF_LINKSOURCE if supporting links to pseudo objects
        if (bIncludeLink && GetLinkSourceData(&stgMedium))
        {
            pDataSource->CacheData((USHORT)RegisterClipboardFormat("Link Source"), &stgMedium);
                
            // add CF_LINKSOURCEDESCRIPTOR
            GetObjectDescriptorData(lpOffset, lpSize, &stgMedium);
            pDataSource->CacheData((USHORT)RegisterClipboardFormat("Link Source Descriptor"), &stgMedium);
        }
    }
    CATCH_ALL(e)
    {
        delete pDataSource;
        THROW_LAST();
    }
    END_CATCH_ALL
    
    ASSERT_VALID(pDataSource);
    return pDataSource;
}

void CPropertyServerItem::OnOpen()
{
    if (IsLinkedItem() && m_pProperty != NULL)
    {
        // for linked items, try to select this request
        // in the DataObject
        CDataObject* pDoc = GetDocument();
        ASSERT(pDoc != NULL);

        POSITION pos = pDoc->GetFirstViewPosition();
        ASSERT(pos != NULL);

        CDataObjectView* pView = NULL ;
        while(pView->IsKindOf(RUNTIME_CLASS(CDataObjectView)) == FALSE)
        {
            pView = (CDataObjectView*)pDoc->GetNextView(pos);
        }
        ASSERT(pView) ;
        ASSERT(pView->IsKindOf(RUNTIME_CLASS(CDataObjectView)));
        pView->SetSelection(m_pProperty);
    }
    
//    if (IsLinkedItem())
//        COleServerItem::OnOpen();
}

void CPropertyServerItem::Serialize(CArchive& ar)
{
}

BOOL CPropertyServerItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
    // Most applications, like this one, only handle drawing the content
    //  aspect of the item.  If you wish to support other aspects, such
    //  as DVASPECT_THUMBNAIL (by overriding OnDrawEx), then this
    //  implementation of OnGetExtent should be modified to handle the
    //  additional aspect(s).

    if (dwDrawAspect != DVASPECT_CONTENT)
        return COleServerItem::OnGetExtent(dwDrawAspect, rSize);

    // CPropertyServerItem::OnGetExtent is called to get the extent in
    //  HIMETRIC units of the entire item.  
    rSize = CSize(0, 0);
    CClientDC dc(NULL);
    dc.SetMapMode(MM_ANISOTROPIC);

    ASSERT_VALID(m_pProperty);
    m_pProperty->CalcDisplaySize(&dc, rSize);

    dc.LPtoHIMETRIC(&rSize); // convert pixels to HIMETRIC

    return TRUE;
}

BOOL CPropertyServerItem::OnDraw(CDC* pDC, CSize& rSize)
{

    // determine extent of this item in the document
    CPoint ptStart(0,0) ;
    rSize = CSize(0, 0);
    m_pProperty->CalcDisplaySize(pDC, rSize);

    // prepare to draw and remember the extent in himetric units
    pDC->SetWindowOrg(0, 0);
    pDC->SetWindowExt(rSize);
    pDC->SetViewportExt(rSize);  // Note: only affects the m_hAttribDC

    pDC->LPtoHIMETRIC(&rSize);   // convert pixels to HIMETRIC

    m_pProperty->Draw(pDC, ptStart) ;
    return TRUE;
}


BOOL CPropertyServerItem::OnRenderFileData(LPFORMATETC lpFormatEtc, CFile* pFile)
{
    ASSERT(lpFormatEtc != NULL);
    if (lpFormatEtc->cfFormat != CF_TEXT)
        return COleServerItem::OnRenderFileData(lpFormatEtc, pFile);

    BOOL bResult = FALSE;
    if (m_pProperty != NULL)
    {
        TRY
        {
            // save as text
            CArchive ar(pFile, CArchive::store);
            m_pProperty->SaveAsText(ar);
            ar << (BYTE)'\0';   // terminate with NUL character
            bResult = TRUE;
        }
        END_TRY
    }
    return bResult;
}

// BUGBUG!
// MFC 2.5 has the following bug in it's COleServerItem IDataObject implementation:
//      The ::DAdvise member does not check the passed FORMATETC to verify that
//      it is a format the server item understands.   Some containers (e.g. Excel 5.0)
//      call DAdvise multiple times, starting with the containers' preferred
//      format and stop calling it once it suceeds.  By doing this they
//      avoid at least one RPC call (i.e. a call to QueryGetData()).
//      However, because MFC 2.5's DAdvise does not check the passed format
//      the container thinks the first format is ok.   
//
// The code below fixes this bug by hooking out the ::XDataObject class of
// COleServerItem and defferring to it (and checking the FORMAT etc in
// DAdvise).
//      
#if (_MFC_VER <= 0x0250)
/////////////////////////////////////////////////////////////////////////////
// CPropertyServerItem::XBugFixDataObject
BEGIN_INTERFACE_MAP(CPropertyServerItem, COleServerItem)
    INTERFACE_PART(CPropertyServerItem, IID_IDataObject, BugFixDataObject)
END_INTERFACE_MAP()

STDMETHODIMP_(ULONG) CPropertyServerItem::XBugFixDataObject::AddRef()
{
    METHOD_PROLOGUE(CPropertyServerItem, BugFixDataObject)
    return (ULONG)pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CPropertyServerItem::XBugFixDataObject::Release()
{
    METHOD_PROLOGUE(CPropertyServerItem, BugFixDataObject)
    return (ULONG)pThis->ExternalRelease();
}

STDMETHODIMP CPropertyServerItem::XBugFixDataObject::QueryInterface(
    REFIID iid, LPVOID far* ppvObj)
{
    METHOD_PROLOGUE(CPropertyServerItem, BugFixDataObject)
    return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CPropertyServerItem::XBugFixDataObject::GetData(
    LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium)
{
    METHOD_PROLOGUE(CPropertyServerItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    //( "GetData:  cfFormat == %d\r\n", lpFormatEtc->cfFormat ) ;
    return pThis->m_xDataObject.GetData(lpFormatEtc, lpStgMedium);
}


STDMETHODIMP CPropertyServerItem::XBugFixDataObject::GetDataHere(
    LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium)
{
    METHOD_PROLOGUE(CPropertyServerItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    //TRACE( "GetDataHere:  cfFormat == %d\r\n", lpFormatEtc->cfFormat ) ;
    return pThis->m_xDataObject.GetDataHere(lpFormatEtc, lpStgMedium);
}

STDMETHODIMP CPropertyServerItem::XBugFixDataObject::QueryGetData(LPFORMATETC lpFormatEtc)
{
    METHOD_PROLOGUE(CPropertyServerItem, BugFixDataObject)
    ASSERT_VALID(pThis);
       
    //TRACE( "QueryGetData:  cfFormat == %d\r\n", lpFormatEtc->cfFormat ) ;

    return pThis->m_xDataObject.QueryGetData(lpFormatEtc);
}

STDMETHODIMP CPropertyServerItem::XBugFixDataObject::GetCanonicalFormatEtc(
    LPFORMATETC lpFormatEtcIn, LPFORMATETC lpFormatEtcOut)
{
    // because we support the target-device (ptd) for server metafile format,
    //  all members of the FORMATETC are significant.

    //TRACE( "GetCanonicalFormatEtc:  In.cfFormat == %d, Out.cfFormat == %d\r\n", lpFormatEtcIn->cfFormat, lpFormatEtcIn->cfFormat ) ;
    return ResultFromScode(DATA_S_SAMEFORMATETC);
}

STDMETHODIMP CPropertyServerItem::XBugFixDataObject::SetData(
    LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium, BOOL fRelease)
{
    METHOD_PROLOGUE(CPropertyServerItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    //TRACE( "SetData:  cfFormat == %d\r\n", lpFormatEtc->cfFormat ) ;
    return pThis->m_xDataObject.SetData( lpFormatEtc, lpStgMedium, fRelease);
}

STDMETHODIMP CPropertyServerItem::XBugFixDataObject::EnumFormatEtc(
    DWORD dwDirection, LPENUMFORMATETC FAR* ppenumFormatEtc)
{
    METHOD_PROLOGUE(CPropertyServerItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    return pThis->m_xDataObject.EnumFormatEtc( dwDirection, ppenumFormatEtc);
}

STDMETHODIMP CPropertyServerItem::XBugFixDataObject::DAdvise(
    FORMATETC FAR* pFormatetc, DWORD advf,
    LPADVISESINK pAdvSink, DWORD FAR* pdwConnection)
{
    METHOD_PROLOGUE(CPropertyServerItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    //TRACE( "DAdvise:  cfFormat == %d, advf = %d\r\n", pFormatetc->cfFormat, advf ) ;

    if (pFormatetc->cfFormat != 0 && FAILED(pThis->m_xDataObject.QueryGetData(pFormatetc)))
    {
        *pdwConnection = 0 ;
        return ResultFromScode( DATA_E_FORMATETC ) ;
    }
    
    return pThis->m_xDataObject.DAdvise(pFormatetc, advf, pAdvSink, pdwConnection);
}

STDMETHODIMP CPropertyServerItem::XBugFixDataObject::DUnadvise(DWORD dwConnection)
{
    METHOD_PROLOGUE(CPropertyServerItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    return pThis->m_xDataObject.DUnadvise( dwConnection ) ;
}

STDMETHODIMP CPropertyServerItem::XBugFixDataObject::EnumDAdvise(
    LPENUMSTATDATA FAR* ppenumAdvise)
{
    METHOD_PROLOGUE(CPropertyServerItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    return pThis->m_xDataObject.EnumDAdvise( ppenumAdvise ) ;
}

#endif // BUGFIX


/////////////////////////////////////////////////////////////////////////////
// CPropertyServerItem diagnostics

#ifdef _DEBUG
void CPropertyServerItem::AssertValid() const
{
    COleServerItem::AssertValid();
}

void CPropertyServerItem::Dump(CDumpContext& dc) const
{
    COleServerItem::Dump(dc);
}
#endif

