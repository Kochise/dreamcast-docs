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
// srvritem.cpp : implementation of the CDataObject/RequestServerItem classes
//
// CDataObjectSvrItem implementation  
// Revisions:
//  December 8, 1993   cek     First implementation.
//
// CDataObjectSvrItem is the COleServerItem derived class that handles
// CDataObject objects.  CDataItem and CProperty server items are 
// implemented in dataitem.* and property.* respectively.
//      
#include "stdafx.h"
#include <afxpriv.h>    // for CSharedFile
#include "windowsx.h"
#include "xrtframe.h"

#include "doc.h"
#include "view.h"
#include "srvritem.h"
#include "dataitem.h"
#include "request.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDataObjectSvrItem, COleServerItem)
#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////

CDataObjectSvrItem::CDataObjectSvrItem(CDataObject* pContainerDoc)
    : COleServerItem(pContainerDoc, TRUE)
{
    ASSERT(GetDocument()->m_cfPrivate != NULL);

    // We support rendering in both CF_TEXT and "WOSA/XRT (Market Data)"
    // per the WOSA/XRT specification
    //
    GetDataSource()->DelayRenderData( CF_TEXT ) ;
    GetDataSource()->DelayRenderData( GetDocument()->m_cfPrivate ) ;
    
    pContainerDoc->m_pServerItem = this ;

    // BUGBUG!:  Excel 5.0 doesn't seem to like monikers that do not 
    // have at least one character in them...
    //
    SetItemName("DataItems");     
    
    m_fInSendOnDataChange = FALSE ;
}

CDataObjectSvrItem::~CDataObjectSvrItem()
{
    GetDocument()->m_pServerItem = NULL ;
}

void CDataObjectSvrItem::Serialize(CArchive& ar)
{
    CDataObject* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    pDoc->Serialize(ar);
}

BOOL CDataObjectSvrItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
    // Most applications, like this one, only handle drawing the content
    //  aspect of the item.  If you wish to support other aspects, such
    //  as DVASPECT_THUMBNAIL (by overriding OnDrawEx), then this
    //  implementation of OnGetExtent should be modified to handle the
    //  additional aspect(s).

    if (dwDrawAspect != DVASPECT_CONTENT)
        return COleServerItem::OnGetExtent(dwDrawAspect, rSize);

    // CDataObjectSvrItem::OnGetExtent is called to get the extent in
    //  HIMETRIC units of the entire item.  The default implementation
    //  here simply returns a hard-coded number of units.

    CDataObject* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    rSize = CSize(0, 0);
    CClientDC dc(NULL);
    dc.SetMapMode(MM_ANISOTROPIC);

    pDoc->CalcDisplaySize(&dc, rSize, IsLinkedItem());

    dc.LPtoHIMETRIC(&rSize); // convert pixels to HIMETRIC

    return TRUE;
}

BOOL CDataObjectSvrItem::OnDraw(CDC* pDC, CSize& rSize)
{
    CDataObject* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    // determine extent of this item in the document
    CPoint ptStart(0,0) ;
    rSize = CSize(0, 0);
    pDoc->CalcDisplaySize(pDC, rSize, IsLinkedItem());

    // prepare to draw and remember the extent in himetric units
    pDC->SetWindowOrg(0, 0);
    pDC->SetWindowExt(rSize);
    pDC->SetViewportExt(rSize);  // Note: only affects the m_hAttribDC

    pDC->LPtoHIMETRIC(&rSize);   // convert pixels to HIMETRIC

    pDoc->Draw(pDC, ptStart, IsLinkedItem()) ;
    return TRUE;
}
 
// BUGFIX: 9/14/94 CEK
// Added override of OnUpdate to be smarter about sending IAdviseSink::OnDataChange
// notifications.   In short, we check our hints here and only send the
// entire data set when needed.
//
void CDataObjectSvrItem::OnUpdate(COleServerItem* /*pSender*/,
	LPARAM lHint, CObject* pHint, DVASPECT nDrawAspect)
{

    if (lHint == UPDATE_ALL || 
        lHint == UPDATE_TIMEOUT || 
        lHint == UPDATE_ADDREQUEST || 
        lHint == UPDATE_CHANGEREQUEST || 
        lHint == UPDATE_REMOVEREQUEST)
    {
    	// the default implementation always notifies the container, regardless
	    //  of the specific hint or sender.
    	NotifyChanged(nDrawAspect);
    }
}


