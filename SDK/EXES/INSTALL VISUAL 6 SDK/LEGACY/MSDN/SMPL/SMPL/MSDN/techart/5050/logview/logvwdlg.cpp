// LogVwDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LogView.h"
#include "LogVwDlg.h"
#include "EntryDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogViewDlg dialog

CLogViewDlg::CLogViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogViewDlg::IDD, pParent), m_rsLogs(&m_db) // *** Important
{
	//{{AFX_DATA_INIT(CLogViewDlg)
	m_dFreq = 0.0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLogViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogViewDlg)
	DDX_Control(pDX, IDC_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_BAND, m_lbBand);
	DDX_Control(pDX, IDC_LOGS, m_lbLogs);
	DDX_Text(pDX, IDC_FREQ, m_dFreq);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLogViewDlg, CDialog)
	//{{AFX_MSG_MAP(CLogViewDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnLookup)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_LBN_SELCHANGE(IDC_LOGS, OnSelchangeLogs)
	ON_BN_CLICKED(IDC_NEW, OnNewEntry)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogViewDlg message handlers

BOOL CLogViewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Open the database
	try {
		m_db.Open("\\\\kirk\\nigelt\\database\\rxlog.mdb", FALSE, FALSE);
	} catch (CDaoException* e) {
         AfxMessageBox(e->m_pErrorInfo->m_strDescription, MB_ICONEXCLAMATION);
	}
	
	// Set the initial frequency
	m_dFreq = 14.0;
	UpdateData(FALSE);
	OnLookup();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLogViewDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLogViewDlg::OnPaint() 
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
HCURSOR CLogViewDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// These two functions prevent the ESC key from ending the dialog
// but still allow it to be closed from the system menu
void CLogViewDlg::OnCancel() 
{
	// Just ignore this
}

void CLogViewDlg::OnClose() 
{
	// End the dialog
	CDialog::EndDialog(0);
}

// Lookup the current frequency in the database
void CLogViewDlg::OnLookup() 
{
	// Ensure the database is open
	if (!m_db.IsOpen()) {
		return;
	}

	// Get the frequency (m_dFreq)
	UpdateData(TRUE);

	// reset the list boxes
	m_lbLogs.ResetContent();
	m_lbBand.ResetContent();

	// construct a query to find records in the database 
	// near to the frequency of interest
	if ((m_dFreq < 0.5) || (m_dFreq > 1000.0)) {
		return;
	}
	double dMin = m_dFreq * 0.9;
	double dMax = m_dFreq * 1.1;

	char szQuery[256];
	sprintf(szQuery,
			"SELECT * FROM Frequencies WHERE Frequency BETWEEN %f AND %f",
			dMin, dMax);

	double dCloseDiff = 999999;
	int iClosest = 0;
	try {
		if (m_rsLogs.IsOpen()) m_rsLogs.Close();
		m_rsLogs.Open(dbOpenDynaset, szQuery);
		int iRecords = m_rsLogs.GetRecordCount();
		if (!m_rsLogs.IsEOF()) m_rsLogs.MoveFirst();
		while (!m_rsLogs.IsEOF()) {
			COleVariant vFreq = m_rsLogs.GetFieldValue("Frequency");
			COleVariant vMode = m_rsLogs.GetFieldValue("Mode");
			COleVariant vStation = m_rsLogs.GetFieldValue("Station");
			COleVariant vDesc = m_rsLogs.GetFieldValue("Description");
			COleVariant vDate = m_rsLogs.GetFieldValue("Date");
			COleVariant vTimes = m_rsLogs.GetFieldValue("Times");

			char buf[256];
			sprintf(buf, "%9.4f %-3s %s, %s",
					vFreq.dblVal,
					vMode.bstrVal,
					vStation.bstrVal,
					vDesc.bstrVal);
			if (vTimes.vt != VT_NULL) {
				strcat(buf, " (");
				strcat(buf, (const char*) vTimes.bstrVal);
				strcat(buf, ")");
			}

			int iSel = m_lbLogs.AddString(buf);

			// See if this is the closest
			double dDiff = fabs(vFreq.dblVal - m_dFreq);
			if (dDiff < dCloseDiff) {
				dCloseDiff = dDiff;
				iClosest = iSel;
			}

			m_rsLogs.MoveNext();
		}

	} catch (CDaoException* e) {
		// barf
         AfxMessageBox(e->m_pErrorInfo->m_strDescription, MB_ICONEXCLAMATION);
	}


	// select the closest item
	m_lbLogs.SetCurSel(iClosest);

	UpdateBandInfo();
}

