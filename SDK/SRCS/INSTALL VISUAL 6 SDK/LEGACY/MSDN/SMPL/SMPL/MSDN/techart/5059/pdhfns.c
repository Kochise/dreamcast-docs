#include <windows.h>
#include <windowsx.h>
#include <pdh.h>
#include <pdhmsg.h>
#include <assert.h>
#include <math.h>
#include <tchar.h>
#include <stdio.h>

#include "RESOURCE.h"
#include "PDHTEST.h"

// globals
BOOL gbIncludeInstanceIndex;
BOOL gbSingleCounterPerAdd;
BOOL gbSingleCounterPerDialog;
BOOL gbLocalCountersOnly;
BOOL gbWildCardInstances;
BOOL gbHideDetailBox;
BOOL gbInitializePath;

HQUERY ghQuery;
LPTSTR gszReturnPath;
DWORD gdwReturnPathSize;
PDH_BROWSE_DLG_CONFIG gpdhBrowseDlgConfig;

/*

  SetScaleDialogProcedure:

  Dialog procedure for selecting a scale for a counter

*/
BOOL CALLBACK SetScaleDialogProcedure(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BOOL fRes = FALSE;

    switch(uMsg)
    {
    case WM_INITDIALOG: 
        {
            int nScale;
            int nZeroIndex = 0;
            int n;
            TCHAR szLabel[1024];
            double f;

            // Build contents of the scale combo box
            for (n = 0, nScale = PDH_MIN_SCALE; nScale <= PDH_MAX_SCALE; n++, nScale++) {
                f = pow(10, nScale);
                _stprintf(szLabel, TEXT("%G"), f);
                ComboBox_AddString(GetDlgItem(hWndDlg, IDC_SCALECOMBO), szLabel);
                if (nScale == 0)
                    nZeroIndex = n;
            }

            ComboBox_SetCurSel(GetDlgItem(hWndDlg, IDC_SCALECOMBO), nZeroIndex);
        }
        break;

    case WM_COMMAND:
        switch(LOWORD(wParam)) {
        case IDOK:
            EndDialog(hWndDlg, PDH_MIN_SCALE + ComboBox_GetCurSel(GetDlgItem(hWndDlg, IDC_SCALECOMBO)) );
            fRes = TRUE;
            break;
        case IDCANCEL:
            EndDialog(hWndDlg, PDH_MAX_SCALE+1);
            fRes = TRUE;
            break;
        }
        break;
    }

    return fRes;
}

