//////////////////////////////////////////////////////////////////////////
// CEDlg.cpp  - Copyright (C) 1997 Microsoft Corporation				//
//            - All rights reserved.									//
// Date       - 12/11/97												//
// Purpose    - Main application dialog									//
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CE.h"
#include "CEDlg.h"
#include "RecordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DATABASE		_T("MyPIM Database")
#define MAXBUFFERSIZE	4096


CCEDlg::CCEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCEDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCEDlg)
	m_strData = _T("");
	m_strResult = _T("");
	m_strSearch = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCEDlg)
	DDX_Control(pDX, IDC_RESULTBOX, m_Results);
	DDX_Control(pDX, IDC_REMOVE, m_btnRemove);
	DDX_Control(pDX, IDC_NEW, m_btnNew);
	DDX_Control(pDX, IDC_EDIT, m_btnEdit);
	DDX_Text(pDX, IDC_QUICKVIEW, m_strData);
	DDX_Text(pDX, IDC_RESULTS, m_strResult);
	DDX_Text(pDX, IDC_SEARCH, m_strSearch);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCEDlg, CDialog)
	//{{AFX_MSG_MAP(CCEDlg)
	ON_EN_CHANGE(IDC_SEARCH, OnChangeSearch)
	ON_LBN_SELCHANGE(IDC_RESULTBOX, OnSelchangeResultbox)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




// OnInitDialog //////////////////////////////////////////////////////////////
//																			//
// Purpose		- Initialize dialog before display							//
// Assumptions	- None														//
// Inputs		- None														//
// Outputs		- (BOOL) TRUE, unless we set the focus to a control			//
//////////////////////////////////////////////////////////////////////////////
BOOL CCEDlg::OnInitDialog()	
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	// Open Database
	if (mDatabase.Open(DATABASE) == FALSE)
	{
		if (mDatabase.Create(DATABASE) == NULL)
		{
			// handle and exit
			MessageBox(_T("Unable to create database!"), _T("OK"), MB_ICONEXCLAMATION);
			return TRUE;
		}

		if (mDatabase.Open(DATABASE) == FALSE)
		{
			// handle and exit
			MessageBox(_T("Unable to open database!"), _T("OK"), MB_ICONEXCLAMATION);
			return TRUE;
		}
	}

	int nNumRecords = mDatabase.GetNumRecords();
	m_strResult.Format(_T("%d records read"), nNumRecords);
	UpdateData(FALSE);

	m_btnEdit.EnableWindow(FALSE);
	m_btnRemove.EnableWindow(FALSE);

	// Fill results box with all records
	OnChangeSearch();

	return TRUE;  
}

// OnChangeSearch ////////////////////////////////////////////////////////////
//																			//
// Purpose		- To handle changes in the user-entered search string		//
// Assumptions	- None														//
// Inputs		- None														//
// Outputs		- None														//
//////////////////////////////////////////////////////////////////////////////
void CCEDlg::OnChangeSearch() 
{
	// Grab search string and update results box with all matching records
	UpdateData(TRUE);
	DisplayAllContaining(m_strSearch);	
}

// DisplayAllContaining //////////////////////////////////////////////////////
//																			//
// Purpose		- Display all records that contain the (case-insensitive)	//
//				- substring 'strSearch' in their text data					//
// Assumptions	- mDatabase is a valid CCeDBDatabase						//
// Inputs		- (const CString&) strSearch								//
//				- String to perform the search against						//
// Outputs		- None														//
//////////////////////////////////////////////////////////////////////////////
void CCEDlg::DisplayAllContaining(const CString & strSearch)
{
	CCeDBRecord		*pRecord;
	CCeDBProp		*pProp;
	CEOID			 oid;

	CString			 strLCSearch = strSearch,
					 strLCText;

	int				 nIndex,
					 n,
					 nCount = 0,
					 nNumRecords = mDatabase.GetNumRecords();

	// Make the search string lowercase
	strLCSearch.MakeLower();

	// Empty the results box
	m_Results.ResetContent();

	// Rewind the database
	oid = mDatabase.SeekFirst();
	
	while(oid)
	{
		pRecord = new CCeDBRecord;

		// Read the record
		mDatabase.ReadCurrRecord(pRecord);
		
		if(pRecord->GetNumProps())
		{
			// Grab the text property
			pProp = pRecord->GetPropFromIndex(0);
		
			// Make sure that it is indeed a string property
			if (pProp && LOWORD (pProp->m_CePropVal.propid) == CEVT_LPWSTR)
			{
				strLCText = pProp->GetString();
				strLCText.MakeLower();
	
				// Do the search
				if(strLCText.Find(strLCSearch) != -1)
				{
					// Found a match!

					nIndex = strLCText.Find('\n');
					
					// Only add the first line of text to the results box
					if(nIndex != -1)
						n = m_Results.AddString(CString(pProp->GetString()).Left(nIndex-1).GetBuffer(MAXBUFFERSIZE));
					else 
						n = m_Results.AddString(CString(pProp->GetString()).GetBuffer(MAXBUFFERSIZE));
	
					// Set the item data to the OID of the record
					m_Results.SetItemData(n, oid);

					nCount++;
				}
			}
		}
		oid = mDatabase.SeekNext();

		delete pRecord;
	}

	if(m_Results.GetCount())
		m_Results.SetCurSel(0);

	nIndex = m_Results.GetCurSel();
	
	// Disable the edit and remove buttons if no selection
	m_btnEdit.EnableWindow(nIndex != LB_ERR);
	m_btnRemove.EnableWindow(nIndex != LB_ERR);

	m_strResult.Format(_T("%d of %d records match"), nCount, nNumRecords);

	UpdateData(FALSE);

	// Display the text data for the currently selected record
	DisplayTextData();
}

