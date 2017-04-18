/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          ShlView.cpp
   
   Description:   Implements IShellView.

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "ShlView.h"
#include "Guid.h"
#include "resource.h"
#include "tools.h"

#define TOOLBAR_ID   (L"RegView")

MYTOOLINFO g_Tools[] = 
   {
   IDM_VIEW_KEYS, 0, IDS_TB_VIEW_KEYS, IDS_MI_VIEW_KEYS, 0, TBSTATE_ENABLED,  TBSTYLE_BUTTON,
   IDM_VIEW_IDW,  0, IDS_TB_VIEW_IDW,  IDS_MI_VIEW_IDW,  0, TBSTATE_ENABLED,  TBSTYLE_BUTTON,
   -1, 0, 0, 0, 0,
   };

/**************************************************************************

   CShellView::CShellView()

**************************************************************************/

CShellView::CShellView(CShellFolder *pFolder, LPCITEMIDLIST pidl)
{
#ifdef INITCOMMONCONTROLSEX

INITCOMMONCONTROLSEX iccex;
iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
iccex.dwICC = ICC_LISTVIEW_CLASSES;
InitCommonControlsEx(&iccex);

#else

InitCommonControls();

#endif   //INITCOMMONCONTROLSEX

m_hMenu = NULL;
m_pDockingWindow = NULL;

m_pPidlMgr = new CPidlMgr();
if(!m_pPidlMgr)
   {
   delete this;
   return;
   }

m_pSFParent = pFolder;
if(m_pSFParent)
   m_pSFParent->AddRef();

//get the shell's IMalloc pointer
//we'll keep this until we get destroyed
if(FAILED(SHGetMalloc(&m_pMalloc)))
   {
   delete this;
   return;
   }

m_pidl = m_pPidlMgr->Copy(pidl);

m_uState = SVUIA_DEACTIVATE;

m_ObjRefCount = 1;
g_DllRefCount++;
}

/**************************************************************************

   CShellView::~CShellView()

**************************************************************************/

CShellView::~CShellView()
{
if(m_pidl)
   {
   m_pPidlMgr->Delete(m_pidl);
   m_pidl = NULL;
   }

if(m_pSFParent)
   m_pSFParent->Release();

if(m_pMalloc)
   {
   m_pMalloc->Release();
   }

if(m_pPidlMgr)
   {
   delete m_pPidlMgr;
   }

g_DllRefCount--;
}

///////////////////////////////////////////////////////////////////////////
//
// IUnknown Implementation
//

/**************************************************************************

   CShellView::QueryInterface

**************************************************************************/

STDMETHODIMP CShellView::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
*ppReturn = NULL;

//IUnknown
if(IsEqualIID(riid, IID_IUnknown))
   {
   *ppReturn = this;
   }

//IOleWindow
else if(IsEqualIID(riid, IID_IOleWindow))
   {
   *ppReturn = (IOleWindow*)this;
   }

//IShellView
else if(IsEqualIID(riid, IID_IShellView))
   {
   *ppReturn = (IShellView*)this;
   }   

//IOleCommandTarget
else if(IsEqualIID(riid, IID_IOleCommandTarget))
   {
   *ppReturn = (IOleCommandTarget*)this;
   }   

if(*ppReturn)
   {
   (*(LPUNKNOWN*)ppReturn)->AddRef();
   return S_OK;
   }

return E_NOINTERFACE;
}                                             

/**************************************************************************

   CShellView::AddRef

**************************************************************************/

STDMETHODIMP_(DWORD) CShellView::AddRef()
{
return ++m_ObjRefCount;
}


/**************************************************************************

   CShellView::Release

**************************************************************************/

STDMETHODIMP_(DWORD) CShellView::Release()
{
if(--m_ObjRefCount == 0)
   {
   delete this;
   return 0;
   }
   
return m_ObjRefCount;
}

///////////////////////////////////////////////////////////////////////////
//
// IOleWindow Implementation
//

/**************************************************************************

   CShellView::GetWindow()
   
**************************************************************************/

STDMETHODIMP CShellView::GetWindow(HWND *phWnd)
{
*phWnd = m_hWnd;

return S_OK;
}

/**************************************************************************

   CShellView::ContextSensitiveHelp()
   
**************************************************************************/

