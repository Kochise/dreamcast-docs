// gridsize.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// gridsize dialog

class gridsize : public CDialog
{
// Construction
public:
	gridsize(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(gridsize)
	enum { IDD = IDD_DIALOG2 };
	int		m_GridSize;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(gridsize)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
