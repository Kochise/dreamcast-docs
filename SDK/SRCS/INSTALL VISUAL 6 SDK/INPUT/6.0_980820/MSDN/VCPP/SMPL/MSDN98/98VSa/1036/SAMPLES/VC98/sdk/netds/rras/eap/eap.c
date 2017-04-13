/********************************************************************/
/**          Copyright(c) 1985-1997 Microsoft Corporation.         **/
/********************************************************************/

//***
//
// Filename:    eap.c
//
// Description: Sample Extensible Authentication Protocol.
//              Here is a graphic of the EAP sample protocol:
//
//
//      Authenticator                       Authenticatee
//      -------------                       -------------
//
//                      "Send Password"
//                  ---------------------->
//                        EAP Request
//
//                        <password>
//                  <----------------------
//                        EAP Response
//
//  
//                  ----------------------->
//                       Success/Failure
//
//

#include <windows.h>
#include <lmcons.h>
#include <string.h>
#include <stdlib.h>
#include <rasauth.h>
#include <raseapif.h>
#include <raserror.h>
#define SDEBUGGLOBALS
#define RASEAPGLOBALS
#include "eap.h"

/*---------------------------------------------------------------------------
** External entry points
**---------------------------------------------------------------------------
*/

BOOL
RasEapDllEntry(
    IN HANDLE hinstDll,
    IN DWORD  fdwReason,
    IN LPVOID lpReserved 
)
    //
    // This routine is called by the system on various events such as the
    // process attachment and detachment.  See Win32 DllEntryPoint
    // documentation.
    //
    // Returns true if successful, false otherwise.
    //
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls( hinstDll );

            break;
        }

        case DLL_PROCESS_DETACH:
        {
            break;
        }
    }

    return( TRUE );
}


DWORD APIENTRY
RasEapGetInfo (
    IN  DWORD         dwEapTypeId,
    OUT PPP_EAP_INFO* pInfo 
)
    //
    // RasEapGetInfo entry point called by the EAP-PPP engine by name.  
    //
{
    if ( dwEapTypeId != PPP_EAP_PROTOCOL_ID )
    {
        return( ERROR_NOT_SUPPORTED );
    }

    ZeroMemory( pInfo, sizeof(PPP_EAP_INFO) );

    pInfo->dwEapTypeId       = PPP_EAP_PROTOCOL_ID;
    pInfo->RasEapBegin       = EapBegin;
    pInfo->RasEapEnd         = EapEnd;
    pInfo->RasEapMakeMessage = EapMakeMessage;

    return( NO_ERROR );
}


DWORD APIENTRY
EapBegin(
    OUT VOID** ppWorkBuf,
    IN  VOID*  pInfo 
)

    //
    // EapBegin entry point called by the EAP-PPP engine thru the passed
    // address.
    //
{
    PPP_EAP_INPUT* pInput = (PPP_EAP_INPUT* )pInfo;
    EAPCB*         pwb;

    //
    // Allocate work buffer.
    //

    if (!(pwb = (EAPCB* )LocalAlloc( LPTR, sizeof(EAPCB) )))
    {
        return( ERROR_NOT_ENOUGH_MEMORY );
    }

    //
    // Save information passed in
    //

    pwb->fAuthenticator                = pInput->fAuthenticator;
    pwb->EapState                      = MYSTATE_Initial;
    pwb->hPort                         = pInput->hPort;
    FpRasAuthenticateClient            = pInput->RasAuthenticateClient;

    //
    // Save the identity. On the authenticatee side, this is obtained by user
    // input, on the authenticator side this was obtained by the Identity
    // request message.

    strcpy( pwb->szIdentity, pInput->pszIdentity );

    //
    // If we are an authenticatee, then use the password passed in
    //

    if ( !pwb->fAuthenticator )
    {
        strcpy (pwb->szPassword, pInput->pszPassword);
    }

    //
    // Register work buffer with engine.
    //

    *ppWorkBuf = pwb;

    return( NO_ERROR );
}


DWORD APIENTRY
EapEnd(
    IN VOID* pWorkBuf 
)
    //
    // RasCpEnd entry point called by the PPP engine thru the passed address.
    // See RasCp interface documentation.
    //
{
    if (pWorkBuf)
    {
        ZeroMemory( pWorkBuf, sizeof(EAPCB) );
        LocalFree( (HLOCAL )pWorkBuf );
    }

    return( NO_ERROR );
}

