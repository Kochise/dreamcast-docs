
//=============================================================================
//  MODULE: browser.c
//
//  Description:
//  Bloodhound parser DLL for MS Browser
//
//  Modification History
//  Written by Scott Jiles with help from Stevehi 6/94
//  7/5/94   Fix Periodicity time to zero values when needed.
//  7/10/94  Fix Server Type bits.
//
//=============================================================================

#include "browser.h"

HPROTOCOL hBrowser = NULL;

typedef VOID (WINAPIV *FORMATPROC)(LPPROPERTYINST);
VOID WINAPI HandleHostAnnounce ( HFRAME hFrame, LPBrowserFRAME BrowserFrame );
VOID WINAPI HandleAnncReq ( HFRAME hFrame, LPBrowserFRAME BrowserFrame );
VOID WINAPI HandleBackReq ( HFRAME hFrame, LPBrowserFRAME BrowserFrame );
VOID WINAPI HandleLocMstrAnnc ( HFRAME hFrame, LPBrowserFRAME BrowserFrame );
VOID WINAPI HandleBecomeBackup ( HFRAME hFrame, LPBrowserFRAME BrowserFrame );
VOID WINAPI HandleBackResp ( HFRAME hFrame, LPBrowserFRAME BrowserFrame );
VOID WINAPI HandleMasterAnnc ( HFRAME hFrame, LPBrowserFRAME BrowserFrame );
VOID WINAPIV FormatPeriodicity(LPPROPERTYINST lpPropertyInst );
VOID WINAPI HandleElection ( HFRAME hFrame, LPBrowserFRAME BrowserFrame, DWORD BytesLeft );
VOID WINAPIV FormatUpTime(LPPROPERTYINST lpPropertyInst );
VOID WINAPI HandleReset ( HFRAME hFrame, LPBrowserFRAME BrowserFrame );
VOID WINAPI HandleWkGrpAnnc ( HFRAME hFrame, LPBrowserFRAME BrowserFrame );

//=============================================================================
//  Labeled Browser command set.
//=============================================================================
LABELED_BYTE Commands[] =
{
    // first name is defined in .h file.  string will be used to describe
    // command.
    { HostAnnouncement,        "Host Announcement [0x01]"},
    { AnnouncementRequest,     "Announcement Request [0x02]"},
    { Election,                "Election [0x08]"},
    { GetBackupListReq,        "Get Backup List Request [0x09]" },
    { GetBackupListResp,       "Get Backup List Response [0x0a]" },
    { BecomeBackup,            "Become Backup [0x0b]" },
    { WkGroupAnnouncement,     "Workgroup Announcement [0x0c]" },
    { MasterAnnouncement,      "Master Announcement [0x0d]" },
    { ResetBrowserState,       "Reset Browser [0x0e]" },
    { LocalMasterAnnouncement, "Local Master Announcement [0x0f]" }
};

#define COMMAND_SET_SIZE    (sizeof Commands / sizeof(LABELED_BYTE))

SET CommandSet = { COMMAND_SET_SIZE, Commands };


//=============================================================================
//  Labeled Server Type bits used in Announces.
//=============================================================================
LABELED_BIT TypeBits[] =
{
  	{0, "Not Workstation", "Workstation",},
  	{1, "Not Server", "Server",},
  	{2, "Not SQL Server", "SQL Server",},
	{3, "Not Domain Controller", "Domain Controller",},
	{4, "Not Backup Controller", "Backup Controller",},
	{5, "Not Time Source", "Time Source Server",},
	{6, "Not Apple Server", "Apple Protocol Server",},
	{7, "Not Novell", "Novell Server",},
	{8, "Not Domain Member Server", "Domain Member Server",},
	{9, "Not Print Queue Server", "Print Queue Server",},
	{10, "Not Dialin Server", "Dialin Server",},
	{11, "Not Xenix Server", "Xenix Server",},
	{12, "Not NT System", "Windows NT System",},
	{13, "Not WFW System", "Windows for Workgroups",},
	{16, "Not Potential Browser", "Potential Browser Server",},
	{17, "Not Backup Browser", "Backup Browser Server",},
	{18, "Not Master Browser", "Master Browser Server",},
	{19, "Not Domain Master Browser", "Domain Master Browser",},
	{20, "Not OSF", "OSF",},
	{21, "Not VMS", "VMS",},
	{30, "Not Local List Only", "Local List Only",},
	{31, "Not Domain Enum", "Domain Enum",},
};

SET TypeSet = {sizeof(TypeBits)/sizeof(LABELED_BIT), TypeBits };


//=============================================================================
//  Labeled bits for Native OS type in Election frames.
//=============================================================================
LABELED_BIT OSBits[] =
{
  	{0, "Not WFW", "Windows for Workgroups"},
  	{1, "Not used", "Not used"},
  	{2, "Not used", "Not used"},
  	{3, "Not used", "Not used"},
  	{4, "Not Windows NT Workstation", "Windows NT Workstation",},
  	{5, "Not Advanced Server", "Advanced Server Windows NT",},
	{6, "Not used", "Not used"},
	{7, "Not used", "Not used"},
};

SET OSSet = {sizeof(OSBits)/sizeof(LABELED_BIT), OSBits };


