// DlgWinMgr.cpp : implementation file
//

#include "stdafx.h"
#include <afxdlgs.h>
#include "resource.h"
#include <ObjModel\addguid.h>
#include <ObjModel\appguid.h>
#include <ObjModel\bldguid.h>
#include <ObjModel\textguid.h>
#include <ObjModel\dbgguid.h>

#include "DlgWinMgr.h"
#include "windowslist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWinMgr dialog
static _TCHAR BASED_CODE szFilter[] = _T("Named File Lists (*.nfl)|*.nfl|All Files (*.*)|*.*||");

CDlgWinMgr::CDlgWinMgr(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWinMgr::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWinMgr)
	m_fAutoDir = FALSE;
	m_fAutoSize = FALSE;
	m_fAutoVis = FALSE;
	//}}AFX_DATA_INIT
	m_pdirList = NULL;
	m_iSortedCol = 0;
}


void CDlgWinMgr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWinMgr)
	DDX_Control(pDX, IDC_BUTTONSELECTALL, m_ctlSelectAll);
	DDX_Control(pDX, IDC_BUTTONREFRESH, m_ctlRefresh);
	DDX_Control(pDX, IDC_BUTTONOPEN, m_ctlOpen);
	DDX_Control(pDX, IDC_BUTTONMAKELIST, m_ctlMakeList);
	DDX_Control(pDX, IDC_BUTTONLOADLIST, m_ctlLoad);
	DDX_Control(pDX, IDC_BUTTONINVERTSEL, m_ctlInvert);
	DDX_Control(pDX, IDC_BUTTONCLOSE, m_ctlClose);
	DDX_Control(pDX, IDC_LIST, m_ctlListWinMgr);
	DDX_Check(pDX, IDC_CHK_AUTODIR, m_fAutoDir);
	DDX_Check(pDX, IDC_CHK_AUTOSIZE, m_fAutoSize);
	DDX_Check(pDX, IDC_CHK_AUTOVIS, m_fAutoVis);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWinMgr, CDialog)
	//{{AFX_MSG_MAP(CDlgWinMgr)
	ON_BN_CLICKED(IDC_BUTTONCLOSE, OnButtonclose)
	ON_BN_CLICKED(IDC_BUTTONINVERTSEL, OnButtoninvertsel)
	ON_BN_CLICKED(IDC_BUTTONOPEN, OnButtonopen)
	ON_BN_CLICKED(IDC_BUTTONSELECTALL, OnButtonselectall)
	ON_BN_CLICKED(IDC_BUTTONMAKELIST, OnButtonmakelist)
	ON_BN_CLICKED(IDC_BUTTONLOADLIST, OnButtonloadlist)
	ON_BN_CLICKED(IDC_BUTTONREFRESH, OnButtonrefresh)
	ON_BN_CLICKED(IDC_BUTTONMINWINS, OnButtonminwins)
	ON_BN_CLICKED(IDC_BUTTONCLEAR, OnButtonclear)
	ON_MESSAGE(WM_NOTIFY, OnNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//	ON_NOTIFY( wNotifyCode, id, OnNotify ) can't use because there is no id associated with a tooltip

/////////////////////////////////////////////////////////////////////////////
// CDlgWinMgr message handlers

BOOL CDlgWinMgr::OnInitDialog() 
{
	CDialog::OnInitDialog();
	_ASSERTE(sizeof(long) == sizeof(CDlgWinMgr*));
	CString strColTitle;

	UpdateData(FALSE);

	m_ctlListWinMgr.SetOnClick((LPFNLCOP)OnListClick, (LPARAM)this);
	m_ctlListWinMgr.SetOnDblClick((LPFNLCOP)OnListDblClick, (LPARAM)this);
	m_ctlListWinMgr.SetSort((PFNLVCOMPARE)MySort, (LPARAM)this);
	m_ctlListWinMgr.SetColClick((LPFNLCSOP)OnColClick, (LPARAM)this);

	strColTitle.LoadString(IDS_COL_FILENAME);
	m_ctlListWinMgr.InsertColumn(COL_FILENAME, strColTitle);
	strColTitle.LoadString(IDS_COL_TIME);
	m_ctlListWinMgr.InsertColumn(COL_TIME, strColTitle);
	strColTitle.LoadString(IDS_COL_EXT);
	m_ctlListWinMgr.InsertColumn(COL_EXT, strColTitle);
	strColTitle.LoadString(IDS_COL_DIRNAME);
	m_ctlListWinMgr.InsertColumn(COL_DIRNAME, strColTitle);
	strColTitle.LoadString(IDS_COL_DEBUGSIZE);
	m_ctlListWinMgr.InsertColumn(COL_DEBUGSIZE, strColTitle);
	strColTitle.LoadString(IDS_COL_SIZE);
	m_ctlListWinMgr.InsertColumn(COL_SIZE, strColTitle);

	FillList();
	m_ctlListWinMgr.DoSort(m_iSortedCol);
	// CG: The following block was added by the ToolTips component.
	{
		// Create the ToolTip control.
		CToolInfo toolinfo;

		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);

		m_tooltip.AddTool(GetDlgItem(IDC_CHK_AUTOSIZE), IDS_TIPAUTOSIZE);
		m_tooltip.GetToolInfo(toolinfo, this, 0);
		toolinfo.lpszText = m_szToolTipBuffer;
		m_tooltip.SetToolInfo(&toolinfo);
		m_tooltip.AddTool(GetDlgItem(IDC_CHK_AUTODIR), IDS_TIPAUTODIR);
		m_tooltip.GetToolInfo(toolinfo, this, 0);
		toolinfo.lpszText = m_szToolTipBuffer;
		m_tooltip.SetToolInfo(&toolinfo);

		m_tooltip.GetToolInfo(toolinfo, this, IDC_CHK_AUTOSIZE);
		m_tooltip.GetToolInfo(toolinfo, this, 0);
		toolinfo.lpszText = m_szToolTipBuffer;
		m_tooltip.SetToolInfo(&toolinfo);

		m_tooltip.AddTool(GetDlgItem(IDC_CHK_AUTOVIS), IDS_TIPAUTOVIS);
		m_tooltip.GetToolInfo(toolinfo, this, 0);
		toolinfo.lpszText = m_szToolTipBuffer;
		m_tooltip.SetToolInfo(&toolinfo);

		m_tooltip.AddTool(GetDlgItem(IDC_LIST), IDS_TIPLIST);
		m_tooltip.GetToolInfo(toolinfo, this, 0);
		toolinfo.lpszText = m_szToolTipBuffer;
		m_tooltip.SetToolInfo(&toolinfo);

		m_tooltip.AddTool(GetDlgItem(IDC_BUTTONREFRESH), IDS_TIPREFRESH);
		m_tooltip.GetToolInfo(toolinfo, this, 0);
		toolinfo.lpszText = m_szToolTipBuffer;
		m_tooltip.SetToolInfo(&toolinfo);

		m_tooltip.AddTool(GetDlgItem(IDC_BUTTONCLEAR), IDS_TIPCLEAR);
		m_tooltip.GetToolInfo(toolinfo, this, 0);
		toolinfo.lpszText = m_szToolTipBuffer;
		m_tooltip.SetToolInfo(&toolinfo);

		m_tooltip.AddTool(GetDlgItem(IDC_BUTTONINVERTSEL), IDS_TIPINVERTSEL);
		m_tooltip.GetToolInfo(toolinfo, this, 0);
		toolinfo.lpszText = m_szToolTipBuffer;
		m_tooltip.SetToolInfo(&toolinfo);

		m_tooltip.AddTool(GetDlgItem(IDC_BUTTONSELECTALL), IDS_TIPSELECTALL);
		m_tooltip.GetToolInfo(toolinfo, this, 0);
		toolinfo.lpszText = m_szToolTipBuffer;
		m_tooltip.SetToolInfo(&toolinfo);

		m_tooltip.AddTool(GetDlgItem(IDC_BUTTONMAKELIST), IDS_TIPMAKELIST);
		m_tooltip.GetToolInfo(toolinfo, this, 0);
		toolinfo.lpszText = m_szToolTipBuffer;
		m_tooltip.SetToolInfo(&toolinfo);

		m_tooltip.AddTool(GetDlgItem(IDC_BUTTONLOADLIST), IDS_TIPLOADLIST);
		m_tooltip.GetToolInfo(toolinfo, this, 0);
		toolinfo.lpszText = m_szToolTipBuffer;
		m_tooltip.SetToolInfo(&toolinfo);

		m_tooltip.AddTool(GetDlgItem(IDC_BUTTONOPEN), IDS_TIPACTIVATE);
		m_tooltip.GetToolInfo(toolinfo, this, 0);
		toolinfo.lpszText = m_szToolTipBuffer;
		m_tooltip.SetToolInfo(&toolinfo);

		m_tooltip.AddTool(GetDlgItem(IDC_BUTTONMINWINS), IDS_TIPMINWINS);
		m_tooltip.GetToolInfo(toolinfo, this, 0);
		toolinfo.lpszText = m_szToolTipBuffer;
		m_tooltip.SetToolInfo(&toolinfo);

		m_tooltip.AddTool(GetDlgItem(IDC_BUTTONCLOSE), IDS_TIPCLOSE);
		m_tooltip.GetToolInfo(toolinfo, this, 0);
		toolinfo.lpszText = m_szToolTipBuffer;
		m_tooltip.SetToolInfo(&toolinfo);

		
		m_tooltip.SetMaxTipWidth(256);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgWinMgr::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		m_tooltip.RelayEvent(pMsg);
	}
	// CG: The following block was added by the ToolTips component.
	{
		// Let the ToolTip process this message.
		//m_tooltip.RelayEvent(pMsg);
	}
	return CDialog::PreTranslateMessage(pMsg);	// CG: This was added by the ToolTips component.
}

