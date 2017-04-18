
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1995-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <string.h>     // includes the string functions
#include <shlobj.h>     // To update the desktop
#include <regstr.h>

#include "setupapi.h"   // includes the inf setup api 
#include "instwiz.h"    // includes the application-specific information
#include "infinst.h"    // includes the application-specific information
#include "infdesc.h"    // includes the specifics of how this
                        // inf is layed out, like the inf names
                        // the HKeys and the DirIds

DWORD InstallFinish(BOOL DoRunOnce);

//
//    FUNCTION: BOOL DoInstallation( HWND hWnd, INSTALLINFO * si )
//
//    PURPOSE: Install components via setupapi.dll.
//
//   COMMENTS:
//    
//      The function does inf install operations based
//      on the content of the INSTALLINFO data.
//      These steps could be done during the wizard but
//      this technique allows for installations with user input.
//
// This routine will take a INSTALLINFO
// and do an installation based on those settings
// using the setupapi.dll

BOOL DoInstallation( HWND hWnd, INSTALLINFO * si )
{

    HINF hInf;
    char szSourcePath[MAX_PATH];
    char szInfFileName[MAX_PATH];
    
    DWORD dwResult;
    BOOL bResult = FALSE;

    // Context for my call back routine
    MY_INSTALL_DATA MyInstallData;

    HSPFILEQ FileQueue;

    //
    // First we setup the inf to what the wizard collected
    // note the hInf will maintain the information and let
    // you build copy list as you go
    // This sample seperates the wizard from the setapi stuff
    // just to keep the setupapi stuff in one place
    //

    //
    // The install process overview is: 
    //   TASK                       SETUPAPI
    //   open a specific inf        SetupOpenInfFile
    //   call the wizard for input  CreateWizard (implemented in instwiz.c)
    //   set the directory ids      SetupSetDirectoryId 
    //   create a file queue        SetupOpenFileQueue
    //   create a queue context     SetupInitDefaultQueueCallback
    //   add files to queue         SetupInstallFilesFromInfSection
    //   do the copy                SetupCommitFileQueue
    //???   do the registry stuff      SetupInstallFromInfSection
    //   close the queue            SetupTermDefaultQueueCallback
    //   close the inf              SetupCloseFileQueue
    
    //
    // In this sample we assume the inf is in the base of the
    // base installation source path--it usually is for most installs
    //
    
    GetModuleFileName(NULL, szSourcePath, _MAX_PATH);
    *(strrchr(szSourcePath, '\\') + 1) = '\0';        // Strip setup.exe off path

    strcpy(szInfFileName, szSourcePath);
    strcat(szInfFileName, "product.inf");

    //
    // Get inf handle
    // must know where the inf is located 
    // SetupOpenInfFile will only look in windows\inf by default
    //

    hInf = SetupOpenInfFile ( 
        szInfFileName,       // If path,needs full path, else looks in %windir%\inf
        NULL,                // Inf Type, matches Class in [Version] section SetupClass=SAMPLE
        INF_STYLE_WIN4,      // or INF_STYLE_OLDNT
        NULL                 // Line where error occurs if inf is has a problem
        );

    if (hInf == INVALID_HANDLE_VALUE) 
    {
        dwResult = GetLastError();

        //   
        // TODO: handle case where inf cannot be opened
        //       by asking the user to locate the inf
    
        return FALSE;
    }

    // Run the wizard
    if (CreateWizard(hWnd, si->hInst))
    {
        RuntimeRegistration(si);
    }
    else
    {
        SetupCloseInfFile(hInf);
        return FALSE;
    }
 
    //
    // Special case the uninstall destitation path
    // this is because we need to get the registry value
    // for where to delete the files from. 
    //

    if (IDC_INSTALL_TYPE_UNINSTALL == si->iInstall_Type)
    {
        // get path installed to here!
        // query registry for si->pszDestPath

        GetRegString (MYPRODUCT_KEY, TEXT("DestinationPath"),
                si->pszDestPath);
    }

    //
    // Directory ids are set per HINF
    //
    // TODO: verify dest path as a valid file name

    bResult = SetupSetDirectoryId(hInf,          // the HINF that will hold these ids
                        (DWORD) DESTINATION_DIR, // the id that matchs one in the inf
                        si->pszDestPath);        // the user's string
    
    if(!bResult) 
    {
        dwResult = GetLastError();
        
        // TODO: handle case where we cannot set dirids, should we default or bail?
        //       perhaps write this out to an error log
        // 
        // Close the inf file and return
        //

        SetupCloseInfFile(hInf);
        return FALSE;
    }

    //
    // Create a Setup file queue and initialize the default Setup
    // queue callback routine.
    //

    FileQueue = SetupOpenFileQueue();

    if(!FileQueue || (FileQueue == INVALID_HANDLE_VALUE)) 
    {
        dwResult = ERROR_NOT_ENOUGH_MEMORY;
        
        //
        // Close the queue and return
        //

        SetupCloseInfFile(hInf);
        return FALSE;
    }

    //
    // This initialize memory for the default call back
    // This context MUST be used if our private callback routine 
    //     wants to callback into the default routine, we do it here with 
    //     a global value for the default context
    //
    // We want to use the default progress dialog.
    // We could override this by specifying a window that
    // will handle the ui in param 2.  
    // By not passing a progress HWND this is the same as 
    // using SetupInitDefaultQueueCallback.
    //

    MyInstallData.pDefaultContext = SetupInitDefaultQueueCallbackEx(
                    hWnd,  // HWND of owner window
                    NULL,  // HWND of alternate progress dialog which receives -- for example
                           //      if you wanted to display your progress bar right in the wizard
                    0,     // Message sent to above window indicating a progress message
                    0,     // DWORD Reserved
                    NULL   // PVOID Reserved
                    );

    if(!(MyInstallData.pDefaultContext)) 
    {
        dwResult = ERROR_NOT_ENOUGH_MEMORY;

        //
        // Close the queue and the inf file and return
        //

        SetupCloseFileQueue(FileQueue);
        SetupCloseInfFile(hInf);
        return FALSE;
    }

    //
    // Now that we have a FileQueue, a Queue Context, and an HINF
    // we want to map the DirectoryIds in the INF to the ones
    // obtained by the user 

    //
    // Queue file operations and commit the queue.
    //

    //
    // Install each option they have selected
    //

    if (IDC_INSTALL_TYPE_UNINSTALL == si->iInstall_Type)
    {
        //TODO: allow the user to remove specific components
        //      note you would want to update the wizard to reflect this
        
        bResult = SetupInstallFilesFromInfSection(
                  hInf,     // HINF that has the directory ids set above
                  NULL,          // layout.inf if you have one, this a convient
                                 //     place to do all of your file to media id mapping
                  FileQueue,     // Queue to add files to
                  TEXT("MyProgramUninstall"),   // SectionName,
                  szSourcePath,    // Path where the source files are located
                  SP_COPY_NEWER);// The controls how to version check
                                 // and how to prompt
    }
    else
    {

      if (si->iCustom_Options1){
        bResult = SetupInstallFilesFromInfSection(
                      hInf,     // HINF that has the directory ids set above
                      NULL,          // layout.inf if you have one, this a convient
                                     //     place to do all of your file to media id mapping
                      FileQueue,     // Queue to add files to
                      INF_OPTION1,   // SectionName,
                      szSourcePath,    // Path where the source files are located
                      SP_COPY_NEWER);// The controls how to version check
                                     // and how to prompt
        }
        
        if (si->iCustom_Options2) {
            bResult = SetupInstallFilesFromInfSection(hInf, NULL, 
                FileQueue, INF_OPTION2, szSourcePath, SP_COPY_NEWER );
        }

        if (si->iCustom_Options3) {
            bResult = SetupInstallFilesFromInfSection(hInf, NULL, 
                FileQueue, INF_OPTION3, szSourcePath, SP_COPY_NEWER );
        }

        if (si->iCustom_Options4) {
            bResult = SetupInstallFilesFromInfSection(hInf, NULL, 
                FileQueue, INF_OPTION4, szSourcePath, SP_COPY_NEWER );
        }
    }

    //
    // All the files for each component are now in one queue
    // now we commit it to start the copy ui, this way the
    // user has one long copy progress dialog--and for a big install
    // can go get the cup of coffee 
    //
    if(bResult) {
        
        bResult = SetupCommitFileQueue(
                hWnd,                      // Owner
                FileQueue,                 // Queue with the file list
                (PSP_FILE_CALLBACK) MyQueueCallback, 
                                           // This is our handler, it calls the default for us
                                           // NOTE:
                                           // (PSP_FILE_CALLBACK) SetupDefaultQueueCallback
                                           // would use the default message handler automatically
                &MyInstallData             // Pointer to resources allocated with SetupInitDefaultQueueCallback/Ex                 
                );

        dwResult = bResult ? NO_ERROR : GetLastError();

    } else {
        
        dwResult = GetLastError();
    
    }

    //
    // Do registry munging, etc. 
    // NOTE: you can do the entire install
    // for a section with this api but in this case
    // we build the file list conditionally and
    // do only out ProductInstall section for registy stuff
    // Also using SPINST_FILES will do the files
    // as above but only one section at a time
    // so the progress bar would keep completing and starting over
    // SPINST_ALL does files, registry and inis
    // 
    if (si->iCustom_Options1)
    {
      bResult = SetupInstallFromInfSection(
            hWnd,
            hInf,
            INF_OPTION1,
            SPINST_REGISTRY | SPINST_INIFILES,
            NULL,
            NULL,//szSourcePath,    // Path where the source files are located
            0,//SP_COPY_NEWER,
            NULL,//(PSP_FILE_CALLBACK) MyQueueCallback, 
            NULL,//&MyInstallData,
            NULL, 
            NULL
            );
    }

    //
    // Perserve first non-success error code.
    //
    if(!bResult && (dwResult == NO_ERROR)) {
    
        dwResult = GetLastError();
    
    }

    //
    // We're done so free the context, close the queue,
    // and release the inf handle
    //

    SetupTermDefaultQueueCallback(MyInstallData.pDefaultContext);
    SetupCloseFileQueue(FileQueue);
    SetupCloseInfFile(hInf);
    
    if(dwResult != NO_ERROR) {
    
        // TODO: Log an error here
    
    }

    if (bResult) {
    
        // do whatever you need to complete a successful install

        //
        // Refresh the desktop for folders and icons.
        //
        InstallFinish(TRUE);    

    } else {

        MessageBox( hWnd, 
            TEXT("Installation script did not complete successfully!"), 
            TEXT("Product Sample Install Error"), 
            MB_OK);
    }
    
    return TRUE;
}

