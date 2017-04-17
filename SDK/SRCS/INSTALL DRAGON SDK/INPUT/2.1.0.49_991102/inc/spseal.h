/*++

Copyright (c) 1992-1998 Microsoft Corporation

Module Name: spseal.h

Purpose: Prototypes for security provider encryption routines.

--*/

#ifndef _SPSEAL_
#define _SPSEAL_

SECURITY_STATUS SEC_ENTRY
SealMessage(    PCtxtHandle         phContext,
                unsigned long       fQOP,
                PSecBufferDesc      pMessage,
                unsigned long       MessageSeqNo);

typedef SECURITY_STATUS
(SEC_ENTRY * SEAL_MESSAGE_FN)(
    PCtxtHandle, unsigned long, PSecBufferDesc, unsigned long);


SECURITY_STATUS SEC_ENTRY
UnsealMessage(  PCtxtHandle         phContext,
                PSecBufferDesc      pMessage,
                unsigned long       MessageSeqNo,
                unsigned long *     pfQOP);


typedef SECURITY_STATUS
(SEC_ENTRY * UNSEAL_MESSAGE_FN)(
    PCtxtHandle, PSecBufferDesc, unsigned long,
    unsigned long *);

#endif // _SPSEAL_
