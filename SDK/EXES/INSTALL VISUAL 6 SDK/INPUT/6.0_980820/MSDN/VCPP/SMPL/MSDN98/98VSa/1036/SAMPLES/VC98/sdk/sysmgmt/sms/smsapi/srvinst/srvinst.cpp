//**************************************************************************
// Copyright (C) 1995 by Microsoft Corporation.
//
// This is a sample program for the SMS SDK.  It illustrates how to create
// a server install job and monitor its status until the job completes.
//
// This sample program also illustrates how to create a run command on
// workstation job.
//
// The program will request the following input:
//
// Share package on workstation job:
//    Package name    = User defined name of the package
//    Package comment = User defined text
//    Package location (UNC path) = The pathname to the directory where the
//                                  package files are located.
//    Package share name = The name that the package will be shared as on the
//                         server.
//    Program item description = User defined text
//    Program item command line = The command to execute on the server.
//    Program item registry name = User defined registry key for the package
//
// Run command on workstation job.
//    Package name = User defined name of the package
//    Package comment = User defined text
//    Package location (share name) = The pathname to the directory where the
//                                    client package is located.
//    WCL Name = User defined name for the workstation command line
//    WCL Command = The command line to execute.
//
// NOTE: If you choose to create a share package on server job, then you must
//       first share the package directory.  If you choose to create a run
//       command on workstation job, then you must first share the directory
//       where the package files are located.
//
//*****************************************************************************


#include <afx.h>
#include <smsapi.h>
#include <smsinfo.h>

// Include the GetStatusName function.
// -------------------------------------
#include "..\common\status.inc"


// ====================================================================
//      Defines.
// ====================================================================

#define CCH_MAXSTRING   256
#define CCH_MAXINPUT    256
#define C_MAXSITES      256

#define SHARE_PERMISSIONS (PACKAGE_USER_READ | PACKAGE_USER_WRITE | PACKAGE_GUEST_READ)


extern const char *GetStatusName( SMS_STATUS stat );

enum {CMD_RUN_COMMAND, CMD_SHARE_PACKAGE, CMD_QUIT};




// ====================================================================
// TClientParams
//
// This typedef defines the parameters for the client setup
// job that are collected from the user.
// ====================================================================
typedef struct
{
    char szPackageName[CCH_MAXSTRING];
    char szPackageComment[CCH_MAXSTRING];
    char szPackagePath[CCH_MAXSTRING];
    char szWclName[CCH_MAXSTRING];
    char szWclCommand[CCH_MAXSTRING];
    char szSiteName[CCH_MAXSTRING];
    DWORD dwPlatforms;
} TClientParams;


// ====================================================================
// TServerParams
//
// This typedef defines the parameters for the share package on
// workstation job that are collected from the user.
// ====================================================================
typedef struct
{
    char szPackageName[CCH_MAXSTRING];
    char szPackageComment[CCH_MAXSTRING];
    char szPackagePath[CCH_MAXSTRING];
    char szShareName[CCH_MAXSTRING];
    char szDescription[CCH_MAXSTRING];
    char szCmdLine[CCH_MAXSTRING];
    char szRegistryName[CCH_MAXSTRING];
    char szSiteName[CCH_MAXSTRING];
    DWORD dwPlatforms;

} TServerParams;



// ====================================================================
//
//  Local prototypes.
//
// ====================================================================

void DisplayHelp();

void DisplayGreeting();

BOOL DidRequestHelp( int argc, char** argv );

void DisplaySmsError( const char *pszMessage, SMS_STATUS stat );

const char *GetStatusName( SMS_STATUS stat );

BOOL DidRequestHelp( int argc, char** argv );

HANDLE ConnectToDatasource();

void InputString( const char *pszMessage, char *pszResult );

void GetSiteName( HANDLE hConnect, char *pszSiteName );

void ClientDoRunCommand( HANDLE hConnect, TClientParams *pcp );

DWORD GetPlatformSelection();

void ServerDoShare( HANDLE hConnect, TServerParams *psp );

int GetJobType();


SMS_STATUS ClientJobCreate( HANDLE hConnect,
                            TClientParams *pcp,
                            char *pszPackageID,
                            char *pszWCLID );


// ====================================================================
//
//  The work starts here.
//
// ====================================================================
void main( int argc, char **argv )
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

    HANDLE hConnect = ConnectToDatasource();
    if (hConnect == NULL) {
        return;
    }


    char szSiteName[CCH_MAXSTRING];
    GetSiteName(hConnect, szSiteName);

    DWORD dwPlatforms = 0;
    while (dwPlatforms == 0) {
        dwPlatforms = GetPlatformSelection();
        if (dwPlatforms == 0) {
            printf("Error: Invalid platform selection\n");
        }
    }




    switch(GetJobType()) {
    case CMD_SHARE_PACKAGE:

        printf("***************************************\n");
        printf("* Share package on server job.        *\n");
        printf("***************************************\n");
        TServerParams sp;
        strcpy(sp.szSiteName, szSiteName);
        sp.dwPlatforms = dwPlatforms;
        InputString("Package name", sp.szPackageName);
        InputString("Package comment", sp.szPackageComment);
        InputString("Package directory location (UNC path)", sp.szPackagePath);
        InputString("Package share name", sp.szShareName);
        InputString("Program item description", sp.szDescription);
        InputString("Program item command line", sp.szCmdLine);
        InputString("Program item registry name", sp.szRegistryName);
        printf("\n");

        // First share the package on the server
        //=======================================
        ServerDoShare(hConnect, &sp);

        printf("**************************************************\n");
        printf("* The server install job has completed.  To      *\n");
        printf("* use the shared package please create a program *\n");
        printf("* group in the SMS administration program and add*\n");
        printf("* the package that was just shared to the group. *\n");
        printf("*                                                *\n");
        printf("* For more information, please refer to chapter  *\n");
        printf("* nine of the SMS Administrator's guide.         *\n");
        printf("**************************************************\n");
        printf("\n");
        break;

    case CMD_RUN_COMMAND:

        printf("************************************************\n");
        printf("* Run command on workstation job.              *\n");
        printf("************************************************\n");
        TClientParams cp;
        strcpy(cp.szSiteName, szSiteName);
        cp.dwPlatforms = dwPlatforms;
        InputString("Package name", cp.szPackageName);
        InputString("Package directory location (UNC path)", cp.szPackagePath);
        InputString("Package comment", cp.szPackageComment);
        InputString("WCL Name", cp.szWclName);
        InputString("WCL Command", cp.szWclCommand);
        printf("\n");


        // Now that we've shared the package on the server,
        // submit a job to setup the client program.
        //=================================================
        ClientDoRunCommand(hConnect, &cp);
        break;
    default:
        printf("Invalid job type. No job submitted.\n");
        break;
    }

    if (hConnect != NULL) {
        SmsDataSourceDisconnect( hConnect );
    }
}






