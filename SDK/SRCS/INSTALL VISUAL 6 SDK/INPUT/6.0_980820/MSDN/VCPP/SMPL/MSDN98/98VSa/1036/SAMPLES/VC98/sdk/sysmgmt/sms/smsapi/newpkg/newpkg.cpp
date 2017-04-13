//**************************************************************************
// Copyright (C) 1995 by Microsoft Corporation.
//
//  File: newpkg.cpp
//
//  DESCRIPTION:
//
//  This program illustrates how to use the SMS SDK to view, create, and
//  delete packages.  It can be used to create sharing and workstation
//  packages but not inventory packages.  Also the packages created with
//  only a single sub-folder.  Thus the packages it creates can not be for
//  both sharing and workstations.
//
//
//  PROGRAM FLOW:
//
//  After logging on to a datasource, a package container is created and
//  populated. The program then enters a loop asking whether the user
//  wants to view the next package folder, delete the currently viewed
//  folder, or create a new folder.
//
//  Author: Larry A. French
//
//==========================================================================
//  The following API calls are used in this program.
//
//      SmsDataSourceConnect
//      SmsDataSourceDisconnect
//      SmsOpenContainer
//      SmsCloseContainer
//      SmsCreateFolder
//      SmsPopulate
//      SmsGetNextFolder
//      SmsDescribeFolder
//      SmsGetFolderID
//      SmsGetFolderType
//      SmsGetFolderCount
//      SmsLinkFolder
//      SmsUnlinkFolder
//      SmsCommitFolder
//      SmsRewind
//      SmsCloseFolder
//      SmsGetScalarCount
//      SmsSetScalar
//      SmsGetNextScalar
//
//**************************************************************************


// ====================================================================
//  Includes.
// ====================================================================
#include <afx.h>
#include <stdlib.h>                 // for itoa
#include <smsapi.h>                 // Header for the APIs.
#include <time.h>                   // for time functions.

// Include the GetStatusName function.
// -------------------------------------
#include "..\common\status.inc"


// ====================================================================
//
//      Defines.
//
// ====================================================================

#define CCH_MAXSTRING   256
#define MAX_CREATE      100

#define PACKAGE_PERMISSIONS (PACKAGE_USER_READ | PACKAGE_USER_WRITE | PACKAGE_GUEST_READ)



// ====================================================================
//
//      Prototypes.
//
// ====================================================================

