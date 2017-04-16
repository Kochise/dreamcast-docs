/* ---------------------------------------------------------------------------------
// Copyright(c) 1991-1996 Microsoft Corporation.  All rights reserved.
// ---------------------------------------------------------------------------------
// File: TOKEN.C
//
// Contains functions necessary to tokenize an OFC document
//
// 02/21/96	Derek Hazeur - Created
// ------------------------------------------------------------------------------- */

/* Standard Include Files  */
#include <stdio.h> 
#include <malloc.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

/* Other Include files */
#include "ofclink.h"	/* Functions to Create / Update linked list */
#include "pbtypes.h"	/* ofc parse & build types */
#include "parse.h"		/* parse only  */

#define iTableSize  173

/* token table for parsing */
TAGTABLENTRY rgtg[] = 
{	
	{tktOFC,bTRUE,dtNONE, "<OFC>\r\n", 7},	
	{tktEndOFC,bTRUE,dtNONE, "</OFC>", 6},

	{tktDTD,bTRUE,dtNUMSTR, "<DTD>", 5},	
	{tktEndDTD,bFALSE,dtNONE,"</DTD>", 6},

	{tktCPAGE,bTRUE,dtIDSTR,"<CPAGE>",7},		 
	{tktEndCPAGE,bFALSE,dtNONE,"</CPAGE>", 8},

	{tktSONRQ,bTRUE,dtNONE, "<SONRQ>\r\n", 9},		
	{tktEndSONRQ,bFALSE,dtNONE,"</SONRQ>\r\n", 10},		

	{tktSESSKEY,bTRUE,dtIDSTR, "<SESSKEY>", 9},		
	{tktEndSESSKEY,bFALSE,dtNONE, "</SESSKEY>",10},		

	{tktDTCLIENT,bTRUE,dtDTSTR,"<DTCLIENT>",10},		
	{tktEndDTCLIENT,bFALSE,dtNONE,"</DTCLIENT>",11},		

	{tktUSERID,bTRUE,dtIDSTR,"<USERID>",8},		
	{tktEndUSERID,bFALSE,dtNONE,"</USERID>",9},	

	{tktUSERPASS,bTRUE,dtCHARSTR,"<USERPASS>",10},	
	{tktEndUSERPASS,bFALSE,dtNONE,"</USERPASS>",11},

	{tktNEWPASS,bTRUE,dtCHARSTR,"<NEWPASS>",9},		
	{tktEndNEWPASS,bFALSE,dtNONE,"</NEWPASS>",10},	

	{tktSONRS,bTRUE,dtNONE,"<SONRS>\r\n",9},		
	{tktEndSONRS,bFALSE,dtNONE,"</SONRS>\r\n", 10},		

	{tktSTATUS,bTRUE,dtNUMSTR,"<STATUS>",8},		
	{tktEndSTATUS,bFALSE,dtNONE,"</STATUS>", 9},	

	{tktDTSERVER,bTRUE,dtDTSTR, "<DTSERVER>",10},		
	{tktEndDTSERVER,bFALSE,dtNONE,"</DTSERVER>",11},	

	{tktERROR,bTRUE,dtCHARSTR,"<ERROR>",7},			
	{tktEndERROR,bFALSE,dtNONE,"</ERROR>",8},	

	{tktSERVICE,bTRUE,dtNUMSTR, "<SERVICE>",9},		
	{tktEndSERVICE,bFALSE,dtNONE,"</SERVICE>",10},		

	{tktDAYSREQD,bTRUE,dtNUMSTR, "<DAYSREQD>",10},		
	{tktEndDAYSREQD,bFALSE,dtNONE, "</DAYSREQD>",11},	 

	{tktDAYSWITH,bTRUE,dtNUMSTR, "<DAYSWITH>", 10},		
	{tktEndDAYSWITH,bFALSE,dtNONE, "</DAYSWITH>",11},		

	{tktMAINTRQ,bTRUE,dtNONE, "<MAINTRQ>\r\n", 11},			
	{tktEndMAINTRQ,bFALSE,dtNONE,"</MAINTRQ>\r\n",12},		

	{tktACCTRQ,bTRUE,dtNONE, "<ACCTRQ>\r\n", 10},			
	{tktEndACCTRQ,bFALSE,dtNONE, "</ACCTRQ>\r\n", 11},		

	{tktPAYEE, bTRUE, dtNONE, "<PAYEE>\r\n", 9},			
	{tktEndPAYEE, bTRUE, dtNONE, "</PAYEE>\r\n", 10},		

	{tktMAILRQ,bTRUE,dtNONE,"<MAILRQ>\r\n", 10},			
	{tktEndMAILRQ,bFALSE,dtNONE,"</MAILRQ>\r\n",11},		

	{tktCLTID,bTRUE,dtIDSTR, "<CLTID>", 7},		
	{tktEndCLTID,bFALSE,dtNONE, "</CLTID>", 8},		

	{tktACTION,bTRUE,dtNUMSTR, "<ACTION>", 8},			
	{tktEndACTION,bFALSE,dtNONE, "</ACTION>", 9},		

	{tktACCOUNT,bFALSE,dtNONE, "<ACCOUNT>\r\n", 11},		
	{tktEndACCOUNT,bFALSE,dtNONE, "</ACCOUNT>\r\n", 12},	

	{tktBANKID,bTRUE,dtIDSTR, "<BANKID>", 8},			
	{tktEndBANKID,bFALSE,dtNONE, "</BANKID>", 9},		

	{tktBRANCHID,bTRUE,dtIDSTR, "<BRANCHID>", 10},		
	{tktEndBRANCHID,bFALSE,dtNONE, "</BRANCHID>", 11},		

	{tktACCTID,bTRUE,dtIDSTR, "<ACCTID>", 8},			
	{tktEndACCTID,bFALSE,dtNONE, "</ACCTID>", 9},		

	{tktACCTTYPE,bTRUE,dtNUMSTR, "<ACCTTYPE>", 10},		
	{tktEndACCTTYPE,bFALSE,dtNONE, "</ACCTTYPE>", 11},		

	{tktACCTFROM,bTRUE,dtNONE, "<ACCTFROM>\r\n", 12},		
	{tktEndACCTFROM,bTRUE,dtNONE,"</ACCTFROM>\r\n", 13},		

	{tktSERVRQST,bTRUE,dtNONE, "<SERVRQST>\r\n", 12},			
	{tktEndSERVRQST,bTRUE,dtNONE, "</SERVRQST>\r\n", 13},		

	{tktMAINTRS,bTRUE,dtNONE, "<MAINTRS>\r\n",  11},			
	{tktEndMAINTRS,bFALSE,dtNONE, "</MAINTRS>\r\n", 12},		

	{tktACCTRS,bTRUE,dtNONE, "<ACCTRS>\r\n", 10},			
	{tktEndACCTRS,bFALSE,dtNONE, "</ACCTRS>\r\n", 11},		

	{tktSERVAUTH,bTRUE,dtNONE, "<SERVAUTH>\r\n", 12},			
	{tktEndSERVAUTH,bTRUE,dtNONE, "</SERVAUTH>\r\n", 13},		

	{tktTRNRQ, bTRUE, dtNONE, "<TRNRQ>\r\n", 9},			
	{tktEndTRNRQ, bFALSE, dtNONE, "</TRNRQ>\r\n", 10},		

	{tktTRNRS, bTRUE, dtNONE, "<TRNRS>\r\n", 9},			
	{tktEndTRNRS, bFALSE, dtNONE, "</TRNRS>\r\n", 10},		

	{tktINTRARQ, bTRUE, dtNONE, "<INTRARQ>\r\n", 11},		
	{tktEndINTRARQ, bFALSE, dtNONE, "</INTRARQ>\r\n", 12},

	{tktINTRARS, bTRUE, dtNONE, "<INTRARS>\r\n", 11},	
	{tktEndINTRARS, bFALSE, dtNONE, "</INTRARS>\r\n", 12},	

	{tktTRNAMT, bTRUE, dtAMTSTR, "<TRNAMT>", 8},	
	{tktEndTRNAMT, bFALSE, dtNONE, "</TRNAMT>", 9},		

	{tktACCTTO, bTRUE, dtNONE, "<ACCTTO>\r\n", 10},		
	{tktEndACCTTO, bTRUE, dtNONE, "</ACCTTO>\r\n", 11},		

	{tktMEMO, bTRUE, dtCHARSTR, "<MEMO>", 6},		
	{tktEndMEMO, bFALSE, dtNONE, "</MEMO>", 7},		

	{tktSRVRTID, bTRUE, dtIDSTR, "<SRVRTID>", 9},		
	{tktEndSRVRTID, bFALSE, dtNONE, "</SRVRTID>", 10},	

	{tktDTPOSTED, bTRUE, dtDTSTR, "<DTPOSTED>", 10},		
	{tktEndDTPOSTED, bFALSE, dtNONE, "</DTPOSTED>", 11},	

	{tktMAILRS, bTRUE, dtNONE, "<MAILRS>\r\n", 10},			
	{tktEndMAILRS, bFALSE, dtNONE, "</MAILRS>\r\n", 11},	

	{tktACCTSTMT, bTRUE, dtNONE, "<ACCTSTMT>\r\n", 12},		
	{tktEndACCTSTMT, bFALSE, dtNONE, "</ACCTSTMT>\r\n", 13},

	{tktENTITY, bFALSE, dtNONE, "<ENTITY>\r\n", 10},		
	{tktEndENTITY, bFALSE, dtNONE, "</ENTITY>\r\n", 11},	

	{tktPAYEERS, bTRUE, dtNONE, "<PAYEERS>\r\n", 11},		
	{tktEndPAYEERS, bFALSE, dtNONE, "</PAYEERS>\r\n", 12},	

	{tktPAYEERQ,bTRUE,dtNONE, "<PAYEERQ>\r\n", 11},			
	{tktEndPAYEERQ,bFALSE,dtNONE, "</PAYEERQ>\r\n", 12},	

	{tktPAYEEID, bTRUE, dtIDSTR, "<PAYEEID>", 9},			
	{tktEndPAYEEID, bFALSE, dtNONE, "</PAYEEID>", 10},		

	{tktPAYACCT, bTRUE, dtCHARSTR, "<PAYACCT>", 9},			
	{tktEndPAYACCT, bFALSE, dtNONE, "</PAYACCT>", 10},		

	{tktNAME, bTRUE, dtCHARSTR, "<NAME>", 6},			
	{tktEndNAME, bFALSE, dtNONE, "</NAME>", 7},			

	{tktADDRESS, bTRUE, dtCHARSTR, "<ADDRESS>", 9},			
	{tktEndADDRESS,	bFALSE, dtNONE, "</ADDRESS>", 10},	

	{tktCITY, bTRUE, dtCHARSTR, "<CITY>", 6},			
	{tktEndCITY, bFALSE, dtNONE, "</CITY>", 7},			

	{tktSTATE, bTRUE, dtCHARSTR, "<STATE>", 7},			
	{tktEndSTATE, bFALSE, dtNONE, "</STATE>", 8},		

	{tktPOSTALID, bTRUE, dtIDSTR, "<POSTALID>", 10},		
	{tktEndPOSTALID, bFALSE, dtNONE, "</POSTALID>", 11},	

	{tktPHONE, bTRUE, dtCHARSTR, "<PHONE>", 7},			
	{tktEndPHONE, bFALSE, dtNONE, "</PHONE>", 8},		

	{tktSTMTRQ, bTRUE, dtNONE, "<STMTRQ>\r\n", 10},		
	{tktEndSTMTRQ, bFALSE, dtNONE, "</STMTRQ>\r\n", 11},		

	{tktSTMTRS, bTRUE, dtNONE, "<STMTRS>\r\n", 10},			
	{tktEndSTMTRS, bFALSE, dtNONE, "</STMTRS>\r\n", 11},		

	{tktDTSTART, bTRUE, dtDTSTR, "<DTSTART>", 9},		
	{tktEndDTSTART, bFALSE, dtNONE, "</DTSTART>", 10},	

	{tktDTEND, bTRUE, dtDTSTR, "<DTEND>", 7},			
	{tktEndDTEND, bFALSE, dtNONE, "</DTEND>", 8},		

	{tktLEDGER,	bTRUE, dtAMTSTR, "<LEDGER>", 8},		
	{tktEndLEDGER, bFALSE, dtNONE, "</LEDGER>", 9},		

	{tktSTMTTRN, bTRUE, dtNONE, "<STMTTRN>\r\n", 11},			
	{tktEndSTMTTRN, bTRUE, dtNONE, "</STMTTRN>\r\n", 12},		

	{tktGENTRN, bFALSE, dtNONE, "<GENTRN>\r\n", 10},	
	{tktEndGENTRN, bFALSE, dtNONE, "</GENTRN>\r\n", 11},		

	{tktTRNTYPE, bTRUE, dtNUMSTR, "<TRNTYPE>", 9},			
	{tktEndTRNTYPE, bFALSE, dtNONE, "</TRNTYPE>", 10},	

	{tktFITID, bTRUE, dtIDSTR, "<FITID>", 7},			
	{tktEndFITID, bFALSE, dtNONE, "</FITID>", 8},		

	{tktCHKNUM, bTRUE, dtIDSTR, "<CHKNUM>", 8},			
	{tktEndCHKNUM, bFALSE, dtNONE, "</CHKNUM>", 9},		

	{tktSIC, bTRUE, dtNUMSTR, "<SIC>", 5},				
	{tktEndSIC, bFALSE, dtNONE, "</SIC>", 6},		

	{tktPAYMTRQ, bTRUE, dtNONE, "<PAYMTRQ>\r\n", 11},			
	{tktEndPAYMTRQ, bFALSE, dtNONE, "</PAYMTRQ>\r\n", 12},		

	{tktPAYMTRS, bTRUE, dtNONE, "<PAYMTRS>\r\n", 11},			
	{tktEndPAYMTRS, bFALSE, dtNONE, "</PAYMTRS>\r\n", 12},	

	{tktDTDUE, bTRUE, dtDTSTR, "<DTDUE>", 7},		
	{tktEndDTDUE, bFALSE, dtNONE, "</DTDUE>", 8},		

	{tktPAYIQRQ,bTRUE, dtNONE, "<PAYIQRQ>\r\n", 11},		
	{tktEndPAYIQRQ, bFALSE, dtNONE, "</PAYIQRQ>\r\n", 12},	

	{tktPAYIQRS, bTRUE, dtNONE, "<PAYIQRS>\r\n", 11},		
	{tktEndPAYIQRS, bFALSE, dtNONE, "</PAYIQRS>\r\n", 12},	

	{tktINTERRQ, bTRUE, dtNONE, "<INTERRQ>\r\n", 11},		
	{tktEndINTERRQ,	bFALSE, dtNONE, "</INTERRQ>\r\n", 12},

	{tktINTERRS, bTRUE, dtNONE, "<INTERRS>\r\n", 11},		
	{tktEndINTERRS,	bFALSE, dtNONE, "</INTERRS>\r\n", 12},	


	{tktEOF,bFALSE,dtNONE, "", 0}				/* End Of File */
};

