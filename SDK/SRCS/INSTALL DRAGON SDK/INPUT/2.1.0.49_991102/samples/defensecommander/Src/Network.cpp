/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    Network.cpp

Abstract:

	Network code. 

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCNetwork.h"
#include <dplay.h>
#include <dplobby.h>

#ifdef DREAMCAST
#define __based(a)
#undef DEFINE_GUID
#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    EXTERN_C const GUID __based(__segname("_CODE")) name \
                    = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }
DEFINE_GUID(IID_IDirectPlay4, 0xab1c530, 0x4745, 0x11d1, 0xa7, 0xa1, 0x0, 0x0, 0xf8, 0x3, 0xab, 0xfc);
DEFINE_GUID(IID_IDirectPlayLobby3, 0x2db72490, 0x652c, 0x11d1, 0xa7, 0xa8, 0x0, 0x0, 0xf8, 0x3, 0xab, 0xfc);
#endif

static const GUID AppGuid = 
{ 0xaae6be20, 0x7b5d, 0x11d3, { 0x94, 0x80, 0x0, 0x50, 0x4, 0x2, 0x43, 0xd0 } };

static const GUID NullGuid =
{ 0x0, 0x0, 0x0, { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0} };

static BOOL Server;
static LPDIRECTPLAYLOBBY DirectPlayLobbyBase=NULL;
static LPDIRECTPLAYLOBBY3 DirectPlayLobby=NULL;
static LPDIRECTPLAY DirectPlayBase=NULL;
static LPDIRECTPLAY4 DirectPlay=NULL;
static DPID OurPlayer=0, OtherPlayer=0;

// Sender thread related stuff.
static BOOL SenderInitialized;
BOOL InitSender();
void ShutdownSender();
DWORD WINAPI SenderFunc(LPVOID lpParam);
void QueueItem(void *Data, int Size);

// Set address information for DirectPlay service provider.
static BOOL SetServiceProviderAddress(GUID *Guid, int Port)
{
	DPCOMPOUNDADDRESSELEMENT	AddressElements[2];
	DPCOMPORTADDRESS			CA;

	AddressElements[0].guidDataType = DPAID_ServiceProvider;
	AddressElements[0].dwDataSize = sizeof(GUID);
	AddressElements[0].lpData = (LPVOID) Guid;
	AddressElements[1].guidDataType = DPAID_ComPort;
	AddressElements[1].dwDataSize = sizeof(DPCOMPORTADDRESS);
	AddressElements[1].lpData = (LPVOID) &CA;

	CA.dwComPort=Port;
	CA.dwBaudRate=CBR_115200;
	CA.dwStopBits=ONESTOPBIT;
	CA.dwParity=NOPARITY;
	CA.dwFlowControl=DPCPA_RTSDTRFLOW;

	DWORD AddressSize=0;
	void *Address;

	// Aee how much room is needed to store this address
	if (DirectPlayLobby->CreateCompoundAddress(AddressElements, 2,	NULL, &AddressSize) 
		!= DPERR_BUFFERTOOSMALL)
	{
		SetErrorMessage(IDS_ERROR_DPMISC);
		return FALSE;
	}

	// Allocate space
	Address = DCMalloc(AddressSize);
	if (!Address)
	{
		SetErrorMessage(IDS_ERROR_DPMISC);
		return FALSE;
	}

	// Create the address
	if (FAILED(DirectPlayLobby->CreateCompoundAddress(AddressElements, 2,
													  Address, &AddressSize)))
	{
		DCFree(Address);
		SetErrorMessage(IDS_ERROR_DPMISC);
		return FALSE;
	}

	// Init connection.
	HRESULT hr;
	if (FAILED(hr=DirectPlay->InitializeConnection(Address, 0)))
	{
		DCFree(Address);
		SetErrorMessage(IDS_ERROR_DPMISC);
		return FALSE;
	}

	DCFree(Address);

	return TRUE;
}

BOOL FAR PASCAL EnumSessionsCallback(LPCDPSESSIONDESC2 lpThisSD,  
									 LPDWORD lpdwTimeOut,  DWORD dwFlags,  LPVOID lpContext)
{
	if (lpThisSD)
	{
		*((GUID *)lpContext)=lpThisSD->guidInstance;
		return FALSE;
	}
	return TRUE;
}


