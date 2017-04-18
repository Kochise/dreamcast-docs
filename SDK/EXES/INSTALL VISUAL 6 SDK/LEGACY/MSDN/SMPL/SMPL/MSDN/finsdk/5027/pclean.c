/* ---------------------------------------------------------------------------------
// Copyright(c) 1991-1996 Microsoft Corporation.  All rights reserved.
// ---------------------------------------------------------------------------------
// File: PCLEAN.C
//
// Contains functions necessary to cleanup after an OFC Parse.
//
// 02/29/96 TimHa - Created
// --------------------------------------------------------------------------------*/

/* Standard Include Files */
#include <stdio.h> 
#include <malloc.h>
#include <ctype.h>
#include <string.h>

/* Other Include files  */
#include "ofcdtd.h"		/* Functions to Create / Update linked list */
#include "pbtypes.h"	/* ofc parse & build types */
#include "parse.h"		/* parse only */



/* ---------------------------------------------------------------------------------
// Function: ParseCleanup
//
// Cleans up and deallocates an OFC linked list
//
// Parameters: 
//	ppofcdoc - The OFC linked list to be freed 
//
// History: 
//	2/29/96	TimHa - Created
//
// -------------------------------------------------------------------------------*/
void ParseCleanup(POFCDOC *ppofcdoc)
{
	POFCTRN		pofctrn;
	POFCTRN		pofctrnNext;

	/* get the transaction list */
	pofctrn = (*ppofcdoc)->pofctrn;

	/* now, head down the trn list and free nodes as we go along */
	while (pofctrn)
	{
		/* first get the next trn */
		pofctrnNext = pofctrn->pofctrnNext;

		/* deal with the node */
		switch(pofctrn->ofctype)
		{
		case ofctypeSONRQ:
		case ofctypeSONRS:
		case ofctypeINTRARS:
		case ofctypeINTERRS:
		case ofctypePAYMTRS:
		case ofctypeERRORRS:
			/* all of these are easy, they just have char *'s in them */
			/* so they can be deleted as is */
			break;

		case ofctypeACCTRQ:
			CleanupACCTRQ((ACCTRQ *) pofctrn->pvTrn);
			break;

		case ofctypeACCTRS:
			CleanupACCTRS((ACCTRS *) pofctrn->pvTrn);
			break;

		case ofctypePAYEERQ:
			CleanupPAYEERQ((PAYEERQ *) pofctrn->pvTrn);
			break;

		case ofctypePAYEERS:
			CleanupPAYEERS((PAYEERS *) pofctrn->pvTrn);
			break;

		case ofctypeMAILRQ:
			CleanupMAILRQ((MAILRQ *) pofctrn->pvTrn);
			break;

		case ofctypeMAILRS:
			CleanupMAILRS((MAILRS *) pofctrn->pvTrn);
			break;

		case ofctypeSTMTRQ:
			CleanupSTMTRQ((STMTRQ *) pofctrn->pvTrn);
			break;

		case ofctypeSTMTRS:
			CleanupSTMTRS((STMTRS *) pofctrn->pvTrn);
			break;

		case ofctypeINTRARQ:
			CleanupINTRARQ((INTRARQ *) pofctrn->pvTrn);
			break;

		case ofctypeINTERRQ:
			CleanupINTERRQ((INTERRQ *) pofctrn->pvTrn);
			break;

		case ofctypePAYMTRQ:
			CleanupPAYMTRQ((PAYMTRQ *) pofctrn->pvTrn);
			break;

		case ofctypePAYIQRQ:
			CleanupPAYIQRQ((PAYIQRQ *) pofctrn->pvTrn);
			break;

		case ofctypePAYIQRS:
			CleanupPAYIQRS((PAYIQRS *) pofctrn->pvTrn);
			break;
			
		case ofctypeACCTSTMT:
			CleanupACCTSTMT((ACCTSTMT *) pofctrn->pvTrn);
			break;

		default:
			/* this should never get hit */
			break;

		
		}
		free(pofctrn->pvTrn);	/* free the transaction node */
		free(pofctrn);			/* free this trn node */
		pofctrn = pofctrnNext;	/* next is now current */

	}
	/* now free the main node and NULL out the caller's pointer */
	free(*ppofcdoc);
	*ppofcdoc = NULL;

	return;
}

/* 
// Individual clean-up routines - these are only responsible for freeing
// sub-structures within the main transaction structures, the higher loop
// will free the actual transaction data
*/
void CleanupACCTRQ(ACCTRQ *pacctrq)
{
	if (pacctrq->pacctACCTFROM)
		free(pacctrq->pacctACCTFROM);

	if (pacctrq->psrqstSERVRQST1)
		free(pacctrq->psrqstSERVRQST1);

	if (pacctrq->psrqstSERVRQST2)
		free(pacctrq->psrqstSERVRQST2);

	return ;
} /* CleanupACCTRQ */