void DisplayScalars( HANDLE hFolder );
void ViewFolder( HANDLE hFolder );
HANDLE CreatePackageFolder( HANDLE hFolderParent );
time_t ReadTime();
BOOL DidRequestHelp(int argc, char** argv);
void DisplayHelp();
void DisplayGreeting();
BOOL UserSaysYes(const char* pszPrompt);
HANDLE ConnectToDatasource();
void DisplaySmsError(const char* pszMessage, SMS_STATUS stat);
const char* GetStatusName(SMS_STATUS stat);
void InputString(const char* pszMessage, char* pszResult);




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


    SMS_STATUS stat;
    HANDLE hConnect;
    HANDLE hContainerPkg;
    DWORD numFolders;
    DWORD numFoldersMax;
    DWORD dwFolder;
    DWORD dwIndex;


    // Connect to the data source.  If the connect fails, give up.
    // Note that a status message will be displayed by ConnectToDatasource.
    //=====================================================================
    hConnect = ConnectToDatasource();
    if (hConnect == NULL) {
        return;
    }

    // Open package container.
    // ==============================================================
    stat = SmsOpenContainer( C_PACKAGE, hConnect, &hContainerPkg );
    if (stat != SMS_OK) {
        printf("SmsOpenContainer failed: %d\n", stat);
        SmsDataSourceDisconnect( hConnect );
        return;
    }

    // Any filters would be set here.


    // Select all folders matching our filters.
    // ========================================
    stat = SmsPopulate( hContainerPkg, POP_SYNC, NULL);
    if (!(stat == SMS_OK || stat==SMS_EMPTY)) {
        printf("Bad return from SmsPopulate: %d\n", stat);
        SmsCloseContainer( hContainerPkg );
        SmsDataSourceDisconnect( hConnect );
        return;
    }


    stat = SmsGetFolderCount( hContainerPkg, F_ANY, &numFolders);
    if (stat != SMS_OK) {
        DisplaySmsError("SmsGetFolderCount failed on package container", stat);
        return;
    }

    printf("==========  Container has %d folders  =========\n\n", numFolders );


    // Allocate enough space to hold handles for all of the folders currently
    // in the container, plus more than enough space to hold all of the folders
    // that we will create.
    //=========================================================================
    numFoldersMax = numFolders + MAX_CREATE;

    HANDLE *phFolders = (HANDLE *)malloc(numFoldersMax * sizeof(HANDLE));
    HANDLE hFolder;

    // Open all top-level folders.
    // ---------------------------
    for (dwFolder = 0; dwFolder < numFolders; dwFolder++) {
        stat = SmsGetNextFolder( hContainerPkg, F_ANY, &hFolder );
        if (stat != SMS_OK) {
            printf("Error in retrieving a folder: %d\n", stat);
            break;
        }

        phFolders[dwFolder] = hFolder;
    }


    // Now we enter a loop asking the user whether they want to
    // view the next folder, Delete the folder just displayed,
    // or create a new folder.
    // =========================================================
    BOOL bDoQuit = FALSE;
    char szReply[CCH_MAXSTRING];
    dwFolder = 0;

    while (!bDoQuit) {

        printf("\n\n");
        printf("*******************************************\n");
        printf("* Enter a command:                        *\n");
        printf("*    N      View next folder.             *\n");
        printf("*    P      View previous folder.         *\n");
        printf("*    V      View current folder.          *\n");
        printf("*    D      Delete current folder.        *\n");
        printf("*    C      Create new folder.            *\n");
        printf("*    X      Exit.                         *\n");
        printf("*******************************************\n");
        printf("\n");

        InputString("[NPVDCX]", szReply);

        switch (szReply[0]) {
        case 0:
        case 'N': case 'n':

            // Fall through to the "View" command
            // =========== View next folder ====================
            if ((dwFolder + 1) < numFolders) {
                dwFolder++;
                ViewFolder( phFolders[dwFolder] );
            } else
                printf("At end of folder list\n");
           break;

        case 'P': case 'p':
            if (dwFolder > 0) {
                --dwFolder;
                ViewFolder(phFolders[dwFolder]);
            } else {
                printf("At first folder\n");
            }
            break;

        case 'V': case 'v':
            if (dwFolder >= 0 && dwFolder < numFolders) {
                ViewFolder( phFolders[dwFolder]);
            } else {
                printf("View: No such folder: %d\n", dwFolder);
            }
            break;

        case 'D': case 'd':
            // =========== Delete current folder ===============

            // Check we have a folder to delete.
            if (dwFolder >= numFolders || dwFolder < 0) {
                printf("Delete: No such folder: %d\n", dwFolder);
                break;
            }

            hFolder = phFolders[dwFolder];

            if (!UserSaysYes("Are you sure you want to delete this folder")) {
                printf("Delete cancelled\n");
                break;
            }

            stat = SmsUnlinkFolder( hFolder );
            if (stat != SMS_OK) {
                DisplaySmsError("Delete: UnlinkFolder failed", stat);
                break;
            }
            stat = SmsCommitFolder( hFolder );
            if (stat != SMS_OK) {
                DisplaySmsError("Delete: commit folder failed", stat);
                break;
            }

            // Close the folder so that its memory will be deallocated
            // when all other references to it go away.  Note that the
            // container retains a reference to its folder, so the memory
            // will not actually be deallocated until the container is
            // also closed.
            //==========================================================
            stat = SmsCloseFolder(hFolder);
            if (stat != SMS_OK) {
                DisplaySmsError("Delete: close folder failed", stat);
                break;
            }

            // Remove the folder's handle from the handle table.
            //==================================================
            for(dwIndex = dwFolder; dwIndex < (numFolders - 1); ++dwIndex) {
                phFolders[dwIndex] = phFolders[dwIndex+1];
            }

            // Adjust the folder index and folder count.
            // since there is now one less folder in the table.
            //=================================================
            --numFolders;
            if ((dwFolder > 0) && (dwFolder >= numFolders)) {
                --dwFolder;
            }
            printf("Folder deleted\n");
            break;

        case 'C': case 'c':
            // =========== Create new folder ===================

            // Check to see if the folder handle array is already
            // full.  If so, then display an error message and
            // begin a new command.
            //===================================================
            if (numFolders >= numFoldersMax) {
                printf("Can't create a new folder because the folder\n");
                printf("handle array is full.\n");
                printf("\n");
                break;
            }

            HANDLE hFolderPkg;
            hFolderPkg = CreatePackageFolder(hContainerPkg);
            if (hFolderPkg != NULL) {
                dwFolder = numFolders;
                phFolders[numFolders++] = hFolderPkg;
            }
            break;

        case 'X': case 'x':
            // Terminate.
            bDoQuit = TRUE;
            break;

        default:
            // print the message again.
            printf("Actions are: N(ext folder), D(elete folder), C(reate folder)\n");
            printf("Type x to exit\n");
            break;
        }
    }

    // Close all of the package folders so that their memory will
    // be deallocated (when the container is closed).
    //===========================================================
    for (dwFolder=0; dwFolder < numFolders; ++dwFolder) {
        stat = SmsCloseFolder(phFolders[dwFolder]);
        if (stat != SMS_OK) {
            DisplaySmsError("Failed to close a package folder", stat);
        }
    }


    // Close the container.
    //=====================
    stat = SmsCloseContainer( hContainerPkg );
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to close the package container", stat);
    }

    // Disconnect from the datasource.
    //================================
    stat = SmsDataSourceDisconnect( hConnect );
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to disconnecct from the datasource", stat);
    }

    // Deallocate memory used for folder handles.
    //===========================================
    free( phFolders );

}  /* main */