STDMETHODIMP CShellView::ContextSensitiveHelp(BOOL fEnterMode)
{
return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////
//
// IOleCommandTarget Implementation
//

/**************************************************************************

   CShellView::QueryStatus()
   
**************************************************************************/

STDMETHODIMP CShellView::QueryStatus(  const GUID *pguidCmdGroup, 
                                       ULONG cCmds, 
                                       OLECMD prgCmds[], 
                                       OLECMDTEXT *pCmdText)
{
ULONG i;

//only process the commands for our command group
if(pguidCmdGroup && (*pguidCmdGroup != CLSID_CmdGrp))
   return OLECMDERR_E_UNKNOWNGROUP;

//make sure prgCmds is not NULL
if(!prgCmds)
   return E_POINTER;

//run through all of the commands and supply the correct information
for(i = 0; i < cCmds;i++)
   {
   switch(prgCmds[i].cmdID)
      {
      case IDM_VIEW_KEYS:
         prgCmds[i].cmdf = OLECMDF_SUPPORTED | OLECMDF_ENABLED;
         break;
      }
   }

return S_OK;
}

/**************************************************************************

   CShellView::Exec()
   
**************************************************************************/

STDMETHODIMP CShellView::Exec(   const GUID *pguidCmdGroup, 
                                 DWORD nCmdID, 
                                 DWORD nCmdExecOpt, 
                                 VARIANTARG *pvaIn, 
                                 VARIANTARG *pvaOut)
{
//only process the commands for our command group
if(pguidCmdGroup && (*pguidCmdGroup == CLSID_CmdGrp))
   {
   OnCommand(nCmdID, 0, NULL);
   return S_OK;
   }

return OLECMDERR_E_UNKNOWNGROUP;
}

///////////////////////////////////////////////////////////////////////////
//
// IShellView Implementation
//

/**************************************************************************

   CShellView::TranslateAccelerator()
   
**************************************************************************/

STDMETHODIMP CShellView::TranslateAccelerator(LPMSG pMsg)
{
return E_NOTIMPL;
}

/**************************************************************************

   CShellView::EnableModeless()
   
**************************************************************************/

STDMETHODIMP CShellView::EnableModeless(BOOL fEnable)
{
return E_NOTIMPL;
}

/**************************************************************************

   CShellView::OnActivate()
   
**************************************************************************/

LRESULT CShellView::OnActivate(UINT uState)
{
//don't do anything if the state isn't really changing
if(m_uState == uState)
   return S_OK;

OnDeactivate();

//only do this if we are active
if(uState != SVUIA_DEACTIVATE)
   {
   //merge the menus
   m_hMenu = CreateMenu();
   
   if(m_hMenu)
      {
   	OLEMENUGROUPWIDTHS   omw = {0, 0, 0, 0, 0, 0};
      MENUITEMINFO         mii;
      TCHAR                szText[MAX_PATH];

      m_pShellBrowser->InsertMenusSB(m_hMenu, &omw);

      //build the top level menu
      //get the menu item's text
      LoadString(g_hInst, IDS_MI_REGISTRY, szText, sizeof(szText));
      
      ZeroMemory(&mii, sizeof(mii));
      mii.cbSize = sizeof(mii);
      mii.fMask = MIIM_SUBMENU | MIIM_TYPE | MIIM_STATE;
      mii.fType = MFT_STRING;
      mii.fState = MFS_ENABLED;
      mii.dwTypeData = szText;
      mii.hSubMenu = BuildRegistryMenu();

      //insert our menu into the menu bar
      if(mii.hSubMenu)
         {
         InsertMenuItem(m_hMenu, FCIDM_MENU_HELP, FALSE, &mii);
         }

      //get the view menu so we can merge with it
      ZeroMemory(&mii, sizeof(mii));
      mii.cbSize = sizeof(mii);
      mii.fMask = MIIM_SUBMENU;
      
      if(GetMenuItemInfo(m_hMenu, FCIDM_MENU_VIEW, FALSE, &mii))
         {
         MergeViewMenu(mii.hSubMenu);
         }

      //add the items that should only be added if we have the focus
      if(SVUIA_ACTIVATE_FOCUS == uState)
         {
         //get the file menu so we can merge with it
         ZeroMemory(&mii, sizeof(mii));
         mii.cbSize = sizeof(mii);
         mii.fMask = MIIM_SUBMENU;
      
         if(GetMenuItemInfo(m_hMenu, FCIDM_MENU_FILE, FALSE, &mii))
            {
            MergeFileMenu(mii.hSubMenu);
            }
         }

      m_pShellBrowser->SetMenuSB(m_hMenu, NULL, m_hWnd);
      }
   }

m_uState = uState;

return 0;
}

/**************************************************************************

   CShellView::OnDeactivate()
   
**************************************************************************/

void CShellView::OnDeactivate(void)
{
if(m_uState != SVUIA_DEACTIVATE)
   {
   if(m_hMenu)
      {
      m_pShellBrowser->SetMenuSB(NULL, NULL, NULL);

      m_pShellBrowser->RemoveMenusSB(m_hMenu);

      DestroyMenu(m_hMenu);

      m_hMenu = NULL;
      }

   m_uState = SVUIA_DEACTIVATE;
   }
}

/**************************************************************************

   CShellView::UIActivate()

   This function activates the view window. Note that activating it 
   will not change the focus, while setting the focus will activate it.

   
**************************************************************************/

STDMETHODIMP CShellView::UIActivate(UINT uState)
{
//don't do anything if the state isn't really changing
if(m_uState == uState)
   return S_OK;

//OnActivate handles the menu merging and internal state
OnActivate(uState);

//remove the docking window
if(g_bShowIDW)
   AddRemoveDockingWindow(FALSE);

//only do this if we are active
if(uState != SVUIA_DEACTIVATE)
   {
   TCHAR szName[MAX_PATH];
   LRESULT  lResult;
   int      nPartArray[1] = {-1};
   
   //update the status bar
   LoadString(g_hInst, IDS_REGISTRY_TITLE, szName, sizeof(szName));
   
   m_pSFParent->GetFolderPath(szName + lstrlen(szName), sizeof(szName) - lstrlen(szName));

   //set the number of parts
   m_pShellBrowser->SendControlMsg(FCW_STATUS, SB_SETPARTS, 1, (LPARAM)nPartArray, &lResult);

   //set the text for the parts
   m_pShellBrowser->SendControlMsg(FCW_STATUS, SB_SETTEXT, 0, (LPARAM)szName, &lResult);

   //add the docking window if necessary
   if(g_bShowIDW)
      AddRemoveDockingWindow(TRUE);
   }

return S_OK;
}

/**************************************************************************

   CShellView::BuildRegistryMenu()
   
**************************************************************************/

HMENU CShellView::BuildRegistryMenu(void)
{
HMENU hSubMenu = CreatePopupMenu();

if(hSubMenu)
   {
   TCHAR          szText[MAX_PATH];
   MENUITEMINFO   mii;
   int            nTools,
                  i;
   //get the number of items in our global array
   for(nTools = 0; g_Tools[nTools].idCommand != -1; nTools++)
      {
      }

   //add the menu items
   for(i = 0; i < nTools; i++)
      {
      LoadString(g_hInst, g_Tools[i].idMenuString, szText, sizeof(szText));
      
      ZeroMemory(&mii, sizeof(mii));
      mii.cbSize = sizeof(mii);
      mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;

      if(TBSTYLE_SEP != g_Tools[i].bStyle)
         {
         mii.fType = MFT_STRING;
         mii.fState = MFS_ENABLED;
         mii.dwTypeData = szText;
         mii.wID = g_Tools[i].idCommand;
         }
      else
         {
         mii.fType = MFT_SEPARATOR;
         }
      
      //tack this item onto the end of the menu
      InsertMenuItem(hSubMenu, (UINT)-1, TRUE, &mii);
      }
   }

return hSubMenu;
}

/**************************************************************************

   CShellView::MergeFileMenu()
   
**************************************************************************/

void CShellView::MergeFileMenu(HMENU hSubMenu)
{
if(hSubMenu)
   {
   MENUITEMINFO   mii;
   TCHAR          szText[MAX_PATH];

   ZeroMemory(&mii, sizeof(mii));

   //add a separator
   mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
   mii.fType = MFT_SEPARATOR;
   mii.fState = MFS_ENABLED;

   //insert this item at the beginning of the menu
   InsertMenuItem(hSubMenu, 0, TRUE, &mii);

   //add the file menu items
   LoadString(g_hInst, IDS_MI_FILEITEM, szText, sizeof(szText));
   mii.cbSize = sizeof(mii);
   mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
   mii.fType = MFT_STRING;
   mii.fState = MFS_ENABLED;
   mii.dwTypeData = szText;
   mii.wID = IDM_MYFILEITEM;

   //insert this item at the beginning of the menu
   InsertMenuItem(hSubMenu, 0, TRUE, &mii);
   }
}

/**************************************************************************

   CShellView::MergeViewMenu()
   
**************************************************************************/

void CShellView::MergeViewMenu(HMENU hSubMenu)
{
if(hSubMenu)
   {
   MENUITEMINFO   mii;
   TCHAR          szText[MAX_PATH];

   ZeroMemory(&mii, sizeof(mii));

   //add a separator at the correct position in the menu
   mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
   mii.fType = MFT_SEPARATOR;
   mii.fState = MFS_ENABLED;
   InsertMenuItem(hSubMenu, FCIDM_MENU_VIEW_SEP_OPTIONS, FALSE, &mii);

   //add the view menu items at the correct position in the menu
   LoadString(g_hInst, IDS_MI_VIEW_KEYS, szText, sizeof(szText));
   mii.cbSize = sizeof(mii);
   mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
   mii.fType = MFT_STRING;
   mii.fState = MFS_ENABLED;
   mii.dwTypeData = szText;
   mii.wID = IDM_VIEW_KEYS;
   InsertMenuItem(hSubMenu, FCIDM_MENU_VIEW_SEP_OPTIONS, FALSE, &mii);
   }
}

/**************************************************************************

   CShellView::Refresh()
   
**************************************************************************/

STDMETHODIMP CShellView::Refresh(void)
{
//empty the list
ListView_DeleteAllItems(m_hwndList);

//refill the list
FillList();

return S_OK;
}

/**************************************************************************

   CShellView::CreateViewWindow()
   
**************************************************************************/

STDMETHODIMP CShellView::CreateViewWindow(   LPSHELLVIEW pPrevView, 
                                             LPCFOLDERSETTINGS lpfs, 
                                             LPSHELLBROWSER psb, 
                                             LPRECT prcView, 
                                             HWND *phWnd)
{
WNDCLASS wc;

*phWnd = NULL;

//if our window class has not been registered, then do so
if(!GetClassInfo(g_hInst, NS_CLASS_NAME, &wc))
   {
   ZeroMemory(&wc, sizeof(wc));
   wc.style          = CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc    = (WNDPROC)WndProc;
   wc.cbClsExtra     = 0;
   wc.cbWndExtra     = 0;
   wc.hInstance      = g_hInst;
   wc.hIcon          = NULL;
   wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
   wc.lpszMenuName   = NULL;
   wc.lpszClassName  = NS_CLASS_NAME;
   
   if(!RegisterClass(&wc))
      return E_FAIL;
   }

//set up the member variables
m_pShellBrowser = psb;
m_FolderSettings = *lpfs;

//get our parent window
m_pShellBrowser->GetWindow(&m_hwndParent);

*phWnd = CreateWindowEx(   0,
                           NS_CLASS_NAME,
                           NULL,
                           WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
                           prcView->left,
                           prcView->top,
                           prcView->right - prcView->left,
                           prcView->bottom - prcView->top,
                           m_hwndParent,
                           NULL,
                           g_hInst,
                           (LPVOID)this);
                           
if(!*phWnd)
   return E_FAIL;

m_pShellBrowser->AddRef();

return S_OK;
}

/**************************************************************************

   CShellView::DestroyViewWindow()
   
**************************************************************************/

STDMETHODIMP CShellView::DestroyViewWindow(void)
{
//Make absolutely sure all our UI is cleaned up.
UIActivate(SVUIA_DEACTIVATE);

if(m_hMenu)
   DestroyMenu(m_hMenu);

DestroyWindow(m_hWnd);

//release the shell browser object
m_pShellBrowser->Release();

return S_OK;
}

/**************************************************************************

   CShellView::GetCurrentInfo()
   
**************************************************************************/

STDMETHODIMP CShellView::GetCurrentInfo(LPFOLDERSETTINGS lpfs)
{
*lpfs = m_FolderSettings;

return S_OK;
}

/**************************************************************************

   CShellView::AddPropertySheetPages()
   
**************************************************************************/

STDMETHODIMP CShellView::AddPropertySheetPages( DWORD dwReserved, 
                                                LPFNADDPROPSHEETPAGE lpfn, 
                                                LPARAM lParam)
{
return E_NOTIMPL;
}

/**************************************************************************

   CShellView::SaveViewState()
   
**************************************************************************/

STDMETHODIMP CShellView::SaveViewState(void)
{
return S_OK;
}

/**************************************************************************

   CShellView::SelectItem()
   
**************************************************************************/

STDMETHODIMP CShellView::SelectItem(LPCITEMIDLIST pidlItem, UINT uFlags)
{
return E_NOTIMPL;
}

/**************************************************************************

   CShellView::GetItemObject()
   
**************************************************************************/

STDMETHODIMP CShellView::GetItemObject(UINT uItem, REFIID riid, LPVOID *ppvOut)
{
*ppvOut = NULL;

return E_NOTIMPL;
}


/**************************************************************************

   CShellView::WndProc()
   
**************************************************************************/

LRESULT CALLBACK CShellView::WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
CShellView  *pThis = (CShellView*)GetWindowLong(hWnd, GWL_USERDATA);

switch (uMessage)
   {
   case WM_NCCREATE:
      {
      LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
      pThis = (CShellView*)(lpcs->lpCreateParams);
      SetWindowLong(hWnd, GWL_USERDATA, (LONG)pThis);

      //set the window handle
      pThis->m_hWnd = hWnd;
      }
      break;
   
   case WM_SIZE:
      return pThis->OnSize(LOWORD(lParam), HIWORD(lParam));
   
   case WM_CREATE:
      return pThis->OnCreate();
   
   case WM_SETFOCUS:
      return pThis->OnSetFocus();
   
   case WM_KILLFOCUS:
      return pThis->OnKillFocus();

   case WM_ACTIVATE:
      return pThis->OnActivate(SVUIA_ACTIVATE_FOCUS);
   
   case WM_COMMAND:
      return pThis->OnCommand(   GET_WM_COMMAND_ID(wParam, lParam), 
                                 GET_WM_COMMAND_CMD(wParam, lParam), 
                                 GET_WM_COMMAND_HWND(wParam, lParam));
   
   case WM_INITMENUPOPUP:
      return pThis->UpdateMenu((HMENU)wParam);
   
   case WM_NOTIFY:
      return pThis->OnNotify((UINT)wParam, (LPNMHDR)lParam);
   
   case WM_SETTINGCHANGE:
      return pThis->OnSettingChange((LPCTSTR)lParam);
   }

return DefWindowProc(hWnd, uMessage, wParam, lParam);
}

