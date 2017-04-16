/***
*fstat.c - return file status info
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines fstat() - return file status info
*
*******************************************************************************/

#ifndef _MAC


#include <cruntime.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <msdos.h>
#include <dostypes.h>
#include <io.h>
#include <internal.h>
#include <stddef.h>
#include <oscalls.h>
#include <stdio.h>
#include <mtdll.h>
#include <time.h>

#define IO_DEVNBR   0x3f

/***
*int _fstat(fildes, buf) - fills supplied buffer with status info
*
*Purpose:
*       Fills the supplied buffer with status information on the
*       file represented by the specified file designator.
*       WARNING: the dev/rdev fields are zero for files.  This is
*       incompatible with DOS 3 version of this routine.
*
*       Note: We cannot directly use the file time stamps returned in the
*       BY_HANDLE_FILE_INFORMATION structure. The values are supposedly in
*       system time and system time is ambiguously defined (it is UTC for
*       Windows NT, local time for Win32S and probably local time for
*       Win32C). Therefore, these values must be converted to local time
*       before than can be used.
*
*Entry:
*       int fildes   - file descriptor
*       struct stat *buf - buffer to store result in
*
*Exit:
*       fills in buffer pointed to by buf
*       returns 0 if successful
*       returns -1 and sets errno if unsuccessful
*
*Exceptions:
*
*******************************************************************************/

#ifdef _USE_INT64

int __cdecl _fstati64 (
        int fildes,
        struct _stati64 *buf
        )

#else  /* _USE_INT64 */

int __cdecl _fstat (
        int fildes,
        struct _stat *buf
        )

