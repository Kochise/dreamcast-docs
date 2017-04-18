/********************************************************************************************/
/* CONFIDENTIAL AND PROPRIETARY:                                                            */
/*      Copyright 2000, Sega of America.  All rights reserved.                              */
/*      This sample source code is provided for demonstration purposes only.                */
/*      Use and distribution of Sega proprietary material is governed by                    */
/*      developer licensing agreement.                                                      */
/********************************************************************************************/

//--------------------------------------------------------------------------------------//
//		NETWORK UTILITY MODULE
//		Provides Generic Dial-up and PPP Facilities
//		Abstraction layer for stack
//		Currently supports : PlanetWeb, Access 1.05
//
//		Thomas Szirtes
//		(C) Sega Europe Ltd. 	2000
//
//--------------------------------------------------------------------------------------//


//--------------------------------------------------------------------------------------//
// Include Files
//--------------------------------------------------------------------------------------//

#include <stdio.h>
#include <stdarg.h>
#include <shinobi.h>
#include <dbdebug.h>

#define GL_HACK  /* Hack to open the modem driver properly (Gary Lake). */

#ifdef KGTRN_PLANET_WEB
#include <pwebinc.h>
#endif

#ifdef KGTRN_ACCESS
#include <types.h>
#include <aveppp.h>
#include "dbdebug.h"
#endif

#include "usrUtl.h"
#include "netUtl.h"


//--------------------------------------------------------------------------------------//
//  Local Definitions
//--------------------------------------------------------------------------------------//

#define	NUERROR				-1

#define	kMaxTCP				2
#define	kMaxUDP				kMaxTCP
#define	kMaxSocket			kMaxTCP

#define SCIF_RCV_BUF_SIZE	0x100
#define SCIF_SND_BUF_SIZE	0x100
#define	kMdmBuffSize		255

//#define	DEBUG_SERIAL
#define	DEBUG_SCREEN


//--------------------------------------------------------------------------------------//
// Global Variables
//--------------------------------------------------------------------------------------//

NUSTATE     gNuState    =   NU_INIT;            // Global state of NU Module
int         kNoErr=0;

// Globals
char            gBuff[kMdmBuffSize];        // Buffer for modem strings.
int             gDisplayModemStrings;

#ifdef KGTRN_PLANET_WEB
	// PWEB Stack
	struct netInfo	gMyNetInfo;

#ifdef GL_HACK
#include <mdmAPI.h>
#include <netinfus.h>

extern MDM  gMdmHandle;     /* Planet Web's modem handle. */
extern NetInfUS usinf;

#define MDM_RX_BUFSIZE 0x10000
#define MDM_TX_BUFSIZE 0x10000
char mdmRxBuf[MDM_RX_BUFSIZE];
char mdmTxBuf[MDM_TX_BUFSIZE];
#endif

#endif

#ifdef KGTRN_ACCESS

#define PEER_HTONL(n) \
    (((((unsigned long)(n))&0xFF)<<24)| \
	 ((((unsigned long)(n))&0xFF00)<<8)| \
	 ((((unsigned long)(n))&0xFF0000)>>8) \
	 |((((unsigned long)(n))&0xFF000000)>>24))

	// Access Stack
    AvepppOpenParam 		iparam;
    AvepppSerialParam 		ac_serial;
    AvepppTelephoneParam 	ac_telephone;
    AvepppConnectionParam 	ac_ppp;
	AvepppStatus 			statpara;
	short					old_statpara_phase		=	AvepppConnectUnused;
	int						ppphandle;

// Our Modem Login Script - Access requires this
static const char login_script[] =
    "send\"AT&F\\r\"\n"
    "wait\"OK\\r\\n\",5\n"
    "send \"ATX3&C1&D2\\r\"\n"
    "wait\"OK\\r\\n\",5\n";

// Dialing Script
static const char dialing_script[] =
    "dial\"%t\"\n";

// DNS
static	char	DnsName[128];
static	long	PPP_DnsServer1 = 0;
static	long	PPP_DnsServer2 = 0;