DWORD APIENTRY
EapMakeMessage(
    IN  VOID*               pWorkBuf,
    IN  PPP_EAP_PACKET*     pReceiveBuf,
    OUT PPP_EAP_PACKET*     pSendBuf,
    IN  DWORD               cbSendBuf,
    OUT PPP_EAP_OUTPUT*     pResult,
    IN  PPP_EAP_INPUT*      pInput 
)
    //
    // RasEapMakeMessage entry point called by the PPP engine thru the passed
    // address.  
    //
{
    EAPCB* pwb = (EAPCB* )pWorkBuf;

    return
        (pwb->fAuthenticator)
          ? SMakeMessage(pwb, pReceiveBuf, pSendBuf, cbSendBuf, pInput, pResult)
          : CMakeMessage( pwb, pReceiveBuf, pSendBuf, cbSendBuf, pInput, pResult );
}


/*---------------------------------------------------------------------------
** Internal routines 
**---------------------------------------------------------------------------
*/

VOID
HostToWireFormat16(
    IN     WORD  wHostFormat,
    IN OUT PBYTE pWireFormat
)
{
    //
    // Will convert a 16 bit integer from host format to wire format
    //

    *((PBYTE)(pWireFormat)+0) = (BYTE) ((DWORD)(wHostFormat) >>  8);
    *((PBYTE)(pWireFormat)+1) = (BYTE) (wHostFormat);
}

WORD
WireToHostFormat16(
    IN PBYTE pWireFormat
)
{
    //
    // Will convert a 16 bit integer from wire format to host format
    //

    WORD wHostFormat = ((*((PBYTE)(pWireFormat)+0) << 8) +
                        (*((PBYTE)(pWireFormat)+1)));

    return( wHostFormat );
}

DWORD
CMakeMessage(
    IN  EAPCB*            pwb,
    IN  PPP_EAP_PACKET*   pReceiveBuf,
    OUT PPP_EAP_PACKET*   pSendBuf,
    IN  DWORD             cbSendBuf,
    IN  PPP_EAP_INPUT*    pInput,
    OUT PPP_EAP_OUTPUT*   pResult
)
    //
    // Authenticatee side event handler
    //
{
    DWORD dwRetCode = NO_ERROR;

    switch( pwb->EapState )
    {
        case MYSTATE_Initial:
        {
            if ( pReceiveBuf == NULL )
            {
                //
                // We are called one in the initial state. Since we are the
                // authenticatee, do nothing wait for request Pakcet from
                // authenticator.
                //

                pResult->Action = EAPACTION_NoAction;

                break;
            }
            else
            {
                //
                // If we received a request packet from the server then we
                // process it.
                //

                if ( pReceiveBuf->Code == EAPCODE_Request )
                {
                    //
                    // Build the response packet
                    //

                    MakeResponseMessage(pwb, pReceiveBuf, pSendBuf, cbSendBuf);
                    
                    //
                    // Response packets should not be sent with any timeout
                    //

                    pResult->Action = EAPACTION_Send;

                    //
                    // We are done so we change to MYSTATE_Done
                    //

                    pwb->EapState = MYSTATE_Done;
                }
                else
                {
                    //
                    // We shouldn't get any other packet in this state so
                    // we simply drop this invalid packet
                    //

                    pResult->Action = EAPACTION_NoAction;

                    dwRetCode = ERROR_PPP_INVALID_PACKET;

                    break;
                }
            }

            break;
        }

        case MYSTATE_Done:
        {
            if ( pReceiveBuf == NULL )
            {
                //  
                // If we did not receive a packet then we check to see if
                // the fSuccessPacketReceived flag is set
                //

                if ( ( pInput != NULL ) && ( pInput->fSuccessPacketReceived ) )
                {
                    //
                    // We are done
                    //

                    pResult->Action = EAPACTION_Done;
                    pwb->EapState   = MYSTATE_Done;
                }
                else
                {
                    //
                    // Otherwise we ignore this event
                    //

                    pResult->Action = EAPACTION_NoAction;
                }

                break;
            }

            if ( ( pReceiveBuf->Code == EAPCODE_Success ) ||
                 ( pReceiveBuf->Code == EAPCODE_Failure ) )
            {
                //
                // If we received success or failure, we are done
                //

                if ( pReceiveBuf->Id != pwb->dwIdExpected )
                {
                    //
                    // But first make sure the the Success/Failure packet ID
                    // matches that of the last response sent.
                    // If not silently discard the packet.
                    //

                    pResult->Action = EAPACTION_NoAction;
                    dwRetCode       = ERROR_PPP_INVALID_PACKET;
                }
                else
                {

                    pResult->Action = EAPACTION_Done;
                    pwb->EapState   = MYSTATE_Done;
                }

                break;
            }
            else if ( pReceiveBuf->Code == EAPCODE_Request )  
            {
                //
                // We must always respond to requests
                //

                MakeResponseMessage(pwb, pReceiveBuf, pSendBuf, cbSendBuf);

                //
                // Response packets should not be sent with any timeout
                //

                pResult->Action = EAPACTION_Send;
            }
            else
            {
                //
                // Otherwise we received an illegal packet, wrong code set
                // So simply drop the packet.
                //

                pResult->Action = EAPACTION_NoAction;
                dwRetCode       = ERROR_PPP_INVALID_PACKET;
            }
        }
    }

    return( dwRetCode );
}


