/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRScom.h
 *  Content:    Lobby server & Lobby client common include 
 ***************************************************************************/
#ifndef _SRS_COM_H_
#define _SRS_COM_H_

/***************************************************************************
 *
 *  Common
 *
 ***************************************************************************/
//=========================================
// Port number
//=========================================
#define	SRS_PORT_SERVER		7000			// This port use to connect to server
#define	SRS_PORT_CLIENT		6000			// This port use to connect to client

//=========================================
//   Process name
//=========================================
#define	SRS_PROC_INITIAL	TEXT("SRSinitial")		// Wait request process
#define	SRS_PROC_LOG		TEXT("SRSlog.exe")		// Display log process
#define	SRS_PROC_LOBBY		TEXT("SRSlobby")		// Server main process
#define SRL_PROC_RCV		TEXT("SRLreceive.exe")	// Client receive process
#define SRL_PROC_SEND		TEXT("SRLsend.exe")	    // Client send process

//=========================================
//   Message number
//=========================================
#define SRS_MSG_LOG		WM_USER + 1					// For Connection log 

//=========================================
//   Return value
//=========================================
#define SRS_WORD_ERROR	(WORD)65535					// Error number of WORD type

//=========================================
//   Timmer
//=========================================
#define SRS_ANSER_WAIT_TIMER	60000				// Client wait time (millisecond)


/***************************************************************************
 *
 *  Lobby server management 
 *
 ***************************************************************************/
//  User status
#define	SRS_SEQ_NOENTRY		(DWORD)0x000000	// NOENTRY
#define	SRS_SEQ_LOBBYENTRY	(DWORD)0x010000	// Lobby entry, Game no entry
#define	SRS_SEQ_GAMEENTRY	(DWORD)0x011000	// Game select, Group no entry
#define	SRS_SEQ_GROUPENTRY	(DWORD)0x011100	// Group entry
#define	SRS_SEQ_PLAY		(DWORD)0x011110	// Play game

//  Max value (default value)
#define SRS_MAX_LOBBY_USER		64			// Max user of one lobby
#define SRS_MAX_LOBBY_GROUP		32			// Max group of one lobby
#define SRS_MAX_GROUP_USER    	64			// Max user entry for one group

#define SRS_MAX_NAME_CLIENT		16			// Max client name
#define SRS_MAX_NAME_USER		40			// Max user name
#define SRS_MAX_NAME_GAME		40			// Max game name
#define SRS_MAX_NAME_GROUP		40			// Max group name
#define SRS_MAX_NAME_LOBBY		40			// Max lobby name    

#define SRS_MAX_PASSWORD		40			// Area for password    
#define SRS_MAX_USERAREA		40			// Area for User data    
#define SRS_MAX_MESSAGE			128			// Max message size
#define SRS_MAX_LOGMSG			256			// Max log message size

//  Management ID
#define	SRS_ID_MAINLOBBY	(WORD)0			// Main lobby ID

//  Entry game status
#define SRS_GAME_PLAY		(WORD)0			// Play game
#define SRS_GAME_WATCH		(WORD)1			// Watch game

//====================================
//  User information area
//====================================
typedef	struct SRS_USER_ITEM
{
	char	USI_cClientName[SRS_MAX_NAME_CLIENT];	// Client name
	char	USI_cUserName[SRS_MAX_NAME_USER];		// User name
	char	USI_cPassword[SRS_MAX_PASSWORD];		// Password (Resrved)
	int		USI_iIp;								// IP address
	int		USI_iPort;								// Port number
	WORD	USI_wUserID;							// User ID
	WORD	USI_wGameID;							// Game ID
	WORD	USI_wLobbyID;							// Lobby ID
	WORD	USI_wGroupID;							// Group ID
	DWORD	USI_dwCondetion;						// Status
	char	USI_cUserArea[SRS_MAX_USERAREA];		// User area
	SYSTEMTIME	USI_time;							// User time
} SRS_USERITEM, * LPSRSUSERITEM;				
#define SRS_USER_ITEM_SZ	(sizeof(struct SRS_USER_ITEM))

