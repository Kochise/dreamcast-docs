// ====================================================================
//
//  File: attribut.cpp
//
//  Copyright (C) 1994, 1995 Microsoft Corp.
//
//  Author:
//      Jonathan Shuval     Microsoft Corp.
//
//  This program illustrates possible uses of the following SMS APIs:
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
//      SmsGetNextFolder
//
//      SmsCreateFilter
//      SmsAddToken
//      SmsCloseFilter
//
//      SmsGetFolderType
//      SmsGetFolderID
//      SmsCloseFolder
//      SmsGetScalarCount
//      SmsGetNextScalar
//
//
//  See the readme.txt file in this directory for a decription of this
//  sample.
//
// ====================================================================
//


// ====================================================================
//
//  Includes.
//
// ====================================================================
#include <afx.h>
#include <smsapi.h>             // Header for the APIs.
#include <time.h>               // For converting time scalars into strings.

// Include the GetStatusName function.
// -------------------------------------
#include "..\common\status.inc"


// ====================================================================
//
//  Defines.
//
// ====================================================================
#define CCH_MAXINPUT 256        // Length for some string buffers.


// ====================================================================
//
//  Globals.
//
// ====================================================================
HANDLE ghConnect;               // Connection handle.


// ====================================================================
//
//  Local prototypes.
//
// ====================================================================


// Set filters.
// -------------------------------------------------------------
BOOL setFilters( HANDLE hContainer );


// Displays folders (recursively).
// -------------------------------------------------------------
void DisplayFolder( DWORD ctFolder, HANDLE hFolder );


// Retrieves, decodes, and displays a folder's scalars.
// -------------------------------------------------------------
void DisplayScalars( HANDLE hFolder );


// Prompt the user for input and return the reply.
// -------------------------------------------------------------
void InputString( const char *pszMessage, char *pszResult );


// Connect to the SMS datasource.
// -------------------------------------------------------------
HANDLE ConnectToDatasource();


// Display the help message.
// -------------------------------------------------------------
void DisplayHelp();


// Display the greeting.
// -------------------------------------------------------------
void DisplayGreeting();


// Check if there was a request for help on the command line.
// -------------------------------------------------------------
BOOL DidRequestHelp( int argc, char **argv );


// Display an error message with its SMS status value.
// -------------------------------------------------------------
void DisplaySmsError( const char *pszMessage, SMS_STATUS stat );


// Get the string equivalence for an SMS status code.
// -------------------------------------------------------------
const char *GetStatusName( SMS_STATUS stat );






// ====================================================================
//  The work starts here.
// ====================================================================
void main( int argc, char **argv )
{

    // Check to see if this is a request to display the help
    // screen. If so, display it. Otherwise, display a greeting
    // banner.
    // =========================================================
    if (DidRequestHelp(argc, argv)) {
        DisplayHelp();
        return;
    }
    else {
        DisplayGreeting();
    }


    SMS_STATUS stat;                    // Return from the APIs.
    HANDLE hContainer;                  // Handle to a container.


    // Get and display the SMS API version.
    // ------------------------------------
    char *pszVersion;                   // Receives pointer to the version string.
    SmsAPIVer( &pszVersion );           // Get version
    printf("Using %s\n", pszVersion);   // and print it.


    //===========================================
    // Connect to the SMS datasource.
    //===========================================
    ghConnect = ConnectToDatasource();
    if (ghConnect == NULL) {
        return;
    }


    // Open the site container.
    // ========================
    stat = SmsOpenContainer( C_SITE, ghConnect, &hContainer );
    if (stat != SMS_OK) {
        DisplaySmsError("SmsOpenContainer failed", stat);
        SmsDataSourceDisconnect( ghConnect );
        return;
    }

    // Construct and apply filters.
    // ============================
    BOOL bRet = setFilters( hContainer );
    if (!bRet) {
        // Error message already displayed, but give a general one as well.
        printf("Problem with setting filters.\n");
        SmsDataSourceDisconnect( ghConnect );
        return;
    }

    // Select all folders matching our filters.
    // ========================================
    stat = SmsPopulate( hContainer, POP_SYNC, NULL );
    if (stat != SMS_OK) {
        DisplaySmsError("Bad return from SmsPopulate", stat);
        SmsCloseContainer( hContainer );
        SmsDataSourceDisconnect( ghConnect );
        return;
    }

    printf("========   Enumerating site hierarchy   =============\n");

    // For each folder in the list enumerate its properties.
    // What we do is open all folders in a loop and  then
    // close the container. The open container causes ALL
    // folders to be left open until the container closes.
    // -----------------------------------------------------
    CObArray topFolders;
    HANDLE hFolder;

    // Open all top-level folders.
    // ===========================
    while ((stat = SmsGetNextFolder( hContainer, F_ANY, &hFolder )) == SMS_OK) {

        // Store the folder's handle for later processing.
        // -----------------------------------------------
        topFolders.Add( (CObject *)hFolder );
    }

    printf("*** Retrieved %d folders ***\n", topFolders.GetSize());

    // Check why we exited the loop.
    // -----------------------------
    if (stat != SMS_NO_MORE_DATA) {
        DisplaySmsError("Failed to retrieve folder", stat);
    }

    // Close the container.
    // --------------------
    SmsCloseContainer( hContainer );


    // Now (recursively) process each top-level folder.
    // ================================================
    for (int iLoop = 0; iLoop < topFolders.GetSize(); iLoop++) {

        // Retrieve the handle.
        // --------------------
        hFolder = (HANDLE)topFolders[iLoop];

        printf("*** Top folder #%d\n", iLoop);

        // Display the folder.
        // -------------------
        DisplayFolder( iLoop, hFolder );

        // Note: the folder is closed inside DisplayFolder.
    }

    printf("********* All done ***************\n");

    stat = SmsDataSourceDisconnect( ghConnect );


}  /* main */