// hash table into rgtg
TAGTABLENTRY tgUnknown = {tktUnknown, bFALSE, dtNONE, "Unknown", 7};
TAGTABLENTRY *rgptg[iTableSize];

void Hash(char *pchBegin,				// IN: string to hash
			int cbToken,				// IN: length of string
			unsigned long *pulHash,		// OUT: first hash
			unsigned long *pulRehash);	// OUT: rehash


/* ---------------------------------------------------------------------------------
// Function: RcInitializeToken
// 
// Initializes the token machine. This function MUST be called before RcReadToken
// This function reads past all the whitespace at the beginning of the file. 
// Then it goes out the the end of the buffer and reads backwards to find 
// the last non-whitespace character in the file. If that character is not a '>'
// and error is returned to the caller. The token state is initialized in a way 
// that it will only read until that last '>' (i.e. bytes to read = cbAvailable -
// number of whitespace characters at start - number of whitespace/NULL characters 
// at end). 
// 
// Note: When walking backwards, NULLs '\0' are treated as whitespace (ONLY here) 
// There should be NO NULL characters between the beginning of the buffer and the
// final end tag </OFC>
// 
// Parameters: 
//	ptks - the state of the token machine (updated by this function)
//	ptk - the current token  (updated by this function)
//	pvRequest - buffer that the token machine is to traverse
//  cbAvailable  - number of bytes in the buffer
//
// History: 
//	2/23/96	Derek Hazeur - Created
//
// ------------------------------------------------------------------------------- */
int RcInitializeToken(TOKEN *ptk, TOKENSTATE *ptks, void *pvRequest, int cbAvailable)
{
	int rcReturn;		/* function return code */
	char * pchFirst;	/* Beginning of buffer */
	char * pchLast;		/* Last character is buffer */

	/* Initilaize pointer to first character in buffer */
	pchFirst = pvRequest;
	
	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (pvRequest == NULL) ||
		((pchFirst + cbAvailable - 1) == NULL))
	{
		rcReturn = INVALID_CALL; 
		goto _END;
	}

	/* Initilaize pointer to last character in buffer */
	pchLast = pchFirst + cbAvailable - 1;

	/* Walk forwards until a non-whitespace character reached  */
	/* Take care not to step off the end  */
	while (isspace(*pchFirst) && (pchFirst < pchLast))
	{
		cbAvailable--;
		pchFirst++;
	}

	/* If the first non-whitespace character is not a '<' from a TAG, */
	/* return an error */
	if ((*pchFirst != '<') || (cbAvailable == 0))
	{
		rcReturn = OFC_ERROR; 
		goto _END;
	}

	/* Move to first character after the '<'. This is  */
	/* consistent with the way the token machine works, see RcReadToken */
	pchFirst++;
	cbAvailable--;

	/* Walk backwards until a non-whitespace / non-NULL character reached  */
	/* Take care not to step off the beginning */
	while ((isspace(*pchLast) || (*pchLast == '\0')) && (pchLast > pchFirst))
	{
		cbAvailable--;
		pchLast--;
	}

	/* If the last non-whitespace character is not a '>' from a TAG, */
	/* return an error */
	if ((*pchLast != '>') || (cbAvailable == 0))
	{
		rcReturn = OFC_ERROR; 
		goto _END;
	}

	/* Initialize the token structure */
	ptk->pch = NULL;			/* No Token */
	ptk->tkt = tktUnknown;		/* Token type not defined */
	ptk->cb = 0;				/* Token length = 0 */

	/* Initialize the token State */
	ptks->pchNext= pchFirst;
	ptks->cbAvailable = cbAvailable;
	ptks->cbDone = 0;

	/* Read the first Token */
	rcReturn = RcReadToken(ptk,ptks);

