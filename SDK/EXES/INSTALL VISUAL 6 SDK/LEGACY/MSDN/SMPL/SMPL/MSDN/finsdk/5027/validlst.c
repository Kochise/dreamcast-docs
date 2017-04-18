/* --------------------------------------------------------------------------------- */ 
/* Copyright(c) 1991-1996 Microsoft Corporation.  All rights reserved.      */ 
/* --------------------------------------------------------------------------------- */
/* File: VALIDLST.C	*/
/* */
/* Contains functions necessary to validate an OFC Linked List */
/* */
/* 02/29/95	Derek Hazeur - Created */
/* --------------------------------------------------------------------------------- */

/* Standard Includes */ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>		/* needed for atol */

/* Other includes */
#include "ofcdtd.h"
#include "validlst.h"

/* --------------------------------------------------------------------------------- */
/*					Max Number of Bytes Needed For Tags
/* --------------------------------------------------------------------------------- */
#define cbMaxTagOFC			29
#define cbMaxTagSONRQ		75
#define cbMaxTagSONRS		107	
#define cbMaxTagMAINTRQ		42
#define cbMaxTagMAINTRS		51
#define cbMaxTagACCTRQ		46
#define cbMaxTagACCTRS		12
#define cbMaxTagACCOUNT		67
#define cbMaxTagSERVRQST	46
#define cbMaxTagSERVAUTH	46
#define cbMaxTagPAYEERQ		65
#define cbMaxTagPAYEERS		68
#define cbMaxTagENTITY		125
#define cbMaxTagMAILRQ		57
#define cbMaxTagMAILRS		12
#define cbMaxTagMEMO		8
#define cbMaxTagTRNRQ		38
#define cbMaxTagTRNRS		47
#define cbMaxTagSTMTRS		42
#define cbMaxTagGENTRN		191 // 174
#define cbMaxTagACCTSTMT	101
#define cbMaxTagSTMTRQ		66
#define cbMaxTagPAYMTRQ		108
#define cbMaxTagPAYMTRS		36
#define cbMaxTagPAYIQRQ		34
#define cbMaxTagPAYIQRS		25
#define cbMaxTagERRORRS		28
#define cbMaxTagINTRARQ		79

#define cbMaxTagINTERRQ		118

/* The following ones have not been counted use 200 as default */

#define cbMaxTagINTRARS		46
#define cbMaxTagINTERRS		56

/* --------------------------------------------------------------------------------- */
/*							Local Function Prototypes */
/* --------------------------------------------------------------------------------- */
int RcCheckOFC(OFCDOC *pofcdoc,int *pcbOFCList);
int RcCheckSONRQ(SONRQ *sonrq,int *pcbOFCList);
int RcCheckSONRS(SONRS *sonrs,int *pcbOFCList);
int RcCheckACCTRQ(ACCTRQ *acctrq,int *pcbOFCList);
int RcCheckACCTRS(ACCTRS *acctrs,int *pcbOFCList);
int RcCheckACCOUNT(ACCOUNT *acct, int *pcbOFCList);
int RcCheckSERVRQST(SERVRQST *srqst, int *pcbOFCList);
int RcCheckSERVAUTH(SERVAUTH *sauth, int *pcbOFCList);
int RcCheckPAYEERQ(PAYEERQ *payeerq,int *pcbOFCList);
int RcCheckPAYEERS(PAYEERS *payeers,int *pcbOFCList);
int RcCheckENTITY(ENTITY *pent,int *pcbOFCList);
int RcCheckMAILRQ(MAILRQ *mailrq,int *pcbOFCList);
int RcCheckMAILRS(MAILRS *mailrs,int *pcbOFCList);
int RcCheckMEMO(MEMO *pmemo,int *pcbOFCList);
int RcCheckSTMTRQ(STMTRQ *stmtrq,int *pcbOFCList);
int RcCheckSTMTRS(STMTRS *stmtrs,int *pcbOFCList);
int RcCheckGENTRN(GENTRN *pgtrn,int *pcbOFCList);
int RcCheckINTRARQ(INTRARQ *pintrarq,int *pcbOFCList);
int RcCheckINTRARS(INTRARS *pintrars,int *pcbOFCList);
int RcCheckINTERRQ(INTERRQ *pinterrq,int *pcbOFCList);
int RcCheckINTERRS(INTERRS *interrs,int *pcbOFCList);
int RcCheckPAYMTRQ(PAYMTRQ *paymtrq,int *pcbOFCList);
int RcCheckPAYMTRS(PAYMTRS *paymtrs,int *pcbOFCList);
int RcCheckPAYIQRQ(PAYIQRQ *ppayiqrq,int *pcbOFCList);
int RcCheckPAYIQRS(PAYIQRS *payiqrs,int *pcbOFCList);
int RcCheckACCTSTMT(ACCTSTMT *acctstmt,int *pcbOFCList);
int RcCheckERRORRS(ERRORRS *errorrs,int *pcbOFCList);
/* --------------------------------------------------------------------------------- */
int RcValidateOFCList(OFCDOC *pofcdoc, int *pcbOFCList)
{
	/* Zero out count */
	*pcbOFCList = 0;

	return RcCheckOFC(pofcdoc,pcbOFCList); 

} /* end RcValidateOFCList */