// ====================================================================
//
// SetScalarString
//
// This function sets the value specified scalar to the given string
// value.
//
// Parameters:
//      HANDLE hFolder
//          The handle of the folder containing the scalar to modify.
//      char *pszName
//          The name of the scalar.
//      char *pszValue
//          The string that will be assigned to the scalar's value.
//
// Returns:
//      SMS_STATUS
//          The SMS status code.
//
// Note that the scalar specified must be of type SCALAR_STRING.
//
// ====================================================================
SMS_STATUS SetScalarString( HANDLE hFolder, char *pszName, char *pszValue )
{
    SCALAR sc;
    sc.pszName = pszName;
    sc.scType = SCALAR_STRING;
    sc.pszValue = pszValue;

    SMS_STATUS stat;
    stat = SmsSetScalar(hFolder, &sc);
    return stat;
}


// ====================================================================
//
// SetScalarBool
//
// This function sets the value specified scalar to the given boolean value
//
// Parameters:
//      HANDLE hFolder
//          The handle of the folder containing the scalar to modify.
//      char *pszName
//          The name of the scalar.
//      BOOL bIsTrue
//          The boolean value to set the scalar to.
//
// Returns:
//      SMS_STATUS
//          The SMS status code.
//
// Note that the scalar specified must be of type SCALAR_INT.
//
// ====================================================================
SMS_STATUS SetScalarBool( HANDLE hFolder, char *pszName, BOOL bIsTrue )
{
    SCALAR sc;
    sc.pszName = pszName;
    sc.scType = SCALAR_INT;
    sc.dwValue = bIsTrue ? 1 : 0;


    SMS_STATUS stat;
    stat = SmsSetScalar(hFolder, &sc);
    return stat;
}


// ====================================================================
//
// SetScalarDword
//
// This function sets the value specified scalar to the given DWORD value.
//
// Parameters:
//      HANDLE hFolder
//          The handle of the folder containing the scalar to modify.
//      char *pszName
//          The name of the scalar.
//      DWORD dwValue
//          The DWORD value to set the scalar to.
//
// Returns:
//      SMS_STATUS
//          The SMS status code.
//
// Note that the scalar specified must be of type SCALAR_INT.
//
// ====================================================================
SMS_STATUS SetScalarDword( HANDLE hFolder, char *pszName, DWORD dwValue )
{
    SCALAR sc;
    sc.pszName = pszName;
    sc.scType = SCALAR_INT;
    sc.dwValue = dwValue;


    SMS_STATUS stat;
    stat = SmsSetScalar(hFolder, &sc);
    return stat;
}


// ====================================================================
//
// SetScalarTime
//
// This function sets the value specified scalar to the given time
// value.
//
// Parameters:
//      HANDLE hFolder
//          The handle of the folder containing the scalar to modify.
//      char *pszName
//          The name of the scalar.
//      time_t tValue
//          The time value to assign to the scalar.
//
// Returns:
//      SMS_STATUS
//          The SMS status code.
//
// Note that the scalar specified must be of type SCALAR_TIME.
//
// ====================================================================
SMS_STATUS SetScalarTime( HANDLE hFolder, char *pszName, time_t tValue )
{
    SCALAR sc;
    sc.pszName = pszName;
    sc.scType = SCALAR_TIME;
    sc.tValue = tValue;

    SMS_STATUS stat;
    stat = SmsSetScalar(hFolder, &sc);
    return stat;
}


// ====================================================================
//
// GetScalarString
//
// This function gets the string value of the specified scalar.
//
// Parameters:
//      HANDLE hFolder
//          The handle of the folder containing the scalar to modify.
//      char *pszName
//          The name of the scalar.
//      char *pchBuffer
//          Pointer to the buffer to store the scalar's string value.
//      DWORD cchBuffer
//          The size of the buffer.
//
// Returns:
//      SMS_STATUS
//          The SMS status code.
//
// Note that the scalar specified must be of type SCALAR_STRING.
//
// ====================================================================
SMS_STATUS GetScalarString( HANDLE hFolder,
                            char *pszName,
                            char *pchBuffer,
                            DWORD cchBuffer )
{
    SCALAR sc;

    SMS_STATUS stat;
    *pchBuffer = '\0';

    char szNameBuffer[CCH_MAXSTRING];
    sc.pszName = szNameBuffer;
    sc.pszValue = pchBuffer;
    sc.dwLen = cchBuffer;
    stat = SmsGetScalarByName(hFolder, pszName, &sc);

    if (stat == SMS_OK) {
        if (sc.scType == SCALAR_STRING) {
            strcpy(pchBuffer, sc.pszValue);
        }
        else {
            DisplaySmsError("GetScalarString: scalar is not SCALAR_STRING", SMS_OK);
            stat = SMS_ERROR;
        }
    }
    else {
        DisplaySmsError("GetScalarString: SmsGetScalarByName failed", stat);
    }
    return(stat);
}


