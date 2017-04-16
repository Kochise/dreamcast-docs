/* ---------------------------------------------------------------------------------
// Copyright(c) 1991-1996 Microsoft Corporation.  All rights reserved.
// ---------------------------------------------------------------------------------
// File: PARSE.C
//
// Contains functions necessary to parse and OFC document.
//
// 02/21/95	Derek Hazeur - Created
// ------------------------------------------------------------------------------- */

/* Standard Include Files */
#include <stdio.h> 
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>

/* Other Include files */
#include "ofclink.h"	/* Functions to Create / Update linked list */
#include "pbtypes.h"	/* ofc parse & build types */
#include "parse.h"		/* parse only  */

/* Prototype of functon for CleanUp, located in ofcparse.c */
void CleanupOFCDOCParse(POFCDOC *ppofcdoc);



/* ---------------------------------------------------------------------------------
// Function: RcParseOFCDOC
//
// Parses an OFC request.  It handles a begin tag <OFC>, all subordinate tags, and 
// an end tag </OFC>.  The begin and end tag is never optional. The token machine is 
// initialized before beginning. A OFC linked list is created and returned to the 
// caller
//
// Parameters: 
//	pvRequest - The buffer to be parsed
//	cbRequest - The # of bytes in the buffer
//  ppofcdoc - The OFC linked list returned to the caller. 
//
// Notes: 
// - According to the DTD:
//   - DTD, CPAGE,((SONRQ,(MAINTRQ*),(TRNRQ*))|
//		(SONRS, (MAINTRS*), (TRNRS*)) |
//		(ACCTSTMT*)))
//
//
// History: 
//	2/29/96	TimHa - Created
//  5/23/96 DerekHa - Change free on Error to CleanupOFCDOCParse to fix memory leak
//
// ------------------------------------------------------------------------------- */
int RcParseOFCDOC(OFCDOCTYPE odt, void *pvRequest, int cbRequest, OFCDOC **ppofcdoc)
{
	int rcReturn;				/* function return code */

	TOKEN tk;
	TOKENSTATE tks;
	char *szDTD;
	char *szCPAGE;
	void *pvData;
	OFCTYPE ofctype; 

	/* Initialize the Token Machine before beginning */
	rcReturn = RcInitializeToken(&tk,&tks,pvRequest,cbRequest);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the <OFC> */
	rcReturn = RcParseTag(tktOFC,&tk,&tks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse DTD */
	rcReturn = RcParseAnyElement(tktDTD,&tk,&tks,&szDTD);
	if (rcReturn != ALL_OK)
		goto _END;

	/* This code reflects only current DTD Version */
	if (atol(szDTD) != OFC_DTDVERSION)
	{
		rcReturn = INVALID_DTD_VER;
		goto _END;
	}

	/* Parse CPAGE */
	rcReturn = RcParseAnyElement(tktCPAGE,&tk,&tks,&szCPAGE);
	if (rcReturn != ALL_OK)
		goto _END;

	/* This code only works with CPAGE = 1252 (Windows Latin I (ANSI)) */
	if (atol(szCPAGE) != OFC_CPAGE)
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

/* **********************************************
/* TBD: Change the way the linked list is handled
/* **********************************************/

	/* Create the Linked List */
	rcReturn = RcCreateOFCDOC(ppofcdoc,szDTD,szCPAGE);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Must be SONRQ, SONRS or ACCTSTMT */
	switch (tk.tkt)
	{
	case tktSONRQ:
		/* do sanity check for request  */
		if (odt != odtREQUEST)
		{
			rcReturn = OFC_ERROR;
			goto _END;
		}

		/* SONRQ , (MAINTRQ*), (TRNRQ*) */
		/* Parse SONRQ */
		rcReturn = RcParseSONRQ(&tk,&tks,(SONRQ **) &pvData);
		if (rcReturn != ALL_OK)
			goto _END;

		/* Add the SONRQ to the Linked List */
		rcReturn = RcAddOFCTRN(*ppofcdoc,ofctypeSONRQ,pvData);

		while (tk.tkt == tktMAINTRQ)
		{
			rcReturn = RcParseMAINTRQ(&tk,&tks,(void **) &pvData, &ofctype);
			if (rcReturn != ALL_OK)
				goto _END;

			/* Add the MAINRQ to the Linked List */
			rcReturn = RcAddOFCTRN(*ppofcdoc,ofctype,pvData);
		}

		while (tk.tkt == tktTRNRQ)
		{
			rcReturn = RcParseTRNRQ(&tk, &tks, (void**) &pvData, &ofctype);
			if (rcReturn != ALL_OK)
				goto _END;

			rcReturn = RcAddOFCTRN(*ppofcdoc, ofctype, pvData);
		}

		break;

	case tktSONRS:
		/* SONRS, (MAINTRS*), (TRNRS*) */

		/* do sanity check for response  */
		if (odt != odtRESPONSE)
		{
			rcReturn = OFC_ERROR;
			goto _END;
		}

		/* Parse SONRS */
		rcReturn = RcParseSONRS(&tk,&tks,(SONRS **) &pvData);
		if (rcReturn != ALL_OK)
			goto _END;

		/* Add the SONRS to the Linked List */
		rcReturn = RcAddOFCTRN(*ppofcdoc,ofctypeSONRS,pvData);

		while (tk.tkt == tktMAINTRS)
		{
			rcReturn = RcParseMAINTRS(&tk,&tks,(void **) &pvData, &ofctype);
			if (rcReturn != ALL_OK)
				goto _END;
	
			/* Add the MAINRS to the Linked List */
			rcReturn = RcAddOFCTRN(*ppofcdoc,ofctype,pvData);
		}

		while (tk.tkt == tktTRNRS)
		{
			rcReturn = RcParseTRNRS(&tk, &tks, (void**) &pvData, &ofctype);
			if (rcReturn != ALL_OK)
				goto _END;

			rcReturn = RcAddOFCTRN(*ppofcdoc, ofctype, pvData);
		}


		break;

	case tktACCTSTMT:
		/* ACCTFROM, STMTRS */

		/* do sanity check for statement */
		if (odt != odtSTATEMENT)
		{
			rcReturn = OFC_ERROR;
			goto _END;
		}

		/* can have multiples of the ACCTSTMTs so loop */
		while (tk.tkt == tktACCTSTMT)
		{
			/* Parse the ACCTFROM */
			rcReturn = RcParseACCTSTMT(&tk, &tks, (ACCTSTMT **)&pvData);
			if (rcReturn != ALL_OK)
				goto _END;

			rcReturn = RcAddOFCTRN(*ppofcdoc, ofctypeACCTSTMT, pvData);
		}
		break;

	default:
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Parse the </OFC> */
	rcReturn = RcParseTag(tktEndOFC,&tk,&tks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If we have an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*ppofcdoc) 
		{
			CleanupOFCDOCParse(ppofcdoc);
			*ppofcdoc = NULL;
		}
	}

	return rcReturn;
} /*RcParseOFC */


/* ---------------------------------------------------------------------------------
// Function: RcParseSONRQ
//
// Parses a SONRQ.  It handles a begin tag <SONRQ>, all subordinate tags, and an 
// end tag </SONRQ>.  The tags may be optional. A SONRQ structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//	ppsonrqData - memory containing the SONRQ structure
//
// Notes: 
// - According to the DTD:
//   - SESSKEY, DTCLIENT, USERID, USERPASS, NEWPASS?
//
// History: 
//	2/23/96	Derek Hazeur - Created
// ------------------------------------------------------------------------------ */
int RcParseSONRQ(TOKEN *ptk, TOKENSTATE *ptks, SONRQ **ppsonrq)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppsonrq == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <SONRQ> */
	rcReturn = RcParseTag(tktSONRQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*ppsonrq = (SONRQ *) malloc(sizeof(SONRQ));
	if (*ppsonrq == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*ppsonrq,0,sizeof(SONRQ));

	/* Parse SESSKEY */
	rcReturn = RcParseAnyElement(tktSESSKEY,ptk,ptks,&((*ppsonrq)->szSESSKEY));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse DTCLIENT */
	rcReturn = RcParseAnyElement(tktDTCLIENT,ptk,ptks,&((*ppsonrq)->szDTCLIENT));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse USERID */
	rcReturn = RcParseAnyElement(tktUSERID,ptk,ptks,&((*ppsonrq)->szUSERID));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse USERPASS */
	rcReturn = RcParseAnyElement(tktUSERPASS,ptk,ptks,&((*ppsonrq)->szUSERPASS));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check for NEWPASS (Optional) */
	if (ptk->tkt == tktNEWPASS)
	{
		/* Parse NEWPASS */
		rcReturn = RcParseAnyElement(tktNEWPASS,ptk,ptks,&((*ppsonrq)->szNEWPASS));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse the </SONRQ> */
	rcReturn = RcParseTag(tktEndSONRQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*ppsonrq) 
		{
			free(*ppsonrq);
			*ppsonrq = NULL;
		}
	}

	return rcReturn;

}	/* end RcParseSONRQ */

/* ---------------------------------------------------------------------------------
// Function: RcParseSONRS
//
// Parses a SONRS.  It handles a begin tag <SONRS>, all subordinate tags, and an 
// end tag </SONRS>.  The tags may be optional. A SONRS structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//	ppSONRSData - memory containing the SONRS structure
//
// Notes: 
// - According to the DTD:
//   - STATUS,DTSERVER,ERROR?,SESSKEY,((SERVICE+),DAYSREQD?,DAYSWITH?)?
// - Other:
// Only two SERVICE allowed
//
// History: 
//	2/23/96	Derek Hazeur - Created
//
// ------------------------------------------------------------------------------- */
int RcParseSONRS(TOKEN *ptk, TOKENSTATE *ptks, SONRS **ppsonrs)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppsonrs == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <SONRS> */
	rcReturn = RcParseTag(tktSONRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*ppsonrs = (SONRS *) malloc(sizeof(SONRS));
	if (*ppsonrs == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*ppsonrs,0,sizeof(SONRS));

	/* Parse STATUS */
	rcReturn = RcParseAnyElement(tktSTATUS,ptk,ptks,&((*ppsonrs)->szSTATUS));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse DTSERVER */
	rcReturn = RcParseAnyElement(tktDTSERVER,ptk,ptks,&((*ppsonrs)->szDTSERVER));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check for ERROR (Optional) */
	if (ptk->tkt == tktERROR)
	{
		/* Parse ERROR */
		rcReturn = RcParseAnyElement(tktERROR,ptk,ptks,&((*ppsonrs)->szERROR));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse SESSKEY */
	rcReturn = RcParseAnyElement(tktSESSKEY,ptk,ptks,&((*ppsonrs)->szSESSKEY));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check for SERVICE (Optional) */
	if (ptk->tkt == tktSERVICE)
	{
		/* Parse SERVICE */
		rcReturn = RcParseAnyElement(tktSERVICE,ptk,ptks,&((*ppsonrs)->szSERVICE1));
		if (rcReturn != ALL_OK)
			goto _END;

		/* Check for a second SERVICE (Optional) */
		if (ptk->tkt == tktSERVICE)
		{
			/* Parse SERVICE */
			rcReturn = RcParseAnyElement(tktSERVICE,ptk,ptks,&((*ppsonrs)->szSERVICE2));
			if (rcReturn != ALL_OK)
				goto _END;
		}

		/* Check for a DAYSREQD (Optional) */
		if (ptk->tkt == tktDAYSREQD)
		{
			/* Parse DAYSREQD */
			rcReturn = RcParseAnyElement(tktDAYSREQD,ptk,ptks,&((*ppsonrs)->szDAYSREQD));
			if (rcReturn != ALL_OK)
				goto _END;
		}

		/* Check for a DAYSWITH (Optional) */
		if (ptk->tkt == tktDAYSWITH)
		{
			/* Parse DAYSWITH */
			rcReturn = RcParseAnyElement(tktDAYSWITH,ptk,ptks,&((*ppsonrs)->szDAYSWITH));
			if (rcReturn != ALL_OK)
				goto _END;
		}
	}


	/* Parse the </SONRS> */
	rcReturn = RcParseTag(tktEndSONRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*ppsonrs) 
		{
			free(*ppsonrs);
			*ppsonrs = NULL;
		}
	}

	return rcReturn;

}	/* end RcParseSONRS */

/* ---------------------------------------------------------------------------------
// Function: RcParseMAINTRQ
//
// Parses a MAINTRQ.  It handles a begin tag <MAINTRQ>, all subordinate tags, and an 
// end tag </MAINTRQ>.  The tags may be optional. 
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//	ppvData - memory containing the output structure, structure may vary depending 
//		on subordinate tags
//  ofctype - type of MAINTRQ (could be ofctypeACCTRQ, ofctypePAYEERQ, ofctypeMAILRQ)
//
// Notes: 
// - According to the DTD:
//   - CLTID, ACTION, (ACCTRQ|PAYEERQ|MAILRQ)
//
// History: 
//	2/23/96	Derek Hazeur - Created
// ------------------------------------------------------------------------------ */
int RcParseMAINTRQ(TOKEN *ptk, TOKENSTATE *ptks, void **ppvData, OFCTYPE *ofctype)
{
	int rcReturn;	/* function return code */
	char *szCLTID;	/* the CLTID */
	char *szACTION;	/* the ACTION */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppvData == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* NULL Local Pointers */
	szCLTID = NULL; 
	szACTION = NULL; 

	/* Parse the <MAINTRQ> */
	rcReturn = RcParseTag(tktMAINTRQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse CLTID */
	rcReturn = RcParseAnyElement(tktCLTID,ptk,ptks,&szCLTID);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse ACTION */
	rcReturn = RcParseAnyElement(tktACTION,ptk,ptks,&szACTION);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check for tktACCTRQ, tktPAYEERQ, or tktMAILRQ */
	if (ptk->tkt == tktACCTRQ)
	{
		/* Parse ACCTRQ */
		rcReturn = RcParseACCTRQ(ptk,ptks,szCLTID,szACTION,(ACCTRQ **) ppvData);
		if (rcReturn != ALL_OK)
			goto _END;

		/* Return the type of MAINTRQ to caller */
		*ofctype = ofctypeACCTRQ;
	}
	else if (ptk->tkt == tktPAYEERQ)
	{
		/* Parse PAYEERQ */
		rcReturn = RcParsePAYEERQ(ptk, ptks, szCLTID,szACTION,(PAYEERQ**) ppvData);
		if (rcReturn != ALL_OK)
			goto _END;

		/* Return the type of MAINTRQ to caller */
		*ofctype = ofctypePAYEERQ;
	}
	else if (ptk->tkt == tktMAILRQ)
	{
		/* Parse MAILRQ */
		rcReturn = RcParseMAILRQ(ptk,ptks,szCLTID,szACTION,(MAILRQ **) ppvData);

		if (rcReturn != ALL_OK)
			goto _END;

		/* Return the type of MAINTRQ to caller */
		*ofctype = ofctypeMAILRQ;

	}
	else
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Parse the </MAINTRQ> */
	rcReturn = RcParseTag(tktEndMAINTRQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	return rcReturn;

}	/* end RcParseMAINTRQ */

/* ---------------------------------------------------------------------------------
// Function: RcParseMAINTRS
//
// Parses a MAINTRS.  It handles a begin tag <MAINTRS>, all subordinate tags, and an 
// end tag </MAINTRS>.  The tags may be optional. 
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//	ppvData - memory containing the output structure, structure may vary depending 
//		on subordinate tags
//  ofctype - type of MAINTRS (could be ofctypeACCTRS, ofctypePAYEERS, ofctypeMAILRS)
//
// Notes: 
// - According to the DTD:
//   - CLTID, STATUS, ERROR?,(ACCTRS|PAYEERS|MAILRS)
//
// History: 
//	2/23/96	Derek Hazeur - Created
// ------------------------------------------------------------------------------- */
int RcParseMAINTRS(TOKEN *ptk, TOKENSTATE *ptks, void **ppvData, OFCTYPE *ofctype)
{
	int rcReturn;	/* function return code */
	char *szCLTID;	/* the CLTID */
	char *szSTATUS;	/* the ACTION */
	char *szERROR;	/* the ERROR */
	int nStatus;	/* the STATUS (integer) */
 
	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppvData == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* NULL Local Pointers */
	szCLTID = NULL; 
	szSTATUS = NULL; 
	szERROR	= NULL;

	/* Parse the <MAINTRS> */
	rcReturn = RcParseTag(tktMAINTRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse CLTID */
	rcReturn = RcParseAnyElement(tktCLTID,ptk,ptks,&szCLTID);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse STATUS */
	rcReturn = RcParseAnyElement(tktSTATUS,ptk,ptks,&szSTATUS);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check for ERROR (Optional) */
	if (ptk->tkt == tktERROR)
	{
		/* Parse ERROR */
		rcReturn = RcParseAnyElement(tktERROR,ptk,ptks,&szERROR);
		if (rcReturn != ALL_OK)
			goto _END;
	}

	// Make the STATUS an int
	nStatus = atol(szSTATUS); 

	// The only STATUS codes that allow for data are 0:Success and 4:Unsolicited
	if ((nStatus != 0) && (nStatus != 4))
	{
#ifdef _TESTAPP
		rcReturn = RcParseERRORRS(ptk, ptks, szCLTID, szSTATUS, szERROR, (ERRORRS**)ppvData, 
									ofctypeACCTRS);
#else
		rcReturn = RcParseERRORRS(ptk, ptks, szCLTID, szSTATUS, szERROR, (ERRORRS**)ppvData);
#endif
		if (rcReturn != ALL_OK)
			goto _END;

		*ofctype = ofctypeERRORRS;
	}
	else if (ptk->tkt == tktACCTRS)
	{
		/* Parse ACCTRS */
		rcReturn = RcParseACCTRS(ptk,ptks,szCLTID,szSTATUS,(ACCTRS **)ppvData);
		if (rcReturn != ALL_OK)
			goto _END;

		/* Return the type of MAINTRS to caller */
		*ofctype = ofctypeACCTRS;

	}
	else if (ptk->tkt == tktPAYEERS)
	{
		/* Parse PAYEERQ */
		rcReturn = RcParsePAYEERS(ptk,ptks,szCLTID,szSTATUS,(PAYEERS**)ppvData);
		if (rcReturn != ALL_OK)
			goto _END;

		/* Return the type of MAINTRS to caller */
		*ofctype = ofctypePAYEERS;

	}
	else if (ptk->tkt == tktMAILRS)
	{
		/* Parse MAILRS */
		rcReturn = RcParseMAILRS(ptk, ptks, szCLTID, szSTATUS, (MAILRS**)ppvData);
		if (rcReturn != ALL_OK)
			goto _END;

		/* Return the type of MAINTRS to calle */
		*ofctype = ofctypeMAILRS;
	}
	else
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Parse the </MAINTRS> */
	rcReturn = RcParseTag(tktEndMAINTRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	return rcReturn;

}	/* end RcParseMAINTRS */

/* ---------------------------------------------------------------------------------
// Function: RcParseERRORRS
//
// Deals with allocating and filling out the ERRORRS structure for error conditions
// in a MAINTRS or TRNRS.
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//  szCLTID - the CLTID  (Parsed by caller)
//  szSTATUS - the STATUS (Parsed by caller)
//  szERROR - the ERROR (Parsed by caller)  // may be NULL
//	pperrorrs - memory containing the ERRORRS structure
//
// NOTE: There are 2 "versions" of this function, one for normal parsing and 
// one for the test application we are using to validate parse/build.  
//
//
// History: 
//	3/05/96	TimHa - Created
//
// ------------------------------------------------------------------------------ */
#ifdef _TESTAPP
int RcParseERRORRS(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szSTATUS,
					 char *szERROR,ERRORRS **pperrorrs,  OFCTYPE ofctype)
#else
int RcParseERRORRS(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szSTATUS,
				 char *szERROR,ERRORRS **pperrorrs)
#endif
{

	int rcReturn;

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (pperrorrs == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Allocate memory */
	*pperrorrs = (ERRORRS *) malloc(sizeof(ERRORRS));
	if (*pperrorrs == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*pperrorrs,0,sizeof(ERRORRS));

	/* Initialize the items passed in by caller */
	(*pperrorrs)->szCLTID = szCLTID;
	(*pperrorrs)->szSTATUS = szSTATUS;
	(*pperrorrs)->szERROR = szERROR;

#ifdef _TESTAPP
	/* For the test app set the type that was passed */
	(*pperrorrs)->ofctype = ofctype;
#else
	/* For normal parse set to Nil */
	(*pperrorrs)->ofctype = ofctypeNil;
#endif

	/* set to OK status */
	rcReturn = ALL_OK;

_END:
	return rcReturn;
}

/* ---------------------------------------------------------------------------------
// Function: RcParseACCTRQ
//
// Parses a ACCTRQ.  It handles a begin tag <ACCTRQ>, all subordinate tags, and an 
// end tag </ACCTRQ>.  The tags may be optional. A ACCTRQ structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//  szCLTID - the CLTID  (Parsed by caller)
//  szACTION - the ACTION (Parsed by caller)
//	ppacctrq - memory containing the ACCTRQ structure
//
// Notes: 
// - According to the DTD:
//   - ACCTFROM,SERVRQST+
//
// History: 
//	2/23/96	Derek Hazeur - Created
//
// ------------------------------------------------------------------------------- */
int RcParseACCTRQ(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szACTION,
				 ACCTRQ **ppacctrq)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppacctrq == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <ACCTRQ> */
	rcReturn = RcParseTag(tktACCTRQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*ppacctrq = (ACCTRQ *) malloc(sizeof(ACCTRQ));
	if (*ppacctrq == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*ppacctrq,0,sizeof(ACCTRQ));

	/* Initialize the items passed in by caller */
	(*ppacctrq)->szCLTID = szCLTID;
	(*ppacctrq)->szACTION = szACTION;

	/* Parse ACCTFROM */
	rcReturn = RcParseACCTFROM(ptk,ptks,(void**)&((*ppacctrq)->pacctACCTFROM));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse SERVRQST */
	rcReturn = RcParseSERVRQST(ptk,ptks,&((*ppacctrq)->psrqstSERVRQST1));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check for second SERVRQST (Optional) */
	if (ptk->tkt == tktSERVRQST)
	{
		/* Parse SERVRQST */
		rcReturn = RcParseSERVRQST(ptk,ptks,&((*ppacctrq)->psrqstSERVRQST2));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse the </ACCTRQ> */
	rcReturn = RcParseTag(tktEndACCTRQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*ppacctrq) 
		{
			free(*ppacctrq);
			*ppacctrq = NULL;
		}
	}

	return rcReturn;

}	/* end RcParseACCTRQ */

/* ---------------------------------------------------------------------------------
// Function: RcParseACCTRS
//
// Parses a ACCTRS.  It handles a begin tag <ACCTRS>, all subordinate tags, and an 
// end tag </ACCTRS>.  The tags may be optional. A ACCTRS structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//  szCLTID - the CLTID  (Parsed by caller)
//  szSTATUS - the STATUS (Parsed by caller)
//	ppacctrs - memory containing the ACCTRS structure
//
// Notes: 
// - According to the DTD:
//   - SERVAUTH+
//
// History: 
//	2/23/96	Derek Hazeur - Created
//
// ------------------------------------------------------------------------------ */
int RcParseACCTRS(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szSTATUS,
				 ACCTRS **ppacctrs)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppacctrs == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <ACCTRS> */
	rcReturn = RcParseTag(tktACCTRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*ppacctrs = (ACCTRS *) malloc(sizeof(ACCTRS));
	if (*ppacctrs == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*ppacctrs,0,sizeof(ACCTRS));

	/* Initialize the items passed in by caller */
	(*ppacctrs)->szCLTID = szCLTID;
	(*ppacctrs)->szSTATUS = szSTATUS;

	/* Parse SERVAUTH */
	rcReturn = RcParseSERVAUTH(ptk,ptks,&((*ppacctrs)->psauthSERVAUTH1));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check for second SERVAUTH (Optional) */
	if (ptk->tkt == tktSERVAUTH)
	{
		/* Parse SERVAUTH */
		rcReturn = RcParseSERVAUTH(ptk,ptks,&((*ppacctrs)->psauthSERVAUTH2));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse the </ACCTRS> */
	rcReturn = RcParseTag(tktEndACCTRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*ppacctrs) 
		{
			free(*ppacctrs);
			*ppacctrs = NULL;
		}
	}

	return rcReturn;

}	/* end RcParseACCTRS */

/* ---------------------------------------------------------------------------------
// Function: RcParseACCTFROM
//
// Parses a ACCTFROM.  It handles a begin tag <ACCTFROM>, all subordinate tags, and an 
// end tag </ACCTFROM>.  The tags may be optional. 
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//	ppvData - memory containing the output structure
//
// Notes: 
// - According to the DTD:
//   - ACCOUNT
//
// History: 
//	2/23/96	Derek Hazeur - Created
// ------------------------------------------------------------------------------- */
int RcParseACCTFROM(TOKEN *ptk, TOKENSTATE *ptks, void **ppvData)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppvData == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <ACCTFROM> */
	rcReturn = RcParseTag(tktACCTFROM,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the ACCOUNT */
	rcReturn = RcParseACCOUNT(ptk,ptks,(ACCOUNT **) ppvData);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the </ACCTFROM> */
	rcReturn = RcParseTag(tktEndACCTFROM,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	return rcReturn;

}	/* end RcParseACCTFROM */

/* ---------------------------------------------------------------------------------
// Function: RcParseACCTTO
//
// Parses a ACCTTO.  It handles a begin tag <ACCTTO>, all subordinate tags, and an 
// end tag </ACCTTO>.  The tags may be optional. 
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//	ppvData - memory containing the output structure
//
// Notes: 
// - According to the DTD:
//   - ACCOUNT
//
// History: 
//	2/26/96	TimHa - Created
// ------------------------------------------------------------------------------ */
int RcParseACCTTO(TOKEN *ptk, TOKENSTATE *ptks, void **ppvData)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppvData == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <ACCTTO> */
	rcReturn = RcParseTag(tktACCTTO,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the ACCOUNT */
	rcReturn = RcParseACCOUNT(ptk,ptks,(ACCOUNT **) ppvData);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the </ACCTTO> */
	rcReturn = RcParseTag(tktEndACCTTO,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	return rcReturn;

} /* RcParseACCTTO */


/* ---------------------------------------------------------------------------------
// Function: RcParseACCOUNT
//
// Parses a ACCOUNT.  It handles a begin tag <ACCOUNT>, all subordinate tags, and an 
// end tag </ACCOUNT>.  The tags may be optional. A ACCOUNT structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//	ppacct - memory containing the ACCOUNT structure
//
// Notes: 
// - According to the DTD:
//   - BANKID, BRANCHID?, ACCTID, ACCTTYPE
//
// History: 
//	2/23/96	Derek Hazeur - Created
//
// ------------------------------------------------------------------------------ */
int RcParseACCOUNT(TOKEN *ptk, TOKENSTATE *ptks, ACCOUNT **ppacct)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppacct == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Allocate memory */
	*ppacct = (ACCOUNT *) malloc(sizeof(ACCOUNT));
	if (*ppacct == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*ppacct,0,sizeof(ACCOUNT));

	/* Parse the <ACCOUNT> */
	rcReturn = RcParseTag(tktACCOUNT,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse BANKID */
	rcReturn = RcParseAnyElement(tktBANKID,ptk,ptks,&(*ppacct)->szBANKID);
	if (rcReturn != ALL_OK)
		goto _END;
	
	/* Check for second BRANCHID (Optional) */
	if (ptk->tkt == tktBRANCHID)
	{
		/* Parse BRANCHID */
		rcReturn = RcParseAnyElement(tktBRANCHID,ptk,ptks,&(*ppacct)->szBRANCHID);
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse ACCTID */
	rcReturn = RcParseAnyElement(tktACCTID,ptk,ptks,&(*ppacct)->szACCTID);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse ACCTTYPE */
	rcReturn = RcParseAnyElement(tktACCTTYPE,ptk,ptks,&(*ppacct)->szACCTTYPE);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the </ACCOUNT> */
	rcReturn = RcParseTag(tktEndACCOUNT,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*ppacct) 
		{
			free(*ppacct);
			*ppacct = NULL;
		}
	}

	return rcReturn;

}	/* end RcParseACCOUNT */

/* ---------------------------------------------------------------------------------
// Function: RcParseSERVRQST
//
// Parses a SERVRQST.  It handles a begin tag <SERVRQST>, all subordinate tags, and an 
// end tag </SERVRQST>.  The tags may be optional. A SERVRQST structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//	ppsrqst - memory containing the SERVRQST structure
//
// Notes: 
// - According to the DTD:
//   - SERVICE, ACTION
//
// History: 
//	2/23/96	Derek Hazeur - Created
//
// ------------------------------------------------------------------------------ */
int RcParseSERVRQST(TOKEN *ptk, TOKENSTATE *ptks, SERVRQST **ppsrqst)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppsrqst == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Allocate memory */
	*ppsrqst = (SERVRQST *) malloc(sizeof(SERVRQST));
	if (*ppsrqst == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*ppsrqst,0,sizeof(SERVRQST));

	/* Parse the <SERVRQST> */
	rcReturn = RcParseTag(tktSERVRQST,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse SERVICE */
	rcReturn = RcParseAnyElement(tktSERVICE,ptk,ptks,&(*ppsrqst)->szSERVICE);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse ACTION */
	rcReturn = RcParseAnyElement(tktACTION,ptk,ptks,&(*ppsrqst)->szACTION);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the </SERVRQST> */
	rcReturn = RcParseTag(tktEndSERVRQST,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*ppsrqst) 
		{
			free(*ppsrqst);
			*ppsrqst = NULL;
		}
	}

	return rcReturn;

}	/* end RcParseSERVRQST */

/* ---------------------------------------------------------------------------------
// Function: RcParseSERVAUTH
//
// Parses a SERVAUTH.  It handles a begin tag <SERVAUTH>, all subordinate tags, and an 
// end tag </SERVAUTH>.  The tags may be optional. A SERVAUTH structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//	ppauth - memory containing the SERVAUTH structure
//
// Notes: 
// - According to the DTD:
//   - SERVICE, STATUS
//
// History: 
//	2/23/96	Derek Hazeur - Created
//
// ------------------------------------------------------------------------------ */
int RcParseSERVAUTH(TOKEN *ptk, TOKENSTATE *ptks, SERVAUTH **ppauth)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppauth == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Allocate memory */
	*ppauth = (SERVAUTH *) malloc(sizeof(SERVAUTH));
	if (*ppauth == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*ppauth,0,sizeof(SERVAUTH));

	/* Parse the <SERVAUTH> */
	rcReturn = RcParseTag(tktSERVAUTH,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse SERVICE */
	rcReturn = RcParseAnyElement(tktSERVICE,ptk,ptks,&(*ppauth)->szSERVICE);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse STATUS */
	rcReturn = RcParseAnyElement(tktSTATUS,ptk,ptks,&(*ppauth)->szSTATUS);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the </SERVAUTH> */
	rcReturn = RcParseTag(tktEndSERVAUTH,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*ppauth) 
		{
			free(*ppauth);
			*ppauth = NULL;
		}
	}

	return rcReturn;

}	/* end RcParseSERVAUTH */


/* ---------------------------------------------------------------------------------
// Function: RcParseTRNRQ
//
// Parses a TRNRQ.  It handles a begin tag <TRNRQ>, all subordinate tags, and an 
// end tag </TRNRQ>.  The tags may be optional. A TRNRQ structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//	ppvData - memory containing the output structure, type depends on subordinate tags
//  ofctype - type of TRNRS (could be ofctypeSTMTRQ, ofctype INTRARQ, ofctype INTERRQ,
//									  ofctypePAYMTRQ or ofctype PAYIQRQ
//
//
// Notes: 
// - According to the DTD:
//   - CLTID, ACTION, (STMTRQ | INTRARQ | INTERRQ | PAYMTRQ | PAYIQRQ)
//
// History: 
//	2/26/96	TimHa - Created
//
// ------------------------------------------------------------------------------ */
int RcParseTRNRQ(TOKEN *ptk, TOKENSTATE *ptks, void **ppvData, OFCTYPE *ofctype)
{
	int rcReturn;	
	char *szCLTID;	/* the CLTID */
	char *szACTION;	/* the ACTION */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppvData == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* NULL Local Pointers */
	szCLTID = NULL; 
	szACTION = NULL; 

	/* Parse the <TRNRQ> */
	rcReturn = RcParseTag(tktTRNRQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse CLTID */
	rcReturn = RcParseAnyElement(tktCLTID,ptk,ptks,&szCLTID);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse ACTION */
	rcReturn = RcParseAnyElement(tktACTION,ptk,ptks,&szACTION);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check for tktINTRARQ, tktSTMTRQ, tktINTERRQ, tktPAYMTRQ or tktPAYIQRQ  */
	if (ptk->tkt == tktINTRARQ)
	{
		/* Parse INTRARQ */
		rcReturn = RcParseINTRARQ(ptk,ptks,szCLTID,szACTION,(INTRARQ **) ppvData);
		if (rcReturn != ALL_OK)
			goto _END;

		/* Return the type of TRNRQ to caller */
		*ofctype = ofctypeINTRARQ;
	}
	else if (ptk->tkt == tktSTMTRQ)
	{
		/* Parse STMTRQ */
		rcReturn = RcParseSTMTRQ(ptk,ptks,szCLTID,szACTION,(STMTRQ **) ppvData);		
		if (rcReturn != ALL_OK)
			goto _END;

		/* Return the type of TRNRQ to caller */
		*ofctype = ofctypeSTMTRQ;
	}
	else if (ptk->tkt == tktINTERRQ)
	{
		/* Parse INTERRQ */
		rcReturn = RcParseINTERRQ(ptk,ptks,szCLTID,szACTION,(INTERRQ **) ppvData);
		if (rcReturn != ALL_OK)
			goto _END;

		/* Return the type of TRNRQ to caller */
		*ofctype = ofctypeINTERRQ;

	}
	else if (ptk->tkt == tktPAYMTRQ)
	{
		/* Parse PAYMTRQ */
		rcReturn = RcParsePAYMTRQ(ptk,ptks,szCLTID,szACTION,(PAYMTRQ **) ppvData);
		if (rcReturn != ALL_OK)
			goto _END;

		/* Return the type of TRNRQ to caller */
		*ofctype = ofctypePAYMTRQ;

	}
	else if (ptk->tkt == tktPAYIQRQ)
	{
		/* Parse PAYIQRQ */
		rcReturn = RcParsePAYIQRQ(ptk,ptks,szCLTID,szACTION,(PAYIQRQ **) ppvData);
		if (rcReturn != ALL_OK)
			goto _END;

		/* Return the type of TRNRQ to caller */
		*ofctype = ofctypePAYIQRQ;

	}
	else
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Parse the </TRNRQ> */
	rcReturn = RcParseTag(tktEndTRNRQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	return rcReturn;
} /* RcParseTRNRQ */

/* ---------------------------------------------------------------------------------
// Function: RcParseTRNRS
//
// Parses a TRNRS.  It handles a begin tag <TRNRS>, all subordinate tags, and an 
// end tag </TRNRS>.  The tags may be optional. A TRNRS structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//	ppvData - memory containing the output structure, type depends on subordinate tags
//  ofctype - type of TRNRS (could be ofctypeSTMTRS, ofctype INTRARS, ofctype INTERRS,
//									  ofctypePAYMTRS or ofctype PAYIQRS
//
// Notes: 
// - According to the DTD:
//     - CLTID, STATUS, ERROR? (STMTRS | INTRARS | INTERRS | PAYMTRS | PAYIQRS)
//
// History: 
//	2/26/96	TimHa - Created
//
// ------------------------------------------------------------------------------- */
int RcParseTRNRS(TOKEN *ptk, TOKENSTATE *ptks, void **ppvData, OFCTYPE *ofctype)
{
	int rcReturn;	
	char *szCLTID;	/* the CLTID */
	char *szSTATUS;	/* the STATUS */
	char *szERROR;	/* the ERROR */
	int nStatus;	/* the STATUS (integer) */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppvData == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* NULL Local Pointers */
	szCLTID = NULL; 
	szSTATUS = NULL; 
	szERROR = NULL;

	/* Parse the <TRNRS> */
	rcReturn = RcParseTag(tktTRNRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse CLTID */
	rcReturn = RcParseAnyElement(tktCLTID,ptk,ptks,&szCLTID);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse STATUS */
	rcReturn = RcParseAnyElement(tktSTATUS,ptk,ptks,&szSTATUS);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse ERROR if it exsists */
	if (ptk->tkt == tktERROR)
	{
		/* Parse ERROR */
		rcReturn = RcParseAnyElement(tktERROR,ptk,ptks,&szERROR);
		if (rcReturn != ALL_OK)
			goto _END;

	}

	// Make the STATUS an int
	nStatus = atol(szSTATUS);

	// The only STATUS codes that allow for data are 0:Success and 4:Unsolicited
	if ((nStatus != 0) && (nStatus != 4))
	{
#ifdef _TESTAPP
		rcReturn = RcParseERRORRS(ptk, ptks, szCLTID, szSTATUS, szERROR, (ERRORRS**)ppvData, 
									ofctypeACCTRS);
#else
		rcReturn = RcParseERRORRS(ptk, ptks, szCLTID, szSTATUS, szERROR, (ERRORRS**)ppvData);
#endif
		if (rcReturn != ALL_OK)
			goto _END;

		*ofctype = ofctypeERRORRS;
	}
	/* Check for tktINTRARS, tktSTMTRS, tktINTERRS, tktPAYMTRS or tktPAYIQRS  */
	else if (ptk->tkt == tktINTRARS)
	{
		/* Parse INTRARS */
		rcReturn = RcParseINTRARS(ptk,ptks,szCLTID,szSTATUS,(INTRARS **) ppvData);
		if (rcReturn != ALL_OK)
			goto _END;

		/* Return the type of TRNRS to caller */
		*ofctype = ofctypeINTRARS;
	}
	else if (ptk->tkt == tktSTMTRS)
	{
		/* Parse STMTRS */
		rcReturn = RcParseSTMTRS(ptk,ptks,szCLTID,szSTATUS,(STMTRS **) ppvData);		
		if (rcReturn != ALL_OK)
			goto _END;

		/* Return the type of TRNRS to caller */
		*ofctype = ofctypeSTMTRS;
	}
	else if (ptk->tkt == tktINTERRS)
	{
		/* Parse INTERRS */
		rcReturn = RcParseINTERRS(ptk,ptks,szCLTID,szSTATUS,(INTERRS **) ppvData);
		if (rcReturn != ALL_OK)
			goto _END;

		/* Return the type of TRNRS to caller */
		*ofctype = ofctypeINTERRS;

	}
	else if (ptk->tkt == tktPAYMTRS)
	{
		/* Parse PAYMTRS */
		rcReturn = RcParsePAYMTRS(ptk,ptks,szCLTID,szSTATUS,(PAYMTRS **) ppvData);
		if (rcReturn != ALL_OK)
			goto _END;

		/* Return the type of TRNRS to caller */
		*ofctype = ofctypePAYMTRS;

	}
	else if (ptk->tkt == tktPAYIQRS)
	{
		/* Parse PAYIQRS */
		rcReturn = RcParsePAYIQRS(ptk,ptks,szCLTID,szSTATUS,(PAYIQRS **) ppvData);
		if (rcReturn != ALL_OK)
			goto _END;

		/* Return the type of TRNRS to caller */
		*ofctype = ofctypePAYIQRS;
	}
	else
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}


	/* Parse the </TRNRS> */
	rcReturn = RcParseTag(tktEndTRNRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	return rcReturn;
} /* RcParseTRNRS */


/* ---------------------------------------------------------------------------------
// Function: RcParseMAILRQ
//
// Parses a MAILRQ.  It handles a begin tag <MAILRQ>, all subordinate tags, and an 
// end tag </MAILRQ>.  The tags may be optional. A MAILRQ structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//  szCLTID - the CLTID (Parsed by caller)
//  szACTION - the ACTION (Parsed by caller)
//	ppmailrq - memory containing the MAILRQ structure
//
// Notes: 
// - According to the DTD:
//   - SERVICE, ACCTFROM?, (MEMO+)
//
// History: 
//	2/27/96	TimHa - Created
//
// ------------------------------------------------------------------------------- */
int RcParseMAILRQ(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szACTION, MAILRQ **ppmailrq)
{
		int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppmailrq == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <MAILRQ> */
	rcReturn = RcParseTag(tktMAILRQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*ppmailrq = (MAILRQ *) malloc(sizeof(MAILRQ));
	if (*ppmailrq == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*ppmailrq,0,sizeof(MAILRQ));

	/* Initialize the items passed in by caller */
	(*ppmailrq)->szCLTID = szCLTID;
	(*ppmailrq)->szACTION = szACTION;

	/* Parse SERVICE */
	rcReturn = RcParseAnyElement(tktSERVICE, ptk, ptks, &((*ppmailrq)->szSERVICE));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse ACCTFROM if needed */
	if (ptk->tkt == tktACCTFROM)
	{
		rcReturn = RcParseACCTFROM(ptk,ptks,(void**)&((*ppmailrq)->pacctACCTFROM));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse MEMOS */
	rcReturn = RcParseMemos(mfONEORMORE, ptk, ptks, &((*ppmailrq)->pmemoMEMO));
	if (rcReturn != ALL_OK)
		goto _END;


	/* Parse the </MAILRQ> */
	rcReturn = RcParseTag(tktEndMAILRQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*ppmailrq) 
		{
			free(*ppmailrq);
			*ppmailrq = NULL;
		}
	}

	return rcReturn;

} /* RcParseMAILRQ */


/* ---------------------------------------------------------------------------------
// Function: RcParseMAILRS
//
// Parses a MAILRS.  It handles a begin tag <MAILRS>, all subordinate tags, and an 
// end tag </MAILRS>.  The tags may be optional. A MAILRS structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//	szCLTID - the CLTID (Parsed by caller)
//  szSTATUS - the STATUS (Parsed by caller)
//  ppmailrs - memory containing the MAILRS structure
//
// Notes: 
// - According to the DTD:
//   - (MEMO*)
//
// History: 
//	2/27/96	TimHa - Created
//
// ------------------------------------------------------------------------------ */
int RcParseMAILRS(TOKEN *ptk, TOKENSTATE *ptks,  char * szCLTID, char * szSTATUS, 
				 MAILRS **ppmailrs)
{
		int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppmailrs == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <MAIlRS> */
	rcReturn = RcParseTag(tktMAILRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*ppmailrs = (MAILRS *) malloc(sizeof(MAILRS));
	if (*ppmailrs == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*ppmailrs,0,sizeof(MAILRS));

	/* Initialize the items passed in by caller */
	(*ppmailrs)->szCLTID = szCLTID;
	(*ppmailrs)->szSTATUS = szSTATUS;

	/* Parse MEMOs */
	rcReturn = RcParseMemos(mfZEROORMORE, ptk, ptks, &((*ppmailrs)->pmemoMEMO));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the </MAILRS> */
	rcReturn = RcParseTag(tktEndMAILRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*ppmailrs) 
		{
			free(*ppmailrs);
			*ppmailrs = NULL;
		}
	}

	return rcReturn;
} /* RcParseMAILRS */




/* ---------------------------------------------------------------------------------
// Function: RcParseACCTSTMT
//
// Parses a ACCTSTMT.  It handles a begin tag <ACCTSTMT>, all subordinate tags, and an 
// end tag </ACCTSTMT>.  The tags may be optional. A ACCTSTMT structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//  ppacctstmt - memory containing the ACCTSTMT structure
//
// Notes: 
// - According to the DTD:
//   - ACCTFROM, STMTRS
//
// History: 
//	2/27/96	TimHa - Created
//
// ------------------------------------------------------------------------------ */
int RcParseACCTSTMT(TOKEN *ptk, TOKENSTATE *ptks, ACCTSTMT **ppacctstmt)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppacctstmt == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <ACCTSTMT> */
	rcReturn = RcParseTag(tktACCTSTMT,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*ppacctstmt = (ACCTSTMT *) malloc(sizeof(ACCTSTMT));
	if (*ppacctstmt == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*ppacctstmt,0,sizeof(ACCTSTMT));

	/* Parse ACCOUNTFROM */
	rcReturn = RcParseACCTFROM(ptk,ptks,(void**)&((*ppacctstmt)->pacctACCTFROM));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse off the STMTRS tag */
	rcReturn = RcParseTag(tktSTMTRS, ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the DTSTART */
	rcReturn = RcParseAnyElement(tktDTSTART,ptk,ptks,&((*ppacctstmt)->szDTSTART));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse DTEND */
	rcReturn = RcParseAnyElement(tktDTEND,ptk,ptks,&((*ppacctstmt)->szDTEND));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse LEDGER */
	rcReturn = RcParseAnyElement(tktLEDGER,ptk,ptks,&((*ppacctstmt)->szLEDGER));
	if (rcReturn != ALL_OK)
		goto _END;


	/* Parse Statement Transactions */
	if (ptk->tkt == tktSTMTTRN)
	{
		rcReturn = RcParseSTMTTRN(ptk, ptks, (void **)&((*ppacctstmt)->pgtrnSTMTTRN));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Eat STMTRS End tag if it exists */
	rcReturn = RcParseTag(tktEndSTMTRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the </ACCTSTMT> */
	rcReturn = RcParseTag(tktEndACCTSTMT,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*ppacctstmt) 
		{
			free(*ppacctstmt);
			*ppacctstmt = NULL;
		}
	}

	return rcReturn;

} /* RcParseACCTSTMT */