/*

  PDH_SetCounterScale:

  Function to set the scale for an individual counter

*/
BOOL PDH_SetCounterScale(HINSTANCE hInst, HWND hWnd, PPDHCOUNTERSTRUCT pCounterStruct) 
{
    BOOL fRes = TRUE;
    LONG lFactor;

    lFactor = DialogBox(hInst, MAKEINTRESOURCE(IDD_SETSCALEDIALOG), hWnd, SetScaleDialogProcedure);

    // cancel selected?
    if (lFactor == (PDH_MAX_SCALE + 1))
        return FALSE;

    __try {
        if (ERROR_SUCCESS != PdhSetCounterScaleFactor(pCounterStruct->hCounter, lFactor)) {
            UpdateStatus(TEXT("Failure in PdhSetCounterScaleFactor."));
            fRes = FALSE;
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        UpdateStatus(TEXT("Exception in PdhSetCounterScaleFactor. (Handled)"));
        MessageBeep(0);
        fRes = FALSE;
    }

    return fRes;
}

/*

  InitGetInfoDialog:

  Initialize the counter info dialog with the info retrieved
  for the counter examined.

*/
BOOL InitGetInfoDialog(HWND hWndDlg, PPDH_COUNTER_INFO pCounterInfo)
{
    SetDlgItemInt(hWndDlg, IDC_TYPE, pCounterInfo->dwType, FALSE);

    SetDlgItemInt(hWndDlg, IDC_CVERSION, pCounterInfo->CVersion, FALSE);
    SetDlgItemInt(hWndDlg, IDC_CSTATUS, pCounterInfo->CStatus, FALSE);

    SetDlgItemInt(hWndDlg, IDC_SCALE, pCounterInfo->lScale, TRUE);
    SetDlgItemInt(hWndDlg, IDC_DEFAULTSCALE, pCounterInfo->lDefaultScale, TRUE);

    SetDlgItemText(hWndDlg, IDC_FULLPATH, pCounterInfo->szFullPath);
    SetDlgItemText(hWndDlg, IDC_MACHINENAME, pCounterInfo->szMachineName);
    SetDlgItemText(hWndDlg, IDC_OBJECTNAME, pCounterInfo->szObjectName);
    SetDlgItemText(hWndDlg, IDC_INSTANCENAME, pCounterInfo->szInstanceName);
    SetDlgItemText(hWndDlg, IDC_PARENTINSTANCE, pCounterInfo->szParentInstance);
    SetDlgItemInt(hWndDlg, IDC_INSTANCEINDEX, pCounterInfo->dwInstanceIndex, FALSE);
    SetDlgItemText(hWndDlg, IDC_COUNTERNAME, pCounterInfo->szCounterName);
    SetDlgItemText(hWndDlg, IDC_EXPLAINTEXT, pCounterInfo->szExplainText);

    return TRUE;
}

/*

  GetInfoDialogProcedure:

  Dialog procedure for displaying the counter info retrieved.

*/
BOOL CALLBACK GetInfoDialogProcedure(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BOOL fRes = FALSE; // return value if I don't do anything with the message
    PPDH_COUNTER_INFO pCounterInfo;

    switch(uMsg) {
    case WM_INITDIALOG:
        if (lParam)
            pCounterInfo = (PPDH_COUNTER_INFO) lParam;
        else {
            UpdateStatus(TEXT("lParam is null in GetInfoDialogProcedure."));
            EndDialog(hWndDlg, 0);
        }

        InitGetInfoDialog(hWndDlg, pCounterInfo);

        fRes = TRUE;
        break;

    case WM_COMMAND:
        switch(LOWORD(wParam)) {
        case IDCANCEL:
        case IDOK:
            EndDialog(hWndDlg, 0);
            fRes = TRUE;
            break;
        }
        break;
    }

    return fRes;
}

/*

  PDH_GetCounterInfo:

  Function to call PdhGetCounterInfo to retrieve counter info and 
  display the results.

*/
BOOL PDH_GetCounterInfo(HINSTANCE hInst, HWND hWnd, PPDHCOUNTERSTRUCT pCounterInfo)
{
    BOOL fRes = TRUE;
    DWORD dwBufferSize;
    PPDH_COUNTER_INFO pInfo;

    dwBufferSize = 2048;
    pInfo = (PPDH_COUNTER_INFO) LocalAlloc(LPTR, dwBufferSize);
    if (pInfo == NULL) {
        UpdateStatus(TEXT("Failure to LocalAlloc(pInfo)."));
        return FALSE;
    }

    __try {
        if (ERROR_SUCCESS != PdhGetCounterInfo(pCounterInfo->hCounter,
                                                TRUE, // retrieve explain text
                                                &dwBufferSize,
                                                pInfo )) {
            UpdateStatus(TEXT("Failure in PdhGetCounterInfo.\n"));
            fRes = FALSE;
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        UpdateStatus(TEXT("Exception in PdhGetCounterInfo. (Handled)"));
        MessageBeep(0);
        fRes = FALSE;
    }

    if (fRes)
        DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_GETINFODIALOG), hWnd, GetInfoDialogProcedure, (LPARAM) pInfo);

    if (NULL != LocalFree(pInfo)) {
        UpdateStatus(TEXT("Failure in LocalFree(pInfo)."));
        fRes = FALSE;
    }
    
    return TRUE;
}