#endif

ERR_RESPONSE NUErrHandlerCB(int);


//--------------------------------------------------------------------------------------//
// Function Calls
//--------------------------------------------------------------------------------------//

//---------------------------------------------------------
//	NUConnectTransport(NUISP *my_isp)
//	T. Szirtes / SOE
//
//	New generic transport wrapper initialization
//	If my_isp is empty then we use inbuilt flash details (default)
//---------------------------------------------------------

int	NUInitTransport(NUISP *my_isp)
{
#ifdef  KGTRN_PLANET_WEB

	// Planet web stack used
	if (my_isp==NULL)
		UUInitISPInfo(UU_PWEB);

	// Initialize highwater marks for various connections
	gMyNetInfo.maxTCP=				kMaxTCP;
	gMyNetInfo.maxUDP=				kMaxUDP;
	gMyNetInfo.maxSocket=			kMaxTCP;
	gMyNetInfo.netMalloc  =			NUMallocCB;
	gMyNetInfo.netFree    =			NUFreeCB;
	gMyNetInfo.netRealloc =			NUReallocCB;
	gMyNetInfo.progressCallback=	(void*)NUProgressCB;
	gMyNetInfo.modemStringsStart=	NUMdmStrStartCB;
	gMyNetInfo.modemStringsFinish=	NUMdmStrEndCB;
    gMyNetInfo.modemString=         (void*)NUMdmStrCB;
	gMyNetInfo.dlgHandler=			(void*)NUErrHandlerCB;
	gMyNetInfo.nl_pClockTicks=		NUClockCB;
	gMyNetInfo.nl_ticksPerSecond=	10;


	if (my_isp==NULL)
	{
		gMyNetInfo.nl_outline=			UUGetOutsideLine();
		gMyNetInfo.nl_callwait=			UUGetCallWaiting();
		gMyNetInfo.nl_areacode=			UUGetAreaCode();
		gMyNetInfo.nl_longdist=			UUGetLongDst();
		gMyNetInfo.nl_flags=			UUGetConnectFlags();
		gMyNetInfo.nl_telephone=		(const char *)UUGetPrimaryNumber();
		gMyNetInfo.nl_alttelephone=		(const char *)UUGetSecondaryNumber();
		gMyNetInfo.nl_loginID=			(const char *)UUGetLoginID();
		gMyNetInfo.nl_password=			(const char *)UUGetPassword();
		gMyNetInfo.nl_modem=			UUGetModemInit();
	}
	else
	{
		gMyNetInfo.nl_flags=			NETL_USETONE;
		gMyNetInfo.nl_outline=			"";
		gMyNetInfo.nl_callwait=			"";
		gMyNetInfo.nl_areacode=			"";
		gMyNetInfo.nl_longdist=			"";
		gMyNetInfo.nl_telephone=		my_isp->phone;
		gMyNetInfo.nl_alttelephone=		"";
		gMyNetInfo.nl_loginID=			my_isp->login;
		gMyNetInfo.nl_password=			my_isp->passwd;
		gMyNetInfo.nl_modem=			"";
	}

	gMyNetInfo.nl_primaryDNS.s_addr=		UUGetPrimaryDNS();
//	gMyNetInfo.nl_primaryDNS.s_addr=		htonl(INADDR_ANY);
	gMyNetInfo.nl_secondaryDNS.s_addr=		UUGetSecondaryDNS();
//	gMyNetInfo.nl_secondaryDNS.s_addr=		htonl(INADDR_ANY);
#endif

#ifdef  KGTRN_ACCESS
	int status	=	0;

	dbInit();
    vsInitVSyncProc(0);

	// Planet web stack used
	if (my_isp==NULL)
        UUInitISPInfo(UU_ACCESS);

	// Access stack
	// Serial Initialize
    ac_serial.speed         = 5;    // speed 0-6 : 2400,4800,9600,19200,38400,57600(,115200)
    ac_serial.stop			= 0;    // stop bit 0:1bit, 1:2bit
    ac_serial.parity        = 2;    // parity 0:even, 1:odd, 2:none
    ac_serial.flow          = 2;    // flow control 0:non, 1:RTS, 2:DTR
    ac_serial.databit		= 0;	// data size 0:8bit, 1:7bit

	// Telephone initialize
    ac_telephone.dialtype 		= 0;		// Dial type 0:TONE, 1:PULSE
    ac_telephone.outside_line   = 0;        // Use Outside line (no)
    ac_telephone.timeout 		= 60;		// timeout
    ac_telephone.dial_retry 	= 0;		// redial tries (none)
    ac_telephone.dial_interval	= 30;		// redial interval
    ac_telephone.outside_number	= UUGetOutsideLine();		// outside line number ("0,")

	// PPP Setup
    ac_ppp.recognize		= 4;  			// user authorization, 0:PAP,1:chat,2:CHAP
    ac_ppp.mru 				= 1500;     	// maximum receiving bytes
    ac_ppp.magic_number		= 0x12345678; 	// magic number
    ac_ppp.acfcomp 			= 0;    		// HDLC header compression (enable)
    ac_ppp.protocomp 		= 0;  			// PPP header compression (enable)
    ac_ppp.vjcomp 			= 0;     		// IPCP IP-TCP header compression (enable)

    iparam.serial 			= &ac_serial;
    iparam.telephone 		= &ac_telephone;
    iparam.pppconection 	= &ac_ppp;
    iparam.login_script1	= login_script;
    iparam.login_script2	= dialing_script;

	if(my_isp==NULL)
	{
		// use ISP defaults
    	iparam.telephone_number	= (char *)UUGetPrimaryNumber();
    	iparam.login 			= (char *)UUGetLoginID();
    	iparam.password 		= (char *)UUGetPassword();
	}
	else
	{
    	// use new login details
    	iparam.telephone_number	= my_isp->phone;
    	iparam.login 			= my_isp->login;
    	iparam.password 		= my_isp->passwd;
	}

    status = AvepppInitialize();			// Initialize PPP
    if (status==-1) return NUERROR;
    AT_init(0);
#endif
}


