/****************************** Module Header ******************************\
*
* Module Name: SNADOS.H
*
* Description: Microsoft SNA Server MSDOS specific 3270 Emulator Interface
*              definitions.
*
* Copyright (c) 1994, Microsoft Corporation.  All rights reserved.
*
\***************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/* Common definitions */

#define PASCAL	pascal
#define FAR		far
#define NEAR	near
#define VOID	void

#define APIENTRY far pascal
#ifndef WINAPI
#define WINAPI APIENTRY
#endif

#define CHAR	char		/* ch  */
#define SHORT	short		/* s   */
#define LONG	long		/* l   */
#define INT		int			/* i   */

typedef unsigned char UCHAR;	/* uch */
typedef unsigned short USHORT;	/* us  */
typedef unsigned long ULONG;	/* ul  */
typedef unsigned int  UINT;		/* ui  */
typedef unsigned char BYTE;		/* b   */

typedef unsigned short SHANDLE;


/* define NULL pointer value */
/* Echo the format of the ifdefs that stdio.h uses */

#if (_MSC_VER >= 600)
#define NULL	((void *)0)
#else
#if (defined(M_I86L) || defined(M_I86CM) || defined(M_I86LM) || defined(M_I86HM))
#define  NULL	 0L
#else
#define  NULL	 0
#endif
#endif

typedef SHANDLE HFILE;		/* hf */
typedef HFILE far *PHFILE;

typedef unsigned char far  *PSZ;
typedef unsigned char near *NPSZ;
typedef char far *LPSTR;

typedef unsigned char far  *PCH;
typedef unsigned char near *NPCH;

typedef int   (pascal far  *PFN)();
typedef int   (pascal near *NPFN)();
typedef PFN far *PPFN;

typedef BYTE   FAR  *PBYTE;
typedef BYTE   near *NPBYTE;

typedef CHAR   FAR *PCHAR;
typedef SHORT  FAR *PSHORT;
typedef LONG   FAR *PLONG;
typedef INT    FAR *PINT;

typedef UCHAR  FAR *PUCHAR;
typedef USHORT FAR *PUSHORT;
typedef ULONG  FAR *PULONG;
typedef UINT   FAR *PUINT;
typedef VOID   FAR *PVOID;

typedef unsigned short BOOL;	/* f   */
typedef BOOL FAR *PBOOL;

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

typedef unsigned short SEL;		/* sel */
typedef SEL FAR *PSEL;

/*** Useful Helper Macros */

/* Create untyped far pointer from selector and offset */
#define MAKEP(sel, off) 	((PVOID)MAKEULONG(off, sel))

/* Extract selector or offset from far pointer */
#define SELECTOROF(p)		(((PUSHORT)&(p))[1])
#define OFFSETOF(p)		(((PUSHORT)&(p))[0])


/* Cast any variable to an instance of the specified type. */
#define MAKETYPE(v, type)	(*((type far *)&v))

/* Calculate the byte offset of a field in a structure of type type. */
#define FIELDOFFSET(type, field)    ((SHORT)&(((type *)0)->field))

/* Combine l & h to form a 32 bit quantity. */
#define MAKEULONG(l, h) ((ULONG)(((USHORT)(l)) | ((ULONG)((USHORT)(h))) << 16))
#define MAKELONG(l, h)	((LONG)MAKEULONG(l, h))

/* Combine l & h to form a 16 bit quantity. */
#define MAKEUSHORT(l, h) (((USHORT)(l)) | ((USHORT)(h)) << 8)
#define MAKESHORT(l, h)  ((SHORT)MAKEUSHORT(l, h))

/* Extract high and low order parts of 16 and 32 bit quantity */
#define LOBYTE(w)	LOUCHAR(w)
#define HIBYTE(w)	HIUCHAR(w)
#define LOUCHAR(w)	((UCHAR)(USHORT)(w))
#define HIUCHAR(w)	((UCHAR)(((USHORT)(w) >> 8) & 0xff))
#define LOUSHORT(l)	((USHORT)(ULONG)(l))
#define HIUSHORT(l)	((USHORT)(((ULONG)(l) >> 16) & 0xffff))

#define SWAPUSHORT(x) (x=(((x<<8)&0xFF00)|((x>>8)&0x00FF)))

/*** Common DOS types */

typedef USHORT	  HMODULE;	/* hmod */
typedef HMODULE FAR *PHMODULE;

typedef USHORT	  PID;		/* pid	*/
typedef PID FAR *PPID;

typedef USHORT	  TID;		/* tid	*/
typedef TID FAR *PTID;

typedef VOID FAR *HSEM; 		/* hsem */
typedef HSEM FAR *PHSEM;

/**** DOS FMI Error codes */

#define ERROR_SEM_TIMEOUT  0xfffc /* Time out happened from the     */
                                  /* semaphore api functions.       */
#define ERROR_SEM_OWNED    0xfffd /* Semaphore is already owned     */

/**** DOS FMI Semaphore functions */

extern USHORT  APIENTRY CMDSemClear(HSEM);
extern USHORT  APIENTRY CMDSemRequest(HSEM, USHORT);
extern USHORT  APIENTRY CMDSemSet(HSEM);
extern USHORT  APIENTRY CMDSemWait(HSEM, USHORT);

/*** DOS FMI TSR functions */

extern USHORT  APIENTRY CMDGoTSR(ULONG, UCHAR FAR *, UCHAR FAR *);

extern USHORT  APIENTRY CMDStartFG(void);
extern USHORT  APIENTRY CMDStopFG(USHORT);

/*** DOS FMI Task switching functions */
extern USHORT  APIENTRY RegisterSwitchProc(ULONG);

/*** Other DOS FMI functions */
extern USHORT APIENTRY SNAGetVersion(VOID);

#ifdef __cplusplus
}
#endif


