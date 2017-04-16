// OCCSampDoc.cpp : implementation of the COCCSampDoc class
//

#include "stdafx.h"
#include "OCCSamp.h"

#include "OCCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COCCSampDoc

IMPLEMENT_DYNCREATE(COCCSampDoc, CDocument)

BEGIN_MESSAGE_MAP(COCCSampDoc, CDocument)
	//{{AFX_MSG_MAP(COCCSampDoc)
	ON_COMMAND(ID_INSERT_FILE, OnInsertFile)
	ON_COMMAND(ID_FILE_POST, OnPostFile)
	ON_COMMAND(ID_FILE_ADDROUTINGSLIP, OnFileAddroutingslip)
	ON_COMMAND(ID_FILE_ROUTE, OnFileRoute)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COCCSampDoc construction/destruction

COCCSampDoc::COCCSampDoc()
{
	m_rgstrFileList.SetSize(10,5);
	m_pJournalEntry = NULL;
	m_RouteSlip = NULL;
}

COCCSampDoc::~COCCSampDoc()
{
	if (m_pJournalEntry != NULL)
		m_pJournalEntry->Close(NULL, NULL, NULL, NULL);

	if (m_RouteSlip != NULL)
	{
		m_RouteSlip->Release();
		m_RouteSlip = NULL;
	}
}

BOOL COCCSampDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_rgstrFileList.RemoveAll(); // Clear out list

	if (vpOC != NULL)
	{
		IMsocOutlook *pOutlook = vpOC->PioutGetOutlook();

		if (pOutlook)
			m_pJournalEntry = pOutlook->PiojeCreateOutlookJournalEntry(NULL);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// COCCSampDoc serialization

void COCCSampDoc::Serialize(CArchive& ar)
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
// COCCSampDoc diagnostics

#ifdef _DEBUG
void COCCSampDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COCCSampDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COCCSampDoc commands

void COCCSampDoc::OnInsertFile() 
{
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST, 
		"All Files (*.*) | *.*", AfxGetMainWnd());

	if (dlgFile.DoModal() == IDOK)
	{
		m_rgstrFileList.Add(dlgFile.GetPathName());
		  
		SetModifiedFlag();

		UpdateAllViews(NULL);
	}

}

void COCCSampDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class

	if (m_pJournalEntry != NULL)
	{
		m_pJournalEntry->Close(NULL, NULL, NULL, NULL);
		m_pJournalEntry = NULL;
	}

	if (m_RouteSlip != NULL)
	{
		m_RouteSlip->Release();
		m_RouteSlip = NULL;
	}

	CDocument::OnCloseDocument();

}

BOOL COCCSampDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	DeleteContents();
	SetModifiedFlag();  // dirty during de-serialize

	CStdioFile stdioFile;
	if( !stdioFile.Open( lpszPathName, CFile::modeRead | CFile::shareDenyWrite) ) 
		return FALSE;	
	
	CString strInput;
	strInput.GetBuffer(1024);

	stdioFile.ReadString(strInput);  // Read header

	stdioFile.ReadString(strInput);  // get first file
	while(strInput != "")
	{
		strInput = (strInput.Mid(1)).SpanExcluding("\""); // remove quotes

		m_rgstrFileList.Add(strInput);

        stdioFile.ReadString(strInput);  // get next file
	};

    stdioFile.ReadString(strInput); // Blank line at end of file names

	stdioFile.Close();

	SetModifiedFlag(FALSE);     // start off with unmodified

	
	// TODO: Add your specialized creation code here
	m_pJournalEntry = NULL;

	if (vpOC != NULL)
	{
		IMsocOutlook *pOutlook = vpOC->PioutGetOutlook();

		if (pOutlook)
		{
			LPCWSTR pwzFileName = ConvertToUnicode(lpszPathName);

			m_pJournalEntry = pOutlook->PiojeCreateOutlookJournalEntry(pwzFileName);
		}
	}
	
	return TRUE;
}

BOOL COCCSampDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	LPCWSTR pwzPathName = ConvertToUnicode(lpszPathName);

	if (m_pJournalEntry != NULL)
		m_pJournalEntry->Save(pwzPathName);
	
	CStdioFile stdioFile;
	if( !stdioFile.Open( lpszPathName, CFile::modeCreate | CFile::modeWrite | CFile::typeText ) ) 
		return FALSE;
	
	// Strings are surrounded by quotes for VB compatibility

	stdioFile.WriteString("\"Office Compatible Sample Data\"\n");

	int i;
    for (i = 0; i < m_rgstrFileList.GetSize() ; i++)
	{
        stdioFile.WriteString("\"");
        stdioFile.WriteString(m_rgstrFileList[i]);
		stdioFile.WriteString("\"\n");
	}

    stdioFile.WriteString("\n"); // Blank line at end of file names

	// Save Routing Info here

    stdioFile.WriteString("\n"); // Blank line at end of Routing Info

	stdioFile.Close();

	SetModifiedFlag(FALSE);

	return TRUE;
}

void COCCSampDoc::OnPostFile() 
{

	CString strPathName = GetPathName();

	// make sure it has been saved and is unmodified
	if (IsModified() == TRUE || strPathName == "")
		return;


	if (vpOC != NULL)
	{
		if (vpOC->FCanPostDoc() != TRUE)
			return; // Can't post a document
	
		LPCWSTR pwzPathName = ConvertToUnicode(strPathName);

		vpOC->PostDoc(pwzPathName, L"Office Compatible Document", AfxGetMainWnd()->m_hWnd);
	}
}

void COCCSampDoc::OnFileAddroutingslip() 
{
	// make sure it has been saved and is unmodified
	if (IsModified() == TRUE)
		return;

	if (vpOC == NULL)
		return;

	if (m_RouteSlip == NULL)
	{
		m_RouteSlip = vpOC->PirsCreateRoutingSlip();

		if (m_RouteSlip == NULL)
			return;
	}

	m_RouteSlip->ShowEditDialog(AfxGetMainWnd()->m_hWnd);
}


void COCCSampDoc::OnFileRoute() 
{
	if (vpOC == NULL || m_RouteSlip == NULL)
		return;

	m_RouteSlip->PrepareToRoute();

	TCHAR szTempName[_MAX_PATH];
	TCHAR szPath[_MAX_PATH];

	// save to temporary path
	GetTempPath(_MAX_PATH, szPath);
	GetTempFileName(szPath, _T("afx"), 0, szTempName);

	// save it, but remember original modified flag
	BOOL bModified = IsModified();
	BOOL bResult = DoSave(szTempName, FALSE);
	SetModifiedFlag(bModified);
	if (!bResult)
		return;

	WCHAR wzTempName[MAX_PATH];
	_mbstowcsz(wzTempName, szTempName, _MAX_PATH);

	m_RouteSlip->Route(wzTempName);

	// remove temporary file
	CFile::Remove(szTempName);
}
