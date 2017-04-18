// PicCube.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PicCube.h"
#include "GLlib.h"
#include "Scene.h"
#include "glwnd.h"
#include "savewnd.h"
#include "movewnd.h"
#include "configdl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicCubeApp

BEGIN_MESSAGE_MAP(CPicCubeApp, CWinApp)
	//{{AFX_MSG_MAP(CPicCubeApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicCubeApp construction

CPicCubeApp::CPicCubeApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPicCubeApp object

CPicCubeApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPicCubeApp initialization

BOOL CPicCubeApp::InitInstance()
{
 	Enable3dControls();

    // If the command line contains /s -s or s then just run as a 
    // screen saver.  If the command line is blank or contains 
    // /c -c or c then show the config dialog
	
    if (((!strcmpi(m_lpCmdLine,"/s") 
    		||  !strcmpi(m_lpCmdLine,"-s")) 
    		||  !strcmpi(m_lpCmdLine,"s")))
    {
    
        // Run as screen saver
        CMovingChildWnd* pWnd = new CMovingChildWnd;
        pWnd->Create();
        m_pMainWnd = pWnd;
	    return TRUE;

    }
    else
    {
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

void CPicCubeApp::DoConfig(CWnd* pParent)
{
    CConfigDlg dlg(pParent);

    // Set up the current params

    // Do the dialog
    if (dlg.DoModal() != IDOK) return;

    // Save the new params

}
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CPicCubeApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPicCubeApp commands
