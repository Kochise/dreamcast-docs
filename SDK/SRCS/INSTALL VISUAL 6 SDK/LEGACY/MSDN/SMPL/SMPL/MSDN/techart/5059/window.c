#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <pdh.h>

#include "RESOURCE.h"
#include "PDHTEST.h"

// Globals
HINSTANCE ghInst;
HWND ghWndMain;
HWND ghWndListView;
HWND ghWndStatus;
BOOL gfStatsOn = FALSE;

POINT ptLastRClick;

LPTSTR glpszClassName = TEXT("PDH Main Window");
LPTSTR glpszWindowName = TEXT("PDH Test Application");

/*

  ReportError:

  Function handle error message display.

*/
void ReportError(LPTSTR szErrMsg)
{
    MessageBox(NULL, szErrMsg, NULL, MB_OK);
}

/*

  InitApplication:

  Function initialize the application.  Registers window class and 
  creates main window.

*/
BOOL InitApplication(HINSTANCE hInst)
{
    ATOM aRes;
    WNDCLASS wndClass;

    // Window stuff
    ZeroMemory(&wndClass, sizeof(wndClass));
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = MainWindowProc;
    wndClass.hInstance = hInst;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MAINMENU);
    wndClass.lpszClassName = glpszClassName;

    aRes = RegisterClass(&wndClass);
    if (aRes == 0) {
        ReportError(TEXT("Failed to register window class."));
        return FALSE;
    }

    ghWndMain = CreateWindow(glpszClassName, 
                             glpszWindowName,
                             WS_OVERLAPPEDWINDOW, 
                             CW_USEDEFAULT, CW_USEDEFAULT,   // x, y
                             CW_USEDEFAULT, CW_USEDEFAULT,   // height, width
                             NULL, // parent window
                             NULL, // menu
                             hInst,
                             NULL);

    if (ghWndMain == NULL) {
        ReportError(TEXT("Could not create window."));
        return FALSE;
    }

    ShowWindow(ghWndMain, SW_SHOW);

    return TRUE;
}

/*

  DoMessageLoop:

  Standard windows message loop.

*/
void DoMessageLoop()
{
    MSG msg; 
    BOOL fRes;
 
    while (TRUE) {
        fRes = GetMessage(&msg, (HWND) ghWndMain, 0, 0);
        if (fRes != TRUE)
            break;

        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
    } 
 
}

/*

  WinMain:

  Application entry-point.  Intializes and calls message loop function.

*/
int WINAPI WinMain( HINSTANCE hInst, 
                    HINSTANCE hPrev, 
                    LPSTR lpszCmdLine, 
                    int nCmdShow )
{
    ghInst = hInst;

    if (!InitApplication(hInst))
        return -1;
    
    DoMessageLoop();

    return 0;
}

/*

  OnCommand:

  Handles WM_COMMAND messages to the main window.

*/
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch(id) {

        // FILE Functions
    case ID_FILE_IMPORT:        FileImport(hwnd);                   break;
    case ID_FILE_EXPORT:        FileExport(hwnd);                   break;
    case ID_FILE_EXIT:          PostMessage(hwnd, WM_CLOSE, 0, 0);  break;
    
        // PDH Functions
    case ID_PDH_BROWSECOUNTERS:     PDH_BrowseCounters(hwnd);   break;
    case ID_PDH_REMOVECOUNTER:      RemoveCounter(hwnd);        break;
    case ID_PDH_REMOVEALLCOUNTERS:  RemoveAllCounters(hwnd);    break;
    case ID_PDH_GETCOUNTERINFO:     GetCounterInfo(hwnd);       break;
    case ID_PDH_SETCOUNTERSCALE:    SetCounterScale(hwnd);      break;
    case ID_PDH_COLLECTQUERYDATA:   UpdateListView();           break;

        // PDH Flags
    case ID_FLAGS_INCLUDEINSTANCEINDEX:
    case ID_FLAGS_SINGLECOUNTERPERADD:
    case ID_FLAGS_SINGLECOUNTERPERDIALOG:
    case ID_FLAGS_LOCALCOUNTERSONLY:
    case ID_FLAGS_WILDCARDINSTANCES:
    case ID_FLAGS_HIDEDETAILBOX:
    case ID_FLAGS_INITIALIZEPATH:
        PDH_ToggleFlag(id);
        PDH_CheckMenuItem(GetMenu(hwnd), id);
        break;

        // AUTO options
    case ID_AUTO_START:         AutoStart();                            break;
    case ID_AUTO_STOP:          AutoStop();                             break;
    case ID_AUTO_STATISTICS:    AutoToggleStatistics(GetMenu(hwnd));    break;

    case ID_HELP_INFO:          HelpInfo(hwnd);                         break;
    }
}