void CLogViewDlg::UpdateBandInfo()
{
	// erase the current data
	m_lbBand.ResetContent();

	// Get the selected frequency
	double dFreq = 0;
	int iFSel = m_lbLogs.GetCurSel();
	if (iFSel == LB_ERR) {
		dFreq = m_dFreq;
	} else {
		// extract the frequency
		char buf[256];
		m_lbLogs.GetText(iFSel, buf);
		int i = sscanf(buf, "%lf", &dFreq);
		if (i != 1) dFreq = m_dFreq;
	}

	// now do the band info
	CDaoRecordset rs(&m_db);
	char szQuery[256];
	sprintf(szQuery,
			"SELECT * FROM Bands WHERE (%f >= Lower AND %f <= Upper)"
			"OR (%f >= Lower AND %f <= Upper)",
			dFreq, dFreq,
			m_dFreq, m_dFreq);

	try {
		rs.Open(dbOpenDynaset, szQuery, dbReadOnly);
		int iRecords = rs.GetRecordCount();
		if (iRecords == 0) return;
		rs.MoveFirst();
		while (!rs.IsEOF()) {
			COleVariant vLower = rs.GetFieldValue("Lower");
			COleVariant vUpper = rs.GetFieldValue("Upper");
			COleVariant vName = rs.GetFieldValue("Name");
			COleVariant vDesc = rs.GetFieldValue("Description");

			char buf[256];
			sprintf(buf, "%6.4f - %6.4f %s, %s",
					vLower.dblVal,
					vUpper.dblVal,
					vName.bstrVal,
					vDesc.bstrVal);
			m_lbBand.AddString(buf);

			rs.MoveNext();
		}
		rs.Close();

	} catch (CDaoException* e) {
         AfxMessageBox(e->m_pErrorInfo->m_strDescription, MB_ICONEXCLAMATION);
	}

	
}

void CLogViewDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	// Close the logs record set
	if (m_rsLogs.IsOpen()) {
		m_rsLogs.Close();
	}

	// Close the database
	if (m_db.IsOpen()) {
		m_db.Close();
	}
	
}

void CLogViewDlg::OnSelchangeLogs() 
{
	UpdateBandInfo();
	int iSel = m_lbLogs.GetCurSel();
	if (iSel != LB_ERR) {
		m_btnDelete.EnableWindow(TRUE);

		// Move to this record
		m_rsLogs.MoveFirst();
		int i = iSel;
		while (i--) {
			m_rsLogs.MoveNext();
		}

		// Get the frequency
		COleVariant vFreq = m_rsLogs.GetFieldValue("Frequency");

		// Update the frequency entry box
		m_dFreq = vFreq.dblVal;
		UpdateData(FALSE);

	} else {
		m_btnDelete.EnableWindow(FALSE);
	}
}

void CLogViewDlg::OnNewEntry() 
{
	// Get the frequency (m_dFreq)
	UpdateData(TRUE);
	
	// Show the dialog to get the new info
	CNewEntryDlg dlg;
	dlg.m_dFreq = m_dFreq;
	if (dlg.DoModal() != IDOK) return;

	// Write a new entry to the database
	try {

		// Add a new entry to the record set
		m_rsLogs.AddNew();

		// position the recordset at the new entry
		m_rsLogs.SetBookmark(m_rsLogs.GetLastModifiedBookmark());

		// Set the new field values
		char buf[64];
		COleVariant v;
		sprintf(buf, "%f", dlg.m_dFreq);
		v.SetString(buf, VT_BSTRT);
		m_rsLogs.SetFieldValue("Frequency", v);

		v.SetString(dlg.m_strMode, VT_BSTRT);
		m_rsLogs.SetFieldValue("Mode", v);
		
		v.SetString(dlg.m_strStation, VT_BSTRT);
		m_rsLogs.SetFieldValue("Station", v);

		v.SetString(dlg.m_strDesc, VT_BSTRT);
		m_rsLogs.SetFieldValue("Description", v);

		m_rsLogs.SetFieldValue("Date", dlg.m_Date); // m_Date in a COleDateTime object

		v.SetString(dlg.m_strTime, VT_BSTRT);
		m_rsLogs.SetFieldValue("Times", v);

		// Update the database
		m_rsLogs.Update();

		// Rebuild the view
		OnLookup();

	} catch (CDaoException* e) {
         AfxMessageBox(e->m_pErrorInfo->m_strDescription, MB_ICONEXCLAMATION);
	}
}

void CLogViewDlg::OnDelete() 
{
	ASSERT(m_rsLogs.GetRecordCount() > 0);

	// Get the current selection
	int iSel = m_lbLogs.GetCurSel();
	if (iSel == LB_ERR) return; // no selection

	// make this the current record in the record set
	// Note: for this to work it's important that the list box and 
	// record set are in sync since we rely on the relative position in
	// the list box to give us the relative position in the record set.
	m_rsLogs.MoveFirst();
	while (iSel--) {
		m_rsLogs.MoveNext();
	}

	// Verify with the user that this is the record to delete
	COleVariant vFreq = m_rsLogs.GetFieldValue("Frequency");
	COleVariant vMode = m_rsLogs.GetFieldValue("Mode");
	COleVariant vStation = m_rsLogs.GetFieldValue("Station");
	COleVariant vDesc = m_rsLogs.GetFieldValue("Description");

	char buf[256];
	sprintf(buf,
			"Delete: %9.4f %-3s %s, %s ?",
			vFreq.dblVal,
			vMode.bstrVal,
			vStation.bstrVal,
			vDesc.bstrVal);
	if (AfxMessageBox(buf, MB_YESNO) != IDYES) return;

	// delete the record from the record set
	m_rsLogs.Delete();

	// regenerate the list box view of the data
	OnLookup();
}
