// clipvw.cpp : implementation of the CClipView class
//

#include "stdafx.h"
#include "afxpriv.h" // for CSharedFile
#include "transbmp.h" // for CTransBmp
#include "mfcclip.h"
#include "myobj.h"
#include "myoblist.h"

#include "clipdoc.h"
#include "clipvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClipView

IMPLEMENT_DYNCREATE(CClipView, CView)

BEGIN_MESSAGE_MAP(CClipView, CView)
    //{{AFX_MSG_MAP(CClipView)
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_DRAWITEM()
    ON_WM_MEASUREITEM()
    ON_WM_SIZE()
    ON_WM_SETFOCUS()
    ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
    ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
    ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
    ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
    ON_UPDATE_COMMAND_UI(ID_EDIT_DEL, OnUpdateEditDel)
    ON_COMMAND(ID_EDIT_DEL, OnEditDel)
    ON_COMMAND(ID_EDIT_ADD, OnEditAdd)
    ON_CONTROL(LBN_DBLCLK, IDC_MYLIST, OnListBoxDblClick)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipView construction/destruction

CClipView::CClipView()
{
    // Load the font we want to use
    m_font.CreateStockObject(ANSI_FIXED_FONT);
    // Get the metrics of the font
    CDC dc;
    dc.CreateCompatibleDC(NULL);
    CFont* pfntOld = (CFont*) dc.SelectObject(&m_font);
    TEXTMETRIC tm;
    dc.GetTextMetrics(&tm);
    dc.SelectObject(pfntOld);
    m_iFontHeight = tm.tmHeight;
    m_iFontWidth = tm.tmMaxCharWidth;
    // Load the bitmap we want
    m_bmSmile.LoadBitmap(IDB_SMILE);
}

CClipView::~CClipView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CClipView drawing

void CClipView::OnDraw(CDC* pDC)
{
    // Nothing to do here - all done by the listbox
}



/////////////////////////////////////////////////////////////////////////////
// CClipView diagnostics

#ifdef _DEBUG
void CClipView::AssertValid() const
{
    CView::AssertValid();
}

void CClipView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CClipDoc* CClipView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClipDoc)));
    return (CClipDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClipView message handlers

int CClipView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    CRect rc;
    GetClientRect(&rc);
    // adjust the client are to make the list box look better
    rc.bottom -= 2;
    m_wndList.Create(WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL
                       | LBS_DISABLENOSCROLL | LBS_OWNERDRAWFIXED
                       | LBS_EXTENDEDSEL | LBS_NOINTEGRALHEIGHT
                       | LBS_NOTIFY,
                       rc,
                       this,
                       IDC_MYLIST);
    return 0;
}

void CClipView::OnInitialUpdate()
{
    // Get a pointer to the list of objects in the doc
    CClipDoc* pDoc = GetDocument();
    CMyObList* pObList = pDoc->GetObList();
    ASSERT(pObList);
    // Reset the listbox
    m_wndList.ResetContent();
    // Fill the listbox from the object list
    POSITION pos = pObList->GetHeadPosition();
    while (pos) {
        CMyObj* pObj =  pObList->GetNext(pos);
        m_wndList.AddString((char*) pObj);
    }
}

void CClipView::OnUpdate(CView* pView, LPARAM lHint, CObject* pHint)
{
    // Be lazy and just redo the entire thing
    OnInitialUpdate(); 
}

void CClipView::OnDestroy()
{
    CView::OnDestroy();
    // Be sure to destroy the window we created
    m_wndList.DestroyWindow();
}

void CClipView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT pDI)
{
    CMyObj* pObj;
    HFONT hfntOld;
    CRect rcText;
    switch (pDI->itemAction) {
    case ODA_DRAWENTIRE:
        // Draw the whole line of information
        // Get a pointer to the object
        pObj = (CMyObj*) pDI->itemData;
        ASSERT(pObj);
        ASSERT(pObj->IsKindOf(RUNTIME_CLASS(CMyObj)));
        // Set up the font we want to use
        hfntOld = (HFONT) ::SelectObject(pDI->hDC, m_font.m_hObject);
        rcText = pDI->rcItem;
        // Erase the entire area
        ::ExtTextOut(pDI->hDC, 
                     rcText.left, rcText.top,
                     ETO_OPAQUE,
                     &rcText,
                     "", 0,
                     NULL);
 
        // Draw the bitmap in place
        m_bmSmile.DrawTrans(pDI->hDC, rcText.left, rcText.top);

        // Move the text over to just beyond the bitmap
        rcText.left = pDI->rcItem.left + m_bmSmile.GetWidth() + 2;
        ::DrawText(pDI->hDC,
                   pObj->GetText(),
                   -1,
                   &rcText,
                   DT_LEFT | DT_VCENTER);

        // Check if we need to show selection state
        if (pDI->itemState & ODS_SELECTED) {
            ::InvertRect(pDI->hDC, &(pDI->rcItem));
        }
        // Check if we need to show focus state
        if (pDI->itemState & ODS_FOCUS) {
            ::DrawFocusRect(pDI->hDC, &(pDI->rcItem));
        }
        ::SelectObject(pDI->hDC, hfntOld);
        break;

    case ODA_FOCUS:
        // Toggle the focus state
        ::DrawFocusRect(pDI->hDC, &(pDI->rcItem));
        break;

    case ODA_SELECT:
        // Toggle the selection state
        ::InvertRect(pDI->hDC, &(pDI->rcItem));
        break;
    default:
        break;
    }
}

void CClipView::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
    // Return the height of the font or the bitmap, 
    // whichever is greater
    lpMeasureItemStruct->itemHeight = max(m_iFontHeight,
                                          m_bmSmile.GetHeight());
}

