/*++

Copyright (c) 1991-1998 Microsoft Corporation

Module Name:

    rpcdce.h

Abstract:

    This module contains the DCE RPC runtime APIs.

Author:

    Michael Montague (mikemon) 25-Sep-1991

Revision History:

--*/

#ifndef __RPCDCE_H__
#define __RPCDCE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define IN
#define OUT
#define OPTIONAL

#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct _GUID
{
    unsigned long Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
} GUID, *PGUID;
#endif /* GUID_DEFINED */

#ifndef UUID_DEFINED
#define UUID_DEFINED
typedef GUID UUID;
#ifndef uuid_t
#define uuid_t UUID
#endif
#endif

typedef void __RPC_FAR * RPC_IF_HANDLE;

#ifdef __cplusplus
}
#endif

#endif /* __RPCDCE_H__ */
