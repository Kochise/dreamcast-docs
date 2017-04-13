// DlgFilter.cpp : implementation file
//

#include "stdafx.h"
#include "pipe.h"
#include "DlgFilter.h"
#include <afxdlgs.h>
#include "mrustrings.h"
#include "io.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFilter dialog
static CString strMainKey = _T("Software\\Microsoft\\devstudio\\AddIns\\Filter\\");


CDlgFilter::CDlgFilter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFilter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFilter)
	//}}AFX_DATA_INIT
}


void CDlgFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFilter)
	DDX_Control(pDX, IDC_WARNING, m_ctlWarning);
	DDX_Control(pDX, IDC_COMBO_CMD, m_ctlComboCmd);
	DDX_Control(pDX, IDC_CHECKTRIM, m_ctlChkTrim);
	DDX_Control(pDX, IDC_EDITOUTFILE, m_ctlEditOutFile);
	DDX_Control(pDX, IDC_CHECKPIPE, m_ctlChkPipe);
	DDX_Control(pDX, IDC_CHECKAPPEND, m_ctlChkAppend);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFilter, CDialog)
	//{{AFX_MSG_MAP(CDlgFilter)
	ON_BN_CLICKED(IDC_BTNBROWSECMD, OnBtnbrowsecmd)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTONSRCFILE, OnButtonsrcfile)
	ON_BN_CLICKED(IDC_BUTTONSELECTION, OnButtonselection)
	ON_BN_CLICKED(IDC_BUTTONSTARTLINE, OnButtonstartline)
	ON_BN_CLICKED(IDC_BUTTONENDLINE, OnButtonendline)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFilter message handlers
void CDlgFilter::OnClose() 
{
	SaveMRU();	
	CDialog::OnClose();
}

