//
// This program installs the PROCSRV.exe into the Service Control Manager.  It also
// adds a service entry to the SQL Service Manager.
// The service name "ProcSrv" will be added to the registry under the tree
// "\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\SQLServer\"
//
// Copyright 1994, Microsoft.
//

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROCSRV             "ProcSrv"
#define PROCSRV_KEY_PATH    "SOFTWARE\\Microsoft\\MSSQLServer\\ProcSrv\\"
#define SQL_SM_KEY          "SOFTWARE\\Microsoft\\MSSQLServer\\SQL Service Manager\\"

#define NAMED_PIPE_DLL      "SSNMPN60"
#define NAMED_PIPE_ADDRESS  "\\\\.\\pipe\\sql\\query"
#define TCP_IP_DLL          "SSMSSO60"
#define TCP_ADDRESS         "1433"

void AddToRegistry();
void RemoveFromRegistry();
BOOL DuplicateEntry();
void RefreshStoplight();

void main( int argc, char ** argv )
{
    if( argc != 2 )
        goto Usage;

    if( !stricmp("add", argv[1]) )
                AddToRegistry();
        else if( !stricmp("remove", argv[1]) )
                RemoveFromRegistry();
    else
        goto Usage;

    RefreshStoplight();
    return;

Usage:
        printf( "Usage: service {add|remove}\n"
                    "  where \"add\" adds ProcSrv and \"remove\" removes it\n" );
}


// **************************************************************************
//
//  FUNCTION: AddToRegistry()
//
//  PURPOSE:  Add ProcSrv to Registry and Service Control Manager
//
// **************************************************************************

