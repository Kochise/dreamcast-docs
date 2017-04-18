/* ---------------------------------------------------------------------------------
// Copyright(c) 1991-1996 Microsoft Corporation.  All rights reserved.
// ---------------------------------------------------------------------------------
// File: PBTYPES.H
//
// Header file for OFC Parse & Build Common definitions
//
// 02/26/95	TimHa - Created
// -------------------------------------------------------------------------------*/


/* ---------------------------------------------------------------------------------
//							Type Definitions and Data Structures
// -------------------------------------------------------------------------------*/
typedef enum  /* Hungarian: b */
{
	bFALSE = 0,
	bTRUE = 1	

} BOOL; 


typedef enum  /* Hungarian: tk */
{
	tktOFC = 0,			/* 0 */
	tktEndOFC,			/* 1 */
	tktDTD,				/* 2 */ 
	tktEndDTD,			/* 3 */
	tktCPAGE,			/* 4 */
	tktEndCPAGE,		/* 5 */ 
	tktSONRQ,			/* 6 */
	tktEndSONRQ,		/* 7 */
	tktSESSKEY,			/* 8 */
	tktEndSESSKEY,		/* 9 */
	tktDTCLIENT,		/* 10 */
	tktEndDTCLIENT,		/* 11 */
	tktUSERID,			/* 12 */
	tktEndUSERID,		/* 13 */
	tktUSERPASS,		/* 14 */
	tktEndUSERPASS,		/* 15 */
	tktNEWPASS,			/* 16 */
	tktEndNEWPASS,		/* 17 */
	tktSONRS,			/* 18 */
	tktEndSONRS,		/* 19 */
	tktSTATUS,			/* 20 */
	tktEndSTATUS,		/* 21 */
	tktDTSERVER,		/* 22 */
	tktEndDTSERVER,		/* 23 */
	tktERROR,			/* 24 */
	tktEndERROR,		/* 25 */
	tktSERVICE,			/* 26 */
	tktEndSERVICE,		/* 27 */
	tktDAYSREQD,		/* 28 */
	tktEndDAYSREQD,		/* 29 */
	tktDAYSWITH,		/* 30 */
	tktEndDAYSWITH,		/* 31 */
	tktMAINTRQ,			/* 32 */
	tktEndMAINTRQ,		/* 33 */
	tktACCTRQ,			/* 34 */
	tktEndACCTRQ,		/* 35 */
	tktPAYEE,			/* 36 */
	tktEndPAYEE,		/* 37 */
	tktMAILRQ,			/* 38 */
	tktEndMAILRQ,		/* 39 */
	tktCLTID,			/* 40 */
	tktEndCLTID,		/* 41 */
	tktACTION,			/* 42 */
	tktEndACTION,		/* 43 */
	tktACCOUNT,			/* 44 */
	tktEndACCOUNT,		/* 45 */
	tktBANKID,			/* 46 */
	tktEndBANKID,		/* 47 */
	tktBRANCHID,		/* 48 */
	tktEndBRANCHID,		/* 49 */
	tktACCTID,			/* 50 */
	tktEndACCTID,		/* 51 */
	tktACCTTYPE,		/* 52 */
	tktEndACCTTYPE,		/* 53 */
	tktACCTFROM,		/* 54 */
	tktEndACCTFROM,		/* 55 */
	tktSERVRQST,		/* 56 */
	tktEndSERVRQST,		/* 57 */
	tktMAINTRS,			/* 58 */
	tktEndMAINTRS,		/* 59 */
	tktACCTRS,			/* 60 */
	tktEndACCTRS,		/* 61 */
	tktSERVAUTH,		/* 62 */
	tktEndSERVAUTH,		/* 63 */
	tktTRNRQ,			/* 64 */
	tktEndTRNRQ,		/* 65 */
	tktTRNRS,			/* 66 */
	tktEndTRNRS,		/* 67 */
	tktINTRARQ,			/* 68 */
	tktEndINTRARQ,		/* 69 */
	tktINTRARS,			/* 70 */
	tktEndINTRARS,		/* 71 */
	tktTRNAMT,			/* 72 */
	tktEndTRNAMT,		/* 73 */
	tktACCTTO,			/* 74 */
	tktEndACCTTO,		/* 75 */
	tktMEMO,			/* 76 */
	tktEndMEMO,			/* 77 */
	tktSRVRTID,			/* 78 */
	tktEndSRVRTID,		/* 79 */
	tktDTPOSTED,		/* 80 */
	tktEndDTPOSTED,		/* 81 */
	tktMAILRS,			/* 82 */
	tktEndMAILRS,		/* 83 */
	tktACCTSTMT,		/* 84 */
	tktEndACCTSTMT,		/* 85 */
	tktENTITY,			/* 86 */
	tktEndENTITY,		/* 87 */
	tktPAYEERS,			/* 88 */
	tktEndPAYEERS,		/* 89 */
	tktPAYEERQ,			/* 90 */
	tktEndPAYEERQ,		/* 91 */
	tktPAYEEID,			/* 92 */
	tktEndPAYEEID,		/* 93 */
	tktPAYACCT,			/* 94 */
	tktEndPAYACCT,		/* 95 */
	tktNAME,			/* 96 */
	tktEndNAME,			/* 97 */
	tktADDRESS,			/* 98 */
	tktEndADDRESS,		/* 99 */
	tktCITY,			/* 100 */
	tktEndCITY,			/* 101 */
	tktSTATE,			/* 102 */
	tktEndSTATE,		/* 103 */
	tktPOSTALID,		/* 104 */
	tktEndPOSTALID,		/* 105 */
	tktPHONE,			/* 106 */
	tktEndPHONE,		/* 107 */
	tktSTMTRQ,			/* 108 */
	tktEndSTMTRQ,		/* 109 */
	tktSTMTRS,			/* 110 */
	tktEndSTMTRS,		/* 111 */
	tktDTSTART,			/* 112 */
	tktEndDTSTART,		/* 113 */
	tktDTEND,			/* 114 */
	tktEndDTEND,		/* 115 */
	tktLEDGER,			/* 116 */
	tktEndLEDGER,		/* 117 */
	tktSTMTTRN,			/* 118 */
	tktEndSTMTTRN,		/* 119 */
	tktGENTRN,			/* 120 */
	tktEndGENTRN,		/* 121 */
	tktTRNTYPE,			/* 122 */
	tktEndTRNTYPE,		/* 123 */
	tktFITID,			/* 124 */
	tktEndFITID,		/* 125 */
	tktCHKNUM,			/* 126 */
	tktEndCHKNUM,		/* 127 */
	tktSIC,				/* 128 */
	tktEndSIC,			/* 129 */
	tktPAYMTRQ,			/* 130 */
	tktEndPAYMTRQ,		/* 131 */
	tktPAYMTRS,			/* 132 */
	tktEndPAYMTRS,		/* 133 */
	tktDTDUE,			/* 134 */
	tktEndDTDUE,		/* 135 */
	tktPAYIQRQ,			/* 136 */
	tktEndPAYIQRQ,		/* 137 */
	tktPAYIQRS,			/* 138 */
	tktEndPAYIQRS,		/* 139 */
	tktINTERRQ,			/* 140 */
	tktEndINTERRQ,		/* 141 */
	tktINTERRS,			/* 142 */
	tktEndINTERRS,		/* 143 */


	tktUnknown,			/* Token type undefined */
	tktDATA,			/* Token is Data */
	tktEOF				/* No token remaining */
	
} TOKTYPE;