_END:

	return rcReturn;

} /* end RcInitializeToken */

/* ---------------------------------------------------------------------------------
// Function: RcReadToken
// 
// The heart of the OFC parser. This function should be called to advance to the 
// next token and to update the token state. 

// The token machine MUST be initialized with a call to TInitializeToken
// before this function is called. No other function should advance the 
// token or update the token state by any other means. 

// The token machine uses '<' and '>' as delimiters, therefore every call 1) read 
// to next delimiter, 2) sets variables within the TOKEN structure, 3) updates the 
// token machine state by updating variables within the TOKENSTATE structure. 
// Unless EOF reached, the machine always updates the token state pchNext pointer 
// to the first character 'after' the delimiter. If EOF is reached the next 
// pointer will be NULL, and the token type will be tktEOF.
// 
// Parameters: 
//	ptks - the state of the token machine (updated by this function)
//	ptk - the current token  (updated by this function)
//
// History: 
//	2/23/96	Derek Hazeur - Created

// ------------------------------------------------------------------------------- */
int RcReadToken(TOKEN* ptk, TOKENSTATE *ptks)
{
	/* Local Variables */
	char * pchCurr;		/* Pointer to traverse the buffer */
	int rcReturn;		/* Function Return code */
	int cbStripped;		/* Number of whitespace characters stripped */

	BOOL bTagNotValid;

	/* Initialize Variables */
	rcReturn = ALL_OK;
	bTagNotValid = bFALSE;

	/* Assure valid pointers before we begin  */
	if ((ptk == NULL) || (ptks == NULL) )
	{
		rcReturn = INVALID_CALL; 
		goto _END;
	}

	/* If we were already at EndOfFile then return */
	/* Should have never been called */
	if (ptk->tkt == tktEOF) 
	{
		rcReturn = INVALID_CALL; 
		goto _END;
	}

	/* If we have read all the bytes, then flag EOF */
	if (ptks->cbDone >= ptks->cbAvailable)
	{
		ptk->tkt = tktEOF;
		ptks->pchNext = NULL;
		goto _END;
	}

	/* If we have <TAG1><TAG2>..the first character can be */
	/* a '<'...This is OK..if there was at least one space */
	/* it would be caught by the isspace code below		   */
	if ((*(ptks->pchNext) == '<') && (ptk->tkt != tktDATA))
	{
		/* Move past the < and continue  */
		ptks->pchNext++;

		/* Add the number of read to cbDone */
		(ptks->cbDone)++;
	}

	if (isspace(*(ptks->pchNext)))
	{
		/* There are three cases where we can start at a space, two are			*/
		/* valid and one is invalid												*/
		/* 1)  <TAG1>     <TAG2>												*/
		/*           ^             This is valid, ignore spaces so tkt = TAG2	*/
		/* 2)  <TAG1>   data  <TAG2>											*/
		/*           ^             This is valid, tkt = data					*/
		/* 3)  <   TAG1>														*/
		/*      ^			       This is invalid								*/
		/*																		*/
		/* Thus..we could only arrive at Case #3 if the last type was DATA		*/
		/* because that's the only time that the character before the starting  */
		/* position would be a '<'												*/

		/* TBD: Assure that pchStripWhiteSpace does not walk off the end		*/
		/*		of the buffer													*/
		pchCurr = pchStripWhiteSpace(ptks->pchNext,&cbStripped);
		if (*pchCurr == '<')
		{
			/* This is Case #1 */
			/* Move past the < and continue as if it never happened */
			pchCurr++;
			ptks->pchNext = pchCurr;

			/* Add the number of read to cbDone */
			ptks->cbDone += cbStripped + 1;
		}
		else
		{
			/* This is case # 3, Invalid */
			if (ptk->tkt == tktDATA)
			{
				rcReturn = OFC_ERROR;
				goto _END;
			}
		}
	}

	/* Initialize token */
	ptk->cb		= 0;				/* Number of bytes read in token */
	ptk->tkt	= tktUnknown;		/* Type of tag */

	/* Set current of token to the token we are reading  */
	ptk->pch = ptks->pchNext;
			
	/* Assign moving pointer to beginning of token */
	pchCurr = ptk->pch;

	/* Read until the next delimtter found */
	pchCurr = pchReadToDelimiter(pchCurr,&ptk->cb);

	/* Increment cbDone by the size of the token */
	ptks->cbDone += ptk->cb;

	/* Let's determine what we have read (TAG or DATA) */
	if (*pchCurr == '>')
	{
		/* This is a tag */

		/* Determine which tag it is */
		ptk->tkt = tktTypeFromTag(ptk->pch,ptk->cb);
	}
	else
	{
		/* This token is DATA */
		ptk->tkt = tktDATA;
	}

	/* Next ReadToken should start reading at character after the  */
	/* Delimiter .  Read a character, so increment cbDone			 */
	ptks->pchNext = pchCurr + 1; 
	ptks->cbDone++;

	/* Set OK return code */
	rcReturn = ALL_OK;

_END:

	return rcReturn; 

} /* end RcReadToken */

