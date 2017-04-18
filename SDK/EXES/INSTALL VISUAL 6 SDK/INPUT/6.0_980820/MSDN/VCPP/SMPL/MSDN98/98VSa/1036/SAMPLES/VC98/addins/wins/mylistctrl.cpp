// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MyListCtrl.h"
#include "fileitem.h"
#include "winsapp.h"
#include "windowslist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int  PIXEL_PAD = 20;

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl

CMyListCtrl::CMyListCtrl()
{
	m_cCols = 0;
	m_pfnSort = NULL;

	m_pfnLCClick = NULL;
	m_pfnLCColClick = NULL;
	m_pfnLCDblClick = NULL;
}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers

void CMyListCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLISTVIEW* pNMListView = (NMLISTVIEW*)pNMHDR;
	struct SortInfo si;

	si.iColumn = pNMListView->iSubItem;
	si.pList = this;

	*pResult = 0;
	if (m_pfnLCColClick)
	{
		m_pfnLCColClick(pNMHDR, pResult, m_lParamColClick, &si);
	}
	if (m_pfnSort && pNMListView)
	{
		SortItems(m_pfnSort, (LPARAM)&si);
	}
}

void CMyListCtrl::DoSort(int iCol)
{
	struct SortInfo si;

	si.iColumn = iCol + 1; 
	si.pList = this;

	SortItems(m_pfnSort, (LPARAM)&si);
}

void CMyListCtrl::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	if (m_pfnLCClick)
	{
		m_pfnLCClick(pNMHDR, pResult, m_lParamClick);
	}
}

int CMyListCtrl::InsertItem(int nItem, LPCTSTR lpszItem, LPARAM lItemData)
{
	int iRes;
	iRes = CListCtrl::InsertItem(nItem, lpszItem);
	SetItemData(nItem, lItemData);
	return(iRes);
}


	
int CMyListCtrl::GetCurrentIndex()
{
    // Get the current mouse location and convert it to client
    // coordinates.
    DWORD pos = GetMessagePos();
    CPoint pt(LOWORD(pos), HIWORD(pos));
    ScreenToClient(&pt);

    // Get indexes of the first and last visible items in listview
    // control.
    int index = GetTopIndex();
    int last_visible_index = index + GetCountPerPage();
    if (last_visible_index > GetItemCount())
        last_visible_index = GetItemCount();

    // Loop until number visible items has been reached.
    while (index <= last_visible_index)
    {
        // Get the bounding rectangle of an item. If the mouse
        // location is within the bounding rectangle of the item,
        // you know you have found the item that was being clicked.
        CRect r;
        GetItemRect(index, &r, LVIR_BOUNDS);
        if (r.PtInRect(pt))
        {
            UINT flag = LVIS_SELECTED | LVIS_FOCUSED;
            SetItemState(index, flag, flag);
            break;
        }

        // Get the next item in listview control.
        index++;
    }
	return(index);
}


void CMyListCtrl::SetWidths()
{
	int cCols = GetColumnCount();
	int *pWidths = new int[cCols];
	int i, j, iWidth;
	CString strItem;

	for (j = cCols-1; j >= 0; j--)
	{
		pWidths[j] = 0;
	}
	if (pWidths)
	{
		i = GetItemCount()-1;
		for (;i >= 0; i--)
		{
			for (j = cCols-1; j >= 0; j--)
			{
				GetItemText(i, j, strItem.GetBuffer(_MAX_PATH), _MAX_PATH);
				strItem.ReleaseBuffer();
				iWidth = GetStringWidth(strItem) + PIXEL_PAD;
				if (pWidths[j] < iWidth)
				{
					pWidths[j] = iWidth;
				}
			}
		}
		for (j = cCols-1; j >= 0; j--)
		{
			iWidth = GetColumnWidth(j);
			if (iWidth <= pWidths[j])
			{
				iWidth = pWidths[j];
			}
			SetColumnWidth(j, iWidth);
		}
		delete[] pWidths;
	}
}

int CMyListCtrl::InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
		int nFormat /*= LVCFMT_LEFT*/, int nWidth /*= -1*/, int nSubItem /* = -1*/)
{
	m_cCols++;
	int iWidth, iRes;

	iWidth = GetStringWidth(lpszColumnHeading) + PIXEL_PAD;
	if (nWidth != -1)
		iWidth = nWidth;
	iRes = CListCtrl::InsertColumn(nCol, lpszColumnHeading, nFormat, iWidth, nSubItem);
	SetColumnWidth(nCol, iWidth);

	return(iRes);
}

int CMyListCtrl::GetColumnCount()
{
	return(m_cCols);
}

void CMyListCtrl::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	if (m_pfnLCDblClick)
	{
		m_pfnLCDblClick(pNMHDR, pResult, m_lParamDblClick);
	}
}

void CMyListCtrl::SetSort(PFNLVCOMPARE pfnSort, LPARAM lParam)
{
	m_pfnSort = pfnSort;
	m_lParamSort = lParam;
}

void CMyListCtrl::SetOnClick(LPFNLCOP pfnLCOpHandler, LPARAM lParam)
{
	m_pfnLCClick = pfnLCOpHandler;
	m_lParamClick = lParam;
}

void CMyListCtrl::SetOnDblClick(LPFNLCOP pfnLCOpHandler, LPARAM lParam)
{
	m_pfnLCDblClick = pfnLCOpHandler;
	m_lParamDblClick = lParam;
}

void CMyListCtrl::SetColClick(LPFNLCSOP pfnLCOpHandler, LPARAM lParam)
{
	m_pfnLCColClick = pfnLCOpHandler;
	m_lParamColClick = lParam;
}


void CMyListCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
//	if (nChar == Del)
//	{
//	}
	CListCtrl::OnChar(nChar, nRepCnt, nFlags);
}
