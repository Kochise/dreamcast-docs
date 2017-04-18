
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

/****************************************************************************\
* MODULE:       sidclean.c
*
*               NT never deletes SIDs, so the name of this sample is most
*                 accurately be intrepreted as "Clean up SID ownership and
*                 ACE's that relate to SIDs that still (and always will)
*                 exist, but for which the corresponding user account has been
*                 deleted"
*
*
* PURPOSE:      Demonstrate some of the Win32 security api(s), and provide a
*                 sample of how a utility could be written that recovers
*                 on-disk resources remaining allocated to deleted user
*                 accounts.  The on-disk resources recovered are 1) Files that
*                 are still owned by accounts that have been deleted are
*                 assigned ownership to the account logged on when this sample
*                 is run, and 2) ACE's for deleted accounts are edited
*                 (deleted) out of the ACLs of files to which the deleted
*                 accounts had been granted authorizations (eg., Read access)
*
*               It may be that running this sample as a utility has no
*                 practical value in many environments, as the number of files
*                 belonging to deleted user accounts will often be quite
*                 small, and the number of bytes recovered on disk by editing
*                 out ACEs for deleted accounts may well not be worth the time
*                 it takes to run this sample.  The time it takes to run this
*                 sample may be quite significant when processing an entire
*                 hard disk or partition
*
*               This sample is not a supported utility
*
*
* TO RUN:       You must log on using an account, such as Administrator, that
*                 has the priviledges to take file ownership and edit ACls
*
*               The ACL editing part of this sample can only be excercised for
*                 files on a partition that has ACLs NT processes:  NTFS
*
*               Typical test scenario:  Create a user account or two, log on
*                 as each of these accounts in turn, while logged on for each
*                 account, go to an NTFS partition, create a couple of files
*                 so the test accounts each own a few files, use the file
*                 manager to edit permissions for those files so that each
*                 test user has some authorities (e.g., Read) explicitly
*                 granted for those files.  Logon as Administrator, authorize
*                 each test user to a few Administrator-owned files.  Delete
*                 the test accounts.  Run the sample in the directories where
*                 you put the files the test accounts owned or were authorized
*                 to
*
*
* OVERALL APPROACH: The command line interface is kept inflexible to simplify
*                 it's parsing in this sample.  The user must pass in a switch
*                 argument, a directory spec, and a file search pattern
*
*               The sample positions the current directory (of the process the
*                 sample runs in) to the dir spec, and uses FindFirstFile and
*                 FindNextFile to walk through the directory specified looking
*                 for files that match the file pattern specified
*
*               The switch argument can cause subdirectories to be searched
*                 recursively
*
*               The switch argument lets the user choose only to take
*                 ownerships, only to edit ACLs, do both, or do neither, in
*                 which case the sample merely reports on what ownerships
*                 would have been taken, and what ACE's would have been
*                 deleted
*
*               As the directories are walked, each file that matches the
*                 file pattern is processed right then
*
*               Note that we process files in a directory, and we also process
*                 the directory itself that contains the files.  We process
*                 directories because they can also be owned by deleted
*                 accounts, or could have ACEs that will no longer be used
*
*               Note also that we process all directories that we check for
*                 files, regardless of the spelling of the directory name
*
*               Counters are kept of file ownerships taken, ACEs deleted and
*                 total files checked, to print a summary line at the end of
*                 the run
*
*               The sample considers it perfectly acceptable if 0 files match
*                 the file pattern for the entire run
*
*
* FUNCTIONS:  DoMatchingFilesInOneDir
*
*               Look in one dir or sub-dir for files that match the file
*                 pattern.  For each match call DoOneFileOrDir
*
*             DoAllDirsInOneDir
*
*               For all the sub-dirs in a dir, set the current directory to be
*                 that directory, check for files that match the file pattern,
*                 and if any match, call DoMatchingFilesInOneDir to process
*                 those.  Then reset the current directory
*
*             GetFullFileOrDirName
*
*               Get the full name of the file or dir for simplified processing
*                 (and for display on the console)
*
*             DoOneFileOrDir
*
*               Get the file's SD (Security Descriptor), and call
*                 TakeOwnershipIfAppropriate and/or DeleteACEsAsAppropriate as
*                 needed
*
*             TakeOwnershipIfAppropriate
*
*               Get the owning SID of the file from the file's SD that
*                 DoOneFileOrDir passed in, check that SID to see if the
*                 account is deleted.  If so, edit into the file's SD a new
*                 owning SID (the SID of the process running the sample).
*                 Then write the modified file SD to disk
*
*             DeleteACEsAsAppropriate
*
*               Get the DACL of the file from the file's SD that
*                 DoOneFileOrDir passed in.  Walk through the ACE list for
*                 that DACL, checking each ACE to see what SID the ACE refers
*                 to.  For the SID referred to, check to see if the account is
*                 deleted.  If so, delete that ACE from the DACL.  When all
*                 ACE's have been examined, write the new DACL into the file's
*                 SD.  Then write the modified file SD to disk
*
*             GetProcessSid
*
*               Retrieve into a global variable the SID of the user account
*                 logged on when this sample is run.  This is the SID used by
*                 TakeOwnershipIfAppropriate
*
*               NOTE:  This routine has the notable side-effect on the access
*                 token of the curent process of enabling two privileges:
*                 SeTakeOwnershipPrivilege, and SeSecurityPrivilege.
*                 SeTakeOwnershipPrivilege is needed to ensure we can take
*                 ownership in spite of any DACL on the file.
*                 SeSecurityPrivilege is needed to work with SACLs
*
*             CrackArgs
*
*               Process the command line, cracking (parsing/decoding) the
*                 switch argument into boolean global variables (see below).
*                 Call DisplayHelp if anything illegal is found in the command
*                 line, or if the user asked for help
*
*             DisplayHelp
*
*               Display help text on the console
*
*
* GLOBAL VARS:
*             BOOL  bTakeOwnership
*             BOOL  bEditACLs
*             BOOL  bRecurse
*             BOOL  bJustCount
*
*               These store the values the user specified on the command
*                 line's first argument (the switches argument).
*                 Respectively, they record whether we are to do the
*                 processing to Take Ownerships, Edit ACLs, whether we are to
*                 recurse into all subdirectories, and whether we are just
*                 counting up what would be processed (in which case we take
*                 no ownerships and edit no ACLs)
*
*             DWORD dwFilesChecked
*             DWORD dwFilesOwned
*             DWORD dwACEsDeleted
*
*               These count, respecively, the total files we checked, the
*                 number of files we took ownership of (or would have if we
*                 had not been told only to count), and the number of ACEs we
*                 deleted (or would have if we had not been told only to
*                 count).  Note that the total number of files checked does
*                 not include files in the directories we process that do not
*                 match the file pattern
*
*               Note, however, that we process directories regardless of
*                 whether they match the file pattern
*
*             UCHAR ucProcessSIDBuf
*             PSID  psidProcessOwnerSID
*
*               These store the SID of the account logged on as this sample
*                 runs, and a pointer to that SID
*
\****************************************************************************/


