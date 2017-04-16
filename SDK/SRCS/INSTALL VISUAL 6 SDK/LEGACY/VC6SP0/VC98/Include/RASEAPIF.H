/********************************************************************/
/**               Copyright(c) 1989 Microsoft Corporation.	       **/
/********************************************************************/

//***
//
// Filename:	raseapif.h
//
// Description: Defines interface between a third party authentication module
//              and the Remote Access Service PPP engine.
//

#ifndef _RASEAPIF_
#define _RASEAPIF_

#include <lmcons.h>     // For UNLEN definition

//
// Defines used for installtion of EAP DLL
//
// Custom EAP DLL (ex. Name=Sample.dll, Type=40) regsitry installation
//
// HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\Rasman\PPP\EAP\40)
//      Path                (REG_EXPAND_SZ) %SystemRoot%\system32\sample.dll  
//      FriendlyName        (REG_SZ) Sample EAP Protocol
//      ConfigUIPath        (REG_EXPAND_SZ) %SystemRoot%\system32\sample.dll  
//      InteractiveUIPath   (REG_EXPAND_SZ) %SystemRoot%\system32\sample.dll  
//      RequireConfigUI     (REG_DWORD) 1
//
//

#define RAS_EAP_REGISTRY_LOCATION   \
    TEXT("System\\CurrentControlSet\\Services\\Rasman\\PPP\\EAP")

#define RAS_EAP_VALUENAME_PATH              TEXT("Path")   
#define RAS_EAP_VALUENAME_CONFIGUI          TEXT("ConfigUIPath")
#define RAS_EAP_VALUENAME_INTERACTIVEUI     TEXT("InteractiveUIPath")
#define RAS_EAP_VALUENAME_FRIENDLY_NAME     TEXT("FriendlyName")
#define RAS_EAP_VALUENAME_DEFAULT_DATA      TEXT("ConfigData")
#define RAS_EAP_VALUENAME_DEFAULT_IDENTITY  TEXT("Identity")
#define RAS_EAP_VALUENAME_REQUIRE_CONFIGUI  TEXT("RequireConfigUI")
#define RAS_EAP_VALUENAME_INVOKE_STDUI   TEXT("InvokeStandardCredentialsDialog")

//
// EAP packet codes from EAP spec.
//

#define EAPCODE_Request         1
#define EAPCODE_Response        2
#define EAPCODE_Success         3
#define EAPCODE_Failure         4

#define MAXEAPCODE              4

typedef struct _PPP_EAP_PACKET
{
    BYTE    Code;       // 1-Request, 2-Response, 3-Success, 4-Failure

    BYTE    Id;         // Id of this packet

    BYTE    Length[2];  // Length of this packet

    BYTE    Data[1];    // Data - First byte is Type for Request/Response

}PPP_EAP_PACKET, *PPPP_EAP_PACKET;

#define PPP_EAP_PACKET_HDR_LEN  ( sizeof( PPP_EAP_PACKET ) - 1 )

//
// Interface structure between the engine and APs. This is passed to the
// AP's via the RasCpBegin call. 
//

