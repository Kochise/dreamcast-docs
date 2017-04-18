// ====================================================================
//
//  File: newjob.cpp
//
//  Copyright (C) 1994, 1995 by Microsoft Corporation.
//
//  Author:
//      Jonathan Shuval     Microsoft Corp.
//
//
//  This program illustrates the use of the SMS APIs to view, create
//  and delete jobs.
//
//  See the readme.txt file in this directory for more information.
//
//
// ====================================================================



// ====================================================================
//  Includes.
// ====================================================================
#include <afx.h>
#include <smsapi.h>                 // Header for the APIs.
#include <time.h>                   // for time functions.

// Include the GetStatusName function.
// -------------------------------------
#include "..\common\status.inc"



// ====================================================================
//
//  Defines.
//
// ====================================================================
#define CCH_MAXINPUT 256



// ====================================================================
//  Local prototypes.
// ====================================================================


// Display the folder's scalars.
// -------------------------------------------------------------
void DisplayScalars( HANDLE hFolder );


// Display a folder.
// -------------------------------------------------------------
void ViewFolder( HANDLE hFolder );


// Create a new folder.
// -------------------------------------------------------------
void CreateNewFolder( HANDLE hParent );


// Convert date string from "dd\mm\yy hh:mm" to time_t.
// -------------------------------------------------------------
time_t ReadTime( char szTime[] );


// Prompt the user for input and return the reply.
//------------------------------------------------
void InputString(const char* pszMessage, char* pszResult);


// Connect to the SMS datasource.
//------------------------------
HANDLE ConnectToDatasource();




// Display the help message.
//=========================
void DisplayHelp();

// Display the greeting.
//======================
void DisplayGreeting();


// Check to see if there was a request for help
// on the command line.
//==============================================
BOOL DidRequestHelp(int argc, char** argv);



// Display an error message with its SMS status value.
//====================================================
void DisplaySmsError(const char* pszMessage, SMS_STATUS stat);

// Get the string equivallent for an SMS status code.
//===================================================
const char* GetStatusName(SMS_STATUS stat);






