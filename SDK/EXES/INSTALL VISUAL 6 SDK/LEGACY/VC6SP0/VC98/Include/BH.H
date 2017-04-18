
//=============================================================================
//  Microsoft (R) Bloodhound (tm). Copyright (C) 1991-1998.
//
//  MODULE: bh.h
//
//  This is the top-level include file for all Bloodhound components.
//=============================================================================

#if !defined(_BH_)

#define _BH_

#include "naltypes.h"               //... Network types.
#include "bhsupp.h"                 //... Supplemental API's.
#include "nal.h"                    //... Network definitions.
#include "bhtypes.h"                //... Type definitions for BH.
#include "bherr.h"                  //... Error code definitions for BH.
#include "bhfilter.h"               //... Filter definitions.
#include "parser.h"                 //... Parser helper functions and structures.
#include "inilib.h"

#pragma pack(1)

//=============================================================================
//  A frame with no number contains this value as its frame number.
//=============================================================================

#define INVALID_FRAME_NUMBER            ((DWORD) -1)

//=============================================================================
//  Capture file flags.
//=============================================================================

#define CAPTUREFILE_OPEN                OPEN_EXISTING
#define CAPTUREFILE_CREATE              CREATE_NEW

//=============================================================================
//  TRANSMIT API's.
//=============================================================================

extern LPTRANSMITSTATS      WINAPI TransmitFrame(HNETWORK   hNetwork,
                                                 HFRAME     hFrame,
                                                 DWORD      Iterations,
                                                 DWORD      TimeDelta,
                                                 LPDWORD    TxCorrelator);

extern LPTRANSMITSTATS      WINAPI TransmitCapture(HNETWORK     hNetwork,
                                                   HCAPTURE     hCapture,
                                                   DWORD        StartingFrameNumber,
                                                   DWORD        EndingFrameNumber,
                                                   DWORD        Iterations,
                                                   DWORD        IterationTimeDelta,
                                                   DWORD        TimeDelta,
                                                   FILTERPROC   FilterProc,
                                                   LPVOID       FilterInstData,
                                                   LPDWORD      TxCorrelator);

//=============================================================================
//  CAPTURE CONTEXT API's.
//=============================================================================

extern DWORD                WINAPI StationQuery(DWORD NetworkID,
                                               LPADDRESS DestAddress,
                                               LPQUERYTABLE QueryTable,
                                               HPASSWORD hPassword);

extern HCAPTURE             WINAPI CreateCapture(HWND hWnd,
                                                HBUFFER hBuffer,
                                                HPASSWORD hPassword);

extern DWORD                WINAPI DestroyCapture(HCAPTURE hCapture);

extern LPVOID               WINAPI GetCaptureInstanceData(HCAPTURE hCapture);

extern HADDRESSDB           WINAPI GetCaptureAddressDB(HCAPTURE hCapture);

extern LPSYSTEMTIME         WINAPI GetCaptureTimeStamp(HCAPTURE hCapture);

extern DWORD                WINAPI GetCaptureTotalFrames(HCAPTURE hCapture);

extern HBUFFER              WINAPI GetCaptureBuffer(HCAPTURE hCapture);

extern LPSTR                WINAPI GetCaptureComment(HCAPTURE hCapture);

extern DWORD                WINAPI LoadCapture(HCAPTURE hCapture, LPSTR FileName);

extern DWORD                WINAPI SaveCapture(HCAPTURE   hCapture,
                                              LPSTR      FileName,
                                              LPSTR      lpComment,
                                              LPVOID     UserData,
                                              DWORD      UserDataLength,
                                              FILTERPROC FilterProc,
                                              LPVOID     FilterInstData,
                                              DWORD      nFirstFrame,
                                              DWORD      nLastFrame);

extern LPVOID               WINAPI SetCaptureInstanceData(HCAPTURE hCapture, LPVOID InstData);

extern HADDRESSDB           WINAPI SetCaptureAddressDB(HCAPTURE hCapture, HADDRESSDB);

//=============================================================================
//  FRAME HELP API's.
//=============================================================================

extern BOOL                 WINAPI ConvertMacAddress(LPADDRESS Address, DWORD NewAddressType);

extern DWORD                WINAPI MacTypeToAddressType(DWORD MacType);

extern DWORD                WINAPI AddressTypeToMacType(DWORD AddressType);

extern DWORD                WINAPI GetFrameDstAddressOffset(HFRAME hFrame, DWORD AddressType, LPDWORD AddressLength);

extern DWORD                WINAPI GetFrameSrcAddressOffset(HFRAME hFrame, DWORD AddressType, LPDWORD AddressLength);

