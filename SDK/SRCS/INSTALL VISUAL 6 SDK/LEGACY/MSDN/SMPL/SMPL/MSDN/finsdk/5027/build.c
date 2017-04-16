/* --------------------------------------------------------------------------------- */
/* Copyright(c) 1991-1996 Microsoft Corporation.  All rights reserved. */
/* --------------------------------------------------------------------------------- */
/* File: BUILD.C */
/* */
/* Contains functions necessary to build an OFC document from an OFC Linked List */
/* */
/* 02/29/95	Derek Hazeur - Created */
/* --------------------------------------------------------------------------------- */
/* Standard Includes */
#include <stdio.h>
#include <string.h>
#include <malloc.h>

/* Other includes */
#include "ofcdtd.h"		/* OFC List data types  */
#include "validlst.h"	/* Prototypes for OFC List Validation  */
#include "pbtypes.h"	/* Types used for Parsing/Building */
#include "build.h"		/* Include file for this file */

/* --------------------------------------------------------------------------------- */
/*							Local Function Prototypes */
/* --------------------------------------------------------------------------------- */
int RcBuildOFC(OFCDOCTYPE odt,OFCDOC *pofcdoc,void **ppvRequest, int *pcbRequest);

void BuildSONRQ(SONRQ *sonrq,char **ppchCurr);
void BuildSONRS(SONRS *sonrs,char **ppchCurr);

void BuildACCTRQ(ACCTRQ *acctrq,char **ppchCurr);
void BuildACCTRS(ACCTRS *acctrs, char **ppchCurr);
void BuildACCOUNT(ACCOUNT *acct,char **ppchCurr);
void BuildSERVRQST(SERVRQST *srqst, char **ppchCurr);
void BuildSERVAUTH(SERVAUTH *sauth,char **ppchCurr);

void BuildPAYEERQ(PAYEERQ *payeerq,char **ppchCurr);
void BuildPAYEERS(PAYEERS *payeers,char **ppchCurr);
void BuildENTITY(ENTITY *pent,char **ppchCurr);

void BuildMAILRQ(MAILRQ *mailrq,char **ppchCurr);
void BuildMAILRS(MAILRS *mailrs,char **ppchCurr);
void BuildMEMO(MEMO *pmemo,char ** ppchCurr);

void BuildSTMTRQ(STMTRQ *stmtrq,char ** ppchCurr);
void BuildSTMTRS(STMTRS *stmtrs,char ** ppchCurr);
void BuildSTMTTRN(GENTRN *pgtrn,char ** ppchCurr);
void BuildACCTSTMT(ACCTSTMT *acctstmt,char ** ppchCurr);

void BuildPAYMTRQ(PAYMTRQ *ppaymtrq, char **ppchCurr);
void BuildPAYMTRS(PAYMTRS *ppaymtrs, char **ppchCurr);

void BuildPAYIQRQ(PAYIQRQ *ppayiqrq,char ** ppchCurr);
void BuildPAYIQRS(PAYIQRS *payiqrs, char **ppchCurr);

void BuildERRORRS(ERRORRS *errorrs,char **ppchCurr);

void BuildINTRARQ(INTRARQ *intrarq, char **ppchCurr);
void BuildINTRARS(INTRARS *intrars, char **ppchCurr);

