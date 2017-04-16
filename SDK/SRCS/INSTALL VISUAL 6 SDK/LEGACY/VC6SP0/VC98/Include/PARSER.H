
//=============================================================================
//  Microsoft (R) Bloodhound (tm). Copyright (C) 1991-1994.
//
//  MODULE: parser.h
//
//  This header file defines helper functions for use by Bloodhound parser DLL's.
//=============================================================================

#include "bhtypes.h"
#include "frame.h"

#if !defined(_PARSER_)

#define _PARSER_

#pragma pack(1)


//=============================================================================
//  Format Procedure Type.
//
//  NOTE: All format functions *must* be decalred as WINAPIV not WINAPI!
//=============================================================================

typedef VOID (WINAPIV *FORMAT)(LPPROPERTYINST, ...);

//=============================================================================
//  PROTOCOL_STATUS_RECOGNIZED:
//
//  The protocol recognized the frame and moved the pointer to end of its
//  protocol header. Bloodhound uses the protocols follow set to continue
//  parsing.
//=============================================================================

#define PROTOCOL_STATUS_RECOGNIZED                        0

//=============================================================================
//  PROTOCOL_STATUS_NOT_RECOGNIZED:
//
//  The protocol did not recognized the frame and did not move the pointer
//  (i.e. the start data pointer which was passed in). Bloodhound uses the
//  protocols follow set to continue parsing.
//=============================================================================

#define PROTOCOL_STATUS_NOT_RECOGNIZED                    1

//=============================================================================
//  PROTOCOL_STATUS_CLAIMED:
//
//  The protocol recognized the frame and claimed it all for itself,
//  and parsing terminates.
//=============================================================================

#define PROTOCOL_STATUS_CLAIMED                           2

//=============================================================================
//  PROTOCOL_STATUS_NEXT_PROTOCOL:
//
//  The protocol recognized the frame and moved the pointer to end of its
//  protocol header. The current protocol requests that Bloodhound continue
//  parsing at a known next protocol by returning the next protocols handle back
//  to Bloodhound. In this case, the follow of the current protocol, if any,
//  is not used.
//=============================================================================

#define PROTOCOL_STATUS_NEXT_PROTOCOL                     3

//=============================================================================
//  Macros.
//=============================================================================

extern  BYTE HexTable[];

#define XCHG(x)         MAKEWORD( HIBYTE(x), LOBYTE(x) )

#define DXCHG(x)        MAKELONG( XCHG(HIWORD(x)), XCHG(LOWORD(x)) )

#define LONIBBLE(b) ((BYTE) ((b) & 0x0F))

#define HINIBBLE(b)     ((BYTE) ((b) >> 4))

#define HEX(b)          (HexTable[LONIBBLE(b)])

#define SWAPBYTES(w)    ((w) = XCHG(w))

#define SWAPWORDS(d)    ((d) = DXCHG(d))

//=============================================================================
//  All the MAC frame types combined.
//=============================================================================

typedef union _MACFRAME
{
    LPBYTE      MacHeader;              //... generic pointer.
    LPETHERNET  Ethernet;               //... ethernet pointer.
    LPTOKENRING Tokenring;              //... tokenring pointer.
    LPFDDI      Fddi;                   //... FDDI pointer.
} MACFRAME;

typedef MACFRAME *LPMACFRAME;

#define HOT_SIGNATURE       MAKE_IDENTIFIER('H', 'O', 'T', '$')
#define HOE_SIGNATURE       MAKE_IDENTIFIER('H', 'O', 'E', '$')

typedef struct _HANDOFFENTRY
{
#ifdef DEBUGNEVER  // remove retail/debug mixing nightmare.
    DWORD       hoe_sig;                    //... 'HOE$'
#endif

   DWORD        hoe_ProtIdentNumber;        //Port/Socket number used to determine who to handoff to
   HPROTOCOL    hoe_ProtocolHandle;         //Handle of Protocol to hand off to
   DWORD        hoe_ProtocolData;           //Additional Data to pass to protocol when handed off
} HANDOFFENTRY;

typedef HANDOFFENTRY * LPHANDOFFENTRY;    

typedef struct _HANDOFFTABLE
{
#ifdef DEBUGNEVER  // remove retail/debug mixing nightmare.
    DWORD           hot_sig;                //... 'HOT$'
#endif

    DWORD           hot_NumEntries;
    LPHANDOFFENTRY  hot_Entries;
} HANDOFFTABLE, *LPHANDOFFTABLE;

//=============================================================================
//  Parser helper macros.
//=============================================================================

INLINE LPVOID GetPropertyInstanceData(LPPROPERTYINST PropertyInst)
{
    if ( PropertyInst->DataLength != (WORD) -1 )
    {
        return PropertyInst->lpData;
    }

    return (LPVOID) PropertyInst->lpPropertyInstEx->Byte;
}

#define GetPropertyInstanceDataValue(p, type)  ((type *) GetPropertyInstanceData(p))[0]

INLINE DWORD GetPropertyInstanceFrameDataLength(LPPROPERTYINST PropertyInst)
{
    if ( PropertyInst->DataLength != (WORD) -1 )
    {
        return PropertyInst->DataLength;
    }

    return PropertyInst->lpPropertyInstEx->Length;
}

INLINE DWORD GetPropertyInstanceExDataLength(LPPROPERTYINST PropertyInst)
{
    if ( PropertyInst->DataLength == (WORD) -1 )
    {
        PropertyInst->lpPropertyInstEx->Length;
    }

    return (WORD) -1;
}

//=============================================================================
//  Parser helper functions.
//=============================================================================

extern LPLABELED_WORD  WINAPI GetProtocolDescriptionTable(LPDWORD TableSize);

