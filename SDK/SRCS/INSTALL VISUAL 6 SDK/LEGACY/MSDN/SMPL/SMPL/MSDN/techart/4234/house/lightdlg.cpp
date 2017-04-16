// lightdlg.cpp : implementation file
//

#include "stdafx.h"
#include "House.h"
#include "..\include\impiunk.h"
#include "..\include\ilight.h"
#include "..\include\inotify.h"
#include "..\include\inotifysrc.h"
#include "lightdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLightDlg dialog


CLightDlg::CLightDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLightDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLightDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pILight = NULL;
    m_pParent = NULL;
}

void CLightDlg::Create()
{
    CDialog::Create(IDD);
}


void CLightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLightDlg)
	DDX_Control(pDX, IDC_BRIGHTNESS, m_wndBright);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLightDlg, CDialog)
	//{{AFX_MSG_MAP(CLightDlg)
	ON_WM_CLOSE()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// 3:Interface map for Notification
BEGIN_INTERFACE_MAP(CLightDlg, CDialog)
    INTERFACE_PART(CLightDlg, IID_INotify, Notify)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLightDlg message handlers

BOOL CLightDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Make sure we have a light to play with
	ASSERT(m_pILight);

    // AddRef it so it can't go away while we are using it
    m_pILight->AddRef();

    // 3:Tell it we'd like change notification
    INotifySrc* pINotifySrc = NULL;
    if (m_pILight->QueryInterface(IID_INotifySrc, (LPVOID*)&pINotifySrc) != S_OK) {
        dprintf2("INotifySrc not supported");
    } else {

        // Give the COM object a pointer to our own INotify interface
        // and use the user info ptr to store the object's IUnknown ptr
        m_pINotify = NULL;
        ExternalQueryInterface(&IID_INotify, (LPVOID*)&m_pINotify);
        ASSERT(m_pINotify); 
        pINotifySrc->AddUser(m_pINotify, m_pILight);

        // free the interface
        pINotifySrc->Release();
    }


    // And know which window to repaint for changes
    ASSERT(m_pParent);
	
    // Set the slider range
    m_wndBright.SetRange(0, 255);
    BYTE b;
    m_pILight->GetBrightness(&b);
    m_wndBright.SetPos(255 - b);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// Note: very important for modal dialogs to include
// this handler which is always the last thing called.
// this is where you can safely delete the C++ object
void CLightDlg::PostNcDestroy() 
{
    // 3:Remove the notification event
    INotifySrc* pINotifySrc = NULL;
    m_pILight->QueryInterface(IID_INotifySrc, (LPVOID*)&pINotifySrc);
    ASSERT(pINotifySrc);
    ASSERT(m_pINotify);
    pINotifySrc->RemoveUser(m_pINotify);
    pINotifySrc->Release();

    // Done with our own interface ptr
    m_pINotify->Release();

    // Release the ILight interface
    ASSERT(m_pILight);
    m_pILight->Release();
    delete this;
}

void CLightDlg::OnClose() 
{
    DestroyWindow();
}

void CLightDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CSliderCtrl* pSlider = (CSliderCtrl*) pScrollBar;
	UINT nOldPos = pSlider->GetPos();
    UINT nNewPos = nOldPos;
	
	// This can only come from the slider
    switch (nSBCode) {
    case TB_THUMBTRACK:
        nNewPos = nPos;
        break;
        
    }
    
    m_pILight->SetBrightness(255 - nNewPos);
}

//////////////////////////////////////////////////////////////////////////////
// 3:INotify

    IMPLEMENT_IUNKNOWN(CLightDlg, Notify)

STDMETHODIMP CLightDlg::XNotify::Change(LPVOID pUserInfo)
{
    METHOD_PROLOGUE(CLightDlg, Notify);

    // The object has changed so redraw to see the effect
    BYTE b;
    pThis->m_pILight->GetBrightness(&b);
    pThis->m_wndBright.SetPos(255 - b);

    return NOERROR;
}

