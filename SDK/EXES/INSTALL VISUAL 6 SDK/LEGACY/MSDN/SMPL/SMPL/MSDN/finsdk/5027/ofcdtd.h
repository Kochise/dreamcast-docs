#ifndef OFCDTD_H
#define OFCDTD_H
/*----------------------------------------------------------------------
	Copyright(c) 1991 - 1996 Microsoft Corporation.  All rights reserved.
	file: ofcdtd.h
	owner: timjo
	co-owner: derekha
	purpose: OFC structures
  ----------------------------------------------------------------------*/

/*----------------------------------------------------------------------
						Function Return Codes
  ----------------------------------------------------------------------*/

#define ALL_OK			1
#define OFC_ERROR		-100
#define NO_MEMORY		-101	/* Memory Allocation failed			*/
#define INVALID_CALL	-102	/* A function was called incorrectly*/
#define INVALID_DTD_VER	-103	/* DTD version != OFC_DTDVERSION

/*----------------------------------------------------------------------
							Defines
  ----------------------------------------------------------------------*/
#define OFC_DTDVERSION	2
#define OFC_CPAGE		1252

/*----------------------------------------------------------------------
						OFC Transaction Types
  ----------------------------------------------------------------------*/

typedef enum  /* Hungarian: ofctype */
{
	ofctypeMin,
	ofctypeNil,			/* unknown type */	
	ofctypeACCTSTMT,	/* OFC file import */
	ofctypeSONRQ,		/* signon request */
	ofctypeSONRS,		/* signon response */
	ofctypeACCTRQ,		/* account maintenance request */
	ofctypeACCTRS,		/* account maintenance response */	
	ofctypePAYEERQ, 	/* payee maintenance request */	
	ofctypePAYEERS, 	/* payee maintenance response */	
	ofctypeMAILRQ,		/* mail request */	
	ofctypeMAILRS,		/* mail response */	
	ofctypeSTMTRQ,		/* bank statement request */	
	ofctypeSTMTRS,		/* bank statement response */	
	ofctypeINTRARQ, 	/* intrabank transfer request */	
	ofctypeINTRARS, 	/* intrabank transfer response */	
	ofctypeINTERRQ, 	/* interbank transfer request */	
	ofctypeINTERRS, 	/* interbank transfer response */	
	ofctypePAYMTRQ, 	/* bill payment request */	
	ofctypePAYMTRS, 	/* bill payment response */	
	ofctypePAYIQRQ, 	/* bill payment inquiry request */	
	ofctypePAYIQRS, 	/* bill payment inquiry response */
	ofctypeERRORRS,		/* general error response */	
	ofctypeMax	
} OFCTYPE;

/*----------------------------------------------------------------------
						OFC Transaction Linked List 
  ----------------------------------------------------------------------*/

typedef struct _OFCTRN		/* Hungarian: ofctrn */ 
{
	OFCTYPE				ofctype;
	void *				pvTrn;
	struct _OFCTRN *	pofctrnNext;
} OFCTRN;
typedef OFCTRN * POFCTRN;	/* Hungarian: pofctrn */

typedef struct				/* Hungarian: ofcdoc */ 
{
	char *		szDTD;
	char *		szCPAGE;
	OFCTRN *	pofctrn;
} OFCDOC;
typedef OFCDOC * POFCDOC;	/* Hungarian: pofcdoc */

/*----------------------------------------------------------------------
						OFC Repeated Element Structures 
  ----------------------------------------------------------------------*/

typedef struct _MEMO	/* Hungarian: memo */ 
{
	char *			szMEMO;
	struct _MEMO *	pmemoNext;	/* may be NULL */
} MEMO;

/*----------------------------------------------------------------------
						OFC Aggregate Structures 
  ----------------------------------------------------------------------*/

typedef struct		/* Hungarian: acct */ 
{
	char *	szBANKID;
	char *	szBRANCHID;		/* may be NULL */
	char *	szACCTID;
	char *	szACCTTYPE;
} ACCOUNT;