typedef struct _PPP_EAP_INPUT
{
    //
    // Size of this structure
    //

    DWORD       dwSizeInBytes;  

    //
    // The follwing four fields are valid only in RasEapBegin call
    //

    HANDLE      hPort;          // Used to pass to back-end authenticator

    BOOL 	    fAuthenticator;	// Act as authenticator or authenticatee

    CHAR *      pszIdentity;    // Users's identity

    CHAR *      pszPassword;    // Client's account password.

    //
    // Set of attributes for the currently dialed in user, set only on
    // RasEapBegin call for the authenticator side. 
    // Identifies the port used, NAS IP Address etc. May be used to send to
    // the authentication provider, if this protocol is using one.
    //

    RAS_AUTH_ATTRIBUTE * pUserAttributes;

    //
    // The following fields are used only if the EAP DLL is using the 
    // currently configured authentication provider ex: RADIUS or Windows NT 
    // domain authentication, and the fAuthenticator field above is set to 
    // TRUE.
    //

    //
    // This call should be used to make use of the installed back-end
    // authenticator. It is upto the EAP DLL to free the pInAttributes
    // memory. The pInAttributes structure may be freed soon after the
    // call since a copy of this is made.
    //

    DWORD  (APIENTRY *RasAuthenticateClient)(
                                IN  HANDLE                  hPort,
                                IN  RAS_AUTH_ATTRIBUTE *    pInAttributes );

    //
    // Indicates that the authenticator has completed the previous call to
    // RasAuthenticateClient. Ignore this field if an authentication provider
    // is not being used.
    //

    BOOL                fAuthenticationComplete;    

    //
    // Used to indicate an error that did not allow the authentication process
    // to complete successfully. NO_ERROR means the dwAuthResultCode field 
    // below is valid. This field is valid only when the field above is TRUE.
    //

    DWORD               dwAuthError;

    //
    // Result of the authentication process by the authentication provider. 
    // NO_ERROR indicates success, 
    // otherwise is a value from winerror.h, raserror.h or mprerror.h 
    // indicating failure reason. Valid only when the field above is NO_ERROR.
    //

    DWORD               dwAuthResultCode;  

    //
    // When the fAuthenticationComplete flag is TRUE this will point to 
    // attributes returned by the authentication provider, if the 
    // authentication was successful. ie. dwAuthResultCode and dwAuthError are 
    // both NO_ERROR. This memory is not owned by the EAP DLL and it should 
    // only used for read.
    //

    OPTIONAL RAS_AUTH_ATTRIBUTE * pAttributesFromAuthenticator;

    //
    // Valid only on the authenticatee side. This may be used on the 
    // authenticatee side to impersonate the user being authenticated.
    //

    HANDLE              hTokenImpersonateUser;

    //
    // This variable should be examined only by the authenticatee side.
    // The EAP specification states that the success packet may be lost and 
    // since it is a non-acknowledged packet, reception of an NCP packet should
    // be interpreted as a success packet. This varable is set to TRUE in this
    // case only on the authenticatee side
    //

    DWORD               fSuccessPacketReceived;

    //
    // Will be set to TRUE only when the user dismissed the interactive
    // UI that was invoked by the EAP dll
    //

    DWORD               fDataReceivedFromInteractiveUI;

    //
    // Data received from the Interactive UI. Will be set to non-NULL when
    // fDataFromInteractiveUI is set to TRUE and the RasEapInvokeInteractiveUI
    // returned non-NULL data. This buffer will be freed by the PPP engine
    // on return from the RasEapMakeMessage call. A copy of this data should
    // be made in the EAP Dll's memory space.
    //

    OPTIONAL PBYTE      pDataFromInteractiveUI;

    //
    // Size in bytes of data pointed to by pDataFromInteractiveUI. This may
    // be 0 if there was no data passed back by the RasEapInvokeInteractiveUI
    // call.
    //

    DWORD               dwSizeOfDataFromInteractiveUI;

    //
    // Data received from the Config UI. Will be set to non-NULL when
    // fDataFromConfigUI is set to TRUE and the RasEapInvokeConfigUI
    // returned non-NULL data. This buffer will be freed by the PPP engine
    // on return from the RasEapMakeMessage call. A copy of this data should
    // be made in the EAP Dll's memory space.
    //

    OPTIONAL PBYTE      pDataFromConfigUI;

    //
    // Size in bytes of data pointed to by pDataFromConfigUI. This may
    // be 0 if there was no data passed back by the RasEapInvokeConfigUI
    // call.
    //

    DWORD               dwSizeOfDataFromConfigUI;

}PPP_EAP_INPUT, *PPPP_EAP_INPUT;

typedef enum _PPP_EAP_ACTION
{
    //
    // These actions are provided by the EAP DLL as output from the
    // RasEapMakeMessage API.  They tell the PPP engine what action (if any) to
    // take on the EAP DLL's behalf, and eventually inform the engine that the 
    // EAP DLL has finished authentication.
    //

    EAPACTION_NoAction,     // Be passive, i.e. listen without timeout (default)
    EAPACTION_Done,         // End auth session, dwAuthResultCode is set 
    EAPACTION_SendAndDone,  // As above but send message without timeout first
    EAPACTION_Send,         // Send message, don't timeout waiting for reply
    EAPACTION_SendWithTimeout, // Send message, timeout if reply not received
    EAPACTION_SendWithTimeoutInteractive // As above, but don't increment 
                                         // retry count

}PPP_EAP_ACTION;