extern HCAPTURE             WINAPI GetFrameCaptureHandle(HFRAME hFrame);


extern DWORD                WINAPI GetFrameDestAddress(HFRAME       hFrame,
                                                       LPADDRESS    lpAddress,
                                                       DWORD        AddressType,
                                                       DWORD        Flags);

extern DWORD                WINAPI GetFrameSourceAddress(HFRAME     hFrame,
                                                         LPADDRESS  lpAddress,
                                                         DWORD      AddressType,
                                                         DWORD      Flags);

extern DWORD                WINAPI GetFrameMacHeaderLength(HFRAME hFrame);

extern BOOL                 WINAPI CompareFrameDestAddress(HFRAME hFrame, LPADDRESS lpAddress);

extern BOOL                 WINAPI CompareFrameSourceAddress(HFRAME hFrame, LPADDRESS lpAddress);

extern DWORD                WINAPI GetFrameLength(HFRAME hFrame);

extern DWORD                WINAPI GetFrameStoredLength(HFRAME hFrame);

extern DWORD                WINAPI GetFrameMacType(HFRAME hFrame);

extern DWORD                WINAPI GetFrameMacHeaderLength(HFRAME hFrame);

extern DWORD                WINAPI GetFrameNumber(HFRAME hFrame);

extern LPBYTE               WINAPI GetFrameRoutingInformation(HFRAME hFrame, LPDWORD lpRILength);

extern DWORD                WINAPI GetFrameTimeStamp(HFRAME hFrame);

extern int                  WINAPI CompareRawAddresses(LPBYTE Address1, LPBYTE Address2, UINT AddressType);

//=============================================================================
//  FRAME API's.
//=============================================================================

extern DWORD                WINAPI InsertFrame(HCAPTURE hCapture, HFRAME hFrame, DWORD FrameNumber);

extern DWORD                WINAPI DeleteFrame(HCAPTURE hCapture, DWORD FrameNumber);

extern HFRAME               WINAPI ModifyFrame(HCAPTURE hCapture,
                                               DWORD    FrameNumber,
                                               LPBYTE   FrameData,
                                               DWORD    FrameLength,
                                               DWORD    TimeStamp);

extern HFRAME               WINAPI CreateFrame(LPBYTE FrameData, DWORD FrameLength, DWORD TimeStamp);

extern DWORD                WINAPI DestroyFrame(HFRAME hFrame);

extern HFRAME               WINAPI FindNextFrame(HFRAME hCurrentFrame,
                                                LPSTR ProtocolName,
                                                LPADDRESS lpDesstAddress,
                                                LPADDRESS lpSrcAddress,
                                                LPWORD ProtocolOffset,
                                                DWORD  OriginalFrameNumber,
                                                DWORD  nHighestFrame);

extern HFRAME               WINAPI FindPreviousFrame(HFRAME hCurrentFrame,
                                                    LPSTR ProtocolName,
                                                    LPADDRESS lpDstAddress,
                                                    LPADDRESS lpSrcAddress,
                                                    LPWORD ProtocolOffset,
                                                    DWORD  OriginalFrameNumber,
                                                    DWORD  nLowestFrame );

extern DWORD                WINAPI FrameRecognize(HFRAME hFrame);

extern HCAPTURE             WINAPI GetFrameCaptureHandle(HFRAME);

extern HFRAME               WINAPI GetFrame(HCAPTURE hCapture, DWORD FrameNumber);

extern LPRECOGNIZEDATATABLE WINAPI GetFrameRecognizeData(HFRAME hFrame);

extern LPBYTE               WINAPI LockFrame(HFRAME hFrame);

extern LPPROPERTYTABLE      WINAPI LockFrameText(HFRAME hFrame);

extern LPPROPERTYTABLE      WINAPI LockFramePropertyTable(HFRAME hFrame);

extern DWORD                WINAPI UnlockFrame(HFRAME hFrame);

extern DWORD                WINAPI UnlockFrameText(HFRAME hFrame);

extern DWORD                WINAPI UnlockFramePropertyTable(HFRAME hFrame);


//=============================================================================
//  AddFrame() is a special form of insert frame, it add the frame to
//  the end of the current capture.
//=============================================================================

INLINE DWORD WINAPI AddFrame(HCAPTURE hCapture, HFRAME hFrame)
{
    return InsertFrame(hCapture, hFrame, INVALID_FRAME_NUMBER);
}


#ifdef DEBUG
extern VOID                 WINAPI DebugShowLocks(HCAPTURE hCapture);

extern VOID                 WINAPI DebugGetFrameLocks(HFRAME hFrame, LPDWORD lpLocks, LPDWORD lpPropertyTableLocks);

