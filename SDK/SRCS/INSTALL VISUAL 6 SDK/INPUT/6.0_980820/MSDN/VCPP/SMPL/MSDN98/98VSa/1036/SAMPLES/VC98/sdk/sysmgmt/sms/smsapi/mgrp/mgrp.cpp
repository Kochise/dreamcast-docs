// ====================================================================
//
//  File: mgrp.cpp
//
//  Copyright (C) 1996 by Microsoft Corporation.
//
//  Author:
//      Jonathan Shuval     Microsoft Corp.
//
//
//  This sample shows how to create a machine group and insert machines
//  into it.
//
// ====================================================================



// ====================================================================
//  Includes.
// ====================================================================
#include <afx.h>
#include <smsapi.h>             // Header for the APIs.
#include <time.h>               // For converting time scalars into string.

// Include the GetStatusName function.
// -------------------------------------
#include "..\common\status.inc"



// ====================================================================
//  Defines.
// ====================================================================
#define CCH_MAXINPUT 256



// ====================================================================
//  Local prototypes.
// ====================================================================

// Does the real work.
// -------------------------------------------------------------
void doTheWork( HANDLE hConnect );


// Set filters according to what container we're looking at.
// -------------------------------------------------------------
BOOL setMachFilters( HANDLE hConnect, HANDLE hContainer );


// Functions to display folders, scalars, and expressions.
// -------------------------------------------------------------
void DisplayFolder( HANDLE hFolder );
void DisplayScalars( HANDLE hFolder );


// Prompt the user for input and return the reply.
// -------------------------------------------------------------
void InputString(const char* pszMessage, char* pszResult);


// Connect to the SMS datasource.
// -------------------------------------------------------------
HANDLE ConnectToDatasource();


// Display an error message with its SMS status value.
// -------------------------------------------------------------
void DisplaySmsError(const char* pszMessage, SMS_STATUS stat);


// Get the string equivallent for an SMS status code.
// -------------------------------------------------------------
const char *GetStatusName(SMS_STATUS stat);

// Set a string scalar.
// -------------------------------------------------------------
SMS_STATUS SetScalarString( HANDLE hFolder, char *pszName, char *pszValue);


// ====================================================================
//
//  Macros for checking status
//
// ====================================================================
        // Void return
#define CHKSTAT(str) if (stat != SMS_OK) { \
        DisplaySmsError(str, stat);         \
        return; }

        // Bool return
#define CHKSTAT_RTN(str) if (stat != SMS_OK) { \
        DisplaySmsError(str, stat);             \
        return(FALSE); }



// ====================================================================
//
//  The work starts here.
//
// ====================================================================
void main()
{

    HANDLE hConnect;

    // Get and display API version.
    // ----------------------------
    char *pszVersion;
    SmsAPIVer( &pszVersion );
    printf("%s\n", pszVersion );



    //===========================================
    // Connect to the SMS datasource.
    //===========================================
    hConnect = ConnectToDatasource();
    if (hConnect == NULL) {
        return;
    }


    // This loop allows us to do the real work multiple times.
    // =======================================================
    BOOL bDone = FALSE;
    char reply[10];

    while (!bDone) {

        doTheWork( hConnect );

        printf("Restart [y/n]? "); gets(reply);
        bDone = (reply[0] != 'y' && reply[0] != 'Y');
    }


    // Disconnect from the datasource.
    // ===============================
    SmsDataSourceDisconnect( hConnect );


}  /* main */



// ====================================================================
//
//  This function does whatever work is required.
//  In this case, it will:
//      - open a machine group container
//      - create a machine group folder
//      - open a machine container
//      - select machine folders from mach container that I want
//          to copy to the mgrp folder
//      - loop copying these machine folders to the mgrp folder
//      - link and commit the mgrp folder
//      - close everything

