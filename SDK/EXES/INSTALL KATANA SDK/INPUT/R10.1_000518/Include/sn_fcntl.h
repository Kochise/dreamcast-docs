#ifndef __SN_FCNTL_H_
#define __SN_FCNTL_H_

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
 *	crosslib.h	21/09/95
 */


#define SNASM_O_RDONLY		0x0000	/* open for read only */
#define SNASM_O_WRONLY		0x0001	/* open for write only */
#define SNASM_O_RDWR		0x0002	/* open for read and write */
#define SNASM_O_APPEND		0x0010	/* writes done at end of file */
#define SNASM_O_CREAT 		0x0020	/* create new file */
#define SNASM_O_TRUNC 		0x0040	/* truncate existing file */
#define SNASM_O_NOINHERIT	0x0080	/* file is not inherited by child process */
#define SNASM_O_TEXT		0x0100	/* text file */
#define SNASM_O_BINARY		0x0200	/* binary file */
#define SNASM_O_EXCL		0x0400	/* exclusive open */

#define SNASM_S_IREAD		0x0400	/* read permitted */
#define SNASM_S_IWRITE		0x0200	/* write permitted */


#endif  /* __SN_FCNTL_H_ */
