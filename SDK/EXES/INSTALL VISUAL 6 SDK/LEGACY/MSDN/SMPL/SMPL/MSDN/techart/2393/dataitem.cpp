// WOSA/XRT XRTFrame Sample Application Version 1.01
//
// Copyright (c) 1993 Microsoft Corporation, All Rights Reserved.
//
//      This is a part of the Microsoft Source Code Samples. 
//      This source code is only intended as a supplement to 
//      Microsoft Development Tools and/or WinHelp documentation.
//      See these sources for detailed information regarding the 
//      Microsoft samples programs.
//
// dataitem.cpp : CDataItem implementation file
//
// This file implements the CDataItem and CDataItemServerItem classes.
//
// CDataItem objects are the objects that exist in the lower listbox in
// the CDataObject view windows.   They represent the "DataItem" objects
// as defined in the WOSA/XRT spec.
//
// The CDataItemServerItem class is derived from COleServerItem which
// provides linking support.  Thus an OLE 2.0 container can link to
// a particular DataItem object.
//
#include "stdafx.h"
#include <afxpriv.h>    // for CSharedFile

#include "xrtframe.h"
#include "doc.h"
#include "collist.h"

#include "request.h"

#include "properti.h"
#include "property.h"
#include "dataitem.h"
#include "view.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataItem
IMPLEMENT_DYNAMIC(CDataItemServerItem, COleServerItem)
IMPLEMENT_SERIAL(CDataItem, CCmdTarget,1)
#define new DEBUG_NEW

CDataItem::CDataItem( CDataObject* pDataObject, CProperties* pProperties )
{
    m_pDataObject = pDataObject ;
    m_pRequestProps = pProperties ;
    m_pServerItem = NULL ; // will get connected it need be
    m_dwID = pDataObject->GenerateDataItemID() ;
    m_dwRequestID = 0 ;

    m_pValueProps = new CProperties( pDataObject ) ;
    ASSERT(m_pValueProps) ;
    
    EnableAutomation();
}

CDataItem::~CDataItem()
{
    // If we are attached to a server item, detach from it
    //
    if (m_pServerItem != NULL)
        m_pServerItem->m_pDataItem = NULL ;
    if (m_pValueProps != NULL)
    {
        #ifdef USERELEASETODELETE
        m_pValueProps->ExternalRelease() ;
        #else 
        delete m_pValueProps ;
        #endif
    }        
}

void CDataItem::OnFinalRelease()
{
    // When the last reference for an automation object is released
    //  OnFinalRelease is called.  This implementation deletes the 
    //  object.  Add additional cleanup required for your object before
    //  deleting it from memory.

    delete this;
}

BEGIN_MESSAGE_MAP(CDataItem, CCmdTarget)
    //{{AFX_MSG_MAP(CDataItem)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDataItem, CCmdTarget)
    //{{AFX_DISPATCH_MAP(CDataItem)
    DISP_FUNCTION(CDataItem, "Copy", Copy, VT_EMPTY, VTS_NONE)
    //}}AFX_DISPATCH_MAP
    //DISP_PROPERTY_EX(CDataItem, "Properties", GetProperties, SetNotSupported, VT_VARIANT)
    DISP_PROPERTY_PARAM(CDataItem, "Properties", GetProperties, SetNotSupported, VT_VARIANT, VTS_VARIANT)
END_DISPATCH_MAP()


void CDataItem::Serialize(CArchive& ar)
{
    // CDataItem objects are never stored in persisent storage
    // they may be linked, but not embedded.
    //
    // Note:  It would be possible to make them embeddable, but
    // it would probably not be very useful....
    //
}    

// Since links are made available using CF_TEXT we need to be able
// to render ourself as text.  This function does the work.
//
// The fIncludeNames flag is an XRTFrame specific extension to the
// WOSA/XRT model.  Via an Automation controller a user can say 
// "Include the item names in items I link to".
//
static char BASED_CODE szTAB[] = "\t" ;
static char BASED_CODE szCRLF[] = "\r\n";
void CDataItem::SaveAsText(CArchive& ar, BOOL fIncludeNames)
{
    ASSERT(ar.IsStoring());
    m_pValueProps->SaveAsText( ar, fIncludeNames ) ;
}