//=============================================================================
//  Labeled bit set for Election Desire.
//=============================================================================
LABELED_BIT DesireBits[] =
{
  	{0, "Not Backup Browse Server", "Currently Backup Browse Server"},
  	{1, "Not Standby Browse Server", "Standby Browser Server"},
  	{2, "Not Master Browser", "Currently Master Browser Server"},
  	{3, "Not Domain Master Browser", "Domain Master Browse Server"},
	{4, "Not used", "Not used"},
	{5, "Not WINS Client", "Transport Running WINS Client"},
	{6, "Not used", "Not used"},
	{7, "Not Advanced Server", "Windows NT Advanced Server"},
};

SET DesireSet = {sizeof(DesireBits)/sizeof(LABELED_BIT), DesireBits };


//=============================================================================
//  Labeled bits for Reset option bits.
//=============================================================================
LABELED_BIT ResetBits[] =
{
  	{0, "Zero", "Stop Being Browse Master"},
  	{1, "Zero", "Reset Entire Browser State"},
  	{2, "Zero", "Shutdown Browser"},
};

SET ResetSet = {sizeof(ResetBits)/sizeof(LABELED_BIT), ResetBits };


//=============================================================================
//  Property Table.
//
//  Browser database.
//  	The order of the database entry must match the
//	property defines in browser.h
//
//=============================================================================
//	#define Browser_COMMAND         	0
//	#define Browser_SUMMARY         	1
//	#define HA_UpdateCount			2
//	#define HA_Periodicity			3
//	#define HA_ServerName			4
//	#define HA_VersionMajor			5
//	#define HA_VersionMinor			6
//	#define HA_Type_Flag_Summary		7
//	#define HA_Type				8
//	#define HA_ElectionVersion		9
//	#define HA_Constant			10
//	#define AR_Flags			11
//	#define AR_Reply			12
//	#define BREQ_RequestedCount		13
//	#define BREQ_Token			14
//	#define BRSP_ServerCnt			15
//	#define BRSP_Token			16
//	#define BRSP_ServerList			17
//	#define MA_MasterName			18
//	#define ELEC_Version			19
//	#define ELEC_Criteria			20
//	#define ELEC_TimeUp			21
//	#define ELEC_MustBeZero			22
//	#define ELEC_ServerName			23
//	#define ELEC_OS_Summary			24
//	#define ELEC_OS				25
//	#define ELEC_Revision			26
//	#define ELEC_Desire_Summary		27
//	#define ELEC_Desire			28
//	#define RST_Options			29
//	#define WKGRP_CommentPtr		30
//	#define WKGRP_Comment			31
//	#define RST_Options_Summary		32
//=============================================================================
PROPERTYINFO BrowserDatabase[] =
{
	{   // Browser_COMMAND
	0,0,
	"Command",
	"Browser Command",
	PROP_TYPE_BYTE,
	PROP_QUAL_LABELED_SET,
	&CommandSet,			// use this if you have labeled set
	64,				// avg line length
	FormatPropertyInstance},        // generic format routine

    	{   // Browser_Summary
	0,0,                    // handle, label
	"Summary",              // prop name
	"Browser Summary",      // status bar message
	PROP_TYPE_SUMMARY,      // must have special prop type of summary
	PROP_QUAL_LABELED_SET,         // qualifiier
	&CommandSet,                      // address of set struct
	64,                     // max string size of display set
	FormatBrowserSummary},  // instance data - format routine

        {   // HA_UpdateCount
	0,0,
	"Update Count",
	"Incremented when Announce Data Changes.",
	PROP_TYPE_BYTE,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},        // generic format routine


        {   // HA_Periodicity
	0,0,
	"Periodicity",
	"Announcement cycle in milliseconds.",
	PROP_TYPE_DWORD,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPeriodicity},

	{   // HA_ServerName
	0,0,
	"Name",
	"Name.",
	PROP_TYPE_STRING,               // use this prop for char data
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},

	{   // HA_VersionMajor
	0,0,
	"Major Version",
	"Major Version Number.",
	PROP_TYPE_BYTE,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},

	{   // HA_VersionMinor
	0,0,
	"Minor Version",
	"Minor Version Number.",
	PROP_TYPE_BYTE,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},

	{   // HA_Type_Flag_Summary
	0,0,
	"Server Type Summary",
	"Server Type Summary.",
	PROP_TYPE_DWORD,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},

	{   // HA_Type
	0,0,
	"Server Type",
	"Server Type.",
	PROP_TYPE_DWORD,
	PROP_QUAL_FLAGS,
	&TypeSet,
	64 * 22,           // Must have space for all label bits.
	FormatPropertyInstance},

	{   // HA_ElectionVersion
	0,0,
	"Browser Election Version",
	"Browser Election Version.",
	PROP_TYPE_WORD,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},

	{   // HA_Constant
	0,0,
	"Browser Constant",
	"Browser Constant.",
	PROP_TYPE_WORD,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},

	{   // AR_Flags
	0,0,
	"Unused Flags",
	"Unused Flags.",
	PROP_TYPE_BYTE,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},


	{   // AR_Reply
	0,0,
	"Reply System Name",
	"Send Reply to this name [Not used for Windows NT].",
	PROP_TYPE_STRING,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},

	{   // BREQ_RequestedCount
	0,0,
	"Get Backup List Requested Count",
	"Get Backup List Requested Count.",
	PROP_TYPE_BYTE,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},

	{   // BREQ_Token
	0,0,
	"Backup Request Token",
	"Correlates Request with Response.",
	PROP_TYPE_DWORD,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},

	{   // BRSP_ServerCnt
	0,0,
	"Backup Server Count",
	"Number of Backup Servers returned.",
	PROP_TYPE_BYTE,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},

	{   // BRSP_Token
	0,0,
	"Backup Response Token",
	"Correlates Request with Response.",
	PROP_TYPE_DWORD,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},

	{   // BRSP_ServerList
	0,0,
	"Backup Servers",
	"List of Backup Servers.",
	PROP_TYPE_STRING,
	PROP_QUAL_NONE,
	0,
	100,
	FormatPropertyInstance},


	{   // MA_MasterName
	0,0,
	"Master Name",
	"Master Annoucement Server Name.",
	PROP_TYPE_STRING,
	PROP_QUAL_NONE,
	0,
	100,
	FormatPropertyInstance},

	{   // ELEC_Version
	0,0,
	"Election Version",
	"Election Version.",
	PROP_TYPE_BYTE,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},

	{   // ELEC_Criteria
	0,0,
	"Election Criteria",
	"Election Criteria.",
	PROP_TYPE_DWORD,
	PROP_QUAL_NONE,
	0,
	100,
	FormatPropertyInstance},

	{   // ELEC_TimeUp
	0,0,
	"Server Up Time [DD:hh:mm:ss] ",
	"Amount of Time Server has been Running.",
	PROP_TYPE_DWORD,
	PROP_QUAL_NONE,
	0,
	80,
	FormatUpTime},

	{   // ELEC_MustBeZero
	0,0,
	"Must be zero",
	"Must be zero.",
	PROP_TYPE_DWORD,
	PROP_QUAL_NONE,
	0,
	80,
	FormatPropertyInstance},

	{   // ELEC_ServerName
	0,0,
	"Election Server Name",
	"Election Server Name.",
	PROP_TYPE_STRING,
	PROP_QUAL_NONE,
	0,
	80,
	FormatPropertyInstance},

	{   // ELEC_OS_Summary
	0,0,
	"Election OS Summary",
	"Election OS Summary.",
	PROP_TYPE_BYTE,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},

	{   // ELEC_OS
	0,0,
	"Native OS",
	"Native Operating System.",
	PROP_TYPE_BYTE,
	PROP_QUAL_FLAGS,
	&OSSet,
	64 * 8,           // Must have space for all label bits.
	FormatPropertyInstance},


	{   // ELEC_Revision
	0,0,
	"Election Revision",
	"Election Revision.",
	PROP_TYPE_WORD,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},

	{   // ELEC_Desire_Summary
	0,0,
	"Election Desire Summary",
	"Election Desire Summary.",
	PROP_TYPE_BYTE,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},

	{   // ELEC_Desire
	0,0,
	"Election Desire",
	"Election Desire.",
	PROP_TYPE_BYTE,
	PROP_QUAL_FLAGS,
	&DesireSet,
	64 * 8,           // Must have space for all label bits.
	FormatPropertyInstance},

	{   // RST_Options
	0,0,
	"Reset Options",
	"Reset Options.",
	PROP_TYPE_BYTE,
	PROP_QUAL_FLAGS,
	&ResetSet,
	64 * 4,           // Must have space for all label bits.
	FormatPropertyInstance},

	{   // WKGRP_CommentPtr
	0,0,
	"Comment Pointer",
	"Comment Pointer.",
	PROP_TYPE_DWORD,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},

	{   // WKGRP_Comment
	0,0,
	"Server Name",
	"Server Source Name.",
	PROP_TYPE_STRING,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},

	{   // RST_Options_Summary
	0,0,
	"Options Summary",
	"Reset Frame Options Summary.",
	PROP_TYPE_BYTE,
	PROP_QUAL_NONE,
	0,
	64,
	FormatPropertyInstance},
};

