// ====================================================================
//
//  File: testall.cpp
//
//  Copyright (C) 1994, 1995 by Microsoft Corporation.
//
//  Author:
//      Jonathan Shuval     Microsoft Corp.
//
//
//  This program illustrates the use of the SMS APIs to examine either
//  a site container, a jobs container, or a package container. The
//  only difference in code between them is the setting of filters.
//
//  The following APIs are used in this program:
//
//      SmsAPIVer
//
//      SmsDataSourceConnect
//      SmsDataSourceDisconnect
//
//      SmsOpenContainer
//      SmsSetFilter
//      SmsPopulate
//      SmsGetFolderCount
//      SmsCloseContainer
//
//      SmsCreateFilter
//      SmsGetToken
//      SmsGetTokenCount
//      SmsAddToken
//      SmsCloseFilter
//
//      SmsGetFolderID
//      SmsGetFolderType
//      SmsGetNextFolder
//      SmsGetScalarCount
//      SmsGetNextScalar
//      SmsCloseFolder
//
//  See the readme.txt file in this directory for more information.
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


// Ask user if they want to see site, jobs or package container.
// -------------------------------------------------------------
DWORD getDumpOption();


// Set filters according to what container we're looking at.
// -------------------------------------------------------------
BOOL setSiteFilters( HANDLE hConnect, HANDLE hContainer );
BOOL setJobFilters( HANDLE hConnect, HANDLE hContainer );
BOOL setPkgFilters( HANDLE hConnect, HANDLE hContainer );


// Functions to display folders, scalars, and expressions.
// -------------------------------------------------------------
void DisplayFolder( HANDLE hFolder );
void DisplayScalars( HANDLE hFolder );
void DisplayExpression( HANDLE hFolder );


// Prompt the user for input and return the reply.
// -------------------------------------------------------------
void InputString(const char* pszMessage, char* pszResult);


// Connect to the SMS datasource.
// -------------------------------------------------------------
HANDLE ConnectToDatasource();


// Display the help message.
// -------------------------------------------------------------
void DisplayHelp();


// Display the greeting.
// -------------------------------------------------------------
void DisplayGreeting();


// Check to see if there was a request for help
// on the command line.
// -------------------------------------------------------------
BOOL DidRequestHelp(int argc, char** argv);


// Display an error message with its SMS status value.
// -------------------------------------------------------------
void DisplaySmsError(const char* pszMessage, SMS_STATUS stat);


