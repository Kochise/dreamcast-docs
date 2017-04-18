// splitfrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// csplitframe frame with splitter

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif


class csplitframe : public CMDIChildWnd
{
	DECLARE_DYNCREATE(csplitframe)
protected:
	csplitframe();			// protected constructor used by dynamic creation

// Attributes
protected:
public:

	csubsplit *m_wndSplitter;


// Operations
public:

// Implementation
public:
	virtual ~csplitframe();
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	// Generated message map functions
	//{{AFX_MSG(csplitframe)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


};

/////////////////////////////////////////////////////////////////////////////