//
// ====================================================================
void doTheWork( HANDLE hConnect )
{
    HANDLE hMGrpContainer;
    HANDLE hMachContainer;
    SMS_STATUS stat;

    // Open the containers
    // ===================
    stat = SmsOpenContainer( C_MACHINEGROUP, hConnect, &hMGrpContainer );
    if (stat != SMS_OK) {
        DisplaySmsError("SmsOpenContainer (mach grp) failed", stat);
        return;
    }

    stat = SmsOpenContainer( C_MACHINE, hConnect, &hMachContainer );
    if (stat != SMS_OK) {
        DisplaySmsError("SmsOpenContainer (mach) failed", stat);
        SmsCloseContainer( hMGrpContainer );
        return;
    }


    // Create machine group folder
    // ===========================
    HANDLE hMGrpFolder;
    stat = SmsCreateFolder( hMGrpContainer, F_MACHINEGROUP, "", &hMGrpFolder );
    if (stat != SMS_OK) {
        char szError[256];
        sprintf(szError, "SmsCreateFolder failed to create MachineGroup folder");
        DisplaySmsError(szError, stat);
        SmsCloseContainer( hMGrpContainer );
        SmsCloseContainer( hMachContainer );
        return;
    }




    // Select machine folders that we want tp put in to the mgrp folder.
    // Just get all the PC machines from the mach container for now.
    // Set filter for arch PC only machines.
    // =================================================================
    setMachFilters( hConnect, hMachContainer );

    stat = SmsPopulate( hMachContainer, POP_SYNC, NULL );
    if (stat != SMS_OK) {
        DisplaySmsError("Bad return from SmsPopulate", stat);
        // Close everything and return.
        SmsCloseContainer( hMGrpContainer );
        SmsCloseContainer( hMachContainer );
        SmsCloseFolder( hMGrpFolder );
        return;
    }



    // Loop getting a handle to each machine folder and
    // inserting it into the new mgroup folder.
    // ================================================
    DWORD ctFolders;
    SmsGetFolderCount( hMachContainer, F_ANY, &ctFolders );
    printf("\n======== Mach Container has %d folders\n", ctFolders);

    HANDLE hFolder;
    char szFolderID[100];               // This folder's ID.
    BOOL bValid = TRUE;

    for (DWORD dwLoop = 0; dwLoop < ctFolders; dwLoop++) {

        SmsGetNextFolder( hMachContainer, F_ANY, &hFolder );

        // Display message saying what we've got
        // -------------------------------------
        stat = SmsGetFolderID( hFolder, szFolderID );
        printf("[%d] Got folder: %s, about to insert in new folder\n",
                dwLoop+1, szFolderID);


        // Insert the machine folder into the machine group folder.
        // This can't do a straight swap of parents since we want to keep
        // the machine folder's relationship to his current parent.
        // What this API does therefore is to make a *copy* of the folder
        // and link this copy into the mach group folder (ie the mach group
        // folder becomes the new folder's parent).
        // This means that this API returns a handle to the newly-created
        // folder.
        // ================================================================
        HANDLE hNewFolder;
        stat = SmsDupFolder( hMGrpFolder, hFolder, &hNewFolder );
        if (stat != SMS_OK) {
            printf("Failure duplicating folder %s: %d\n", szFolderID, stat);
            bValid = FALSE;
            break;
        }

        // Now we need to link and commit the new machine folder to
        // the machine group folder.
        // ========================================================
        stat = SmsLinkFolder( hNewFolder );
        if (stat != SMS_OK) {
            printf("Failure linking folder %s: %d\n", szFolderID, stat);
            goto CLOSE;
        }

        stat = SmsCommitFolder( hNewFolder );
        if (stat != SMS_OK && stat != SMS_PARENT_NEEDS_COMMIT) {
            printf("Failure comitting folder %s: %d\n", szFolderID, stat);
            goto CLOSE;
        }



        SmsCloseFolder( hFolder );
        SmsCloseFolder( hNewFolder );
    }


    // Set scalars for the mach group folder.
    // ======================================
    char szBuff[99];
    InputString("Give me a unique name for the mach gp", szBuff);
    SetScalarString( hMGrpFolder, "Name", szBuff );
    SetScalarString( hMGrpFolder, "Comment", "some comment" );

    // Link mach grp folder into parent and commit it.
    // ===============================================
    stat = SmsLinkFolder( hMGrpFolder );
    if (stat != SMS_OK) {
        DisplaySmsError("SmsLinkFolder failed on the mach Group folder", stat);
        goto CLOSE;
    }

    // Write it back to data source.
    // =============================
    stat = SmsCommitFolder( hMGrpFolder );
    if (stat != SMS_OK) {
        DisplaySmsError("SmsCommitFolder failed on the mach Group folder", stat);
        goto CLOSE;
    }



    // If we got here then all seems to be ok.
    // Display the mach group folder
    // =======================================
    DisplayFolder( hMGrpFolder );

    // Close everything - we're done.
    // ==============================
CLOSE:
    SmsCloseContainer( hMGrpContainer );
    SmsCloseContainer( hMachContainer );
    SmsCloseFolder( hMGrpFolder );


    printf("\n********* All done ***************\n");

}