// DisplayTextData ///////////////////////////////////////////////////////////
//																			//
// Purpose		- Display the text property of the selected record			//
// Assumptions	- mDatabase is a valid CCeDBDatabase						//
// Inputs		- None														//
// Outputs		- None														//
//////////////////////////////////////////////////////////////////////////////
void CCEDlg::DisplayTextData()
{
	int				 nIndex = m_Results.GetCurSel();
	CCeDBRecord		*pRecord;
	CCeDBProp		*pProp;
	CEOID			 oid;

	if (nIndex == -1)
	{
		// If no selection, clear the data
		m_strData.Empty();
	}
	else
	{
		// Get the OID of the selected record
		oid = m_Results.GetItemData(nIndex);

		// Find the record
		if (mDatabase.SeekToRecord(oid))
		{
			pRecord = new CCeDBRecord;

			// Read the record
			mDatabase.ReadCurrRecord(pRecord);

			// If it has a property associated...
			if(pRecord->GetNumProps())
			{
				// Grab the first property
				pProp = pRecord->GetPropFromIndex(0);

				// Make sure that it's a string property - then grab it
				if (pProp && LOWORD (pProp->m_CePropVal.propid) == CEVT_LPWSTR)
					m_strData = CString(pProp->GetString()).GetBuffer(MAXBUFFERSIZE);

				delete pRecord;
			}
		}
	}
	UpdateData(FALSE);
}

// OnSelchangeResultbox //////////////////////////////////////////////////
//																		//
// Purpose		- Called automatically when the result box selection	//	
//				- changes.												//
// Assumptions	- mDatabase is a valid CCeDBDatabase					//
// Inputs		- None													//
// Outputs		- None													//
//////////////////////////////////////////////////////////////////////////
void CCEDlg::OnSelchangeResultbox() 
{
	CEOID		oid;
	CCeDBRecord *pRecord;

	UpdateData(TRUE);

	DisplayTextData();
	
	int nIndex = m_Results.GetCurSel();

	m_btnEdit.EnableWindow(nIndex != LB_ERR);
	m_btnRemove.EnableWindow(nIndex != LB_ERR);

	if(nIndex == LB_ERR)
		return;

	// Grab OID of newly selected record
	oid = m_Results.GetItemData(nIndex);

	if(oid)
	{
		// find the record...
		if (mDatabase.SeekToRecord(oid))
		{
			pRecord = new CCeDBRecord;

			// ... and read it to find out if there's a sketch associated
			mDatabase.ReadCurrRecord(pRecord);

			if(pRecord->GetNumProps() > 1)
				m_strResult = _T("Record contains sketch");
			else
				m_strResult = _T("Record contains no sketch");

			UpdateData(FALSE);
			delete pRecord;
		}
	}
}

// OnNew /////////////////////////////////////////////////////////////////
//																		//
// Purpose		- Called when user presses the 'New' button				//
//				- Brings up the 'new record' dialog and saves the		//
//				- record to the database								//
// Assumptions	- None													//
// Inputs		- None													//
// Outputs		- None													//
//////////////////////////////////////////////////////////////////////////
void CCEDlg::OnNew() 
{
	CRecordDlg	dlg;

	if (dlg.DoModal() != IDCANCEL)
	{
		if(AddRecord(dlg) == FALSE)
			MessageBox(_T("Error adding record!"), _T("OK"), MB_ICONEXCLAMATION);	

		// Update the results box
		DisplayAllContaining(m_strSearch);
	}
}

// OnRemove //////////////////////////////////////////////////////////////
//																		//
// Purpose		- Called when user presses the 'Remove' button			//
//				- Removes the current record from the database and		//
//				- updates the results box and the text box				//
// Assumptions	- None													//
// Inputs		- None													//
// Outputs		- None													//
//////////////////////////////////////////////////////////////////////////
void CCEDlg::OnRemove() 
{
	CEOID		oid;

	UpdateData(TRUE);

	// Get the index of the selected record
	int nIndex = m_Results.GetCurSel();

	if(nIndex == LB_ERR)
	{
		// No selection, make sure the buttons are disabled
		m_btnRemove.EnableWindow(FALSE);
		m_btnEdit.EnableWindow(FALSE);
		return;
	}

	oid = m_Results.GetItemData(nIndex);

	// remove the record from the database
	RemoveRecord(oid);

	// remove the record from the results box
	m_Results.DeleteString(nIndex);

	// Update the results box
	DisplayAllContaining(m_strSearch);
}