void AddToRegistry()
{
    int    i;
    HKEY   hKey;
    HKEY   hKeySM;
    DWORD  dwDisposition;
    DWORD  dwSize = 0;
    DWORD  dwSizeSM;
    DWORD  dwType;
    DWORD  dwPathLength;
    char   szPath[1024];
    char   szSMvalues[1024];
    char   szSaveListenOn[1024];
    char * szSaveListenOnPos = szSaveListenOn;

    SC_HANDLE hSCM;     // Handle to opened Service Control Manager
    SC_LOCK   LockSCM;  // Lock of Service Control Manager
    SC_HANDLE hSrvc;    // Handle to service

    // Check for existance of "ProcSrv" in registry
    //
    if( DuplicateEntry() )
    {
        printf( "Duplicate entry 'ProcSrv' found in Registry, remove 'ProcSrv' from Registry\n" );
        return;
    }

    // ======== Update SQL Service Manager info ===========
    //
    if( RegCreateKeyEx(HKEY_LOCAL_MACHINE,
                       SQL_SM_KEY,
                       0,
                       NULL,
                       REG_OPTION_NON_VOLATILE,
                       KEY_ALL_ACCESS,
                       NULL,
                       &hKeySM,
                       &dwDisposition)
    != ERROR_SUCCESS )
        goto AddExit2;

    dwSizeSM = sizeof( szSMvalues );

    // Get list of SQL Service Manager entries
    //
    if( RegQueryValueEx(hKeySM,
                        "Services",
                        NULL,
                        &dwType,
                        szSMvalues,
                        &dwSizeSM)
    != ERROR_SUCCESS )
    {
        dwSizeSM = 1;
        szSMvalues[0] = '\0';
    }

    if( (dwSizeSM+strlen(PROCSRV)+1) < sizeof(szSMvalues) )
    {
        // Append new value to list of SQL Service Manager entries.
        //
        memcpy( (szSMvalues+dwSizeSM-1),
                PROCSRV,
                (strlen(PROCSRV)+1) );
        dwSizeSM += strlen(PROCSRV);
        szSMvalues[dwSizeSM] = '\0';
        dwSizeSM++;
    }

    // Note that we delay write of new values to Stoplight Registry entry.
    // First well will try to update the Service Control Manager.

    // ==== Write entry to Service Control Manager ====
    //
    hSCM = OpenSCManager( NULL,
                          "ServicesActive",
                          SC_MANAGER_ALL_ACCESS );
    if( hSCM == NULL )
        goto AddExit4;

    i = 0;
    while( TRUE )
    {
        LockSCM = LockServiceDatabase( hSCM );

        if( LockSCM != NULL )
            break;

        if( i++ >= 5 )
            goto AddExit3;  // Can't lock database

        Sleep( 1000 );  // sleep for a second
    }

    // Get the path of this process.  We'll use it to constuct the path of the
    // ProcSrv.exe
    //
    szPath[0] = '\0';
    dwPathLength = GetModuleFileName( GetModuleHandle(NULL), szPath, sizeof(szPath) );

    // Stip off process name (i.e. "service.exe")
    //
    while( dwPathLength > 1 )
    {
        --dwPathLength;
        if( szPath[dwPathLength] == '\\' || szPath[dwPathLength] == ':' )
        {
                dwPathLength++;
                szPath[dwPathLength] = '\0';    // Null terminate after the back slash
                break;
        }
    }

    // Append "procsrv.exe" to path
    //
    strcat( szPath, PROCSRV );
    strcat( szPath, ".exe" );

    // Let's create the service entry
    //
    hSrvc = CreateService( hSCM,
                           PROCSRV,  // Service name to start
                           PROCSRV,  // Display name
                           SERVICE_ALL_ACCESS,
                           SERVICE_WIN32_OWN_PROCESS,
                           SERVICE_DEMAND_START,
                           SERVICE_ERROR_NORMAL,
                           szPath,
                           NULL,
                           NULL,
                           NULL,
                           NULL,
                           NULL );
    if( hSrvc == NULL )
        goto AddExit3;

    CloseServiceHandle( hSrvc );
    UnlockServiceDatabase( LockSCM );
    CloseServiceHandle( hSCM );

    // Now we'll update Registry with new ProcSrv entry
    //
    if( RegCreateKeyEx(HKEY_LOCAL_MACHINE,
                       PROCSRV_KEY_PATH,
                       0,
                       NULL,
                       REG_OPTION_NON_VOLATILE,
                       KEY_ALL_ACCESS,
                       NULL,
                       &hKey,
                       &dwDisposition)
    != ERROR_SUCCESS )
        goto AddExit2;

    // ==== Update ListenOn ====
    //
    strcpy( szSaveListenOnPos, NAMED_PIPE_DLL );
    strcat( szSaveListenOnPos, "," );
    strcat( szSaveListenOnPos, NAMED_PIPE_ADDRESS );

    dwSize += (strlen(szSaveListenOnPos) + 1);
    szSaveListenOnPos = szSaveListenOn + dwSize;

    strcpy( szSaveListenOnPos, TCP_IP_DLL );
    strcat( szSaveListenOnPos, "," );
    strcat( szSaveListenOnPos, TCP_ADDRESS );


    dwSize += (strlen(szSaveListenOnPos) + 1);
    szSaveListenOnPos = szSaveListenOn + dwSize;

    szSaveListenOn[dwSize] = '\0';
    dwSize++;

    if( RegSetValueEx(hKey,
                      "ListenOn",
                      0,
                      REG_MULTI_SZ,
                      szSaveListenOn,
                      dwSize)
    != ERROR_SUCCESS )
        goto AddExit1;

    // ==== Complete the update of the SQL Service Manager info ============
    // We do it here to avoid a duplicate entry if other registry updates
    // fail.
    //
    if( RegSetValueEx(hKeySM,
                      "Services",
                      0,
                      REG_MULTI_SZ,
                      szSMvalues,
                      dwSizeSM)
    != ERROR_SUCCESS )
    {
        RegCloseKey( hKeySM );
        goto AddExit1;
    }

    RegFlushKey( hKeySM );
    RegCloseKey( hKeySM );

    return;

AddExit1:
    RegCloseKey( hKey );

AddExit2:
    printf( "Unable to Update Registry\n" );
    return;

AddExit3:
    UnlockServiceDatabase( LockSCM );
    CloseServiceHandle( hSCM );

AddExit4:
    printf( "Unable to Update Service Control Manager\n" );
    return;
}


// **************************************************************************
//
//  FUNCTION: RemoveFromRegistry()
//
//  PURPOSE:  Remove ProcSrv From Registry and Service Control Manager
//
// **************************************************************************