/*

  OnClose:

  Handles WM_CLOSE message.

*/
void OnClose(HWND hwnd)
{
    PDH_Uninitialize();
    DestroyWindow(hwnd);
}

/*

  OnCreate:

  Handles WM_CREATE message.

  Used to call PDH_Initialize to get the PDH library started.
  Checks appropriate menu items to reflect current flag state.
  Creates child window (status window and list view control).

*/
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
    if (!PDH_Initialize())
        return FALSE;

    PDH_CheckMenuItem(GetMenu(hwnd), ID_FLAGS_INCLUDEINSTANCEINDEX);
    PDH_CheckMenuItem(GetMenu(hwnd), ID_FLAGS_SINGLECOUNTERPERADD);
    PDH_CheckMenuItem(GetMenu(hwnd), ID_FLAGS_SINGLECOUNTERPERDIALOG);
    PDH_CheckMenuItem(GetMenu(hwnd), ID_FLAGS_LOCALCOUNTERSONLY);
    PDH_CheckMenuItem(GetMenu(hwnd), ID_FLAGS_WILDCARDINSTANCES);
    PDH_CheckMenuItem(GetMenu(hwnd), ID_FLAGS_HIDEDETAILBOX);
    PDH_CheckMenuItem(GetMenu(hwnd), ID_FLAGS_INITIALIZEPATH);

    ghWndStatus = InitStatusWindow(hwnd);

    ghWndListView = CreateListView(hwnd);

    UpdateStatus(TEXT("Initialization complete."));

    return TRUE;
}

/*

  OnTimer:

  Handles WM_TIMER messages.

  Used for updating current values.
  If statistics are selected, then also used to update the latest raw values
  and display statical values (min, max, avg).

*/
void OnTimer(HWND hwnd, UINT id)
{
    // Display value results
    if (!UpdateListView()) {
        // Failure in updating the list view
        AutoStop();
    }
    else {
        // Updating the list view worked for the actual value
        // Now update the list view for stats (if enabled)
        if (gfStatsOn) {
            // Update raw values
            if (!UpdateRawValues()) {
                AutoToggleStatistics(GetMenu(hwnd));
                return ;
            }

            // Display statistics
            if (!DisplayStatistics()) {
                AutoToggleStatistics(GetMenu(hwnd));
                return ;
            }
        }
    }
}

/*

  OnSize:

  Handles WM_SIZE.

  Changes size of child windows with the size change in the main window.

*/
void OnSize(HWND hwnd, UINT state, int cx, int cy)
{
    RECT rect;

    GetWindowRect(ghWndStatus, &rect);
    MoveWindow(ghWndListView, 0,0, cx, cy-(rect.bottom - rect.top), FALSE);
    MoveWindow(ghWndStatus, 0, cy-(rect.bottom-rect.top), cx, cy-(rect.bottom-rect.top), FALSE);
}

