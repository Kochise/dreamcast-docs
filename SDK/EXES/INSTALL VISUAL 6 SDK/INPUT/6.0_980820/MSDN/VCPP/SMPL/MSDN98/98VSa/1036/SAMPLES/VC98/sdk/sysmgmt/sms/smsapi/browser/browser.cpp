//***************************************************************************
//
//  File: browser.cpp
//
//  Copyright (c) 1994, 1995 Microsoft Corp.
//
//  Sample Windows application for the SMS API.
//
//  Author:
//      Jonathan Shuval
//
//  This program implements a browser for SMS objects.
//
//  See the readme.txt file in this directory for full details.
//
//***************************************************************************


// ====================================================================
//
//  Includes
//
// ====================================================================
#include "resource.h"

#include <afx.h>
#include <afxcoll.h>
#include <time.h>               // For converting time scalars into strings.

#include <smsapi.h>             // SMS API

// 3d controls.
// -----------------------
#include <ctl3d.h>

// My header.
// -----------------------
#include "browser.h"


// ====================================================================
//
//  Manifests.
//
// ====================================================================
#define WM_LOGIN_MSG    WM_USER+101     // So we can send ourself an
                                        // instruction to connect.





// -------------------------------------------------------------
//  Debug utility
// -------------------------------------------------------------
#ifdef DEBUG
#include <io.h>
#include <stdio.h>
#include <time.h>
int  Log( char *pFmt, ... );
#endif  // DEBUG


// ====================================================================
//
//  The program starts here.
//
// ====================================================================

int PASCAL WinMain(
                HINSTANCE hInstance,
                HINSTANCE hPrevInstance,
                LPSTR lpszCmdLine,
                int nCmdShow)
{
    int rc;

    _hInstance = hInstance;

    // Register the 3d controls.
    // =========================
    Ctl3dRegister(_hInstance);
    Ctl3dAutoSubclass(_hInstance);


    // Load the saved db login information into the globals.
    // Change to suite your preference.
    // =========================================================
    strcat( gszServer,   "jonshu2" );
    strcat( gszDbName,   "SMS" );
    strcat( gszUserName, "sa" );

    // Dialogue does the work.
    // =======================
    rc = DialogBox( _hInstance,
                    MAKEINTRESOURCE(IDD_MAIN_DIALOG),
                    0,
                    (DLGPROC)MainDlg );



    Ctl3dUnregister(_hInstance);

    return(rc);
}



// ====================================================================
//
//  Dialogue to solicit login information for the datasource.
//
// ====================================================================

extern "C" BOOL CALLBACK LoginDlg(  HWND hDlg,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam)
{

    HWND hEdit;

    switch (message) {

    case WM_INITDIALOG:
        //KLUDGE: set it with the params I most often use.
        SetDlgItemText( hDlg, IDC_SQLSERVER, gszServer );
        SetDlgItemText( hDlg, IDC_DATABASE,  gszDbName );
        SetDlgItemText( hDlg, IDC_LOGINID,   gszUserName);

        // Set focus on this control.
        hEdit = GetDlgItem( hDlg, IDC_SQLSERVER );
        SetFocus(hEdit);
        return(TRUE);

    case WM_CLOSE:
        EndDialog( hDlg, IDCANCEL );
        return(TRUE);

    case WM_SYSCOLORCHANGE:
        Ctl3dColorChange();
        return(TRUE);


    case WM_COMMAND:

        switch (wParam) {

        case IDOK:
            // Retrieve the values from the edit controls.
            //LATER: validate.
            gdsParams.sqlParams.ds          = DB_SQL;
            gdsParams.sqlParams.pFunc       = NULL;     // No encryption.
            gdsParams.sqlParams.pszKey      = "";
            gdsParams.sqlParams.pszServer   = gszServer;
            gdsParams.sqlParams.pszDbName   = gszDbName;
            gdsParams.sqlParams.pszUserName = gszUserName;
            gdsParams.sqlParams.pszPasswd   = gszPasswd;

            hEdit = GetDlgItem( hDlg, IDC_SQLSERVER );
            SendMessage( hEdit, WM_GETTEXT, sizeof(gszServer), (LPARAM)gszServer );

            hEdit = GetDlgItem( hDlg, IDC_DATABASE );
            SendMessage( hEdit, WM_GETTEXT, sizeof(gszDbName), (LPARAM)gszDbName );

            hEdit = GetDlgItem( hDlg, IDC_LOGINID );
            SendMessage( hEdit, WM_GETTEXT, sizeof(gszUserName), (LPARAM)gszUserName );

            hEdit = GetDlgItem( hDlg, IDC_PASSWORD );
            SendMessage( hEdit, WM_GETTEXT, sizeof(gszPasswd), (LPARAM)gszPasswd );

            // Disable the Login button. This will be enabled after a
            // container enumeration has completed.
            hEdit = GetDlgItem( hDlg, IDC_CONNECT );
            EnableWindow( hEdit, FALSE );


            // And now terminate.
            EndDialog( hDlg, IDOK );
            return(TRUE);
        }
    }

    return(FALSE);

}  /* LoginDlg */




// ====================================================================
//
//  The real work starts here.
//
//  This dialogue allows the user to select a container from the list
//  of available containers. Once selected the user can select filters
//  to be applied to the container.
//  When these steps are completed the container can be viewed by
//  pressing the "View container" button.
// ====================================================================