#endif  /* _USE_INT64 */
{
        int isdev;          /* 0 for a file, 1 for a device */
        int retval = 0;     /* assume good return */
        BY_HANDLE_FILE_INFORMATION bhfi;
        FILETIME LocalFTime;
        SYSTEMTIME SystemTime;

        if ( ((unsigned)fildes >= (unsigned)_nhandle) ||
             !(_osfile(fildes) & FOPEN) )
        {
            errno = EBADF;
            return(-1);
        }

        /* Lock the file */

        _lock_fh(fildes);

        /* Find out what kind of handle underlies filedes
         */
        isdev = GetFileType((HANDLE)_osfhnd(fildes)) & ~FILE_TYPE_REMOTE;

        if ( isdev != FILE_TYPE_DISK ) {

            /* not a disk file. probably a device or pipe
             */
            if ( (isdev == FILE_TYPE_CHAR) || (isdev == FILE_TYPE_PIPE) ) {
                /* treat pipes and devices similarly. no further info is
                 * available from any API, so set the fields as reasonably
                 * as possible and return.
                 */
                if ( isdev == FILE_TYPE_CHAR )
                    buf->st_mode = _S_IFCHR;
                else
                    buf->st_mode = _S_IFIFO;

                buf->st_rdev = buf->st_dev = (_dev_t)fildes;
                buf->st_nlink = 1;
                buf->st_uid = buf->st_gid = buf->st_ino = 0;
                buf->st_atime = buf->st_mtime = buf->st_ctime = 0;
                if ( isdev == FILE_TYPE_CHAR ) {
#ifdef _USE_INT64
                    buf->st_size = 0i64;
#else  /* _USE_INT64 */
                    buf->st_size = 0;
#endif  /* _USE_INT64 */
                }
                else {
                    unsigned long ulAvail;
                    int rc;
                    rc = PeekNamedPipe((HANDLE)_osfhnd(fildes),
                                       NULL,
                                       0,
                                       NULL,
                                       &ulAvail,
                                       NULL);

                    if (rc) {
                        buf->st_size = (_off_t)ulAvail;
                    }
                    else {
                        buf->st_size = (_off_t)0;
                    }
                }

                goto done;
            }
            else if ( isdev == FILE_TYPE_UNKNOWN ) {
                errno = EBADF;
                retval = -1;
                goto done;      /* join common return code */
            }
            else {
                /* according to the documentation, this cannot happen, but
                 * play it safe anyway.
                 */
                _dosmaperr(GetLastError());
                retval = -1;
                goto done;
            }
        }


        /* set the common fields
         */
        buf->st_ino = buf->st_uid = buf->st_gid = buf->st_mode = 0;
        buf->st_nlink = 1;

        /* use the file handle to get all the info about the file
         */
        if ( !GetFileInformationByHandle((HANDLE)_osfhnd(fildes), &bhfi) ) {
            _dosmaperr(GetLastError());
            retval = -1;
            goto done;
        }

        if ( bhfi.dwFileAttributes & FILE_ATTRIBUTE_READONLY )
            buf->st_mode |= (_S_IREAD + (_S_IREAD >> 3) + (_S_IREAD >> 6));
        else
            buf->st_mode |= ((_S_IREAD|_S_IWRITE) + ((_S_IREAD|_S_IWRITE) >> 3)
              + ((_S_IREAD|_S_IWRITE) >> 6));

        /* set file date fields
         */
        if ( !FileTimeToLocalFileTime( &(bhfi.ftLastWriteTime), &LocalFTime )
             || !FileTimeToSystemTime( &LocalFTime, &SystemTime ) )
        {
            retval = -1;
            goto done;
        }

        buf->st_mtime = __loctotime_t(SystemTime.wYear,
                                      SystemTime.wMonth,
                                      SystemTime.wDay,
                                      SystemTime.wHour,
                                      SystemTime.wMinute,
                                      SystemTime.wSecond,
                                      -1);

        if ( bhfi.ftLastAccessTime.dwLowDateTime ||
             bhfi.ftLastAccessTime.dwHighDateTime )
        {

            if ( !FileTimeToLocalFileTime( &(bhfi.ftLastAccessTime),
                                           &LocalFTime ) ||
                 !FileTimeToSystemTime( &LocalFTime, &SystemTime ) )
            {
                retval = -1;
                goto done;
            }

            buf->st_atime = __loctotime_t(SystemTime.wYear,
                                          SystemTime.wMonth,
                                          SystemTime.wDay,
                                          SystemTime.wHour,
                                          SystemTime.wMinute,
                                          SystemTime.wSecond,
                                          -1);
        }
        else
            buf->st_atime = buf->st_mtime;

        if ( bhfi.ftCreationTime.dwLowDateTime ||
             bhfi.ftCreationTime.dwHighDateTime )
        {

            if ( !FileTimeToLocalFileTime( &(bhfi.ftCreationTime),
                                           &LocalFTime ) ||
                 !FileTimeToSystemTime( &LocalFTime, &SystemTime ) )
            {
                retval = -1;
                goto done;
            }

            buf->st_ctime = __loctotime_t(SystemTime.wYear,
                                          SystemTime.wMonth,
                                          SystemTime.wDay,
                                          SystemTime.wHour,
                                          SystemTime.wMinute,
                                          SystemTime.wSecond,
                                          -1);
        }
        else
            buf->st_ctime = buf->st_mtime;

#ifdef _USE_INT64
        buf->st_size = ((__int64)(bhfi.nFileSizeHigh)) * (0x100000000i64) +
                       (__int64)(bhfi.nFileSizeLow);
#else  /* _USE_INT64 */
        buf->st_size = bhfi.nFileSizeLow;
#endif  /* _USE_INT64 */

        buf->st_mode |= _S_IFREG;

        /* On DOS, this field contains the drive number, but
         * the drive number is not available on this platform.
         * Also, for UNC network names, there is no drive number.
         */
        buf->st_rdev = buf->st_dev = 0;

/* Common return code */

done:
        _unlock_fh(fildes);
        return(retval);
}


#else  /* _MAC */


#include <cruntime.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <memory.h>
#include <msdos.h>
#include <dostypes.h>
#include <io.h>
#include <internal.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <macos\osutils.h>
#include <macos\files.h>
#include <macos\errors.h>

#define IO_DEVNBR   0x3f

unsigned short __cdecl _dtoxmode ( CInfoPBPtr pcinfoPB );

