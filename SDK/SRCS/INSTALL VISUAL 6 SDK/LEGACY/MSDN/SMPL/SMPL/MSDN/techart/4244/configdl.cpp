// configdl.cpp : implementation file
//

#include "stdafx.h"
#include "PicCube.h"
#include "configdl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

LPCTSTR CConfigDlg::s_key[6] = { _T("Face1"), _T("Face2"), _T("Face3"), 
				                     _T("Face4"), _T("Face5"), _T("Face6")} ;

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog


CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)
	//}}AFX_DATA_INIT
}


void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_Control(pDX, IDC_CHECKDEFAULT, m_checkDefault);
	DDX_Control(pDX, IDC_FACE1, m_btnFace1);
	DDX_Control(pDX, IDC_EDIT1, m_editPath);
	DDX_Control(pDX, IDC_BROWSE, m_btnBrowse);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_FACE1, OnFace1)
	ON_BN_CLICKED(IDC_FACE2, OnFace2)
	ON_BN_CLICKED(IDC_FACE3, OnFace3)
	ON_BN_CLICKED(IDC_FACE4, OnFace4)
	ON_BN_CLICKED(IDC_FACE5, OnFace5)
	ON_BN_CLICKED(IDC_FACE6, OnFace6)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_BN_CLICKED(IDC_CHECKDEFAULT, OnCheckdefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

// Open a file dialog box to get a DIB file to texture with...
void CConfigDlg::OnBrowse() 
{
    // Show an open file dialog to get the name
    CFileDialog dlg   (TRUE,    // open
                       NULL,    // no default extension
                       NULL,    // no initial file name
                       OFN_FILEMUSTEXIST
                       | OFN_HIDEREADONLY,
                       "Image files (*.DIB, *.BMP)|*.DIB;*.BMP|All files (*.*)|*.*||");	 
    if (dlg.DoModal() == IDOK)
    {	
      int i = GetCheckedRadioButton(IDC_FACE1, IDC_FACE6) - IDC_FACE1;
      m_strPath[i] = dlg.GetPathName();
      m_editPath.SetWindowText(m_strPath[i]) ;	
      return  ; // TRUE ;
    }

   return ; //FALSE ;  	
}

BOOL CConfigDlg::OnInitDialog() 
{
	m_strDefault = _T("--DEFAULT--") ; 
	m_strSection.LoadString(IDS_PROFILE_SECTION) ;	
	m_strIniName.LoadString(IDS_PROFILE_INI) ;

	CDialog::OnInitDialog();
	
	LPTSTR buffer ;

	for(int i = 0 ; i < 6 ; i++)
	{
		buffer = m_strPath[i].GetBufferSetLength(512) ;
		::GetPrivateProfileString(m_strSection,
								s_key[i],
								m_strDefault, 
								buffer,
								512,
								m_strIniName) ;
		m_strPath[i].ReleaseBuffer() ;

		m_bDefault[i] = ((m_strPath[i] == m_strDefault) ||
						 (m_strPath[i].IsEmpty()) ) ;
	}

	CheckRadioButton(IDC_FACE1, IDC_FACE6, IDC_FACE1) ;
	OnFace1() ;
	m_btnFace1.SetFocus() ;		
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigDlg::HandleRadioBtn(int i)
{
	m_checkDefault.SetCheck(m_bDefault[i]) ;
	m_editPath.SetWindowText(m_strPath[i]) ;	
	m_editPath.EnableWindow(!m_bDefault[i]) ;
}

void CConfigDlg::OnFace1() 
{
	HandleRadioBtn(0) ;
}

void CConfigDlg::OnFace2() 
{
	HandleRadioBtn(1) ;
}

void CConfigDlg::OnFace3() 
{
	HandleRadioBtn(2);
}

void CConfigDlg::OnFace4() 
{
	HandleRadioBtn(3) ;
}

void CConfigDlg::OnFace5() 
{
	HandleRadioBtn(4) ;
}

void CConfigDlg::OnFace6() 
{
	HandleRadioBtn(5) ;
}

void CConfigDlg::OnKillfocusEdit1() 
{
    int i = GetCheckedRadioButton(IDC_FACE1, IDC_FACE6) - IDC_FACE1;
	m_editPath.GetWindowText(m_strPath[i]); 
	m_bDefault[i] = m_checkDefault.GetCheck() ;	
}

void CConfigDlg::OnOK() 
{
	for (int i = 0 ; i < 6 ; i++)
	{
		::WritePrivateProfileString(m_strSection,
									s_key[i],
									(m_bDefault[i] ? NULL : m_strPath[i]),
									m_strIniName) ;
	}
		
	CDialog::OnOK();
}

void CConfigDlg::OnCheckdefault() 
{
    int i = GetCheckedRadioButton(IDC_FACE1, IDC_FACE6) - IDC_FACE1;
	m_bDefault[i] = m_checkDefault.GetCheck() ;	
	m_editPath.SetWindowText(m_strPath[i]) ;	
	m_editPath.EnableWindow(!m_bDefault[i]) ;

}