//***************************************************************************
// ReadTime
//
// Ask the user to enter a time string and convert it to a time_t value.
//
// Input: None.
//
// Returns:
//      time_t     The time value the user entered.
//
//
//***************************************************************************
time_t ReadTime()
{
    char szTime[CCH_MAXSTRING];
    InputString("Enter time in the form mm/dd/yy hh:mm ", szTime);


    int mon, day, year, hour, min;
    time_t today;
    time( &today );

    // Get the month (1..12)
    mon = (szTime[0] - '0') * 10 + (szTime[1]) - '0';
    mon--;
    if (mon < 0 || mon > 11) {
        printf("Month wrong (valid 01-12)\n");
        return(today);
    }

    // Day (1..31)
    day = (szTime[3] - '0') * 10 + (szTime[4] - '0');
    if (day < 1 || day > 31) {
        printf("Day wrong (Valid 01-07)\n");
        return(today);
    }

    // Year
    year = (szTime[6] - '0') * 10 + (szTime[7] - '0');
    if (year < 90 || year > 99) {
        printf("Year wrong (Valid 90-99)\n");
        return(today);
    }

    // Hour (0..23)
    hour = (szTime[9] - '0') * 10 + (szTime[10] - '0');
    if (hour < 0 || hour > 23) {
        printf("Hour wrong (Valid 00-23)\n");
        return(today);
    }

    // Minute (0..59)
    min = (szTime[12] - '0') * 10 + (szTime[13] - '0');
    if (min < 0 || min > 59) {
        printf("Minute wrong (Valid 00-59)\n");
        return(today);
    }

    // Format the time, we want a time_t.
    struct tm theTime;
    theTime.tm_mon   = mon;
    theTime.tm_mday  = day;
    theTime.tm_year  = year;
    theTime.tm_hour  = hour;
    theTime.tm_min   = min;
    theTime.tm_sec   = 0;
    theTime.tm_isdst = -1;

    time_t time = mktime( &theTime );
    return(time);
}




//**************************************************************************
// SetScalarString
//
// This function sets the value specified scalar to the given string
// value.
//
// Parameters:
//      HANDLE hFolder
//          The handle of the folder containing the scalar to modify.
//      char* pszName
//          The name of the scalar.
//      char* pszValue
//          The string that will be assigned to the scalar's value.
//
// Returns:
//      SMS_STATUS
//          The SMS status code.
//
// Note that the scalar specified must be of type SCALAR_STRING.
//***************************************************************************
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




