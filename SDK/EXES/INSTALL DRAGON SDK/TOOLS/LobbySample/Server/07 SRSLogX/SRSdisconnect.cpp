/***************************************************************************
 *
 *  Copyright (C) 2000 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRSdisconnect.cpp  (based on SRSstop,SRSinitial)
 *
 *  Content:    Lobby server disconnect command
 *
 ***************************************************************************/
#include <windows.h>
#include <stdio.h>

#include "SRScom.h"
#include "SRSdebug.h"

#include "SRSdisconnect.h"
#include "Registry.h"

int SRSdisconnect( int iPort, WORD fix /* = IF_REQ_DISCONNECT */ )
{
	SOCKET	ServerSd;			
	int 	iResult;
	int 	iSendLen;
	int 	iSendData;
    PHOSTENT lphostent;
	struct	SRS_IF_FIX *lpIfFix;
	char	cIfFix[256];
	char	cServerName[32];
	char	cDummyBuff[16];
	char	cMsg[256];

	struct timeval *lpConnectTime = new struct timeval;
	struct fd_set *lpWriteFds = new struct fd_set;
	// for socket
	WORD      wVersionRequested = MAKEWORD(1, 1);
	WSADATA   wsaData;
	SOCKADDR_IN   ClientAddr;
	SOCKADDR_IN   ServerAddr;
	u_long ulCmdArg = 1;

	iResult = WSAStartup( wVersionRequested, &wsaData );
	if ( iResult != 0 )
	{
		iResult = WSAGetLastError();
		sprintf( cMsg, "SRSLogX : WSAStartup error:%d", iResult );
		SRS_Dbg_WriteLog( cMsg );
		goto ERRORRET;
	}

	ServerSd = socket( AF_INET, SOCK_STREAM, 0 );

	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_port = 0;
	ClientAddr.sin_addr.s_addr = htonl(INADDR_ANY);	

	iResult = bind( ServerSd, (LPSOCKADDR)&ClientAddr, sizeof(ClientAddr));
	if( iResult == SOCKET_ERROR )
	{
		iResult = WSAGetLastError();
		sprintf( cMsg, "SRSLogX : bind error:%d", iResult );
		SRS_Dbg_WriteLog( cMsg );

		iResult = closesocket(ServerSd);
		goto ERRORRET;
	}

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(SRS_PORT_SERVER);
    gethostname( cServerName, sizeof(cServerName) );
    lphostent = gethostbyname(cServerName);
    memcpy( (char *)&ServerAddr.sin_addr.s_addr, *lphostent->h_addr_list, 4);
	{
		DWORD ip;
		ip = SRSLog_IPLoad();
		if ( ip != 0 )
		{
			if ( ip != ServerAddr.sin_addr.s_addr )
			{
				sprintf( cMsg, "SRSLogX : IP error:Sock[%d.%d.%d.%d] Reg[%d.%d.%d.%d]", (ServerAddr.sin_addr.s_addr & 0xff), ((ServerAddr.sin_addr.s_addr >> 8) & 0xff), ((ServerAddr.sin_addr.s_addr >> 16) & 0xff), ((ServerAddr.sin_addr.s_addr >> 24) & 0xff), (ip & 0xff), ((ip >> 8) & 0xff), ((ip >> 16) & 0xff), ((ip >> 24) & 0xff) );
				SRS_Dbg_WriteLog( cMsg );
				ServerAddr.sin_addr.s_addr = ip;
			}
		}
	}

	iResult = connect( ServerSd, (LPSOCKADDR)&ServerAddr, sizeof(ServerAddr) );
	if( iResult == SOCKET_ERROR )
	{
		iResult = WSAGetLastError();
		if( iResult == WSAEWOULDBLOCK )
		{
			FD_ZERO(lpWriteFds);
			FD_SET(ServerSd, lpWriteFds);

			lpConnectTime->tv_sec = 10;
			lpConnectTime->tv_usec = 0;

			SRS_Dbg_WriteLog( "SRSLogX : select" );
			iResult = select(0, NULL, lpWriteFds, NULL, lpConnectTime);

			if( (iResult == 0) || (iResult == SOCKET_ERROR) )
			{
				sprintf( cMsg, "SRSLogX : select error %d", iResult );
				SRS_Dbg_WriteLog( cMsg );
				iResult = closesocket(ServerSd);
				goto ERRORRET;
			}
		}
		else
		{
			sprintf( cMsg, "SRSLogX : connect error %d", iResult );
			SRS_Dbg_WriteLog( cMsg );
			iResult = closesocket(ServerSd);
			goto ERRORRET;
		}
	}

	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;

	lpIfFix->IF_wRequest = fix;
	if ( iPort > 0 ) lpIfFix->IF_iPortNo = iPort;

	iSendLen = 0;
	do
	{
		iSendData = send( ServerSd, (char*)cIfFix, SRS_IF_FIX_SZ, 0 );
		iSendLen += iSendData;								
	}while( (iSendData != SOCKET_ERROR) && (iSendLen != SRS_IF_FIX_SZ) );

	if ( iSendData == SOCKET_ERROR )
	{
		iResult = WSAGetLastError();
		sprintf( cMsg,"SRSLogX : Send error :%d", iResult );
		SRS_Dbg_WriteLog( cMsg );
		closesocket( ServerSd );
		goto ERRORRET;
	}

	iResult = recv( ServerSd, cDummyBuff, 16, 0 );

	SRS_Dbg_WriteLog( "SRSLogX OK" );
	closesocket( ServerSd );

	delete lpConnectTime;
	delete lpWriteFds;

	return( 0 );

ERRORRET:
	delete lpConnectTime;
	delete lpWriteFds;

	return ( -1 );
}
