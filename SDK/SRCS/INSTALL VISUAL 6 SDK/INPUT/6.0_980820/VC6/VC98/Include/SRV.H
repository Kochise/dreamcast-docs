//
// Open Data Services header file
//
// Copyright 1989 - 1998 Microsoft Corporation.
//

#include "windows.h"

// Use same packing pragma as SQLServer. Otherwise it causes problems
// when these are files included mixed with SQLServer files.
#if !defined( _MSSQLRISC_)
#pragma pack(2)
#endif

//  Include miscellaneous Open Data Services definitions
//
#include    <srvmisc.h>

//  Include DBLIB definitions (it checks to see if they have already
//  been defined)
//
#include    <srvdbtyp.h>

//  Include Open Data Services structure definitions
//
#include    <srvstruc.h>

//  Include Open Data Services token definitions
//
#include    <srvtok.h>

//  Include Open Data Services constant definitions
//
#include    <srvconst.h>

//  Include Open Data Services datatype definitions
//
#include    <srvtypes.h>

//  Include Open Data Services MACRO definitions and function prototypes
//
#include    <srvapi.h>
#if !defined( _MSSQLRISC_)
#pragma pack()
#endif

