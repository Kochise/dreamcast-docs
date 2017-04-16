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
	ON_UPDATE_COMMAND_UI(ID_DATABASE_READ, OnUpdateDatabaseRead)
	ON_UPDATE_COMMAND_UI(ID_DATABASE_WRITE, OnUpdateDatabaseWrite)
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
		delete m_pDB;
		m_pDB=NULL;
		}
}

BOOL CDBDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	//CPPtoCOM: create a database object
	m_pDB=new CDB;
	
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
	m_pDB->Create(m_nTable, _T("Testing"));	
	m_nCount=0; // set number of writes to 0 
}

void CDBDoc::OnDatabaseWrite() 
{
	m_nCount++;
	CString csText;
	csText.Format(_T("Test data #%d in table %d, row 0!"), m_nCount, (int) m_nTable);
	m_pDB->Write(m_nTable, 0, csText);
}

void CDBDoc::OnDatabaseRead() 
{
	m_pDB->Read(m_nTable, 0, m_csData.GetBuffer(80));
	m_csData.ReleaseBuffer();
	UpdateAllViews(NULL);
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
	int nCount=AfxGetApp()->GetProfileInt(_T("ReadMultiple"),_T("NumCalls"), 10000);
	LPTSTR lpData=m_csData.GetBuffer(80);

	DWORD startTime=GetCurrentTime();
	for (int i=0; i<nCount; i++) {
		m_pDB->Read(m_nTable, 0, lpData);
		}
	DWORD endTime=GetCurrentTime();

	m_csData.ReleaseBuffer();
	lpData=NULL;

	DWORD dif=endTime-startTime;
	CString csText;
	if (dif>10) {
		csText.Format(_T("%d calls: %.3f seconds - %d CPS"), nCount, (float) dif/1000, nCount*1000/dif);
		AfxMessageBox(csText);
		}
	else {
		AfxMessageBox(_T("Too few calls: timing invalid. Change [ReadMultiple] NumCalls in INI"));
		}
}

void CDBDoc::OnUpdateDatabaseReadMultiple(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_nCount>0);
}
