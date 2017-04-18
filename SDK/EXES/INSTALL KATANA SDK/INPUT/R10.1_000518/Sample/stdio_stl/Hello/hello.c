/*
 * File for Clibrary server functions
 *
 * Copyright (c) 1995 Cross Products Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the Cross Products Ltd, 23 The Calls, Leeds, LS2 7EH UK.  The
 * name of the company may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *
 * File Server Sample Program.
 * ===========================
 *
 * Demonstrates the operation of the low level fileserver commands
 * described in "usrsnasm.h".
 *
 * Gary Ellison.
 */


#include <errno.h>
#include <sn_fcntl.h>
#include <usrsnasm.h>

/*
 * Macro Redefinition of _ASSERT to ASSERT. This is performed to cause the
 * compiler to insert at least one opcode after the jsr _ASSERT has returned
 * it also permits the ASSERT code to be included / removed based on a
 * compiler define.
 */

#ifdef _DEBUG_BUILD_
	#define ASSERT(X) while(_ASSERT(X)) { ; }
#else
	#define ASSERT(X)
#endif /* _DEBUG_BUILD_ */


#define BUFFER_SIZE				(32 * 1024)
#define NUMBER_OF_TRANSFERS		150

char acOutBuffer[BUFFER_SIZE];
char acInBuffer[BUFFER_SIZE];

char *pTestFilename1 = "Output1.jnk";
char *pTestFilename2 = "Output2.jnk";


static char *ERRNO_NAME[43] = {
	"SNASM_NOERROR",
	"SNASM_EPERM",
	"SNASM_ENOENT",
	"SNASM_ESRCH",
	"SNASM_EINTR",
	"SNASM_EIO",
	"SNASM_ENXIO",
	"SNASM_E2BIG",
	"SNASM_ENOEXEC",
	"SNASM_EBADF",
	"SNASM_ECHILD",
	"SNASM_EAGAIN",
	"SNASM_ENOMEM",
	"SNASM_EACCESS",
	"SNASM_EFAULT",
	"SNASM_?",
	"SNASM_EBUSY",
	"SNASM_EEXIST",
	"SNASM_EXDEV",
	"SNASM_ENODEV",
	"SNASM_ENOTDIR",
	"SNASM_EISDIR",
	"SNASM_EINVAL",
	"SNASM_ENFILE",
	"SNASM_EMFILE",
	"SNASM_ENOTTY",
	"SNASM_?",
	"SNASM_EFBIG",
	"SNASM_ENOSPC",
	"SNASM_ESPIPE",
	"SNASM_EROFS",
	"SNASM_EMLINK",
	"SNASM_EPIPE",
	"SNASM_EDOM",
	"SNASM_ERANGE",
	"SNASM_?",
	"SNASM_EDEADLK",
	"SNASM_?",
	"SNASM_ENAMETOOLONG",
	"SNASM_ENOLCK",
	"SNASM_ENOSYS",
	"SNASM_ENOTEMPTY",
	"SNASM_EILSEQ"
	};

/*
 * Dump the errno info
 */
void DisplayErrno(void)
{
	if ((errno >= 0) &&
		(errno <= 42))
		debug_printf("     The errno is %s", ERRNO_NAME[errno]);
	else
		debug_printf("     The errno is %d", errno);
}


/*
 *  Test the low level Read functions
 */
void ReadTest(char *pFilename)
{
	int nFileID;
	int nCnt;
	int nBytesRead = 0;

	/* File Open / Read test */
	nFileID = debug_open(pFilename, SNASM_O_RDONLY);
	ASSERT(nFileID != -1);

	if (nFileID != -1)
	{
		debug_printf("Start Read of data");

		for (nCnt = 0; nCnt < NUMBER_OF_TRANSFERS; nCnt++)
			nBytesRead += debug_read(nFileID, acInBuffer, BUFFER_SIZE);

		debug_printf("Completed Read of data (%d bytes read)", nBytesRead);
		debug_close(nFileID);
	}
}


/*
 *  Test the low level Write functions
 */
void WriteTest(char *pFilename)
{
	int nFileID;
	int nCnt;
	int nbyteswritten = 0;

	/* File Open / Write test */
	nFileID = debug_open(pFilename,
				SNASM_O_WRONLY | SNASM_O_CREAT | SNASM_O_TRUNC,
                SNASM_S_IREAD | SNASM_S_IWRITE);
	ASSERT(nFileID != -1);

	if (nFileID != -1)
	{
		debug_printf("Start Write of data    ");

		for (nCnt = 0; nCnt < NUMBER_OF_TRANSFERS; nCnt++)
			nbyteswritten += debug_write(nFileID, acOutBuffer, BUFFER_SIZE);

		debug_printf("Completed Write of data (%d bytes written)", nbyteswritten);
		debug_close(nFileID);
	}
}


