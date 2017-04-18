/* ---------------------------------------------------------------------------------
// Copyright(c) 1991-1996 Microsoft Corporation.  All rights reserved.
// ---------------------------------------------------------------------------------
// File: PELEMENT.C
//
// Contains functions necessary to parse elements from an OFC document.
//
// 02/21/95	Derek Hazeur - Created
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
// Function: RcParseAnyElement
//
// Parses any basic ELEMENT.  It handles a begin tag <TAG>, the data, and an 
// end tag </TAG>.  The tags may be optional. 
//
// Parameters: 
//	tkt - the token type expected
//	ptk - the current token
//	ptks - the state of the token machine
//	ppchData - pointer where data is to be stored
//
// History: 
//	2/23/96	Derek Hazeur - Created
// ------------------------------------------------------------------------------- */
int RcParseAnyElement(TOKTYPE tkt, TOKEN *ptk, TOKENSTATE *ptks, char **ppchData)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppchData == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Parse the begin Tag <TAG> */
	rcReturn = RcParseTag(tkt,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the Data */
	rcReturn = RcGetBasicType(rgtg[tkt].dt,ptk,ptks,ppchData);
	if (rcReturn != ALL_OK)
		goto _END;

	/* Parse the end Tag </TAG> */
	/* tktEndTAG is always right after tktTAG in enum TOKTYPE. so just add 1 */
	rcReturn = RcParseTag(tkt + 1,ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	return rcReturn;

}	/* end RcParseAnyElement */


/* ---------------------------------------------------------------------------------
// Function: RcParseMemos
//
// Parses a group of MEMO tags.  Since MEMOs are linked together this function 
// will loop and generate the list of MEMOs and link them in to the caller structure
// via the ppmemo pointer passed in.  
//
// Parameters: 
//	mf - the memo flag, either ZEROORMORE or ONEORMORE
//	ptk - the current token
//	ptks - the state of the token machine
//	ppmemo - memory containing the MEMO structure
//
// Notes: 
// - According to the DTD:
//   - MEMO
//
// History: 
//	2/26/96	TimHa - Created
//
// ------------------------------------------------------------------------------ */
int RcParseMemos(MEMOFLAG mf, TOKEN *ptk, TOKENSTATE *ptks, MEMO **ppmemo)
{
	MEMO	*pmemo;
	MEMO	*pmemoNext;
	int		rcReturn;

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppmemo == NULL))
	{
		return INVALID_CALL;
	}

	/* what if we aren't at a MEMO */
	if (ptk->tkt != tktMEMO)
	{
		if (mf == mfONEORMORE)
			return OFC_ERROR;	/* oops, we needed at least one */
		else if (mf == mfZEROORMORE)
			return ALL_OK;		/* we are fine */
	}
	

	/* we know we have at least one memo to deal with here, so			*/
	/* loop through them and build up the list of memos					*/
	
	/* grab the first memo structure and assign it back up to the caller*/
	*ppmemo = (MEMO *)malloc(sizeof(MEMO));
	if (*ppmemo == NULL)
	{
		rcReturn = NO_MEMORY;
		goto _END;
	}
	memset(*ppmemo, 0, sizeof(MEMO));	/* zero it out */
	pmemo = *ppmemo;		/* use this as our current memo  */

	/* now loop until we have no more MEMOs to do */
	for(;;)
	{
		/* parse the MEMO out into the string */
		rcReturn = RcParseAnyElement(tktMEMO, ptk, ptks, &pmemo->szMEMO);
		if (rcReturn != ALL_OK)
			goto _END;

		/* check next token - if its a memo then grab another node */
		if (ptk->tkt == tktMEMO)
		{
			/* allocate a new MEMO structure */
			pmemoNext = (MEMO *)malloc(sizeof(MEMO));
			if (pmemoNext == NULL)
			{
				rcReturn = NO_MEMORY;
				goto _END;
			}
			memset(pmemoNext, 0, sizeof(MEMO));	/* zero it out */
			pmemo->pmemoNext = pmemoNext;		/* link to current one */
			pmemo = pmemoNext;					/* set the new one as our current */
		}
		else 
			break;	/* we are out of MEMOs, get out of the loop */
	} /* for(;;) */

