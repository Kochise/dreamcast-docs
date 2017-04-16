/* ---------------------------------------------------------------------------------
// Copyright(c) 1991-1996 Microsoft Corporation.  All rights reserved.
// ---------------------------------------------------------------------------------
// File: PPAYMENT.C
//
// Contains functions necessary to parse and OFC payment data.
// 
// Includes:
//		RcParseENTITY - parse an ENTITY
//		RcParsePAYEE - parse a payee (basically an ENTITY)
//		RcParsePAYEERQ - parse a payee request
//		RcParsePAYEERS - parse a payee response
//		RcParsePAYMTRQ - parse a payment request
//		RcParsePAYMTRS - parse a payment response
//		RcParsePAYIQRQ - parse a payment inquiry request
//		RcParsePAYIQRS - parse a payment inquiry response
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
// Function: RcParseENTITY
//
// Parses a ENTITY.  It handles a begin tag <ENTITY>, all subordinate tags, and an 
// end tag </ENTITY>.  The tags may be optional. A ENTITY structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//  ppentity - memory containing the ENTITY structure
//
// Notes: 
// - According to the DTD:
//   - (NAME+), (ADDRESS+), CITY, STATE, POSTALID, (PHONE+)
//
// History: 
//	2/27/96	TimHa - Created
//
// ------------------------------------------------------------------------------- */
int RcParseENTITY(TOKEN *ptk, TOKENSTATE *ptks, ENTITY **ppentity)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppentity == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Allocate memory */
	*ppentity = (ENTITY *) malloc(sizeof(ENTITY));
	if (*ppentity == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*ppentity,0,sizeof(ENTITY));

	/* Parse the <ENTITY> */
	rcReturn = RcParseTag(tktENTITY,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse up to 3 NAMEs, one is required */
	rcReturn = RcParseAnyElement(tktNAME,ptk,ptks,&(*ppentity)->szNAME1);
	if (rcReturn != ALL_OK)
		goto _END;
	
	/* Check for second NAME (Optional) */
	if (ptk->tkt == tktNAME)
	{
		/* Parse NAME */
		rcReturn = RcParseAnyElement(tktNAME,ptk,ptks,&(*ppentity)->szNAME2);
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Check for third NAME (Optional) */
	if (ptk->tkt == tktNAME)
	{
		/* Parse NAME */
		rcReturn = RcParseAnyElement(tktNAME,ptk,ptks,&(*ppentity)->szNAME3);
		if (rcReturn != ALL_OK)
			goto _END;
	}


	/* Parse ADDRESSs up to 3, one is required */
	rcReturn = RcParseAnyElement(tktADDRESS,ptk,ptks,&(*ppentity)->szADDRESS1);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check for 2nd ADDRESS (Optional) */
	if (ptk->tkt == tktADDRESS)
	{
		/* Parse ADDRESS */
		rcReturn = RcParseAnyElement(tktADDRESS,ptk,ptks,&(*ppentity)->szADDRESS2);
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Check for 3rd ADDRESS (Optional) */
	if (ptk->tkt == tktADDRESS)
	{
		/* Parse ADDRESS */
		rcReturn = RcParseAnyElement(tktADDRESS,ptk,ptks,&(*ppentity)->szADDRESS3);
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse CITY */
	rcReturn = RcParseAnyElement(tktCITY,ptk,ptks,&(*ppentity)->szCITY);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse STATE */
	rcReturn = RcParseAnyElement(tktSTATE,ptk,ptks,&(*ppentity)->szSTATE);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse POSTALID */
	rcReturn = RcParseAnyElement(tktPOSTALID,ptk,ptks,&(*ppentity)->szPOSTALID);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse PHONEs up to 2, one is required */
	rcReturn = RcParseAnyElement(tktPHONE,ptk,ptks,&(*ppentity)->szPHONE1);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Check for 2nd PHONE (Optional) */
	if (ptk->tkt == tktPHONE)
	{
		/* Parse PHONE */
		rcReturn = RcParseAnyElement(tktPHONE,ptk,ptks,&(*ppentity)->szPHONE2);
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse the </ACCOUNT> */
	rcReturn = RcParseTag(tktEndENTITY,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*ppentity) 
		{
			free(*ppentity);
			*ppentity = NULL;
		}
	}

	return rcReturn;

} /* RcParseENTITY */

/* ---------------------------------------------------------------------------------
// Function: RcParsePAYEE
//
// Parses a PAYEE.  It handles a begin tag <PAYEE>, all subordinate tags, and an 
// end tag </PAYEE>.  The tags may be optional. A PAYEE structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//  ppvData - memory containing the PAYEE (ENTITY) structure
//
// Notes: 
// - According to the DTD:
//   - ENTITY
//
// History: 
//	2/27/96	TimHa - Created
//
// ------------------------------------------------------------------------------- */
int RcParsePAYEE(TOKEN *ptk, TOKENSTATE *ptks, void **ppvData)
{
		int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppvData == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <PAYEE> */
	rcReturn = RcParseTag(tktPAYEE,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the ENTITY */
	rcReturn = RcParseENTITY(ptk,ptks,(ENTITY **) ppvData);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the </PAYEE> */
	rcReturn = RcParseTag(tktEndPAYEE,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	return rcReturn;

} /* RcParsePAYEE */


/* ---------------------------------------------------------------------------------
// Function: RcParsePAYEERQ
//
// Parses a PAYEERQ.  It handles a begin tag <PAYEERQ>, all subordinate tags, and an 
// end tag </PAYEERQ>.  The tags may be optional. A PAYEERQ structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//  szCLTID - the CLTID (Parsed by caller)
//  szACTION - the ACTION (Parsed by caller)
//	pppayeerq - memory containing the PAYEERQ structure
//
// Notes: 
// - According to the DTD:
//   - ACCTFROM, PAYEEID?, PAYEE, PAYACCT
//
// History: 
//	2/27/96	TimHa - Created
//
// ------------------------------------------------------------------------------- */
int RcParsePAYEERQ(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szACTION, PAYEERQ **pppayeerq)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (pppayeerq == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <PAYEERQ> */
	rcReturn = RcParseTag(tktPAYEERQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*pppayeerq = (PAYEERQ *) malloc(sizeof(PAYEERQ));
	if (*pppayeerq == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*pppayeerq,0,sizeof(PAYEERQ));

	/* Initialize the items passed in by caller */
	(*pppayeerq)->szCLTID = szCLTID;
	(*pppayeerq)->szACTION = szACTION;

	/* Parse PAYEE */
	rcReturn = RcParsePAYEE(ptk, ptks, (void**)&((*pppayeerq)->pentPAYEE));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse PAYEEID if it exists */
	if (ptk->tkt == tktPAYEEID)
	{
		rcReturn = RcParseAnyElement(tktPAYEEID, ptk, ptks, &((*pppayeerq)->szPAYEEID));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse the PAYACCT */
	rcReturn = RcParseAnyElement(tktPAYACCT, ptk, ptks, &((*pppayeerq)->szPAYACCT));
	if (rcReturn != ALL_OK)
		goto _END;


	/* Parse the </PAYEERQ> */
	rcReturn = RcParseTag(tktEndPAYEERQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*pppayeerq) 
		{
			free(*pppayeerq);
			*pppayeerq = NULL;
		}
	}

	return rcReturn;

} /* RcParsePAYEERQ */


/* ---------------------------------------------------------------------------------
// Function: RcParsePAYEERS
//
// Parses a PAYEERS.  It handles a begin tag <PAYEERS>, all subordinate tags, and an 
// end tag </PAYEERS>.  The tags may be optional. A PAYEERS structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//	szCLTID - the CLTID (Parsed by caller)
//  szSTATUS - the STATUS (Parsed by caller)
//  pppayeers - memory containing the PAYEERS structure
//
// Notes: 
// - According to the DTD:
//   - PAYEEID, PAYEE?, DAYSREQD, DAYSWITH
//
// History: 
//	2/27/96	TimHa - Created
//
// ------------------------------------------------------------------------------- */
int RcParsePAYEERS(TOKEN *ptk, TOKENSTATE *ptks,  char * szCLTID, char * szSTATUS, 
				 PAYEERS **pppayeers)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (pppayeers == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <PAYEERS> */
	rcReturn = RcParseTag(tktPAYEERS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*pppayeers = (PAYEERS *) malloc(sizeof(PAYEERS));
	if (*pppayeers == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*pppayeers,0,sizeof(PAYEERS));

	/* Initialize the items passed in by caller */
	(*pppayeers)->szCLTID = szCLTID;
	(*pppayeers)->szSTATUS = szSTATUS;

	/* Parse PAYEEID */
	rcReturn = RcParseAnyElement(tktPAYEEID, ptk, ptks, &((*pppayeers)->szPAYEEID));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse PAYEE if it exsists */
	if (ptk->tkt == tktPAYEE)
	{
		rcReturn = RcParsePAYEE(ptk, ptks, (void**)&((*pppayeers)->pentPAYEE));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse DAYSREQD */
	rcReturn = RcParseAnyElement(tktDAYSREQD, ptk, ptks, &((*pppayeers)->szDAYSREQD));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse DAYSWITH */
	rcReturn = RcParseAnyElement(tktDAYSWITH, ptk, ptks, &((*pppayeers)->szDAYSWITH));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the </PAYEERS> */
	rcReturn = RcParseTag(tktEndPAYEERS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*pppayeers) 
		{
			free(*pppayeers);
			*pppayeers = NULL;
		}
	}

	return rcReturn;
} /* RcParsePAYEERS */


/* ---------------------------------------------------------------------------------
// Function: RcParsePAYMTRQ
//
// Parses a PAYMTRQ.  It handles a begin tag <PAYMTRQ>, all subordinate tags, and an 
// end tag </PAYMTRQ>.  The tags may be optional. A PAYMTRQ structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//  szCLTID - the CLTID (Parsed by caller)
//  szACTION - the ACTION (Parsed by caller)
//	pppaymtrq - memory containing the PAYMTRQ structure
//
// Notes: 
// - According to the DTD:
//   - ACCTFROM, TRNAMT, (PAYEEID | (PAYEE, PAYACCT)), DTDUE, SRVRTID?, (MEMO*)
//
// History: 
//	2/27/96	TimHa - Created
//  4/24/96 DerekHa - PAYACCT always required
//
// ------------------------------------------------------------------------------- */
int RcParsePAYMTRQ(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szACTION, PAYMTRQ **pppaymtrq)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (pppaymtrq == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <PAYMTRQ> */
	rcReturn = RcParseTag(tktPAYMTRQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*pppaymtrq = (PAYMTRQ *) malloc(sizeof(PAYMTRQ));
	if (*pppaymtrq == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*pppaymtrq,0,sizeof(PAYMTRQ));

	/* Initialize the items passed in by caller */
	(*pppaymtrq)->szCLTID = szCLTID;
	(*pppaymtrq)->szACTION = szACTION;

	/* Parse ACCTFROM */
	rcReturn = RcParseACCTFROM(ptk,ptks,(void**)&((*pppaymtrq)->pacctACCTFROM));
	if (rcReturn != ALL_OK)
			goto _END;

	/* Parse TRNAMT */
	rcReturn = RcParseAnyElement(tktTRNAMT, ptk, ptks, &(*pppaymtrq)->szTRNAMT); 
	if (rcReturn != ALL_OK)
		goto _END;

	/* check for PAYEEID or PAYEE */
	if (ptk->tkt == tktPAYEEID)
	{
		/* easy case, get the PAYEEID */
		rcReturn = RcParseAnyElement(tktPAYEEID, ptk, ptks, &((*pppaymtrq)->szPAYEEID));
		if (rcReturn != ALL_OK)
			goto _END;
	} 
	else if (ptk->tkt == tktPAYEE)
	{
		/* parse the PAYEE first  */
		rcReturn = RcParsePAYEE(ptk, ptks, (void**)&((*pppaymtrq)->pentPAYEE));
		if (rcReturn != ALL_OK)
			goto _END;
	}
	else
	{
		/* oops, error here */
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Parse PAYACCT  */
	rcReturn = RcParseAnyElement(tktPAYACCT, ptk, ptks, &((*pppaymtrq)->szPAYACCT));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse DTDUE  */
	rcReturn = RcParseAnyElement(tktDTDUE, ptk, ptks, &((*pppaymtrq)->szDTDUE));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse SRVRTID if it exists */
	if (ptk->tkt == tktSRVRTID)
	{
		rcReturn = RcParseAnyElement(tktSRVRTID, ptk, ptks, &((*pppaymtrq)->szSRVRTID));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse MEMOs if any */
	rcReturn = RcParseMemos(mfZEROORMORE, ptk, ptks, &((*pppaymtrq)->pmemoMEMO));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the </PAYMTRQ> */
	rcReturn = RcParseTag(tktEndPAYMTRQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*pppaymtrq) 
		{
			free(*pppaymtrq);
			*pppaymtrq = NULL;
		}
	}

	return rcReturn;

} /* RcParsePAYMTRQ */

/* ---------------------------------------------------------------------------------
// Function: RcParsePAYMTRS
//
// Parses a PAYMTRS.  It handles a begin tag <PAYMTRS>, all subordinate tags, and an 
// end tag </PAYMTRS>.  The tags may be optional. A PAYMTRS structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//	szCLTID - the CLTID (Parsed by caller)
//  szSTATUS - the STATUS (Parsed by caller)
//  pppaymtrs - memory containing the PAYMTRS structure
//
// Notes: 
// - According to the DTD:
//   - SRVRTID, PAYEEID?
//
// History: 
//	2/27/96	TimHa - Created
//
// ------------------------------------------------------------------------------- */
int RcParsePAYMTRS(TOKEN *ptk, TOKENSTATE *ptks,  char * szCLTID, char * szSTATUS, 
				 PAYMTRS **pppaymtrs)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (pppaymtrs == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <PAYMTRS> */
	rcReturn = RcParseTag(tktPAYMTRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*pppaymtrs = (PAYMTRS *) malloc(sizeof(PAYMTRS));
	if (*pppaymtrs == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*pppaymtrs,0,sizeof(PAYMTRS));

	/* Initialize the items passed in by caller */
	(*pppaymtrs)->szCLTID = szCLTID;
	(*pppaymtrs)->szSTATUS = szSTATUS;

	/* Parse SRVRTID */
	rcReturn = RcParseAnyElement(tktSRVRTID, ptk, ptks, &((*pppaymtrs)->szSRVRTID));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse PAYEEID if it exists */
	if (ptk->tkt == tktPAYEEID)
	{
		rcReturn = RcParseAnyElement(tktPAYEEID, ptk, ptks, &((*pppaymtrs)->szPAYEEID));
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Parse the </PAYMTRS> */
	rcReturn = RcParseTag(tktEndPAYMTRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*pppaymtrs) 
		{
			free(*pppaymtrs);
			*pppaymtrs = NULL;
		}
	}

	return rcReturn;
} /* RcParsePAYMTRS */


/* ---------------------------------------------------------------------------------
// Function: RcParsePAYIQRQ
//
// Parses a PAYIQRQ.  It handles a begin tag <PAYIQRQ>, all subordinate tags, and an 
// end tag </PAYIQRQ>.  The tags may be optional. A PAYIQRQ structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//  szCLTID - the CLTID (Parsed by caller)
//  szACTION - the ACTION (Parsed by caller)
//	pppayiqrq - memory containing the PAYIQRQ structure
//
// Notes: 
// - According to the DTD:
//   - SRVRTID, (MEMO+)
//
// History: 
//	2/27/96	TimHa - Created
//
// ------------------------------------------------------------------------------- */
int RcParsePAYIQRQ(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szACTION, PAYIQRQ **pppayiqrq)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (pppayiqrq == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <PAYIQRQ> */
	rcReturn = RcParseTag(tktPAYIQRQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*pppayiqrq = (PAYIQRQ *) malloc(sizeof(PAYIQRQ));
	if (*pppayiqrq == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*pppayiqrq,0,sizeof(PAYIQRQ));

	/* Initialize the items passed in by caller */
	(*pppayiqrq)->szCLTID = szCLTID;
	(*pppayiqrq)->szACTION = szACTION;

	/* Parse SRVRTID */
	rcReturn = RcParseAnyElement(tktSRVRTID, ptk, ptks, &((*pppayiqrq)->szSRVRTID));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse MEMOs */
	rcReturn = RcParseMemos(mfONEORMORE, ptk, ptks, &((*pppayiqrq)->pmemoMEMO));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the </PAYIQRQ> */
	rcReturn = RcParseTag(tktEndPAYIQRQ,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*pppayiqrq) 
		{
			free(*pppayiqrq);
			*pppayiqrq = NULL;
		}
	}

	return rcReturn;

} /* RcParsePAYIQRQ */

/* ---------------------------------------------------------------------------------
// Function: RcParsePAYIQRS
//
// Parses a PAYIQRS.  It handles a begin tag <PAYIQRS>, all subordinate tags, and an 
// end tag </PAYIQRS>.  The tags may be optional. A PAYIQRS structure is allocated and 
// returned to the caller.  
//
// Parameters: 
//	ptk - the current token
//	ptks - the state of the token machine
//	szCLTID - the CLTID (Parsed by caller)
//  szSTATUS - the STATUS (Parsed by caller)
//  pppayiqrs - memory containing the PAYIQRS structure
//
// Notes: 
// - According to the DTD:
//   - SRVRTID, (MEMO*)
//
// History: 
//	2/27/96	TimHa - Created
//
// ------------------------------------------------------------------------------- */
int RcParsePAYIQRS(TOKEN *ptk, TOKENSTATE *ptks,  char * szCLTID, char * szSTATUS, 
				 PAYIQRS **pppayiqrs)
{
	int rcReturn;	/* function return code */ 

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (pppayiqrs == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the <PAYIQRS> */
	rcReturn = RcParseTag(tktPAYIQRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Allocate memory */
	*pppayiqrs = (PAYIQRS *) malloc(sizeof(PAYIQRS));
	if (*pppayiqrs == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END; 
	}

	/* Zero out return structure */
	memset(*pppayiqrs,0,sizeof(PAYIQRS));

	/* Initialize the items passed in by caller */
	(*pppayiqrs)->szCLTID = szCLTID;
	(*pppayiqrs)->szSTATUS = szSTATUS;

	/* Parse SRVRTID */
	rcReturn = RcParseAnyElement(tktSRVRTID, ptk, ptks, &((*pppayiqrs)->szSRVRTID));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the MEMOs */
	rcReturn = RcParseMemos(mfZEROORMORE, ptk, ptks, &((*pppayiqrs)->pmemoMEMO));
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the </PAYIQRS> */
	rcReturn = RcParseTag(tktEndPAYIQRS,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	/* If there was an error, free memory  */
	if (rcReturn != ALL_OK)
	{
		if (*pppayiqrs) 
		{
			free(*pppayiqrs);
			*pppayiqrs = NULL;
		}
	}

	return rcReturn;
} /* RcParsePAYIQRS */

