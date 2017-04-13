/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File: midi.cpp
 *
 ***************************************************************************/

// Includes....
#include "windows.h"
#include "midi.h"
#include "stdio.h"

// Externals....
extern HWND	g_hWnd;

//------------------------------------------------------------------
// 
// Function	: PlayMidi()
//
// Purpose	: Plays a midi file
//
//------------------------------------------------------------------

BOOL PlayMidi(char *sFileName)
{
    char buf[256];

    sprintf(buf, "open %s type sequencer alias MUSIC", sFileName);
    
    if (mciSendString("close all", NULL, 0, NULL) != 0)
    {
	return(FALSE);
    }

    if (mciSendString(buf, NULL, 0, NULL) != 0)
    {
	return(FALSE);
    }

    if (mciSendString("play MUSIC from 0", NULL, 0, g_hWnd) != 0)
    {
	return(FALSE);
    }
    
    // Yahoo!
    return TRUE;
}

//------------------------------------------------------------------
// 
// Function	: PauseMidi()
//
// Purpose	: Pauses midi file
//
//------------------------------------------------------------------

BOOL PauseMidi()
{
    // Pause if we're not already paused...
    if (mciSendString("stop MUSIC", NULL, 0, NULL) != 0)
    {
	return(FALSE);
    }

    
    // Yahoo!
    return TRUE;
}

//------------------------------------------------------------------
// 
// Function	: ResumeMidi()
//
// Purpose	: Resumes playing of a midi file
//
//------------------------------------------------------------------

BOOL ResumeMidi()
{	
    // Resume midi
    if (mciSendString("play MUSIC notify", NULL, 0, g_hWnd) != 0)
    {
	return(FALSE);
    }

    // Yahoo!
    return TRUE;
}

//------------------------------------------------------------------
// 
// Function	: StopMidi
//
// Purpose	: Stops a midi file playing
//
//------------------------------------------------------------------

BOOL StopMidi()
{
    if (mciSendString("close all", NULL, 0, NULL) != 0)
    {
	return(FALSE);
    }	

    // Yahoo!
    return TRUE;
}

//------------------------------------------------------------------
// 
// Function	: ReplayMidi()
//
// Purpose	: Replays a midi file
//
//------------------------------------------------------------------

BOOL ReplayMidi()
{
    // Replay midi
    if (mciSendString("play MUSIC from 0 notify", NULL, 0, g_hWnd) != 0)
    {
	return(FALSE);
    }

    // Yahoo!
    return TRUE;
}