extern BOOL                 WINAPI DebugIsRemote(HCAPTURE hCapture);
#endif

//=============================================================================
//  Protocol API's.
//=============================================================================

extern HPROTOCOL            WINAPI CreateProtocol(LPSTR ProtocolName,
                                                  LPENTRYPOINTS lpEntryPoints,
                                                  DWORD cbEntryPoints);

extern VOID                 WINAPI DestroyProtocol(HPROTOCOL hProtocol);

extern DWORD                WINAPI DisableProtocol(HCAPTURE hCapture, HPROTOCOL hProtocol);

extern DWORD                WINAPI EnableProtocol(HCAPTURE hCapture, HPROTOCOL hProtocol);

extern LPPROTOCOLTABLE      WINAPI EnumProtocols(VOID);

extern LPPROTOCOLINFO       WINAPI GetProtocolInfo(HPROTOCOL hProtocol);

extern LPSTR                WINAPI GetProtocolDLLName(HPROTOCOL hProtocol);

extern HPROPERTY            WINAPI GetProperty(HPROTOCOL hProtocol, LPSTR PropertyName);

extern HPROTOCOL            WINAPI GetProtocolFromProperty(HPROPERTY hProperty);

extern HPROTOCOL            WINAPI GetProtocolFromName(LPSTR ProtocolName);

extern DWORD                WINAPI GetProtocolStartOffset(HFRAME hFrame, LPSTR ProtocolName);

extern DWORD                WINAPI GetProtocolStartOffsetHandle(HFRAME hFrame, HPROTOCOL hProtocol);

extern LPPROTOCOLTABLE      WINAPI GetEnabledProtocols(HCAPTURE hCapture);

extern HPROTOCOL            WINAPI GetProtocolFromProtocolID(DWORD dwProtocolID);

extern VOID                 WINAPI SetMaxAmountOfProtocols(DWORD dwAmountOfProtocols);

extern DWORD                WINAPI GetMaxAmountOfProtocols();

//=============================================================================
//  Property API's.
//=============================================================================

extern DWORD                WINAPI CreatePropertyDatabase(HPROTOCOL hProtocol, DWORD nProperties);

extern DWORD                WINAPI DestroyPropertyDatabase(HPROTOCOL hProtocol);

extern HPROPERTY            WINAPI AddProperty(HPROTOCOL hProtocol, LPPROPERTYINFO PropertyInfo);

extern LPPROPERTYINST       WINAPI AttachPropertyInstance(HFRAME    hFrame,
                                                          HPROPERTY hProperty,
                                                          DWORD     Length,
                                                          ULPVOID   lpData,
                                                          DWORD     HelpID,
                                                          DWORD     Level,
                                                          DWORD     IFlags);

extern LPPROPERTYINST       WINAPI AttachPropertyInstanceEx(HFRAME      hFrame,
                                                            HPROPERTY   hProperty,
                                                            DWORD       Length,
                                                            ULPVOID     lpData,
                                                            DWORD       ExLength,
                                                            ULPVOID     lpExData,
                                                            DWORD       HelpID,
                                                            DWORD       Level,
                                                            DWORD       IFlags);

extern LPPROPERTYINST       WINAPI FindPropertyInstance(HFRAME hFrame, HPROPERTY hProperty);

extern LPPROPERTYINFO       WINAPI GetPropertyInfo(HPROPERTY hProperty);

extern LPSTR                WINAPI GetPropertyText(HFRAME hFrame, LPPROPERTYINST lpPI, LPSTR szBuffer, DWORD BufferSize);

extern INT WINAPI QueryProtocolState(HCAPTURE hCapture, HPROTOCOL hProtocol);

//=============================================================================
//  ADDRESS API's.
//=============================================================================

extern LPADDRESSINFO        WINAPI AddAddress(HADDRESSDB hAddressDB,
                                              LPADDRESS  lpAddress,
                                              LPSTR      lpName,
                                              LPVOID     InstData);

extern HADDRESSDB           WINAPI CreateAddressDatabase(VOID);

extern DWORD                WINAPI DeleteAddress(HADDRESSDB hAddressDB, LPADDRESS lpAddressToDelete);

extern DWORD                WINAPI DestroyAddressDatabase(HADDRESSDB hAddressDB);

extern DWORD                WINAPI EmptyAddressDatabase(HADDRESSDB hAddressDB);

extern LPADDRESSINFO        WINAPI GetAddressInfo(HADDRESSDB hAddressDB, LPADDRESS lpAddress);

extern LPADDRESSINFO        WINAPI GetAddressInfoByName(HADDRESSDB hAddressDB, LPSTR lpName);

extern LPADDRESSINFOTABLE   WINAPI EnumAddresses(HADDRESSDB hAddressDB, int SortByType);