DWORD nBrowserProperties = ((sizeof BrowserDatabase) / PROPERTYINFO_SIZE);


//=============================================================================
//  Protocol entry points.
//=============================================================================
extern VOID   WINAPI BrowserRegister(HPROTOCOL);
extern VOID   WINAPI BrowserDeregister(HPROTOCOL);
extern LPBYTE WINAPI BrowserRecognizeFrame(HFRAME, LPVOID, LPVOID, DWORD, DWORD, HPROTOCOL, DWORD, LPDWORD, LPHPROTOCOL, LPDWORD);
extern LPBYTE WINAPI BrowserAttachProperties(HFRAME, LPVOID, LPVOID, DWORD, DWORD, HPROTOCOL, DWORD, DWORD);
extern DWORD  WINAPI BrowserFormatProperties(HFRAME, LPVOID, LPVOID, DWORD, LPPROPERTYINST);

ENTRYPOINTS BrowserEntryPoints =
{
    BrowserRegister,
    BrowserDeregister,
    BrowserRecognizeFrame,
    BrowserAttachProperties,
    BrowserFormatProperties
};


//=============================================================================
//  FUNCTION: BrowserRegister()
//
//  Modification History
//  Written by Scottji 6/94
//
//=============================================================================
VOID WINAPI BrowserRegister(HPROTOCOL hBrowserProtocol)
{
    register DWORD i;

    //=========================================================================
    //  Create the property database.
    //=========================================================================

    CreatePropertyDatabase(hBrowserProtocol, nBrowserProperties);

    for(i = 0; i < nBrowserProperties; ++i)
    {
	AddProperty(hBrowserProtocol, &BrowserDatabase[i]);
    }
}

