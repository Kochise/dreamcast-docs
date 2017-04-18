#ifndef	OFCBUILD_H
#define OFCBUILD_H
/* --------------------------------------------------------------------------------- */
/* Copyright(c) 1991-1996 Microsoft Corporation.  All rights reserved. */
/* --------------------------------------------------------------------------------- */
/* File: OFCBUILD.H */
/* */
/* Header file for OFCBUILD.C */
/* */
/* 02/29/95	Derek Hazeur - Created */
/* --------------------------------------------------------------------------------- */

#include "ofcdtd.h"

#ifdef __cplusplus
#define EXTERN	extern "C"
#else
#define EXTERN
#endif

EXTERN int RcCreateOFCRequest(OFCDOC *pofcdoc, void **ppvOFCFile, int *pcbOFCFile);
EXTERN int RcCreateOFCResponse(OFCDOC *pofcdoc, void **ppvOFCFile, int *pcbOFCFile);
EXTERN int RcCreateOFCStatement(OFCDOC *pofcdoc, void **ppvOFCFile, int *pcbOFCFile);
EXTERN void CleanupOFCFile(void **ppvOFCFile);

#endif

