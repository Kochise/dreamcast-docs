//-----------------------------------------------------------------------------
// Microsoft OLE DB TABLECOPY Sample
// Copyright (C) 1995-1998 Microsoft Corporation
//
// @doc
//
// @module STEP3.CPP
//
//-----------------------------------------------------------------------------



/////////////////////////////////////////////////////////////////////
// Includes
//
/////////////////////////////////////////////////////////////////////
#include "wizard.h"
#include "common.h"
#include "Tablecopy.h"
#include "Table.h"


/////////////////////////////////////////////////////////////////////
// CS3Dialog::CS3Dialog
//
/////////////////////////////////////////////////////////////////////
CS3Dialog::CS3Dialog(HWND hWnd, HINSTANCE hInst, CTableCopy* pCTableCopy)
	: CDialogBase(hWnd, hInst)
{
	ASSERT(pCTableCopy);
	m_pCTableCopy = pCTableCopy;
}


/////////////////////////////////////////////////////////////////////
// CS3Dialog::~CS3Dialog
//
/////////////////////////////////////////////////////////////////////
CS3Dialog::~CS3Dialog()
{
}


/////////////////////////////////////////////////////////////////////////////
// ULONG CS3Dialog::Display
//
/////////////////////////////////////////////////////////////////////////////
ULONG CS3Dialog::Display()
{
	//Create a modal dialog box
	return DialogBoxParam(m_hInst, MAKEINTRESOURCE(IDD_TO_INFO), NULL, DlgProc, (LPARAM)this);
}


