/*==========================================================================
 *
 *	Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *	File:       LSPdplay.cpp
 *
 *	Content:	Main code file for DirectPlay LOBBY-SP
 *
 *  Functions:  DPLSPInit
 *				LP_Shutdown
 *
 *	History:	1999/09/02		Created it
 *
 *=========================================================================*/
#include <windows.h>

// include of DLPAY
#include "dplay.h"
#include "dpldplay.h"
//#include "lobbysp.h"

// include of LOBBY-SP
#include "LSPdebug.h"
#include "LSPfuncs.h"

//--------------------------------------------------------------------------
//
//	Globals
//
//--------------------------------------------------------------------------
//==========================================================================
//  defined TCP GUID
// REVIEW!!!! -- This should come out of the DPADDRESS, not be hard-coded.
// This is a complete hack until we figure out the multiple SP guid problem
// inside DPADDRESSes.
// 36E95EE0-8577-11cf-960C-0080C7534E82
//==========================================================================
DEFINE_GUID(GUID_TCP,
0x36E95EE0, 0x8577, 0x11cf, 0x96, 0xc, 0x0, 0x80, 0xc7, 0x53, 0x4e, 0x82);

//==========================================================================
//  defined LOBBY-SP GUID
//	DirectPlay Service Provider for Lobby-SP
//	{4AF206E0-9712-11cf-A021-00AA006157AC}
//==========================================================================
//  17AF6382-87AF-11D3-ADF6-0020AF6849EF
DEFINE_GUID(GUID_DirectPlaySP,    0x17af6382, 0x87af, 0x11d3, 0xad, 0xf6, 0x0, 0x20, 0xaf, 0x68, 0x49, 0xef);

//	{4AF206E0-9712-11cf-A021-00AA006157AC}
//DEFINE_GUID(GUID_DirectPlaySP, 0x4af206e0, 0x9712, 0x11cf, 0xa0, 0x21, 0x0, 0xaa, 0x0, 0x61, 0x57, 0xac);

/*==========================================================================
 *
 *  DPLSPInit （Init LOBBY-SP）
 *
 *=========================================================================*/
