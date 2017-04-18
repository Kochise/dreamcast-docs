
//=============================================================================
//  Microsoft (R) Bloodhound (tm). Copyright (C) 1991-1992.
//
//  MODULE: buffer.h
//
//  This source file contains defintions for Bloodhound buffers.
//=============================================================================

#if !defined(_BUFFER_)

#define _BUFFER_

#pragma pack(1)

#define BUFFERSIZE      ((DWORD) 32768U)    //... Size of each buffer (NDIS and ODI NAL's).

#define ONE_MEG         32

#define ONE_HALF_MEG    (ONE_MEG / 2)

#define STAT_FRAME_SIZE 1024

//=============================================================================
//  Frame type.
//=============================================================================

typedef struct _FRAME
{
    DWORD   TimeStamp;		//... Relative time in milliseconds.
    WORD    FrameLength;	//... MAC frame length.
    WORD    nBytesAvail;	//... Actual frame length copied.
    BYTE    MacFrame[0];	//... Frame data.
} FRAME;

typedef FRAME *LPFRAME;
typedef FRAME UNALIGNED *ULPFRAME;

#define FRAME_SIZE  sizeof(FRAME)

//=============================================================================
//  Buffer Table Entry (BTE). This is the private part of the buffer for
//  the NDIS 2.0, NDIS 3.0, and ODI nals.
//=============================================================================

typedef struct _BTE *LPBTE;

typedef struct _BTE
{
    DWORD   ObjectType; 	//... 'BTE$'. Filled in byt kernel.
    DWORD   Flags;		//... Used by Nal/driver.
    LPBTE   KrnlModeNext;	//... Optional, reserved for NAL usage.
    LPBTE   Next;		//... Pointer to next BTE.
    LPFRAME UserModeBuffer;	//... User mode buffer pointer.
    LPVOID  KrnlModeBuffer;	//... Kernel mode buffer pointer.
    DWORD   Length;		//... Overall buffer length (in bytes)
    DWORD   ByteCount;		//... Number of bytes in buffer.
    DWORD   FrameCount; 	//... Number of frames in buffer.
    WORD    DropCount;          //... Number of dropped frames detected.
    WORD    TransfersPended;    //... Number of transferdatas pended by mac
} BTE;

#define BTE_SIZE    sizeof(BTE)

//=============================================================================
//  Buffer type.
//=============================================================================

typedef struct _BUFFER
{
    //=========================================================================
    //  PUBLIC portion of BUFFER type. This section is filled in by NAL.DLL.
    //  The public section is 64 bytes in size.
    //=========================================================================

    DWORD           ObjectType;         //... 'BUF$'.
    DWORD           NetworkID;          //... Network ID.
    DWORD           BufferSize;         //... Buffer size requested.
    DWORD           TotalBytes;         //... Total bytes captured.
    DWORD           TotalFrames;        //... Total frames captured.
    LPVOID          hNetwork;           //... Handle of network.
    SYSTEMTIME      TimeOfCapture;      //... Time of capture.
    LPBTE           StatFrameBTE;          //... Pointer to the stat frame
    DWORD           Reserved[5];        //... Reserved for future use.

    //=========================================================================
    //  PRIVATE portion of BUFFER type. This section is filled by NAL drivers/dlls.
    //  The private section is 32 bytes in size.
    //=========================================================================

//    BYTE	    Private[32];	//... 32 bytes of private space for NAL use.
//  start MSINTERNAL
    DWORD	    HeadBTEIndex;	//... BTE containing frame #1, filled in by NAL.
    DWORD	    TailBTEIndex;	//... BTE containing frame #N, filled in by NAL.
    DWORD	    NumberOfBuffers;	//... Total number of BTE's, filled in by kernel.
    DWORD           NumberOfBuffersUsed;//... Total number of BTE's used, filled in by driver.
    DWORD           Pad[4];             //... Pad out to 32 bytes.
    BTE             bte[0];             //... BTE's follow BUFFER structure in memory.
// stop MSINTERNAL
} BUFFER;

typedef BUFFER *HBUFFER;

//=============================================================================
//  FUNCTION: GetBteIndex();
//
//  Modification History
//
//  raypa       07/10/93                Created.
//=============================================================================

#define GetBteIndex(hBuffer, lpBte)       ((DWORD) ((lpBte) - (hBuffer)->bte))

#pragma pack()

#endif
