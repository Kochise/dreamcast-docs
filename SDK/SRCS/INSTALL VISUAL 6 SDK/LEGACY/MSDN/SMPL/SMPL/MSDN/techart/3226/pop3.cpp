// pop3.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "pop3.h"
#include "configdl.h"
#include "mywnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPop3App

BEGIN_MESSAGE_MAP(CPop3App, CWinApp)
	//{{AFX_MSG_MAP(CPop3App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPop3App construction

CPop3App::CPop3App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPop3App object

CPop3App theApp;

/////////////////////////////////////////////////////////////////////////////
// CPop3App initialization

BOOL CPop3App::InitInstance()
{
    // If the command line contains /s -s or s then just run as a 
    // screen saver.  If the command line is blank or contains 
    // /c -c or c then show the config dialog
	
    if (((!strcmpi(m_lpCmdLine,"/s") 
    || !strcmpi(m_lpCmdLine,"-s")) 
    || !strcmpi(m_lpCmdLine,"s"))) {
    
        // Run as screen saver
        CMyWnd* pWnd = new CMyWnd;
        pWnd->Create();
        m_pMainWnd = pWnd;
	    return TRUE;
    } else {
    
        // Run the configuration dialog
        if(((!strcmpi(m_lpCmdLine,"/c") 
           || !strcmpi(m_lpCmdLine,"-c")) 
           || !strcmpi(m_lpCmdLine,"c"))) {

            // Run config with current window as parent
            DoConfig(CWnd::GetActiveWindow());

        } else {

            // Run the config dlg with no parent
            DoConfig(NULL);
        }

        // Now just terminate
        return FALSE;
    }
}

void CPop3App::DoConfig(CWnd* pParent)
{
    CConfigDlg dlg(pParent);

    // Set up the current params
    dlg.m_iBackground = GetProfileInt("Config",
                                      "Background",
                                      0);

    // Do the dialog
    if (dlg.DoModal() != IDOK) return;

    // Save the new params
    WriteProfileInt("Config",
                    "Background",
                    dlg.m_iBackground);
}
