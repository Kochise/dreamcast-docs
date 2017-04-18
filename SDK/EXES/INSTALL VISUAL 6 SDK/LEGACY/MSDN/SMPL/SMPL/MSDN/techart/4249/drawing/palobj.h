// palobj.h : header file
//

#include "colorpal.h"
#include "image.h"


/////////////////////////////////////////////////////////////////////////////
// CColorPalObj command target

class CColorPalObj : public CCmdTarget
{
	DECLARE_DYNCREATE(CColorPalObj)
protected:
	CColorPalObj();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorPalObj)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CColorPalObj();

	// Generated message map functions
	//{{AFX_MSG(CColorPalObj)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CColorPalObj)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CColorPalObj)
	afx_msg long GetHPal();
	afx_msg BOOL CreateColorCube();
	afx_msg void Draw(long hDC, long x1, long y1, long x2, long y2);
	afx_msg void MakeIdentity();
	afx_msg BOOL CreateFromImage(LPDISPATCH pImage);
	afx_msg void Apply(long hDC);
	afx_msg void Remove(long hDC);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

    CColorPalette m_Pal;
    HDC m_hdcActive;
    HPALETTE m_hpalOld;
};

/////////////////////////////////////////////////////////////////////////////