void BuildINTERRQ(INTERRQ *interrq, char **ppchCurr);
void BuildINTERRS(INTERRS *interrs, char **ppchCurr);
/* --------------------------------------------------------------------------------- */
int RcBuildOFC(OFCDOCTYPE odt,OFCDOC *pofcdoc,void **ppvRequest, int *pcbRequest)
{
	OFCTRN *pofctrn;
	int rcReturn;  /* function return code */
	char * pchCurr;

	/* Initialize return code */
	rcReturn = ALL_OK;

	/* Verify that we have a valid OFCDOC */
	if ((pofcdoc == NULL) || (pcbRequest == NULL))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Validate the List, also counts required buffer size */
	rcReturn = RcValidateOFCList(pofcdoc,pcbRequest);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate the Output Buffer */
	*ppvRequest = malloc((*pcbRequest + 1) * sizeof(char));
	if (!(*ppvRequest))
	{
		rcReturn = NO_MEMORY;
		goto _END;
	}

	/* Assign pointer to current position */
	pchCurr = *ppvRequest; 

	/* Write Required fields */
	sprintf(pchCurr,"<OFC>\r\n<DTD>%s\r\n<CPAGE>%s\r\n",pofcdoc->szDTD,pofcdoc->szCPAGE);
	pchCurr += strlen(pchCurr);

	/* Start at the first transaction */
	pofctrn = pofcdoc->pofctrn;

	switch (pofctrn->ofctype)
	{
	case ofctypeSONRQ:

		/* Do sanity check for REQUEST */
		if (odt != odtREQUEST)
		{
			rcReturn = OFC_ERROR;
			goto _END;
		}

		/* Check the SONRQ  */
		BuildSONRQ((SONRQ *) pofctrn->pvTrn,&pchCurr);

		/* Move to next Transaction */
		pofctrn = pofctrn->pofctrnNext;

		/* Process all MAINTRQ's */
		/* Process all ACCTRQ's */
		while ((pofctrn) && 
			(	(pofctrn->ofctype == ofctypeACCTRQ) ||
				(pofctrn->ofctype == ofctypePAYEERQ)||
				(pofctrn->ofctype == ofctypeMAILRQ)	))
		{
			/* Write MAINTRQ */
			sprintf(pchCurr,"<MAINTRQ>\r\n");
			pchCurr += strlen(pchCurr);
			switch(pofctrn->ofctype)
				{
				case ofctypeACCTRQ:
					/* Write ACCTRQ */
					BuildACCTRQ((ACCTRQ *) pofctrn->pvTrn,&pchCurr);
					break;
				case ofctypePAYEERQ:
					/* Write PAYEERQ */
					BuildPAYEERQ((PAYEERQ *) pofctrn->pvTrn,&pchCurr);
					break;
				case ofctypeMAILRQ:
					/* Write MAILRQ */
					BuildMAILRQ((MAILRQ *) pofctrn->pvTrn,&pchCurr);
					break;
				}

			/* Write /MAINTRQ */
			sprintf(pchCurr,"</MAINTRQ>\r\n");
			pchCurr += strlen(pchCurr);

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
			/* Write TRNRQ */
			sprintf(pchCurr,"<TRNRQ>\r\n");
			pchCurr += strlen(pchCurr);

			switch(pofctrn->ofctype)
				{
				case ofctypeSTMTRQ:
					/* Write STMTRQ */
					BuildSTMTRQ((STMTRQ *) pofctrn->pvTrn,&pchCurr);
					break;
				case ofctypeINTRARQ:
					/* Write INTRARQ */
					BuildINTRARQ((INTRARQ *) pofctrn->pvTrn,&pchCurr);
					break;
				case ofctypeINTERRQ:
					/* Write INTERRQ */
					BuildINTERRQ((INTERRQ *) pofctrn->pvTrn,&pchCurr);
					break;
				case ofctypePAYMTRQ:
					/* Write PAYMTRQ */
					BuildPAYMTRQ((PAYMTRQ *) pofctrn->pvTrn,&pchCurr);
					break;
				case ofctypePAYIQRQ:
					/* Write PAYIQRQ */
					BuildPAYIQRQ((PAYIQRQ *) pofctrn->pvTrn,&pchCurr);
					break;
				}

			/* Write /TRNRQ */
			sprintf(pchCurr,"</TRNRQ>\r\n");
			pchCurr += strlen(pchCurr);

			/* Move to next Transaction */
			pofctrn = pofctrn->pofctrnNext;
		}
		break;
	case ofctypeSONRS:

		/* Do sanity check for RESPONSE */
		if (odt != odtRESPONSE)
		{
			rcReturn = OFC_ERROR;
			goto _END;
		}

		/* Check the SONRS  */
		BuildSONRS((SONRS *) pofctrn->pvTrn,&pchCurr);

		/* Move to next Transaction */
		pofctrn = pofctrn->pofctrnNext;

		/* Process any MAINTRS */ 
		while ((pofctrn) && (	(pofctrn->ofctype == ofctypeERRORRS) ||
								(pofctrn->ofctype == ofctypeACCTRS) ||
								(pofctrn->ofctype == ofctypePAYEERS) ||
								(pofctrn->ofctype == ofctypeMAILRS) ))
		{
			if (pofctrn->ofctype == ofctypeERRORRS)
				/* Write ERRORRS */
				BuildERRORRS((ERRORRS *) pofctrn->pvTrn,&pchCurr);
			else
				{
				/* Write MAINTRS */
				sprintf(pchCurr,"<MAINTRS>\r\n");
				pchCurr += strlen(pchCurr);

				switch(pofctrn->ofctype)
					{
					case ofctypeACCTRS:
						/* Write ACCTRS */
						BuildACCTRS((ACCTRS *) pofctrn->pvTrn,&pchCurr);
						break;
					case ofctypePAYEERS:
						/* Write PAYEERS */
						BuildPAYEERS((PAYEERS *) pofctrn->pvTrn,&pchCurr);
						break;
					case ofctypeMAILRS:
						/* Write MAILRS */
						BuildMAILRS((MAILRS *) pofctrn->pvTrn,&pchCurr);
						break;
					}

				/* Write /MAINTRS */
				sprintf(pchCurr,"</MAINTRS>\r\n");
				pchCurr += strlen(pchCurr);
				}
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
				BuildERRORRS((ERRORRS *) pofctrn->pvTrn,&pchCurr);
			else
				{
				/* Write TRNRS */
				sprintf(pchCurr,"<TRNRS>\r\n");
				pchCurr += strlen(pchCurr);

				switch(pofctrn->ofctype)
					{
					case ofctypeSTMTRS:
						/* Write STMTRS */
						BuildSTMTRS((STMTRS *) pofctrn->pvTrn,&pchCurr);
						break;
					case ofctypeINTRARS:
						/* Write INTRARS */
						BuildINTRARS((INTRARS *) pofctrn->pvTrn,&pchCurr);
						break;
					case ofctypeINTERRS:
						/* Write INTERRS */
						BuildINTERRS((INTERRS *) pofctrn->pvTrn,&pchCurr);
						break;
					case ofctypePAYMTRS:
						/* Write PAYMTRS */
						BuildPAYMTRS((PAYMTRS *) pofctrn->pvTrn,&pchCurr);
						break;
					case ofctypePAYIQRS:
						/* Write PAYIQRS */
						BuildPAYIQRS((PAYIQRS *) pofctrn->pvTrn,&pchCurr);
 						break;

					}

					/* Write /TRNTRS */
					sprintf(pchCurr,"</TRNRS>\r\n");
					pchCurr += strlen(pchCurr);
				}
			/* Move to next Transaction */
			pofctrn = pofctrn->pofctrnNext;

		}

		break;

	case ofctypeACCTSTMT:
		/* Do sanity check for STATEMENT */
		if (odt != odtSTATEMENT)
		{
			rcReturn = OFC_ERROR;
			goto _END;
		}

		while ((pofctrn) && (pofctrn->ofctype == ofctypeACCTSTMT))
		{
			/* Write ACCTSTMT */
			BuildACCTSTMT((ACCTSTMT *) pofctrn->pvTrn,&pchCurr);

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

	/* Write Required fields */
	sprintf(pchCurr,"</OFC>");
	pchCurr += strlen(pchCurr);

	*pcbRequest = strlen(*ppvRequest);
_END:

	return rcReturn;

}

/* --------------------------------------------------------------------------------- */
void BuildERRORRS(ERRORRS *errorrs,char **ppchCurr)
{
	switch (errorrs->ofctype)
	{
	case ofctypeACCTRS:
	case ofctypePAYEERS:
	case ofctypeMAILRS:
		/* Write Begin Tag */
		sprintf(*ppchCurr,"<MAINTRS>\r\n");
		*ppchCurr += strlen(*ppchCurr);
		break;
	case ofctypeSTMTRS:
	case ofctypeINTRARS:
	case ofctypeINTERRS:
	case ofctypePAYMTRS:
	case ofctypePAYIQRS:
	default:
		/* Write Begin Tag */
		sprintf(*ppchCurr,"<TRNRS>\r\n");
		*ppchCurr += strlen(*ppchCurr);
		break;
	}

	/* Write CLTID and ACTION from Parent */
	sprintf(*ppchCurr,"<CLTID>%s\r\n<STATUS>%s\r\n",errorrs->szCLTID,errorrs->szSTATUS);
	*ppchCurr += strlen(*ppchCurr);

	/* Write ERROR (Optional) */
	if (errorrs->szERROR)
	{
		sprintf(*ppchCurr,"<ERROR>%s\r\n",errorrs->szERROR);
		*ppchCurr += strlen(*ppchCurr);
	}

	switch (errorrs->ofctype)
	{
	case ofctypeACCTRS:
	case ofctypePAYEERS:
	case ofctypeMAILRS:
		/* Write Begin Tag */
		sprintf(*ppchCurr,"</MAINTRS>\r\n");
		*ppchCurr += strlen(*ppchCurr);
		break;
	case ofctypeSTMTRS:
	case ofctypeINTRARS:
	case ofctypeINTERRS:
	case ofctypePAYMTRS:
	case ofctypePAYIQRS:
	default:
		/* Write Begin Tag */
		sprintf(*ppchCurr,"</TRNRS>\r\n");
		*ppchCurr += strlen(*ppchCurr);
		break;
	}

} /* end BuildERRORRS */


/* --------------------------------------------------------------------------------- */
void BuildSONRQ(SONRQ *sonrq,char **ppchCurr)
{
	/* Write Begin Tag */
	sprintf(*ppchCurr,"<SONRQ>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write Required fields */
	sprintf(*ppchCurr,"<SESSKEY>%s\r\n<DTCLIENT>%s\r\n<USERID>%s\r\n<USERPASS>%s\r\n",
						sonrq->szSESSKEY,sonrq->szDTCLIENT,sonrq->szUSERID,
						sonrq->szUSERPASS);
	*ppchCurr += strlen(*ppchCurr);

	/* Write optional fields */
	if (sonrq->szNEWPASS)
	{
		sprintf(*ppchCurr,"<NEWPASS>%s\r\n",sonrq->szNEWPASS);
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write /SONRQ */
	sprintf(*ppchCurr,"</SONRQ>\r\n");
	*ppchCurr += strlen(*ppchCurr);


} /* end BuildSONRQ */

/* --------------------------------------------------------------------------------- */
void BuildSONRS(SONRS *sonrs,char **ppchCurr)
{
	/* Write Begin Tag */
	sprintf(*ppchCurr,"<SONRS>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write STATUS, DTSERVER */
	sprintf(*ppchCurr,"<STATUS>%s\r\n<DTSERVER>%s\r\n",
						sonrs->szSTATUS,sonrs->szDTSERVER);
	*ppchCurr += strlen(*ppchCurr);

	/* Write ERROR (Optional) */
	if (sonrs->szERROR)
	{
		sprintf(*ppchCurr,"<ERROR>%s\r\n",sonrs->szERROR);
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write SESSKEY  */
	sprintf(*ppchCurr,"<SESSKEY>%s\r\n",sonrs->szSESSKEY);
	*ppchCurr += strlen(*ppchCurr);

	/* Write SERVICE1 (Optional) */
	if (sonrs->szSERVICE1)
	{
		sprintf(*ppchCurr,"<SERVICE>%s\r\n",sonrs->szSERVICE1);
		*ppchCurr += strlen(*ppchCurr);

		/* Write SERVICE2 (Optional) */
		if (sonrs->szSERVICE2)
		{
			sprintf(*ppchCurr,"<SERVICE>%s\r\n",sonrs->szSERVICE2);
			*ppchCurr += strlen(*ppchCurr);
		}

		/* Write DAYSREQD (Optional) */
		if (sonrs->szDAYSREQD)
		{
			sprintf(*ppchCurr,"<DAYSREQD>%s\r\n",sonrs->szDAYSREQD);
			*ppchCurr += strlen(*ppchCurr);
		}

		/* Write DAYSWITH (Optional) */
		if (sonrs->szDAYSWITH)
		{
			sprintf(*ppchCurr,"<DAYSWITH>%s\r\n",sonrs->szDAYSWITH);
			*ppchCurr += strlen(*ppchCurr);
		}
	}

	/* Write /SONRS */
	sprintf(*ppchCurr,"</SONRS>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildSONRS */

/* --------------------------------------------------------------------------------- */
void BuildACCTRQ(ACCTRQ *acctrq,char **ppchCurr)
{
	/* Write CLTID and ACTION from Parent */
	sprintf(*ppchCurr,"<CLTID>%s\r\n<ACTION>%s\r\n",acctrq->szCLTID,acctrq->szACTION);
	*ppchCurr += strlen(*ppchCurr);

	/* Write Begin Tag */
	sprintf(*ppchCurr,"<ACCTRQ>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write ACCTFROM */
	sprintf(*ppchCurr,"<ACCTFROM>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write ACCOUNT */
	BuildACCOUNT((ACCOUNT *) acctrq->pacctACCTFROM,ppchCurr);

	/* Write /ACCTFROM */
	sprintf(*ppchCurr,"</ACCTFROM>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write SERVRQST */
	BuildSERVRQST((SERVRQST *) acctrq->psrqstSERVRQST1,ppchCurr);

	/* Write SERVRQST (Optional) */
	if (acctrq->psrqstSERVRQST2)
	{
		BuildSERVRQST((SERVRQST *) acctrq->psrqstSERVRQST2,ppchCurr);
	}

	/* Write End Tag */
	sprintf(*ppchCurr,"</ACCTRQ>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildACCTRQ */

/* --------------------------------------------------------------------------------- */
void BuildACCTRS(ACCTRS *acctrs, char **ppchCurr)
{
	/* Write CLTID and STATUS from Parent */
	sprintf(*ppchCurr,"<CLTID>%s\r\n<STATUS>%s\r\n",acctrs->szCLTID,acctrs->szSTATUS);
	*ppchCurr += strlen(*ppchCurr);

	/* Write Begin Tag */
	sprintf(*ppchCurr,"<ACCTRS>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write SERVAUTH1 */
	BuildSERVAUTH((SERVAUTH *) acctrs->psauthSERVAUTH1,ppchCurr);

	/* Write psrqstSERVAUTH2 (Optional) */
	if (acctrs->psauthSERVAUTH2)
	{
		BuildSERVAUTH((SERVAUTH *) acctrs->psauthSERVAUTH2,ppchCurr);
	}

	/* Write End Tag */
	sprintf(*ppchCurr,"</ACCTRS>\r\n");
	*ppchCurr += strlen(*ppchCurr);


} /* end BuildACCTRS */

/* --------------------------------------------------------------------------------- */
void BuildACCOUNT(ACCOUNT *acct, char **ppchCurr)
{
	/* Write Begin Tag */
	sprintf(*ppchCurr,"<ACCOUNT>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write Other Fields, BRANCHID is optional  */
	if (acct->szBRANCHID)
	{	
		sprintf(*ppchCurr,"<BANKID>%s\r\n<BRANCHID>%s\r\n<ACCTID>%s\r\n<ACCTTYPE>%s\r\n",
				acct->szBANKID,acct->szBRANCHID,acct->szACCTID,acct->szACCTTYPE);
	}
	else
	{
		sprintf(*ppchCurr,"<BANKID>%s\r\n<ACCTID>%s\r\n<ACCTTYPE>%s\r\n",
				acct->szBANKID,acct->szACCTID,acct->szACCTTYPE);
	}
	*ppchCurr += strlen(*ppchCurr);

	/* Write End Tag */
	sprintf(*ppchCurr,"</ACCOUNT>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildACCOUNT */

/* --------------------------------------------------------------------------------- */
void BuildSERVRQST(SERVRQST *srqst, char **ppchCurr)
{
	/* Write Begin Tag */
	sprintf(*ppchCurr,"<SERVRQST>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write Required Fields */
	sprintf(*ppchCurr,"<SERVICE>%s\r\n<ACTION>%s\r\n",
				srqst->szSERVICE,srqst->szACTION);
	*ppchCurr += strlen(*ppchCurr);

	/* Write End Tag */
	sprintf(*ppchCurr,"</SERVRQST>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildSERVRQST */

/* --------------------------------------------------------------------------------- */

void BuildSERVAUTH(SERVAUTH *sauth,char **ppchCurr)
{
	/* Write Begin Tag */
	sprintf(*ppchCurr,"<SERVAUTH>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write Required Fields */
	sprintf(*ppchCurr,"<SERVICE>%s\r\n<STATUS>%s\r\n",
				sauth->szSERVICE,sauth->szSTATUS);
	*ppchCurr += strlen(*ppchCurr);

	/* Write End Tag */
	sprintf(*ppchCurr,"</SERVAUTH>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildSERVAUTH */

/* --------------------------------------------------------------------------------- */
void BuildPAYEERQ(PAYEERQ *payeerq,char **ppchCurr)
{
	/* Write CLTID and ACTION from Parent */
	sprintf(*ppchCurr,"<CLTID>%s\r\n<ACTION>%s\r\n",payeerq->szCLTID,payeerq->szACTION);
	*ppchCurr += strlen(*ppchCurr);

	/* Write Begin Tag */
	sprintf(*ppchCurr,"<PAYEERQ>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write PAYEE */
	sprintf(*ppchCurr,"<PAYEE>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write ENTITY */
	BuildENTITY((ENTITY *) payeerq->pentPAYEE,ppchCurr);

	/* Write /PAYEE */
	sprintf(*ppchCurr,"</PAYEE>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write PAYEEID (optional) */
	if (payeerq->szPAYEEID)
	{
		sprintf(*ppchCurr,"<PAYEEID>%s\r\n",payeerq->szPAYEEID);
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write PAYACCT */
	sprintf(*ppchCurr,"<PAYACCT>%s\r\n",payeerq->szPAYACCT);
	*ppchCurr += strlen(*ppchCurr);


	/* Write End Tag */
	sprintf(*ppchCurr,"</PAYEERQ>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildPAYEERQ */

/* --------------------------------------------------------------------------------- */
void BuildPAYEERS(PAYEERS *payeers,char ** ppchCurr)
{
	/* Write CLTID and STATUS from Parent */
	sprintf(*ppchCurr,"<CLTID>%s\r\n<STATUS>%s\r\n",payeers->szCLTID,payeers->szSTATUS);
	*ppchCurr += strlen(*ppchCurr);

	/* Write Begin Tag */
	sprintf(*ppchCurr,"<PAYEERS>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write PAYEEID */
	sprintf(*ppchCurr,"<PAYEEID>%s\r\n",payeers->szPAYEEID);
	*ppchCurr += strlen(*ppchCurr);

	/* Write PAYEE (Optional) */
	if (payeers->pentPAYEE)
	{
		/* Write PAYEE */
		sprintf(*ppchCurr,"<PAYEE>\r\n");
		*ppchCurr += strlen(*ppchCurr);

		/* Write ENTITY */
		BuildENTITY((ENTITY *) payeers->pentPAYEE,ppchCurr);

		/* Write /PAYEE */
		sprintf(*ppchCurr,"</PAYEE>\r\n");
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write DAYSREQD, DAYSWITH */
	sprintf(*ppchCurr,"<DAYSREQD>%s\r\n<DAYSWITH>%s\r\n",payeers->szDAYSREQD,
						payeers->szDAYSWITH);
	*ppchCurr += strlen(*ppchCurr);

	/* Write End Tag */
	sprintf(*ppchCurr,"</PAYEERS>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildPAYEERS */

/* --------------------------------------------------------------------------------- */
void BuildENTITY(ENTITY *pent,char **ppchCurr)
{
	/* Write Begin Tag */
	sprintf(*ppchCurr,"<ENTITY>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write NAME1 (optional) */
	sprintf(*ppchCurr,"<NAME>%s\r\n",pent->szNAME1);
	*ppchCurr += strlen(*ppchCurr);

	/* Write NAME2 (optional) */
	if (pent->szNAME2)
	{
		sprintf(*ppchCurr,"<NAME>%s\r\n",pent->szNAME2);
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write NAME3 (optional) */
	if (pent->szNAME3)
	{
		sprintf(*ppchCurr,"<NAME>%s\r\n",pent->szNAME3);
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write ADDRESS1 */
	sprintf(*ppchCurr,"<ADDRESS>%s\r\n",pent->szADDRESS1);
	*ppchCurr += strlen(*ppchCurr);

	/* Write ADDRESS3 (optional) */
	if (pent->szADDRESS2)
	{
		sprintf(*ppchCurr,"<ADDRESS>%s\r\n",pent->szADDRESS2);
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write ADDRESS3 (optional) */
	if (pent->szADDRESS3)
	{
		sprintf(*ppchCurr,"<ADDRESS>%s\r\n",pent->szADDRESS3);
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Verify other fields PHONE 2 is optional */
	if (pent->szPHONE2)
	{
		sprintf(*ppchCurr,"<CITY>%s\r\n<STATE>%s\r\n<POSTALID>%s\r\n<PHONE>%s\r\n<PHONE>%s\r\n",
					pent->szCITY,pent->szSTATE,pent->szPOSTALID,pent->szPHONE1,pent->szPHONE2);
	}
	else
	{
		sprintf(*ppchCurr,"<CITY>%s\r\n<STATE>%s\r\n<POSTALID>%s\r\n<PHONE>%s\r\n",
					pent->szCITY,pent->szSTATE,pent->szPOSTALID,pent->szPHONE1);
	}
	*ppchCurr += strlen(*ppchCurr);

	/* Write End Tag */
	sprintf(*ppchCurr,"</ENTITY>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildENTITY */

/* --------------------------------------------------------------------------------- */
void BuildMAILRQ(MAILRQ *mailrq,char **ppchCurr)
{
	/* Write CLTID and ACTION from Parent */
	sprintf(*ppchCurr,"<CLTID>%s\r\n<ACTION>%s\r\n",mailrq->szCLTID,mailrq->szACTION);
	*ppchCurr += strlen(*ppchCurr);

	/* Write Begin Tag */
	sprintf(*ppchCurr,"<MAILRQ>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write SERVICE */
	sprintf(*ppchCurr,"<SERVICE>%s\r\n",mailrq->szSERVICE);
	*ppchCurr += strlen(*ppchCurr);

	/* Write ACCTFROM (Optional) */
	if (mailrq->pacctACCTFROM)
	{
		sprintf(*ppchCurr,"<ACCTFROM>\r\n");
		*ppchCurr += strlen(*ppchCurr);

		/* Write ACCOUNT */
		BuildACCOUNT((ACCOUNT *) mailrq->pacctACCTFROM,ppchCurr);

		/* Write /ACCTFROM */
		sprintf(*ppchCurr,"</ACCTFROM>\r\n");
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write MEMO (optional) */
	if (mailrq->pmemoMEMO)
	{
		/* Write MEMO */
		BuildMEMO((MEMO *) mailrq->pmemoMEMO,ppchCurr);
	}

	/* Write End Tag */
	sprintf(*ppchCurr,"</MAILRQ>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildMAILRQ */

/* --------------------------------------------------------------------------------- */
void BuildMAILRS(MAILRS *mailrs,char ** ppchCurr)
{
	/* Write CLTID and STATUS from Parent */
	sprintf(*ppchCurr,"<CLTID>%s\r\n<STATUS>%s\r\n",mailrs->szCLTID,mailrs->szSTATUS);
	*ppchCurr += strlen(*ppchCurr);

	/* Write Begin Tag */
	sprintf(*ppchCurr,"<MAILRS>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write MEMO (optional) */
	if (mailrs->pmemoMEMO)
	{
		/* Write MEMO */
		BuildMEMO((MEMO *) mailrs->pmemoMEMO,ppchCurr);
	}

	/* Write End Tag */
	sprintf(*ppchCurr,"</MAILRS>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildMAILRS */

/* --------------------------------------------------------------------------------- */
void BuildMEMO(MEMO *pmemo,char ** ppchCurr)
{
	/* Write Begin Tag and Text*/
	sprintf(*ppchCurr,"<MEMO>%s\r\n",pmemo->szMEMO);
	*ppchCurr += strlen(*ppchCurr);

	/* Write Next MEMO (optional) */
	if (pmemo->pmemoNext)
	{
		/* NOTE: This is a recursive call */
		BuildMEMO((MEMO *) pmemo->pmemoNext, ppchCurr);
	}

} /* end BuildMEMO */

/* --------------------------------------------------------------------------------- */
void BuildSTMTRQ(STMTRQ *stmtrq,char ** ppchCurr)
{
	/* Write CLTID and ACTION from Parent */
	sprintf(*ppchCurr,"<CLTID>%s\r\n<ACTION>%s\r\n",stmtrq->szCLTID,stmtrq->szACTION);
	*ppchCurr += strlen(*ppchCurr);

	/* Write Begin Tag */
	sprintf(*ppchCurr,"<STMTRQ>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	sprintf(*ppchCurr,"<ACCTFROM>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write ACCOUNT */
	BuildACCOUNT((ACCOUNT *) stmtrq->pacctACCTFROM,ppchCurr);

	/* Write /ACCTFROM */
	sprintf(*ppchCurr,"</ACCTFROM>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write DTSTART (Optional) */
	if (stmtrq->szDTSTART)
	{
		sprintf(*ppchCurr,"<DTSTART>%s\r\n",stmtrq->szDTSTART);
		*ppchCurr += strlen(*ppchCurr);	
	}

	/* Write DTEND (Optional) */
	if (stmtrq->szDTEND)
	{
		sprintf(*ppchCurr,"<DTEND>%s\r\n",stmtrq->szDTEND);
		*ppchCurr += strlen(*ppchCurr);	
	}

	/* Write End Tag */
	sprintf(*ppchCurr,"</STMTRQ>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildSTMTRQ */

/* --------------------------------------------------------------------------------- */
void BuildSTMTRS(STMTRS *stmtrs,char ** ppchCurr)
{
	/* Write CLTID and STATUS from Parent */
	sprintf(*ppchCurr,"<CLTID>%s\r\n<STATUS>%s\r\n",stmtrs->szCLTID,stmtrs->szSTATUS);
	*ppchCurr += strlen(*ppchCurr);

	/* Write Begin Tag */
	sprintf(*ppchCurr,"<STMTRS>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write DTSTART */
	sprintf(*ppchCurr,"<DTSTART>%s\r\n",stmtrs->szDTSTART);
	*ppchCurr += strlen(*ppchCurr);	

	/* Write DTEND */
	sprintf(*ppchCurr,"<DTEND>%s\r\n",stmtrs->szDTEND);
	*ppchCurr += strlen(*ppchCurr);	

	/* Write LEDGER */
	sprintf(*ppchCurr,"<LEDGER>%s\r\n",stmtrs->szLEDGER);
	*ppchCurr += strlen(*ppchCurr);	

	/* Write STMTTRN (Optional) */
	if (stmtrs->pgtrnSTMTTRN)
	{
		BuildSTMTTRN((GENTRN *) stmtrs->pgtrnSTMTTRN, ppchCurr);
	}

	/* Write End Tag */
	sprintf(*ppchCurr,"</STMTRS>\r\n");
	*ppchCurr += strlen(*ppchCurr);


} /* end BuildSTMTRS */

/* --------------------------------------------------------------------------------- */
void BuildSTMTTRN(GENTRN *pgtrn,char ** ppchCurr)
{
	/* Write Begin Tag */
	sprintf(*ppchCurr,"<STMTTRN>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write Begin Tag */
	sprintf(*ppchCurr,"<GENTRN>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write TRNTYPE, DTPOSTED, TRNAMT */
	sprintf(*ppchCurr,"<TRNTYPE>%s\r\n<DTPOSTED>%s\r\n<TRNAMT>%s\r\n",
				pgtrn->szTRNTYPE,pgtrn->szDTPOSTED,pgtrn->szTRNAMT);
	*ppchCurr += strlen(*ppchCurr);

	/* Write FITID (Optional) */
	if (pgtrn->szFITID)
	{
		sprintf(*ppchCurr,"<FITID>%s\r\n",pgtrn->szFITID);
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write CLTID (Optional) */
	if (pgtrn->szCLTID)
	{
		sprintf(*ppchCurr,"<CLTID>%s\r\n",pgtrn->szCLTID);
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write SRVRTID (Optional) */
	if (pgtrn->szSRVRTID)
	{
		sprintf(*ppchCurr,"<SRVRTID>%s\r\n",pgtrn->szSRVRTID);
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write CHKNUM (Optional) */
	if (pgtrn->szCHKNUM)
	{
		sprintf(*ppchCurr,"<CHKNUM>%s\r\n",pgtrn->szCHKNUM);
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write SIC (Optional) */
	if (pgtrn->szSIC)
	{
		sprintf(*ppchCurr,"<SIC>%s\r\n",pgtrn->szSIC);
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write PAYEEID (Optional) */
	if (pgtrn->szPAYEEID)
	{
		sprintf(*ppchCurr,"<PAYEEID>%s\r\n",pgtrn->szPAYEEID);
		*ppchCurr += strlen(*ppchCurr);
	}

	/* The following code was changed to either accept PAYEE or NAME. */
	/* Both are optional */
	/* Write PAYEE (Optional) */
	if (pgtrn->pentPAYEE)
	{
		/* Write PAYEE */
		sprintf(*ppchCurr,"<PAYEE>\r\n");
		*ppchCurr += strlen(*ppchCurr);

		/* Write ENTITY */
		BuildENTITY((ENTITY *) pgtrn->pentPAYEE,ppchCurr);

		/* Write /PAYEE */
		sprintf(*ppchCurr,"</PAYEE>\r\n");
		*ppchCurr += strlen(*ppchCurr);
	}
	else if (pgtrn->szNAME) /* Write NAME (Optional) */
	{
		/* Write NAME */
		sprintf(*ppchCurr,"<NAME>%s\r\n",pgtrn->szNAME);
		*ppchCurr += strlen(*ppchCurr);
	}


	/* Write ACCTTO (Optional) */
	if (pgtrn->pacctACCTTO)
	{
		sprintf(*ppchCurr,"<ACCTTO>\r\n");
		*ppchCurr += strlen(*ppchCurr);

		/* Write ACCOUNT */
		BuildACCOUNT((ACCOUNT *) pgtrn->pacctACCTTO,ppchCurr);

		/* Write /ACCTTO */
		sprintf(*ppchCurr,"</ACCTTO>\r\n");
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write MEMO (optional) */
	if (pgtrn->pmemoMEMO)
	{
		/* Write MEMO */
		BuildMEMO((MEMO *) pgtrn->pmemoMEMO,ppchCurr);
	}

	/* Write End Tag */
	sprintf(*ppchCurr,"</GENTRN>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write Begin Tag */
	sprintf(*ppchCurr,"</STMTTRN>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Check for another GENTRN */
	if (pgtrn->pgtrnNext)
	{
		/* NOTE: This is a recursive call */
		BuildSTMTTRN((GENTRN *) pgtrn->pgtrnNext, ppchCurr);
	}

} /* end BuildSTMTTRN */

/* --------------------------------------------------------------------------------- */
void BuildACCTSTMT(ACCTSTMT *acctstmt,char **ppchCurr)
{
	/* Write Begin Tag */
	sprintf(*ppchCurr,"<ACCTSTMT>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write ACCTFROM */
	sprintf(*ppchCurr,"<ACCTFROM>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write ACCOUNT */
	BuildACCOUNT((ACCOUNT *) acctstmt->pacctACCTFROM,ppchCurr);

	/* Write /ACCTFROM */
	sprintf(*ppchCurr,"</ACCTFROM>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write STMTRS Begin Tag */
	sprintf(*ppchCurr,"<STMTRS>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write DTSTART */
	sprintf(*ppchCurr,"<DTSTART>%s\r\n",acctstmt->szDTSTART);
	*ppchCurr += strlen(*ppchCurr);	

	/* Write DTEND */
	sprintf(*ppchCurr,"<DTEND>%s\r\n",acctstmt->szDTEND);
	*ppchCurr += strlen(*ppchCurr);	

	/* Write LEDGER */
	sprintf(*ppchCurr,"<LEDGER>%s\r\n",acctstmt->szLEDGER);
	*ppchCurr += strlen(*ppchCurr);	

	/* Write STMTTRN (Optional) */
	if (acctstmt->pgtrnSTMTTRN)
	{
		BuildSTMTTRN((GENTRN *) acctstmt->pgtrnSTMTTRN, ppchCurr);
	}

	/* Write STMTRS End Tag */
	sprintf(*ppchCurr,"</STMTRS>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write End Tag */
	sprintf(*ppchCurr,"</ACCTSTMT>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildACCTSTMT */

/* --------------------------------------------------------------------------------- */
void BuildPAYMTRQ(PAYMTRQ *ppaymtrq, char **ppchCurr)
{
	/* Write CLTID and ACTION from Parent */
	sprintf(*ppchCurr,"<CLTID>%s\r\n<ACTION>%s\r\n",ppaymtrq->szCLTID,ppaymtrq->szACTION);
	*ppchCurr += strlen(*ppchCurr);

	/* Write Begin Tag */
	sprintf(*ppchCurr,"<PAYMTRQ>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	sprintf(*ppchCurr,"<ACCTFROM>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write ACCOUNT */
	BuildACCOUNT((ACCOUNT *) ppaymtrq->pacctACCTFROM,ppchCurr);

	/* Write /ACCTFROM */
	sprintf(*ppchCurr,"</ACCTFROM>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write TRNAMT */
	sprintf(*ppchCurr,"<TRNAMT>%s\r\n",ppaymtrq->szTRNAMT);
	*ppchCurr += strlen(*ppchCurr);	

	/* Write PAYEEID (Optional) */
	if (ppaymtrq->szPAYEEID)
	{
		sprintf(*ppchCurr,"<PAYEEID>%s\r\n",ppaymtrq->szPAYEEID);
		*ppchCurr += strlen(*ppchCurr);	
	}
	else
	{	
		/* Write PAYEE */
		sprintf(*ppchCurr,"<PAYEE>\r\n");
		*ppchCurr += strlen(*ppchCurr);

		/* Write ENTITY */
		BuildENTITY((ENTITY *) ppaymtrq->pentPAYEE,ppchCurr);

		/* Write /PAYEE */
		sprintf(*ppchCurr,"</PAYEE>\r\n");
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write PAYACCT */
	sprintf(*ppchCurr,"<PAYACCT>%s\r\n",ppaymtrq->szPAYACCT);
	*ppchCurr += strlen(*ppchCurr);	

	/* Write DTDUE */
	sprintf(*ppchCurr,"<DTDUE>%s\r\n",ppaymtrq->szDTDUE);
	*ppchCurr += strlen(*ppchCurr);	

	/* Write SRVRTID (Optional) */
	if (ppaymtrq->szSRVRTID)
	{
		sprintf(*ppchCurr,"<SRVRTID>%s\r\n",ppaymtrq->szSRVRTID);
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write MEMO (Optional) */
	if (ppaymtrq->pmemoMEMO)
	{
		BuildMEMO((MEMO *) ppaymtrq->pmemoMEMO, ppchCurr);
	}

	/* Write End Tag */
	sprintf(*ppchCurr,"</PAYMTRQ>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildPAYMTRQ	 */

/* --------------------------------------------------------------------------------- */
void BuildPAYMTRS(PAYMTRS *paymtrs,char ** ppchCurr)
{
	/* Write CLTID and STATUS from Parent */
	sprintf(*ppchCurr,"<CLTID>%s\r\n<STATUS>%s\r\n",paymtrs->szCLTID,paymtrs->szSTATUS);
	*ppchCurr += strlen(*ppchCurr);

	/* Write Begin Tag */
	sprintf(*ppchCurr,"<PAYMTRS>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write SRVRTID */
	sprintf(*ppchCurr,"<SRVRTID>%s\r\n",paymtrs->szSRVRTID);
	*ppchCurr += strlen(*ppchCurr);

	/* Write PAYEEID (Optional) */
	if (paymtrs->szPAYEEID)
	{
		sprintf(*ppchCurr,"<PAYEEID>%s\r\n",paymtrs->szPAYEEID);
		*ppchCurr += strlen(*ppchCurr);	
	}

	/* Write End Tag */
	sprintf(*ppchCurr,"</PAYMTRS>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildPAYMTRS */

/* --------------------------------------------------------------------------------- */
void BuildPAYIQRQ(PAYIQRQ *ppayiqrq,char ** ppchCurr)
{
	/* Write CLTID and ACTION from Parent */
	sprintf(*ppchCurr,"<CLTID>%s\r\n<ACTION>%s\r\n",ppayiqrq->szCLTID,ppayiqrq->szACTION);
	*ppchCurr += strlen(*ppchCurr);

	/* Write Begin Tag */
	sprintf(*ppchCurr,"<PAYIQRQ>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write SRVRTID (Optional) */
	sprintf(*ppchCurr,"<SRVRTID>%s\r\n",ppayiqrq->szSRVRTID);
	*ppchCurr += strlen(*ppchCurr);

	/* Write MEMO */
	BuildMEMO((MEMO *) ppayiqrq->pmemoMEMO, ppchCurr);

	/* Write End Tag */
	sprintf(*ppchCurr,"</PAYIQRQ>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildPAYIQRQ	 */

/* --------------------------------------------------------------------------------- */
void BuildPAYIQRS(PAYIQRS *ppayiqrs, char **ppchCurr)
{
	/* Write CLTID and STATUS from Parent */
	sprintf(*ppchCurr,"<CLTID>%s\r\n<STATUS>%s\r\n",ppayiqrs->szCLTID,ppayiqrs->szSTATUS);
	*ppchCurr += strlen(*ppchCurr);

	/* Write Begin Tag */
	sprintf(*ppchCurr,"<PAYIQRS>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write SRVRTID */
	sprintf(*ppchCurr,"<SRVRTID>%s\r\n",ppayiqrs->szSRVRTID);
	*ppchCurr += strlen(*ppchCurr);

	/* Write MEMO (Optional) */
	if (ppayiqrs->pmemoMEMO)
	{
		BuildMEMO((MEMO *) ppayiqrs->pmemoMEMO, ppchCurr);
	}

	/* Write End Tag */
	sprintf(*ppchCurr,"</PAYIQRS>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildPAYIQRS */

/* --------------------------------------------------------------------------------- */
void BuildINTRARQ(INTRARQ *pintrarq,char ** ppchCurr)
{
	/* Write CLTID and ACTION from Parent */
	sprintf(*ppchCurr,"<CLTID>%s\r\n<ACTION>%s\r\n",pintrarq->szCLTID,pintrarq->szACTION);
	*ppchCurr += strlen(*ppchCurr);

	/* Write Begin Tag */
	sprintf(*ppchCurr,"<INTRARQ>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write ACCTFROM */
	sprintf(*ppchCurr,"<ACCTFROM>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write ACCOUNT */
	BuildACCOUNT((ACCOUNT *) pintrarq->pacctACCTFROM,ppchCurr);

	/* Write /ACCTFROM */
	sprintf(*ppchCurr,"</ACCTFROM>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write TRNAMT */
	sprintf(*ppchCurr,"<TRNAMT>%s\r\n",pintrarq->szTRNAMT);
	*ppchCurr += strlen(*ppchCurr);

	/* Write ACCTTO */
	sprintf(*ppchCurr,"<ACCTTO>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write ACCOUNT */
	BuildACCOUNT((ACCOUNT *) pintrarq->pacctACCTTO,ppchCurr);

	/* Write /ACCTTO */
	sprintf(*ppchCurr,"</ACCTTO>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write MEMO (optional) */
	if (pintrarq->pmemoMEMO)
	{
		/* Write MEMO */
		BuildMEMO((MEMO *) pintrarq->pmemoMEMO,ppchCurr);
	}

	/* Write End Tag */
	sprintf(*ppchCurr,"</INTRARQ>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildINTRARQ */


/* --------------------------------------------------------------------------------- */
void BuildINTRARS(INTRARS *intrars, char **ppchCurr)
{
	/* Write CLTID and STATUS from Parent */
	sprintf(*ppchCurr,"<CLTID>%s\r\n<STATUS>%s\r\n",intrars->szCLTID,intrars->szSTATUS);
	*ppchCurr += strlen(*ppchCurr);

	/* Write Begin Tag */
	sprintf(*ppchCurr,"<INTRARS>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write SRVRTID */
	sprintf(*ppchCurr,"<SRVRTID>%s\r\n",intrars->szSRVRTID);
	*ppchCurr += strlen(*ppchCurr);

	/* Write DTPOSTED (Optional) */
	if (intrars->szDTPOSTED)
	{
		/* Write DTPOSTED */
		sprintf(*ppchCurr,"<DTPOSTED>%s\r\n",intrars->szDTPOSTED);
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write End Tag */
	sprintf(*ppchCurr,"</INTRARS>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildINTRARS */

/* --------------------------------------------------------------------------------- */
void BuildINTERRQ(INTERRQ *pinterrq,char ** ppchCurr)
{
	/* Write CLTID and ACTION from Parent */
	sprintf(*ppchCurr,"<CLTID>%s\r\n<ACTION>%s\r\n",pinterrq->szCLTID,pinterrq->szACTION);
	*ppchCurr += strlen(*ppchCurr);

	/* Write Begin Tag */
	sprintf(*ppchCurr,"<INTERRQ>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write ACCTFROM */
	sprintf(*ppchCurr,"<ACCTFROM>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write ACCOUNT */
	BuildACCOUNT((ACCOUNT *) pinterrq->pacctACCTFROM,ppchCurr);

	/* Write /ACCTFROM */
	sprintf(*ppchCurr,"</ACCTFROM>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write TRNAMT */
	sprintf(*ppchCurr,"<TRNAMT>%s\r\n",pinterrq->szTRNAMT);
	*ppchCurr += strlen(*ppchCurr);

	/* There is either a PAYEEID or a ACCTTO*/
	if (pinterrq->szPAYEEID)
	{
		/* Write PAYEEID */
		sprintf(*ppchCurr,"<PAYEEID>%s\r\n",pinterrq->szPAYEEID);
		*ppchCurr += strlen(*ppchCurr);
	}
	else
	{
		/* Write ACCTTO */
		sprintf(*ppchCurr,"<ACCTTO>\r\n");
		*ppchCurr += strlen(*ppchCurr);

		/* Write ACCOUNT */
		BuildACCOUNT((ACCOUNT *) pinterrq->pacctACCTTO,ppchCurr);

		/* Write /ACCTTO */
		sprintf(*ppchCurr,"</ACCTTO>\r\n");
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write NAME */
	sprintf(*ppchCurr,"<NAME>%s\r\n",pinterrq->szNAME);
	*ppchCurr += strlen(*ppchCurr);

	/* Write PAYACCT */
	sprintf(*ppchCurr,"<PAYACCT>%s\r\n",pinterrq->szPAYACCT);
	*ppchCurr += strlen(*ppchCurr);

	/* Write DTDUE */
	sprintf(*ppchCurr,"<DTDUE>%s\r\n",pinterrq->szDTDUE);
	*ppchCurr += strlen(*ppchCurr);

	/* Write SRVRTID */
	if (pinterrq->szSRVRTID)
	{
		sprintf(*ppchCurr,"<SRVRTID>%s\r\n",pinterrq->szSRVRTID);
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write MEMO (optional) */
	if (pinterrq->pmemoMEMO)
	{
		/* Write MEMO */
		BuildMEMO((MEMO *) pinterrq->pmemoMEMO,ppchCurr);
	}

	/* Write End Tag */
	sprintf(*ppchCurr,"</INTERRQ>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildINTERRQ */


/* --------------------------------------------------------------------------------- */
void BuildINTERRS(INTERRS *interrs, char **ppchCurr)
{
	/* Write CLTID and STATUS from Parent */
	sprintf(*ppchCurr,"<CLTID>%s\r\n<STATUS>%s\r\n",interrs->szCLTID,interrs->szSTATUS);
	*ppchCurr += strlen(*ppchCurr);

	/* Write Begin Tag */
	sprintf(*ppchCurr,"<INTERRS>\r\n");
	*ppchCurr += strlen(*ppchCurr);

	/* Write SRVRTID */
	sprintf(*ppchCurr,"<SRVRTID>%s\r\n",interrs->szSRVRTID);
	*ppchCurr += strlen(*ppchCurr);

	/* Write DTPOSTED (Optional) */
	if (interrs->szDTPOSTED)
	{
		/* Write DTPOSTED */
		sprintf(*ppchCurr,"<DTPOSTED>%s\r\n",interrs->szDTPOSTED);
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write CHKNUM (Optional) */
	if (interrs->szCHKNUM)
	{
		/* Write CHKNUM */
		sprintf(*ppchCurr,"<CHKNUM>%s\r\n",interrs->szCHKNUM);
		*ppchCurr += strlen(*ppchCurr);
	}

	/* Write End Tag */
	sprintf(*ppchCurr,"</INTERRS>\r\n");
	*ppchCurr += strlen(*ppchCurr);

} /* end BuildINTERRS */