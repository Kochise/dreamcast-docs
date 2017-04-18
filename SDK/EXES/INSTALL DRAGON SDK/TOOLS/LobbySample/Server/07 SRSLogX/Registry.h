/***************************************************************************
 *
 *  Copyright (C) 2000 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       Registry.h
 *  Content:    Registry header
 *
 ***************************************************************************/
#ifndef __REGISTRY_H__
#define __REGISTRY_H__

#include <windows.h>

typedef struct {
	char name[MAX_PATH];
	int max_entry;
} ENTRYINFO, *LPENTRYINFO;

#define DEFAULT_AUTOUPDATE		3
#define DEFAULT_DICONNECTTIME	5

extern int auto_update;
extern int disconnecttime;

// export member
LONG IsRegistryEntry();
int GetPortNum();
int GetMaxUserNum();
int GetMaxLobbyNum();
int GetMaxGroupNum();
int GetMaxGameNum();
int GetSendMode();
int GetDebugInfo();
BOOL GetLobbyInfo( int, LPENTRYINFO );
BOOL GetGameInfo( int, LPENTRYINFO );
BOOL GetLogginMessage( char* );
BOOL SetPortNum( int );
BOOL SetMaxUserNum( int );
BOOL SetMaxLobbyNum( int );
BOOL SetMaxGroupNum( int );
BOOL SetMaxGameNum( int );
BOOL SetSendMode( int );
BOOL SetDebugInfo( int );
BOOL SetLobbyInfo( int, LPENTRYINFO );
BOOL SetGameInfo( int, LPENTRYINFO );
BOOL SetLogginMessage( char* );
void SetRegistryDefault();
BOOL SRSLog_RegSave();
int SRSLog_RegLoad();
BOOL SRSLog_IPSave( int );
int SRSLog_IPLoad();

#endif __REGISTRY_H__