// ====================================================================
//  We are passed in a handle to a folder. We retrieve the folder's
//  information, displaying scalars if any.
//  We then recursively examine sub-folders (after closing the
//  current folder).
// ====================================================================
void DisplayFolder( HANDLE hFolder )
{

    SMS_STATUS stat;
    HANDLE hSubFolder;
    DWORD fType;                   // type of folder we're dealing with.
    char szfType[30];                   // type as a string.
    DWORD totFolders;                   // Total number of sub-folders of
                                        // all types.
    char szFolderID[100];               // This folder's ID.
    DWORD ctScalars;                    // How many scalars in this folder.

    printf("\n============================================================\n");

    // Get folder type and id.
    // -----------------------
    stat = SmsGetFolderID( hFolder, szFolderID );
    if (stat != SMS_OK) {
        if (stat == SMS_NEW_FOLDER) {
            strcpy(szFolderID, "**New folder**");
        } else {
            CHKSTAT("SmsGetFolderID");
        }
    }

    stat = SmsGetFolderType( hFolder, &fType, szfType );
    CHKSTAT("SmsGetFolderType");
    printf("Folder ID \"%s\" is a %s\n\n", szFolderID, szfType);

    // How many scalars in this folder.
    // --------------------------------------------------------
    stat = SmsGetScalarCount( hFolder, &ctScalars );
    CHKSTAT("SmsGetScalarCount");
    printf("Contains %d scalars\n\n", ctScalars);
    DisplayScalars( hFolder );


    // Get count of all sub-folders (ie of all types).
    // and allocate space for their handles.
    // -----------------------------------------------
    stat = SmsGetFolderCount( hFolder, F_ANY, &totFolders );
    printf("Contains %d folders\n\n", totFolders);

    char szSubFolderID[100];
    DWORD ctFolders;
    HANDLE *phFolders;
    phFolders = (HANDLE *)malloc(totFolders * sizeof(HANDLE));


    // This loop gets the sub-folder IDs and displays them.
    // ====================================================

    for (ctFolders = 0; ctFolders < totFolders; ctFolders++) {

        // Get a handle to a sub-folder.
        // -----------------------------
        stat = SmsGetNextFolder( hFolder, F_ANY, &hSubFolder );
        CHKSTAT("SmsGetNextFolder");
        phFolders[ctFolders] = hSubFolder;

        // Get and display the sub-folder's ID.
        // ------------------------------------
        stat = SmsGetFolderID( hSubFolder, szSubFolderID );
        CHKSTAT("SmsGetFolderID");
        printf("\tSub-folder: \"%s\"\n", szSubFolderID);
    }


    // =======================================================
    // We can now release the handle that was passed in to us.
    // If we wait until the function returns then, because we
    // recurse, we don't release it till the very end.
    // =======================================================
    SmsCloseFolder( hFolder );

    // This loop gets the sub-folders and displays them.
    // =================================================
    for (ctFolders = 0; ctFolders < totFolders; ctFolders++) {
        DisplayFolder( phFolders[ctFolders] );
    }

    // Free the folder handle array.
    // -----------------------------
    free( phFolders );

}  /* DisplayFolder */



// ====================================================================
//
//  Display all the scalars for the folder.
//
// Note: the buffer for string scalars has been deliberately set to a
// value lower than the maximum. If we encounter a string scalar whose
// value exceeds this amount then we will print the 'data truncated'
// message.
//
// ====================================================================
void DisplayScalars( HANDLE hFolder )
{
    SMS_STATUS stat = SMS_OK;
    SCALAR scalar;
    char szName[50];                        // Buffer for name.
    char szValue[SMS_DATA_BUFF_SIZE+1];     // Buffer for string value.
    BYTE byValue[SMS_DATA_BUFF_SIZE+1];     // Buffer for binary scalars.
    scalar.pszName  = szName;
    scalar.pszValue = szValue;
    scalar.pValue   = byValue;

    char *pszTime;          // For time scalars.


    while (1) {

        scalar.dwLen = sizeof(szValue)-1;       // must tell him the size

        stat = SmsGetNextScalar( hFolder, &scalar);
        if (stat != SMS_OK && stat != SMS_MORE_DATA) {
            break;
        }

        if (stat == SMS_MORE_DATA) {
            printf("Receive buffer too small, should be %d. Data truncated\n",
                            scalar.dwLen);
        }
        // Check scalar type, display accordingly.
        // ---------------------------------------
        switch (scalar.scType) {
        case SCALAR_STRING:
            printf("\t%30s: %s\n", scalar.pszName, scalar.pszValue);
            break;

        case SCALAR_INT:
            printf("\t%30s: %ld\n", scalar.pszName, scalar.dwValue);
            break;

        case SCALAR_TIME:
            // If there is a string equivalence use it.
            if (scalar.bStringEquivalence) {
                printf("\t%30s: %s\n", scalar.pszName, scalar.pszValue);
            } else {
                pszTime = ctime( &scalar.tValue );
                printf("\t%30s: %s", scalar.pszName, pszTime);
            }
            break;

        case SCALAR_BINARY:
            // Got binary data.
            // Just tell the user how much data there is.
            printf("\t%30s: Binary data - %d bytes of data\n",
                        scalar.pszName, scalar.dwLen);
            break;
        }
    }

    // Why did we exit (other than no more scalars)?
    // ---------------------------------------------
    if (stat != SMS_NO_MORE_DATA) {
        DisplaySmsError("Bad return from Scalar access", stat);
    }

    // Terminate with newline.
    // -----------------------
    printf("\n");

}