typedef struct		/* Hungarian: ent */ 
{
	char *	szNAME1;
	char *	szNAME2;		/* may be NULL */
	char *	szNAME3;		/* may be NULL */
	char *	szADDRESS1;
	char *	szADDRESS2;		/* may be NULL */
	char *	szADDRESS3;		/* may be NULL */
	char *	szCITY;
	char *	szSTATE;
	char *	szPOSTALID;
	char *	szPHONE1;
	char *	szPHONE2;		/* may be NULL */
} ENTITY;

typedef struct		/* Hungarian: srqst */ 
{
	char *	szSERVICE;
	char *	szACTION;
} SERVRQST;

typedef struct		/* Hungarian: sauth */ 
{
	char *	szSERVICE;
	char *	szSTATUS;
} SERVAUTH ;

typedef struct _GENTRN	/* Hungarian: gtrn */ 
{
	char *				szTRNTYPE;
	char *				szDTPOSTED;
	char *				szTRNAMT;
	char *				szFITID;		/* may be NULL */
	char *				szCLTID;		/* may be NULL */
	char *				szSRVRTID;		/* may be NULL */
	char *				szCHKNUM;		/* may be NULL */
	char *				szSIC;			/* may be NULL */
	char *				szPAYEEID;		/* may be NULL */
	ENTITY *			pentPAYEE;		/* may be NULL */
	char *				szNAME;			/* may be NULL */
	ACCOUNT *			pacctACCTTO; 	/* may be NULL */
	MEMO *				pmemoMEMO;		/* may be NULL */
	struct _GENTRN *	pgtrnNext;		/* may be NULL */
} GENTRN;

/*----------------------------------------------------------------------
						OFC Transaction Structures 
  ----------------------------------------------------------------------*/

typedef struct		/* Hungarian: acctstmt */ 
{
	ACCOUNT *	pacctACCTFROM;
	char *		szDTSTART;
	char *		szDTEND;
	char *		szLEDGER;
	GENTRN *	pgtrnSTMTTRN;	/* may be NULL */
} ACCTSTMT;

typedef struct		/* Hungarian: sonrq */ 
{
	char *		szSESSKEY;
	char *		szDTCLIENT;
	char *		szUSERID;
	char *		szUSERPASS;
	char *		szNEWPASS;		/* may be NULL */
} SONRQ;

typedef struct		/* Hungarian: sonrs */ 
{
	char *		szSTATUS;
	char *		szDTSERVER;
	char *		szERROR;		/* may be NULL */
	char *		szSESSKEY;
	char *		szSERVICE1;		/* may be NULL */
	char *		szSERVICE2;		/* may be NULL */
	char *		szDAYSREQD;		/* may be NULL */
	char *		szDAYSWITH;		/* may be NULL */
} SONRS;

typedef struct		/* Hungarian: errorrs */ 
{
	OFCTYPE		ofctype;		/* type of request transaction in error */
	char *		szCLTID;
	char *		szSTATUS;
	char *		szERROR;		/* may be NULL */
} ERRORRS;

typedef struct		/* Hungarian: acctrq */ 
{
	char *		szCLTID;
	char *		szACTION;
	ACCOUNT *	pacctACCTFROM;
	SERVRQST *	psrqstSERVRQST1;
	SERVRQST *	psrqstSERVRQST2;/* may be NULL */
} ACCTRQ;

typedef struct		/* Hungarian: acctrs */ 
{
	char *		szCLTID;
	char *		szSTATUS;
	SERVAUTH *	psauthSERVAUTH1;
	SERVAUTH *	psauthSERVAUTH2;/* may be NULL */
} ACCTRS;

typedef struct		/* Hungarian: payeerq */ 
{
	char *		szCLTID;
	char *		szACTION;
	char *		szPAYEEID;		/* may be NULL */
	ENTITY *	pentPAYEE;
	char *		szPAYACCT;
} PAYEERQ;

