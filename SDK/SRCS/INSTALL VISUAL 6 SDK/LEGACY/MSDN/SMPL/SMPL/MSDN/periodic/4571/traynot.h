/////////////////////////////////////////////////////////////////////////////
// TrayNot.h : header file
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//

/////////////////////////////////////////////////////////////////////////////
// CTrayNot window

class CTrayNot : public CObject
{
// Construction
public:
	CTrayNot ( CWnd* pWnd, UINT uCallbackMessage,
				  LPCTSTR szTip, HICON* pList ) ;

// Attributes
public:
	BOOL				m_bEnabled ;	// does O/S support tray icon?
	NOTIFYICONDATA	m_tnd ;
	HICON*			m_pIconList ;	// caller's list of status icons

// Operations
public:
	void SetState ( int id = 0 ) ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrayNot)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTrayNot();

};

/////////////////////////////////////////////////////////////////////////////