// ====================================================================
//
// GetScalarDword
//
// This function gets the DWORD value of the specified scalar.
//
// Parameters:
//      HANDLE hFolder
//          The handle of the folder containing the scalar to modify.
//
//      char *pszName
//          The name of the scalar.
//
//      DWORD *pdwValue
//          Pointer to the place to store the scalar's DWORD value.
//
// Returns:
//      SMS_STATUS
//          The SMS status code.
//
// Note that the scalar specified must be of type SCALAR_INT.
//
// ====================================================================
SMS_STATUS GetScalarDword( HANDLE hFolder, char *pszName, DWORD *pdwValue )
{
    SCALAR sc;

    SMS_STATUS stat;
    char szNameBuffer[CCH_MAXSTRING];
    sc.pszName = szNameBuffer;
    stat = SmsGetScalarByName(hFolder, pszName, &sc);

    if (stat == SMS_OK) {
        if (sc.scType == SCALAR_INT) {
            *pdwValue = sc.dwValue;
        }
        else {
            DisplaySmsError("GetScalarDword: Scalar is not SCALAR_INT", SMS_OK);
            stat = SMS_ERROR;
        }
    }
    else {
        DisplaySmsError("GetScalarDword: SmsGetScalarByName failed", stat);
    }
    return(stat);
}


// ====================================================================
//
// FindFolder
//
// This function searches a container for a folder with a scalar that
// matches the given scalar name and string scalar value.
//
// Parameters:
//      HANDLE hContainer
//          The handle of the containter to search.
//
//      char *pszName
//          The name of the scalar.
//
//      char *pszScalarValue
//          The "match" value to test for.
//
//      HFOLDER* phFolder
//          Pointer to the place to store the folder handle if a folder
//          containing the specified scalar value is found.
//
//
// Returns;
//      SMS_OK if the folder is found, SMS_NOT_FOUND otherwise.
//      The folder handle is returned via a pointer.
//
// ====================================================================
SMS_STATUS FindFolder( HANDLE hContainer,
                       DWORD fType,
                       char *pszScalarName,
                       char *pszScalarValue,
                       HANDLE *phFolder )
{
    *phFolder = NULL;

    while(TRUE) {
        SMS_STATUS stat;
        HANDLE hFolder;
        char szValue[CCH_MAXSTRING];

        stat = SmsGetNextFolder(hContainer, fType, &hFolder);
        if (stat == SMS_NO_MORE_DATA) {
            return(SMS_NOT_FOUND);
        }

        if (stat != SMS_OK) {
            DisplaySmsError("SmsGetNextFolder error", stat);
            return(SMS_NOT_FOUND);
        }

        GetScalarString(hFolder, pszScalarName, szValue, sizeof(szValue));
        if (!strcmp(szValue, pszScalarValue)) {
            *phFolder = hFolder;
            return(SMS_OK);
        }

        SmsCloseFolder(hFolder);
    }
}


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
// GetPlatformSelection
//
// Prompt the user to select a one or more platforms.  The platforms
// are selected by entering a comma separated list of platform indexes.
// These platform indexes are converted to the platforms flags value
// for the SDK.
//
// Parameters:  None.
//
// Returns:
//      The SMS SDK platform flags value.
//
// ====================================================================
DWORD GetPlatformSelection()
{
    printf("**********************************************\n");
    printf("* Select a platform from the following list. *\n");
    printf("**********************************************\n");
    printf("   1) MS-DOS \n");
    printf("   2) Windows 3.1\n");
    printf("   3) Windows95\n");
    printf("   4) Windows NT (X86)\n");
    printf("   5) Windows NT (Mips)\n");
    printf("   6) Windows NT (Alpha)\n");
    printf("   7) Macintosh\n");
    printf("\n");

    DWORD dwPlatforms = 0;
    char szReply[CCH_MAXINPUT];
    InputString("Enter a comma separated list of platform number(s)", szReply);
    printf("\n");

    const char *pszReply = szReply;
    while (*pszReply) {


        if (*pszReply < '1' || *pszReply > '6') {
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
        while(*pszReply == ' ' || *pszReply=='\t') {
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




// ====================================================================
//
// ServerWriteProgItem
//
// Set the value of the program item folder's scalars, link it into the
// folder hierarchy and finally insert it into the data source.
//
// Parameters:
//      HANDLE hFolderProgItem
//          The program item folder's handle.
//
//      TServerParams *psp
//          Pointer to the "share package on server" parameters
//          that the user was asked to input at the beginning of the
//          program.
//
// Returns:
//      SMS_OK if no error occurred, otherwise the SDK status code.
//
// ====================================================================
SMS_STATUS ServerWriteProgItem( HANDLE hFolderProgItem, TServerParams *psp )
{

    SetScalarString(hFolderProgItem, "Description", psp->szDescription);
    SetScalarString(hFolderProgItem, "Command line", psp->szCmdLine);
    SetScalarDword(hFolderProgItem,  "Run minimized", 0);
    SetScalarDword(hFolderProgItem,  "Platforms", psp->dwPlatforms);
    SetScalarString(hFolderProgItem, "Configure script file", "");
    SetScalarDword(hFolderProgItem,  "Search local flag", 1);
    SetScalarDword(hFolderProgItem,  "Drive mode", 1);
    SetScalarString(hFolderProgItem, "Registry name", psp->szRegistryName);
    SetScalarDword(hFolderProgItem,  "Executable flag", 1);



    SMS_STATUS stat;
    stat = SmsLinkFolder(hFolderProgItem);
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to link the server share program item folder into the hierarchy", stat);
        return( stat );
    }

    stat = SmsCommitFolder(hFolderProgItem);
    if ((stat != SMS_OK) && (stat != SMS_PARENT_NEEDS_COMMIT)) {
        DisplaySmsError("Failed to insert the server share program item folder into the package", stat);
    }
    else {
        // If the status code was SMS_PARENT_NEEDS_COMMIT, we convert the status to
        // SMS_OK, since the commit was successful.
        //=========================================================================
        stat = SMS_OK;
    }


    // Note program item folders are not actually inserted into the
    // datasource until a commit is also done on the parent
    // package folder.
    //=====================================================
    return( stat );
}


// ====================================================================
//
// ServerWritePkg
//
// Set the value of the package folder's scalars, link it into the
// folder hierarchy and finally insert it into the data source.
//
// Parameters:
//      HANDLE hFolderPkg
//          The package folder's handle.
//
//      TServerParams *psp
//          Pointer to the "share package on server" parameters
//          that the user was asked to input at the beginning of the
//          program.
//
// Returns:
//      SMS_OK if no error occurred, otherwise the SDK status code.
//
// ====================================================================
SMS_STATUS ServerWritePkg( HANDLE hFolderPkg, TServerParams *psp )
{
    SetScalarString(hFolderPkg, "Name", psp->szPackageName);
    SetScalarString(hFolderPkg, "Comment", psp->szPackageComment);
    SetScalarString(hFolderPkg, "Server root", psp->szPackagePath);
    SetScalarString(hFolderPkg, "Share name", psp->szShareName);
    SetScalarDword(hFolderPkg,  "Share permissions", (DWORD)SHARE_PERMISSIONS);


    SMS_STATUS stat;
    stat = SmsLinkFolder(hFolderPkg);
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to link the server share package folder into the hierarchy", stat);
        return( stat );
    }


    stat = SmsCommitFolder(hFolderPkg);
    if ((stat != SMS_OK) && (stat != SMS_PARENT_NEEDS_COMMIT)) {
        DisplaySmsError("Failed to insert the server share package folder into the datasource", stat);
    }

    return( stat );
}


// ====================================================================
//
// ServerCreatePkg
//
// This function create the server install job package.
//
// Parameters:
//      HANDLE hConnect
//          The datasource connection handle.
//
//      TServerParams *psp
//          Pointer to the "share package on server" parameters
//          that the user was asked to input at the beginning of the
//          program.
//
//      char *pszPackageID
//          Pointer to the buffer where the package ID will be
//          returned.
//
//      DWORD cchPackageID
//          Size of the package ID buffer.
//
//      char *pszProgItemID
//          Pointer to the buffer where the program item ID will be
//          returned.
//
//      DWORD cchProgItemID
//          Size of the program item ID buffer.
//
// Returns:
//      SMS_OK if no error occurred, otherwise the SDK status code.
//
// ====================================================================
SMS_STATUS ServerCreatePkg( HANDLE hConnect,
                            TServerParams *psp,
                            char *pszPackageID,
                            DWORD cchPackageID,
                            char *pszProgItemID,
                            DWORD cchProgItemID)
{
    SMS_STATUS stat;
    HANDLE hContainer;
    HANDLE hFolderPkg = NULL;
    HANDLE hFolderProgItem = NULL;

    // First open the package container.  If we fail to open it,
    // display an error message and give up.
    //=========================================================
    stat = SmsOpenContainer( C_PACKAGE, hConnect, &hContainer );
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to open the package container", stat);
        return( stat );
    }

    // Now create a new package folder.
    //=================================
    stat = SmsCreateFolder( hContainer, F_PACKAGE, "Dummy", &hFolderPkg );
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to create server share package", stat);
        goto CLEANUP_AND_EXIT;
    }


    stat = SmsCreateFolder(hFolderPkg, F_PROGITEM, "Dummy", &hFolderProgItem);
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to create server share program item", stat);
        goto CLEANUP_AND_EXIT;
    }


    stat = ServerWriteProgItem(hFolderProgItem, psp);
    if (stat != SMS_OK) {
        goto CLEANUP_AND_EXIT;
    }

    stat = ServerWritePkg(hFolderPkg, psp);
    if (stat != SMS_OK) {
        goto CLEANUP_AND_EXIT;
    }


    GetScalarString(hFolderPkg, "Key", pszPackageID, cchPackageID);
    GetScalarString(hFolderProgItem, "ItemKey", pszProgItemID, cchProgItemID);
    stat = SMS_OK;