//**************************************************************************
// SetScalarDword
//
// This function sets the value of the specified scalar to
// the given DWORD value.
//
// Parameters:
//      HANDLE hFolder
//          The handle of the folder containing the scalar to modify.
//      char* pszName
//          The name of the scalar.
//      DWORD dwValue
//          The DWORD value to set the scalar to.
//
// Returns:
//      SMS_STATUS
//          The SMS status code.
//
// Note that the scalar specified must be of type SCALAR_INT.
//***************************************************************************
SMS_STATUS SetScalarDword(HANDLE hFolder, char* pszName, DWORD dwValue)
{
    SCALAR sc;
    sc.pszName = pszName;
    sc.scType = SCALAR_INT;
    sc.dwValue = dwValue;


    SMS_STATUS stat;
    stat = SmsSetScalar(hFolder, &sc);
    return( stat );
}




//**************************************************************************
// GetPlatformSelection
//
// Prompt the user to select a one or more platforms.  The platforms are
// selected by entering a comma separated list of platform indexes.  These
// platform indexes are converted to the platforms flags value for the SDK.
//
// Parameters:  None.
//
// Returns:
//      The SMS SDK platform flags value.
//***************************************************************************
DWORD GetPlatformSelection()
{
    printf("\n\n");
    printf("**********************************************\n");
    printf("* Select a platform from the following list. *\n");
    printf("**********************************************\n");
    printf("   1) MS-DOS \n");
    printf("   2) Windows 3.1\n");
    printf("   3) Windows 95\n");
    printf("   4) Windows NT (X86)\n");
    printf("   5) Windows NT (Mips)\n");
    printf("   6) Windows NT (Alpha)\n");
    printf("   7) Macintosh\n");
    printf("\n");

    DWORD dwPlatforms = 0;
    char szReply[CCH_MAXSTRING];
    InputString("Enter a comma separated list of platform number(s)", szReply);
    printf("\n");

    // Scan through the reply string and set the bits
    // dwPlatforms to correspond to the platform(s) specified
    // by the user.  Note that the list is a string of comma
    // separated digits.
    //======================================================
    const char* pszReply = szReply;
    while (*pszReply) {
        if (*pszReply < '1' || *pszReply > '7') {
            // An invalid character is present in the
            // reply.  Flag this error by returning zero.
            //==========================================
            dwPlatforms = 0;
            break;
        }

        // Interpret the platform selector character.
        //===========================================
        switch(*pszReply++) {
        case '1':
            dwPlatforms |= PLTFRM_MSDOS;
            break;
        case '2':
            dwPlatforms |= PLTFRM_WIN16;
            break;
        case '3':
            dwPlatforms |= PLTFRM_WIN95;
            break;
        case '4':
            dwPlatforms |= PLTFRM_WIN32_X86;
            break;
        case '5':
            dwPlatforms |= PLTFRM_WIN32_MIPS;
            break;
        case '6':
            dwPlatforms |= PLTFRM_WIN32_ALPHA;
            break;
        case '7':
            dwPlatforms |= PLTFRM_MACINTOSH;
            break;
        }

        // Skip any trailing whitespace after the digit.
        //==============================================
        while (*pszReply == ' ' || *pszReply=='\t') {
            ++pszReply;
        }

        // Skip the comma.
        //================
        if (*pszReply == ',') {
            ++pszReply;
        }

        // Skip white space preceding the next digit.
        //=========================
        while (*pszReply == ' ' || *pszReply=='\t') {
            ++pszReply;
        }

    }

    return( dwPlatforms );
}






