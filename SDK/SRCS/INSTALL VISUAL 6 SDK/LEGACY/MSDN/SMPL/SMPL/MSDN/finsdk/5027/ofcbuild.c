/* --------------------------------------------------------------------------------- */
/* Copyright(c) 1991-1996 Microsoft Corporation.  All rights reserved. */
/* --------------------------------------------------------------------------------- */
/* File: OFCBUILD.C */
/* */
/* Contains functions necessary to build an OFC document from an OFC Linked List */
/* */
/* 02/29/95	Derek Hazeur - Created */
/* --------------------------------------------------------------------------------- */

#include <stdio.h>
#include <malloc.h>
#include "ofcbuild.h"	/* Prototypes for this file */
#include "pbtypes.h"	/* Types used for Parsing/Building */
#include "build.h"		/* Prototypes for build functions */

/* --------------------------------------------------------------------------------- */
/*								Function Definitions */
/* --------------------------------------------------------------------------------- */
int RcCreateOFCRequest(OFCDOC *pofcdoc, void **ppvOFCFile, int *pcbOFCFile)
{
	/* Zero out count */
	*pcbOFCFile = 0;

	return RcBuildOFC(odtREQUEST,pofcdoc,ppvOFCFile,pcbOFCFile); 


} /* end RcCreateOFCRequest */
/* --------------------------------------------------------------------------------- */
int RcCreateOFCResponse(OFCDOC *pofcdoc, void **ppvOFCFile, int *pcbOFCFile)
{
	/* Zero out count */
	*pcbOFCFile = 0;

	return RcBuildOFC(odtRESPONSE,pofcdoc,ppvOFCFile,pcbOFCFile); 


} /* end RcCreateOFCResponse */

/* --------------------------------------------------------------------------------- */
int RcCreateOFCStatement(OFCDOC *pofcdoc, void **ppvOFCFile, int *pcbOFCFile)
{
	/* Zero out count */
	*pcbOFCFile = 0;

	return RcBuildOFC(odtSTATEMENT,pofcdoc,ppvOFCFile,pcbOFCFile); 


} /* end RcCreateOFCStatement */

/* --------------------------------------------------------------------------------- */

/* --------------------------------------------------------------------------------- */
void CleanupOFCFile(void **ppvOFCFile)
{
	if (ppvOFCFile != NULL)
		{
		free(*ppvOFCFile);
		*ppvOFCFile = NULL;
		}

	return;
} /* end CleanupOFCFile */

/* --------------------------------------------------------------------------------- */
