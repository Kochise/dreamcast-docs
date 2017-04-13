#include "fdfilter.h"
#include "filter.h"

CGargle::CGargle( int nFreq, int nChannels, int nBytesPerSample )
    {
    m_nPhase = 0;
    m_Shape = SHAPE_TRIANGLE;
    m_nGargleRate = 10;
    m_nBytesPerSample = nBytesPerSample;
    m_nSamplesPerSec = nFreq;
    m_nChannels = nChannels;
    }


//Below resutls in cl error C2600 - the compiler
//has already generated a default destructor due
//to the abstract delcaration of the CGargle class
//in FDFILTER.H
//CGargle::~CGargle()
//    {
//    }


// Copy the required information about the new format for the buffer
HRESULT CGargle::SetFormat( PWAVEFORMATEX pwfx )
    {
    if( NULL == pwfx )
        return ResultFromScode( E_POINTER );

    m_nSamplesPerSec = pwfx->nSamplesPerSec;
    m_nChannels = pwfx->nChannels;
    m_nBytesPerSample = pwfx->wBitsPerSample / 8;

    return NOERROR;    
    }


//
// MessItAbout
//
// Mess the sound about by modulating it with a waveform.
// We know the frequency of the modulation (from the slider setting
// which we were told through our internal interface, IGargle, and
// which we stored in m_GargleRate).  At the end of the call we
// record what part of the waveform we finished at in m_Phase and
// we resume at that point next time.
// Uses and updates m_Phase
// Uses m_SamplesPerSec, m_Channels, m_GargleRate, m_Shape
//
void CGargle::MessItAbout( PBYTE pbIn, DWORD cb, PBYTE pbOut )
{
    // We know how many samples per sec and how
    // many channels so we can calculate the modulation period in samples.
    //

    int Period = (m_nSamplesPerSec * m_nChannels) / m_nGargleRate;

    while( cb > 0 ) {
        --cb;

        // If m_Shape is 0 (triangle) then we multiply by a triangular waveform
        // that runs 0..Period/2..0..Period/2..0... else by a square one that
        // is either 0 or Period/2 (same maximum as the triangle) or zero.
        //
        {
            // m_Phase is the number of samples from the start of the period.
            // We keep this running from one call to the next,
            // but if the period changes so as to make this more
            // than Period then we reset to 0 with a bang.  This may cause
            // an audible click or pop (but, hey! it's only a sample!)
            //
            ++m_nPhase;
            if( m_nPhase > Period )
                m_nPhase = 0;

            int M = m_nPhase;      // m is what we modulate with

            if( m_Shape == SHAPE_TRIANGLE ) {   // Triangle
                if( M > Period / 2 )
                    M = Period - M;  // handle downslope
            } else if( m_Shape == SHAPE_TRIANGLE ) {             // Square wave
                if( M <= Period / 2 )
                    M = Period / 2;
                else M = 0;
            }

            if( m_nBytesPerSample == 1 ) {
                // 8 bit sound uses 0..255 representing -128..127
                // Any overflow, even by 1, would sound very bad.
                // so we clip paranoically after modulating.
                // I think it should never clip by more than 1
                //
                int i = *pbIn - 128;            // sound sample, zero based
                i = (i * M * 2) / Period;       // modulate
                if(i > 127)                     // clip
                    i = 127;
                if(i < -128)
                    i = -128;

               *pbOut = (unsigned char)(i + 128);       // reset zero offset to 128

            } else if( m_nBytesPerSample == 2 ) {
                // 16 bit sound uses 16 bits properly (0 means 0)
                // We still clip paranoically
                //
                short int *psi = (short int *)pbOut;
                int i = *((short int *)pbIn);   // in a register, we might hope
                i = (i*M*2)/Period;     // modulate
                if(i > 32767)
                    i = 32767;          // clip
                if(i < -32768)
                    i = -32768;
                *psi = (short)i;
                ++pbIn; // nudge it on another 8 bits here to get a 16 bit step
                ++pbOut;
                --cb;   // and nudge the count too.
            } else {
//               DbgBreak("Too many bytes per sample");
               // just leave it alone!
            }
        }
        ++pbIn;   // move on 8 bits to next sound sample
        ++pbOut;
    }
} // MessItAbout


//
// Transform
//
//
HRESULT CGargle::Transform( PBYTE pbIn, int cbWrite, PBYTE pbOut )
{
    // Actually transform the data
    //
    if( m_nSamplesPerSec && m_nChannels && m_nBytesPerSample )
        MessItAbout( pbIn, cbWrite, pbOut );

    return NOERROR;

} // Transform
