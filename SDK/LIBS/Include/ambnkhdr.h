// ------------------------------------------------------------------------------------------
// ambnkhdr.h
//
// This is the bank header data type, this file is shared between the am library and the 
// bank building tools hence the WIN32 ifdef in the head and tail to resolve structure
// alignment issues.
//
// COPYRIGHT (C) SEGA OF AMERICA, INC. 1998
// All rights reserved.
//
// Author: Ralph "Cooksey" Thomas
//
// Tabs: 4
//
// Rev:		01/05/99	File Originated
//			04/15/99	Added ADPCM token
//
// ------------------------------------------------------------------------------------------

#ifndef AM_BANK_HEADER_H
#define AM_BANK_HEADER_H


// for the tools, these build under MSVC/WIN32
#ifdef WIN32
typedef unsigned long	KTU32;
typedef signed long		KTS32;
typedef char			KTCHAR;
#endif


// tokens written in mkscript and read in mkbank
#define		AM_TONE_BANK_TOKEN			"MidiToneBank"
#define		AM_TONE_BANK_TYPE_TOKEN		"BankType"
#define		AM_MELODIC_TONE_BANK_TOKEN	"Melodic"
#define		AM_DRUM_TONE_BANK_TOKEN		"Drum"
#define		AM_FX_PROGRAM_BANK_TOKEN	"FxProgramBank"
#define		AM_FX_OUTPUT_BANK_TOKEN		"FxOutputBank"
#define		AM_UNKNOWN_FILE_TOKEN		"UserAsset"
#define		AM_MIDI_FILE0_TOKEN			"MidiFileType0"
#define		AM_WAVE_FILE_TOKEN			"WaveFile"
#define		AM_BANK_FILENAME_TOKEN		"BankFileName"
#define		AM_SAMPLE_RATE_TOKEN		"SampleRate"
#define		AM_RANDOM_PITCH_TOKEN		"RandomPitchAmount"
#define		AM_LOOP_TOKEN				"Loop"
#define		AM_VOLUME_TOKEN				"Volume"
#define		AM_GM_MODE_TOKEN			"GmMode"
#define		AM_TYPE_TOKEN				"Type"
#define		AM_PPQN_TOKEN				"TicksPerQuarterNote"
#define		AM_ASSET_END_TOKEN			"AssetEnd"
#define		AM_SCRIPT_END_TOKEN			"ScriptEnd"
#define		AM_ADPCM_COMPRESSION_TOKEN	"Adpcm"
#define		AM_LOOP_START_TOKEN			"LoopStart"
#define		AM_LOOP_END_TOKEN			"LoopEnd"

// filename extensions
#define AM_MIDI_FILE_EXTENSION			".mid"
#define AM_WAVE_FILE_EXTENSION			".wav"
#define AM_AIFF_FILE_EXTENSION			".aif"
#define AM_TONE_BANK_FILE_EXTENSION		".mpb"
#define AM_FX_PROGRAM_FILE_EXTENSION	".fpb"
#define AM_FX_OUTPUT_FILE_EXTENSION		".fob"

typedef enum 
{
AM_UNINITIALIZED			=	0,
AM_WAVE_ASSET				=	1,
AM_MIDI_ASSET				=	2,
AM_MIDI_TONE_BANK_ASSET		=	3,
AM_FX_PROGRAM_BANK_ASSET	=	4,
AM_FX_OUTPUT_BANK_ASSET		=	5,
AM_UNKNOWN_ASSET			=	6
}AM_BANK_ASSET_TYPE;

// asset types R8.2


// ------------------------------------------------------------------------------------------
// storage container for parameter data
// ------------------------------------------------------------------------------------------

typedef struct
{
// the asset type
AM_BANK_ASSET_TYPE	type;			// from enum above.
KTU32			offset;			// offset to first data byte from head of file
KTU32			size;			// size of asset in bytes
}AM_BANK_COMMON;

#define AM_MAX_UNKNOWN_PARAMETERS	8

typedef struct
{
AM_BANK_COMMON	asset;									// common asset parameters
KTS32			parameter[AM_MAX_UNKNOWN_PARAMETERS];	// these are generic parameter containers
}AM_BANK_UNKNOWN;

typedef struct
{
AM_BANK_COMMON	asset;			// common asset parameters
KTU32			sampleRate;		// real world sample rate
KTU32			loop;			// 1,0 true==loop false==not
KTU32			bitDepth;		// 4,8,16 bits 
KTU32			random;			// 0-100%, random pitch shift
KTU32			loopStart;		// the loop start point in frames
KTU32			loopEnd;		// the loop end point in frames
KTCHAR			pad[8];			// unused
}AM_BANK_WAVE;

typedef struct
{
AM_BANK_COMMON	asset;			// common asset parameters
KTU32			ppqn;			// ticks per quarter note
KTU32			volume;			// midi MASTER volume, 0-127
KTU32			gmMode;			// GM on or off 1=on 0=off
KTU32			loop;			// 1 if the sequence is to loop, 0 if not
KTU32			bpm;			// the tempo in BPM
KTU32			uspqn;			// microseconds per quarter note
KTCHAR			pad[8];
}AM_BANK_MIDI;

typedef struct
{
AM_BANK_COMMON	asset;			// common asset parameters
KTU32			isMelodic;		// true if it is a melodic bank, else its a drum bank
KTCHAR			pad[28];			
}AM_BANK_MTB;

typedef struct
{
AM_BANK_COMMON	asset;			// common asset parameters
KTCHAR			pad[32];			
}AM_BANK_FOB;

typedef struct
{
AM_BANK_COMMON	asset;			// common asset parameters
KTCHAR			pad[32];			
}AM_BANK_FPB;

typedef union
{
AM_BANK_UNKNOWN		unknown;	// unknown data types
AM_BANK_WAVE		wave;		// .wav file data type
AM_BANK_MIDI		midi;		// .mid file data type
AM_BANK_MTB			mtb;		// .mtb file data type
AM_BANK_FOB			fob;		// .fob file data type
AM_BANK_FPB			fpb;		// .fpb file data type
}AM_BANK_FILE_UNION;

typedef AM_BANK_FILE_UNION * AM_BANK_FILE_UNION_PTR;

#endif // end of #ifndef AM_BANK_HEADER_H

// -------------------------------------------------------------------------------------------
// end of file: ambnkhdr.h
// -------------------------------------------------------------------------------------------