extern "C" BOOL CALLBACK MainDlg(   HWND hDlg,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam)
{

    // At init we disable all controls except the "Select container" button.
    // Once a container has been selected this button is disabled and the
    // "Select filter" button and associated listbox are enabled.
    // This button enables us to select multiple filters.
    // Pressing the "View container" button causes us to dismiss this
    // dialogue and display the container contents.
    // =====================================================================
    HWND hEdit;
    SMS_STATUS stat;
    DWORD dwI;
    FOLDER_INFO *pCont = NULL;
    FILTER_INFO    *pF = NULL;
    MY_FILTER_INFO *pMyFilter = NULL;
    DWORD ctContainers = 0;
    int index;
    static CObArray aFilters;       // Array of FILTER_INFOs representing
                                    // selected filters.
    // Get the container types and insert them into the menu
    static FOLDER_INFO **pContainerList = NULL;
    int reply;
    HANDLE hFilter;

    switch (message) {
    case WM_INITDIALOG:
        // Dialogue initialisation.


        // Post a message to ourselves. This will be processed after the init
        // completes.
        // This message causes us to connect to the data source.
        PostMessage( hDlg, WM_LOGIN_MSG, 0, 0 );


        // ==============================================================
        // We need to enumerate the containers and filters
        // and populate the appropriate listboxes.
        // Enumeration is done by calling into the engine.
        // The resulting lists are held in globals.
        // ==============================================================

        // Enumerate the container types.
        // ---------------------------------------------------------

            // Get the number of containers.
        SmsEnumContainers(NULL, &ctContainers);

            // Allocate memory and call the enum again.
        pContainerList = new FOLDER_INFO *[ctContainers];
        SmsEnumContainers(pContainerList, &ctContainers);

            // Populate the listbox.
        hEdit = GetDlgItem(hDlg, IDC_AVAIL_CONTAINER_LIST);

        for (dwI = 0; dwI < ctContainers; dwI++) {

            pCont = pContainerList[dwI];
            SendMessage(hEdit, LB_ADDSTRING, 0, (LPARAM)pCont->pszTag);
        }

            // Select the first one in the list.
        SendMessage(hEdit, LB_SETCURSEL, 0, 0);


        // Enumerate the filter types.
        // ---------------------------------------------------------
            // Get the number of filters.
        SmsEnumFilters(0, &ctFilters);

            // Allocate memory and call the enum again.
        gpAvailFilterList = new FILTER_INFO[ctFilters];
        SmsEnumFilters(gpAvailFilterList, &ctFilters);

            // Populate the listbox.
        hEdit = GetDlgItem(hDlg, IDC_AVAIL_FILTER_LIST);

        for (dwI = 0; dwI < ctFilters; dwI++) {
            pF = &gpAvailFilterList[dwI];
            SendMessage(hEdit, LB_ADDSTRING, 0, (LPARAM)pF->szTag);
            pF++;
        }

            // Select the first one in the list.
        SendMessage(hEdit, LB_SETCURSEL, 0, 0);


        // Disable all except the select container button.
        // ===============================================
            // Container group
            // ---------------
        hEdit = GetDlgItem(hDlg, IDC_SELECT_CONTAINER_BTN);
        EnableWindow( hEdit, TRUE );

        hEdit = GetDlgItem(hDlg, IDC_SELECT_CONTAINER_DONE);
        EnableWindow( hEdit, FALSE );

            // Filter group.
            // -------------
        hEdit = GetDlgItem(hDlg, IDC_SELECT_FILTER_BTN);
        EnableWindow( hEdit, FALSE );

        hEdit = GetDlgItem(hDlg, IDC_DESELECT_FILTER_BTN);
        EnableWindow( hEdit, FALSE );

        hEdit = GetDlgItem(hDlg, IDC_SELECT_FILTERS_DONE);
        EnableWindow( hEdit, FALSE );

        // Disable the "view container" button.
        hEdit = GetDlgItem(hDlg, IDOK);
        EnableWindow( hEdit, FALSE );

        // Disable the "configure filter" button.
        hEdit = GetDlgItem(hDlg, IDC_CONFIG_FILTER_BTN);
        EnableWindow( hEdit, FALSE );

        // Disable the "View selected filters" button.
        hEdit = GetDlgItem(hDlg, IDC_VIEW_SEL_FILTERS_BTN);
        EnableWindow( hEdit, FALSE );

        return(TRUE);


    case WM_CLOSE:
        EndDialog( hDlg, IDCANCEL );
        return(TRUE);


    case WM_SYSCOLORCHANGE:
        Ctl3dColorChange();
        return(TRUE);


    case WM_LOGIN_MSG:
        // Establish connection to datasource.
        // Done via the Login dialogue.
        // ====================================
        DialogBox( _hInstance,
                   MAKEINTRESOURCE(IDD_LOGIN),
                   hDlg,
                   (DLGPROC)LoginDlg );

        stat = SmsDataSourceConnect( &gdsParams, &ghConnect );
        if (stat != SMS_OK) {
            wsprintf(szMsg, "DataSourceConnect fails: %d", stat);
            MessageBox(hDlg, szMsg, "Problem here", MB_OK);

        } else {
            // Enable "select container" button.
            hEdit = GetDlgItem(hDlg, IDC_SELECT_CONTAINER_BTN);
            EnableWindow( hEdit, TRUE );
        }
        return(TRUE);

    case WM_COMMAND:

        switch (wParam) {

        case IDC_SELECT_CONTAINER_BTN:
            // This takes the current selection from the avail containers
            // list and puts it in the selected container control.
            hEdit = GetDlgItem(hDlg, IDC_AVAIL_CONTAINER_LIST);
            index = SendMessage(hEdit, LB_GETCURSEL, 0, 0);
            gpCInfo = pContainerList[index];

            hEdit = GetDlgItem(hDlg, IDC_SELECTED_CONTAINER);
            SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)gpCInfo->pszTag);

            // Enable the container done button.
            hEdit = GetDlgItem(hDlg, IDC_SELECT_CONTAINER_DONE);
            EnableWindow( hEdit, TRUE );

            // Disable the "Connect" button.
            hEdit = GetDlgItem(hDlg, IDC_CONNECT);
            EnableWindow( hEdit, FALSE );

            return(TRUE);


        case IDC_SELECT_CONTAINER_DONE:

            // Disable the "Select container" button and enable the
            // "Select filters" button.
            hEdit = GetDlgItem(hDlg, IDC_SELECT_CONTAINER_BTN);
            EnableWindow( hEdit, FALSE );

            // Disable container done btn.
            hEdit = GetDlgItem(hDlg, IDC_SELECT_CONTAINER_DONE);
            EnableWindow( hEdit, FALSE );

            // Enable the filters buttons.
            // ---------------------------
            hEdit = GetDlgItem(hDlg, IDC_SELECT_FILTER_BTN);
            EnableWindow( hEdit, TRUE );

            hEdit = GetDlgItem(hDlg, IDC_SELECT_FILTERS_DONE);
            EnableWindow( hEdit, TRUE );



            // Open the container.
            // -------------------
            stat = SmsOpenContainer( gpCInfo->dwTag, ghConnect, &ghContainer );
            if (stat != SMS_OK) {
                wsprintf(szMsg, "bad return from OpenContainer: %d", stat);
                MessageBox(hDlg, szMsg, "Badness", MB_OK );
            }

            return(TRUE);


        case IDC_SELECT_FILTER_BTN:
            // "Select filter" button.
            // This button is grayed-out until a container has
            // been selected.

            // Take the currently selected filter from the
            // available filter listbox and add it to the selected
            // filters listbox.
            hEdit = GetDlgItem(hDlg, IDC_AVAIL_FILTER_LIST);
            index = SendMessage(hEdit, LB_GETCURSEL, 0, 0);
            pF = &gpAvailFilterList[index];

            hEdit = GetDlgItem(hDlg, IDC_SELECTED_FILTERS);
            index = SendMessage(hEdit, LB_ADDSTRING, 0, (LPARAM)pF->szTag);

            // Highlight this selection in the selected box.
            SendMessage(hEdit, LB_SETCURSEL, (WPARAM)index, 0 );


            // Add the filter entry to a list of filters that we
            // keep handy. Maintain the index for easier access.
            //NOTE: remember to free it all.
            pMyFilter = new MY_FILTER_INFO;
            pMyFilter->pF = pF;
            pMyFilter->hFilter = NULL;
            aFilters.Add( (CObject *)pMyFilter );

            // Enable the deselect button.
            // ---------------------------
            hEdit = GetDlgItem(hDlg, IDC_DESELECT_FILTER_BTN);
            EnableWindow( hEdit, TRUE );

            // And the "configure filter" button.
            // ----------------------------------
            hEdit = GetDlgItem(hDlg, IDC_CONFIG_FILTER_BTN);
            EnableWindow( hEdit, TRUE );

            // Enable the "selected filters" label and combo.
            hEdit = GetDlgItem(hDlg, IDC_SELECTED_FILTERS);
            EnableWindow( hEdit, TRUE );

            return(TRUE);


        case IDC_DESELECT_FILTER_BTN:
            // Remove the current item from the selected filters listbox.
            hEdit = GetDlgItem(hDlg, IDC_SELECTED_FILTERS);
            index = SendMessage(hEdit, LB_GETCURSEL, 0, 0);
            SendMessage(hEdit, LB_DELETESTRING, (WPARAM)index, 0);

            // Remove this filter from the selected filters list.
            pMyFilter = (MY_FILTER_INFO *)aFilters.GetAt( index );
            delete pMyFilter;
            pMyFilter = NULL;
            aFilters.RemoveAt( index );

            // Select the previous one in the list.
            // If this was the first (index = 0) then leave index alone
            // else decrement it.
            if (index > 0) {
                index--;
            }
            SendMessage(hEdit, LB_SETCURSEL, (WPARAM)index, 0);

            // Check if we need to disable any buttons.
            // If the selected filters listbox is now empty disable
            // the "deselect" and "configure" filter buttons.
            // -----------------------------------------------------
            index = SendMessage(hEdit, LB_GETCOUNT, 0, 0);
            if (index == 0) {
                // deselect button.
                // ---------------------------
                hEdit = GetDlgItem(hDlg, IDC_DESELECT_FILTER_BTN);
                EnableWindow( hEdit, FALSE );

                // configure filter button.
                // ----------------------------------
                hEdit = GetDlgItem(hDlg, IDC_CONFIG_FILTER_BTN);
                EnableWindow( hEdit, FALSE );
            }


            return(TRUE);


        case IDC_CONFIG_FILTER_BTN:
            // Call a dialogue to handle this.

            // Retrieve the filter and pass it in a global so that
            // the dlgproc can use it.
            hEdit = GetDlgItem(hDlg, IDC_SELECTED_FILTERS);
            index = SendMessage(hEdit, LB_GETCURSEL, 0, 0);
            gpMyFilter = (MY_FILTER_INFO *)aFilters[index];

            reply = DialogBox(  _hInstance,
                                MAKEINTRESOURCE(IDD_CONFIG_FILTER),
                                hDlg,
                                (DLGPROC)ConfigFilterDlg );

            //LATER: put in cancel btn
            return(TRUE);


        case IDC_VIEW_SEL_FILTERS_BTN:
            // User has requested to view filters that have been
            // applied to the container.
            // =================================================
            DialogBox(  _hInstance,
                        MAKEINTRESOURCE(IDD_VIEW_SEL_FILTERS_DLG),
                        hDlg,
                        (DLGPROC)ViewSelFiltersDlg );
            return(TRUE);



        case IDC_SELECT_FILTERS_DONE:
            // Check that all of the filters that we've selected have been
            // configured, warning if not.
            // (NOTE: we should put in a check mark next to selected
            // filters to show if they've been configured.)
            // It is only at this point that we can actually apply the
            // filter to the container.

            // Loop through the filters.
            for (dwI = 0; dwI < (DWORD)aFilters.GetSize(); dwI++) {
                pMyFilter = (MY_FILTER_INFO *)aFilters[dwI];
                if (pMyFilter->hFilter == NULL) {
                    wsprintf(szMsg, "A %s has not been configured,\ndo you want to configure it now?",
                                    pMyFilter->pF->szTag);
                    reply = MessageBox( hDlg,
                                        szMsg,
                                        "Warning",
                                        MB_ICONEXCLAMATION| MB_YESNO );
                    if (reply == IDYES) {
                        // We want to configure this filter now.
                        // Stubbed: needs implementing.
                        MessageBox(hDlg, "Not implemented", "Go away", MB_OK);
                    }

                } else {
                    // We can apply the filter now.
                    hFilter = pMyFilter->hFilter;
                    stat = SmsSetFilter( ghContainer, hFilter );
                    SmsCloseFilter( hFilter);
                    if (stat != SMS_OK) {
                        wsprintf(szMsg, "SetFilter for %s failed: %d",
                                            pMyFilter->pF->szTag, stat);
                        MessageBox(hDlg, szMsg, "Warning", MB_OK);
                    }
                }
            }

            // Must grey-out all other filter controls.
            hEdit = GetDlgItem(hDlg, IDC_SELECT_FILTERS_DONE);
            EnableWindow( hEdit, FALSE );

            hEdit = GetDlgItem(hDlg, IDC_SELECT_FILTER_BTN);
            EnableWindow( hEdit, FALSE );

            hEdit = GetDlgItem(hDlg, IDC_DESELECT_FILTER_BTN);
            EnableWindow( hEdit, FALSE );

            hEdit = GetDlgItem(hDlg, IDC_CONFIG_FILTER_BTN);
            EnableWindow( hEdit, FALSE );


            // The view container btn enabled only when filter done btn
            // clicked.
            hEdit = GetDlgItem(hDlg, IDOK);
            EnableWindow( hEdit, TRUE );

            // Enable the "Connect" button.
            hEdit = GetDlgItem(hDlg, IDC_CONNECT);
            EnableWindow( hEdit, TRUE );

            // Enable the "View selected filters" button.
            // We only want to do this if we have any filters.
            if (aFilters.GetSize() > 0) {
                hEdit = GetDlgItem(hDlg, IDC_VIEW_SEL_FILTERS_BTN);
                EnableWindow( hEdit, TRUE );
            }

            return(TRUE);

        case IDOK:
            // This is the "View Container" button.

            // Tell the container to populate himself.
            stat = SmsPopulate( ghContainer, POP_SYNC, NULL );
            if (stat != SMS_OK) {
                wsprintf(szMsg, "bad return from Populate: %d", stat);
                MessageBox(hDlg, szMsg, "Badness", MB_OK );
            }

            // Enter the container view dialogue.
            DialogBox(  _hInstance,
                        MAKEINTRESOURCE(IDD_THE_CONTAINER),
                        hDlg,
                        (DLGPROC)ContainerViewDlg );

            SmsCloseContainer( ghContainer );

            // Log off from data source.
            SmsDataSourceDisconnect( ghConnect );


            ////////////////////////////////////////////////////
            //  Ready for restart.
            ////////////////////////////////////////////////////

            // Free all global and static data.
            // -------------------------------------------------
            for (index = 0; index < aFilters.GetSize(); index ++) {
                pMyFilter = (MY_FILTER_INFO *)aFilters.GetAt( index );
                delete pMyFilter;
                pMyFilter = NULL;
            }
            aFilters.RemoveAll();

            pCont = NULL;
            pF = NULL;
            gpCInfo = NULL;
            ghConnect = NULL;

            // Delete any strings that were in the selected
            // container and filter edit controls.
            // -------------------------------------------------
            SetDlgItemText( hDlg, IDC_SELECTED_CONTAINER, "" );
            hEdit = GetDlgItem(hDlg, IDC_SELECTED_FILTERS);
            SendMessage( hEdit, LB_RESETCONTENT, 0, 0 );

            // Disable all controls except Login.
            // -------------------------------------------------
                // Container group
                // ---------------
            hEdit = GetDlgItem(hDlg, IDC_SELECT_CONTAINER_BTN);
            EnableWindow( hEdit, FALSE );

            hEdit = GetDlgItem(hDlg, IDC_SELECT_CONTAINER_DONE);
            EnableWindow( hEdit, FALSE );

                // Filter group.
                // -------------
            hEdit = GetDlgItem(hDlg, IDC_SELECT_FILTER_BTN);
            EnableWindow( hEdit, FALSE );

            hEdit = GetDlgItem(hDlg, IDC_DESELECT_FILTER_BTN);
            EnableWindow( hEdit, FALSE );

            hEdit = GetDlgItem(hDlg, IDC_SELECT_FILTERS_DONE);
            EnableWindow( hEdit, FALSE );

            // Disable the "view container" button.
            hEdit = GetDlgItem(hDlg, IDOK);
            EnableWindow( hEdit, FALSE );

            // Disable the "configure filter" button.
            hEdit = GetDlgItem(hDlg, IDC_CONFIG_FILTER_BTN);
            EnableWindow( hEdit, FALSE );

            // Disable the "View selected filters" button.
            hEdit = GetDlgItem(hDlg, IDC_VIEW_SEL_FILTERS_BTN);
            EnableWindow( hEdit, FALSE );

            // Reset listbox selections.
            // -------------------------------------------------
            // Reset listbox selections to first in list.
            hEdit = GetDlgItem(hDlg, IDC_AVAIL_CONTAINER_LIST);
            SendMessage(hEdit, LB_SETCURSEL, 0, 0);

            hEdit = GetDlgItem(hDlg, IDC_AVAIL_FILTER_LIST);
            SendMessage(hEdit, LB_SETCURSEL, 0, 0);


            ////////////////////////////////////////////////////

            // Enable the Login button so use can try again.
            hEdit = GetDlgItem( hDlg, IDC_CONNECT );
            EnableWindow( hEdit, TRUE );

            return(TRUE);


        case IDC_CONNECT:
            // This is the "Connect" button.
            SendMessage( hDlg, WM_LOGIN_MSG, 0, 0 );
            return(TRUE);


        case IDC_ALL_DONE:
            // This is the "done" button.
            EndDialog( hDlg, IDOK );

            // And now terminate.
            return(TRUE);
        }
    }

    return(FALSE);

}