//-------------------------------------------------------------------------------------//

//
// Startup sequence for the PW stack
//
int NUConnectTransport(void)
{
#ifdef  KGTRN_PLANET_WEB

	int	status=kNoErr;

	syTmrGenSetClock(SYD_TMR_CLOCK_P1024);
	syTmrGenStart();

	NUMsg("NUConnectTransport: Initializing Planet Web stack.\n");

#ifdef GL_HACK
    sprintf (usinf.modemInit, "AT&F0&D2&C1M1");
    mdmInit (mdmRxBuf, mdmTxBuf, MDM_RX_BUFSIZE, MDM_TX_BUFSIZE);
    gMdmHandle = mdmOpen(1);
#endif

	if (kNoErr != InitializeNetwork(&gMyNetInfo))
		NUMsg("ERROR: Error initializing the Network\n");

	if (NetworkAdmState() == NIS_UP)
		NUMsg("MSG: Network administrative state already UP\n");

	// ConnectToNetwork
	ConnectToNet();


	if (NetworkAdmState() == NIS_UP)
	{
		NUMsg("MSG:: Network administrative state UP\n");
	}

	return status;

#endif
#ifdef  KGTRN_ACCESS
	int	status=0;

	NUMsg("AvepppOpen: Opening the Access PPP connectopm.\n");
    if ((ppphandle=AvepppOpen(&iparam))==-1) return NUERROR;			// Open PPP

//    vsWaitVSync(100);

#endif
}


