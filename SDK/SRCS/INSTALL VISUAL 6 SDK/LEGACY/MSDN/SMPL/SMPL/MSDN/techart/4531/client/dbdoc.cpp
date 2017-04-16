// DBdoc.cpp : implementation of the CDBDoc class
//

#include "stdafx.h"
#include "DB.h"

#include "DBdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBDoc

IMPLEMENT_DYNCREATE(CDBDoc, CDocument)

BEGIN_MESSAGE_MAP(CDBDoc, CDocument)
	//{{AFX_MSG_MAP(CDBDoc)
	ON_COMMAND(ID_DATABASE_CREATE, OnDatabaseCreate)
	ON_COMMAND(ID_DATABASE_WRITE, OnDatabaseWrite)
	ON_COMMAND(ID_DATABASE_READ, OnDatabaseRead)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_WRITE, OnUpdateDatabaseWrite)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_READ, OnUpdateDatabaseRead)
	ON_COMMAND(ID_DATABASE_READMULTIPLE, OnDatabaseReadMultiple)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_READMULTIPLE, OnUpdateDatabaseReadMultiple)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBDoc construction/destruction

CDBDoc::CDBDoc()
{
	// TODO: add one-time construction code here
	m_pDB=NULL;
}

CDBDoc::~CDBDoc()
{	
	if (m_pDB) {
		m_pDB->Release(); //CPPToCOM: let some code in the DLL delete the object instead of using delete directly
		// otherwise, we deallocate memory allocated by the DLL...
		m_pDB=NULL;
		}
}

BOOL CDBDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	// create a database object through the exported function & class factory object
	IClassFactory *pDBFactory=NULL;
	
	HRESULT hRes;
	if (AfxMessageBox(_T("Do you want a local server?"), MB_YESNO)==IDYES) {
		hRes=CoGetClassObject(CLSID_DBSAMPLE, CLSCTX_LOCAL_SERVER, NULL, IID_IClassFactory, (LPVOID*) &pDBFactory);
		}
	else {
		hRes=CoGetClassObject(CLSID_DBSAMPLE, CLSCTX_SERVER, NULL, IID_IClassFactory, (LPVOID*) &pDBFactory);
		}
	if (FAILED(hRes)) {
		CString csError;
		csError.Format(_T("Error %x obtaining class factory for DB Object!"), hRes);
		AfxMessageBox(csError);
		return FALSE;
		}

	hRes=pDBFactory->CreateInstance(NULL, IID_IUnknown, (void**) &m_pDB);
	if (FAILED(hRes)) {
		CString csError;
		csError.Format(_T("Error %x creating DB Object!"), hRes);
		AfxMessageBox(csError);
		return FALSE;
		}
	
	pDBFactory->Release(); // do not need the factory anymore

	// equivalent way of creating object:
	//   hRes=CoCreateInstance(CLSID_DBSAMPLE, NULL, CLSCTX_SERVER, IID_IDB, (void**) &pDBFactory);

	// initialize state of the document:
	m_csData="No data yet!"; // string displayed in views: last data read
	m_nCount=0;							 // number of writes done through this document
	m_nTable=-1;						 // number of last table created through this document
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDBDoc serialization

void CDBDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDBDoc diagnostics

#ifdef _DEBUG
void CDBDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDBDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDBDoc commands

void CDBDoc::OnDatabaseCreate() 
{
	IDBManage* pManage=NULL;
	if (FAILED(m_pDB->QueryInterface(IID_IDBManage, (void**) &pManage))) {
		AfxMessageBox(_T("Error in QueryInterface for IDBManage!"));
		return;
		}
	pManage->Create(m_nTable, L"Testing");	
	m_nCount=0; // set number of writes to 0 
	pManage->Release();
}

void CDBDoc::OnDatabaseWrite() 
{
	IDBAccess* pAccess=NULL;
	if (FAILED(m_pDB->QueryInterface(IID_IDBAccess, (void**) &pAccess))) {
		AfxMessageBox(_T("Error in QueryInterface for IDBAccess!"));
		return;
		}
	m_nCount++;
	CString csText;
	csText.Format(_T("Test data #%d in table %d, row 0!"), m_nCount, (int) m_nTable);
#ifdef UNICODE
	pAccess->Write(m_nTable, 0, csText);
#else
	WCHAR szuText[80]; // special treatment for ASCII client
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, csText, -1, szuText, sizeof(szuText));
	pAccess->Write(m_nTable, 0, szuText);
#endif
	pAccess->Release();
}

void CDBDoc::OnDatabaseRead() 
{
	IDBAccess* pAccess=NULL;
	if (FAILED(m_pDB->QueryInterface(IID_IDBAccess, (void**) &pAccess))) {
		AfxMessageBox(_T("Error in QueryInterface for IDBAccess!"));
		return;
		}
#ifdef UNICODE
	pAccess->Read(m_nTable, 0, m_csData.GetBuffer(80));
#else
	WCHAR szuData[80];
	pAccess->Read(m_nTable, 0, szuData);
	WideCharToMultiByte(CP_ACP, 0, szuData, -1, m_csData.GetBuffer(80), 80, NULL, NULL);
#endif
	m_csData.ReleaseBuffer();
	UpdateAllViews(NULL);
	pAccess->Release();
}

void CDBDoc::OnUpdateDatabaseWrite(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_nTable>=0);	
}

void CDBDoc::OnUpdateDatabaseRead(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_nCount>0);
}

void CDBDoc::OnDatabaseReadMultiple() 
{
	IDBAccess* pAccess=NULL;
	if (FAILED(m_pDB->QueryInterface(IID_IDBAccess, (void**) &pAccess))) {
		AfxMessageBox(_T("Error in QueryInterface for IDBAccess!"));
		return;
		}
	int nCount=AfxGetApp()->GetProfileInt(_T("ReadMultiple"),_T("NumCalls"), 10000);

#ifdef UNICODE
	LPTSTR lpData=m_csData.GetBuffer(80);
#else
	WCHAR lpData[80];
#endif

	DWORD startTime=GetCurrentTime();
	for (int i=0; i<nCount; i++) {
		pAccess->Read(m_nTable, 0, lpData);
		}
	DWORD endTime=GetCurrentTime();

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, lpData, -1, m_csData.GetBuffer(80), 80, NULL, NULL);
#endif

	m_csData.ReleaseBuffer();

	DWORD dif=endTime-startTime;
	CString csText;
	if (dif>10) {
		csText.Format(_T("%d calls: %.3f seconds - %d CPS"), nCount, (float) dif/1000, nCount*1000/dif);
		AfxMessageBox(csText);
		}
	else {
		AfxMessageBox(_T("Too few calls: timing invalid. Change [ReadMultiple] NumCalls in INI"));
		}
	pAccess->Release();
}

void CDBDoc::OnUpdateDatabaseReadMultiple(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_nCount>0);
}
