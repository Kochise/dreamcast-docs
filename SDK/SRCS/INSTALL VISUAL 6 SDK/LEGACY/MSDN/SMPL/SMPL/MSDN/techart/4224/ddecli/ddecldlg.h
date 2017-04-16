// DDECldlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDDECliDlg dialog

class CDDECliDlg : public CDialog
{
// Construction
public:
	CDDECliDlg(CWnd* pParent = NULL);	// standard constructor
    void Status(const char* pszFormat, ...);
    void NewData(const char* pszItem, const char* pData);

// Dialog Data
	//{{AFX_DATA(CDDECliDlg)
	enum { IDD = IDD_DDECLI_DIALOG };
	CListBox	m_wndStatus;
	CButton	m_wndPoke;
	CButton	m_wndExec;
	CButton	m_wndDisconnect;
	CButton	m_wndConnect;
	CString	m_strExecCmd;
	CString	m_strItem;
	CString	m_strItemData;
	CString	m_strService;
	CString	m_strTopic;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDDECliDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
    CMyClient m_DDEClient;
    CMyConv* m_pConversation;

    void UpdateUI();

	// Generated message map functions
	//{{AFX_MSG(CDDECliDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnectBtn();
	afx_msg void OnDisconnectBtn();
	afx_msg void OnChangeService();
	afx_msg void OnChangeTopic();
	afx_msg void OnChangeItem();
	afx_msg void OnDestroy();
	afx_msg void OnExecBtn();
	afx_msg void OnPokeBtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
