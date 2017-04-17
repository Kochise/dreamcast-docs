/***************************************************************************
 *
 *  Copyright (C) 2000 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       Registry.cpp
 *  Content:    Registry I/O class for SRSlog
 *
 ***************************************************************************/

#include "Registry.h"
#include <stdio.h>

HKEY ghKey = NULL;

// private functions
LONG RegistryOpen( char* = NULL );
LONG RegistryCreate( char* = NULL );
void RegistryClose();
void RegistryGetValue( char*, char* );

//----------------------------------------------------------------
// private
//----------------------------------------------------------------

LONG RegistryOpen( char *str )
{
	char subkey[MAX_PATH] = "SOFTWARE\\LOBBY SERVER";
	if ( str )
	{
		strcat( subkey, "\\" );
		strcat( subkey, str );
	}
	return RegOpenKeyEx( HKEY_LOCAL_MACHINE, subkey, 0, KEY_ALL_ACCESS, &ghKey );
}

LONG RegistryCreate( char *str )
{
	char subkey[MAX_PATH] = "SOFTWARE\\LOBBY SERVER";
	DWORD dw;
	if ( str )
	{
		strcat( subkey, "\\" );
		strcat( subkey, str );
	}
	return RegCreateKeyEx( HKEY_LOCAL_MACHINE, subkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &ghKey, &dw );
}

void RegistryClose()
{
	if ( ghKey )
	{
		RegCloseKey( ghKey );
		ghKey = NULL;
	}
}

void RegistryGetValue( char *str, char *dst )
{
	char temp[MAX_PATH];
	DWORD dw;
	dw = MAX_PATH;
	RegQueryValueEx( ghKey, str, NULL, NULL, (LPBYTE) &temp, &dw );
	strcpy( dst, temp );
}

void RegistrySetValue( char *str, char *src )
{
	DWORD dw;
	dw = (DWORD) strlen( src );
	RegSetValueEx( ghKey, str, 0, REG_SZ, (LPBYTE) src, dw );
}

//----------------------------------------------------------------
// export functions
//----------------------------------------------------------------

LONG IsRegistryEntry()
{
	LONG retVal;
	retVal = RegistryOpen();
	if ( retVal == 0 )
	{
		RegistryClose();
	}
	return retVal;
}

//----------------------------------------------------------------
// export functions (Read)
//----------------------------------------------------------------

int GetPortNum()
{
	char str[MAX_PATH];
	if ( RegistryOpen() ) return 0;
	RegistryGetValue( "client port", str );
	RegistryClose();
	return atoi( str );
}

int GetMaxUserNum()
{
	char str[MAX_PATH];
	if ( RegistryOpen() ) return 0;
	RegistryGetValue( "max user", str );
	RegistryClose();
	return atoi( str );
}

int GetMaxLobbyNum()
{
	char str[MAX_PATH];
	if ( RegistryOpen() ) return 0;
	RegistryGetValue( "max lobby", str );
	RegistryClose();
	return atoi( str );
}

int GetMaxGroupNum()
{
	char str[MAX_PATH];
	if ( RegistryOpen() ) return 0;
	RegistryGetValue( "max group", str );
	RegistryClose();
	return atoi( str );
}

int GetMaxGameNum()
{
	char str[MAX_PATH];
	if ( RegistryOpen() ) return 0;
	RegistryGetValue( "max game", str );
	RegistryClose();
	return atoi( str );
}

int GetSendMode()
{
	char str[MAX_PATH];
	if ( RegistryOpen() ) return 0;
	RegistryGetValue( "send mode", str );
	RegistryClose();
	return atoi( str );
}

