/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    ADsSmp.h

Abstract:

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _ADSSMP_H_
#define _ADSSMP_H_

#ifndef INITGUID
#define INITGUID
#endif

#define _LARGE_INTEGER_SUPPORT_
#define UNICODE
#define _UNICODE
#define INC_OLE2
#define SECURITY_WIN32

#include <windows.h>
#include <windowsx.h>
#include <winspool.h>
#include <cguid.h>
#include <stdlib.h>
#include <limits.h>
#include <io.h>
#include <activeds.h>
#include <crtdbg.h>                                     

#define ADsAssert(x) _ASSERT((x)) 

#include "libmain.h"
#include "util.h"
#include "memory.h"
#include "intf.h"
#include "cdispmgr.h"
#include "guid.h"
#include "macro.h"
#include "cmacro.h"
#include "common.h"
#include "getobj.h"
#include "smptypes.h"
#include "parse.h"
#include "core.h"
#include "pack.h"
#include "property.h"
#include "object.h"
#include "cprovcf.h"
#include "cprov.h"
#include "cnamcf.h"
#include "cnamesp.h"
#include "smpoper.h"
#include "cprops.h"
#include "cgenobj.h"
#include "cschobj.h"
#include "cclsobj.h"
#include "cprpobj.h"
#include "regdsapi.h"
#include "cenumvar.h"
#include "cenumns.h"
#include "cenumobj.h"
#include "cenumsch.h"
#include "globals.h"

#define     DISPID_REGULAR             1
#define     SampleDS_CLASS_ID          9
#define     SampleDS_SCHEMA_ID         12
#define     SampleDS_PROPERTY_ID       13
#define     SampleDS_OU_ID             15
#define     SampleDS_CLASSPROP_ID      18

#endif