void CDlgWinMgr::SetDirList(CDirList* pList, CWindowsList *pWndList) // pWndList is a misnomer, but...
{
	m_pdirList = pList;
	m_pWndList = pWndList;
}

void CDlgWinMgr::OnButtonclose() 
{
	CString strDoc;
	POSITION p;
	int iItem;

	p = m_ctlListWinMgr.GetFirstSelectedItemPosition();
	while (p)
	{
		iItem = m_ctlListWinMgr.GetNextSelectedItem(p);
		strDoc = m_ctlListWinMgr.GetItemText(iItem, COL_DIRNAME);
		strDoc += _T('\\');
		strDoc += m_ctlListWinMgr.GetItemText(iItem, COL_FILENAME);
		m_pWndList->CloseDoc(strDoc);
	}
	
	
}

void CDlgWinMgr::OnButtoninvertsel() 
{
	int iItem = 0, iItemLast = 0;
	UINT state;
	
	if (m_ctlListWinMgr.GetItemCount() > 0)
	{
		while (iItem != -1)
		{
			state = m_ctlListWinMgr.GetItemState(iItem, LVIS_SELECTED);
			m_ctlListWinMgr.SetItemState(iItem, ~state, LVIS_SELECTED);
			iItem = m_ctlListWinMgr.GetNextItem(iItem, LVNI_BELOW );
			if (iItem == iItemLast)
				iItem = -1;
			iItemLast = iItem;
		}
	}
	SetButtonStates();
}

