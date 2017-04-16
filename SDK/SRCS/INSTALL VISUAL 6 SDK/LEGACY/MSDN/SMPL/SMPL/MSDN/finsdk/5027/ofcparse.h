#ifndef	OFCPARSE_H
#define OFCPARSE_H

/* ---------------------------------------------------------------------------------
// Copyright(c) 1991-1996 Microsoft Corporation.  All rights reserved.
// ---------------------------------------------------------------------------------
// File: OFCPARSE.H
//
// Header file for OFCPARSE.C
//
// 02/26/95	Derek Hazeur - Created
// -------------------------------------------------------------------------------*/

#include "ofcdtd.h"

#ifdef __cplusplus
#define EXTERN	extern "C"
#else
#define EXTERN
#endif
EXTERN void InitOFCParse(void);
EXTERN int RcParseOFCRequest(void *pvRequest, int cbRequest, POFCDOC *ppofcdoc);
EXTERN int RcParseOFCResponse(void *pvResponse, int cbResponse, POFCDOC *ppofcdoc);
EXTERN int RcParseOFCStatement(void *pvStatement, int cbStatement, POFCDOC *ppofcdoc);
EXTERN void CleanupOFCDOCParse(POFCDOC *ppofcdoc);

#endif

