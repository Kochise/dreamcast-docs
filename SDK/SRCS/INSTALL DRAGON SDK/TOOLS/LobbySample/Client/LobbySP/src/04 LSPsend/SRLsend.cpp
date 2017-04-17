/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRLsend.cpp
 *
 *  Content:    Lobby client requests to connect to Lobby server
 *
 *
 ***************************************************************************/
//================================
//    Include
//================================
#include <windows.h>
#include <stdio.h>
#include <winsock.h>

#include "SRScom.h"
#include "LSPdebug.h"
#include "SRLregistry.h"
#include "SRLsend.h"
#include "SRLmanage.h"

#define LSP_PROC_RCV		TEXT("LSPreceive.exe")	// Rcv process

// for select   
struct fd_set *lpReadFds = new struct fd_set;		//Socket descriptor
struct timeval *lpSockTime = new struct timeval;	//Timmer
struct timeval *lpConnectTime = new struct timeval;	//Select stract
struct fd_set *lpWriteFds = new struct fd_set;		//Socket descriptor

// for socket
WORD      wVersionRequested = MAKEWORD(1, 1);		// Winsock 1.1 
WSADATA   wsaData;									// Winsock data
SOCKADDR_IN   ClientAddr;							// Client address
SOCKADDR_IN   ServerAddr;							// Server address
u_long ulCmdArg = 1;								// Blocking mode
SOCKET	ServerSd;			
//=============

