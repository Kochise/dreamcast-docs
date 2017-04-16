// DocProps.cpp : implementation file
//

#include "stdafx.h"
#include "OCCSamp.h"
#include "DocProps.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocProps dialog


CDocProps::CDocProps(CWnd* pParent /*=NULL*/)
	: CDialog(CDocProps::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDocProps)
	m_EditComments = _T("");
	//}}AFX_DATA_INIT

	if (vpOC != NULL)
		m_pAutoCorrect = vpOC->PiacGetAutoCorrect();
	else
		m_pAutoCorrect = NULL;
}


void CDocProps::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDocProps)
	DDX_Text(pDX, IDC_EDITCOMMENTS, m_EditComments);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDocProps, CDialog)
	//{{AFX_MSG_MAP(CDocProps)
	ON_BN_CLICKED(IDC_ALLPROPS, OnAllprops)
	ON_EN_CHANGE(IDC_EDITCOMMENTS, OnChangeEditcomments)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDocProps message handlers


void CDocProps::OnAllprops() 
{
	// TODO: Add your control notification handler code here
	if (m_pDocProps != NULL)
		m_pDocProps->ShowDialog(m_hWnd, L"Properties", L"FileName", NULL);
}

void CDocProps::OnChangeEditcomments() 
{
	// TODO: Add your control notification handler code here

	static BOOL fInChangeEdit = FALSE;

	if (m_pAutoCorrect == NULL || fInChangeEdit == TRUE)
		return;

	CEdit* pWndEdit = (CEdit*)GetDescendantWindow( IDC_EDITCOMMENTS, FALSE );

	CString strComments;
	pWndEdit->GetWindowText(strComments);

	int nStartChar, nEndChar;
	pWndEdit->GetSel(nStartChar, nEndChar);
	if (nStartChar != nEndChar) // there is a selection
		return;
		
	LPCWSTR pwzComments = ConvertToUnicode(strComments);


	WCHAR wchTo[256];
	unsigned int cchTo, cchReplace;

	cchTo = 256;
	if (m_pAutoCorrect->FCorrect(pwzComments, nStartChar - 1, FALSE, wchTo, &cchTo, &cchReplace))
	{
		fInChangeEdit = TRUE;

		pWndEdit->SetSel(nEndChar - cchReplace, nEndChar - 1, FALSE);

		LPCSTR pszComments = ConvertToAnsi(wchTo);
		pWndEdit->ReplaceSel(pszComments);

		fInChangeEdit = FALSE;
	}

}
