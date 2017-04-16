// fileview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEasyOutputView view


#define MAXSTRING 200


class CEasyOutputView : public CView
{
private:
 CListBox m_LB;
 int m_iLongestStringSizeInPixels;
 int m_iFontWidth;
 CFont *m_cfFixedFont;
 CRITICAL_SECTION m_csAddString;

protected:
 char m_szBuf[MAXSTRING];
 char m_Selection[MAXSTRING];

protected:
 CEasyOutputView();           // protected constructor used by dynamic creation
 DECLARE_DYNCREATE(CEasyOutputView)

// Attributes
public:

// Operations
public:


// helper functions
 void AddStringandAdjust(char *cString);
 void ClearWindow();

void inline ComputeNewHorizontalExtent(int i)
{ 
 EnterCriticalSection(&m_csAddString);
 m_iLongestStringSizeInPixels = max(i, m_iLongestStringSizeInPixels);
 LeaveCriticalSection(&m_csAddString);
}

   afx_msg void OnLBDoubleClicked();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEasyOutputView)
	protected:
    virtual void DispatchDoubleClick(int iVal);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CEasyOutputView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CEasyOutputView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