/* ---------------------------------------------------------------------------------
// Function: pchReadToDelimiter 
//
// ------------------------------------------------------------------------------- */
char * pchReadToDelimiter(char *pchBegin,int *pcbToken)
{
	/* Local Variables */
	char * pchCurr;		/* Pointer to traverse the buffer */


	/* Assign moving pointer to beginning of buffer */
	pchCurr = pchBegin;

	/* Set byte count to zero */
	*pcbToken = 0;	

	/* Move pointer until next Delimiter   */

	/* TBD : Only read the MAX specified to assure we don't walk off end */

	/* Continue to move pointer until a delimiter is reached  */
	while ((*pchCurr != '>') && (*pchCurr != '<')) 
	{
		/* Increment pointer and byte count */
		(*pcbToken) = (*pcbToken) + 1;
		pchCurr++;
	}

	/* Return a pointer to the delimiter */
	return pchCurr;

} /* end pchReadToDelimiter  */

/* ---------------------------------------------------------------------------------
// Function: tktTypeFromTag
//
// NOTE: This is a temporary solution using strncmp for everything, we will
//		 turn this into a real lookup using a hash function in the future
//
// ------------------------------------------------------------------------------- */
TOKTYPE tktTypeFromTag(char *pchBegin, int cbToken)
{
	TOKTYPE tkt;  /* The type of the tag */
	int i =(int)*pchBegin;
	unsigned long ul = cbToken;
	unsigned long ulHash, ulRehash;
	int j;		/* just to make sure we stop when we don't have a match
 
	/* find the hash value for this token */
	Hash(pchBegin, ul, &ulHash, &ulRehash);
  	assert(rgptg[ulHash]->tagtype != tktUnknown);

	/* find the token in the hash table	*/
	j = 0;
	while((strncmp(pchBegin, (rgptg[ulHash]->szTag)+1 ,cbToken) != 0) && (j <= iTableSize))
		{
		/* we should not step through a hole in the table */
		assert(rgptg[ulHash]->tagtype != tktUnknown);
		ulHash = (ulRehash + ulHash)%iTableSize;
		j++;
		}
	tkt =  ( j <= iTableSize) ? rgptg[ulHash]->tagtype : tktUnknown;

	assert(tkt != tktUnknown);

	/* Return the tag type */
	return tkt ;

} /* end tktTypeFromTag */