// ====================================================================
//  The work starts here.
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
    HANDLE hContainer;


    //===========================================
    // Connect to the SMS datasource.
    //===========================================
    hConnect = ConnectToDatasource();
    if (hConnect == NULL) {
        return;
    }

    // Open job container.
    // ===================
    stat = SmsOpenContainer( C_JOB, hConnect, &hContainer );
    if (stat != SMS_OK) {
        DisplaySmsError("SmsOpenContainer failed", stat);
        SmsDataSourceDisconnect( hConnect );
        return;
    }


    // Set filters.
    // ============
    // None.


    // Select all folders matching our filters.
    // ========================================
    stat = SmsPopulate( hContainer, POP_SYNC, NULL );
    if (stat != SMS_OK && stat != SMS_EMPTY) {
        DisplaySmsError("Bad return from SmsPopulate", stat);
        SmsCloseContainer( hContainer );
        SmsDataSourceDisconnect( hConnect );
        return;
    }



    // Retrieve all the folders from the container and save them
    // away in a list. SmsGetFolderCount tells us how many folders
    // are in the container, use this value to allocate space for
    // the handles.
    // Don't close the container because it will be needed if we
    // want to create a job.
    // ===========================================================
    DWORD  numFolders;
    DWORD  dwI;
    HANDLE *phFolders;
    HANDLE hFolder;

    SmsGetFolderCount( hContainer, F_ANY, &numFolders);
    printf("==========  Container has %d folders  =========\n\n", numFolders );


    // Allocate memory for the top-level folders.
    // ------------------------------------------
    phFolders = (HANDLE *)malloc(numFolders * sizeof(HANDLE));

    // Open all top-level folders.
    // ---------------------------
    for (dwI = 0; dwI < numFolders; dwI++) {

        stat = SmsGetNextFolder( hContainer, F_ANY, &hFolder );
        if (stat != SMS_OK) {
            DisplaySmsError("Error in retrieving a folder", stat);
            break;
        }

        phFolders[dwI] = hFolder;
    }


    // Now we enter a loop asking the user whether they want to
    // view the next folder, delete the folder just displayed,
    // or create a new folder.
    // =========================================================
    BOOL  done = FALSE;
    char  reply[10];
    DWORD dwIndex = 0;
    char  szFolderID[SMS_DATA_BUFF_SIZE+1];

    // Display the first one (if it exists). That way we always
    // have a current folder.
    // If we don't have any then that's ok because the Delete
    // will fail like it's supposed to.
    // ========================================================
    if (numFolders > 0) {
        ViewFolder( phFolders[dwIndex] );
    }

    printf("You may now do one of the following:\n");
    printf("View the Next folder, Delete the current folder, Create a new folder\n");
    printf("Type X to exit\n");

    while (!done) {

        printf("[NDCX]: ");
        gets(reply);

        switch (reply[0]) {
        case 0:
        case 'N': case 'n':
            // =========== View next folder ====================
            dwIndex++;
            if (dwIndex < numFolders) {
                ViewFolder( phFolders[dwIndex] );
            } else {
                printf("No more folders to view\n");
            }
            break;

        case 'D': case 'd':
            // =========== Delete current folder ===============
            // Check we have a folder to delete.
            if (dwIndex >= numFolders) {
                printf("No folder to delete\n");
                break;
            }

            SmsGetFolderID( phFolders[dwIndex], szFolderID );
            printf("Confirm deletion of folder \"%s\"? [y/n] ", szFolderID);
            gets(reply);
            if (reply[0] != 'y') {
                printf("Delete cancelled\n");
                break;
            }

            stat = SmsUnlinkFolder( phFolders[dwIndex] );
            if (stat != SMS_OK) {
                DisplaySmsError( "SmsUnlinkFolder failed", stat);
                break;
            }
            stat = SmsCommitFolder( phFolders[dwIndex] );
            if (stat != SMS_OK) {
                DisplaySmsError("SmsCommitFolder error", stat);
                break;
            }

            printf("Folder deleted\n");
            break;

        case 'C': case 'c':
            // =========== Create new folder ===================
            CreateNewFolder( hContainer );
            break;

        case 'X': case 'x':
            // Terminate.
            done = TRUE;
            break;

        default:
            // print the message again.
            printf("Actions are: N(ext folder), D(elete folder), C(reate folder)\n");
            printf("Type X to exit\n");
            break;
        }
    }





    // Close the container, and disconnect from datasource.
    // ----------------------------------------------------
    SmsCloseContainer( hContainer );
    stat = SmsDataSourceDisconnect( hConnect );


    // Deallocate memory used for folder handles.
    // ------------------------------------------
    free( phFolders );

}  /* main */





// ====================================================================
// Display the folder contents.
//
//  This version only displays the folder name and type, number of
//  scalars, and the scalars. Other information not relevant.
//
//  NOTE: no error checking.
//
// ====================================================================
void ViewFolder( HANDLE hFolder )
{
    char szFolderID[SMS_DATA_BUFF_SIZE+1];              // This folder's ID.
    char szfType[SMS_DATA_BUFF_SIZE+1];                 // Folder's tag.
    DWORD fType;                                        // Folder's type.
    DWORD ctScalars;                                    // How many scalars in this folder.
    SMS_STATUS stat;

    // Get folder ID and type.
    // -----------------------
    stat = SmsGetFolderID( hFolder, szFolderID );
    // Test return. If this is a newly created folder that hasn't been
    // inserted into the datasource it will not yet have a valid ID.
    if (stat != SMS_OK) {
        strcpy(szFolderID, "<New Job>");
    }
    stat = SmsGetFolderType( hFolder, &fType, szfType );

    // Rewind the folder, just in case.
    // This allows us to re-examine a folder (ie call this multiple times).
    // ====================================================================
    SmsRewind( hFolder, RW_ALL );

    // Get count of scalars.
    // ---------------------
    stat = SmsGetScalarCount( hFolder, &ctScalars );
    printf("%s (%s) contains %d scalars\n", szFolderID, szfType, ctScalars);

    // Display the scalars.
    // --------------------
    DisplayScalars( hFolder );

    printf("============== %s ===========\n", szFolderID);

}  /* ViewFolder */



// ====================================================================
//
//  Create a new folder.
//
//  This is an example of how to create a folder.
//
//  There are several types of job folder. This function can create:
//      a run command on workstation job
//      a share package on server job
//      a remove package from server job.
//
//
// ====================================================================

