// subsplit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// csubsplit frame with splitter

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CCommView;

class csubsplit : public CSplitterWnd
{	
	DECLARE_DYNCREATE(csubsplit)
protected:
public:

// Operations
public:

// Implementation
public:
    csubsplit();			// protected constructor used by dynamic creation

    void OnTextTyped();

	virtual ~csubsplit();

	//{{AFX_MSG(csubsplit)
	afx_msg void OnDestroy();
	//}}AFX_MSG


	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