// Get the string equivallent for an SMS status code.
// -------------------------------------------------------------
const char* GetStatusName(SMS_STATUS stat);



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
void main(int argc, char** argv)
{
    // Check to see if this is a request to display the help
    // screen.  If so, display it. Otherwise, display a greeting
    // banner.
    //=========================================================
    if (DidRequestHelp(argc, argv)) {
        DisplayHelp();
        return;
    }
    else {
        DisplayGreeting();
    }



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
//      - open a container
//      - set filters
//      - populate the container
//      - retrieve all folders from the container and store the handles
//      - cause these folder to be displayed.
//
// ====================================================================
void doTheWork( HANDLE hConnect )
{
    HANDLE hContainer;
    SMS_STATUS stat;

    // Ask the user if he wants a site hierarchy, jobs, or package dump.
    // =================================================================
    DWORD cType = getDumpOption();
    BOOL bRet;

    stat = SmsOpenContainer( cType, hConnect, &hContainer );
    if (stat != SMS_OK) {
        DisplaySmsError("SmsOpenContainer failed", stat);
        return;
    }

    switch (cType) {
    case C_SITE:
        bRet = setSiteFilters( hConnect, hContainer );
        break;

    case C_JOB:
        bRet = setJobFilters( hConnect, hContainer );
        break;

    case C_PACKAGE:
        bRet = setPkgFilters( hConnect, hContainer );
        break;
    }

    if (!bRet) {
        printf("Failure in filters.\n");
        SmsCloseContainer( hContainer );
        return;
    }

    // Select all objects matching filter.
    // -----------------------------------
    stat = SmsPopulate( hContainer, POP_SYNC, NULL );
    if (stat != SMS_OK) {
        DisplaySmsError("Bad return from SmsPopulate", stat);
        SmsCloseContainer( hContainer );
        return;
    }

    DWORD numFolders;
    SmsGetFolderCount( hContainer, F_ANY, &numFolders );
    printf("\n======== Container has %d folders ==========================\n\n",
                                numFolders);


    // For each object in the list enumerate its properties.
    // What I'm going to do is open all folders in a loop and
    // then close the container. The open container causes all
    // objects to be left open until the container closes. This
    // chews up memory big time.
    // ------------------------------------------------------
    CObArray topFolders;
    HANDLE hFolder;

    // Open all top-level folders.
    // ===========================
    while (1) {
        stat = SmsGetNextFolder( hContainer, F_ANY, &hFolder );
        if (stat != SMS_OK) {
            // Either error or no more objects in list.
            break;
        }

        // Store the folder's handle for later processing.
        // -----------------------------------------------
        topFolders.Add( (CObject *)hFolder );
    }

    printf("*** Retrieved %d folders ***\n", topFolders.GetSize());
    // Check why we exited the loop.
    // -----------------------------
    if (stat != SMS_NO_MORE_DATA) {
        printf("Failed to retrieve folder: %d\n", stat);
    }

    // Close the container.
    // --------------------
    SmsCloseContainer( hContainer );
    printf("*** Container closed ***\n");


    for (int iLoop = 0; iLoop < topFolders.GetSize(); iLoop++) {

        // Retrieve the handle.
        // --------------------
        hFolder = (HANDLE)topFolders[iLoop];

        printf("\n*** Top folder #%d\n", iLoop);

        // Display the folder.
        // -------------------
        DisplayFolder( hFolder );

        // The folder is closed inside DisplayFolder.
    }

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
    CHKSTAT("SmsGetFolderID");

    stat = SmsGetFolderType( hFolder, &fType, szfType );
    CHKSTAT("SmsGetFolderType");
    printf("Folder ID \"%s\" is a %s\n\n", szFolderID, szfType);

    // How many scalars in this folder.
    // --------------------------------------------------------
    stat = SmsGetScalarCount( hFolder, &ctScalars );
    CHKSTAT("SmsGetScalarCount");
    printf("Contains %d scalars\n\n", ctScalars);
    DisplayScalars( hFolder );


    // If folder has an associated expression, display it.
    // ---------------------------------------------------
    DisplayExpression( hFolder );

    // Get count of all sub-folders (ie of all types).
    // and allocate space for their handles.
    // -----------------------------------------------
    stat = SmsGetFolderCount( hFolder, F_ANY, &totFolders );
    printf("Contains %d folders\n\n", totFolders);

    HANDLE *phFolders = (HANDLE *)malloc(totFolders * sizeof(HANDLE));


    // This loop gets the sub-folder IDs and displays them.
    // ====================================================
    char szSubFolderID[100];
    DWORD ctFolders;

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



// ====================================================================
//
// DisplayExpression -- inv pkg has an expression, display it.
//
// ====================================================================
void DisplayExpression( HANDLE hFolder )
{
    DWORD ctTokens;
    SMS_STATUS stat;

    stat = SmsGetTokenCount( hFolder, &ctTokens );
    if (stat != SMS_OK) {
        printf("Folder has no expression\n\n");
        return;
    }


    printf("Folder has expression with %d tokens\n\n", ctTokens);

    TOKEN Token;

    for (DWORD dwI = 0; dwI < ctTokens; dwI++) {
        stat = SmsGetToken( hFolder, (INT)dwI, &Token );
        if (stat != SMS_OK) {
            DisplaySmsError("GetToken failed", stat);
            break;
        }
        // print out token
        CString sTokenType;

        switch (Token.tokenType) {
        case TOKEN_USER:
            sTokenType = "User token ";
            break;

        case TOKEN_OR:
            sTokenType = "OR token   ";
            break;

        case TOKEN_AND:
            sTokenType = "AND token  ";
            break;

        case TOKEN_OPENPAREN:
            sTokenType = "Open paren ";
            break;

        case TOKEN_CLOSEPAREN:
            sTokenType = "Close paren";
            break;

        default:
            sTokenType = "Invalid token type!";
            break;
        }

        printf("[%d: %s] %s\n", dwI,
                (const char *)sTokenType, Token.szTokenString );

    }

    // Terminate with newline.
    // -----------------------
    printf("\n");

}



// ********************************************************************
//      Helper functions.
// ********************************************************************


// ====================================================================
// Ask the user if they want to look at site, jobs, pkg hierarchy.
// ====================================================================
DWORD getDumpOption()
{
    DWORD cType;
    char reply[10];
    BOOL valid = FALSE;

    while (!valid) {
        printf("Options: (S)ites (J)obs (P)ackages: ");
        gets(reply);

        switch (reply[0]) {
        case 'S': case 's':
            cType = C_SITE;
            valid = TRUE;
            break;

        case 'J': case 'j':
            cType = C_JOB;
            valid = TRUE;
            break;

        case 'P': case 'p':
            cType = C_PACKAGE;
            valid = TRUE;
            break;

        default:
            printf("Invalid - try again (S, J, P): ");
            break;

        }
    }

    return(cType);
}




// ====================================================================
// This function sets the filters when we are looking at a site
// container.
//
// This illustrates the use of the following filters: Site filter,
// architecture filter, machine filter, group filter.
//
// The user is given the choice of using some of these filters or not.
// ====================================================================
BOOL setSiteFilters( HANDLE hConnect, HANDLE hContainer )
{
    SMS_STATUS stat;
    char reply[5];
    HANDLE hFilter;

    // =========================================================
    // Site filter: RootSite or SiteByCode
    // =========================================================
    TOKEN SiteToken;
    memset( &SiteToken, 0, sizeof(TOKEN) );
    stat = SmsCreateFilter( SITE_FILTER, hConnect, &hFilter );
    CHKSTAT_RTN("SmsCreateFilter");

    printf("Site filter. Rootsite or Site by code [R/S]? ");
    gets(reply);
    if (reply[0] == 'R' || reply[0] == 'r') {
        strcpy( SiteToken.szName, "RootSite" );
        stat = SmsAddToken( hFilter, OP_OR, &SiteToken, 0 );
        CHKSTAT_RTN("SmsAddToken (site filter)");

    } else {
        printf("Give 3 letter site code: ");
        gets(reply);
        strcpy( SiteToken.szName, "SiteByCode" );
        strcpy( SiteToken.szValue, reply );
        SiteToken.dwOp = QOP_STR_EQ;
        stat = SmsAddToken( hFilter, OP_OR, &SiteToken, 0 );
        CHKSTAT_RTN("SmsAddToken (site filter)");
    }
    stat = SmsSetFilter( hContainer, hFilter );
    SmsCloseFilter( hFilter );
    if (stat != SMS_OK) {
        printf("SmsSetFilter failed: %d\n", stat);
        return(FALSE);
    }



    // =========================================================
    // Architecture filter.
    // Must set an architecture filter else we get no machines.
    // Architecture = Personal Computer.
    // =========================================================
    TOKEN ArchToken;
    memset( &ArchToken, 0, sizeof(TOKEN) );

    stat = SmsCreateFilter( ARCHITECTURE_FILTER, hConnect, &hFilter );
    CHKSTAT_RTN("SmsCreateFilter");

    strcpy( ArchToken.szName, "Architecture" );
    strcpy( ArchToken.szValue, "Personal Computer" );
    ArchToken.dwOp = QOP_STR_EQ;

    stat = SmsAddToken( hFilter, OP_OR, &ArchToken, 0 );
    CHKSTAT_RTN("SmsAddToken (architecture filter)");

    stat = SmsSetFilter( hContainer, hFilter );
    SmsCloseFilter( hFilter );

    CHKSTAT_RTN("SmsSetFilter (architecture filter)");


    // =========================================================
    // Machine filter. This filter will result in only machines
    // with a SystemRole of Server being included in the parent
    // (domain) folder.
    // =========================================================
    printf("Filter SystemRole=Server [y/n]? ");
    gets(reply);
    if (reply[0] == 'y') {
        TOKEN MachToken;
        memset( &MachToken, 0, sizeof(TOKEN) );
        strcpy( MachToken.szArchitecture, "Personal Computer" );
        strcpy( MachToken.szGroupClass, "MICROSOFT|IDENTIFICATION|1.0" );
        strcpy( MachToken.szAttributeName, "SystemRole" );
        strcpy( MachToken.szValue, "Server" );
        MachToken.dwOp = QOP_STR_EQ;

        stat = SmsCreateFilter( MACHINE_FILTER, hConnect, &hFilter );
        CHKSTAT_RTN("SmsCreateFilter (machine filter)");

        stat = SmsAddToken( hFilter, OP_AND, &MachToken, 0 );
        CHKSTAT_RTN("SmsAddToken (machine filter)");

        stat = SmsSetFilter( hContainer, hFilter );
        SmsCloseFilter( hFilter );
        CHKSTAT_RTN("SmsSetFilter (machine filter)");
    }


    // =========================================================
    // Group filter.
    //  Only one filter of a particular type can be applied to a
    //  container. So we just record whether or not there is a
    //  group filter to be set.
    //  This group filter says that we only want the
    //  identification group for a machine.
    // =========================================================
    BOOL bSetGroupFilter = FALSE;

    stat = SmsCreateFilter( GROUP_FILTER, hConnect, &hFilter );
    CHKSTAT_RTN("SmsCreateFilter (group filter)");
    TOKEN GroupToken;
    memset( &GroupToken, 0, sizeof(TOKEN) );

    printf("Filter Group= MICROSOFT|IDENTIFICATION|1.0 [y/n]? ");
    gets(reply);
    if (reply[0] == 'y') {

        // Define a (perculating) filter: Group=Ident.
        // -------------------------------------------------
        strcpy( GroupToken.szName, "GroupClass" );
        strcpy( GroupToken.szValue, "MICROSOFT|IDENTIFICATION|1.0" );
        GroupToken.dwOp = QOP_STR_EQ;

        stat = SmsAddToken( hFilter, OP_OR, &GroupToken, 0 );
        CHKSTAT_RTN("SmsAddToken (group filter - ID group)");
        bSetGroupFilter = TRUE;
    }

    // =========================================================
    //  This one says that we only want the netcard
    //  group for a machine.
    // =========================================================
    printf("Filter Group= MICROSOFT|NETCARD|1.0 [y/n]? ");
    gets(reply);
    if (reply[0] == 'y') {

        // Define a (perculating) filter: Group=Netcard.
        // -------------------------------------------------
        strcpy( GroupToken.szName, "GroupClass" );
        strcpy( GroupToken.szValue, "MICROSOFT|NETCARD|1.0" );
        GroupToken.dwOp = QOP_STR_EQ;

        stat = SmsAddToken( hFilter, OP_OR, &GroupToken, 0 );
        CHKSTAT_RTN("SmsAddToken (group filter - Netcard group)");
        bSetGroupFilter = TRUE;
    }

    // Did user select a group filter? If so apply it to the container now.
    // ====================================================================
    if (bSetGroupFilter) {
        stat = SmsSetFilter( hContainer, hFilter );
        CHKSTAT_RTN("SmsSetFilter (group filter)");
    }
    SmsCloseFilter( hFilter );

    return(TRUE);

}  /* setSiteFilters */




// ====================================================================
// This function sets filters appropriate for a jobs container.
// It illustrates the use of jobs filters.
//
// If no job filter is selected, then all jobs will be retrieved.
// Currently, this will only test out the JobType tokens.
// The user can select one or more of the following JobType tokens in
// a job filter:
//  look at workstation install jobs
//  look at server share jobs
//  look at remove package jobs
//  look at system jobs (ie all the rest).
//
// NOTE: minimal error checking at the moment.
//
// ====================================================================
BOOL setJobFilters( HANDLE hConnect, HANDLE hContainer )
{

    SMS_STATUS stat = SMS_OK;
    HANDLE hFilter;
    BOOL done = FALSE;
    char reply[10];
    BOOL bRet = TRUE;
    BOOL bTokenSelected = FALSE;    // Has token been added to filter?
    const INT iIndex = -2;          // Token index in filter. -2 means add to end.

    printf("Select filters for jobs container.\n");
    printf("Choices are: \n\tWorkstation install 'w'\n\tServer share 's'\n\tRemove package 'r'\n\tSystem 'y'\n");

    stat = SmsCreateFilter( JOB_FILTER, hConnect, &hFilter );
    CHKSTAT_RTN("SmsCreateFilter (job filter)");

    TOKEN JobToken;
    memset( &JobToken, 0, sizeof(TOKEN) );

    while (!done) {
        printf("\nSelect one of [wsry] 'x' to complete: ");
        gets(reply);

        switch (reply[0]) {
        case 'W':
        case 'w':
            // Workstation install jobs
            strcpy( JobToken.szName, "JobType" );
            strcpy( JobToken.szValue, "Install" );
            JobToken.dwOp = QOP_STR_EQ;
            stat = SmsAddToken( hFilter, OP_OR, &JobToken, iIndex );
            CHKSTAT_RTN("SmsAddToken (job filter)");
            bTokenSelected = TRUE;
            break;

        case 'S':
        case 's':
            // Server share jobs
            strcpy( JobToken.szName, "JobType" );
            strcpy( JobToken.szValue, "Server" );
            JobToken.dwOp = QOP_STR_EQ;
            stat = SmsAddToken( hFilter, OP_OR, &JobToken, iIndex );
            CHKSTAT_RTN("SmsAddToken (job filter)");
            bTokenSelected = TRUE;
            break;

        case 'R':
        case 'r':
            // Remove package jobs
            strcpy( JobToken.szName, "JobType" );
            strcpy( JobToken.szValue, "Remove package" );
            JobToken.dwOp = QOP_STR_EQ;
            stat = SmsAddToken( hFilter, OP_OR, &JobToken, iIndex );
            CHKSTAT_RTN("SmsAddToken (job filter)");
            bTokenSelected = TRUE;
            break;

        case 'Y':
        case 'y':
            // System jobs
            strcpy( JobToken.szName, "JobType" );
            strcpy( JobToken.szValue, "System" );
            JobToken.dwOp = QOP_STR_EQ;
            stat = SmsAddToken( hFilter, OP_OR, &JobToken, iIndex );
            CHKSTAT_RTN("SmsAddToken (job filter)");
            bTokenSelected = TRUE;
            break;

        case 'X':
        case 'x':
            // finished
            done = TRUE;
            break;

        default:
            // give message again
            printf("Invalid response\n");
            printf("Choices are: \n\tWorkstation install 'w'\n\tServer share 's'\n\tRemove package 'r'\n\tSystem 'y'\n");
        }
    }


    // Only apply the filter if a token has been selected.
    // ---------------------------------------------------
    if (bTokenSelected) {
        stat = SmsSetFilter( hContainer, hFilter );
        CHKSTAT_RTN("SmsSetFilter (job filter)");
    }
    SmsCloseFilter( hFilter );


    return(bRet);
}


// ====================================================================
//
// This function sets filters appropriate for a packages container.
// It illustrates the use of packages filters.
//
// If no package filter is selected, then all packages will be retrieved.
//
// Package filter only uses the value field, values are:
//  "Workstation", "Server", "Inventory"
//
// NOTE: minimal error checking at the moment.
//
// ====================================================================
BOOL setPkgFilters( HANDLE hConnect, HANDLE hContainer )
{

    SMS_STATUS stat = SMS_OK;
    HANDLE hFilter;
    BOOL done = FALSE;
    char reply[10];
    BOOL bRet = TRUE;
    BOOL bTokenSelected = FALSE;    // Has token been added to filter?
    const INT iIndex = -2;          // Token index in filter. -2 means add to end.

    printf("Select filters for packages container.\n");
    printf("Choices are: \n\tWorkstation 'w'\n\tServer 's'\n\tInventory 'i'\n");

    stat = SmsCreateFilter( PACKAGE_FILTER, hConnect, &hFilter );
    CHKSTAT_RTN("SmsCreateFilter (package filter)");

    TOKEN PkgToken;
    memset( &PkgToken, 0, sizeof(TOKEN) );

    while (!done) {
        printf("\nSelect one of [wsi] 'x' to complete: ");
        gets(reply);

        switch (reply[0]) {
        case 'W': case 'w':
            // Workstation packages
            strcpy( PkgToken.szName, "PackageType" );
            strcpy( PkgToken.szValue, "Workstation" );
            PkgToken.dwOp = QOP_STR_EQ;
            stat = SmsAddToken( hFilter, OP_OR, &PkgToken, iIndex );
            CHKSTAT_RTN("SmsAddToken (package filter)");
            bTokenSelected = TRUE;
            break;

        case 'S': case 's':
            // Server share packages
            strcpy( PkgToken.szName, "PackageType" );
            strcpy( PkgToken.szValue, "Server" );
            PkgToken.dwOp = QOP_STR_EQ;
            stat = SmsAddToken( hFilter, OP_OR, &PkgToken, iIndex );
            CHKSTAT_RTN("SmsAddToken (package filter)");
            bTokenSelected = TRUE;
            break;

        case 'I': case 'i':
            // Inventory package.
            strcpy( PkgToken.szName, "PackageType" );
            strcpy( PkgToken.szValue, "Inventory" );
            PkgToken.dwOp = QOP_STR_EQ;
            stat = SmsAddToken( hFilter, OP_OR, &PkgToken, iIndex );
            CHKSTAT_RTN("SmsAddToken (package filter)");
            bTokenSelected = TRUE;
            break;

        case 'X':
        case 'x':
            // finished
            done = TRUE;
            break;

        default:
            // give message again
            printf("Invalid response\n");
            printf("Choices are: \n\tWorkstation 'w'\n\tServer 's'\n\tInventory 'i'\n");
        }
    }


    // Only apply the filter if a token has been selected.
    // ---------------------------------------------------
    if (bTokenSelected) {
        stat = SmsSetFilter( hContainer, hFilter );
        CHKSTAT_RTN("SmsSetFilter (package filter)");
    }

    SmsCloseFilter( hFilter );


    return(bRet);
}



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







// ====================================================================
// DidRequestHelp
//
// Check the program's arguments to see if the user asked for
// the help screen to be displayed.
//
// Parameters:
//      int argc
//          The argc value from main(argc, argv)
//
//      char** argv
//          The argv value from main(argc, argv)
//
// Returns:
//      TRUE if command line parameters included a request
//      for help to be displayed.
//
// ====================================================================
BOOL DidRequestHelp( int argc, char **argv )
{
    if (argc == 2  && (strcmp(argv[1], "-help") == 0)) {
        return(TRUE);
    }
    else {
        return(FALSE);
    }
}


// ====================================================================
// DisplayHelp
//
// This function displays the samples help screen.
//
// Parameters:
//      None
//
// Returns:
//      Nothing.
//
// ====================================================================
void DisplayHelp()
{
    printf("\n\n");
    printf("********************************************************\n");
    printf("* testall.exe:                                         *\n");
    printf("*                                                      *\n");
    printf("* This is a sample program for the SMS SDK. It can be  *\n");
    printf("* used to view the contents of site, job, and package  *\n");
    printf("* folders in the SMS database.                         *\n");
    printf("*                                                      *\n");
    printf("* Syntax:                                              *\n");
    printf("*     testall.exe [-help]                              *\n");
    printf("*                                                      *\n");
    printf("* Switches:                                            *\n");
    printf("*     -help       Display this help screen.            *\n");
    printf("*                                                      *\n");
    printf("********************************************************\n");
    printf("\n");
}



// ====================================================================
// DisplayGreeting
//
// Display the initial greeting banner.
//
// Parameters:
//     None.
//
// Returns:
//     Nothing.
//
// ====================================================================
void DisplayGreeting()
{
    // For this sample, the greeting is identical to the help screen.
    //===============================================================
    DisplayHelp();
}



/* EOF: testall.cpp */