/////////////////////////////////////////////////////////////////////
// CS3Dialog::DlgProc
//
/////////////////////////////////////////////////////////////////////
BOOL WINAPI CS3Dialog::DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg) 
	{
		case WM_INITDIALOG:
		{
			Busy();
			//Store the "this" pointer, since this is a static method
			CS3Dialog* pThis = (CS3Dialog*)lParam;
			SetWindowLong(hWnd, GWL_USERDATA, (LONG)pThis);
			
			//On INIT we know we have a valid hWnd to store
			CenterDialog(hWnd);
			pThis->m_hWnd = hWnd;

			//Init all controls to the default values
			pThis->InitControls();
			
			//Limit the length of User Entered TableName
			SendDlgItemMessage(hWnd, IDE_TO_TABLE, EM_LIMITTEXT, (WPARAM)MAX_NAME_LEN-1, 0L);

			pThis->RefreshControls();
			pThis->m_pCTableCopy->m_pCWizard->DestroyPrevStep(WIZ_STEP3);
			return HANDLED_MSG;
		}
		
		case WM_COMMAND:
		{
			//Obtain the "this" pointer
			CS3Dialog* pThis = (CS3Dialog*)GetWindowLong(hWnd, GWL_USERDATA);

			CTable* pCFromTable = pThis->m_pCTableCopy->m_pCFromTable;		
			CTable* pCToTable = pThis->m_pCTableCopy->m_pCToTable;		
			CDataSource* pCToDataSource = pCToTable->m_pCDataSource;		
			CDataSource* pCFromDataSource = pCFromTable->m_pCDataSource;		

			// All buttons are handled the same way
			switch(GET_WM_COMMAND_ID(wParam, lParam)) 
			{
				case IDB_TO_CONNECT:
				{
					Busy();
					if(pThis->Connect()) 
					{
						Busy();
						pThis->RefreshControls();
						SetFocus(GetDlgItem(hWnd, IDE_TO_TABLE));
						SendMessage(GetDlgItem(hWnd, IDE_TO_TABLE), EM_SETSEL, 0, -1); //Highlight TableName
					}
					return HANDLED_MSG;
				}

                case IDOK:
				{	
					//Get the TableName
					Busy();
					wSendMessage(GetDlgItem(hWnd, IDE_TO_TABLE), WM_GETTEXT, MAX_NAME_LEN-1, pCToTable->m_TableInfo.wszTableName);
					
					//If the TableNames are the same (ignoring case) and the 
					//DataSource is the same then the copy is worthless (a no-op)
					if(_wcsicmp(pCToTable->m_TableInfo.wszTableName, pCFromTable->m_TableInfo.wszTableName)==0 &&
						pCToDataSource->IsEqual(pCFromDataSource))
					{
						//Need to enter a different table name from the source
						wMessageBox(hWnd, MB_TASKMODAL | MB_ICONEXCLAMATION | MB_OK, 	
							wsz_ERROR, wsz_SAME_TABLE_NAME, pCToDataSource->m_pwszTableTerm);
						SetFocus(GetDlgItem(hWnd, IDE_TO_TABLE));
						SendMessage(GetDlgItem(hWnd, IDE_TO_TABLE), EM_SETSEL, 0, -1); //Highlight TableName
						return HANDLED_MSG;
					}
					
					wcscpy(pCToTable->m_wszQualTableName, pCToTable->m_TableInfo.wszTableName);
					pThis->m_pCTableCopy->m_pCWizard->DisplayStep(WIZ_STEP4);
					return HANDLED_MSG;
				}
                
                case IDB_PREV:
					//Get the TableName
					Busy();
					wSendMessage(GetDlgItem(hWnd, IDE_TO_TABLE), WM_GETTEXT, MAX_NAME_LEN-1, pCToTable->m_TableInfo.wszTableName);
					wcscpy(pCToTable->m_wszQualTableName,pCToTable->m_TableInfo.wszTableName);
					pThis->m_pCTableCopy->m_pCWizard->DisplayStep(WIZ_STEP2);
                	return HANDLED_MSG;

				case IDCANCEL:
					Busy();
                	EndDialog(hWnd, GET_WM_COMMAND_ID(wParam, lParam));
                	return HANDLED_MSG;
			}

			// Now look for notification messages
			switch(GET_WM_COMMAND_CMD(wParam, lParam)) 
			{
				case LBN_SELCHANGE:
				{
					//A Provider Change requires a refresh
					if(IDC_PROVIDER_NAME == GET_WM_COMMAND_ID(wParam, lParam)) 
					{
						//Get new selection
						Busy();
						LONG iSel = 0;
						if((iSel = SendMessage(GetDlgItem(pThis->m_hWnd, IDC_PROVIDER_NAME), CB_GETCURSEL, 0, 0L)) != CB_ERR)
						{
							//Since we have the CBS_SORT turned on, the order in the Combo Box does
							//not match our array, so we pass the array index (lParam) as the item data
							LONG lParam = SendMessage(GetDlgItem(pThis->m_hWnd, IDC_PROVIDER_NAME), CB_GETITEMDATA, iSel, 0L);
							if((lParam < (LONG)pCToDataSource->m_cProviderInfo) && (wcscmp(pCToDataSource->m_rgProviderInfo[lParam].wszName, pCToDataSource->m_pwszProviderName)!=0))
							{
								pCToDataSource->Disconnect();
							}
						}
					}

					pThis->RefreshControls();
				}
				
				case EN_CHANGE:
				{
					pThis->EnableTable();
					return HANDLED_MSG;
				}
			}
		}
	}

	return UNHANDLED_MSG;
}