CLEANUP_AND_EXIT:

    if (hFolderProgItem) {
        SmsCloseFolder(hFolderProgItem);
    }

    if (hFolderPkg) {
        SmsCloseFolder(hFolderPkg);
    }

    SmsCloseContainer(hContainer);
    return( stat );
}



// ====================================================================
//
// ServerWriteJob
//
// This function sets the values of the job folder's scalars, links the
// job folder into the folder hierachy, and then inserts the folder
// into the data source.
//
// Parameters:
//      HANDLE hFolderJob
//          The handle to the server install job folder.
//
//      TServerParams *psp
//          Pointer to the "share package on server" parameters
//          that the user was asked to input at the beginning of the
//          program.
//
//      char *pszPackageID
//          Pointer to the server install package ID.
//
// Returns:
//      SMS_OK if no error occurred, otherwise the SDK status code.
//
// ====================================================================
BOOL ServerWriteJob( HANDLE hFolderJob,
                     TServerParams *psp,
                     char *pszPackageID )
{
    // Submit the job immediately, so set the job submission time
    // to the current time.
    //===========================================================
    time_t timeJob;
    time( &timeJob );


    SetScalarString(hFolderJob, "Job comment",      "This is an SDK sample job");
    SetScalarTime(  hFolderJob, "Activate time",    timeJob);
    SetScalarDword( hFolderJob, "Priority",         3);
    SetScalarDword( hFolderJob, "Repeat mode",      1);
    SetScalarDword( hFolderJob, "Cancel mode",      0);
    SetScalarString(hFolderJob, "Package ID",       pszPackageID);
    SetScalarDword( hFolderJob, "PackageOverwriteFlag", 0);
    SetScalarDword( hFolderJob, "Job target",       WKSTAJOB_TGT_MACHPATH);
    SetScalarDword( hFolderJob, "Limit to sites",   JOBTGT_SITE);
    SetScalarDword( hFolderJob, "Include subsites", JOBTGT_INCLUDESUBSITES);
    SetScalarString(hFolderJob, "Site limit name",  psp->szSiteName);

    // At this point we have a folder in memory, but it has not
    // been linked into the folder hierarchy yet.  We do so by
    // calling SmsLinkFolder.
    //=========================================================
    SMS_STATUS stat;
    stat = SmsLinkFolder(hFolderJob);
    if (stat != SMS_OK) {
        DisplaySmsError("SmsLinkFolder(hFolderJob) failed", stat);
        return(stat);
    }

    // The folder is now linked into the folder hierachy, but it
    // has not yet been inserted into the data source.  We do so
    // now by calling SmsCommitFolder.
    //==========================================================
    stat = SmsCommitFolder(hFolderJob);
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to insert the job into the datasource", stat);
        return(stat);
    }

    return( SMS_OK );
}




