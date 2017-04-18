#ifndef VALIDLST_H
#define VALIDLST_H
/* ---------------------------------------------------------------------------------
// Copyright(c) 1991-1996 Microsoft Corporation.  All rights reserved.
// ---------------------------------------------------------------------------------
// File: VALIDLST.H
//
// Header file for VALIDLST.C
//
// 02/29/95	Derek Hazeur - Created
// -------------------------------------------------------------------------------*/
#include "ofcdtd.h"

#ifdef __cplusplus
#define EXTERN	extern "C"
#else
#define EXTERN
#endif

EXTERN int RcValidateOFCList(OFCDOC *pofcdoc, int *pcbOFCList);

#endif

