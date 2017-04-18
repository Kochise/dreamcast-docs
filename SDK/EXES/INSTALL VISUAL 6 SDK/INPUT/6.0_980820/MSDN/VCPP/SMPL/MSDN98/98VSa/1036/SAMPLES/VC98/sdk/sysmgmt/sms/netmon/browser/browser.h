
//==========================================================================================================================
//  MODULE: browser.h
//
//  Description:
//
//  Bloodhound parser DLL for MS Browser
//
//  Modification History
//  Written by Scottji 6/94
//
//
//==========================================================================================================================

// question:  need to look at bh.h and inilib.h
#include <windows.h>
#include <string.h>
#include <bh.h>
#include <parser.h>
#include <inilib.h>
#include <malloc.h>
#include <stdlib.h>

//question:
#pragma pack(1)

//
// Browser Commands
//
#define HostAnnouncement				1   //  done
#define AnnouncementRequest				2   //  done
#define Election					8   //
#define GetBackupListReq				9   //  done
#define GetBackupListResp				10  //a done
#define BecomeBackup					11  //b done
#define WkGroupAnnouncement				12  //c change
#define MasterAnnouncement				13  //d done
#define ResetBrowserState				14  //e
#define LocalMasterAnnouncement				15  //f done

//
// Struct for Recognize Function
//
typedef struct _BrowserFRAME
{
    BYTE        command;
    CHAR        data;
} BrowserFRAME;

typedef BrowserFRAME UNALIGNED *LPBrowserFRAME;


//
// Lanman names from lmcons.h
//
#define CNLEN       15                  // Computer name length
#define LM20_CNLEN  15                  // LM 2.0 Computer name length
#define DNLEN       CNLEN               // Maximum domain name length
#define LM20_DNLEN  LM20_CNLEN          // LM 2.0 Maximum domain name length


//
// Mailslot name strings.
//
#define SMB_MAILSLOT_PREFIX "\\MAILSLOT"
#define UNICODE_SMB_MAILSLOT_PREFIX L"\\MAILSLOT"
#define SMB_MAILSLOT_PREFIX_LENGTH (sizeof(SMB_MAILSLOT_PREFIX) - 1)
#define UNICODE_SMB_MAILSLOT_PREFIX_LENGTH \
                    (sizeof(UNICODE_SMB_MAILSLOT_PREFIX) - sizeof(WCHAR))

#define MAILSLOT_LANMAN_NAME SMB_MAILSLOT_PREFIX "\\LANMAN"
#define MAILSLOT_BROWSER_NAME SMB_MAILSLOT_PREFIX "\\BROWSE"
//#define ANNOUNCEMENT_MAILSLOT_NAME     "\\\\*" ITRANS_MS_NAME
#define MAXCOMMENTSZ 256                // Multipurpose comment length
#define LM20_MAXCOMMENTSZ 48            // LM 2.0 Multipurpose comment length


//
//Browser netbios name extensions.
//
#define WORKSTATION_SIGNATURE       '\0'
#define SERVER_SIGNATURE            ' '
#define PRIMARY_DOMAIN_SIGNATURE    '\0'
#define PRIMARY_CONTROLLER_SIGNATURE '\x1B'
#define DOMAIN_CONTROLLER_SIGNATURE '\x1C'
#define MASTER_BROWSER_SIGNATURE    '\x1D'
#define BROWSER_ELECTION_SIGNATURE  '\x1E'
#define DOMAIN_ANNOUNCEMENT_NAME    "\x01\x02__MSBROWSE__\x02\x01"


//
//  AnnouncementRequest
//
//  The request announcement packet is sent by clients to request that
//  remote servers announce themselves.
//

typedef struct _REQUEST_ANNOUNCE_PACKET_1 {      // Contents of request announcement
    UCHAR    Type;
    UCHAR    Flags;                 // Unused Flags
    CHAR     Reply[LM20_CNLEN+1];
}  REQUEST_ANNOUNCE_PACKET_1, UNALIGNED *LP_ANNC_REQ;

//typedef REQUEST_ANNOUNCE_PACKET_1 UNALIGNED *LP_ANNC_REQ;


//  HostAnnouncement and LocalMasterAnnouncement
//
// General announcement message.  This is used for opcodes:
//
//