//
// Information management area
//
typedef struct SRS_INFO_USER
{
	WORD	US_wMaxUser;						// Max user
	WORD	US_wEntryUser;						// Entry user
	struct  SRS_USER_ITEM US_info_user[1];		// User information
} SRS_INFOUSER, * LPSRS_INFOUSER;
#define SRS_INFO_USER_SZ		(sizeof(struct SRS_INFO_USER))
#define SRS_INFO_USER_COM_SZ	(SRS_INFO_USER_SZ - SRS_USER_ITEM_SZ)	// Common area size

//====================================
//  Game information area
//====================================
typedef struct SRS_GAME_ITEM
{
	int		GMI_iLockword;						// Lock word
	char	GMI_cGameName[SRS_MAX_NAME_GAME];	// Game name
	WORD	GMI_wGameID;						// Game ID
	WORD	GMI_wMaxGameUser;					// Max entry user
	DWORD	GMI_Reserve;						// Reserve
} SRS_GAMEITEM, * LPSRS_GAMEITEM;
#define SRS_GAME_ITEM_SZ	(sizeof(struct SRS_GAME_ITEM))

//
// Information management area
//
typedef struct	SRS_INFO_GAME
{
	WORD	GM_wMaxGame;						// Max game 
	WORD	GM_wEntryGame;						// Entry game
	struct  SRS_GAME_ITEM  GM_info_game[1];		// Game information
} SRS_INFOGAME, * LPSRS_INFOGAME;
#define SRS_INFO_GAME_SZ		(sizeof(struct SRS_INFO_GAME))
#define SRS_INFO_GAME_COM_SZ	(SRS_INFO_GAME_SZ - SRS_GAME_ITEM_SZ)	// Common area size

//====================================
//  Lobby information area
//====================================
typedef struct	SRS_LOBBY_ITEM
{
	int		LBI_iLockword;						// Lock word
	char	LBI_cLobbyName[SRS_MAX_NAME_LOBBY];	// Lobby name
	WORD	LBI_wLobbyID;						// Lobby ID
	WORD	LBI_Reserve;						// Reserve
	WORD	LBI_wMaxLobbyUser;					// Max user
	WORD	LBI_wLobbyUser;						// Entry user
	WORD	LBI_wUserID[SRS_MAX_LOBBY_USER];	// UserID
	WORD	LBI_wGroupID[SRS_MAX_LOBBY_GROUP];	// GroupID
} SRS_LOBBYITEM, * LPSRS_LOBBYITEM;
#define SRS_LOBBY_ITEM_SZ	(sizeof(SRS_LOBBY_ITEM))

//
// Information management area
//
typedef struct	SRS_INFO_LOBBY
{
	WORD	LB_wMaxLobby;						// Max Lobby 
	WORD	LB_Reserved;						// Reserve
	struct  SRS_LOBBY_ITEM LB_info_lobby[1];	// Lobby information
} SRS_INFOLOBBY, * LPSRS_INFOLOBBY;
#define SRS_INFO_LOBBY_SZ		(sizeof(struct SRS_INFO_LOBBY))
#define SRS_INFO_LOBBY_COM_SZ	(SRS_INFO_LOBBY_SZ - SRS_LOBBY_ITEM_SZ)	// Common area size

//====================================
//  Group information area
//====================================
typedef struct	SRS_GROUP_ITEM
{
	int		GPI_iLockword;						// Lock word
	char	GPI_cGroupName[SRS_MAX_NAME_GROUP];	// Group name
	WORD	GPI_wGroupID;						// Group ID
	WORD	GPI_wGameID;						// Game ID
	WORD	GPI_wEntryUser;						// Entry user
	WORD   	GPI_wMaxUser;						// Max user
	WORD	GPI_wUserID[SRS_MAX_GROUP_USER];	// Entry ID
} SRS_GROUPITEM, * LPSRS_GROUPITEM; 
#define SRS_GROUP_ITEM_SZ	(sizeof(SRS_GROUP_ITEM))