BOOL InitNetwork(BOOL InServer, int Port)
{
	// Init variables.
	Server=InServer;
	
	// Create DirectPlay lobbby.
	if (FAILED(DirectPlayLobbyCreate(NULL, &DirectPlayLobbyBase, NULL, NULL, NULL)))
	{
		SetErrorMessage(IDS_ERROR_DPLOBBYCREATE);
		return FALSE;
	}
	HRESULT hr=DirectPlayLobbyBase->QueryInterface(IID_IDirectPlayLobby3, (void **)&DirectPlayLobby);
	if (FAILED(hr))
	{
		SetErrorMessage(IDS_ERROR_DPLOBBYCREATE);
		return FALSE;
	}

	// Create DirectPlay object.
	GUID GuidTmp=NullGuid;
	if (FAILED(DirectPlayCreate(&GuidTmp, &DirectPlayBase, NULL)))
	{
		SetErrorMessage(IDS_ERROR_DPCREATE);
		ShutdownNetwork();
		return FALSE;
	}
	hr=DirectPlayBase->QueryInterface(IID_IDirectPlay4, (void **)&DirectPlay);
	if (FAILED(hr))
	{
		SetErrorMessage(IDS_ERROR_DPCREATE);
		ShutdownNetwork();
		return FALSE;
	}

	// Set address information for DirectPlay service provider.
	GuidTmp=DPSPGUID_SERIAL;
	if (!SetServiceProviderAddress(&GuidTmp,Port))
	{
		ShutdownNetwork();
		return FALSE;
	}

	// Connect.
	DPSESSIONDESC2 SessionDesc;
	DCZeroMemory(&SessionDesc, sizeof(DPSESSIONDESC2));
	SessionDesc.dwSize = sizeof(DPSESSIONDESC2);
	SessionDesc.guidApplication = AppGuid;
	
	if (Server)
	{
		// Start new session.
		SessionDesc.dwMaxPlayers = 2;
		SessionDesc.dwFlags = DPSESSION_KEEPALIVE | DPSESSION_CLIENTSERVER;
		SessionDesc.lpszSessionName = L"Server";
		hr=DirectPlay->Open(&SessionDesc, DPOPEN_CREATE);
	}
	else
	{
		// Connect to an existing session.
		GUID GuidSession=NullGuid;
		hr = DirectPlay->EnumSessions(&SessionDesc, 0, EnumSessionsCallback, &GuidSession, DPENUMSESSIONS_AVAILABLE);
		if (GuidSession==NullGuid)
			hr=DPERR_GENERIC;
		if(SUCCEEDED(hr))
		{
			SessionDesc.guidInstance = GuidSession;
			hr = DirectPlay->Open(&SessionDesc, DPOPEN_JOIN);
		}
	}

	if (FAILED(hr))
	{
		SetErrorMessage(IDS_ERROR_DPCONNECT);
		ShutdownNetwork();
		return FALSE;
	}

	// Create server player.
	if (FAILED(DirectPlay->CreatePlayer(&OurPlayer,
										NULL, // Player name
										NULL, // hEvent for receiving messages for this player
										NULL, // Initial data
										0,	  // Size of initial Data
										(Server) ? DPPLAYER_SERVERPLAYER : 0)))  // Player type.
	{
		SetErrorMessage(IDS_ERROR_DPMISC);
		ShutdownNetwork();
		return FALSE;
	}

	OtherPlayer=(Server) ? DPID_ALLPLAYERS : DPID_SERVERPLAYER;

	return TRUE;
}

void ShutdownNetwork()
{
	// Kill off the sender thread first.
	if (SenderInitialized)
		ShutdownSender();

	OurPlayer=OtherPlayer=0;

	if (DirectPlay)
	{
		DirectPlay->Close();
		DirectPlay->Release();
		DirectPlay=NULL;
	}
	if (DirectPlayBase)
	{
		DirectPlayBase->Release();
		DirectPlayBase=NULL;
	}
	if (DirectPlayLobby)
	{
		DirectPlayLobby->Release();
		DirectPlayLobby=NULL;
	}
	if (DirectPlayLobbyBase)
	{
		DirectPlayLobbyBase->Release();
		DirectPlayLobbyBase=NULL;
	}
}

BOOL IsNetworkClient()
{
	return (DirectPlay && !Server);	
}

// Variables for stats.
static int LastReceivedBytes,CurrentReceivedBytes;
static int LastSentBytes,CurrentSentBytes;

void TickNetworkSend()
{
	LastReceivedBytes=CurrentReceivedBytes;
	LastSentBytes=CurrentSentBytes;
	CurrentReceivedBytes=CurrentSentBytes=0;
}

