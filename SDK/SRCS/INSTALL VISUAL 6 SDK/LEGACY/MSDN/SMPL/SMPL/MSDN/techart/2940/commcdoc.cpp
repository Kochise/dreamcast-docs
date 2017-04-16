// commcdoc.cpp : implementation of the CCommchatDoc class
//

#include "stdafx.h"
//#include "protocol.h"

#include "commchat.h"



#include "comclass.h"


#include "commcdoc.h"
#include "commcvw.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CCommchatDoc

IMPLEMENT_DYNCREATE(CCommchatDoc, CDocument)

BEGIN_MESSAGE_MAP(CCommchatDoc, CDocument)
	//{{AFX_MSG_MAP(CCommchatDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommchatDoc construction/destruction

CCommchatDoc::CCommchatDoc()
{
	// TODO: add one-time construction code here
}

CCommchatDoc::~CCommchatDoc()
{
}

BOOL CCommchatDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCommchatDoc serialization

void CCommchatDoc::Serialize(CArchive& ar)
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
// CCommchatDoc diagnostics

#ifdef _DEBUG
void CCommchatDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCommchatDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCommchatDoc commands


BOOL CCommchatDoc::OnOpenDocument(const char* pszPathName)
{
SetTitle((CString)"Communication with: "+ (CString)pszPathName);
return TRUE;
}

BOOL CCommchatDoc::SetReaderCommunicationObject(CChatProtocol *cpArg,BOOL bServer)
{
m_bAreWeServer = bServer;
cpProtocol = cpArg;
m_ReaderView->StartRunning();
  return TRUE;
}