void CDlgWinMgr::OnButtonopen() 
{
	CString strDoc;
	POSITION p;
	int iItem;

	p = m_ctlListWinMgr.GetFirstSelectedItemPosition();
	while (p)
	{
		iItem = m_ctlListWinMgr.GetNextSelectedItem(p);
		strDoc = m_ctlListWinMgr.GetItemText(iItem, COL_DIRNAME);
		strDoc += _T('\\');
		strDoc += m_ctlListWinMgr.GetItemText(iItem, COL_FILENAME);
		m_pWndList->OpenDoc(strDoc);
	}
	
}

void CDlgWinMgr::OnButtonselectall() 
{
	int iItem = 0, iItemLast = 0;
	
	if (m_ctlListWinMgr.GetItemCount() > 0)
	{
		while (iItem != -1)
		{
			m_ctlListWinMgr.SetItemState(iItem, LVIS_SELECTED, LVIS_SELECTED);
			iItem = m_ctlListWinMgr.GetNextItem(iItem, LVNI_BELOW );
			if (iItem == iItemLast)
				iItem = -1;
			iItemLast = iItem;
		}
	}
	SetButtonStates();
}

/*
LIST ideas:
	The list idea is just barely implemented here. It would
	be more useful if you could search for lists, and each
	list could show a description as it was selected.

	Each file could also have comments.
	Each file SHOULD have a file position remembered.

*/
void CDlgWinMgr::OnButtonmakelist() 
{
	CStringList rgStr;
	CString strDoc, strInfo;
	POSITION p;
	CFileItem *pFileItem;
	CRect rectDbg, rect;
	int iItem;
	int iRes;

	p = m_ctlListWinMgr.GetFirstSelectedItemPosition();
	while (p)
	{
		iItem = m_ctlListWinMgr.GetNextSelectedItem(p);
		strDoc = m_ctlListWinMgr.GetItemText(iItem, COL_DIRNAME);
		strDoc += _T('\\');
		strDoc += m_ctlListWinMgr.GetItemText(iItem, COL_FILENAME);
		pFileItem = (CFileItem *)m_ctlListWinMgr.GetItemData(iItem);
		rectDbg = pFileItem->GetDbgRect();
		rect = pFileItem->GetRect();
		strInfo.Format(_T("%s*%d,%d,%d,%d | %d,%d,%d,%d"), strDoc, rect.top, rect.left, rect.bottom, rect.right,
					rectDbg.top, rectDbg.left, rectDbg.bottom, rectDbg.right);
		rgStr.AddTail(strDoc);
	}

	if (rgStr.GetCount() > 0)
	{
		CFile fileWndList;
		CFileDialog dlgFile(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

		iRes = dlgFile.DoModal();
		if (iRes == IDOK)
		{
			strDoc = dlgFile.GetFileName();
			if (strDoc.ReverseFind(_T('.')) == -1)
			{
				strDoc += _T(".nfl"); // add the missing extension
			}
			TRY
			{
				if (fileWndList.Open(strDoc, CFile::modeCreate | CFile::modeWrite))
				{
				CArchive ar( &fileWndList, CArchive::store);

				rgStr.Serialize(ar);
				}
			}
			CATCH(CFileException, e)
			{
				CString strMsg;
				CString strErr;
				e->GetErrorMessage(strErr.GetBuffer(_MAX_PATH), _MAX_PATH);
				strErr.ReleaseBuffer();
				strMsg.Format(_T("%s \n    %s"), strErr, strDoc);
				MessageBox(strMsg, _T("BOOKNOTE"), MB_OK);
			}
			END_CATCH
		}
	}
}

void CDlgWinMgr::OnButtonloadlist() 
{
	CFile fileWndList;
	CFileException exptFile;
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);
	CStringList rgStr;
	CString strDoc, strInfo;
	BOOL fOK = FALSE;
	int iRes, i;

	iRes = dlgFile.DoModal();
	if (iRes == IDOK)
	{
		strDoc = dlgFile.GetFileName();
		if (strDoc.ReverseFind(_T('.')) == -1)
		{
			strDoc += _T(".nfl"); // add the missing extension
		}
		TRY
		{
			fileWndList.Open(strDoc, CFile::modeRead, &exptFile);
			CArchive ar( &fileWndList, CArchive::load);

			rgStr.Serialize(ar);
			fOK = TRUE;
		}
		CATCH(CFileException, e)
		{
		}
		END_CATCH
	}
	
	if (fOK)
	{
		POSITION p;

		p = rgStr.GetHeadPosition();
		while (p)
		{
			strInfo = rgStr.GetNext(p);
			i = strInfo.ReverseFind(_T('*'));
			if (i < 0)
			{
				strDoc = strInfo; // Assume we didn't store any size info
			}
			else
			{
				strDoc = strInfo.Left(i);
			}
			if (!strDoc.IsEmpty())
			{
				CComPtr<IGenericDocument> pDoc;
				m_pWndList->OpenDoc(strDoc, &pDoc);
				if (pDoc)
				{
					CComPtr<IDispatch> pDispWnd;
					CComQIPtr<IGenericWindow, &IID_IGenericWindow> pWnd;

					pDoc->get_ActiveWindow(&pDispWnd);
					if (pDispWnd && i > 0)
					{
						pWnd = pDispWnd;
						pDispWnd = NULL;

						strInfo = strInfo.Mid(i+1);
						if (!strInfo.IsEmpty())
						{
							long t, l, b, r;
							i = strInfo.Find(_T(','));
							t = _ttol(strInfo);
							strInfo = strInfo.Mid(i+1);
							i = strInfo.Find(_T(','));
							l = _ttol(strInfo);
							strInfo = strInfo.Mid(i+1);
							i = strInfo.Find(_T(','));
							b = _ttol(strInfo);
							strInfo = strInfo.Mid(i+1);
							r = _ttol(strInfo);
							pWnd->put_Top(t);
							pWnd->put_Left(l);
							pWnd->put_Width(r - l);
							pWnd->put_Height(b - t);
						}
					}
				}
			}
		}
		OnButtonrefresh();
	}
}

