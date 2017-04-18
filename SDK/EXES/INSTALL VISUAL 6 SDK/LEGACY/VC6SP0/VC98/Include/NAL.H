
//=============================================================================
//  Microsoft (R) Bloodhound. Copyright (C) 1991-1994.
//
//  MODULE: nal.h
//
//  This source file contains defintions for the Network Abstraction Layer (NAL)
//=============================================================================

#if !defined(_NAL_)

#define _NAL_

#pragma pack(1)

//=============================================================================
//  NETWORK API's.
//=============================================================================

extern DWORD                WINAPI CancelTransmit(HNETWORK hNetwork, LPVOID TxCorrelator);

extern DWORD                WINAPI CloseNetwork(HNETWORK hNetwork, DWORD CloseFlags);

extern DWORD                WINAPI ContinueCapturing(HNETWORK hNetwork);

extern DWORD                WINAPI EnumNetworks(VOID);

extern HBUFFER              WINAPI GetNetworkBuffer(HNETWORK hNetwork);

extern NETWORKPROC          WINAPI GetNetworkCallback(HNETWORK hNetwork);

extern LPNETWORKINFO        WINAPI GetNetworkInfo(DWORD NetworkID);

extern DWORD                WINAPI GetNetworkID(HNETWORK hNetwork);

extern LPVOID               WINAPI GetNetworkInstanceData(HNETWORK hNetwork);

extern HNETWORK             WINAPI OpenNetwork(DWORD NetworkID,
                                               HPASSWORD hPassword,
                                               NETWORKPROC NetworkProc,
                                               LPVOID UserContext,
                                               LPSTATISTICSPARAM StatisticsParam);

extern DWORD                WINAPI PauseCapturing(HNETWORK hNetwork);

extern DWORD                WINAPI SetNetworkBuffer(HNETWORK hNetwork, HBUFFER hBuffer);

extern DWORD                WINAPI SetNetworkFilter(HNETWORK hNetwork, LPCAPTUREFILTER lpCaptureFilter, HBUFFER hBuffer);

extern LPVOID               WINAPI SetNetworkInstanceData(HNETWORK hNetwork, LPVOID InstanceData);

extern NETWORKPROC          WINAPI SetNetworkCallback(HNETWORK hNetwork, NETWORKPROC NetworkProc);

extern DWORD                WINAPI StartCapturing(HNETWORK hNetwork, HBUFFER hBuffer);

extern DWORD                WINAPI StopCapturing(HNETWORK hNetwork);

extern LPVOID               WINAPI TransmitQueue(HNETWORK hNetwork, LPPACKETQUEUE PacketQueue);

extern VOID                 WINAPI TransmitSpecialFrame( DWORD FrameType, DWORD Flags, LPBYTE pUserData, DWORD UserDataLength );

extern LPNETWORKSTATUS      WINAPI QueryNetworkStatus(HNETWORK hNetwork, LPNETWORKSTATUS NetworkStatus);

extern DWORD                WINAPI ClearStatistics(HNETWORK hNetwork);

extern DWORD                WINAPI GetReconnectInfo(HNETWORK        hNetwork,
                                                    LPRECONNECTINFO ReconnectInfoBuffer,
                                                    DWORD           ReconnectInfoBufferLength,
                                                    LPDWORD         nBytesAvail);


extern DWORD                WINAPI SetConnectInfo(HNETWORK        hNetwork,
                                                  LPRECONNECTINFO ReconnectInfoBuffer,
                                                  DWORD           ReconnectInfoBufferLength);

extern DWORD                WINAPI SetupNetwork(DWORD NetworkID, LPSETUPNETWORKPARMS lpSetupParms);
extern DWORD                WINAPI DestroyNetworkID(DWORD NetworkID );

//=============================================================================
//  BUFFER API's
//=============================================================================

extern HBUFFER              WINAPI AllocNetworkBuffer(DWORD NetworkID, DWORD BufferSize);

extern HBUFFER              WINAPI FreeNetworkBuffer(HBUFFER hBuffer);

extern VOID                 WINAPI CompactNetworkBuffer(HBUFFER hBuffer);

extern LPFRAME              WINAPI GetNetworkFrame(HBUFFER hBuffer, DWORD FrameNumber);

extern DWORD                WINAPI GetBufferSize(HBUFFER hBuffer);

extern DWORD                WINAPI GetBufferTotalFramesCaptured(HBUFFER hBuffer);

extern DWORD                WINAPI GetBufferTotalBytesCaptured(HBUFFER hBuffer);

extern LPSYSTEMTIME         WINAPI GetBufferTimeStamp(HBUFFER hBuffer, LPSYSTEMTIME SystemTime);

#pragma pack()
#endif