//=============================================================================
//  FUNCTION: Deregister()
//
//  Modification History
//  Written by Scottji 6/94
//
//=============================================================================
VOID WINAPI BrowserDeregister(HPROTOCOL hBrowserProtocol)
{
    DestroyPropertyDatabase(hBrowserProtocol);
}

//=============================================================================
//  FUNCTION: BrowserRecognizeFrame()
//
//  Modification History
//  Written by Scottji 6/94
//
//=============================================================================
LPBYTE WINAPI BrowserRecognizeFrame(HFRAME          hFrame,                     //... frame handle.
				    LPBYTE          MacFrame,                   //... Frame pointer.
				    LPBrowserFRAME  BrowserFrame,
				    DWORD           MacType,                    //... MAC type.
				    DWORD           BytesLeft,                  //... Bytes left.
				    HPROTOCOL       hPreviousProtocol,          //... Previous protocol or NULL if none.
				    DWORD           nPreviousProtocolOffset,    //... Offset of previous protocol.
				    LPDWORD         ProtocolStatusCode,         //... Pointer to return status code in.
				    LPHPROTOCOL     hNextProtocol,              //... Next protocol to call (optional).
				    LPDWORD         InstData)                   //... Next protocol instance data.
{
    // Will only be called if SMB parser finds Transact
    // with path = \mailslot\browse.

    // Make sure there is some data left.
    if (BytesLeft == 0) {
	*ProtocolStatusCode = PROTOCOL_STATUS_NOT_RECOGNIZED;
	return (LPBYTE) BrowserFrame;
    }

    // should probably check bytes left for max and min length.
    // need to find max and min length.
    if (BytesLeft < 2 ) { // Reset frame has 2 bytes.
	*ProtocolStatusCode = PROTOCOL_STATUS_NOT_RECOGNIZED;
	return (LPBYTE) BrowserFrame;
    }

    // Make sure command is between max and min command code.
    if ((BrowserFrame->command >= HostAnnouncement) &
       (BrowserFrame->command <= LocalMasterAnnouncement) ) {
	    *ProtocolStatusCode = PROTOCOL_STATUS_CLAIMED;
	    return NULL;  //  null means I claim the rest
    }

    #ifdef DEBUG
    DebugBreak();
    #endif

    // should never hit this point.
    *ProtocolStatusCode = PROTOCOL_STATUS_NOT_RECOGNIZED;
    return (LPBYTE) BrowserFrame;

}

//=============================================================================
//  FUNCTION: BrowserAttachProperties()
//
//  Modification History
//  Written by Scottji 6/94
//
//=============================================================================
LPBYTE WINAPI BrowserAttachProperties(HFRAME          hFrame,
				      LPBYTE          Frame,
				      LPBrowserFRAME  BrowserFrame,
				      DWORD           MacType,
				      DWORD           BytesLeft,
				      HPROTOCOL       hPreviousProtocol,
				      DWORD           nPreviousProtocolOffset,
				      DWORD           InstData)
{

    //=========================================================================
    //  Attach Summary.
    //=========================================================================

    AttachPropertyInstance(hFrame,
			   BrowserDatabase[Browser_SUMMARY].hProperty,
			   BytesLeft,   // claim the remaining bytes
			   BrowserFrame,
			   0, 0, 0);    // Summary should be 0.

    //=========================================================================
    //  Attach Command.
    //=========================================================================

    AttachPropertyInstance(hFrame,
			   BrowserDatabase[Browser_COMMAND].hProperty,
			   sizeof(BYTE),
			   BrowserFrame,
			   0, 1, 0);  // Detail other than 0 for drill down.

    switch( BrowserFrame->command )
    {
	case HostAnnouncement:
	    HandleHostAnnounce ( hFrame, BrowserFrame );
	    break;

	case AnnouncementRequest:
	    HandleAnncReq ( hFrame, BrowserFrame );
	    break;

	case Election:
	    HandleElection ( hFrame, BrowserFrame, BytesLeft);
	    break;

	case GetBackupListReq:
	    HandleBackReq ( hFrame, BrowserFrame );
	    break;

	case GetBackupListResp:
	    HandleBackResp ( hFrame, BrowserFrame );
	    break;

	case BecomeBackup:
	    HandleBecomeBackup ( hFrame, BrowserFrame );
	    break;

	case WkGroupAnnouncement:
	    HandleWkGrpAnnc ( hFrame, BrowserFrame );
	    break;

	case MasterAnnouncement:
	    HandleMasterAnnc ( hFrame, BrowserFrame );
	    break;

	case ResetBrowserState:
	    HandleReset ( hFrame, BrowserFrame );
	    break;

	case LocalMasterAnnouncement:
	    HandleLocMstrAnnc ( hFrame, BrowserFrame );
	    break;

	default:
	    // CommandString = "";
	    break;
    }
    return NULL;  //must return null from attachproperies.
}


///////////////////////////////////////////////////////////////////////////
//
// FormatProperties (Bloodhound parser DLL entrypoint)
//
///////////////////////////////////////////////////////////////////////////
DWORD WINAPI BrowserFormatProperties(HFRAME hFrame,
				     LPBYTE MacFrame,
				     LPBYTE BrowserFrame,
				     DWORD  nPropertyInsts,
				     LPPROPERTYINST p)
{
    while(nPropertyInsts--)
    {
	if (p->lpPropertyInfo->InstanceData != NULL )
	    ((FORMATPROC)p->lpPropertyInfo->InstanceData)(p);
	p++;
    }
    return BHERR_SUCCESS;
}