// ====================================================================
//
//  This is the view container dialogue that is brought up in response
//  to the "view container" button in the main dialogue.
//
//  We have a listbox for the sub-folders, which we need to populate.
//  We also have a group box containing details about the container.
//
//  The container handle is held in a global "ghContainer".
//
// ====================================================================

extern "C" BOOL CALLBACK ContainerViewDlg(
                                    HWND hDlg,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam)
{

    // We need to fill in the container tag and the number of folders.
    // The first we'll put into a global for now (from MainDlg), the
    // latter is currently unavailable so we'll put in some gunk.

    HWND hEdit;
    static DWORD ctFolders = 0;
    SMS_STATUS stat;
    static CStringArray asID;           // Array of CStrings for IDs.
    CString sID;
    char szID[SMS_DATA_BUFF_SIZE+1];    // buffer to read in folder ID.
    DWORD dwI;
    HANDLE handle;                      // Temp holds handle of folder.
    int index;
    static CDWordArray folderList;      // List of opened folder handles.


    switch (message) {

    case WM_INITDIALOG:
        // Dialogue initialisation.

        // We have to open all the sub-folders, holding their
        // handles in some array. For each folder we want to extract
        // and display in the listbox it's ID.
        // NOTE: GetFolderCount not yet imnplemented for containers.
        // Instead I'll do GetNextFolder till I run out of folders.
        ctFolders = 0;

        for (ctFolders = 0; 1; ctFolders++) {

            stat = SmsGetNextFolder( ghContainer, F_ANY, &handle );
            if (stat != SMS_OK) {
                // assume no more folders for now
                break;
            }
            // Save the handle.
            folderList.Add( (DWORD)handle );
        }


        // Get the ID of each folder and insert into listbox.
        // --------------------------------------------------
        hEdit = GetDlgItem(hDlg, IDC_ID_LB);

        for (dwI = 0; dwI < ctFolders; dwI++) {

            // Retrieve the ID and store in the listbox.
            handle = (HANDLE)folderList.GetAt( dwI );
            stat = SmsGetFolderID( handle, szID );
            if (stat != SMS_OK) {
                wsprintf(szMsg, "GetID [%d] fails: %d", dwI, stat);
                MessageBox(hDlg, szMsg, "API problem", MB_OK);
            }
            asID.SetAtGrow( dwI, (CString)szID );

            SendMessage(hEdit, LB_ADDSTRING, 0, (LPARAM)szID);
        }


        // Select the first one in the list.
        SendMessage(hEdit, LB_SETCURSEL, 0, 0);


        // Set container name and number of folders.
        // -----------------------------------------
        SetDlgItemText( hDlg, IDC_WHAT_CONTAINER, (LPCSTR)gpCInfo->pszTag );
        SetDlgItemInt( hDlg, IDC_CTR_NUM_FOLDERS, ctFolders, FALSE );

        // If no folders disable the "View folder" button.
        // -----------------------------------------------
        if (ctFolders == 0) {
            hEdit = GetDlgItem(hDlg, IDOK);
            EnableWindow( hEdit, FALSE );
        }

        return(TRUE);


    case WM_CLOSE:
        // Close all folders.
        for (dwI = 0; dwI < ctFolders; dwI++) {
            handle = (HANDLE)folderList.GetAt( dwI );
            SmsCloseFolder( handle );
        }
        folderList.RemoveAll();

        // Clear the ID string array.
        asID.RemoveAll();

        EndDialog( hDlg, IDCANCEL );
        return(TRUE);


    case WM_SYSCOLORCHANGE:
        Ctl3dColorChange();
        return(TRUE);


    case WM_COMMAND:

        switch (wParam) {

        case IDOK:
            // Get the current selection and store it in a global
            // so that it can be picked up by FolderViewDlg.
            // --------------------------------------------------
            hEdit = GetDlgItem(hDlg, IDC_ID_LB);
            index = SendMessage(hEdit, LB_GETCURSEL, 0, 0);
            ghFolder = (HANDLE)folderList.GetAt( index );

            // Now we rewind the folder. This means that we can re-enumerate
            // the folder's properties (ID, scalars etc).
            SmsRewind( ghFolder, RW_ALL );

            // Enter the folder view dialogue.
            DialogBox(  _hInstance,
                        MAKEINTRESOURCE(IDD_FOLDER_VIEW),
                        hDlg,
                        (DLGPROC)FolderViewDlg );

            return(TRUE);

        case IDC_DONE:
            // We're done with this container. Close all the folders
            // and the container.
            for (dwI = 0; dwI < ctFolders; dwI++) {
                handle = (HANDLE)folderList.GetAt( dwI );
                // Close the folder
                SmsCloseFolder( handle );
            }
            folderList.RemoveAll();


            // Clear the ID string array.
            asID.RemoveAll();


            // Container closed in calling dlg.

            // This returns us to the previous dialogue.
            EndDialog(hDlg, IDOK);
            return(TRUE);
        }
    }

    return(FALSE);



}  /* ContainerViewDlg */


