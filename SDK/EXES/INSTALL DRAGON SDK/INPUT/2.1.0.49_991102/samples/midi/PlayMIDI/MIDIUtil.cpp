/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    MIDIUtil.cpp

Abstract:

   Utility functions for MIDI

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "PlayMIDI.hpp"

// DWORDs corresponding to the 4-character data tags for the chunks
#define MTHD  0x6468544D // Start of file
#define MTRK  0x6B72544D // Start of track

// Chunk header. dwTag is either MTrk or MThd.
typedef struct
{
    DWORD   dwTag;            // Type of chunk
    DWORD   dwChunkLength;    // Length of chunk (MSB first)
} MIDICHUNK;

// Contents of MThd chunk.
typedef struct
{
    WORD    wFormat;        // Format (MSB first)
    WORD    wTrackCount;    // Number of tracks (MSB first)
    WORD    wTimeDivision;  // Time division (MSB first)
} MIDIFILEHDR;

// Macros for swapping big/little-endian data
#define WORDSWAP(w)   (((w) >> 8) | (((w) << 8) & 0xFF00))
#define DWORDSWAP(dw) (((dw) >> 24)               | (((dw) >>  8) & 0x0000FF00) | \
                      (((dw) <<  8) & 0x00FF0000) | (((dw) << 24) & 0xFF000000))

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    AllocAligned

Description:

    This function allocates a block of memory, ensuring that the pointer
    returned is aligned on an aligned boundary.  This is useful for
    allocating memory which might need to be transferred via DMA, which
    requires all data transfers to be in multiples of 32 bytes, on 32-byte
    aligned boundaries.

Arguments:

    DWORD cb       --  Buffer size requested in bytes

    DWORD cbAlign  --  Byte boundary required

Return Value:

    A pointer to the allocated block of memory

