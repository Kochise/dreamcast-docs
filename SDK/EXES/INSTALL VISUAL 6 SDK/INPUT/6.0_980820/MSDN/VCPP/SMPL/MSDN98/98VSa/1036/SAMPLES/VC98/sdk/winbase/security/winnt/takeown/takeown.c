
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

/*++

Module Name:

    Takeown.c

Abstract:

    Implements a recovery scheme to give an Administrator access to a 
    file that has been denied to all.  

Environment:

    Must be run from an Administrator account in order to perform 
    reliably.  

--*/
#include <windows.h>
#include <stdio.h>
#include <malloc.h>

BOOL
AssertTakeOwnership(
    HANDLE TokenHandle
    );

BOOL
GetTokenHandle(
    PHANDLE TokenHandle
    );

BOOL
VariableInitialization();




PSID AliasAdminsSid = NULL;
PSID SeWorldSid;

static SID_IDENTIFIER_AUTHORITY    SepNtAuthority = SECURITY_NT_AUTHORITY;
static SID_IDENTIFIER_AUTHORITY    SepWorldSidAuthority   = SECURITY_WORLD_SID_AUTHORITY;




void main (int argc, char *argv[])
{


    BOOL Result;
    LPSTR lpFileName;
    SECURITY_DESCRIPTOR SecurityDescriptor;
    HANDLE TokenHandle;


    //
    // We expect a file...
    //
    if (argc <= 1) {

        printf("Must specify a file name");
        return;
    }


    lpFileName = argv[1];


    Result = VariableInitialization();

    if ( !Result ) {
        printf("Out of memory\n");
        return;
    }




    Result = GetTokenHandle( &TokenHandle );

    if ( !Result ) {

        //
        // This should not happen
        //

        printf("Unable to obtain the handle to our token, exiting\n");
        return;
    }






    //
    // Attempt to put a NULL Dacl on the object
    //

    InitializeSecurityDescriptor( &SecurityDescriptor, SECURITY_DESCRIPTOR_REVISION );


    Result = SetSecurityDescriptorDacl (
                 &SecurityDescriptor,
                 TRUE,
                 NULL,
                 FALSE
                 );



    if ( !Result ) {
        printf("SetSecurityDescriptorDacl failed, error code = %d\n", GetLastError());
        printf("Exiting\n");
        return;
    }

    Result = SetFileSecurity(
                 lpFileName,
                 DACL_SECURITY_INFORMATION,
                 &SecurityDescriptor
                 );

    if ( Result ) {

        printf("Successful, protection removed\n");
        return;
    } 


    //
    // That didn't work.
    //


    //
    // Attempt to make Administrator the owner of the file.
    //


    Result = SetSecurityDescriptorOwner (
                 &SecurityDescriptor,
                 AliasAdminsSid,
                 FALSE
                 );

    if ( !Result ) {
        printf("SetSecurityDescriptorOwner failed, lasterror = %d\n", GetLastError());
        return;
    }


    Result = SetFileSecurity(
                 lpFileName,
                 OWNER_SECURITY_INFORMATION,
                 &SecurityDescriptor
                 );

    if ( !Result ) {


        //
        // That didn't work either.
        //



        //
        // Assert TakeOwnership privilege, then try again.  Note that
        // since the privilege is only enabled for the duration of 
        // this process, we don't have to worry about turning it off
        // again.
        //

        Result = AssertTakeOwnership( TokenHandle );

        if ( !Result ) {
            printf("Could not enable SeTakeOwnership privilege\n");
            printf("Log on as Administrator and try again\n");
            return;
        }


        Result = SetFileSecurity(
                     lpFileName,
                     OWNER_SECURITY_INFORMATION,
                     &SecurityDescriptor
                     );

        if ( !Result ) {

            printf("Unable to assign Administrator as owner\n");
            printf("Log on as Administrator and try again\n");
            return;

        }
    }

    //
    // Try to put a benign DACL onto the file again
    //

    Result = SetFileSecurity(
                 lpFileName,
                 DACL_SECURITY_INFORMATION,
                 &SecurityDescriptor
                 );

    if ( !Result ) {

        //
        // This should not happen.
        //

        printf("SetFileSecurity unexpectedly failed, error code = %d\n", GetLastError());

    } else {

        printf("Successful, protection removed\n");
        return;
    }
}





BOOL
GetTokenHandle(
    PHANDLE TokenHandle
    )
//
// This routine will open the current process and return
// a handle to its token.
//
// These handles will be closed for us when the process
// exits.
//
{

    HANDLE ProcessHandle;
    BOOL Result;

    ProcessHandle = OpenProcess(
                        PROCESS_QUERY_INFORMATION,
                        FALSE,
                        GetCurrentProcessId()
                        );

    if ( ProcessHandle == NULL ) {

        //
        // This should not happen
        //

        return( FALSE );
    }


    Result = OpenProcessToken (
                 ProcessHandle,
                 TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
                 TokenHandle
                 );

    if ( !Result ) {

        //
        // This should not happen
        //

        return( FALSE );

    }

    return( TRUE );
}


BOOL
AssertTakeOwnership(
    HANDLE TokenHandle
    )
//
// This routine turns on SeTakeOwnershipPrivilege in the current
// token.  Once that has been accomplished, we can open the file
// for WRITE_OWNER even if we are denied that access by the ACL
// on the file.

{
    LUID TakeOwnershipValue;
    BOOL Result;
    TOKEN_PRIVILEGES TokenPrivileges;


    //
    // First, find out the value of TakeOwnershipPrivilege
    //


    Result = LookupPrivilegeValue(
                 NULL,
                 "SeTakeOwnershipPrivilege",
                 &TakeOwnershipValue
                 );

    if ( !Result ) {

        //
        // This should not happen
        //

        printf("Unable to obtain value of TakeOwnership privilege\n");
        printf("Error = %d\n",GetLastError());
        printf("Exiting\n");
        return FALSE;
    }

    //
    // Set up the privilege set we will need
    //

    TokenPrivileges.PrivilegeCount = 1;
    TokenPrivileges.Privileges[0].Luid = TakeOwnershipValue;
    TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;




    (VOID) AdjustTokenPrivileges (
                TokenHandle,
                FALSE,
                &TokenPrivileges,
                sizeof( TOKEN_PRIVILEGES ),
                NULL,
                NULL
                );

    if ( GetLastError() != NO_ERROR ) {

        return( FALSE );

    } else {

        return( TRUE );
    }

}



BOOL
VariableInitialization()

//
// Create some useful SIDs.
//

{

    BOOL Result;

    Result = AllocateAndInitializeSid(
                 &SepNtAuthority,
                 2,
                 SECURITY_BUILTIN_DOMAIN_RID,
                 DOMAIN_ALIAS_RID_ADMINS,
                 0,
                 0,
                 0,
                 0,
                 0,
                 0,
                 &AliasAdminsSid
                 );

    if ( !Result ) {
        return( FALSE );
    }


    Result = AllocateAndInitializeSid(
                 &SepWorldSidAuthority,
                 1,
                 SECURITY_WORLD_RID,
                 0,
                 0,
                 0,
                 0,
                 0,
                 0,
                 0,
                 &SeWorldSid
                 );

    if ( !Result ) {
        return( FALSE );
    }

    return( TRUE );
}
