/* ---------------------------------------------------------------------------------
// Copyright(c) 1991-1996 Microsoft Corporation.  All rights reserved.
// ---------------------------------------------------------------------------------
// File: PBANKING.C
//
// Contains functions necessary to parse and OFC banking data.
//
// Includes:
//		RcParseGENTRN - parse general transaction
//		RcParseSTMTTRN - parse a statement transaction
//		RcParseSTMTRQ - parse a statement request
//		RcParseSTMTRS - parse a statement response
//		RcParseINTERRQ - parse an interbank xfer request
//		RcParseINTERRS - parse an interbank xfer response
//		RcParseINTRARQ - parse an intrabank xfer request
//		RcParseINTRARS - parse an intrabank xfer response
//
// 02/27/95	TimHa - Created
// ------------------------------------------------------------------------------- */

/* Standard Include Files */
#include <stdio.h> 
#include <malloc.h>
#include <ctype.h>
#include <string.h>

/* Other Include files */
#include "ofclink.h"	/* Functions to Create / Update linked list */
#include "pbtypes.h"	/* ofc parse & build types */
#include "parse.h"		/* parse only  */


/* ---------------------------------------------------------------------------------
// Function: RcParseGENTRN
//
// Parses a GENTRN.  It handles a begin tag <GENTRN>, all subordinate tags, and an 
// end tag </GENTRN>.  The tags may be optional. A GENTRN structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//  ppgentrn - memory containing the GENTRN structure
//
// Notes: 
// - According to the DTD:
//	 TRNTYPE, DTPOSTED, TRNAMT, FITID?, CLTID?, SRVRTID?, CHKNUM?, SIC?, PAYEEID?, 
//		(PAYEE | NAME)?, ACCTTO?, (MEMO*)
//
// History: 
//	2/27/96	TimHa - Created
//  5/23/96 DerekHa - (PAYEE | NAME)? replaced (PAYEE)?
//
// -------------------------------------------------------------------------------*/
int RcParseGENTRN(TOKEN *ptk, TOKENSTATE *ptks, GENTRN **ppgentrn)
{
	int		rcReturn;

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppgentrn == NULL))
	{
		return INVALID_CALL;
	}

	/* Parse the <GENTRN> */
	rcReturn = RcParseTag(tktGENTRN,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*ppgentrn = (GENTRN *) malloc(sizeof(GENTRN));
	if (*ppgentrn == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*ppgentrn,0,sizeof(GENTRN));


	/* Parse the TRNTYPE */
	rcReturn = RcParseAnyElement(tktTRNTYPE,ptk,ptks,&((*ppgentrn)->szTRNTYPE));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse DTPOSTED */
	rcReturn = RcParseAnyElement(tktDTPOSTED,ptk,ptks,&((*ppgentrn)->szDTPOSTED));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse TRNAMT */
	rcReturn = RcParseAnyElement(tktTRNAMT,ptk,ptks,&((*ppgentrn)->szTRNAMT));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse FITID, if it exists */
	if (ptk->tkt == tktFITID)
	{
		rcReturn = RcParseAnyElement(tktFITID,ptk,ptks,&((*ppgentrn)->szFITID));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse CLTID, if it exists */
	if (ptk->tkt == tktCLTID)
	{
		rcReturn = RcParseAnyElement(tktCLTID,ptk,ptks,&((*ppgentrn)->szCLTID));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse SRVRTID, if it exists */
	if (ptk->tkt == tktSRVRTID)
	{
		rcReturn = RcParseAnyElement(tktSRVRTID,ptk,ptks,&((*ppgentrn)->szSRVRTID));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse CHKNUM, if it exists */
	if (ptk->tkt == tktCHKNUM)
	{
		rcReturn = RcParseAnyElement(tktCHKNUM,ptk,ptks,&((*ppgentrn)->szCHKNUM));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse SIC, if it exists */
	if (ptk->tkt == tktSIC)
	{
		rcReturn = RcParseAnyElement(tktSIC,ptk,ptks,&((*ppgentrn)->szSIC));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse PAYEEID, if it exists */
	if (ptk->tkt == tktPAYEEID)
	{
		rcReturn = RcParseAnyElement(tktPAYEEID,ptk,ptks,&((*ppgentrn)->szPAYEEID));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* The following cose was changed to either accept PAYEE or NAME. */
	/* Both are optional */
	if (ptk->tkt == tktPAYEE)
	{
		rcReturn = RcParsePAYEE(ptk,ptks,(void **)&((*ppgentrn)->pentPAYEE));
		if (rcReturn != ALL_OK)
			goto _END;
	}
	else if (ptk->tkt == tktNAME)
	{
		rcReturn = RcParseAnyElement(tktNAME,ptk,ptks,&((*ppgentrn)->szNAME));
		if (rcReturn != ALL_OK)
			goto _END;
	}


	/* Parse ACCTTO, if one exists */
	if (ptk->tkt == tktACCTTO)
	{
		rcReturn = RcParseACCTTO(ptk,ptks,(void**)&((*ppgentrn)->pacctACCTTO));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* parse MEMOs */
	rcReturn = RcParseMemos(mfZEROORMORE, ptk, ptks, &((*ppgentrn)->pmemoMEMO));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the </GENTRN> */
	rcReturn = RcParseTag(tktEndGENTRN,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:
	if (rcReturn != ALL_OK)
	{
		/* clean up anything allocated so far */
		if (*ppgentrn)
		{
			free(*ppgentrn);
			*ppgentrn = NULL;
		}
	} 
	return rcReturn;
} /* RcParseGENTRN */


/* ---------------------------------------------------------------------------------
// Function: RcParseSTMTTRN
//
// Parses a STMTTRN.  It handles a begin tag <STMTTRN>, all subordinate tags, and an 
// end tag </STMTTRN>.  The tags may be optional. A STMTTRN structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//  ppvData - memory containing the GENTRN structure
//
// This function is a bit weird since GENTRN is all optional tags and STMTTRN is 
// required.  Thus we must iterate here on STMTTRN and build up the linked list
// of GENTRNs that all get connected to the caller's ppvData pointer. 
//
// Notes: 
// - According to the DTD:
//   - GENTRN
//
// History: 
//	2/27/96	TimHa - Created
//
// ------------------------------------------------------------------------------- */
int RcParseSTMTTRN(TOKEN *ptk, TOKENSTATE *ptks, void **ppvData)
{
	GENTRN *pgtrnLast;
	GENTRN *pgtrn;
	int		rcReturn = ALL_OK;

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppvData == NULL))
	{
		return INVALID_CALL;
	}

	pgtrnLast = NULL;
	*ppvData = NULL;

	/* we will have a group of STMTTRNs possibly, so let's go			*/
	/* and loop on them, making sure to link up the GENTRNs that		*/
	/* get passed in													*/
	/*																	*/
	/* REVIEW: My brain is dead so this code probably is too, I know	*/
	/*		   it can be written better									*/
	/*																	*/
	while (ptk->tkt == tktSTMTTRN)
	{
		/* Parse the <STMTTRN> */
		rcReturn = RcParseTag(tktSTMTTRN,ptk,ptks);
		if (rcReturn != ALL_OK)
			goto _END;

		/* Parse the GENTRN */
		rcReturn = RcParseGENTRN(ptk,ptks,&pgtrn);
		if (rcReturn != ALL_OK)
			goto _END;
		
		/* link it in to the list of GENTRNs */
		if (*ppvData == NULL)
		{
			/* get our mail link set up */
			*ppvData = (void *)pgtrn;

		} 
		else 
		{
			/* link to last one */
			pgtrnLast->pgtrnNext = pgtrn;
		}
		/* save this one as our last one in list */
		pgtrnLast = pgtrn;

		/* Parse the </STMTTRN> */
		rcReturn = RcParseTag(tktEndSTMTTRN,ptk,ptks);
		if (rcReturn != ALL_OK)
			goto _END;
	}

_END:
	if (rcReturn != ALL_OK)
	{
		/* clean up anything allocated so far */
		if (*ppvData)
		{
			CleanupStmts((GENTRN *)*ppvData);
			*ppvData = NULL;
		}
	} 
	return rcReturn;


}  /* RcParseSTMTTRN */


/* ---------------------------------------------------------------------------------
// Function: RcParseSTMTRQ
//
// Parses a STMTRQ.  It handles a begin tag <STMTRQ>, all subordinate tags, and an 
// end tag </STMTRQ>.  The tags may be optional. A STMTRQ structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//  szCLTID - the CLTID (Parsed by caller)
//  szACTION - the ACTION (Parsed by caller)
//	ppstmtrq - memory containing the STMTRQ structure
//
// Notes: 
// - According to the DTD:
//   - ACCTFROM, DTSTART?, DTEND?
//
// History: 
//	2/27/96	TimHa - Created
//
// ------------------------------------------------------------------------------- */
int RcParseSTMTRQ(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szACTION, STMTRQ **ppstmtrq)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppstmtrq == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <STMTRQ> */
	rcReturn = RcParseTag(tktSTMTRQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*ppstmtrq = (STMTRQ *) malloc(sizeof(STMTRQ));
	if (*ppstmtrq == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*ppstmtrq,0,sizeof(STMTRQ));

	/* Initialize the items passed in by caller */
	(*ppstmtrq)->szCLTID = szCLTID;
	(*ppstmtrq)->szACTION = szACTION;

	/* Parse ACCTFROM */
	rcReturn = RcParseACCTFROM(ptk,ptks,(void**)&((*ppstmtrq)->pacctACCTFROM));
	if (rcReturn != ALL_OK)
			goto _END;

	/* Parse DTSTART if it exists */
	if (ptk->tkt == tktDTSTART)
	{
		rcReturn = RcParseAnyElement(tktDTSTART, ptk, ptks, &((*ppstmtrq)->szDTSTART));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse DTEND if it exists */
	if (ptk->tkt == tktDTEND)
	{
		rcReturn = RcParseAnyElement(tktDTEND, ptk, ptks, &((*ppstmtrq)->szDTEND));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse the </STMTRQ> */
	rcReturn = RcParseTag(tktEndSTMTRQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*ppstmtrq) 
		{
			free(*ppstmtrq);
			*ppstmtrq = NULL;
		}
	}

	return rcReturn;

} /* RcParseSTMTRQ */


/* ---------------------------------------------------------------------------------
// Function: RcParseSTMTRS
//
// Parses a STMTRS.  It handles a begin tag <STMTRS>, all subordinate tags, and an 
// end tag </STMTRS>.  The tags may be optional. A STMTRS structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//	szCLTID - the CLTID (Parsed by caller)
//  szSTATUS - the STATUS (Parsed by caller)
//  ppstmtrs - memory containing the STMTRS structure
//
// Notes: 
// - According to the DTD:
//   - DTSTART, DTEND, LEDGER, (STMTTRN*)
//
// History: 
//	2/27/96	TimHa - Created
//
// ------------------------------------------------------------------------------- */
int RcParseSTMTRS(TOKEN *ptk, TOKENSTATE *ptks,  char * szCLTID, char * szSTATUS, 
				 STMTRS **ppstmtrs)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppstmtrs == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <STMTRS> */
	rcReturn = RcParseTag(tktSTMTRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*ppstmtrs = (STMTRS *) malloc(sizeof(STMTRS));
	if (*ppstmtrs == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*ppstmtrs,0,sizeof(STMTRS));

	/* Initialize the items passed in by caller */
	(*ppstmtrs)->szCLTID = szCLTID;
	(*ppstmtrs)->szSTATUS = szSTATUS;

	/* Parse DTSTART */
	rcReturn = RcParseAnyElement(tktDTSTART, ptk, ptks, &((*ppstmtrs)->szDTSTART));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse DTEND */
	rcReturn = RcParseAnyElement(tktDTEND, ptk, ptks, &((*ppstmtrs)->szDTEND));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse LEDGER */
	rcReturn = RcParseAnyElement(tktLEDGER, ptk, ptks, &((*ppstmtrs)->szLEDGER));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the STMTTRNs */
	if (ptk->tkt == tktSTMTTRN)
	{
		rcReturn = RcParseSTMTTRN(ptk, ptks, (void **)&((*ppstmtrs)->pgtrnSTMTTRN));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse the </STMTRS> */
	rcReturn = RcParseTag(tktEndSTMTRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*ppstmtrs) 
		{
			free(*ppstmtrs);
			*ppstmtrs = NULL;
		}
	}

	return rcReturn;
} /* RcParseSTMTRS */



/* ---------------------------------------------------------------------------------
// Function: RcParseINTERRQ
//
// Parses a INTERRQ.  It handles a begin tag <INTERRQ>, all subordinate tags, and an 
// end tag </INTERRQ>.  The tags may be optional. A INTERRQ structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//  szCLTID - the CLTID (Parsed by caller)
//  szACTION - the ACTION (Parsed by caller)
//	ppinterrq - memory containing the INTERRQ structure
//
// Notes: 
// - According to the DTD:
//   - ACCTFROM, TRNAMT, ACCTTO, NAME?, PAYACCT?, DTDUE, SRVRTID?, (MEMO*)
//
// History: 
//	2/27/96	TimHa - Created
//
// ------------------------------------------------------------------------------- */
int RcParseINTERRQ(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szACTION, INTERRQ **ppinterrq)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppinterrq == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <INTERRQ> */
	rcReturn = RcParseTag(tktINTERRQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*ppinterrq = (INTERRQ *) malloc(sizeof(INTERRQ));
	if (*ppinterrq == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*ppinterrq,0,sizeof(INTERRQ));

	/* Initialize the items passed in by caller */
	(*ppinterrq)->szCLTID = szCLTID;
	(*ppinterrq)->szACTION = szACTION;

	/* Parse ACCTFROM */
	rcReturn = RcParseACCTFROM(ptk, ptks, (void**)&((*ppinterrq)->pacctACCTFROM));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse TRNAMT */
	rcReturn = RcParseAnyElement(tktTRNAMT, ptk, ptks, &(*ppinterrq)->szTRNAMT);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse PAYEEID if it exists */
	if (ptk->tkt == tktPAYEEID)
	{
		rcReturn = RcParseAnyElement(tktPAYEEID, ptk, ptks, &((*ppinterrq)->szPAYEEID));
		if (rcReturn != ALL_OK)
			goto _END;
	}
	else 
	{
		/* If there is no PAYEEID, there has to be a ACCTTO */
		/* Parse ACCTTO */
		rcReturn = RcParseACCTTO(ptk, ptks, (void**)&((*ppinterrq)->pacctACCTTO));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	rcReturn = RcParseAnyElement(tktNAME, ptk, ptks, &(*ppinterrq)->szNAME);
	if (rcReturn != ALL_OK)
		goto _END;

	rcReturn = RcParseAnyElement(tktPAYACCT, ptk, ptks, &(*ppinterrq)->szPAYACCT);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse DTDUE */
	rcReturn = RcParseAnyElement(tktDTDUE, ptk, ptks, &(*ppinterrq)->szDTDUE);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse SRVRTID, if it exists */
	if (ptk->tkt == tktSRVRTID)
	{
		rcReturn = RcParseAnyElement(tktSRVRTID, ptk, ptks, &(*ppinterrq)->szSRVRTID);
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse MEMOs */
	rcReturn = RcParseMemos(mfZEROORMORE, ptk, ptks, &((*ppinterrq)->pmemoMEMO));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the </INTERRQ> */
	rcReturn = RcParseTag(tktEndINTERRQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*ppinterrq) 
		{
			free(*ppinterrq);
			*ppinterrq = NULL;
		}
	}

	return rcReturn;

} /* RcParseINTERRQ */

/* ---------------------------------------------------------------------------------
// Function: RcParseINTERRS
//
// Parses a INTERRS.  It handles a begin tag <INTERRS>, all subordinate tags, and an 
// end tag </INTERRS>.  The tags may be optional. A INTERRS structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//	szCLTID - the CLTID (Parsed by caller)
//  szSTATUS - the STATUS (Parsed by caller)
//  ppinterrs - memory containing the INTERRS structure
//
// Notes: 
// - According to the DTD:
//   - SRVRTID, DTPOSTED?, CHKNUM?
//
// History: 
//	2/27/96	TimHa - Created
//
// ------------------------------------------------------------------------------- */
int RcParseINTERRS(TOKEN *ptk, TOKENSTATE *ptks,  char * szCLTID, char * szSTATUS, 
				 INTERRS **ppinterrs)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppinterrs == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <INTERRS> */
	rcReturn = RcParseTag(tktINTERRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*ppinterrs = (INTERRS *) malloc(sizeof(INTERRS));
	if (*ppinterrs == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*ppinterrs,0,sizeof(INTERRS));

	/* Initialize the items passed in by caller */
	(*ppinterrs)->szCLTID = szCLTID;
	(*ppinterrs)->szSTATUS = szSTATUS;

	/* Parse SRVRTID */
	rcReturn = RcParseAnyElement(tktSRVRTID, ptk, ptks, &((*ppinterrs)->szSRVRTID));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse DTPOSTED if it exists */
	if (ptk->tkt == tktDTPOSTED)
	{
		rcReturn = RcParseAnyElement(tktDTPOSTED, ptk, ptks, &(*ppinterrs)->szDTPOSTED);
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse CHKNUM if it exists */
	if (ptk->tkt == tktCHKNUM)
	{
		rcReturn = RcParseAnyElement(tktCHKNUM, ptk, ptks, &(*ppinterrs)->szCHKNUM);
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse the </INTERRS> */
	rcReturn = RcParseTag(tktEndINTERRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*ppinterrs) 
		{
			free(*ppinterrs);
			*ppinterrs = NULL;
		}
	}
	return rcReturn;
}  /* RcParseINTERRS */


/* ---------------------------------------------------------------------------------
// Function: RcParseINTRARQ
//
// Parses a INTRARQ.  It handles a begin tag <INTRARQ>, all subordinate tags, and an 
// end tag </INTRARQ>.  The tags may be optional. A INTRARQ structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//  szCLTID - the CLTID (Parsed by caller)
//  szACTION - the ACTION (Parsed by caller)
//	ppintrarq - memory containing the INTRAQ structure
//
// Notes: 
// - According to the DTD:
//   - ACTTFROM, TRNAMT, ACCTTO, (MEMO*)
//
// History: 
//	2/26/96	TimHa - Created
//
// ------------------------------------------------------------------------------- */
int RcParseINTRARQ(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char * szACTION, INTRARQ **ppintrarq)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppintrarq == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <INTRARQ> */
	rcReturn = RcParseTag(tktINTRARQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*ppintrarq = (INTRARQ *) malloc(sizeof(INTRARQ));
	if (*ppintrarq == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*ppintrarq,0,sizeof(INTRARQ));

	/* Initialize the items passed in by caller */
	(*ppintrarq)->szCLTID = szCLTID;
	(*ppintrarq)->szACTION = szACTION;

	/* Parse ACCTFROM */
	rcReturn = RcParseACCTFROM(ptk,ptks,(void**)&((*ppintrarq)->pacctACCTFROM));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse TRNAMT */
	rcReturn = RcParseAnyElement(tktTRNAMT, ptk,ptks,&((*ppintrarq)->szTRNAMT));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse ACCTTO */
	rcReturn = RcParseACCTTO(ptk,ptks,(void**)&((*ppintrarq)->pacctACCTTO));
	if (rcReturn != ALL_OK)
		goto _END;

	/* we can have 0 or more MEMOs to parse out here */
	rcReturn = RcParseMemos(mfZEROORMORE, ptk, ptks, &((*ppintrarq)->pmemoMEMO));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the </ACCTRQ> */
	rcReturn = RcParseTag(tktEndINTRARQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*ppintrarq) 
		{
			free(*ppintrarq);
			*ppintrarq = NULL;
		}
	}

	return rcReturn;

} /* RcParseINTRARQ */

/* ---------------------------------------------------------------------------------
// Function: RcParseINTRARS
//
// Parses a INTRARS.  It handles a begin tag <INTRARS>, all subordinate tags, and an 
// end tag </INTRARS>.  The tags may be optional. A INTRARS structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//  szCLTID - the CLTID (Parsed by caller)
//  szSTATUS - the STATUS (Parsed by caller)
//	ppauth - memory containing the INTRARS structure
//
// Notes: 
// - According to the DTD:
//   - SRVRTID, DTPOSTED?
//
// History: 
//	2/26/96	TimHa - Created
//
// ------------------------------------------------------------------------------- */
int RcParseINTRARS(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char * szSTATUS, 
				  INTRARS **ppintrars)
{
		int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppintrars == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <INTRARS> */
	rcReturn = RcParseTag(tktINTRARS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*ppintrars = (INTRARS *) malloc(sizeof(INTRARS));
	if (*ppintrars == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*ppintrars,0,sizeof(INTRARS));

	/* Initialize the items passed in by caller */
	(*ppintrars)->szCLTID = szCLTID;
	(*ppintrars)->szSTATUS = szSTATUS;

	/* Parse SRVRTID */
	rcReturn = RcParseAnyElement(tktSRVRTID, ptk,ptks,&((*ppintrars)->szSRVRTID));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse DTPOSTED if it exists */
	if (ptk->tkt == tktDTPOSTED)
	{
		rcReturn = RcParseAnyElement(tktDTPOSTED, ptk,ptks,&((*ppintrars)->szDTPOSTED));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse the </INTRARS> */
	rcReturn = RcParseTag(tktEndINTRARS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*ppintrars) 
		{
			free(*ppintrars);
			*ppintrars = NULL;
		}
	}

	return rcReturn;

} /* RcParseINTRARS */