//==============================================================================
//  FUNCTION: FormatBrowserSummary()
//
//  Modification History
//  Scottji             6/94        Created
//  Tom Laird-McConnell 07/20/94    Modified to have more info on summary line
//  Scottji             07/25/94    Modified Election. Pass BytesLeft.  Add Force.
//  Tom Laird-McConnell 08/31/94    Converted strings to ANSI
//==============================================================================
VOID WINAPIV FormatBrowserSummary(LPPROPERTYINST lpPropertyInst )
{
    LPBrowserFRAME BrowserFrame;
//    CHAR * CommandString;
    char szAnsiName[255];

    BrowserFrame = (LPBrowserFRAME) lpPropertyInst->lpData;

//    CommandString = (char *) malloc (sizeof(char) * 80);

	switch( BrowserFrame->command )
	{
	    case HostAnnouncement:
        {
            LP_HA_FRAME HA_Frame = (LP_HA_FRAME) BrowserFrame;

            // convert string to ANSI
            OemToChar( (LPCSTR)&HA_Frame->ServerName, szAnsiName);

            wsprintf(lpPropertyInst->szPropertyText, "%s %s", Commands[0].Label, szAnsiName);
    		break;
        }

	    case AnnouncementRequest:
        {
            LP_ANNC_REQ AR_Frame = (LP_ANNC_REQ) BrowserFrame;

            wsprintf(lpPropertyInst->szPropertyText, Commands[1].Label);
    		break;
        }

	    case Election:
        {
            LP_ELECTION ELEC_Frame = (LP_ELECTION) BrowserFrame;

            if (ELEC_Frame->Criteria == NULL ) {
                wsprintf(lpPropertyInst->szPropertyText, "%s [Force]", Commands[2].Label);
            }
            else 
            {
                // convert string to ANSI
                OemToChar( (LPCSTR)&ELEC_Frame->ServerName, szAnsiName);
                
                wsprintf(lpPropertyInst->szPropertyText, "%s %s", Commands[2].Label, szAnsiName);
            }
    		break;
        }

	    case GetBackupListReq:
            wsprintf(lpPropertyInst->szPropertyText, Commands[3].Label);
    		break;

	    case GetBackupListResp:
        {
            LP_BACK_RESP BRSP_Frame = (LP_BACK_RESP) BrowserFrame;

            wsprintf(lpPropertyInst->szPropertyText, "%s %d Servers", Commands[4].Label, BRSP_Frame->BackupServerCount);
    		break;
        }

	    case BecomeBackup:
        {
            LP_BECOME_BACKUP BB_Frame = (LP_BECOME_BACKUP) BrowserFrame;

            // convert string to ANSI
            OemToChar( (LPCSTR)&BB_Frame->BrowserToPromote, szAnsiName);
            
            wsprintf(lpPropertyInst->szPropertyText, "%s Name = %s",  Commands[5].Label, szAnsiName);
    		break;
        }

	    case WkGroupAnnouncement:
        {
            LP_WKGRP_FRAME WKGRP_Frame = (LP_WKGRP_FRAME) BrowserFrame;

            // convert string to ANSI
            OemToChar( (LPCSTR)&WKGRP_Frame->ServerName, szAnsiName);
            
            wsprintf(lpPropertyInst->szPropertyText, "%s %s", Commands[6].Label, szAnsiName);
    		break;
        }

	    case MasterAnnouncement:
        {
            LP_MASTER_ANNC MA_Frame = (LP_MASTER_ANNC) BrowserFrame;

            // convert string to ANSI
            OemToChar( (LPCSTR)&MA_Frame->MasterName, szAnsiName);

            wsprintf(lpPropertyInst->szPropertyText, "%s %s", Commands[7].Label, szAnsiName);
    		break;
        }

	    case ResetBrowserState:
            wsprintf(lpPropertyInst->szPropertyText, Commands[8].Label);
    		break;

	    case LocalMasterAnnouncement:
        {
            LP_HA_FRAME HA_Frame = (LP_HA_FRAME) BrowserFrame;

            // convert string to ANSI
            OemToChar( (LPCSTR)&HA_Frame->ServerName, szAnsiName);

            wsprintf(lpPropertyInst->szPropertyText, "%s %s", Commands[9].Label, szAnsiName);
    		break;
        }

	    default:
            wsprintf(lpPropertyInst->szPropertyText, "Unknown Command?");
    		break;
	}
}




