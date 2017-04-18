/*
| ---------------------------------------------------------------------------------
| Copyright(c) 1991-1996 Microsoft Corporation.  All rights reserved. 
| --------------------------------------------------------------------------------- 
| File: OFCPARSE.C 
|
| Contains functions necessary to parse an OFC document. 
|
| 02/21/95	Derek Hazeur - Created 
+-------------------------------------------------------------------------------*/

#include <stdio.h>
#include "ofcparse.h"	/* Prototypes for this file */
#include "pbtypes.h"
#include "parse.h"

/* -------------------------------------------------------------------------------*/
void InitOFCParse(void)
{
	/* initialize the hash table */
	InitHash();
} /* end InitOFCParse */

/* -------------------------------------------------------------------------------*/
int RcParseOFCRequest(void *pvRequest, int cbRequest, POFCDOC *ppofcdoc)
{
	
	return RcParseOFCDOC(odtREQUEST, pvRequest,cbRequest,ppofcdoc);

} /* end FParseOFCRequest */

/* -------------------------------------------------------------------------------*/
int RcParseOFCResponse(void *pvRequest, int cbRequest, POFCDOC *ppofcdoc)
{

	return RcParseOFCDOC(odtRESPONSE, pvRequest,cbRequest,ppofcdoc);

} /* end FParseOFCRequest */

/* -------------------------------------------------------------------------------*/
int RcParseOFCStatement(void *pvRequest, int cbRequest, POFCDOC *ppofcdoc)
{

	return RcParseOFCDOC(odtSTATEMENT, pvRequest,cbRequest,ppofcdoc);

} /* end FParseOFCRequest */

/* -------------------------------------------------------------------------------*/
void CleanupOFCDOCParse(POFCDOC *ppofcdoc)
{

	ParseCleanup(ppofcdoc);
	return;
}
/* -------------------------------------------------------------------------------*/