/*=============================================================================
     Function : SRL_Snd_Connect
     Input    : lpServerIP Pointer for Server IP Address
	 Output   : no
	 Return   : True   Port number
	            False  -1
==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Snd_Connect( char *lpServerIP )
{
	int		iRtn;								//
	int		iPort;								// Server port number
	int		iReqSize;							//
	int 	nResult, iResult;					//
	int 	nBytesRecv;							//
	int 	iRecvBytes;							//
	int 	iSendLen;							// Send data size
	int 	iSendData;							// Send data counter
	DWORD	dwMax;								//
	struct	SRS_IF_FIX *lpIfFix;				//
	struct	SRS_IF_CONNECT *lpIfConnect;		// Connect request
	char	cIfFix[256];						//
	char	cRegBuff[16];						//
	char	cReceiveProc[512];					//
	char	cMsg[128];


//===========================================================================
//
//    Server connection
//
//===========================================================================
	/*==================================*/
	/* Init socket                      */
	/*==================================*/
	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("SRL_Snd_Connect: start\n"));
	iPort = 0;
	iResult = WSAStartup( wVersionRequested, &wsaData );
	if ( iResult != 0 )
	{
		iResult = WSAGetLastError();
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Connect: WSAStartup error:%d \n"),iResult );
		return( -1 );
	}

	ServerSd = socket( AF_INET, SOCK_STREAM, 0 );
	if( ServerSd == INVALID_SOCKET )
	{
		iResult = WSAGetLastError();
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Connect: socket error:%d \n"),iResult );
		return( -1 );
	}
	
	/*==================================*/
	/* Create session 		    */
	/*==================================*/
	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_port = 0;
	ClientAddr.sin_addr.s_addr = htonl(INADDR_ANY);	

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(SRS_PORT_SERVER);
	ServerAddr.sin_addr.s_addr = inet_addr( lpServerIP );	

	LSP_Dbg_Printf( DBG_LEVEL_2,TEXT( "SRL_Snd_Connect : connect\n" ));
	iResult = connect( ServerSd, (LPSOCKADDR)&ServerAddr, sizeof(ServerAddr) );
	if( iResult == SOCKET_ERROR )
	{
		iResult = WSAGetLastError();			//Get error
		if( iResult == WSAEWOULDBLOCK )	
		{
			FD_ZERO(lpWriteFds);				
			FD_SET(ServerSd, lpWriteFds);		

			// Watch about select
			lpConnectTime->tv_sec = 10;			
			lpConnectTime->tv_usec = 0;			

			iResult = select(0, NULL, lpWriteFds, NULL, lpConnectTime);

			//　Timeout or error
			if( (iResult == 0) || (iResult == SOCKET_ERROR) )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Connect: select error %d \n"),iResult );
				iRtn = shutdown( ServerSd, 2 );
				iResult = closesocket(ServerSd);
				return( -1 );
			}
		}
		else
		{
			// error except block
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Connect: connect error %d \n"),iResult );
			iRtn = shutdown( ServerSd, 2 );
			iResult = closesocket(ServerSd);
			return( -1 );
		}
	}

	//==================================
	// Send connection request			  			
	//==================================
	//　Create request
	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;
	lpIfFix->IF_wRequest = IF_REQ_CONNECT;

	//  Send  request
	iSendLen = 0;
	do
	{
		iSendData = send( ServerSd, (char*)cIfFix, SRS_IF_FIX_SZ, 0 );
		iSendLen += iSendData;								
	}while( (iSendData != SOCKET_ERROR) && (iSendLen != SRS_IF_FIX_SZ) );

	if ( iSendData == SOCKET_ERROR )
	{
		iResult = WSAGetLastError();
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Connect: Send error :%d \n"),iResult );
		iRtn = shutdown( ServerSd, 2 );
		closesocket( ServerSd );
		return( -1 );
	}
	
	//==========================================
	// Receive request (common area)
	//==========================================
	for( iRecvBytes = 0, nBytesRecv = 0 ; iRecvBytes < SRS_IF_FIX_SZ ; )
	{
		nBytesRecv = recv( ServerSd, cIfFix, 256, 0 );
		if( nBytesRecv == SOCKET_ERROR)
		{
			nResult = WSAGetLastError();
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Connect: recv error:%d \n"),nResult );
			iRtn = shutdown( ServerSd, 2 );
			closesocket( ServerSd );
			return( -1 );
		}
		iRecvBytes += nBytesRecv;
	}

	//==========================================
	// Receive request (proper area)
	//==========================================
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;
	iReqSize = SRS_IF_FIX_SZ + lpIfFix->IF_iInformationSize;
	LSP_Dbg_Printf( DBG_LEVEL_2,TEXT("SRL_Snd_Connect: Wait for message size=%d request＝%04x \n"),
															iReqSize , lpIfFix->IF_wRequest);
	for( ; iRecvBytes < iReqSize ; )
	{
		nBytesRecv = recv( ServerSd, cIfFix, 256, 0 );
		if( nBytesRecv == SOCKET_ERROR)
		{
			nResult = WSAGetLastError();
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Connect: recv error:%d \n"), nResult);
			iRtn = shutdown( ServerSd, 2 );
			closesocket( ServerSd );
			return( -1 );
		}
		iRecvBytes += nBytesRecv;
	}
	iRtn = shutdown( ServerSd, 2 );
	closesocket( ServerSd );

	//=======================================
	//  Check result of request
	//=======================================
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;
	if( lpIfFix->IF_wResult != IF_CMP_SUCCESS )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Connect: request result %04x\n"),lpIfFix->IF_wResult);
		return( -1 );
	}
	iPort = lpIfFix->IF_iPortNo;					// Save port number
	
	//======================================
	//  Save server data
	//======================================
	lpIfConnect = (struct SRS_IF_CONNECT *)lpIfFix->IF_cInformation;

	// Set max user
	memset( cRegBuff, 0, 16 );
	dwMax = (DWORD)lpIfConnect->IF_CN_wMaxUser;
	iRtn = SRL_Reg_SetInfoDWORD( SRL_REG_KEY_COM, SRL_REG_MAXUSER, dwMax );
	if( iRtn == -1 )
	{
		return( -1 );
	}

	// Set max lobby
	dwMax = (DWORD)lpIfConnect->IF_CN_wMaxLobby;
	iRtn = SRL_Reg_SetInfoDWORD( SRL_REG_KEY_COM, SRL_REG_MAXLOBBY, dwMax );
	if( iRtn == -1 )
	{
		return( -1 );
	}

	// Set max group
	dwMax = (DWORD)lpIfConnect->IF_CN_wMaxGroup;
	iRtn = SRL_Reg_SetInfoDWORD( SRL_REG_KEY_COM, SRL_REG_MAXGROUP, dwMax );
	if( iRtn == -1 )
	{
		return( -1 );
	}

	// Set max game
	dwMax = (DWORD)lpIfConnect->IF_CN_wMaxGame;
	iRtn = SRL_Reg_SetInfoDWORD( SRL_REG_KEY_COM, SRL_REG_MAXGAME, dwMax );
	if( iRtn == -1 )
	{
		return( -1 );
	}
	memcpy( cMsg, lpIfConnect->IF_CN_cMessage, sizeof(lpIfConnect->IF_CN_cMessage) );
	SRL_Reg_SetInfo( SRL_REG_KEY_COM, SRL_REG_KEY_MSG, (LPCTSTR)cMsg );

	//======================================
	//  Init management data
	//======================================
	iRtn = SRL_Mng_Startup( );
	if( iRtn == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Connect: SRL_Mng_Startup error\n"));
		return( -1 );
	}

