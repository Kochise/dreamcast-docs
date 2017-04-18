// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.
//
#include <afxwin.h>

class CProg2 {
	private:
		int nCount;

		//Do not use non-static functions as callbacks.
		int FAR PASCAL EXPORT 
			EnumObjectsProc( LPSTR lpLogObject, LPSTR lpData) ;
		
	public:		
		//Constructor
		 CProg2() : nCount(NULL) {} ;
	 
		//Member Function
		 void enumIt(HDC hdc) ;
 };
		
void CProg2::enumIt(HDC hdc)	 
 {	 
#pragma message("MESSAGE:-------------------------------------")
#pragma message("The next line of code will generate an error.")
#pragma message("---------------------------------------------")
  ::EnumObjects(hdc, OBJ_BRUSH, (FARPROC)EnumObjectsProc, NULL) ;	
 }
 
int FAR PASCAL EXPORT CProg2::EnumObjectsProc( LPSTR lpLogObject, LPSTR lpData)
{
	nCount++ ;
	MessageBeep(0) ;
	return 1 ;
}


//////////////////////////////////////////////////////
//
// helloapp.cpp : Minimal MFC Windows app.
//
// Define a window class derived from CFrameWnd
class CHelloWindow : public CFrameWnd
{ 
public:
	CHelloWindow() 
		{ Create(NULL, "Hello World!", WS_OVERLAPPEDWINDOW, rectDefault);
		  CProg2 cprog2;
			cprog2.enumIt( ::GetDC(GetSafeHwnd()) );
		}
};

// Define an application class derived from CWinApp
class CHelloApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

// Construct the CHelloApp's m_pMainWnd data member
BOOL CHelloApp::InitInstance()
{
	m_pMainWnd = new CHelloWindow();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

CHelloApp HelloApp;  // HelloApp's constructor initializes and runs the app
