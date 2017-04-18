// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   rasutil.c
//
//  PURPOSE:  Implement the windows procedure for the main application
//            windows.  
//
//  FUNCTIONS:
//    GetRasConnState - maps RASCONNSTATE value in index in string table
//
//  COMMENTS:
//
//

#include <windows.h>            // required for all Windows applications
#include <windowsx.h>
#ifdef WIN16
#include "win16ext.h"           // required only for win16 applications
#endif

#include "globals.h"            // prototypes specific to this application
#include <stdlib.h>
#include <ras.h>
#include <raserror.h>
#include "rasutil.h"


//
//  FUNCTION: GetRasConnState( RASCONNSTATE )
//
//  PURPOSE: get the index to the corresponding string
//
//  PARAMETERS:
//    rasconn - ras connection state
//
//  RETURN VALUE:
//    index into stringtable.
//
//  COMMENTS:
//
UINT GetRasConnState( RASCONNSTATE rasconn )
{
    switch( rasconn )
    {
        case RASCS_OpenPort:
            return IDS_OPENPORT;
        case RASCS_PortOpened:
            return IDS_PORTOPENED;            
        case RASCS_ConnectDevice:
            return IDS_CONNECTDEVICE;        
        case RASCS_DeviceConnected:
            return IDS_DEVICECONNECTED;       
        case RASCS_AllDevicesConnected:
            return IDS_ALLDEVICESCONNECTED;   
        case RASCS_Authenticate:
            return IDS_AUTHENTICATE;          
        case RASCS_AuthNotify:
            return IDS_AUTHNOTIFY;            
        case RASCS_AuthRetry:
            return IDS_AUTHRETRY;             
        case RASCS_AuthCallback:
            return IDS_AUTHCALLBACK;          
        case RASCS_AuthChangePassword:
            return IDS_AUTHCHANGEPASSWORD;    
        case RASCS_AuthProject:
            return IDS_AUTHPROJECT;           
        case RASCS_AuthLinkSpeed:
            return IDS_AUTHLINKSPEED;         
        case RASCS_AuthAck: 
            return IDS_AUTHACK;               
        case RASCS_ReAuthenticate:
            return IDS_REAUTHENTICATE;        
        case RASCS_Authenticated:
            return IDS_AUTHENTICATED;         
        case RASCS_PrepareForCallback:
            return IDS_PREPAREFORCALLBACK;    
        case RASCS_WaitForModemReset:
            return IDS_WAITFORMODEMRESET;     
        case RASCS_WaitForCallback:
            return IDS_WAITFORCALLBACK;       
        case RASCS_Interactive:
            return IDS_INTERACTIVE;           
        case RASCS_RetryAuthentication: 
            return IDS_RETRYAUTHENTICATION;            
        case RASCS_CallbackSetByCaller: 
            return IDS_CALLBACKSETBYCALLER;   
        case RASCS_PasswordExpired:
            return IDS_PASSWORDEXPIRED;       
        case RASCS_Connected:
            return IDS_CONNECTED;            
        case RASCS_Disconnected:
            return IDS_DISCONNECTED;          
        default:
            return IDS_UNDEFINED_ERROR;
    }
}
