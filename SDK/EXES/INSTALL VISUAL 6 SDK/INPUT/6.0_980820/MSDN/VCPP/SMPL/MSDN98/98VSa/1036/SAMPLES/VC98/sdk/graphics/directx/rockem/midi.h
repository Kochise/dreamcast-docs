/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File: midi.h
 *
 ***************************************************************************/

#ifndef __MIDI_H
#define __MIDI_H

BOOL PlayMidi(char *sFileName);
BOOL PauseMidi();
BOOL ResumeMidi();
BOOL StopMidi();
BOOL ReplayMidi();

#endif