/////////////////////////////////////////////////////////////////////////////
// CDataItem message handlers
//
int CDataItem::Draw( CDC* pDC, CPoint ptStart, int n ) 
{
    TEXTMETRIC tm ;
    VARIANT va ;
    VariantInit( &va ) ;
    
    if (m_pDataObject)
    {
        COLINFO* rgColInfo ;
        int nCols ;
        CString strTitle ;
  
        // Use the document (CDataObject) defined font for our
        // rendering.
        //
        CFont   font ;
        CFont*  pOldFont = m_pDataObject->SelectDocFont(pDC, font);
        pDC->GetTextMetrics( &tm ) ;

        RECT rc ;                             
        rc.left = ptStart.x ;
        rc.top = ptStart.y ;
        rc.bottom = ptStart.y + tm.tmHeight ;
        rc.right = rc.left ;
        
        // Use the column info to see how wide we are
        //
        rgColInfo = m_pDataObject->GetDataColInfo( &nCols, strTitle) ;
        rc.right += rgColInfo[0].uiWidth ;

        CProperty* pProp ;
        n = 0 ;
        POSITION pos ;
        for ( pos = m_pValueProps->m_lstProps.GetHeadPosition() ; pos != NULL ; n++)
        {
            rc.right += rgColInfo[n].uiWidth ;
            pProp = (CProperty*)m_pValueProps->m_lstProps.GetNext( pos ) ;
            ASSERT(pProp) ;
            if (SUCCEEDED(VariantChangeType( &va, &pProp->m_varValue, 0, VT_BSTR)))
            {
                CColumnListBox::JustifiedTextOut( pDC, rc.left+2, rc.top,  
                                   rc, va.bstrVal, 0, rgColInfo[n].uiFormatFlags ) ;
                VariantClear( &va ) ;
            }
            else
            {
                CColumnListBox::JustifiedTextOut( pDC, rc.left+2, rc.top,  
                                   rc, "", 0, rgColInfo[n].uiFormatFlags ) ;
            }
            rc.left += rgColInfo[n].uiWidth ;
        }
        if (pOldFont != NULL)
            pDC->SelectObject(pOldFont);
    }
    else
        pDC->GetTextMetrics( &tm ) ;
    
    return tm.tmHeight ;
}

void CDataItem::CalcDisplaySize( CDC* pDC, CSize& sizeItem ) 
{  
    TEXTMETRIC tm ;

    if (m_pDataObject) 
    {
        CFont   font ;
        CFont*  pOldFont = m_pDataObject->SelectDocFont(pDC, font);
        pDC->GetTextMetrics( &tm ) ;
        sizeItem.cx = m_pDataObject->GetWidth( pDC ) ;
        if (pOldFont != NULL)
            pDC->SelectObject(pOldFont);
    }
    else 
    {
        pDC->GetTextMetrics( &tm ) ;
        sizeItem.cx = 10 ;
    }
    sizeItem.cy = tm.tmHeight ;
}

// This is called whenever something else in XRTFrame thinks a 
// property should notify it's link clients that it is changed.
// by doing this, we can optimize how XRTFrame works when there
// are tons of Properties linked into containers
//
void CDataItem::NotifyLinks()
{
    if (m_pServerItem)
        m_pServerItem->NotifyChanged() ;
}

/////////////////////////////////////////////////////////////////////////////
// CDataItem  Automation methods/properties
//