//===========================================================================
//
//    Run receipt's process
//
//===========================================================================
	//======================================
	// Create process names of run receipt
	//======================================
	memset( cReceiveProc, 0, 256 );
	memcpy( cReceiveProc, LSP_PROC_RCV, sizeof(LSP_PROC_RCV) );
//	memcpy( cReceiveProc, SRL_PROC_RCV, sizeof(SRL_PROC_RCV) );

	//=======================================
	// Run process
	//=======================================
	LSP_Dbg_Printf( DBG_LEVEL_2,TEXT("SRL_Snd_CreateProc %s \n"), (LPCTSTR)cReceiveProc);
	iRtn = SRL_Snd_CreateProc( 1, (LPCTSTR)cReceiveProc );
	if( iRtn == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Connect: SRL_Snd_CreateProc NG %s\n"),
																			cReceiveProc );
		iRtn = SRL_Snd_Disconnect( lpServerIP, iPort );	
		return( -1 );
	}
	LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("SRL_Snd_Connect: return\n"));
	return( iPort );
}

/*=============================================================================
     Function：Send free request
	Input   ：lpServerIP
	 	  iPort
	Output  ：no
	Return  ：True 0
                  False -1

==============================================================================*/
__declspec( dllexport )int __stdcall  SRL_Snd_Disconnect( char *lpServerIP, int iPort )
{
	int		iRtn;
	int 	iResult;							//
	int 	iSendLen;							// Send data's length
	int 	iSendData;							// Send data's length (count)
	struct	SRS_IF_FIX *lpIfFix;				//
	char	cIfFix[256];						//
	char	cBuff[16];

#if 0
	// for select
	struct fd_set *lpReadFds = new struct fd_set;		
	struct timeval *lpSockTime = new struct timeval;	
	struct timeval *lpConnectTime = new struct timeval;	
	struct fd_set *lpWriteFds = new struct fd_set;		
	// for socket
	WORD      wVersionRequested = MAKEWORD(1, 1);		// Request Winsock 1.1
	WSADATA   wsaData;	
	SOCKADDR_IN   ClientAddr;
	SOCKADDR_IN   ServerAddr;
	u_long ulCmdArg = 1;
	SOCKET 	ServerSd;			
#endif

	iRtn = SRL_Snd_Term( );

	iRtn = SRL_Mng_Shutdown( );
	/*==================================*/
	/* Init socket                     */
	/*==================================*/
	if( iPort == 0 )
	{
		return( 0 );
	}
	iResult = WSAStartup( wVersionRequested, &wsaData );
	if ( iResult != 0 )
	{
		iResult = WSAGetLastError();
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Disconnect: WSAStartup error:%d \n"), iResult);
		return( -1 );
	}

	ServerSd = socket( AF_INET, SOCK_STREAM, 0 );	//Create socket of server
	if( ServerSd == INVALID_SOCKET )
	{
		iResult = WSAGetLastError();
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Disconnect: socket error:%d \n"),iResult );
		return( -1 );
	}

	/*==================================*/
	/* Bluid up session	            */
	/*==================================*/
	// Save client address data to address structure
	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_port = 0;
	ClientAddr.sin_addr.s_addr = htonl(INADDR_ANY);	

	// Save server address data to address structure
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(SRS_PORT_SERVER);		
	ServerAddr.sin_addr.s_addr = inet_addr( lpServerIP );	

	//　Bluid up connection　
	LSP_Dbg_Printf( DBG_LEVEL_2,TEXT( "SRL_Snd_Disconnect: connect\n" ));
	iResult = connect( ServerSd, (LPSOCKADDR)&ServerAddr, sizeof(ServerAddr) );
	if( iResult == SOCKET_ERROR )
	{
		iResult = WSAGetLastError();	
		if( iResult == WSAEWOULDBLOCK )
		{
			FD_ZERO(lpWriteFds);
			FD_SET(ServerSd, lpWriteFds);

			// watch select
			lpConnectTime->tv_sec = 10;
			lpConnectTime->tv_usec = 0;

			LSP_Dbg_Printf( DBG_LEVEL_2,TEXT( "SRL_Snd_Disconnect: select\n" ));
			iResult = select(0, NULL, lpWriteFds, NULL, lpConnectTime);

			//　Timeout or Error
			if( (iResult == 0) || (iResult == SOCKET_ERROR) )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Disconnect: select error %d \n"), iResult);
				iResult = shutdown( ServerSd, 2 );
				iResult = closesocket(ServerSd);
				return( -1 );
			}
		}
		else
		{
			// error except block
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Disconnect: connect error %d \n"), iResult);
			iResult = shutdown( ServerSd, 2 );
			iResult = closesocket(ServerSd);
			return( -1 );
		}
	}

	/*==================================*/
	/* Send free request                */
	/*==================================*/
	//　Create request
	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;
	lpIfFix->IF_wRequest = IF_REQ_DISCONNECT;
	lpIfFix->IF_iInformationSize = 0;
	lpIfFix->IF_iPortNo = iPort;

	//  Send request
	iSendLen = 0;
	do
	{
		iSendData = send( ServerSd, (char*)cIfFix, SRS_IF_FIX_SZ, 0 );
		iSendLen += iSendData;								
	}while( (iSendData != SOCKET_ERROR) && (iSendLen != SRS_IF_FIX_SZ) );

	if ( iSendData == SOCKET_ERROR )
	{
		iResult = WSAGetLastError();
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Disconnect: Send error :%d \n"), iResult);
		iResult = shutdown( ServerSd, 2 );
		closesocket( ServerSd );
		return( -1 );
	}

	/*==================================*/
	/* Check request                    */
	/*==================================*/
	iResult = recv( ServerSd, cBuff, 16, 0 );
	iResult = shutdown( ServerSd, 2 );
	closesocket( ServerSd );
	LSP_Dbg_Printf( DBG_LEVEL_1,TEXT( "SRL_Snd_Disconnect: return\n" ));

	return( 0 );
}