// ====================================================================
//
//  This is the view folder dialogue that is brought up in response to
//  the "view folder" button in the container dialogue.
//
//  We have a listbox for the sub-folders, which we need to populate.
//  We also have a group box containing details about the folder.
//
//  The handle to the current folder has been placed in the ghFolder
//  global.
//
//  When this dlgproc is entered via INITDIALOG we create a folder
//  frame that contains information that we have gleaned from the
//  folder, including the folder's handle. This frame is stacked.
//  When the 'view sub-folder" button is pressed we will simulate this
//  same action. A 'Done" button press causes us to free the current
//  frame and reload from the top of stack (if any).
//  The WM_CLOSE causes us to walk the stack frame freeing all frames.
//
// ====================================================================

// Macro for easier checking of returns from the APIs.
// Not sure about the NO_MORE_DATA. Check it.
#define CHKIT(h, str) if (stat != SMS_OK && stat != SMS_MORE_DATA && stat != SMS_NO_MORE_DATA) { \
    wsprintf(szMsg, "Handle: %08X %s fails: %d", h, str, stat); \
    MessageBox(hDlg, szMsg, "API Error", MB_OK); return((CFrame *)NULL); }


extern "C" BOOL CALLBACK FolderViewDlg(
                                    HWND hDlg,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam)
{
    HWND hEdit;
    DWORD dwI;                          // Loop index.

    int index;
    CString sID;                        // Temp sub-folder's ID.
    static CFrame *pf = NULL;           // Current stack frame.
    char *pszTmp;
    char szBuff[SMS_DATA_BUFF_SIZE+1];  // Just for setting window title.

    static CFrameStack frameStack(hDlg);

    switch (message) {

    case WM_INITDIALOG:
        // Dialogue initialisation.

        // Set the window title to say "View of folder: <name>".
        SmsGetFolderID( ghFolder, szBuff );
        wsprintf(szMsg, "View of folder: %s", szBuff);
        SetWindowText( hDlg, szMsg );

        // Extract requisite information about the folder:
        // ID, type (use tag), scalar count, folder count, folder type count.
        pf = CreateFolderFrame( hDlg, ghFolder );
        if (pf) {
            // And display it.
            DisplayFolderFrame( hDlg, pf );

        } else {
            // This is an error.
            wsprintf(szMsg, "CreateFolderFrame failed for handle %08X", ghFolder);
            MessageBox(hDlg, szMsg, "An error", MB_OK);
            EndDialog( hDlg, IDCANCEL );
        }

        return(TRUE);


    case WM_CLOSE:
        // Delete current frame.
        // =====================
        // remove the ID strings from the string array
        for (dwI = 0; dwI < (DWORD)pf->aszID.GetSize(); dwI++) {
            pszTmp = (char *)pf->aszID[dwI];
            delete pszTmp;
        }
        // remove the handles
        delete pf->phFolders;

        delete pf;
        pf = NULL;

        // Free all previous frames.
        // =========================
        while (pf = frameStack.pop()) {
            // remove the ID strings from the string array
            for (dwI = 0; dwI < (DWORD)pf->aszID.GetSize(); dwI++) {
                pszTmp = (char *)pf->aszID[dwI];
                delete pszTmp;
            }
            // Remove the handles
            delete pf->phFolders;
            ghFolder = pf->hFolder;
            delete pf;

        }
        EndDialog( hDlg, IDCANCEL );
        return(TRUE);


    case WM_SYSCOLORCHANGE:
        Ctl3dColorChange();
        return(TRUE);


    case WM_COMMAND:

        switch (wParam) {

        case IDC_VIEW_FOLDER:
            // We're going down a level so stack our frame.
            frameStack.push( pf );

            // Get the current selection index. Use this to locate
            // the folder's handle.
            // We must save the existing folder handle in the frame
            // and re-instate it when we return.

            hEdit = GetDlgItem( hDlg, IDC_SUBFOLDER_LIST );
            index = SendMessage(hEdit, LB_GETCURSEL, 0, 0);
            ghFolder = pf->phFolders[index];

            // First clear the listbox entries (should clear other entries
            // as well, but I think they'll just get overwritten.)
            SendMessage(hEdit, LB_RESETCONTENT, 0, 0);

            // Create a new stack frame with all the details
            // that we did in the INITDLG.
            pf = CreateFolderFrame( hDlg, ghFolder );
            if (pf) {
                // And display it.
                DisplayFolderFrame( hDlg, pf );

            } else {
                // This is an error.
                wsprintf(szMsg, "CreateFolderFrame failed for handle %08X", ghFolder);
                MessageBox(hDlg, szMsg, "An error", MB_OK);
                EndDialog( hDlg, IDCANCEL );
            }


            // Select the first one in the list and set focus here.
            SendMessage(hEdit, LB_SETCURSEL, 0, 0);
            SetFocus(hEdit);

            return(TRUE);


        case IDC_VIEW_SCALARS:
            // So we can enumerate scalars from the beginning.
            SmsRewind( ghFolder, RW_ALL );

            DialogBox( _hInstance,
                       MAKEINTRESOURCE(IDD_SCALARS),
                       hDlg,
                       (DLGPROC)ScalarViewDlg );
            return(TRUE);


        case IDC_VIEW_EXPRESSION:
            // So we can enumerate tokens in expression from the beginning.
            SmsRewind( ghFolder, RW_ALL );

            DialogBox( _hInstance,
                       MAKEINTRESOURCE(IDD_EXPRESSION),
                       hDlg,
                       (DLGPROC)ExpressionViewDlg );
            return(TRUE);



        case IDC_BACK:
            // This will take us back one level.
            // We have to free all data from the current stack frame
            // and then restore the previous one.
            // When the stack frame is empty we return to the previous
            // dialogue.

            // Delete current frame.
            // =====================
            // remove the ID strings from the string array
            for (dwI = 0; dwI < (DWORD)pf->aszID.GetSize(); dwI++) {
                pszTmp = (char *)pf->aszID[dwI];
                delete pszTmp;
            }
            // remove the handles
            delete pf->phFolders;

            delete pf;
            pf = NULL;


            // Restore the previous frame.
            // ===========================
            pf = frameStack.pop();
            if (pf == NULL) {
                // Nothing there, return to previous dialogue.
                EndDialog(hDlg, IDOK);
                return(TRUE);
            }


            DisplayFolderFrame( hDlg, pf );
            // restore folder handle
            ghFolder = pf->hFolder;

            return(TRUE);
        }
    }

    return(FALSE);

}   /* FolderViewDlg */