//==============================================================================
//  FUNCTION: HandleHostAnnouce()
//
//  Modification History
//  Written by Scottji 6/94
//
//
//==============================================================================
VOID WINAPI HandleHostAnnounce ( HFRAME hFrame, LPBrowserFRAME BrowserFrame )
{
    LP_HA_FRAME HA_Frame;

    // HA Update Count
    HA_Frame = (LP_HA_FRAME) BrowserFrame;
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_UpdateCount].hProperty,
			   sizeof(BYTE),
			   &HA_Frame->UpdateCount,
			   0, 1, 0);
    // Periodicity;     announcement cycle in milliseconds
    HA_Frame = (LP_HA_FRAME) BrowserFrame;
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_Periodicity].hProperty,
			   sizeof(ULONG),
			   &HA_Frame->Periodicity,
			   0, 1, 0);
    // HA_ServerName
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_ServerName].hProperty,
			   LM20_CNLEN+1,
			   &HA_Frame->ServerName,
			   0, 1, 0);
    // HA_VersionMajor
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_VersionMajor].hProperty,
			   sizeof(BYTE),
			   &HA_Frame->VersionMajor,
			   0, 1, 0);
    // HA_VersionMinor
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_VersionMinor].hProperty,
			   sizeof(BYTE),
			   &HA_Frame->VersionMinor,
			   0, 1, 0);
    // HA_Type_Flag_Summary
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_Type_Flag_Summary].hProperty,
			   sizeof(ULONG),
			   &HA_Frame->Type,
			   0, 1, 0);
    // HA_Type
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_Type].hProperty,
			   sizeof(ULONG),
			   &HA_Frame->Type,
			   0, 2, 0);
    // HA_ElectionVersion
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_ElectionVersion].hProperty,
			   sizeof(WORD),
			   &HA_Frame->HAElectionVersion,
			   0, 1, 0);
    // HA_Constant
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_Constant].hProperty,
			   sizeof(WORD),
			   &HA_Frame->HAConstant,
			   0, 1, 0);
}

//==============================================================================
//  FUNCTION: HandleAnncReq()
//
//  Modification History
//  Written by Scottji 6/94
//
//
//==============================================================================

VOID WINAPI HandleAnncReq ( HFRAME hFrame, LPBrowserFRAME BrowserFrame )
{
    LP_ANNC_REQ AR_Frame;
    int len;

    AR_Frame = (LP_ANNC_REQ) BrowserFrame;

    // AR_Flags
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[AR_Flags].hProperty,
			   sizeof(UCHAR),
			   &AR_Frame->Flags,
			   0, 1, 0);
    len = strlen ( &AR_Frame->Reply[0] );
    // AR_Reply
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[AR_Reply].hProperty,
			   len,
			   &AR_Frame->Reply,
			   0, 1, 0);
}

//==============================================================================
//  FUNCTION: HandleBackReq()
//
//  Modification History
//  Written by Scottji 6/94
//
//
//==============================================================================
VOID WINAPI HandleBackReq ( HFRAME hFrame, LPBrowserFRAME BrowserFrame )
{
    LP_BACK_REQ_FRAME BREQ_Frame;

    BREQ_Frame = (LP_BACK_REQ_FRAME) BrowserFrame;

    // BREQ_RequestedCount
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[BREQ_RequestedCount].hProperty,
			   sizeof(UCHAR),
			   &BREQ_Frame->RequestedCount,
			   0, 1, 0);
    // BREQ_Token
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[BREQ_Token].hProperty,
			   sizeof(LONG),
			   &BREQ_Frame->Token,
			   0, 1, 0);
}

//==============================================================================
//  FUNCTION: HandleLocMstrAnnc()
//
//  Modification History
//  Written by Scottji 6/94
//
//
//==============================================================================
VOID WINAPI HandleLocMstrAnnc ( HFRAME hFrame, LPBrowserFRAME BrowserFrame )
{
    LP_HA_FRAME HA_Frame;

    //=========================================================================
    //  Same as Host Announcement frame.
    //=========================================================================

    // HA Update Count
    HA_Frame = (LP_HA_FRAME) BrowserFrame;
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_UpdateCount].hProperty,
			   sizeof(BYTE),
			   &HA_Frame->UpdateCount,
			   0, 1, 0);
    // Periodicity;     announcement cycle in milliseconds

    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_Periodicity].hProperty,
			   sizeof(ULONG),
			   &HA_Frame->Periodicity,
			   0, 1, 0);
    // HA_ServerName
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_ServerName].hProperty,
			   LM20_CNLEN+1,
			   &HA_Frame->ServerName,
			   0, 1, 0);
    // HA_VersionMajor
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_VersionMajor].hProperty,
			   sizeof(BYTE),
			   &HA_Frame->VersionMajor,
			   0, 1, 0);
    // HA_VersionMinor
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_VersionMinor].hProperty,
			   sizeof(BYTE),
			   &HA_Frame->VersionMinor,
			   0, 1, 0);
    // HA_Type_Flag_Summary
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_Type_Flag_Summary].hProperty,
			   sizeof(ULONG),
			   &HA_Frame->Type,
			   0, 1, 0);
    // HA_Type
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_Type].hProperty,
			   sizeof(ULONG),
			   &HA_Frame->Type,
			   0, 2, 0);
    // HA_ElectionVersion
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_ElectionVersion].hProperty,
			   sizeof(WORD),
			   &HA_Frame->HAElectionVersion,
			   0, 1, 0);
    // HA_Constant
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_Constant].hProperty,
			   sizeof(WORD),
			   &HA_Frame->HAConstant,
			   0, 1, 0);
}

//==============================================================================
//  FUNCTION: HandleBecomeBackup()
//
//  Modification History
//  Written by Scottji 6/94
//
//
//==============================================================================
VOID WINAPI HandleBecomeBackup ( HFRAME hFrame, LPBrowserFRAME BrowserFrame )
{
    LP_BECOME_BACKUP BB_Frame;
    int len;

    BB_Frame = (LP_BECOME_BACKUP) BrowserFrame;

    // BrowserToPromote = HA_ServerName
    len = strlen ( &BB_Frame->BrowserToPromote[0] );
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_ServerName].hProperty,
			   len,
			   &BB_Frame->BrowserToPromote,
			   0, 1, 0);
}