/*=============================================================================
     Function：Create process
	 Input   ：iMode
		   0
		   1
		   lpstrCommandLine
	Output  ：no
	Return  ：True 0
                  False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Snd_CreateProc( int iMode, LPCTSTR lpCommandLine )
{

	BOOL    cprc;

    PROCESS_INFORMATION ProcInfo;
	DWORD	dwExitCode;
	DWORD	dwRtn;
	//
	// プロセス生成（起動）
	//
	//
	//  起動情報設定
	//
    cprc = CreateProcess( (LPCTSTR)lpCommandLine,
                		  (LPCTSTR)lpCommandLine,
                          NULL,
                          NULL,
                          FALSE,
                          0,
                          NULL,
                          NULL,
                          NULL,
                          &ProcInfo );
    if ( cprc == TRUE )
	{
		if( iMode == 0 )
    	{
			//
			// Wait finish
			//
			dwExitCode = STILL_ACTIVE;
			while( dwExitCode == STILL_ACTIVE )
			{
   				WaitForSingleObject( ProcInfo.hProcess, INFINITE );
				GetExitCodeProcess( ProcInfo.hProcess, &dwExitCode );
				if( dwExitCode != 0 )
				{
			    	return( -1 );
				}
			}
		}
		return( 0 );
    }
	dwRtn = GetLastError();
	LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_CreateProc : error %d \n"), dwRtn);
    return( -1 );
}
/*=============================================================================
     Function：Send request
	 Input   ：lpServerIP
	 	   iPort
		   lpSendData
		   szSendSize   
	Output  ：no
	Return  ：True 0
                  False -1
==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Snd_Request( char *lpServerIP, int iPort, char *lpSendData, size_t szSendSize )
{
	LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("###### SRL_Snd_Request: start \n"));
	LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("###### SRL_Snd_Request: used port %d\n"), iPort);
	
	int 	iResult;						//
	int 	iSendLen;						// 
	int 	iSendData;						// 
	char	cDummyBuff[16];					// 

#if 0
	// for select   
	struct fd_set *lpReadFds = new struct fd_set;		//
	struct timeval *lpSockTime = new struct timeval;	//
	struct timeval *lpConnectTime = new struct timeval;	//
	struct fd_set *lpWriteFds = new struct fd_set;		//
	// for socket
	WORD      wVersionRequested = MAKEWORD(1, 1);		// request Winsock 1.1
	WSADATA   wsaData;									// 
	SOCKADDR_IN   ClientAddr;							//
	SOCKADDR_IN   ServerAddr;							//
	u_long ulCmdArg = 1;								//
	SOCKET	ServerSd;						//
#endif

	//==========================================
	// Build up new connection
	//==========================================
	LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("###### SRL_Snd_Request: start used port %d\n"), iPort);

	/*==================================*/
	/* Init socket                     */
	/*==================================*/
	iResult = WSAStartup( wVersionRequested, &wsaData );
	if ( iResult != 0 )
	{
		iResult = WSAGetLastError();
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Request: WSAStartup error:%d \n"), iResult);
		return( -1 );
	}

	ServerSd = socket( AF_INET, SOCK_STREAM, 0 );
	if( ServerSd == INVALID_SOCKET )
	{
		iResult = WSAGetLastError();
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Request: socket error:%d \n"),iResult );
		return( -1 );
	}

	/*==================================*/
	/* Build up session 		    */
	/*==================================*/
	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_port = 0;							
	ClientAddr.sin_addr.s_addr = htonl(INADDR_ANY);	

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons( iPort );		
	ServerAddr.sin_addr.s_addr = inet_addr( lpServerIP );	

	//　Build up connection　
	LSP_Dbg_Printf( DBG_LEVEL_2,TEXT( "SRL_Snd_Request : connect\n" ));
	iResult = connect( ServerSd, (LPSOCKADDR)&ServerAddr, sizeof(ServerAddr) );
	if( iResult == SOCKET_ERROR )
	{
		iResult = WSAGetLastError();
		if( iResult == WSAEWOULDBLOCK )
		{
			FD_ZERO(lpWriteFds);
			FD_SET(ServerSd, lpWriteFds);

			// Watch select
			lpConnectTime->tv_sec = 10;
			lpConnectTime->tv_usec = 0;

			LSP_Dbg_Printf( DBG_LEVEL_2,TEXT("SRL_Snd_Request: select wait=%ds \n"),
																		 lpConnectTime->tv_sec);
			iResult = select(0, NULL, lpWriteFds, NULL, lpConnectTime);

			//　timeout or Error
			if( (iResult == 0) || (iResult == SOCKET_ERROR) )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Request: select error %d \n"), iResult);
				iResult = shutdown( ServerSd, 2 );
				iResult = closesocket(ServerSd);
				return( -1 );
			}
		}
		else
		{
			// Error except of block
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Request: connect error %d \n"), iResult);
			iResult = shutdown( ServerSd, 2 );
			iResult = closesocket(ServerSd);
			return( -1 );
		}
	}
	/*==================================*/
	/* Send request			    */
	/*==================================*/
	LSP_Dbg_Printf( DBG_LEVEL_2,TEXT( "SRL_Snd_Request : Send request\n" ));
	for( iSendLen = 0 ; iSendLen < (int)szSendSize ; )
	{
		iSendData = send( ServerSd, (char*)lpSendData, szSendSize, 0 );
		if ( iSendData == SOCKET_ERROR )
		{
			iResult = WSAGetLastError();
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Request: Send error :%d \n"), iResult);
			iResult = shutdown( ServerSd, 2 );
			closesocket( ServerSd );
			return( -1 );
		}
		iSendLen += iSendData;
	}
	/*==================================*/
	/* Check request      			*/
	/*==================================*/
	LSP_Dbg_Printf( DBG_LEVEL_2,TEXT( "SRL_Snd_Request: Wait for request\n") );
	iResult = recv( ServerSd, cDummyBuff, 16, 0 );
	iResult = shutdown( ServerSd, 2 );
	closesocket( ServerSd );
	LSP_Dbg_Printf( DBG_LEVEL_1,TEXT( "SRL_Snd_Request: return\n" ));
	return( 0 );
}

