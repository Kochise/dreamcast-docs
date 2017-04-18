// cstm1dlg.cpp : implementation file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp and/or WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "hierwiz.h"
#include "Hierwaw.h"
#include "cstm1dlg.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg dialog
int CCustom1Dlg::m_DataSource = READFILE ;

CCustom1Dlg::CCustom1Dlg()
	:CAppWizStepDlg(CCustom1Dlg::IDD)
{
	//{{AFX_DATA_INIT(CCustom1Dlg)
	m_TextView = 0;
	m_SampleDataSource = 0;
	//}}AFX_DATA_INIT
}


void CCustom1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX) ;
	//{{AFX_DATA_MAP(CCustom1Dlg)
	DDX_Control(pDX, IDC_PICTURE, m_PicFrame);
	DDX_Radio(pDX, IDC_TEXTVIEW, m_TextView);
	DDX_Radio(pDX, IDC_READFILE, m_SampleDataSource);
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom1Dlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;
	// Where are you getting the default data?
	switch (m_SampleDataSource)  // From file
	{
		// Clear previously selected options in case the user changed his/her mind
		ClearSampleTxtSettings() ;
		case TEXT_FROM_FILE:
			m_DataSource = READFILE ; // sample text read in from an existing file
			hierwizaw.m_Dictionary.SetAt("OPEN_FILE","READFILE") ;
			hierwizaw.m_Dictionary.SetAt("hiersample","mfcclass.hie") ;
			break;

		case TEXT_FROM_KEYBOARD: // From keyboard input
			m_DataSource = ENTERTEXT ; // sample text entered by user
			// No input data until the user actually types in text on the next page.
			hierwizaw.m_Dictionary.SetAt("NO_INPUT_DATA","YES") ;
			break ;

		case NO_SAMPLE_TXT: // No sample data.
			break ;
	}
	// Do you wants a text view?
	if (m_TextView == 0)
	{
		hierwizaw.m_Dictionary.SetAt("WANTS_TEXTVIEW","YES") ;
	}
	else
		hierwizaw.m_Dictionary.RemoveKey("WANTS_TEXTVIEW") ;

	return TRUE;    // return FALSE if the dialog shouldn't be dismissed
}


// Removes Read file related options in case the user changed his/her mind
void CCustom1Dlg::ClearSampleTxtSettings()
{
	hierwizaw.m_Dictionary.RemoveKey("OPEN_FILE") ;
	hierwizaw.m_Dictionary.RemoveKey("hiersample") ;
	hierwizaw.m_Dictionary.RemoveKey("TEXT_FILE") ;
	hierwizaw.m_Dictionary.RemoveKey("USER_INPUT_DATA") ;
	hierwizaw.m_Dictionary.RemoveKey("NO_INPUT_DATA") ;
}



BEGIN_MESSAGE_MAP(CCustom1Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom1Dlg)
	ON_BN_CLICKED(IDC_NODATA, OnNodata)
	ON_BN_CLICKED(IDC_EDITDATA, OnEditdata)
	ON_BN_CLICKED(IDC_READFILE, OnReadfile)
	ON_BN_CLICKED(IDC_TEXTVIEW, OnTextView)
	ON_BN_CLICKED(IDC_NOTEXTVIEW, OnNoTextView)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg message handlers


BOOL CCustom1Dlg::OnInitDialog()
{
	CAppWizStepDlg::OnInitDialog();

	//Set default options.
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CCustom1Dlg::OnNodata()
{
	pSampletxtBMap = &bNoSampletxt ;
	SetNumberOfSteps(NO_DATA_STEPS);
	DrawBitmaps() ;

}

void CCustom1Dlg::OnEditdata()
{
	pSampletxtBMap = &bfromKb ;
	SetNumberOfSteps(ENTER_DATA_STEPS);
	DrawBitmaps() ;
}

void CCustom1Dlg::OnReadfile()
{
	pSampletxtBMap = &bfromFile ;
	SetNumberOfSteps(READ_FILE_STEPS);
	DrawBitmaps() ;
}

void CCustom1Dlg::OnTextView()
{
		pViewsBMap = &bTVandTxtVw ;
		DrawBitmaps() ;
}

void CCustom1Dlg::OnNoTextView()
{
	pViewsBMap = &bTVOnly ;
	DrawBitmaps() ;
}

void CCustom1Dlg::DrawBitmaps()
{
	CDC cpDcVw, cpDcTxt, *cdc  ;
	RECT rec ;
	m_PicFrame.GetWindowRect(&rec) ;
	cdc = m_PicFrame.GetDC() ;
	cpDcVw.CreateCompatibleDC(cdc);
	// Draw the text view bitmap
	cpDcVw.SelectObject(pViewsBMap) ;
	cdc->BitBlt(0,0,rec.right - rec.left, rec.bottom-rec.top,&cpDcVw,0,0,SRCCOPY) ;

	// Draw the sample data source bitmaps.
	cpDcTxt.CreateCompatibleDC(cdc);
	cpDcTxt.SelectObject(pSampletxtBMap) ;
	cdc->BitBlt(0,165,rec.right - rec.left, rec.bottom-rec.top,&cpDcTxt,0,0,SRCCOPY) ;
}

void CCustom1Dlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	DrawBitmaps() ;

}

HBRUSH CCustom1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if(pWnd == GetDlgItem(IDC_PICTURE))
		DrawBitmaps() ;

	return CAppWizStepDlg::OnCtlColor(pDC, pWnd, nCtlColor);
}

int CCustom1Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CAppWizStepDlg::OnCreate(lpCreateStruct) == -1)
		return -1;

	bTVOnly.LoadBitmap(IDB_TVONLY) ;
	bTVandTxtVw.LoadBitmap(IDB_TVANDTXTVW) ;
	bNoSampletxt.LoadBitmap(IDB_NOSAMPLETXT) ;
	bfromFile.LoadBitmap(IDB_TXTFROMFILE) ;
	bfromKb.LoadBitmap(IDB_TXTFROMKB) ;

	pViewsBMap = &bTVandTxtVw ;
	pSampletxtBMap = &bfromFile ;

	return 0;
}
