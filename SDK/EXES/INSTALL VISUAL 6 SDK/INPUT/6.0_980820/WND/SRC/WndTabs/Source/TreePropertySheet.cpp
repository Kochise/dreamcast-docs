/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// TreePropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "TreePropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CPropertySheet CHHPropSheet

// margins
const int MARGIN_X =       6;       // between tree and pages
const int MARGIN_T =       4;       // between tree and top of dialog
const int MARGIN_B =       12;      // on bottom

const int DEF_TREE_WIDTH = 156;

// pixels taken up by tab control's internal frame
const int TAB_CTRL_FRAME_WIDTH = 6;

// misc
const int WM_RESYNCTREE = (WM_USER + 10);
const int CTRL_ID       = 999;
const int MAX_LEVELS    = 20;


/////////////////////////////////////////////////////////////////////////////
// CXTabCtrl window

class CXTabCtrl : public CTabCtrl
{
// Construction
public:
    CXTabCtrl() {};

protected:
    afx_msg void OnChangeSel(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()
};



// helper function
static HTREEITEM GetNextItemInTree(CTreeCtrl& treeCtrl, HTREEITEM item)
{
    HTREEITEM retval;

    if (item == NULL)
        return NULL;

    // try going down
    if (retval = treeCtrl.GetChildItem(item))
    {
        return retval;
    }

    // try sibling
    if (retval = treeCtrl.GetNextSiblingItem(item))
    {
        return retval;
    }

    // try going up
    item = treeCtrl.GetParentItem(item);
    while (item)
    {
        if (retval = treeCtrl.GetNextSiblingItem(item))
        {
            return retval;
        }
        item = treeCtrl.GetParentItem(item);
    }

    // no more items
    return NULL;
}



/////////////////////////////////////////////////////////////////////////////
// CTreePropertySheet

IMPLEMENT_DYNAMIC(CTreePropertySheet, CPropertySheet)

CTreePropertySheet::CTreePropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
    :CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
    CommonInit();
}

CTreePropertySheet::CTreePropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
    :CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
    CommonInit();
}

void CTreePropertySheet::CommonInit()
{
    m_pTabCtrl = new CXTabCtrl();
    m_iTreeWidth = DEF_TREE_WIDTH;
    m_bChangingPages = false;
    m_iSel = -1;
}

CTreePropertySheet::~CTreePropertySheet()
{
    delete m_pTabCtrl;
}


BEGIN_MESSAGE_MAP(CTreePropertySheet, CPropertySheet)
    //{{AFX_MSG_MAP(CTreePropertySheet)
    ON_WM_DESTROY()
    //}}AFX_MSG_MAP
//  ON_MESSAGE(PSM_SETCURSEL, OnSetActivePage)
    ON_NOTIFY(TVN_SELCHANGEDW, CTRL_ID, OnSelChangedW)
    ON_NOTIFY(TVN_SELCHANGEDA, CTRL_ID, OnSelChangedA)
    ON_MESSAGE(WM_RESYNCTREE, OnResyncTree)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreePropertySheet message handlers

