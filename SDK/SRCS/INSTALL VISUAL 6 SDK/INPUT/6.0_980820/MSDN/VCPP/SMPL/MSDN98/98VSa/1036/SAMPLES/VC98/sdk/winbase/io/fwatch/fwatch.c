/**********************************************************************
   File name: fwatch.c

      Main source file for sample demonstrating use of file change
      notification APIs.

   Functions:

      CheckChangedFile()      - Gets and displays change information
      HandleDirectoryChange() - Watch function
      WatchDirectories()      - Starts the watch
      main()                  - Program main


   Written by Microsoft Product Support Services, Windows Developer Support.
   Copyright 1996-1997 Microsoft Corporation. All rights reserved.
**********************************************************************/
#define UNICODE

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define MAX_DIRS    10
#define MAX_FILES   255
#define MAX_BUFFER  4096

// this is the all purpose structure that contains  
// the interesting directory information and provides
// the input buffer that is filled with file change data
typedef struct _DIRECTORY_INFO {
HANDLE      hDir;
TCHAR       lpszDirName[MAX_PATH];
CHAR        lpBuffer[MAX_BUFFER];
DWORD       dwBufLength;
OVERLAPPED  Overlapped;
}DIRECTORY_INFO, *PDIRECTORY_INFO, *LPDIRECTORY_INFO;

DIRECTORY_INFO  DirInfo[MAX_DIRS];        // Buffer for all of the directories
TCHAR           FileList[MAX_FILES*MAX_PATH];   // Buffer for all of the files
DWORD           numDirs;


/**********************************************************************
   CheckChangedFile()

   Purpose:
      This function prints out information when one of the files we
      are watching is changed.

   Parameters:

      LPDIRECTORY_INFO lpdi - Information about the watched directory
      PFILE_NOTIFY_INFORMATION lpfni - Information about modified file


   Return Value:
      None

   Comments:

********************************************************************/
void WINAPI CheckChangedFile( LPDIRECTORY_INFO lpdi,
                              PFILE_NOTIFY_INFORMATION lpfni)
{
    TCHAR      szFullPathName[MAX_PATH];
    TCHAR      *p;
    HANDLE     hFile;
    FILETIME   LocalFileTime;
    SYSTEMTIME SystemTime;
    BY_HANDLE_FILE_INFORMATION FileInfo;

    p = FileList;

    while(*p && lstrcmpi(p,lpfni->FileName))
        p+=(lstrlen(p)+1);

    if(*p)
    {
        lstrcpy( szFullPathName, lpdi->lpszDirName );
        lstrcat( szFullPathName, L"\\" );
        lstrcat( szFullPathName, lpfni->FileName );

        // we assume that the file was changed, since 
        // that is the only thing we look for in this sample
        wprintf( L"%s changed,", szFullPathName );

        hFile=CreateFile( szFullPathName,
                          GENERIC_READ,
                          FILE_SHARE_READ,
                          NULL,
                          OPEN_EXISTING,
                          FILE_FLAG_SEQUENTIAL_SCAN,
                          0);

        GetFileInformationByHandle( hFile, &FileInfo );

        FileTimeToLocalFileTime( &(FileInfo.ftLastWriteTime), &LocalFileTime );

        FileTimeToSystemTime( &LocalFileTime, &SystemTime );

        wprintf( L" Size = %d bytes,", FileInfo.nFileSizeLow );
        wprintf( L" Last Access = %02d/%02d/%02d %02d:%02d:%02d",
                 SystemTime.wMonth,
                 SystemTime.wDay,
                 SystemTime.wYear,
                 SystemTime.wHour,
                 SystemTime.wMinute,
                 SystemTime.wSecond );

        CloseHandle( hFile );

        wprintf( L"\n" );
    }
}


/**********************************************************************
   HandleDirectoryChanges()

   Purpose:
      This function receives notification of directory changes and
      calls CheckChangedFile() to display the actual changes. After
      notification and processing, this function calls
      ReadDirectoryChangesW to reestablish the watch.

   Parameters:

      HANDLE hCompPort - Handle for completion port


   Return Value:
      None

   Comments:

********************************************************************/
void WINAPI HandleDirectoryChange( DWORD dwCompletionPort )
{
    DWORD numBytes;
    DWORD cbOffset;
    LPDIRECTORY_INFO di;
    LPOVERLAPPED lpOverlapped;
    PFILE_NOTIFY_INFORMATION fni;

    do
    {
        // Retrieve the directory info for this directory
        // through the completion key
        GetQueuedCompletionStatus( (HANDLE) dwCompletionPort,
                                   &numBytes,
                                   (LPDWORD) &di,
                                   &lpOverlapped,
                                   INFINITE);

        if ( di )
        {

            fni = (PFILE_NOTIFY_INFORMATION)di->lpBuffer;

            do
            {
                cbOffset = fni->NextEntryOffset;

                if( fni->Action == FILE_ACTION_MODIFIED )
                    CheckChangedFile( di, fni );

                fni = (PFILE_NOTIFY_INFORMATION)((LPBYTE) fni + cbOffset);

            } while( cbOffset );

            // Reissue the watch command
            ReadDirectoryChangesW( di->hDir,di->lpBuffer,
                                   MAX_BUFFER,
                                   TRUE,
                                   FILE_NOTIFY_CHANGE_LAST_WRITE,
                                   &di->dwBufLength,
                                   &di->Overlapped,
                                   NULL);
        }

    } while( di );


}