// ====================================================================
//
//  Creates a frame for this folder.
//  Note: We could check if we have already stacked this folder.
//
// ====================================================================

CFrame *CreateFolderFrame( HWND hDlg, HANDLE hFolder )
{
    HANDLE hSubFolder = NULL;           // Temp reference to sub-folder.
    CFrame *pFrame = new CFrame;
    SMS_STATUS stat;


    SmsRewind( hFolder, RW_ALL );

    // Save the folder's handle.
    pFrame->hFolder = ghFolder;

    stat = SmsGetFolderID( hFolder, pFrame->szFolderID );
    CHKIT(hFolder, "GetFolderID");

    stat = SmsGetFolderType( hFolder, &pFrame->fType, pFrame->szfType );
    CHKIT(hFolder, "GetFolderType");

    stat = SmsGetScalarCount( hFolder, &pFrame->ctScalars );
    CHKIT(hFolder, "GetScalarCount");

    stat = SmsGetFolderCount( hFolder, F_ANY, &pFrame->ctFolders );
    CHKIT(hFolder, "GetFolderCount");

    stat = SmsEnumFolderTypes( hFolder, NULL, &pFrame->ctFolderTypes );
    CHKIT(hFolder, "EnumFolderTypes");

    // 02-May-96. Add expression display (inventory folder).
    stat = SmsGetTokenCount( hFolder, &pFrame->ctTokens );
//    CHKIT(hFolder, "GetTokenCount");


    // Enumerate the sub-folders.
    // -----------------------------------------
    char szBuff[SMS_DATA_BUFF_SIZE+1];

    // Allocate a handle for each folder.
    pFrame->phFolders = (HANDLE *)new HANDLE[pFrame->ctFolders];
    char *pszTmp;

    DWORD dwI;
    for (dwI = 0; dwI < pFrame->ctFolders; dwI++) {
        // Rewind the folder - just in case.

        stat = SmsGetNextFolder( hFolder, F_ANY, &hSubFolder );
        CHKIT(hFolder, "GetNextFolder");
        pFrame->phFolders[dwI] = hSubFolder;

        // Get folder's ID and add it to our cstring array and to the listbox.
        // We want it saved since we will have to redraw the listbox when
        // drilling down and then up in the folder list.
        stat = SmsGetFolderID( hSubFolder, szBuff );
        CHKIT(hFolder, "GetFolderID");
        pszTmp = new char[strlen(szBuff)+1];        // deleted when we do a BACK or CLOSE
        strcpy(pszTmp, szBuff);
        pFrame->aszID.Add( (CObject *)pszTmp );

    }

    return(pFrame);

}  /* CreateFolderFrame */




// ====================================================================
//
//  Display the given folder frame. This is part of the Folder view
//  dialogue.
//
// ====================================================================

void DisplayFolderFrame( HWND hDlg, CFrame *pFrame )
{
    HWND hEdit;

    // First of all lets clear the listbox (whether needs it or not).
    hEdit = GetDlgItem( hDlg, IDC_SUBFOLDER_LIST );
    SendMessage(hEdit, LB_RESETCONTENT, 0, 0);


    SetDlgItemText( hDlg, IDC_FOLDERID, (LPCSTR)pFrame->szFolderID);
    SetDlgItemText( hDlg, IDC_FOLDERTYPE, (LPCSTR)pFrame->szfType);
    SetDlgItemInt( hDlg,  IDC_FOLDERSC_CT, pFrame->ctScalars, FALSE);
    SetDlgItemInt( hDlg,  IDC_FOLDERFOLDER_CT, pFrame->ctFolders, FALSE);
    SetDlgItemInt( hDlg,  IDC_FOLDERFT_CT, pFrame->ctFolderTypes, FALSE);


    // Display the sub-folder IDs.
    // -----------------------------------------
    hEdit = GetDlgItem( hDlg, IDC_SUBFOLDER_LIST );
    char *pszTmp;

    for (DWORD dwI = 0; dwI < pFrame->ctFolders; dwI++) {

        pszTmp = (char *)pFrame->aszID.GetAt( dwI );
        SendMessage(hEdit, LB_ADDSTRING, 0, (LPARAM)pszTmp);
    }

    // If there are no sub-folders or no scalars then
    // disable the appropriate buttons.
    // -----------------------------------------------------
    hEdit = GetDlgItem( hDlg, IDC_VIEW_SCALARS );
    if (pFrame->ctScalars == 0) {
        EnableWindow( hEdit, FALSE );
    } else {
        EnableWindow( hEdit, TRUE );
    }

    hEdit = GetDlgItem( hDlg, IDC_VIEW_FOLDER );
    if (pFrame->ctFolders == 0) {
        EnableWindow( hEdit, FALSE );
    } else {
        EnableWindow( hEdit, TRUE );
    }


    // Select the first one in the list and set focus here.
    hEdit = GetDlgItem( hDlg, IDC_SUBFOLDER_LIST );
    SendMessage(hEdit, LB_SETCURSEL, 0, 0);

    // [02-May-96] If there are no tokens in this folder (ie it doesn't
    // have an expression) then disable the 'View expression' button.
    // ----------------------------------------------------------------
    hEdit = GetDlgItem( hDlg, IDC_VIEW_EXPRESSION );
    if (pFrame->ctTokens == 0) {
        EnableWindow( hEdit, FALSE );
    } else {
        EnableWindow( hEdit, TRUE );
    }
}


// ==========================================================================
//
//  Dialogue proc for the scalar view.
//
//  We need the hFolder, and preferably it's ID as well. We can put that
//  in the dlg title.
//  The hFolder is needed since we're going to enumerate its scalars.
//  We'll construct 2 string arrays, one for the scalar name, the other
//  for the value (maybe put in type as well later).
//
// ==========================================================================