//
// Information management area
//
typedef struct	SRS_INFO_GROUP
{
	WORD	GP_wMaxGroup;						// Max group
	WORD	GP_wEntryGroup;						// Entry group
	struct  SRS_GROUP_ITEM	GP_info_group[1];	// Group information
} SRS_INFOGROUP, * LPSRS_INFOGROUP;
#define SRS_INFO_GROUP_SZ		(sizeof(struct SRS_INFO_GROUP))
#define SRS_INFO_GROUP_COM_SZ	(SRS_INFO_GROUP_SZ - SRS_GROUP_ITEM_SZ)	// Common area size

/***************************************************************************
 *
 *  Lobby client / server interface
 *
 ***************************************************************************/
//==============================
//  Request code
//==============================
//
//  Client -> Server
//
#define IF_REQ_CONNECT		0x0001		// Request connect
#define IF_REQ_DISCONNECT	0x0002		// Request disconnect
#define IF_REQ_LOGMSG		0x0003		// Request logging massage

#define	IF_REQ_ALL			0x0101		// Request all information
#define IF_REQ_USER_ENTRY	0x0111		// Request user entry
#define IF_REQ_USER_DELETE	0x0112		// Request user delete
#define IF_REQ_LOBBY_ENTRY	0x0121		// Request Lobby entry
#define IF_REQ_LOBBY_DEFECT	0x0122		// Request Lobby defact
#define IF_REQ_GROUP_MAKE	0x0131		// Request group create
#define IF_REQ_GROUP_JOIN	0x0132		// Request group join
#define IF_REQ_GROUP_DEFECT	0x0133		// Request group defact
#define IF_REQ_GAME_JOIN	0x0141		// Request game join
#define IF_REQ_GAME_DEFECT	0x0142		// Request game defact
#define IF_REQ_GAME_START	0x0143		// Request game start
#define IF_REQ_GAME_END		0x0144		// Request game end
#define IF_REQ_SENDMSG		0x0151		// Request send message
#define IF_REQ_SAVE_INFO	0x0161		// Request information save

//
// Server -> Client
//
#define IF_REQ_RENEWAL		0x0201		// Information renewal
#define IF_REQ_RCVMSG		0x0202		// Recive message

//
// Command -> server request
//
#define IF_REQ_TERMINATE	0xFFFF		// Request terminate

//================================
//  Result code
//================================
#define IF_CMP_SUCCESS		0x0000		// Success
#define IF_CMP_MAXOVER		0xFF01		// Over max value
#define IF_CMP_MULTI		0xFF02		// User Dup
#define IF_CMP_AREAOVER		0xFF03		// Not Resource 
#define IF_CMP_SEQERR		0xFF04		// Request error
#define IF_CMP_PROCERR		0xFF05		// Lobby process running error
#define IF_CMP_ERROR		0xFFFF		// SYSTEM ERROR

//====================================
//  Interface block
//====================================
typedef struct  SRS_IF_FIX
{
	WORD	IF_wRequest;			// Request code
	WORD	IF_wResult;				// Result code
	int		IF_iInformationSize;	// Protocol size
	int		IF_iPortNo;				// Server port number
	int		IF_iIp;					// Client IP address
	char	IF_cInformation[4];		// Information area
} SRS_IFFIX, * LPSRS_IFFIX;
#define	SRS_IF_FIX_SZ	(sizeof(struct SRS_IF_FIX) - 4)