/*

  OnRClick:

  Handles right click notification for a child control.

  Determines which, if any, item was right-clicked.  Location of the mouse-click
  is maintainted in the OnParentNotify function.
  Appropriate menu is loaded from the resource.
  Menu is displayed.
  Selected option is posted as if the menu item were 
  selected from the main menu.

*/
BOOL OnRClick(HWND hWndCtrl)
{  
    LV_HITTESTINFO lvHitTestInfo;
    int nItemIndex;
    int nMenuSelection;
    int nMenuPos;
    HMENU hMenu, hMenuPopup;

    ZeroMemory(&lvHitTestInfo, sizeof(LV_HITTESTINFO));
    lvHitTestInfo.pt.x = ptLastRClick.x;
    lvHitTestInfo.pt.y = ptLastRClick.y;

    if (hWndCtrl == ghWndListView) {
        nItemIndex = ListView_HitTest(ghWndListView, &lvHitTestInfo);
        if (nItemIndex == -1)
            nMenuPos = 1;
        else
            nMenuPos = 0;

        hMenuPopup = LoadMenu(ghInst, MAKEINTRESOURCE(IDR_POPUPMENU));
        hMenu = GetSubMenu(hMenuPopup, nMenuPos);
        nMenuSelection = (int) ItemDisplayPopup(hMenu);
        DestroyMenu(hMenuPopup);

        if (nMenuSelection != 0) {
            PostMessage(ghWndMain, WM_COMMAND, MAKEWPARAM(nMenuSelection, 0), (LPARAM)hWndCtrl);
        }
    }

    return TRUE;
}

/*

  OnNotify:

  Handles WM_NOTIFY for a child control

*/
BOOL OnNotify(HWND hwnd, int idCtrl, LPNMHDR pnmh)
{
    if (pnmh->code == NM_RCLICK) {
        return OnRClick(pnmh->hwndFrom);
    }

    return TRUE;
}

/*

  OnParentNotify:

  Handles WM_PARENTNOTIFY.

  Only interested in WM_RBUTTONDOWN messages.  Keeps track of where the last
  right-click takes place.  This location is used in the OnRClick function to 
  determine which item is right-clicked.

*/
void OnParentNotify(HWND hwnd, UINT msg, HWND hwndChild, int idChild)
{
    switch(msg) {

    case WM_RBUTTONDOWN:
        // hwndChild is actually the coords:
        ptLastRClick.x = LOWORD((LPARAM) hwndChild);
        ptLastRClick.y = HIWORD((LPARAM) hwndChild);
        break;

    default:
        return;
    }
}

/*

  MainWindowProc:

  Main window procedure.

*/
LRESULT CALLBACK MainWindowProc( HWND hwnd,     // handle of window 
                                 UINT uMsg,     // message identifier 
                                 WPARAM wParam, // first message parameter 
                                 LPARAM lParam) // second message parameter
{
    switch(uMsg) {

    HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
    HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
    HANDLE_MSG(hwnd, WM_TIMER, OnTimer);
    HANDLE_MSG(hwnd, WM_CLOSE, OnClose);
    HANDLE_MSG(hwnd, WM_SIZE, OnSize);
    HANDLE_MSG(hwnd, WM_PARENTNOTIFY, OnParentNotify);
    case WM_NOTIFY:
        OnNotify(hwnd, (int) wParam, (LPNMHDR) lParam);
        // fall through:

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);

    }

    return 0;
}

/*

  InitStatusWindow:

  Function to create the status window.  Used to report status messages.

*/
HWND InitStatusWindow(HWND hWnd)
{
    InitCommonControls();
    // Create child windows for results.
    return CreateStatusWindow(  WS_VISIBLE | WS_CHILD, 
                                (LPCTSTR)NULL, 
                                hWnd, 
                                1 );
}

/*

  UpdateStatus:

  Display a status message.

*/
BOOL UpdateStatus(LPTSTR lpszMessage)
{
    SetWindowText(ghWndStatus, lpszMessage);
    UpdateWindow(ghWndStatus);

    return TRUE;
}

/*

  InitListViewColumns:
 
  Adds columns to a list view control.  

*/
BOOL InitListViewColumns(HWND hwndLV) 
{ 
    TCHAR achTemp[256];     // temporary buffer 
    LV_COLUMN lvc; 
    int iCol; 
 
    // Initialize the LV_COLUMN structure. 
    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM; 
    lvc.fmt = LVCFMT_LEFT; 
    lvc.pszText = achTemp; 
 
    // Add the columns. 
    for (iCol = COL_COUNTERNAME; iCol <= COL_FINALCOLUMN; iCol++) { 
        lvc.iSubItem = iCol; 
        lvc.cx = (iCol == COL_COUNTERNAME) ? 200 : 75; 
        LoadString(ghInst, IDS_COLUMN1 + iCol, 
                achTemp, sizeof(achTemp)); 
        if (ListView_InsertColumn(hwndLV, iCol, &lvc) == -1) 
            return FALSE; 
    } 

    return TRUE; 
} 

