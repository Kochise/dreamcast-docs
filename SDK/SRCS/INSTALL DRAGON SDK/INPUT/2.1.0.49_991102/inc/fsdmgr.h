/*++

Copyright (c) 1997-1998  Microsoft Corporation

Module Name:

    fsdmgr.h

Abstract:

    This file contains external definitions for the WinCE FSD Manager (FSDMGR.DLL).

Revision History:

--*/

#ifndef FSDMGR_H
#define FSDMGR_H

#include <extfile.h>            // for definitions such as SHELLFILECHANGEFUNC_t


#ifndef HDSK
#define HDSK    DWORD
#endif

#ifndef HVOL
#define HVOL    DWORD
#endif

#ifndef PVOLUME
#define PVOLUME DWORD
#endif

#ifndef PFILE
#define PFILE   DWORD
#endif

#ifndef PSEARCH
#define PSEARCH DWORD
#endif


/*  FSD_DISK_INFO structure (returned by FSDMGR_GetDiskInfo):
 */
#define FDI_MBR             0x00000001  // device type has/needs an MBR
#define FDI_CHS_UNCERTAIN   0x00000002  // driver generated CHS values are suspect
#define FDI_UNFORMATTED     0x00000004  // low level format (DISK_IOCTL_FORMAT_MEDIA) needed
#define FDI_PAGEABLE        0x00000008  // device can be used for demand paging
#define FDI_READONLY        0x00000010  // device is read-only
#define FDI_RESERVED        0xffffffe0

typedef struct _FSD_DISK_INFO {
    DWORD   cSectors;
    DWORD   cbSector;
    DWORD   cCylinders;
    DWORD   cHeadsPerCylinder;
    DWORD   cSectorsPerTrack;
    DWORD   dwFlags;            // see FDI_* above
} FSD_DISK_INFO, *PFDI;


/*  FSD_BUFFER_INFO (used in FSD_SCATTER_GATHER_INFO):
 */
typedef struct _FSD_BUFFER_INFO {
	PBYTE   pBuffer;            // pointer to buffer
	DWORD   cbBuffer;           // size of buffer, in bytes
} FSD_BUFFER_INFO, *PFBI;


/*  FSD_SCATTER_GATHER_INFO (used by FSDMGR_ReadDiskEx and FSDMGR_WriteDiskEx):
 */
typedef DWORD (*PFNFSG)(struct _FSD_SCATTER_GATHER_INFO *pfsgi, struct _FSD_SCATTER_GATHER_RESULTS *pfsgr);

typedef struct _FSD_SCATTER_GATHER_INFO {
    DWORD   dwFlags;            // reserved (must be zero)
    DWORD   idDsk;              // disk ID (as passed to XXX_MountDisk)
    DWORD   dwSector;           // starting sector #
    DWORD   cSectors;           // number of sectors to transfer
    PFDI    pfdi;               // address of FSD_DISK_INFO
    DWORD   cfbi;               // count of FSD_BUFFER_INFO structures (can be zero)
    PFBI    pfbi;               // pointer to zero or more FSD_BUFFER_INFO structures
    PFNFSG  pfnCallBack;        // callback function
} FSD_SCATTER_GATHER_INFO, *PFSGI;


/*  FSD_SCATTER_GATHER_RESULTS (returned by FSDMGR_ReadWriteDiskEx and FSDMGR_WriteDiskEx):
 */
typedef struct _FSD_SCATTER_GATHER_RESULTS {
    DWORD   dwFlags;            // reserved
    DWORD   cSectorsTransferred;// total sectors transferred
} FSD_SCATTER_GATHER_RESULTS, *PFSGR;


/*  Interfaces exported by FSDMGR.DLL to FSDs
 */