typedef struct _BROWSE_ANNOUNCE_PACKET_1 {
    UCHAR       BrowseType;
    UCHAR       UpdateCount;    // Inc'ed when announce data changed.
    ULONG       Periodicity;    // announcement cycle in milliseconds

    UCHAR       ServerName[LM20_CNLEN+1];
    UCHAR       VersionMajor;
    UCHAR       VersionMinor;   /*  "  "   "   "    "    "    "   */
    ULONG       Type;           // Server type.
    WORD        HAElectionVersion;
    WORD	HAConstant;
    CHAR        Comment[LM20_MAXCOMMENTSZ+1];
} BROWSE_ANNOUNCE_PACKET, UNALIGNED *LP_HA_FRAME;

// WkGroupAnnouncement
//
//
typedef struct _WKGRP_ANNOUNCE_PACKET_1 {
    UCHAR       BrowseType;
    UCHAR       UpdateCount;    // Inc'ed when announce data changed.
    ULONG       Periodicity;    // announcement cycle in milliseconds

    UCHAR       ServerName[LM20_CNLEN+1];
    UCHAR       VersionMajor;
    UCHAR       VersionMinor;   /*  "  "   "   "    "    "    "   */
    ULONG       Type;           // Server type.
    ULONG       CommentPtr;
    CHAR        Comment[LM20_MAXCOMMENTSZ+1];
} WKGRP_ANNOUNCE_PACKET, UNALIGNED *LP_WKGRP_FRAME;


// GetBackupListReq
//
//
typedef struct _BACKUP_LIST_REQUEST_1 {
    UCHAR	Type;
    UCHAR       RequestedCount;
    ULONG       Token;
} BACKUP_LIST_REQUEST_1, UNALIGNED *LP_BACK_REQ_FRAME;



//  BackupListResp
//  Response containing a backup server list.
//

typedef struct _BACKUP_LIST_RESPONSE_1 {
    UCHAR 	Type;
    UCHAR       BackupServerCount;
    ULONG       Token;
    UCHAR       BackupServerList[51];
} BACKUP_LIST_RESPONSE_1, UNALIGNED *LP_BACK_RESP;



//  BecomeBackup
//  Message indicating that a potential browser server should become a backup
//  server.
//
typedef struct _BECOME_BACKUP_1 {
    UCHAR 	Type;
    UCHAR       BrowserToPromote[1];
} BECOME_BACKUP_1;

typedef BECOME_BACKUP_1 UNALIGNED *LP_BECOME_BACKUP;



//  MasterAnnouncement
//  Send from master to domain master.
//

typedef struct _MASTER_ANNOUNCEMENT_1 {
    UCHAR 	Type;
    UCHAR       MasterName[16];
} MASTER_ANNOUNCEMENT_1, UNALIGNED *LP_MASTER_ANNC;



//  Election
//  Sent during the election process.
//

typedef struct _REQUEST_ELECTION_1 {
    UCHAR 	Type;
    UCHAR       Version;
    ULONG       Criteria;
    ULONG       TimeUp;
    ULONG       MustBeZero;
    UCHAR       ServerName[1];
} REQUEST_ELECTION_1, UNALIGNED *LP_ELECTION;


#define ELECTION_CR_OSTYPE      0xFF000000L // Native OS running on server
#define ELECTION_CR_OSWFW       0x01000000L //  Windows for workgroups server
#define ELECTION_CR_WIN_NT      0x10000000L //  Windows/NT Server
#define ELECTION_CR_LM_NT       0x20000000L //  Lan Manager for Windows/NT

#define ELECTION_CR_REVISION    0x00FFFF00L // Browser software revision
#define ELECTION_MAKE_REV(major, minor) (((major)&0xffL)<<16|((minor)&0xFFL)<<8)

#define ELECTION_CR_DESIRE      0x000000FFL // Desirability of becoming master.

//
//  Election desirability within criteria.
//
//  Most important is a running PDC, next is a configured domain master.
//
//  After that come running masters, then configured backups, then existing
//  running backups.
//

#define ELECTION_DESIRE_AM_BACKUP  0x00000001L // Currently is backup
#define ELECTION_DESIRE_AM_CFG_BKP 0x00000002L // Always want to be
                                               //  master - set if backup &&
                                               //  MaintainServerList==YES
#define ELECTION_DESIRE_AM_MASTER  0x00000004L // Currently is master
#define ELECTION_DESIRE_AM_DOMMSTR 0x00000008L // Configured as domain master

#define ELECTION_DESIRE_AM_PDC     0x00000080L // Machine is a lanman NT server.