/*

  CreateListView:
  
  creates a list view control.  

*/
HWND CreateListView(HWND hwndParent) 
{ 
    HWND hwndLV; 
    RECT rect;
    RECT statRect;
 
    // Force the common controls DLL to be loaded. 
    InitCommonControls(); 

    GetClientRect(hwndParent, &rect);
    GetWindowRect(ghWndStatus, &statRect);
 
    // Create the list view window. 
    hwndLV = CreateWindow(WC_LISTVIEW, TEXT(""), 
        WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL, 
        0, 0, rect.right - rect.left, rect.bottom - rect.top - (statRect.bottom-statRect.top), 
        hwndParent, NULL, ghInst, NULL); 
    if (hwndLV == NULL) 
        return NULL; 
 
    // Call function to add columns
    if (!InitListViewColumns(hwndLV)) { 
        DestroyWindow(hwndLV); 
        return NULL; 
    } 

    return hwndLV;              // return the control's handle 
} 

/*

  AddListViewItem:
  
  Adds item to a list view.
  pParam - Counter query structure for the counter item.

*/
int AddListViewItem(LPTSTR szCounterName, PPDHCOUNTERSTRUCT pParam) 
{ 
    int nReturnValue;
    LV_ITEM lvi; 

    ZeroMemory(&lvi, sizeof(lvi));
 
    // Initialize LV_ITEM members that are common to all items. 
    lvi.mask = LVIF_TEXT | LVIF_STATE | LVIF_PARAM;
    // item number
    lvi.iItem = ListView_GetItemCount(ghWndListView); 
    // text
    lvi.pszText = szCounterName;
    lvi.cchTextMax = lstrlen(szCounterName);
    // selection state
    lvi.stateMask = LVIS_SELECTED;
    lvi.state = 0;
    // parameter
    lvi.lParam = (LPARAM) pParam;

    // Add the item. 
    nReturnValue = ListView_InsertItem(ghWndListView, &lvi);
    if (nReturnValue == -1) {
        ReportError(TEXT("Failed to insert item."));
        return -1;
    }

    return nReturnValue; 
} 

/*

  FindSelectedListViewItem:

  Returns the index (zero-based) of the selected list view item.

*/
int FindSelectedListViewItem(HWND hwndLV)
{
    return (ListView_GetNextItem(hwndLV, -1, LVNI_SELECTED));
}

/*

  GetCounterStruct:

  Returns a pointer to the counter struct associated with the selected
  list view item.

*/
PPDHCOUNTERSTRUCT GetCounterStruct()
{
    int nItemIndex;
    LV_ITEM lvi;
    
    // Find the LV item that with state == LVIS_SELECTED;
    nItemIndex = FindSelectedListViewItem(ghWndListView);

    if (nItemIndex == -1) {
        ReportError(TEXT("Cannot find selected list view item."));
        return NULL;
    }

    ZeroMemory(&lvi, sizeof(lvi));
    lvi.iItem = nItemIndex;
    lvi.mask = LVIF_PARAM;

    if (!ListView_GetItem(ghWndListView, &lvi)) {
        ReportError(TEXT("Cannot get selected item's text."));
        return NULL;
    }

    return (PPDHCOUNTERSTRUCT) lvi.lParam;
}

/*

  RemoveCounter:

  Removes the selected counter from the list view control.

  Also calls PDH_RemoveCounter to remove the counter from the PDH query.

*/
BOOL RemoveCounter(HWND hwnd)
{
    int nItemIndex;
    LV_ITEM lvi;
    TCHAR szItemText[256];
    
    nItemIndex = FindSelectedListViewItem(ghWndListView);

    if (nItemIndex == -1) {
        ReportError(TEXT("Cannot find selected list view item."));
        return FALSE;
    }

    ZeroMemory(&lvi, sizeof(lvi));
    lvi.iItem = nItemIndex;
    lvi.iSubItem = 0;
    lvi.mask = LVIF_TEXT | LVIF_PARAM;
    lvi.pszText = szItemText;
    lvi.cchTextMax = 256;

    if (!ListView_GetItem(ghWndListView, &lvi)) {
        ReportError(TEXT("Cannot get selected item's text."));
        return FALSE;
    }

    PDH_RemoveCounter(szItemText, (PPDHCOUNTERSTRUCT) lvi.lParam);

    RemoveItem(nItemIndex);

    return TRUE;
}

