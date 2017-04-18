/***
*drive.c - get and change current drive
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file has the _getdrive() and _chdrive() functions
*
*******************************************************************************/

#ifndef _MAC

#include <cruntime.h>
#include <oscalls.h>
#include <mtdll.h>
#include <internal.h>
#include <msdos.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


/***
*int _getdrive() - get current drive (1=A:, 2=B:, etc.)
*
*Purpose:
*       Returns the current disk drive
*
*Entry:
*       No parameters.
*
*Exit:
*       returns 1 for A:, 2 for B:, 3 for C:, etc.
*       returns 0 if current drive cannot be determined.
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _getdrive (
        void
        )
{
        ULONG drivenum;
        UCHAR curdirstr[_MAX_PATH];

        drivenum = 0;
        if (GetCurrentDirectory(sizeof(curdirstr), curdirstr))
                if (curdirstr[1] == ':')
                        drivenum = toupper(curdirstr[0]) - 64;

        return drivenum;
}


/***
*int _chdrive(int drive) - set the current drive (1=A:, 2=B:, etc.)
*
*Purpose:
*       Allows the user to change the current disk drive
*
*Entry:
*       drive - the number of drive which should become the current drive
*
*Exit:
*       returns 0 if successful, else -1
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _chdrive (
        int drive
        )
{
        char  newdrive[3];

        if (drive < 1 || drive > 31) {
            errno = EACCES;
            _doserrno = ERROR_INVALID_DRIVE;
            return -1;
        }

        _mlock(_ENV_LOCK);

        newdrive[0] = (char)('A' + (char)drive - (char)1);
        newdrive[1] = ':';
        newdrive[2] = '\0';

        /*
         * Set new drive. If current directory on new drive exists, it
         * will become the cwd. Otherwise defaults to root directory.
         */

        if ( SetCurrentDirectory((LPSTR)newdrive) ) {
            _munlock(_ENV_LOCK);
            return 0;
        }
        else {
            _dosmaperr(GetLastError());
            _munlock(_ENV_LOCK);
            return -1;
        }
}

#else  /* _MAC */


#include <cruntime.h>
#include <ctype.h>
#include <stdlib.h>
#include <macos\osutils.h>
#include <macos\files.h>
#include <macos\errors.h>

/***
*int _getdrive() - get current drive (-1=BootDisk, -2=Second mounted drive, etc.)
*
*Purpose:
*       Returns the current disk drive
*
*Entry:
*       No parameters.
*
*Exit:
*       returns 1 for BootDisk, 2 for Second mounted drive, etc.
*       returns 0 if current drive cannot be determined.
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _getdrive (
        void
        )
{
        OSErr osErr;
        WDPBRec wdPB;
        char st[256];

        wdPB.ioNamePtr = &st[0];
        osErr = PBHGetVolSync(&wdPB);
        if (osErr)
        {
            return 0;
        }


        return wdPB.ioWDVRefNum;
}


/***
*int _chdrive(int drive) - set the current drive (-1=BootDisk, -2=Second drive, etc.)
*
*Purpose:
*       Allows the user to change the current disk drive
*
*
*Entry:
*       drive - the number of drive which should become the current drive
*
*Exit:
*       returns 0 if successful, else -1
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _chdrive (
        int drive
        )
{
        OSErr osErr;
        WDPBRec wdPB;

        wdPB.ioNamePtr = NULL;
        wdPB.ioWDDirID = 0;
        wdPB.ioVRefNum = drive;
        osErr = PBHSetVolSync(&wdPB);
        if (osErr)
        {
            return -1;
        }

        return 0;
}

#endif  /* _MAC */
