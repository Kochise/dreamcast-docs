/* ---------------------------------------------------------------------------------
// Copyright(c) 1991-1996 Microsoft Corporation.  All rights reserved.
// ---------------------------------------------------------------------------------
// File: PARSE.H
//
// Header file for OFC Parse
//
// 02/26/95	TimHa - Created
// -------------------------------------------------------------------------------*/


/* ---------------------------------------------------------------------------------
//							Function Prototypes
// -------------------------------------------------------------------------------*/
/* in TOKEN.C */
char * pchReadToDelimiter(char *pchBegin,int *pcbToken);
TOKTYPE tktTypeFromTag(char *pchBegin, int cbToken);
char * pchStripWhiteSpace(char *pchBegin, int *pcbStripped);
int RcInitializeToken(TOKEN *ptoken, TOKENSTATE *ptks, void *pvRequest, int cbAvailable);
int RcReadToken(TOKEN* ptoken, TOKENSTATE *ptks);
void InitHash();

/* in PELEMENT.C */
int RcReadNUMSTR(char *pchBegin, char **pszData);
int RcReadIDSTR(char *pchBegin, char **pszData);
int RcReadCHARSTR(char *pchBegin, char **pszData);
int RcReadDTSTR(char *pchBegin, char **pszData);
int RcReadAMTSTR(char *pchBegin, char **pszData);
int RcParseTag(TOKTYPE tkt, TOKEN *ptk, TOKENSTATE *ptks);
int RcGetBasicType(DATATYPE dt, 
				  TOKEN *ptk, TOKENSTATE *ptks, char **ppchData);
int RcParseAnyElement(TOKTYPE tkt, TOKEN *ptk, TOKENSTATE *ptks, char **ppchData);
int RcParseMemos(MEMOFLAG mf, TOKEN *ptk, TOKENSTATE *ptks, MEMO **ppmemo);

/* in PARSE.C */
int RcParseOFCDOC(OFCDOCTYPE odt, void *pvRequest, int cbRequest, OFCDOC **ppofcdoc);
int RcParseSONRQ(TOKEN *ptk, TOKENSTATE *ptks, SONRQ **sonrqData);
int RcParseSONRS(TOKEN *ptk, TOKENSTATE *ptks, SONRS **ppsonrs);
int RcParseMAINTRQ(TOKEN *ptk, TOKENSTATE *ptks, void **ppvData, OFCTYPE * ofctype);
int RcParseMAINTRS(TOKEN *ptk, TOKENSTATE *ptks, void **ppvData, OFCTYPE * ofctype);
int RcParseACCTRQ(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szACTION,
				 ACCTRQ **ppacctrq);
int RcParseACCTRS(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szSTATUS,
				 ACCTRS **ppacctrs);
int RcParseACCTFROM(TOKEN *ptk, TOKENSTATE *ptks, void **ppvData);
int RcParseACCOUNT(TOKEN *ptk, TOKENSTATE *ptks, ACCOUNT **ppacct);
int RcParseSERVRQST(TOKEN *ptk, TOKENSTATE *ptks, SERVRQST **ppsrqst);
int RcParseSERVAUTH(TOKEN *ptk, TOKENSTATE *ptks, SERVAUTH **ppauth);
int RcParseTRNRQ(TOKEN *ptk, TOKENSTATE *ptks, void **ppvData, OFCTYPE * ofctype);
int RcParseTRNRS(TOKEN *ptk, TOKENSTATE *ptks, void **ppvData, OFCTYPE * ofctype);

int RcParseACCTTO(TOKEN *ptk, TOKENSTATE *ptks, void **ppvData);
int RcParseMAILRQ(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szACTION, MAILRQ **ppmailrq);
int RcParseMAILRS(TOKEN *ptk, TOKENSTATE *ptks,  char * szCLTID, char * szSTATUS, 
				 MAILRS **ppmailrs);

int RcParseACCTSTMT(TOKEN *ptk, TOKENSTATE *ptks, ACCTSTMT **ppacctstmt);


