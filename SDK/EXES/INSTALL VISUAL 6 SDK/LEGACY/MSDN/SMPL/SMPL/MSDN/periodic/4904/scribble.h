#include "resource.h"       // main symbols

class CScribbleApp : public CWinApp {
public:
	CScribbleApp();
	//{{AFX_VIRTUAL(CScribbleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	//{{AFX_MSG(CScribbleApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileSample();	// **MOD** new command handler
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
