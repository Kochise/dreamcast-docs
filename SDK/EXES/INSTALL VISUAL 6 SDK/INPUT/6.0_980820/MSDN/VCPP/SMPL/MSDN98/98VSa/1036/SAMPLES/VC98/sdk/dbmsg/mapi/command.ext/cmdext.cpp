///////////////////////////////////////////////////////////////////////////////
//
//  File Name
//      CMDEXT.CPP 
//
//  Description
//      Implementation of interface objects
//
//      IExchExt interface methods:
//          MyExchExt::QueryInterface()
//          MyExchExt::AddRef()
//          MyExchExt::Release()
//
//          MyExchExt::Install()
//
//      IExchExtCommands interface methods:
//          MyExchExtCommands::QueryInterface()
//          MyExchExtCommands::AddRef()
//          MyExchExtCommands::Release()
//
//          MyExchExtCommands::InstallCommands()
//          MyExchExtCommands::DoCommand()
//          MyExchExtCommands::InitMenu()
//          MyExchExtCommands::Help()
//          MyExchExtCommands::QueryHelpText()
//          MyExchExtCommands::QueryButtonInfo()
//          MyExchExtCommands::ResetToolbar()
//
//          MyExchExtCommands::SetContext()
//          MyExchExtCommands::GetCmdID()
//
//      IExchExtUserEvents interface methods:
//          MyExchExtUserEvents::QueryInterface()
//          MyExchExtUserEvents::AddRef()
//          MyExchExtUserEvents::Release()
//
//          MyExchExtUserEvents::OnSelectionChange()
//          MyExchExtUserEvents::OnObjectChange()
//
//          MyExchExtUserEvents::SetContext()
//          MyExchExtUserEvents::SetIExchExt()
//
//  Author
//      Gary Peluso
//
//  Revision: 1.00
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1992-1995 Microsoft Corporation. All rights reserved.
//
#define INITGUID
#define USES_IID_IExchExt
#define USES_IID_IExchExtAdvancedCriteria
#define USES_IID_IExchExtAttachedFileEvents
#define USES_IID_IExchExtCommands
#define USES_IID_IExchExtMessageEvents
#define USES_IID_IExchExtPropertySheets
#define USES_IID_IExchExtSessionEvents
#define USES_IID_IExchExtUserEvents
#define USES_IID_IMAPIFolder

#include "CMDEXT.H"

///////////////////////////////////////////////////////////////////////////////
// data
static HINSTANCE ghInstDLL = NULL;  // instance handle of DLL

///////////////////////////////////////////////////////////////////////////////
//    FUNCTION: DLLMain()
//
//    Purpose
//    Do initilization processesing
//
//    Return Value
//    TRUE - DLL successfully loads and LoadLibrary will succeed.
//    FALSE - will cause an Exchange error message saying it cannot locate
//            the extension DLL.
//
//    Comments
//    We only need to get a copy of the DLL's HINSTANCE
//
BOOL WINAPI DllMain(
    HINSTANCE  hinstDLL,
    DWORD  fdwReason,   
    LPVOID  lpvReserved) 
{
 if (DLL_PROCESS_ATTACH == fdwReason)
 {
    ghInstDLL = hinstDLL;
 }
 return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//    FUNCTION: ExchEntryPoint
//
//    Parameters - none
//
//    Purpose
//    The entry point which Exchange calls.  
//
//    Return Value
//    Pointer to Exchange Extension Object
//
//    Comments
//    This is called for each context entry.  Create a new MyExchExt object
//    every time so each context will get its own MyExchExt interface.
//
LPEXCHEXT CALLBACK ExchEntryPoint(void)
{
    return new MyExchExt;
}


///////////////////////////////////////////////////////////////////////////////
//    MyExchExt::MyExchExt()
//
//    Parameters - none
//
//    Purpose
//    Constructor. Initialize members and create supporting interface objects
//
//    Comments
//    Each context of Exchange gets its own set of interface objects.
//    Furthermore, interface objects per context are kept track of by Exchange
//    and the interface methods are called in the proper context.
//    
MyExchExt::MyExchExt () 
{ 
  m_cRef = 1; 
  m_context = 0;
  
  m_pExchExtCommands = new MyExchExtCommands;
  m_pExchExtUserEvents = new MyExchExtUserEvents;

  // in MyExchExtUserEvents methods I need a reference to MyExchExt
  m_pExchExtUserEvents->SetIExchExt(this);

}


///////////////////////////////////////////////////////////////////////////////
//  IExchExt virtual member functions implementation
//

///////////////////////////////////////////////////////////////////////////////
//    MyExchExt::QueryInterface()
//
//    Parameters
//    riid   -- Interface ID.
//    ppvObj -- address of interface object pointer.
//
//    Purpose
//    Called by Exchage to request for interfaces
//
//    Return Value
//    S_OK  -- interface is supported and returned in ppvObj pointer
//    E_NOINTERFACE -- interface is not supported and ppvObj is NULL
//
//    Comments
//    Exchange client calls QueryInterface for each object.  Only
//    Need to support objects that apply to the extension.  QueryInterface
//    is called onces for each IID for each context.  We support two
//    contexts in this example so QueryInterface is called twice for
//    each IID.
//    
STDMETHODIMP MyExchExt::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
    HRESULT hr = S_OK;

    *ppvObj = NULL;

    if ( (IID_IUnknown == riid) || (IID_IExchExt == riid) )
    {
        *ppvObj = (LPUNKNOWN)this;
    }
    else if ( IID_IExchExtCommands == riid)
    {
        *ppvObj = (LPUNKNOWN)m_pExchExtCommands;
        m_pExchExtCommands->SetContext(m_context);
    }
    else if ( IID_IExchExtUserEvents == riid)
    {
        *ppvObj = (LPUNKNOWN)m_pExchExtUserEvents;
        m_pExchExtUserEvents->SetContext(m_context);
    }
    else
        hr = E_NOINTERFACE;

    if (NULL != *ppvObj)
        ((LPUNKNOWN)*ppvObj)->AddRef();

    return hr;
}