/////////////////////////////////////////////////////////////////////////////
// BOOL CS3Dialog::InitControls
//
/////////////////////////////////////////////////////////////////////////////
BOOL CS3Dialog::InitControls()
{
	//Initialize the Provider List (if not done so already)
	CDataSource* pCDataSource = m_pCTableCopy->m_pCToTable->m_pCDataSource;
	CDataSource* pCFromDataSource = m_pCTableCopy->m_pCFromTable->m_pCDataSource;
	
	if(pCDataSource->m_rgProviderInfo == NULL)
		pCDataSource->GetProviders();
	
	WCHAR wszBuffer[MAX_NAME_LEN*2];
	HWND hWndProv = GetDlgItem(m_hWnd, IDC_PROVIDER_NAME);

	//Fill out the provider name combo box.
	for(ULONG i=0; i<pCDataSource->m_cProviderInfo; i++)
	{
		//Add the name to the list
		//Since we have the CBS_SORT turned on, the order in the Combo Box does
		//not match our array, so we pass the array index (lParam) as the item data
		swprintf(wszBuffer, wsz_PROVIDER_INFO_, pCDataSource->m_rgProviderInfo[i].wszName, pCDataSource->m_rgProviderInfo[i].wszDescription);
		LONG iIndex = wSendMessage(hWndProv, CB_ADDSTRING, (WPARAM)0, wszBuffer);
		SendMessage(hWndProv, CB_SETITEMDATA, (WPARAM)iIndex, (LPARAM)i);
	}
	
	//By default, it selects the same provider chossen in Step1
	if(pCDataSource->m_pwszProviderName == NULL)
		pCDataSource->m_pwszProviderName = pCFromDataSource->m_pwszProviderName;

	//Try and select the previous selected Provider
	if(CB_ERR == wSendMessage(hWndProv, CB_SELECTSTRING, 0, pCDataSource->m_pwszProviderName))
	{
		//If not found, just select the first one
		SendMessage(hWndProv, CB_SETCURSEL, 0, 0);
	}

	//By default, try and Connect to the same DataSource as in Step1
	//if using the same provider as in Step1
	if(!m_pCTableCopy->m_pCToTable->IsConnected() && wcscmp(pCDataSource->m_pwszProviderName, pCFromDataSource->m_pwszProviderName)==0)
	{
		//The Provider must support more than 1 active session as well to do
		//this functionality by default...
		if(pCFromDataSource->m_ulActiveSessions==0 || pCFromDataSource->m_ulActiveSessions>=2)
			Connect(pCFromDataSource);
	}

	// Enable Connect button only if there are providers installed.
	EnableWindow(GetDlgItem(m_hWnd, IDB_FROM_CONNECT), SendMessage(hWndProv, CB_GETCURSEL, 0, 0L) != CB_ERR);

	// Set the "Source" info
	//CONNECT_STRING
	wSetDlgItemText(m_hWnd, IDT_FROM_CONNECT, wsz_CONNECT_STRING_,
		pCFromDataSource->m_pwszProviderName, 
		pCFromDataSource->m_pwszDataSource, 
		pCFromDataSource->m_pwszDBMS,
		pCFromDataSource->m_pwszDBMSVer,
		pCFromDataSource->m_pwszProviderFileName,
		pCFromDataSource->m_pwszProviderVer);

	//TABLE
	wSetDlgItemText(m_hWnd, IDE_FROM_TABLE, m_pCTableCopy->m_pCFromTable->m_wszQualTableName);
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// BOOL CS3Dialog::RefreshControls
//
/////////////////////////////////////////////////////////////////////////////
BOOL CS3Dialog::RefreshControls()
{
	BOOL		fConnected;
	
	CTable* pCToTable = m_pCTableCopy->m_pCToTable;
	CTable* pCFromTable = m_pCTableCopy->m_pCFromTable;
	CDataSource* pCDataSource = pCToTable->m_pCDataSource;

	// Must have a connection to edit other controls
	fConnected = pCToTable->IsConnected();

	//Enable certain dialog controls, only if connected
	EnableWindow(GetDlgItem(m_hWnd, IDE_TO_TABLE),		fConnected);
	EnableWindow(GetDlgItem(m_hWnd, IDT_TARGET),		fConnected);
	EnableWindow(GetDlgItem(m_hWnd, IDT_TOTABLEHELP),	fConnected);
	
	//Store the selected ProviderName and ProviderDesc
	LONG iSel = 0;
	if((iSel = SendMessage(GetDlgItem(m_hWnd, IDC_PROVIDER_NAME), CB_GETCURSEL, 0, 0L)) != CB_ERR)
	{
		//Since we have the CBS_SORT turned on, the order in the Combo Box does
		//not match our array, so we pass the array index (lParam) as the item data
		LONG lParam = SendMessage(GetDlgItem(m_hWnd, IDC_PROVIDER_NAME), CB_GETITEMDATA, iSel, 0L);
		ASSERT(lParam < (LONG)pCDataSource->m_cProviderInfo);
		pCDataSource->m_pwszProviderName = pCDataSource->m_rgProviderInfo[lParam].wszName;
		pCDataSource->m_pwszProviderParseName = pCDataSource->m_rgProviderInfo[lParam].wszParseName;
	}
	
	// Show user the connection string, and enable Next that requires connection
	if(fConnected)
	{
		//CONNECTSTATUS
		SetDlgItemText(m_hWnd, IDT_CONNECTSTATUS, "");
		
		//CONNECT_STRING
		wSetDlgItemText(m_hWnd, IDT_TO_CONNECT, wsz_CONNECT_STRING_,
			pCDataSource->m_pwszProviderName, 
			pCDataSource->m_pwszDataSource, 
			pCDataSource->m_pwszDBMS,
			pCDataSource->m_pwszDBMSVer,
			pCDataSource->m_pwszProviderFileName,
			pCDataSource->m_pwszProviderVer);

		//TABLEHELPMSG
		wSetDlgItemText(m_hWnd, IDT_TOTABLEHELP, wsz_TOTABLEHELP_, 
			pCDataSource->m_pwszTableTerm);
	}
	else
	{
		//CONNECTSTATUS
		wSetDlgItemText(m_hWnd, IDT_CONNECTSTATUS, wsz_NOT_CONNECTED);

		//CONNECT_STRING
		wSetDlgItemText(m_hWnd, IDT_TO_CONNECT, L"");
	}
	
	// If there is already a Table from previous selections, just use that one
	wSetDlgItemText(m_hWnd, IDE_TO_TABLE, pCToTable->m_TableInfo.wszTableName[0] ? pCToTable->m_TableInfo.wszTableName : pCFromTable->m_TableInfo.wszTableName);
	
	// Determine if there is enough information to move on
	return EnableTable();
}

		


/////////////////////////////////////////////////////////////////////////////
// BOOL CS3Dialog::Connect
//
/////////////////////////////////////////////////////////////////////////////
BOOL CS3Dialog::Connect(CDataSource* pCDataSource)
{
	CDataSource* pCToDataSource = m_pCTableCopy->m_pCToTable->m_pCDataSource;
	CDataSource* pCFromDataSource = m_pCTableCopy->m_pCFromTable->m_pCDataSource;
	
	//Connect to the DataSource
	BOOL fConnected = m_pCTableCopy->m_pCToTable->Connect(m_hWnd, pCDataSource);
	
	//If Connected
	if(fConnected)
	{
		// Verify we can use this data source
		// Just give a warning to the user, since the DataSource may actually
		// be updatable, but it is returning the wrong property value.
		if(pCToDataSource->m_fReadOnly) 
		{
			wMessageBox(m_hWnd, MB_TASKMODAL | MB_ICONEXCLAMATION | MB_OK, 	wsz_WARNING, 
					wsz_READONLY_DATASOURCE_, pCToDataSource->m_pwszDataSource);
		}

		//See if this is a similar DSN than the Source
		//If DSN's are not similar, then we need to translate
		m_pCTableCopy->m_fTranslate = !pCToDataSource->IsSimilar(pCFromDataSource);
	}

	return fConnected;
}


/////////////////////////////////////////////////////////////////////////////
// BOOL CS3Dialog::EnableTable
//
/////////////////////////////////////////////////////////////////////////////
BOOL CS3Dialog::EnableTable()
{
	BOOL fConnected = m_pCTableCopy->m_pCToTable->IsConnected();
	
	EnableWindow(GetDlgItem(m_hWnd, IDOK), 
			fConnected && SendDlgItemMessage(m_hWnd, IDE_TO_TABLE, WM_GETTEXTLENGTH, 0, 0L));

	return TRUE;
}