static void NUConnectCompleteTransport()
{
#ifdef  KGTRN_ACCESS
	long myip, hisip, mydns1, mydns2, hisdns1, hisdns2;

	strcpy(DnsName, "");

	// Default values from the ROM
	PPP_DnsServer1	= (unsigned long)UUGetPrimaryDNS();
	PPP_DnsServer2 	= (unsigned long)UUGetSecondaryDNS();

	// IPCP - DNS
	AvepppGetDns(&myip, &hisip, &mydns1, &mydns2, &hisdns1, &hisdns2);

	// if IPCP has managed to negotiate a DNS server for us, use this one
	if (mydns1 != 0)
		PPP_DnsServer1 = PEER_HTONL(mydns1);

	if (mydns2 != 0)
		PPP_DnsServer2 = PEER_HTONL(mydns2);


	ADNS_Initialize(DnsName, PPP_DnsServer1, PPP_DnsServer2);

#endif
}


int	NUKillTransport()
{
#ifdef   KGTRN_ACCESS
    AvepppTerminate();
#endif
}


NUSTATE	NUPollTransport()
{
	static	NUSTATE	MyState	=	NU_INIT;

#ifdef  KGTRN_PLANET_WEB
	NetworkIdle();
	switch (NetworkActualState())
	{
		case NIS_UP:
			MyState	= NU_CONNECTED;
			break;
		case NIS_DOWN:
			MyState = NU_DISCONNECTED;
			break;
		case NIS_OPENING:
			MyState = NU_CONNECTING;
			break;
		case NIS_CLOSING:
			MyState = NU_DISCONNECTING;
			break;
		case NIS_BROKEN:
			MyState	= NU_FAILED;
			break;
		default:
			break;
	}

#endif
#ifdef  KGTRN_ACCESS

	AvepppGetStatus(&statpara);				// Get PPP status

	// We have to plug this into our callback mechanism (not automatic)

	if (statpara.last_error != AvepppErrorNon)
		NUErrHandlerCB(statpara.last_error);

	if (statpara.phase != old_statpara_phase)		// check for change in phase - otherwise no callback
	{
		old_statpara_phase	=	statpara.phase;
		NUProgressCB(statpara.phase);
	}

	switch(old_statpara_phase)
	{
		case AvepppConnectUnused:
			MyState = NU_INIT;
			break;
		case AvepppConnectOpenStandby:
		case AvepppConnectDialing:
		case AvepppConnectAuthen:
			MyState =	NU_CONNECTING;
			break;
		case AvepppConnectEstablished:
			if (MyState != NU_CONNECTED) NUConnectCompleteTransport();
			MyState =	NU_CONNECTED;
			break;
		case AvepppConnectDisconnected:
			MyState =	NU_DISCONNECTED;
			break;
		case AvepppConnectCloseStandby:
		case AvepppConnectOnhooking:
			MyState =	NU_DISCONNECTING;
			break;
	 	case AvepppConnectFail:
			MyState =	NU_FAILED;
			break;
	}

#endif

	return	MyState;
}

int NUDisconnectTransport(void)
{
#ifdef  KGTRN_PLANET_WEB
	int	status=kNoErr;

	NUMsg("NUCloseTransport: Stopping Planet Web stack.\n");

	// Drop connection and hang-up the phone.
	// DjR - Need error handling here!
	DisconnectFromNet();

	return status;
#endif
#ifdef  KGTRN_ACCESS
    AvepppClose(ppphandle);
	AT_disp(0);

	return	0;
#endif
}


//
// Callbacks
//


//--------------------------------------------------------------------------------------//
// Callback Codes
//--------------------------------------------------------------------------------------//


//
// Memory
//
void *NUMallocCB(size_t size)
{
	void	*retVal=NULL;


//  DjR - These generate a lot of messages
//	NUMsg("MEMORY: NUMallocCB\n");
	retVal = syMalloc(size);

	if (retVal == NULL)
		NUMsg("ERROR: Memory allocation failed\n");

	return retVal;
}

void NUFreeCB(void *ptr)
{
//  DjR - These generate a lot of messages
//	NUMsg("MEMORY: NUFreeCB\n");

	if (ptr == NULL)
		NUMsg("ERROR: NULL pointer -> NUFree\n");

	syFree(ptr);
}