void RemoveFromRegistry()
{
    int    i;
    HKEY   hKey;
    DWORD  dwSizeSM;
    DWORD  dwType;
    char   szSMvalues[1024];
    char * szSMvaluesPos;

    SC_HANDLE hSCM;     // Handle to opened Service Control Manager
    SC_LOCK   LockSCM;  // Lock of Service Control Manager
    SC_HANDLE hSrvc;    // Handle to service

    // Check for non-existance of "ProcSrv" in registry
    //
    if( !DuplicateEntry() )
    {
        printf( "'ProcSrv' not found in Registry\n" );
        return;
    }

    // =============== Remove 'ProcSrv' key from Registry =============
    //
    RegDeleteKey( HKEY_LOCAL_MACHINE, PROCSRV_KEY_PATH );

    // =============== Update SQL Service Manager info ================
    //
    if( RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                     SQL_SM_KEY,
                     0,
                     KEY_ALL_ACCESS,
                     &hKey)
    != ERROR_SUCCESS )
        goto RemoveExit2;

    dwSizeSM = sizeof( szSMvalues );

    // Get SQL Service Manager entries
    //
    if( RegQueryValueEx(hKey,
                        "Services",
                        NULL,
                        &dwType,
                        szSMvalues,
                        &dwSizeSM)
    != ERROR_SUCCESS )
        goto RemoveExit1;       // No SQL Service Manager entries.

    szSMvaluesPos = szSMvalues;

    while( szSMvaluesPos < (szSMvalues + dwSizeSM) )
    {
        if( !stricmp(szSMvaluesPos, PROCSRV) )
        {
                // Remove 'ProcSrv' from SQL Service Manager entries.
                //
                memcpy( szSMvaluesPos,
                        szSMvaluesPos + sizeof(PROCSRV),
                        ((szSMvalues + dwSizeSM) - (szSMvaluesPos + sizeof(PROCSRV))) );

            dwSizeSM -= sizeof( PROCSRV );
                break;
        }

        // 'ProcSrv' entry not found, position to next entry.
        //
        szSMvaluesPos += (strlen( szSMvaluesPos ) + 1);
    }

    // Write back out new list of SQL Service Manager entries.
    //
    if( RegSetValueEx(hKey,
                      "Services",
                      0,
                      REG_MULTI_SZ,
                      szSMvalues,
                      dwSizeSM)
    != ERROR_SUCCESS )
    {
        RegCloseKey( hKey );
        goto RemoveExit1;
    }

    RegFlushKey( hKey );
    RegCloseKey( hKey );

    // ==== Remove entry from Service Control Manager ====
    //
    hSCM = OpenSCManager( NULL,
                          "ServicesActive",
                          SC_MANAGER_ALL_ACCESS );
    if( hSCM == NULL )
        goto RemoveExit4;

    i = 0;
    while( TRUE )
    {
        LockSCM = LockServiceDatabase( hSCM );

        if( LockSCM != NULL )
            break;

        if( i++ >= 5 )
            goto RemoveExit3;   // Can't lock database

        Sleep( 1000 );  // sleep for a second
    }

    // Let's remove the service entry
    //
    hSrvc = OpenService( hSCM,
                         PROCSRV,       // Service name
                         SERVICE_ALL_ACCESS );
    if( hSrvc == NULL )
        goto RemoveExit3;

    DeleteService( hSrvc );

    CloseServiceHandle( hSrvc );
    UnlockServiceDatabase( LockSCM );
    CloseServiceHandle( hSCM );

    return;

RemoveExit1:
    RegCloseKey( hKey );

RemoveExit2:
    printf( "Unable to Update Registry\n" );
    return;

RemoveExit3:
    UnlockServiceDatabase( LockSCM );
    CloseServiceHandle( hSCM );

RemoveExit4:
    printf( "Unable to Update Service Control Manager\n" );
    return;
}


// **************************************************************************
//
//  FUNCTION: DuplicateEntry
//
//  PURPOSE:  Determines if a duplicate "ProcSrv" exist in
//            the registry.
//
//  RETURNS:
//          TRUE if name exist, else
//          FALSE if name not found.
//
//
// **************************************************************************

BOOL DuplicateEntry()
{
    HKEY     hKey;

    if( RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                     PROCSRV_KEY_PATH,
                     0,
                     KEY_ENUMERATE_SUB_KEYS,
                     &hKey)
    != ERROR_SUCCESS )
        return FALSE;

    RegCloseKey( hKey );
    return TRUE;
}


// **************************************************************************
//
//  FUNCTION: RefreshStoplight()
//
//  PURPOSE:  This routine causes the SQL Service Manager to refresh its
//            list.
//
// **************************************************************************

void RefreshStoplight()
{
    HANDLE hEvent;

    hEvent = OpenEvent( EVENT_MODIFY_STATE,
                        TRUE,
                        "MICROSOFTSQLServiceControlManagerRefresh" );
    if( hEvent )
    {
        SetEvent( hEvent );
        CloseHandle( hEvent );
    }
}