/****************************************************************************\
*  INCLUDES, DEFINES, TYPEDEFS
\****************************************************************************/
#define STRICT
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PERR(api) printf("%s: Error %d from %s on line %d\n",  \
    __FILE__, GetLastError(), api, __LINE__);
#define PMSG(msg) printf("%s line %d: %s\n",  \
    __FILE__, __LINE__, msg);

#define PrintAppStyleAPIError(ApiTxt,MsgTxt) {                     \
  DWORD dwLastError;                                               \
  dwLastError = GetLastError();                                    \
  switch (dwLastError)                                             \
  { case ERROR_FILE_NOT_FOUND :                                    \
      printf("\nFile not found (%s) line %d",MsgTxt,__LINE__);     \
      break;                                                       \
    case ERROR_INVALID_NAME   :                                    \
      printf("\nInvalid name (%s) line %d",MsgTxt,__LINE__);       \
      break;                                                       \
    case ERROR_PATH_NOT_FOUND :                                    \
      printf("\nError path not found (%s) line %d",MsgTxt,__LINE__); \
      break;                                                       \
    case ERROR_SHARING_VIOLATION :                                 \
      printf("\nSharing violation - shut down net and/or stop other sessions (%s) line %d",MsgTxt,__LINE__); \
      break;                                                       \
    case ERROR_ACCESS_DENIED  :                                    \
      printf("\nAccess denied (%s) line %d",MsgTxt,__LINE__);      \
      break;                                                       \
    default                   :                                    \
      printf("\n" #ApiTxt " - unexpected return code=%d (%s) line %d",dwLastError,MsgTxt,__LINE__); \
      break;                                                       \
  }                                                                \
  }

/****************************************************************************\
* GLOBAL VARIABLES
\****************************************************************************/

BOOL  bTakeOwnership  = FALSE;
BOOL  bEditACLs       = FALSE;
BOOL  bRecurse        = FALSE;
BOOL  bJustCount      = FALSE;

DWORD dwFilesChecked  = 0;
DWORD dwFilesOwned    = 0;
DWORD dwACEsDeleted   = 0;

PSID  psidProcessOwnerSID;


/****************************************************************************\
* FUNCTION PROTOTYPES
\****************************************************************************/

BOOL DoMatchingFilesInOneDir(HANDLE          hFound,
                             WIN32_FIND_DATA ffdFoundData);
BOOL DoAllDirsInOneDir(char *FilePattern);
BOOL GetFullFileOrDirName(LPTSTR lpszFileName);
BOOL DoOneFileOrDir(LPTSTR lpszFullName);
BOOL TakeOwnershipIfAppropriate(PSECURITY_DESCRIPTOR psdFileSD,
                                LPTSTR  lpszFullName);
BOOL DeleteACEsAsAppropriate   (PSECURITY_DESCRIPTOR psdFileSD,
                                LPTSTR  lpszFullName);
BOOL GetProcessSid(VOID);
BOOL CrackArgs(UINT argc, char *argv[]);
VOID DisplayHelp(VOID);

/****************************************************************************\
*
* FUNCTION: Main
*
\****************************************************************************/

UINT main(UINT argc, char *argv[])
{
  WIN32_FIND_DATA ffdFoundData;
  HANDLE          hFound;
  #define                   SZ_NAME_BUF MAX_PATH
  UCHAR           ucPathBuf[SZ_NAME_BUF];
  LPTSTR          lpszFullName = (LPTSTR)&ucPathBuf;

  /**************************************************************************\
  *
  * Store the process's SID in a global variable for later use (in taking
  *   ownership).
  *
  \**************************************************************************/

  if (!GetProcessSid())
  { PERR("Can't proceed without process SID - see earlier error messages");
    return(1);
  }

  if (!CrackArgs(argc,argv))
    return(1);

  /**************************************************************************\
  *
  * CrackArgs has set our global processing switches, and proven argv[2] and
  *   argv[3] are our non-blank dir-spec and file-pattern strings.  Now we
  *   must see that the file-spec is acceptable to the Win32 api's.  Argv[2]
  *   is the file-spec to pass to SetCurrentDirectory, and argv[3] is the
  *   file-pattern to pass to FindFirstFile
  *
  * First we have to expand the dir-spec in argv[2], because if we set the
  *   current directory to it before expansion,the expansion will have a
  *   different result if argv[2] is something like ..\..
  *
  \**************************************************************************/

  strcpy(lpszFullName,argv[2]);

  if (!GetFullFileOrDirName(lpszFullName))
  { PERR("Failed to expand to full name the 2nd argument (directory specification)");
    return(1);
  }

  /**************************************************************************\
  *
  * Now we pass the un-expanded argv[2] to SetCurrentDirectory for validity
  *   checking.  GetFullPathName (called by GetFullFileOrDirName) does not
  *   validity check
  *
  \**************************************************************************/

  if (!SetCurrentDirectory(argv[2]))
  { PrintAppStyleAPIError(SetCurrentDirectory,"2nd argument (directory specification)");
    return(1);
  }

  /**************************************************************************\
  *
  * We begin processing with the current directory, using the expanded form we
  *   got before.  We have to use the expanded form, because if we set to
  *   ..\.. and then try to process the string ..\.. as a dir name, instead of
  *   processing the dir two levels up from where we are we'll process the dir
  *   four levels up
  *
  \**************************************************************************/

  if (!DoOneFileOrDir(lpszFullName))
    return(1);

  /**************************************************************************\
  *
  * It's OK to get no hits.  The files-checked counter will show how many
  *   files we looked at, and it's OK to look at 0
  *
  * On the else branch, Argv[3] has been verified, and we have a good handle.
  *   We now pass to DoMatchingFilesInOneDir for processing the handle and
  *   found data we just got from FindFirstFile
  *
  \**************************************************************************/

  hFound = FindFirstFile(argv[3],
                         (LPWIN32_FIND_DATA)&ffdFoundData);
  if ((HANDLE)(-1) == hFound)
  { if (GetLastError() != ERROR_FILE_NOT_FOUND)
    { PrintAppStyleAPIError(FindFirstFile,"3rd argument");
      return(1);
    }
  }
  else if (!DoMatchingFilesInOneDir(hFound,ffdFoundData))
    return(1);

  /**************************************************************************\
  *
  * Pass the original file pattern for recursive calling to DoAllDirsInOneDir
  *
  \**************************************************************************/

  if (!DoAllDirsInOneDir(argv[3]))
    return(1);

  if (bJustCount)
    printf("\nChecked %d files, would have taken ownership of %d files, would have deleted %d ACEs\n",
           dwFilesChecked,dwFilesOwned,dwACEsDeleted);
  else
    printf("\nChecked %d files, took ownership of %d files, deleted %d ACEs\n",
           dwFilesChecked,dwFilesOwned,dwACEsDeleted);

  free(psidProcessOwnerSID);

  return(0);
}