void *NUReallocCB(void *ptr, size_t size)
{
//  DjR - These generate a lot of messages
//	NUMsg("MEMORY: NUReallocCB\n");
	if (ptr == NULL)
	{
		NUMsg("ERROR: NULL pointer -> NURealloc\n");
		ptr=NULL;
		return ptr;
	}
	else
		NUFreeCB(ptr);
	return NUMallocCB(size);
}


//
// Timing
//
// This function will be used to generate timeout values for
// the network, and to measure round trip times.
// This clock should be running at the time InitializeNetwork is called.
unsigned long NUClockCB(void)
{
	return syTmrGenGetCount()/4900;
}


//
// Messaging
//
void NUProgressCB(int progress)
{
#ifdef  KGTRN_PLANET_WEB
	switch (progress)
	{
		case MPS_INIT_PORT:
			NUMsg("NUProgressCB:  MPS_INIT_PORT\n");
		break;

		case MPS_INIT_MODEM:
			NUMsg("NUProgressCB:  MPS_INIT_MODEM\n");
		break;

		case MPS_DIAL_MODEM:
			NUMsg("NUProgressCB:  MPS_DIAL_MODEM\n");
		break;

		case MPS_LOGGING_IN:
			NUMsg("NUProgressCB:  MPS_LOGGING_IN%s %s\n", UUGetLoginID(), UUGetPassword());
		break;

		case MPS_CONNECTION_CONFIGURE:
			NUMsg("NUProgressCB:  MPS_CONNECTION_CONFIGURE\n");
		break;

		case MPS_CONFIGURE_INTERNET:
			NUMsg("NUProgressCB:  MPS_CONFIGURE_INTERNET\n");
		break;

		case MPS_CONNECTION_ESTABLISHED:
			NUMsg("NUProgressCB:  MPS_CONNECTION_ESTABLISHED\n");
		break;

		case MPS_DISCONNECTING:
			NUMsg("NUProgressCB:  MPS_DISCONNECTING\n");
		break;

		case MPS_HANGING_UP:
			NUMsg("NUProgressCB:  MPS_HANGING_UP\n");
		break;

		case MPS_DISCONNECTED:
			NUMsg("NUProgressCB:  MPS_DISCONNECTED\n");
		break;

		default:
			NUMsg("NUProgressCB:  default\n");
		break;
	}
#endif
#ifdef  KGTRN_ACCESS
	switch (progress)
	{
		case AvepppConnectOpenStandby:
			NUMsg("NUProgressCB:  AvepppConnectOpenStandby\n");
			break;
		case AvepppConnectDialing:
			NUMsg("NUProgressCB:  AvepppConnectDialing\n");
			break;
		case AvepppConnectAuthen:
			NUMsg("NUProgressCB:  AvepppConnectAuthen\n");
			break;
		case AvepppConnectEstablished:
			NUMsg("NUProgressCB:  AvepppConnectEstablished\n");
			break;
		case AvepppConnectDisconnected:
			NUMsg("NUProgressCB:  AvepppConnectDisconnected\n");
			break;
		case AvepppConnectCloseStandby:
			NUMsg("NUProgressCB:  AvepppConnectCloseStandby\n");
			break;
		case AvepppConnectOnhooking:
			NUMsg("NUProgressCB:  AvepppConnectOnhooking\n");
			break;
		case AvepppConnectFail:
			NUMsg("NUProgressCB:  AvepppConnectFail\n");
			break;

	}

#endif
}


// called when the low level state machine thinks that printable
// strings are likely to come from the modem (typically at the
// initial dialup stage).
void NUMdmStrStartCB(void)
{
/*	NUMsg("MStrStart: Start String\n");
	gDisplayModemStrings = TRUE;*/

}


// called when the data connection switches to PPP packet mode
// and printable strings become unlikely.
void NUMdmStrEndCB(void)
{
/*	NUMsg("MStrEnd: End String\n");
	gDisplayModemStrings = FALSE;*/
}


