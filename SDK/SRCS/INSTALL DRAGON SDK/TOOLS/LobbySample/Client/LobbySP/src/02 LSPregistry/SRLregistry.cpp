/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRLregistry.cpp
 *                	SRL_Reg_GetInfo	: Get Reg information
 *
 *  Content:    Lobby Client registry access tools 
 *
 ***************************************************************************/
//================================
// Include
//================================
#include <windows.h>
#include <stdio.h>

#include "LSPdebug.h"
#include "SRLregistry.h"

/*=============================================================================
     Function: Get common information
     Input   ：lpRegInfo
     Output  ：lpRegInfo
     Return  ：True 0
               False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Reg_GetComInfo( struct SRL_REG_INFO *lpRegInfo )
{
    LONG    lRtn;
	HKEY    hKey;
	DWORD	dwRtn;
	DWORD	dwMax;
	DWORD   dwSize;
	DWORD   dwGetSize;
	
    //===========================================
    // Open common information
	//===========================================
    lRtn = RegOpenKeyEx( HKEY_LOCAL_MACHINE, SRL_REG_KEY_COM, 0, KEY_READ, &hKey );
    if( lRtn != ERROR_SUCCESS )
    {
		dwRtn = GetLastError( );
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_GetCominfo : RegOpenKeyEx Error %d %s\n"), dwRtn, SRL_REG_KEY_COM );
        return( -1 );
    }

    //===========================================
    // Get max user information
	//===========================================
    dwSize = 4;
	dwGetSize = 4;
    lRtn = RegQueryValueEx( hKey,SRL_REG_MAXUSER,NULL,NULL,(LPBYTE)&dwMax, &dwGetSize );
    if( lRtn != ERROR_SUCCESS ) 
    {
        RegCloseKey( hKey );
        if( lRtn == ERROR_MORE_DATA )
        {
			LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("SRL_Reg_GetComInfo: MORE_DATA AreaSize%d GetSize=%d\n"), dwSize,dwGetSize  );
        }
        else
        {
			dwRtn = GetLastError( );
			LSP_Dbg_Printf( DBG_LEVEL_0, TEXT("SRL_Reg_GetComInfo: RegQueryValueEx Error %d\n"), dwRtn );
        }
        return( -1 );
    }
	lpRegInfo->wMaxUser = (WORD)dwMax;			// Set max user
	
    //===========================================
    // Get max lobby information
    //===========================================
    dwSize = 4;
	dwGetSize = 4;
    lRtn = RegQueryValueEx( hKey,SRL_REG_MAXLOBBY,NULL,NULL,(LPBYTE)&dwMax, &dwGetSize );
    if( lRtn != ERROR_SUCCESS )
    {
        RegCloseKey( hKey );
        if( lRtn == ERROR_MORE_DATA )
        {
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_GetComInfo : MORE_DATA AreaSize%d GetSize=%d\n"), dwSize,dwGetSize  );
		}
	   	else
        {
 			dwRtn = GetLastError( );
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_GetComInfo : RegQueryValueEx Error %d\n"), dwRtn );
		}
        return( -1 );
    }
	lpRegInfo->wMaxLobby = (WORD)dwMax;			// Set max lobby

    //===========================================
    // Get max game information
	//===========================================
    dwSize = 4;
	dwGetSize = 4;
    lRtn = RegQueryValueEx( hKey,SRL_REG_MAXGAME,NULL,NULL,(LPBYTE)&dwMax, &dwGetSize );
    if( lRtn != ERROR_SUCCESS )
    {
        RegCloseKey( hKey );
        if( lRtn == ERROR_MORE_DATA ) 
        {
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_GetComInfo : MORE_DATA AreaSize%d GetSize=%d\n"), dwSize,dwGetSize   );
		}
	   	else
        {
 			dwRtn = GetLastError( );
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("RL_Reg_GetComInfo : RegQueryValueEx Error %d\n"), dwRtn );
		}
        return( -1 );
    }
	lpRegInfo->wMaxGame = (WORD)dwMax;			// Set max game
	
    //===========================================
    // Get max group information
	//===========================================
    dwSize = 4;
	dwGetSize = 4;
    lRtn = RegQueryValueEx( hKey,SRL_REG_MAXGROUP,NULL,NULL,(LPBYTE)&dwMax, &dwGetSize );
    if( lRtn != ERROR_SUCCESS ) 
    {
        RegCloseKey( hKey );
        if( lRtn == ERROR_MORE_DATA ) 
        {
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_GetComInfo : MORE_DATA AreaSize%d GetSize=%d \n"), dwSize,dwGetSize );
		}
	   	else
        {
 			dwRtn = GetLastError( );
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_GetComInfo : RegQueryValueEx Error %d \n"), dwRtn);
		}
        return( -1 );
    }
	lpRegInfo->wMaxGroup = (WORD)dwMax;			// Set max groups

    RegCloseKey( hKey );

    return( 0 );
}

/*=============================================================================
     Function：Get text information from Reg
	 Input   ：lpRegKey
	 		   lpReg
			   lpBuff
     Output  ：lpRegBuff
	 Return  ：True 0
               False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Reg_GetInfo( LPCTSTR lpRegKey, 
													  LPCTSTR lpReg,
													  LPCTSTR lpBuff )
{
    LONG    lRtn;
	DWORD	dwRtn; 
    HKEY    hKey;
    DWORD   dwSize;
	DWORD   dwGetSize;
	
    //===========================================
    // Open Reg
	//===========================================
    lRtn = RegOpenKeyEx( HKEY_LOCAL_MACHINE, lpRegKey, 0, KEY_READ, &hKey );
    if( lRtn != ERROR_SUCCESS ) 
    {
		dwRtn = GetLastError( );
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_GetInfo:RegOpenKeyEx Error %s %d \n"),lpRegKey,dwRtn );
        return( -1 );
    }
    dwSize = 256;
    dwGetSize = 256;

    //===========================================
    // Get reg information 
    //===========================================
    lRtn = RegQueryValueEx( hKey, lpReg, NULL, NULL, (LPBYTE)lpBuff, &dwGetSize );
    if( lRtn != ERROR_SUCCESS ) 
    {
        RegCloseKey( hKey );
        if( lRtn == ERROR_MORE_DATA )   
        {
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_GetInfo : MORE_DATA AreaSize=%d, GetSize=%d\n"),dwSize, dwGetSize );
        }
        else
        {
	  		dwRtn = GetLastError( );
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_GetInfo : RegQueryValueEx Error %d %s\n"),dwRtn, lpRegKey );
        }
        return( -1 );
    }
    RegCloseKey( hKey );

    return( 0 );
}

/*=============================================================================
     Function：Set text information to Reg
	 Input   ：lpRegKey
	 		   lpReg
			   lpBuff
     Output  ：no
	 Return  ：True 0
               False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Reg_SetInfo( LPCTSTR lpRegKey,
                                                      LPCTSTR lpReg,
                                                      LPCTSTR lpBuff )
{
    LONG    lRtn=0;
	DWORD	dwRtn;
    HKEY    hKey;
	DWORD   dwDisposition;

    /*==========================================*/
    /*  Open/Create Reg key                     */
    /*==========================================*/
    lRtn = RegCreateKeyEx( HKEY_LOCAL_MACHINE, lpRegKey, 0, NULL, 
                           REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL,
                           &hKey, &dwDisposition );    
    if( lRtn != ERROR_SUCCESS )
    {
		dwRtn = GetLastError( );
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_SetInfo : RegCreateKeyEx Error %d %s\n"), 
				dwRtn, lpRegKey);
		return( -1 );
    }

    /*==================================*/
    /*   Set value and Data             */
    /*==================================*/
    lRtn = RegSetValueEx( hKey, lpReg, 0, REG_SZ, (LPBYTE)lpBuff, strlen((const char *)lpBuff)+1 );
    if( lRtn != ERROR_SUCCESS )
    {
		dwRtn = GetLastError( );
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_SetInfo : RegSetValueEx Error %d\n"), 
				dwRtn, lpReg);
        RegCloseKey( hKey );
        return( -1 );
    }
    RegCloseKey( hKey );
    return( 0 );
}