/****************************************************************************\
*
* FUNCTION: DoMatchingFilesInOneDir
*
\****************************************************************************/

BOOL DoMatchingFilesInOneDir(HANDLE          hFound,
                             WIN32_FIND_DATA ffdFoundData)
{
  BOOL bDoneWithHandle = FALSE;

  /**************************************************************************\
  *
  * Process all files referred to by the handle, but not including
  *   directories, because directories are handled with separate calls to
  *   DoOneFileOrDir.  Such separate calls are made as we are setting the
  *   current directory to be the directory to be processed
  *
  \**************************************************************************/

  while (!bDoneWithHandle)
  {
    if (!(FILE_ATTRIBUTE_DIRECTORY & ffdFoundData.dwFileAttributes))
    {
      if (!DoOneFileOrDir(ffdFoundData.cFileName))
        return(FALSE);
    }

    if (!FindNextFile(hFound,
                      (LPWIN32_FIND_DATA)&ffdFoundData))
      if (GetLastError() == ERROR_NO_MORE_FILES)
        bDoneWithHandle = TRUE;
      else
      { PrintAppStyleAPIError(FindNextFile,"on FindNext");
        return(FALSE);
      }
  }
  return TRUE;
}

/****************************************************************************\
*
* FUNCTION: DoAllDirsInOneDir
*
\****************************************************************************/

BOOL DoAllDirsInOneDir(char *FilePattern)
{
  HANDLE          hFound;
  WIN32_FIND_DATA ffdFoundData;
  BOOL            bDoneWithHandle = FALSE;

  /**************************************************************************\
  *
  * If not recursing into dirs, simply return
  *
  \**************************************************************************/

  if (!bRecurse)
    return TRUE;

  /**************************************************************************\
  *
  * Since we are recursing, get a handle that points to entire directory, and
  *   walk the handle picking off only directories to recurse into
  *
  \**************************************************************************/

  hFound = FindFirstFile("*.*",
                         (LPWIN32_FIND_DATA)&ffdFoundData);
  if ((HANDLE)(-1) == hFound)
  { PrintAppStyleAPIError(FindFirstFile,"on dir *.* FindFirst");
    return(FALSE);
  }

  while (!bDoneWithHandle)
  {
    /************************************************************************\
    *
    * We only do dirs here, and we only do directories with textual names
    *   (i.e., not "." and not "..")
    *
    \************************************************************************/

    if (   (FILE_ATTRIBUTE_DIRECTORY & ffdFoundData.dwFileAttributes)
        && (0 != strcmp("." ,ffdFoundData.cFileName))
        && (0 != strcmp("..",ffdFoundData.cFileName)))
    {
      HANDLE          hFile2;
      WIN32_FIND_DATA ffdFound2;

      /**********************************************************************\
      *
      * We begin processing the new current directory by processing it itself,
      *   then setting the current dir to be the dir itself
      *
      \**********************************************************************/

      if (!DoOneFileOrDir(ffdFoundData.cFileName))
        return(FALSE);

      if (!SetCurrentDirectory(ffdFoundData.cFileName))
      { PrintAppStyleAPIError(SetCurrentDirectory,"recursive set");
        return(FALSE);
      }

      /**********************************************************************\
      *
      * It's OK to get no hits.  The files-checked counter will show how many
      *   files we looked at, and it's OK to look at 0
      *
      \**********************************************************************/

      hFile2 = FindFirstFile(FilePattern,
                             (LPWIN32_FIND_DATA)&ffdFound2);
      if ((HANDLE)(-1) == hFile2)
      { if (GetLastError() != ERROR_FILE_NOT_FOUND)
        { PrintAppStyleAPIError(FindFirstFile,"during recursion");
          return(FALSE);
        }
      }
      else if (!DoMatchingFilesInOneDir(hFile2,ffdFound2))
        return(FALSE);

      if (!DoAllDirsInOneDir(FilePattern))
        return(FALSE);

      if (!SetCurrentDirectory(".."))
      { PrintAppStyleAPIError(SetCurrentDirectory,"un-recursive set");
        return(FALSE);
      }
    }

    /************************************************************************\
    *
    * Get next recursion candidate (file or dir at this point, however at loop
    *   top files are screened out)
    *
    \************************************************************************/

    if (!FindNextFile(hFound,
                      (LPWIN32_FIND_DATA)&ffdFoundData))
      if (GetLastError() == ERROR_NO_MORE_FILES)
        bDoneWithHandle = TRUE;
      else
      { PrintAppStyleAPIError(FindNextFile,"on dir *.* FindNext");
        return(FALSE);
      }
  }
  return(TRUE);
}

/****************************************************************************\
*
* FUNCTION: GetFullFileOrDirName
*
\****************************************************************************/

BOOL GetFullFileOrDirName(LPTSTR lpszFileName)
{
  UCHAR   ucPathBuf[SZ_NAME_BUF];
  DWORD   dwSzReturned;
  LPTSTR  lpszLastNamePart;
  LPTSTR  lpszFullName;

  dwSzReturned = GetFullPathName
                   (lpszFileName,
                    (DWORD)SZ_NAME_BUF,
                    (LPTSTR)&ucPathBuf,
                    (LPTSTR *)&lpszLastNamePart);
  if (0 == dwSzReturned)
    switch (GetLastError())
    { case ERROR_INVALID_NAME   :
        printf("\nError invalid file full-name (on GetFullPathName)");
        return(FALSE);
      default                   :
        PERR("GetFullPathName - unexpected return code");
        return(FALSE);
    }

  if (dwSzReturned > SZ_NAME_BUF)
  { PERR("GetFullPathName - buffer too small");
    return(FALSE);
  }

  lpszFullName = CharLower((LPTSTR)&ucPathBuf);

  if (!lpszFullName)
  { PERR("CharLower failure");
    return(FALSE);
  }

  /**************************************************************************\
  *
  * Copy the expanded and upper-case-shifted name to the buffer pointed to by
  *   the input argument
  *
  \**************************************************************************/

  strcpy(lpszFileName,lpszFullName);
}

