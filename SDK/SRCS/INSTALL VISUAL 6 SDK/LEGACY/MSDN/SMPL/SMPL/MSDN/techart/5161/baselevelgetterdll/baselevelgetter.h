#if !defined(AFX_BASELEVELGETTER_H__C20EA056_F61C_11D0_A25F_000000000000__INCLUDED_)
#define AFX_BASELEVELGETTER_H__C20EA056_F61C_11D0_A25F_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BaseLevelGetter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BaseLevelGetter command target


#include "ILevelGetter.h"
#include "BaseLevelGetterExport.h"

class BASE_LEVEL_GETTER_EXPORT BaseLevelGetter : public CCmdTarget
{	
	DECLARE_DYNCREATE(BaseLevelGetter)
	BaseLevelGetter();           // protected constructor used by dynamic creation

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BaseLevelGetter)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~BaseLevelGetter();

	// Generated message map functions
	//{{AFX_MSG(BaseLevelGetter)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(BaseLevelGetter)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(BaseLevelGetter)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(LevelGetter, ILevelGetter)		  
		STDMETHOD(GetCurrentLevel)				(long* plCurrentLevel);
		STDMETHOD(GetHighestPossibleSafeLevel)	(long* plHighestSafeLevel);
		STDMETHOD(GetLowestPossibleSafeLevel)	(long* plLowestSafeLevel);
		STDMETHOD(GetTextMessage)				(BSTR* ppbstrMessage);

		//added for sample
		XLevelGetter(){m_pOwner = NULL;}  //constructor sets member to NULL
		void SetOwner(BaseLevelGetter* pOwner){m_pOwner = pOwner;}
		BaseLevelGetter* m_pOwner;

	END_INTERFACE_PART(LevelGetter)

protected:

	//since the class can be dynamically created
	//these virtual functions cannot be pure
	virtual long GetCurrentLevel();
	virtual long GetHighestSafeLevel();
	virtual long GetLowestSafeLevel();
	virtual CString GetMessage();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASELEVELGETTER_H__C20EA056_F61C_11D0_A25F_000000000000__INCLUDED_)
