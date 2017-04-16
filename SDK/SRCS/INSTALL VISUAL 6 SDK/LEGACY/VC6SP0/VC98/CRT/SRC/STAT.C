/***
*stat.c - get file status
*
*       Copyright (c) 1985-1997, Microsoft Corporation. All rights reserved.
*
*Purpose:
*       defines _stat() - get file status
*
*******************************************************************************/

#ifndef _MAC

#include <cruntime.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <msdos.h>
#include <dostypes.h>
#include <oscalls.h>
#include <string.h>
#include <internal.h>
#include <stdlib.h>
#include <direct.h>
#include <mbstring.h>
#include <tchar.h>


#define ISSLASH(a)  ((a) == _T('\\') || (a) == _T('/'))


#ifdef _UNICODE
#define __tdtoxmode __wdtoxmode
#else  /* _UNICODE */
#define __tdtoxmode __dtoxmode
#endif  /* _UNICODE */


/*
 * Local routine which returns true if the argument is a UNC name
 * specifying the root name of a share, such as '\\server\share\'.
 */

static int IsRootUNCName(const _TSCHAR *path);


/***
*unsigned __tdtoxmode(attr, name) -
*
*Purpose:
*
*Entry:
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

#ifdef _USE_INT64

extern unsigned short __cdecl __tdtoxmode(int, const _TSCHAR *);

#else  /* _USE_INT64 */

unsigned short __cdecl __tdtoxmode (
        int attr,
        const _TSCHAR *name
        )
{
        REG1 unsigned short uxmode;
        unsigned dosmode;
        REG2 const _TSCHAR *p;

        dosmode = attr & 0xff;
        if ((p = name)[1] == _T(':'))
            p += 2;

        /* check to see if this is a directory - note we must make a special
        * check for the root, which DOS thinks is not a directory
        */

        uxmode = (unsigned short)
                 (((ISSLASH(*p) && !p[1]) || (dosmode & A_D) || !*p)
                 ? _S_IFDIR|_S_IEXEC : _S_IFREG);

        /* If attribute byte does not have read-only bit, it is read-write */

        uxmode |= (dosmode & A_RO) ? _S_IREAD : (_S_IREAD|_S_IWRITE);

        /* see if file appears to be executable - check extension of name */

        if (p = _tcsrchr(name, _T('.'))) {
            if ( !_tcsicmp(p, _T(".exe")) ||
                 !_tcsicmp(p, _T(".cmd")) ||
                 !_tcsicmp(p, _T(".bat")) ||
                 !_tcsicmp(p, _T(".com")) )
                uxmode |= _S_IEXEC;
        }

        /* propagate user read/write/execute bits to group/other fields */

        uxmode |= (uxmode & 0700) >> 3;
        uxmode |= (uxmode & 0700) >> 6;

        return(uxmode);
}

#endif  /* _USE_INT64 */

/***
*int _stat(name, buf) - get file status info
*
*Purpose:
*       _stat obtains information about the file and stores it in the
*       structure pointed to by buf.
*
*       Note: We cannot directly use the file time stamps returned in the
*       WIN32_FIND_DATA structure. The values are supposedly in system time
*       and system time is ambiguously defined (it is UTC for Windows NT, local
*       time for Win32S and probably local time for Win32C). Therefore, these
*       values must be converted to local time before than can be used.
*
*Entry:
*       _TSCHAR *name -    pathname of given file
*       struct _stat *buffer - pointer to buffer to store info in
*
*Exit:
*       fills in structure pointed to by buffer
*       returns 0 if successful
*       returns -1 and sets errno if unsuccessful
*
*Exceptions:
*
*******************************************************************************/

#ifdef _USE_INT64

int __cdecl _tstati64 (
        REG1 const _TSCHAR *name,
        REG2 struct _stati64 *buf
        )

#else  /* _USE_INT64 */

int __cdecl _tstat (
        REG1 const _TSCHAR *name,
        REG2 struct _stat *buf
        )

