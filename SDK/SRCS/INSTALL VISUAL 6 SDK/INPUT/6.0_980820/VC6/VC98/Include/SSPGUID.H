/*++

Copyright (c) 1996  Microsoft Corporation

Module Name:

    SspGUID

Abstract:

    This file contains the GUIDS for the low level COM objects/interfaces
    
Author:

    Chris Dudley (cdudley) 1/6/1997

Environment:

    Win32, C++ w/Exceptions, ATL, COM/OLE

Revision History:

    Chris Dudley (cdudley) 2/10/1997

Notes:

--*/

#ifndef __SSPGUID_H__
#define __SSPGUID_H__

#define IID_DEFINED

// SCardDat
#include <scarddat_i.c>

//SCardMgr
#include <scardmgr_i.c>

//SCardSrv
#include <scardsrv_i.c>

#ifndef CLSCTX_LOCAL
#define CLSCTX_LOCAL            (CLSCTX_INPROC_SERVER| \
                                 CLSCTX_INPROC_HANDLER| \
                                 CLSCTX_LOCAL_SERVER)
#endif
#endif //__SSPGUID_H__
