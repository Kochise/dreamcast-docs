// neview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNEView view

class CNEView : public CFileView
{
public:
	CNEView();           // protected constructor used by dynamic creation
	virtual ~CNEView();

	DECLARE_DYNCREATE(CNEView)

// Attributes
public:

// helper functions

void FillInEntryTable(unsigned char *lpEntryTable);
void FillInSegmentTable(PSEGENTRY lpSegmentTable,int iEntries, WORD wAlign);
void FillInResourceTable(BYTE *lpResourceTable);


// Operations
public:

static BOOL IsMyKindOfFile(BYTE *lpImage);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNEView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL
void DispatchDoubleClick(int iVal);

CNEView *GetDLLPane();


// Implementation
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CNEView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
    afx_msg long OnLoadDLL(WPARAM wParam, LPARAM lParam);
	afx_msg long OnRefresh(WPARAM wParam, LPARAM lParam);
	afx_msg void OnFileExecute();

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