#endif  /* _USE_INT64 */

{
        _TSCHAR *  path;
        _TSCHAR    pathbuf[ _MAX_PATH ];
        int drive;          /* A: = 1, B: = 2, etc. */
        HANDLE findhandle;
        WIN32_FIND_DATA findbuf;

        /* Don't allow wildcards to be interpreted by system */

#ifdef _UNICODE
        if (wcspbrk(name, L"?*")) {
#else  /* _UNICODE */
        if (_mbspbrk(name, "?*")) {
#endif  /* _UNICODE */
            errno = ENOENT;
            _doserrno = E_nofile;
            return(-1);
        }

        /* Try to get disk from name.  If none, get current disk.  */

        if (name[1] == _T(':')){
            if ( *name && !name[2] ){
                errno = ENOENT;             /* return an error if name is   */
                _doserrno = E_nofile;       /* just drive letter then colon */
                return( -1 );
            }
            drive = _totlower(*name) - _T('a') + 1;
        }
        else
            drive = _getdrive();

        /* Call Find Match File */
        findhandle = FindFirstFile((_TSCHAR *)name, &findbuf);
        if ( findhandle == INVALID_HANDLE_VALUE ) {
#ifdef _UNICODE
            if ( !( wcspbrk(name, L"./\\") &&
#else  /* _UNICODE */
            if ( !( _mbspbrk(name, "./\\") &&
#endif  /* _UNICODE */
                 (path = _tfullpath( pathbuf, name, _MAX_PATH )) &&
                 /* root dir. ('C:\') or UNC root dir. ('\\server\share\') */
                 ((_tcslen( path ) == 3) || IsRootUNCName(path)) &&
                 (GetDriveType( path ) > 1) ) )
            {
                errno = ENOENT;
                _doserrno = E_nofile;
                return( -1 );
            }

            /*
             * Root directories (such as C:\ or \\server\share\ are fabricated.
             */

            findbuf.dwFileAttributes = A_D;
            findbuf.nFileSizeHigh = 0;
            findbuf.nFileSizeLow = 0;
            findbuf.cFileName[0] = _T('\0');

            buf->st_mtime = __loctotime_t(1980,1,1,0,0,0, -1);
            buf->st_atime = buf->st_mtime;
            buf->st_ctime = buf->st_mtime;
        }
        else {
            SYSTEMTIME SystemTime;
            FILETIME LocalFTime;

            if ( !FileTimeToLocalFileTime( &findbuf.ftLastWriteTime,
                                           &LocalFTime )            ||
                 !FileTimeToSystemTime( &LocalFTime, &SystemTime ) )
            {
                _dosmaperr( GetLastError() );
                FindClose( findhandle );
                return( -1 );
            }

            buf->st_mtime = __loctotime_t( SystemTime.wYear,
                                           SystemTime.wMonth,
                                           SystemTime.wDay,
                                           SystemTime.wHour,
                                           SystemTime.wMinute,
                                           SystemTime.wSecond,
                                           -1 );

            if ( findbuf.ftLastAccessTime.dwLowDateTime ||
                 findbuf.ftLastAccessTime.dwHighDateTime )
            {
                if ( !FileTimeToLocalFileTime( &findbuf.ftLastAccessTime,
                                               &LocalFTime )                ||
                     !FileTimeToSystemTime( &LocalFTime, &SystemTime ) )
                {
                    _dosmaperr( GetLastError() );
                    FindClose( findhandle );
                    return( -1 );
                }

                buf->st_atime = __loctotime_t( SystemTime.wYear,
                                               SystemTime.wMonth,
                                               SystemTime.wDay,
                                               SystemTime.wHour,
                                               SystemTime.wMinute,
                                               SystemTime.wSecond,
                                               -1 );
            } else
                buf->st_atime = buf->st_mtime ;

            if ( findbuf.ftCreationTime.dwLowDateTime ||
                 findbuf.ftCreationTime.dwHighDateTime )
            {
                if ( !FileTimeToLocalFileTime( &findbuf.ftCreationTime,
                                               &LocalFTime )                ||
                     !FileTimeToSystemTime( &LocalFTime, &SystemTime ) )
                {
                    _dosmaperr( GetLastError() );
                    FindClose( findhandle );
                    return( -1 );
                }

                buf->st_ctime = __loctotime_t( SystemTime.wYear,
                                               SystemTime.wMonth,
                                               SystemTime.wDay,
                                               SystemTime.wHour,
                                               SystemTime.wMinute,
                                               SystemTime.wSecond,
                                               -1 );
            } else
                buf->st_ctime = buf->st_mtime ;

            FindClose(findhandle);
        }

        /* Fill in buf */

        buf->st_mode = __tdtoxmode(findbuf.dwFileAttributes, name);
        buf->st_nlink = 1;

#ifdef _USE_INT64
        buf->st_size = ((__int64)(findbuf.nFileSizeHigh)) * (0x100000000i64) +
                        (__int64)(findbuf.nFileSizeLow);
#else  /* _USE_INT64 */
        buf->st_size = findbuf.nFileSizeLow;
#endif  /* _USE_INT64 */

        /* now set the common fields */

        buf->st_uid = buf->st_gid = buf->st_ino = 0;

        buf->st_rdev = buf->st_dev = (_dev_t)(drive - 1); /* A=0, B=1, etc. */

        return(0);
}


/*
 * IsRootUNCName - returns TRUE if the argument is a UNC name specifying
 *      a root share.  That is, if it is of the form \\server\share\.
 *      This routine will also return true if the argument is of the
 *      form \\server\share (no trailing slash) but Win32 currently
 *      does not like that form.
 *
 *      Forward slashes ('/') may be used instead of backslashes ('\').
 */

static int IsRootUNCName(const _TSCHAR *path)
{
        /*
         * If a root UNC name, path will start with 2 (but not 3) slashes
         */

        if ( ( _tcslen ( path ) >= 5 ) /* minimum string is "//x/y" */
             && ISSLASH(path[0]) && ISSLASH(path[1]))
        {
            const _TSCHAR * p = path + 2 ;

            /*
             * find the slash between the server name and share name
             */
            while ( * ++ p )
                if ( ISSLASH(*p) )
                    break ;

            if ( *p && p[1] )
            {
                /*
                 * is there a further slash?
                 */
                while ( * ++ p )
                    if ( ISSLASH(*p) )
                        break ;

                /*
                 * just final slash (or no final slash)
                 */
                if ( !*p || !p[1])
                    return 1;
            }
        }

        return 0 ;
}


#else  /* _MAC */


#include <cruntime.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <internal.h>
#include <stdlib.h>
#include <direct.h>
#include <macos\osutils.h>
#include <macos\files.h>
#include <macos\errors.h>

#ifdef _MBCS
#include <mbstring.h>
#define STRPBRK _mbspbrk
#else  /* _MBCS */
#define STRPBRK strpbrk
#endif  /* _MBCS */


unsigned short __cdecl _dtoxmode ( CInfoPBPtr pcinfoPB );

/***
*unsigned _dtoxmode(CInfoPBPtr) -
*
*Purpose:
*
*Entry:
*
*Exit:
*
*Exceptions:
*
*******************************************************************************/

unsigned short __cdecl _dtoxmode (
        CInfoPBPtr pcinfoPB
        )
{
        REG1 unsigned short uxmode;
        unsigned char dosmode;
        int fReadOnly;

        dosmode = pcinfoPB->hFileInfo.ioFlAttrib;

        /* file or dir */
        if (dosmode & 0x10)
        {
            uxmode = _S_IFDIR;
            fReadOnly = pcinfoPB->dirInfo.ioDrUsrWds.frFlags == fsRdPerm;
        }
        else
        {
            uxmode = _S_IFREG;
            fReadOnly = pcinfoPB->hFileInfo.ioFlFndrInfo.fdFlags == fsRdPerm;
            /* see if file appears to be executable - check 'APPL'? */
            if (pcinfoPB->hFileInfo.ioFlFndrInfo.fdType == 'APPL')
                uxmode |= _S_IEXEC;
        }


        /* If attribute byte has 0 bit set, file is locked, then read-only */

        uxmode |= (((dosmode & 0x01) || fReadOnly) ? _S_IREAD :
                  (_S_IREAD|_S_IWRITE));


        /* propagate user read/write/execute bits to group/other fields */

        uxmode |= (uxmode & 0700) >> 3;
        uxmode |= (uxmode & 0700) >> 6;

        return(uxmode);
}


/***
*int _stat(name, buf) - get file status info
*
*Purpose:
*       _stat obtains information about the file and stores it in the structure
*       pointed to by buf.
*
*Entry:
*       char *name -    pathname of given file
*       struct _stat *buffer - pointer to buffer to store info in
*
*Exit:
*       fills in structure pointed to by buffer
*       returns 0 if successful
*       returns -1 and sets errno if unsuccessful
*
*Exceptions:
*
*******************************************************************************/

int __cdecl _stat (
        REG1 const char *name,
        REG2 struct _stat *buf
        )
{
        CInfoPBRec cinfoPB;
        OSErr osErr;
        char szBuf[256];
        DateTimeRec dt;
        DateTimeRec dtc;
        HParamBlockRec hparamBlock;


        if (!*name)
        {
            errno = ENOENT;
            return -1;
        }

        strcpy(szBuf, name);
        cinfoPB.hFileInfo.ioNamePtr = _c2pstr(szBuf);
        cinfoPB.hFileInfo.ioFDirIndex = 0;
        cinfoPB.hFileInfo.ioVRefNum = 0;
        cinfoPB.hFileInfo.ioDirID = 0;

        osErr = PBGetCatInfoSync(&cinfoPB);
        switch (osErr)
        {
            case noErr:
                break;
            case bdNamErr:
            case dirNFErr:
            case extFSErr:
            case fnfErr:
            case ioErr:
            case nsvErr:
            case paramErr:
                errno = ENOENT;
                return -1;
            default:
                return -1;
        }


        /* file or dir ? */
        if (cinfoPB.hFileInfo.ioFlAttrib & 0x10)
        {   /*dir*/
            Secs2Date(cinfoPB.dirInfo.ioDrMdDat, &dt);
            Secs2Date(cinfoPB.dirInfo.ioDrCrDat, &dtc);
            buf->st_size = 0;
        }
        else
        {   /*file*/
            Secs2Date(cinfoPB.hFileInfo.ioFlMdDat, &dt);
            Secs2Date(cinfoPB.hFileInfo.ioFlCrDat, &dtc);
            buf->st_size = cinfoPB.hFileInfo.ioFlLgLen +
                           cinfoPB.hFileInfo.ioFlRLgLen;
        }

        buf->st_mtime = _gmtotime_t( dt.year,
                                     dt.month,
                                     dt.day,
                                     dt.hour,
                                     dt.minute,
                                     dt.second );

        buf->st_atime = buf->st_mtime;
        buf->st_ctime = _gmtotime_t( dtc.year,
                                     dtc.month,
                                     dtc.day,
                                     dtc.hour,
                                     dtc.minute,
                                     dtc.second );

        buf->st_nlink = 1;
        buf->st_uid = buf->st_gid = buf->st_ino = 0;

        buf->st_mode = _dtoxmode(&cinfoPB);

        /* get volume number and map it to st_dev/rdev */
        hparamBlock.volumeParam.ioNamePtr = szBuf;
        hparamBlock.volumeParam.ioVRefNum = 0;
        hparamBlock.volumeParam.ioVolIndex = 0;
        osErr = PBHGetVInfoSync(&hparamBlock);
        if (osErr != noErr)
            return -1;

        buf->st_rdev = buf->st_dev = hparamBlock.volumeParam.ioVRefNum;

        return(0);
}

#endif  /* _MAC */
