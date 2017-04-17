/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRLreceive.cpp
 *
 *  Content:    Lobby client process request
 *
 ***************************************************************************/
/*================================
    INCLUDE
==================================*/
#include <windows.h>
#include <winsock.h>

// include of DLPAY
#include "dplay.h"		// defined return code (DP_,DPERR_)
#include "lobbysp.h"	// defined structer (LPSPDATA_xxxxxxx)

// include of LOBBY-SP
#include "LSPdebug.h"

// include of original functions 
#include "SRScom.h"
#include "SRLregistry.h"
#include "SRLmanage.h"

void SRL_Rcv_SysMessage( LPSRS_IFFIX lpIfFix );
/*================================
    global area
==================================*/
SOCKET 	AcceptClientSd = 0;	
SOCKET 	ClientSd = 0;

/*=============================================================================
     Function: Wait request to receive
     Input   ：no
     Output  ：no
     Return  ：True 0
               False -1

==============================================================================*/
int WINAPI WinMain( HINSTANCE hInstanc,HINSTANCE hPrevInstanc,
					LPWSTR lpszCmdLin,int nCmdSho )
{
	SOCKADDR_IN addr;
	SOCKADDR_IN clientAddr;						//
	IN_ADDR clientIn;							//
	int 	nClientAddrLen;						//					
	
	WORD 	wVersionRequested = MAKEWORD(1, 1);	// request Winsock 1.1
	WSADATA wsaData;							// Winsock data
	int 	nBytesRecv;
	int 	iRecvBytes;
	int 	nResult;
	int		iLoopOut;							//
	int		iReqSize;							//
	int		iRtn;								//
	int		iRcvSize;							//
	int		iOpt;
	struct 	SRS_IF_FIX	*lpIfFix;				//
	struct 	SRS_IF_MESSAGE	*lpIfMessage;		//
	char	*lpRcvData;							//
	char	*lpRenewal;							// 
	char	cWait[8];
	char	cIfFix[32768];						// intereface area

	//=================================
	// init management information
	//=================================
	LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("SRLreceive start\n"));
	iRtn = SRL_Mng_Startup( );
	if( iRtn == -1 )
	{
		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("SRLreceive : SRL_Mng_Startup error\n"));
		return( -1 );
	}
	//=================================
	// init socket
	//=================================
	if( WSAStartup( wVersionRequested, &wsaData ) != 0 ) 
	{
		nResult = WSAGetLastError();
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive main : WSAStartup error:%d \n"),nResult );

		//  event notice
//		memset( (char *)&cEventMng, 0, SRLEVENTMNG_SZ );
//		cEventMng.EM_dwEventID = SRLERROR_COMERROR;		
//		iRtn = SRL_Evt_SetEvent( SRL_EVENTMODE_ERROR, (LPSRLEVENTMNG)&cEventMng );
		return( -1 );
	}

	//=================================
	//　create socket
	//=================================
	AcceptClientSd = socket( AF_INET, SOCK_STREAM, 0 );
	
	if( AcceptClientSd == INVALID_SOCKET )	
	{
		nResult = WSAGetLastError();
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive main : socket error %d \n"),nResult );

		// event notice
//		memset( (char *)&cEventMng, 0, SRLEVENTMNG_SZ );
//		cEventMng.EM_dwEventID = SRLERROR_COMERROR;		
//		iRtn = SRL_Evt_SetEvent( SRL_EVENTMODE_ERROR, (LPSRLEVENTMNG)&cEventMng );
		return( -1 );
	}
	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("SRLreceive : socket %08x\n"),AcceptClientSd );

	addr.sin_family = AF_INET;
	addr.sin_port = htons( SRS_PORT_CLIENT );
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	//=================================
	//　Set socket option
	//=================================
	LINGER	ling;								//
	ling.l_onoff = -1;							// 
	ling.l_linger = 0;							//
	setsockopt( AcceptClientSd, SOL_SOCKET, SO_LINGER, (LPSTR)&ling, sizeof(ling) );
	iOpt = 1;
	setsockopt( AcceptClientSd, SOL_SOCKET, SO_REUSEADDR, (LPSTR)&iOpt, sizeof(int) );

	//===================================
	// Bind socket 
	//===================================
	nResult = bind( AcceptClientSd, (LPSOCKADDR)&addr, sizeof(addr) );
	if(  nResult == SOCKET_ERROR )
	{
		nResult = WSAGetLastError();
		if( nResult != WSAEADDRINUSE )
		{
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive main: bind error:%d \n"),nResult );
			shutdown( AcceptClientSd, 2 );
			iRtn = closesocket( AcceptClientSd );
			if( iRtn != 0 )
			{
				nResult = WSAGetLastError();
				LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive main: closesoket error:%d \n"),nResult);
			}
			// event notice
//			memset( (char *)&cEventMng, 0, SRLEVENTMNG_SZ );
//			cEventMng.EM_dwEventID = SRLERROR_COMERROR;	
//			iRtn = SRL_Evt_SetEvent( SRL_EVENTMODE_ERROR, (LPSRLEVENTMNG)&cEventMng );
			return( -1 );
		}
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive main: bind WSAEADDRINUSE\n"),nResult );
	}
	//===================================
	//　Listen for connent 
	//===================================
	nResult = listen( AcceptClientSd , 5 );	
	if( nResult == SOCKET_ERROR )
	{
		nResult = WSAGetLastError();
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive main: listen error %d \n"),nResult );
		shutdown( AcceptClientSd, 2 );
		closesocket( AcceptClientSd );
		if( iRtn != 0 )
		{
			nResult = WSAGetLastError();
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive main: closesoket error:%d \n"),nResult );
		}

		//イベント通知
//		memset( (char *)&cEventMng, 0, SRLEVENTMNG_SZ );
//		cEventMng.EM_dwEventID = SRLERROR_COMERROR;
//		iRtn = SRL_Evt_SetEvent( SRL_EVENTMODE_ERROR, (LPSRLEVENTMNG)&cEventMng );
		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("SRLreceive : abend\n") );
		return( -1 );
	}
	//==========================================================================
	//
	//	Wait request
	//
	//==========================================================================
	for( iLoopOut = 0 ; iLoopOut == 0 ; )
	{
		nClientAddrLen = sizeof( clientAddr );
		//==========================================
		// waite to build to connention for client receive
		//==========================================
		LSP_Dbg_Printf( DBG_LEVEL_2, TEXT("SRLreceive: accept\n") );
		ClientSd = accept( AcceptClientSd, (LPSOCKADDR)&clientAddr, &nClientAddrLen );
		if( ClientSd == INVALID_SOCKET )
		{
			nResult = WSAGetLastError();
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive main: accept error:%d \n"),nResult );
			shutdown( AcceptClientSd, 2 );
			iRtn = closesocket( AcceptClientSd );
			if( iRtn != 0 )
			{
				nResult = WSAGetLastError();
				LSP_Dbg_Printf(DBG_LEVEL_0,TEXT("SRLreceive main: closesoket error:%d \n"),nResult);
			}
            // event notice
//			memset( (char *)&cEventMng, 0, SRLEVENTMNG_SZ );
//			cEventMng.EM_dwEventID = SRLERROR_COMERROR;
//			iRtn = SRL_Evt_SetEvent( SRL_EVENTMODE_ERROR, (LPSRLEVENTMNG)&cEventMng );
			LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("SRLreceive : abend\n") );
			return( -1 );
		}

		// Copy from IP address of 4byte to IP address structure
 		memcpy( &clientIn, &clientAddr.sin_addr.s_addr, 4 );

		//==========================================
		// Receive request (common area)
		//==========================================
		memset( cIfFix, 0, sizeof(cIfFix) );
		for( iRecvBytes = 0, nBytesRecv = 0 ; iRecvBytes < SRS_IF_FIX_SZ ; )
		{
			nBytesRecv = recv( ClientSd, cIfFix, sizeof(cIfFix), 0 );
			if( nBytesRecv == SOCKET_ERROR)
			{
				nResult = WSAGetLastError();
				LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive : recv error:%d \n"),nResult );

                // event notice
//				memset( (char *)&cEventMng, 0, SRLEVENTMNG_SZ );
//				cEventMng.EM_dwEventID = SRLERROR_COMERROR;
//				iRtn = SRL_Evt_SetEvent( SRL_EVENTMODE_ERROR, (LPSRLEVENTMNG)&cEventMng );
				shutdown( AcceptClientSd, 2 );
				iRtn = closesocket( ClientSd );
				if( iRtn != 0 )
				{
					nResult = WSAGetLastError();
					LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive main: closesoket error:%d ClientSD\n"),nResult );
				}
				shutdown( AcceptClientSd, 2 );
				iRtn = closesocket( AcceptClientSd );
				if( iRtn != 0 )
				{
					nResult = WSAGetLastError();
					LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive main: closesoket error:%d \n"),nResult);
				}
				LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("SRLreceive : abend") );
				return( -1 );
			}
			iRecvBytes += nBytesRecv;

			LSP_Dbg_Printf( DBG_LEVEL_2,TEXT("SRLreceive : Common data Recv %d bytes \n"),iRecvBytes );
		}
		//==========================================
		//  Receive request (proper area)
		//==========================================
		lpIfFix = (struct SRS_IF_FIX *)cIfFix;
		iReqSize = SRS_IF_FIX_SZ + lpIfFix->IF_iInformationSize;
		LSP_Dbg_Printf( DBG_LEVEL_2,TEXT("SRLreceive : request size=%d request＝%04x \n"),
																iReqSize , lpIfFix->IF_wRequest);
		
		for( ; ; )
		{
			iRcvSize = iReqSize - iRecvBytes;	
			LSP_Dbg_Printf( DBG_LEVEL_2,TEXT("SRLreceive : Wait for message data  remained %d Bytes \n"),
																						iRcvSize );
			
			if( iRcvSize <= 0 )
			{
				break;
			}
			lpRcvData = &cIfFix[iRecvBytes];
			nBytesRecv = recv( ClientSd, lpRcvData, iRcvSize, 0 );
			if( nBytesRecv == SOCKET_ERROR)
			{
				nResult = WSAGetLastError();
				LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive : recv error:%d \n"),nResult );

                // event notice
//				memset( (char *)&cEventMng, 0, SRLEVENTMNG_SZ );
//				cEventMng.EM_dwEventID = SRLERROR_COMERROR;
//				iRtn = SRL_Evt_SetEvent( SRL_EVENTMODE_ERROR, (LPSRLEVENTMNG)&cEventMng );

				shutdown( ClientSd, 2 );
				iRtn = closesocket( ClientSd );
				if( iRtn != 0 )
				{
					nResult = WSAGetLastError();
					LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive main: closesoket error:%d ClientSD\n"),nResult );
				}

				shutdown( AcceptClientSd, 2 );
				iRtn = closesocket( AcceptClientSd );
				if( iRtn != 0 )
				{
					nResult = WSAGetLastError();
					LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive main: closesoket error:%d \n"),nResult);
				}

				return( -1 );
			}
			iRecvBytes += nBytesRecv;

			LSP_Dbg_Printf( DBG_LEVEL_2,TEXT("SRLreceive : Recv %d bytes \n"),nBytesRecv );
		}

		//===================================================
		//  Check result of request
		//===================================================
		LSP_Dbg_Printf( DBG_LEVEL_2,TEXT("SRLreceive : Request %04x \n"),lpIfFix->IF_wRequest );
		switch( lpIfFix->IF_wRequest )
		{
			//==================================
			// Receive response to register user
			//==================================
			case	IF_REQ_USER_ENTRY	:
						LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("SRLreceive: USER_ENTRY anser\n"));
						shutdown( ClientSd, 2 );
						iRtn = closesocket( ClientSd );
						if( iRtn != 0 )
						{
							nResult = WSAGetLastError();
							LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive: closesoket error:%d ClientSD\n"),nResult );
						}
						if( lpIfFix->IF_wResult == IF_CMP_SUCCESS )
						{
							lpRenewal = (char *)lpIfFix->IF_cInformation;
							iRtn = SRL_Mng_Renewal( lpRenewal );	
							//

							if( SRL_Reg_SetInfo( SRL_REG_KEY_USER,SRL_REG_STATUS,SRL_REG_USER_ON ) == -1 )
							{
								LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive: SRL_Reg_SetInfo error %s %s\n"),SRL_REG_KEY_USER,SRL_REG_STATUS );
							}
							//
							if( SRL_Reg_SetInfo(SRL_REG_KEY_WAIT,SRL_REG_USERENTRY,SRL_REG_WAIT_OK)
        	                    	== -1 )
							{
									LSP_Dbg_Printf( DBG_LEVEL_0,
                                                TEXT("SRLreceive: SRL_Reg_SetInfo error %s %s\n"),
                                                SRL_REG_KEY_WAIT, SRL_REG_USERENTRY );
							}
							memset(cWait,0,sizeof(cWait));

							if( SRL_Reg_GetInfo( SRL_REG_KEY_WAIT, SRL_REG_USERENTRY, (LPCTSTR)cWait ) == -1 )
							{
									LSP_Dbg_Printf( DBG_LEVEL_0,
                                                TEXT("SRLreceive: SRL_Reg_GetInfo error %s %s\n"),
                                                SRL_REG_KEY_WAIT, SRL_REG_USERENTRY );
							}
							LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive: SRL_Reg_SetInfo Reg read Success SRL_REG_USERENTRY read cWait=%s \n"),cWait);

							// message notice
							SRL_Rcv_SysMessage( lpIfFix ); 
						}
						else
						{
							LSP_Dbg_Printf( DBG_LEVEL_0,
											TEXT("SRLreceive: USER_ENTRY anser error %04x\n"),
											lpIfFix->IF_wResult );
							
							if(SRL_Reg_SetInfo(SRL_REG_KEY_WAIT,SRL_REG_USERENTRY,SRL_REG_WAIT_NG)
        	                    == -1 )
							{
								LSP_Dbg_Printf( DBG_LEVEL_0,
                    	                        TEXT("SRLreceive: SRL_Reg_SetInfo error %s %s\n"),
                                                SRL_REG_KEY_WAIT, SRL_REG_USERENTRY );
							}
						}
						break;
			//==================================
			// Delete user Receive response
			//==================================
			case	IF_REQ_USER_DELETE	:	
						LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("SRLreceive: USER_DELETE anser\n") );
						shutdown( ClientSd, 2 );
						iRtn = closesocket( ClientSd );
						if( iRtn != 0 )
						{
							nResult = WSAGetLastError();
							LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive: closesoket error:%d ClientSD\n"),nResult );
						}
						if( lpIfFix->IF_wResult == IF_CMP_SUCCESS )
						{
							lpRenewal = (char *)lpIfFix->IF_cInformation;
							iRtn = SRL_Mng_Renewal( lpRenewal );
							

							iRtn = SRL_Reg_SetInfo(SRL_REG_KEY_USER,SRL_REG_STATUS,SRL_REG_USER_OFF);
							if(SRL_Reg_SetInfo(SRL_REG_KEY_WAIT,SRL_REG_USERDELETE,SRL_REG_WAIT_OK)
        	                    	== -1 )
							{
								LSP_Dbg_Printf( DBG_LEVEL_0,
                                                TEXT("SRLreceive: SRL_Reg_SetInfo error %s %s\n"),
                                                SRL_REG_KEY_WAIT, SRL_REG_USERDELETE );
							}

							SRL_Rcv_SysMessage( lpIfFix ); 
						}
						else
						{
							LSP_Dbg_Printf( DBG_LEVEL_0,
                                            TEXT("SRLreceive: USER_DELETE anser error %04x\n"),
                                            lpIfFix->IF_wResult );
							if(SRL_Reg_SetInfo(SRL_REG_KEY_WAIT,SRL_REG_USERDELETE,SRL_REG_WAIT_NG)
        	                    	== -1 )
							{
								LSP_Dbg_Printf( DBG_LEVEL_0,
                                                TEXT("SRLreceive: SRL_Reg_SetInfo error %s %s\n"),
                                                SRL_REG_KEY_WAIT, SRL_REG_USERDELETE );
							}
						}
						break;

			//==================================
			// Entry lobby Receive response
			//==================================
			case	IF_REQ_LOBBY_ENTRY	:	
						LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("SRLreceive: LOBBY_ENTRY anser\n") );
						shutdown( ClientSd, 2 );
						closesocket( ClientSd );

						if( lpIfFix->IF_wResult == IF_CMP_SUCCESS )
						{
							lpRenewal = (char *)lpIfFix->IF_cInformation;
							iRtn = SRL_Mng_Renewal( lpRenewal );
						}
						else
						{
							LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("SRLreceive: LOBBY_ENTRY anser error %04x\n"),lpIfFix->IF_wResult );
						}
						break;

			//==================================
			// Leave lobby Receive response
			//==================================
			case	IF_REQ_LOBBY_DEFECT	:	
						LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("SRLreceive: LOBBY_DEFECT anser\n") );
						shutdown( ClientSd, 2 );
						closesocket( ClientSd );

						if( lpIfFix->IF_wResult == IF_CMP_SUCCESS )
						{
							lpRenewal = (char *)lpIfFix->IF_cInformation;
							iRtn = SRL_Mng_Renewal( lpRenewal );	// 更新情報反映
						}
						else
						{
							LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("SRLreceive: LOBBY_DEFECT anser error %04x\n"),lpIfFix->IF_wResult );
						}
						break;

			//==================================
			// Create group  Receive response
			//==================================
			case	IF_REQ_GROUP_MAKE	:	
						LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("SRLreceive: GROUP_MAKE anser\n") );
						shutdown( ClientSd, 2 );
						closesocket( ClientSd );

						if( lpIfFix->IF_wResult == IF_CMP_SUCCESS )
						{
							lpRenewal = (char *)lpIfFix->IF_cInformation;
							iRtn = SRL_Mng_Renewal( lpRenewal );
							

							if(SRL_Reg_SetInfo(SRL_REG_KEY_WAIT,SRL_REG_GROUPMAKE,SRL_REG_WAIT_OK)
        	                    	== -1 )
							{
								LSP_Dbg_Printf( DBG_LEVEL_0,
                                                TEXT("SRLreceive: SRL_Reg_SetInfo error %s %s\n"),
                                                SRL_REG_KEY_WAIT, SRL_REG_GROUPMAKE );
							}

							SRL_Rcv_SysMessage( lpIfFix ); 
						}
						else
						{
							LSP_Dbg_Printf( DBG_LEVEL_0,
											TEXT("SRLreceive: GROUP_MAKE anser error %04x\n"),
											lpIfFix->IF_wResult );

							if(SRL_Reg_SetInfo(SRL_REG_KEY_WAIT,SRL_REG_GROUPMAKE,SRL_REG_WAIT_NG)
        	                    	== -1 )
							{
								LSP_Dbg_Printf( DBG_LEVEL_0,
                                                TEXT("SRLreceive: SRL_Reg_SetInfo error %s %s\n"),
                                                SRL_REG_KEY_WAIT, SRL_REG_GROUPMAKE );
							}
						}
						break;

			//==================================
			// Entry group   Receive response
			//==================================
			case	IF_REQ_GROUP_JOIN	:	
						LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("SRLreceive: GROUP_JOIN anser\n") );
						shutdown( ClientSd, 2 );
						closesocket( ClientSd );

						if( lpIfFix->IF_wResult == IF_CMP_SUCCESS )
						{
							lpRenewal = (char *)lpIfFix->IF_cInformation;
							iRtn = SRL_Mng_Renewal( lpRenewal );

							if(SRL_Reg_SetInfo(SRL_REG_KEY_WAIT,SRL_REG_GROUPJOIN,SRL_REG_WAIT_OK)
        	                    	== -1 )
							{
								LSP_Dbg_Printf( DBG_LEVEL_0,
                                                TEXT("SRLreceive: SRL_Reg_SetInfo error %s %s\n"),
                                                SRL_REG_KEY_WAIT, SRL_REG_GROUPJOIN );
							}

							SRL_Rcv_SysMessage( lpIfFix ); 
						}
						else
						{
							LSP_Dbg_Printf( DBG_LEVEL_0,
											TEXT("SRLreceive: GROUP_JOIN anser error %04x\n"),
											lpIfFix->IF_wResult );
							//
							if(SRL_Reg_SetInfo(SRL_REG_KEY_WAIT,SRL_REG_GROUPJOIN,SRL_REG_WAIT_NG)
        	                    	== -1 )
							{
								LSP_Dbg_Printf( DBG_LEVEL_0,
                                                TEXT("SRLreceive: SRL_Reg_SetInfo error %s %s\n"),
                                                SRL_REG_KEY_WAIT, SRL_REG_GROUPJOIN );
							}
						}
						break;

			//==================================
			// Leave group   Receive response
			//==================================
			case	IF_REQ_GROUP_DEFECT	:	
						LSP_Dbg_Printf( DBG_LEVEL_1,
										TEXT("SRLreceive: GROUP_DEFECT anser\n") );
						shutdown( ClientSd, 2 );
						closesocket( ClientSd );

						if( lpIfFix->IF_wResult == IF_CMP_SUCCESS )
						{
							lpRenewal = (char *)lpIfFix->IF_cInformation;
							iRtn = SRL_Mng_Renewal( lpRenewal );
							

							if( SRL_Reg_SetInfo( SRL_REG_KEY_WAIT, SRL_REG_GROUPDEFECT,
                                         								 SRL_REG_WAIT_OK ) == -1 )
							{
								LSP_Dbg_Printf( DBG_LEVEL_0,
                                                TEXT("SRLreceive: SRL_Reg_SetInfo error %s %s\n"),
                                                SRL_REG_KEY_WAIT, SRL_REG_GROUPDEFECT );
							}

							SRL_Rcv_SysMessage( lpIfFix ); 
						}
						else
						{
							LSP_Dbg_Printf( DBG_LEVEL_0, 
											TEXT("SRLreceive: GROUP_DEFECT anser error %04x\n"),
											lpIfFix->IF_wResult );

							if(SRL_Reg_SetInfo(SRL_REG_KEY_WAIT,SRL_REG_GROUPDEFECT,SRL_REG_WAIT_NG)
        	                    	== -1 )
							{
								LSP_Dbg_Printf( DBG_LEVEL_0,
                                                TEXT("SRLreceive: SRL_Reg_SetInfo error %s %s\n"),
                                                SRL_REG_KEY_WAIT, SRL_REG_GROUPDEFECT );
							}
						}
						break;

			//==================================
			// Receive message
			//==================================
			case	IF_REQ_SENDMSG		:	
						LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("SRLreceive: SENDMSG accept\n") );
						shutdown( ClientSd, 2 );
						closesocket( ClientSd );
						lpIfFix = (struct SRS_IF_FIX *)cIfFix;               
						if( lpIfFix->IF_wResult == IF_CMP_SUCCESS )
						{
							lpIfMessage = (struct SRS_IF_MESSAGE *)lpIfFix->IF_cInformation;
							LSP_Dbg_Printf( DBG_LEVEL_1,
											TEXT("SRLreceive: SEND_MESSAGE anser error %04x\n"),
											lpIfFix->IF_wResult );

							SRL_Rcv_SysMessage( lpIfFix ); 
						}
						else
						{
							LSP_Dbg_Printf( DBG_LEVEL_1,
											TEXT("SRLreceive: SEND_MESSAGE anser error %04x\n"),
											lpIfFix->IF_wResult );
						}
						break;

			//==================================
			// Receive request renewal
			//==================================
			case	IF_REQ_RENEWAL		:	
						LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("SRLreceive: RENEWAL accept\n") );
						shutdown( ClientSd, 2 );
						closesocket( ClientSd );
						lpRenewal = (char *)lpIfFix->IF_cInformation;
						iRtn = SRL_Mng_Renewal( lpRenewal );
						break;

			//==================================
			// Reference of all information  Receive response  
			//==================================
			case	IF_REQ_ALL			:	
						LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("SRLreceive: GETALL anser\n") );
						shutdown( ClientSd, 2 );
						closesocket( ClientSd );
				
						if( lpIfFix->IF_wResult == IF_CMP_SUCCESS )
						{
							lpRenewal = (char *)lpIfFix->IF_cInformation;
							iRtn = SRL_Mng_Renewal( lpRenewal );
							
							if( SRL_Reg_SetInfo(SRL_REG_KEY_WAIT,SRL_REG_ALLGET,SRL_REG_WAIT_OK)
        	                    	== -1 )
							{
									LSP_Dbg_Printf( DBG_LEVEL_0,
                                                TEXT("SRLreceive: SRL_Reg_SetInfo error %s %s\n"),
                                                SRL_REG_KEY_WAIT, SRL_REG_ALLGET );
							}
						}
						else
						{
							LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("SRLreceive: REQ_ALL anser error %04x\n"),lpIfFix->IF_wResult );

							if( SRL_Reg_SetInfo(SRL_REG_KEY_WAIT,SRL_REG_ALLGET,SRL_REG_WAIT_NG)
        	                    	== -1 )
							{
									LSP_Dbg_Printf( DBG_LEVEL_0,
                                                TEXT("SRLreceive: SRL_Reg_SetInfo error %s %s\n"),
                                                SRL_REG_KEY_WAIT, SRL_REG_ALLGET );
							}
						}
						break;

			//==================================
			// Start game  Receive response
			//==================================
			case	IF_REQ_GAME_START	:	
						LSP_Dbg_Printf(DBG_LEVEL_1,TEXT("SRLreceive: GAME_START anser\n"));
						shutdown( ClientSd, 2 );
						closesocket( ClientSd );
						break;

			//==================================
			// Finish game Receive response
			//==================================
			case	IF_REQ_GAME_END		:	
						LSP_Dbg_Printf(DBG_LEVEL_1,TEXT("SRLreceive: GAME_END anser\n") );
						shutdown( ClientSd, 2 );
						closesocket( ClientSd );
						break;

			//==================================
			// Entry game  Receive response
			//==================================
			case	IF_REQ_GAME_JOIN	:	
						LSP_Dbg_Printf(DBG_LEVEL_1,TEXT("SRLreceive: GAME_JOIN asner\n") );
						shutdown( ClientSd, 2 );
						closesocket( ClientSd );
						break;

			//==================================
			// Leave game  Receive response
			//==================================
			case	IF_REQ_GAME_DEFECT	:	
						LSP_Dbg_Printf(DBG_LEVEL_1,TEXT("SRLreceive: GAME_DEFECT anser\n"));
						shutdown( ClientSd, 2 );
						closesocket( ClientSd );
						break;

			//==================================
			// Terminate message
			//==================================
			case	IF_REQ_TERMINATE	:	
						LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("SRLreceive : TERMINATE accept\n") );
						shutdown( ClientSd, 2 );
						iRtn = closesocket( ClientSd );
						if( iRtn != 0 )
						{
							nResult = WSAGetLastError();
							LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive: closesoket error:%d ClientSD\n"),nResult);
						}
						iRtn = shutdown( AcceptClientSd, 2 );	// SD_BOTH
						iRtn = closesocket( AcceptClientSd );
						if( iRtn != 0 )
						{
							nResult = WSAGetLastError();
							LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive: closesoket error:%d \n"),nResult);
						}
						iRtn = WSACleanup();
						LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("SRLreceive: Terminate\n") );
						return( 0 );

			//==================================
			// System error
			//==================================
			default						:	
						LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive: IF_REQ_??? accept\n") );
						shutdown( ClientSd, 2 );
						closesocket( ClientSd );
						iLoopOut = 1;

						shutdown( AcceptClientSd, 2 );
						iRtn = closesocket( AcceptClientSd );
						if( iRtn != 0 )
						{
							nResult = WSAGetLastError();
							LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive: closesoket error:%d \n"),nResult);
						}
						LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("SRLreceive: abend\n") );
						return( -1 );
		}
		LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("SRLreceive : Next Waitting\n") );
	}

	shutdown( ClientSd, 2 );
	iRtn = closesocket( ClientSd );
	shutdown( AcceptClientSd, 2 );
	iRtn = closesocket( AcceptClientSd );
	if( iRtn != 0 )
	{
		nResult = WSAGetLastError();
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRLreceive main: closesoket error:%d \n"),nResult);
	}
	LSP_Dbg_Printf( DBG_LEVEL_1,TEXT("SRLreceive : SRLreceive Terminate\n") );
	iRtn = WSACleanup();
	return( 0 );
}