typedef enum  /* Hungarian: dt */
{
	dtIDSTR,				/* IDSTR */
	dtNUMSTR,				/* NUMSTR */
	dtCHARSTR,				/* CHARSTR */
	dtDTSTR,				/* DTSTR */
	dtAMTSTR,				/* AMTSTR */

	dtNONE					/* Not a Element type, so no datatype */

} DATATYPE;

typedef enum /* Hungarian: mf */
{
	mfZEROORMORE,			/* zero or more memos allowed */
	mfONEORMORE,			/* one of more memos allowed */
} MEMOFLAG;

typedef enum {		/* Hungarian: odt */
	odtREQUEST,
	odtRESPONSE,
	odtSTATEMENT
} OFCDOCTYPE;

typedef struct /* Hungarian: tg */ 
{
	TOKTYPE tagtype;			/* Type of the tag */
	BOOL bRequired;			/* Is the tag required */
	DATATYPE dt;				/* Type of Data */
	char *szTag;					/* The Tag string - includes <TAG> & maybe \r\n */
	int	 cbTag;						/* The length of the whole tag */
} TAGTABLENTRY;

typedef struct /* Hungarian: tk */
{
	char *pch;				/* Start of token */
	TOKTYPE tkt;		/* Type of the current token */
	int	cb;					/* Length of current token */
} TOKEN;

typedef struct  /* Hungarian: tks */
{
	int	cbAvailable;		/* Total number of bytes in buffer */
	int	cbDone;				/* Number of bytes already read */
	char *pchNext;			/* Start of next token */

} TOKENSTATE;

/* initialize the hash table */
void InitHash();	

/* ---------------------------------------------------------------------------------
//							Global Table of OCF Tags
// -------------------------------------------------------------------------------*/
extern TAGTABLENTRY rgtg[];