//====================================
//  Request
//====================================
//=========================
//  Request connect 
//=========================
typedef struct	SRS_IF_CONNECT
{
	WORD	IF_CN_wMaxUser;			// Max user
	WORD	IF_CN_wMaxLobby;		// Max lobby
	WORD	IF_CN_wMaxGroup;		// Max group
	WORD	IF_CN_wMaxGame;			// Max game
	char	IF_CN_cMessage[SRS_MAX_MESSAGE];
} SRS_IFCONNECT, * LPSRS_IFCONNECT;
#define	SRS_IF_CONNECT_SZ 		(sizeof(struct SRS_IF_CONNECT))

//========================
//  Logging message
//========================
typedef struct	SRS_IF_LOGMSG
{
	char	IF_LM_cMessage[SRS_MAX_LOGMSG];		// display message
} SRS_IFLOGMSG, * LPSRS_IFLOGMSG;
#define	SRS_IF_LOGMSG_SZ 		(sizeof(struct SRS_IF_LOGMSG))

//========================
//  User entry 
//========================
typedef struct	SRS_IF_USER_ENTRY
{
	char	IF_UE_cClientName[SRS_MAX_NAME_CLIENT];	// Client name
	char	IF_UE_cUserName[SRS_MAX_NAME_USER];		// User name
} SRS_IFUSERENTRY, * LPSRS_IFUSERENTRY;
#define SRS_IF_USER_ENTRY_SZ	(sizeof(struct SRS_IF_USER_ENTRY))

//========================
// User Delete
//========================
typedef struct	SRS_IF_USER_DELETE
{
	WORD	IF_UD_wUserID;			// User ID
	WORD	IF_UD_wReserved;		// Reserve
} SRS_IFUSERDELETE, * LPSRS_IFUSERDELETE;
#define SRS_IF_USER_DELETE_SZ	(sizeof(struct SRS_IF_USER_DELETE))

//========================
//  Lobby entry 
//========================
typedef struct	SRS_IF_LOBBY_ENTRY
{
	WORD	IF_LE_wUserID;			// User ID
	WORD	IF_LE_wLobbyID;			// Lobby ID
} SRS_IFLOBBYENTRY, * LPSRS_IFLOBBYENTRY;
#define SRS_IF_LOBBY_ENTRY_SZ	(sizeof(struct SRS_IF_LOBBY_ENTRY))

//========================
//  Lobby defact 
//========================
typedef struct	SRS_IF_LOBBY_DEFECT
{
	WORD	IF_LD_wUserID;			// User ID
	WORD	IF_LD_wLobbyID;			// Lobby ID
} SRS_IFLOBBYDEFECT, * LPSRS_IFLOBBYDEFECT;
#define SRS_IF_LOBBY_DEFECT_SZ	(sizeof(struct SRS_IF_LOBBY_DEFECT))

//========================
//  Group Create 
//========================
typedef struct	SRS_IF_GROUP_MAKE
{
	WORD	IF_GM_wUserID;							// Main user ID
	WORD	IF_GMwReserved;							// Reserve
	char	IF_GM_cGroupName[SRS_MAX_NAME_GROUP];	// Group name
} SRS_IFGROUPMAKE, * LPSRS_IFGROUPMAKE;
#define SRS_IF_GROUP_MAKE_SZ	(sizeof(struct SRS_IF_GROUP_MAKE))

//========================
//  Group Join
//========================
typedef struct	SRS_IF_GROUP_JOIN
{
	WORD	IF_GJ_wUserID;			// User ID
	WORD	IF_GJ_wGroupID;			// Group ID
	WORD	IF_GJ_wCondition;		// Join condition
	WORD	IF_GJ_wReserved;		// Reserve
} SRS_IFGROUPJOIN, * LPSRS_IFGROUPJOIN;
#define SRS_IF_GROUP_JOIN_SZ	(sizeof(struct SRS_IF_GROUP_JOIN))

//========================
//  Group defact
//========================
typedef struct	SRS_IF_GROUP_DEFECT
{
	WORD	IF_GD_wUserID;			// User ID
	WORD	IF_GD_wGroupID;			// Group ID
} SRS_IFGROUPDEFECT, * LPSRS_IFGROUPDEFECT;
#define SRS_IF_GROUP_DEFECT_SZ	(sizeof(struct SRS_IF_GROUP_DEFECT))