void TickNetworkReceive(void (*Callback)(void *Buffer, int Size))
{
	if (!DirectPlay)
		return;

	HRESULT hr;
	BYTE LocalBuffer[0x400];
	BYTE *Buffer;
	DWORD BufferSize;
	DPID PlayerFrom, PlayerTo;

	do
	{
		Buffer=LocalBuffer;
		BufferSize=sizeof(LocalBuffer);
		
		hr = DirectPlay->Receive(&PlayerFrom, &PlayerTo, DPRECEIVE_ALL, Buffer, &BufferSize);

		if(hr == DPERR_BUFFERTOOSMALL)
		{
			Buffer = (BYTE *) DCMalloc(BufferSize);
			if (Buffer)
				DirectPlay->Receive(&PlayerFrom, &PlayerTo, DPRECEIVE_ALL, Buffer, &BufferSize);
		}

		if (SUCCEEDED(hr))
		{
			if(PlayerFrom != DPID_SYSMSG)
			{
				// Non system message.
				Callback(Buffer,BufferSize);
			}
			CurrentReceivedBytes+=BufferSize;
		}
		if (Buffer!=LocalBuffer)
			DCFree(Buffer);
	} while(SUCCEEDED(hr));
}

void SendNetworkPacket(void *Buffer, int Size)
{
	if (!DirectPlay)
		return;

	if (Server)
	{
		// We initialize the sender thread here rather than earlier
		// to cover the case when a client never attaches.
		if (!SenderInitialized)
			if (!InitSender())
				return;
		
		// Queue packet to be sent.
		QueueItem(Buffer,Size);
	}
	else
	{
		// On the client don't worry about sending in the background since
		// sends are rare and not done in performance critical areas.
		DirectPlay->Send(OurPlayer,OtherPlayer,DPSEND_GUARANTEED,Buffer,Size);
//		DirectPlay->SendEx(OurPlayer,OtherPlayer,DPSEND_ASYNC | DPSEND_NOSENDCOMPLETEMSG,
//						   Buffer,Size,
//						   0,0,NULL,NULL);
	}

	CurrentSentBytes+=Size;
}

// Certain DPlay service providers (all on Dreamcast) don't support
// asynchronous sends so we do it ourselves via threads.
#define MAX_QUEUE_ITEMS 65536
#define QUEUE_BUFFER_SIZE (128*1024)

static CRITICAL_SECTION CritSec;
static BYTE *QueueBuffer;
static HANDLE SenderWakeupEvent;
static HANDLE MainWakeupEvent;
static HANDLE SenderThread;
static DWORD SenderThreadID;

// This stuff should only be accessed in the critical section.
static BOOL SenderNeedsWakeup;
static BOOL MainNeedsWakeup;
static BOOL SenderExit;
static int CurrentQueueItem, EndQueueItem;
static struct {	int BufferOffset, Size; } QueueItems[MAX_QUEUE_ITEMS];

// Inits the sender thread and related stuff.
BOOL InitSender()
{
	// Init vars.
	SenderNeedsWakeup=MainNeedsWakeup=SenderExit=FALSE;
	CurrentQueueItem=EndQueueItem=-1;

	// Init critical section.
	InitializeCriticalSection(&CritSec);

	// Allocate buffer for queue.
	QueueBuffer=(BYTE *)DCMalloc(QUEUE_BUFFER_SIZE);
	if (!QueueBuffer)
		return FALSE;

	// Create events.
	SenderWakeupEvent=CreateEvent(NULL, FALSE, FALSE, NULL);
	MainWakeupEvent=CreateEvent(NULL, FALSE, FALSE, NULL);
	if (!SenderWakeupEvent || !MainWakeupEvent)
	{
		ShutdownSender();
		return FALSE;
	}
		
	// Create the thread.
	SenderThread=CreateThread(NULL, 0, SenderFunc, 0, 0, &SenderThreadID);
	if (!SenderThread)
	{
		ShutdownSender();
		return FALSE;
	}

	SenderInitialized=TRUE;
	return TRUE;
}

void ShutdownSender()
{
	SenderInitialized=FALSE;

	if (SenderThread)
	{
		// Tell thread to exit.
		EnterCriticalSection(&CritSec);
		SenderExit=TRUE;
		if (SenderNeedsWakeup)
		{
			SetEvent(SenderWakeupEvent);
			SenderNeedsWakeup=FALSE;
		}
		LeaveCriticalSection(&CritSec);

		// Wait for it to terminate.
		WaitForSingleObject(SenderThread,INFINITE);

		// Close it.
		CloseHandle(SenderThread);
		SenderThread=NULL;
		SenderThreadID=0;
	}

	if (SenderWakeupEvent)
	{
		CloseHandle(SenderWakeupEvent);
		SenderWakeupEvent=NULL;
	}

	if (MainWakeupEvent)
	{
		CloseHandle(MainWakeupEvent);
		MainWakeupEvent=NULL;
	}

	DCSafeFree(QueueBuffer);

	DeleteCriticalSection(&CritSec);
}