void CreateNewFolder( HANDLE hParent )
{
    printf("This function allows the creation of one of:\n");
    printf("\t\"Run command on Workstation\" job (w)\n");
    printf("\t\"Share package on Server\" job    (s)\n");
    printf("\t\"Remove package from Server\" job (r)\n");

    DWORD dwJobType;
    char szType[10];
    BOOL done = FALSE;

    while (!done) {
        done = TRUE;

        printf("Enter one of [wsr]: ");
        gets(szType);

        switch (szType[0]) {
        case 'w': case 'W':
            dwJobType = F_INSTALLJOB;
            break;

        case 's': case 'S':
            dwJobType = F_SRVINSTALLJOB;
            break;

        case 'r': case 'R':
            dwJobType = F_REMPKGJOB;
            break;

        default:
            done = FALSE;
            printf("Invalid reply\n");
        }
    }

    HANDLE hNewFolder;
    SMS_STATUS stat;

    // Note the id of "<New Job>", this is because for jobs, SMS assigns
    // the job id itself.

    stat = SmsCreateFolder( hParent, dwJobType, "<New Job>", &hNewFolder );
    if (stat != SMS_OK) {
        DisplaySmsError("SmsCreateFolder fails", stat);
        return;
    }

    // Use an objectity engine API to get information about the
    // folder and its scalars.
    // ---------------------------------------------------------
    FOLDER_INFO *pFInfo;
    stat = SmsDescribeFolder( T_FOLDER, dwJobType, &pFInfo );

    SCALAR_INFO *pSInfo;        // The info structure contains a pointer
                                // to an array of SCALAR_INFOs. Each of these
                                // describes a scalar.
    SCALAR sc;                  // We create scalars using a SCALAR.

    // Data for retrieving information from user for scalars.
    char szValue[SMS_DATA_BUFF_SIZE+1];     // User enters value here.
    time_t time;                            // Times are converted to t_time.


    // Loop through all the scalars, ask the user to supply a
    // value, but only if the scalar is modifiable.
    // =========================================================

    for (DWORD dwI = 0; dwI < pFInfo->ctScalars; dwI++) {

        pSInfo = &pFInfo->pScalars[dwI];

        // Is scalar modifiable?
        if (pSInfo->fAccess == ACCESS_CREATE || pSInfo->fAccess == ACCESS_MODIFY) {

            // Set up common fields in the scalar.
            // -----------------------------------
            sc.pszName = pSInfo->szName;
            sc.scType  = pSInfo->scType;

            char *pszType;

            switch (sc.scType) {
            case SCALAR_STRING:
                pszType = "string";     break;

            case SCALAR_INT:
                pszType = "integer";    break;

            case SCALAR_TIME:
                pszType = "time";       break;

            case SCALAR_BINARY:
                pszType = "binary";     break;
            }
            printf("Enter (%s) value for '%s': ", pszType, pSInfo->szName);

            // Now we need to know what type this is (string, int etc)
            if (pSInfo->scType == SCALAR_STRING) {
                gets( szValue );
                // store it directly
                sc.dwLen = sizeof(szValue)-1;   // -1 for terminating NULL.
                sc.pszValue = szValue;

                stat = SmsSetScalar( hNewFolder, &sc );


            } else if (pSInfo->scType == SCALAR_INT) {
                gets( szValue );
                // convert to int
                sc.dwValue = atol( szValue );

                stat = SmsSetScalar( hNewFolder, &sc );


            } else if (pSInfo->scType == SCALAR_TIME) {
                printf("Enter time in the form mm/dd/yy hh:mm ");
                gets( szValue );
                // Only primitive checking
                time = ReadTime( szValue );
                sc.tValue = time;

                stat = SmsSetScalar( hNewFolder, &sc );


            } else if (pSInfo->scType == SCALAR_BINARY) {
                // Be simplistic about this.
                gets( szValue );
                memcpy( sc.pValue, szValue, strlen(szValue) );
                stat = SmsSetScalar( hNewFolder, &sc );
            }
        }

    }


    // Now display it and ask user for confirmation of creation.
    // =========================================================
    printf("Newly created folder:\n");
    ViewFolder( hNewFolder );
    printf("OK to link folder into parent [y/n]? ");
    char reply[10];
    gets(reply);
    if (reply[0] == 'y') {
        // link it in to parent.
        stat = SmsLinkFolder( hNewFolder );
        if (stat != SMS_OK) {
            DisplaySmsError("SmsLinkFolder error", stat);
            return;
        }

        // write it back to data source.
        stat = SmsCommitFolder( hNewFolder );
        if (stat != SMS_OK) {
            DisplaySmsError("SmsCommitFolder error", stat);
            return;
        }
        SmsGetFolderID( hNewFolder, szValue );

        char *pszType;
        switch (dwJobType) {
        case F_INSTALLJOB:
            pszType = "Workstation install job";
            break;

        case F_SRVINSTALLJOB:
            pszType = "Server share job";
            break;

        case F_REMPKGJOB:
            pszType = "Remove package job";
            break;

        }

        printf("*****  %s %s created *****\n\n", pszType, szValue);

        printf("View of new folder from the datasource...\n");
        ViewFolder( hNewFolder );
        printf("\n\n");

    } else {
        printf("Folder creation cancelled\n");
    }

}



