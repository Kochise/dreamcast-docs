// EmpBiz.cpp : implementation file
//
#define INITGUID
#include "stdafx.h"
#include "Emp.h"
#include "EmpBiz.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define THROW_ERR(exp)	if (FAILED(hr = (exp))) throw hr

const LPCWSTR g_lpcwszSource = L"OLE_DB_NWind_Jet;";
const LPCWSTR g_lpcwszUser = L"Admin";
const LPCWSTR g_lpcwszPwd = L"";
const LPCWSTR g_lpcwszSQL = L"select EmployeeId, LastName, FirstName, Title, HomePhone from Employees";

static bool fResetFilter = false;

/////////////////////////////////////////////////////////////////////////////
// CEmpBiz 

CEmpBiz::CEmpBiz()
{
	m_piConnection = NULL;
	m_piEmpRecordSet = NULL; 
	m_fConnected = FALSE;
	m_fRecordsetEmpty = TRUE;
}

CEmpBiz::~CEmpBiz()
{	
	if ( m_piConnection != NULL )
		m_piConnection->Release();			 		
	if ( m_piEmpRecordSet != NULL )
		m_piEmpRecordSet->Release();			 		
	m_varLastGoodRecord.Clear();
	m_piConnection = NULL;
	m_piEmpRecordSet = NULL;
}



long CEmpBiz::GetEmployeeId() 
{
	HRESULT			hr;
	COleVariant		vFldName, vID;
	
	if (!m_fConnected)
		return 0;

	//Watch for empty recordset
	if(m_fRecordsetEmpty)
		return 0;

	vFldName.bstrVal = CString(EMP_EMPLOYEE_ID).AllocSysString();
	vFldName.vt = VT_BSTR;
	THROW_ERR(	 m_piEmpRecordSet->get_Collect(vFldName, vID)	);
	
	return VTOLONG(vID);
}

		
CString CEmpBiz::GetFirstName() 
{
	HRESULT			hr;
	COleVariant		vFldName, vFirstName;

 	if (!m_fConnected)
		return "";

	//Watch for empty recordset
	if(m_fRecordsetEmpty)
		return "";

	vFldName.bstrVal = CString(EMP_FIRST_NAME).AllocSysString();
	vFldName.vt = VT_BSTR;
	THROW_ERR(	m_piEmpRecordSet->get_Collect(vFldName, vFirstName) );
	
	return VTOCSTR(vFirstName);
}
	 			 	
CString CEmpBiz::GetLastName() 
{
	HRESULT			hr;
	COleVariant		vFldName, vLastName;

 	if (!m_fConnected)
		return "";

	//Watch for empty recordset
	if(m_fRecordsetEmpty)
		return "";

	vFldName.bstrVal = CString(EMP_LAST_NAME).AllocSysString();
	vFldName.vt = VT_BSTR;
	THROW_ERR(	m_piEmpRecordSet->get_Collect(vFldName, vLastName) );
	
	return VTOCSTR(vLastName);
}
						 	
CString CEmpBiz::GetHomePhone() 
{
	HRESULT			hr;
	COleVariant		vFldName, vHomePhone;
 
 	if (!m_fConnected)
		return "";

	//Watch for empty recordset
	if(m_fRecordsetEmpty)
		return "";

	vFldName.bstrVal = CString(EMP_HOME_PHONE).AllocSysString();
	vFldName.vt = VT_BSTR;
	THROW_ERR(	m_piEmpRecordSet->get_Collect(vFldName, vHomePhone) );
	
	return VTOCSTR(vHomePhone);
}
			  		 	
CString CEmpBiz::GetTitle() 
{
	HRESULT			hr;
	COleVariant		vFldName, vTitle;

 	if (!m_fConnected)
		return "";

	//Watch for empty recordset
	if(m_fRecordsetEmpty)
		return "";

	vFldName.bstrVal = CString(EMP_TITLE).AllocSysString();
	vFldName.vt = VT_BSTR;
	THROW_ERR(	m_piEmpRecordSet->get_Collect(vFldName, vTitle) );
	
	return VTOCSTR(vTitle);
}

		  

BOOL CEmpBiz::IsAddMode() 
{
	HRESULT			hr;
 	EditModeEnum	lEditMode;

	THROW_ERR(	m_piEmpRecordSet->get_EditMode(&lEditMode) );

	return lEditMode == adEditAdd ;
}