/****************************************************************************\
*
* FUNCTION: DoOneFileOrDir
*
\****************************************************************************/

BOOL DoOneFileOrDir(LPTSTR lpszFullName)
{
  #define                                 SZ_REL_SD_BUF 1000
  #define                                 SZ_ABS_SD_BUF  500
  #define                                 SZ_DACL_BUF    500
  #define                                 SZ_SACL_BUF    500
  #define                                 SZ_SID_OWN_BUF 500
  #define                                 SZ_SID_PG_BUF  500
  UCHAR                ucBuf             [SZ_REL_SD_BUF];
  UCHAR                ucBufAbs          [SZ_ABS_SD_BUF];
  UCHAR                ucBufDacl         [SZ_DACL_BUF];
  UCHAR                ucBufSacl         [SZ_SACL_BUF];
  UCHAR                ucBufCtrl         [sizeof(PSECURITY_DESCRIPTOR_CONTROL)];
  UCHAR                ucBufSidOwn       [SZ_SID_OWN_BUF];
  UCHAR                ucBufSidPG        [SZ_SID_PG_BUF];
  DWORD                dwSDLength       = SZ_REL_SD_BUF;
  DWORD                dwDACLLength     = SZ_DACL_BUF;
  DWORD                dwSACLLength     = SZ_SACL_BUF;
  DWORD                dwSidOwnLength   = SZ_SID_OWN_BUF;
  DWORD                dwSidPGLength    = SZ_SID_PG_BUF;
  DWORD                dwSDLengthNeeded;
  PSECURITY_DESCRIPTOR psdSrelFileSD    = (PSECURITY_DESCRIPTOR)&ucBuf;
  PSECURITY_DESCRIPTOR psdAbsFileSD     = (PSECURITY_DESCRIPTOR)&ucBufAbs;
  PSECURITY_DESCRIPTOR_CONTROL psdcCtrl = (PSECURITY_DESCRIPTOR_CONTROL)&ucBufCtrl;
  PACL                 paclDacl         = (PACL)&ucBufDacl;
  PACL                 paclSacl         = (PACL)&ucBufSacl;
  PSID                 psidSidOwn       = (PSID)&ucBufSidOwn;
  PSID                 psidSidPG        = (PSID)&ucBufSidPG;
  BOOL                 bDaclPresent;
  BOOL                 bDaclDefaulted;
  BOOL                 bSaclPresent;
  BOOL                 bSaclDefaulted;
  BOOL                 bOwnerDefaulted;
  BOOL                 bGroupDefaulted;
  BOOL                 bSDSelfRelative;
  DWORD                dwRevision;

  if (!GetFullFileOrDirName(lpszFullName))
    return(FALSE);

  /**************************************************************************\
  *
  * Now the input argument's name is accurate:  it is expanded and lower-case
  *
  \**************************************************************************/

  printf("\nChecking %s",lpszFullName);

  dwFilesChecked++;

  if (!GetFileSecurity
        (lpszFullName,
         (SECURITY_INFORMATION)( OWNER_SECURITY_INFORMATION
                               | GROUP_SECURITY_INFORMATION
                               | DACL_SECURITY_INFORMATION
                               | SACL_SECURITY_INFORMATION),
         psdSrelFileSD,
         dwSDLength,
         (LPDWORD)&dwSDLengthNeeded))
  { PERR("GetFileSecurity");
    return(FALSE);
  }

  /**************************************************************************\
  *
  * This validity check is here for demonstration pruposes.  It's not likely a
  *   real app would need to check the validity of this returned SD.  The
  *   validity check APIs are more intended to check validity after app code
  *   has manipulated the structure and is about to hand it back to the system
  *
  \**************************************************************************/

  if (!IsValidSecurityDescriptor(psdSrelFileSD))
  { PERR("IsValidSecurityDescriptor said bad SD");
    return(FALSE);
  }

  /**************************************************************************\
  *
  *  Build File SD in absolute format for potential later modification
  *
  *  First Initialize a new SD, which is by definition in absolute format
  *
  *  Then Set in the fields from the relative format SD we just fetched
  *
  \**************************************************************************/

  if (!InitializeSecurityDescriptor(psdAbsFileSD,
                 SECURITY_DESCRIPTOR_REVISION))
  { PERR("InitializeSecurityDescriptor");
    return FALSE;
  }

  /**************************************************************************\
  *
  * Get Control from relative format File SD
  *
  * This control info isn't much queried in the code that follows, as the
  *   Get/Set calls are more convienent in this case, but it does give us a
  *   change to verify that the SD is in relative format
  *
  \**************************************************************************/

  if (!GetSecurityDescriptorControl(psdSrelFileSD,
          psdcCtrl,
          &dwRevision))
  { PERR("GetSecurityDescriptorControl");
    return FALSE;
  }

  bSDSelfRelative = (SE_SELF_RELATIVE & *psdcCtrl);

  /**************************************************************************\
  *
  * Set DACL into absolute format File SD
  *
  * Note that it is possible that a NULL DACL has been explictly specified.
  *   If so the Get/Set call pair will correctly map that into the absolute
  *   format SD
  *
  * The next if statement isn't necessary, it simply shows the relationship
  *   between SE_DACL_PRESENT and SE_DACL_DEFAULTED, and lets you trace
  *   through with the debugger
  *
  \**************************************************************************/

  if (bDaclPresent = (SE_DACL_PRESENT   & *psdcCtrl))
  {                // SE_DACL_DEFAULTED ignored if SE_DACL_PRESENT not set
    bDaclDefaulted = (SE_DACL_DEFAULTED & *psdcCtrl);
  }
  else
  { // No DACL at all
  }

  if (!GetSecurityDescriptorDacl(psdSrelFileSD,
          &bDaclPresent,      // fDaclPresent flag
          &paclDacl,
          &bDaclDefaulted))   // is/is not a default DACL
  { PERR("GetSecurityDescriptorDacl");
    return FALSE;
  }
  if (!SetSecurityDescriptorDacl(psdAbsFileSD,
          bDaclPresent,       // fDaclPresent flag
          paclDacl,
          bDaclDefaulted))    // is/is not a default DACL
  { PERR("SetSecurityDescriptorDacl");
    return FALSE;
  }

  /**************************************************************************\
  *
  * Set SACL into absolute format File SD
  *
  * Note that it is possible that a NULL SACL has been explictly specified.
  *   If so the Get/Set call pair will correctly map that into the absolute
  *   format SD
  *
  * The next if statement isn't necessary, it simply shows the relationship
  *   between SE_SACL_PRESENT and SE_SACL_DEFAULTED, and lets you trace
  *   through with the debugger
  *
  \**************************************************************************/

  if (bSaclPresent = (SE_SACL_PRESENT   & *psdcCtrl))
  {                // SE_SACL_DEFAULTED ignored if SE_SACL_PRESENT not set
    bSaclDefaulted = (SE_SACL_DEFAULTED & *psdcCtrl);
  }
  else
  { // No SACL at all
  }

  if (!GetSecurityDescriptorSacl(psdSrelFileSD,
          &bSaclPresent,      // fSaclPresent flag
          &paclSacl,
          &bSaclDefaulted))   // is/is not a default SACL
  { PERR("GetSecurityDescriptorSacl");
    return FALSE;
  }
  if (!SetSecurityDescriptorSacl(psdAbsFileSD,
          bSaclPresent,       // fSaclPresent flag
          paclSacl,
          bSaclDefaulted))    // is/is not a default SACL
  { PERR("SetSecurityDescriptorSacl");
    return FALSE;
  }

  /**************************************************************************\
  *
  * Set Owner into absolute format File SD
  *
  * The next if statement isn't necessary, it simply let's you trace through
  *   with the debugger
  *
  \**************************************************************************/

  bOwnerDefaulted = (SE_OWNER_DEFAULTED & *psdcCtrl);

  if (!GetSecurityDescriptorOwner(psdSrelFileSD,
          &psidSidOwn,
          &bOwnerDefaulted))   // is/is not a default Owner
  { PERR("GetSecurityDescriptorOwner");
    return FALSE;
  }
  if (!SetSecurityDescriptorOwner(psdAbsFileSD,
          psidSidOwn,
          bOwnerDefaulted))    // is/is not a default Owner
  { PERR("SetSecurityDescriptorOwner");
    return FALSE;
  }

  /**************************************************************************\
  *
  * Set Group into absolute format File SD
  *
  * The next if statement isn't necessary, it simply let's you trace through
  *   with the debugger
  *
  \**************************************************************************/

  bGroupDefaulted = (SE_GROUP_DEFAULTED & *psdcCtrl);

  if (!GetSecurityDescriptorGroup(psdSrelFileSD,
          &psidSidOwn,
          &bGroupDefaulted))   // is/is not a default Group
  { PERR("GetSecurityDescriptorGroup");
    return FALSE;
  }
  if (!SetSecurityDescriptorGroup(psdAbsFileSD,
          psidSidOwn,
          bGroupDefaulted))    // is/is not a default Group
  { PERR("SetSecurityDescriptorGroup");
    return FALSE;
  }

  /**************************************************************************\
  *
  * This validity check is here for demonstration pruposes.  It's not likely a
  *   real app would need to check the validity of the SD after it was just
  *   built into absolute format.  The validity check APIs are more intended
  *   to check validity after app code has manipulated the structure and is
  *   about to hand it back to the system
  *
  * One thing to notice is that IsValidSecurityDescriptor will succeed on both
  *   self-relative and absolute format SDs.  However, some other api's, such
  *   as SetSecurityDescriptorOwner, require the SD to be in a certain format,
  *   and will give a return code of Invalid SD if the SD passed to the api is
  *   valid, but in the wrong format.  In other words, when an api such as
  *   SetSecurityDescriptorOwner gives the retun code Invalid SD, this doesn't
  *   mean the SD passed in was necessarily invalid.  It might have been in
  *   the wrong format
  *
  \**************************************************************************/

  if (!IsValidSecurityDescriptor(psdAbsFileSD))
  { PERR("IsValidSecurityDescriptor said bad SD");
    return(FALSE);
  }

  if (bTakeOwnership)
    if (!TakeOwnershipIfAppropriate(psdAbsFileSD,lpszFullName))
      return(FALSE);

  if (bEditACLs)
    if (!DeleteACEsAsAppropriate   (psdAbsFileSD,lpszFullName))
      return(FALSE);

  return(TRUE);
}

