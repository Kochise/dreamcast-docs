// leview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLEView view

class CLEView : public CFileView
{
public:
	CLEView();           // protected constructor used by dynamic creation
	virtual ~CLEView();

	DECLARE_DYNCREATE(CLEView)

// Attributes
public:

// Operations
public:

static BOOL IsMyKindOfFile(BYTE *lpImage);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLEView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL
    void DispatchDoubleClick(int iVal);


// Implementation
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CLEView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
