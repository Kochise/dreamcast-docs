/*
 *  Shinobi Library
 *  Copyright (c) 1998 SEGA
 *  
 *       Memory Management
 *
 *  Module  : Library Header File
 *  File    : sg_Maloc.h
 *  Create  : 1998-03-25
 *  Modify  : 1998-08-26 syMalloc, syFree is now MACRO not a function.
 *  Version : 1.00
 *  Note    :
 */

#ifndef _SG_MALOC_H_
#define _SG_MALOC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct{
  Void *(*malloc)(Uint32 nbytes);
  Void (*free)(Void *ap);
  Void *(*calloc)(Uint32 nobj, Uint32 size);
  Void *(*realloc)(Void *ap, Uint32 nbytes);
} SYS_MALLOC_IF;

Void syMallocInit(Void *heap, Uint32 size);

Void syMallocFinish(Void);

Void *syMalloc(Uint32 nbytes);

void *syRealloc(void *op, Uint32 nbytes);

void *syCalloc(Uint32 nobj, Uint32 size);

Void syFree(Void *ap);

Void syMallocStat(Uint32 *wholeFreeSize, Uint32 *biggestFreeBlockSize);

SYS_MALLOC_IF *syMallocChangeIF(SYS_MALLOC_IF *mallocIF);

#ifndef _STDLIB
/* On Dreamcast environment. 
 * syMalloc providing these functions instead of SHC standard library.
 * and these functions are removed from SHC standard library. (ex. sh4nplfzz.lib )
 */
# ifndef _SIZE_T
# define _SIZE_T
typedef unsigned long size_t;
# endif
extern void *calloc(size_t, size_t);
extern void free(void *) ;
extern void *malloc(size_t);
extern void *realloc(void *, size_t) ;
#endif

#ifdef __cplusplus
	   }
#endif /* __cplusplus */

#endif /* _SG_MALOC_H_ */

/******************************* end of file *******************************/