/* --------------------------------------------------------------------------------- */
int RcCheckOFC(OFCDOC *pofcdoc,int *pcbOFCList)
{
	OFCTRN *pofctrn;
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify that we have a valid OFCDOC */
	if ((pofcdoc == NULL) || (pcbOFCList == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Verify all required pointers are valid */
	if ((pofcdoc->szDTD == NULL) || (pofcdoc->szCPAGE == NULL) ||
		(pofcdoc->pofctrn == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagOFC;

	/* Add lengths of strings in the OFCDOC */
	*pcbOFCList += strlen(pofcdoc->szDTD) + strlen(pofcdoc->szCPAGE);

	/* This code reflects current DTD Version */
	if (atol(pofcdoc->szDTD) != OFC_DTDVERSION)
	{
		rcReturn = INVALID_DTD_VER;
		goto _END;
	}

	/* This code only works with CPAGE = 1252 (Windows Latin I (ANSI)) */
	if (atol(pofcdoc->szCPAGE) != OFC_CPAGE)
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Start at the first transaction */
	pofctrn = pofcdoc->pofctrn;

	switch (pofctrn->ofctype)
	{
	case ofctypeSONRQ:

		/* Check the SONRQ  */
		rcReturn = RcCheckSONRQ((SONRQ *) pofctrn->pvTrn,pcbOFCList);
		if (rcReturn != ALL_OK)
			goto _END;

		/* Move to next Transaction */
		pofctrn = pofctrn->pofctrnNext;

		/* Process all MAINTRQ's */
		/* Process all MAINTRQ's */
		/* Process all ACCTRQ's */
		while ((pofctrn) && 
			(	(pofctrn->ofctype == ofctypeACCTRQ) ||
				(pofctrn->ofctype == ofctypePAYEERQ)||
				(pofctrn->ofctype == ofctypeMAILRQ)	))
		{
			/* Add the max number of bytes for tags */
			*pcbOFCList += cbMaxTagMAINTRQ;
			
			switch(pofctrn->ofctype)
				{
				case ofctypeACCTRQ:
					rcReturn = RcCheckACCTRQ((ACCTRQ *) pofctrn->pvTrn,pcbOFCList);
					break;
				case ofctypePAYEERQ:
					rcReturn = RcCheckPAYEERQ((PAYEERQ *) pofctrn->pvTrn,pcbOFCList);
					break;
				case ofctypeMAILRQ:
					rcReturn = RcCheckMAILRQ((MAILRQ *) pofctrn->pvTrn,pcbOFCList);
					break;
				}

			if (rcReturn != ALL_OK)
				goto _END;

			/* Move to next Transaction */
			pofctrn = pofctrn->pofctrnNext;
		}

		/* Process all TRNRQ's */
		while ((pofctrn) && (	(pofctrn->ofctype == ofctypeSTMTRQ) ||
								(pofctrn->ofctype == ofctypeINTRARQ)||	
								(pofctrn->ofctype == ofctypeINTERRQ)||	
								(pofctrn->ofctype == ofctypePAYMTRQ)||	
								(pofctrn->ofctype == ofctypePAYIQRQ)	))
		{
			/* Add the max number of bytes for tags */
			*pcbOFCList += cbMaxTagTRNRQ;

			switch(pofctrn->ofctype)
				{
				case ofctypeSTMTRQ:
					rcReturn = RcCheckSTMTRQ((STMTRQ *) pofctrn->pvTrn,pcbOFCList);
					break;
				case ofctypeINTRARQ:
					rcReturn = RcCheckINTRARQ((INTRARQ *) pofctrn->pvTrn,pcbOFCList);
					break;
				case ofctypeINTERRQ:
					rcReturn = RcCheckINTERRQ((INTERRQ *) pofctrn->pvTrn,pcbOFCList);
					break;
				case ofctypePAYMTRQ:
					rcReturn = RcCheckPAYMTRQ((PAYMTRQ *) pofctrn->pvTrn,pcbOFCList);
					break;
				case ofctypePAYIQRQ:
					rcReturn = RcCheckPAYIQRQ((PAYIQRQ *) pofctrn->pvTrn,pcbOFCList);
					break;
				}

			if (rcReturn != ALL_OK)
				goto _END;

			/* Move to next Transaction */
			pofctrn = pofctrn->pofctrnNext;
		}

		break;

	case ofctypeSONRS:

		/* Check the SONRS  */
		rcReturn = RcCheckSONRS((SONRS *) pofctrn->pvTrn,pcbOFCList);
		if (rcReturn != ALL_OK)
				goto _END;

		/* Move to next Transaction */
		pofctrn = pofctrn->pofctrnNext;

		/* Process any MAINTRS */ 
		while ((pofctrn) && (	(pofctrn->ofctype == ofctypeERRORRS) ||
								(pofctrn->ofctype == ofctypeACCTRS) ||
								(pofctrn->ofctype == ofctypePAYEERS) ||
								(pofctrn->ofctype == ofctypeMAILRS) ))
		{
			if (pofctrn->ofctype == ofctypeERRORRS)
				rcReturn = RcCheckERRORRS((ERRORRS *) pofctrn->pvTrn,pcbOFCList);
			else
				{
				/* Add the max number of bytes for tags */
				*pcbOFCList += cbMaxTagMAINTRS;

				switch(pofctrn->ofctype)
					{
					case ofctypeACCTRS:
						rcReturn = RcCheckACCTRS((ACCTRS *) pofctrn->pvTrn,pcbOFCList);
						break;
					case ofctypePAYEERS:
						rcReturn = RcCheckPAYEERS((PAYEERS *) pofctrn->pvTrn,pcbOFCList);
						break;
					case ofctypeMAILRS:
						rcReturn = RcCheckMAILRS((MAILRS *) pofctrn->pvTrn,pcbOFCList);
						break;
					}

				}

			if (rcReturn != ALL_OK)
				goto _END;

			/* Move to next Transaction */
			pofctrn = pofctrn->pofctrnNext;
		}
		/* Process all TRNRS's */
		while ((pofctrn) && (	(pofctrn->ofctype == ofctypeERRORRS)	||
								(pofctrn->ofctype == ofctypeSTMTRS)		||
								(pofctrn->ofctype == ofctypeINTRARS)	||
								(pofctrn->ofctype == ofctypeINTERRS)	||
								(pofctrn->ofctype == ofctypePAYMTRS)	||
								(pofctrn->ofctype == ofctypePAYIQRS)	) )
		{
			if (pofctrn->ofctype == ofctypeERRORRS)
				/* Write ERRORRS */
				rcReturn = RcCheckERRORRS((ERRORRS *) pofctrn->pvTrn,pcbOFCList);
			else
				{
				/* Add the max number of bytes for tags */
				*pcbOFCList += cbMaxTagTRNRS;

				switch(pofctrn->ofctype)
					{
					case ofctypeSTMTRS:
						rcReturn = RcCheckSTMTRS((STMTRS *) pofctrn->pvTrn,pcbOFCList);
						break;
					case ofctypeINTRARS:
						rcReturn = RcCheckINTRARS((INTRARS *) pofctrn->pvTrn,pcbOFCList);
						break;
					case ofctypeINTERRS:
						rcReturn = RcCheckINTERRS((INTERRS *) pofctrn->pvTrn,pcbOFCList);
						break;
					case ofctypePAYMTRS:
						rcReturn = RcCheckPAYMTRS((PAYMTRS *) pofctrn->pvTrn,pcbOFCList);
						break;
					case ofctypePAYIQRS:
						rcReturn = RcCheckPAYIQRS((PAYIQRS *) pofctrn->pvTrn,pcbOFCList);
 						break;

					}
				}

				if (rcReturn != ALL_OK)
				goto _END;

	   			/* Move to next Transaction */
				pofctrn = pofctrn->pofctrnNext;
			}

		break;

	case ofctypeACCTSTMT:

		/* Process all ACCTSTMT's */
		while ((pofctrn) && (pofctrn->ofctype == ofctypeACCTSTMT))
		{
			rcReturn = RcCheckACCTSTMT((ACCTSTMT *) pofctrn->pvTrn,pcbOFCList);
			if (rcReturn != ALL_OK)
				goto _END;

			/* Move to next Transaction */
			pofctrn = pofctrn->pofctrnNext;
		}

		break;

	default:
		/* The first transaction should always be a SONRQ, SONRS, or ACTSTMT */
		rcReturn = OFC_ERROR;
		goto _END;
	}


	/* There should be no more transactions */
	if (pofctrn != NULL)
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

_END:

	return rcReturn;

}

/* --------------------------------------------------------------------------------- */
int RcCheckERRORRS(ERRORRS *errorrs,int *pcbOFCList)
{
	int rcReturn;

	switch (errorrs->ofctype)
	{
	case ofctypeACCTRS:
	case ofctypePAYEERS:
	case ofctypeMAILRS:
		/* Add the max number of bytes for tags */
		*pcbOFCList += cbMaxTagMAINTRS;
		break;
	case ofctypeSTMTRS:
	case ofctypeINTRARS:
	case ofctypeINTERRS:
	case ofctypePAYMTRS:
	case ofctypePAYIQRS:
		/* Add the max number of bytes for tags */
		*pcbOFCList += cbMaxTagTRNRS;
		break;
	default:
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Verify all required pointers are valid */
	if ((errorrs->szCLTID == NULL) || (errorrs->szSTATUS == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add length of required fields */
	*pcbOFCList += strlen(errorrs->szCLTID) + strlen(errorrs->szSTATUS);

	/* Add length of optional fields */
	if (errorrs->szERROR)
		*pcbOFCList += strlen(errorrs->szERROR);

	rcReturn = ALL_OK; 

_END:

	return rcReturn;

} /* end RcCheckERRORRS */

/* --------------------------------------------------------------------------------- */
int RcCheckSONRQ(SONRQ *sonrq,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((sonrq->szSESSKEY == NULL) || (sonrq->szDTCLIENT == NULL) ||
		(sonrq->szUSERID == NULL) || (sonrq->szUSERPASS == NULL)) 
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagSONRQ;

	/* Add length of required fields */
	*pcbOFCList += strlen(sonrq->szSESSKEY) + strlen(sonrq->szDTCLIENT) +
				  strlen(sonrq->szUSERID) + strlen(sonrq->szUSERPASS);

	/* Add length of optional fields */
	if (sonrq->szNEWPASS)
		*pcbOFCList += strlen(sonrq->szNEWPASS);

	/* Check required structures */
	/* None */

	/* Check optional structures */
	/* None */

_END:

	return rcReturn;

} /* end RcCheckSONRQ */

/* --------------------------------------------------------------------------------- */
int RcCheckSONRS(SONRS *sonrs,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;


	/* Verify all required pointers are valid */
	if ((sonrs->szSTATUS == NULL) || (sonrs->szDTSERVER == NULL) ||
		(sonrs->szSESSKEY == NULL)) 
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* There can only be a SERVICE2, DAYSWITH, or DAYSREQD if there is */
	/* a SERVICE1 */
	if ((sonrs->szSERVICE1 == NULL) && 
		((sonrs->szSERVICE2) || (sonrs->szDAYSWITH) || (sonrs->szDAYSREQD)))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagSONRS;

	/* Add length of required fields */
	*pcbOFCList += strlen(sonrs->szSTATUS) + strlen(sonrs->szDTSERVER) +
				  strlen(sonrs->szSESSKEY);

	/* Add length of optional fields */
	if (sonrs->szERROR)
		*pcbOFCList += strlen(sonrs->szERROR);
	if (sonrs->szSERVICE1)
		*pcbOFCList += strlen(sonrs->szSERVICE1);
	if (sonrs->szSERVICE2)
		*pcbOFCList += strlen(sonrs->szSERVICE2);
	if (sonrs->szDAYSWITH)
		*pcbOFCList += strlen(sonrs->szDAYSWITH);
	if (sonrs->szDAYSREQD)
		*pcbOFCList += strlen(sonrs->szDAYSREQD);

	/* Check required structures */
	/* None */

	/* Check optional structures */
	/* None */

_END:

	return rcReturn;

} /* end RcCheckSONRS */

/* --------------------------------------------------------------------------------- */
int RcCheckACCTRQ(ACCTRQ *acctrq,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((acctrq->szCLTID == NULL) || (acctrq->szACTION == NULL) ||
		(acctrq->pacctACCTFROM == NULL) || (acctrq->psrqstSERVRQST1 == NULL)) 
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Cannot have a psrqstSERVRQST2 without a psrqstSERVRQST1 */
	if ((acctrq->psrqstSERVRQST2) && (acctrq->psrqstSERVRQST1 == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagACCTRQ;

	/* Add length of required fields */
	*pcbOFCList += strlen(acctrq->szCLTID) + strlen(acctrq->szACTION);

	/* Add length of optional fields */
	/* None */

	/* Check required structures */
	rcReturn = RcCheckACCOUNT((ACCOUNT *) acctrq->pacctACCTFROM,pcbOFCList);
	if (rcReturn != ALL_OK)
		goto _END;

	rcReturn = RcCheckSERVRQST((SERVRQST *) acctrq->psrqstSERVRQST1,pcbOFCList);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check optional structures */
	if (acctrq->psrqstSERVRQST2)
	{
		rcReturn = RcCheckSERVRQST((SERVRQST *) acctrq->psrqstSERVRQST2,pcbOFCList);
		if (rcReturn != ALL_OK)
			goto _END;
	}

_END:

	return rcReturn;

} /* end RcCheckACCTRQ */

/* --------------------------------------------------------------------------------- */
int RcCheckACCTRS(ACCTRS *acctrs,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((acctrs->szCLTID == NULL) || (acctrs->szSTATUS == NULL) ||
		(acctrs->psauthSERVAUTH1 == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Cannot have a psauthSERVAUTH2 without a psauthSERVAUTH1 */
	if ((acctrs->psauthSERVAUTH2) && (acctrs->psauthSERVAUTH1 == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagACCTRS;

	/* Add length of required fields */
	*pcbOFCList += strlen(acctrs->szCLTID) + strlen(acctrs->szSTATUS);

	/* Check required structures */
	/* None */

	/* Check optional structures */
	if (acctrs->psauthSERVAUTH1)
	{
		rcReturn = RcCheckSERVAUTH((SERVAUTH *) acctrs->psauthSERVAUTH1,pcbOFCList);
		if (rcReturn != ALL_OK)
			goto _END;

		if (acctrs->psauthSERVAUTH2)
		{
			rcReturn = RcCheckSERVAUTH((SERVAUTH *) acctrs->psauthSERVAUTH2,pcbOFCList);
			if (rcReturn != ALL_OK)
				goto _END;
		}
	}

_END:

	return rcReturn;

} /* end RcCheckACCTRS */

/* --------------------------------------------------------------------------------- */
int RcCheckACCOUNT(ACCOUNT *acct, int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((acct->szBANKID == NULL) || (acct->szACCTID == NULL) ||
		(acct->szACCTTYPE == NULL)) 
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagACCOUNT;

	/* Add length of required fields */
	*pcbOFCList += strlen(acct->szBANKID) + strlen(acct->szACCTID) + 
					strlen(acct->szACCTTYPE);

	/* Add length of optional fields */
	if (acct->szBRANCHID)
		*pcbOFCList += strlen(acct->szBRANCHID);

	/* Check required structures */
	/* None */

	/* Check optional structures */
	/* None */
_END:

	return rcReturn;

} /* end RcCheckACCOUNT */

/* --------------------------------------------------------------------------------- */
int RcCheckSERVRQST(SERVRQST *srqst, int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((srqst->szSERVICE == NULL) || (srqst->szACTION == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagSERVRQST;

	/* Add length of required fields */
	*pcbOFCList += strlen(srqst->szSERVICE) + strlen(srqst->szACTION);

	/* Add length of optional fields */
	/* None */

	/* Check required structures */
	/* None */

	/* Check optional structures */
	/* None */

_END:

	return rcReturn;

} /* end RcCheckSERVRQST */
/* --------------------------------------------------------------------------------- */

int RcCheckSERVAUTH(SERVAUTH *sauth, int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((sauth->szSERVICE == NULL) || (sauth->szSTATUS == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagSERVAUTH;

	/* Add length of required fields */
	*pcbOFCList += strlen(sauth->szSERVICE) + strlen(sauth->szSTATUS);

	/* Add length of optional fields */
	/* None */

	/* Check required structures */
	/* None */

	/* Check optional structures */
	/* None */

_END:

	return rcReturn;

} /* end RcCheckSERVAUTH */
/* --------------------------------------------------------------------------------- */

int RcCheckPAYEERQ(PAYEERQ *payeerq,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((payeerq->szCLTID == NULL) || (payeerq->szACTION == NULL) ||
		(payeerq->pentPAYEE == NULL) || (payeerq->szPAYACCT == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagPAYEERQ;

	/* Add length of required fields */
	*pcbOFCList += strlen(payeerq->szCLTID) + strlen(payeerq->szACTION) +
					strlen(payeerq->szPAYACCT); 

	/* Add length of optional fields */
	if (payeerq->szPAYEEID)
		*pcbOFCList += strlen(payeerq->szPAYEEID);

	rcReturn = RcCheckENTITY((ENTITY *) payeerq->pentPAYEE,pcbOFCList);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check optional structures */
	/* None */


_END:

	return rcReturn;

} /* end RcCheckPAYEERQ */

/* --------------------------------------------------------------------------------- */

int RcCheckPAYEERS(PAYEERS *payeers,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((payeers->szCLTID == NULL) || (payeers->szSTATUS == NULL) ||
		(payeers->szPAYEEID == NULL) || (payeers->szDAYSREQD == NULL) ||
		(payeers->szDAYSWITH == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagPAYEERS;

	/* Add length of required fields */
	*pcbOFCList += strlen(payeers->szCLTID) + strlen(payeers->szSTATUS) + 
					strlen(payeers->szPAYEEID) + strlen(payeers->szDAYSREQD) +
					strlen(payeers->szDAYSWITH);

	/* Add length of optional fields */
	/* None */

	/* Check required structures */
	/* None */

	/* Check optional structures */
	if (payeers->pentPAYEE)
	{
		rcReturn = RcCheckENTITY((ENTITY *) payeers->pentPAYEE,pcbOFCList);
		if (rcReturn != ALL_OK)
			goto _END;
	}

_END:

	return rcReturn;

} /* end RcCheckPAYEERS */

/* --------------------------------------------------------------------------------- */
int RcCheckENTITY(ENTITY *pent,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;


	/* Verify all required pointers are valid */
	if ((pent->szNAME1 == NULL) || (pent->szADDRESS1 == NULL) ||
		(pent->szCITY == NULL) || (pent->szSTATE == NULL) ||
		(pent->szPOSTALID == NULL) || (pent->szPHONE1 == NULL)) 
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* There can only be a szNAME2 or szNAME3, if there is a szNAME1 */
	if ((pent->szNAME1 == NULL) && 
		((pent->szNAME2) || (pent->szNAME3)))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* There can only be a szADDRESS2 or szADDRESS3, if there is a szADDRESS1 */
	if ((pent->szADDRESS1 == NULL) && 
		((pent->szADDRESS2) || (pent->szADDRESS3)))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* There can only be a szPHONE2, if there is a szPHONE1 */
	if ((pent->szPHONE1 == NULL) && (pent->szPHONE2))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagENTITY;

	/* Add length of required fields */
	*pcbOFCList += strlen(pent->szNAME1) + strlen(pent->szADDRESS1) +
		strlen(pent->szCITY) + strlen(pent->szSTATE) + 
		strlen(pent->szPOSTALID) + strlen(pent->szPHONE1);

	/* Add length of optional fields */
	if (pent->szNAME2)
		*pcbOFCList += strlen(pent->szNAME2);
	if (pent->szNAME3)
		*pcbOFCList += strlen(pent->szNAME3);
	if (pent->szADDRESS2)
		*pcbOFCList += strlen(pent->szADDRESS2);
	if (pent->szADDRESS3)
		*pcbOFCList += strlen(pent->szADDRESS3);
	if (pent->szPHONE2)
		*pcbOFCList += strlen(pent->szPHONE2);

	/* Check required structures */
	/* None */

	/* Check optional structures */
	/* None */

_END:

	return rcReturn;

} /* end RcCheckENTITY */

/* --------------------------------------------------------------------------------- */
int RcCheckMAILRQ(MAILRQ *mailrq,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((mailrq->szCLTID == NULL) || (mailrq->szACTION == NULL) ||
		(mailrq->szSERVICE == NULL) || (mailrq->pmemoMEMO == NULL)) 
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagMAILRQ;

	/* Add length of required fields */
	*pcbOFCList += strlen(mailrq->szCLTID) + strlen(mailrq->szACTION) +
					strlen(mailrq->szSERVICE); 

	/* Add length of optional fields */
	/* None */

	/* Check required structures */
	rcReturn = RcCheckMEMO((MEMO *) mailrq->pmemoMEMO ,pcbOFCList);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check optional structures */
	if (mailrq->pacctACCTFROM)
	{
		rcReturn = RcCheckACCOUNT((ACCOUNT *) mailrq->pacctACCTFROM,pcbOFCList);
		if (rcReturn != ALL_OK)
			goto _END;
	}

_END:

	return rcReturn;

} /* end RcCheckMAILRQ */

/* --------------------------------------------------------------------------------- */
int RcCheckMAILRS(MAILRS *mailrs,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((mailrs->szCLTID == NULL) || (mailrs->szSTATUS == NULL)) 
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagMAILRS;

	/* Add length of required fields */
	*pcbOFCList += strlen(mailrs->szCLTID) + strlen(mailrs->szSTATUS);

	/* Add length of optional fields */
	/* None *.

	/* Check required structures */
	/* None */

	/* Check optional structures */
	if (mailrs->pmemoMEMO)
	{
		rcReturn = RcCheckMEMO((MEMO *) mailrs->pmemoMEMO ,pcbOFCList);
		if (rcReturn != ALL_OK)
			goto _END;
	}

_END:

	return rcReturn;

} /* end RcCheckMAILRS */

/* --------------------------------------------------------------------------------- */
int RcCheckMEMO(MEMO *pmemo,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if (pmemo->szMEMO == NULL)
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagMEMO;

	/* Add length of required fields */
	*pcbOFCList += strlen(pmemo->szMEMO);

	/* Add length of optional fields */
	/* None */

	/* Check required structures */
	/* None */

	/* Check optional structures */
	if (pmemo->pmemoNext)
	{
		/* NOTE: This is a recursive call */
		rcReturn = RcCheckMEMO((MEMO *) pmemo->pmemoNext ,pcbOFCList);
		if (rcReturn != ALL_OK)
			goto _END;
	}

_END:

	return rcReturn;

} /* end RcCheckMEMO */

/* --------------------------------------------------------------------------------- */
int RcCheckSTMTRQ(STMTRQ *stmtrq,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((stmtrq->szCLTID == NULL) || (stmtrq->szACTION == NULL) ||
		(stmtrq->pacctACCTFROM == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagSTMTRQ;

	/* Add length of required fields */
	*pcbOFCList += strlen(stmtrq->szCLTID) + strlen(stmtrq->szACTION);

	/* Add length of optional fields */
	if (stmtrq->szDTSTART)
		*pcbOFCList += strlen(stmtrq->szDTSTART);
	if (stmtrq->szDTEND)
		*pcbOFCList += strlen(stmtrq->szDTEND);

	/* Check required structures */
	rcReturn = RcCheckACCOUNT((ACCOUNT *) stmtrq->pacctACCTFROM,pcbOFCList);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check optional structures */
	/* None */

_END:

	return rcReturn;

} /* end RcCheckSTMTRQ */

/* --------------------------------------------------------------------------------- */
int RcCheckSTMTRS(STMTRS *stmtrs,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((stmtrs->szCLTID == NULL) || (stmtrs->szSTATUS == NULL) ||
		(stmtrs->szDTSTART == NULL) || (stmtrs->szDTEND == NULL) ||
		(stmtrs->szLEDGER == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagSTMTRS;

	/* Add length of required fields */
	*pcbOFCList += strlen(stmtrs->szCLTID) + strlen(stmtrs->szSTATUS) +
							strlen(stmtrs->szDTSTART) + strlen(stmtrs->szDTEND) + 
							strlen(stmtrs->szLEDGER);

	/* Add length of optional fields */
	/* None */

	/* Check required structures */
	/* None */

	/* Check optional structures */
	if (stmtrs->pgtrnSTMTTRN)
	{
		rcReturn = RcCheckGENTRN((GENTRN *) stmtrs->pgtrnSTMTTRN ,pcbOFCList);
		if (rcReturn != ALL_OK)
			goto _END;
	}

_END:

	return rcReturn;

} /* end RcCheckSTMTRS */

/* --------------------------------------------------------------------------------- */
int RcCheckGENTRN(GENTRN *pgtrn,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((pgtrn->szTRNTYPE == NULL) || (pgtrn->szDTPOSTED == NULL) ||
		(pgtrn->szTRNAMT == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Cannot have both a PAYEE and a NAME */
	if ((pgtrn->szNAME) && (pgtrn->pentPAYEE))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagGENTRN;

	/* Add length of required fields */
	*pcbOFCList += strlen(pgtrn->szTRNTYPE) + strlen(pgtrn->szDTPOSTED) + 
					strlen(pgtrn->szTRNAMT);

	/* Add length of optional fields */
	if (pgtrn->szFITID)
		*pcbOFCList += strlen(pgtrn->szFITID);
	if (pgtrn->szCLTID)
		*pcbOFCList += strlen(pgtrn->szCLTID);
	if (pgtrn->szSRVRTID)
		*pcbOFCList += strlen(pgtrn->szSRVRTID);
	if (pgtrn->szCHKNUM)
		*pcbOFCList += strlen(pgtrn->szCHKNUM);
	if (pgtrn->szSIC)
		*pcbOFCList += strlen(pgtrn->szSIC);
	if (pgtrn->szPAYEEID)
		*pcbOFCList += strlen(pgtrn->szPAYEEID);
	if (pgtrn->szNAME)
		*pcbOFCList += strlen(pgtrn->szNAME);

	/* Check required structures */
	/* None */

	/* Check optional structures */
	if (pgtrn->pentPAYEE)
	{
		rcReturn = RcCheckENTITY((ENTITY *) pgtrn->pentPAYEE,pcbOFCList);
		if (rcReturn != ALL_OK)
			goto _END;
	}

	if (pgtrn->pacctACCTTO)
	{
		rcReturn = RcCheckACCOUNT((ACCOUNT *) pgtrn->pacctACCTTO,pcbOFCList);
		if (rcReturn != ALL_OK)
			goto _END;
	}

	if (pgtrn->pmemoMEMO)
	{
		rcReturn = RcCheckMEMO((MEMO *) pgtrn->pmemoMEMO ,pcbOFCList);
		if (rcReturn != ALL_OK)
			goto _END;
	}

	if (pgtrn->pgtrnNext)
	{
		/* NOTE: This is a recursive call */
		rcReturn = RcCheckGENTRN((GENTRN *) pgtrn->pgtrnNext ,pcbOFCList);
		if (rcReturn != ALL_OK)
			goto _END;
	}


_END:

	return rcReturn;

} /* end RcCheckGENTRN */


/* --------------------------------------------------------------------------------- */
int RcCheckINTRARQ(INTRARQ *pintrarq,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((pintrarq->szCLTID == NULL) || (pintrarq->szACTION == NULL) ||
		(pintrarq->pacctACCTFROM == NULL) || (pintrarq->pacctACCTTO == NULL) ||
		(pintrarq->szTRNAMT == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagINTRARQ;

	/* Add length of required fields */
	*pcbOFCList += strlen(pintrarq->szCLTID) + strlen(pintrarq->szACTION) +
					strlen(pintrarq->szTRNAMT);

	/* Add length of optional fields */
	/* None */

	/* Check required structures */
	rcReturn = RcCheckACCOUNT((ACCOUNT *) pintrarq->pacctACCTFROM,pcbOFCList);
	if (rcReturn != ALL_OK)
		goto _END;

	rcReturn = RcCheckACCOUNT((ACCOUNT *) pintrarq->pacctACCTTO,pcbOFCList);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check optional structures */
	if (pintrarq->pmemoMEMO)
	{
		rcReturn = RcCheckMEMO((MEMO *) pintrarq->pmemoMEMO ,pcbOFCList);
		if (rcReturn != ALL_OK)
			goto _END;
	}

_END:

	return rcReturn;

} /* end RcCheckINTRARQ */


/* --------------------------------------------------------------------------------- */
int RcCheckINTRARS(INTRARS *intrars,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((intrars->szCLTID == NULL) || (intrars->szSTATUS == NULL) ||
		(intrars->szSRVRTID == NULL)) 
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagINTRARS;

	/* Add length of required fields */
	*pcbOFCList += strlen(intrars->szCLTID) + strlen(intrars->szSTATUS) +
					strlen(intrars->szSRVRTID);

	/* Add length of optional fields */
	if (intrars->szDTPOSTED)
		*pcbOFCList += strlen(intrars->szDTPOSTED);

	/* Check required structures */
	/* None */

	/* Check optional structures */
	/* None */

_END:

	return rcReturn;

} /* end RcCheckINTRARS */

/* --------------------------------------------------------------------------------- */
int RcCheckINTERRQ(INTERRQ *pinterrq,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((pinterrq->szCLTID == NULL) || (pinterrq->szACTION == NULL) ||
		(pinterrq->pacctACCTFROM == NULL) || (pinterrq->szNAME == NULL) ||
		(pinterrq->szPAYACCT == NULL) ||
		(pinterrq->szTRNAMT == NULL) || (pinterrq->szDTDUE == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Both pacctACCTTO and szPAYEEID cannot be NULL */
	if ((pinterrq->pacctACCTTO == NULL) && (pinterrq->szPAYEEID == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagINTERRQ;

	/* Add length of required fields */
	*pcbOFCList += strlen(pinterrq->szCLTID) + strlen(pinterrq->szACTION) +
					strlen(pinterrq->szTRNAMT) + strlen(pinterrq->szDTDUE) + 
					strlen(pinterrq->szPAYACCT) + strlen(pinterrq->szNAME);

	/* Add length of optional fields */
	if (pinterrq->szSRVRTID)
		*pcbOFCList += strlen(pinterrq->szSRVRTID);

	/* Check required structures */

	/* There is either an ACCTTO or a PAYEEID */
	if (pinterrq->pacctACCTTO)
	{
		rcReturn = RcCheckACCOUNT((ACCOUNT *) pinterrq->pacctACCTTO,pcbOFCList);
		if (rcReturn != ALL_OK)
			goto _END;
	}
	else
		*pcbOFCList += strlen(pinterrq->szPAYEEID);

	rcReturn = RcCheckACCOUNT((ACCOUNT *) pinterrq->pacctACCTFROM,pcbOFCList);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check optional structures */
	if (pinterrq->pmemoMEMO)
	{
		rcReturn = RcCheckMEMO((MEMO *) pinterrq->pmemoMEMO ,pcbOFCList);
		if (rcReturn != ALL_OK)
			goto _END;
	}

_END:

	return rcReturn;

} /* end RcCheckINTERRQ */

/* --------------------------------------------------------------------------------- */
int RcCheckINTERRS(INTERRS *interrs,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((interrs->szCLTID == NULL) || (interrs->szSTATUS == NULL) ||
		(interrs->szSRVRTID == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagINTERRS;

	/* Add length of required fields */
	*pcbOFCList += strlen(interrs->szCLTID) + strlen(interrs->szSTATUS) +
					strlen(interrs->szSRVRTID);

	/* Add length of optional fields */
	if (interrs->szDTPOSTED)
		*pcbOFCList += strlen(interrs->szDTPOSTED);
	if (interrs->szCHKNUM)
		*pcbOFCList += strlen(interrs->szCHKNUM);

	/* Check required structures */
	/* None */

	/* Check optional structures */
	/* None */

_END:

	return rcReturn;

} /* end RcCheckINTERRS */


/* --------------------------------------------------------------------------------- */
int RcCheckPAYMTRQ(PAYMTRQ *ppaymtrq,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((ppaymtrq->szCLTID == NULL) || (ppaymtrq->szACTION == NULL) ||
		(ppaymtrq->pacctACCTFROM == NULL) || (ppaymtrq->szTRNAMT == NULL) || 
		(ppaymtrq->szDTDUE == NULL) || (ppaymtrq->szPAYACCT == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagPAYMTRQ;

	/* Add length of required fields */
	*pcbOFCList += strlen(ppaymtrq->szCLTID) + strlen(ppaymtrq->szACTION) +
					strlen(ppaymtrq->szTRNAMT) + strlen(ppaymtrq->szDTDUE) + 
					strlen(ppaymtrq->szPAYACCT);

	/* Add length of optional fields */
	if (ppaymtrq->szPAYEEID)
		*pcbOFCList += strlen(ppaymtrq->szPAYEEID);
	if (ppaymtrq->szSRVRTID)
		*pcbOFCList += strlen(ppaymtrq->szSRVRTID);

	/* Check required structures */
	rcReturn = RcCheckACCOUNT((ACCOUNT *) ppaymtrq->pacctACCTFROM,pcbOFCList);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check optional structures */
	if (ppaymtrq->pentPAYEE)
	{
		rcReturn = RcCheckENTITY((ENTITY *) ppaymtrq->pentPAYEE,pcbOFCList);
		if (rcReturn != ALL_OK)
			goto _END;
	}

	if (ppaymtrq->pmemoMEMO)
	{
		rcReturn = RcCheckMEMO((MEMO *) ppaymtrq->pmemoMEMO ,pcbOFCList);
		if (rcReturn != ALL_OK)
			goto _END;
	}

_END:

	return rcReturn;

} /* end RcCheckPAYMTRQ	 */

/* --------------------------------------------------------------------------------- */
int RcCheckPAYMTRS(PAYMTRS *paymtrs,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((paymtrs->szCLTID == NULL) || (paymtrs->szSTATUS == NULL) ||
		(paymtrs->szSRVRTID == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagPAYMTRS;

	/* Add length of required fields */
	*pcbOFCList += strlen(paymtrs->szCLTID) + strlen(paymtrs->szSTATUS) +
					strlen(paymtrs->szSRVRTID);

	/* Add length of optional fields */
	if (paymtrs->szPAYEEID)
		*pcbOFCList += strlen(paymtrs->szPAYEEID);

	/* Check required structures */
	/* None */

	/* Check optional structures */
	/* None */

_END:

	return rcReturn;

} /* end RcCheckPAYMTRS */


/* --------------------------------------------------------------------------------- */
int RcCheckPAYIQRQ(PAYIQRQ *ppayiqrq,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((ppayiqrq->szCLTID == NULL) || (ppayiqrq->szACTION == NULL) ||
		(ppayiqrq->szSRVRTID == NULL) || (ppayiqrq->pmemoMEMO == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagPAYIQRQ;

	/* Add length of required fields */
	*pcbOFCList += strlen(ppayiqrq->szCLTID) + strlen(ppayiqrq->szACTION) +
					strlen(ppayiqrq->szSRVRTID);

	/* Add length of optional fields */
	/* None */

	/* Check required structures */
	rcReturn = RcCheckMEMO((MEMO *) ppayiqrq->pmemoMEMO ,pcbOFCList);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check optional structures */
	/* None */

_END:

	return rcReturn;

} /* end RcCheckPAYIQRQ	 */

/* --------------------------------------------------------------------------------- */
int RcCheckPAYIQRS(PAYIQRS *payiqrs,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((payiqrs->szCLTID == NULL) || (payiqrs->szSTATUS == NULL) ||
		(payiqrs->szSRVRTID == NULL))
	{	
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagPAYIQRS;

	/* Add length of required fields */
	*pcbOFCList += strlen(payiqrs->szCLTID) + strlen(payiqrs->szSTATUS) +
					strlen(payiqrs->szSRVRTID);

	/* Add length of optional fields */
	/* None */

	/* Check required structures */
	/* None */

	/* Check optional structures */
	if (payiqrs->pmemoMEMO)
	{
		rcReturn = RcCheckMEMO((MEMO *) payiqrs->pmemoMEMO ,pcbOFCList);
		if (rcReturn != ALL_OK)
			goto _END;
	}

_END:

	return rcReturn;

} /* end RcCheckPAYIQRS */

/* --------------------------------------------------------------------------------- */
int RcCheckACCTSTMT(ACCTSTMT *acctstmt,int *pcbOFCList)
{
	int rcReturn;  /* function return code */

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify all required pointers are valid */
	if ((acctstmt->pacctACCTFROM == NULL) || (acctstmt->szDTSTART == NULL) ||
		(acctstmt->szDTEND == NULL) || (acctstmt->szLEDGER== NULL) ||
		(acctstmt->pgtrnSTMTTRN == NULL) )
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Add the max number of bytes for tags */
	*pcbOFCList += cbMaxTagACCTSTMT;

	/* Add length of required fields */
	*pcbOFCList += strlen(acctstmt->szDTSTART) + strlen(acctstmt->szDTEND) +
					strlen(acctstmt->szLEDGER);

	/* Add length of optional fields */
	/* None */

	/* Check required structures */
	rcReturn = RcCheckACCOUNT((ACCOUNT *) acctstmt->pacctACCTFROM,pcbOFCList);
	if (rcReturn != ALL_OK)
		goto _END;

	rcReturn = RcCheckGENTRN((GENTRN *) acctstmt->pgtrnSTMTTRN ,pcbOFCList);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check optional structures */
	/* None */

_END:

	return rcReturn;

} /* end RcCheckACCTSTMT */
