#if !defined(AFX_HOTTUBLEVELGETTER_H__34CA0A53_F81C_11D0_8FE8_00409500EFA8__INCLUDED_)
#define AFX_HOTTUBLEVELGETTER_H__34CA0A53_F81C_11D0_8FE8_00409500EFA8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// HotTubLevelGetter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// HotTubLevelGetter command target

#include <BaseLevelGetter.h>

class HotTubLevelGetter : public BaseLevelGetter
{
	DECLARE_DYNCREATE(HotTubLevelGetter)

	HotTubLevelGetter();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HotTubLevelGetter)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~HotTubLevelGetter();

	virtual CString GetMessage(){return "HotTubLevelGetter";}
	virtual long GetCurrentLevel(){return -2;}

	// Generated message map functions
	//{{AFX_MSG(HotTubLevelGetter)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(HotTubLevelGetter)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(HotTubLevelGetter)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOTTUBLEVELGETTER_H__34CA0A53_F81C_11D0_8FE8_00409500EFA8__INCLUDED_)
