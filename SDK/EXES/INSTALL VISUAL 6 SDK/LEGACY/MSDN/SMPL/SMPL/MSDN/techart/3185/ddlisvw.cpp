// ddlisvw.cpp : implementation of the CDdlistView class
//

#include "stdafx.h"
#include "afxpriv.h" // for shared file
#include "ddlist.h"
#include "strlist.h"
#include "ddlisdoc.h"
#include "ddclip.h"
#include "ddlisvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDdlistView

IMPLEMENT_DYNCREATE(CDdlistView, CView)

BEGIN_MESSAGE_MAP(CDdlistView, CView)
    //{{AFX_MSG_MAP(CDdlistView)
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_SIZE()
    ON_WM_SETFOCUS()
    ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
    ON_COMMAND(ID_EDIT_COPY, OnEditCopy)                                 
    ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
    ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
    ON_REGISTERED_MESSAGE(ddcMsgQueryDrop, OnQueryDrop)
    ON_REGISTERED_MESSAGE(ddcMsgDoDrop, OnDoDrop)
    ON_REGISTERED_MESSAGE(ddcMsgBeginDragDrop, OnBeginDragDrop)
    //}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDdlistView construction/destruction

CDdlistView::CDdlistView()
{
    // TODO: add construction code here
}

CDdlistView::~CDdlistView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDdlistView drawing

void CDdlistView::OnDraw(CDC* pDC)
{
    CDdlistDoc* pDoc = GetDocument();

    // TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CDdlistView printing

BOOL CDdlistView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void CDdlistView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CDdlistView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}




/////////////////////////////////////////////////////////////////////////////
// CDdlistView diagnostics

#ifdef _DEBUG
void CDdlistView::AssertValid() const
{
    CView::AssertValid();
}

void CDdlistView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CDdlistDoc* CDdlistView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDdlistDoc)));
    return (CDdlistDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDdlistView message handlers

int CDdlistView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    // Create the list box
    m_wndList.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL
                      |LBS_MULTIPLESEL|LBS_NOINTEGRALHEIGHT
                      |LBS_DISABLENOSCROLL,
                     CRect(0,0,0,0),
                     this,
                     1);

    return 0;
}

void CDdlistView::OnDestroy()
{
    m_wndList.DestroyWindow();
    CView::OnDestroy();
}

void CDdlistView::OnSize(UINT nType, int cx, int cy)
{
    // Resize the listbox
    m_wndList.MoveWindow(0, 0, cx, cy);
}

void CDdlistView::OnSetFocus(CWnd* pOldWnd)
{
    // Set focus to the listbox
    m_wndList.SetFocus();
}

void CDdlistView::OnInitialUpdate()
{
    // Fill the list box from the doc
    CDdlistDoc* pDoc = GetDocument();
    POSITION pos = pDoc->m_StrList.GetHeadPosition();
    while(pos) {
        CString* pStr = pDoc->m_StrList.GetNext(pos);
        m_wndList.AddString(*pStr);
    }
}    

void CDdlistView::OnUpdate(CView* pView, LPARAM lHint, CObject* pObj)
{
    // Just empty the list box and rebuild the entire thing
    m_wndList.ResetContent();
    OnInitialUpdate();
}

void CDdlistView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
    // Enable copy if any items are selected
    int i = m_wndList.GetSelCount();
    pCmdUI->Enable(i > 0 ? TRUE : FALSE);
}

void CDdlistView::OnEditCopy()
{
    // Get the number of selected items
    int iCount = m_wndList.GetSelCount();
    ASSERT(iCount > 0);
    // get the list of selection ids
    int* pItems = new int [iCount];
    m_wndList.GetSelItems(iCount, pItems);
    // Create a string list
    CStrList StrList;
    // Add all the selected items to the list
    int i;
    for (i=0; i<iCount; i++) {
        CString* pStr = new CString;
        m_wndList.GetText(pItems[i], *pStr);
        StrList.AddTail(pStr);
    }
    // Done with item list
    delete pItems;
    SetClipboardObject(theApp.m_uiStrListClipFormat, &StrList);
    // Nuke the list
    StrList.DeleteAll();
}

void CDdlistView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
    // See if there is a string list available
    OpenClipboard();
    UINT uiFmt = 0;
    while (uiFmt = EnumClipboardFormats(uiFmt)) {
        if (uiFmt == theApp.m_uiStrListClipFormat) {
            CloseClipboard();
            pCmdUI->Enable(TRUE);
            return;
        }
    }
    pCmdUI->Enable(FALSE);
    CloseClipboard();    
}

void CDdlistView::OnEditPaste()
{
    CStrList PasteList;
    ::GetClipboardObject(this, theApp.m_uiStrListClipFormat, &PasteList);

    // Add all the strings to the doc
    CDdlistDoc* pDoc = GetDocument();
    ASSERT(pDoc);
    CStrList* pStrList = &pDoc->m_StrList;
    ASSERT(pStrList);
    POSITION pos = NULL;
    // Use the data in the list to update the current info
    while (! PasteList.IsEmpty()) {
        CString* pStr = PasteList.RemoveHead();
        ASSERT(pStr);
        pStrList->AddTail(pStr);
    }
    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL);
}

LRESULT CDdlistView::OnQueryDrop(WPARAM wParam,LPARAM lParam)
{
    // wParam has the format
    if (wParam == theApp.m_uiStrListClipFormat) {
        return TRUE;
    }
    return FALSE;
}

LRESULT CDdlistView::OnDoDrop(WPARAM wParam, LPARAM lParam)
{
    // wParam has the format
    // we only accept one format so check that's what we got
    ASSERT(wParam == theApp.m_uiStrListClipFormat);
    // Create an object to receive the data
    CStrList PasteList;
    ::GetDropData(&PasteList);

    // Add all the strings to the doc
    CDdlistDoc* pDoc = GetDocument();
    ASSERT(pDoc);
    CStrList* pStrList = &pDoc->m_StrList;
    ASSERT(pStrList);
    POSITION pos = NULL;
    // Use the data in the list to update the current info
    while (! PasteList.IsEmpty()) {
        CString* pStr = PasteList.RemoveHead();
        ASSERT(pStr);
        pStrList->AddTail(pStr);
    }
    GetParentFrame()->SetActiveView(this); // make this the active child
    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL);
    return 0;
}

LRESULT CDdlistView::OnBeginDragDrop(WPARAM wParam,LPARAM lParam)
{
    // wParam is child window ID
    // lParam is pointer to the window object

    // Construct a drag and drop object from our data
    // Get the number of selected items
    int iCount = m_wndList.GetSelCount();
    if (iCount <= 0) return 0; // nothing to drag
    // get the list of selection ids
    int* pItems = new int [iCount];
    m_wndList.GetSelItems(iCount, pItems);
    // Create a string list
    CStrList StrList;
    // Add all the selected items to the list
    int i;
    for (i=0; i<iCount; i++) {
        CString* pStr = new CString;
        m_wndList.GetText(pItems[i], *pStr);
        StrList.AddTail(pStr);
    }
    // Done with item list
    delete pItems;
    ::BeginDragDrop((CWnd*)lParam, // source window
                    theApp.m_uiStrListClipFormat, // format
                    &StrList); // object
    // Nuke the list
    StrList.DeleteAll();
    return 0;
}

