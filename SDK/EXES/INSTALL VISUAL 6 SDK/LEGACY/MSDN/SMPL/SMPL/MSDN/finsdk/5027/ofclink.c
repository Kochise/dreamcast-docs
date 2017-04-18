/* --------------------------------------------------------------------------------- */
/* Copyright(c) 1991-1996 Microsoft Corporation.  All rights reserved. */
/* --------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------- */
/* File: OFCLINK.C */
/* */
/* Contains functions necessary to create / maintain the OFC Linked List  */
/*  */
/* TBD: More Comments */
/* */
/* */
/* 02/21/95	Derek Hazeur - Created */
/* */
/* --------------------------------------------------------------------------------- */

/* Standard Include */
#include <stdio.h>
#include <malloc.h>

/* Other includes */
#include "ofcdtd.h"			/* Data structure definitions */
/*#include "parse.h"		 */
#include "ofclink.h"		/* Include file for this file */

/* --------------------------------------------------------------------------------- */
/* Function: RcCreateOFCDOC */
/* */
/* --------------------------------------------------------------------------------- */
int RcCreateOFCDOC(OFCDOC ** ppofcdoc, char * szDTD, char * szCPAGE)
{
	int rcReturn; 

	/* Allocate memory */
	*ppofcdoc = (OFCDOC *) malloc(sizeof(OFCDOC));
	if (*ppofcdoc == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END;
	}

	/* Fill in structure */
	(*ppofcdoc)->szDTD = szDTD;
	(*ppofcdoc)->szCPAGE = szCPAGE;
	(*ppofcdoc)->pofctrn = (OFCTRN *) NULL;

	/* Set OK return code */
	rcReturn = ALL_OK; 

_END:

	return rcReturn; 

} /* end CreateOFCDOC */

/* --------------------------------------------------------------------------------- */
/* Function: AddOFCTRN */
/* */
/* --------------------------------------------------------------------------------- */
int RcAddOFCTRN(OFCDOC * pofcdoc, OFCTYPE ofctype , void * pTran)
{
	OFCTRN*	pofctrn;
	OFCTRN* pofctrnCurrent;
	int rcReturn; 

	/* Allocate memory */
	pofctrn = (OFCTRN *) malloc(sizeof(OFCTRN));
	if (pofctrn == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END;
	}

	/* Fill in structure */
	pofctrn->ofctype = ofctype;
	pofctrn->pvTrn = pTran;
	pofctrn->pofctrnNext = (OFCTRN *) NULL;

	/* If this is the first OFCTRN, fill in now, otherwise traverse until  */
	/* end of the list and add there */
	if (pofcdoc->pofctrn == NULL)
		pofcdoc->pofctrn = pofctrn;
	else
	{
		/* Start with first transaction */
		pofctrnCurrent = pofcdoc->pofctrn;

		/* Traverse to last OFCTRN in the list */
		while (pofctrnCurrent->pofctrnNext != NULL)
			pofctrnCurrent = pofctrnCurrent->pofctrnNext;

		/* Add the OFCTRN  */
		pofctrnCurrent->pofctrnNext = pofctrn;
	}

	/* Set OK return code */
	rcReturn = ALL_OK;

_END:

	return rcReturn; 

} /* end AddOFCTRN */

/* --------------------------------------------------------------------------------- */