void CDlgWinMgr::SetVars(BOOL fAutoVis, BOOL fAutoDir, BOOL fAutoSize, int iSortedCol, long lSize)
{
	m_fAutoDir = fAutoDir;
	m_fAutoSize = fAutoSize;
	m_fAutoVis = fAutoVis;
	m_iSortedCol = iSortedCol;
	m_lSize = lSize;
}

void CDlgWinMgr::GetVars(BOOL& fAutoVis, BOOL& fAutoDir, BOOL& fAutoSize, int& iSortedCol, long& lSize)
{
	fAutoDir = m_fAutoDir;
	fAutoSize = m_fAutoSize;
	fAutoVis = 	m_fAutoVis;
	iSortedCol = m_iSortedCol;
	lSize = m_lSize;
}

void CDlgWinMgr::OnButtonrefresh() 
{
	DoClear();
	m_pWndList->WorkspaceOpen();
	FillList();
}

int CDlgWinMgr::FillList()
{
	POSITION p;
	CFileItem *pFileItem;
	int i, j, ich;
	CTime timeFile;
	CString strTime, strFile, strRect;
	CRect rect;
	
	i = 0;
	m_ctlListWinMgr.DeleteAllItems();
	if (m_pdirList)
	{
		p = m_pdirList->GetHeadPosition();
		while (p)
		{
			pFileItem = m_pdirList->GetNextPos(p);
			strFile = pFileItem->GetFile();
			j = m_ctlListWinMgr.InsertItem(i, strFile, (LPARAM)pFileItem); // COL_FILENAME
			m_ctlListWinMgr.SetItemText(j, COL_DIRNAME, pFileItem->GetDir());
			timeFile = pFileItem->GetTime();
			strTime = timeFile.Format(_T("%I:%M:%S %p  %d/%m/%Y"));
			m_ctlListWinMgr.SetItemText(j, COL_TIME, strTime);
			ich = strFile.ReverseFind(_T('.'));
			if (ich > 0)
			{
				if (ich < strFile.GetLength())
					strFile = strFile.Mid(ich+1);
				else
					strFile.Empty();
			}
			m_ctlListWinMgr.SetItemText(j, COL_EXT, strFile);

			rect = pFileItem->GetRect();
			strRect.Format(_T("(%d, %d, %d, %d)"), rect.top, rect.left, rect.bottom, rect.right);
			m_ctlListWinMgr.SetItemText(j, COL_SIZE, strRect);

			rect = pFileItem->GetDbgRect();
			strRect.Format(_T("(%d, %d, %d, %d)"), rect.top, rect.left, rect.bottom, rect.right);
			m_ctlListWinMgr.SetItemText(j, COL_DEBUGSIZE, strRect);

			i++;
		}
	}
	m_ctlListWinMgr.SetWidths();
	SetButtonStates();
	return(i);
}