/* ---------------------------------------------------------------------------------
// Function: pchStripWhiteSpace
//
// -------------------------------------------------------------------------------- */
char * pchStripWhiteSpace(char *pchBegin, int *pcbStripped)
{
	/* Local Variables */
	char * pchCurr;
	int cbStripCount; 

	/* Initialize count */
	cbStripCount = 0;

	/* Assign pointer to beginning of buffer */
	pchCurr = pchBegin;

	/* Increment pointer until a non-space reached */
	while (isspace(*pchCurr))
	{
		cbStripCount = cbStripCount + 1;
		pchCurr++;
	}

	/* If the caller wants a count, pass it on */
	if (pcbStripped != NULL)
		*pcbStripped = cbStripCount;

	return pchCurr; 

} /* end pchStripSpaces */

/* ---------------------------------------------------------------------------------
   Function: Hash
  
   -------------------------------------------------------------------------------- */
void Hash(char *pchBegin,	// IN: string to hash
			int cbToken,		// IN: length of string
			unsigned long *pulHash,	// OUT: first hash
			unsigned long *pulRehash)	// OUT: rehash
{
	int i;
	unsigned long ulHash = 0;
	unsigned long ulRehash = 0;

	for (i = 0; i + 1 < cbToken; )
		{
		ulHash = (ulHash << 4) + *pchBegin++;
		ulRehash = (ulRehash << 2) + *pchBegin++;
		i += 2;
		}

	ulHash %= iTableSize;
	ulRehash = ulRehash%iTableSize;
	if (ulRehash == 0)
		ulRehash = 1;

	*pulHash = ulHash;
	*pulRehash = ulRehash;
}
/* ---------------------------------------------------------------------------------
   Function: InitHash

   Initialize the hash table of sgml tags
  
   -------------------------------------------------------------------------------- */
void InitHash()	
{
	unsigned long cbTag;			/* number of characters in the tag */
	unsigned long ulHash, ulRehash;	/* hash and rehash of current tag */
	int i;

	for ( i = 0; i < iTableSize ; i++)
		rgptg[i] =  &tgUnknown;

	// set up the hash table
	i = 0;
	while(rgtg[i].tagtype != tktEOF)
		{
		assert(strchr(rgtg[i].szTag, '>') != NULL);

		cbTag = strchr(rgtg[i].szTag, '>') - rgtg[i].szTag - 1;

		// hash the tag
		Hash((rgtg[i].szTag) + 1, cbTag, &ulHash, &ulRehash);

		// find an empty bin for this tag
		while( rgptg[ulHash] != &tgUnknown)
			{
			ulHash = (ulHash + ulRehash) %iTableSize;
			}

		// put this tag in the bucket
		rgptg[ulHash] = &rgtg[i];

		i++;

		}


}