/*
 *  Test the low level Seek functions
 */
void SeekTest(char *pFilename)
{
	int nFileID, nPos;

	nFileID = debug_open(pFilename, SNASM_O_RDONLY);
	ASSERT(nFileID != -1);

	if (nFileID != -1)
	{
		debug_printf("Start Seek of data");

		nPos = debug_lseek(nFileID, 6, SNASM_SEEK_SET);
		debug_read(nFileID, acInBuffer, 10);
		debug_write(SNASM_STDOUT, acInBuffer, 10);

		nPos = debug_lseek(nFileID, 6, SNASM_SEEK_CUR);
		debug_read(nFileID, acInBuffer, 10);
		debug_write(SNASM_STDOUT, acInBuffer, 10);

		nPos = debug_lseek(nFileID, -10, SNASM_SEEK_END);
		debug_read(nFileID, acInBuffer, 10);
		debug_write(SNASM_STDOUT, acInBuffer, 10);

		debug_printf("Completed Seek of data");
		debug_close(nFileID);
	}
}


/*
 * Test each of the new Directory commands
 */
void DirectoryTest(void)
{
	char *result, cwd_buffer[256];
	int chdir_res, mkdir_res, rmdir_res;

	debug_printf("Start Directory Test");

	/* Test _getcwd() */
	debug_printf("  Test _getcwd()");
	result = debug_getcwd(cwd_buffer, 256);

	/* Test _chdir() */
	debug_printf("  Test _chdir()");
	chdir_res = debug_chdir("C:\\temp");
	ASSERT(chdir_res == 0);

	if (chdir_res == 0)
	{
		/* Test _mkdir() */
		debug_printf("  Test _mkdir()");
		mkdir_res = debug_mkdir("new_dir");
		/* This will assert if the directory already exists */
		ASSERT(mkdir_res == 0);

		if (mkdir_res == 0)
		{
			/* Test _rmdir() */
			debug_printf("  Test _rmdir()");
			rmdir_res = debug_rmdir("new_dir");
			ASSERT(rmdir_res == 0);
		}
		else
			DisplayErrno();
	}

	debug_printf("Completed Directory Test");
}



/*
 * List the contents of a specific directory
 */
void FindTest(void)
{
	struct SNASM_finddata_t FileInfo;
	int nHandle, nIsMore, nClosedHandle;

	debug_printf("Start FindTest");

	debug_printf("  Test _findfirst() & _findnext()");
	nHandle = debug_findfirst("*", &FileInfo);
	ASSERT(nHandle != -1);

	if (nHandle != -1)
	{	/* We found one look for more */
		debug_printf("  Attr    Size   File Name");
		do {
			debug_printf("   %02x  %8d  %s",FileInfo.m_ulAttributes,FileInfo.m_ulSize, FileInfo.m_szFilename);
			nIsMore = debug_findnext(nHandle, &FileInfo);
		} 	while (nIsMore != -1);

		debug_printf("  Test _findclose()");
		nClosedHandle = debug_findclose(nHandle);
		ASSERT(nClosedHandle == 0);
	}

	debug_printf("Stop FindTest");
}

/*
 * Run a script
 */
void ScriptTest(void)
{
	debug_runscript("Scripts\\Display.js", SCRIPTTYPE_JSCRIPT);
}


/*
 *
 */
void InitialiseOutBuffer(void)
{
	int nCnt;
	/* initialise the buffer */
	for (nCnt = 0; nCnt < BUFFER_SIZE; nCnt++)
	{
		acOutBuffer[nCnt] = (char)('0' + nCnt%10);
	}
}


/*
 * Main test function
 */
main()
{
	char ReadBuffer[256];
	int nBytesRead = 0;

	InitialiseOutBuffer();

	/* Test the ASSERT MACRO command (This will always go off) */
	ASSERT(0);

	/* Check debug_printf & default channels (SNASM_STDOUT / SNASM_STDERR) */
	debug_printf("debug_printf: Start of Test");
	debug_write(SNASM_STDOUT, "Test Data to stdout", 19);
	debug_write(SNASM_STDERR, "Test Data to stderr", 19);
	nBytesRead = debug_read(SNASM_STDIN,  ReadBuffer, 256);

	/* Change / create/ delete a directory */
	DirectoryTest();

	/* List the contents of a directory */
	FindTest();

	/* Run a script and see what happens */
	ScriptTest();

	/* File Open / Write test */
	WriteTest(pTestFilename1);

	/* File Open / Read test */
	ReadTest(pTestFilename1);

	/* File Open / Seek test */
	SeekTest(pTestFilename1);

	/* Loop Forever */
	for ( ; ; ) ;
}