/*

  RemoveAllCounters:

  Removes all counters from the list view control.

  Also calls PDH_RemoveCounter for each counter to remove the counter
  from the PDH query.

*/
BOOL RemoveAllCounters(HWND hwnd)
{
    int nIndex, nNumItems;
    LV_ITEM lvi;
    TCHAR szItemText[256];

    if (IDNO == MessageBox(hwnd, TEXT("Are you sure you want to clear all counters?"), TEXT("Remove All Counters"), MB_YESNO | MB_ICONQUESTION))
        return FALSE;

    nNumItems = ListView_GetItemCount(ghWndListView);

    ZeroMemory(&lvi, sizeof(lvi));
    lvi.mask = LVIF_TEXT | LVIF_PARAM;
    lvi.pszText = szItemText;
    lvi.cchTextMax = 256;

    for (nIndex = nNumItems - 1; nIndex >= 0; nIndex--) {
        lvi.iItem = nIndex;

        if (!ListView_GetItem(ghWndListView, &lvi)) {
            ReportError(TEXT("Cannot get item's text."));
            return FALSE;
        }

        PDH_RemoveCounter(szItemText, (PPDHCOUNTERSTRUCT) lvi.lParam);
        RemoveItem(nIndex);
    }

    return TRUE;
}

/*

  RemoveItem:

  Removes an item (using the index passed in) from the list view control.

*/
BOOL RemoveItem(int nItemIndex) 
{
    if (!ListView_DeleteItem(ghWndListView, nItemIndex)) {
        ReportError(TEXT("Cannot delete item from list view."));
        return FALSE;
    }

    return TRUE;
}
 
/*

  UpdateListView:

  Updates the current counter values.

  First, calls PDH_CollectQueryData to collect the most recent data.
  Then calls PDH_UpdateValue for each item in the list view to
  update the value.

*/
BOOL UpdateListView()
{
    int nIndex, nNumItems;
    LV_ITEM lvi;

    nNumItems = ListView_GetItemCount(ghWndListView);

    if (nNumItems == 0) {
        // Bail out since there is not data to collect
        UpdateStatus("No data to collect.");
        return FALSE;
    }

    if (!PDH_CollectQueryData()) {
        // Bail out since data collection failed
        return FALSE;
    }

    ZeroMemory(&lvi, sizeof(lvi));
    lvi.mask = LVIF_PARAM;

    for (nIndex = 0; nIndex < nNumItems; nIndex++)
    {
        lvi.iItem = nIndex;
        if (!ListView_GetItem(ghWndListView, &lvi))
            return FALSE;

        PDH_UpdateValue((PPDHCOUNTERSTRUCT) lvi.lParam, nIndex);
    }

    return TRUE;
}

/*

  UpdateRawValues:

  Function to update the raw values for each counter in the list view.

*/
BOOL UpdateRawValues()
{
    int nIndex, nNumItems;
    LV_ITEM lvi;

    nNumItems = ListView_GetItemCount(ghWndListView);

    ZeroMemory(&lvi, sizeof(lvi));
    lvi.mask = LVIF_PARAM;

    for (nIndex = 0; nIndex < nNumItems; nIndex++)
    {
        lvi.iItem = nIndex;
        if (!ListView_GetItem(ghWndListView, &lvi))
            return FALSE;

        PDH_UpdateRawValue((PPDHCOUNTERSTRUCT) lvi.lParam, nIndex);
    }

    return TRUE;
}