// OnEdit ////////////////////////////////////////////////////////////////
//																		//
// Purpose		- Called when user hits the 'edit' buttons				//
//				- Used to modify existing records						//
// Assumptions	- mDatabase is a valid CCeDBDatabase					//
// Inputs		- None													//
// Outputs		- None													//
//////////////////////////////////////////////////////////////////////////
void CCEDlg::OnEdit() 
{
	CRecordDlg	 dlg;
	CEOID		 oid;
	CEBLOB		 blob;
	CCeDBProp	*pProp;
	CCeDBRecord *pRecord;

	UpdateData(TRUE);

	// Get the current selection
	int nIndex = m_Results.GetCurSel();

	if(nIndex == LB_ERR)
	{
		// Disable the edit and remove buttons and return
		m_btnEdit.EnableWindow(FALSE);
		m_btnRemove.EnableWindow(FALSE);
		return;
	}

	// Grab the selected records OID
	oid = m_Results.GetItemData(nIndex);

	if(oid)
	{
		// Find the record...
		if(mDatabase.SeekToRecord(oid))
		{
			pRecord = new CCeDBRecord;

			// ...and read it.
			mDatabase.ReadCurrRecord(pRecord);

			// If there's a sketch associated
			if(pRecord->GetNumProps() > 1)
			{
				pProp = pRecord->GetPropFromIndex(1);

				// make sure the property is really a blob (byte array)
				if(pProp && LOWORD(pProp->m_CePropVal.propid) == CEVT_BLOB)
				{
					// get the sketch data
					blob = pProp->GetBlob();

					// and pass it to the 'edit record' dialog
					dlg.SetSketchData(blob.lpb, blob.dwCount);
				}

				if(pProp)
					delete pProp;
			}

			delete pRecord;
		}
	}

	// we already have the text data, so just pass it straight through
	dlg.SetTextData(m_strData);

	if(dlg.DoModal() != IDCANCEL)
	{
		oid = m_Results.GetItemData(nIndex);

		// to update, remove the old record...
		RemoveRecord(oid);
		m_Results.DeleteString(nIndex);

		// ...and add the new one
		if(AddRecord(dlg) == FALSE)
			MessageBox(_T("Error editing record!"), _T("OK"), MB_ICONEXCLAMATION);

		// update the results box
		DisplayAllContaining(m_strSearch);
	}
}

// RemoveRecord //////////////////////////////////////////////////////////
//																		//
// Purpose		- To remove a record from the DB based on its OID		//
// Assumptions	- mDatabase is a valid CCeDBDatabase					//
// Inputs		- (CEOID) oid - the OID of the record to remove			//
// Outputs		- None													//
//////////////////////////////////////////////////////////////////////////
void CCEDlg::RemoveRecord(CEOID oid)
{
	if(!oid)
		return;

	// Find the record
	if (!mDatabase.SeekToRecord(oid))
		return;

	// and delete it
	mDatabase.DeleteCurrRecord();

	// clear the text box
	m_strData.Empty();
	UpdateData(FALSE);
}

// AddRecord /////////////////////////////////////////////////////////////
//																		//
// Purpose		- To add a new record to the DB based on the dlg info	//
// Assumptions	- The information in dlg is valid						//
//				- mDatabase is a valid CCeDBDatabase					//
// Inputs		- (CRecordDlg&) dlg - A reference to the dialog			//
//				- containing the information to be added				//
// Outputs		- (BOOL) TRUE for success, FALSE for failure			//
//////////////////////////////////////////////////////////////////////////
BOOL CCEDlg::AddRecord(CRecordDlg & dlg)
{
	CCeDBRecord		*pRecord;
	CCeDBProp		*pProp_Text,
					*pProp_Blob = NULL;

	LPBYTE			 lpData;
	long			 nSize;
	CEBLOB			 blob;

	pRecord		= new CCeDBRecord;
	pProp_Text	= new CCeDBProp;

	// Grab the text data from the dialog and assign it to a property
	pProp_Text->SetString(dlg.GetTextData().GetBuffer(MAXBUFFERSIZE));

	// add the property to the record
	pRecord->AddProp(pProp_Text);
	
	lpData = dlg.GetSketchData();
	nSize = dlg.GetSketchSize();

	// if there is a sketch...
	if(nSize)
	{		
		pProp_Blob = new CCeDBProp;

		blob.dwCount = nSize;
		blob.lpb = lpData;

		// assign sketch data to a property
		pProp_Blob->SetBlob(blob);

		// and add the property to the record
		pRecord->AddProp(pProp_Blob);

		// note: dlg.GetSketchData() returns a copy of the data, so we must free it
		delete lpData;
	}

	// add the record to the database
	BOOL b = mDatabase.AddRecord(pRecord);


	// clean up
	delete pRecord;
	delete pProp_Text;

	if(pProp_Blob)
		delete pProp_Blob;

	return b;
}