HRESULT WINAPI DPLSPInit(LPSPDATA_INIT lpInit) 
{
	LPDIRECTPLAY		lpIDP = NULL;
	LPDIRECTPLAY3		lpIDP3 = NULL;
	LPSP_CALLBACKS		pcbTable;
	LPSPDATABLOB		lpBlob = NULL;
	LPVOID				lpAddress = NULL;
	DWORD				dwAddressSize = 0;
	HRESULT				hResult;
//	LPDPADDRESS			lpAddrIn;

	LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: entry\n"),DBG_NAME_DPLSPINIT );

	pcbTable = lpInit->lpCB;
	if (pcbTable->dwSize < sizeof(SP_CALLBACKS))	// table not big enough
	{
		LSP_Dbg_Printf( DBG_LEVEL_0, 
			TEXT("%s: Callback table too small\n"),DBG_NAME_DPLSPINIT);
		return DPERR_GENERIC;
	}

	// Setup the version information
	lpInit->dwSPVersion = DPLSP_MAJORVERSION;

	// Increment the global count of lobby providers
	gdwDPlaySPRefCount++;

    // Set up callbacks
    pcbTable->dwSize = sizeof(SP_CALLBACKS);	// MUST set the return size of the table
    pcbTable->dwFlags = 0;						// no flags
    pcbTable->AddGroupToGroup = LP_AddGroupToGroup;
	pcbTable->AddPlayerToGroup = LP_AddPlayerToGroup;
	pcbTable->BuildParentalHeirarchy = LP_BuildParentalHeirarchy;
    pcbTable->Close = LP_Close;
    pcbTable->CreateGroup = LP_CreateGroup;
	pcbTable->CreateGroupInGroup = LP_CreateGroupInGroup;
    pcbTable->CreatePlayer = LP_CreatePlayer;
    pcbTable->DeleteGroupFromGroup = LP_DeleteGroupFromGroup;
	pcbTable->DeletePlayerFromGroup = LP_DeletePlayerFromGroup;
    pcbTable->DestroyGroup = LP_DestroyGroup;
    pcbTable->DestroyPlayer = LP_DestroyPlayer;
    pcbTable->EnumSessions = LP_EnumSessions;
	pcbTable->GetCaps = LP_GetCaps;
	pcbTable->GetGroupConnectionSettings = LP_GetGroupConnectionSettings;
    pcbTable->GetGroupData = LP_GetGroupData;
	pcbTable->GetPlayerCaps = LP_GetPlayerCaps;
    pcbTable->GetPlayerData = LP_GetPlayerData;
    pcbTable->Open = LP_Open;
	pcbTable->Send = LP_Send;
	pcbTable->SendChatMessage = LP_SendChatMessage;
	pcbTable->SetGroupConnectionSettings = LP_SetGroupConnectionSettings;
    pcbTable->SetGroupData = LP_SetGroupData;
    pcbTable->SetGroupName = LP_SetGroupName;
    pcbTable->SetPlayerData = LP_SetPlayerData;
    pcbTable->SetPlayerName = LP_SetPlayerName;
	pcbTable->Shutdown = LP_Shutdown;
	pcbTable->StartSession = LP_StartSession;


	// Alloc memory for our internal "global" structure
	// (it's really per Lobby object)
	lpBlob = (LPSPDATABLOB)malloc(sizeof(SPDATABLOB));

	if(!lpBlob)
	{
		LSP_Dbg_Printf( DBG_LEVEL_0,
			TEXT("%s: couldn't allocate memory for SPDATABLOB\n"), DBG_NAME_DPLSPINIT);
		return DPERR_GENERIC;
	}

	// Store the DPlay interface pointer in SPDataBlob
	lpBlob->lpIDP = lpIDP3;
	hResult = IDPLobbySP_SetSPDataPointer(lpInit->lpISP, (LPVOID)lpBlob);

	if(FAILED(hResult))
	{
		LSP_Dbg_Printf( DBG_LEVEL_0, 
			TEXT("%s: failed to set SPData pointer!\n"), DBG_NAME_DPLSPINIT);
		realloc(lpBlob, 0);
		return DPERR_GENERIC;
	}

//	// Copy the address if it exists
//	lpAddrIn = pid->lpAddress;
//	if(lpAddrIn)
//	{
//		// Figure out the size of the Address and then make a copy of it
//		// REVIEW!!!! -- Currently, there is no good way to pick out the
//		// size of the DPADDRESS.  You need to know the size to call EnumAddress,
//		// but we don't know the size.  This should be addressed in bug #7353.
//		// For now, just pull the size out of the address ourselves
//		if(IsEqualGUID(lpAddrIn->guidDataType, DPAID_TotalSize))
//		{
//			dwAddressSize = *((DWORD *)(++lpAddrIn));
//		}
//		else
//		{
//			// If we don't understand the address, we will prompt for it
//			LSP_Dbg_Printf( DBG_LEVEL_0,
//				TEXT("%s: Unable to get the address size from the DPADDRESS\n"),DBG_NAME_DPLSPINIT);
//			return DP_OK;
//		}
//
//		// Allocate memory for the address
//		lpAddress = malloc(dwAddressSize);
//		if(!lpAddress)
//		{
//			// If we don't save the address, we will prompt for it
//			LSP_Dbg_Printf( DBG_LEVEL_0,
//				TEXT("%s: Unable to allocate memory for local address"),DBG_NAME_DPLSPINIT);
//			return DP_OK;
//		}
//
//		// Copy the address
//		memcpy(lpAddress, pid->lpAddress, dwAddressSize);
//
//		// Save the DPADDRESS of the lobby server
//		lpBlob->lpAddress = (LPDPADDRESS)lpAddress;
//	}

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s return\n"),DBG_NAME_DPLSPINIT );
	return DP_OK;
}

/*==========================================================================
 *
 *  LP_Shutdown （finish notice）
 *
 *=========================================================================*/
HRESULT WINAPI LP_Shutdown(LPSPDATA_SHUTDOWN psd) 
{
	LPSPDATABLOB		lpBlob = NULL;
	LPDIRECTPLAY3		lpIDP = NULL;
	HRESULT				hResult;
	
	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s entry\n"),DBG_NAME_SHUTDOWN );

	// Decrement the global count of lobby providers
	gdwDPlaySPRefCount--;		

	// Get a pointer to our "global" data
	hResult = (HRESULT)IDPLobbySP_GetSPDataPointer(psd->lpISP, (void **)&lpBlob);
	if(FAILED(hResult))
	{
		LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("%s: failed to get SPData pointer!\n"),DBG_NAME_SHUTDOWN);
		return DPERR_GENERIC;
	}

	// Release the DirectPlay object
	if(lpBlob)
		lpIDP = lpBlob->lpIDP;

	if(lpIDP)
	{
		IDirectPlay3_Release(lpIDP);
		//lpIDP->lpVtbl->Release(lpIDP);
	}

	// Free our address struct if one exists
	if(lpBlob->lpAddress)
		realloc( lpBlob->lpAddress, 0 );

	// Free all of our memory
	if(lpBlob)
		realloc( lpBlob, 0 );

	LSP_Dbg_Printf( DBG_LEVEL_1, TEXT("%s return\n"),DBG_NAME_SHUTDOWN );
	return DP_OK;
}