/*

  DisplayStatistics:

  Function to calculate and display the statistical results (min, max, avg) 
  of each counter in the list view.

*/
BOOL DisplayStatistics()
{
    int nIndex, nNumItems;
    LV_ITEM lvi;

    nNumItems = ListView_GetItemCount(ghWndListView);

    ZeroMemory(&lvi, sizeof(lvi));
    lvi.mask = LVIF_PARAM;

    for (nIndex = 0; nIndex < nNumItems; nIndex++)
    {
        lvi.iItem = nIndex;
        if (!ListView_GetItem(ghWndListView, &lvi))
            return FALSE;

        PDH_DisplayStatistics((PPDHCOUNTERSTRUCT) lvi.lParam, nIndex);
    }

    return TRUE;
}

/*

  SetSubItemText:

  Function to set the appropriate items/column text

  nItemIndex is the zero-based index of the item (line).
  nSubItem is the zero-based index of the column.
  szMsg is the text for the cell.

*/
BOOL SetSubItemText(int nItemIndex, int nSubItem, LPTSTR szMsg)
{
    ListView_SetItemText(ghWndListView, nItemIndex, nSubItem, szMsg);

    return TRUE;
}

/*

  GetCounterInfo:

  Function to call PDH_GetCounterInfo for the selected list view item.

*/
BOOL GetCounterInfo(HWND hWnd)
{
    PPDHCOUNTERSTRUCT pCounterStruct;
    
    pCounterStruct = GetCounterStruct();
    if (pCounterStruct == NULL)
        return FALSE;

    PDH_GetCounterInfo(ghInst, hWnd, pCounterStruct);

    return TRUE;
}

/*

  SetCounterScale:

  Set the counter scale for the selected listview item.

*/
BOOL SetCounterScale(HWND hWnd)
{
    PPDHCOUNTERSTRUCT pCounterStruct;

    pCounterStruct = GetCounterStruct();
    if (pCounterStruct == NULL)
        return FALSE;

    PDH_SetCounterScale(ghInst, hWnd, pCounterStruct);

    return TRUE;
}

/*

  AutoStart:

  Starts the automatic collection and display of counter data

*/
BOOL AutoStart()
{
    // An interval could be selected here.
    // We're just using a hard coded 1000 millisecond timer

    SetTimer(ghWndMain, 1, 1000, NULL);
        
    return TRUE;
}

/*

  AutoStop:

  Stop the automatic collection and display of counter data.

*/
BOOL AutoStop()
{
    // Kill the timer
    KillTimer(ghWndMain, 1);

    return TRUE;
}

/*

  AutoToggleStatistics:

  Toggles the selection of statistics.

*/
BOOL AutoToggleStatistics(HMENU hMenu)
{
    gfStatsOn = !gfStatsOn;

    CheckMenuItem(hMenu, ID_AUTO_STATISTICS, gfStatsOn ? MF_CHECKED : MF_UNCHECKED);

    return TRUE;
}

/*

  FileImport:

  Import a file.

  This opens a file and adds each counter to the query.
  Each counter string is terminated with /r/n.

*/
void FileImport(HWND hWnd)
{
    HANDLE hFile;
    HCURSOR hOrigCursor;
    TCHAR szFileName[1024];

    if (!File_GetName(hWnd, szFileName, 1024))
        return ;

    // Open the file
    hFile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        ReportError(TEXT("Error in CreateFile."));
        return ;
    }

    UpdateStatus(TEXT("Importing counters..."));

    hOrigCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));

    TraverseFileAndAddCounters(hFile);

    SetCursor(hOrigCursor);

    UpdateStatus(TEXT("Counters imported."));
    
    // Close the file
    CloseHandle(hFile);

    return;
}

/*

  FileExport:

  Save current queries to a text file.  Each counter name is terminated with \r\n.

*/
void FileExport(HWND hWnd)
{
    HANDLE hFile;
    HCURSOR hOrigCursor;
    TCHAR szFileName[1024];

    if (!File_SaveName(hWnd, szFileName, 1024))
        return ;

    // Create the file
    hFile = CreateFile(szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        ReportError(TEXT("Error in CreateFile."));
        return ;
    }

    UpdateStatus(TEXT("Exporting counters..."));

    hOrigCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));

    // Traverse and write items
    TraverseAndWriteItems(hFile);

    SetCursor(hOrigCursor);

    UpdateStatus(TEXT("Counters exported."));

    // Close the file
    CloseHandle(hFile);

    return;
}