extern "C" BOOL CALLBACK ScalarViewDlg(
                                    HWND hDlg,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam)
{

    HWND hEditName;                 // Explicit handle to name listbox.
    HWND hEditVal;                  // Explicit handle to value listbox.
    HWND hEditType;                 // Explicit handle to type listbox.
    int index;
    SCALAR scalar;
    char szName[SMS_DATA_BUFF_SIZE+1];      // Scalar name.
    char szValue[SMS_DATA_BUFF_SIZE+1];     // String value.
    BYTE byValue[SMS_DATA_BUFF_SIZE];       // Binary value.
    scalar.pszName  = szName;
    scalar.pszValue = szValue;
    scalar.pValue   = byValue;
    SMS_STATUS stat;
    char szBuff[SMS_DATA_BUFF_SIZE+1];

    char *pszVal;                   // Point to scalar's value.
    char *pszType;                  // Point to scalar's type.

    CTime tTime;                    // For time scalars
    CString sTime;                  //  ditto


    switch (message) {

    case WM_INITDIALOG:
        // Dialogue initialisation.

        // 1. Set the window title to say "Scalars for folder <name>".
        SmsGetFolderID( ghFolder, szBuff );
        wsprintf(szMsg, "Scalars for folder %s", szBuff);
        SetWindowText( hDlg, szMsg );

        // 2. Enumerate the scalars storing the strings (strings only at
        // the moment) in 2 string lists: name and value.

        hEditName = GetDlgItem(hDlg, IDC_SCNAME_LB);
        hEditVal  = GetDlgItem(hDlg, IDC_SCVAL_LB);
        hEditType = GetDlgItem(hDlg, IDC_SCTYPE_LB);

        while (1) {
            scalar.dwLen = sizeof(szValue)-1;

            stat = SmsGetNextScalar( ghFolder, &scalar );
            if (stat != SMS_OK) {
                break;
            }

            // Copy the name and value into the listboxes - don't think I'll
            // bother with saving them though.


            switch (scalar.scType) {
            case SCALAR_STRING:
                pszVal = scalar.pszValue;
                pszType = "String";
                break;

            case SCALAR_INT:
                // Convert to string.
                wsprintf(szBuff, "%d", scalar.dwValue);
                pszVal = szBuff;
                pszType = "Integer";
                break;

            case SCALAR_TIME:
                // Check if we have a string equivalence. If so use it.
                if (scalar.bStringEquivalence) {
                    pszVal = scalar.pszValue;

                } else {
                    // Use time functions to make a string out of it.
                    // NOTE: we really need to get rid of trailing newline.
                    tTime = scalar.tValue;
                    sTime = tTime.Format( "%m/%d/%y %I:%M %p" );
                    pszVal = (char *)(const char *)sTime;
                }
                pszType = "Time";
                break;

            case SCALAR_BINARY:
                // Just print out its length.
                pszType = "Binary";
                wsprintf( szBuff, "Length of binary data: %ld", scalar.dwLen);
                pszVal = szBuff;
                break;

            default:
                wsprintf(szBuff, "UNKNOWN TYPE");
                pszVal = szBuff;
                pszType = "Unknown type";
                break;
            }

            // Scalar name.
            SendMessage(hEditName, LB_ADDSTRING, 0, (LPARAM)scalar.pszName);

            // Scalar type.
            SendMessage(hEditType, LB_ADDSTRING, 0, (LPARAM)pszType);

            // Scalar value.
            SendMessage(hEditVal,  LB_ADDSTRING, 0, (LPARAM)pszVal);


        }

        // Set current selections to the first in each list.
        SendMessage(hEditName, LB_SETCURSEL, (WPARAM)0, 0);
        SendMessage(hEditType, LB_SETCURSEL, (WPARAM)0, 0);
        SendMessage(hEditVal,  LB_SETCURSEL, (WPARAM)0, 0);

        // Set focus on this control.
        SetFocus(hEditName);

        return(TRUE);


    case WM_CLOSE:
        // Do I need to delete the strings from the listboxes??
        EndDialog( hDlg, IDCANCEL );
        return(TRUE);

    case WM_SYSCOLORCHANGE:
        Ctl3dColorChange();
        return(TRUE);


    case WM_COMMAND:

        // Whatever listbox is selected we want to select the
        // corresponding entry in the other.
        if (HIWORD(wParam) == LBN_SELCHANGE) {

            index = SendMessage((HWND)lParam, LB_GETCURSEL, 0, 0);


            hEditName = GetDlgItem(hDlg, IDC_SCNAME_LB);
            hEditType = GetDlgItem(hDlg, IDC_SCTYPE_LB);
            hEditVal  = GetDlgItem(hDlg, IDC_SCVAL_LB);

            // Select the corresponding entry all listboxes.
            SendMessage(hEditName, LB_SETCURSEL, (WPARAM)index, 0);
            SendMessage(hEditType, LB_SETCURSEL, (WPARAM)index, 0);
            SendMessage(hEditVal,  LB_SETCURSEL, (WPARAM)index, 0);

            return(TRUE);
        }


        switch (wParam) {

        case IDOK:
            // Do I need to delete the strings from the listboxes??
            EndDialog(hDlg, IDOK);
            return(TRUE);

        }
    }

    return(FALSE);

}  /* ScalarViewDlg */


// ==========================================================================
//
//  Dialogue proc for the expression view.
//##//
//  We need the hFolder, and preferably it's ID as well. We can put that
//  in the dlg title.
//  The hFolder is needed since we're going to enumerate its scalars.
//  We'll construct 2 string arrays, one for the scalar name, the other
//  for the value (maybe put in type as well later).
//
// ==========================================================================

extern "C" BOOL CALLBACK ExpressionViewDlg(
                                    HWND hDlg,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam)
{

    HWND hEditToken;                // Explicit handle to token listbox.
    char szBuff[SMS_DATA_BUFF_SIZE+1];  // Just for setting window title.
    DWORD dwLoop = 0;


    switch (message) {

    case WM_INITDIALOG:
        // Dialogue initialisation.

        // 1. Set the window title to say "Expression for folder <name>".
        SmsGetFolderID( ghFolder, szBuff );
        wsprintf(szMsg, "Expression for folder %s", szBuff);
        SetWindowText( hDlg, szMsg );

        // 2. Enumerate the tokens storing them (ie their display strings)
        // into a string list.

        hEditToken = GetDlgItem(hDlg, IDC_TOKENS_LB);

        // Clear the token.
        // ================
        TOKEN Token;
        DWORD ctTokens;

        // Loop through its tokens, display the token string in the
        // edit control.
        // ========================================================
        SmsGetTokenCount( ghFolder, &ctTokens );
        for (dwLoop = 0; dwLoop < ctTokens; dwLoop++) {

            memset(&Token, 0, sizeof(TOKEN));
            Token.bIndent = 1;                  // Request indentation.
            // Get token.
            SmsGetToken( ghFolder, dwLoop, &Token );

            SendMessage(hEditToken, LB_ADDSTRING, 0, (LPARAM)Token.szTokenString);
        }


        // Set focus on this control.
        SetFocus(hEditToken);

        return(TRUE);


    case WM_CLOSE:
        // Do I need to delete the strings from the listboxes??
        EndDialog( hDlg, IDCANCEL );
        return(TRUE);

    case WM_SYSCOLORCHANGE:
        Ctl3dColorChange();
        return(TRUE);


    case WM_COMMAND:

        switch (wParam) {

        case IDOK:
            // Do I need to delete the strings from the listboxes??
            EndDialog(hDlg, IDOK);
            return(TRUE);

        }
#ifdef XXX
        // Whatever listbox is selected we want to select the
        // corresponding entry in the other.
        if (HIWORD(wParam) == LBN_SELCHANGE) {

            index = SendMessage((HWND)lParam, LB_GETCURSEL, 0, 0);


            hEditName = GetDlgItem(hDlg, IDC_SCNAME_LB);
            hEditType = GetDlgItem(hDlg, IDC_SCTYPE_LB);
            hEditVal  = GetDlgItem(hDlg, IDC_SCVAL_LB);

            // Select the corresponding entry all listboxes.
            SendMessage(hEditName, LB_SETCURSEL, (WPARAM)index, 0);
            SendMessage(hEditType, LB_SETCURSEL, (WPARAM)index, 0);
            SendMessage(hEditVal,  LB_SETCURSEL, (WPARAM)index, 0);

            return(TRUE);
        }
#else
        return(TRUE);
#endif  // XXX


        switch (wParam) {

        case IDOK:
            // Do I need to delete the strings from the listboxes??
            EndDialog(hDlg, IDOK);
            return(TRUE);

        }
    }

    return(FALSE);

}  /* ExpressionViewDlg */




// ====================================================================
//
// This is the dialogue that is brought up in response to the
// config filter button in the main dialogue.
//
//  A MY_FILTER_INFO struct is passed via a global. This
//  contains a description of the filter template (ie a FILTER_INFO
//  structure) and the handle of a particular filter. By examining
//  the filter info we determine how the filter's tokens are composed.