extern LPLABELED_WORD  WINAPI GetProtocolDescription(DWORD ProtocolID);

extern DWORD        WINAPI GetMacHeaderLength(LPVOID MacHeader, DWORD MacType);

extern DWORD        WINAPI GetLLCHeaderLength(LPLLC Frame);

extern DWORD        WINAPI GetEtype(LPVOID MacHeader, DWORD MacType);

extern DWORD        WINAPI GetSaps(LPVOID MacHeader, DWORD MacType);

extern BOOL         WINAPI IsLLCPresent(LPVOID MacHeader, DWORD MacType);

extern VOID         WINAPI CanonicalizeHexString(LPSTR hex, LPSTR dest, DWORD len);

extern void         WINAPI CanonHex(UCHAR * pDest, UCHAR * pSource, int iLen, BOOL fOx );

extern DWORD        WINAPI ByteToBinary(LPSTR string, DWORD ByteValue);

extern DWORD        WINAPI WordToBinary(LPSTR string, DWORD WordValue);

extern DWORD        WINAPI DwordToBinary(LPSTR string, DWORD DwordValue);

extern LPSTR        WINAPI AddressToString(LPSTR string, BYTE *lpAddress);

extern LPBYTE       WINAPI StringToAddress(BYTE *lpAddress, LPSTR string);

extern LPDWORD      WINAPI VarLenSmallIntToDword( LPBYTE  pValue, 
                                                  WORD    ValueLen, 
                                                  BOOL    fIsByteswapped,
                                                  LPDWORD lpDword );

extern LPBYTE       WINAPI LookupByteSetString (LPSET lpSet, BYTE Value);

extern LPBYTE       WINAPI LookupWordSetString (LPSET lpSet, WORD Value);

extern LPBYTE       WINAPI LookupDwordSetString (LPSET lpSet, DWORD Value);

extern DWORD        WINAPIV FormatByteFlags(LPSTR string, DWORD ByteValue, DWORD BitMask);

extern DWORD        WINAPIV FormatWordFlags(LPSTR string, DWORD WordValue, DWORD BitMask);

extern DWORD        WINAPIV FormatDwordFlags(LPSTR string, DWORD DwordValue, DWORD BitMask);

extern LPSTR        WINAPIV FormatTimeAsString(SYSTEMTIME *time, LPSTR string);

extern VOID         WINAPIV FormatLabeledByteSetAsFlags(LPPROPERTYINST lpPropertyInst);

extern VOID         WINAPIV FormatLabeledWordSetAsFlags(LPPROPERTYINST lpPropertyInst);

extern VOID         WINAPIV FormatLabeledDwordSetAsFlags(LPPROPERTYINST lpPropertyInst);

extern VOID         WINAPIV FormatPropertyDataAsByte(LPPROPERTYINST lpPropertyInst, DWORD Base);

extern VOID         WINAPIV FormatPropertyDataAsWord(LPPROPERTYINST lpPropertyInst, DWORD Base);

extern VOID         WINAPIV FormatPropertyDataAsDword(LPPROPERTYINST lpPropertyInst, DWORD Base);

extern VOID         WINAPIV FormatLabeledByteSet(LPPROPERTYINST lpPropertyInst);

extern VOID         WINAPIV FormatLabeledWordSet(LPPROPERTYINST lpPropertyInst);

extern VOID         WINAPIV FormatLabeledDwordSet(LPPROPERTYINST lpPropertyInst);

extern VOID         WINAPIV FormatPropertyDataAsInt64(LPPROPERTYINST lpPropertyInst, DWORD Base);

extern VOID         WINAPIV FormatPropertyDataAsTime(LPPROPERTYINST lpPropertyInst);

extern VOID         WINAPIV FormatPropertyDataAsString(LPPROPERTYINST lpPropertyInst);

extern VOID         WINAPIV FormatPropertyDataAsHexString(LPPROPERTYINST lpPropertyInst);


// Parsers should NOT call LockFrame().  If a parser takes a lock and then gets
// faulted or returns without unlocking, it leaves the system in a state where
// it cannot change protocols or cut/copy frames.  Parsers should use ParserTemporaryLockFrame
// which grants a lock ONLY during the context of the api entry into the parser.  The 
// lock is released on exit from the parser for that frame.
extern LPBYTE       WINAPI ParserTemporaryLockFrame(HFRAME hFrame);

extern LPVOID       WINAPI GetCCInstPtr(VOID);
extern VOID         WINAPI SetCCInstPtr(LPVOID lpCurCaptureInst);
extern LPVOID       WINAPI CCHeapAlloc(DWORD dwBytes, BOOL bZeroInit);
extern LPVOID       WINAPI CCHeapReAlloc(LPVOID lpMem, DWORD dwBytes, BOOL bZeroInit);
extern BOOL         WINAPI CCHeapFree(LPVOID lpMem);
extern DWORD        WINAPI CCHeapSize(LPVOID lpMem);

extern BOOL BERGetInteger( LPBYTE  pCurrentPointer,
                           LPBYTE *ppValuePointer,
                           LPDWORD pHeaderLength,
                           LPDWORD pDataLength,
                           LPBYTE *ppNext);
extern BOOL BERGetString( LPBYTE  pCurrentPointer,
                          LPBYTE *ppValuePointer,
                          LPDWORD pHeaderLength,
                          LPDWORD pDataLength,
                          LPBYTE *ppNext);
extern BOOL BERGetHeader( LPBYTE  pCurrentPointer,
                          LPBYTE  pTag,
                          LPDWORD pHeaderLength,
                          LPDWORD pDataLength,
                          LPBYTE *ppNext);
#pragma pack()
#endif