void CDlgWinMgr::SetButtonStates()
{
	int cItems;
	cItems = m_ctlListWinMgr.GetSelectedCount();
	if (cItems)
	{
		m_ctlOpen.EnableWindow(TRUE);
		m_ctlMakeList.EnableWindow(TRUE);
		m_ctlClose.EnableWindow(TRUE);
	}
	else
	{
		m_ctlOpen.EnableWindow(FALSE);
		m_ctlMakeList.EnableWindow(FALSE);
		m_ctlClose.EnableWindow(FALSE);
	}
}

void CDlgWinMgr::OnButtonminwins() 
{
	CString strDoc;
	POSITION p;
	int iItem;

	p = m_ctlListWinMgr.GetFirstSelectedItemPosition();
	while (p)
	{
		iItem = m_ctlListWinMgr.GetNextSelectedItem(p);
		strDoc = m_ctlListWinMgr.GetItemText(iItem, COL_DIRNAME);
		strDoc += _T('\\');
		strDoc += m_ctlListWinMgr.GetItemText(iItem, COL_FILENAME);
		m_pWndList->DoMinWin(strDoc);
	}
	
}



int CALLBACK CDlgWinMgr::MySort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	int iComp = 0;
	CString strOne, strTwo;
	CTime timeOne, timeTwo;
	struct SortInfo *psi;
	psi = (SortInfo *)lParamSort;
	CFileItem *pFIOne, *pFITwo;
	_ASSERTE(psi);

	/*
			The comparison function must return a negative value
			if the first item should precede the second, a positive 
			value if the first item should follow the second, or
			zero if the two items are equivalent.
	*/
	if (psi)
	{
		CMyListCtrl *pList;
		pList = psi->pList;
		int i;
		_ASSERTE(pList);

		iComp = 0;

		if (pList)
		{
			pFIOne = (CFileItem *)lParam1;
			pFITwo = (CFileItem *)lParam2;
			_ASSERTE(pFIOne && pFITwo);
			if (pFIOne && pFITwo)
			{
				switch(abs(psi->iColumn) - 1) // iColumn here is "1 based" so we don't get -0.
				{
				case COL_FILENAME:
					strOne = pFIOne->GetFile();
					strTwo = pFITwo->GetFile();
					iComp = strOne.CompareNoCase(strTwo);
					break;
				case COL_DIRNAME:
					strOne = pFIOne->GetDir();
					strTwo = pFITwo->GetDir();
					iComp = strOne.CompareNoCase(strTwo);
					break;
				case COL_TIME:
					timeOne = pFIOne->GetTime();
					timeTwo = pFITwo->GetTime();
					iComp = timeOne > timeTwo ? 1 : ( timeOne == timeTwo ? 0 : -1);
					break;
				case COL_EXT:
					strOne = pFIOne->GetFile();
					i = strOne.ReverseFind(_T('.'));
					if (i > 0)
					{
						if (i < strOne.GetLength())
							strOne = strOne.Mid(i+1);
						else
							strOne.Empty();
					}
					strTwo = pFITwo->GetFile();
					i = strTwo.ReverseFind(_T('.'));
					if (i > 0)
					{
						if (i < strTwo.GetLength())
							strTwo = strTwo.Mid(i+1);
						else
							strTwo.Empty();
					}
					iComp = strOne.CompareNoCase(strTwo);
					break;
				case COL_SIZE:
					{
						CRect rectOne, rectTwo;
						rectOne = pFIOne->GetRect();
						rectTwo = pFITwo->GetRect();
						long l1, l2;
						l1 = rectOne.top * 100000 + rectOne.left;
						l2 = rectTwo.top * 100000 + rectTwo.top;
						if (rectOne == rectTwo)
							iComp = 0;
						else if (l1 <= l2)
							iComp = 1;
						else
							iComp = -1;
					}
					break;
				case COL_DEBUGSIZE:
					{
						CRect rectOne, rectTwo;
						rectOne = pFIOne->GetDbgRect();
						rectTwo = pFITwo->GetDbgRect();
						long l1, l2;
						l1 = rectOne.top * 100000 + rectOne.left;
						l2 = rectTwo.top * 100000 + rectTwo.top;
						if (rectOne == rectTwo)
							iComp = 0;
						else if (l1 <= l2)
							iComp = 1;
						else
							iComp = -1;
					}
					break;
				}
				if (psi->iColumn < 0)
				{
					iComp = -iComp; // reverse sorting sense.
				}
			}
		}
	}
	return(iComp);
}


