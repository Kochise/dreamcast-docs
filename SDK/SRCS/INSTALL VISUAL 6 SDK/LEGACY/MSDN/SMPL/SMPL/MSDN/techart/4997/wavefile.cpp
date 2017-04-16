// WaveFile.cpp

#define VC_EXTRALEAN
#define STRICT

#include <windows.h>
#include <mmsystem.h>
#include "assert.h"
#include "debug.h"
#include "WaveFile.h"


// WaveFile class implementation
//
////////////////////////////////////////////////////////////

// Constructor
WaveFile::WaveFile (void)
{
    DOUT ("WaveFile::WaveFile\n\r");

    // Init data members
    m_pwfmt = NULL;
    m_hmmio = NULL;
    m_nBlockAlign= 0;
    m_nAvgDataRate = 0;
    m_nDataSize = 0;
    m_nBytesPlayed = 0;
    m_nDuration = 0;
    memset (&m_mmckiRiff, 0, sizeof (MMCKINFO));
    memset (&m_mmckiFmt, 0, sizeof (MMCKINFO));
    memset (&m_mmckiData, 0, sizeof (MMCKINFO));

}

// Destructor
WaveFile::~WaveFile (void)
{
    DOUT ("WaveFile::~WaveFile\n\r");

    // Free memory
    if (m_pwfmt)
    {
        GlobalFree (m_pwfmt);
    }
    
    // Close file
    if (m_hmmio)
    {
        mmioClose (m_hmmio, 0);
    }

}

// Open
BOOL WaveFile::Open (LPSTR pszFilename)
{
    WORD cbExtra = 0;
    DOUT ("WaveFile::Open\n\r");

    BOOL fRtn = SUCCESS;    // assume success
    
    // Open the requested file
    if ((m_hmmio = mmioOpen (pszFilename, NULL, MMIO_ALLOCBUF | MMIO_READ)) == NULL)
    {
        m_mmr = MMIOERR_CANNOTOPEN;
        goto OPEN_ERROR;
    }
    
    // Descend into initial chunk ('RIFF')
    if (m_mmr = mmioDescend (m_hmmio, &m_mmckiRiff, NULL, 0))
    {
        goto OPEN_ERROR;
    }
    
    // Validate that it's a WAVE file
    if ((m_mmckiRiff.ckid != FOURCC_RIFF) || (m_mmckiRiff.fccType != mmioFOURCC('W', 'A', 'V', 'E')))
    {
        m_mmr = MMIOERR_INVALIDFILE;
        goto OPEN_ERROR;
    }
    
    // Find format chunk ('fmt '), allocate and fill WAVEFORMATEX structure
    m_mmckiFmt.ckid = mmioFOURCC('f', 'm', 't', ' ');
    if (m_mmr = mmioDescend (m_hmmio, &m_mmckiFmt, &m_mmckiRiff, MMIO_FINDCHUNK))
    {
        goto OPEN_ERROR;
    }
    
    // Read the format chunk into temporary structure
    PCMWAVEFORMAT pcmwf;
    if (mmioRead (m_hmmio, (CHAR *) &pcmwf, sizeof(PCMWAVEFORMAT)) != sizeof(PCMWAVEFORMAT))
    {
        m_mmr = MMIOERR_CANNOTREAD;
        goto OPEN_ERROR;
    }

    // If format is not PCM, then there are extra bytes appended to WAVEFORMATEX
    if (pcmwf.wf.wFormatTag != WAVE_FORMAT_PCM)
    {
        // Read WORD specifying number of extra bytes
        if (mmioRead (m_hmmio, (LPSTR) &cbExtra, sizeof (cbExtra)) != sizeof(cbExtra))
        {
            m_mmr = MMIOERR_CANNOTREAD;
            goto OPEN_ERROR;
        }
    }

    // Allocate memory for WAVEFORMATEX structure + extra bytes
    // UNDONE: GMEM_FIXED???? use malloc?
    if (m_pwfmt = (WAVEFORMATEX *) GlobalAlloc (GMEM_FIXED, sizeof(WAVEFORMATEX)+cbExtra))
    {
        // Copy bytes from temporary format structure
        memcpy (m_pwfmt, &pcmwf, sizeof(pcmwf));
        m_pwfmt->cbSize = cbExtra;
        
        // Read those extra bytes, append to WAVEFORMATEX structure
        if (cbExtra != 0)
        {
            if ((m_mmr = mmioRead (m_hmmio, (LPSTR) ((BYTE *)(m_pwfmt) + sizeof (WAVEFORMATEX)), cbExtra)) != cbExtra)
            {
                // Error reading extra bytes
                m_mmr = MMIOERR_CANNOTREAD;
                goto OPEN_ERROR;
            }
        }
    }
    else
    {
        // Error allocating memory
        m_mmr = MMIOERR_OUTOFMEMORY;
        goto OPEN_ERROR;
    }
    
            
    // Init some member data from format chunk
    m_nBlockAlign = m_pwfmt->nBlockAlign;
    m_nAvgDataRate = m_pwfmt->nAvgBytesPerSec;

    // Ascend out of format chunk
    if (m_mmr = mmioAscend (m_hmmio, &m_mmckiFmt, 0))
    {
        goto OPEN_ERROR;
    }

    // Cue for streaming
    Cue ();
    
    // Init some member data from data chunk
    m_nDataSize = m_mmckiData.cksize;
    m_nDuration = (m_nDataSize * 1000) / m_nAvgDataRate;
    
    // Successful open!
    goto OPEN_DONE;
    
OPEN_ERROR:
    // Handle all errors here
    fRtn = FAILURE;
    if (m_hmmio)
    {
        // Close file
        mmioClose (m_hmmio, 0);
        m_hmmio = NULL;
    }
    if (m_pwfmt)
    {
        // UNDONE: Change here if using malloc
        // Free memory
        GlobalFree (m_pwfmt);
        m_pwfmt = NULL;
    }

OPEN_DONE:
    return (fRtn);
}