// called when there's a line of text from the modem.
void NUMdmStrCB(char *theStr)
{
//  DjR - These generate a lot of messages
//	NUMsg("MdmStrCB: MODEM STRING CALLED\n");
/*/	if (gDisplayModemStrings == TRUE)
 	{
		sprintf(gBuff, "MODEMSTR: %s\n", theStr);
		NUMsg("%s",gBuff);
	}*/
}


ERR_RESPONSE NUErrHandlerCB(int hdnler)
{
#ifdef  KGTRN_PLANET_WEB
	switch (hdnler)
	{

		// No error has occured.
		case ME_NONE:
		break;

		//	Indicates that the modem has stopped responding at the register level.
		//	On those platforms where this is possible, it usually means the user
		//	has removed the modem device from the system, or somehow knocked it loose.
		//	Valid responses for a broken modem error are RESP_RETRY or RESP_CANCEL.
		case ME_BROKEN:
			NUMsg("NUDlgHandlerCB:  ME_BROKEN\n");
			return ERR_RESPONSE_RETRY;
			break;

		//	This indicates that the modem is reporting that the telephone is busy.
		//	Valid responses are RESP_CANCEL, RESP_RETRY, or RESP_RETRY_TIL_CONNECTED.
		case ME_BUSY:
			NUMsg("NUDlgHandlerCB:  ME_BUSY\n");
			return ERR_RESPONSE_RETRY_TIL_CONNECTED;
			break;

		//	The modem was unable to detect a dialtone. Usually, this means the user hasn't
		//	plugged in the telephone.  Valid responses are RESP_CANCEL or RESP_RETRY.
		case ME_NODIALTONE:
			NUMsg("NUDlgHandlerCB:  ME_NODIALTONE\n");
			return ERR_RESPONSE_RETRY;
			break;

		//	The connection was dropped.  Many ISPs have inactivity timeouts on their lines,
		//	and a ME_CARRIERLOSS error is the result of that. Valid responses are RESP_CANCEL
		//	or RESP_RETRY.
		case ME_CARRIERLOSS:
			NUMsg("NUDlgHandlerCB:  ME_CARRIERLOSS\n");
			return ERR_RESPONSE_CANCEL;
			break;

		//	The network was informed that the username/password pair was incorrect.
		//	(Note that not all login methods report this information.)  The only valid response
		//	is RESP_CANCEL.
		case ME_BADPASSWORD:
			NUMsg("NUDlgHandlerCB:  ME_BADPASSWORD\n");
			return ERR_RESPONSE_CANCEL;
			break;

		//	There was no answer at the other end of the phone line. Valid responses are RESP_CANCEL,
		//	RESP_RETRY, or RESP_RETRY_TIL_CONNECTED.
		case ME_NOANSWER:
			NUMsg("NUDlgHandlerCB:  ME_NOANSWER\n");
			return ERR_RESPONSE_RETRY_TIL_CONNECTED;
			break;

		case ME_BADINIT:
			NUMsg("NUDlgHandlerCB:  ME_BADINIT\n");
			return ERR_RESPONSE_CANCEL;
			break;

		default:
			break;
	}
#endif
#ifdef  KGTRN_ACCESS

	switch (hdnler)
	{
		case AvepppErrorModem:
			NUMsg("NUErrHandlerCB:  AvepppErrorModem\n");
			return ERR_RESPONSE_RETRY;
			break;
		case AvepppErrorBusy:
			NUMsg("NUErrHandlerCB:  AvepppErrorBusy\n");
			return ERR_RESPONSE_RETRY;
			break;
		case AvepppErrorNoDialTone:
			NUMsg("NUErrHandlerCB:  AvepppErrorNoDialTone\n");
			return ERR_RESPONSE_RETRY;
			break;
		case AvepppErrorScript:
			NUMsg("NUErrHandlerCB:  AvepppErrorScript\n");
			return ERR_RESPONSE_CANCEL;
			break;
		case AvepppErrorLcp:
			NUMsg("NUErrHandlerCB:  AvepppErrorLcp\n");
			return ERR_RESPONSE_CANCEL;
			break;
		case AvepppErrorAuth:
			NUMsg("NUErrHandlerCB:  AvepppErrorAuth\n");
			return ERR_RESPONSE_CANCEL;
			break;
		case AvepppErrorIpcp:
			NUMsg("NUErrHandlerCB:  AvepppErrorIpcp\n");
			return ERR_RESPONSE_CANCEL;
			break;
		case AvepppErrorTcp:
			NUMsg("NUErrHandlerCB:  AvepppErrorTcp\n");
			return ERR_RESPONSE_CANCEL;
			break;

		default:
			break;
	}
#endif

}


