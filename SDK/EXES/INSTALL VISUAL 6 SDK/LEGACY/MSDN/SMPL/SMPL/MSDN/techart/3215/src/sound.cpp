// sound.cpp : implementation file
// @doc

#include "stdafx.h"
#include "animate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSound

IMPLEMENT_SERIAL(CSound, CObject, 0 /* schema number*/ )

CSound::CSound()
{
    m_pSoundImage = NULL;
}

CSound::~CSound()
{
}


/////////////////////////////////////////////////////////////////////////////
// CSound serialization

void CSound::Serialize(CArchive& ar)
{
    ASSERT(0); // not supported
}

/////////////////////////////////////////////////////////////////////////////
// CSound commands

/*
@mfunc BOOL | CSound | Load | Load a wavform sound from a resource.
@syntax BOOL Load(WORD wResid);
@parm WORD | wResid | The resource ID of the sound to load.
@rdesc The return value is TRUE if the sound is loaded, FALSE if not.
@comm The resource must be added to the resource script as type WAVE.
@xref <c CSound> <mf CSound::Play> <mf CSound::PlaySync>
*/

BOOL CSound::Load(WORD wResid)
{
    ASSERT(wResid);
    HINSTANCE hInst = AfxGetResourceHandle();
    HRSRC hrsrc = ::FindResource(hInst,
                                 MAKEINTRESOURCE(wResid), 
                                 "WAVE");
    if (!hrsrc) {
        TRACE("WAVE resource not found");
        return FALSE;
    }
    HGLOBAL hg = LoadResource(hInst, hrsrc);
    if (!hg) {
        TRACE("Failed to load WAVE resource");
        return FALSE;
    }
    m_pSoundImage = (BYTE*) LockResource(hg);
    ASSERT(m_pSoundImage);
    return TRUE;
}

/*
@mfunc void | CSound | Play | Play the sound asynchronously.
@syntax void Play();
@rdesc There is no return value.
@comm The sound must first have been loaded with <mf CSound::Load>. The
sound is played using the ::sndPlaySound function.
@xref <c CSound> <mf CSound::PlaySync>
*/

void CSound::Play()
{
    if (!m_pSoundImage) {
        TRACE("Nothing to play");
        return;
    }
    ::sndPlaySound((LPCSTR) m_pSoundImage,
                   SND_MEMORY | SND_ASYNC | SND_NODEFAULT);
}

/*
@mfunc void | CSound | PlaySync | Play the sound synchronously.
@syntax void PlaySync();
@rdesc There is no return value.
@comm The sound must first have been loaded with <mf CSound::Load>. The
sound is played using the ::sndPlaySound function.
@xref <c CSound> <mf CSound::Play>
*/

void CSound::PlaySync()
{
    if (!m_pSoundImage) {
        TRACE("Nothing to play");
        return;
    }
    ::sndPlaySound((LPCSTR) m_pSoundImage,
                   SND_MEMORY | SND_SYNC | SND_NODEFAULT);
}