BOOL GetLobbyInfo( int lobbynum, LPENTRYINFO plobbyinfo )
{
	char str[MAX_PATH];

	if ( lobbynum < 1 || lobbynum > GetMaxLobbyNum() ) return FALSE;

	plobbyinfo->max_entry = 1;
	ZeroMemory( plobbyinfo->name, sizeof(plobbyinfo->name) );
	sprintf( str, "lobby%d", lobbynum );
	if ( RegistryOpen( str ) ) return FALSE;
	RegistryGetValue( "name", plobbyinfo->name );
	RegistryGetValue( "max entry", str );
	plobbyinfo->max_entry = atoi( str );
	RegistryClose();
	return TRUE;
}

BOOL GetGameInfo( int gamenum, LPENTRYINFO pgameinfo )
{
	char str[MAX_PATH];

	if ( gamenum < 1 || gamenum > GetMaxGameNum() ) return FALSE;

	pgameinfo->max_entry = 1;
	ZeroMemory( pgameinfo->name, sizeof(pgameinfo->name) );
	sprintf( str, "game%d", gamenum );
	if ( RegistryOpen( str ) ) return FALSE;
	RegistryGetValue( "name", pgameinfo->name );
	RegistryGetValue( "max entry", str );
	pgameinfo->max_entry = atoi( str );
	RegistryClose();
	return TRUE;
}

int GetDebugInfo()
{
	char str[MAX_PATH] = "";

	if ( RegistryOpen( "debug" ) ) return -1;
	RegistryGetValue( "mode", str );
	RegistryClose();
	return atoi( str );
}

BOOL GetLogginMessage( char *str )
{
	if ( RegistryOpen( "logging" ) ) return FALSE;
	RegistryGetValue( "logging message", str );
	RegistryClose();
	return TRUE;
}


//----------------------------------------------------------------
// export functions (Write)
//----------------------------------------------------------------

BOOL SetPortNum( int port )
{
	char str[32];
	sprintf( str, "%d", port );
	if ( RegistryCreate() ) return FALSE;
	RegistrySetValue( "client port", str );
	RegistryClose();
	return TRUE;
}

BOOL SetMaxUserNum( int user )
{
	char str[32];
	sprintf( str, "%d", user );
	if ( RegistryCreate() ) return FALSE;
	RegistrySetValue( "max user", str );
	RegistryClose();
	return TRUE;
}

BOOL SetMaxLobbyNum( int lobby )
{
	char str[32];
	sprintf( str, "%d", lobby );
	if ( RegistryCreate() ) return FALSE;
	RegistrySetValue( "max lobby", str );
	RegistryClose();
	return TRUE;
}

BOOL SetMaxGroupNum( int group )
{
	char str[32];
	sprintf( str, "%d", group );
	if ( RegistryCreate() ) return FALSE;
	RegistrySetValue( "max group", str );
	RegistryClose();
	return TRUE;
}

BOOL SetMaxGameNum( int game )
{
	char str[32];
	sprintf( str, "%d", game );
	if ( RegistryCreate() ) return FALSE;
	RegistrySetValue( "max game", str );
	RegistryClose();
	return TRUE;
}

BOOL SetSendMode( int send )
{
	char str[32];
	sprintf( str, "%d", send );
	if ( RegistryCreate() ) return FALSE;
	RegistrySetValue( "send mode", str );
	RegistryClose();
	return TRUE;
}

BOOL SetDebugInfo( int debug )
{
	char str[32];
	sprintf( str, "%d", debug );
	if ( RegistryCreate( "debug" ) ) return FALSE;
	RegistrySetValue( "mode", str );
	RegistryClose();
	return TRUE;
}

BOOL SetLobbyInfo( int lobbynum, LPENTRYINFO plobbyinfo )
{
	char str[MAX_PATH];

	sprintf( str, "lobby%d", lobbynum );
	if ( RegistryCreate( str ) ) return FALSE;
	RegistrySetValue( "name", plobbyinfo->name );
	str[0] = '\0';
	if ( plobbyinfo->max_entry > 0 )
	{
		sprintf( str, "%d", plobbyinfo->max_entry );
	}
	RegistrySetValue( "max entry", str );
	RegistryClose();
	return TRUE;
}