/*

  File_GetName:

  Get the name of a file to open, file must exist.

*/
BOOL File_GetName(HWND hWnd, LPTSTR lpszName, DWORD dwNameBufSize)
{
    OPENFILENAME ofn;
    TCHAR * lpszFilter = TEXT("Text files (.txt)\0*.txt\0All files\0*.*\0");

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFilter = lpszFilter;
    ZeroMemory(lpszName, dwNameBufSize * sizeof(TCHAR));
    ofn.lpstrFile = lpszName;
    ofn.nMaxFile = dwNameBufSize;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

    return GetOpenFileName(&ofn);
}

/*

  File_SaveName:

  Get the name of a file for saving.

*/
BOOL File_SaveName(HWND hWnd, LPTSTR lpszName, DWORD dwNameBufSize)
{
    OPENFILENAME ofn;
    TCHAR * lpszFilter = TEXT("Text files (.txt)\0*.txt\0All files\0*.*\0");

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;
    ofn.hInstance = ghInst;
    ofn.lpstrFilter = lpszFilter;
    ZeroMemory(lpszName, dwNameBufSize * sizeof(TCHAR));
    ofn.lpstrFile = lpszName;
    ofn.nMaxFile = dwNameBufSize;
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;

    return GetSaveFileName(&ofn);
}

/*

  TraverseAndWriteItems:

  Traverse the items in the listview control and then write each one to the
  file.

*/
BOOL TraverseAndWriteItems(HANDLE hFile)
{
    int nIndex, nNumItems;
    LV_ITEM lvi;
    TCHAR szItemText[256];

    nNumItems = ListView_GetItemCount(ghWndListView);
    if (nNumItems == 0) {
        ReportError("No items found.");
        return FALSE;
    }

    ZeroMemory(&lvi, sizeof(lvi));
    lvi.mask = LVIF_TEXT;
    lvi.pszText = szItemText;
    lvi.cchTextMax = 256;

    for (nIndex = 0; nIndex < nNumItems; nIndex++) {
        lvi.iItem = nIndex;

        if (!ListView_GetItem(ghWndListView, &lvi)) {
            ReportError(TEXT("Cannot get item's text."));
            return FALSE;
        }

        if (!WriteItem(hFile, szItemText))
            return FALSE;
    }

    return TRUE;
    
}

