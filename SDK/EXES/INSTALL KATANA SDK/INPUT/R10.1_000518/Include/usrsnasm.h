#ifndef __USRSNASM_H_
#define __USRSNASM_H_

/*
 * Include file for Clibrary server functions
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
 *
 * This file exports the Clib interface for use with DreamCast Console.
 * ====================================================================
 *
 *
 * Created by G.N. Ellison
 *
 */

/* Default Channel */
#define SNASM_STDIN		0		/* Channel ID for STDIN (NOT CURRENTLY SUPPORTED) */
#define SNASM_STDOUT	1		/* Channel ID for STDOUT */
#define SNASM_STDERR	2		/* Channel ID for STDERR */

/* Seek origin specifications */
#define SNASM_SEEK_SET	0		/* allocate top position		*/
#define SNASM_SEEK_CUR	1		/* allocate current position	*/
#define SNASM_SEEK_END	2		/* allocate bottom position		*/

/* file attribute definitions provided by _findfirst() & _findnext() */
#define SNASM_A_NORMAL	0x00	/* Normal. File can be read or written to without restriction. */
#define SNASM_A_RDONLY	0x01	/* Read-only. File cannot be opened for writing, and a file with the same name cannot be created. */
#define SNASM_A_HIDDEN	0x02	/* Hidden file. Not normally seen with the DIR command, unless the /AH option is used. Returns information about normal files as well as files with this attribute.*/
#define SNASM_A_SYSTEM	0x04	/* System file. Not normally seen with the DIR command, unless the /A or /A:S option is used. */
#define SNASM_A_SUBDIR	0x10	/* Subdirectory. */
#define SNASM_A_ARCH	0x20    /* Archive. Set whenever the file is changed, and cleared by the BACKUP command. */

struct SNASM_finddata_t {
    unsigned long	m_ulSize;
	unsigned long   m_ulAttributes;
    char			m_szFilename[260];
} ;

typedef enum{ SCRIPTTYPE_UNDEF, SCRIPTTYPE_JSCRIPT, SCRIPTTYPE_VBSCRIPT } SCRIPTTYPE;

/*
 * Exported Interface Functions.
 *
 * NOTE: None of these functions are available without the CodeScape
 *       debugger running on the host.
 */

#ifdef __cplusplus
extern "C" {
#endif

extern int debug_open(const char *filename, int flags, ...);
extern int debug_close(int file);
extern int debug_read(int file, char *ptr, int len);
extern int debug_write(int file, char *ptr, int len);
extern int debug_lseek(int file, int offset, int origin);

extern char * debug_getcwd(char *buffer, int maxlen);
extern int debug_chdir(const char *dirname);
extern int debug_mkdir(const char *dirname);
extern int debug_rmdir(const char *dirname);

extern int debug_findfirst(const char *filespec, struct SNASM_finddata_t *fileinfo);
extern int debug_findnext(int handle, struct SNASM_finddata_t *fileinfo);
extern int debug_findclose(int handle);

extern int _ASSERT(int nFlag);

extern int debug_runscript(const char *filename, SCRIPTTYPE eScriptType);

extern int debug_printf(char *format, ...);

#ifdef __cplusplus
}
#endif


/*
 * Fileserver - Error Codes
 */

#define SNASM_NOERROR		0
#define SNASM_EPERM			1
#define SNASM_ENOENT		2
#define SNASM_ESRCH			3
#define SNASM_EINTR			4
#define SNASM_EIO			5
#define SNASM_ENXIO			6
#define SNASM_E2BIG			7
#define SNASM_ENOEXEC 		8
#define SNASM_EBADF			9
#define SNASM_ECHILD		10
#define SNASM_EAGAIN		11
#define SNASM_ENOMEM		12
#define SNASM_EACCESS		13
#define SNASM_EFAULT		14
#define SNASM_EBUSY			16
#define SNASM_EEXIST		17
#define SNASM_EXDEV			18
#define SNASM_ENODEV		19
#define SNASM_ENOTDIR 		20
#define SNASM_EISDIR		21
#define SNASM_EINVAL		22
#define SNASM_ENFILE		23
#define SNASM_EMFILE		24
#define SNASM_ENOTTY		25
#define SNASM_EFBIG			27
#define SNASM_ENOSPC		28
#define SNASM_ESPIPE		29
#define SNASM_EROFS			30
#define SNASM_EMLINK		31
#define SNASM_EPIPE			32
#define SNASM_EDOM			33
#define SNASM_ERANGE		34
#define SNASM_EDEADLK		36
#define SNASM_ENAMETOOLONG	38
#define SNASM_ENOLCK		39
#define SNASM_ENOSYS		40
#define SNASM_ENOTEMPTY		41
#define SNASM_EILSEQ		42


#endif  /* __USRSNASM_H_ */