//==============================================================================
//  FUNCTION: HandleBackResp()
//
//  Modification History
//  Written by Scottji 6/94
//
//
//==============================================================================
VOID WINAPI HandleBackResp ( HFRAME hFrame, LPBrowserFRAME BrowserFrame )
{
    LP_BACK_RESP BRSP_Frame;
    int i, k, len, offset;

    BRSP_Frame = (LP_BACK_RESP) BrowserFrame;
    i = (int)BRSP_Frame->BackupServerCount;

    // BRSP_ServerCnt
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[BRSP_ServerCnt].hProperty,
			   sizeof(UCHAR),
			   &BRSP_Frame->BackupServerCount,
			   0, 1, 0);
    // BRSP_Token
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[BRSP_Token].hProperty,
			   sizeof(ULONG),
			   &BRSP_Frame->Token,
			   0, 1, 0);

    for (k = 1, offset = 0 ; k <= i; k++) {
        len = strlen ( &BRSP_Frame->BackupServerList[offset] );
        // BRSP_ServerList
        AttachPropertyInstance(hFrame,
			   BrowserDatabase[BRSP_ServerList].hProperty,
			   len,
			   &BRSP_Frame->BackupServerList[offset],
			   0, 1, 0);
        offset = offset + 1 + strlen( (UCHAR *) &BRSP_Frame->BackupServerList[offset] );
    }
}

//==============================================================================
//  FUNCTION: HandleMasterAnnc()
//
//  Modification History
//  Written by Scottji 6/94
//
//
//==============================================================================
VOID WINAPI HandleMasterAnnc ( HFRAME hFrame, LPBrowserFRAME BrowserFrame )
{
    LP_MASTER_ANNC MA_Frame;
    int len;

    MA_Frame = (LP_MASTER_ANNC) BrowserFrame;
    len = strlen ( &MA_Frame->MasterName[0] );

    // MA_MasterName
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[MA_MasterName].hProperty,
			   len,
			   &MA_Frame->MasterName,
			   0, 1, 0);
}

//==============================================================================
//  FUNCTION: FormatPeriodicity()
//
//  Modification History
//  Written by Scottji 6/94
//
//
//==============================================================================
VOID WINAPIV FormatPeriodicity(LPPROPERTYINST lpPropertyInst )
{
    ULPDWORD period;
    ULONG value;
    char CommandString[80];

    period =  (ULPDWORD)lpPropertyInst->lpData;
    value = (((ULONG)* period) / 1000) /60 ;
    _ultoa (value, CommandString, 10);
    strcpy (lpPropertyInst->szPropertyText, "Annoucement Interval [minutes] = ");
    strcat ( lpPropertyInst->szPropertyText, CommandString );
}

//==============================================================================
//  FUNCTION: HandleElection()
//
//  Modification History
//  Written by Scottji 6/94
//  Scottji             07/25/94    Modified Election. Add Force.
//                                  Pass BytesLeft.  Check length before attach.
//
//==============================================================================
VOID WINAPI HandleElection ( HFRAME hFrame, LPBrowserFRAME BrowserFrame, DWORD BytesLeft )
{
    LP_ELECTION ELEC_Frame;
    int len;
    char *p;

    ELEC_Frame = (LP_ELECTION) BrowserFrame;
    len = strlen ( &ELEC_Frame->ServerName[0] );

    if (BytesLeft >= 2 ) {
        // ELEC_Version
        AttachPropertyInstance(hFrame,
			   BrowserDatabase[ELEC_Version].hProperty,
			   sizeof(BYTE),
			   &ELEC_Frame->Version,
			   0, 1, 0);
    }

    if (BytesLeft >= 6  ) {
        // ELEC_Criteria
        AttachPropertyInstance(hFrame,
			   BrowserDatabase[ELEC_Criteria].hProperty,
			   sizeof(DWORD),
			   &ELEC_Frame->Criteria,
			   0, 1, 0);

        p = (char *) &ELEC_Frame->Criteria;
        // ELEC_OS_Summary
        AttachPropertyInstance(hFrame,
			   BrowserDatabase[ELEC_OS_Summary].hProperty,
			   sizeof(BYTE),
			   p+3,
			   0, 2, 0);
        // ELEC_OS
        AttachPropertyInstance(hFrame,
			   BrowserDatabase[ELEC_OS].hProperty,
			   sizeof(BYTE),
			   p+3,
			   0, 3, 0);
        // ELEC_Revision
        AttachPropertyInstance(hFrame,
			   BrowserDatabase[ELEC_Revision].hProperty,
			   sizeof(WORD),
			   p+1,
			   0, 2, 0);
        // ELEC_Desire_Summary
        AttachPropertyInstance(hFrame,
			   BrowserDatabase[ELEC_Desire_Summary].hProperty,
			   sizeof(BYTE),
			   p,
			   0, 2, 0);

        // ELEC_Desire
        AttachPropertyInstance(hFrame,
			   BrowserDatabase[ELEC_Desire].hProperty,
			   sizeof(BYTE),
			   p,
			   0, 3, 0);
    }

    if (BytesLeft >= 10 ) {
        // ELEC_TimeUp
        AttachPropertyInstance(hFrame,
			   BrowserDatabase[ELEC_TimeUp].hProperty,
			   sizeof(DWORD),
			   &ELEC_Frame->TimeUp,
			   0, 1, 0);
    }

    if ((BytesLeft > 14 ) & (BytesLeft <50 ) ) {
    	// ELEC_ServerName
    	AttachPropertyInstance(hFrame,
			   BrowserDatabase[ELEC_ServerName].hProperty,
			   len,
			   &ELEC_Frame->ServerName,
			   0, 1, 0);
    }
}

