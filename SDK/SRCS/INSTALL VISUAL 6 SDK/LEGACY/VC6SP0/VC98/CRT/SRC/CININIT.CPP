/***
*cininit.cpp - definitions and initialization for predefined stream cin.
*
*       Copyright (c) 1991-1997, Microsoft Corporation.  All rights reserved.
*
*Purpose:
*       Definitions and initialization of predefined stream cin.
*
*******************************************************************************/
#include <cruntime.h>
#include <internal.h>
#include <iostream.h>
#include <fstream.h>
#include <dbgint.h>
#pragma hdrstop

// put contructors in special MS-specific XIFM segment
#pragma warning(disable:4074)   // ignore init_seg warning
#pragma init_seg(compiler)

istream_withassign cin(_new_crt filebuf(0));

static Iostream_init  __InitCin(cin);

