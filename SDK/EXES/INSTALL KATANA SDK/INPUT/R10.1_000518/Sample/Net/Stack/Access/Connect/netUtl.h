#ifndef _NETUTLH
#define	_NETUTLH
//-----------------------------------------------------------------------------------------//
//	NETWORK UTILITY TRANSPORT ABSTRACTION LAYER MODULE
//	T. Szirtes (Sega Europe)
//  D. Randolph (Sega America)
//
//  Abstracts stacks PPP handling
//
//
//-----------------------------------------------------------------------------------------//


//-------------------------------------------------------------//
//	Data Types
//-------------------------------------------------------------//

// Custom ISP details
typedef	struct {
	char	*phone;
	char	*login;
	char	*passwd;
	int		flags;
} NUISP;


// Simplified states of network
typedef	enum { NU_INIT, NU_DIALING, NU_CONNECTING, NU_CONNECTED, NU_DISCONNECTING, NU_DISCONNECTED, NU_FAILED } NUSTATE;

// Response types
typedef enum {
    ERR_RESPONSE_NONE,
    ERR_RESPONSE_CANCEL,
    ERR_RESPONSE_RETRY,
    ERR_RESPONSE_RETRY_TIL_CONNECTED
} ERR_RESPONSE;


//-------------------------------------------------------------//
//	Functions
//-------------------------------------------------------------//

// INITIALIZE TRANSPORT
// Pass this either NULL to retrieve the flash RAM ISP settings (default for final code)
// Or pass NUISP structure for dial-in details of custom debug ISP
int				NUInitTransport(NUISP *my_isp);	

// CONNECT TO TRANSPORT
// Call this to begin connection to the transport specified by NUInitTransport
// Non-blocking so returns immediately - use NUPollTransport to find current status	
int				NUConnectTransport(void);


// POLL TRANSPORT LAYER
// Call this intermitently to find out status of connection
// This should also regularly (for Planet Web stack) to ensure processing of events
NUSTATE			NUPollTransport();

// DISCONNECT 
int				NUDisconnectTransport(void);
int				NUKillTransport(void);


// Callback functions
void			*NUMallocCB(size_t size);
void			NUFreeCB(void *pointer);
void			*NUReallocCB(void *pointer, size_t size);

unsigned long	NUClockCB(void);
void			NUProgressCB(int progress);

void			NUMdmStrStartCB(void);
void			NUMdmStrEndCB(void);
void			NUMdmStrCB(char *theStr);
//errorResponse	NUErrHandlerCB(int hdnler);	
void			NUCheckNetState(void);
//int				NUGetPWFlash(NetworkAccessInfo *isp, NetInfUS *usinf);

// Console printing functions
void			NUMsg(char *in_format, ...);
void			NUDumpBuf(char *label, int len, char *buff);
void			NUDebugInit(void);
void			NUDebugRefresh(void);

#endif