///////////////////////////////////////////////////////////////////////////////
//    MyExchExt::Install()
//
//    Parameters
//    peecb     -- pointer to Exchange Extension callback function
//    eecontext -- context code at time of being called.
//    ulFlags   -- flag to say if install is for modal or not
//
//    Purpose
//    Called once for each new contexted that is entered.  Proper version 
//    number is checked here.  
//
//    Return Value
//    S_OK -- object supported in the requested context
//    S_FALSE -- object is not supported in teh requested context
//
//    Comments
//
 STDMETHODIMP MyExchExt::Install (LPEXCHEXTCALLBACK pmecb, 
                         ULONG mecontext, ULONG ulFlags)
{
    ULONG ulBuildVersion;
    HRESULT hr;

    m_context = mecontext;

    // make sure this is the right version 
    pmecb->GetVersion(&ulBuildVersion, EECBGV_GETBUILDVERSION);
    if (EECBGV_BUILDVERSION_MAJOR != (ulBuildVersion & EECBGV_BUILDVERSION_MAJOR_MASK))
        return S_FALSE;

    switch (mecontext)
    {
        case EECONTEXT_VIEWER:
        case EECONTEXT_SEARCHVIEWER:
            hr = S_OK;
            break;
        default:
            hr = S_FALSE;
            break;
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
//  IExchExtCommands virtual member functions implementation
//

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::QueryInterface()
//
//    Parameters
//    riid   -- Interface ID.
//    ppvObj -- address of interface object pointer.
//
//    Purpose
//    Exchange Client does not call IExchExtCommands::QueryInterface().  
//    So return nothing.
//
//    Return Value - none
//

STDMETHODIMP MyExchExtCommands::QueryInterface(REFIID riid, LPVOID FAR * ppvObj)          
{
    *ppvObj = NULL;
    if ( (riid == IID_IExchExtCommands) || (riid == IID_IUnknown) )
    {
        *ppvObj = (LPVOID)this;
        // Increase usage count of this object
        AddRef();
        return S_OK;
    }
    return E_NOINTERFACE;
}

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::InstallCommands()
//
//    Parameters
//    pmecb  -- Exchange Callback Interface
//    hWnd   -- window handle to main window of context
//    hMenu  -- menu handle to main menu of context
//    lptbeArray -- array of toolbar button entries
//    ctbe   -- count of button entries in array
//    ulFlags -- reserved
//
//    Purpose
//    This function is called when commands are installed for each context
//    the extension services.
//
//    Return Value
//    S_FALSE means the commands have been handled.
//
//    Comments
//    The hWnd and hMenu are in context.  If the context is for the SENDNOTE 
//    dialog, then the hWnd is the window handle to the dialog and the hMenu is
//    the main menu of the dialog.
//    
//    Call ResetToolbar so that Exchange will show it's toolbar
//


STDMETHODIMP MyExchExtCommands::InstallCommands(LPEXCHEXTCALLBACK pmecb, 
                            HWND hWnd, HMENU hMenu,
                            UINT FAR * pcmdidBase, LPTBENTRY lptbeArray,
                            UINT ctbe, ULONG ulFlags)
{
 HRESULT hr = S_FALSE;
 HMENU hMenuTools;

 if ((EECONTEXT_SEARCHVIEWER == m_context) || (EECONTEXT_VIEWER == m_context))
 {


  // -------  install the new menu command, append to end of Tools menu. ----
  m_hWnd = hWnd;

  pmecb->GetMenuPos(EECMDID_ToolsCustomizeToolbar, &hMenuTools, NULL, NULL, 0);
 

  // add a menu separator
   AppendMenu(hMenuTools, MF_SEPARATOR, 0, NULL);

  // add our extension command
   AppendMenu(hMenuTools,
         MF_BYPOSITION | MF_STRING, 
         *pcmdidBase, 
         "Folder Stats");

     m_cmdid = *pcmdidBase;

     (*pcmdidBase)++;

 }

 if (EECONTEXT_VIEWER == m_context)
 {

  // --------------  install the new toolbar button --------------

  // walk through the toolbars and find the standard toolbar
  
  int tbindx;
  HWND hwndToolbar = NULL;
  for (tbindx = ctbe-1; (int) tbindx > -1; --tbindx)
  {
   if (EETBID_STANDARD == lptbeArray[tbindx].tbid)
   {
    hwndToolbar = lptbeArray[tbindx].hwnd;
    m_itbb = lptbeArray[tbindx].itbbBase++;
    break;
   }
  }

  // add out button's bitmap to the toolbar's set of buttons
  if (hwndToolbar)
  {
   TBADDBITMAP tbab;

   tbab.hInst = ghInstDLL;
   tbab.nID = IDB_EXTBTN;
   m_itbm = SendMessage(hwndToolbar, TB_ADDBITMAP, 1, (LPARAM)&tbab);
  }


 }

 return hr;

}


///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::DoCommand()
//
//    Parameters
//    pmecb -- pointer to Exchange Callback Interface
//
//    Purpose
//    This method is called by Exchange for each WM_COMMAND is sent to the
//    window in context. 
//
//    Return Value
//    S_OK if command is handled
//    S_FALSE if command is not handled
//
//    Comments
//    Use this function to either respond to the command item (menu or toolbar)
//    added or modify an existing command in Exchange.  Return S_OK to let
//    Exchange know the command was handled.  Return S_OK on commands you are
//    taking over from Exchange.  Return S_FALSE to let Exchange know you want
//    it to carry out its command, even if you modify its action.
//
                                                                                                          
STDMETHODIMP MyExchExtCommands::DoCommand(LPEXCHEXTCALLBACK pmecb, UINT cmdid)
{
 static char szBuffer[200];
 ULONG uNumSelected = 0;
 ULONG ulSubFolders = 0;
 ULONG ulReadMsgs = 0;
 ULONG ulUnReadMsgs = 0;
 LPMDB lpMDB = NULL;
 LPMAPIFOLDER lpFolder = NULL;
 LPMAPISESSION lpSession = NULL;
 LPADRBOOK lpAddrBook = NULL;
 ULONG cbeid;
 LPENTRYID lpeid = NULL;
 ULONG ulType;
 char szMsgClass[50];
 ULONG cbMsgClass;
// ULONG ulMsgFlags; 
 
 HRESULT hr = S_FALSE;   // assume it is not our command

 if (m_cmdid != cmdid)
    return hr;           // not our command

 if (m_context == EECONTEXT_VIEWER)
 {

    cbMsgClass = 49;
    szMsgClass[0] = '\0';


    hr = pmecb->GetSession(&lpSession, &lpAddrBook);
    if (FAILED(hr))
    {
        hr = S_OK;     // we still handled the command
        goto error_return;
    }

    hr = pmecb->GetSelectionItem(0, &cbeid, &lpeid, &ulType, NULL, 
        0, NULL, 0);
    if (FAILED(hr))
    {
        hr = S_OK;     // we still handled the command
        goto error_return;
    }

    if (ulType != MAPI_FOLDER)          // should never get this
    {
        hr = S_OK;     // we still handled the command
        goto error_return;
    }


    hr = lpSession->OpenEntry(cbeid, lpeid, NULL, 0, &ulType, 
                         (LPUNKNOWN FAR *)&lpFolder);
    if (FAILED(hr))
    {
        hr = S_OK;     // we still handled the command
        goto error_return;
    }
    

    if (NULL == lpFolder) 
    {
        hr = S_OK;     // we still handled the command
        goto error_return;              // no folder, not going to continue
    }

    GetFolderStats(lpFolder, &ulSubFolders, &ulReadMsgs, &ulUnReadMsgs);
    wsprintf(szBuffer, "Number of subfolders: %ld\n"
                       "Number of read messages: %ld\n"
                       "Number of unread messages: %ld", 
                       ulSubFolders, ulReadMsgs, ulUnReadMsgs);

    MessageBox(m_hWnd, szBuffer, "Sample Extension - Folder Stats", MB_OK);

    hr = S_OK;
    
 }

 // must use a different technique in Find window
 if (m_context == EECONTEXT_SEARCHVIEWER)  
 {


    pmecb->GetObject(&lpMDB, (LPMAPIPROP FAR *)&lpFolder);

    if (lpFolder == NULL)
    {
        hr = S_OK;     // we still handled the command
        goto error_return;              // no folder, not going to continue
    }

    GetFolderStats(lpFolder, &ulSubFolders, &ulReadMsgs, &ulUnReadMsgs);
    wsprintf(szBuffer, "Number of subfolders: %d\n"
                       "Number of read messages: %d\n"
                       "Number of unread messages: %d", 
                       ulSubFolders, ulReadMsgs, ulUnReadMsgs);


    MessageBox(m_hWnd, szBuffer, "Sample Extension - Folder Stats", MB_OK);

    hr = S_OK;

 }

error_return:

    MAPIFreeBuffer(lpeid);
    
    if (NULL != lpSession)
        lpSession->Release();

    if (NULL != lpAddrBook)
        lpAddrBook->Release();

    if (NULL != lpMDB)
        lpMDB->Release();                        

    if (NULL != lpFolder)
        lpFolder->Release();

 return hr; 
}


///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::InitMenu()
//
//    Parameters
//    pmecb -- pointer to Exchange Callback Interface
//
//    Purpose
//    This method is called by Exchange when the menu of context is about to
//    be activated.  See WM_INITMENU in the Windows API Reference for more
//    information.
//
//    Return Value - none
//

STDMETHODIMP_(VOID) MyExchExtCommands::InitMenu(LPEXCHEXTCALLBACK pmecb)
{
 // do nothing

}

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::Help()
//
//    Parameters
//    pmecb -- pointer to Exchange Callback Interface
//    cmdid -- command id
//
//    Purpose
//    Respond when user presses F1 while custom menu item is selected.
//
//    Return Value
//    S_OK -- recognized the command and provided help
//    S_FALSE -- not our command and we didn't provide help
//

STDMETHODIMP MyExchExtCommands::Help(LPEXCHEXTCALLBACK pmecb, UINT cmdid)
{
 HRESULT hr;


 if (cmdid == m_cmdid)
 {

   MessageBox(m_hWnd, "Called through IExchExtCommands::Help()\n"
                      "Contained in cmdext32.dll\n\n"
                      "Copyright (c) 1995 Microsoft Corporation.\n"
                      "All rights reserved.",
                      "About Folder Stats Sample Extension", MB_OK);

   hr = S_OK;
 } 
 else
   hr = S_FALSE;

 return hr;
}


///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::QueryHelpText()
//
//    Parameters
//    cmdid -- command id corresponding to menu item activated
//    ulFlags -- identifies either EECQHT_STATUS or EECQHT_TOOLTIP
//    psz -- pointer to buffer to be populated with text to display
//    cch -- count of characters available in psz buffer
//
//    Purpose
//    Exchange calls this function each time it requires to update the status
//    bar text or if it is to display a tooltip on the toolbar.
//
//    Return Value
//    S_OK to indicate our command was handled
//    S_FALSE to tell Exchange it can continue with its function
//

STDMETHODIMP MyExchExtCommands::QueryHelpText(UINT cmdid, ULONG ulFlags, 
                                              LPTSTR psz, UINT cch)
{

 HRESULT hr;

 if (cmdid == m_cmdid)
 {
  if (ulFlags == EECQHT_STATUS)
    lstrcpyn(psz, "Display Stats on Current Folder", cch);
  
  if (ulFlags == EECQHT_TOOLTIP)
    lstrcpyn(psz, "Folder Stats", cch);

  hr = S_OK;

 }
 else
  hr = S_FALSE;

 return hr;
}

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::QueryButtonInfo()
//
//    Parameters
//    tbid    -- toolbar identifier
//    itbb    -- toolbar button index
//    ptbb    -- pointer to toolbar button structure -- see TBBUTTON structure
//    lpsz    -- point to string describing button
//    cch     -- maximum size of lpsz buffer
//    ulFlags -- EXCHEXT_UNICODE may be specified
//
//    Purpose
//    For Exchange to find out about toolbar button information.
//
//    Return Value
//    S_FALSE - not our button
//    S_OK    - we filled information about our button
//
//    Comments
//    Called for every button installed for toolbars when IExchExtCommands
//    is installed for each context. The lpsz text is used when the Customize
//    Toolbar dialog is displayed.  The text will be displayed next to the
//    button.
//

STDMETHODIMP MyExchExtCommands::QueryButtonInfo (ULONG tbid, UINT itbb, 
                            LPTBBUTTON ptbb, LPTSTR lpsz, UINT cch, 
                            ULONG ulFlags)
{
 HRESULT hr = S_FALSE;

  if (m_itbb == itbb)
  {
   ptbb->iBitmap = m_itbm;             // see InstallCommands in this source file
   ptbb->idCommand = m_cmdid;
   ptbb->fsState = TBSTATE_ENABLED;
   ptbb->fsStyle = TBSTYLE_BUTTON;
   ptbb->dwData = 0;
   ptbb->iString = -1;
   lstrcpyn(lpsz, "Folder Stats Toolbar Button", cch);

   hr = S_OK;
  }
 return hr;
}


///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::ResetToolbar()
//
//    Parameters
//    tbid
//    ulFlags
//
//    Purpose
//
//    Return Value  S_OK always
//
STDMETHODIMP MyExchExtCommands::ResetToolbar(ULONG tbid, ULONG ulFlags)
{
 return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//  IExchExtUserEvents virtual member functions implementation
//

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtUserEvents::QueryInterface()
//
//    Parameters
//    riid   -- Interface ID.
//    ppvObj -- address of interface object pointer.
//
//    Purpose
//    Exchange Client does not call IExchExtUserEvents::QueryInterface().  
//    So return nothing.
//
//    Return Value - none
//

STDMETHODIMP MyExchExtUserEvents::QueryInterface(REFIID riid, LPVOID FAR * ppvObj)          
{
    *ppvObj = NULL;
    if (( riid == IID_IExchExtUserEvents) || (riid == IID_IUnknown) )
    {
        *ppvObj = (LPVOID)this;
        // Increase usage count of this object
        AddRef();
        return S_OK;
    }
    return E_NOINTERFACE;
}

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtUserEvents::OnSelectionChange()
//
//    Parameters
//    pmecb  -- pointer to Exchange Callback Object
//    
//
//    Purpose
//    This function is called when the selection in the UI is changed.
//
//    Return Value - none
//
//    Comments
//    OnSelectionChange is called whenever the selection changes either within
//    a pane or is changed between panes.
//

STDMETHODIMP_(VOID) MyExchExtUserEvents::OnSelectionChange(LPEXCHEXTCALLBACK pmecb)
{
 static ULONG cbeid;
 static LPENTRYID lpeid = NULL;
 static ULONG ulType;
 static char szMsgClass[50];
 ULONG cbMsgClass;
 ULONG ulMsgFlags;
 HMENU hMenu;
 HRESULT hr;
 UINT cmdid;
 MyExchExtCommands * pExchExtCommands = NULL;

 // do not care about enabling or disabling menu item if in the search viewer
 if (m_context == EECONTEXT_SEARCHVIEWER)
    return;

 cbMsgClass = 49;
 szMsgClass[0] = '\0';


 hr = pmecb->GetSelectionItem(0, &cbeid, &lpeid, &ulType, szMsgClass, 
        cbMsgClass, &ulMsgFlags, 0);
 
 if (FAILED(hr))
 {
  goto error_return;
 }


 pmecb->GetMenu(&hMenu);

 hr = m_pExchExt->QueryInterface(IID_IExchExtCommands, (LPVOID *)&pExchExtCommands);
 if (FAILED(hr))
 {
    goto error_return;
 }

 cmdid = pExchExtCommands->GetCmdID();
 pExchExtCommands->Release();
 pExchExtCommands = NULL;


 // enable or disable the command depending if the selected object is
 // a folder or a "non-folder"  Enable if object is a folder.
 if (ulType == MAPI_FOLDER)
 {
    EnableMenuItem(hMenu, cmdid, MF_BYCOMMAND | MF_ENABLED);
 }
 else
 {
    EnableMenuItem(hMenu, cmdid, MF_BYCOMMAND | MF_GRAYED);
 }


error_return:

 if (lpeid != NULL)
    MAPIFreeBuffer(lpeid);

}


///////////////////////////////////////////////////////////////////////////////
//    MyExchExtUserEvents::OnObjectChange()
//
//    Parameters
//    pmecb  -- pointer to Exchange Callback Object
//    
//
//    Purpose
//    This function is called when the selection in the UI is to a different
//    of object on the left pane.
//
//    Return Value - none
//
//    Comments
//    OnObjectChange is called whenever the selection is changed between 
//    objects in the left pane only.  Change in selection between folders, 
//    subfolders or container object in the left pane will be reflected with a
//    call to OnObjectChange.  Change in selection between objects (messages, 
//    subfolders) in the right pane will not call OnObjectChange, only 
//    OnSelectionChange.
//

STDMETHODIMP_(VOID) MyExchExtUserEvents::OnObjectChange(LPEXCHEXTCALLBACK pmecb)
{
 // no need to handle this one
}



///////////////////////////////////////////////////////////////////////////////
//  Helper functions to accomplish this extension's task
//


///////////////////////////////////////////////////////////////////////////////
//    GetFolderStats()
//
//    Parameters
//    lpFolder      -- pointer to Folder of which to get statistics
//    pulFolder     -- pointer to buffer to be filled with number of subfolders
//    pulReadMsgs   -- pointer to buffer to be filled with number of read 
//                     messages
//    pulUnReadMsgs -- pointer to buffer to be filled with number of unread
//                     messages
//
//    Purpose
//    This function gathers information information about the given message
//    folder.  It calculates the number of subfolders, read messages, and
//    unread messages.
//
//    Return Value - none
//
//    Comments
//    The Find window results folder only contains messages and not subfolders
//    so it sets the number of subfolders to zero
//

void GetFolderStats(LPMAPIFOLDER lpFolder, ULONG FAR * pulSubFolders, 
                    ULONG FAR * pulReadMsgs, ULONG FAR * pulUnReadMsgs)
{
 HRESULT hr = 0;
 LPMAPITABLE lpTable = NULL;
 ULONG ulRows = 0;
 UINT u;
 LPSRowSet lpRows = NULL;

 enum { MESSAGE_FLAGS, STATTAGS };

 SizedSPropTagArray(STATTAGS,  MsgTags) =
      { STATTAGS, 
        { 
         PR_MESSAGE_FLAGS        // contains read/unread flags
        } 
      };


 hr = lpFolder->GetHierarchyTable(0, &lpTable);   // get table of subfolders
 if (MAPI_E_NO_SUPPORT == hr)                     // Find window folder doesn't 
    *pulSubFolders = 0;                           // support GetHierarchyTable
    
 else if (S_OK != hr)              // some other error
    goto error_return;

 if (lpTable != NULL)
 {
    lpTable->GetRowCount(0, pulSubFolders);
    lpTable->Release();
    lpTable =NULL;
 }

 hr = lpFolder->GetContentsTable(0, &lpTable);    // get table of messages
 if (S_OK != hr)
    goto error_return;

 hr = lpTable->SetColumns((LPSPropTagArray)&MsgTags, 0);
 if (S_OK != hr)
    goto error_return;

 lpTable->GetRowCount(0, &ulRows);
 hr = lpTable->QueryRows(ulRows, 0, &lpRows);
 if (S_OK != hr)
    goto error_return;

 *pulReadMsgs = 0;
 *pulUnReadMsgs = 0;

 for (u=0; u<ulRows; u++)
 {

  if (MSGFLAG_READ & lpRows->aRow[u].lpProps[MESSAGE_FLAGS].Value.ul)
    (*pulReadMsgs)++;
  else
    (*pulUnReadMsgs)++;

 }


error_return:

 if (NULL != lpTable)
    lpTable->Release();

 if (NULL != lpRows)
    FreeProws(lpRows);

}