_END:
	if (rcReturn != ALL_OK)
	{
		if (*ppmemo)
		{
			CleanupMemos(*ppmemo);
			*ppmemo = NULL;
		}
	} 
	return rcReturn;
} /* RcParseMemos */


/* ---------------------------------------------------------------------------------
// Function: RcGetBasicType
//
// Processes the basic element types. Data processing begins at the current token. 
// Therefore, RcReadToken should be called before this function.  For this reason, 
// no checking is done for the EndOfFile. None of the basic types allow for reading 
// past a '<' or '>', so RcReadToken is suitable for validation.  After processing
// the data, RcReadToken is called to advance the token. 
//
// Parameters: 
//	dt - the type of data to be read
//	ptk - the current token
//	ptks - the state of the token machine
//	ppchData - pointer where data is to be stored
//
// History: 
//	2/23/96	Derek Hazeur - Created
// ------------------------------------------------------------------------------- */
int RcGetBasicType(DATATYPE dt, 
				  TOKEN *ptk, TOKENSTATE *ptks, char **ppchData)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL) || (ppchData == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Verify that we are supposed to be reading data here */
	if (ptk->tkt != tktDATA)
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* Read the correct type of data according to the datatype supplied  */
	/*  by the caller.													 */
	switch (dt)
	{
		case dtNUMSTR:
			rcReturn = RcReadNUMSTR(ptk->pch,ppchData);
			if (rcReturn != ALL_OK)
				goto _END;
			break; 
		case dtIDSTR:
			rcReturn = RcReadIDSTR(ptk->pch,ppchData);
			if (rcReturn != ALL_OK)
				goto _END;
			break; 
		case dtDTSTR:
			rcReturn = RcReadDTSTR(ptk->pch,ppchData);
			if (rcReturn != ALL_OK)
				goto _END;
			break; 
		case dtCHARSTR: 
			rcReturn = RcReadCHARSTR(ptk->pch,ppchData);
			if (rcReturn != ALL_OK)
				goto _END;
			break; 
		case dtAMTSTR: 
			rcReturn = RcReadAMTSTR(ptk->pch,ppchData);
			if (rcReturn != ALL_OK)
				goto _END;
			break; 
		default:
		{
			rcReturn = INVALID_CALL; 
			goto _END;
		}
	}

	/* The OFC DTD states that all elements must contain at least 1 valid character */
	/* This should be understood, but let's check anyway							 */
	if (strlen(*ppchData) == 0)
	{
		rcReturn = OFC_ERROR; 
		goto _END;
	}

	/* Move on to next token */
	rcReturn = RcReadToken(ptk,ptks);
	if (rcReturn != ALL_OK)
		goto _END;

_END:

	return rcReturn; 

} /* end fGetElementType */

