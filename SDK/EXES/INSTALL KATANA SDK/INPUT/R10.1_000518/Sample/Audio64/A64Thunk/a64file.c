//-----------------------------------------------------------------------------
//
//	FILE:		a64file.c
//
//	DESC:		Audio64 hooks for porting G2 DMA function support.
//
//				The Audio64 library contains Audio64 hook functions that map
//				(thunk) to appropriate functions in the Shinobi library. If
//				needed, these may be overridden by explicitly including this
//				module in your object file list and substituting alternate
//				support.
//
//				NOTE:	The public/exported function names MUST be the only
//						globally visible symbols.
//
//	HISTORY:	2000.01.xx	Reworked samples/boilerplates for R10 release.
//
//-----------------------------------------------------------------------------
//	COPYRIGHT (C) SEGA OF AMERICA DREAMCAST, INC. 1998, 1999, 2000
//	All rights reserved.
//
//	Information and source code samples contained herein are provided "as-is",
//	without representations or warranties, and are subject to change without
//	notice.
//
//	SEGA OF AMERICA DREAMCAST, INC. cannot support modifications or derivative
//	works created from the sample source code provided. Developers may use,
//	reproduce, and modify portions or entire sections of the sample source
//	code for the purposes of creating Dreamcast applications.
//
//	Sample source code contained herein may not be appropriate for use under
//	all circumstances. Please consult Developer documentation provided along
//	with your Dreamcast unit for additional information and suggestions.
//-----------------------------------------------------------------------------

#include <ac.h>
#include <a64thunk.h>
#include <am.h>

#if defined(AUDIO64_THUNKS_SHINOBI)
#include <shinobi.h>
#endif

#define _ARG_CHECKING_
#define STATIC static
//#define STATIC

//-----------------------------------------------------------------------------

#if defined(AUDIO64_THUNKS_SHINOBI)

// A64_FILE_MAX_HANDLES must be sync'd with FILES (sbinit.c)
#define A64_FILE_MAX_HANDLES		8
#define A64_FILE_VBLANK_ID 			0xc0c0cafe
#define A64_FILE_VBLANK_PRIORITY 	0x7f

struct
{
	GDFS fileHandleArray[A64_FILE_MAX_HANDLES];
	KTU32 idVblankHandler;
	volatile KTBOOL newVblank;
} a64FileEnv;

#else

	//	Provide an alternate thunking here.

#endif

//-----------------------------------------------------------------------------

STATIC KTBOOL _a64FileAllocateHandle(KTU32 *fd);
STATIC void _a64FileFreeHandle(KTU32 *fd);
STATIC KTBOOL _a64FileValidHandle(KTU32 fd);
STATIC void _a64FileVblankHandler(void *arg);
STATIC void _a64FileVblankWait(void);

//-----------------------------------------------------------------------------

KTBOOL a64FileInit(void)
{
#if defined(AUDIO64_THUNKS_SHINOBI)

	memset(&a64FileEnv, 0, sizeof(a64FileEnv));

	a64FileEnv.idVblankHandler = a64ChainAddHandler(
												AC_INT_AICA_POLL_CHAIN_ID,
												_a64FileVblankHandler,
												A64_FILE_VBLANK_PRIORITY,
												(void*)A64_FILE_VBLANK_ID);
	return (!!a64FileEnv.idVblankHandler);

#else

	//	Provide an alternate thunking here.

#endif
}

//-----------------------------------------------------------------------------

