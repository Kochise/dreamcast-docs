/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *  File:       SRLtestApl.cpp
 *  Content:    Lobby client test application for WinNT
 *
 ***************************************************************************/
#include <windows.h>
#include <stdio.h>
#include "SRScom.h"
#include "SRLdebug.h"
#include "SRLregistry.h"
#include "SRLsend.h"
#include "SRLmanage.h"
#include "SRLevent.h"

int     SRL_Apl_Event( void );

/*=====================================================================================
Lobby test program start
=======================================================================================*/
int WINAPI WinMain( HINSTANCE hInstanc,HINSTANCE hPrevInstanc, LPSTR lpszCmdLin,int nCmdSho )
{
    int     iMsg;
    int     iPort;
    WORD    wUserID;
    WORD    wLobbyID;
    WORD    wGroupID;
    WORD    wMessageCode;
    DWORD   dwPort;
    char    cServerIP[SRS_MAX_NAME_CLIENT];      // Server IP Address from REG
    char    cClientName[SRS_MAX_NAME_CLIENT];    // Client name from REG
    char    cUserName[SRS_MAX_NAME_USER];        // Username from REG
    char    cGroupName[SRS_MAX_NAME_GROUP];      // Groupname from user name
    char    cMessage[SRS_MAX_MESSAGE];           // Init message from Server
    DWORD   dwSleep;                             // Wait time from REG
    DWORD   dwLoop;                              // Loop count from REG
    DWORD   dwMsg;                               // Message flg from REG
    int     iRtn;                                // Return value from API()
    DWORD   dwCount;                             // Loop counter
    char    cMsg[256];                           // Debug message 


    wUserID = 0;
    wLobbyID = 0;
    wGroupID = 0;
    wMessageCode = 0;
    iMsg = 0;
    dwCount = 0;

    MessageBox( NULL, "\n\n\n\n\n                 All test start                 \n\n\n\n\n","SRLtestApl",MB_OK );

    //=======================================================================
    //    Start to test
    //=======================================================================
    while( 1 )
    {
        //=======================================================================
        //    Read Test data from REG
        //=======================================================================
         iRtn = SRL_Reg_GetInfo( (LPSTR)SRL_REG_KEY_COM,(LPSTR)SRL_REG_CLIENT,(LPSTR)cClientName );
         if( ( iRtn == -1 ) || ( cClientName[0] == 0 ) )
         {
             MessageBox( NULL, "Error Pass2\nCannot get Client name from REG","SRLtestApl",MB_OK );
             return( -1 );
         }
         iRtn = SRL_Reg_GetInfo( (LPSTR)SRL_REG_KEY_COM,(LPSTR)SRL_REG_USER,(LPSTR)cUserName );
         if( ( iRtn == -1 ) || ( cUserName[0] == 0 ) )
         {
             MessageBox( NULL, "Error Pass3\nCannot get User name from REG","SRLtestApl",MB_OK );
             return( -1 );
         }
         wsprintf( cGroupName, "%s%s", cUserName, cServerIP );
         dwSleep = SRL_Reg_GetInfoDWORD( (LPSTR)SRL_REG_KEY_COM, (LPSTR)"Sleep" );
         if( dwSleep == (DWORD)-1 )
         {
             MessageBox( NULL, "Error Pass4\nCannot get Sleep time from REG","SRLtestApl",MB_OK );
             return( -1 );
         }
         dwLoop = SRL_Reg_GetInfoDWORD( (LPSTR)SRL_REG_KEY_COM, (LPSTR)"Loop" );
         if( dwLoop == (DWORD)-1 )
         {
             MessageBox( NULL, "Error Pass5\nCannot get Loop count from REG","SRLtestApl",MB_OK );
             return( -1 );
         }
         dwMsg = SRL_Reg_GetInfoDWORD( (LPSTR)SRL_REG_KEY_COM, (LPSTR)"Message" );
         if( dwMsg == (DWORD)-1 )
         {
             MessageBox( NULL, "Error Pass6\nCannot get Message flag from REG","SRLtestApl",MB_OK );
             return( -1 );
         }
         iRtn = SRL_Reg_GetInfo( (LPSTR)SRL_REG_KEY_COM,(LPSTR)SRL_REG_SERVERIP,(LPSTR)cServerIP );
         if( ( iRtn == -1 ) || ( cServerIP[0] == 0 ) )
         {
             MessageBox( NULL, "Error Pass1\nCannot get IP address from REG","SRLtestApl",MB_OK );
             return( -1 );
         }

        if( dwMsg == 1)
        {
            iRtn = MessageBox( NULL, "----- Test program start -----\n\nStart to connect to the lobby server from Win32 test tool\n\n", "SRLtestApl", MB_YESNO );
            if( iRtn == IDNO )
            {
                return( 0 );
            }
        }

		//==========================
        // init event environment
        //==========================
        iRtn = SRL_Evt_Initial();
        if( iRtn == -1 )
        {
            sprintf( cMsg, "Error pass7\nSRLtestApl : SRL_Evt_Initial error" );
            return( -1 );
        }

        //==========================
        //  Connect to Server
        //==========================
        iPort = SRL_Snd_Connect( (LPSTR)cServerIP, (LPSTR)cUserName, (LPSTR)cClientName, (LPSTR)cMessage );
        if( iPort == -1 )
        {
            MessageBox( NULL, "Error pass8\nSRL_Snd_Connect error","SRLtestApl",MB_OK );
            return( -1 );
        }
        if( SRL_Reg_SetInfoDWORD( (LPSTR)SRL_REG_KEY_COM, (LPSTR)"port",(DWORD)iPort ) == -1 )
        {
            MessageBox( NULL, "Error pass8\nSRL_Reg_SetInfoDWORD error", "SRLtestApl", MB_OK );
            wUserID = SRL_Mng_GetUserByName( cUserName );
            SRL_Snd_UserDelete( cServerIP, iPort, wUserID );
            SRL_Snd_Disconnect( cServerIP, iPort );
            return( -1 );
        }
        dwPort = SRL_Reg_GetInfoDWORD( (LPSTR)SRL_REG_KEY_COM, (LPSTR)"port" );
        if( dwPort == (DWORD)-1 )
        {
            MessageBox( NULL, "Error pass9\nSRL_Reg_GetInfoDWORD error", "SRLtestApl", MB_OK );
            wUserID = SRL_Mng_GetUserByName( cUserName );
            SRL_Snd_UserDelete( cServerIP, iPort, wUserID );
            SRL_Snd_Disconnect( cServerIP, iPort );
            return( -1 );
        }
        if( dwMsg == 1)
        {
            sprintf( cMsg, "<Test pass1(1/8)>\nSRL_Snd_Connect()API ### success ###\nFinished connecting to Lobby Server. port=%d\nmsg=%s", iPort, cMessage );
            MessageBox( NULL, cMsg, "SRLtestApl", MB_OK );
        }

        //========================
        // Create User
        //========================
        iRtn = SRL_Snd_UserEntry( cServerIP, iPort, cClientName, cUserName );
        Sleep(dwSleep);
        if( iRtn == 0 )
        {
            for( ; ; )
            {
                iRtn = SRL_Apl_Event( );    
                sprintf( cMsg, "SRLtestApl : Waitting SRLEVENT_USER_ADDED(%d) get event(%d)", SRLEVENT_USER_ADDED, iRtn );
                SRL_Dbg_WriteLog( cMsg ); 
                if( (iRtn == SRLEVENT_USER_ADDED) || (iRtn == 0))
                    break;
            }
            if( dwMsg == 1)
            {
                sprintf( cMsg, "<Test pass2(2/8)>\nSRL_Snd_UserEntry()API ### success ###\nSuccessed to entry to lobby server" );
                MessageBox( NULL, cMsg, "SRLtestApl", MB_OK );
            }
        }
        else
        {
            MessageBox( NULL, "Error Pass10\nFailed to make an entry of the user", "SRLtestApl", MB_OK );
            wUserID = SRL_Mng_GetUserByName( cUserName );
            SRL_Snd_UserDelete( cServerIP, iPort, wUserID );
            SRL_Snd_Disconnect( cServerIP, iPort );
            continue;
        }

        //========================
        // Get user list
        //========================
        if( dwMsg == 1)
        {
            iRtn = MessageBox( NULL, "<Test pass3(3/8)>\nCall SRL_Snd_AllGet()API?????\nSend request to get all information from Lobby", "SRLtestApl", MB_YESNO );
        }
        else
        {
            iRtn = IDYES;
        }
        if( iRtn == IDYES ) 
        {
            iRtn = SRL_Snd_AllGet( cServerIP, iPort );
            Sleep(dwSleep);
            if( iRtn == 0 )
            {
                for( ; ; )
                {
                    iRtn = SRL_Apl_Event( );
                    if( (iRtn == SRLEVENT_LOBBY_REFRESH_END) || (iRtn == 0) )
                        break;
                }
                if( dwMsg == 1)
                {
                    MessageBox( NULL, "<Test pass3(3/8)>\nSRL_Snd_AllGet()API ### success ###\nSuccessed to get lobby entry data", "SRLtestApl", MB_OK );
                }
            }
            else
            {
                MessageBox( NULL, "Error Pass11\nFailed to get user entry data", "SRLtestApl", MB_OK );
                wUserID = SRL_Mng_GetUserByName( cUserName );
                SRL_Snd_UserDelete( cServerIP, iPort, wUserID );
                SRL_Snd_Disconnect( cServerIP, iPort );
                continue;
            }
        }

        //========================
        // SendMessage
        //========================
        if( dwMsg == 1)
        {
            iRtn = MessageBox( NULL, "<Test pass4(4/8)>\nCall SRL_Snd_Message()API?????\nSend a message", "SRLtestApl", MB_YESNO );
        }
        else
        {
            iRtn = IDYES;
        }
        if( iRtn == IDYES ) 
        {
            wMessageCode = (WORD)0;
            memset( cMessage, 0, 128 );
            sprintf( cMessage, "Test message to UserID1 count=%d",iMsg );
            iMsg++;
            wUserID = 1;
            iRtn = SRL_Snd_Message( cServerIP, iPort, wUserID, wMessageCode, cMessage );
            Sleep(dwSleep);
            if( iRtn == 0 )
            {
                if( dwMsg == 1)
				{
                    MessageBox( NULL, "<Test pass4(4/8)>\nSRL_Snd_Message()API ### success ###\nSend a message", "SRLtestApl", MB_OK );
				}
			}
            else
            {
                MessageBox( NULL, "Error Pass12\nFailed to send message", "SRLtestApl", MB_OK );
                wUserID = SRL_Mng_GetUserByName( cUserName );
                SRL_Snd_UserDelete( cServerIP, iPort, wUserID );
                SRL_Snd_Disconnect( cServerIP, iPort );
                continue;
            }
        }
# if 0
        //========================
        // Create group
        //========================
        if( dwMsg == 1)
        {
            iRtn = MessageBox( NULL, "<Test pass5(5/8)>\nCall SRL_Snd_GroupMake()API?????\nCreate a group on lobby", "SRLtestApl", MB_YESNO );
        }
        else
        {
            iRtn = IDYES;
        }
        if( iRtn == IDYES ) 
        {
            wUserID = SRL_Mng_GetUserByName( cUserName );
            if( wUserID == SRS_WORD_ERROR )
            {
                MessageBox( NULL, "Error Pass13\nFailed to get UserID from User name", "SRLtestApl", MB_OK );
                wUserID = SRL_Mng_GetUserByName( cUserName );
                SRL_Snd_UserDelete( cServerIP, iPort, wUserID );
                SRL_Snd_Disconnect( cServerIP, iPort );
                continue;
            }
            else
            {
                iRtn = SRL_Snd_GroupMake( cServerIP, iPort, wUserID, cGroupName );
                if( iRtn == 0 )
                {
                    for( ; ; )
                    {
                        iRtn = SRL_Apl_Event( );    
                        if( (iRtn == SRLEVENT_GROUP_ADDED) || (iRtn == 0) )
                            break;
                    }
                    if( dwMsg == 1)
                    {
                        MessageBox( NULL, "<Test pass5(5/8)>\nSRL_Snd_GroupMake()API ### success ###\nSuccessed to create group on lobby", "SRLtestApl", MB_OK );
                    }
                }
                else
                {
                    MessageBox( NULL, "Error Pass14\nFailed to create group", "SRLtestApl", MB_OK );
                    wUserID = SRL_Mng_GetUserByName( cUserName );
                    SRL_Snd_UserDelete( cServerIP, iPort, wUserID );
                    SRL_Snd_Disconnect( cServerIP, iPort );
                    continue;
                }
            }

            //========================
            // Delete group
            //========================
            if( dwMsg == 1)
            {
                iRtn = MessageBox( NULL, "<Test pass6(6/8)>\nCall SRL_Snd_GroupDefect()API?????\nDefact group", "SRLtestApl", MB_YESNO );
            }
            else
            {
                iRtn = IDYES;
            }
            if( iRtn == IDYES ) 
            {
                wGroupID = SRL_Mng_GetGroupByName( cGroupName );
                if( wGroupID == SRS_WORD_ERROR )
                {
                    MessageBox( NULL, "Error Pass15\nFailed to get GroupID from Group name", "SRLtestApl", MB_OK );
                    wUserID = SRL_Mng_GetUserByName( cUserName );
                    SRL_Snd_UserDelete( cServerIP, iPort, wUserID );
                    SRL_Snd_Disconnect( cServerIP, iPort );
                    continue;
                }
                iRtn = SRL_Snd_GroupDefect( cServerIP, iPort, wUserID, wGroupID );
                if( iRtn == 0 )
                {
                    for( ; ; )
                    {
                        iRtn = SRL_Apl_Event( );    
                        if( (iRtn == SRLEVENT_GROUP_LEAVE) || (iRtn == 0) )
                            break;
                    }
                    if( dwMsg == 1)
                    {
                        MessageBox( NULL, "<Test pass6(6/8)>\nSRL_Snd_GroupDefect()API ### success ###\nSuccessed to defact group from lobby", "SRLtestApl", MB_OK );
                    }
                }
                else
                {
                    MessageBox( NULL, "Error Pass16\nFailed to destroy group", "SRLtestApl", MB_OK );
                    wUserID = SRL_Mng_GetUserByName( cUserName );
                    SRL_Snd_UserDelete( cServerIP, iPort, wUserID );
                    SRL_Snd_Disconnect( cServerIP, iPort );
                    continue;
                }
            }
        }
#endif
        //========================
        // Delete user
        //========================
        if( dwMsg == 1)
        {
            iRtn = MessageBox( NULL, "<Test pass7(7/8)>\nCall SRL_Snd_UserDelete()API \nDelete user from lobby", "SRLtestApl", MB_OK );
        }
        wUserID = SRL_Mng_GetUserByName( cUserName );
        if( wUserID == SRS_WORD_ERROR )
        {
            MessageBox( NULL, "Error Pass17\nFailed to get UserID from user name", "SRLtestApl", MB_OK );
            wUserID = SRL_Mng_GetUserByName( cUserName );
            SRL_Snd_UserDelete( cServerIP, iPort, wUserID );
            SRL_Snd_Disconnect( cServerIP, iPort );
            continue;
        }
        else
        {
            iRtn = SRL_Snd_UserDelete( cServerIP, iPort, wUserID );
            Sleep(dwSleep);
            if( iRtn == 0 )
            {
                for( ; ; )
                {
                    iRtn = SRL_Apl_Event( );    
                    if( (iRtn == SRLEVENT_USER_REMOVED) || (iRtn == 0))
                        break;
                }
                if( dwMsg == 1)
                {
                    MessageBox( NULL, "<Test pass7(7/8)>\nSRL_Snd_GroupDefect()API ### success ###\nSuccessed to destroy user", "SRLtestApl", MB_OK );
                }
            }
            else
            {
                MessageBox( NULL, "Error Pass18\nFailed to destroy user from lobby", "SRLtestApl", MB_OK );
                wUserID = SRL_Mng_GetUserByName( cUserName );
                SRL_Snd_UserDelete( cServerIP, iPort, wUserID );
                SRL_Snd_Disconnect( cServerIP, iPort );
                continue;
            }
        }

        //==========================
        //  Disconnect from Server
        //==========================
        iPort = SRL_Snd_Disconnect( (char *)cServerIP, (int) iPort );
        if( iPort == -1 )
        {
            MessageBox( NULL, "Error Pass19\nSRL_Snd_Disconnect error", "SRLtestApl", MB_OK );
            return( -1 );
        }
        if( dwMsg == 1)
        {
            MessageBox( NULL, "<Test pass8(8/8)>\nSRL_Snd_Disconnect()API ### success ###\nSuccessed Disconnect from lobby server", "SRLtestApl", MB_OK );
        }
        Sleep(dwSleep);

        //==========================
        //  Exit from test program
        //==========================
        if( dwLoop == 0 )
        {
            break;
        }
        else
        {
            dwCount ++;
            if( dwLoop == dwCount )
            {
                break;
            }
        }
    }

    MessageBox( NULL, "\n\n\n\n\n                 All test success                 \n\n\n\n\n","SRLtestApl",MB_OK );
    return( 0 );
}