VOID
MakeResponseMessage(
    IN  EAPCB*           pwb,
    IN  PPP_EAP_PACKET * pReceiveBuf,
    OUT PPP_EAP_PACKET * pSendBuf,
    IN DWORD             cbSendBuf
)
    //
    // Builds a response packet.  'pwb' is the address of the work
    // buffer associated with the port.
    //
{
    BYTE* pcbPassword;
    CHAR* pchPassword;

    (void )cbSendBuf;

    //
    // Fill in the password.
    //

    pcbPassword = pSendBuf->Data + 1; 

    *pcbPassword = (BYTE )strlen( pwb->szPassword );

    pchPassword = pcbPassword + 1;

    strcpy( pchPassword, pwb->szPassword );

    //
    // Set the response code
    //

    pSendBuf->Code = (BYTE )EAPCODE_Response;

    //
    // The Reponse packet Id MUST match the Request packet Id.
    //

    pSendBuf->Id = pReceiveBuf->Id;

    //
    // The Success/Failure packet that we get must match the ID of the last 
    // response sent
    //

    pwb->dwIdExpected = pSendBuf->Id;

    //
    // Set the EAP type ID
    //

    pSendBuf->Data[0] = (BYTE )PPP_EAP_PROTOCOL_ID;

    //
    // Set the length of the packet
    //

    HostToWireFormat16((WORD )(PPP_EAP_PACKET_HDR_LEN+1+*pcbPassword+1),
                       pSendBuf->Length );
}
   

VOID
MakeResultMessage(
    IN  DWORD           dwError,
    IN  BYTE            bId,
    OUT PPP_EAP_PACKET* pSendBuf,
    IN  DWORD           cbSendBuf 
)

    //
    // Builds a result packet (Success or Failure) in caller's 'pSendBuf' 
    // buffer. 'cbSendBuf' is the length of caller's buffer.  
    // 'dwError' indicates whether an Success or Failure should be generated, 
    // 'bId' is the Id of the Success of Failure packet.
    //
{
    (void )cbSendBuf;

    //
    // If there was no error then we send a Success packet, otherwise we send
    // a failure message
    //

    if ( dwError == NO_ERROR )
    {
        pSendBuf->Code = EAPCODE_Success;
    }
    else
    {
        pSendBuf->Code = EAPCODE_Failure;
    }

    //
    // Id must match the last response received
    //

    pSendBuf->Id = bId;

    //
    // Set the length
    //

    HostToWireFormat16((WORD)PPP_EAP_PACKET_HDR_LEN, (PBYTE )pSendBuf->Length);
}

VOID
MakeRequestMessage(
    IN  EAPCB*           pwb,
    OUT PPP_EAP_PACKET * pSendBuf,
    IN DWORD             cbSendBuf
)

    //
    // Will build a request packet
    //
{
    BYTE *pcbPeerMessage;
    CHAR *pchPeerMessage;

    pcbPeerMessage  = pSendBuf->Data + 1;

    *pcbPeerMessage = (BYTE)strlen("send password");

    pchPeerMessage  = pcbPeerMessage + 1;

    strcpy (pchPeerMessage,"send password");

    //
    // Set the Request Code
    // 

    pSendBuf->Code = EAPCODE_Request;

    //
    // Set the Identifier
    //

    pSendBuf->Id = (BYTE) dwNextId++;

    //
    // Remember this Id since we need to send the Success/Failure packet with
    // this Id
    //

    pwb->dwIdExpected = pSendBuf->Id; 

    //
    // Set the length
    //

    HostToWireFormat16((WORD)(PPP_EAP_PACKET_HDR_LEN+1+*pcbPeerMessage+1),  
                              pSendBuf->Length );

    //
    // Set the EAP Type Id
    //

    pSendBuf->Data[0] = PPP_EAP_PROTOCOL_ID;

}