/*

  PDH_CollectQueryData:

  Function to call PdhCollectQueryData to collect raw data for the counters
  in the query.

*/    
BOOL PDH_CollectQueryData()
{
    BOOL fRes = TRUE;

    __try {
        if (ERROR_SUCCESS != PdhCollectQueryData(ghQuery)) {
            UpdateStatus(TEXT("Error in PdhCollectQueryData."));
            fRes = FALSE;
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        UpdateStatus(TEXT("Exception in PdhCollectQueryData. (Aborting)"));
        MessageBeep(0);
        fRes = FALSE;
    }

    return fRes;
}

/*

  PDH_DisplayFormattedValue:

  Function which displays a formatted value in the associate list view column.
  Parameters: 
    lValue (the value to display)
    nItemIndex (the item in the list view control (zero based index))
    nSubItem (the column # (zero based))

*/
BOOL PDH_DisplayFormattedValue(LONG lValue, int nItemIndex, int nSubItem)
{
    TCHAR szMsg[1024];

    wsprintf(szMsg, TEXT("%d"), lValue);

    SetSubItemText(nItemIndex, nSubItem, szMsg);

    return TRUE;
}

/*

  PDH_UpdateValue:

  Function to call PdhGetFormattedCounterValue and display the results.

*/
BOOL PDH_UpdateValue(PPDHCOUNTERSTRUCT pCounterStruct, int nItemIndex)
{
    BOOL fRes = TRUE;
    PDH_FMT_COUNTERVALUE pdhFormattedValue;

    __try {

        if (ERROR_SUCCESS != PdhGetFormattedCounterValue( 
                                    pCounterStruct->hCounter,
                                    PDH_FMT_LONG,
                                    NULL,
                                    &pdhFormattedValue )) {
            UpdateStatus(TEXT("Failure in PdhGetFormattedCounterValue."));
            fRes = FALSE;
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        UpdateStatus(TEXT("Exception in PdhGetFormattedCounterValue. (Handled)"));
        MessageBeep(0);
        fRes = FALSE;
    }

    if (fRes) {
        if (pdhFormattedValue.CStatus != ERROR_SUCCESS) {
            // error in the counter
            // report the error in the list view
            SetSubItemText(nItemIndex, COL_COUNTERVALUE, TEXT("Error"));
            fRes = FALSE;
        }
        else
            PDH_DisplayFormattedValue(pdhFormattedValue.longValue, nItemIndex, COL_COUNTERVALUE);
    }

    return fRes;
}

/*

  PDH_UpdateRawValue:

  Function to call PdhGetRawCounterValue to update the ring buffer with the latest
  collected value.

  Updates the counter struct to indicate the state of the data collection.
  After function is complete:
    nRawCount contains the number of raw value in the ring buffer.
    nNextIndex indicates the next element of the buffer to be updated.
    nOldestIndex indicates which element contains the oldest raw value.

*/
BOOL PDH_UpdateRawValue(PPDHCOUNTERSTRUCT pCounterStruct, int nItemIndex)
{
    BOOL fRes = TRUE;
    PPDH_RAW_COUNTER ppdhRawCounter;

    __try {
        // Assign the next value into the array
        ppdhRawCounter = &(pCounterStruct->a_RawValue[pCounterStruct->nNextIndex]);

        if (ERROR_SUCCESS != PdhGetRawCounterValue( 
                                    pCounterStruct->hCounter,
                                    NULL,
                                    ppdhRawCounter) ) {
            fRes = FALSE;
        }
        else {

            // update raw counter - up to MAX_RAW_VALUES
            pCounterStruct->nRawCount = min(pCounterStruct->nRawCount + 1, MAX_RAW_VALUES);

            // Update next index - rolls back to zero upon reaching MAX_RAW_VALUES
            pCounterStruct->nNextIndex = (pCounterStruct->nNextIndex + 1) % MAX_RAW_VALUES;

            // The Oldest index remains zero until the array is filled.
            // It will now be the same as the 'next' index since it was previously assigned.
            if (pCounterStruct->nRawCount >= MAX_RAW_VALUES)
                pCounterStruct->nOldestIndex = pCounterStruct->nNextIndex;
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        UpdateStatus(TEXT("Exception in PDH_UpdateRawValue. (Handled)"));
        MessageBeep(0);
        fRes = FALSE;
    }

    return fRes;
}

/*

  PDH_DisplayStatistics:

  Function to call PdhComputeCounterStatistics.  This function calculates
  counter statistics (min, max, avg) and formats the values for display.
  This function also is reponsible for calling the appropriate display
  functions to get the statistical values displayed in the proper columns.

*/
BOOL PDH_DisplayStatistics(PPDHCOUNTERSTRUCT pCounterStruct, int nItemIndex)
{
    BOOL fRes = TRUE;
    PDH_STATISTICS pdhStats;

    __try {
        if (ERROR_SUCCESS != PdhComputeCounterStatistics(
                                        pCounterStruct->hCounter,
                                        PDH_FMT_LONG,
                                        pCounterStruct->nOldestIndex,
                                        pCounterStruct->nRawCount,
                                        pCounterStruct->a_RawValue,
                                        &pdhStats)) {
            fRes = FALSE;
        }
        else {

            if (pdhStats.min.CStatus != ERROR_SUCCESS)
                SetSubItemText(nItemIndex, COL_COUNTERMIN, TEXT("N/A"));
            else
                PDH_DisplayFormattedValue(pdhStats.min.longValue, nItemIndex, COL_COUNTERMIN);

            if (pdhStats.max.CStatus != ERROR_SUCCESS)
                SetSubItemText(nItemIndex, COL_COUNTERMAX, TEXT("N/A"));
            else
                PDH_DisplayFormattedValue(pdhStats.max.longValue, nItemIndex, COL_COUNTERMAX);

            if (pdhStats.mean.CStatus != ERROR_SUCCESS)
                SetSubItemText(nItemIndex, COL_COUNTERAVG, TEXT("N/A"));
            else
                PDH_DisplayFormattedValue(pdhStats.mean.longValue, nItemIndex, COL_COUNTERAVG);
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        UpdateStatus(TEXT("Exception in PDH_DisplayStatistics. (Handled)"));
        MessageBeep(0);
        fRes = FALSE;
    }

    return fRes;
}

/*

  PDH_AddCounter:

  Function to add a counter to the query.  Before calling PdhAddCounter, this
  function allocates the associated counter struct, and adds the item to the
  list view control.  If these preliminary steps are complete, then PdhAddCounter
  is performed.  If PdhAddCounter fails, or an exception occurs anywhere inside the
  function call, then the list view item and the counter struct are cleaned up.

*/
BOOL PDH_AddCounter(LPTSTR szCounterName)
{
    BOOL fRes = TRUE;
    PPDHCOUNTERSTRUCT pCounterStruct;
    int nItemIndex;

    // Allocate a PDHCOUNTERSTRUCT for this new counter
    pCounterStruct = (PPDHCOUNTERSTRUCT) LocalAlloc(LPTR, sizeof(PDHCOUNTERSTRUCT));
    if (pCounterStruct == NULL) {
        UpdateStatus(TEXT("Failed to LocalAlloc(pCounterStruct)."));
        return FALSE;
    }

    // Add the counter to the list view control
    nItemIndex = AddListViewItem(szCounterName, pCounterStruct);
    if (nItemIndex == -1) {
        UpdateStatus(TEXT("Failed to add list view item."));
        return FALSE;
    }

    __try {
        // Add the counter to the current query
        if (ERROR_SUCCESS != PdhAddCounter(ghQuery, szCounterName, (DWORD) pCounterStruct, &(pCounterStruct->hCounter))) {
            UpdateStatus(TEXT("Failed to PdhAddCounter."));
            fRes = FALSE;
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        UpdateStatus(TEXT("Exception in PdhAddCounter. (Handled)"));
        MessageBeep(0);
        fRes = FALSE;
    }

    // If the add failed, then clean up the list view and the counter struct
    if (fRes == FALSE) {
        RemoveItem(nItemIndex);
        LocalFree(pCounterStruct);
    }

    return fRes;
}

/*

  PDH_RemoveCounter:

  Function to call PdhRemoveCounter to remove a counter from the query.

*/
BOOL PDH_RemoveCounter(LPTSTR szCounterName, PPDHCOUNTERSTRUCT pCounterStruct)
{
    BOOL fRes = TRUE;
    TCHAR szMsg[1024];

    __try {
        // Remove the counter from the current query
        if (ERROR_SUCCESS != PdhRemoveCounter(pCounterStruct->hCounter)) {
            UpdateStatus(TEXT("Failed PdhRemoveCounter."));
            MessageBeep(0);
            fRes = FALSE;
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        UpdateStatus(TEXT("Exception in PdhRemoveCounter. (Handled)"));
        MessageBeep(0);
        fRes = FALSE;
    }

    if (fRes) {
        wsprintf(szMsg, TEXT("Counter removed: %s"), szCounterName);
        UpdateStatus(szMsg);
    }

    if (NULL != LocalFree(pCounterStruct)) {
        UpdateStatus(TEXT("Failed to LocalFree(pCounterStruct)."));
        MessageBeep(0);
    }

    return TRUE;
}

/*

  PDH_ToggleFlag:

  Function to toggle one of the browse dialog flags we maintain.

*/
BOOL PDH_ToggleFlag(int id)
{
    switch(id) {
    case ID_FLAGS_INCLUDEINSTANCEINDEX:
        gbIncludeInstanceIndex = !gbIncludeInstanceIndex;
        break;
    case ID_FLAGS_SINGLECOUNTERPERADD:
        gbSingleCounterPerAdd = !gbSingleCounterPerAdd;
        break;
    case ID_FLAGS_SINGLECOUNTERPERDIALOG:
        gbSingleCounterPerDialog = !gbSingleCounterPerDialog;
        break;
    case ID_FLAGS_LOCALCOUNTERSONLY:
        gbLocalCountersOnly = !gbLocalCountersOnly;
        break;
    case ID_FLAGS_WILDCARDINSTANCES:
        gbWildCardInstances = !gbWildCardInstances;
        break;
    case ID_FLAGS_HIDEDETAILBOX:
        gbHideDetailBox = !gbHideDetailBox;
        break;
    case ID_FLAGS_INITIALIZEPATH:
        gbInitializePath = !gbInitializePath;
        break;
    }

    return TRUE;
}

/*

  PDH_CheckMenuItem:

  Function to check or uncheck a menu item based on the state of the browse dialog
  flags we maintain.

*/
BOOL PDH_CheckMenuItem(HMENU hMenu, int id)
{
    BOOL fChecked = FALSE;
    switch(id) {
    case ID_FLAGS_INCLUDEINSTANCEINDEX:
        fChecked = gbIncludeInstanceIndex;
        break;
    case ID_FLAGS_SINGLECOUNTERPERADD:
        fChecked = gbSingleCounterPerAdd;
        break;
    case ID_FLAGS_SINGLECOUNTERPERDIALOG:
        fChecked = gbSingleCounterPerDialog;
        break;
    case ID_FLAGS_LOCALCOUNTERSONLY:
        fChecked = gbLocalCountersOnly;
        break;
    case ID_FLAGS_WILDCARDINSTANCES:
        fChecked = gbWildCardInstances;
        break;
    case ID_FLAGS_HIDEDETAILBOX:
        fChecked = gbHideDetailBox;
        break;
    case ID_FLAGS_INITIALIZEPATH:
        fChecked = gbInitializePath;
        break;
    default:
        return FALSE;
    }

    CheckMenuItem(hMenu, id, fChecked ? MF_CHECKED : MF_UNCHECKED);

    return TRUE;
}

/*

  PDH_Initialize:

  Function to call PdhOpenQuery and allocate the buffer for holding counter name
  strings.

*/
BOOL PDH_Initialize()
{
    BOOL fRes = TRUE;

    gbIncludeInstanceIndex = FALSE;
    gbSingleCounterPerAdd = FALSE;
    gbSingleCounterPerDialog = FALSE;
    gbLocalCountersOnly = TRUE;
    gbWildCardInstances = FALSE;
    gbHideDetailBox = TRUE;
    gbInitializePath = FALSE;

    __try {
        if (ERROR_SUCCESS != PdhOpenQuery(NULL, 1, &ghQuery)) {
            UpdateStatus(TEXT("Could not open PDH query."));
            fRes = FALSE;
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        UpdateStatus(TEXT("Exception in PdhOpenQuery. (Handled)"));
        MessageBeep(0);
        fRes = FALSE;
    }

    if (fRes) {
        gdwReturnPathSize = INIT_RETURNPATH;
        gszReturnPath = (LPTSTR) LocalAlloc(LPTR, INIT_RETURNPATH);
        if (gszReturnPath == NULL) {
            UpdateStatus(TEXT("Could not LocalAlloc gszReturnPath."));
            fRes = FALSE;
        }
    }

    return fRes;
}

/*

  PDH_Uninitialize:

  Function to call PdhCloseQuery and to deallocate the buffer for the counter name
  strings.

*/
BOOL PDH_Uninitialize()
{
    BOOL fRes = TRUE;

    __try {
        if (NULL != LocalFree(gszReturnPath)) {
            UpdateStatus(TEXT("Failed to LocalFree(gszReturnPath)."));
            fRes = FALSE;
        }

        if (ERROR_SUCCESS != PdhCloseQuery(ghQuery)) {
            UpdateStatus(TEXT("Failed to close PDH query."));
            fRes = FALSE;
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        UpdateStatus(TEXT("Exception in PDH_Uninitialize. (Handled)"));
        MessageBeep(0);
        fRes = FALSE;
    }

    return fRes;
}

/*

  PDH_BrowseCallback:

  Callback function to handle browse dialog counter selections.
  This callback is called by the PDH Library and the global string 
  buffer contains the names of the counter(s) selected.

  The Browse Dialog Config structure contains status information.

  Each counter selected is added to the query.

*/
PDH_STATUS __stdcall PDH_BrowseCallback(DWORD dwParam) 
{
    PDH_STATUS returnValue;
    LPTSTR szCurrentPath;
    int nLen;

    if (gpdhBrowseDlgConfig.CallBackStatus == PDH_MORE_DATA) {
        // Buffer too small for the counters selected
        UpdateStatus(TEXT("Buffer is too small. Realloc'g and trying again."));

        // Free original buffer
        if (NULL != LocalFree(gszReturnPath)) {
            UpdateStatus(TEXT("Could not LocalFree(gszReturnPath)."));
            return PDH_MEMORY_ALLOCATION_FAILURE;
        }

        // Alloc new larger buffer
        gdwReturnPathSize += BUFFER_INCREMENT;
        gszReturnPath = (LPTSTR) LocalAlloc(LPTR, gdwReturnPathSize);
        if (gszReturnPath == NULL) {
            UpdateStatus(TEXT("Could not LocalAlloc gszReturnPath."));
            return PDH_MEMORY_ALLOCATION_FAILURE;
        }

        // Set the config structure members for the new buffer
        gpdhBrowseDlgConfig.szReturnPathBuffer = gszReturnPath;
        gpdhBrowseDlgConfig.cchReturnPathLength = gdwReturnPathSize;

        // retry the counter browse selection
        return PDH_RETRY;
    }

    returnValue = ERROR_SUCCESS;
    szCurrentPath = gszReturnPath;
    // This string manipulation code is in a try/except block
    // to gracefully handle any problems 
    // with pointer values, null termination, boundary conditions, etc.
    __try {
        while (TRUE) {
            nLen = lstrlen(szCurrentPath);

            if (nLen == 0)
                break;

            PDH_AddCounter(szCurrentPath);

            szCurrentPath += (nLen + 1);
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        returnValue = PDH_INVALID_BUFFER;
    }

    return returnValue ;
}

/*

  PDH_BrowseCounter:

  Function to call PdhBrowseCounters.  This function initializes the browse dialog 
  config structure according to the global flags we maintain and other members also.

  The PdhBrowseCounters function displays a dialog box allowing the user to select
  counters.

  The Pdh_BrowseCallback function processes the selections.

*/
BOOL PDH_BrowseCounters(HWND hWnd)
{
    BOOL fRes = TRUE;

    ZeroMemory(&gpdhBrowseDlgConfig, sizeof(gpdhBrowseDlgConfig));
    
    gpdhBrowseDlgConfig.bIncludeInstanceIndex = gbIncludeInstanceIndex;
    gpdhBrowseDlgConfig.bSingleCounterPerAdd = gbSingleCounterPerAdd;
    gpdhBrowseDlgConfig.bSingleCounterPerDialog = gbSingleCounterPerDialog;
    gpdhBrowseDlgConfig.bLocalCountersOnly = gbLocalCountersOnly;
    gpdhBrowseDlgConfig.bWildCardInstances = gbWildCardInstances;
    gpdhBrowseDlgConfig.bHideDetailBox = gbHideDetailBox;
    gpdhBrowseDlgConfig.bInitializePath = gbInitializePath;

    gpdhBrowseDlgConfig.hWndOwner = hWnd;

    gpdhBrowseDlgConfig.szReturnPathBuffer = gszReturnPath;
    gpdhBrowseDlgConfig.cchReturnPathLength = gdwReturnPathSize;

    gpdhBrowseDlgConfig.pCallBack = PDH_BrowseCallback;

    __try {
        PdhBrowseCounters(&gpdhBrowseDlgConfig);
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        UpdateStatus(TEXT("Exception in PdhBrowseCounters. (Handled)"));
        MessageBeep(0);
        fRes = FALSE;
    }

    return fRes;
}