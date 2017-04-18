// dsurfobj.h : header file
//

#include "colorpal.h"
#include "image.h"

/////////////////////////////////////////////////////////////////////////////
// CDrawSurfObj command target

class CDrawSurfObj : public CCmdTarget
{
	DECLARE_DYNCREATE(CDrawSurfObj)
protected:
	CDrawSurfObj();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawSurfObj)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDrawSurfObj();

	// Generated message map functions
	//{{AFX_MSG(CDrawSurfObj)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CDrawSurfObj)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDrawSurfObj)
	afx_msg long GetWidth();
	afx_msg long GetHeight();
	afx_msg long GetHDC();
	afx_msg BOOL LoadFile(LPCTSTR pszFile);
	afx_msg void Draw(long hDC, long x, long y);
	afx_msg BOOL MapToPalette(long hPal);
	afx_msg long GetBitmapInfo();
	afx_msg BOOL CreateNew(long width, long height, long hPal);
	afx_msg void CopyWithTransparency(LPDISPATCH ds, long x, long y);
	afx_msg long GetDIBSurface();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

    CImage m_ds;
};

/////////////////////////////////////////////////////////////////////////////
