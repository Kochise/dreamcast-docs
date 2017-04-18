// ===========================================================================
// Copyright (C) 1995 by Microsoft Corporation.
//
//  File: deljob.cpp
//
//  This program illustrates how to use the SMS SDK to delete an SMS
//  job.
//
//  Author: Larry A. French
//
// ===========================================================================


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
//      Defines.
// ====================================================================

#define CCH_MAXSTRING   256
#define MAX_CREATE      100



// ====================================================================
//  Local prototypes.
// ====================================================================
const char *GetStatusName( SMS_STATUS stat );

void DisplaySmsError(const char* pszMessage, SMS_STATUS stat);

BOOL DidRequestHelp(int argc, char** argv);

HANDLE ConnectToDatasource();

void DisplayHelp();

void InputString(const char* pszMessage, char* pszResult);

void DisplayGreeting();

BOOL UserSaysYes(const char* pszPrompt);


// ====================================================================
//  Structs.
// ====================================================================
// This struct holds a folder handle and its ID.
typedef struct _FOLDERREC {
    HANDLE hFolder;                     // Handle to a folder.
    char szID[SMS_DATA_BUFF_SIZE+1];    // Its ID.
    BOOL bDeleted;                      // marked as deleted in this program.
} FOLDERREC;



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
    HANDLE hContainerJob;
    char szJobID[SMS_DATA_BUFF_SIZE + 1];
    char szPrompt[CCH_MAXSTRING];



    // Connect to the data source. If the connect fails, give up.
    // Note a message will have already been displayed by
    // ConnectToDatasource.
    //===========================================================
    hConnect = ConnectToDatasource();
    if (hConnect == NULL) {
        return;
    }

    // Open package container.
    // =======================
    stat = SmsOpenContainer( C_JOB, hConnect, &hContainerJob );
    if (stat != SMS_OK) {
        printf("SmsOpenContainer failed: %d\n", stat);
        SmsDataSourceDisconnect( hConnect );
        return;
    }




    // Select all folders (no filters.)
    // ================================
    stat = SmsPopulate( hContainerJob, POP_SYNC, NULL);
    if (!(stat == SMS_OK || stat==SMS_EMPTY)) {
        printf("Bad return from SmsPopulate: %d\n", stat);
        SmsCloseContainer( hContainerJob );
        SmsDataSourceDisconnect( hConnect );
        return;
    }




    FOLDERREC *paFolderRec = NULL;

    // Get count of folders in container, allocate memory.
    // ===================================================
    DWORD ctFolders;
    SmsGetFolderCount( hContainerJob, F_ANY, &ctFolders );
    paFolderRec = (FOLDERREC *)malloc( ctFolders * sizeof(FOLDERREC) );

    // Retrieve all the jobs and store their handles and IDs.
    // ======================================================
    for (DWORD dwI = 0; dwI < ctFolders; dwI++) {

        SmsGetNextFolder( hContainerJob, F_ANY, &(paFolderRec[dwI].hFolder) );
        SmsGetFolderID( paFolderRec[dwI].hFolder, paFolderRec[dwI].szID );
        paFolderRec[dwI].bDeleted = FALSE;
    }
    
    BOOL bDidDeleteFolder;

AGAIN:
    
    // The bDidDelete flag is used to indicate whether or not
    // the folder deletion was successful.  We assume that something
    // will go wrong until we have proven otherwise and know that
    // the folder was in fact deleted.
    //=============================================================
    bDidDeleteFolder = FALSE;

    printf("**************************************************\n");
    printf("* Please enter the ID of the job that you wish   *\n");
    printf("* to delete.                                     *\n");
    printf("* Available jobs are:                            *\n");
    printf("**************************************************\n");

    // Display the job IDs.
    // ====================
    for (dwI = 0; dwI < ctFolders; dwI++) {
        if (!paFolderRec[dwI].bDeleted) {
            printf("[%d] %s\n", dwI, paFolderRec[dwI].szID);
        }
    }
    printf("\n");

    InputString("Job ID", szJobID);
    sprintf(szPrompt, "Delete job \"%s\"", szJobID);


    if (UserSaysYes(szPrompt)) {
        // Control comes here if the user has given the OK to delete
        // the specified job. To delete the job, we first get its
        // its folder handle, unlink the folder, and then commit it.
        // Note that SmsGetFolderByID doesn't work on containers.
        //
        // Search the array of FOLDERRECs looking for this ID.
        // =========================================================
        BOOL bFound = FALSE;
        for (dwI = 0; dwI < ctFolders; dwI++) {
            if (strcmp( szJobID, paFolderRec[dwI].szID ) == 0) {

                // Check that not already deleted
                if (!paFolderRec[dwI].bDeleted) {
                    bFound = TRUE;
                }
                break;
            }
        }


        // If we found the ID, unlink and commit the folder.
        // =================================================
        if (bFound) {
            // Unlink the folder to remove it from the in-memory hierarchy.
            //============================================================
            stat = SmsUnlinkFolder(paFolderRec[dwI].hFolder);
            if (stat != SMS_OK) {
                DisplaySmsError("Failed to unlink the job folder", stat);
            }


            // Commit the unlinked folder to delete the folder in the
            // datasource.
            //=======================================================
            stat = SmsCommitFolder(paFolderRec[dwI].hFolder);
            if (stat != SMS_OK) {
                DisplaySmsError("Failed to commit the job folder", stat);
            }

            // If all OK then mark that job as deleted in our array.
            // =====================================================
            if (stat == SMS_OK) {
                paFolderRec[dwI].bDeleted = TRUE;
                bDidDeleteFolder = TRUE;
                printf("Job: %s was deleted succesfully\n\n", szJobID);
            }

        } else {
            printf("Job %s not found\n", szJobID );
        }

    }

    // Allow user to try again.
    // (This is one of the few cases where a goto is permitted.)
    // =========================================================
    
    if (UserSaysYes(bDidDeleteFolder ? "Delete another job?" : "Try again?")) {
        goto AGAIN;
    }


    // Close all job folders.
    // ======================
    for (dwI = 0; dwI < ctFolders; dwI++) {
        SmsCloseFolder( paFolderRec[dwI].hFolder );
    }


    // Close the container.
    //=====================
    stat = SmsCloseContainer( hContainerJob );
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to close the package container", stat);
    }

    // Disconnect from the datasource.
    //================================
    stat = SmsDataSourceDisconnect( hConnect );
    if (stat != SMS_OK) {
        DisplaySmsError("Failed to disconnect from the datasource", stat);
    }


}  /* main */




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
//
// ====================================================================
BOOL UserSaysYes(const char* pszPrompt)
{
    printf("%s? [y/n]", pszPrompt);
    char szReply[256];
    gets(szReply);

    return(szReply[0] == 'y' || szReply[0] == 'Y');
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
    printf("* deljob.exe:                                          *\n");
    printf("*                                                      *\n");
    printf("* This program illustrates how to use the SMS SDK to   *\n");
    printf("* delete a job in the SMS database.                    *\n");
    printf("*                                                      *\n");
    printf("* Syntax:                                              *\n");
    printf("*     deljob.exe [-help]                               *\n");
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




/* EOF: deljob.cpp */