// ====================================================================
//
// ServerSubmitShareJob
//
// This function creates a share package on server job.
//
// Parameters:
//      HANDLE hConnect
//          The datasource connection handle.
//
//      TServerParams *psp
//          Pointer to the "share package on server" parameters
//          that the user was asked to input at the beginning of the
//          program.
//
//      char *pszPackageID
//          Pointer to the server install package ID.
//
//      char *pszJobID
//          Pointer to the buffer where the server install job ID will
//          be returned.
//
//      DWORD cchJobID
//          The size of the job ID buffer.
//
// Returns;
//      SMS_OK if everything was successful, otherwise the SMS SDK
//      status code.
//      The job ID is in the job name buffer.
//
// ====================================================================
SMS_STATUS ServerSubmitShareJob(HANDLE hConnect,
                                TServerParams *psp,
                                char *pszPackageID,
                                char *pszJobID,
                                DWORD cchJobID)
{
    *pszJobID = 0;

    SMS_STATUS stat;
    HANDLE hContainerJob;
    stat = SmsOpenContainer( C_JOB, hConnect, &hContainerJob );
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to open job container", stat);
        return( stat );
    }

    HANDLE hFolderJob;
    stat = SmsCreateFolder( hContainerJob, F_SRVINSTALLJOB, "Dummy", &hFolderJob );
    if (stat == SMS_OK) {
        if (ServerWriteJob(hFolderJob, psp, pszPackageID) == SMS_OK) {

            // We will need the Job ID later so that we can wait for
            // the job to complete before submitting the client setup
            // package.  We get the Job ID below.
            //==================================================
            GetScalarString(hFolderJob, "Job ID", pszJobID, cchJobID);
        }


        // We close the folder to avoid a memory leak.
        //============================================
        stat = SmsCloseFolder(hFolderJob);
        if (stat != SMS_OK) {
            DisplaySmsError("Failed to close job folder", stat);
        }

    }
    else {
        DisplaySmsError("Failed to create the job folder", stat);
    }



    stat = SmsCloseContainer(hContainerJob);
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to close the job container", stat);
    }
    return stat;
}


// ====================================================================
//
// JobStatusToString
//
// Convert the job status value to a human readable string.
//
// Parameters:
//      DWORD dwJobStatus
//          The status value from the job's "Job status" scalar.
//
//      char *pszJobStatus
//          Pointer to a buffer to recieve the human readable version
//          of the job status.
//          The size of the job ID buffer.
//
// Returns;
//      SMS_OK if everything was successful, otherwise the SMS SDK
//      status code.
//
// ====================================================================
void JobStatusToString( DWORD dwJobStatus, char *pszJobStatus )
{
    char *psz;
    switch(dwJobStatus) {
    case JOBSTAT_PENDING:
        psz = "pending";
        break;
    case JOBSTAT_ACTIVE:
        psz = "active";
        break;
    case JOBSTAT_CANCELLED:
        psz = "cancelled";
        break;
    case JOBSTAT_COMPLETE:
        psz = "complete";
        break;
    case JOBSTAT_FAILED:
        psz = "failed";
        break;
    case JOBSTAT_RETRYING:
        psz = "retrying";
        break;
    default:
        sprintf(pszJobStatus, "unkown status %ld", dwJobStatus);
        return;
        break;
    }
    strcpy(pszJobStatus, psz);
}



// ====================================================================
//
// ServerWaitJobComplete
//
// This function polls the status of the server install job and
// continues doing so until the job is complete.  As this is done,
// status given to the user as to the progress of the job.
//
// Parameters:
//      HANDLE hConnect
//          The datasource connection handle.
//
//      char *pszJobID
//          Pointer to the ID string for the job to wait on.
//
// Returns:
//      SMS_OK if everything went ok and the job has completed,
//      otherwise the SDK status code.
//
// ====================================================================
SMS_STATUS ServerWaitJobComplete( HANDLE hConnect, char *pszJobID )
{
    printf("***************************************\n");
    printf("* Share package on server job.        *\n");
    printf("* Waiting for job to complete.        *\n");
    printf("***************************************\n");

    while(TRUE) {
        SMS_STATUS stat;
        HANDLE hContainerJob;
        stat = SmsOpenContainer( C_JOB, hConnect, &hContainerJob );
        if (stat != SMS_OK) {
            DisplaySmsError("Failed to open job container while waiting for server share job", stat);
            return( stat );
        }

        stat = SmsPopulate(hContainerJob, POP_SYNC, NULL);
        if (stat != SMS_OK) {
            DisplaySmsError("Failed to populate job container while waiting for server share job", stat);
            SmsCloseContainer(hContainerJob);
            return(stat);
        }

        HANDLE hFolderJob;
        stat = FindFolder(hContainerJob,  F_SRVINSTALLJOB, "Job ID", pszJobID, &hFolderJob);
        if (stat != SMS_OK) {
            DisplaySmsError("Server share job not found while waiting", stat);
            SmsCloseContainer(hContainerJob);
            return(stat);
        }

        DWORD dwScalarValue;
        GetScalarDword(hFolderJob, "Job status", &dwScalarValue);

        SmsCloseFolder(hFolderJob);
        SmsCloseContainer(hContainerJob);


        char szJobStatus[CCH_MAXSTRING];
        JobStatusToString(dwScalarValue, szJobStatus);

        printf("Share package on server job, status = %s\n", szJobStatus);

        if (dwScalarValue == 4) {
             return(SMS_OK);
        }



        // Sleep for 10 seconds before checking the status of the server
        // share job again.
        //=============================================================
        Sleep(10000);
    }

    // Control should never come here. So no return value is
    // necessary.
    //======================================================

}






