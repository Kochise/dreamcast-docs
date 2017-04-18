//
// VdMFCDlg.cpp: Implements the CVdMFCDlg class, which is
//               the application's main dialog. 
//
// Copyright (C) 1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Broadcast Architecture Programmer's Reference.
// For detailed information regarding Broadcast
// Architecture, see the reference.
//

#include "stdafx.h"
#include <initguid.h>
#include "VdMFC.h"
#include "VdMFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVdMFCDlg dialog

CVdMFCDlg::CVdMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVdMFCDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVdMFCDlg)
	m_channel = 0;
	m_filename = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVdMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVdMFCDlg)
	DDX_Control(pDX, IDC_VIDCNTRL, m_CVid);
	DDX_Text(pDX, IDC_EDITCHANNEL, m_channel);
	DDX_Text(pDX, IDC_EDITFILENAME, m_filename);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVdMFCDlg, CDialog)
	//{{AFX_MSG_MAP(CVdMFCDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SETINPUT, OnSetInput)
	ON_BN_CLICKED(IDC_SETOUTPUT, OnSetOutput)
	ON_BN_CLICKED(IDC_SETCHANNEL, OnSetChannel)
	ON_BN_CLICKED(IDC_SETFILENAME, OnSetFile)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_VIDEOON, OnVideoOn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVdMFCDlg message handlers

BOOL CVdMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Assign the list-box control to the CListBox variable and
	// then verify.
	VERIFY( box.SubclassDlgItem( IDC_LISTBOX, this ) );
	
	// Obtain pointers to unknown and enumerate-variant objects.

	LPUNKNOWN lpunk;
	LPENUMVARIANT lpenumvar;

	// Declare and allocate a Devices object and assign the 
	// collection of all the available input and output devices 
	// for the video control to this object.
	CBPCDevices pDevices = m_CVid.GetDevices();

	// Assign the unknown object to the value returned from the
	// GetNewEnum function. GetNewEnum is a custom function added
	// to the CBPCDevices class.
	lpunk = pDevices.GetNewEnum(); 

	// Query the unknown object to obtain an enumerate-variant 
	// object and then release the unknown object.
	if( lpunk == NULL )
		return FALSE;

	VERIFY( SUCCEEDED( lpunk->QueryInterface( IID_IEnumVARIANT, ( void** )&lpenumvar ) ) );
	lpunk->Release();
	
	long celt;
	COleVariant var;

	// While there are still devices that can provide input or  
	// output for the video control, construct a DeviceBase object
	// from the next variant obtained from the enumerate-variant
	// object and add the device's name to the list box.
	while( S_OK == lpenumvar->Next( 1, &var, ( unsigned long* )&celt ) )
	{
		ASSERT( var.vt == VT_DISPATCH );
		CBPCDeviceBase id( var.pdispVal );
		box.AddString( id.GetName() );

		var.Clear();
	}

	// Release the enumerate-variant object.
	lpenumvar->Release();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVdMFCDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVdMFCDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVdMFCDlg::OnSetInput() 
{
	LPUNKNOWN lpunk;
	LPENUMVARIANT lpenumvar;
	BOOL bFound = FALSE;
	IBPCDeviceBase* pDevice;

	CBPCDevices pDevices = m_CVid.GetDevices();
	lpunk = pDevices.GetNewEnum(); //GetNewEnum custom function see 
								   //details

	if( lpunk == NULL )
		return;

	VERIFY( SUCCEEDED( lpunk->QueryInterface( IID_IEnumVARIANT, ( void** )&lpenumvar ) ) );
	lpunk->Release();

	for( int i = 0; i < m_CVid.GetDeviceCount(); i++ )
	{
		long celt;
		COleVariant var;

		if( SUCCEEDED( lpenumvar->Next( 1, &var, (unsigned long*)&celt ) ) )
		{
			var.punkVal->QueryInterface( IID_IBPCDeviceBase, (void**)&pDevice );

			if( pDevice != NULL )
			{
				BSTR bsDeviceName;
				pDevice->get_Name( &bsDeviceName );
				CString str( bsDeviceName );
				SysFreeString( bsDeviceName );

				CString string;
				int sel = box.GetCurSel();

				if( sel == LB_ERR )
				{
					AfxMessageBox( "Please select a device from the list" );
					pDevice->Release();
					lpenumvar->Release();
					var.Clear();
					return;
				}
				box.GetText( sel, string );

				if( str == string )
				{
					m_CVid.SetInput( pDevice );
					m_pDeviceBase = pDevice;
					bFound = TRUE; 
				}
				pDevice->Release();
			}
			var.Clear();
		}
		if( bFound )
			break;
	}
	ASSERT( lpenumvar != NULL );
	lpenumvar->Release();	
}

void CVdMFCDlg::OnSetOutput() 
{
	LPUNKNOWN lpunk;
	LPENUMVARIANT lpenumvar;
	BOOL bFound = FALSE;
	IBPCDeviceBase* pDevice;

	CBPCDevices pDevices = m_CVid.GetDevices();
	lpunk = pDevices.GetNewEnum(); //GetNewEnum custom function see 
								   //details

	if( lpunk == NULL )
		return;

	VERIFY( SUCCEEDED( lpunk->QueryInterface( IID_IEnumVARIANT, ( void** )&lpenumvar ) ) );
	lpunk->Release();

	for( int i = 0; i < m_CVid.GetDeviceCount(); i++ )
	{
		long celt;
		COleVariant var;

		if( SUCCEEDED( lpenumvar->Next( 1, &var, (unsigned long*)&celt ) ) )
		{
			var.punkVal->QueryInterface( IID_IBPCDeviceBase, (void**)&pDevice );

			if( pDevice != NULL )
			{
				BSTR bsDeviceName;
				pDevice->get_Name( &bsDeviceName );
				CString str( bsDeviceName );
				SysFreeString( bsDeviceName );

				CString string;
				int sel = box.GetCurSel();

				if( sel == LB_ERR )
				{
					AfxMessageBox( "Please select a device from the list" );
					pDevice->Release();
					lpenumvar->Release();
					var.Clear();
					return;
				}
				box.GetText( sel, string );

				if( str == string )
				{
					m_CVid.SetOutput( pDevice );
					m_pDeviceBase = pDevice;
					bFound = TRUE; 
				}
				pDevice->Release();
			}
			var.Clear();
		}
		if( bFound )
			break;
	}
	ASSERT( lpenumvar != NULL );
	lpenumvar->Release();	
}

void CVdMFCDlg::OnVideoOn() 
{
	m_CVid.SetVideoOn( !m_CVid.GetVideoOn() );
	
}

void CVdMFCDlg::OnSetChannel() 
{
	UpdateData( TRUE );
 	CBPCDeviceBase id;
	
	id.AttachDispatch( m_pDeviceBase, FALSE );
	id.SetChannel( m_channel );
}

void CVdMFCDlg::OnSetFile() 
{
	UpdateData( TRUE );
	m_CVid.SetFileName( m_filename );
	
}

void CVdMFCDlg::OnPlay() 
{
	m_CVid.Run();
	
}

void CVdMFCDlg::OnPause() 
{
	m_CVid.Pause();
	
}

void CVdMFCDlg::OnStop() 
{
	m_CVid.Stop();
	
}

