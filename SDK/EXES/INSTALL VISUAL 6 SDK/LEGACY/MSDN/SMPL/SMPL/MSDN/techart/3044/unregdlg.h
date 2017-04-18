// unregdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUnregisterDlg dialog

class CUnregisterDlg : public CDialog
{
// Construction
public:
	CUnregisterDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUnregisterDlg)
	enum { IDD = IDD_DLGUNREGISTER };
	CListBox	m_theListBox;
	//}}AFX_DATA

	CString m_strThePath ;
   	CFont m_font;
    int m_iFontHeight;
    int m_iFontWidth;
    //CTransBmp m_bmSmile;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnregisterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CPtrArray m_PtrArray ;
	BOOL GetControlNames() ;
	void CleanUp() ;
	BOOL WipeOut(HKEY hKey, LPCTSTR lpszSubKey)	;

	// Generated message map functions
	//{{AFX_MSG(CUnregisterDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg int OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	afx_msg void OnCleanup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