void CDlgWinMgr::OnListDblClick(NMHDR *pNMHDR, LRESULT *pResult, LPARAM lParam)
{
	int iItem;
	CWindowsList *pWindowsList;
	CDlgWinMgr *pThis = (CDlgWinMgr *)lParam;
	pNMHDR; // UNREFERENCED

	_ASSERTE(pThis);

	iItem = pThis->m_ctlListWinMgr.GetCurrentIndex();
	pWindowsList = pThis->m_pWndList;
	if (pWindowsList)
	{
		CString strDoc;
		CFileItem *pItem;

		pItem = (CFileItem *)pThis->m_ctlListWinMgr.GetItemData(iItem);
		if (pItem)
		{
			strDoc = pItem->GetDir();
			strDoc += "\\";
			strDoc += pItem->GetFile();
			pWindowsList->OpenDoc(strDoc);
		}
	}
	*pResult = 0;

}

void CDlgWinMgr::OnListClick(NMHDR *pNMHDR, LRESULT *pResult, LPARAM lParam)
{
	pNMHDR; // UNREFERENCED
	CDlgWinMgr *pThis = (CDlgWinMgr *)lParam;

	_ASSERTE(pThis);
	pThis->SetButtonStates();
	*pResult = 0;
}


void CDlgWinMgr::OnColClick(NMHDR *pNMHDR, LRESULT *pResult, LPARAM lParam, SortInfo *pSortInfo)
{
	NMLISTVIEW* pNMListView = (NMLISTVIEW*)pNMHDR;
	CDlgWinMgr *pThis = (CDlgWinMgr *)lParam;
	int iColumn, iColumnLast;

	_ASSERTE(pThis);
	
	iColumn = pNMListView->iSubItem + 1;
	iColumnLast = pThis->m_iSortedCol;
	if (iColumn == abs(iColumnLast)) // a repeat so we switch directions?
	{
		iColumn = -iColumnLast;
	}
	pThis->m_iSortedCol = iColumn;
	pSortInfo->iColumn = iColumn;
	*pResult = 0;
}