KTBOOL a64FileOpen(KTSTRING fileName, KTU32 *fd)
{
#if defined(AUDIO64_THUNKS_SHINOBI)

	KTU32 descriptor;

#if defined(_ARG_CHECKING_)

	if (!fileName || !fd)
	{
		acErrorSet(AC_NULL_PARAMETER, "a64FileOpen - fileName/fd is NULL");
		return (KTFALSE);
	}

	// ----- end parameter testing -----
#endif

	if (!_a64FileAllocateHandle(&descriptor))
	{
		acErrorSet(AC_NO_FREE_FILE_HANDLE,
						"a64FileOpen - No more free file handles");
		return (KTFALSE);
	}

	a64FileEnv.fileHandleArray[descriptor] = gdFsOpen(fileName, KTNULL);

	if (!a64FileEnv.fileHandleArray[descriptor])
	{
		_a64FileFreeHandle(&descriptor);

		acErrorSet(AC_OPEN_FAIL, "a64FileOpen - file not found");
		return (KTFALSE);
	}

	*fd = descriptor;
				
	return (KTTRUE);

#else

	//	Provide an alternate thunking here.

#endif
}

//-----------------------------------------------------------------------------

KTBOOL a64FileClose(KTU32 *fd)
{
#if defined(AUDIO64_THUNKS_SHINOBI)

#if defined(_ARG_CHECKING_)
	// ----- end parameter testing -----
#endif

	if (_a64FileValidHandle(*fd) && a64FileEnv.fileHandleArray[*fd])
	{
		A64_FILE_STATUS status;
		// drain the file stream before closing
		while ((status = a64FileGetStatus(*fd)) != A64_FILE_READ_COMPLETE)
		{
			if (status == A64_FILE_READ_ERROR)
			{
				break;
			}
		}

		(void)gdFsClose(a64FileEnv.fileHandleArray[*fd]);

		_a64FileFreeHandle(fd);

		return (KTTRUE);
	}
	else
	{
		acErrorSet(AC_INVALID_FILE_HANDLE, "a64FileClose - fd is invalid");
		return (KTFALSE);
	}

#else

	//	Provide an alternate thunking here.

#endif
}

//-----------------------------------------------------------------------------

KTBOOL a64FileRead(KTU32 fd, KTU8 *buffer, KTU32 size)
{
#if defined(AUDIO64_THUNKS_SHINOBI)

#if defined(_ARG_CHECKING_)

	if (!buffer)
	{
		acErrorSet(AC_NULL_PARAMETER, "a64FileRead - buffer is NULL");
		return (KTFALSE);
	}

	if (!IS_ALIGNED_32(buffer))
	{
		acErrorSet(AC_NOT_32BYTE_ALIGNED,
					"a64FileRead - buffer is not 32 byte aligned");
		return (KTFALSE);
	}

	if (acSystemIsSoundMemory((KTU32*)buffer))
	{
		amErrorSet(AM_CANT_LOAD_INTO_AICA_MEMORY,
						"a64FileRead - buffer must be in SH4 memory");
		return (KTFALSE);
	}

	if (!size)
	{
		acErrorSet(AC_0_SIZE_PARAMETER, "a64FileRead - size is 0");
		return (KTFALSE);
	}

	// ----- end parameter testing -----
#endif

	if (_a64FileValidHandle(fd) && a64FileEnv.fileHandleArray[fd])
	{
		// even number of sectors
		if (gdFsRead(a64FileEnv.fileHandleArray[fd],
										(size / AM_FILE_BLOCK_SIZE), buffer))
		{
			acErrorSet(AC_READ_FAIL, "a64FileRead - gdFsRead failed");
			return (KTFALSE);
		}

		return (KTTRUE);
	}
	else
	{
		acErrorSet(AC_INVALID_FILE_HANDLE, "a64FileRead - fd is invalid");
		return (KTFALSE);
	}

#else

	//	Provide an alternate thunking here.

#endif
}

//-----------------------------------------------------------------------------

