#ifndef OFCLINK_H
#define OFCLINK_H
/* ---------------------------------------------------------------------------------
/* Copyright(c) 1991-1996 Microsoft Corporation.  All rights reserved. */
/* --------------------------------------------------------------------------------- */
/* File: OFCLINK.H */
/* */
/* 02/26/95	Derek Hazeur - Created */
/* -------------------------------------------------------------------------------*/ /* */

#include "ofcdtd.h"

#ifdef __cplusplus
#define EXTERN	extern "C"
#else
#define EXTERN
#endif

EXTERN int RcCreateOFCDOC(OFCDOC ** ppofcdoc, char * szDTD, char * szCPAGE);
EXTERN int RcAddOFCTRN(OFCDOC * pofcdoc, OFCTYPE ofctype , void * pTran);

#endif