BOOL CDlgFilter::OnInitDialog() 
{
	CString strTitle;
	CString strInfo;
	CComBSTR bstrFile;
	CStdioFile fileSel;
	CString strCmd;
	CString strDoc;
	int iCmd;
	long lStartLastLine;

	CDialog::OnInitDialog();
	
	m_ctlWarning.ShowWindow(SW_HIDE);

	_ASSERTE(m_pApp);
	CComPtr<IDispatch> pDispDoc;

	// initialise
	m_fColumnar = FALSE;
	m_fLineSelection = FALSE;
	m_fMidSelection = FALSE;

	m_cbLineLength = 0;
	m_cbLineLengthLast = 0;
	m_lEnd = 0;
	m_lStart = 0;
	m_iColEnd = 0;
	m_iColStart = 0;

	//initialise controls
	m_ctlChkPipe.SetCheck(TRUE);

	strCmd =  _T("Cmd");
	m_mruCmds.Create(HKEY_CURRENT_USER, strMainKey, strCmd);
	iCmd = 0;
	do {
		m_mruCmds.GetString(iCmd, strCmd);
		if (!strCmd.IsEmpty())
		{
			m_ctlComboCmd.AddString(strCmd);
		}
		iCmd++;
	} while (!strCmd.IsEmpty());
	m_mruCmds.GetString(0, strCmd);
	m_ctlComboCmd.SetWindowText(strCmd);

	m_pApp->get_ActiveDocument(&pDispDoc);
	m_pDoc = pDispDoc;
	pDispDoc = NULL;

	if (m_pDoc)
	{
		CComPtr<IDispatch> pDispSel;
		CComBSTR bstr;
		CString strText;
		HRESULT hr;

		hr = m_pDoc->get_Name(&bstrFile);
		strDoc = bstrFile;
		m_pDoc->get_Selection(&pDispSel);
		m_pSel = pDispSel;
		pDispSel = NULL;

		/*  Determine selection area.
			Cases:
				1. Easy Columnar selection -- text is really a column
				2. Truncated Columnar selection -- text would be a column if whitespace added to end. iColEnd doesn't help much.
				3. Line selection -- iColEnd == 1 and not columnar
				4. Mid-Line selection -- first column doesn't start at beginning of line, end column may be anywhere.
				5. Fractional line selection -- can be treated as a columnar selection on one line
				6. No selection. We insert into doc

			Problem: ITextSelection doesn't give us quite enough information directly to determine selection.
		*/
		hr = m_pSel->get_Text(&bstr);
		if (SUCCEEDED(hr))
		{
			hr = m_pSel->get_TopLine(&m_lStart);
			hr = m_pSel->get_BottomLine(&m_lEnd);
			hr = m_pSel->get_CurrentColumn(&m_iColEnd);

			m_strSelFileName = _T("finXXXX");
			_tmktemp(m_strSelFileName.GetBuffer(0));
			m_strSelFileName.ReleaseBuffer();
			m_strSelFileName += _T(".tmp");

			fileSel.Open(m_strSelFileName, CFile::modeWrite | CFile::modeCreate);
			strText = bstr;
			m_fColumnar = FALSE;
			m_cbLineLength = strText.Find(_T('\n'));
			lStartLastLine = 0;
			if (m_cbLineLength < 0)
			{ // case 5
				m_fColumnar = TRUE;
				m_cbLineLength = strText.GetLength();
			}
			else 
			{ // case 1 ,case 2, case 3,  or case 4?
				int i, j;

				i = m_cbLineLength;
				m_cbLineLengthFirst = m_cbLineLength;
				m_fColumnar = TRUE; // see if we are a full column selection -- assume case 1
				while (i >= 0)
				{
					j = strText.Find(_T('\n'), i+1);
					if (j >= 0)
					{
						if (m_fColumnar && j - i - 1 != m_cbLineLength)
						{
							m_fColumnar = FALSE; // not case 1
							m_cbLineLength = j - i;
						}
						m_cbLineLengthLast = j - i; // pick up last line length so we know where to end.
					}
					else
					{
						m_cbLineLengthLast = strText.GetLength() - i;
					}
					if (j >= 0 || (j < 0 && m_cbLineLengthLast > 1))
						lStartLastLine = i+1;
					i = j;
				}
			}
			if (m_lStart == m_lEnd && m_cbLineLength == 0)
			{
				m_fColumnar = FALSE; // case 6
			}
			if (lStartLastLine > 0 && m_iColEnd > 1) //iColEnd == 1 means line select (not case 3)
			{ // determine if we have case 2 -- side-effect - destroys current sel.
				// also pickup info needed for cases 1, 2, 4
				CString strCurr, strPiece;
				CComBSTR bstrCurr;
				CComVariant var;
				long iColBottomLeft;

				var = dsMove;
				m_pSel->MoveTo(m_lStart, 1, var);
				var = dsExtend;
				m_pSel->EndOfLine(var);
				m_pSel->get_Text(&bstrCurr);
				strCurr = bstrCurr;
				strPiece = strText.Left(m_cbLineLengthFirst-1);
				m_iColStart = strCurr.Find(strPiece) + 1;

				// eliminate 4
				var = dsMove;
				m_pSel->MoveTo(m_lEnd, 1, var);
				var = dsExtend;
				m_pSel->EndOfLine(var);
				m_pSel->get_Text(&bstrCurr);
				strCurr = bstrCurr;
				strPiece = strText.Mid(lStartLastLine);
				strPiece.Remove(_T('\n'));
				strPiece.Remove(_T('\r'));
				iColBottomLeft = strCurr.Find(strPiece) + 1;
				if (iColBottomLeft == m_iColStart || m_fColumnar) // m_fColumnar is safer than MidSelection if we are wrong
				{
					m_fColumnar = TRUE; // case 1 or 2
				}
				else
				{
					m_fMidSelection = TRUE; // case 4
				}

			}
			if (!m_fColumnar && m_iColEnd == 1)
				m_fLineSelection = TRUE;

			//_ASSERTE(m_fColumnar + m_fLineSelection + m_fMidSelection == 1);
			fileSel.WriteString(strText);
			fileSel.Close();
		}
	}

	
	GetWindowText(strTitle);
	if (m_iColStart)
	{
		strInfo.Format(IDS_FORMATSELINFO, strDoc, m_lStart, m_lEnd, m_iColStart, m_iColEnd);
	}
	else
	{
		strInfo.Format(IDS_FORMATLINEINFO, strDoc, m_lStart, m_lEnd);
	}
	strTitle += strInfo;
	SetWindowText(strTitle);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgFilter::OnOK() 
{
// Do apply here...
	CString strCmd, strFilterCmd, strFilterSrc;
	CString strOutFile;
	BOOL fPipe, fAppend, fTrim;
	CStdioFile fileTmp, fileOut;
	CString strTmpOut;
	int iRes;
	CString strT;
	HRESULT hr;
	CComBSTR bstrFile;
	CComVariant var;
	long lLine;
	long iColStart;

	if (m_pApp == NULL || m_pDoc == NULL || m_pSel == NULL)
		return;

	m_ctlComboCmd.GetWindowText(strFilterCmd);
	strFilterSrc = strFilterCmd; // save this for use in combobox
	m_ctlEditOutFile.GetWindowText(strOutFile);
	if (!strOutFile.IsEmpty())
		strTmpOut = strOutFile;
	else
	{
		strTmpOut = _T("foutXXXX");
		_tmktemp(strTmpOut.GetBuffer(0));
		strTmpOut.ReleaseBuffer();
		strTmpOut += _T(".tmp");
	}
	fAppend = m_ctlChkAppend.GetCheck();
	fPipe = m_ctlChkPipe.GetCheck();
	fTrim = m_ctlChkTrim.GetCheck();

	hr = m_pDoc->get_Name(&bstrFile);
	strT = bstrFile;
	strFilterCmd.Replace(_T("%f"), strT);
	strFilterCmd.Replace(_T("%x"), m_strSelFileName);
	strT.Format(_T("%d"), m_lEnd);
	strFilterCmd.Replace(_T("%e"), strT);
	strT.Format(_T("%d"), m_lStart);
	strFilterCmd.Replace(_T("%l"), strT);
	if (fPipe)
	{
		strCmd.Format(_T("type %s | %s "), m_strSelFileName, strFilterCmd);
	}
	else
	{
		strCmd.Format(_T("%s "), strFilterCmd);
	}
	if (fAppend)
	{
		strCmd += _T('>');
	}
	strCmd += _T("> ");
	strCmd += strTmpOut;

	iRes = _tsystem(strCmd);
	if (strOutFile.IsEmpty() && m_pSel && iRes == 0)
	{
		// add a successful cmd to the combo box
		if (m_ctlComboCmd.FindStringExact(0, strFilterSrc) == CB_ERR)
		{
			m_ctlComboCmd.AddString(strFilterSrc);
		}

		// process output
		if (fileTmp.Open(strTmpOut, CFile::modeRead))
		{
			CString strIn;
			CComBSTR bstrIn;
			DWORD cb;
			TCHAR *pch;

			if (m_fLineSelection )
			{
				cb = fileTmp.GetLength();
				pch = strIn.GetBufferSetLength(cb+1);
				memset(pch, _T('\0'), sizeof(TCHAR)*(cb+1)); // make sure we don't get extra garbage.
				strIn.ReleaseBuffer();
				fileTmp.Read(strIn.GetBuffer(cb), cb);
				bstrIn = strIn;
				m_pSel->put_Text(bstrIn);
			}
			else if (m_fMidSelection)
			{
				// do first line
				lLine = m_lStart;
				var = dsMove;
				m_pSel->MoveTo(lLine, 1, var);
				var = dsExtend;
				m_pSel->EndOfLine(var);
				m_pSel->get_CurrentColumn(&iColStart);
				iColStart -= m_cbLineLengthFirst;
				strIn.Empty();
				fileTmp.ReadString(strIn);
				strIn.Remove(_T('\n'));
				strIn.Remove(_T('\r'));
				if (fTrim)
				{
					strIn.TrimLeft();
					strIn.TrimRight();
				}
				bstrIn = strIn;
				var = dsMove;
				m_pSel->MoveTo(lLine, iColStart, var);
				var = dsExtend;
				m_pSel->EndOfLine(var);
				m_pSel->put_Text(bstrIn);
				
				for (lLine = m_lStart + 1 ; lLine <=  m_lEnd - 1; lLine++)
				{
					strIn.Empty();
					fileTmp.ReadString(strIn);
					strIn.Remove(_T('\n'));
					strIn.Remove(_T('\r'));
					if (fTrim)
					{
						strIn.TrimLeft();
						strIn.TrimRight();
					}
					bstrIn = strIn;
					var = dsMove;
					m_pSel->MoveTo(lLine, 1, var);
					var = dsExtend;
					m_pSel->EndOfLine(var);
					m_pSel->put_Text(bstrIn);

				}

				// do last line
				lLine = m_lEnd;
				var = dsMove;
				iColStart = 1;
				strIn.Empty();
				fileTmp.ReadString(strIn);
				strIn.Remove(_T('\n'));
				strIn.Remove(_T('\r'));
				if (fTrim)
				{
					strIn.TrimLeft();
					strIn.TrimRight();
				}
				bstrIn = strIn;
				var = dsMove;
				m_pSel->MoveTo(lLine, iColStart, var);
				var = dsExtend;
				m_pSel->MoveTo(lLine, m_cbLineLengthLast, var);
				m_pSel->put_Text(bstrIn);
			}
			else
			{
				_ASSERTE(m_fColumnar);
				iColStart = m_iColStart;
				
				for (lLine = m_lStart; lLine <=  m_lEnd; lLine++)
				{
					strIn.Empty();
					fileTmp.ReadString(strIn);
					strIn.Remove(_T('\n'));
					strIn.Remove(_T('\r'));
					if (fTrim)
					{
						strIn.TrimLeft();
						strIn.TrimRight();
					}
					bstrIn = strIn;
					var = dsMove;
					m_pSel->MoveTo(lLine, iColStart, var);
					var = dsExtend;
					m_pSel->MoveTo(lLine, m_iColEnd, var);
					m_pSel->put_Text(bstrIn);

				}
			}
			fileTmp.Close();
		}

	}

	// cleanup
	if (strOutFile.IsEmpty())
	{ // if we were using strOutFile, we don't want to delete it!
		_tremove(strTmpOut);
	}
	_tremove(m_strSelFileName);


	// reset selection
#ifdef RESET_SEL
	var = dsMove;
	m_pSel->MoveTo(lLine, iColStart, var);
	for (lLine = m_lStart; lLine <=  m_lEnd; lLine++)
		{
			var = dsExtend;
			m_pSel->MoveTo(lLine, -1, var);
		}
#endif
	m_ctlWarning.ShowWindow(SW_NORMAL);

}

void CDlgFilter::SetApp(IApplication * pApp)
{
	m_pApp = pApp;
}

void CDlgFilter::OnBtnbrowsecmd() 
{
	CString strFilter;

	strFilter.LoadString(IDS_EXEBATCMD_FILTER);
	CFileDialog dlgGetFile(FALSE, NULL, NULL, OFN_EXPLORER,
		strFilter,
		this);
	
	if (dlgGetFile.DoModal() == IDOK)
	{
		CString strFile;
		strFile = dlgGetFile.GetPathName();
		m_ctlComboCmd.SetWindowText(strFile);
	}
}

void CDlgFilter::OnButtonsrcfile() 
{
	CString str;


	m_ctlComboCmd.GetWindowText(str);
	str += _T(" %f");
	m_ctlComboCmd.SetWindowText(str);
	
}

void CDlgFilter::OnButtonselection() 
{
	CString str;


	m_ctlComboCmd.GetWindowText(str);
	str += _T(" %x");
	m_ctlComboCmd.SetWindowText(str);
}

void CDlgFilter::OnButtonstartline() 
{
	CString str;


	m_ctlComboCmd.GetWindowText(str);
	str += _T(" %l");
	m_ctlComboCmd.SetWindowText(str);
}

void CDlgFilter::OnButtonendline() 
{
	CString str;


	m_ctlComboCmd.GetWindowText(str);
	str += _T(" %e");
	m_ctlComboCmd.SetWindowText(str);
}

void CDlgFilter::OnCancel() 
{
	SaveMRU();	
	CDialog::OnCancel();
}

void CDlgFilter::SaveMRU()
{
	int i;
	CString strCmd;

	for (i = 0; i < m_ctlComboCmd.GetCount(); i++)
	{
		m_ctlComboCmd.GetLBText(i, strCmd);
		m_mruCmds.SetString(i, strCmd);
	}
}
