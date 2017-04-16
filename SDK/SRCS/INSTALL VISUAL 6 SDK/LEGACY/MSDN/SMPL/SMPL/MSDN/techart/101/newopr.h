#ifndef __NEWOPR_H__
#define __NEWOPR_H__

/////////////////////////////////////////////////////////////////////////////
//
//  This class just wastes space
//
class CSpaceWaste : public CObject{
	private:
		char space[1024] ;
};

/////////////////////////////////////////////////////////////////////////////
//
// CMainWindow:
// See NEWOPR.cpp for the code to the member functions and the message map.
//
class CMainWindow : public CFrameWnd
{
public:
	CMainWindow();

	afx_msg void OnPaint();
	afx_msg void OnDestroy() ;
	afx_msg void OnAbout();
	afx_msg void OnAlloc() ;
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

// CTheApp:
// See NEWOPR.cpp for the code to the InitInstance member function.
//
class CTheApp : public CWinApp
{
public:
	BOOL InitInstance();
};

/////////////////////////////////////////////////////////////////////////////

#endif // __NEWOPR_H__