-------------------------------------------------------------------*/
BYTE*
AllocAligned(DWORD cb, DWORD cbAlign)
{
    DWORD cbAlloc;
    BYTE *pbyAlloc, *pbyRet;

    // The actual block needs to be large enough to allow for saving the original pointer
    // of the block, as well as any extra space that might be needed to start the actual
    // space used by the caller on an aligned boundary
    cbAlloc = cb + sizeof(BYTE *) + cbAlign - 1;

    /* Allocate the block */
    pbyAlloc = (BYTE *)LocalAlloc(LPTR, cbAlloc);
    if (pbyAlloc == NULL)
        return NULL;

    // Calculate a pointer that's between 0 and 31 bytes past an aligned address within the
    // block of memory, and also far enough ahead to allow us to save the original pointer
    pbyRet = pbyAlloc + sizeof(BYTE *) + cbAlign - 1;

    // Truncate that pointer back to the aligned address within the block of memory
    pbyRet = (BYTE *)((DWORD)pbyRet & ~(cbAlign - 1));

    // Save the original pointer in the memory just ahead of the pointer returned to the caller
    *(((BYTE **)pbyRet) - 1) = pbyAlloc;

    return pbyRet;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    FreeAligned

Description:

    Frees a pointer that was allocated using AllocAligned

Arguments:

    BYTE *pbData  --  The block of memory to free

Return Value:

    None

-------------------------------------------------------------------*/
void
FreeAligned(BYTE *pbyData)
{
    BYTE *pbyAlloc;

    // Get the original address of the allocated block
    pbyAlloc = *(((BYTE **)pbyData) - 1);

    LocalFree(pbyAlloc);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GetDataResource

Description:

    Given a resource name, return a pointer to the resource data.

    NOTE: we don't bother to remember the handle to the resource here.  This is
    because these resources will reside in the EXE, and are already loaded into
    memory with the EXE.  Freeing the resource would do no good as the data
    would still remain in memory, so don't we don't bother to worry about the
    handle, or freeing it later.

Arguments:

    TCHAR *psz      --  The name of the resource

    DWORD *pcbData  --  Pointer to a variable to take the length of the data

Return Value:

    A pointer to the data itself

-------------------------------------------------------------------*/
BYTE*
GetDataResource(TCHAR *psz, DWORD *pcbData)
{
    HRSRC   hrsrc;
    HGLOBAL hglobal;
    BYTE    *pbRet = NULL;

    // This series of statements is simply the standard Windows sequence for obtaining a 
    // pointer to a memory block that contains the data found in a resource included in the EXE
    hrsrc = FindResource(g_hinstApp, psz, RT_RCDATA);
    if (hrsrc == NULL)
        return NULL;

    *pcbData = SizeofResource(g_hinstApp, hrsrc);
    if (*pcbData == 0)
        return NULL;

    hglobal = LoadResource(g_hinstApp, hrsrc);
    if (hglobal == NULL)
        return NULL;

    return (BYTE*)LockResource(hglobal);
}

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GetDataFile

Description:

    Given a filename, opens and reads the data in the file into a single
    memory block.

Arguments:

    TCHAR *psz      --  The name of the file
    
    DWORD *pcbData  --  Pointer to variable to take file length in bytes

Return Value:

    A pointer to the data itself.

-------------------------------------------------------------------*/
BYTE *
GetDataFile(TCHAR *psz, DWORD *pcbData)
{
    HANDLE hFile = NULL;
    BOOL   fSuccess = FALSE;
    DWORD  cbFile, cbRead;
    BYTE   *pbRet = NULL;

    // Open the file
    hFile = CreateFile(psz, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        RetailOutput(TEXT("Error: can't open data file \"%s\"\r\n"), psz);
        goto Fail;
    }

    // Find out how long it is, in bytes
    cbFile = GetFileSize(hFile, NULL);
    if (cbFile == 0xffffffff)
    {
        RetailOutput(TEXT("Error: error getting file size\r\n"));
        goto Fail;
    }

    // Allocate a memory block to keep the file data
    pbRet = (BYTE*)LocalAlloc(LPTR, cbFile);
    if (pbRet == NULL)
    {
        RetailOutput(TEXT("Error: failed to allocate %d bytes for file data\r\n"), cbFile);
    }

    // Read the data from the file
    ReadFile(hFile, pbRet, cbFile, &cbRead, NULL);
    if (cbRead != cbFile)
    {
        RetailOutput(TEXT("Error: read %d bytes, expected %d bytes\r\n"), cbRead, cbFile);
    }

    // Store the file size and finish up
    *pcbData = cbRead;
    fSuccess = TRUE;

Fail:

    if (!fSuccess && pbRet != NULL)
    {
        LocalFree(pbRet);
        pbRet = NULL;
    }

    if (hFile != INVALID_HANDLE_VALUE)
        CloseHandle(hFile);
    return pbRet;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    LoadSequence

Description:

    Given a pointer to a memory block that contains an SMF format file,
    initializes a MIDIHDR structure with the first track found in the file,
    and also returns the time division.

Arguments:

    TCHAR   *tszName -- Name of the sequence to load
    
    MIDIHDR *pmh     --  The MIDIHDR structure to initialize

    WORD    *ptd     --  Variable to copy the time division into

Return Value:

    TRUE on success, FALSE otherwise

-------------------------------------------------------------------*/
BOOL
LoadSequence(TCHAR *tszName, MIDIHDR *pmh, WORD *ptd)
{
    BOOL        fRet = FALSE;
    MIDICHUNK   mthd;
    MIDICHUNK   mtrk;
    MIDIFILEHDR mfh;
    BYTE        *pbSequence = NULL;
    BYTE        *pbSequenceOrig = NULL;
    BYTE        *pbData;
    DWORD       cbSequence;

    // Get pointer to MIDI sequence
    pbSequence = GetDataFile(tszName, &cbSequence);
    if (pbSequence == NULL)
        return FALSE;

	pbSequenceOrig = pbSequence;

    // Read first chunk description; should be for the header
    if (cbSequence < sizeof(mthd))
        goto Fail;
    
    memcpy(&mthd, pbSequence, sizeof(mthd));

    if (mthd.dwTag != MTHD)
        goto Fail;

    pbSequence += sizeof(mthd);
    cbSequence -= sizeof(mthd);

    // Read the rest of the header data.  NOTE: we must have at least sizeof(mfh)
    // bytes, but there may be more; only read what can fit into our data structure
    mthd.dwChunkLength = DWORDSWAP(mthd.dwChunkLength);
    if (mthd.dwChunkLength < sizeof(mfh))
        goto Fail;

    if (cbSequence < sizeof(mfh))
        goto Fail;

    memcpy(&mfh, pbSequence, sizeof(mfh));
    pbSequence += mthd.dwChunkLength;
    cbSequence -= mthd.dwChunkLength;

    // SMF format specifies big-endian, but Dreamcast is little-endian
    mfh.wFormat       = WORDSWAP(mfh.wFormat);
    mfh.wTrackCount   = WORDSWAP(mfh.wTrackCount);
    mfh.wTimeDivision = WORDSWAP(mfh.wTimeDivision);

    // Get first track (fail multi-track formats)
    // NOTE: handling Format 1 SMF with more than one track wouldn't be *that* hard.
    // But it would involve parsing the SMF data, and merging all of the tracks into a
    // single track to be sent to a single MIDI port, or just loading each track separately,
    // and playing each into one of the 16 MIDI ports available on Dreamcast.  

    // Format 1 isn't really a problem as long as there's still just one track
    if (mfh.wFormat != 0 && mfh.wTrackCount > 1)
    {
        RetailOutput(TEXT("Error: This sample cannot play Format-1 MIDI files with more \r\n"));
        RetailOutput(TEXT("than one track.  Please use the \"format1\" sample to play this\r\n"));
        RetailOutput(TEXT("MIDI file.\r\n"));
        goto Fail;
    }

    if (cbSequence < sizeof(mthd))
        goto Fail;

    memcpy(&mtrk, pbSequence, sizeof(mthd));
    pbSequence += sizeof(mthd);
    cbSequence -= sizeof(mthd);

    // Verify track header
    if (mtrk.dwTag != MTRK)
        goto Fail;

    mtrk.dwChunkLength = DWORDSWAP(mtrk.dwChunkLength);
    if (cbSequence < mtrk.dwChunkLength)
        goto Fail;

    pbData = AllocAligned(cbSequence, 32);
    if (pbData == NULL)
        goto Fail;
    memcpy (pbData, pbSequence, cbSequence);

    // If track chunk header checks out, set up MIDIHDR
    pmh->dwBufferLength = mtrk.dwChunkLength;
    pmh->lpData = (char*)pbData;
    *ptd = mfh.wTimeDivision;

    fRet = TRUE;

Fail:

    if (pbSequenceOrig != NULL)
        LocalFree(pbSequenceOrig);

    return fRet;
}

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    FreeSequence

Description:

    Helper function so that caller of LoadSequence doesn't need to actually
    know how the sequence data was allocated in memory
Arguments:

    BYTE *pbSequence -- The sequence to free

Return Value:

    None

-------------------------------------------------------------------*/
void
FreeSequence(BYTE *pbSequence)
{
    // Could also unload DLL data here if we'd loaded sequence that way
    FreeAligned(pbSequence);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    LoadTonebank

Description:

    Loads the tonebank resource and initializes a MIDIHDR structure to point to
    the tonebank data.  Since the tonebank data is just raw data to be copied
    directly to the sound RAM, this is a lot simpler than loading a MIDI sequence.

Arguments:

    TCHAR   *tszName -- Name of the sequence to load
   
    MIDIHDR *pmh  --  The MIDIHDR structure to initialize

Return Value:

    TRUE on success, FALSE otherwise

-------------------------------------------------------------------*/
BOOL
LoadTonebank(TCHAR *tszName, MIDIHDR *pmh)
{
    BYTE *pbTonebank;
    DWORD cbTonebank;

    // Get the data
    pbTonebank = GetDataResource(tszName, &cbTonebank);
    if (pbTonebank == NULL)
        return FALSE;

    // Initialize the MIDIHDR
    pmh->lpData = (char*)pbTonebank;
    pmh->dwBufferLength = cbTonebank;

    return TRUE;
}