DWORD
SMakeMessage(
    IN  EAPCB*              pwb,
    IN  PPP_EAP_PACKET*     pReceiveBuf,
    OUT PPP_EAP_PACKET*     pSendBuf,
    IN  DWORD               cbSendBuf,
    IN  PPP_EAP_INPUT*      pInput,
    OUT PPP_EAP_OUTPUT*     pResult 
)
    //
    // Authenticator side event handler
    //
{
    DWORD dwRetCode = NO_ERROR;

    switch( pwb->EapState )
    {
        case MYSTATE_ReqSent:

            if ( pReceiveBuf != NULL )
            {
                //
                // If we received a packet
                //

                if ( pReceiveBuf->Code == EAPCODE_Response )
                {
                    CHAR szPassword[PWLEN + 1];

                    //
                    // If we received a response to our identity request, 
                    // then process it. There is no need to check the Id    
                    // here since the PPP engine will only pass on packets
                    // whose Id matches those set with the 
                    // EAPACTION_SendWithTimeout action.
                    //

                    dwRetCode = GetPasswordFromResponse( pReceiveBuf, 
                                                         szPassword );

                    if ( dwRetCode != NO_ERROR )
                    {    
                        if ( dwRetCode != ERROR_PPP_INVALID_PACKET )
                        {
                            //
                            // Fatal error, we fail the connection. 
                            //

                            return( dwRetCode );
                        }
                        
                        //
                        // Otherwise the packet is most likely corrupt.  
                        // Fall thru to the initial state to resend the
                        // request with the same Id.
                        //

                        dwNextId = pwb->dwIdExpected;
                    }
                    else
                    {

                        //
                        // Request authentication provider to authenticate 
                        // this user.
                        //

                        dwRetCode = AuthenticateUser( pwb->szIdentity, 
                                                      szPassword,   
                                                      pwb );

                        if ( dwRetCode != NO_ERROR )
                        {
                            return( dwRetCode );
                        }
                        else
                        {
                            //
                            // Authentication request completed successfully.
                            // This is an asynchronous call so we change state
                            // and wait for the provider to complete the 
                            // authentication.  
                            //

                            pwb->EapState = 
                                    MYSTATE_WaitForAuthenticationToComplete;

                            pResult->Action = EAPACTION_NoAction;
                        }        
                    }

                    break;
                }
                else
                {
                    //
                    // Otherwise silently drop the packet. 
                    // We should only get requests
                    //

                    pResult->Action = EAPACTION_NoAction;

                    break;
                }
            }
            else
            {
                //
                // If in this state we get called with a NULL pReceiveBuf, this
                // means that we timed out waiting for a response from the
                // the authenticatee, we need to resend with the same Id. 
                // 

                dwNextId = pwb->dwIdExpected;

                //
                // Fall thru to resend the request packet
                //
            }

        case MYSTATE_Initial:

            //
            // Create Request packet
            //

            MakeRequestMessage( pwb, pSendBuf, cbSendBuf );

            //
            // Tell the PPP engine to drop all responses that do not mactch
            // this Id
            //

            pResult->dwIdExpected = (BYTE)pwb->dwIdExpected;

            //
            // Request messages must be sent with a timeout
            //

            pResult->Action = EAPACTION_SendWithTimeout;

            //
            // Send we have sent a Request we change to the ReqSent state
            // where we will wait for a response
            //

            pwb->EapState = MYSTATE_ReqSent;

            break;

        case MYSTATE_WaitForAuthenticationToComplete:
        {
            if ( pInput != NULL )
            {
                //
                // Did the authentication provider complete the authentication?
                //

                if ( pInput->fAuthenticationComplete )
                {
                    //
                    // If there was a processing error, simply return this 
                    // error.
                    //

                    if ( pInput->dwAuthError != NO_ERROR )
                    {
                        return( pInput->dwAuthError );
                    }

                    //
                    // If the authentication process completed successfully but
                    // the user failed to authenticate, save the failure code.
                    //

                    if ( pInput->dwAuthResultCode != NO_ERROR )
                    {
                        pwb->dwResult = pInput->dwAuthResultCode;
                    }

                    pResult->Action = EAPACTION_SendAndDone;
                    pwb->EapState   = MYSTATE_Done;

                    //
                    // fall thru to the MYSTATE_Done state where we will
                    // send a Success or Failure packet
                    //
                }
            }

            if ( ( pInput == NULL ) || ( !pInput->fAuthenticationComplete ) )
            {
                //
                // Ignore everything if authentication is not complete
                //

                pResult->Action = EAPACTION_NoAction;

                break;
            }

            //
            // ...fall thru to the MYSTATE_Done state where we will
            // send a Success or Failure packet
            //
        }

        case MYSTATE_Done:
        {
            //
            // Make Success or Failure packet.  
            //

            MakeResultMessage( pwb->dwResult,    
                               (BYTE)pwb->dwIdExpected,   
                               pSendBuf,  
                               cbSendBuf);     

            strcpy( pResult->szIdentity, pwb->szIdentity );

            pResult->Action = EAPACTION_SendAndDone;

            pResult->dwAuthResultCode = pwb->dwResult;

            break;
        }

        default:

            break;
    }

    return( dwRetCode );

}

