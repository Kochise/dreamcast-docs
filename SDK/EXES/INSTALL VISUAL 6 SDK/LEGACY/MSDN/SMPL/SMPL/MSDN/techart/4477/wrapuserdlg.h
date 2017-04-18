// WrapUserDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWrapUserDlg dialog
#include "CSimpleWrap.h"

class CWrapUserDlg : public CDialog
{
// Construction
public:
	CWrapUserDlg(CWnd* pParent = NULL);	// standard constructor

   virtual void OnCancel( )
      { cleanUp() ; CDialog::OnCancel() ;}
   virtual void OnOK( )
      { cleanUp() ; CDialog::OnOK() ;}

// Dialog Data
	//{{AFX_DATA(CWrapUserDlg)
	enum { IDD = IDD_WRAPUSER_DIALOG };
	CButton	m_btnInc;
	CButton	m_btnRelease;
	CListBox	m_ListBox;
	CEdit	m_EditCtl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWrapUserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

   int m_ObjectNum ;
   CMap< int, int, CSimpleWrap*, CSimpleWrap* >  m_SimpleMap ;
   void DrawHelper(CSimpleWrap* pWISimple) ;
   void cleanUp() ;
   void EnableBtns(BOOL bEnable) ;

	// Generated message map functions
	//{{AFX_MSG(CWrapUserDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCreateBtn();
	afx_msg void OnReleaseBtn();
	afx_msg void OnIncBtn();
	afx_msg void OnSelchangeListBox();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