/**********************************************************************
   WatchDirectories()

   Purpose:
      This function implements the ReadDirectoryChangesW API for
      indicated directories. For each directory watched, a thread
      is created which waits for changes to the directory. This
      function waits for the user to input 'q', then cleans up and
      quits.

   Parameters:

      HANDLE hCompPort - Handle for completion port


   Return Value:
      None

********************************************************************/
void WINAPI WatchDirectories( HANDLE hCompPort )
{
    DWORD   i;
    DWORD   tid;
    HANDLE  hThread;


    // Start watching each of the directories of interest

    for (i=0;i<numDirs;i++)
    {
        ReadDirectoryChangesW( DirInfo[i].hDir,
                               DirInfo[i].lpBuffer,
                               MAX_BUFFER,
                               TRUE,
                               FILE_NOTIFY_CHANGE_LAST_WRITE,
                               &DirInfo[i].dwBufLength,&DirInfo[i].Overlapped,
                               NULL);
    }

    // Create a thread to sit on the directory changes

    hThread = CreateThread( NULL,
                            0,
                            (LPTHREAD_START_ROUTINE) HandleDirectoryChange,
                            hCompPort,
                            0,
                            &tid);

    // Just loop and wait for the user to quit

    while (getch() != 'q');

    // The user has quit - clean up

    PostQueuedCompletionStatus( hCompPort, 0, 0, NULL );

    // Wait for the Directory thread to finish before exiting

    WaitForSingleObject( hThread, INFINITE );

    CloseHandle( hThread );
}


/**********************************************************************
   main()

   Purpose:
      Main entry-point for fwatch sample. This function reads an .ini
      file (fwatch.ini) to determine which directories and files to
          watch. For each directory watched some information is gathered
      and stored.

   Return Value:  (see errors.h for description)
      None

   Comments:

********************************************************************/
void main(int argc, char *argv[])
{

    TCHAR   *p,*q;                          // Temporary String Pointer
    HANDLE  hCompPort=NULL;                 // Handle To a Completion Port
    DWORD   i;                              // You always need an I.
    TCHAR   DirList[MAX_DIRS*MAX_PATH];     // Buffer for all of the directories
    TCHAR   IniFile[MAX_PATH];
    TCHAR   FilePath[MAX_PATH];
    HANDLE  hFile;

    GetCurrentDirectory( MAX_PATH, IniFile );

    lstrcat( IniFile, L"\\fwatch.ini" );

    GetPrivateProfileString( L"Directories",
                             NULL,
                             NULL,
                             DirList,
                             MAX_DIRS*MAX_PATH,
                             IniFile );

    GetPrivateProfileString( L"Files",
                             NULL,
                             NULL,
                             FileList,
                             MAX_FILES*MAX_PATH,
                             IniFile );

    wprintf( L"Watching these directories:\n" );

    // First, walk through the raw list and count items, creating
    // an array of handles for each directory
    for (p=DirList;*p!='\0';numDirs++,p+=(lstrlen(p)+1))
    {


        if( CreateDirectory( p, NULL ) )
            wprintf( L"Directory %s created\n", p );
        else
            wprintf( L"Directory %s exists\n", p );

        // Get a handle to the directory
        DirInfo[numDirs].hDir = CreateFile( p,
                                            FILE_LIST_DIRECTORY,
                                            FILE_SHARE_READ |
                                            FILE_SHARE_WRITE |
                                            FILE_SHARE_DELETE,
                                            NULL,
                                            OPEN_EXISTING,
                                            FILE_FLAG_BACKUP_SEMANTICS |
                                            FILE_FLAG_OVERLAPPED,
                                            NULL);

        if( DirInfo[numDirs].hDir == INVALID_HANDLE_VALUE )
        {
            wprintf( L"Unable to open directory %s. GLE=%d. Terminating...\n",
                     p, GetLastError() );
            exit( 0 );
        }

        for (q=FileList;*q!='\0';q+=(lstrlen(q)+1))
        {
            lstrcpy( FilePath, p );
            lstrcat( FilePath, L"\\" );
            lstrcat( FilePath, q );

            if( hFile = CreateFile( FilePath,
                                    GENERIC_WRITE,
                                    FILE_SHARE_READ |
                                    FILE_SHARE_WRITE |
                                    FILE_SHARE_DELETE,
                                    NULL,
                                    CREATE_ALWAYS,
                                    FILE_ATTRIBUTE_NORMAL,
                                    NULL) )
            {
                wprintf( L"  File %s created\n", FilePath );
                CloseHandle( hFile );
            }
            else
                wprintf( L"  File %s could not be created\n", FilePath );

        }

        lstrcpy( DirInfo[numDirs].lpszDirName, p );

        // Set up a key(directory info) for each directory
        hCompPort=CreateIoCompletionPort( DirInfo[numDirs].hDir,
                                          hCompPort,
                                          (DWORD) &DirInfo[numDirs],
                                          0);

    }

    wprintf( L"\n\nPress <q> to exit\n" );

    // Start watching
    WatchDirectories( hCompPort );

    for(i=0;i<numDirs;i++)
        CloseHandle( DirInfo[i].hDir );

    CloseHandle( hCompPort );

}