//========================
//  Group delete
//========================
typedef struct	SRS_IF_GROUP_DELETE
{
	WORD	IF_GL_wGroupID;			// Group ID
	WORD	IF_GL_wReserved;		// Reserve
} SRS_IFGROUPDELETE, * LPSRS_IFGROUPDELETE;
#define SRS_IF_GROUP_DELETE_SZ	(sizeof(struct SRS_IF_GROUP_DELETE))

//========================
//  Game join
//========================
typedef struct	SRS_IF_GAME_JOIN
{
	WORD	IF_GJ_wUserID;			// User ID
	WORD	IF_GJ_wGameID;			// Game ID
	WORD	IF_GJ_wCondition;		// Join condition
	WORD	IF_GJ_wReserved;		// Reserve
} SRS_IFGAME_JOIN, * LPSRS_IFGAMEJOIN;
#define SRS_IF_GAME_JOIN_SZ	(sizeof(struct SRS_IF_GAME_JOIN))

//========================
//  Game defact
//========================
typedef struct	SRS_IF_GAME_DEFECT
{
	WORD	IF_GD_wUserID;			// User ID
	WORD	IF_GD_wGameID;			// Game ID
} SRS_IFGAMEDEFECT, * LPSRS_IFGAMEDEFECT;
#define SRS_IF_GAME_DEFECT_SZ	(sizeof(struct SRS_IF_GAME_DEFECT))

//========================
//  Game start
//========================
typedef struct	SRS_IF_GAME_START
{
	WORD	IF_GS_wUserID;			// User ID
	WORD	Reserve;				// Reserve
} SRS_IFGAMESTART, * LPSRS_IFGAMESTART;
#define SRS_IF_GAME_START_SZ	(sizeof(struct SRS_IF_GAME_START))

//========================
//  Game end
//========================
typedef struct	SRS_IF_GAME_END
{
	WORD	IF_GE_wUserID;			// User ID
	WORD	IF_GE_Reserve;			// Reserve
} SRS_IFGAMEEND, * LPSRS_IFGAMEEND;
#define SRS_IF_GAME_END_SZ	(sizeof(struct SRS_IF_GAME_END))

//========================
//  information save
//========================
typedef struct	SRS_IF_SAVE_INFO
{
	WORD	IF_SI_wUserID;					// User ID
	WORD	IF_SI_Reserve;					// Reserve
	char	IF_SI_cInfo[SRS_MAX_USERAREA];	// Extra information
} SRS_IFSAVEINFO, * LPSRS_IFSAVEINFO;
#define SRS_IF_SAVE_INFO_SZ	(sizeof(struct SRS_IF_SAVE_INFO))

//========================
//  Information renewal 
//========================
typedef struct	SRS_IF_RENEWAL
{
	WORD	IF_RE_wUserInfoNo;		// User information
	WORD	IF_RE_wLobbyInfoNo;		// Lobby information
	WORD	IF_RE_wGroupInfoNo;		// Group information
	WORD	IF_RE_wGameInfoNo;		// Game information
	char	IF_RE_cInfo[4];			// Information area
} SRS_IFRENEWAL, * LPSRS_IFRENEWAL;
#define SRS_IF_RENEWAL_SZ	(sizeof(struct SRS_IF_RENEWAL) - 4 )

//========================
//  Snd/Rcv Message
//========================
typedef struct	SRS_IF_MESSAGE
{
	WORD	IF_MS_wUserID;						// To user ID
	WORD	IF_MS_wMessageCode;					// Message code
	char	IF_MS_cMessage[SRS_MAX_MESSAGE];	// Message
} SRS_IFMESSAGE, * LPSRS_IFMESSAGE;
#define SRS_IF_MESSAGE_SZ	(sizeof(struct SRS_IF_MESSAGE))

#endif