BOOL SetGameInfo( int gamenum, LPENTRYINFO pgameinfo )
{
	char str[MAX_PATH];

	sprintf( str, "game%d", gamenum );
	if ( RegistryCreate( str ) ) return FALSE;
	RegistrySetValue( "name", pgameinfo->name );
	str[0] = '\0';
	if ( pgameinfo->max_entry > 0 )
	{
		sprintf( str, "%d", pgameinfo->max_entry );
	}
	RegistrySetValue( "max entry", str );
	RegistryClose();
	return TRUE;
}

BOOL SetLogginMessage( char *str )
{
	if ( RegistryCreate( "logging" ) ) return FALSE;
	RegistrySetValue( "logging message", str );
	RegistryClose();
	return TRUE;
}

void SetRegistryDefault()
{
	int i;
	ENTRYINFO entryinfo;
	SetPortNum( 1002 );
	SetMaxUserNum( 8 );
	SetMaxLobbyNum( 8 );
	SetMaxGroupNum( 4 );
	SetMaxGameNum( 1 );
	SetSendMode( 1 );
	SRSLog_IPSave( 0 );
	entryinfo.max_entry = 1;
	strcpy( entryinfo.name, "Game Title" );
	for( i = 1; i <= 1; i++ )
	{
		SetGameInfo( i, &entryinfo );
	}
	entryinfo.max_entry = 8;
	for( i = 1; i <= 8; i++ )
	{
		sprintf( entryinfo.name, "lobby%02d", i );
		SetLobbyInfo( i, &entryinfo );
	}
	auto_update = DEFAULT_AUTOUPDATE;
	disconnecttime = DEFAULT_DICONNECTTIME;
	SRSLog_RegSave();
}


//----------------------------------------------------------------
// Registry I/O for SRSLogX.exe
//----------------------------------------------------------------

BOOL SRSLog_RegSave()
{
	char str[MAX_PATH];

	if ( RegistryCreate( "SRSLog" ) ) return FALSE;
	sprintf( str, "%d", auto_update );
	RegistrySetValue( "auto update", str );
	sprintf( str, "%d", disconnecttime );
	RegistrySetValue( "auto disconnect", str );
	RegistryClose();
	return TRUE;
}

BOOL SRSLog_RegLoad()
{
	char str[MAX_PATH];
	if ( RegistryOpen( "SRSLog" ) ) return FALSE;
	RegistryGetValue( "auto update", str );
	auto_update = atoi( str );
	if ( auto_update == 0 ) auto_update = DEFAULT_AUTOUPDATE;
	RegistryGetValue( "auto disconnect", str );
	disconnecttime = atoi( str );
	if ( disconnecttime == 0 ) disconnecttime = DEFAULT_DICONNECTTIME;
	RegistryClose();
	return TRUE;
}

BOOL SRSLog_IPSave( int ip )
{
	char str[MAX_PATH];

	if ( RegistryCreate() ) return FALSE;
	sprintf( str, "%d.%d.%d.%d", (ip & 0xff), ((ip >> 8) & 0xff), ((ip >> 16) & 0xff), ((ip >> 24) & 0xff) );
	RegistrySetValue( "IP Address", str );
	RegistryClose();
	return TRUE;
}

int SRSLog_IPLoad()
{
	char str[MAX_PATH];
	int bi1, bi2, bi3, bi4;
	bi1 = bi2 = bi3 =  bi4 = 0;
	if ( RegistryOpen() ) return 0;
	RegistryGetValue( "IP Address", str );
	RegistryClose();
	sscanf( str, "%d.%d.%d.%d", &bi1, &bi2, &bi3, &bi4 );
	return ((bi1 & 0xff) | ((bi2 & 0xff) << 8) | ((bi3 & 0xff) << 16) | ((bi4 & 0xff) << 24));
}