void CClipView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);
    // Resize the listbox the fit in the entire client area
    m_wndList.SetWindowPos(NULL, 
                           0, 0,
                           cx, cy-2,
                           SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);
}

void CClipView::OnSetFocus(CWnd* pOldWnd)
{
    // Set focus to the listbox
    m_wndList.SetFocus();
}

void CClipView::OnListBoxDblClick()
{
    // Find what was clicked
    int i = m_wndList.GetSelCount();
    // Get the first selected item
    int iSel = LB_ERR;
    m_wndList.GetSelItems(1, &iSel);
    ASSERT(iSel != LB_ERR);
    CMyObj* pObj = (CMyObj*) m_wndList.GetItemData(iSel);
    ASSERT(pObj);
    ASSERT(pObj->IsKindOf(RUNTIME_CLASS(CMyObj)));
    if (pObj->DoEditDialog() == IDOK) {
        CClipDoc* pDoc = GetDocument();
        pDoc->SetModifiedFlag();
        pDoc->UpdateAllViews(NULL);
    }
}

void CClipView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
    int i = m_wndList.GetSelCount();
    pCmdUI->Enable(i > 0 ? TRUE : FALSE);
}

void CClipView::OnEditCopy()
{
    // Get the number of selected items
    int iCount = m_wndList.GetSelCount();
    ASSERT(iCount > 0);
    // get the list of selection ids
    int* pItems = new int [iCount];
    m_wndList.GetSelItems(iCount, pItems);
    // Create a list
    CMyObList ObList;
    // Add all the items to the list
    int i;
    CMyObj* pObj;
    for (i=0; i<iCount; i++) {
        pObj = (CMyObj*) m_wndList.GetItemData(pItems[i]);
        ObList.Append(pObj);
    }
    // Done with the item list
    delete pItems;
    // Create a memory file based archive
    CSharedFile mf (GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);
    CArchive ar(&mf, CArchive::store);  
    ObList.Serialize(ar);
    ar.Close(); // flush and close
    HGLOBAL hMem = mf.Detach();
    if (!hMem) return;
    // Nuke the list but not the objects
    ObList.RemoveAll();
    // Send the clipboard the data
    OpenClipboard();
    EmptyClipboard();
    SetClipboardData(theApp.m_uiMyListClipFormat, hMem);
    CloseClipboard();
}

void CClipView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
    // See if there is a list available
    OpenClipboard();
    UINT uiFmt = 0;
    while (uiFmt = EnumClipboardFormats(uiFmt)) {
        if (uiFmt == theApp.m_uiMyListClipFormat) {
            CloseClipboard();
            pCmdUI->Enable(TRUE);
            return;
        }
    }
    pCmdUI->Enable(FALSE);
    CloseClipboard();    
}

void CClipView::OnEditPaste()
{
    OpenClipboard();
    HGLOBAL hMem = ::GetClipboardData(theApp.m_uiMyListClipFormat);
    if (!hMem) {
        CloseClipboard();
        return;
    }
    // Create a mem file
    CSharedFile mf;
    mf.SetHandle(hMem);
    // Create the archive and get the data
    CArchive ar(&mf, CArchive::load);  
    CMyObList PasteList;
    PasteList.Serialize(ar);
    ar.Close();
    mf.Detach();
    CloseClipboard();

    // Add all the objects to the doc
    CClipDoc* pDoc = GetDocument();
    ASSERT(pDoc);
    CMyObList* pObList = pDoc->GetObList();
    ASSERT(pObList);
    ASSERT(pObList->IsKindOf(RUNTIME_CLASS(CMyObList)));
    POSITION pos = NULL;
    // Remove each of the CMyObj objects from the paste list
    // and append them to the list
    while (! PasteList.IsEmpty()) {
        CMyObj* pObj =  PasteList.RemoveHead();
        ASSERT(pObj);
        ASSERT(pObj->IsKindOf(RUNTIME_CLASS(CMyObj)));
        pObList->Append(pObj);
    }
    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL);
}


void CClipView::OnUpdateEditDel(CCmdUI* pCmdUI)
{
    int i = m_wndList.GetSelCount();
    pCmdUI->Enable(i > 0 ? TRUE : FALSE);
}

void CClipView::OnEditDel()
{
    // Delete any currently selected items
    int iCount = m_wndList.GetSelCount();
    if((iCount != LB_ERR) && (iCount > 0)) {
        CClipDoc* pDoc = GetDocument();
        ASSERT(pDoc);
        CMyObList* pObList = pDoc->GetObList();
        ASSERT(pObList);
        ASSERT(pObList->IsKindOf(RUNTIME_CLASS(CMyObList)));
        // get the list of selection ids
        int* pItems = new int [iCount];
        m_wndList.GetSelItems(iCount, pItems);
        // Delete all the items
        for (int i=0; i<iCount; i++) {
            CMyObj* pObj 
                = (CMyObj*) m_wndList.GetItemData(pItems[i]);
            pObList->Remove(pObj);
            delete pObj;
        }
        delete pItems;
        pDoc->SetModifiedFlag();
        pDoc->UpdateAllViews(NULL);
    }
}

void CClipView::OnEditAdd()
{
    CMyObj* pOb = new CMyObj;
    if (pOb->DoEditDialog() == IDOK) {
        CClipDoc* pDoc = GetDocument();
        ASSERT(pDoc);
        CMyObList* pList = pDoc->GetObList();
        ASSERT(pList);
        pList->Append(pOb);
        pDoc->SetModifiedFlag();
        pDoc->UpdateAllViews(NULL);
    }
}
