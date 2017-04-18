/*
 -  X P T X T M S G . H
 -
 *  Purpose:
 *      Support for the textized TNEF encapsulated message transport.
 *      
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */
 
/* Stuff to support the textized message formating */

enum 
{
    tagMessage, 
    tagFrom,
    tagRepresenting,
    tagReplyTo,
    tagDate,
    tagTo,
    tagCc,
    tagBcc,
    tagSubject,
    tagPrioUrgent,
    tagPrioNormal,
    tagPrioLow,
    tagContents,
    tagTextItem,
    tagFileItem,
    NUM_TAGS        
};


#define MAX_TAG_LEN         32
#define MAX_TXTMSG_PROPS    17
#define MAX_STRM_BUF        256
#define MAX_LINE            256

/* Macro to DebugTrace failures from a Read/Write calls */

#define TraceFailedRead(_a, _b) \
    hr = (_a); \
    if(HR_FAILED(hr)) \
    { \
        DebugTraceResult(Read(), hr); \
        goto _b; \
    }

#define TraceFailedWrite(_a, _b) \
    hr = (_a); \
    if(HR_FAILED(hr)) \
    { \
        DebugTraceResult(Write(), hr); \
        goto _b; \
    }
    

/* All extern variables are declared in xpqueue.c  */

extern TCHAR rgszTags[NUM_TAGS][MAX_TAG_LEN];
extern TCHAR szCRLF[3];
extern TCHAR szCRLFCRLF[5];


/* Function Prototypes */

HRESULT HrGetLine(LPSTREAM lpSof, ULONG cbDest, LPTSTR lpsz, ULONG *pcbRead);
HRESULT HrBuildSenderProps(LPXPL lpxpl, LPSPropValue lpPropArray, ULONG ulTag, 
        LPTSTR lpszToken, LPTSTR lpszAddrType, LPMESSAGE lpMessage, 
        ULONG * lpcValues, LPSPropValue lpMsgProps);
HRESULT HrGetStreamedProp(LPXPL lpxpl, LPSTREAM lpSof, LPMESSAGE lpMsg, 
        ULONG ulPropTag, ULONG * lpcValues, LPSPropValue lpMsgProps, 
        LPTSTR lpszLine, ULONG * lpulTag, LPTSTR * lppszToken);
HRESULT HrAddRecipToAdrList(LPXPL lpxpl, LONG lRecipType, 
        LPTSTR lpszNameAddr, LPTSTR lpszAddrType, LPMYADRLIST lpMyAdrList);
HRESULT HrAddRecipToReplyList(LPXPL lpxpl, LPTSTR lpszToken, LPTSTR lpszAddrType,
        LPTSTR *lppszNames, ULONG *lpcbEIDList, LPFLATENTRYLIST *lppEIDList);
HRESULT HrCrackSenderEID(LPXPL lpxpl, ULONG cb, LPBYTE lpb, LPTSTR lpsz);       
HRESULT HrMakeSearchKey(LPXPL lpxpl, LPVOID lpParent, LPTSTR lpszAddrType, 
        LPTSTR lpszAddress, ULONG *lpcbSK, LPBYTE *lppSK);  
BOOL    FGetTagAndToken(LPTSTR lpsz, ULONG *pulTag, LPTSTR *lppszToken);
void    FileTimeFromSzTime(LPTSTR lpszTime, FILETIME *pft);

HRESULT HrPrepareRecipientTable(LPSPropValue, LPMESSAGE, LPMAPITABLE *);
BOOL    FPropIndex(LPSPropValue, ULONG, ULONG, ULONG *);
void    FormatFileTime(FILETIME *, LPTSTR);

HRESULT HrIMsgToTextMsg(LPXPL lpxpl, LPSPropValue lpPropArray, LPMESSAGE lpMessage, LPSTREAM lpSof);
HRESULT HrIMsgFromTextMsg(LPXPL lpxpl, LPSPropValue lpPropArray, LPMESSAGE lpMessage, LPSTREAM lpSof);
