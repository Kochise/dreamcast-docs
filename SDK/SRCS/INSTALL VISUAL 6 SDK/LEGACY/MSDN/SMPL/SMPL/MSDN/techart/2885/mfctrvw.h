// mfctrvw.h : interface of the CMfctrackView class
//
/////////////////////////////////////////////////////////////////////////////

class CMfctrackView : public CView
{
protected: // create from serialization only
	CMfctrackView();
	DECLARE_DYNCREATE(CMfctrackView);
	CSliderCtrl m_Slider;
	int m_Min;
	int m_Max;
	int m_PageSize;
	int m_LineSize;

// Attributes
public:
	CMfctrackDoc* GetDocument();

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfctrackView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMfctrackView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMfctrackView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnProperties();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mfctrvw.cpp
inline CMfctrackDoc* CMfctrackView::GetDocument()
   { return (CMfctrackDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
// constants
#define ID_SLIDER	1

/////////////////////////////////////////////////////////////////////////////
// propsheet

class propsheet : public CPropertySheet
{
	DECLARE_DYNAMIC(propsheet)

// Construction
public:
	propsheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	propsheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(propsheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~propsheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(propsheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CPage dialog

class CPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPage)

// Construction
public:
	CPage();
	~CPage();

// Dialog Data
	//{{AFX_DATA(CPage)
	enum { IDD = IDD_PAGEANDLINE };
	int		m_LineSize;
	int		m_PageSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CRange dialog

class CRange : public CPropertyPage
{
	DECLARE_DYNCREATE(CRange)

// Construction
public:
	CRange();
	~CRange();

// Dialog Data
	//{{AFX_DATA(CRange)
	enum { IDD = IDD_Range };
	int		m_Max;
	int		m_Min;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CRange)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CRange)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
