// savewnd.h : header file
//

#ifndef _SAVEWND_
#define _SAVEWND_

/////////////////////////////////////////////////////////////////////////////
// CSaveWnd window

class CSaveWnd : public CWnd
{
// Construction
public:
	CSaveWnd();
    BOOL Create();


private:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveWnd)
	protected:
	virtual void PostNcDestroy();
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSaveWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSaveWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif // _SAVEWND_