// ====================================================================
//
//  DisplayFolder
//
//  Display the folder's details and scalars, then recursively process
//  any sub-folders.
//
//  Parameters:
//      DWORD ctFolder
//          The number of sub-folders at this level of the container/folder
//          hierarchy.
//
//      HANDLE hFolder
//          The handle of the folder to display.
//
//  Returns: Nothing.
//
// ====================================================================

// Simple macro for checking status.
#define CHKSTAT(str) if (stat != SMS_OK && stat != SMS_MORE_DATA) { \
        printf(str); printf(": %d\n", stat); \
        return; }

void DisplayFolder( DWORD ctFolder, HANDLE hFolder )
{

    SMS_STATUS stat;
    HANDLE hSubFolder;
    DWORD fType;                        // type of folder we're dealing with.
    char szfType[30];                   // type as a string.
    DWORD totFolders;                   // Total number of sub-folders of
                                        // all types.
    char szFolderID[100];               // This folder's ID.
    DWORD ctScalars;                    // How many scalars in this folder.


    // Get object type and id.
    // -----------------------
    stat = SmsGetFolderID( hFolder, szFolderID );
    CHKSTAT("SmsGetFolderID");

    stat = SmsGetFolderType( hFolder, &fType, szfType );
    CHKSTAT("SmsGetFolderType");

    printf("===================================================\n");
    printf("[%d] Folder %s is a %s\n", ctFolder, szFolderID, szfType);

    // How many scalars and folders in this folder.
    // --------------------------------------------------------
    stat = SmsGetScalarCount( hFolder, &ctScalars );
    stat = SmsGetFolderCount( hFolder, F_ANY, &totFolders );
    printf("\tContains %d scalars and %d folders\n", ctScalars, totFolders);
    DisplayScalars( hFolder );


    // Allocate space for sub-folder handles.
    // --------------------------------------
    CObArray subFolders;
    subFolders.SetSize( totFolders );


    // This loop gets the sub-folder IDs and displays them.
    // ====================================================
    char szSubFolderID[100];
    DWORD ctFolders;

    for (ctFolders = 0; ctFolders < totFolders; ctFolders++) {

        // Get a handle to a sub-folder.
        // -----------------------------
        stat = SmsGetNextFolder( hFolder, F_ANY, &hSubFolder );
        CHKSTAT("SmsGetNextFolder");
        subFolders.SetAt( ctFolders, (CObject *)hSubFolder );

        // Get and display the sub-folder's ID.
        // ------------------------------------
        stat = SmsGetFolderID( hSubFolder, (char *)szSubFolderID );
        CHKSTAT("SmsGetFolderID");
        printf("Sub-folder #%d: %s\n", ctFolders, szSubFolderID);
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
        hSubFolder = (HANDLE)subFolders[ctFolders];
        DisplayFolder( ctFolders, hSubFolder );
    }

    // Free the folder handle array.
    // -----------------------------
    subFolders.RemoveAll();

}  /* DisplayFolder */