/****************************************************************************\
*
* FUNCTION: TakeOwnershipIfAppropriate
*
\****************************************************************************/

BOOL TakeOwnershipIfAppropriate(PSECURITY_DESCRIPTOR psdFileSD,
                                LPTSTR  lpszFullName)
{
  PSID psidFileOwnerSID;
  {
    BOOL  bOwnerDefaulted;

    if (!GetSecurityDescriptorOwner
           (psdFileSD,
            (PSID *)&psidFileOwnerSID,
            (LPBOOL)&bOwnerDefaulted))
    { PERR("GetSecurityDescriptorOwner");
      return(FALSE);
    }

    /************************************************************************\
    *
    * This validity check is here for demonstration pruposes.  It's not likely
    *   a real app would need to check the validity of this returned SID.  The
    *   validity check APIs are more intended to check validity after app code
    *   has manipulated the structure and is about to hand it back to the
    *   system
    *
    \************************************************************************/

    if (!IsValidSid(psidFileOwnerSID))
    { PERR("IsValidSid said bad SID!");
      return(FALSE);
    }
  }

  {
    DWORD        dwLastError   = NO_ERROR;
    #define                      SZ_ACCT_NAME_BUF 1000
    UCHAR        ucNameBuf      [SZ_ACCT_NAME_BUF];
    DWORD        dwNameLength  = SZ_ACCT_NAME_BUF;
    #define                      SZ_DMN_NAME_BUF  1000
    UCHAR        ucDomainNmBuf  [SZ_DMN_NAME_BUF ];
    DWORD        dwDNameLength = SZ_DMN_NAME_BUF ;
    SID_NAME_USE peAcctNameUse;

    if (!LookupAccountSid
           ((LPTSTR)"",             // Look on local machine
           psidFileOwnerSID,
           (LPTSTR)&ucNameBuf,
           (LPDWORD)&dwNameLength,
           (LPTSTR)&ucDomainNmBuf,
           (LPDWORD)&dwDNameLength,
           (PSID_NAME_USE)&peAcctNameUse))
    { dwLastError = GetLastError();
      if (ERROR_NONE_MAPPED != dwLastError)
      { PERR("LookupAccountSID");
        return(FALSE);
      }
    }

    /************************************************************************\
    *
    * If deleted account, take ownership.  This routine's caller checked the
    *   global switches that said we are in take ownership mode
    *
    * In some cases, the account lookup will fail with ERROR_NONE_MAPPED,
    *   meaning there is no deleted account mapped to the SID, in which case
    *   we also take ownership
    *
    *   We check that first to avoid referencing peAcctNameUse, which in that
    *     case is not set
    *
    \************************************************************************/

    if (  (ERROR_NONE_MAPPED == dwLastError)
       || (SidTypeDeletedAccount == peAcctNameUse))
    {
      dwFilesOwned++;

      if (bJustCount)
      { printf(" - would have taken ownership");
        return(TRUE);
      }
      else
      {
        /********************************************************************\
        *
        * Modify the SD in virtual memory.  No check on the new owning SID
        *   here, because we validity checked it when we fetched it in
        *   GetProcessSid
        *
        \********************************************************************/

        if (!SetSecurityDescriptorOwner
               (psdFileSD,
                psidProcessOwnerSID,
                FALSE))               // New owner explicitly specified
        { PERR("SetSecurityDescriptorOwner");
          return(FALSE);
        }

        /********************************************************************\
        *
        *  This validity check is something a real app might actually like to
        *    do.  We manupulated the SD, so before we write it back out to the
        *    file system, a check is worth considering.
        *
        \********************************************************************/

        if (!IsValidSecurityDescriptor(psdFileSD))
        { PERR("IsValidSecurityDescriptor said bad SD");
          return(FALSE);
        }

        /********************************************************************\
        *
        * Modify the SD on the hard disk
        *
        \********************************************************************/

        if (!SetFileSecurity
               (lpszFullName,
                (SECURITY_INFORMATION)OWNER_SECURITY_INFORMATION,
                psdFileSD))
        { PERR("SetFileSecurity");
          return(FALSE);
        }

        printf(" - took ownership");
      }
    }
  }

  return(TRUE);

}