/* ---------------------------------------------------------------------------------
// Function: RcParseTag
//
// Parses a tag <TAG> or </TAG>. This function uses a global table to determine 
// whether or not the tag is required. If the tag is required and not found, and 
// error is returned.  If the tag is found, required or not, the token is advanced. 
//
// Parameters: 
//	tkt - the type of tag expected 
//	ptk - the current token
//	ptks - the state of the token machine
//
// History: 
//	2/23/96	Derek Hazeur - Created
// ------------------------------------------------------------------------------- */
int RcParseTag(TOKTYPE tkt, TOKEN *ptk, TOKENSTATE *ptks)
{
	int rcReturn;	/* function return code */

	/* Assure valid pointers before beginning */
	if ((ptk == NULL) || (ptks == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	if (ptk->tkt != tkt) 
	{
		if (rgtg[tkt].bRequired == bTRUE)  
		{
			/* It's the WRONG tag and it was NOT optional */
			rcReturn = OFC_ERROR;
			goto _END;
		}
	}
	else
	{
		/* It's the correct tag, move to next token */
		rcReturn = RcReadToken(ptk,ptks);
		if (rcReturn != ALL_OK)
			goto _END;
	}

	/* Set OK Return Code */
	rcReturn = ALL_OK; 

_END:

	return  rcReturn;

} /* end RcParseTag */


/* ---------------------------------------------------------------------------------
// Function: RcReadNUMSTR
// 
// This function reads a NUMSTR as described in the OFC DTD.  The DTD states that 
// a number string is made of "numeric characters that can be converted to a 
// positive integer value greater than 0" 
//
// Leading and trailing spaces are ignored, but there should be no data between 
// the end of the NUMSTR and the next '<'
//
// ------------------------------------------------------------------------------ */
int RcReadNUMSTR(char *pchBegin, char **pszData)
{
	/* Local Variables */
	char * pchEnd;		/* Pointer to end of the string, place to NULL-terminate */
	char * pchCurr;		/* Pointer to traverse the buffer */
	int rcReturn;		/* Return code */

	/* Assure valid pointers before we begin  */
	if ((pchBegin == NULL) || (pszData == NULL))
	{
		rcReturn = INVALID_CALL; 
		goto _END;
	}

	/* Assign moving pointer to beginning of buffer */
	pchCurr = pchBegin;

	/* Strip Leading White Space */
	pchCurr = pchStripWhiteSpace(pchCurr,NULL);

	/* Save the start position  */
	*pszData = pchCurr;

	/* NULL out terminate position */ 
	pchEnd = NULL; 

	/* Move pointer until a non-digit reached */
	while (isdigit(*pchCurr))
		pchCurr++;

	/* This should be the end of the string */
	pchEnd = pchCurr;

	/* Strip Trailing White Space */
	pchCurr = pchStripWhiteSpace(pchCurr,NULL);

	/* The next char is supposed to be a '<'  */
	if (*pchCurr != '<')
	{
		/* NULL Output Param and return NULL */
		*pszData = NULL; 
		rcReturn = OFC_ERROR; 
		goto _END;
	}
	else
	{
		/* OK...let's NULL terminate the string */
		*pchEnd = '\0';
	}

	/* Set OK return code */
	rcReturn = ALL_OK;

_END:

	return rcReturn; 

} /* end RcReadNUMSTR */

/* ---------------------------------------------------------------------------------
// Function: RcReadIDSTR
// 
// This function reads a IDSTR as described in the OFC DTD.  The DTD states that 
// an ID string "Must be composed of alphanumeric characters.  It may contain the 
// following Delimiters: ()-,.;:/\ as well as spaces." 
//
// Leading and trailing spaces are ignored.  
//
/// ------------------------------------------------------------------------------ */
int RcReadIDSTR(char *pchBegin, char **pszData)
{
	/* Local Variables */
	char * pchCurr;
	int	rcReturn; 
	char * pchEnd; 

	/* The following characters are valid. Also, alphanumeric and spaces */
	char szValid[] = "()-,.;:/\\#";  /* These characters are valid */

	/* Assure valid pointers before we begin  */
	if ((pchBegin == NULL) || (pszData == NULL))
	{
		rcReturn = INVALID_CALL; 
		goto _END;
	}

	/* Assign moving pointer to beginning of buffer */
	pchCurr = pchBegin;

	/* Strip Leading White Spaces  */
	pchCurr = pchStripWhiteSpace(pchCurr,NULL);

	/* Save the start position  */
	*pszData = pchCurr;

	/* NULL out terminate position */ 
	pchEnd = NULL; 

	/* Move pointer until a illegal character is reached */
	/* Legal chars = alpanumeric spaces ( ) - , . ; : / / */
	while (isalnum(*pchCurr) || strchr(szValid,*pchCurr) || (*pchCurr == ' '))
	{
		/* We are tracking spaces encountered and if no valid char follows		*/
		/* a stream of blanks, we will truncate them							*/
		/* If we find a blank, track it's position, but if we get a valid char	*/
		/* afterwards, clear it.												*/
		if ((*pchCurr == ' ') && (pchEnd == NULL))
			pchEnd = pchCurr;
		else if ((*pchCurr != ' ') && (pchEnd != NULL))
			pchEnd = NULL; 

		pchCurr++;
	}

	/* If we dont have an end pointer from the blanks, truncate where we are */
	if (pchEnd == NULL)
	{
		/* This should be the end of the string */
		pchEnd = pchCurr;
	}

	/* Strip Trailing White Space */
	pchCurr = pchStripWhiteSpace(pchCurr,NULL);

	/* The next char is supposed to be a '<'  */
	if (*pchCurr != '<')
	{
		/* NULL Output Param and return NULL */
		*pszData = NULL; 
		rcReturn = OFC_ERROR; 
		goto _END;
	}
	else
	{
		/* OK...let's NULL terminate the string */
		*pchEnd = '\0';
	}

	/* Set OK return code */
	rcReturn = ALL_OK;

_END:

	return rcReturn; 

} /* end RcReadIDSTR */

/* ---------------------------------------------------------------------------------
// Function: RcReadCHARSTR
// 
// This function reads a CHARSTR as described in the OFC DTD.  The DTD states that 
// a character stream "will be Tag delimitted. If the stream encounters a CR-LF
// prior to an SGML start/end tag, it will be converted to a space and the 
// adjoining lines will be concatenated. This process will continue until the next
// start/end tag is encountered."
//
// Leading spaces will be perserved, but trailing spaces will be ignored
// -------------------------------------------------------------------------------*/
int RcReadCHARSTR(char *pchBegin, char **pszData)
{
	/* Local Variables */
	char * pchCurr;
	int	rcReturn; 
	BOOL bShift;
	char *pchShiftPos = NULL;

	/* Assure valid pointers before we begin  */
	if ((pchBegin == NULL) || (pszData == NULL))
	{
		rcReturn = INVALID_CALL; 
		goto _END;
	}

	/* Assign moving pointer to beginning of buffer */
	pchCurr = pchBegin;

	/* Save the start position  */
	*pszData = pchCurr;

	/* Move pointer until a the beginning of a tag '<' is reached */
	bShift = bFALSE;
	while (*pchCurr != '<') 
	{	
		/* Check to see if we have a CR-LF */
		if ((*pchCurr == '\r') && (*(pchCurr+1) == '\n'))
		{
			/* We have a CR-LF */
			if (bShift == bFALSE)
			{
				/* We have not been shifting yet, so let's start.  */
				bShift = bTRUE;
				pchShiftPos = pchCurr;
			}

			/* Copy a space to the shift position and move curr pass the /n */
			*pchShiftPos = ' ';
			pchShiftPos++; 
			pchCurr += 2;
		}
		else
		{
			if (bShift == bTRUE)
			{
				/* We are shifting so copy the current pointer to the shift pos */
				*pchShiftPos = *pchCurr;
				pchShiftPos++;
				pchCurr++;
			}
			else
			{
				/* No shifting..just increment the pointer */
				pchCurr++;
			}
		}
	}

	/* The next char is supposed to be a '<'  */
	if (*pchCurr != '<')
	{
		/* NULL Output Param and return NULL */
		*pszData = NULL; 
		rcReturn = OFC_ERROR; 
		goto _END;
	}

	/* NULL terminate the string replacing the '\0'					 */
	/* We use pchShiftPos because this is the string that received	 */
	/* all the shifted characters									 */
	if (bShift == bTRUE)
	{
		*pchShiftPos = '\0';
		pchCurr = pchShiftPos;
	}
	else
		*pchCurr = '\0';

	/* Walk backwards strip trailing whitespace by changing to NULLs */
	pchCurr--;
	while (isspace(*pchCurr))
	{
		*pchCurr = '\0';
		pchCurr--;
	}

	/* Set OK return code */
	rcReturn = ALL_OK;
	
_END:

	return rcReturn; 

} /* end RcReadCHARSTR */

/* ---------------------------------------------------------------------------------
// Function: RcReadAMTSTR
// 
// This function reads a AMTSTR as described in the OFC DTD.  The DTD states that 
// an Amount string "must be made up of numeric characters plus the following 
// delimiters for indicating the decimal place: . , If the amount is negative 
// (a debit with respect to the user's account), then the first character must be 
// the following: -  All other characters are illegal."
//
// Leading and trailing spaces are ignored.  
// ------------------------------------------------------------------------------- */
int RcReadAMTSTR(char *pchBegin, char **pszData)
{
	/* Local Variables */
	char * pchCurr;
	int rcReturn; 
	char * pchEnd;

	/* Assure valid pointers before we begin  */
	if ((pchBegin == NULL) || (pszData == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Assign moving pointer to beginning of buffer */
	pchCurr = pchBegin;

	/* Strip Leading White Spaces  */
	pchCurr = pchStripWhiteSpace(pchCurr,NULL);

	/* Save the start position  */
	*pszData = pchCurr;

	/* A '-' is legal as the first character to denote a negative amount	 */
	/* Only allowed as the first character									 */
	if (*pchCurr == '-')
		pchCurr++;

	/* Move pointer until an illegal char reached						 */
	/* Legal chars are digits and commas (,) and a decimal point (.)	 */
	while (isdigit(*pchCurr) || (*pchCurr == '.') || (*pchCurr == ','))
	{
		/* If we have a comma or a period there should be whitespace or  */
		/* a tag '<' three chars ahead									 */
		if ((*pchCurr == '.') || (*pchCurr == ',')) 
		{
			/* Make sure we have a valid pointer down there */
			if (pchCurr+3)
			{
				if (!isspace(*(pchCurr+3)) && (*(pchCurr+3) != '<')) 
				{
					/* We have a decimal point in a weird place, should be only  */
					/* two places after the decimal point						 */
					rcReturn = OFC_ERROR; 
					goto _END;
				}
			}
			else
			{
				/* There's nothing out there */
				rcReturn = OFC_ERROR; 
				goto _END;
			}
		}

		pchCurr++;
	}

	/* This should be the end of the string */
	pchEnd = pchCurr;

	/* Strip Trailing White Spaces  */
	pchCurr = pchStripWhiteSpace(pchCurr,NULL);

	/* The next char is supposed to be a '<' which is either the	 */
	/* beginning of a tag (could be a start or an end tag)			 */
	if (*pchCurr != '<')
	{
		rcReturn = OFC_ERROR; 
		goto _END;
	}

	/* OK...let's NULL terminate the string */
	*pchEnd = '\0';

	/* Set OK return code */
	rcReturn = ALL_OK;

_END: 

	return rcReturn; 

} /* end RcReadAMTSTR */

/* ---------------------------------------------------------------------------------
// Function: RcReadDTSTR
// 
// This function reads a Date/Time string described in the OFC DTD.  The DTD states that 
// an Date/Time string 
//
// ------------------------------------------------------------------------------- */
int RcReadDTSTR(char *pchBegin, char **pszData)
{
	/* Local Variables */
	char * pchCurr;
	int rcReturn; 
	int nCount; 
	char * pchEnd;

	/* Assure valid pointers before we begin  */
	if ((pchBegin == NULL) || (pszData == NULL))
	{
		rcReturn = INVALID_CALL;
		goto _END;
	}

	/* Assign moving pointer to beginning of buffer */
	pchCurr = pchBegin;

	/* Strip Leading White Spaces  */
	pchCurr = pchStripWhiteSpace(pchCurr,NULL);

	/* Save the start position  */
	*pszData = pchCurr;

	/* Move pointer until an illegal char reached						 */
	/* Legal chars are digits and commas (,) and a decimal point (.)	 */
	nCount = 0;
	while (isdigit(*pchCurr))
	{
		/* Count number of digits */
		nCount++; 
		pchCurr++;
	}

	/* Make sure we have either 8 or 14 digits */
	if ((nCount != 8) && (nCount != 14))
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* This should be the end of the string */
	pchEnd = pchCurr;

	/* Strip Trailing White Spaces  */
	pchCurr = pchStripWhiteSpace(pchCurr,NULL);

	/* The next char is supposed to be a '<' which is either the	 */
	/* beginning of a tag (could be a start or an end tag)			 */
	if (*pchCurr != '<')
	{
		rcReturn = OFC_ERROR;
		goto _END;
	}

	/* OK...let's NULL terminate the string */
	*pchEnd = '\0';

	/* Set OK return code */
	rcReturn = ALL_OK;

_END:

	return rcReturn; 

} /* end RcReadDTSTR */

/* ------------------------------------------------------------------------------- */