void CEmpBiz::AddRecord() 
{
	// TODO: Add your control notification handler code here
	HRESULT			hr;
	VARIANT			rgvFields;
	VARIANT			rgvValues;

	if (!m_fConnected)
		return;

	ClearFilter() ;

	//Watch for empty recordset
	if(!m_fRecordsetEmpty && !IsAddMode() )
	{
		//Remember where we were before adding in case the user
		//cancels and we have to return
		THROW_ERR(	m_piEmpRecordSet->get_Bookmark(m_varLastGoodRecord) );
	}

	rgvFields.vt = VT_ERROR;
	rgvFields.scode = DISP_E_PARAMNOTFOUND;

	rgvValues.vt = VT_ERROR;
	rgvValues.scode = DISP_E_PARAMNOTFOUND;

	THROW_ERR(	m_piEmpRecordSet->AddNew(rgvFields, rgvValues) );
//	THROW_ERR(	 m_piEmpRecordSet->Update(rgvFields, rgvValues) );

	m_fRecordsetEmpty = FALSE;
	return ;
}

void CEmpBiz::CancelPendingAdd()
{
	HRESULT hr;
	THROW_ERR(	 m_piEmpRecordSet->CancelUpdate() );
	THROW_ERR(	 m_piEmpRecordSet->put_Bookmark(m_varLastGoodRecord) );
}

void CEmpBiz::DeleteRecord() 
{
	// TODO: Add your control notification handler code here
	HRESULT			hr;
 	EditModeEnum	lEditMode;
	VARIANT_BOOL	vbEOF, vbBOF;

	//Watch for empty recordset
	if (!m_fConnected || m_fRecordsetEmpty)
		return;

	//Delete method depends on current mode
	THROW_ERR(	m_piEmpRecordSet->get_EditMode(&lEditMode) );

	switch (lEditMode)
	{
		case adEditNone: // Just delete it
		{
			THROW_ERR(	 m_piEmpRecordSet->Delete(adAffectCurrent) );
			THROW_ERR(	 m_piEmpRecordSet->MoveNext() );
			//Watch for end of record set
			THROW_ERR(	 m_piEmpRecordSet->get_EOF(&vbEOF) );
			if(vbEOF)
			{
				THROW_ERR(	m_piEmpRecordSet->MovePrevious() );
				//Check for empty record set.
				THROW_ERR(	 m_piEmpRecordSet->get_BOF(&vbBOF) );
				if(vbBOF)
					m_fRecordsetEmpty  = TRUE;
			}
			break;
		}

		case adEditInProgress: //Forget changes
		{
			THROW_ERR(	 m_piEmpRecordSet->CancelUpdate() );
			THROW_ERR(	 m_piEmpRecordSet->Delete(adAffectCurrent) );
			THROW_ERR(	 m_piEmpRecordSet->MoveFirst() );
			break;
		}

		case adEditAdd: //If new record, go back to last known
		{
			THROW_ERR(	 m_piEmpRecordSet->CancelUpdate() );
			THROW_ERR(	 m_piEmpRecordSet->put_Bookmark(m_varLastGoodRecord) );
		}
	}

	return ;
}