/*

  WriteItem:

  Write an individual counter name to the file.

  Provides proper termination of the string for our format.

*/
BOOL WriteItem(HANDLE hFile, LPTSTR lpszItemText)
{
    BOOL fRes = TRUE;
    DWORD dwBytesToWrite;
    DWORD dwBytesWritten;
    TCHAR szStringToWrite[1024];

    __try {

        wsprintf(szStringToWrite, "%s\r\n", lpszItemText);

        dwBytesToWrite = lstrlen(szStringToWrite) * sizeof(TCHAR);
        if (!WriteFile(hFile, szStringToWrite, dwBytesToWrite, &dwBytesWritten, NULL)) {
            ReportError(TEXT("Error in WriteFile."));
            fRes = FALSE;
        }
        else {
            if (dwBytesWritten != dwBytesToWrite) {
                ReportError(TEXT("Wrote fewer bytes than expected."));
                fRes = FALSE;
            }
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        fRes = FALSE;
    }

    return TRUE;
}

/*

  TraverseFileAndAddCounters:

  Scans a file and adds each counter name to our query.

  Much care is taken to handle the case where the buffer contains 
  a partial string because the file contains more data than our buffer
  will hold.

*/
BOOL TraverseFileAndAddCounters(HANDLE hFile) 
{
    TCHAR szFileContents[FILE_BUFFER_SIZE];
    TCHAR szItemString[FILE_BUFFER_SIZE];
    LPTSTR lpBufferPointer;
    LPTSTR lpCurrentStringStart;
    DWORD dwBytesToRead;
    DWORD dwBytesRead;
    int nCharsRemaining;
    int nIndex;
    int nStrLen;
    BOOL fRes = TRUE;

    lpBufferPointer = szFileContents;
    dwBytesToRead = FILE_BUFFER_SIZE;
    nCharsRemaining = 0;

    __try {

        while(fRes) {
            if (!ReadFile(hFile, lpBufferPointer, dwBytesToRead, &dwBytesRead, NULL)) {
                ReportError(TEXT("Error in ReadFile."));
                fRes = FALSE;
                break;
            }
            else {
                if (dwBytesRead == 0)
                    break;

                nIndex = 0;
                dwBytesRead += nCharsRemaining;

                while(TRUE) {
                    lpCurrentStringStart = szFileContents + nIndex;

                    // Find "\r\n" terminator
                    for (nStrLen = 0; (nIndex < (int) dwBytesRead) && (szFileContents[nIndex] != '\n'); nIndex++, nStrLen++)
                        ;

                    if (nIndex >= (int)dwBytesRead) {
                        MoveMemory(szFileContents, lpCurrentStringStart, nStrLen);
                        lpBufferPointer = szFileContents + nStrLen;
                        nCharsRemaining = nStrLen;
                        dwBytesToRead = FILE_BUFFER_SIZE - nCharsRemaining;
                        break;
                    }
                    else {
                        if (nStrLen > 2) {
                            lstrcpyn(szItemString, lpCurrentStringStart, nStrLen);
                            if (!PDH_AddCounter(szItemString)) {
                                fRes = FALSE;
                                break;
                            }
                        }   
                        else
                            OutputDebugString("Error: string length is too small.");
                    }

                    // get past the '\n'
                    nIndex++;
                }
            }
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        fRes = FALSE;
    }

    return fRes;
}

/*

  ItemDisplayPopup:

  Display the popup menu (right-click menu) and return the result from TrackPopupMenu.

  The result will be the menu item selected.

*/
BOOL ItemDisplayPopup(HMENU hMenu)
{   
    BOOL fRet;
    POINT pt;

    pt.x = ptLastRClick.x;
    pt.y = ptLastRClick.y;

    ClientToScreen(ghWndMain, &pt);

    fRet = TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_LEFTBUTTON, 
        pt.x, pt.y, 0, ghWndMain, NULL );

    return fRet;
}

/*

  HelpInfoInit:

  Initialize the help dialog.  Reads the readme.txt file and 
  displays it an edit control.

*/
void HelpInfoInit(HWND hWndDlg)
{
    HWND hWndEdit;
    HANDLE hFile;
    DWORD dwBytesRead;
    TCHAR szBuffer[FILE_BUFFER_SIZE+1];

    hWndEdit = GetDlgItem(hWndDlg, IDC_README);
    if (hWndEdit == NULL) {
        ReportError(TEXT("Can't find IDC_README."));
        return;
    }

    // Open the file
    hFile = CreateFile(TEXT("Readme.txt"), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        ReportError(TEXT("Error in CreateFile."));
        return ;
    }

    while(TRUE) {
        if (!ReadFile(hFile, szBuffer, FILE_BUFFER_SIZE, &dwBytesRead, NULL))
            break;

        if (dwBytesRead == 0)
            break;

        szBuffer[dwBytesRead] = '\0';

        Edit_SetSel(hWndEdit, (WPARAM) -1, (LPARAM) 0x7FFFFFFF);
        Edit_ReplaceSel(hWndEdit, szBuffer);
    }

    CloseHandle(hFile);
}

/*

  HelpInfoDialogProcedure:

  Dialog procedure for the Help dialog.

*/
BOOL CALLBACK HelpInfoDialogProcedure(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BOOL fRes = FALSE;

    switch(uMsg)
    {
    case WM_INITDIALOG: 
        HelpInfoInit(hWndDlg);
        break;

    case WM_COMMAND:
        switch(LOWORD(wParam)) {
        case IDOK:
        case IDCANCEL:
            EndDialog(hWndDlg, 0);
            fRes = TRUE;
            break;
        }
        break;
    }

    return fRes;
}

/*

  HelpInfo:

  Function to display the Help dialog.

*/
void HelpInfo(HWND hwnd)
{
    DialogBox(ghInst, MAKEINTRESOURCE(IDD_HELPINFO), hwnd, HelpInfoDialogProcedure);
}   