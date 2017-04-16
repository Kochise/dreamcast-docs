// PAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ParseApp.h"
#include "PAppDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "ofcdtd.h"
#include "ofcparse.h"
#include "ofcbuild.h"
#include "validlst.h"



/////////////////////////////////////////////////////////////////////////////
// CPAppDlg dialog

CPAppDlg::CPAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPAppDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPAppDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPAppDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPAppDlg, CDialog)
	//{{AFX_MSG_MAP(CPAppDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GETFILE, OnGetfile)
	ON_BN_CLICKED(IDC_REQUEST, OnRequest)
	ON_BN_CLICKED(IDC_RESPONSE, OnResponse)
	ON_BN_CLICKED(IDC_ACCTSTMT, OnAcctstmt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPAppDlg message handlers

BOOL CPAppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CheckDlgButton(IDC_REQUEST,TRUE);

	InitOFCParse();					// Init parse library
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPAppDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPAppDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// ---------------------------------------------------------------------------------
// Function: SelectFile
// 
// Purpose: Displays a standard Windows95 FileOpen Dialog. Only CPP and H files are 
//	available for selection
//
// Params: None
//
// Return: A CString containing the full path of the selected filename. A valid 
//  CString is always returned.  The caller should check for an empty filename 
//	using CString::IsEmpty(). 
//
// Change History: 1/21/96 Created - Derek Hazeur
//
// ---------------------------------------------------------------------------------
CString SelectFile() 
{
	// Initialize the Filter
	char szFilter[] = "OFC Files (*.ofc) | *.ofc\0";
	CString strFileName;

	// Empty the return string
	strFileName.Empty();

	// Initialize the Win95 File Dialog
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,szFilter,NULL);
	if (dlg.DoModal() == IDOK)
	{
		// Retrieve the selected filename from dialog
		strFileName = dlg.GetPathName();
	}

	// Return the FileName
	return strFileName;

} // end SelectFile 