// Cue
//
BOOL WaveFile::Cue (void)
{
    BOOL fRtn = SUCCESS;    // assume success

    DOUT ("WaveFile::Cue\n\r");

    // Seek to 'data' chunk from beginning of file
    if (mmioSeek (m_hmmio, m_mmckiRiff.dwDataOffset + sizeof(FOURCC), SEEK_SET) != -1)
    {
        // Descend into 'data' chunk
        m_mmckiData.ckid = mmioFOURCC('d', 'a', 't', 'a');
        if ((m_mmr = mmioDescend (m_hmmio, &m_mmckiData, &m_mmckiRiff, MMIO_FINDCHUNK)) == MMSYSERR_NOERROR)
        {
            // Reset byte counter
            m_nBytesPlayed = 0;
        }
        else
        {
            // UNDONE: set m_mmr
            fRtn = FAILURE;
        }
    }
    else
    {
        // mmioSeek error
        m_mmr = MMIOERR_CANNOTSEEK;
        fRtn = FAILURE;
    }


    return fRtn;
}


// Read
//
// Returns number of bytes actually read.
// On error, returns 0, MMIO error code in m_mmr.
//
UINT WaveFile::Read (BYTE * pbDest, UINT cbSize)
{
    MMIOINFO mmioinfo;
    UINT cb;

    DOUT ("WaveFile::Read\n\r");

    // Use direct buffer access for reads to maximize performance
    if (m_mmr = mmioGetInfo (m_hmmio, &mmioinfo, 0))
    {
        goto READ_ERROR;
    }
                
    // Limit read size to chunk size
    cbSize = (cbSize > m_mmckiData.cksize) ? m_mmckiData.cksize : cbSize;

    // Adjust chunk size
    m_mmckiData.cksize -= cbSize;

    // Copy bytes from MMIO buffer
    for (cb = 0; cb < cbSize; cb++)
    {
        // Advance buffer if necessary
        if (mmioinfo.pchNext == mmioinfo.pchEndRead)
        {
            if (m_mmr = mmioAdvance (m_hmmio, &mmioinfo, MMIO_READ))
            {
                goto READ_ERROR;
            }
            
            if (mmioinfo.pchNext == mmioinfo.pchEndRead)
            {
                m_mmr = MMIOERR_CANNOTREAD;
                goto READ_ERROR;
            }
        }
            
        // Actual copy
//      *((BYTE*)pbDest+cb) = *((BYTE*)mmioinfo.pchNext)++;
        *(pbDest+cb) = *(mmioinfo.pchNext)++;
    }

    // End direct buffer access
    if (m_mmr = mmioSetInfo (m_hmmio, &mmioinfo, 0))
    {
        goto READ_ERROR;
    }

    // Successful read, keep running total of number of data bytes read
    m_nBytesPlayed += cbSize;
    goto READ_DONE;
    
READ_ERROR:
    cbSize = 0;

READ_DONE:
    return (cbSize);
}


// GetSilenceData
//
// Returns 8 bits of data representing silence for the Wave file format.
//
// Since we are dealing only with PCM format, we can fudge a bit and take
// advantage of the fact that for all PCM formats, silence can be represented
// by a single byte, repeated to make up the proper word size. The actual size
// of a word of wave data depends on the format:
//
// PCM Format       Word Size       Silence Data
// 8-bit mono       1 byte          0x80
// 8-bit stereo     2 bytes         0x8080
// 16-bit mono      2 bytes         0x0000
// 16-bit stereo    4 bytes         0x00000000
//
BYTE WaveFile::GetSilenceData (void)
{
    BYTE bSilenceData = 0;

    // Silence data depends on format of Wave file
    if (m_pwfmt)
    {
        if (m_pwfmt->wBitsPerSample == 8)
        {
            // For 8-bit formats (unsigned, 0 to 255)
            // Packed DWORD = 0x80808080;
            bSilenceData = 0x80;
        }
        else if (m_pwfmt->wBitsPerSample == 16)
        {
            // For 16-bit formats (signed, -32768 to 32767)
            // Packed DWORD = 0x00000000;
            bSilenceData = 0x00;
        }
        else
        {
            ASSERT (0);
        }
    }
    else
    {
        ASSERT (0);
    }

    return (bSilenceData);
}