// Machines running WINS client are important because they are more capable
// of connecting to a PDC who's address was configured via DHCP.

#define ELECTION_DESIRE_WINS_CLIENT 0x00000020L // Transport running WINS client


// ResetBrowserState
//  "Tickle" packet - sent to change state of browser.
//

typedef struct _RESET_STATE_1 {
        UCHAR 	Type;
        UCHAR   Options;
} RESET_STATE_1, *LP_RESET;

#define RESET_STATE_STOP_MASTER 0x01    // Stop being master
#define RESET_STATE_CLEAR_ALL   0x02    // Clear all browser state.
#define RESET_STATE_STOP        0x04    // Stop the browser service.


//
// Type Server
//
#define	SV_TYPE_WORKSTATION		0x00000001
#define	SV_TYPE_SERVER			0x00000002
#define	SV_TYPE_SQLSERVER		0x00000004
#define	SV_TYPE_DOMAIN_CTRL		0x00000008
#define	SV_TYPE_DOMAIN_BAKCTRL		0x00000010
#define	SV_TYPE_TIME_SOURCE		0x00000020
#define	SV_TYPE_AFP			0x00000040
#define	SV_TYPE_NOVELL			0x00000080
#define	SV_TYPE_DOMAIN_MEMBER		0x00000100
#define	SV_TYPE_PRINTQ_SERVER		0x00000200
#define	SV_TYPE_DIALIN_SERVER		0x00000400
#define	SV_TYPE_XENIX_SERVER		0x00000800
#define	SV_TYPE_NT			0x00001000
#define	SV_TYPE_POTENTIAL_BROWSER	0x00010000
#define	SV_TYPE_BACKUP_BROWSER		0x00020000
#define	SV_TYPE_MASTER_BROWSER		0x00040000
#define	SV_TYPE_DOMAIN_MASTER		0x00080000
#define	SV_TYPE_LOCAL_LIST_ONLY		0x40000000
#define	SV_TYPE_DOMAIN_ENUM		0x80000000


//===========================================================================
//  Function prototypes.
//===========================================================================

// question:  what other functions?

extern VOID  WINAPIV BrowserFormatSummary(LPPROPERTYINST lpPropertyInst);
extern VOID  WINAPIV BrowserFormatCommand(LPPROPERTYINST lpPropertyInst);
extern VOID  WINAPIV FormatBrowserSummary(LPPROPERTYINST lpPropertyInst);

//=============================================================================
//  Helper functions.
//=============================================================================

//question: what helper functions?

// extern WORD   WINAPI GetBrowserFrameSize(LPBrowser Frame);


//=============================================================================
//  Format Table.
//=============================================================================
// question:  what is this?


//=============================================================================
//  Manifests for Creating Handoff Set
//=============================================================================

//question: what is handoff set?

//#define MAX_SAPS            50
//#define MAX_ETYPES          50

#define ELECTION_DESIRE_AM_BACKUP  0x00000001L // Currently is backup
#define ELECTION_DESIRE_AM_CFG_BKP 0x00000002L // Always want to be


#pragma pack()

//=============================================================================
//  Property table index constants
//=============================================================================

#define Browser_COMMAND         	0
#define Browser_SUMMARY         	1
#define HA_UpdateCount			2
#define HA_Periodicity			3
#define HA_ServerName			4
#define HA_VersionMajor			5
#define HA_VersionMinor			6
#define HA_Type_Flag_Summary		7
#define HA_Type				8
#define HA_ElectionVersion		9
#define HA_Constant			10
#define AR_Flags			11
#define AR_Reply			12
#define BREQ_RequestedCount		13
#define BREQ_Token			14
#define BRSP_ServerCnt			15
#define BRSP_Token			16
#define BRSP_ServerList			17
#define MA_MasterName			18
#define ELEC_Version			19
#define ELEC_Criteria			20
#define ELEC_TimeUp			21
#define ELEC_MustBeZero			22
#define ELEC_ServerName			23
#define ELEC_OS_Summary			24
#define ELEC_OS				25
#define ELEC_Revision			26
#define ELEC_Desire_Summary		27
#define ELEC_Desire			28
#define RST_Options			29
#define WKGRP_CommentPtr		30
#define WKGRP_Comment			31
#define RST_Options_Summary		32
//#define WKGRP_VersionMajor			5
//#define WKGRP_VersionMinor			6