/*=============================================================================
     Function : System message notice
     Input    : lpIfFix
	Output   : no
	Return   : no
==============================================================================*/

void SRL_Rcv_SysMessage( LPSRS_IFFIX lpIfFix )
{
	HRESULT					hResult;
	LPSRS_IFMESSAGE			lpIfMessage;
	LPSPDATA_HANDLEMESSAGE  lpHandleMessage;
	char					*lpMessage;

	if( lpIfFix->IF_wRequest == IF_REQ_SENDMSG )
	{
		lpHandleMessage = (LPSPDATA_HANDLEMESSAGE)malloc( sizeof(SPDATA_HANDLEMESSAGE) );
		if( lpHandleMessage == NULL )
		{
			return;
		}
		memset( lpHandleMessage, 0, sizeof(SPDATA_HANDLEMESSAGE) );
		lpMessage = (char *)malloc( SRS_MAX_MESSAGE );

		if( lpMessage == NULL )
		{
			realloc( lpHandleMessage, 0 );
			return;
		}
		memset( lpMessage, 0, SRS_MAX_MESSAGE );

		memcpy( lpMessage, lpIfMessage->IF_MS_cMessage, SRS_MAX_MESSAGE );

		lpHandleMessage->dwSize = sizeof(SPDATA_HANDLEMESSAGE);
		lpHandleMessage->dwFromID = (DWORD)lpIfMessage->IF_MS_wUserID;
		lpHandleMessage->dwToID = (DWORD)lpIfMessage->IF_MS_wMessageCode;
		lpHandleMessage->lpBuffer = (LPVOID)lpMessage;
		lpHandleMessage->dwBufSize = (DWORD)SRS_MAX_MESSAGE;

		hResult = DP_OK;
//		hResult = lpISP->lpVtbl->HandleMessage(lpISP,lpHandleMessage );

		realloc( lpHandleMessage, 0 );
		realloc( lpMessage, 0 );
	}
	return;
}