/**************************************************************************

   CShellView::OnSetFocus()
   
**************************************************************************/

LRESULT CShellView::OnSetFocus(void)
{
/*
Tell the browser one of our windows has received the focus. This should always 
be done before merging menus (OnActivate merges the menus) if one of our 
windows has the focus.
*/
m_pShellBrowser->OnViewWindowActive(this);

OnActivate(SVUIA_ACTIVATE_FOCUS);

return 0;
}

/**************************************************************************

   CShellView::OnKillFocus()
   
**************************************************************************/

LRESULT CShellView::OnKillFocus(void)
{
OnActivate(SVUIA_ACTIVATE_NOFOCUS);

return 0;
}

/**************************************************************************

   CShellView::OnCommand()
   
**************************************************************************/

LRESULT CShellView::OnCommand(DWORD dwCmdID, DWORD dwCmd, HWND hwndCmd)
{
switch(dwCmdID)
   {
   case IDM_VIEW_KEYS:
      g_bViewKeys = ! g_bViewKeys;
      Refresh();
      break;

   case IDM_VIEW_IDW:
      g_bShowIDW = ! g_bShowIDW;
      AddRemoveDockingWindow(g_bShowIDW);
      break;
   
   case IDM_MYFILEITEM:
      MessageBeep(MB_OK);
      break;
   }

return 0;
}