void QueueItem(void *Data, int Size)
{
	if (Size > QUEUE_BUFFER_SIZE) // Overkill.
		return;

	for (;;)
	{
		EnterCriticalSection(&CritSec);

		// Look for place in queue to put buffer.
		if (EndQueueItem<0)
		{
			// Nothing in queue so use first item.
			CurrentQueueItem=EndQueueItem=0;
			QueueItems[0].BufferOffset=0;
		}
		else
		{
			int Item,Offset;

			Item=EndQueueItem+1;
			if (Item>=MAX_QUEUE_ITEMS)
				Item=0;

			Offset=QueueItems[EndQueueItem].BufferOffset+QueueItems[EndQueueItem].Size;
			if (Offset+Size >= QUEUE_BUFFER_SIZE)
				Offset=0;

			if (Item==CurrentQueueItem || 
				(Offset<QueueItems[CurrentQueueItem].BufferOffset && 
				 Offset+Size>=QueueItems[CurrentQueueItem].BufferOffset))
			{
				// No room in buffer so go to sleep and have
				// sender wake us when its finished an item.
				MainNeedsWakeup=TRUE;
				LeaveCriticalSection(&CritSec);

				WaitForSingleObject(MainWakeupEvent,INFINITE);
				
				// Try again.
				continue;
			}

			EndQueueItem=Item;
			QueueItems[Item].BufferOffset=Offset;
		}

		// Copy data.
		QueueItems[EndQueueItem].Size=Size;
		DCCopyMemory(QueueBuffer + QueueItems[EndQueueItem].BufferOffset,Data,Size);

		// Wake up sender if necessary.
		if (SenderNeedsWakeup)
		{
			SenderNeedsWakeup=FALSE;
			SetEvent(SenderWakeupEvent);
		}

		// We are done.
		LeaveCriticalSection(&CritSec);
		break;
	}
}

DWORD WINAPI SenderFunc(LPVOID lpParam)
{
	BYTE *Data;
	int Size;

	EnterCriticalSection(&CritSec);

	for (;;)
	{
		// See if anything in queue.
		if (CurrentQueueItem < 0)
		{
			// See if we are supposed to quit.
			if (SenderExit)
				break;

			// Go to sleep.
			SenderNeedsWakeup=TRUE;
			LeaveCriticalSection(&CritSec);

			WaitForSingleObject(SenderWakeupEvent,INFINITE);

			// Look at queue again.
			EnterCriticalSection(&CritSec);
			continue;
		}

		Data=QueueBuffer + QueueItems[CurrentQueueItem].BufferOffset;
		Size=QueueItems[CurrentQueueItem].Size;

		LeaveCriticalSection(&CritSec);

		// Send Data.
		DirectPlay->Send(OurPlayer,OtherPlayer,DPSEND_GUARANTEED,Data,Size);
	
		EnterCriticalSection(&CritSec);

		// Adjust Queue.
		if (CurrentQueueItem==EndQueueItem)
		{
			// Buffer empty.
			CurrentQueueItem=EndQueueItem=-1;
		}
		else
		{
			CurrentQueueItem++;
			if (CurrentQueueItem>=MAX_QUEUE_ITEMS)
				CurrentQueueItem=0;
		}

		// Give main a wakeup if it wants one.
		if (MainNeedsWakeup)
		{
			MainNeedsWakeup=FALSE;
			SetEvent(MainWakeupEvent);
		}
	}

	LeaveCriticalSection(&CritSec);
	return 0;
}


void GetNetStats(int *ReceivedBytes,int *SentBytes, int *PacketsQueued, int *DataQueued)
{
	*ReceivedBytes=LastReceivedBytes;
	*SentBytes=LastSentBytes;
	*PacketsQueued=*DataQueued=0;

	if (SenderInitialized && EndQueueItem>0)
	{
		EnterCriticalSection(&CritSec);

		*PacketsQueued=EndQueueItem-CurrentQueueItem+1;
		if (*PacketsQueued<0)
			*PacketsQueued+=MAX_QUEUE_ITEMS;

		*DataQueued=QueueItems[EndQueueItem].BufferOffset +
					QueueItems[EndQueueItem].Size -
					QueueItems[CurrentQueueItem].BufferOffset;
		if (*DataQueued<0)
			*DataQueued+=QUEUE_BUFFER_SIZE;

		LeaveCriticalSection(&CritSec);
	}

}