//  The dialogue itself has the group name controls set to not-
//  visible. If this is a Token2 then we make them visible.
//
//  For each token there is a name, a value and an operator.
//  I'll hard-code the operators for the moment.
//  Not all tokens need the value and operator, this should be
//  determined by the token processing.
//  The nature of the value is also dependent on the token, it's
//  (currently) either a DWORD or a string.
//
//  We create the filter and do the add tokens here. The filter
//  handle is stored in the MY_FILTER_INFO struct. When we
//  return the invoker of this dialogue will do a SetFilter.
//
// ====================================================================

extern "C" BOOL CALLBACK ConfigFilterDlg(
                                    HWND hDlg,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam)
{

    HWND hEdit;
    FILTER_INFO *pFltr = NULL;
    static MY_FILTER_INFO *pMyF;
    int index;
    SMS_STATUS stat;
    static HANDLE hFilter = NULL;
    ANDOR opAndOr;
    TOKEN Token;                        // Token to add into filter.

    // We only know what fields the filter supports when we check the
    // TOKEN_INFO structure. The fields there that contain strings
    // tell us a) that the field is used by the filter, and b) what
    // the label should be for that field.
    // For simplicity we have two dialogues, we use one dialogue proc
    // to process both. This is only because of the difficulties
    // involved in moving edit controls around.
    // Different filter types will use different combinations of the
    // edit controls.
    // ===============================================================
    static BOOL bHasName;
    static BOOL bHasValue;
    static BOOL bHasGroupClass;
    static BOOL bHasArch;
    static BOOL bHasOp;
    static BOOL bHasAttribute;

    int iLoop;                          // Loop index.

    switch (message) {

    case WM_INITDIALOG:
        // Dialogue initialisation.
        pMyF = gpMyFilter;
        pFltr = pMyF->pF;

        // Look at the filter to determine what fields it will use.
        // make the appropriate fields visible, and set their labels.
        // ==========================================================
        bHasName       = FALSE;
        bHasValue      = FALSE;
        bHasGroupClass = FALSE;
        bHasArch       = FALSE;
        bHasOp         = FALSE;
        bHasAttribute  = FALSE;

        // Clear the token.
        // ================
        memset(&Token, 0, sizeof(TOKEN));

        // Name.
        if (strlen(pFltr->szName)) {
            hEdit = GetDlgItem(hDlg, IDC_NAME_STATIC);
            SetWindowText( hEdit, pFltr->szName );
            ShowWindow( hEdit, SW_SHOWNORMAL );

            hEdit = GetDlgItem(hDlg, IDC_NAME);
            ShowWindow( hEdit, SW_SHOWNORMAL );
            bHasName = TRUE;
        }

        // Value.
        if (strlen(pFltr->szValue)) {
            hEdit = GetDlgItem(hDlg, IDC_VALUE_STATIC);
            SetWindowText( hEdit, pFltr->szValue );
            ShowWindow( hEdit, SW_SHOWNORMAL );

            hEdit = GetDlgItem(hDlg, IDC_VALUE);
            ShowWindow( hEdit, SW_SHOWNORMAL );
            bHasValue = TRUE;
        }

        // GroupClass.
        if (strlen(pFltr->szGroupClass)) {
            hEdit = GetDlgItem(hDlg, IDC_GROUPCLASS_STATIC);
            SetWindowText( hEdit, pFltr->szGroupClass );
            ShowWindow( hEdit, SW_SHOWNORMAL );

            hEdit = GetDlgItem(hDlg, IDC_GROUPCLASS);
            ShowWindow( hEdit, SW_SHOWNORMAL );
            bHasGroupClass = TRUE;
        }

        // AttributeName.
        if (strlen(pFltr->szAttributeName)) {
            hEdit = GetDlgItem(hDlg, IDC_ATTRIBUTE_STATIC);
            SetWindowText( hEdit, pFltr->szAttributeName );
            ShowWindow( hEdit, SW_SHOWNORMAL );

            hEdit = GetDlgItem(hDlg, IDC_ATTRIBUTE);
            ShowWindow( hEdit, SW_SHOWNORMAL );
            bHasAttribute = TRUE;
        }

        // Architecture.
        if (strlen(pFltr->szArchitecture)) {
            hEdit = GetDlgItem(hDlg, IDC_ARCHITECTURE_STATIC);
            SetWindowText( hEdit, pFltr->szArchitecture );
            ShowWindow( hEdit, SW_SHOWNORMAL );

            hEdit = GetDlgItem(hDlg, IDC_ARCHITECTURE);
            ShowWindow( hEdit, SW_SHOWNORMAL );
            bHasArch = TRUE;
        }

        // Operator.
        if (strlen(pFltr->szOperator)) {
            hEdit = GetDlgItem(hDlg, IDC_OPERATOR_STATIC);
            SetWindowText( hEdit, pFltr->szOperator );
            ShowWindow( hEdit, SW_SHOWNORMAL );

            hEdit = GetDlgItem(hDlg, IDC_OP_CB);
            ShowWindow( hEdit, SW_SHOWNORMAL );
            bHasOp = TRUE;
        }



        // Create the filter.
        // If all goes ok then this will be stored in
        // gpMyFilter, and used in the main dlg.
        // -----------------------------------------------------
        stat = SmsCreateFilter( pFltr->filterType, ghConnect, &hFilter );
        if (stat != SMS_OK) {
            wsprintf(szMsg, "OpenFilter fails: %d", stat);
            MessageBox(hDlg, szMsg, "Whoops", MB_OK);
        }


        // Insert the operators that we support into the combobox.
        hEdit = GetDlgItem(hDlg, IDC_OP_CB);
        for (iLoop = 0; iLoop < QOP_LAST; iLoop++) {
            SendMessage(hEdit, CB_ADDSTRING, 0, (LPARAM)OpName[iLoop]);
        }

        // Default to selecting string equals.
        SendMessage(hEdit, CB_SETCURSEL, QOP_STR_EQ, 0);

        // Modify the window text to "Configure <type> filter"
        // We access the global MyFilter pointer, this points to
        // the filter type that we're working with.
        wsprintf(szMsg, "Configuring %s", pFltr->szTag);
        SetWindowText( hDlg, szMsg );

        // Disable the "Done" button.
        hEdit = GetDlgItem(hDlg, IDOK);
        EnableWindow( hEdit, FALSE );

        return(TRUE);


    case WM_CLOSE:
        EndDialog( hDlg, IDCANCEL );
        return(TRUE);


    case WM_SYSCOLORCHANGE:
        Ctl3dColorChange();
        return(TRUE);

    case WM_COMMAND:

        switch (wParam) {

        case IDC_ADDAND_BTN:
        case IDC_ADDOR_BTN:
            if (wParam == IDC_ADDAND_BTN) {
                opAndOr = OP_AND;
            } else {
                opAndOr = OP_OR;
            }

            // Extract the fields. We recorded in INITDIALOG which fields
            // we have.
                // Name
            if (bHasName) {
                GetDlgItemText(hDlg, IDC_NAME, (LPTSTR)Token.szName, sizeof(Token.szName));
            }

                // Value (string first)
            if (bHasValue) {
                GetDlgItemText(hDlg, IDC_VALUE, (LPTSTR)Token.szValue, sizeof(Token.szValue));
            }

                // Operator. Get the index of the selection in the listbox
                // and convert to operator code.
            if (bHasOp) {
                hEdit = GetDlgItem(hDlg, IDC_OP_CB);
                index = SendMessage(hEdit, CB_GETCURSEL, 0, 0);
                Token.dwOp = index;
            }

                // GroupClass
            if (bHasGroupClass) {
                GetDlgItemText(hDlg, IDC_GROUPCLASS, (LPTSTR)Token.szGroupClass, sizeof(Token.szGroupClass));
            }

                // Attribute name.
            if (bHasAttribute) {
                GetDlgItemText(hDlg, IDC_ATTRIBUTE, (LPTSTR)Token.szAttributeName, sizeof(Token.szAttributeName));
            }

                // Architecture
            if (bHasArch) {
                GetDlgItemText(hDlg, IDC_ARCHITECTURE, (LPTSTR)Token.szArchitecture, sizeof(Token.szArchitecture));
            }
            // Add the token into the filter.
            // -2 for the index parameter means add the token at the end
            // of the filter's expression.
            // ---------------------------------------------------------
            pMyF = gpMyFilter;
            pFltr = pMyF->pF;

            stat = SmsAddToken( hFilter, opAndOr, &Token, -2 ); // -2 = at end.
            if (stat != SMS_OK) {
               wsprintf(szMsg, "AddToken fails: %d", stat);
               MessageBox(hDlg, szMsg, "Whoops", MB_OK);
            }


            // Clear the edit controls.
            // ------------------------
            SetDlgItemText( hDlg, IDC_NAME        , "" );
            SetDlgItemText( hDlg, IDC_VALUE       , "" );
            SetDlgItemText( hDlg, IDC_GROUPCLASS  , "" );
            SetDlgItemText( hDlg, IDC_ATTRIBUTE   , "" );
            SetDlgItemText( hDlg, IDC_ARCHITECTURE, "" );


            // Enable the "Done" button.
            // -------------------------
            hEdit = GetDlgItem(hDlg, IDOK);
            EnableWindow( hEdit, TRUE );

            return(TRUE);

        case IDOK:
            // We need to set the filter handle in the MYFILTER.
            pMyF = gpMyFilter;
            pMyF->hFilter = hFilter;
            hFilter = NULL;

            EndDialog(hDlg, IDOK);
            return(TRUE);


        }
    }

    return(FALSE);

}  /* SelectFilterDlg */