// COleServerItem has 3 overridables for rendering to an IDataObject
// stgmedium:
//    BOOL OnRenderData( LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium )
//    BOOL OnRenderGlobalData( LPFORMATETC lpFormatEtc, HGLOBAL* phGlobal ) 
//    BOOL OnRenderFileData( LPFORMATETC lpFormatEtc, CFile* pFile )
//
// OnRenderData is called first.  Then, depending on the tymed, and whether
// it does anything, it calls OnRenderGlobalData.   If OnRenderGlobalData
// returns FALSE, OnRenderData then builds a memory based CFile and
// tries OnRenderFileData.
//
// We override OnRenderGlobalData and use the passed HGLOBAL to render
// the "Market Data (WOSA/XRT)" clipboard data when the data stream
// needs to be generated from scratch (i.e. IDataObject::GetData was called
// because of a 'real' GetData call.  OnRenderFile data is used when
// ::GetData was called by our IDataAdviseHolder implementation as part of
// IAdviseSink::OnDataChange notifications.
//
// Note: Possible performance enhancement:
//      From the time that the client (either a container or
//      the IDataAdviseHolder::SendOnDataChange) calls IDataObject::GetData until
//      OnRenderGlobalData below is called there are about 6 layers in between.
//      In otherwords, we are significantly abstracted from the actuall 
//      IDataObject::GetData implementation way down in the COleServerDoc class
//      (which our CDataObject is derived from).
//
//      The possible performance enhancement would be to hook out the 
//      CDataObject::XDataObject::GetData implementation and check for
//      lpFormatEtc->tymed == TYMED_HGLOBAL && lpFormatEtc->cfFormat == pDoc->m_cfPrivate
//      and in that case call pDoc->RenderToGlobal, else call the base
//      implementation.   This would reduce the # of functions called to 
//      render this data from 6 or 7 to 1.
//
BOOL CDataObjectSvrItem::OnRenderGlobalData(LPFORMATETC lpFormatEtc, HGLOBAL* phGlobal)
{
    ASSERT(lpFormatEtc != NULL);
    CDataObject* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    ASSERT(GetDocument()->m_cfPrivate != NULL);
                                                     
    if (lpFormatEtc->cfFormat == pDoc->m_cfPrivate)
    {
        BOOL f = FALSE ;
        if (m_fInSendOnDataChange == FALSE)
        {
            // Force rendering of entire data set
            //
            f = pDoc->RenderToGlobal( phGlobal ) ;
        }
        else if  (pDoc->m_pXRTData)
        {
            if (*phGlobal == NULL)
            {   
                *phGlobal = GlobalAlloc( GHND, pDoc->m_pXRTData->cbStream ) ;
                LPMARKETDATA p = (LPMARKETDATA)GlobalLock( *phGlobal ) ;
                memcpy( p, pDoc->m_pXRTData, (UINT)pDoc->m_pXRTData->cbStream ) ;
                GlobalUnlock( *phGlobal ) ;
                f = TRUE ;
            }
        }
        return f ;
    }
    else
    {
        return COleServerItem::OnRenderGlobalData( lpFormatEtc, phGlobal ) ;
    }
}
 