KTBOOL a64FileReadAsync(KTU32 fd, KTU8 *buffer, KTU32 size)
{
#if defined(AUDIO64_THUNKS_SHINOBI)

#if defined(_ARG_CHECKING_)

	if (!buffer)
	{
		acErrorSet(AC_NULL_PARAMETER, "a64FileReadAsync - buffer is NULL");
		return (KTFALSE);
	}

	if (!IS_ALIGNED_32(buffer))
	{
		acErrorSet(AC_NOT_32BYTE_ALIGNED,
					"a64FileReadAsync - buffer is not 32 byte aligned");
		return (KTFALSE);
	}

	if (acSystemIsSoundMemory((KTU32*)buffer))
	{
		amErrorSet(AM_CANT_LOAD_INTO_AICA_MEMORY,
						"a64FileReadAsync - buffer must be in SH4 memory");
		return (KTFALSE);
	}

	if (!size)
	{
		acErrorSet(AC_0_SIZE_PARAMETER, "a64FileReadAsync - size is 0");
		return (KTFALSE);
	}

	// ----- end parameter testing -----
#endif

	if (_a64FileValidHandle(fd) && a64FileEnv.fileHandleArray[fd])
	{
		if (a64FileEnv.newVblank)
		{
			KTS32 nSectors = (size / AM_FILE_BLOCK_SIZE);
			// even number of sectors
			if (gdFsReqRd32(a64FileEnv.fileHandleArray[fd],
												nSectors, buffer) != nSectors)
			{
				acErrorSet(AC_READ_FAIL,
								"a64FileReadAsync - gdFsReqRd32 failed");
				return (KTFALSE);
			}

			a64FileEnv.newVblank = KTFALSE;

			return (KTTRUE);
		}

		return (KTFALSE);
	}
	else
	{
		acErrorSet(AC_INVALID_FILE_HANDLE, "a64FileReadAsync - fd is invalid");
		return (KTFALSE);
	}

#else

	//	Provide an alternate thunking here.

#endif
}

//-----------------------------------------------------------------------------

KTBOOL a64FileGetSize(KTSTRING fileName, KTU32 *size)
{
#if defined(AUDIO64_THUNKS_SHINOBI)

	GDFS fp = KTNULL;
	Sint32 fileSize = 0;

#if defined(_ARG_CHECKING_)

	if (!fileName || !size)
	{
		acErrorSet(AC_NULL_PARAMETER, "a64FileGetSize - fileName/size is NULL");
		return (KTFALSE);
	}

	// ----- end parameter testing -----
#endif

	fp = gdFsOpen(fileName, NULL);
	if (!fp)
	{
		acErrorSet(AC_OPEN_FAIL,
						"a64FileGetSize - gdFsOpen fail (file not found)");
		return (KTFALSE);
	}

	if (!gdFsGetFileSize(fp, &fileSize))
	{
		acErrorSet(AC_GET_SIZE_FAIL, "a64FileGetSize - gdFsGetFileSize fail");
		gdFsClose(fp);
		return (KTFALSE);
	}
		
	(void)gdFsClose(fp);

	*size = fileSize;

	return (KTTRUE);

#else

	//	Provide an alternate thunking here.

#endif
}
 
//-----------------------------------------------------------------------------

KTBOOL a64FileRewind(KTU32 fd)
{
#if defined(AUDIO64_THUNKS_SHINOBI)

#if defined(_ARG_CHECKING_)
	// ----- end parameter testing -----
#endif

	if (_a64FileValidHandle(fd) && a64FileEnv.fileHandleArray[fd])
	{
		if (gdFsSeek(a64FileEnv.fileHandleArray[fd], 0, GDD_SEEK_SET))
		{
			acErrorSet(AC_SEEK_FAIL, "a64FileRewind - gdFsSeek fail");
			return (KTFALSE);
		}

		return (KTTRUE);
	}
	else
	{
		acErrorSet(AC_INVALID_FILE_HANDLE, "a64FileRewind - fd is invalid");
		return (KTFALSE);
	}

#else

	//	Provide an alternate thunking here.

#endif
}

//-----------------------------------------------------------------------------