void CPAppDlg::OnOK() 
{
	// NOTE: THIS FUNCTION LEAKS MEMORY ON ERRORS, BUT NO LEAKS SHOULD EXISTS
	// ON SUCCESSFUL COMPLETION. NO TIME TO FIX. 
	char *pchBuffer;
	unsigned long nNumberOfBytesWritten;
	unsigned long nNumberOfBytesRead;
	unsigned long nNumberOfBytesToRead;
	char *pvRequest  = NULL;
	char *pvRequest2  = NULL;
	int nOutputLength;

	OFSTRUCT  ReOpenBuff;
	BOOL bRC; 
	
	CString strStartFile;
	GetDlgItemText(IDC_FILENAME,strStartFile);

	strStartFile.TrimLeft();
	strStartFile.TrimRight();
	if (strStartFile.GetLength() == 0)
	{
		AfxMessageBox("No File Selected",MB_ICONSTOP|MB_OK,0);
		return;
	}
	
	char pchFileName[256];
	strcpy(pchFileName,strStartFile);

	strStartFile.MakeUpper();

	CString strValidExt("OFC");
	CString strOutFile = strStartFile.Left(strStartFile.GetLength() - 4);
	CString strFile1 = strOutFile + ".out1.ofc";
	CString strFile2 = strOutFile + ".out2.ofc";
	
	if (strStartFile.Right(3) != strValidExt)
	{
		AfxMessageBox("File Must Have .OFC Extension",MB_ICONSTOP|MB_OK,0);
		return;
	}

	HFILE hFile = OpenFile(strStartFile,&ReOpenBuff,OF_READ);
	if (hFile == HFILE_ERROR)
	{
		AfxMessageBox("Unable to open Input File",MB_ICONSTOP|MB_OK,0);
		return;
	}

	// Get file size
	DWORD  FileSizeHigh;
	nNumberOfBytesToRead = GetFileSize((HANDLE) hFile,&FileSizeHigh);

	// Allocate buffer
	pchBuffer = (char *) malloc(nNumberOfBytesToRead * sizeof(char));

	bRC = ReadFile((HANDLE) hFile,pchBuffer,nNumberOfBytesToRead,&nNumberOfBytesRead,0);
	if (bRC == FALSE)
	{
		AfxMessageBox("Unable to Read Input File",MB_ICONSTOP|MB_OK,0);
		return;
	}

	// Close the output file
	_lclose(hFile);

	// Parse the request
	POFCDOC pofcdocPtr = NULL; 
	int nRC; 
	if (IsDlgButtonChecked(IDC_REQUEST))
		nRC = RcParseOFCRequest(pchBuffer,nNumberOfBytesRead,&pofcdocPtr);
	else if (IsDlgButtonChecked(IDC_RESPONSE))
		nRC = RcParseOFCResponse(pchBuffer,nNumberOfBytesRead,&pofcdocPtr);
	else 
		nRC = RcParseOFCStatement(pchBuffer,nNumberOfBytesRead,&pofcdocPtr);

	if (nRC != ALL_OK)
	{
		switch (nRC)
		{
		case OFC_ERROR:
			AfxMessageBox("Parse Failed - OFC_ERROR",MB_ICONSTOP|MB_OK,0);
			goto _END;
			break;
		case NO_MEMORY:
			AfxMessageBox("Parse Failed - NO_MEMORY",MB_ICONSTOP|MB_OK,0);
			goto _END;
			break;
		case INVALID_CALL:
			AfxMessageBox("Parse Failed - INVALID_CALL - Contact Derek Hazeur",MB_ICONSTOP|MB_OK,0);
			goto _END;
			break;
		default:
			AfxMessageBox("Parse Failed - Unknown Error - Contact Derek Hazeur",MB_ICONSTOP|MB_OK,0);
			goto _END;
			break;
		}
	}

	int cbOFCList; 
	nRC = RcValidateOFCList(pofcdocPtr,&cbOFCList);
	if (nRC != ALL_OK)
	{
		AfxMessageBox("Created List Is Invalid -  - Contact Derek Hazeur",MB_ICONSTOP|MB_OK,0);
		goto _END;
	}


	// Build a New File
	if (IsDlgButtonChecked(IDC_REQUEST))
		nRC = RcCreateOFCRequest(pofcdocPtr,(void **) &pvRequest,&nOutputLength);
	else if (IsDlgButtonChecked(IDC_RESPONSE))
		nRC = RcCreateOFCResponse(pofcdocPtr,(void **) &pvRequest,&nOutputLength);
	else 
		nRC = RcCreateOFCStatement(pofcdocPtr,(void **) &pvRequest,&nOutputLength);
	if (nRC != ALL_OK)
	{
		AfxMessageBox("Unable to Build OFC File From List - Contact Derek Hazeur",MB_ICONSTOP|MB_OK,0);
		goto _END;
	}
	
	TRACE("DEBUG: Max Length = %d, OutputLength = %d\n",cbOFCList,nOutputLength);

	// Make sure we did not build something to big. May GPF before here.
	if (nOutputLength > cbOFCList)
	{
		AfxMessageBox("Potential GPF - Buffer Overflow - Contact Derek Hazeur",MB_ICONSTOP|MB_OK,0);
		goto _END;
	}

	// Write output file
	hFile = OpenFile(strFile1,&ReOpenBuff,OF_CREATE);
	bRC = WriteFile((HANDLE) hFile,pvRequest,nOutputLength,&nNumberOfBytesWritten,0);
	_lclose(hFile);

	// Cleanup Parsing
	CleanupOFCDOCParse(&pofcdocPtr);
	pofcdocPtr = NULL; 

	// Free buffer
	if (pchBuffer)
	{
		free(pchBuffer);
		pchBuffer = NULL;
	}

	// Parse the New File (Double Check)
	if (IsDlgButtonChecked(IDC_REQUEST))
		nRC = RcParseOFCRequest(pvRequest,nOutputLength,&pofcdocPtr);
	else if (IsDlgButtonChecked(IDC_RESPONSE))
		nRC = RcParseOFCResponse(pvRequest,nOutputLength,&pofcdocPtr);
	else 
		nRC = RcParseOFCStatement(pvRequest,nOutputLength,&pofcdocPtr);

	if (nRC != ALL_OK)
	{
		switch (nRC)
		{
		case OFC_ERROR:
			AfxMessageBox("Pass #2: Parse of Failed - OFC_ERROR - Contact Derek Hazeur",MB_ICONSTOP|MB_OK,0);
			goto _END;
			break;
		case NO_MEMORY:
			AfxMessageBox("Pass #2: Parse Failed - NO_MEMORY  - Contact Derek Hazeur",MB_ICONSTOP|MB_OK,0);
			goto _END;
			break;
		case INVALID_CALL:
			AfxMessageBox("Pass #2: Parse Failed - INVALID_CALL - Contact Derek Hazeur",MB_ICONSTOP|MB_OK,0);
			goto _END;
			break;
		default:
			AfxMessageBox("Pass #2: Parse Failed - Unknown Error - Contact Derek Hazeur",MB_ICONSTOP|MB_OK,0);
			goto _END;
			break;
		}
	}

	// Build a Second File
	if (IsDlgButtonChecked(IDC_REQUEST))
		nRC = RcCreateOFCRequest(pofcdocPtr,(void **) &pvRequest2,&nOutputLength);
	else if (IsDlgButtonChecked(IDC_RESPONSE))
		nRC = RcCreateOFCResponse(pofcdocPtr,(void **) &pvRequest2,&nOutputLength);
	else 
		nRC = RcCreateOFCStatement(pofcdocPtr,(void **) &pvRequest2,&nOutputLength);
	if (nRC != ALL_OK)
	{
		AfxMessageBox("Unable to Build OFC File From List - Contact Derek Hazeur",MB_ICONSTOP|MB_OK,0);
		goto _END;
	}

	// Write a 2nd File
	hFile = OpenFile(strFile2,&ReOpenBuff,OF_CREATE);
	bRC = WriteFile((HANDLE) hFile,pvRequest2,nOutputLength,&nNumberOfBytesWritten,0);
	_lclose(hFile);

	AfxMessageBox("Parse and Build Successful",MB_OK,0);

_END:
	// Cleanup Parsing
	if (pofcdocPtr)
	{
		CleanupOFCDOCParse(&pofcdocPtr);
		pofcdocPtr = NULL; 
	}

	// Free buffer
	if (pvRequest)
	{
		free(pvRequest);
		pvRequest = NULL;
	}

	// Free buffer
	if (pvRequest2)
	{
		free(pvRequest2);
		pvRequest2 = NULL;
	}

	// Free buffer
	if (pchBuffer)
	{
		free(pchBuffer);
		pchBuffer = NULL;
	}

}

void CPAppDlg::OnGetfile() 
{
	CString strStartFile = SelectFile();
	
	char pchFileName[256];
	strcpy(pchFileName,strStartFile);

	strStartFile.MakeUpper();

	SetDlgItemText(IDC_FILENAME,strStartFile);
}

void CPAppDlg::OnRequest() 
{
	CheckDlgButton(IDC_REQUEST,TRUE);
	CheckDlgButton(IDC_RESPONSE,FALSE);
	CheckDlgButton(IDC_ACCTSTMT,FALSE);
}

void CPAppDlg::OnResponse() 
{
	CheckDlgButton(IDC_REQUEST,FALSE);
	CheckDlgButton(IDC_RESPONSE,TRUE);
	CheckDlgButton(IDC_ACCTSTMT,FALSE);
}

void CPAppDlg::OnAcctstmt() 
{
	CheckDlgButton(IDC_REQUEST,FALSE);
	CheckDlgButton(IDC_RESPONSE,FALSE);
	CheckDlgButton(IDC_ACCTSTMT,TRUE);
}