void CDlgWinMgr::OnButtonclear() 
{
	DoClear();
	SetButtonStates();
}

void CDlgWinMgr::DoClear()
{
	m_pWndList->Reset();
	m_ctlListWinMgr.DeleteAllItems();
}

afx_msg void CDlgWinMgr::OnNotify( NMHDR * pNotifyStruct, LRESULT * result )
{
	result; // UNREFD
	pNotifyStruct; // UNREFD
/*
WM_NOTIFY 
    idCtrl = (int) wParam; 
    pnmh = (LPNMHDR) lParam; 

TTN_GETDISPINFO
    lpnmtdi = (LPNMTTDISPINFO)lParam;

#define TTN_NEEDTEXT TTN_GETDISPINFO

Sent by a tooltip control to retrieve information needed to display a tooltip window. This notification supersedes the TTN_NEEDTEXT notification. This notification is sent in the form of a WM_NOTIFY message. 

The return value for this notification is not used. 
lpnmtdi 
Address of an NMTTDISPINFO structure that identifies the tool that needs text and receives the requested information. 
Fill the structure's appropriate fields to return the requested information to the tooltip control. If your message handler sets the uFlags field of the NMTTDISPINFO structure to TTF_DI_SETITEM, the tooltip control stores the information and will not request it again. 

  		m_tooltip.AddTool(GetDlgItem(IDC_CHK_AUTOSIZE), IDS_TIPAUTOSIZE);
		m_tooltip.AddTool(GetDlgItem(IDC_CHK_AUTODIR), IDS_TIPAUTODIR);
		m_tooltip.AddTool(GetDlgItem(IDC_CHK_AUTOVIS), IDS_TIPAUTOVIS);
		m_tooltip.AddTool(GetDlgItem(IDC_LIST), IDS_TIPLIST);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTONREFRESH), IDS_TIPREFRESH);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTONCLEAR), IDS_TIPCLEAR);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTONINVERTSEL), IDS_TIPINVERTSEL);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTONSELECTALL), IDS_TIPSELECTALL);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTONMAKELIST), IDS_TIPMAKELIST);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTONLOADLIST), IDS_TIPLOADLIST);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTONOPEN), IDS_TIPACTIVATE);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTONMINWINS), IDS_TIPMINWINS);
		m_tooltip.AddTool(GetDlgItem(IDC_BUTTONCLOSE), IDS_TIPCLOSE);


*/

}
