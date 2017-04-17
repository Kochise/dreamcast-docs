/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    DCNetwork.h

Abstract:

   Network functions. 

-------------------------------------------------------------------*/

BOOL InitNetwork(BOOL Server, int Port);
void ShutdownNetwork();

BOOL IsNetworkClient();

void TickNetworkReceive(void (*Callback)(void *Buffer, int Size));
void TickNetworkSend();

void SendNetworkPacket(void *Buffer, int Size);

void GetNetStats(int *ReceivedBytes,int *SentBytes, int *PacketsQueued, int *DataQueued);
