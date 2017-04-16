// commcvw.h : interface of the CReaderView class
//
/////////////////////////////////////////////////////////////////////////////

#define ID_NUKEDOC WM_USER+0x7001

#define ID_STARTCHATCOMM         32769
#define ID_STARTTRANSFERCOMM     32770


class CReaderView : public CEditView
{
protected: // create from serialization only
	CReaderView();
	DECLARE_DYNCREATE(CReaderView)

// Attributes
public:
	CCommchatDoc* GetDocument();

// Operations
public:

// Implementation
public:
    void StartRunning();
	virtual ~CReaderView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

HANDLE m_hReceiveEditMemory;
HANDLE m_hReceiveThread;
char *m_lpReceiveBuffer;
int	m_iMemPointer;

// Generated message map functions
protected:
	//{{AFX_MSG(CReaderView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
    afx_msg long OnNukeDoc(UINT wParam, LONG lParam);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in commcvw.cpp
inline CCommchatDoc* CReaderView::GetDocument()
   { return (CCommchatDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

class CWriterView : public CEditView
{

private:

HANDLE m_hReceiveThread;


protected: // create from serialization only
	CWriterView();
	DECLARE_DYNCREATE(CWriterView)

// Attributes
public:
	CCommchatDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~CWriterView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

    void ReactToChanges();
// Generated message map functions
protected:
	//{{AFX_MSG(CWriterView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG	// debug version in commcvw.cpp
inline CCommchatDoc* CWriterView::GetDocument()
   { return (CCommchatDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