//**************************************************************************
// ConnectToDatasource
//
// Get the datasource connection information from the user and use it
// to connect to the datasource.
//
// Parameters:  None.
//
// Returns:
//      The connection handle or NULL if the connection failed.
//***************************************************************************
HANDLE ConnectToDatasource()
{
    // Get the information we need to connect to the
    // data source from the user.
    //==============================================
    char szServer[CCH_MAXSTRING];
    char szUser[CCH_MAXSTRING];
    char szPasswd[CCH_MAXSTRING];
    char szDatabase[CCH_MAXSTRING];

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







//**************************************************************************
// ViewFolder
//
//  Display the folder contents.  This version only displays the folder name
//  and type, number of scalars, and the scalars. Other information not
//  relevant.
//
//  NOTE: no error checking.
//
// Parameters:
//      HANDLE hFolder
//          The handle of the folder to view.
//
// Returns: Nothing.
//
//**************************************************************************
void ViewFolder( HANDLE hFolder )
{
    char szFolderID[SMS_DATA_BUFF_SIZE + 1];        // This folder's ID.
    char szfType[SMS_DATA_BUFF_SIZE + 1];           // Folder's tag.
    DWORD fType;                        // Folder's type.
    DWORD ctScalars;                    // How many scalars in this folder.
    SMS_STATUS stat;


    // Get folder ID and type.
    // -----------------------
    stat = SmsGetFolderID( hFolder, szFolderID );
    if (stat == SMS_NEW_FOLDER) {
        strcpy( szFolderID, "New folder without an ID yet" );

    }
    else if (stat != SMS_OK) {
        DisplaySmsError("ViewFolder: can't get folder ID", stat);
        strcpy( szFolderID, "Couldn't get the folder ID" );
    }

    printf("============== %s ===========\n", szFolderID);

    stat = SmsGetFolderType( hFolder, &fType, szfType );
    if (stat != SMS_OK) {
        DisplaySmsError("ViewFolder: can't get folder type", stat);
    }

    printf("SCALARS FOR FOLDER %s\n", szFolderID);

    // Get count of scalars.
    // ---------------------
    stat = SmsGetScalarCount( hFolder, &ctScalars );
    if (stat != SMS_OK) {
        DisplaySmsError("ViewFolder: can't get scalar count", stat);
    }
    printf("%s (%s) contains %d scalars\n", szFolderID, szfType, ctScalars);


    // Display the scalars.
    // --------------------
    DisplayScalars( hFolder );


    // Get the folder count
    DWORD ctFolders;
    stat = SmsGetFolderCount(hFolder, F_ANY, &ctFolders);
    printf("%s (%s) contains %d sub-folders\n", szFolderID, szfType, ctFolders);
    for (DWORD dwFolder = 0; dwFolder < ctFolders; ++dwFolder) {
        printf("Getting subfolder\n");
        HANDLE hSubFolder;
        stat = SmsGetNextFolder(hFolder, F_ANY, &hSubFolder);
        if (stat != SMS_OK) {
            DisplaySmsError("SmsGetNextFolder failed", stat);
            break;
        }

        ViewFolder(hSubFolder);

        // Close the sub-folder to avoid a memory leak.
        //============================================
        stat = SmsCloseFolder(hSubFolder);
        if (stat != SMS_OK) {
            DisplaySmsError("Failed to close an open folder", stat);
            break;
        }
    }


    SmsRewind(hFolder, RW_FOLDER | RW_SCALAR);

}  /* ViewFolder */





//*************************************************************************
// CreateWcl
//
// This method is called to create a WCL subfolder in
// a package folder.
//
// Parameters:
//      HANDLE hFolderPkg
//          This is the handle of the parent folder that the newly
//          created subfolder will be inserted into.  For WCL and
//          program item folders, the parent folder is a package
//          folder.
//
// Returns:
//      HANDLE
//          This is the handle of the newly created subfolder.
//
//*************************************************************************
HANDLE CreateWcl(HANDLE hFolderPkg)
{
    printf("\n\n");
    printf("*****************************************************\n");
    printf("* Creating the workstation command line sub-folder. *\n");
    printf("*****************************************************\n");
    printf("\n");


    HANDLE hFolderNew;
    SMS_STATUS stat;
    char szError[CCH_MAXSTRING];
    char szReply[CCH_MAXSTRING];
    DWORD dwPlatforms;

    // Create the WCL folder
    //======================
    stat = SmsCreateFolder( hFolderPkg, F_WCL, "", &hFolderNew );
    if (stat != SMS_OK) {
        sprintf(szError, "SmsCreateFolder failed to create the WCL folder");
        DisplaySmsError(szError, stat);
        return( NULL );
    }


    dwPlatforms = GetPlatformSelection();


    printf("\n\n");
    printf("*********************************************\n");
    printf("* Enter values for the WCL folder scalars.  *\n");
    printf("*********************************************\n");
    printf("\n");

    InputString("Name", szReply);
    SetScalarString(hFolderNew, "Name", szReply);

    InputString("Command", szReply);
    SetScalarString(hFolderNew, "Command", szReply);

    SetScalarDword(hFolderNew, "Flags", 0);
    SetScalarDword(hFolderNew, "Platforms", dwPlatforms);



    // Link the new WCL folder into the folder hierarchy.  Note that
    // this does not insert the folder into the datasource.  Only
    // SmsCommitFolder modifies the datasource.
    //==============================================================
    stat = SmsLinkFolder(hFolderNew);
    if ((stat != SMS_OK) && (stat != SMS_PARENT_NEEDS_COMMIT)) {
        sprintf(szError, "SmsLinkFolder failed to link the WCL folder");
        DisplaySmsError(szError, stat);
        return( NULL );
    }

    return( hFolderNew ) ;
}



//*************************************************************************
// CreateProgItem
//
// This method is called to create a program item subfolder in
// a package folder.
//
// Parameters:
//      HANDLE hFolderPkg
//          This is the handle of the parent folder that the newly
//          created subfolder will be inserted into.  For WCL and
//          program item folders, the parent folder is a package
//          folder.
//
// Returns:
//      HANDLE
//          This is the handle of the newly created subfolder.
//
//*************************************************************************
HANDLE CreateProgItem(HANDLE hFolderPkg)
{
    printf("\n\n");
    printf("*****************************************\n");
    printf("* Creating the program item sub-folder. *\n");
    printf("*****************************************\n");
    printf("\n");

    HANDLE hFolderNew;
    SMS_STATUS stat;
    char szReply[CCH_MAXSTRING];
    char szError[CCH_MAXSTRING];
    DWORD dwPlatforms;

    // Create the programe item folder
    //================================
    stat = SmsCreateFolder( hFolderPkg, F_PROGITEM, "", &hFolderNew );
    if (stat != SMS_OK) {
        sprintf(szError, "SmsCreateFolder failed to create the program item folder");
        DisplaySmsError(szError, stat);
        return( NULL );
    }



    // Set the value of the scalars for the program item.
    //===================================================
    dwPlatforms = GetPlatformSelection();



    printf("\n\n");
    printf("******************************************************\n");
    printf("* Enter values for the program item folder scalars.  *\n");
    printf("******************************************************\n");
    printf("\n");

    InputString("Description", szReply);
    SetScalarString(hFolderNew, "Description", szReply);

    InputString("Command line", szReply);
    SetScalarString(hFolderNew, "Command line", szReply);

    SetScalarDword(hFolderNew,  "Run minimized", FALSE);
    SetScalarDword(hFolderNew,  "Platforms", dwPlatforms);
    SetScalarString(hFolderNew, "Configure script file", "");
    SetScalarDword(hFolderNew,  "Search local flag", 1);
    SetScalarDword(hFolderNew,  "Drive mode", 1);

    InputString("Registry name", szReply);
    SetScalarString(hFolderNew, "Registry name", szReply);
    SetScalarDword(hFolderNew,  "Executable flag", TRUE);



    // Link the new WCL folder into the folder hierarchy.  Note that
    // this does not insert the folder into the datasource.  Only
    // SmsCommitFolder modifies the datasource.
    //==============================================================
    stat = SmsLinkFolder(hFolderNew);
    if ((stat != SMS_OK) && (stat != SMS_PARENT_NEEDS_COMMIT)) {
        sprintf(szError, "SmsLinkFolder failed to link the programe item folder");
        DisplaySmsError(szError, stat);
        return( NULL );
    }

    return( hFolderNew ) ;
}





//*************************************************************************
// CreatePackageFolder
//
// Create a new package folder
//
// Parameters:
//      HANDLE hPackageContainer
//          This is the handle to the package folder's parent, which
//          is a package container.
//
// Returns:
//      The package folder's handle.
//
// ====================================================================
HANDLE CreatePackageFolder(HANDLE hPackageContainer)
{
    SMS_STATUS stat;
    char szReply[CCH_MAXSTRING];
    HANDLE hFolderPkg = NULL;
    HANDLE hFolderWCL = NULL;
    HANDLE hFolderProgItem = NULL;



    stat = SmsCreateFolder( hPackageContainer, F_PACKAGE, "", &hFolderPkg );
    if (stat != SMS_OK) {
        DisplaySmsError("SmsCreateFolder failed to create the package folder.", stat);
        return( NULL );
    }


    printf("\n\n");
    printf("***************************************************\n");
    printf("* Creating package folder.  Select a package      *\n");
    printf("* type.                                           *\n");
    printf("*                                                 *\n");
    printf("*    S         Sharing.                           *\n");
    printf("*    W         Workstation.                       *\n");
    printf("***************************************************\n");
    printf("\n");

    InputString("SW: ", szReply);
    switch(szReply[0]) {
    case 'S': case 's':
        hFolderProgItem = CreateProgItem(hFolderPkg);
        break;
    case 'W': case 'w':
        hFolderWCL = CreateWcl(hFolderPkg);
        break;
    }




    printf("\n\n");
    printf("*************************************\n");
    printf("* Enter the package folder scalars. *\n");
    printf("*************************************\n");
    printf("\n");


    InputString("Package name", szReply);
    SetScalarString(hFolderPkg, "Name", szReply);

    InputString("Package comment", szReply);
    SetScalarString(hFolderPkg, "Comment", szReply);

    // If this package contains a workstation command line, then set the
    // scalars that are relevant to workstation command lines.
    //==================================================================
    if (hFolderWCL) {
        SetScalarDword(hFolderPkg, "Share permissions", (DWORD) PACKAGE_PERMISSIONS);

        InputString("Workstation root", szReply);
        SetScalarString(hFolderPkg, "Workstation root", szReply);

    }

    // If this package contains a program item, then set the scalars
    // that are relevant to program items.
    //==============================================================
    if (hFolderProgItem) {
        SetScalarDword(hFolderPkg, "Share permissions", (DWORD) PACKAGE_PERMISSIONS);

        InputString("Server root", szReply);
        SetScalarString(hFolderPkg, "Server root", szReply);

        InputString("Share name", szReply);
        SetScalarString(hFolderPkg, "Share name", szReply);
    }





    // Display the folder and ask the user if he or she really wants to
    // write the folder to the datasource.  If the user says yes, then
    // commit the subfolder's first and then the package folder.  Note that
    // it does not make any sense to commit the package folder before its
    // subfolders because, once a folder is committed, modification is not
    // allowed and it would not be possible to commit the subfolders.
    //===================================================================

    ViewFolder(hFolderPkg);

    if (UserSaysYes("OK to write the folder to the datasource")) {

        if (hFolderWCL) {
            stat = SmsCommitFolder(hFolderWCL);
            if (stat != SMS_OK && stat!=SMS_PARENT_NEEDS_COMMIT) {
                DisplaySmsError("Failed to commit the WCL folder", stat);
                goto CLOSE_FOLDERS_AND_EXIT;
            }
        }

        if (hFolderProgItem) {
            stat = SmsCommitFolder(hFolderProgItem);
            if (stat != SMS_OK && stat!=SMS_PARENT_NEEDS_COMMIT) {
                DisplaySmsError("Failed to commit the program item folder", stat);
                goto CLOSE_FOLDERS_AND_EXIT;
            }
        }



        // Place the package folder in the in-memory hierarchy.
        stat = SmsLinkFolder(hFolderPkg);
        if (stat != SMS_OK) {
            DisplaySmsError("SmsLinkFolder failed on the package folder", stat);
            goto CLOSE_FOLDERS_AND_EXIT;
        }


        // write it back to data source.
        stat = SmsCommitFolder( hFolderPkg );
        if (stat != SMS_OK) {
            DisplaySmsError("Failed to commit the package folder", stat);
        }
    }

    // Fall through to close the folders.

CLOSE_FOLDERS_AND_EXIT:

    // Close the folder's so that memory will be freed when there are no
    // references to them.  A folder's memory is freed when its reference
    // count goes to zero.  A folder has one reference for each handle to it
    // that is returned plus an additional refernce from its parent folder or
    // container.  Thus we close the folder handles here so that the memory
    // allocated to the folders will be freed, but the memory won't actually
    // be freed until the package container is closed.  If you fail to close
    // any handle returned to you by the SMS API, the memory for that folder
    // will never be deallocated (even when the folder's container is closed).
    //========================================================================


    if (hFolderWCL != NULL) {
        stat = SmsCloseFolder(hFolderWCL);
        if (stat != SMS_OK) {
            DisplaySmsError("Failed to close the WCL folder", stat);
        }
    }

    if (hFolderProgItem != NULL) {
        stat = SmsCloseFolder(hFolderProgItem);
        if (stat != SMS_OK) {
            DisplaySmsError("Failed to close the program item folder", stat);
        }
    }


    return( hFolderPkg );
}


//*************************************************************************
// DisplayScalars
//
// Display a folder's scalars.
//
// Parameters:
//      HANDLE hfolder
//          This is the folder handle.
//
// Returns: Nothing.
//
// ====================================================================
void DisplayScalars( HANDLE hFolder )
{
    SMS_STATUS stat = SMS_OK;
    SCALAR scalar;
    char *pszTime;          // For conversion of time scalars.

    // The scalars do not have their own string value buffer, so
    // we allocate the buffers here and set pointers to them in the
    // scalar structure.
    //=============================================================
    char szName[SMS_DATA_BUFF_SIZE+1];
    char szValue[SMS_DATA_BUFF_SIZE+1];
    scalar.pszName  = szName;
    scalar.pszValue = szValue;
    scalar.pValue = NULL;


    while (1) {

        scalar.dwLen = sizeof(szValue)-1;       // must tell him the size

        stat = SmsGetNextScalar( hFolder, &scalar);
        if (stat == SMS_NO_MORE_DATA) {
            break;
        }

        if (stat != SMS_OK && stat != SMS_MORE_DATA) {
            DisplaySmsError("SmsGetNextScalar failed in method DisplayScalars", stat);
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
            printf("\t%25s: %s\n", scalar.pszName, scalar.pszValue);
            break;

        case SCALAR_INT:
            printf("\t%25s: %ld\n", scalar.pszName, scalar.dwValue);
            break;

        case SCALAR_TIME:
            // Check if we have a string equivalence. If so use it.
            if (scalar.bStringEquivalence) {
                printf("\t%25s: %s\n", scalar.pszName, scalar.pszValue);

            } else {
                pszTime = ctime( &scalar.tValue );
                printf("\t%25s: %s", scalar.pszName, pszTime);
            }
            break;

        case SCALAR_BINARY:
            // In this sample we won't display the binary data.
            // Just tell the user its size.
            printf("\t%25s (Binary - this is its size): %ld\n", scalar.pszName, scalar.dwLen);
            break;
        }
    }

    // Why did we exit (other than no more scalars)?
    //==============================================
    if (stat != SMS_NO_MORE_DATA) {
        printf("Bad return from Scalar access: %d\n", stat);
    }

    printf("\n");
}










// ********************************************************************
//      Helper functions.
// ********************************************************************

//**********************************************************
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
//***********************************************************
BOOL DidRequestHelp(int argc, char** argv)
{
    const char* pszCommand = argv[1];
    if (argc==2  && (strcmp((const char*) argv[1], "-help")==0)) {
        return(TRUE);
    }
    else {
        return(FALSE);
    }
}


//**********************************************************************
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
//*********************************************************************
void DisplayHelp()
{
    printf("\n\n");
    printf("********************************************************\n");
    printf("* newpkg.exe:                                          *\n");
    printf("*                                                      *\n");
    printf("* This is a sample program for the SMS SDK. It can be  *\n");
    printf("* used to view, create, or delete packages in the SMS  *\n");
    printf("* database.                                            *\n");
    printf("*                                                      *\n");
    printf("* Syntax:                                              *\n");
    printf("*     newpkg.exe [-help]                               *\n");
    printf("*                                                      *\n");
    printf("* Switches:                                            *\n");
    printf("*     -help       Display this help screen.            *\n");
    printf("*                                                      *\n");
    printf("********************************************************\n");
    printf("\n");
}



//*******************************************************************
// DisplayGreeting
//
// Display the initial greeting banner.
//
// Parameters:
//     None.
//
// Returns:
//     Nothing.
//******************************************************************
void DisplayGreeting()
{
    // For this sample, the greeting is identical to the help screen.
    //===============================================================
    DisplayHelp();
}




//**************************************************************************
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
//***************************************************************************
void InputString(const char* pszMessage, char* pszResult)
{
    printf("%s: ", pszMessage);
    gets(pszResult);
}


//**************************************************************************
// UserSaysYes
//
// Prompt the user to reply yes or no.  If the user enters "Y" then
// return TRUE, otherwise FALSE.
//
// Parameters:
//      const char* pszPrompt
//          The string used to prompt the user
//
// Returns:
//      TRUE = User replied "Y" or "y"
//      FALSE = User gave any other reply.
//**************************************************************************
BOOL UserSaysYes(const char* pszPrompt)
{
    printf("%s? [y/n]", pszPrompt);
    char szReply[CCH_MAXSTRING];
    gets(szReply);

    return(szReply[0] == 'y' || szReply[0] == 'Y');

}



/* EOF: newjob.cpp */