// ====================================================================
//
// This is the dialogue that is brought up in response to the
// view selected filters button in the main dialogue.
// It enables the user to view the filters that they have
// created and applied to the container. It shows the use of the
// SmsRetrieveFilters and SmsGetToken APIs.
//
// ====================================================================

extern "C" BOOL CALLBACK ViewSelFiltersDlg(
                                    HWND hDlg,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam)
{

    HWND hEdit, hEdit1;
    SMS_STATUS stat;
    static DWORD ctFilters = 0;     // How many filters there are in the
                                    // container.
    DWORD ctTokens;                 // How many tokens in filter.
    static HANDLE *ahFilters;       // Retrieve an array of handles.
    DWORD dwLoop;                   // Loop index.
    TOKEN Token;
    int index;                      // Get index of selected filter.
    char szBuff[256];               // Build up filter tokens here.




    switch (message) {

    case WM_INITDIALOG:
        // Dialogue initialisation.

        // Get the number of filters, then allocate spae and call again.
        // =============================================================
        stat = SmsGetAllFilters( ghContainer, NULL, &ctFilters );

        ahFilters = new HANDLE[ctFilters];
        stat = SmsGetAllFilters( ghContainer, ahFilters, &ctFilters );

        // Build up the list of filters. We want to populate the listbox
        // with the filter tags. When one of these is selected (via the
        // view button) we'll display its contents in the edit control box.

            // Populate the listbox.
        hEdit = GetDlgItem(hDlg, IDC_SEL_FILTERS_LB);

        HANDLE hFilter;
        DWORD filterType;               // Current filter's type and tag
        char szFilterTag[50];           // ...

        for (dwLoop = 0; dwLoop < ctFilters; dwLoop++) {
            hFilter = ahFilters[dwLoop];
            SmsGetFilterType( hFilter, &filterType, szFilterTag );

            SendMessage(hEdit, LB_ADDSTRING, 0, (LPARAM)szFilterTag);
        }

            // Select the first one in the list.
        SendMessage(hEdit, LB_SETCURSEL, 0, 0);

            // Send the listbox a focus message. This should cause him
            // to display the contents of the specified filter.
        if (ctFilters > 0) {
            WPARAM wp = MAKEWPARAM( IDC_SEL_FILTERS_LB, LBN_SELCHANGE );
            SendMessage(hDlg, WM_COMMAND, wp, (LPARAM)hEdit);
        }
        return(TRUE);


    case WM_CLOSE:
        // Close all the filters that we retrieved in SmsGetAllFilters.
        for (dwLoop = 0; dwLoop < ctFilters; dwLoop++) {
            hFilter = ahFilters[dwLoop];
            SmsCloseFilter( hFilter );
        }
        delete ahFilters;

        EndDialog( hDlg, IDCANCEL );
        return(TRUE);


    case WM_SYSCOLORCHANGE:
        Ctl3dColorChange();
        return(TRUE);

    case WM_COMMAND:

        if ((HIWORD(wParam) == LBN_SELCHANGE) &&
            (LOWORD(wParam) == IDC_SEL_FILTERS_LB)) {

            hEdit1 = (HWND)lParam;

            // Clear the contents of the view listbox.
            // =======================================
            szBuff[0] = '\0';
            hEdit = GetDlgItem(hDlg, IDC_VIEWFILTER);
            SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"");

            // Find out which filter we've selected and get it's handle.
            // =========================================================
            index = SendMessage(hEdit1, LB_GETCURSEL, 0, 0);
            hFilter = ahFilters[index];

            // Clear the token.
            // ================
            memset(&Token, 0, sizeof(TOKEN));

            // Loop through its tokens, display the token string in the
            // edit control.
            // ========================================================
            SmsGetTokenCount( hFilter, &ctTokens );
            for (dwLoop = 0; dwLoop < ctTokens; dwLoop++) {
                // Get token.
                SmsGetToken( hFilter, dwLoop, &Token );

                strcat( szBuff, Token.szTokenString );
                strcat( szBuff, " ");
            }
            SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)szBuff);

            return(TRUE);
        }

        switch (wParam) {


        case IDOK:
            EndDialog(hDlg, IDOK);
            return(TRUE);


        }
    }

    return(FALSE);

}  /* ViewSelFiltersDlg */





// ====================================================================
//
//  CFrameStack class.
//
//  This is only used in the folder view dialogue. It enables us to
//  descend into sub-folders but keep this current folder's data
//  around.
//  When we want to look at a sub-folder we just pop the current
//  folder's data onto the stack. when we return from a sub-folder we
//  just pop the stack.
//
// ====================================================================
CFrameStack::CFrameStack(HWND hDlg)
{
    sp = 0;
    _hDlg = hDlg;
}

CFrameStack::~CFrameStack()
{
    // Clear all objects from stack and delete them.
    CFrame *pFrame;
    for (int i = 0; i < stack.GetSize(); i++) {
        pFrame = (CFrame *)stack[i];
        delete pFrame;
    }
    stack.RemoveAll();
}


void CFrameStack::push( CFrame *pFrame )
{
    stack.Add( (CObject *)pFrame );
    sp++;

}


CFrame *CFrameStack::pop()
{
    if (sp == 0) {
        return(NULL);
    }
    --sp;
    CFrame *pFrame = (CFrame *)stack.GetAt( sp );
    stack.RemoveAt( sp );

    return(pFrame);
}


//Debug: dump the stack
void CFrameStack::Dump( const char *psz )
{
    CFrame *pf;
    char *p = szMsg;

    wsprintf(p, "sp=%d GetUpperBound=%d\n", sp-1, stack.GetUpperBound());
    p += strlen(p);

    for (int i = 0; i <= sp-1; i++) {
        pf = (CFrame *)stack[i];
        wsprintf(p, "%d ID: %s\n", i, pf->szFolderID);
        p += strlen(p);
    }
    MessageBox( _hDlg, szMsg, psz, MB_OK );
}



#ifdef DEBUG

// ====================================================================
//
//  Debug log utility.
//  Here so people can see an example of such a thing.
//
// eg: Log("WM_TIMER GetWindowRect fails: %d", GetLastError());
//
// ====================================================================
int Log(char *fmt, ...)
{
    char *buffer = new char[2048];

    va_list argptr;
    int cnt;
    va_start(argptr, fmt);
    cnt = vsprintf(buffer, fmt, argptr);
    va_end(argptr);

    FILE *fp;

    fp = fopen("browser.log", "at");

    if (!fp) {
        delete buffer;
        return( 0 );
    }

    time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    fprintf(fp, "%s\n", buffer);

    BOOL killfile = FALSE;

    if (ftell(fp) > 0x10000) {
        killfile = TRUE;   // 64K Limit on log
    }

    fclose(fp);

    if (killfile) {
        remove("log.log");
    }

    delete buffer;

    return( cnt );
}
#endif  // DEBUG


/* EOF: browser.cpp */