int    SRL_Apl_Event( void )
{
    int     iMaxLoop = 10;
    int     iLoop;
    int     iRtn;
    int     iEventID;
    BOOL    fRtn;
    SRLEVENTMNG cEventMng;

    memset( (char *)&cEventMng, 0, SRLEVENTMNG_SZ );
    for( iLoop = 0 ; iLoop < iMaxLoop ; iLoop++ )
    {
        iRtn = SRL_Evt_GetEventCount( SRL_EVENTMODE_EVENT );
        SRL_Dbg_DebugPrintf( 1,TEXT("SRLtestApl : SRL_Evt_GetEventCount %d"),iRtn );
        if( iRtn > 0 )
        {
            break;
        }
        Sleep( 2000 );
    }
    if( iLoop == iMaxLoop )
    {
        SRL_Dbg_WriteLog( "SRLtestApl : Event loop over" );
        return( 0 );
    }
    fRtn = SRL_Evt_GetEvent( SRL_EVENTMODE_EVENT, (LPSRLEVENTMNG)&cEventMng ); 
    if( fRtn == FALSE )
        return( -1 );
    iEventID = cEventMng.EM_dwEventID;
    SRL_Dbg_DebugPrintf( 1,TEXT("SRLtestApl : SRL_Evt_GetEvent %d"),iEventID );

    return( iEventID );
}