/****************************************************************************\
*
* FUNCTION: DeleteACEsAsAppropriate
*
\****************************************************************************/

BOOL DeleteACEsAsAppropriate(PSECURITY_DESCRIPTOR psdFileSD,
                             LPTSTR  lpszFullName)
{
  PACL                 paclFile;
  BOOL                 bHasACL;
  BOOL                 bOwnerDefaulted;
  DWORD                dwAcl_i;
  DWORD                dwACEsDeletedBeforeNow;

  ACL_SIZE_INFORMATION                      asiAclSize;
  DWORD                dwBufLength = sizeof(asiAclSize);
  ACCESS_ALLOWED_ACE   *paaAllowedAce;

  if (!GetSecurityDescriptorDacl(psdFileSD,
                                 (LPBOOL)&bHasACL,
                                 (PACL *)&paclFile,
                                 (LPBOOL)&bOwnerDefaulted))
  { PERR("GetSecurityDescriptorDacl");
    return(FALSE);
  }

  if (!bHasACL)  // No ACL to process, so OK, return
    return(TRUE);

  /**************************************************************************\
  *
  * This validity check is here for demonstration pruposes.  It's not likely a
  *   real app would need to check the validity of this returned ACL.  The
  *   validity check APIs are more intended to check validity after app code
  *   has manipulated the structure and is about to hand it back to the system
  *
  \**************************************************************************/

  if (!IsValidAcl(paclFile))
  { PERR("IsValidAcl said bad ACL!");
    return(FALSE);
  }

  if (!GetAclInformation(paclFile,
                         (LPVOID)&asiAclSize,
                         (DWORD)dwBufLength,
                         (ACL_INFORMATION_CLASS)AclSizeInformation))
  { PERR("GetAclInformation");
    return(FALSE);
  }

  dwACEsDeletedBeforeNow = dwACEsDeleted;

  /**************************************************************************\
  *
  * We loop through in reverse order, because that's simpler, given that we
  *   potentially delete ACEs as we loop through.  If started at 0 and went
  *   up, if we deleted the 0th ACE, then the 1th ACE would become the 0th,
  *   and we'd have to check the 0th ACE again
  *
  \**************************************************************************/

  for (dwAcl_i = asiAclSize.AceCount-1;  ((int)dwAcl_i) >= 0;  dwAcl_i--)
  {
    /************************************************************************\
    *
    * It doesn't matter for this sample that we don't yet know the ACE type,
    *   because they all start with the header field and that's what we need
    *
    \************************************************************************/

    if (!GetAce(paclFile,
                dwAcl_i,
                (LPVOID *)&paaAllowedAce))
    { PERR("GetAce");
      return(FALSE);
    }

    /************************************************************************\
    *
    * There are only four Ace Types pre-defined, so this next check is
    *   redundant in a real app, but useful as a sanity check and a
    *   demonstration in a sample
    *
    \************************************************************************/

    if (!( (paaAllowedAce->Header.AceType == ACCESS_ALLOWED_ACE_TYPE)
         ||(paaAllowedAce->Header.AceType == ACCESS_DENIED_ACE_TYPE )
         ||(paaAllowedAce->Header.AceType == SYSTEM_AUDIT_ACE_TYPE  )
         ||(paaAllowedAce->Header.AceType == SYSTEM_ALARM_ACE_TYPE  )))
    { PERR("Invalid AceType");
      return(FALSE);
    }

    { // Find SID of ACE, check if acct deleted

      UCHAR        ucNameBuf      [SZ_ACCT_NAME_BUF];
      DWORD        dwNameLength  = SZ_ACCT_NAME_BUF;
      UCHAR        ucDomainNmBuf  [SZ_DMN_NAME_BUF];
      DWORD        dwDNameLength = SZ_DMN_NAME_BUF;
      SID_NAME_USE peAcctNameUse;
      DWORD        dwLastError   = NO_ERROR;

      /**********************************************************************\
      *
      * This validity check is here for demonstration pruposes.  It's not
      *   likely a real app would need to check the validity of the SID
      *   contained in the returned ACL.  The validity check APIs are more
      *   intended to check validity after app code has manipulated the
      *   structure and is about to hand it back to the system
      *
      \**********************************************************************/

      if (!IsValidSid((PSID)&(paaAllowedAce->SidStart)))
      { PERR("IsValidSid said bad SID!");
        return(FALSE);
      }

      if (!LookupAccountSid
             ((LPTSTR)"",         // Look on local machine
             (PSID)&(paaAllowedAce->SidStart),
             (LPTSTR)&ucNameBuf,
             (LPDWORD)&dwNameLength,
             (LPTSTR)&ucDomainNmBuf,
             (LPDWORD)&dwDNameLength,
             (PSID_NAME_USE)&peAcctNameUse))
      { dwLastError = GetLastError();
        if (ERROR_NONE_MAPPED != dwLastError)
        { PERR("LookupAccountSID");
          return(FALSE);
        }
      }

      if (  (ERROR_NONE_MAPPED == dwLastError)
         || (SidTypeDeletedAccount == peAcctNameUse))
      {
        dwACEsDeleted++;

        if (bJustCount)
        { printf(" - would have edited ACL");
          return(TRUE);
        }

        if (!DeleteAce(paclFile,dwAcl_i))
        { PERR("DeleteAce");
          return(FALSE);
        }
      }
    }
  }

  if (dwACEsDeletedBeforeNow < dwACEsDeleted)
  {
    /************************************************************************\
    *
    * This validity check is something a real app might actually like to do.
    *   We manupulated the ACL, so before we write it back into an SD, a check
    *   is worth considering
    *
    \************************************************************************/

    if (!IsValidAcl(paclFile))
    { PERR("IsValidAcl said bad ACL!");
      return(FALSE);
    }

    /************************************************************************\
    *
    * Modify the SD in virtual memory
    *
    \************************************************************************/

    if (!SetSecurityDescriptorDacl
           (psdFileSD,
            TRUE,                 // Yes, set the DACL
            paclFile,
            FALSE))               // New DACL explicitly specified
    { PERR("SetSecurityDescriptorDacl");
      return(FALSE);
    }

    /************************************************************************\
    *
    * This validity check is something a real app might actually like to do.
    *   We manupulated the SD, so before we write it back out to the file
    *   system, a check is worth considering
    *
    \************************************************************************/

    if (!IsValidSecurityDescriptor(psdFileSD))
    { PERR("IsValidSecurityDescriptor said bad SD");
      return(FALSE);
    }

    /************************************************************************\
    *
    * Modify the SD on the hard disk
    *
    \************************************************************************/

    if (!SetFileSecurity
           (lpszFullName,
            (SECURITY_INFORMATION)DACL_SECURITY_INFORMATION,
            psdFileSD))
    { PERR("SetFileSecurity");
      return(FALSE);
    }

    printf(" - edited ACL");
  }

  return(TRUE);

}

