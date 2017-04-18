#include "stdafx.h"
#include "enumdoc.h"
#include "mainfrm.h"

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
   ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT BASED_CODE buttons[] = {
   ID_FILE_NEW,
      ID_SEPARATOR,
   ID_APP_ABOUT,
};

static UINT BASED_CODE indicators[] = {
   ID_SEPARATOR,
   ID_INDICATOR_CAPS,
   ID_INDICATOR_NUM,
   ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
      return -1;

   if (!m_wndToolBar.Create(this) ||
      !m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
      !m_wndToolBar.SetButtons(buttons, sizeof(buttons)/sizeof(UINT)))
   {
      TRACE("Failed to create toolbar\n");
      return -1;      // fail to create
   }
   if (!m_wndStatusBar.Create(this) ||
      !m_wndStatusBar.SetIndicators(indicators, 
         sizeof(indicators)/sizeof(UINT)))
   {
      TRACE("Failed to create status bar\n");
      return -1;      // fail to create
   }
   return 0;
}

