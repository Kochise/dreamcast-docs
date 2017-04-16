// cstm2dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustom2Dlg dialog

#define MAXOPERATIONS 9

  typedef struct 
  { 
   int iId;
   char *Name;
   char *FullName;
   int iState;
  } DriverOperations;



class CCustom2Dlg : public CAppWizStepDlg
{

// Construction
public:
	CCustom2Dlg();
	virtual BOOL OnDismiss();
// Dialog Data
	//{{AFX_DATA(CCustom2Dlg)
	enum { IDD = IDD_CUSTOM2 };
	BOOL	m_bHasAsynch;
	int		m_iNumDevices;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCustom2Dlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
    BOOL AssignValues(BOOL);
};