// OnRenderFileData is called whenever the DataObject is being rendered
// via Uniform Data Transfer.  We support CF_TEXT and the WOSA/XRT
// clipboard format.
//
static char BASED_CODE szCRLF[] = "\r\n";
BOOL CDataObjectSvrItem::OnRenderFileData(LPFORMATETC lpFormatEtc, CFile* pFile)
{
    ASSERT(lpFormatEtc != NULL);
    
    CDataObject* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    ASSERT(GetDocument()->m_cfPrivate != NULL);

    BOOL bResult = FALSE;

    if (lpFormatEtc->cfFormat == CF_TEXT)
    {
        // Render as CF_TEXT 
        //
        if (pDoc->m_lstDataItems.IsEmpty() == FALSE)
        {
            TRY
            {
                // save as text
                CArchive ar(pFile, CArchive::store);
                
                POSITION pos ;
                CDataItem* pItem ;
                for( pos = pDoc->m_lstDataItems.GetHeadPosition(); pos != NULL; )
                {
                    pItem = (CDataItem*)pDoc->m_lstDataItems.GetNext( pos ) ;
                    if (pItem)
                    {
                        pItem->SaveAsText(ar, pDoc->m_fIncludeNamesOnClipboard );
                        
                        if (pos != NULL)
                            ar.Write(szCRLF, sizeof(szCRLF)-1);
                    }
                }
                ar << (BYTE)'\0';   // terminate with NUL character
                bResult = TRUE;
            }
            END_TRY
        }
        else
        {
            // QUESTION:  What does it mean to have an empty DataItem
            // list?  Does it mean the ::GetData call should return
            // E_FORMATETC?  Or should the call succeed, but the buffer
            // be 'empty'?
            //
            // For now we choose 'fail'...
            bResult = FALSE ;
        }
    }
/*    
    else if (lpFormatEtc->cfFormat == pDoc->m_cfPrivate)
    {
        // Render using the WOSA/XRT clipboard format
        //
        // OnRenderGlobalData (above) is used to render the entire
        // data set.   This implementation just copies what
        // we have so far...
        //
        if (m_fInSendOnDataChange == TRUE)
        {
            // Render just data that has changed since
            // last time.  We do this by simply copying our buffer
            // that is generated on each timer tick
            //
            if (pDoc->m_pXRTData != NULL)
            {
                TRY
                {
                    CArchive ar(pFile, CArchive::store);
                    // BUGBUG:  limited to 64K of data.
                    #ifdef _DEBUG
                    TRACE("Rendering Update Data Only (%d Items)...\r\n", pDoc->m_cItems ) ;
                    #endif
                    ar.Write(pDoc->m_pXRTData, (int)pDoc->m_pXRTData->cbStream) ;
                    TRACE("----Done Rendering Update Data Only...\r\n") ;
                    bResult = TRUE;
                }
                END_TRY
            }
        }
    }
*/    
    else
        return COleServerItem::OnRenderFileData(lpFormatEtc, pFile);
        
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
// CDataObjectSvrItem::XBugFixDataObject
BEGIN_INTERFACE_MAP(CDataObjectSvrItem, COleServerItem)
    INTERFACE_PART(CDataObjectSvrItem, IID_IDataObject, BugFixDataObject)
END_INTERFACE_MAP()

STDMETHODIMP_(ULONG) CDataObjectSvrItem::XBugFixDataObject::AddRef()
{
    METHOD_PROLOGUE(CDataObjectSvrItem, BugFixDataObject)
    return (ULONG)pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CDataObjectSvrItem::XBugFixDataObject::Release()
{
    METHOD_PROLOGUE(CDataObjectSvrItem, BugFixDataObject)
    return (ULONG)pThis->ExternalRelease();
}

STDMETHODIMP CDataObjectSvrItem::XBugFixDataObject::QueryInterface(
    REFIID iid, LPVOID far* ppvObj)
{
    METHOD_PROLOGUE(CDataObjectSvrItem, BugFixDataObject)
    return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CDataObjectSvrItem::XBugFixDataObject::GetData(
    LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium)
{
    METHOD_PROLOGUE(CDataObjectSvrItem, BugFixDataObject)
    ASSERT_VALID(pThis);

//    TRACE( "GetData:  cfFormat == %d\r\n", lpFormatEtc->cfFormat ) ;
    return pThis->m_xDataObject.GetData(lpFormatEtc, lpStgMedium);
}


STDMETHODIMP CDataObjectSvrItem::XBugFixDataObject::GetDataHere(
    LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium)
{
    METHOD_PROLOGUE(CDataObjectSvrItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    //( "GetDataHere:  cfFormat == %d\r\n", lpFormatEtc->cfFormat ) ;
    return pThis->m_xDataObject.GetDataHere(lpFormatEtc, lpStgMedium);
}

STDMETHODIMP CDataObjectSvrItem::XBugFixDataObject::QueryGetData(LPFORMATETC lpFormatEtc)
{
    METHOD_PROLOGUE(CDataObjectSvrItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    //( "QueryGetData:  cfFormat == %d\r\n", lpFormatEtc->cfFormat ) ;

    return pThis->m_xDataObject.QueryGetData(lpFormatEtc);
}

STDMETHODIMP CDataObjectSvrItem::XBugFixDataObject::GetCanonicalFormatEtc(
    LPFORMATETC lpFormatEtcIn, LPFORMATETC lpFormatEtcOut)
{
    // because we support the target-device (ptd) for server metafile format,
    //  all members of the FORMATETC are significant.

    //( "GetCanonicalFormatEtc:  In.cfFormat == %d, Out.cfFormat == %d\r\n", lpFormatEtcIn->cfFormat, lpFormatEtcIn->cfFormat ) ;
    return ResultFromScode(DATA_S_SAMEFORMATETC);
}

STDMETHODIMP CDataObjectSvrItem::XBugFixDataObject::SetData(
    LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium, BOOL fRelease)
{
    METHOD_PROLOGUE(CDataObjectSvrItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    //( "SetData:  cfFormat == %d\r\n", lpFormatEtc->cfFormat ) ;
    return pThis->m_xDataObject.SetData( lpFormatEtc, lpStgMedium, fRelease);
}

STDMETHODIMP CDataObjectSvrItem::XBugFixDataObject::EnumFormatEtc(
    DWORD dwDirection, LPENUMFORMATETC FAR* ppenumFormatEtc)
{
    METHOD_PROLOGUE(CDataObjectSvrItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    return pThis->m_xDataObject.EnumFormatEtc( dwDirection, ppenumFormatEtc);
}

STDMETHODIMP CDataObjectSvrItem::XBugFixDataObject::DAdvise(
    FORMATETC FAR* pFormatetc, DWORD advf,
    LPADVISESINK pAdvSink, DWORD FAR* pdwConnection)
{
    METHOD_PROLOGUE(CDataObjectSvrItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    //( "DAdvise:  cfFormat == %d, advf = %d\r\n", pFormatetc->cfFormat, advf ) ;

    if (pFormatetc->cfFormat != 0 && FAILED(pThis->m_xDataObject.QueryGetData(pFormatetc)))
    {
        *pdwConnection = 0 ;
        return ResultFromScode( DATA_E_FORMATETC ) ;
    }
    
    return pThis->m_xDataObject.DAdvise(pFormatetc, advf, pAdvSink, pdwConnection);
}

STDMETHODIMP CDataObjectSvrItem::XBugFixDataObject::DUnadvise(DWORD dwConnection)
{
    METHOD_PROLOGUE(CDataObjectSvrItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    return pThis->m_xDataObject.DUnadvise( dwConnection ) ;
}

STDMETHODIMP CDataObjectSvrItem::XBugFixDataObject::EnumDAdvise(
    LPENUMSTATDATA FAR* ppenumAdvise)
{
    METHOD_PROLOGUE(CDataObjectSvrItem, BugFixDataObject)
    ASSERT_VALID(pThis);

    return pThis->m_xDataObject.EnumDAdvise( ppenumAdvise ) ;
}

#endif // BUGFIX
  
/////////////////////////////////////////////////////////////////////////////
// CDataObjectSvrItem diagnostics

#ifdef _DEBUG
void CDataObjectSvrItem::AssertValid() const
{
    COleServerItem::AssertValid();
}

void CDataObjectSvrItem::Dump(CDumpContext& dc) const
{
    COleServerItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
