// ddlstbox.cpp : implementation file
//

#include "stdafx.h"
#include "afxpriv.h"
#include "ddlstbox.h"
#include "ddclip.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDListBox

CDDListBox::CDDListBox()
{
    m_iFirstIndex = 0;
    m_bMouseOpPending = FALSE;
    m_bCaptured = FALSE;
}

CDDListBox::~CDDListBox()
{
}

BEGIN_MESSAGE_MAP(CDDListBox, CListBox)
    //{{AFX_MSG_MAP(CDDListBox)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_REGISTERED_MESSAGE(ddcMsgQueryDrop, OnQueryDrop)
    ON_REGISTERED_MESSAGE(ddcMsgDoDrop, OnDoDrop)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDListBox message handlers


void CDDListBox::OnLButtonDown(UINT nFlags, CPoint point)
{
    // Get the index value of the item under the mouse
    int iSel = IndexFromPoint(point);
    // If no item was hit, there is nothing to do
    if (iSel == LB_ERR) return;
    SetCapture();
    m_bCaptured = TRUE;
    // Save the position the mouse is in
    m_ptMouseDown = point;
    // if the item is already selected, defer the operation until the 
    // mouse button goes up since this might be the start of a drag op.
    if (GetSel(iSel)) {
        m_bMouseOpPending = TRUE;
    } else {
        m_bMouseOpPending = FALSE;
        UpdateSelection(iSel, nFlags, point);
    }
}

void CDDListBox::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (m_bCaptured) {
        // See if a mouse op is pending
        if (m_bMouseOpPending == TRUE) {
            int iSel = IndexFromPoint(point);
            if (iSel != LB_ERR) {
                UpdateSelection(iSel, nFlags, point);
            }
        }
        m_bMouseOpPending = FALSE;
        ReleaseCapture();
        m_bCaptured = FALSE;
    }
}

void CDDListBox::UpdateSelection(int iSel, UINT nFlags, CPoint point)
{
    DWORD dwStyle = GetStyle();
    if (dwStyle & (LBS_MULTIPLESEL | LBS_EXTENDEDSEL)) {
        if (nFlags & MK_CONTROL) {
            // Toggle the selection of this item
            SetSel(iSel, !GetSel(iSel));
        } else if (nFlags & MK_SHIFT) {
            // Deselect all items except this one
            SelItemRange(FALSE, 0, GetCount()-1);
            // Select all the items from the first to this one
            SelItemRange(TRUE,
                         min(m_iFirstIndex, iSel),
                         max(m_iFirstIndex, iSel));
        } else {
            // Deselect all items except this one
            SelItemRange(FALSE, 0, GetCount()-1);
            SetSel(iSel, TRUE);
            // Save this item index as the first of a possible range
            m_iFirstIndex = iSel; 
        }
    } else {
        // Select this one
        SetCurSel(iSel);
    }
}

void CDDListBox::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_bCaptured) {
        // See if the mouse has moved far enough to start
        // a drag operation
        if ((abs(point.x - m_ptMouseDown.x) > 3)
        || (abs(point.y - m_ptMouseDown.y) > 3)) {
            // release the mouse capture
            ReleaseCapture();
            m_bCaptured = FALSE;
            // Tell the parent window to begin a drag and drop op.
            GetParent()->PostMessage(ddcMsgBeginDragDrop, 
                                     (WPARAM) GetDlgCtrlID(),
                                     (LPARAM) this);
        }
    }
}

int CDDListBox::IndexFromPoint(CPoint point)
{
    int iTop = GetTopIndex();
    if (iTop == LB_ERR) {
        return LB_ERR; // no items to select
    }

    DWORD dwStyle = GetStyle();
    // Make sure it isn't multi-column
    ASSERT(! (dwStyle & LBS_MULTICOLUMN)); 
    // make sure all the items are the same height
    ASSERT(! (dwStyle & LBS_OWNERDRAWVARIABLE));
    int iHeight = GetItemHeight(0);
    int iSel = iTop + (point.y / iHeight);
    if (iSel >= GetCount()) {
        return LB_ERR;
    }
    return iSel;
}

LRESULT CDDListBox::OnQueryDrop(WPARAM wParam,LPARAM lParam)
{
    return GetParent()->SendMessage(ddcMsgQueryDrop,
                                    wParam, lParam);
}

LRESULT CDDListBox::OnDoDrop(WPARAM wParam,LPARAM lParam)
{
    return GetParent()->SendMessage(ddcMsgDoDrop,
                                    wParam, lParam);
}

