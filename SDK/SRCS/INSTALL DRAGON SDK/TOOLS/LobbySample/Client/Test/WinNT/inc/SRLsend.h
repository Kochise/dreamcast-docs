/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       TPsend.h
 *  Content:    Lobby client debug tools include
 *                                           
 ***************************************************************************/
#ifndef _SRL_SEND_H_
#define _SRL_SEND_H_

//================================
//  ä÷êîêÈåæ
//================================
__declspec( dllexport )int __stdcall SRL_Snd_Connect( LPSTR lpServerIP, LPSTR lpUser, LPSTR lpPass, LPSTR lpMessage );
__declspec( dllexport )int __stdcall SRL_Snd_Disconnect( char *lpServerIP, int iPort );
__declspec( dllexport )int __stdcall SRL_Snd_CreateProc( int iMode, LPCTSTR lpCommandLine );
__declspec( dllexport )int __stdcall SRL_Snd_Request( char *lpServerIP, int iPort, char *lpSendData, size_t szSendSize );
__declspec( dllexport )int __stdcall SRL_Snd_Term( void );

__declspec( dllexport )int __stdcall SRL_Snd_UserEntry( LPSTR lpServerIP, int iPort, LPCTSTR lpClientName, LPCTSTR lpUserName );
__declspec( dllexport )int __stdcall SRL_Snd_UserDelete( char *lpServerIP, int iPort, WORD wUserID );
__declspec( dllexport )int __stdcall SRL_Snd_LobbyEntry( char *lpServerIP, int iPort, WORD wUserID, WORD wLobbyID );
__declspec( dllexport )int __stdcall SRL_Snd_LobbyDefect( char *lpServerIP, int iPort, WORD wUserID, WORD wLobbyID );
__declspec( dllexport )int __stdcall SRL_Snd_GroupMake( char *lpServerIP, int iPort, WORD wUserID, LPCTSTR lpGroupName );
__declspec( dllexport )int __stdcall SRL_Snd_GroupJoin( char *lpServerIP, int iPort, WORD wUserID, WORD wGroupID, WORD wCondition );
__declspec( dllexport )int __stdcall SRL_Snd_GroupDefect( char *lpServerIP, int iPort, WORD wUserID, WORD wGroupID );
__declspec( dllexport )int __stdcall SRL_Snd_GameStart( char *lpServerIP, int iPort, WORD wUserID );
__declspec( dllexport )int __stdcall SRL_Snd_GameJoin( char *lpServerIP, int iPort, WORD wUserID );
__declspec( dllexport )int __stdcall SRL_Snd_GameDefect( char *lpServerIP, int iPort, WORD wUserID );
__declspec( dllexport )int __stdcall SRL_Snd_GameEnd( char *lpServerIP, int iPort, WORD wUserID );
__declspec( dllexport )int __stdcall SRL_Snd_SaveInfo( char *lpServerIP, int iPort, WORD wUserID, LPCTSTR lpSaveInfo );
__declspec( dllexport )int __stdcall SRL_Snd_AllGet( char *lpServerIP, int iPort );
__declspec( dllexport )int __stdcall SRL_Snd_Message( char *lpServerIP, int iPort, WORD wUserID, WORD wMessageCode, LPCTSTR lpMessage );

#endif
