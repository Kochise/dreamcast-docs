/*
 *  _ P C H . H
 *
 *  Sample mail handling hook precompiled header source
 *  Copyright 1992-95 Microsoft Corporation.  All Rights Reserved.
 */

#pragma warning(disable:4001)   /* single line comments */
#pragma warning(disable:4050)   /* different code attributes */
#pragma warning(disable:4054)   /* cast from function pointer to data pointer */
#pragma warning(disable:4100)   /* unreferenced formal parameter */
#pragma warning(disable:4115)   /* named type def in parens */
#pragma warning(disable:4127)   /* conditional expression is constant */
#pragma warning(disable:4200)   /* zero sized array */
#pragma warning(disable:4201)   /* nameless struct/union */
#pragma warning(disable:4204)   /* non-constant aggregate initializer */
#pragma warning(disable:4206)   /* translation unit is empty */
#pragma warning(disable:4209)   /* benign typedef redefinition */
#pragma warning(disable:4213)   /* cast on l-value */
#pragma warning(disable:4214)   /* bit field types other than int */
#pragma warning(disable:4220)   /* varargs matches remaining parameters */
#pragma warning(disable:4505)   /* unreferenced local function removed */
#pragma warning(disable:4514)   /* unreferenced inline function removed */
#pragma warning(disable:4702)   /* unreachable code */
#pragma warning(disable:4704)   /* inline assembler turns off global optimizer */
#pragma warning(disable:4705)   /* statement has no effect */
#pragma warning(disable:4706)   /* assignment within conditional expression */
#pragma warning(disable:4710)   /* function not expanded */

#define STRICT

#include <windows.h>
#include <ole2.h>
#include <string.h>
#include <mapix.h>
#include <mapiwin.h>
#include <mapix.h>
#include <mapidefs.h>
#include <mapicode.h>
#include <mapitags.h>
#include <mapiguid.h>
#include <mapispi.h>
#include <mapihook.h>
#include <mapidbg.h>
#include <mapiutil.h>
#include <mapiwz.h>

#include <windowsx.h>
#include <wrap3d.h>
#include <richedit.h>
#include <prsht.h>

#pragma warning(disable:4001)   /* single line comments */
#pragma warning(disable:4200)   /* zero sized array */

#ifdef WIN16
#define EXPORT __export
#else
#define EXPORT
#endif

#include "_smh.h"
#include "smhrc.h"

#ifdef  WIN16
#include <mmsystem.h>
#endif
