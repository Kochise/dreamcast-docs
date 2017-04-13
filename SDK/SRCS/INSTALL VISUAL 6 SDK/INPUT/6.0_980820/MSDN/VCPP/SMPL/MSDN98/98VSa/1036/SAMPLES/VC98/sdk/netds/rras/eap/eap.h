/********************************************************************/
/**          Copyright(c) 1985-1997 Microsoft Corporation.         **/
/********************************************************************/

//***
//
// Filename:    eap.h
//
// Description: Sample Extensible Authentication Protocol header file
//
//

#ifndef _EAP_H_
#define _EAP_H_

//
// This protocols Type Id
//

#define PPP_EAP_PROTOCOL_ID 20

//
// Defines states within the this EAP protocol.
//

typedef enum _MYSTATE 
{
    MYSTATE_Initial,
    MYSTATE_ReqSent,
    MYSTATE_WaitForAuthenticationToComplete,
    MYSTATE_Done

}MYSTATE;

typedef struct _EAPCB 
{
    MYSTATE     EapState;

    HANDLE      hPort;

    BOOL        fAuthenticator;

    LPVOID      pWorkBuffer;

    CHAR        szIdentity[ UNLEN + 1 ];

    DWORD       dwIdExpected;

    CHAR        szPassword[ PWLEN + 1 ];

    DWORD       dwResult;

    RAS_AUTH_ATTRIBUTE * pUserAttributes;

} EAPCB, *PEAPCB;

//
// Function Prototypes
//

DWORD APIENTRY
EapBegin(
    OUT VOID** ppWorkBuf,
    IN  VOID*  pInfo 
);

DWORD APIENTRY
EapEnd(
    IN VOID* pWorkBuf 
);

DWORD APIENTRY
EapMakeMessage(
    IN  VOID*               pWorkBuf,
    IN  PPP_EAP_PACKET*     pReceiveBuf,
    OUT PPP_EAP_PACKET*     pSendBuf,
    IN  DWORD               cbSendBuf,
    OUT PPP_EAP_OUTPUT*     pResult,
    IN  PPP_EAP_INPUT*      pInput 
);

DWORD
CMakeMessage(
    IN  EAPCB*              pwb,
    IN  PPP_EAP_PACKET*     pReceiveBuf,
    OUT PPP_EAP_PACKET*     pSendBuf,
    IN  DWORD               cbSendBuf,
    IN PPP_EAP_INPUT*       pInput,
    OUT  PPP_EAP_OUTPUT*    pResult
);

DWORD
SMakeMessage(
    IN  EAPCB*              pwb,
    IN  PPP_EAP_PACKET*     pReceiveBuf,
    OUT PPP_EAP_PACKET*     pSendBuf,
    IN  DWORD               cbSendBuf,
    IN PPP_EAP_INPUT*       pInput,
    OUT  PPP_EAP_OUTPUT*    pResult
);

VOID
MakeResponseMessage(
    IN  EAPCB*              pwb,
    IN  PPP_EAP_PACKET*     pReceiveBuf,
    OUT PPP_EAP_PACKET *    pSendBuf,
    IN DWORD                cbSendBuf
);

VOID
MakeResultMessage(
    IN  DWORD              dwError,
    IN  BYTE               bId,
    OUT PPP_EAP_PACKET*    pSendBuf,
    IN  DWORD              cbSendBuf
);

DWORD
GetPasswordFromResponse(
    IN  PPP_EAP_PACKET*    pReceiveBuf,
    OUT CHAR*              pszUserName
);

DWORD
AuthenticateUser(
    IN CHAR *               szUserName,
    IN CHAR *               szPassword,
    IN EAPCB *              pwb
);

//
// Globals.
//

#ifdef RASEAPGLOBALS
#define GLOBALS
#define EXTERN
#else
#define EXTERN extern
#endif

//
// Next packet identifier to assign.  
//
EXTERN DWORD dwNextId
#ifdef GLOBALS
    = 0
#endif
;

EXTERN
DWORD  (APIENTRY *FpRasAuthenticateClient)( 
    IN  HANDLE                  hPort,
    IN  RAS_AUTH_ATTRIBUTE *    pInAttributes 
)
#ifdef GLOBALS
    = NULL
#endif
;

#undef EXTERN
#undef GLOBALS

#endif // _EAP_H_