/*=============================================================================
     Function：Lobby client finish recieved process
	Input   ：no
	Output  ：no
	Return  ：True 0
                  False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Snd_Term( void )
{
	int 	iResult;							//
	int 	iSendLen; 
	int 	iSendData;	
	struct	SRS_IF_FIX *lpIfFix;				//
    PHOSTENT lphostent;     					// 
	char	cIfFix[256];						//
	char	cClientName[32];	
	char	cMsg[256];
#if 0
	// for select
	struct fd_set *lpReadFds = new struct fd_set;		
	struct timeval *lpSockTime = new struct timeval;	
	struct timeval *lpConnectTime = new struct timeval;	
	struct fd_set *lpWriteFds = new struct fd_set;		
	// for socket
	WORD      wVersionRequested = MAKEWORD(1, 1);		// Request Winsock 1.1
	WSADATA   wsaData;
	SOCKADDR_IN   ClientAddr;
	SOCKADDR_IN   ServerAddr;
	u_long ulCmdArg = 1;
	SOCKET	ServerSd;			
#endif
	/*==================================*/
	/* Init socket                     */
	/*==================================*/
	iResult = WSAStartup( wVersionRequested, &wsaData );
	if ( iResult != 0 )
	{
		iResult = WSAGetLastError();
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Term : WSAStartup error:%d \n"), iResult);
		return( -1 );
	}

	ServerSd = socket( AF_INET, SOCK_STREAM, 0 );	
	if( ServerSd == INVALID_SOCKET )
	{
		iResult = WSAGetLastError();
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Term : socket error:%d \n"),iResult );
		return( -1 );
	}

	/*==================================*/
	/* Build up session		    */
	/*==================================*/
	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_port = 0;
	ClientAddr.sin_addr.s_addr = htonl(INADDR_ANY);	

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(SRS_PORT_CLIENT);
    gethostname( cClientName, sizeof(cClientName) );
    lphostent = gethostbyname(cClientName);
    memcpy( (char *)&ServerAddr.sin_addr.s_addr, *lphostent->h_addr_list, 4);

	//　Build up connection　
	iResult = connect( ServerSd, (LPSOCKADDR)&ServerAddr, sizeof(ServerAddr) );
	if( iResult == SOCKET_ERROR )
	{
		iResult = WSAGetLastError();			//
		if( iResult == WSAEWOULDBLOCK )			
		{
			FD_ZERO(lpWriteFds);				
			FD_SET(ServerSd, lpWriteFds);	

			// Watch select
			lpConnectTime->tv_sec = 60;
			lpConnectTime->tv_usec = 0;

			LSP_Dbg_Printf( DBG_LEVEL_1,TEXT( "SRL_Snd_Term : select\n") );
			iResult = select(0, NULL, lpWriteFds, NULL, lpConnectTime);

			//　timeout or Error
			if( (iResult == 0) || (iResult == SOCKET_ERROR) )
			{
				LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Term : select error %d \n"), iResult);
				iResult = shutdown( ServerSd, 2 );
				iResult = closesocket(ServerSd);
				return( -1 );
			}
		}
		else
		{
			// Error except block
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Term : connect error %d \n"), iResult);
			iResult = shutdown( ServerSd, 2 );
			iResult = closesocket(ServerSd);
			return( -1 );
		}
	}

	/*==================================*/
	/* Send Request				  			*/
	/*==================================*/
	//　Create Request
	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;
	lpIfFix->IF_wRequest = IF_REQ_TERMINATE;
	lpIfFix->IF_iInformationSize = 0;

	//  Send Request
	iSendLen = 0;
	do
	{
		iSendData = send( ServerSd, (char*)cIfFix, SRS_IF_FIX_SZ, 0 );
		iSendLen += iSendData;								
	}while( (iSendData != SOCKET_ERROR) && (iSendLen != SRS_IF_FIX_SZ) );

	if ( iSendData == SOCKET_ERROR )
	{
		iResult = WSAGetLastError();
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Snd_Term : Send error :%d \n"), iResult);
		iResult = shutdown( ServerSd, 2 );
		closesocket( ServerSd );
		return( -1 );
	}
	/*==================================*/
	/* Check result			    */
	/*==================================*/
	LSP_Dbg_Printf( DBG_LEVEL_1,TEXT( "SRL_Snd_Term : Wait for disconnect request\n") );
	iResult = recv( ServerSd, cMsg, 16, 0 );
	LSP_Dbg_Printf( DBG_LEVEL_1,TEXT( "SRL_Snd_Term : Disconnect request arrived\n") );

	iResult = shutdown( ServerSd, 2 );
	closesocket( ServerSd );

	LSP_Dbg_Printf( DBG_LEVEL_1,TEXT( "SRL_Snd_Term OK\n" ));

	return( 0 );
}