typedef struct _PPP_EAP_OUTPUT
{
    //
    // Size of this structure
    //

    DWORD                   dwSizeInBytes;  

    //
    // Action that the PPP engine should take
    //

    PPP_EAP_ACTION          Action;

    //
    // MUST be set only if Action is EAPCTION_SendWithTimeout or
    // EAPACTION_SendWithTimeoutInteractive. This value indicates to PPP engine
    // to drop any responses with IDs that do not match this one.
    //

    DWORD                   dwIdExpected;

    //
    // dwAuthResultCode is valid only with an Action code of Done or 
    // SendAndDone. Zero value indicates succesful authentication.  
    // Non-zero indicates unsuccessful authentication with the value 
    // indicating the reason for authentication failure.
    // Non-zero return codes should be only from winerror.h, raserror.h and 
    // mprerror.h
    //

    DWORD	                dwAuthResultCode;

    //
    // Must be set on the Authenticator side when Action is EAPACTION_Done or
    // EAPACTION_SendAndDone. 
    //

    CHAR                    szIdentity[UNLEN+1];

    //
    // Non-NULL if there are any user attributes for this user. This is 
    // allocated by the EAP DLL only if it is not using the currently configured
    // authentication provider. It is upto the EAP DLL to free this memory in
    // RasEapEnd call. Should only be set on the Authenticator side when 
    // Action is EAPACTION_Done or EAPACTION_SendAndDone and if 
    // dwAuthResultCode is 0. 
    //

    OPTIONAL RAS_AUTH_ATTRIBUTE * pAuthenticatedUserAttributes;   

    //
    // Flag set to true will cause the RasEapInvokeInteractiveUI call to be
    // made.
    //

    BOOL                    fInvokeInteractiveUI;

    //
    // Pointer to context data, if any, to be sent to the UI. The EAP dll
    // is responsible for freeing this buffer in the RasEapEnd call or when
    // a response from the user for this invocation is obtained. 
    //

    OPTIONAL PBYTE          pUIContextData;

    //
    // Size in bytes of the data pointed to by pUIContextData. Ignored if 
    // pUIContextData is NULL
    //

    DWORD                   dwSizeOfUIContextData;
    

}PPP_EAP_OUTPUT, *PPPP_EAP_OUTPUT;

typedef struct _PPP_EAP_INFO
{
    //
    // Size of this structure
    //

    DWORD   dwSizeInBytes;  

    DWORD   dwEapTypeId;

    //
    // Called to get a context buffer for this EAP session and pass 
    // initialization  information. This will be called before any other 
    // call is made. Must return errorcodes only from winerror.h, raserror.h or
    // mprerror.h
    //

    DWORD   (APIENTRY *RasEapBegin)( OUT VOID **             ppWorkBuffer,
                                     IN  PPP_EAP_INPUT *     pPppEapInput );

    //
    // Called to free the context buffer for this EAP session. 
    // Called after this session is completed successfully or not.
    // Must return errorcodes only from winerror.h, raserror.h or mprerror.h
    //

    DWORD   (APIENTRY *RasEapEnd)(   IN  VOID *     pWorkBuffer );

    //
    // Called to process an incomming packet and/or send a packet.
    // cbSendPacket is the size in bytes of the buffer pointed to by 
    // pSendPacket. Must return errorcodes only from winerror.h, raserror.h or
    // mprerror.h. Error return code indicates an error occurance during the
    // authentication process.
    //

    DWORD   (APIENTRY *RasEapMakeMessage)(
                            IN  VOID*               pWorkBuf,
                            IN  PPP_EAP_PACKET*     pReceivePacket,
                            OUT PPP_EAP_PACKET*     pSendPacket,
                            IN  DWORD               cbSendPacket,
                            OUT PPP_EAP_OUTPUT*     pEapOutput,
                            IN  PPP_EAP_INPUT*      pEapInput );

}PPP_EAP_INFO, *PPPP_EAP_INFO;

//
// RasEapGetInfo should be exported by the 3rd party EAP dll installed in the
// registry via the Path value.
//

DWORD APIENTRY
RasEapGetInfo(
    IN  DWORD           dwEapTypeId,
    OUT PPP_EAP_INFO*   pEapInfo
);

//
// RasEapInvokeInteractiveUI and RasEapFreeUserData should be exported by the 
// 3rd party EAP dll installed in the registry via the InterfactiveUI value.
//

DWORD APIENTRY 
RasEapInvokeInteractiveUI(
    IN  HWND            hwndParent,
    IN  PBYTE           pUIContextData,
    IN  DWORD           dwSizeofUIContextData,
    OUT PBYTE *         ppUserData              OPTIONAL,
    OUT DWORD *         lpdwSizeOfUserData
);

DWORD APIENTRY 
RasEapFreeUserData(
    IN  PBYTE           pUserData
);

//
// RasEapInvokeConfigUI and RasEapFreeConfigData should be exported by the 
// 3rd party EAP dll installed in the registry via the ConfigUI value.
//

DWORD APIENTRY 
RasEapInvokeConfigUI(
    IN  HWND            hwndParent,
    OUT BYTE *          pConfigData,
    OUT DWORD *         lpdwSizeOfConfigData,
    OUT BOOL  *         fInvokeStandardCredentialsDialog,
    OUT LPSTR           szIdentity              OPTIONAL    
);

DWORD APIENTRY 
RasEapFreeConfigData(
    IN  PBYTE           pConfigData
);

#endif
