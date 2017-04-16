/***
*access.c - access function
*
*       Copyright (c) 1989-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       This file has the _access() function which checks on file accessability.
*
*******************************************************************************/

#ifndef _MAC

#include <cruntime.h>
#include <io.h>
#include <oscalls.h>
#include <stdlib.h>
#include <errno.h>
#include <msdos.h>
#include <internal.h>
#include <tchar.h>

/***
*int _access(path, amode) - check whether file can be accessed under mode
*
*Purpose:
*       Checks to see if the specified file exists and can be accessed
*       in the given mode.
*
*Entry:
*       _TSCHAR *path - pathname
*       int amode -     access mode
*                       (0 = exist only, 2 = write, 4 = read, 6 = read/write)
*
*Exit:
*       returns 0 if file has given mode
*       returns -1 and sets errno if file does not have given mode or
*       does not exist
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _taccess (
        const _TSCHAR *path,
        int amode
        )
{
        DWORD attr;

        attr = GetFileAttributes((LPTSTR)path);
        if (attr  == 0xffffffff) {
                /* error occured -- map error code and return */
                _dosmaperr(GetLastError());
                return -1;
        }

        /* no error; see if returned premission settings OK */
        if ( (attr & FILE_ATTRIBUTE_READONLY) && (amode & 2) ) {
                /* no write permission on file, return error */
                errno = EACCES;
                _doserrno = E_access;
                return -1;
        }
        else
                /* file exists and has requested permission setting */
                return 0;

}

#else  /* _MAC */

#include <cruntime.h>
#include <io.h>
#include <stdlib.h>
#include <errno.h>
#include <internal.h>
#include <string.h>
#include <macos\osutils.h>
#include <macos\files.h>
#include <macos\errors.h>

/***
*int _access(path, amode) - check whether file can be accessed under mode
*
*Purpose:
*       Checks to see if the specified file exists and can be accessed
*       in the given mode.
*
*Entry:
*       char *path -    pathname
*       int amode -     access mode
*                       (0 = exist only, 2 = write, 4 = read, 6 = read/write)
*
*Exit:
*       returns 0 if file has given mode
*       returns -1 and sets errno if file does not have given mode or
*       does not exist
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _access (
        const char *path,
        int amode
        )
{
        CInfoPBRec cinfoPB;
        char szPath[256];
        OSErr osErr;

        if (!*path)
        {
                errno = ENOENT;
                return -1;
        }

        strcpy(szPath, path);
        cinfoPB.dirInfo.ioVRefNum = 0;
        cinfoPB.dirInfo.ioDrDirID = 0;
        cinfoPB.dirInfo.ioFDirIndex = 0;
        cinfoPB.dirInfo.ioNamePtr = _c2pstr(szPath);
        osErr = PBGetCatInfoSync(&cinfoPB);
        if (osErr)
        {
                _dosmaperr(osErr);
                return -1;
        }

        //file locked or read only permission
        if ( (cinfoPB.dirInfo.ioFlAttrib & 0x1 ||
                cinfoPB.dirInfo.ioDrUsrWds.frFlags == 1) && (amode & 2) )
        {
                /* no write permission on file, return error */
                errno = EACCES;
                _macerrno = permErr;
                return -1;
        }
        else
                /* file exists and has requested permission setting */
                return 0;

}

#endif  /* _MAC */
