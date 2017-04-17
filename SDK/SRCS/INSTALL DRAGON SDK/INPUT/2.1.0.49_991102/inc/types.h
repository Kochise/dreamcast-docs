/*++

Copyright (c) 1995-1998  Microsoft Corporation

Module Name: types.h

Purpose: Type definitions.

--*/

/* Useful typedefs */

#ifndef _TYPES_H_
#define _TYPES_H_

/* The left side of these typedefs are machine and compiler dependent */
typedef signed      char        INT8;
typedef unsigned    char        UINT8;
typedef signed      short       INT16;
typedef unsigned    short       UINT16;
typedef signed      int         INT32;
typedef unsigned    int         UINT32;
typedef signed      __int64     INT64;
typedef unsigned    __int64     UINT64;
typedef struct _INT128  { UINT32 u0,u1,u2; INT32 u3; } INT128;
typedef struct _UINT128 { UINT32 u0,u1,u2,u3; } UINT128;

typedef INT8    *PINT8;
typedef UINT8   *PUINT8;
typedef INT16   *PINT16;
typedef UINT16  *PUINT16;
typedef INT32   *PINT32;
typedef UINT32  *PUINT32;
typedef INT64   *PINT64;
typedef UINT64  *PUINT64;
typedef INT128  *PINT128;
typedef UINT128 *PUINT128;


typedef const void * PCVOID;
typedef void ** PPVOID;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef void (*PFNVOID)();
typedef CHAR * LPCHAR;

typedef HANDLE HPROCESS;
typedef HANDLE HTHREAD;

typedef LPCRECT PCRECT;

typedef DWORD WIN32_ERROR_CODE;

#endif // _TYPES_H_

