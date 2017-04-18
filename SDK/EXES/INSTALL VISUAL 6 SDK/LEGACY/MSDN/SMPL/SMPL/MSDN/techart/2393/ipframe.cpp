// WOSA/XRT XRTFrame Sample Application Version 1.01
//
// Copyright (c) 1993-94 Microsoft Corporation, All Rights Reserved.
//
//      This is a part of the Microsoft Source Code Samples. 
//      This source code is only intended as a supplement to 
//      Microsoft Development Tools and/or WinHelp documentation.
//      See these sources for detailed information regarding the 
//      Microsoft samples programs.
//
// ipframe.cpp : implementation of the CInPlaceFrame class
//

#include "stdafx.h"
#include "xrtframe.h"

#include "ipframe.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInPlaceFrame

IMPLEMENT_DYNCREATE(CInPlaceFrame, COleIPFrameWnd)
#define new DEBUG_NEW

BEGIN_MESSAGE_MAP(CInPlaceFrame, COleIPFrameWnd)
    //{{AFX_MSG_MAP(CInPlaceFrame)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
    // Global help commands
    ON_COMMAND(ID_HELP_INDEX, COleIPFrameWnd::OnHelpIndex)
    ON_COMMAND(ID_HELP_USING, COleIPFrameWnd::OnHelpUsing)
    ON_COMMAND(ID_HELP, COleIPFrameWnd::OnHelp)
    ON_COMMAND(ID_DEFAULT_HELP, COleIPFrameWnd::OnHelpIndex)
    ON_COMMAND(ID_CONTEXT_HELP, COleIPFrameWnd::OnContextHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
    // same order as in the bitmap 'itoolbar.bmp'
    ID_EDIT_COPY,
    ID_EDIT_COPYALL,
        ID_SEPARATOR,
    ID_EDIT_REMOVEITEM,
    ID_EDIT_CHANGEITEM,
    ID_EDIT_ADDITEM,
        ID_SEPARATOR,
    ID_OPTIONS_ACTIVE,
        ID_SEPARATOR,
    ID_APP_ABOUT,
};

/////////////////////////////////////////////////////////////////////////////
// CInPlaceFrame construction/destruction

CInPlaceFrame::CInPlaceFrame()
{
}

CInPlaceFrame::~CInPlaceFrame()
{
}

int CInPlaceFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (COleIPFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    // CResizeBar implements in-place resizing.
    if (!m_wndResizeBar.Create(this))
    {
        TRACE("Failed to create resize bar\n");
        return -1;      // fail to create
    }

    // By default, it is a good idea to register a drop-target that does
    //  nothing with your frame window.  This prevents drops from
    //  "falling through" to a container that supports drag-drop.
    m_dropTarget.Register(this);

    return 0;
}

// OnCreateControlBars is called by the framework to create control bars on the
//  container application's windows.  pWndFrame is the top level frame window of
//  the container and is always non-NULL.  pWndDoc is the doc level frame window
//  and will be NULL when the container is an SDI application.  A server
//  application can place MFC control bars on either window.
BOOL CInPlaceFrame::OnCreateControlBars(CWnd* pWndFrame, CWnd* pWndDoc)
{
    // Create toolbar on client's frame window
    if (!m_wndToolBar.Create(pWndFrame) ||
        !m_wndToolBar.LoadBitmap(IDR_XRTFRMTYPE_SRVR_IP) ||
        !m_wndToolBar.SetButtons(buttons, sizeof(buttons)/sizeof(UINT)))
    {
        TRACE("Failed to create toolbar\n");
        return FALSE;
    }
    // Set owner to this window, so messages are delivered to correct app
    m_wndToolBar.SetOwner(this);

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CInPlaceFrame diagnostics

#ifdef _DEBUG
void CInPlaceFrame::AssertValid() const
{
    COleIPFrameWnd::AssertValid();
}

void CInPlaceFrame::Dump(CDumpContext& dc) const
{
    COleIPFrameWnd::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInPlaceFrame commands