/****************************************************************************\
*
* FUNCTION: GetProcessSid
*
\****************************************************************************/

BOOL GetProcessSid(VOID)
{
  HANDLE               hProcess;
  PSECURITY_DESCRIPTOR psdProcessSD;
  PSID                 psidProcessOwnerSIDTemp;

  UCHAR                ucBuf       [SZ_REL_SD_BUF];
  DWORD                dwSDLength = SZ_REL_SD_BUF;
  DWORD                dwSDLengthNeeded;
  BOOL                 bOwnerDefaulted;

  hProcess = GetCurrentProcess();

  if (!hProcess)
  { PERR("GetCurrentProcess");
    return(FALSE);
  }

  psdProcessSD = (PSECURITY_DESCRIPTOR)ucBuf;

  if (!GetKernelObjectSecurity
         (hProcess,
          (SECURITY_INFORMATION)(OWNER_SECURITY_INFORMATION),
          psdProcessSD,
          dwSDLength,
          (LPDWORD)&dwSDLengthNeeded))
  { PERR("GetKernelObjectSecurity on current process handle");
    return(FALSE);
  }

  /**************************************************************************\
  *
  * This validity check is here for demonstration purposes.  It's not likely a
  *   real app would need to check the validity of this returned SD.  The
  *   validity check APIs are more intended to check validity after app code
  *   has manipulated the structure and is about to hand it back to the system
  *
  \**************************************************************************/

  if (!IsValidSecurityDescriptor(psdProcessSD))
  { PERR("IsValidSecurityDescriptor said bad SD");
    return(FALSE);
  }

  if (!GetSecurityDescriptorOwner
         (psdProcessSD,
          (PSID *)&psidProcessOwnerSIDTemp,
          (LPBOOL)&bOwnerDefaulted))
  { PERR("GetSecurityDescriptorOwner of current process");
    return(FALSE);
  }

  /**************************************************************************\
  *
  * This validity check is here for demonstration pruposes.  It's not likely a
  *   real app would need to check the validity of this returned SID.  The
  *   validity check APIs are more intended to check validity after app code
  *   has manipulated the structure and is about to hand it back to the system
  *
  \**************************************************************************/

  if (!IsValidSid(psidProcessOwnerSIDTemp))
  { PERR("IsValidSid said bad process SID!");
    return(FALSE);
  }

  /**************************************************************************\
  *
  * On the other hand, we are about to call GetLengthSid on the returned SID,
  *   and calling GetLengthSid with an invalid SID is a bad idea, since then
  *   GetLengthSid's result is undefined, and an undefined result is hard to
  *   handle cleanly.  So, even in a real app, the above check on SID validity
  *   is a good idea to ensure the result GetLengthSid returns is valid
  *
  * It should be clear that the reason why the CopySid below is needed is that
  *   in the current routine the SID of the current process is on the stack
  *   (in the SD structure), so we have to copy the SID to static storage
  *   before the current routine returns
  *
  \**************************************************************************/

  { DWORD dwSIDLengthNeeded;

    dwSIDLengthNeeded = GetLengthSid(psidProcessOwnerSIDTemp);

    psidProcessOwnerSID = malloc(dwSIDLengthNeeded);

    if (NULL == psidProcessOwnerSID)
      PERR("GetProcessSid - ran out of heap space");

    if (!CopySid(dwSIDLengthNeeded,
                 psidProcessOwnerSID,
                 psidProcessOwnerSIDTemp))
    { PERR("CopySid");
      return(FALSE);
    }
  }


  /**************************************************************************\
  *
  * This validity check is here for demonstration pruposes only (see above).
  *
  \**************************************************************************/

  if (!IsValidSid(psidProcessOwnerSID))
  { PERR("IsValidSid said bad process SID!");
    return(FALSE);
  }


  /**************************************************************************\
  *
  * Now ensure that two privileges are enabled in the access token of the
  *   current process
  *
  \**************************************************************************/

  { HANDLE           hAccessToken;
    LUID             luidPrivilegeLUID;
    TOKEN_PRIVILEGES tpTokenPrivilege;

    if (!OpenProcessToken(hProcess,
                          TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
                          &hAccessToken))
    { PERR("OpenProcessToken");
      return(FALSE);
    }

    /************************************************************************\
    *
    * Get LUID of SeTakeOwnershipPrivilege privilege
    *
    \************************************************************************/

    if (!LookupPrivilegeValue(NULL,
                              "SeTakeOwnershipPrivilege",
                              &luidPrivilegeLUID))
    { PERR("LookupPrivilegeValue");
      printf("\nThe above error means you need to use User Manager (menu item");
      printf("\n  Policies\\UserRights) to turn on the 'Take ownership of...' ");
      printf("\n  privilege, log off, log back on");
      return(FALSE);
    }

    /************************************************************************\
    *
    * Enable the SeTakeOwnershipPrivilege privilege using the LUID just
    *   obtained
    *
    \************************************************************************/

    tpTokenPrivilege.PrivilegeCount = 1;
    tpTokenPrivilege.Privileges[0].Luid = luidPrivilegeLUID;
    tpTokenPrivilege.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges (hAccessToken,
                           FALSE,  // Do not disable all
                           &tpTokenPrivilege,
                           sizeof(TOKEN_PRIVILEGES),
                           NULL,   // Ignore previous info
                           NULL);  // Ignore previous info

    if ( GetLastError() != NO_ERROR )
    { PERR("AdjustTokenPrivileges");
      return(FALSE);
    }

    /************************************************************************\
    *
    * Get LUID of SeSecurityPrivilege privilege
    *
    \************************************************************************/

    if (!LookupPrivilegeValue(NULL,
                              "SeSecurityPrivilege",
                              &luidPrivilegeLUID))
    { PERR("LookupPrivilegeValue");
      printf("\nThe above error means you need to log on as an Administrator");
      return(FALSE);
    }

    /************************************************************************\
    *
    * Enable the SeSecurityPrivilege privilege using the LUID just
    *   obtained
    *
    \************************************************************************/

    tpTokenPrivilege.PrivilegeCount = 1;
    tpTokenPrivilege.Privileges[0].Luid = luidPrivilegeLUID;
    tpTokenPrivilege.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges (hAccessToken,
                           FALSE,  // Do not disable all
                           &tpTokenPrivilege,
                           sizeof(TOKEN_PRIVILEGES),
                           NULL,   // Ignore previous info
                           NULL);  // Ignore previous info

    if ( GetLastError() != NO_ERROR )
    { PERR("AdjustTokenPrivileges");
      return(FALSE);
    }

  }

  return(TRUE);

}