DWORD   FSDMGR_GetDiskInfo(HDSK hDsk, PFDI pfdi);
DWORD   FSDMGR_ReadDisk(HDSK hDsk, DWORD dwSector, DWORD cSectors, PBYTE pBuffer, DWORD cbBuffer);
DWORD   FSDMGR_WriteDisk(HDSK hDsk, DWORD dwSector, DWORD cSectors, PBYTE pBuffer, DWORD cbBuffer);
DWORD   FSDMGR_ReadDiskEx(PFSGI pfsgi, PFSGR pfsgr);
DWORD   FSDMGR_WriteDiskEx(PFSGI pfsgi, PFSGR pfsgr);
HVOL    FSDMGR_RegisterVolume(HDSK hDsk, PWSTR pwsName, PVOLUME pVolume);
int     FSDMGR_GetVolumeName(HVOL hVol, PWSTR pwsName, int cchMax);
void    FSDMGR_DeregisterVolume(HVOL hVol);
HANDLE  FSDMGR_CreateFileHandle(HVOL hVol, HANDLE hProc, PFILE pFile);
HANDLE  FSDMGR_CreateSearchHandle(HVOL hVol, HANDLE hProc, PSEARCH pSearch);

#endif /* FSDMGR_H */


#ifdef FSDAPI

#define DECLAPI(ret,prefix,func)    ret prefix##_##func
#define DECLFSDAPI(ret,prefix,func) DECLAPI(ret,prefix,func)


/*  Interfaces imported by FSDMGR.DLL from FSDs for mount support
 *
 *  Note that the XXX_MountDisk interface must also be exported as
 *  "FSD_MountDisk", since DEVICE.EXE specifically looks for that export
 *  when determining how to load the FSD (ie, using FSDMGR.DLL or
 *  stand-alone).
 *
 *  This requirement is easily satisfied in the DEF file for the FSD;
 *  for example, for an FSD named FATFSD.DLL, the DEF file would contain:
 *
 *      EXPORTS
 *          FATFSD_MountDisk
 *          FATFSD_UnmountDisk
 *          FSD_MountDisk=FATFSD_MountDisk
 *          FSD_UnmountDisk=FATFSD_UnmountDisk
 *          ...
 */

DECLFSDAPI(BOOL, FSDAPI, MountDisk(HDSK hdsk));
DECLFSDAPI(BOOL, FSDAPI, UnmountDisk(HDSK hdsk));


/*  Interfaces imported by FSDMGR.DLL from FSDs for application support
 *
 *  Add a #define for FSDAPI before including this file, so that the following
 *  prototypes match the interface names your FSD must export.  For example,
 *  an FSD named FATFSD.DLL would want to include the following lines in its
 *  source code:
 *
 *      #define FSDAPI FATFSD
 *      #include <fsdmgr.h>
 *
 *  since FSDMGR.DLL will expect to find exports named "FATFSD_CreateDirectoryW",
 *  "FATFSD_RemoveDirectoryW", etc, if it is asked to load an FSD named FATFSD.DLL.
 */