/***
*int _fstat(fildes, buf) - fills supplied buffer with status info
*
*Purpose:
*       Fills the supplied buffer with status information on the
*       file represented by the specified file designator.
*       WARNING: the dev/rdev fields are zero for files.  This is
*       incompatible with DOS 3 version of this routine.
*
*Entry:
*       int fildes -    file descriptor
*       struct stat *buf - buffer to store result in
*
*Exit:
*       fills in buffer pointed to by buf
*       returns 0 if successful
*       returns -1 and sets errno if unsuccessful
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _fstat (
        int fildes,
        struct _stat *buf
        )
{
        int retval = 0;         /* assume good return */
        OSErr osErr;
        FCBPBRec parmFCB;
        char st[32];
        CInfoPBRec cinfoPB;
        DateTimeRec dt;
        DateTimeRec dtc;

        if (fildes < 0 || fildes >= _nfile) {
                errno = EBADF;
                return(-1);
        }

        if (_osfhnd[fildes] == -1 && (_osfile[fildes] & FDEV))
        {
                /* MPW console */
                buf->st_mode = _S_IFCHR;
                buf->st_dev=buf->st_rdev = _osfhnd[fildes];
                buf->st_ino = buf->st_uid = buf->st_gid =  0;
                buf->st_nlink = 1;
                buf->st_atime=buf->st_ctime=buf->st_mtime=0;
                return 0;
        }

        /* Issue the get file control block call. */
        memset(&parmFCB, '\0', sizeof(FCBPBRec));
        parmFCB.ioRefNum = _osfhnd[fildes];
        *st = sizeof(st) - 1;
        parmFCB.ioNamePtr = st;
        osErr = PBGetFCBInfoSync(&parmFCB);
        if (osErr != 0)
        {
                _dosmaperr(osErr);
                return -1;
        }

        memset(&cinfoPB, '\0', sizeof(CInfoPBRec));
        cinfoPB.hFileInfo.ioNamePtr = parmFCB.ioNamePtr;
        cinfoPB.hFileInfo.ioFDirIndex = 0;
        cinfoPB.hFileInfo.ioVRefNum = parmFCB.ioFCBVRefNum;
        cinfoPB.hFileInfo.ioDirID = parmFCB.ioFCBParID;
        osErr = PBGetCatInfoSync(&cinfoPB);
        if (osErr != 0)
        {
                _dosmaperr(osErr);
                return -1;
        }

        /* set the common fields */

        buf->st_ino = buf->st_uid = buf->st_gid = buf->st_mode = 0;
        buf->st_nlink = 1;
        buf->st_mode |= (_osfile[fildes] & FRDONLY)
                        ? (_S_IREAD + (_S_IREAD >> 3) + (_S_IREAD >> 6))
                        : ((_S_IREAD|_S_IWRITE) +
                          ((_S_IREAD|_S_IWRITE) >> 3)
                          + ((_S_IREAD|_S_IWRITE) >> 6));

        /* file or dir ? */
        if (cinfoPB.hFileInfo.ioFlAttrib & 0x10)
        {       /*dir*/
                Secs2Date(cinfoPB.dirInfo.ioDrMdDat, &dt);
                Secs2Date(cinfoPB.dirInfo.ioDrCrDat, &dtc);
                buf->st_size = 0;
        }
        else
        {       /*file*/
                Secs2Date(cinfoPB.hFileInfo.ioFlMdDat, &dt);
                Secs2Date(cinfoPB.hFileInfo.ioFlCrDat, &dtc);
                buf->st_size = cinfoPB.hFileInfo.ioFlLgLen + cinfoPB.hFileInfo.ioFlRLgLen;
        }
        buf->st_mode = _dtoxmode(&cinfoPB);

        buf->st_mtime = _gmtotime_t(dt.year, dt.month, dt.day,
                                    dt.hour, dt.minute, dt.second);
        buf->st_atime = buf->st_mtime;
        buf->st_ctime = _gmtotime_t(dtc.year, dtc.month, dtc.day,
                                    dtc.hour, dtc.minute, dtc.second);

        buf->st_rdev = buf->st_dev = cinfoPB.hFileInfo.ioVRefNum;


/* Common return code */

        return(retval);
}


#endif  /* _MAC */