/*=============================================================================
     Function：Set bin information to Reg
	 Input   ：lpRegKey
	 		   lpReg
			   lpBuff
			   dwSize
     Output  ：no
	 Return  ：True 0
               False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Reg_SetInfoBinary( LPCTSTR lpRegKey,
                                                            LPCTSTR lpReg,
                                                            LPCTSTR lpBuff,
                                                            DWORD dwSize )
{
    LONG    lRtn=0;
	DWORD	dwRtn;
    HKEY    hKey;
	DWORD   dwDisposition;
	
    /*==========================================*/
    /*  Open/Create Reg key                     */
    /*==========================================*/
    lRtn = RegCreateKeyEx( HKEY_LOCAL_MACHINE, lpRegKey, 0, NULL, 
                           REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL,
                           &hKey, &dwDisposition );    
    if( lRtn != ERROR_SUCCESS )
    {
		dwRtn = GetLastError( );
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_SetInfoBinary : RegCreateKeyEx Error %d\n"),dwRtn );
		
        return( -1 );
    }

    /*==================================*/
    /*   Set value and Data             */
    /*==================================*/
    lRtn = RegSetValueEx( hKey, lpReg, 0, REG_BINARY, (LPBYTE)lpBuff, dwSize );
    if( lRtn != ERROR_SUCCESS )
    {
		dwRtn = GetLastError( );
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_SetInfoBinary : RegSetValueEx Error %d\n"),dwRtn );
        RegCloseKey( hKey );
        return( -1 );
    }
    RegCloseKey( hKey );
    return( 0 );
}

