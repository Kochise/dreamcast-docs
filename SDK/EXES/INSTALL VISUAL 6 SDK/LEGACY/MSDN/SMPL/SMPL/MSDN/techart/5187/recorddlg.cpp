//////////////////////////////////////////////////////////////////////////////
// RecordDlg.cpp	- Copyright (C) 1997 Microsoft Corporation				//
//					- All rights reserved.									//
// Date				- 12/11/97												//
// Purpose			- New/edit record dialog								//
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CE.h"
#include "RecordDlg.h"
#include "SketchPad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Constructor ///////////////////////////////////////////////////////////////
//																			//
// Purpose		- Initialize the sketch data								//
//////////////////////////////////////////////////////////////////////////////
CRecordDlg::CRecordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecordDlg::IDD, pParent)
{

	m_lpSketchData	= NULL;
	m_nSketchSize	= 0;

	//{{AFX_DATA_INIT(CRecordDlg)
	m_strData = _T("");
	//}}AFX_DATA_INIT
}

// Destructor ////////////////////////////////////////////////////////////////
//																			//
// Purpose		- Free the sketch data										//
//////////////////////////////////////////////////////////////////////////////
CRecordDlg::~CRecordDlg()
{
	if(m_lpSketchData)
		delete m_lpSketchData;
}


void CRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecordDlg)
	DDX_Control(pDX, IDC_SKETCH, m_btnSketch);
	DDX_Text(pDX, IDC_DATA, m_strData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecordDlg, CDialog)
	//{{AFX_MSG_MAP(CRecordDlg)
	ON_BN_CLICKED(IDC_SKETCH, OnSketch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// SetTextData ///////////////////////////////////////////////////////////////
//																			//
// Purpose		- Initialize the data box with the record text				//
// Assumptions	- None														//
// Inputs		- (const CString&) strData - Text associated with record	//
// Outputs		- None														//
//////////////////////////////////////////////////////////////////////////////
void CRecordDlg::SetTextData(const CString & strData)
{
	m_strData = strData;
}

// SetSketchData /////////////////////////////////////////////////////////////
//																			//
// Purpose		- Initialize the sketch data with the record sketch			//
// Assumptions	- nSize is the actual size of the data pointed to by lpData //
// Inputs		- (LPBYTE) lpData	- the byte array sketch data			//
//				- (long)   nSize	- the size of the data					//
// Outputs		- None														//
//////////////////////////////////////////////////////////////////////////////
void CRecordDlg::SetSketchData(LPBYTE lpData, long nSize)
{
	// save copy of data
	if(m_lpSketchData)
		delete m_lpSketchData;

	if(nSize)
	{
		m_lpSketchData = new BYTE[nSize];
		m_nSketchSize = nSize;
		memcpy(m_lpSketchData, lpData, nSize);
	}
	else
	{
		m_lpSketchData = NULL;
		m_nSketchSize = 0;
	}
}

// GetTextData ///////////////////////////////////////////////////////////////
//																			//
// Purpose		- Returns the text associated with the dialog data edit box //
// Assumptions	- None														//
// Inputs		- None														//
// Outputs		- (CString) Text in the edit box							//
//////////////////////////////////////////////////////////////////////////////
CString CRecordDlg::GetTextData()
{
	return m_strData;
}

// GetSketchData /////////////////////////////////////////////////////////////
//																			//
// Purpose		- Returns the byte array of sketch data						//
// Assumptions	- None														//
// Inputs		- None														//
// Outputs		- (LPBYTE) pointer to a copy of the sketch data entered		//
//////////////////////////////////////////////////////////////////////////////
LPBYTE CRecordDlg::GetSketchData()
{
	// return a copy of data
	LPBYTE	lpData;

	if(!m_nSketchSize)
		return NULL;

	lpData = new BYTE[m_nSketchSize];
	memcpy(lpData, m_lpSketchData, m_nSketchSize);

	return lpData;
}

// GetSketchSize /////////////////////////////////////////////////////////////
//																			//
// Purpose		- To return the size of the sketch data byte array			//
// Assumptions	- None														//
// Inputs		- None														//
// Outputs		- (long) the size of the sketch								//
//////////////////////////////////////////////////////////////////////////////
long CRecordDlg::GetSketchSize()
{
	return m_nSketchSize;
}

// OnInitDialog //////////////////////////////////////////////////////////////
//																			//
// Purpose		- Called by the framework to initialize the dialog			//
//				- Used here just to set the window caption depending on		//
//				- whether the user is editing a record or creating a new one//
// Assumptions	- None														//
// Inputs		- None														//
// Outputs		- (BOOL) Whether focus was given to a control				//
//////////////////////////////////////////////////////////////////////////////
BOOL CRecordDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// if there's existing data, we're editing a record
	if(m_strData.GetLength())
		SetWindowText(_T("Edit Record"));
	else 
		SetWindowText(_T("New Record"));

	return TRUE;  
}

// OnSketch //////////////////////////////////////////////////////////////////
//																			//
// Purpose		- Called by the framework when the 'Sketch' button is hit	//
// Assumptions	- The existing sketch data is valid							//
// Inputs		- None														//
// Outputs		- None														//
//////////////////////////////////////////////////////////////////////////////
void CRecordDlg::OnSketch() 
{
	CSketchPad dlg;

	dlg.SetData(m_lpSketchData, m_nSketchSize);

	if (dlg.DoModal() == IDOK)
	{
		// Copy sketch data
		if(m_lpSketchData)
			delete m_lpSketchData;

		m_lpSketchData = dlg.GetData();
		m_nSketchSize = dlg.GetDataSize();
	}
}