// ====================================================================
//
// ServerDoShare
//
// This function creates a server install package and then submits
// a share package on server job.
//
// Parameters:
//      HANDLE hConnect
//          The datasource connection handle.
//
//      TServerParams *psp
//          Pointer to the "share package on server" parameters
//          that the user was asked to input at the beginning of the
//          program.
//
// Returns:
//      SMS_OK if everything went ok, otherwise the SDK status code.
//
// ====================================================================
void ServerDoShare( HANDLE hConnect, TServerParams *psp )
{
    char szPackageID[CCH_MAXSTRING];
    char szProgItemID[CCH_MAXSTRING];
    char szJobID[CCH_MAXSTRING];
    SMS_STATUS stat;

    stat = ServerCreatePkg(hConnect,
                           psp,
                           szPackageID, sizeof(szPackageID),
                           szProgItemID, sizeof(szProgItemID));
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to create server share package", stat);
        return;
    }


    // Submit the share package on server job and get the
    // job ID.
    //====================================================
    stat = ServerSubmitShareJob(hConnect,
                    psp,
                    szPackageID,
                    szJobID,
                    sizeof(szJobID));
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to submit server share package", stat);
        return;
    }


    ServerWaitJobComplete(hConnect, szJobID);
}





// ====================================================================
//
// ClientWritePkg
//
// This function defines the attributes (scalar values) for the client
// setup package.
//
// Parameters:
//      HANDLE hFolderPkg
//          The handle to the package folder for the client setup job.
//
//      TClientParams *pcp
//          Pointer to the "run setup command on client" parameters
//          that the user was asked to input at the beginning of the
//          program.
//
// Returns:
//      SMS_OK if everything went ok, otherwise the SDK status code.
//
// ====================================================================
BOOL ClientWritePkg( HANDLE hFolderPkg, TClientParams *pcp )
{
    SetScalarString(hFolderPkg, "Name", pcp->szPackageName);
    SetScalarString(hFolderPkg, "Comment", pcp->szPackageComment);
    SetScalarString(hFolderPkg, "Workstation root", pcp->szPackagePath);
    SetScalarDword(hFolderPkg,  "Share permissions", (DWORD) SHARE_PERMISSIONS);

    SMS_STATUS stat;
    stat = SmsCommitFolder(hFolderPkg);
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to insert the package into the datasource", stat);
        return(FALSE);
    }

    return(TRUE);
}


// ====================================================================
//
// ClientWriteWcl
//
// This function defines the attributes (scalar values) for the
// workstation command line folder that is part of the client setup
// package.
//
// Parameters:
//      HANDLE hFolderWcl
//          The handle to the workstation command line folder for the
//          client setup job.
//
//      TClientParams *pcp
//          Pointer to the "run setup command on client" parameters
//          that the user was asked to input at the beginning of the
//          program.
//
// Returns:
//      SMS_OK if everything went ok, otherwise the SDK status code.
//
// ====================================================================
BOOL ClientWriteWcl( HANDLE hFolderWCL, TClientParams *pcp )
{

    SetScalarString(hFolderWCL, "Name",      pcp->szWclName);
    SetScalarString(hFolderWCL, "Command",   pcp->szWclCommand);
    SetScalarDword( hFolderWCL, "Flags",     0);
    SetScalarDword( hFolderWCL, "Platforms", pcp->dwPlatforms);


    SMS_STATUS stat;
    stat = SmsLinkFolder(hFolderWCL);
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to link the WCL folder into the hierarchy", stat);
        return( FALSE );
    }

    stat = SmsCommitFolder(hFolderWCL);
    if ((stat != SMS_OK) && (stat != SMS_PARENT_NEEDS_COMMIT)) {
        DisplaySmsError("Failed to insert the WCL folder into the package", stat);
        return( FALSE );
    }



    // Note WCL folders are not actually inserted into the
    // datasource until a commit is also done on the parent
    // package folder.
    //=====================================================

    return( TRUE );
}






// ====================================================================
//
// ClientPkgCreate
//
// This function defines creates an SMS package for the client setup
// program.
//
// Parameters:
//      HANDLE hConnect
//          The datasource connection handle.
//
//      TClientParams *pcp
//          Pointer to the "run setup command on client" parameters
//          that the user was asked to input at the beginning of the
//          program.
//
//      char *pszPackageID
//          Pointer to the buffer where the package folder ID string
//          will be returned.
//
//      DWORD cchPackageID
//          The size of the package ID buffer.
//
//      char *pszWclID
//          Pointer to the buffer where the workstation command line
//          folder ID will be returned.
//
//      DWORD cchWclID
//          The size of the workstation command line ID buffer.
//
// Returns:
//      SMS_OK if everything went ok, otherwise the SMS SDK status
//      code.
//      The package ID and the WCL IDs are returned in their respective
//      buffers.
//
// ====================================================================
SMS_STATUS ClientPkgCreate( HANDLE hConnect,
                            TClientParams *pcp,
                            char *pszPackageID,
                            DWORD cchPackageID,
                            char *pszWclID,
                            DWORD cchWclID )
{
    SMS_STATUS stat;
    HANDLE hContainer;

    // First open the package container.  If we fail to open it,
    // display an error message and give up.
    //=========================================================
    stat = SmsOpenContainer( C_PACKAGE, hConnect, &hContainer );
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to open the package container", stat);
        return( stat );
    }

    // Now create a new package folder.
    //=================================
    HANDLE hFolderPkg;
    stat = SmsCreateFolder( hContainer, F_PACKAGE, "Dummy", &hFolderPkg );
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to create package folder for setup command", stat);
        SmsCloseContainer(hContainer);
        return(stat);
    }


    HANDLE hFolderWCL;
    stat = SmsCreateFolder(hFolderPkg, F_WCL, "Dummy", &hFolderWCL);
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to create WCL folder for setup command", stat);
        SmsCloseContainer(hContainer);
        return(stat);
    }


    // At this point we have created both the WCL and the package folder
    // and now we define their attributes.  Note that the WCL attributes
    // are defined first because the call to SmsCommitFolder for the WCL
    // must precede the call to SmsCommitFolder for the package.  This is
    // because the WCL is part of the package and the package can't be
    // modified after a commit is done on it.
    //==================================================================
    ClientWriteWcl(hFolderWCL, pcp);
    ClientWritePkg(hFolderPkg, pcp);



    // We now get the identification strings for the package and the WCL.
    // This is done here because the WCL key is not defined until the
    // package it is contained in has been committed.
    //==================================================================
    GetScalarString(hFolderPkg, "Key", pszPackageID, cchPackageID);
    GetScalarString(hFolderWCL, "Name", pszWclID, cchWclID);

    stat = SmsCloseFolder(hFolderWCL);
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to close the WCL folder", stat);
    }


    stat = SmsCloseFolder(hFolderPkg);
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to close the package folder", stat);
    }

    stat = SmsCloseContainer(hContainer);
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to close the package container", stat);
    }

    return( stat );
}