#ifdef _TESTAPP
/* For the test application we need to be able to keep the state for an error */
/* so we can parse a file and re-build it properly.  To handle the error      */
/* condition we need to pass in an ofctype so we know to build a MAINRS or a  */
/* TRNRS around the error.													  */
int RcParseERRORRS(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szSTATUS,
				 char *szERROR,ERRORRS **pperrorrs,OFCTYPE ofctype );
#else
int RcParseERRORRS(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szSTATUS,
				 char *szERROR,ERRORRS **pperrorrs);
#endif

/* in PBANKING.C */
int RcParseGENTRN(TOKEN *ptk, TOKENSTATE *ptks, GENTRN **ppgentrn);
int RcParseSTMTTRN(TOKEN *ptk, TOKENSTATE *ptks, void **ppvData);
int RcParseSTMTRQ(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szACTION, STMTRQ **ppstmtrq);
int RcParseSTMTRS(TOKEN *ptk, TOKENSTATE *ptks,  char * szCLTID, char * szSTATUS, 
				 STMTRS **ppstmtrs);
int RcParseINTERRQ(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szACTION, INTERRQ **ppinterrq);
int RcParseINTERRS(TOKEN *ptk, TOKENSTATE *ptks,  char * szCLTID, char * szSTATUS, 
				 INTERRS **ppinterrs);
int RcParseINTRARQ(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char * szAction,  
				  INTRARQ **ppintrarq);
int RcParseINTRARS(TOKEN *ptk, TOKENSTATE *ptks,  char * szCLTID, char * szSTATUS, 
				  INTRARS **ppintrars);

/* in PPAYMENT.C */
int RcParseENTITY(TOKEN *ptk, TOKENSTATE *ptks, ENTITY **ppentity);
int RcParsePAYEE(TOKEN *ptk, TOKENSTATE *ptks, void **ppvData);
int RcParsePAYEERQ(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szACTION, PAYEERQ **pppayeerq);
int RcParsePAYEERS(TOKEN *ptk, TOKENSTATE *ptks,  char * szCLTID, char * szSTATUS,
				 PAYEERS **pppayeers);
int RcParsePAYMTRQ(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szACTION, PAYMTRQ **pppaymtrq);
int RcParsePAYMTRS(TOKEN *ptk, TOKENSTATE *ptks,  char * szCLTID, char * szSTATUS, 
				 PAYMTRS **pppaymtrs);
int RcParsePAYIQRQ(TOKEN *ptk, TOKENSTATE *ptks, char * szCLTID, char *szACTION, PAYIQRQ **pppayiqrq);
int RcParsePAYIQRS(TOKEN *ptk, TOKENSTATE *ptks,  char * szCLTID, char * szSTATUS, 
				 PAYIQRS **pppayiqrs);


/* in PCLEAN.C */
void ParseCleanup(POFCDOC *ppofcdoc);

void CleanupACCTRQ(ACCTRQ *pacctrq);
void CleanupACCTRS(ACCTRS *pacctrs);
void CleanupPAYEERQ(PAYEERQ *ppayeerq);
void CleanupPAYEERS(PAYEERS *ppayeers);
void CleanupMAILRQ(MAILRQ *pmailrq);
void CleanupMAILRS(MAILRS *pmailrs);
void CleanupSTMTRQ(STMTRQ *pstmtrq);
void CleanupSTMTRS(STMTRS *pstmtrs);
void CleanupINTRARQ(INTRARQ *pintrarq);
void CleanupINTERRQ(INTERRQ *pinterrq);
void CleanupPAYMTRQ(PAYMTRQ *ppaymtrq);
void CleanupPAYIQRQ(PAYIQRQ *ppayiqrq);
void CleanupPAYIQRS(PAYIQRS *ppayiqrs);
void CleanupACCTSTMT(ACCTSTMT *ppacctstmt);

void CleanupMemos(MEMO *pmemo);
void CleanupStmts(GENTRN *pgtrn);
