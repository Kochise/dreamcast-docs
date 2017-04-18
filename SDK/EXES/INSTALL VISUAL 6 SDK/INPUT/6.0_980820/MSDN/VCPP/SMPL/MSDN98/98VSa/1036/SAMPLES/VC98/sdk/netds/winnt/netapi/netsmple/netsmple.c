
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1995-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/


/*
    Net API Example

    Create a user and a local group and add the user to the local group.

    This sample requires NT 3.51
*/

#define UNICODE 1
#include <windows.h>
#include <lmcons.h>
#include <lmaccess.h>
#include <lmerr.h>
#include <lmapibuf.h>
#include <stdio.h>
#include <stdlib.h>

int _CRTAPI1 main( int cArgs, char *pArgs[] );

NET_API_STATUS NetSample( LPWSTR lpszDomain,
                          LPWSTR lpszUser,
                          LPWSTR lpszPassword,
                          LPWSTR lpszLocalGroup )
{

    USER_INFO_1               user_info;
    LOCALGROUP_INFO_1         localgroup_info;
    LOCALGROUP_MEMBERS_INFO_3 localgroup_members;
    LPWSTR                    lpszPrimaryDC = NULL;
    NET_API_STATUS            err = 0;
    DWORD                     parm_err = 0;

/* First get the name of the Primary Domain Controller. */
/* Be sure to free the returned buffer */

    err = NetGetDCName( NULL,                        /* Local Machine */
                        lpszDomain,                  /* Domain Name */
                        (LPBYTE *)&lpszPrimaryDC );  /* returned PDC */

    if ( err != 0 )
    {
        printf( "Error getting DC name: %d\n", err );
        return( err );
    }


/* Set up the USER_INFO_1 struct */

    user_info.usri1_name = lpszUser;
    user_info.usri1_password = lpszPassword;
    user_info.usri1_priv = USER_PRIV_USER;
    user_info.usri1_home_dir = TEXT("");
    user_info.usri1_comment = TEXT("Sample User");
    user_info.usri1_flags = UF_SCRIPT;
    user_info.usri1_script_path = TEXT("");

    err = NetUserAdd( lpszPrimaryDC,       /* PDC name */
                      1,                   /* level */
                      (LPBYTE)&user_info,  /* input buffer */
                      &parm_err );         /* parameter in error */

    switch ( err )
    {
    case 0:
        printf("user successfully created.\n");
        break;
    case NERR_UserExists:
        printf("user already exists.\n");
        err = 0;
        break;
    case ERROR_INVALID_PARAMETER:
        printf("Invalid Parameter Error adding user: Parameter Index = %d\n",
                parm_err);
        NetApiBufferFree( lpszPrimaryDC );
        return( err );
    default:
        printf("Error adding user: %d\n", err);
        NetApiBufferFree( lpszPrimaryDC );
        return( err );
    }

/* Set up the LOCALGROUP_INFO_1 struct */

    localgroup_info.lgrpi1_name = lpszLocalGroup;
    localgroup_info.lgrpi1_comment = TEXT("Sample Local group.");

    err = NetLocalGroupAdd( lpszPrimaryDC,              /* PDC name */
                            1,                          /* level */
                            (LPBYTE)&localgroup_info,   /* input buffer */
                            &parm_err );                /* parm in error */

    switch ( err )
    {
    case 0:
        printf("Local Group successfully created.\n");
        break;
    case ERROR_ALIAS_EXISTS:
        printf("Local Group already exists.\n");
        err = 0;
        break;
    case ERROR_INVALID_PARAMETER:
        printf("Invalid Parameter Error adding Local Group: Parameter Index = %d\n",
                err, parm_err);
        NetApiBufferFree( lpszPrimaryDC );
        return( err );
    default:
        printf("Error adding Local Group: %d\n", err);
        NetApiBufferFree( lpszPrimaryDC );
        return( err );
    }

/* Now add the user to the local group */

    localgroup_members.lgrmi3_domainandname = lpszUser;

    err = NetLocalGroupAddMembers( lpszPrimaryDC,        /* PDC name */
                                   lpszLocalGroup,       /* group name */
                                   3,                    /* passing in name */
                                   (LPBYTE)&localgroup_members, /* Buffer */
                                   1 );                  /* count passed in */

    switch ( err )
    {
    case 0:
        printf("User successfully added to Local Group.\n");
        break;
    case ERROR_MEMBER_IN_ALIAS:
        printf("User already in Local Group.\n");
        err = 0;
        break;
    default:
        printf("Error adding User to Local Group: %d\n", err);
        break;
    }

    NetApiBufferFree( lpszPrimaryDC );
    return( err );

}

int _CRTAPI1 main( int    cArgs,
                   char * pArgs[] )
{
    NET_API_STATUS err = 0;

    printf( "Calling NetSample.\n" );
    err = NetSample( TEXT("SampleDomain"),
                     TEXT("SampleUser"),
                     TEXT("SamplePswd"),
                     TEXT("SampleLG") );
    printf( "NetSample returned %d\n", err );
    return( 0 );
}