/**************************************************************************

   CShellView::UpdateMenu()
   
**************************************************************************/

LRESULT CShellView::UpdateMenu(HMENU hMenu)
{
CheckMenuItem(hMenu, IDM_VIEW_KEYS, MF_BYCOMMAND | (g_bViewKeys ? MF_CHECKED: MF_UNCHECKED));

if(CanDoIDockingWindow())
   {
   EnableMenuItem(hMenu, IDM_VIEW_IDW, MF_BYCOMMAND | MF_ENABLED);
   CheckMenuItem(hMenu, IDM_VIEW_IDW, MF_BYCOMMAND | (g_bShowIDW ? MF_CHECKED: MF_UNCHECKED));
   }
else
   {
   EnableMenuItem(hMenu, IDM_VIEW_IDW, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
   CheckMenuItem(hMenu, IDM_VIEW_IDW, MF_BYCOMMAND | MF_UNCHECKED);
   }

return 0;
}

/**************************************************************************

   CShellView::OnNotify()
   
**************************************************************************/

LRESULT CShellView::OnNotify(UINT CtlID, LPNMHDR lpnmh)
{
switch(lpnmh->code)
   {
   case NM_SETFOCUS:
      OnSetFocus();
      break;

   case NM_KILLFOCUS:
      OnDeactivate();
      break;

   case HDN_ENDTRACK:
      {
      g_nColumn1 = ListView_GetColumnWidth(m_hwndList, 0);
      g_nColumn2 = ListView_GetColumnWidth(m_hwndList, 1);
      }
      return 0;
   
   case LVN_DELETEITEM:
      {
      NM_LISTVIEW *lpnmlv = (NM_LISTVIEW*)lpnmh;
      
      //delete the pidl because we made a copy of it
      m_pPidlMgr->Delete((LPITEMIDLIST)lpnmlv->lParam);
      }
      break;
   
#ifdef LVN_ITEMACTIVATE
   
   case LVN_ITEMACTIVATE:

#else    //LVN_ITEMACTIVATE

   case NM_DBLCLK:
   case NM_RETURN:

#endif   //LVN_ITEMACTIVATE
      {
      LV_ITEM        lvItem;

      ZeroMemory(&lvItem, sizeof(lvItem));
      lvItem.mask = LVIF_PARAM;

#ifdef LVN_ITEMACTIVATE

      LPNMLISTVIEW   lpnmlv = (LPNMLISTVIEW)lpnmh;
      lvItem.iItem = lpnmlv->iItem;

#else    //LVN_ITEMACTIVATE

      lvItem.iItem = -1;

      //need to find the selected item
      {
      int   i;

      for(i = 0; i < ListView_GetItemCount(m_hwndList); i++)
         {
         if(ListView_GetItemState(m_hwndList, i, LVIS_SELECTED))
            {
            lvItem.iItem = i;
            break;
            }
         }
      //we didn't find a selected item
      if(-1 == lvItem.iItem)
         return 0;
      }

#endif   //LVN_ITEMACTIVATE

      if(ListView_GetItem(m_hwndList, &lvItem))
         {
         //only allow keys to be activated
         if(!m_pPidlMgr->IsValue((LPITEMIDLIST)lvItem.lParam))
            m_pShellBrowser->BrowseObject(   (LPITEMIDLIST)lvItem.lParam, 
                                             SBSP_DEFBROWSER | SBSP_RELATIVE);
         }
      }
      return 0;
   
   case LVN_GETDISPINFO:
      {
      LV_DISPINFO    *lpdi = (LV_DISPINFO *)lpnmh;
      LPITEMIDLIST   pidl = (LPITEMIDLIST)lpdi->item.lParam;

      //is the sub-item information being requested?
      if(lpdi->item.iSubItem)
         {
         //is the text being requested?
         if(lpdi->item.mask & LVIF_TEXT)
            {
            //is this a value or a key?
            if(m_pPidlMgr->IsValue(pidl))
               {
               //get the item's value text
               m_pPidlMgr->GetDataText(m_pidl, pidl, lpdi->item.pszText, lpdi->item.cchTextMax);

               //if the data text is NULL, get the no value string
               if(!*lpdi->item.pszText)
                  LoadString(g_hInst, IDS_NODATA, lpdi->item.pszText, lpdi->item.cchTextMax);
               }
            //its a key
            else
               {
               LoadString(g_hInst, IDS_KEY, lpdi->item.pszText, lpdi->item.cchTextMax);
               }
            }
         }
      //the item text is being requested
      else
         {
         //is the text being requested?
         if(lpdi->item.mask & LVIF_TEXT)
            {
            STRRET   str;

            if(SUCCEEDED(m_pSFParent->GetDisplayNameOf(pidl, SHGDN_NORMAL | SHGDN_INFOLDER, &str)))
               {
               if(STRRET_WSTR == str.uType)
                  {
                  WideCharToLocal(lpdi->item.pszText, str.pOleStr, lpdi->item.cchTextMax);

                  //delete the string buffer
                  m_pMalloc->Free(str.pOleStr);
                  }
               }
            }

         //is the image being requested?
         if(lpdi->item.mask & LVIF_IMAGE)
            {
            IExtractIcon   *pei;

            if(SUCCEEDED(m_pSFParent->GetUIObjectOf(m_hWnd, 1, (LPCITEMIDLIST*)&pidl, IID_IExtractIcon, NULL, (LPVOID*)&pei)))
               {
               UINT  uFlags;

               //GetIconLoaction will give us the index into our image list
               pei->GetIconLocation(GIL_FORSHELL, NULL, 0, &lpdi->item.iImage, &uFlags);

               pei->Release();
               }
            }
         }
      }
      return 0;
   }

return 0;
}

/**************************************************************************

   CShellView::OnSize()
   
**************************************************************************/

LRESULT CShellView::OnSize(WORD wWidth, WORD wHeight)
{
//resize the ListView to fit our window
if(m_hwndList)
   {
   MoveWindow(m_hwndList, 0, 0, wWidth, wHeight, TRUE);
   }

return 0;
}

/**************************************************************************

   CShellView::OnCreate()
   
**************************************************************************/

LRESULT CShellView::OnCreate(void)
{
//create the ListView
if(CreateList())
   {
   if(InitList())
      {
      FillList();
      }
   }

return 0;
}


/**************************************************************************

   CShellView::CreateList()
   
**************************************************************************/

BOOL CShellView::CreateList(void)
{
DWORD dwStyle;

dwStyle =   WS_TABSTOP | 
            WS_VISIBLE |
            WS_CHILD | 
            WS_BORDER | 
            LVS_SINGLESEL |
            LVS_REPORT | 
            LVS_NOSORTHEADER |
            LVS_SHAREIMAGELISTS;

m_hwndList = CreateWindowEx(     WS_EX_CLIENTEDGE,
                                 WC_LISTVIEW,
                                 NULL,
                                 dwStyle,
                                 0,
                                 0,
                                 0,
                                 0,
                                 m_hWnd,
                                 (HMENU)ID_LISTVIEW,
                                 g_hInst,
                                 NULL);

if(!m_hwndList)
   return FALSE;

UpdateShellSettings();

return TRUE;
}

/**************************************************************************

   CShellView::InitList()
   
**************************************************************************/

BOOL CShellView::InitList(void)
{
LV_COLUMN   lvColumn;
RECT        rc;
TCHAR       szString[MAX_PATH];

//empty the list
ListView_DeleteAllItems(m_hwndList);

//initialize the columns
lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
lvColumn.fmt = LVCFMT_LEFT;
lvColumn.pszText = szString;

lvColumn.cx = g_nColumn1;
LoadString(g_hInst, IDS_COLUMN1, szString, sizeof(szString));
ListView_InsertColumn(m_hwndList, 0, &lvColumn);

GetClientRect(m_hWnd, &rc);

lvColumn.cx = g_nColumn2;
LoadString(g_hInst, IDS_COLUMN2, szString, sizeof(szString));
ListView_InsertColumn(m_hwndList, 1, &lvColumn);

ListView_SetImageList(m_hwndList, g_himlSmall, LVSIL_SMALL);

return TRUE;
}

/**************************************************************************

   CShellView::FillList()
   
**************************************************************************/

void CShellView::FillList(void)
{
LPENUMIDLIST   pEnumIDList;

if(SUCCEEDED(m_pSFParent->EnumObjects(m_hWnd, SHCONTF_NONFOLDERS | (g_bViewKeys ? SHCONTF_FOLDERS : 0), &pEnumIDList)))
   {
   LPITEMIDLIST   pidl;
   DWORD          dwFetched;

   //turn the listview's redrawing off
   SendMessage(m_hwndList, WM_SETREDRAW, FALSE, 0);

   while((S_OK == pEnumIDList->Next(1, &pidl, &dwFetched)) && dwFetched)
      {
      LV_ITEM  lvItem;

      ZeroMemory(&lvItem, sizeof(lvItem));

      //set the mask
      lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

      //add the item to the end of the list
      lvItem.iItem = ListView_GetItemCount(m_hwndList);

      //set the item's data
      lvItem.lParam = (LPARAM)m_pPidlMgr->Copy(pidl);

      //get text on a callback basis
      lvItem.pszText = LPSTR_TEXTCALLBACK;

      //get the image on a callback basis
      lvItem.iImage = I_IMAGECALLBACK;

      //add the item
      ListView_InsertItem(m_hwndList, &lvItem);
      }

   //sort the items
   ListView_SortItems(m_hwndList, CompareItems, (LPARAM)m_pSFParent);
   
   //turn the listview's redrawing back on and force it to draw
   SendMessage(m_hwndList, WM_SETREDRAW, TRUE, 0);
   InvalidateRect(m_hwndList, NULL, TRUE);
   UpdateWindow(m_hwndList);

   pEnumIDList->Release();
   }
}

/**************************************************************************

   CShellView::CanDoIDockingWindow()
   
**************************************************************************/

BOOL CShellView::CanDoIDockingWindow(void)
{
#if (_WIN32_IE < 0x0400)

return FALSE;

#else //(_WIN32_IE >= 0x0400)

BOOL              bReturn = FALSE;
HRESULT           hr;
IServiceProvider  *pSP;

//get the browser's IServiceProvider
hr = m_pShellBrowser->QueryInterface((REFIID)IID_IServiceProvider, (LPVOID*)&pSP);
if(SUCCEEDED(hr))
   {
   IDockingWindowFrame *pFrame;

   //get the IDockingWindowFrame
   hr = pSP->QueryService(SID_SShellBrowser, IID_IDockingWindowFrame, (LPVOID*)&pFrame);
   if(SUCCEEDED(hr))
      {
      bReturn = TRUE;

      pFrame->Release();
      }

   pSP->Release();
   }

return bReturn;
#endif   //(_WIN32_IE >= 0x0400)
}

/**************************************************************************

   CShellView::AddRemoveDockingWindow()
   
**************************************************************************/

BOOL CShellView::AddRemoveDockingWindow(BOOL bAdd)
{
#if (_WIN32_IE < 0x0400)

return FALSE;

#else //(_WIN32_IE < 0x0400)

BOOL              bReturn = FALSE;
HRESULT           hr;
IServiceProvider  *pSP;

//get the browser's IServiceProvider
hr = m_pShellBrowser->QueryInterface((REFIID)IID_IServiceProvider, (LPVOID*)&pSP);
if(SUCCEEDED(hr))
   {
   IDockingWindowFrame *pFrame;

   //get the IDockingWindowFrame pointer
   hr = pSP->QueryService(SID_SShellBrowser, IID_IDockingWindowFrame, (LPVOID*)&pFrame);
   if(SUCCEEDED(hr))
      {
      if(bAdd)
         {
         hr = S_OK;
         if(!m_pDockingWindow)
            {
            //create the toolbar object
            m_pDockingWindow = new CDockingWindow(this, m_hWnd);
            }

         if(m_pDockingWindow)
            {
            //add the toolbar object
            hr = pFrame->AddToolbar((IDockingWindow*)m_pDockingWindow, TOOLBAR_ID, 0);

            if(SUCCEEDED(hr))
               {
               bReturn = TRUE;
               }
            }
         }
      else
         {
         if(m_pDockingWindow)
            {
            hr = pFrame->RemoveToolbar((IDockingWindow*)m_pDockingWindow, DWFRF_NORMAL);

            if(SUCCEEDED(hr))
               {
               /*
               RemoveToolbar should release the toolbar object which will cause 
               it to destroy itself. Our toolbar object is no longer valid at 
               this point.
               */
               m_pDockingWindow = NULL;
               bReturn = TRUE;
               }
            }
         }
      pFrame->Release();
      }
   pSP->Release();
   }

return bReturn;
#endif   //(_WIN32_IE < 0x0400)
}

/**************************************************************************

   CShellView::UpdateShellSettings()
   
**************************************************************************/

typedef void (WINAPI *PFNSHGETSETTINGSPROC)(LPSHELLFLAGSTATE lpsfs, DWORD dwMask);

void CShellView::UpdateShellSettings(void)
{
#if (_WIN32_IE >= 0x0400)
SHELLFLAGSTATE       sfs;
HINSTANCE            hinstShell32;

/*
Since SHGetSettings is not implemented in all versions of the shell, get the 
function address manually at run time. This allows the extension to run on all 
platforms.
*/

ZeroMemory(&sfs, sizeof(sfs));

/*
The default, in case any of the following steps fails, is classic Windows 95 
style.
*/
sfs.fWin95Classic = TRUE;

hinstShell32 = LoadLibrary(TEXT("shell32.dll"));
if(hinstShell32)
   {
   PFNSHGETSETTINGSPROC pfnSHGetSettings;

   pfnSHGetSettings = (PFNSHGETSETTINGSPROC)GetProcAddress(hinstShell32, TEXT("SHGetSettings"));
   if(pfnSHGetSettings)
      {
      (*pfnSHGetSettings)(&sfs, SSF_DOUBLECLICKINWEBVIEW | SSF_WIN95CLASSIC);
      }
   FreeLibrary(hinstShell32);
   }

DWORD dwExStyles = 0;

if(!sfs.fWin95Classic && !sfs.fDoubleClickInWebView)
   dwExStyles |= LVS_EX_ONECLICKACTIVATE | 
                  LVS_EX_TRACKSELECT | 
                  LVS_EX_UNDERLINEHOT;

ListView_SetExtendedListViewStyle(m_hwndList, dwExStyles);

#endif   //(_WIN32_IE >= 0x0400)
}

/**************************************************************************

   CShellView::OnSettingChange()
   
**************************************************************************/

LRESULT CShellView::OnSettingChange(LPCTSTR lpszSection)
{
//if(0 == lstrcmpi(lpszSection, TEXT("ShellState")))
   {
   UpdateShellSettings();
   return 0;
   }

return 0;
}