LRESULT 
WINAPI
MyQueueCallback (
    IN MY_INSTALL_DATA* pMyInstallData,
    IN UINT Notification,
    IN UINT Param1,
    IN UINT Param2
    )
{
    if (SPFILENOTIFY_DELETEERROR == Notification)
    {
        // Skip any file delete errors
        // this sample only deletes files on an unintall
        // so if the delete encounters an error simply skip the operation
        // and continue processing the queue
        return FILEOP_SKIP;
    }
    else
    {
        // Pass all other notifications through without modification
        return SetupDefaultQueueCallback(pMyInstallData->pDefaultContext, 
                                         Notification, Param1, Param2);
    }
}


DWORD
InstallFinish(
    IN BOOL DoRunOnce
    )
/*++

Routine Description:

    This routine sets up runonce/grpconv to run after a successful INF installation.

Arguments:

    DoRunOnce - If TRUE, then invoke (via WinExec) the runonce utility to perform the
        runonce actions.  If this flag is FALSE, then this routine simply sets the
        runonce registry values and returns.

        NOTE:  The return code from WinExec is not currently being checked, so the return
        value of InstallStop only reflects whether the registry values were set up
        successfully--_not_ whether 'runonce -r' was successfully run.

Return Value:

    If successful, the return value is NO_ERROR, otherwise it is the Win32 error code
    indicating the error that was encountered.

--*/
{
    HKEY  hKey, hSetupKey;
    DWORD Error;
    LONG l;

    //
    // First, open the key "HKLM\Software\Microsoft\Windows\CurrentVersion\RunOnce"
    //
    if((l = RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
                         REGSTR_PATH_RUNONCE, 
                         0, KEY_ALL_ACCESS, &hKey)) != ERROR_SUCCESS) {
        return (DWORD)l;
    }

    //
    // If we need to run the runonce exe for the setup key...
    //
    if(RegOpenKeyEx(hKey,
                    TEXT("Setup"),
                    0,
                    KEY_READ,
                    &hSetupKey) == ERROR_SUCCESS) {
        //
        // We don't need the key--we just needed to check its existence.
        //
        RegCloseKey(hSetupKey);

        //
        // Add the runonce value.
        //
        Error = (DWORD)RegSetValueEx(hKey,
                                     TEXT("Wrapper"),
                                     0,
                                     REG_SZ,
                                     TEXT("runonce"),
                                     sizeof(TEXT("runonce"))
                                    );
    } else {
        //
        // We're OK so far.
        //
        Error = NO_ERROR;
    }

    //
    // GroupConv is always run.
    //
    if(RegSetValueEx(hKey,
                     TEXT("GrpConv"),
                     0,
                     REG_SZ,
                     TEXT("grpconv -o"),
                     sizeof(TEXT("grpconv -o"))) != ERROR_SUCCESS) {
        //
        // Since GrpConv is always run, consider it a more serious error than any error
        // encountered when setting 'runonce'.  (This decision is rather arbitrary, but
        // in practice, it should never make any difference.  Once we get the registry key
        // opened, there's no reason either of these calls to RegSetValueEx should fail.)
        //
        Error = (DWORD)l;
    }

    RegCloseKey(hKey);

    if(DoRunOnce) {
        WinExec("runonce -r", SW_SHOWNORMAL);
    }

    return Error;
}
