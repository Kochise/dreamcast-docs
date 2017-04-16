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
#include <afxcoll.h>
#include "ctimer.h"

class CHelloWindow ;

class CMyTimer : public CTimer {
	private:
		CHelloWindow * output;
	protected:
		void timer(DWORD dwTimer) ;  
									
	public:
		CMyTimer() : output(0) {} ;
		
		void setWindow(CHelloWindow * wnd) {output = wnd;};
};

						
//////////////////////////////////////////////////////
//
// helloapp.cpp : Minimal MFC Windows app.
//
// Define a window class derived from CFrameWnd
class CHelloWindow : public CFrameWnd
{ 
private:
	  CMyTimer aTimer ;
	  short int line ;
	  short int height ;
public:
	CHelloWindow() : line(0) 
		{ 
		  Create(NULL, "Hello World!", WS_OVERLAPPEDWINDOW, rectDefault);
		  
		  CClientDC dc(this) ;
		  TEXTMETRIC metrics ;
		  dc.GetTextMetrics( &metrics) ;
		  height = metrics.tmHeight ;

		  aTimer.setWindow(this) ;
		  aTimer.start(100) ;
		  
		} ;
		
	void write(const LPSTR str);
};


void CHelloWindow::write(const LPSTR str)
{
	CClientDC dc(this) ;
	dc.TextOut(0, line, str, lstrlen(str)) ;
	line += height ;
}







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

//--------------------------------------------------------
void CMyTimer::timer(DWORD dwTimer)
{
	MessageBeep(0);
	if (output)
		output->write("This is the end.") ;
} 

						