BOOL CEmpBiz::MoveNext() 
{
	// TODO: Add your control notification handler code here
	HRESULT		hr;
	VARIANT_BOOL vbEOF;

	if (!m_fConnected || m_fRecordsetEmpty)
		return FALSE;
 
	if (fResetFilter)
		ClearFilter();

	THROW_ERR(	m_piEmpRecordSet->MoveNext() );

	//Watch for end of record set
	THROW_ERR(	m_piEmpRecordSet->get_EOF(&vbEOF) );
	if(vbEOF)
	{
		THROW_ERR(	m_piEmpRecordSet->MovePrevious() );
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}



BOOL CEmpBiz::MovePrevious() 
{
	// TODO: Add your control notification handler code here
	HRESULT		hr;
	VARIANT_BOOL vbBOF;

	if (!m_fConnected || m_fRecordsetEmpty)
		return FALSE;

	if (fResetFilter)
		ClearFilter();

	THROW_ERR(	m_piEmpRecordSet->MovePrevious() );

	//Watch for beginning of recordset
	THROW_ERR(	m_piEmpRecordSet->get_BOF(&vbBOF) );
	if(vbBOF)
	{
		THROW_ERR(	m_piEmpRecordSet->MoveNext() );	 		
		return FALSE;
	}
	else
	{			
		return TRUE;
	}
}



BOOL CEmpBiz::MoveFirst() 
{
	// TODO: Add your control notification handler code here
	HRESULT		hr;
	VARIANT_BOOL vbBOF;

	if (!m_fConnected || m_fRecordsetEmpty)
		return FALSE;

	if (fResetFilter)
		ClearFilter();

	THROW_ERR(	m_piEmpRecordSet->MoveFirst() );

	//Watch for beginning of recordset
	THROW_ERR(	m_piEmpRecordSet->get_BOF(&vbBOF) );
	if(vbBOF)
	{
		return FALSE;
	}
	else
	{			
		return TRUE;
	}
}



BOOL CEmpBiz::MoveLast() 
{
	// TODO: Add your control notification handler code here
	HRESULT		hr;
	VARIANT_BOOL vbEOF;

	if (!m_fConnected || m_fRecordsetEmpty)
		return FALSE;

	if (fResetFilter)
		ClearFilter();

	THROW_ERR(	m_piEmpRecordSet->MoveLast() );

	//Watch for beginning of recordset
	THROW_ERR(	m_piEmpRecordSet->get_BOF(&vbEOF) );
	if(vbEOF)
	{
		return FALSE;
	}
	else
	{			
		return TRUE;
	}
}


BOOL CEmpBiz::FindForward(CString strCriteria) 
{
	HRESULT			hr;
	VARIANT_BOOL	vbEOF;
	COleVariant		v;

	if (!m_fConnected || m_fRecordsetEmpty)
		return FALSE;

	THROW_ERR(	m_piEmpRecordSet->get_Filter(&v) );
	if ( v.vt != VT_BSTR || strCriteria !=	v.bstrVal )
	{
		v.vt = VT_BSTR;
		v.bstrVal = strCriteria.AllocSysString();
		THROW_ERR(  m_piEmpRecordSet->put_Filter(v) );
		fResetFilter = true;
	}
	else
	{
		THROW_ERR( m_piEmpRecordSet->MoveNext() );
	}
		
	//Watch for ending of recordset
	THROW_ERR(	m_piEmpRecordSet->get_EOF(&vbEOF));
	if(vbEOF)
	{			   		
		ClearFilter() ;
		THROW_ERR( m_piEmpRecordSet->MoveLast() );

		return FALSE;
	}
	else
	{			
		return TRUE;
	}
}


void CEmpBiz::ClearFilter() 
{
	HRESULT		hr;
	VARIANT		v;

	if ( !m_fRecordsetEmpty)
	{
		v.vt = VT_I2;
		v.iVal = adFilterNone;
		THROW_ERR(	m_piEmpRecordSet->put_Filter(v) );
		fResetFilter = false;
	}
}

	  


//
//Update record in the database
//
void CEmpBiz::UpdateEmpRec(CString &strFirstName, 
			CString &strHomePhone, CString &strLastName,
			CString &strTitle)
{
	HRESULT		hr;
	VARIANT		varFields;	   	
	VARIANT		varValues;
	WCHAR		*columnNames[4] = { L"firstName", L"Lastname", L"title", L"homePhone"};
	ADOFields	*pFields = NULL;
	ADOField	*pField = NULL;
	CVar		varIndex(VT_BSTR);
	COleVariant	varFieldVal;

	if  (m_fRecordsetEmpty)
		return;

	varFields.vt = VT_ERROR;
	varFields.scode = DISP_E_PARAMNOTFOUND;
	varValues.vt = VT_ERROR;
	varValues.scode = DISP_E_PARAMNOTFOUND;
	
	try
	{
		// get the fields interface
		THROW_ERR(	 m_piEmpRecordSet->get_Fields(&pFields) );

		varIndex = SysAllocString(columnNames[0]) ;
		THROW_ERR(	 pFields->get_Item(varIndex, &pField) );
		varFieldVal.vt = VT_BSTR;
		varFieldVal.bstrVal = strFirstName.AllocSysString();
		THROW_ERR(	 pField->put_Value(varFieldVal) );
		varFieldVal.Clear();

		varIndex = SysAllocString(columnNames[1]) ;
		THROW_ERR(	 pFields->get_Item(varIndex, &pField) );
		varFieldVal.vt = VT_BSTR;
		varFieldVal.bstrVal = strLastName.AllocSysString();
		THROW_ERR(	 pField->put_Value(varFieldVal) );
		varFieldVal.Clear();

		varIndex = SysAllocString(columnNames[2]) ;
		THROW_ERR(	 pFields->get_Item(varIndex, &pField) );
		varFieldVal.vt = VT_BSTR;
		varFieldVal.bstrVal = strTitle.AllocSysString();
		THROW_ERR(	 pField->put_Value(varFieldVal) );
		varFieldVal.Clear();

		varIndex = SysAllocString(columnNames[3]) ;
		THROW_ERR(	 pFields->get_Item(varIndex, &pField) );
		varFieldVal.vt = VT_BSTR;
		varFieldVal.bstrVal = strHomePhone.AllocSysString();
		THROW_ERR(	 pField->put_Value(varFieldVal) );
		varFieldVal.Clear();

		//Commit the changes   	
		THROW_ERR(	 m_piEmpRecordSet->Update(varFields, varValues) );
		
		pField->Release();
		pFields->Release();

		//Return to the edited record
		//CADOBookmark cBookmark = m_piEmpRecordSet->GetLastModified();
		//m_piEmpRecordSet->SetBookmark(cBookmark);
	}
	catch (HRESULT hr)
	{
		if (pField)
			pField->Release();
		if (pFields)
			pFields->Release();
		throw hr;
	}
	return ;
}


/////////////////////////////////////////////////////////////////////////////
// CEmpBiz support 

//When the document is created, connect to the database and open the
//Employee recordset.
BOOL CEmpBiz::ConnectToDatabase()
{

	CVar		varDataSource, varUserId, varPwd, varSQL;
	HRESULT		hr;
	CVar		vNull(VT_ERROR, DISP_E_PARAMNOTFOUND);
	VARIANT_BOOL	vbEOF, vbBOF;

	varDataSource	= g_lpcwszSource;
	varUserId		= g_lpcwszUser;
	varPwd			= g_lpcwszPwd;
	varSQL			= g_lpcwszSQL;

	//Open the database and the recordset
	try
	{
		if ( m_piConnection == NULL || m_piEmpRecordSet == NULL)
		{
			THROW_ERR(	  CoInitialize(NULL) );
			THROW_ERR(	  CoCreateInstance(CLSID_CADOConnection, NULL, CLSCTX_INPROC_SERVER, IID_IADOConnection, (LPVOID *)&m_piConnection) );
			THROW_ERR(	  m_piConnection->Open( varDataSource, varUserId, varPwd, adOpenUnspecified ) );

			THROW_ERR(	  CoCreateInstance(CLSID_CADORecordset, NULL, CLSCTX_INPROC_SERVER, IID_IADORecordset, (LPVOID *)&m_piEmpRecordSet) );
			THROW_ERR(	  m_piEmpRecordSet->putref_ActiveConnection(m_piConnection) );	
			THROW_ERR(	  m_piEmpRecordSet->put_Source(varSQL) );		 

			vNull.vt = VT_ERROR;
			vNull.scode = DISP_E_PARAMNOTFOUND;
			THROW_ERR(	  m_piEmpRecordSet->Open(vNull, vNull, adOpenKeyset, adLockOptimistic, adCmdText) );		

			//Check for empty record set.
			THROW_ERR(	 m_piEmpRecordSet->get_EOF(&vbEOF) );
			THROW_ERR(	 m_piEmpRecordSet->get_BOF(&vbBOF) );
			if(vbEOF && vbBOF)
				m_fRecordsetEmpty  = TRUE;
			else
				m_fRecordsetEmpty  = FALSE;
		}

		return TRUE;
	}
	catch (HRESULT hr)
	{
		PopupErrorMessage(hr);
		return (FALSE);
	}
}

void PopupErrorMessage(HRESULT hr)
{
	IErrorInfo *pei = NULL;
	if (::GetErrorInfo(0, &pei) == S_OK)
	{
		BSTR err;
		int wlen = 0;
		TCHAR szBuff[1024];

		pei->GetDescription(&err);
		pei->Release();
		wlen = WideCharToMultiByte(CP_ACP, 0, err, SysStringLen(err), szBuff, 1023, NULL, NULL);
		SysFreeString(err);
		if (wlen > 0)
		{
			szBuff[wlen] = '\0';
			AfxMessageBox(szBuff);
			return;
		}
	}

	TCHAR szBuf[256];
	wsprintf(szBuf, _T("Error: %X \n"), hr);
	AfxMessageBox(szBuf);
}
