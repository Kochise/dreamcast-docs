// morepfd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMorePFD dialog

class CMorePFD : public CDialog
{
// Construction
public:
	CMorePFD(CWnd* pParent = NULL);	// standard constructor

	LPPIXELFORMATDESCRIPTOR m_ppfd;

// Dialog Data
	//{{AFX_DATA(CMorePFD)
	enum { IDD = IDD_MOREPFD };
	int		m_accumalphabits;
	int		m_accumbluebits;
	int		m_accumgreenbits;
	int		m_accumredbits;
	int		m_alphabits;
	int		m_alphashift;
	int		m_bluebits;
	int		m_blueshift;
	DWORD	m_damagemask;
	int		m_greenbits;
	int		m_greenshift;
	DWORD	m_layermask;
	int		m_redbits;
	int		m_redshift;
	DWORD	m_visiblemask;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CMorePFD)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
