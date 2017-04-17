/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRSnetwork.h
 *  Content:    Lobby server network cotrol library include file
 ***************************************************************************/
#ifndef _SRS_NETWORK_H_
#define _SRS_NETWORK_H_

//=========================================
//   ä÷êîíËã`
//=========================================
__declspec( dllexport )int __stdcall SRS_Net_Open( int iPort );
__declspec( dllexport )int __stdcall SRS_Net_Close( void );
__declspec( dllexport )int __stdcall SRS_Net_RcvReq( char *lpRcvData, size_t szSize );
__declspec( dllexport )int __stdcall SRS_Net_SendReq( int iClientIP, char *lpSendData, size_t szSize );


#endif