DECLFSDAPI(BOOL,  FSDAPI, CloseVolume(PVOLUME pVolume));
DECLFSDAPI(BOOL,  FSDAPI, CreateDirectoryW(PVOLUME pVolume, PCWSTR pwsPathName, PSECURITY_ATTRIBUTES pSecurityAttributes));
DECLFSDAPI(BOOL,  FSDAPI, RemoveDirectoryW(PVOLUME pVolume, PCWSTR pwsPathName));
DECLFSDAPI(DWORD, FSDAPI, GetFileAttributesW(PVOLUME pVolume, PCWSTR pwsFileName));
DECLFSDAPI(BOOL,  FSDAPI, SetFileAttributesW(PVOLUME pVolume, PCWSTR pwsFileName, DWORD dwAttributes));
DECLFSDAPI(BOOL,  FSDAPI, DeleteFileW(PVOLUME pVolume, PCWSTR pwsFileName));
DECLFSDAPI(BOOL,  FSDAPI, MoveFileW(PVOLUME pVolume, PCWSTR pwsOldFileName, PCWSTR pwsNewFileName));
DECLFSDAPI(BOOL,  FSDAPI, DeleteAndRenameFileW(PVOLUME pVolume, PCWSTR pwsOldFileName, PCWSTR pwsNewFileName));
DECLFSDAPI(BOOL,  FSDAPI, GetDiskFreeSpaceW(PVOLUME pVolume, PCWSTR pwsPathName, PDWORD pSectorsPerCluster, PDWORD pBytesPerSector, PDWORD pFreeClusters, PDWORD pClusters));
DECLFSDAPI(void,  FSDAPI, Notify(PVOLUME pVolume, DWORD dwFlags));
DECLFSDAPI(BOOL,  FSDAPI, RegisterFileSystemFunction(PVOLUME pVolume, SHELLFILECHANGEFUNC_t pfn));
DECLFSDAPI(HANDLE,FSDAPI, FindFirstFileW(PVOLUME pVolume, HANDLE hProc, PCWSTR pwsFileSpec, PWIN32_FIND_DATAW pfd));
DECLFSDAPI(BOOL,  FSDAPI, FindNextFileW(PSEARCH pSearch, PWIN32_FIND_DATAW pfd));
DECLFSDAPI(BOOL,  FSDAPI, FindClose(PSEARCH pSearch));
DECLFSDAPI(HANDLE,FSDAPI, CreateFileW(PVOLUME pVolume, HANDLE hProc, PCWSTR pwsFileName, DWORD dwAccess, DWORD dwShareMode, PSECURITY_ATTRIBUTES pSecurityAttributes, DWORD dwCreate, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile));
DECLFSDAPI(BOOL,  FSDAPI, ReadFile(PFILE pFile, PVOID pBuffer, DWORD cbRead, PDWORD pcbRead, OVERLAPPED *pOverlapped));
DECLFSDAPI(BOOL,  FSDAPI, ReadFileWithSeek(PFILE pFile, PVOID pBuffer, DWORD cbRead, PDWORD pcbRead, OVERLAPPED *pOverlapped, DWORD dwLowOffset, DWORD dwHighOffset));
DECLFSDAPI(BOOL,  FSDAPI, WriteFile(PFILE pFile, PCVOID pBuffer, DWORD cbWrite, PDWORD pcbWritten, OVERLAPPED *pOverlapped));
DECLFSDAPI(BOOL,  FSDAPI, WriteFileWithSeek(PFILE pFile, PCVOID pBuffer, DWORD cbWrite, PDWORD pcbWritten, OVERLAPPED *pOverlapped, DWORD dwLowOffset, DWORD dwHighOffset));
DECLFSDAPI(DWORD, FSDAPI, SetFilePointer(PFILE pFile, LONG lDistanceToMove, PLONG pDistanceToMoveHigh, DWORD dwMoveMethod));
DECLFSDAPI(DWORD, FSDAPI, GetFileSize(PFILE pFile, PDWORD pFileSizeHigh));
DECLFSDAPI(BOOL,  FSDAPI, GetFileInformationByHandle(PFILE pFile, PBY_HANDLE_FILE_INFORMATION pFileInfo));
DECLFSDAPI(BOOL,  FSDAPI, FlushFileBuffers(PFILE pFile));
DECLFSDAPI(BOOL,  FSDAPI, GetFileTime(PFILE pFile, FILETIME *pCreation, FILETIME *pLastAccess, FILETIME *pLastWrite));
DECLFSDAPI(BOOL,  FSDAPI, SetFileTime(PFILE pFile, CONST FILETIME *pCreation, CONST FILETIME *pLastAccess, CONST FILETIME *pLastWrite));
DECLFSDAPI(BOOL,  FSDAPI, SetEndOfFile(PFILE pFile));
DECLFSDAPI(BOOL,  FSDAPI, DeviceIoControl(PFILE pFile, DWORD dwIoControlCode, PVOID pInBuf, DWORD nInBufSize, PVOID pOutBuf, DWORD nOutBufSize, PDWORD pBytesReturned, OVERLAPPED *pOverlapped));
DECLFSDAPI(BOOL,  FSDAPI, CloseFile(PFILE pFile));

#endif  // FSDAPI