void CleanupACCTRS(ACCTRS *pacctrs)
{
	if (pacctrs->psauthSERVAUTH1)
		free(pacctrs->psauthSERVAUTH1);

	if (pacctrs->psauthSERVAUTH2)
		free(pacctrs->psauthSERVAUTH2);

	return;

} /* CleanupACCTRS */

void CleanupPAYEERQ(PAYEERQ *ppayeerq)
{
	if (ppayeerq->pentPAYEE)
		free(ppayeerq->pentPAYEE);
	
	return;

} /* CleanupPAYEERQ */

void CleanupPAYEERS(PAYEERS *ppayeers)
{
	if (ppayeers->pentPAYEE)
		free(ppayeers->pentPAYEE);
	
	return;
} /* CleanupPAYEERS */

void CleanupMAILRQ(MAILRQ *pmailrq)
{
	if (pmailrq->pacctACCTFROM)
		free(pmailrq->pacctACCTFROM);

	if (pmailrq->pmemoMEMO)
		CleanupMemos(pmailrq->pmemoMEMO);

	return;
} /* CleanupMAILRQ */

void CleanupMAILRS(MAILRS *pmailrs)
{
	if (pmailrs->pmemoMEMO)
		CleanupMemos(pmailrs->pmemoMEMO);

	return;

} /* CleanupMAILRS */

void CleanupSTMTRQ(STMTRQ *pstmtrq)
{
	if (pstmtrq->pacctACCTFROM)
		free(pstmtrq->pacctACCTFROM);

	return;
} /* CleanupSTMTRQ */

void CleanupSTMTRS(STMTRS *pstmtrs)
{
	if (pstmtrs->pgtrnSTMTTRN)
		CleanupStmts(pstmtrs->pgtrnSTMTTRN);

	return;
}  /* CleanupSTMTRS */

void CleanupINTRARQ(INTRARQ *pintrarq)
{
	if (pintrarq->pacctACCTFROM)
		free(pintrarq->pacctACCTFROM);

	if (pintrarq->pacctACCTTO)
		free(pintrarq->pacctACCTTO);

	if (pintrarq->pmemoMEMO)
		CleanupMemos(pintrarq->pmemoMEMO);

	return;
} /* CleanupINTRARQ */

void CleanupINTERRQ(INTERRQ *pinterrq)
{
	if (pinterrq->pacctACCTFROM)
		free(pinterrq->pacctACCTFROM);

	if (pinterrq->pacctACCTTO)
		free(pinterrq->pacctACCTTO);

	if (pinterrq->pmemoMEMO)
		CleanupMemos(pinterrq->pmemoMEMO);

	return;
} /* CleanupINTERRQ */

void CleanupPAYMTRQ(PAYMTRQ *ppaymtrq)
{
	if (ppaymtrq->pacctACCTFROM)
		free(ppaymtrq->pacctACCTFROM);

	if (ppaymtrq->pentPAYEE)
		free(ppaymtrq->pentPAYEE);

	if (ppaymtrq->pmemoMEMO)
		CleanupMemos(ppaymtrq->pmemoMEMO);

	return;
} /* CleanupPAYMTRQ */

void CleanupPAYIQRQ(PAYIQRQ *ppayiqrq)
{
	if (ppayiqrq->pmemoMEMO)
		CleanupMemos(ppayiqrq->pmemoMEMO);

	return;
} /* CleanupPAYIQRQ */

void CleanupPAYIQRS(PAYIQRS *ppayiqrs)
{ 
	if (ppayiqrs->pmemoMEMO)
		CleanupMemos(ppayiqrs->pmemoMEMO);

	return;
} /* CleanupPAYIQRS */

void CleanupACCTSTMT(ACCTSTMT * pacctstmt)
{
	if (pacctstmt->pacctACCTFROM)
		free(pacctstmt->pacctACCTFROM);
	if (pacctstmt->pgtrnSTMTTRN)
		CleanupStmts(pacctstmt->pgtrnSTMTTRN);
	return;
} /* CleanupACCTSTMT */


void CleanupMemos(MEMO * pmemo)
{
	MEMO * pmemoNext;

	while(pmemo)
	{
		pmemoNext = pmemo->pmemoNext; 
		free(pmemo);
		pmemo = pmemoNext;
	}
	return;
} /* CleanupMemos */

void CleanupStmts(GENTRN * pgtrn)
{
	GENTRN * pgtrnNext;
	
	while(pgtrn)
	{
		pgtrnNext = pgtrn->pgtrnNext;

		/* free sub-storage */
		if (pgtrn->pentPAYEE)
			free(pgtrn->pentPAYEE);
		if (pgtrn->pacctACCTTO)
			free(pgtrn->pacctACCTTO);
		if (pgtrn->pmemoMEMO)
			CleanupMemos(pgtrn->pmemoMEMO);
		/* free the node itself */
		free(pgtrn);
		pgtrn = pgtrnNext;	/* get next */
	}
	return;
} /* CleanupStmts */

