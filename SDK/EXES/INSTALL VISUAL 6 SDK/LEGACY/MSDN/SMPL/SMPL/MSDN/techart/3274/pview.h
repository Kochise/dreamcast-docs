// pview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPView view

class CPView : public CFileView
{

private:
    long m_bRefreshing;
protected:
	CPView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL
void DispatchDoubleClick(int iVal);
//void RefreshProcessList();
int ExtractProcessId(char *cArg);

// Implementation
protected:
	virtual ~CPView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CPView)
	afx_msg void RefreshProcessList();
    afx_msg long AddEntry(UINT, LONG);
    afx_msg long ListFinished(UINT,LONG);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
