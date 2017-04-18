// fileview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileView view

#include "headstr.h"  // for the TAGGEDLISTSTRUCT structure

#define MAXSTRING 200


class CFileView : public CView
{
private:
    CListBox m_LB;
	int m_iLongestStringSizeInPixels;
	int m_iFontWidth;
	CFont *m_cfFixedFont;

protected:
	char m_szBuf[MAXSTRING];
	char m_Selection[MAXSTRING];

protected:
	CFileView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFileView)

// Attributes
public:

// Operations
public:


// helper functions
void AddStringandAdjust(char *cString);
void ClearWindow();


int FillInSizedString(BYTE *lpTarget,BYTE *lpSource);
void FillInTaggedData(BYTE *lpMem, TAGGEDLISTSTRUCT *lpTemplate);
void FillInChainedStructures(int iEntries, PHEADERTEMPLATE pTemplate,WORD *pPointers, unsigned char *pBase);
void FillInFlatStructures(PHEADERTEMPLATE pTemplate, unsigned char* pPointers);

void inline ComputeNewHorizontalExtent(int i)
{ m_iLongestStringSizeInPixels = max(i, m_iLongestStringSizeInPixels);
}
    afx_msg void OnLBDoubleClicked();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileView)
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
    virtual void DispatchDoubleClick(int iVal);
	virtual void OnDraw(CDC* pDC);
	virtual BOOL IsMyKindOfFile(BYTE *lpImage);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFileView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CFileView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