BOOL CTreePropertySheet::OnInitDialog() 
{
    EnableStackedTabs(FALSE);
    BOOL bResult = CPropertySheet::OnInitDialog();

    char buf[1024];
    CSize szMaxPage(0, 0);
    CRect r, rectTabCtrl, rectPagesOld;
    int i, iLevel, iLastLevel = 1, iBottom = 0;
    int iActivePage = GetActiveIndex();
    CString sName;
    HTREEITEM levelItems[MAX_LEVELS];

    CRect rectWnd;
    GetWindowRect(rectWnd);
    
    m_pTabCtrl->SubclassWindow(GetDlgItem(AFX_IDC_TAB_CONTROL)->m_hWnd);
    m_pTabCtrl->GetClientRect(rectTabCtrl);
    r = rectTabCtrl;
    m_pTabCtrl->ClientToScreen(r);
    ScreenToClient(r);

    const CPoint ptTabCtrlMargin = r.TopLeft();

    m_TreeCtrl.Create(WS_VISIBLE | WS_CHILDWINDOW | WS_TABSTOP |
        TVS_SHOWSELALWAYS | TVS_LINESATROOT | TVS_HASLINES | TVS_HASBUTTONS, 
        CRect(0, 0, 1, 1), this, CTRL_ID);
    m_TreeCtrl.ModifyStyleEx(0, WS_EX_CLIENTEDGE);

    for (i = 0; i < GetPageCount(); i++)
    {
        SetActivePage(i);
        const CPropertyPage *pPage = GetPage(i);
        pPage->GetClientRect(r);
        if (i == 0)
        {
            rectPagesOld = r;
            pPage->ClientToScreen(rectPagesOld);
        }
        if (r.Height() > szMaxPage.cy) szMaxPage.cy = r.Height();
        if (r.Width () > szMaxPage.cx) szMaxPage.cx = r.Width();

        pPage->GetWindowText(sName);
        // Start modification by yole@yole.ru: 
        // To handle characters >128 correctly, an explicit cast to 
        // unsigned char is needed
        if (isdigit((unsigned char) sName[0]))
        {
            const char *p = ((LPCTSTR)sName) + 1;
            while (isdigit((unsigned char) *p)) p++;
            int len = p - (LPCTSTR)sName;
            // End modification by yole@yole.ru
            iLevel = atoi(sName.Left(len));
            sName = sName.Mid(len);
            ASSERT(iLevel >= 1);
            --iLevel;
            ASSERT(iLevel < MAX_LEVELS);
            ASSERT(iLevel <= (iLastLevel + 1));
        }
        else
        {
            iLevel = 0;
        }
        
        levelItems[iLevel] = m_TreeCtrl.InsertItem(TVIF_TEXT | TVIF_PARAM, 
            sName, 0, 0, 0, 0, i, 
            iLevel > 0? levelItems[iLevel - 1] : TVI_ROOT, 
            TVI_LAST);
        iLastLevel = iLevel;
    }

    SetActivePage(iActivePage);

    m_rectTreeCtrl = CRect(
        ptTabCtrlMargin.x, 
        MARGIN_T, 
        ptTabCtrlMargin.x + m_iTreeWidth, 
        MARGIN_T + szMaxPage.cy);

    CWnd *pWnd = GetTopWindow();
    while (pWnd)
    {
        ::GetClassName(pWnd->m_hWnd, buf, sizeof(buf) - 1);
        if (strcmp(buf, "Button") != 0)
        {
            pWnd->ShowWindow(SW_HIDE);
        }
        else
        {
            pWnd->GetWindowRect(r);
            ScreenToClient(r);
            const iDiffY = 
                (m_rectTreeCtrl.bottom + MARGIN_B - r.top);
            iBottom = (rectWnd.Height() + iDiffY);
            r.OffsetRect(
                m_iTreeWidth + MARGIN_X - TAB_CTRL_FRAME_WIDTH, 
                iDiffY);
            pWnd->MoveWindow(r, FALSE);
        }
        pWnd = pWnd->GetNextWindow();
    }

    SetWindowPos(NULL, 0, 0,
        rectWnd.Width() + m_iTreeWidth + MARGIN_X - TAB_CTRL_FRAME_WIDTH,
        iBottom,
        SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

    m_TreeCtrl.MoveWindow(m_rectTreeCtrl);
    m_TreeCtrl.ShowWindow(SW_SHOW);

    GetClientRect(rectWnd);
    m_SepLine.Create(NULL, WS_VISIBLE | WS_CHILD | SS_BLACKFRAME | SS_SUNKEN,
        CRect(4, 
              m_rectTreeCtrl.bottom + (MARGIN_B / 2), 
              rectWnd.Width() - 4, 
              m_rectTreeCtrl.bottom + (MARGIN_B / 2) + 2),
        this);

    m_rectPages.left   = m_rectTreeCtrl.right + MARGIN_X;
    m_rectPages.top    = MARGIN_T;
    m_rectPages.right  = m_rectPages.left + szMaxPage.cx;
    m_rectPages.bottom = MARGIN_T + szMaxPage.cy;

    r = m_rectPages;
    ClientToScreen(r);
    CPoint ptDiff(m_rectTreeCtrl.right + MARGIN_X, MARGIN_T);
    ClientToScreen(&ptDiff);
    ptDiff -= rectPagesOld.TopLeft();
    ptDiff += ptTabCtrlMargin;
    rectTabCtrl.OffsetRect(ptDiff);
    m_pTabCtrl->MoveWindow(rectTabCtrl);

    UpdateTreeFromConfig();

    CenterWindow();

    PostMessage(WM_RESYNCTREE);
    
    return bResult;
}

LRESULT CTreePropertySheet::OnResyncTree(WPARAM wParam, LPARAM lParam)
{
    const int iNewIndex = GetActiveIndex();
    HTREEITEM hItem = m_TreeCtrl.GetRootItem();
    int i = iNewIndex;
    while (i--)
    {
        hItem = GetNextItemInTree(m_TreeCtrl, hItem);
    }
    m_TreeCtrl.Select(hItem, TVGN_CARET);
    m_TreeCtrl.EnsureVisible(hItem);
    m_TreeCtrl.SetFocus();

    return 1;
}

void CTreePropertySheet::OnSelChangedW(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEWW *pnmtv = (NM_TREEVIEWW *)pNMHDR;
    SetActivePage(pnmtv->itemNew.lParam);
    *pResult = 1;
}

void CTreePropertySheet::OnSelChangedA(NMHDR* pNMHDR, LRESULT* pResult)
{
    NM_TREEVIEWA *pnmtv = (NM_TREEVIEWA *)pNMHDR;
    SetActivePage(pnmtv->itemNew.lParam);
}

void CTreePropertySheet::OnDestroy() 
{
    m_sTreeCfg = GetTreeConfig();
    CPropertySheet::OnDestroy();
}

/////////////////////////////////////////////////////////////////////////////
// CTreePropertySheet operations

CString CTreePropertySheet::GetTreeConfig()
{
    if (m_TreeCtrl.GetSafeHwnd())
    {
        CString sTreeCfg;
        CString s;
        
        HTREEITEM hItem = m_TreeCtrl.GetRootItem();
        while (hItem)
        {
            s= m_TreeCtrl.GetItemText(hItem);
            if (m_TreeCtrl.GetItemState(hItem, TVIS_EXPANDED) & TVIS_EXPANDED)
            {
                sTreeCfg += "1";
            }
            else
            {
                sTreeCfg += "0";
            }
            hItem = GetNextItemInTree(m_TreeCtrl, hItem);
        }

        return sTreeCfg;
    }

    return m_sTreeCfg;
}

void CTreePropertySheet::SetTreeConfig(LPCTSTR pszTreeCfg)
{
    m_sTreeCfg = pszTreeCfg;
    if (m_TreeCtrl.GetSafeHwnd())
    {
        UpdateTreeFromConfig();
    }
}

void CTreePropertySheet::UpdateTreeFromConfig()
{
    LPCTSTR p = (LPCTSTR)m_sTreeCfg;
    HTREEITEM hItem = m_TreeCtrl.GetRootItem();

    while (hItem  &&  *p)
    {
        if (*p == '1')
        {
            m_TreeCtrl.Expand(hItem, TVE_EXPAND);
        }
        hItem = GetNextItemInTree(m_TreeCtrl, hItem);
        ++p;
    }
    m_sTreeCfg.Empty();
}


/////////////////////////////////////////////////////////////////////////////
// CXTabCtrl

BEGIN_MESSAGE_MAP(CXTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CXTabCtrl)
	//}}AFX_MSG_MAP
    ON_MESSAGE(TCM_SETCURSEL, OnChangeSel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXTabCtrl message handlers

void CXTabCtrl::OnChangeSel(WPARAM iItem, LPARAM)
{
    Default();
    GetParent()->PostMessage(WM_RESYNCTREE);
}
