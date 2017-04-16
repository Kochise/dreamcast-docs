// fontparamdlg.cpp : implementation file
//

#include "stdafx.h"
#include "EasyFont.h"
#include "fontparamdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFontParamDlg dialog


CFontParamDlg::CFontParamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFontParamDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFontParamDlg)
	m_fDeviation = 0.0f;
	m_fExtrusion = 0.0f;
	m_theString = _T("");
	m_iFormatRadio = -1;
	//}}AFX_DATA_INIT

	// Initialize Default Values
	m_iFormatDefault = 0 ;
	m_fDeviationDefault = 0.0f  ;
	m_fExtrusionDefault = 0.0f;
	m_theStringDefault = "Default";
}


void CFontParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFontParamDlg)
	DDX_Text(pDX, IDC_EDIT_DEVIATION, m_fDeviation);
	DDV_MinMaxFloat(pDX, m_fDeviation, 0.f, 1.f);
	DDX_Text(pDX, IDC_EDIT_EXTRUSION, m_fExtrusion);
	DDV_MinMaxFloat(pDX, m_fExtrusion, 0.f, 1.f);
	DDX_Text(pDX, IDC_EDIT_STRING, m_theString);
	DDV_MaxChars(pDX, m_theString, 8);
	DDX_Radio(pDX, IDC_RADIO_POLYGONS, m_iFormatRadio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFontParamDlg, CDialog)
	//{{AFX_MSG_MAP(CFontParamDlg)
	ON_BN_CLICKED(IDC_BTN_FONT, OnBtnFont)
	ON_BN_CLICKED(IDC_BTN_DEFAULT, OnBtnDefault)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFontParamDlg message handlers

void CFontParamDlg::OnBtnFont() 
{
	CFontDialog aDlg(&m_logFont, CF_SCREENFONTS, NULL, this)  ;

	aDlg.m_cf.Flags |= CF_TTONLY  ;
		
	if (aDlg.DoModal() == IDOK)
	{
		memcpy(&m_logFont,aDlg.m_cf.lpLogFont, sizeof(LOGFONT) );
	}	
}

void CFontParamDlg::OnBtnDefault() 
{
	//m_iFormat = m_iFormatDefault ;
	m_fDeviation = m_fDeviationDefault ;
	m_fExtrusion = m_fExtrusionDefault ;
	m_theString = m_theStringDefault ;

	memcpy(&m_logFont, m_pLogFontDefault, sizeof(LOGFONT)) ;

	UpdateData(FALSE) ;
}