DWORD
GetPasswordFromResponse(
    IN  PPP_EAP_PACKET* pReceiveBuf,
    OUT CHAR*           pszPassword
)
    //
    // Fill caller's pszPassword' buffer with the password, in the request 
    // packet.
    //
    // Returns NO_ERROR if successful., or ERROR_PPP_INVALID_PACKET if the 
    // packet is misformatted in any way.
    //
{
    BYTE* pcbPassword;
    CHAR* pchPassword;
    WORD  cbPacket;

    cbPacket = WireToHostFormat16( pReceiveBuf->Length );

    //
    // Extract the password
    //

    if ( cbPacket < ( PPP_EAP_PACKET_HDR_LEN + 1 + 1 ) )
    {
        return( ERROR_PPP_INVALID_PACKET );
    }

    pcbPassword = pReceiveBuf->Data + 1;
    pchPassword = pcbPassword + 1;

    if (cbPacket < PPP_EAP_PACKET_HDR_LEN + 1 + 1 + *pcbPassword)
    {
        return ERROR_PPP_INVALID_PACKET;
    }

    CopyMemory( pszPassword, pchPassword, *pcbPassword );

    //
    // NULL terminate the password
    //

    pszPassword[ *pcbPassword ] = '\0';

    return( NO_ERROR );
}

DWORD 
AuthenticateUser(
    IN CHAR *szUserName,    
    IN CHAR *szPassword,    
    IN EAPCB *pwb
)
    //
    // Will build user attributes and send them to the authentication provider
    // for authentication.
    //
{

    RAS_AUTH_ATTRIBUTE *pAttributes = NULL;
    DWORD dwRetCode;

    pAttributes = (RAS_AUTH_ATTRIBUTE *)
                 LocalAlloc(LPTR, sizeof (RAS_AUTH_ATTRIBUTE) * 3);

    if (pAttributes == NULL) 
    {
        return (GetLastError());
    }

    //
    // for user name
    //

    pAttributes[0].raaType = raatUserName;
    pAttributes[0].dwLength =strlen(szUserName);
    pAttributes[0].Value = LocalAlloc(LPTR, (strlen(szUserName)+1));

    if (pAttributes == NULL) 
    { 
        LocalFree (pAttributes); 
        return (GetLastError());
    }

    CopyMemory (pAttributes[0].Value,szUserName, strlen(szUserName));

    //
    // for password
    //

    pAttributes[1].raaType = raatUserPassword;
    pAttributes[1].dwLength =strlen(szPassword);
    pAttributes[1].Value = LocalAlloc(LPTR, (strlen(szPassword)+1));

    if (pAttributes == NULL) 
    { 
        LocalFree (pAttributes[0].Value);
        LocalFree (pAttributes); 
        return (GetLastError());
    }

    CopyMemory (pAttributes[1].Value,szPassword, strlen(szPassword));
  
    //
    // For Termination
    //

    pAttributes[2].raaType  = raatMinimum;
    pAttributes[2].dwLength = 0;
    pAttributes[2].Value    = NULL;


    //
    // Call the authentication provider
    //

    dwRetCode = (*FpRasAuthenticateClient)( pwb->hPort, pAttributes );

    //
    // Free up Attributes
    //

    LocalFree (pAttributes[0].Value);
    LocalFree (pAttributes[1].Value);

    return( dwRetCode );
}