// ********************************************************************
//      Helper functions.
// ********************************************************************




// ====================================================================
// This function sets the filters when we are looking at a Machine
// container.
//
// Want only PC archs, so we set an architecture filter.
//
// ====================================================================
BOOL setMachFilters( HANDLE hConnect, HANDLE hContainer )
{
    HANDLE hFilter;


    // =========================================================
    // Architecture filter.
    // Architecture = Personal Computer.
    // =========================================================
    SmsCreateFilter( ARCHITECTURE_FILTER, hConnect, &hFilter );

    TOKEN ArchToken;
    memset( &ArchToken, 0, sizeof(TOKEN) );

    strcpy( ArchToken.szName, "Architecture" );
    strcpy( ArchToken.szValue, "Personal Computer" );
    ArchToken.dwOp = QOP_STR_EQ;

    SmsAddToken( hFilter, OP_OR, &ArchToken, 0 );

    SmsSetFilter( hContainer, hFilter );
    SmsCloseFilter( hFilter );

    SmsCloseFilter( hFilter );

    return(TRUE);

}  /* setMachFilters */





// ====================================================================
// InputString
//
// Prompt the user to input a string and return the string in the
// specified buffer.
//
// Parameters:
//      const char* pszMessage
//          The user prompt to display.
//
//      char* pszResult
//          Pointer to the buffer where the user's input will be returned.
//
// Returns;
//      The user's input is returned via the given buffer.
//
// ====================================================================
void InputString(const char* pszMessage, char* pszResult)
{
    printf("%s: ", pszMessage);
    gets(pszResult);
}




// ====================================================================
// ConnectToDatasource
//
// Get the datasource connection information from the user and use it
// to connect to the datasource.
//
// Parameters:  None.
//
// Returns:
//      The connection handle or NULL if the connection failed.
//
// ====================================================================
HANDLE ConnectToDatasource()
{
    // Get the information we need to connect to the
    // data source from the user.
    //==============================================
    char szServer[CCH_MAXINPUT];
    char szUser[CCH_MAXINPUT];
    char szPasswd[CCH_MAXINPUT];
    char szDatabase[CCH_MAXINPUT];

    printf("\n");
    printf("**************************\n");
    printf("* Connect to data source *\n");
    printf("**************************\n");
    InputString("SQL server name", szServer);
    InputString("SQL database name", szDatabase);
    InputString("User name for SQL server", szUser);
    InputString("Password for SQL server", szPasswd);
    printf("\n");


    // Connect to a data source. SQL in this case.
    // ===========================================
    DATASOURCE dsParams;

    dsParams.sqlParams.ds          = DB_SQL;
    dsParams.sqlParams.pszServer   = szServer;
    dsParams.sqlParams.pszUserName = szUser;
    dsParams.sqlParams.pszPasswd   = szPasswd;
    dsParams.sqlParams.pszDbName   = szDatabase;
    dsParams.sqlParams.pFunc       = NULL;         // No encryption.
    dsParams.sqlParams.pszKey      = "";

    HANDLE hConnect;
    SMS_STATUS stat;
    stat = SmsDataSourceConnect( &dsParams, &hConnect);

    if (stat != SMS_OK) {
        hConnect = NULL;
        DisplaySmsError("Connect to data source failed", stat);
    }

    return( hConnect );
}



SMS_STATUS SetScalarString(HANDLE hFolder, char* pszName, char* pszValue)
{
    SCALAR sc;
    sc.pszName = pszName;
    sc.scType = SCALAR_STRING;
    sc.pszValue = pszValue;

    SMS_STATUS stat;
    stat = SmsSetScalar(hFolder, &sc);
    return( stat );
}



/* EOF: mgrp.cpp */