// ====================================================================
//
//  DisplayScalars
//
//  Display all the scalars for the folder.
//
//  Parameters:
//      HANDLE hFolder
//          This is the folder handle. Display this folder's scalars.
//
//  Returns:  Nothing.
//
// ====================================================================

#define MY_BUFF_SIZE 100            // Buff size for strings and binaries.
// NOTE: this is deliberately set lower than the maximum (SMS_DATA_BUFF_SIZE).
// By doing this we can exercise the code for checking if the buffer is too
// small for the data (see 'Check for buffer being too small' below).

void DisplayScalars( HANDLE hFolder )
{
    SMS_STATUS stat = SMS_OK;
    SCALAR scalar;
    char szName[50];                // buffer for name
    char szValue[MY_BUFF_SIZE];     // buffer for value
    BYTE byValue[MY_BUFF_SIZE];     // Buffer for binary scalars.
    scalar.pszName  = szName;
    scalar.pszValue = szValue;
    scalar.pValue   = byValue;

    char *pszTime;                  // For time scalars.
    CTime tTime;                    //  ditto
    CString sTime;                  //  ditto


    while (1) {

        scalar.dwLen = MY_BUFF_SIZE-1;       // must tell him the size

        stat = SmsGetNextScalar( hFolder, &scalar);
        if (stat != SMS_OK && stat != SMS_MORE_DATA) {
            break;
        }

        // Check for buffer being too small.
        // ---------------------------------
        if (stat == SMS_MORE_DATA) {
            printf("Receive buffer too small, should be %d. Data truncated\n",
                            scalar.dwLen);
            // NOTE: at this point we could retrieve the scalar by name
            // after allocating a larger buffer.
        }


        // Check scalar type, display accordingly.
        // ---------------------------------------
        switch (scalar.scType) {
        case SCALAR_STRING:
            printf("\t%25s (string): %s\n", scalar.pszName, scalar.pszValue);
            break;

        case SCALAR_INT:
            printf("\t%25s (Integer): %ld\n", scalar.pszName, scalar.dwValue);
            break;

        case SCALAR_TIME:
            // Check if we have a string equivalence. If so use it.
            if (scalar.bStringEquivalence) {
                pszTime = scalar.pszValue;

            } else {
                // Use time functions to make a string out of it.
                // NOTE: we really need to get rid of trailing newline.
                tTime = scalar.tValue;
                sTime = tTime.Format( "%m/%d/%y %I:%M %p" );
                pszTime = (char *)(const char *)sTime;
            }
            printf("\t%25s (time): %s", scalar.pszName, pszTime);
            break;

        case SCALAR_BINARY:
            // In this sample we won't display the binary data.
            // Just tell the user its size.
            printf("\t%25s (Binary - this is its size): %ld\n", scalar.pszName, scalar.dwLen);
            break;
        }
    }

    // Why did we exit (other than no more scalars)?
    // ---------------------------------------------
    if (stat != SMS_NO_MORE_DATA) {
        DisplaySmsError("Bad return from Scalar access: %d\n", stat);
    }

    // Terminate with newline.
    // -----------------------
    printf("\n");

}


// ********************************************************************
//      Helper functions.
// ********************************************************************


// ====================================================================
//
// setFilters
//
// Create a new filter and apply it to the specified container.
//
// Parameters:
//      HANDLE hContainer
//          This is the handle of the container to which the filter
//          will be applied to.
//
// Returns:
//      BOOL
//          TRUE if no errors occcured, otherwise FALSE.
//
// ====================================================================


#define CHECK(str) if (stat != SMS_OK) {       \
        DisplaySmsError(str, stat);            \
        return(FALSE);                         \
    }


