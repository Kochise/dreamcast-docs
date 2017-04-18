/*++

Copyright (C) 1995-1997 Microsoft Corporation

Module Name:

    appmema.h

Abstract:

    application memory performance counter definitions

Revision History

    30 Aug 1995     Bob Watson (a-robw)     Created

--*/
#ifndef _APPMEMA_H_
#define _APPMEMA_H_

#include "..\inc\appmemi.h"

struct  _APPMEM_DATA_HEADER *pDataHeader;
struct  _APPMEM_INSTANCE    *pAppData;

extern  HANDLE  hAppMemMutex;


#endif // _APPMEMA_H_