/*=============================================================================
     Function：Get bin information from Reg
	 Input   ：lpRegKey
	 		   lpReg
			   lpBuff
			   dwSize
     Output  ：lpRegBuff
	 Return  ：True 0
               False -1

==============================================================================*/
 __declspec( dllexport )int __stdcall SRL_Reg_GetInfoBinary( LPCTSTR lpRegKey,
                                                             LPCTSTR lpReg,
                                                             LPCTSTR lpBuff,
                                                             DWORD dwSize )
{
    LONG    lRtn;
	DWORD	dwRtn;
	HKEY    hKey;
	
    //===========================================
    // Open reg key
	//===========================================
    lRtn = RegOpenKeyEx( HKEY_LOCAL_MACHINE, lpRegKey, 0, KEY_READ, &hKey );
    if( lRtn != ERROR_SUCCESS )
    {
		dwRtn = GetLastError();
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_GetInfoBinary : RegOpenKeyEx Error %d \n"),dwRtn );
        return( -1 );
    }

    //===========================================
    // Get Reg information
	//===========================================
    lRtn = RegQueryValueEx( hKey, lpReg, NULL, NULL, (LPBYTE)lpBuff, &dwSize );
    if( lRtn != ERROR_SUCCESS )
    {
        RegCloseKey( hKey );
        if( lRtn == ERROR_MORE_DATA )
        {
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_GetInfoBinary : MORE_DATA %d \n"),dwSize );
        }
        else
        {
			dwRtn = GetLastError();
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_GetInfoBinary : RegQueryValueEx Error %d \n"),dwRtn );
        }
        return( -1 );
    }
    RegCloseKey( hKey );

    return( 0 );
}