BOOL setFilters( HANDLE hContainer )
{

    printf("This test will set the following filters:\n");
    printf("        Site filter: RootSite\n");
    printf("Architecture filter: Personal Computer\n");
    printf("   Attribute filter: (MS|ID|1.0) Name\n");
    printf("                   : (MS|ID|1.0) SMSLocation\n");
    printf("                   : (MS|ID|1.0) NetCardID\n");

    SMS_STATUS stat;
    HANDLE hFilter;
    TOKEN Token;

    // Define a filter: root site.
    // ----------------------------------
    memset( &Token, 0, sizeof(TOKEN) );             // Clear it.
    stat = SmsCreateFilter( SITE_FILTER, ghConnect, &hFilter );
    strcpy( Token.szName, "RootSite" );
    stat = SmsAddToken( hFilter, OP_OR, &Token, -2 );
    CHECK("SmsAddToken (site)");

    stat = SmsSetFilter( hContainer, hFilter );
    SmsCloseFilter( hFilter );
    CHECK("SmsSetFilter (site)");



    // =========================================================
    // Must set an architecture filter else we get no machines.
    // =========================================================
    memset( &Token, 0, sizeof(TOKEN) );             // Clear it.
    stat = SmsCreateFilter( ARCHITECTURE_FILTER, ghConnect, &hFilter );
    strcpy( Token.szName, "Architecture" );
    strcpy( Token.szValue, "Personal Computer" );
    Token.dwOp = QOP_STR_EQ;
    stat = SmsAddToken( hFilter, OP_OR, &Token, -2 );
    CHECK("SmsAddToken (architecture)");
    stat = SmsSetFilter( hContainer, hFilter );
    SmsCloseFilter( hFilter );
    CHECK("SmsSetFilter (architecture)");


    // =========================================================
    // Attribute filter (MICROSOFT|IDENTIFICATION|1.0)
    // Three tokens:
    //  Name
    //  SMSLocation
    //  NetCardID
    // =========================================================
    memset( &Token, 0, sizeof(TOKEN) );             // Clear it.
    stat = SmsCreateFilter( ATTRIBUTE_FILTER, ghConnect, &hFilter );

    strcpy( Token.szArchitecture, "Personal Computer" );
    strcpy( Token.szGroupClass, "MICROSOFT|IDENTIFICATION|1.0" );
    strcpy( Token.szAttributeName, "Name" );
    stat = SmsAddToken( hFilter, OP_OR, &Token, -2 );
    CHECK("SmsAddToken (attribute:name)");

    strcpy( Token.szAttributeName, "SMSLocation" );
    stat = SmsAddToken( hFilter, OP_OR, &Token, -2 );
    CHECK("SmsAddToken (attribute:Location)");

    strcpy( Token.szAttributeName, "NetCardID" );
    stat = SmsAddToken( hFilter, OP_OR, &Token, -2 );
    CHECK("SmsAddToken (attribute:NetCardID)");

    stat = SmsSetFilter( hContainer, hFilter );
    SmsCloseFilter( hFilter );
    CHECK("SmsSetFilter (attribute)");


    return( TRUE );

}  /* setFilters */




// ====================================================================
//
// InputString
//
// Prompt the user to input a string and return the string in the
// specified buffer.
//
// Parameters:
//      const char *pszMessage
//          The user prompt to display.
//
//      char *pszResult
//          Pointer to the buffer where the user's input will be returned.
//
// Returns;
//      The user's input is returned via the given buffer.
//
// ====================================================================
void InputString( const char *pszMessage, char *pszResult )
{
    printf("%s: ", pszMessage);
    gets(pszResult);
}




// ====================================================================
//
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
//
// DidRequestHelp
//
// Check the program's arguments to see if the user asked for
// the help screen to be displayed.
//
// Parameters:
//      int argc
//          The argc value from main(argc, argv)
//
//      char **argv
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
        return( TRUE );
    }
    else {
        return( FALSE );
    }

}




// ====================================================================
//
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
    printf("***********************************************************\n");
    printf("* attribut.exe:                                           *\n");
    printf("*                                                         *\n");
    printf("* SMS API Example: Test attribute filters.                *\n");
    printf("*                                                         *\n");
    printf("* This sample illustrates the use of the Attribute filter *\n");
    printf("* that is applied to a site container in order to         *\n");
    printf("* enumerate specified properties of a machine             *\n");
    printf("* (architecture Personal Computer).                       *\n");
    printf("*                                                         *\n");
    printf("* Applying an attribute filter in order to enumerate      *\n");
    printf("* machines is considerably faster than setting group      *\n");
    printf("* filters and then retrieving specified machine group     *\n");
    printf("* scalars (machine properties).                           *\n");
    printf("*                                                         *\n");
    printf("* Syntax:                                                 *\n");
    printf("*     attribut.exe [-help]                                *\n");
    printf("*                                                         *\n");
    printf("* Switches:                                               *\n");
    printf("*     -help       Display this help message.              *\n");
    printf("*                                                         *\n");
    printf("***********************************************************\n");
    printf("\n");
}



// ====================================================================
//
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



/* EOF: attribut.cpp */

