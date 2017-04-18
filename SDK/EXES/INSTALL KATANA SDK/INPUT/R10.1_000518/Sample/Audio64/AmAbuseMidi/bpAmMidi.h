// ------------------------------------------------------------------------------------------------
// MyMidi.h
//
// This is the header for MyMidi.c
//
// COPYRIGHT (C) SEGA OF AMERICA, INC. 1998
// All rights reserved.
//
// Information and source code samples contained herein are 
// provided "as-is", without representations or warranties, and 
// are subject to change without notice.
//
// SEGA OF AMERICA, INC. cannot support modifications or 
// derivative works created from the sample source code provided. 
// Developers may use, reproduce, and modify portions or entire 
// sections of the sample source code for the purposes of creating
// Dreamcast applications.  
//
// Sample source code contained herein may not be appropriate 
// for use under all circumstances.  Please consult Developer 
// documentation provided along with your Dreamcast unit for
// additional information and suggestions.
//
//
// Author: Ralph "Cooksey" Thomas
//
// Tabs: 4
//
// Rev:			05/27/99	File Originated
// ------------------------------------------------------------------------------------------------

#ifndef _MYSTREAM_H
#define _MYSTREAM_H

#ifdef __cplusplus
extern "C" {
#endif

KTBOOL MyMidiPlay(AM_BANK_PTR theBank,AM_SEQUENCE *theSequence,KTU32 theAssetNumber,AM_MIDI_CALLBACK theCallback);
KTBOOL MyMidiStop(AM_SEQUENCE *theSequence);

#ifdef __cplusplus
}
#endif

#endif