// ====================================================================
//
//  Display all the scalars for the folder.
//
//  This example also shows how the scalar can detect that a buffer is
//  too small.
// ====================================================================
void DisplayScalars( HANDLE hFolder )
{
    SMS_STATUS stat = SMS_OK;
    SCALAR scalar;
    char szName[SMS_DATA_BUFF_SIZE+1];       // buffer for name
    char szValue[SMS_DATA_BUFF_SIZE+1];      // buffer for value
    char *pszTime;          // For conversion of time scalars.


    scalar.pszName  = szName;
    scalar.pszValue = szValue;


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
            printf("\t%25s: %s\n", scalar.pszName, scalar.pszValue);
            break;

        case SCALAR_INT:
            printf("\t%25s: %ld\n", scalar.pszName, scalar.dwValue);
            break;

        case SCALAR_TIME:
            // If there is a string equivalence use it.
            if (scalar.bStringEquivalence) {
                printf("\t%25s: %s\n", scalar.pszName, scalar.pszValue);
            } else {
                pszTime = ctime( &scalar.tValue );
                printf("\t%25s: %s", scalar.pszName, pszTime);
            }
            break;

        case SCALAR_BINARY:
            // Got binary data.
            // Just tell the user how much data there is.
            printf("\t%25s: Binary data %d bytes of data\n",
                    scalar.pszName, scalar.dwLen);
            break;
        }
    }

    // Why did we exit (other than no more scalars)?
    // ---------------------------------------------
    if (stat != SMS_NO_MORE_DATA) {
        DisplaySmsError("Bad return from Scalar access", stat);
    }

}



// ********************************************************************
//      Helper functions.
// ********************************************************************


// ====================================================================
//  Convert time string to time_t. Primitive checking only.
//  If there are any errors we print a wanring and set the date/time to
//  today.
// ====================================================================
time_t ReadTime( char szTime[] )
{
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
    printf("***********************************************************\n");
    printf("* newjob.exe:                                             *\n");
    printf("*                                                         *\n");
    printf("* SMS API Example: view, create, and delete job folders.  *\n");
    printf("*                                                         *\n");
    printf("* This sample illustrates the use of the SMS APIs in      *\n");
    printf("* order to view create, and delete job folders.           *\n");
    printf("* There are four types of job folders:                    *\n");
    printf("*         Run command on Workstation job                  *\n");
    printf("*         Share package on Server job                     *\n");
    printf("*         Remove package from Server job                  *\n");
    printf("*         System job                                      *\n");
    printf("* All of these except system jobs can be created and      *\n");
    printf("* deleted.                                                *\n");
    printf("*                                                         *\n");
    printf("* Syntax:                                                 *\n");
    printf("*     newjob.exe [-help]                                  *\n");
    printf("*                                                         *\n");
    printf("* Switches:                                               *\n");
    printf("*     -help       Display this help message.              *\n");
    printf("*                                                         *\n");
    printf("***********************************************************\n");
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




/* EOF: newjob.cpp */
