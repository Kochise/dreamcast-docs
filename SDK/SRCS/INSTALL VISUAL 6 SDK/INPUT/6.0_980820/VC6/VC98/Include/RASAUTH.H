/********************************************************************/
/**               Copyright(c) 1997 Microsoft Corporation.	       **/
/********************************************************************/

//***
//
// Filename:    RASAUTH.H
//
// Description: Contains definitions to allow for third parties to plug in 
//              back-end authenticaion modules into Remote Access Service.
//
#ifndef _RASAUTH_
#define _RASAUTH_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _RAS_AUTH_ATTRIBUTE_TYPE_
{
    raatMinimum = 0,                // Undefined
    raatUserName,                   // Value field is a Pointer       
    raatUserPassword,               // Value field is a Pointer       
    raatMD5CHAPPassword,            // Value field is a Pointer       
    raatNASIPAddress,               // Value field is a 32 bit integral value
    raatNASPort,                    // Value field is a 32 bit integral value
    raatServiceType,                // Value field is a 32 bit integral value
    raatFramedProtocol,             // Value field is a 32 bit integral value
    raatFramedIPAddress,            // Value field is a 32 bit integral value
    raatFramedIPNetmask,            // Value field is a 32 bit integral value
    raatFramedRouting,              // Value field is a 32 bit integral value
    raatFilterId,                   // Value field is a Pointer       
    raatFramedMTU,                  // Value field is a 32 bit integral value
    raatFramedCompression,          // Value field is a 32 bit integral value
    raatLoginIPHost,                // Value field is a 32 bit integral value
    raatLoginService,               // Value field is a 32 bit integral value
    raatLoginTCPPort,               // Value field is a 32 bit integral value
    raatUnassigned1,                // Undefined
    raatReplyMessage,               // Value field is a Pointer       
    raatCallbackNumber,             // Value field is a Pointer       
    raatCallbackId,                 // Value field is a Pointer       
    raatUnassigned2,                // Undefined
    raatFramedRoute,                // Value field is a Pointer       
    raatFramedIPXNetwork,           // Value field is a 32 bit integral value
    raatState,                      // Value field is a Pointer       
    raatClass,                      // Value field is a Pointer       
    raatVendorSpecific,             // Value field is a Pointer       
    raatSessionTimeout,             // Value field is a 32 bit integral value
    raatIdleTimeout,                // Value field is a 32 bit integral value
    raatTerminationAction,          // Value field is a 32 bit integral value
    raatCalledStationId,            // Value field is a Pointer       
    raatCallingStationId,           // Value field is a Pointer       
    raatNASIdentifier,              // Value field is a Pointer       
    raatProxyState,                 // Value field is a Pointer       
    raatLoginLATService,            // Value field is a Pointer       
    raatLoginLATNode,               // Value field is a Pointer       
    raatLoginLATGroup,              // Value field is a Pointer       
    raatFramedAppleTalkLink,        // Value field is a 32 bit integral value
    raatFramedAppleTalkNetwork,     // Value field is a 32 bit integral value
    raatFramedAppleTalkZone,        // Value field is a Pointer       
    raatAcctStatusType,             // Value field is a 32 bit integral value
    raatAcctDelayType,              // Value field is a 32 bit integral value
    raatAcctInputOctets,            // Value field is a 32 bit integral value
    raatAcctOutputOctets,           // Value field is a 32 bit integral value
    raatAcctSessionId,              // Value field is a Pointer       
    raatAcctAuthentic,              // Value field is a 32 bit integral value
    raatAcctSessionTime,            // Value field is a 32 bit integral value
    raatAcctInputPackets,           // Value field is a 32 bit integral value
    raatAcctOutputPackets,          // Value field is a 32 bit integral value
    raatAcctTerminateCause,         // Value field is a 32 bit integral value
    raatAcctMultiSessionId,         // Value field is a Pointer       
    raatAcctLinkCount,              // Value field is a 32 bit integral value
    raatMD5CHAPChallenge = 60,      // Value field is a Pointer       
    raatNASPortType,                // Value field is a 32 bit integral value
    raatPortLimit,                  // Value field is a 32 bit integral value
    raatLoginLATPort,               // Value field is a Pointer       
    raatPrompt,                     // Value field is a 32 bit integral value
    raatConnectInfo,                // Value field is a Pointer       
    raatSignature,                  // Value field is a Pointer       
    raatEAPMessage,                 // Value field is a Pointer       
    raatConfigurationToken,         // Value field is a Pointer       
    raatPasswordRetry,              // Value field is a 32 bit integral value
    raatARAPPassword,               // Value field is a Pointer       
    raatARAPFeatures,               // Value field is a Pointer       
    raatARAPZoneAccess,             // Value field is a 32 bit integral value
    raatARAPSecurity,               // Value field is a 32 bit integral value
    raatARAPSecurityData,           // Value field is a Pointer       
    raatReserved        = (0xFFFFFFFF)      // Undefined

}RAS_AUTH_ATTRIBUTE_TYPE;

//
// Value is set to the 32 bit integral value or a pointer to data.
// 32 bit integral values should be in host format, not network format.
// Length for a 32 bit integral value can be 1, 2 or 4. The array of 
// attributes must be terminated with an attribute of type raatMinimum.
//

typedef struct _RAS_AUTH_ATTRIBUTE 
{
    RAS_AUTH_ATTRIBUTE_TYPE raaType; 
    DWORD                   dwLength;   
    PVOID                   Value;    

}RAS_AUTH_ATTRIBUTE, *PRAS_AUTH_ATTRIBUTE;

//
// The following APIs (except for RasStartAccounting and RasStopAccounting)
// must be exported by the back-end authentication DLL
//

//
// Called from setup application to allow backend package to bring up UI to
// configure itself.
//

VOID APIENTRY
RasAuthSetup(
    VOID
);

DWORD APIENTRY 
RasAuthConfigChangeNotification(
    VOID
);

//
// Called once before any other calls are made.
//

DWORD APIENTRY
RasAuthInitialize(
    VOID
);

//
// Called once to deallocate resources etc. No more calls will be made before
// calling RasAuthInitialize again
//

DWORD APIENTRY
RasAuthTerminate(
    VOID
);

//
// Called once per multilink connection, not per link.
//

DWORD APIENTRY
RasStartAccounting(
    IN  RAS_AUTH_ATTRIBUTE *    pInAttributes,
    OUT PRAS_AUTH_ATTRIBUTE *   ppOutAttributes
);

//
// Called once per multilink connection, not per link.
//

DWORD APIENTRY
RasStopAccounting(
    IN  RAS_AUTH_ATTRIBUTE *    pInAttributes,
    OUT PRAS_AUTH_ATTRIBUTE *   ppOutAttributes
);

//
// Called to authenticate a dialed in user. 
//

DWORD APIENTRY
RasAuthenticateUser(
    IN  RAS_AUTH_ATTRIBUTE *    pInAttributes,
    OUT PRAS_AUTH_ATTRIBUTE *   ppOutAttributes,
    OUT DWORD *                 lpdwResultCode
);

//
// Called to free attributes allocated by the back-end module
//

DWORD APIENTRY
RasFreeAttributes(
    IN  RAS_AUTH_ATTRIBUTE *    pAttributes
);

#ifdef __cplusplus
}
#endif

#endif