/*=============================================================================
     Function：Set DWORD information to Reg
	 Input   ：lpRegKey
	 		   lpReg
			   dwInfo
     Output  ：no
	 Return  ：True 0
               False -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRL_Reg_SetInfoDWORD( LPCTSTR lpRegKey,
                                                           LPCTSTR lpReg,
                                                           DWORD dwInfo )
{
    LONG    lRtn=0;
	DWORD	dwRtn;
    HKEY    hKey;
    DWORD   dwDisposition;

    /*==========================================*/
    /*  Open/Create Reg key                     */
    /*==========================================*/
    lRtn = RegCreateKeyEx( HKEY_LOCAL_MACHINE, lpRegKey, 0, NULL, 
                           REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL,
                           &hKey, &dwDisposition );    
    if( lRtn != ERROR_SUCCESS )
    {
		dwRtn = GetLastError( );
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_SetInfoDWORD : RegCreateKeyEx Error %d\n"),dwRtn );
		
        return( -1 );
    }

    /*==========================================*/
    /*  Set value and data                      */
    /*==========================================*/
    lRtn = RegSetValueEx( hKey, lpReg, 0, REG_DWORD, (LPBYTE)&dwInfo, (DWORD)4 );
    if( lRtn != ERROR_SUCCESS )
    {
		dwRtn = GetLastError( );
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_SetInfoDWORD : RegSetValueEx Error %d\n"),dwRtn );
        RegCloseKey( hKey );
        return( -1 );
    }
    RegCloseKey( hKey );
    return( 0 );
}

/*=============================================================================
     Function：Get DWORD information from Reg
	 Input   ：lpRegKey
	 		   lpReg
     Output  ：no
	 Return  ：True 0
               False -1

==============================================================================*/
 __declspec( dllexport )DWORD __stdcall SRL_Reg_GetInfoDWORD( LPCTSTR lpRegKey,LPCTSTR lpReg)
 {
    LONG    lRtn;
	DWORD	dwRtn;
	DWORD	dwInfo;
	DWORD	dwSize;
	DWORD	dwType;
    HKEY    hKey;
	
	LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("##### SRL_Reg_GetInfoDWORD : Start ######\n"));

    //===========================================
    // Open reg key
	//===========================================
    lRtn = RegOpenKeyEx( HKEY_LOCAL_MACHINE, lpRegKey, 0, KEY_READ, &hKey );
    if( lRtn != ERROR_SUCCESS ) 
    {
		dwRtn = GetLastError();
		LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_GetInfoDWORD : RegOpenKeyEx Error %d \n"),dwRtn );
        return( -1 );
    }

    //===========================================
    // Get Reg information
	//===========================================
	dwType = REG_DWORD;
    lRtn = RegQueryValueEx( hKey, lpReg, NULL, &dwType, (LPBYTE)&dwInfo, &dwSize );
    if( lRtn != ERROR_SUCCESS )
    {
        RegCloseKey( hKey );
        if( lRtn == ERROR_MORE_DATA )
        {
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_GetInfoDWORD : MORE_DATA %d \n"),dwSize );
        }
        else
        {
			dwRtn = GetLastError();
			LSP_Dbg_Printf( DBG_LEVEL_0,TEXT("SRL_Reg_GetInfoDWORD : RegQueryValueEx Error %d\n"),dwRtn);
        }
        return( -1 );
    }
    RegCloseKey( hKey );

    return( dwInfo );
}

/*=============================================================================
     Function ：Delete Reg information
     Input	  ：no
     Output   ：no
     Return   ：no

==============================================================================*/
__declspec( dllexport )void __stdcall SRL_Reg_Delete( void )
{
	HKEY	hKey;
	LONG	lRtn;

	//==================================
	// Delete Reg information
	//==================================
    lRtn = RegOpenKeyEx( HKEY_LOCAL_MACHINE, SRL_REG_KEY_COM, 0, KEY_READ, &hKey );
    if( lRtn == ERROR_SUCCESS )
    {
		lRtn = RegDeleteKey( hKey, TEXT("manage") );		// Manegement information
		lRtn = RegDeleteKey( hKey, TEXT("event") );			// Events information
		lRtn = RegDeleteKey( hKey, TEXT("handle") );		// Hundle information
	}
    RegCloseKey( hKey );

	return;
}
