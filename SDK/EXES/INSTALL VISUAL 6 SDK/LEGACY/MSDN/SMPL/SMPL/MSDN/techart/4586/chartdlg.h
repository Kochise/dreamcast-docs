// chartdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChartDlg dialog

class CChartDlg : public CDialog
{
// Construction
public:
	CChartDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChartDlg)
	enum { IDD = IDD_CHARTDLG };
	CComboBox	m_cbChart;
	//}}AFX_DATA
	int m_cbIndex;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChartDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