/****************************************************************************\
*
* FUNCTION: CrackArgs
*
\****************************************************************************/

BOOL CrackArgs(UINT argc, char *argv[])
{
  char *p;

  /**************************************************************************\
  *
  * There must be three arguments
  *
  \**************************************************************************/

  if (argc != 4)
  { DisplayHelp();
    return(FALSE);
  }

  p=argv[1];

  /**************************************************************************\
  *
  * The switch argument must be 2-5 chars long
  *
  \**************************************************************************/

  if ((strlen(p) < 2) || (strlen(p) > 5))
  { DisplayHelp();
    return(FALSE);
  }

  /**************************************************************************\
  *
  * The first char in the switch argument must be /
  *
  \**************************************************************************/

  if ('/' != *p)
  { DisplayHelp();
    return(FALSE);
  }

  /**************************************************************************\
  *
  * Chars 2-5 of the switch argument must be O or A or R or C
  *
  \**************************************************************************/

  for (p=p+1; *p; p++)
    switch (*p)
    { case 'o':
      case 'O':
        bTakeOwnership = TRUE;
        break;
      case 'a':
      case 'A':
        bEditACLs      = TRUE;
        break;
      case 'r':
      case 'R':
        bRecurse       = TRUE;
        break;
      case 'c':
      case 'C':
        bJustCount     = TRUE;
        break;
      default :
        DisplayHelp();
        return(FALSE);
    }

  /**************************************************************************\
  *
  * Have to say one of O or A
  *
  \**************************************************************************/

  if (!(bTakeOwnership || bEditACLs))
  { DisplayHelp();
    return(FALSE);
  }

  return(TRUE);
}

/****************************************************************************\
*
* FUNCTION: DisplayHelp
*
\****************************************************************************/

VOID DisplayHelp(VOID)
{
  printf("\nTo run type SIDCLEAN and 3 parameters.  Syntax:");
  printf("\n  SIDCLEAN /roah dirspec filepattern");
  printf("\n           /r    Recursively process subdirectories");
  printf("\n           /o    For any files matching filepattern: Take ownership if");
  printf("\n                   file currently owned by any deleted SID");
  printf("\n           /a    For any files matching filepattern: Edit ACL, deleting");
  printf("\n                   ACEs associated with any deleted SID");
  printf("\n           /c    Overrides /o and /a, causes counts of /a or /o actions that");
  printf("\n                   would take place if /c not used.  Counts always displayed");
  printf("\n           /h    Override other switch values, just display this message\n");
  printf("\n                 . and .. syntax allowed in dirspec");
  printf("\n                 * and ? wildcards allowed in filepattern");
  printf("\n                 Switch letters can be in any order, upper or lower case");
  printf("\nExamples:");
  printf("\n  SIDCLEAN /o  .  *.*  Take ownership of all files (but not subdirs) in ");
  printf("\n                         current dir that are owned by any deleted SID");
  printf("\n  SIDCLEAN /a  .  *.*  For any file in current dir (but not subdirs), delete");
  printf("\n                         any ACL info that is associated with any deleted SID");
  printf("\n  SIDCLEAN /ro .  *.*  Same as first  example, but also recursively process");
  printf("\n                         subdirectories");
  printf("\n  SIDCLEAN /ar .  *.*  Same as second example, but also recursively process");
  printf("\n                         subdirectories");
  printf("\n  SIDCLEAN /O  \\  *.*  Same as first  example, but process files in root");
  printf("\n                         of current drive");
  printf("\n  SIDCLEAN /oC .. *.*  Same as first  example, but looks at files in dir");
  printf("\n                         containing current dir, processes nothing, just counts");
  printf("\n  SIDCLEAN /A d:\\ *.*  Same as second example, but process files in root");
  printf("\n                         of D: drive");
  printf("\n  SIDCLEAN             Displays this message");
  printf("\n  SIDCLEAN /h          Displays this message (so do ? -? /? -h -H /H)\n");
  printf("\nThis utility must be run while logged on as Administrator\n");

  return;
}