//==============================================================================
//  FUNCTION: FormatUpTime()
//
//  Modification History
//  Written by Scottji 6/94
//
//
//==============================================================================
VOID WINAPIV FormatUpTime(LPPROPERTYINST lpPropertyInst )
{
    ULPDWORD value;
    ULONG time, days, hours, minutes, seconds;
    char CommandString[80];
    ULONG ONEDAY, ONEHOUR, ONEMINUTE;

    ONEDAY =   86400000;
    ONEHOUR =  3600000;
    ONEMINUTE =  60000;
    value =  (ULPDWORD)lpPropertyInst->lpData;
    time = (ULONG) *value;

    if (time >= ONEDAY) {
        days = time / ONEDAY;
        time = time - (days * ONEDAY);
    }
    else {
        days = 0;
    }
    if (time >= ONEHOUR){
        hours = time / ONEHOUR;
        time = time - (hours * ONEHOUR);
    }
    else {
        hours = 0;
    }
    if (time >= ONEMINUTE) {
        minutes = time / ONEMINUTE;
        time = time - (minutes * ONEMINUTE);
    }
    else {
        minutes = 0;
    }
    if(seconds != 0) {
        seconds = time / 1000;
    }
    else {
        seconds = 0;
    }

    strcpy (lpPropertyInst->szPropertyText, "Server Up Time [DD:hh:mm:ss] ");
    if( (ULONG)*value != 0 ) {
	    _ultoa (days, CommandString, 10);
	    strcat (lpPropertyInst->szPropertyText, CommandString );
	    strcat (lpPropertyInst->szPropertyText, ":");
	    _ultoa (hours, CommandString, 10);
	    strcat (lpPropertyInst->szPropertyText, CommandString );
	    strcat (lpPropertyInst->szPropertyText, ":");
	    _ultoa (minutes, CommandString, 10);
	    strcat (lpPropertyInst->szPropertyText, CommandString );
	    strcat (lpPropertyInst->szPropertyText, ":");
	    _ultoa (seconds, CommandString, 10);
	    strcat (lpPropertyInst->szPropertyText, CommandString );
    }
    else {
	    strcat (lpPropertyInst->szPropertyText, "Null");
	 }
}

//==============================================================================
//  FUNCTION: HandleReset()
//
//  Modification History
//  Written by Scottji 6/94
//
//
//==============================================================================
VOID WINAPI HandleReset ( HFRAME hFrame, LPBrowserFRAME BrowserFrame )
{
    LP_RESET RST_Frame;

    RST_Frame = (LP_RESET) BrowserFrame;


    // RST_Options_Summary
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[RST_Options_Summary].hProperty,
			   sizeof(BYTE),
			   &RST_Frame->Options,
			   0, 1, 0);
    // RST_Options
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[RST_Options].hProperty,
			   sizeof(BYTE),
			   &RST_Frame->Options,
			   0, 2, 0);
}


//==============================================================================
//  FUNCTION: HandleWkGrpAnnc()
//
//  Modification History
//  Written by Scottji 6/94
//
//
//==============================================================================
VOID WINAPI HandleWkGrpAnnc ( HFRAME hFrame, LPBrowserFRAME BrowserFrame )
{
    LP_WKGRP_FRAME WKGRP_Frame;
    int len;

    //=========================================================================
    //  Same as Host Announcement frame.
    //=========================================================================

    WKGRP_Frame = (LP_WKGRP_FRAME) BrowserFrame;
    //  Update Count

    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_UpdateCount].hProperty,
			   sizeof(BYTE),
			   &WKGRP_Frame->UpdateCount,
			   0, 1, 0);
    // Periodicity;     announcement cycle in milliseconds
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_Periodicity].hProperty,
			   sizeof(ULONG),
			   &WKGRP_Frame->Periodicity,
			   0, 1, 0);
    // ServerName
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_ServerName].hProperty,
			   LM20_CNLEN+1,
			   &WKGRP_Frame->ServerName,
			   0, 1, 0);
    // VersionMajor
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_VersionMajor].hProperty,
			   sizeof(BYTE),
			   &WKGRP_Frame->VersionMajor,
			   0, 1, 0);
    // VersionMinor
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_VersionMinor].hProperty,
			   sizeof(BYTE),
			   &WKGRP_Frame->VersionMinor,
			   0, 1, 0);
    // Type_Flag_Summary
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_Type_Flag_Summary].hProperty,
			   sizeof(ULONG),
			   &WKGRP_Frame->Type,
			   0, 1, 0);
    // Type
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[HA_Type].hProperty,
			   sizeof(ULONG),
			   &WKGRP_Frame->Type,
			   0, 2, 0);
    // WKGRP_CommentPtr
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[WKGRP_CommentPtr].hProperty,
			   sizeof(DWORD),
			   &WKGRP_Frame->CommentPtr,
			   0, 1, 0);
    len = strlen ( &WKGRP_Frame->Comment[0] );
    // WKGRP_Comment
    AttachPropertyInstance(hFrame,
			   BrowserDatabase[WKGRP_Comment].hProperty,
			   len,
			   &WKGRP_Frame->Comment,
			   0, 1, 0);
}