// ====================================================================
//
// ClientWriteJob
//
// This function defines the values of the job folder, links the folder
// into the folder hierarchy, and finally inserts the folder into the
// datasource.
//
// Parameters:
//      HANDLE hFolderJob
//          The job folder's handle.
//
//      TClientParams *pcp
//          Pointer to the "run command on client" parameters
//          that the user was asked to input at the beginning of the
//          program.
//
//      char *pszPackageID
//          Pointer to the package folder ID string.
//
//      char *pszWclID
//          Pointer to the workstation command line folder ID.
//
// Returns:
//   SMS_OK if everything went OK, otherwise the SMS SDK status code.
//
// ====================================================================
SMS_STATUS ClientWriteJob(  HANDLE hFolderJob,
                            TClientParams *pcp,
                            char *pszPackageID,
                            char *pszWCLID)
{
    // Submit the job immediately. To do this we set the job
    // submission time to the current time.
    //======================================================
    time_t timeJob;
    time( &timeJob );

    SetScalarString(hFolderJob, "Job comment",          "This is an SDK sample job");
    SetScalarTime(  hFolderJob, "Activate time",        timeJob);
    SetScalarDword( hFolderJob, "Priority",             JOBPRI_LOW);
    SetScalarDword( hFolderJob, "Repeat mode",          JOBRPT_NEVER);
    SetScalarDword( hFolderJob, "Cancel mode",          JOBCANCEL_DONT_CANCEL);
    SetScalarString(hFolderJob, "Package ID",           pszPackageID);
    SetScalarString(hFolderJob, "WCL name",             pcp->szWclName);
    SetScalarString(hFolderJob, "Machine path",         "*|*|*");
    SetScalarTime(  hFolderJob, "Offer time",           timeJob);
    SetScalarTime(  hFolderJob, "Mandatory time",       timeJob);
    SetScalarDword( hFolderJob, "Use mandatory time",   0);
    SetScalarDword( hFolderJob, "Force over slow link", 0);
    SetScalarDword( hFolderJob, "Use expire time",      0);
    SetScalarDword( hFolderJob, "Job target",           WKSTAJOB_TGT_MACHPATH);
    SetScalarDword( hFolderJob, "Limit to sites",       JOBTGT_SITE);
    SetScalarDword( hFolderJob, "Include subsites",     JOBTGT_INCLUDESUBSITES);
    SetScalarString(hFolderJob, "Site limit name",      pcp->szSiteName);
    SetScalarDword( hFolderJob, "Run workstation command",  TRUE);


    // At this point, the job folder exists in memory.  Now
    // we must insert the folder into the data source.  We do
    // this by calling SmsCommitFolder.
    //=========================================================
    SMS_STATUS stat;
    stat = SmsLinkFolder(hFolderJob);
    if (stat != SMS_OK) {
        DisplaySmsError("SmsLinkFolder(hFolderJob) failed", stat);
        return(stat);
    }

    stat = SmsCommitFolder(hFolderJob);
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to insert the job into the datasource", stat);
        return(stat);
    }

    return( SMS_OK );
}




// ====================================================================
//
// ClientJobCreate
//
// This function creates an SMS job to run a command on the client
// workstation.   The name of the network share path is passed
// as a parameter to the client setup program.
//
// Parameters:
//      HANDLE hConnect
//          The datasource connection handle.
//
//      TClientParams *pcp
//          Pointer to the "run command on client" parameters
//          that the user was asked to input at the beginning of the
//          program.
//
//      char *pszPackageID
//          Pointer to the package folder ID string.
//
//      char *pszWclID
//          Pointer to the workstation command line folder ID.
//
// Returns:
//      SMS_OK if everything went OK, otherwise the SMS SDK status
//      code.
//
// ====================================================================
SMS_STATUS ClientJobCreate( HANDLE hConnect,
                            TClientParams *pcp,
                            char *pszPackageID,
                            char *pszWCLID)
{

    SMS_STATUS stat;

    HANDLE hContainerJob;
    stat = SmsOpenContainer( C_JOB, hConnect, &hContainerJob );
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to open job container", stat);
        return( stat );
    }

    HANDLE hFolderJob;
    stat = SmsCreateFolder( hContainerJob, F_INSTALLJOB, "Dummy", &hFolderJob );
    if (stat == SMS_OK) {
        ClientWriteJob(hFolderJob, pcp, pszPackageID, pszWCLID);

        stat = SmsCloseFolder(hFolderJob);
        if (stat != SMS_OK) {
            DisplaySmsError("Failed to close job folder", stat);
        }

    }
    else {
        DisplaySmsError("Failed to create the job folder", stat);
    }

    stat = SmsCloseContainer(hContainerJob);
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to close the job container", stat);
    }
    return stat;
}