typedef struct		/* Hungarian: payeers */ 
{
	char *		szCLTID;
	char *		szSTATUS;
	char *		szPAYEEID;	
	ENTITY *	pentPAYEE;		/* may be NULL */
	char *		szDAYSREQD;	
	char *		szDAYSWITH;
} PAYEERS;

typedef struct		/* Hungarian: mailrq */ 
{
	char *		szCLTID;
	char *		szACTION;
	char *		szSERVICE;
	ACCOUNT *	pacctACCTFROM; 	/* may be NULL */
	MEMO *		pmemoMEMO;
} MAILRQ;

typedef struct		/* Hungarian: mailrs */ 
{
	char *		szCLTID;
	char *		szSTATUS;
	MEMO *		pmemoMEMO;		/* may be NULL */
} MAILRS;

typedef struct		/* Hungarian: stmtrq */ 
{
	char *		szCLTID;
	char *		szACTION;
	ACCOUNT *	pacctACCTFROM;
	char *		szDTSTART;		/* may be NULL */
	char *		szDTEND;	 	/* may be NULL */
} STMTRQ;

typedef struct		/* Hungarian: stmtrs */ 
{
	char *		szCLTID;
	char *		szSTATUS;
	char *		szDTSTART;	
	char *		szDTEND;	
	char *		szLEDGER;	
	GENTRN *	pgtrnSTMTTRN;	/* may be NULL */
} STMTRS;

typedef struct		/* Hungarian: intrarq */ 
{
	char *		szCLTID;
	char *		szACTION;
	ACCOUNT *	pacctACCTFROM;
	char *		szTRNAMT;
	ACCOUNT *	pacctACCTTO;
	MEMO *		pmemoMEMO;		/* may be NULL */
} INTRARQ;

typedef struct		/* Hungarian: intrars */ 
{
	char *		szCLTID;
	char *		szSTATUS;
	char *		szSRVRTID;
	char *		szDTPOSTED;		/* may be NULL */
} INTRARS;

typedef struct		/* Hungarian: interrq */ 
{
	char *		szCLTID;
	char *		szACTION;
	ACCOUNT *	pacctACCTFROM;
	char *		szTRNAMT;
	char *		szPAYEEID; 		/* may be NULL if pacctACCTTO is NULL */
	ACCOUNT *	pacctACCTTO;	/* may be NULL if szPAYEEID is NULL */
	char *		szNAME; 		
	char *		szPAYACCT; 		
	char *		szDTDUE;
	char *		szSRVRTID; 		/* may be NULL */
	MEMO *		pmemoMEMO; 		/* may be NULL */
} INTERRQ;

typedef struct		/* Hungarian: interrs */ 
{
	char *		szCLTID;
	char *		szSTATUS;
	char *		szSRVRTID;
	char *		szDTPOSTED; 	/* may be NULL */
	char *		szCHKNUM; 		/* may be NULL */
} INTERRS;

typedef struct		/* Hungarian: paymtrq */ 
{
	char *		szCLTID;
	char *		szACTION;
	ACCOUNT *	pacctACCTFROM;
	char *		szTRNAMT;
	char *		szPAYEEID;		/* may be NULL */
	ENTITY *	pentPAYEE;		/* may be NULL */
	char *		szPAYACCT;		
	char *		szDTDUE;
	char *		szSRVRTID;		/* may be NULL */
	MEMO *		pmemoMEMO;		/* may be NULL */
} PAYMTRQ;

typedef struct		/* Hungarian: paymtrs */ 
{
	char *		szCLTID;
	char *		szSTATUS;
	char *		szSRVRTID;
	char *		szPAYEEID;		/* may be NULL */
} PAYMTRS;

typedef struct		/* Hungarian: payiqrq */ 
{
	char *		szCLTID;
	char *		szACTION;
	char *		szSRVRTID;
	MEMO *		pmemoMEMO;
} PAYIQRQ;

typedef struct		/* Hungarian: payiqrs */ 
{
	char *		szCLTID;
	char *		szSTATUS;
	char *		szSRVRTID;
	MEMO *		pmemoMEMO;		/* may be NULL */
} PAYIQRS;

#endif