// Set props = dataitem.Properties
//
VARIANT CDataItem::GetProperties( const VARIANT FAR& item ) 
{
    // BUGFIX: 9/29/94 cek 
    // Changed .Properties from DISP_PROPERTY_EX to DISP_PROPERTY_PARAM
    // so that req.Properties("Last") works.
    //
    VARIANT va;
    VariantInit(&va) ;

    ASSERT(m_pValueProps) ;
    if (m_pValueProps == NULL || !m_pValueProps->IsKindOf(RUNTIME_CLASS(CProperties)))
    {
        // TODO:  raise exception
        va.vt = VT_DISPATCH ;
        va.pdispVal = NULL ;
        return va ;
    }    

    if (item.vt == VT_ERROR ||item.vt == VT_EMPTY ) // no index
    {
        va.vt = VT_DISPATCH ;
        va.pdispVal = m_pValueProps->GetIDispatch(TRUE) ;
        return va;
    }
    else
    {
        va.vt = VT_DISPATCH ;
        va.pdispVal = m_pValueProps->Item( item ) ;
        return va ;
    }
}

// dataitem.Copy
//
// Copies this data item to the clipboard, making the OLE 2.0 link
// formats available.
// (non WOSA/XRT method)
//
void CDataItem::Copy()
{
    // get a server item suitable to generate the clipboard data
    if (m_pServerItem == NULL)
        m_pServerItem = new CDataItemServerItem(m_pDataObject, this);

    ASSERT_VALID(m_pServerItem); 
    m_pServerItem->CopyToClipboard(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CDataItemServerItem
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// COleServerItem derived class that allows CDataItems to support linking
//
CDataItemServerItem::CDataItemServerItem(CDataObject* pContainerDoc, CDataItem* pDataItem) :
    COleServerItem(pContainerDoc, TRUE) 
{
    // need to attach this server item to the node in the document
    ASSERT_VALID(pDataItem);
    m_pDataItem = pDataItem;
    pDataItem->m_pServerItem = this;
    CProperty*  pProp = (CProperty*)pDataItem->m_pValueProps->m_lstProps.GetHead() ;

    if (pProp->m_varValue.vt == VT_BSTR)
    {
        BSTR    bstr ;
        bstr = SysAllocStringLen( NULL, SysStringLen(pProp->m_varValue.bstrVal) + 1 ) ;
        wsprintf( bstr, "%s", (LPCSTR)pProp->m_varValue.bstrVal ) ;
        SetItemName( bstr );
        SysFreeString(bstr) ;
    }
    else
    {
        char sz[32] ;  wsprintf( sz, "DataItem%lu", m_pDataItem->m_dwID ) ;
        SetItemName( sz );    
    }

    // support CF_TEXT format
    GetDataSource()->DelayRenderFileData(CF_TEXT);    
}

CDataItemServerItem::~CDataItemServerItem()
{
    if (m_pDataItem != NULL)
    {
        m_pDataItem->m_pServerItem = NULL ;
    }
}

// We override OnGetClipboardData so that we can prevent it from putting
// the "embedding" clipboard formats (CF_EMBEDDEDOBJECT and CF_OBJECTDESCRIPTOR)
// on the clipboard.  The default impelementation calls 
// COleServerItem::GetClipboardData.  
//
COleDataSource* CDataItemServerItem::OnGetClipboardData(BOOL bIncludeLink,
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

// OnOpen is called when the user double clicks on a link item in a
// container.  Our implementation here calls into the view
// and tells it what item to select in the DataItem list box.
//
void CDataItemServerItem::OnOpen()
{
    if (IsLinkedItem() && m_pDataItem != NULL)
    {
        // for linked items, try to select this DataItem
        // in the DataObject
        //
        CDataObject* pDoc = GetDocument();
        ASSERT(pDoc != NULL);
        POSITION pos = pDoc->GetFirstViewPosition();
        ASSERT(pos != NULL);
        CDataObjectView* pView = (CDataObjectView*)pDoc->GetNextView(pos);
        
        // There may be more than one view on a document...
        //
        while (pos != NULL && !pView->IsKindOf(RUNTIME_CLASS(CDataObjectView)))
        {
            pView = (CDataObjectView*)pDoc->GetNextView(pos);
        }
        ASSERT(pView) ;
        ASSERT(pView->IsKindOf(RUNTIME_CLASS(CDataObjectView)));
        
        pView->SetSelection(m_pDataItem);
    }
    
    COleServerItem::OnOpen();
}

void CDataItemServerItem::Serialize(CArchive& ar)
{
    // CDataItems cant can't be embedded so there's nothing to
    // serialize.
}

BOOL CDataItemServerItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
    // Most applications, like this one, only handle drawing the content
    //  aspect of the item.  If you wish to support other aspects, such
    //  as DVASPECT_THUMBNAIL (by overriding OnDrawEx), then this
    //  implementation of OnGetExtent should be modified to handle the
    //  additional aspect(s).

    if (dwDrawAspect != DVASPECT_CONTENT)
        return COleServerItem::OnGetExtent(dwDrawAspect, rSize);

    // CDataItemServerItem::OnGetExtent is called to get the extent in
    //  HIMETRIC units of the entire item.  
    rSize = CSize(0, 0);
    CClientDC dc(NULL);
    dc.SetMapMode(MM_ANISOTROPIC);

    ASSERT_VALID(m_pDataItem);
    m_pDataItem->CalcDisplaySize(&dc, rSize);

    dc.LPtoHIMETRIC(&rSize); // convert pixels to HIMETRIC

    return TRUE;
}

BOOL CDataItemServerItem::OnDraw(CDC* pDC, CSize& rSize)
{

    // determine extent of this item in the document
    CPoint ptStart(0,0) ;
    rSize = CSize(0, 0);
    m_pDataItem->CalcDisplaySize(pDC, rSize);

    // prepare to draw and remember the extent in himetric units
    pDC->SetWindowOrg(0, 0);
    pDC->SetWindowExt(rSize);
    pDC->SetViewportExt(rSize);  // Note: only affects the m_hAttribDC

    pDC->LPtoHIMETRIC(&rSize);   // convert pixels to HIMETRIC

    m_pDataItem->Draw(pDC, ptStart) ;
    return TRUE;
}

// Support of CF_TEXT is handled here
//
BOOL CDataItemServerItem::OnRenderFileData(LPFORMATETC lpFormatEtc, CFile* pFile)
{
    ASSERT(lpFormatEtc != NULL);
    if (lpFormatEtc->cfFormat != CF_TEXT)
        return COleServerItem::OnRenderFileData(lpFormatEtc, pFile);

    BOOL bResult = FALSE;
    if (m_pDataItem != NULL)
    {
        TRY
        {
            // save as text
            CArchive ar(pFile, CArchive::store);
            m_pDataItem->SaveAsText(ar);
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
// CDataItemServerItem::XBugFixDataObject
BEGIN_INTERFACE_MAP(CDataItemServerItem, COleServerItem)
    INTERFACE_PART(CDataItemServerItem, IID_IDataObject, BugFixDataObject)
END_INTERFACE_MAP()

STDMETHODIMP_(ULONG) CDataItemServerItem::XBugFixDataObject::AddRef()
{
    METHOD_PROLOGUE(CDataItemServerItem, BugFixDataObject)
    return (ULONG)pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CDataItemServerItem::XBugFixDataObject::Release()
{
    METHOD_PROLOGUE(CDataItemServerItem, BugFixDataObject)
    return (ULONG)pThis->ExternalRelease();
}

STDMETHODIMP CDataItemServerItem::XBugFixDataObject::QueryInterface(
    REFIID iid, LPVOID far* ppvObj)
{
    METHOD_PROLOGUE(CDataItemServerItem, BugFixDataObject)
    return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CDataItemServerItem::XBugFixDataObject::GetData(
    LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium)
{
    METHOD_PROLOGUE(CDataItemServerItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    //TRACE( "GetData:  cfFormat == %d\r\n", lpFormatEtc->cfFormat ) ;
    return pThis->m_xDataObject.GetData(lpFormatEtc, lpStgMedium);
}


STDMETHODIMP CDataItemServerItem::XBugFixDataObject::GetDataHere(
    LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium)
{
    METHOD_PROLOGUE(CDataItemServerItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    //TRACE( "GetDataHere:  cfFormat == %d\r\n", lpFormatEtc->cfFormat ) ;
    return pThis->m_xDataObject.GetDataHere(lpFormatEtc, lpStgMedium);
}

STDMETHODIMP CDataItemServerItem::XBugFixDataObject::QueryGetData(LPFORMATETC lpFormatEtc)
{
    METHOD_PROLOGUE(CDataItemServerItem, BugFixDataObject)
    ASSERT_VALID(pThis);

//    TRACE( "QueryGetData:  cfFormat == %d\r\n", lpFormatEtc->cfFormat ) ;

    return pThis->m_xDataObject.QueryGetData(lpFormatEtc);
}

STDMETHODIMP CDataItemServerItem::XBugFixDataObject::GetCanonicalFormatEtc(
    LPFORMATETC lpFormatEtcIn, LPFORMATETC lpFormatEtcOut)
{
    // because we support the target-device (ptd) for server metafile format,
    //  all members of the FORMATETC are significant.

    //TRACE( "GetCanonicalFormatEtc:  In.cfFormat == %d, Out.cfFormat == %d\r\n", lpFormatEtcIn->cfFormat, lpFormatEtcIn->cfFormat ) ;
    return ResultFromScode(DATA_S_SAMEFORMATETC);
}

STDMETHODIMP CDataItemServerItem::XBugFixDataObject::SetData(
    LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium, BOOL fRelease)
{
    METHOD_PROLOGUE(CDataItemServerItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    //TRACE( "SetData:  cfFormat == %d\r\n", lpFormatEtc->cfFormat ) ;
    return pThis->m_xDataObject.SetData( lpFormatEtc, lpStgMedium, fRelease);
}

STDMETHODIMP CDataItemServerItem::XBugFixDataObject::EnumFormatEtc(
    DWORD dwDirection, LPENUMFORMATETC FAR* ppenumFormatEtc)
{
    METHOD_PROLOGUE(CDataItemServerItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    return pThis->m_xDataObject.EnumFormatEtc( dwDirection, ppenumFormatEtc);
}

STDMETHODIMP CDataItemServerItem::XBugFixDataObject::DAdvise(
    FORMATETC FAR* pFormatetc, DWORD advf,
    LPADVISESINK pAdvSink, DWORD FAR* pdwConnection)
{
    METHOD_PROLOGUE(CDataItemServerItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    //TRACE( "DAdvise:  cfFormat == %d, advf = %d\r\n", pFormatetc->cfFormat, advf ) ;

    if (pFormatetc->cfFormat != 0 && FAILED(pThis->m_xDataObject.QueryGetData(pFormatetc)))
    {
        *pdwConnection = 0 ;
        return ResultFromScode( DATA_E_FORMATETC ) ;
    }
    
    return pThis->m_xDataObject.DAdvise(pFormatetc, advf, pAdvSink, pdwConnection);
}

STDMETHODIMP CDataItemServerItem::XBugFixDataObject::DUnadvise(DWORD dwConnection)
{
    METHOD_PROLOGUE(CDataItemServerItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    return pThis->m_xDataObject.DUnadvise( dwConnection ) ;
}

STDMETHODIMP CDataItemServerItem::XBugFixDataObject::EnumDAdvise(
    LPENUMSTATDATA FAR* ppenumAdvise)
{
    METHOD_PROLOGUE(CDataItemServerItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    return pThis->m_xDataObject.EnumDAdvise( ppenumAdvise ) ;
}

#endif // BUGFIX


/////////////////////////////////////////////////////////////////////////////
// CDataItemServerItem diagnostics

#ifdef _DEBUG
void CDataItemServerItem::AssertValid() const
{
    COleServerItem::AssertValid();
}

void CDataItemServerItem::Dump(CDumpContext& dc) const
{
    COleServerItem::Dump(dc);
}
#endif