//--------------------------------------------------------------------------------------//
// Debug Codes
//--------------------------------------------------------------------------------------//

#ifdef DEBUG_SCREEN
#define	DEBUG_DEPTH		48
	char	debug_buffer	[DEBUG_DEPTH+1][64];
	int		debug_line	=	0;
#endif


//  Initialize Serial Terminal Settings
//
void	NUDebugInit(void)
{
#ifdef	DEBUG_SERIAL
    /* Initialize serial terminal for output. */
    dbInit();
#endif

#ifdef	DEBUG_SCREEN
	int	n,m;

	// no initialization
	debug_line=0;
	for (n=0;n<DEBUG_DEPTH;n++)
		for(m=0;m<64;m++)
			debug_buffer[n][m]	=	(char)0;
#endif

	gDisplayModemStrings=TRUE;

    NUMsg("\nDebug interface initialized...\n");
}


void	NUDebugRefresh()
{


#ifdef	DEBUG_SCREEN
	int n;
	for (n=0;n<DEBUG_DEPTH;n++)
	{
		njPrintC(NJM_LOCATION(4,n+8),&debug_buffer[n][0]);
	}

#endif
}


#ifdef DEBUG_SCREEN
void scrollup()
{
	// scroll window - ouch
	int n,m;
	for (n=1;n<=DEBUG_DEPTH;n++)
	{
		for (m=0;m<64;m++)
		debug_buffer[n-1][m]=debug_buffer[n][m];
	}
	debug_line=DEBUG_DEPTH;
	debug_buffer[debug_line][0]=0;
}
#endif


//
// Serial port specific routines
//
void NUMsg(char *in_format, ...)
{
	static char msg[8192];
	int n;
	va_list ap;
    char *p;

	va_start(ap, in_format);
	vsprintf(msg, in_format, ap);
	va_end(ap);

#ifdef	DEBUG_SERIAL
 	for (p = msg; *p != 0; p++)
    {
        if (*p == '\n')
        {
            scif_putq('\r');
        }
        scif_putq(*p);
    }
#endif

#ifdef	DEBUG_SCREEN
	n=0;
	// check if at bottom of window
	if (debug_line>DEBUG_DEPTH) scrollup();

	// scan through
	for (p = msg; *p !=0; p++)
	{
		if (*p == (char)10 || *p == (char)13 )
		{
			debug_buffer[debug_line][n] = 0;
			debug_line++;
			n=0;
			if (debug_line>DEBUG_DEPTH)
				scrollup();
		}
		else
			debug_buffer[debug_line][n++]= *p;
	}
	debug_buffer[debug_line][n++]=0;
	debug_line++;
#endif
}

void NUDumpBuf(char *label, int len, char *buff)
{
    int i;
    int j;

    NUMsg("--- %s(%d):\n", label, len);
    for (i = 0; i < (len > 64 ? 64 : len); i += 16)
    {
        NUMsg("  %04x: ", i);
        for (j = 0; j < 16; j++)
        {
            if (i + j > len)
            {
                NUMsg("   ");
            }
            else
            {
                NUMsg("%02x ", buff[i + j]);
            }
        }
        NUMsg("[", i);
        for (j = 0; j < 16; j++)
        {
            if (i + j > len)
            {
                NUMsg(" ");
            }
            else
            {
                int c;
                c = buff[i + j];

                NUMsg("%c", 0x20 < c && c < 0x7f ? c : '.');
            }
        }
        NUMsg("]\n");
    }
}