extern LPVOID               WINAPI GetAddressDatabaseInstanceData(HADDRESSDB hAddressDB);

extern LPVOID               WINAPI SetAddressDatabaseInstanceData(HADDRESSDB hAddressDB, LPVOID InstData);

extern LPADDRESSINFO *      WINAPI FindAddressInfoByAddress(LPADDRESSINFOTABLE lpAddressInfoTable, LPADDRESS lpAddress);

extern LPADDRESSINFO *      WINAPI FindAddressInfoByName(LPADDRESSINFOTABLE lpAddressInfoTable, LPSTR lpName,
                                                         LPADDRESS lpSpecificAddress );

//=============================================================================
//  MISC. API's.
//=============================================================================

extern LPSTR                WINAPI GetSystemPath(LPSTR Path, DWORD Length);

extern DWORD                WINAPI GetCaptureCommentFromFilename(LPSTR lpFilename, LPSTR lpComment, DWORD BufferSize);

extern int                  WINAPI CompareAddresses(LPADDRESS lpAddress1, LPADDRESS lpAddress2);

extern DWORD                WINAPIV FormatPropertyInstance(LPPROPERTYINST lpPropertyInst, ...);

extern SYSTEMTIME *         WINAPI AdjustSystemTime(SYSTEMTIME *SystemTime, DWORD TimeDelta);

//=============================================================================
//  MISC. API's.
//=============================================================================

extern VOID                 WINAPI eprintf(LPSTR format, ...);

extern VOID                 WINAPI CreateErrorLogEntry(VOID);

extern DWORD                WINAPI BHGetLastError(VOID);

extern DWORD                WINAPI BHSetLastError(DWORD Error);

extern DWORD                WINAPI ResetPropertyInstanceLength( LPPROPERTYINST lpProp,
                                                                WORD nOrgLen,
                                                                WORD nNewLen );

//=============================================================================
//  DEBUG API's.
//=============================================================================

#ifdef DEBUG

//=============================================================================
//  BreakPoint() macro.
//=============================================================================

#ifdef _X86_
#define BreakPoint()        _asm { int 3h }
#else
#define BreakPoint()        DebugBreak()
#endif

//=============================================================================
//  FUNCTION: BhAssert()
//=============================================================================

INLINE VOID BhAssert(
    LPVOID  assert,
    LPSTR   file,
    UINT    line,
    LPVOID  msg
    )
{
    if ( msg == NULL )
    {
        dprintf("ASSERT -- %s occured on line %u of file %s.\n",
                 assert,
                 line,
                 file);
    }
    else
    {
        dprintf("ASSERT -- %s occured on line %u of file %s: Message = %s.\n",
                assert,
                line,
                file,
                msg);
    }
}

//=============================================================================
//  MACRO: ASSERT()
//=============================================================================

#define ASSERT(exp)                                 \
{                                                   \
    if ( !(exp) )                                   \
    {                                               \
        BhAssert(#exp, __FILE__, __LINE__, NULL);   \
        BreakPoint();                               \
    }                                               \
}                                                   \

#define ASSERTMSG(exp, msg)                         \
{                                                   \
    if ( !(exp) )                                   \
    {                                               \
        BhAssert(#exp, __FILE__, __LINE__, msg);    \
        BreakPoint();                               \
    }                                               \
}                                                   \

#else   //... DEBUG

#define ASSERT(exp)

#define ASSERTMSG(exp, msg)

#define ASSERT_DWORD_ALIGNMENT(p)       (p)

#endif  //... DEBUG

//=============================================================================
//  PanicPoint().
//=============================================================================

extern VOID WINAPI PanicMessage(UINT line, LPSTR file, LPSTR msg);

#ifdef DEBUG

#define PanicPoint()                            \
    {                                           \
        PanicMessage(__LINE__, __FILE__, NULL); \
        BreakPoint();                           \
    }

#else

#define PanicPoint()                            \
    {                                           \
        PanicMessage(__LINE__, __FILE__, NULL); \
    }

#endif

//=============================================================================
//  Alignment macro.
//=============================================================================

#ifndef _X86_
#ifdef DEBUG

INLINE LPVOID WINAPI ASSERT_DWORD_ALIGNMENT(LPVOID p)
{
    if ( (((DWORD) (p)) & 0x00000003) != 0 )
    {
        dprintf("Fatal error on line %u of %s. Pointer is not DWORD aligned.", __LINE__, __FILE__);

        BreakPoint();
    }

    return p;
}

#endif

#else
#define ASSERT_DWORD_ALIGNMENT(p)       (p)
#endif

#pragma pack()
#endif