KTBOOL a64FileLoad(KTSTRING fileName, KTU32 *buffer, KTU32 size)
{
#if defined(AUDIO64_THUNKS_SHINOBI)

	KTU32 fileSize = 0;
	KTU32 fd = 0;

#if defined(_ARG_CHECKING_)

	if (!fileName || !buffer)
	{
		acErrorSet(AC_NULL_PARAMETER, "a64FileLoad - fileName/buffer is NULL");
		return (KTFALSE);
	}

	// ----- end parameter testing -----
#endif

	if (a64FileOpen(fileName, &fd)
	&& a64FileRead(fd, (KTU8*)buffer, size)
	&& a64FileClose(&fd))
	{
		return (KTTRUE);
	}

	(void)a64FileClose(&fd);

	return (KTFALSE);

#else

	//	Provide an alternate thunking here.

#endif
}
 
//-----------------------------------------------------------------------------

A64_FILE_STATUS a64FileGetStatus(KTU32 fd)
{
#if defined(AUDIO64_THUNKS_SHINOBI)

#if defined(_ARG_CHECKING_)
	// ----- end parameter testing -----
#endif

	if (_a64FileValidHandle(fd) && a64FileEnv.fileHandleArray[fd])
	{
		if (a64FileEnv.newVblank)
		{
			a64FileEnv.newVblank = KTFALSE;
			if (!gdFsGetWorkHn())
			{
				switch (gdFsGetStat(a64FileEnv.fileHandleArray[fd]))
				{
					case GDD_STAT_IDLE:
					case GDD_STAT_COMPLETE:

						return (A64_FILE_READ_COMPLETE);

					case GDD_STAT_READ:

						return (A64_FILE_READ_PENDING);

					case GDD_STAT_ERR:
					default:

						return (A64_FILE_READ_ERROR);
				}
			}
		}
		return (A64_FILE_READ_BUSY);
	}
	else
	{
		acErrorSet(AC_INVALID_FILE_HANDLE, "a64FileGetStatus - fd is invalid");
		return (A64_FILE_READ_ERROR);
	}

#else

	//	Provide an alternate thunking here.

#endif
}

//=============================================================================

STATIC KTBOOL _a64FileAllocateHandle(KTU32 *fd)
{
#if defined(AUDIO64_THUNKS_SHINOBI)

	KTU32 i = 0;
	for (i = 0; i < A64_FILE_MAX_HANDLES; i++)
	{
		if (!a64FileEnv.fileHandleArray[i])
		{
			*fd = i;
			return (KTTRUE);
		}
	}
	return (KTFALSE);

#else

	//	Provide an alternate thunking here.

#endif
}

//-----------------------------------------------------------------------------

STATIC void _a64FileFreeHandle(KTU32 *fd)
{
#if defined(AUDIO64_THUNKS_SHINOBI)

	if (_a64FileValidHandle(*fd))
	{
		a64FileEnv.fileHandleArray[*fd] = KTNULL;
		// invalidate caller's copy of file handle
		*fd = AM_UNINITIALIZED_FILE_DESCRIPTOR;
	}

#else

	//	Provide an alternate thunking here.

#endif
}

//-----------------------------------------------------------------------------

STATIC KTBOOL _a64FileValidHandle(KTU32 fd)
{
#if defined(AUDIO64_THUNKS_SHINOBI)

	return (fd < A64_FILE_MAX_HANDLES);

#else

	//	Provide an alternate thunking here.

#endif
}

//=============================================================================

#if defined(AUDIO64_THUNKS_SHINOBI)

STATIC void _a64FileVblankHandler(void *arg)
{
	if (arg == (void*)A64_FILE_VBLANK_ID)
	{
		// accommodate shinobi single gdfs call per vblank
		a64FileEnv.newVblank = KTTRUE;
	}
}

#endif

//-----------------------------------------------------------------------------

#if defined(AUDIO64_THUNKS_SHINOBI)

STATIC void _a64FileVblankWait(void)
{
	while (!a64FileEnv.newVblank)
	{
		// something to keep optimizers in check
		if (!a64FileEnv.idVblankHandler)
		{
			break;
		}
	}
}

#endif