// ====================================================================
//
// ClientDoRunCommand
//
// This function submits a run command on workstation job.
//
//
// Parameters:
//      HANDLE hConnect
//          The datasource connection handle.
//
//      TClientParams *pcp
//          Pointer to the "client" parameters that the user was asked to
//          input at the beginning of the program.
//
// Returns:  Nothing.
//
// ====================================================================
void ClientDoRunCommand( HANDLE hConnect, TClientParams *pcp )
{
    char szPackageID[CCH_MAXSTRING];
    char szWclID[CCH_MAXSTRING];

    SMS_STATUS stat;
    stat = ClientPkgCreate(hConnect,
                           pcp,
                           szPackageID, sizeof(szPackageID),
                           szWclID, sizeof(szWclID));
    if (stat != SMS_OK) {
        DisplaySmsError("Could not create client package", stat);
        return;
    }

    stat =  ClientJobCreate(hConnect, pcp, szPackageID, szWclID);
    if (stat != SMS_OK) {
        DisplaySmsError("Could not create client job", stat);
    }
}



// ====================================================================
//
// GetSiteName
//
// This function query's the user to select the SMS site that will be
// used in this sample
//
// Parameters:
//      HANDLE hConnect
//          The datasource connection handle.
//
//      char *pszSiteName
//          Pointer to the buffer where the site name will be returned.
//
// Returns:  Nothing.
//
// ====================================================================
void GetSiteName( HANDLE hConnect, char *pszSiteName )
{
    *pszSiteName = '\0';


    HANDLE hContainerSite;
    SMS_STATUS stat;

    stat = SmsOpenContainer( C_SITE, hConnect, &hContainerSite );
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to open site container", stat);
        return;
    }


    stat = SmsPopulate(hContainerSite, POP_SYNC, NULL);
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to populate site container", stat);
        return;
    }


    HANDLE ahFolderSite[C_MAXSITES];
    HANDLE hFolderSite;
    int ctFolders = 0;
    int iFolder;


    // Get the folder handle for each folder in the site container.  Also
    // count the folders so that we know how many we have.
    //===================================================================
    while(SmsGetNextFolder(hContainerSite, F_SITE, &hFolderSite) == SMS_OK) {
        ahFolderSite[ctFolders] = hFolderSite;
        ++ctFolders;
    }



    // Ask the user to select one of the sites.  After the user
    // select's a site, copy its name to pszSiteName.
    //=========================================================
    char szValue[CCH_MAXSTRING];
    if (ctFolders > 0) {
        printf("******************************************\n");
        printf("* Select a site from the following list. *\n");
        printf("******************************************\n");
        printf("\n");


        for(iFolder=0; iFolder < ctFolders; ++iFolder) {
            GetScalarString(ahFolderSite[iFolder], "Site name", szValue, sizeof(szValue));
            printf("[%d]. %s\n", iFolder + 1, szValue);
        }
        printf("\n");


        InputString("Enter site number", szValue);
        printf("\n");
        sscanf(szValue, "%d", &iFolder);

        if (iFolder > 0 && iFolder <= ctFolders) {
            GetScalarString(ahFolderSite[iFolder-1], "Site name", szValue, sizeof(szValue));
            strcpy(pszSiteName, szValue);
        }
    }

    // Close all of the site folders that we opened via SmsGetNextFolder.
    //===================================================================
    for (iFolder = 0; iFolder < ctFolders; ++iFolder) {
        SmsCloseFolder(ahFolderSite[iFolder]);
    }

}


// ====================================================================
//
// GetJobType
//
// This function query's the user to select the type of SMS job he or
// she would like to create.
//
// Parameters: None.
//
// Returns.  A status code indicating the job type.
//      CMD_RUN_COMMAND = Run command on workstation job.
//      CMD_SHARE_PACKAGE = Share package on server job.
//      CMD_QUIT = Exit without creating a job.
//
// ====================================================================
int GetJobType()
{
    printf("***************************************\n");
    printf("* Select the job type to create.      *\n");
    printf("***************************************\n");
    printf("1. Run command on workstation.\n");
    printf("2. Share package on server.\n");
    printf("3. Quit.\n");
    printf("\n");

    char szReply[CCH_MAXSTRING];
    InputString("Enter the job type", szReply);
    printf("\n");

    int iType = 0;
    sscanf(szReply, "%d", &iType);
    switch(iType) {
    case 1:
        return(CMD_RUN_COMMAND);
    case 2:
        return(CMD_SHARE_PACKAGE);
    default:
        return(CMD_QUIT);
    }
}




// ********************************************************************
//      Helper functions.
// ********************************************************************




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
//      char** argv
//          The argv value from main(argc, argv)
//
// Returns:
//      TRUE if command line parameters included a request
//      for help to be displayed.
//
// ====================================================================
BOOL DidRequestHelp(int argc, char** argv)
{
    if (argc == 2  && (strcmp(argv[1], "-help") == 0)) {
        return(TRUE);
    }
    else {
        return(FALSE);
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
    printf("* srvinst.exe:                                            *\n");
    printf("*                                                         *\n");
    printf("* SMS API Example: Creation of jobs.                      *\n");
    printf("*                                                         *\n");
    printf("* This sample program demonstrates how the SMS SDK can    *\n");
    printf("* be used to create a \"share package on server\" job or a  *\n");
    printf("* \"run command on workstation\" job.                       *\n");
    printf("*                                                         *\n");
    printf("* Prior to running this program, you must first share the *\n");
    printf("* directory where the source files are for the package.   *\n");
    printf("*                                                         *\n");
    printf("* Syntax:                                                 *\n");
    printf("*     srvinst.exe [-help]                                 *\n");
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



/* EOF: srvinst.cpp */

