//-----------------------------------------------------------------------------
//
//	FILE:		am.h
//
//	DESC:		Declarations and definitions for the Audio64 AM layer.
//
//	HISTORY:	2000.02.xx	Reworked samples/boilerplates for R10 release.
//
//-----------------------------------------------------------------------------
//
// COPYRIGHT (C) SEGA OF AMERICA DREAMCAST, INC. 1998, 1999, 2000
// All rights reserved.
//
// Information and source code samples contained herein are  provided "as-is",
// without representations or warranties, and are subject to change without
// notice.
//
// SEGA OF AMERICA DREAMCAST, INC. cannot support modifications or derivative
// works created from the sample source code provided. Developers may use,
// reproduce, and modify portions or entire sections of the sample source code
// for the purposes of creating Dreamcast applications.  
//
// Sample source code contained herein may not be appropriate for use under
// all circumstances. Please consult Developer documentation provided along
// with your Dreamcast unit for additional information and suggestions.
//
//-----------------------------------------------------------------------------

#if !defined(_AM_H_)
#define _AM_H_

#include <ac.h>
#include <ambnkhdr.h>	// the bank header declaration
#include <amstrhdr.h>	// the stream header declaration

#ifdef __cplusplus
extern "C" {
#endif

// ----------------------------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------------------------

#define AM_FILE_BLOCK_SIZE					2048
#define AM_FILE_BOUNDRY_ALIGNMENT			32		// aligned on 32 byte boundries

#define AM_HEAP_BOUNDRY_ALIGNMENT			32
#define AM_HEAP_SIZE_IN_BYTES				(1024 * 1024 * 2)
#define AM_HEAP_SIZE_IN_DWORDS				(AM_HEAP_SIZE_IN_BYTES/4)
#define AM_HEAP_MAX_MASTER_POINTERS			100
#define AM_HEAP_FINGERPRINT_LENGTH			4
#define AM_HEAP_ALIGNMENT					4

#define AM_MIDI_EOT_OFFSET					6
#define AM_MIDI_LOOP_OFFSET					10
// this will go when the driver is updated to parse the header of the smf
#define AM_MIDI_MTRK_OFFSET					22	

#define AM_MAX_VOLUME						127
#define AM_MIN_VOLUME						0

#define AM_PAN_RIGHT						AC_PAN_RIGHT
#define AM_PAN_CENTER						(((AC_PAN_CENTER + 1) << 2) - 1)
#define AM_PAN_LEFT							(((AC_PAN_LEFT + 1) << 2) - 1)
#define AM_MAX_PAN							(((AC_MAX_PAN + 1) << 2) - 1)

// dsp ranges
#define AM_MAX_DSP_MIXER_CHANNELS			15
#define AM_MAX_Q_CHANNELS					16
#define AM_MAX_DSP_SOURCE_MIX				100

#define AM_UNINITIALIZED_VOICE_CHANNEL		0x666
#define AM_UNINITIALIZED_FILE_DESCRIPTOR	((KTU32)-1)

#define AM_ISR_RETRY_COUNT					100
#define AM_ISR_RETRY_DELAY					3000

#define USELINEAR							KTTRUE
#define USELOG								KTFALSE

//-----------------------------------------------------------------------------
// abstract types
//-----------------------------------------------------------------------------

typedef volatile KTU32 *AM_BANK_PTR;

//-----------------------------------------------------------------------------
// proc pointer types
//-----------------------------------------------------------------------------

typedef void (*AM_MEMORY_CALLBACK)(KTU32 *blockAddress);

typedef void (*AM_USER_CALLBACK)(KTU32);
typedef void (*AM_SYSTEM_CALLBACK)(KTU32);

typedef void (*AM_MIDI_CALLBACK)(KTU32);

typedef void (*AM_STREAM_ISR)(KTU32);

//-----------------------------------------------------------------------------
// enum types
//-----------------------------------------------------------------------------

typedef enum
{
	AM_MONO = 1,
	AM_STEREO
} AM_TRACK_TYPE;

typedef enum
{
	AM_UNINITIALIZED_MEMORY_TYPE, 
	AM_FIXED_MEMORY,
	AM_PURGABLE_MEMORY,
	AM_ALL_MEMORY
} AM_HEAP_MEMORY_TYPE;

typedef enum
{
	AMS_IDLE,
	AMS_WARMINGUP,
	AMS_PLAYING,
	AMS_DONE
} AM_STREAM_MODE;

typedef enum
{
	AMS_NO_OPERATION,
	AMS_INIT,						// init the object
	AMS_OPEN,						// open the stream file
	AMS_OPEN_CHECK,
	AMS_HEADER_READ,				// reading in the header buffer (pending/complete),
	AMS_HEADER_READ_CHECK,
	AMS_PREPARE,					// set up the stream object with the header information
	AMS_ALLOC_VOICES,				// allocate the necessary voice channels
	AMS_TBUFF_REFRESH,				// refresh the transfer buffer (pending/complete)
	AMS_TBUFF_REFRESH_CHECK,
	AMS_PRIME_PBUFFERS,				// prime the play buffers
	AMS_START,						// open and start the voice channel(s)
	AMS_PLAY,						// play the stream
	AMS_END
} AM_STREAM_OPERATION;

typedef enum
{
	AMS_FILL_BACK,					// fill the back halfs of the play buffers
	AMS_FILL_FRONT					// fill the front halfs of the play buffers
} AMS_PLAY_BUFFER_OPERATION;
  
typedef enum
{
	AM_NO_ERROR						=	0,		// all is well
	// memory allocation 1-100
	
	// bad parameters 101-200
	AM_NULL_PARAMETER				=	101,	// a pointer parameter is NULL
	AM_OUT_OF_RANGE_PARAMETER		=	102,	// a parameter is out of range
	AM_0_SIZE_PARAMETER				=	103,	// the parameter size is 0
	AM_0_ALIGNMENT_PARAMETER		=	104, 	// can't have memory alignment of 0
	AM_0_CHANNELS_PARAMETER			=	105,
	// file system 201-300
	AM_SEEK_FAIL					=	201,
	AM_READ_FAIL					=	202,
	AM_GET_SIZE_FAIL				=	203,
	AM_CLOSE_FAIL					=	204,
	AM_FILE_NOT_FOUND				=	205,
	AM_LOAD_FAIL					=	206,
	AM_REWIND_FAIL					=	207,
	AM_OPEN_FAIL					=	208,
	// driver 301-400
	AM_CANT_SEND_DRIVER_COMMAND		=	301,
	AM_DRIVER_NOT_INSTALLED			=	302,
	AM_UNABLE_TO_INSTALL_DRIVER		=	303,
	AM_DRIVER_IS_INSTALLED			=	304,
	AM_UNABLE_TO_INIT_AC_SYSTEM		=	305,
	AM_RETRY_ISR_EVENT_WARN			=	306,
	AM_CANT_SET_STREAM_CALLBACK		=	307,
	// warns 401-500
	AM_OUT_OF_RANGE_PARAMETER_FIXED	=	401,	// an out of range parameter was "fixed" see the docs for the behavior of that specific function
	// memory 501-600
	AM_NON_32_BYTE_ALIGNED_ADDRESS	=	501,
	AM_NON_DWORD_ALIGNED_ADDRESS	=	502,
	AM_AUDIO_HEAP_NOT_INITIALIZED	=	503,
	AM_UNSUPPORTED_MEMORY_TYPE		=	504,
	AM_INSUFFICIENT_PURGABLE_MEMORY	=	505,
	AM_CAN_ONLY_FREE_TOP_BLOCK		=	506,
	AM_INVALID_BLOCK_HANDLE			=	507,
	AM_INSUFFICIENT_MEMORY			=	508,
	AM_OUT_OF_MEMORY_CONTROL_BLOCKS	=	509,
	AM_HEAP_IS_ALREADY_INITIALIZED	=	510,
	AM_HEAP_IS_CORRUPT				=	511,
	AM_IMPROPER_ADDRESS_ALIGNMENT	=	512,
	AM_IMPROPER_SIZE_ALIGNMENT		=	513,
	AM_INVALID_DMA_CHANNEL			=	514,
	AM_BUFFER_IS_NOT_IN_AICA_MEMORY	=	516,
	AM_CANT_LOAD_INTO_AICA_MEMORY	=	517,
	
	// bank 601-700
	AM_ASSET_INDEX_NOT_PRESENT		=	601,
	AM_NOT_A_MIDI_ASSET				=	602,
	AM_NOT_A_WAVE_ASSET				=	603,
	AM_NOT_AN_UNKKNOWN_ASSET		=	604,
	// voice pool 701-800
	AM_NO_VOICES_AVAILABLE			=	701,
	AM_UNSUPPORTED_VOICE_TYPE		=	702,
	AM_VOICE_CHANNEL_UNINITIALIZED	=	703,
	// system 801-900
	AM_INTERNAL_ERROR				=	801,	// this should never happen
	AM_UNSUPPORTED_AICA_AUDIO_TYPE	=	802,
	AM_UNSUPPORTED_AICA_SAMPLE_RATE	=	803,	// the aica rates are even rates 44100,22050,11025 etc, see ac.h
	AM_UNSUPPORTED_BIT_DEPTH		=	804,
	AM_FAILED_TO_CHAIN_INT_HANDLER	=	805,	// failed to add the interrupt handler to the chain
	// midi 901-1000
	AM_TONE_BANK_SLOT_OUT_OF_RANGE	=	901,
	AM_MIDI_PORT_OUT_OF_RANGE		=	902,
	AM_MIDI_CHANNEL_OUT_OF_RANGE	=	903,
	AM_MIDI_PROGRAM_OUT_OF_RANGE	=	904,
	AM_MIDI_NOTE_OUT_OF_RANGE		=	905,
	AM_MIDI_VELOCITY_OUT_OF_RANGE	=	906,
	// digital audio 1001-1100
	AM_UNSUPPORTED_SAMPLE_RATE		=	1001,	// a sample rate exceeding 1128900 was requested
	AM_SOUND_IS_NOT_PLAYING			=	1002,
	AM_SOUND_IS_PLAYING				=	1003,
	// stream 1101-1200
	AM_CORRUPT_STREAM_OBJECT		=	1101,	// most of the time this means that a track has more then 2 channels, this is not supported so the data must be corrupt	
	AM_STREAM_NOT_OPEN				=	1102,
	AM_STREAM_BUFFER_NOT_MULTIPLE_OF_2048	=	1103,
	AM_TRACK_NUMBER_OUT_OF_RANGE	=	1104,
	AM_STREAM_IS_NOT_PLAYING		=	1105,
	AM_CANT_SET_PAN_ON_STEREO_STREAM	=	1106,
	AM_STREAM_IS_DONE				=	1107,
	AM_STREAM_IS_NOT_INITIALIZED	=	1108,
	AM_WRONG_INTERLEAVE_RATE		=	1109,	// the interleave rate that the stream was built with does not match up with the play buffer size, adjust one or the other...
	AM_DMA_TRANSFER_NOT_IMPLEMENTED_YET	=	1110,
	AM_STREAM_IS_OPEN				=	1111,
	AM_FILENAME_TOO_LONG			=	1112,
	AM_STREAM_SEEK_FAIL				=	1113,
	AM_STREAM_READ_FAIL				=	1114,
	AM_STREAM_GET_SIZE_FAIL			=	1115,
	AM_STREAM_CLOSE_FAIL			=	1116,
	AM_STREAM_FILE_NOT_FOUND		=	1117,
	AM_STREAM_REWIND_FAIL			=	1118,
	AM_STREAM_OPEN_FAIL				=	1119,
	AM_STREAM_TRANSFER_BUFFER_OVERRUN	=	1120,
	// sound effects (amSound)
	AM_SOUND_STRUCT_NOT_INITIALIZED	=	1201,
	AM_SOUND_IS_PLAYING_ERROR		=	1202,
	AM_LAST_ERROR					=	5000
} AM_ERROR_TYPE;

#define AM_ERROR_MESSAGE_LENGTH	255
typedef struct 
{
	KTCHAR message[AM_ERROR_MESSAGE_LENGTH + 1];
	AM_ERROR_TYPE number;
} AM_ERROR;

// ----------------------------------------------------------------------------------------------
// aggregates
// ----------------------------------------------------------------------------------------------

typedef enum
{
	AM_UNINITIALIZED_VOICE,
	AM_ONESHOT_VOICE,
	AM_MIDI_VOICE,
	AM_STREAM_VOICE
} AM_VOICE_TYPE;

typedef struct
{
	AM_SYSTEM_CALLBACK systemCallback;
	AM_USER_CALLBACK userCallback[AC_TOTAL_VOICES];
	AM_STREAM_ISR streamIsr[AC_TOTAL_VOICES];
	KTBOOL channels[AC_TOTAL_VOICES];
	AM_VOICE_TYPE channelType[AC_TOTAL_VOICES];
	void *channelOwner[AC_TOTAL_VOICES];
} AM_VOICE_POOL;

typedef struct 
{
	KTU32 *address;						// aligned address of the block
	KTU32 *fingerprintAddress;			// address of the fingerprint "RCTT"
	KTU32 size;							// size of the block + overhead
	KTBOOL allocated;					// KTTRUE if block is allocated
	AM_MEMORY_CALLBACK callback;		// address of callback function
} AM_MCB_STRUCT;

typedef struct
{
	KTBOOL open;						// true if the heap has been initialized
	KTU32 bytesRemaining;				// bytes remaining for allocation
	KTU32 heapSize;						// total size of the heap zone
	KTU32 *baseOfHeap;					// the unaligned start of the zone
	KTU32 *bottomOfHeap;				// the DWORD aligned start, first address allocated
	KTU32 *topOfHeap;					// the last byte owned by the zone
	AM_MCB_STRUCT purgableMCB[AM_HEAP_MAX_MASTER_POINTERS];	// purgable memory control blocks
	AM_MCB_STRUCT fixedMCB[AM_HEAP_MAX_MASTER_POINTERS];	// fixed memory control blocks
} AM_HEAP_STRUCT;

typedef struct
{
	KTU32 *startOfMonoPlayBuffer;		// start of mono buffer in audio memory
	KTU32 *middleOfMonoPlayBuffer;		// middle of mono buffer in audio memory
	KTU32 *startOfLeftPlayBuffer;		// start of left buffer in audio memory
	KTU32 *middleOfLeftPlayBuffer;		// middle of left buffer in audio memory
	KTU32 *startOfRightPlayBuffer;		// start of right buffer in audio memory
	KTU32 *middleOfRightPlayBuffer;		// middle of right buffer in audio memory
	KTU32 interruptsTillEnd;			// number of interrupts till end
	KTU32 channels;						// 1 for mono, 2 for stereo
	KTU32 volume;						// the aica volume, 0-15
	KTU32 pan;							// the aica pan, 0-31 
	KTU32 monoPort;						// port used for the mono stream
	KTU32 leftPort;						// port used for the left stream
	KTU32 rightPort;					// port used for the right stream
} AM_STREAM_TRACK;	

#define AM_STREAM_FILENAME_LEN				80		// used in AM_STREAM structure

typedef struct
{
	AM_STREAM_TRACK track[AM_STREAM_MAX_TRACKS];	// the track data
	KTU32 numberOfTracks;				// number of tracks in this stream
	KTU32 *transferBuffer;				// pointer to transfer buffer (SH4)
	KTU32 transferBufferSize;			// size of transfer buffer
	KTU32 *transferBucket;				// pointer to current transfer bucket (SH4)
	KTU32 transferBucketSize;			// size of current transfer bucket
	KTU32 *playBuffer;					// start of play buffer memory (AICA)
	KTU32 playBufferSize;				// size of play buffer
	KTU32 middleOfBufferInFrames;		// middle of mono or left buffer in audio memory in flames
	KTU32 endOfBufferInFrames;			// end of mono or left buffer in audio memory in flames
	KTU32 bufferToggle;					// flipped by the ISR to alternately load the buffers
	KTU32 playTime;						// KTTRUE: refresh playBuffer
	KTU32 xferTime;						// KTTRUE: refresh transferBucket
	KTU32 xchkTime;						// KTTRUE: refresh transferBucket check
	KTCHAR fileName[AM_STREAM_FILENAME_LEN];	// the file name
	ACFILE sd;							// descriptor for the stream io file system
	KTU32 sampleRate;					// aica sample rate i.e. AC_22K_SAMPLE_RATE, AC_44K_SAMPLE_RATE etc...
	AC_AUDIO_TYPE type;					// aica sample type 
	AM_STREAM_ISR isr;					// stream ISR
	KTU32 isrPort;						// port used for event messages
	KTU32 isrCounter;					// number of interrupts served
	KTU32 interruptsTillEnd;			// number of interrupts till end
	KTU32 sizeInSectors;				// fileSize/2048 		
	KTU32 sizeInBytes;					// fileSize
	KTU32 sectorsRemaining;				// countdown
	AM_STREAM_MODE mode;				// warming up, playing, etc.
	AM_STREAM_OPERATION operation;		// open, header read, etc.
	AMS_PLAY_BUFFER_OPERATION bufferOperation;	// what to do with the pbuffer refresh
	KTU32 transferCount;
	AM_STREAM_FILE_HEADER *headerBuffer;	// buffer for the header sector
} AM_STREAM;

// multi track stream scene mixing 
typedef struct
{
	KTU32 volume;						// 0-127
	KTU32 pan;							// 0-127
} AM_STREAM_MIX_TRACK;
 
typedef struct
{
	AM_STREAM_MIX_TRACK	track[AM_STREAM_MAX_TRACKS];
} AM_STREAM_MIX;

// sound effects
typedef struct
{
	KTU32 sampleRate;
	AC_AUDIO_TYPE aicaSampleType;
	KTU32 volume;
	KTU32 pan;
	KTU32 effectMix;
	KTU32 effectMixerChannel;
	KTBOOL effectFlag;
	KTU32 qPanAngle;
	KTS32 aicaLoopFlag;
	KTU32 pitchOffsetInCents;
	KTU32 sizeInBytes;
	KTU32 voiceChannel;
	KTBOOL randomPitchAmount;
	KTU32 *soundData;
	KTBOOL isPlaying;
	AM_USER_CALLBACK callback;
} AM_SOUND;

typedef struct
{
	KTU32 firstQChannel;
	KTU32 lastQChannel;
	KTBOOL qEnabledFlag;
} AM_SOUND_SYSTEM;

// midi sequences
typedef struct
{
	KTU32 voiceChannel;					// the voice channel number
	KTU32 midiPort;						// the MIDI port number
	KTS32 gmMode;						// AC_GM_ON or AC_GM_OFF
	KTU32 ticksPQN;						// the time division in ticks per quarter note
	KTU32 usPQN;						// the time division in microseconds per quarter note
	KTU32 volume;						// midi master volume 0-127
	KTU32 loop;							// 1 if looping, 0 if not
	KTU32 size;							// the size of the sequence data
	KTU32 *address;						// the address of the sequence data
	AM_MIDI_CALLBACK callback;			// the callback proc
	KTU32 callbackOffset;				// the offset in sound memory to the EOT marker
} AM_SEQUENCE;

typedef struct
{
	AC_TRANSFER_REQUEST request;
	KTBOOL allocated;
} AM_TRANSFER_POOL;

typedef struct
{
	KTBOOL sysinit;
	AM_ERROR error;
	AM_HEAP_STRUCT heap;
	AM_VOICE_POOL voice;
	AM_SOUND_SYSTEM sound;
	AM_TRANSFER_POOL xfer[AC_MAX_TRANSFER_QUEUE];
} AM_SYSTEM_STRUCT;

extern AM_SYSTEM_STRUCT	gAmSystem;

//-----------------------------------------------------------------------------
// prototypes
//-----------------------------------------------------------------------------

// error functions

void amErrorSet(AM_ERROR_TYPE errorNumber, KTSTRING errorMessage);
AM_ERROR *amErrorGetLast(void);
KTBOOL amErrorExists(void);
void amErrorClear(void);

// play one shot wave files from a katbank

KTBOOL amSoundPlay(AM_SOUND *theSound);
KTBOOL amSoundStop(AM_SOUND *theSound);
KTBOOL amSoundStopAll(void);
KTBOOL amSoundIsPlaying(AM_SOUND *theSound);
KTBOOL amSoundSetCurrentPlaybackRate(AM_SOUND *theSound, KTU32 sampleRate);
KTBOOL amSoundSetVolume(AM_SOUND *theSound, KTU32 aicaVolume);
KTBOOL amSoundSetPan(AM_SOUND *theSound, KTU32 aicaPan);
KTBOOL amSoundSetVoiceChannel(AM_SOUND *theSound, KTU32 voiceChannel);
KTBOOL amSoundSetCallback(AM_SOUND *theSound, AM_USER_CALLBACK callback);
KTBOOL amSoundAllocateVoiceChannel(AM_SOUND *theSound);
KTBOOL amSoundIsLooping(AM_SOUND *theSound, KTBOOL *loopFlag);
KTBOOL amSoundGetSampleRate(AM_SOUND *theSound, KTU32 *realWorldSampleRate);
KTBOOL amSoundGetVolume(AM_SOUND *theSound, KTU32 *aicaVolume);
KTBOOL amSoundGetPan(AM_SOUND *theSound, KTU32 *aicaPan);
KTBOOL amSoundGetVoiceChannel(AM_SOUND *theSound, KTU32 *voiceChannel);
KTBOOL amSoundGetCallback(AM_SOUND *theSound, AM_USER_CALLBACK *theCallback);
KTBOOL amSoundFetchSample(AM_BANK_PTR theBank, KTU32 soundNumber, AM_SOUND *theSound);
KTBOOL amSoundSetEffectsBus(AM_SOUND *theSound, KTU32 dspMixerChannel, KTU32 sourceMix);
KTBOOL amSoundSetQSoundChannels(KTU32 firstQChannel, KTU32 numberOfQChannels);
KTBOOL amSoundPlayRaw(KTS32 voiceChannel, KTU32 sizeInBytes, KTU32 address, KTU32 sampleRate, AC_AUDIO_TYPE aicaAudioType, KTU32 pitchOffsetInCents, KTS32 aicaLoopFlag, AM_USER_CALLBACK userCallbackProc, KTU32 dryVolume, KTU32 wetVolume, KTU32 channelVolume, KTU32 pan, KTU32 mixerChannel, KTBOOL effectsOnOrOff);
KTBOOL amSoundReleaseVoiceChannel(AM_SOUND *theSound);

// play [AD]PCM streaming audio from memory or disk

KTBOOL amStreamInitFile(AM_STREAM *theStream, KTSTRING fileName);
KTBOOL amStreamSetBuffers(AM_STREAM *theStream, KTU32 *transferBuffer, KTU32 transferBufferSize, KTU32 *playBuffer, KTU32 playBufferSize);
KTBOOL amStreamSetHeaderBuffer(AM_STREAM *theStream, KTU8 *headerBuffer);
KTBOOL amStreamSetIsr(AM_STREAM *theStream, AM_STREAM_ISR theIsr);
KTBOOL amStreamServer(AM_STREAM *theStream);
KTBOOL amStreamStart(AM_STREAM *theStream);
KTBOOL amStreamIsDone(AM_STREAM *theStream, KTBOOL *isDone);
KTBOOL amStreamIsIdle(AM_STREAM *theStream, KTBOOL *isIdle);
KTBOOL amStreamIsPlaying(AM_STREAM *theStream, KTBOOL *isPlaying);
KTBOOL amStreamSetHeaderBuffer(AM_STREAM *theStream, KTU8 *headerBuffer);
KTBOOL amStreamStop(AM_STREAM *theStream);
KTBOOL amStreamClose(AM_STREAM *theStream);
KTBOOL amStreamSetVolume(AM_STREAM *theStream, KTU8 newVolume, KTU32 trackNumber);
KTBOOL amStreamSetPan(AM_STREAM *theStream, KTU8 newPan, KTU32 trackNumber);
KTBOOL amStreamReleaseVoiceChannels(AM_STREAM *theStream);
// ISRs for streaming audio
void _amStreamIsr(KTU32 streamPtr); 

// general utility functions

KTBOOL amUtilGetNibblesPerFrame(AC_AUDIO_TYPE type, KTU32 *nibblesPerFrame);
KTBOOL amUtilGetLengthInMs(AC_AUDIO_TYPE type, KTU32 channels, KTU32 size ,KTU32 aicaSampleRate, KTU32 *lengthInMs);
KTBOOL amUtilGetMsPerIrq(AC_AUDIO_TYPE type, KTS32 aicaSampleRate, KTU32 playBufferSizeInBytes, KTU32 *msPerIrq);
KTBOOL amUtilGetLengthInFrames(AC_AUDIO_TYPE type, KTU32 channels, KTU32 size, KTU32 *lengthInFrames);
KTBOOL amUtilGetAicaSampleType(KTU32 bitDepth, AC_AUDIO_TYPE_PTR aicaSampleType);
KTBOOL amUtilGetEndOfBufferInFrames(KTU32 bitDepthOfSample, KTU32 sizeOfBufferInBytes, KTU32 *endInFrames);
KTBOOL amUtilGetMiddleOfBufferInFrames(KTU32 bitDepthOfSample, KTU32 sizeOfBufferInBytes, KTU32 *middleInFrames);
KTBOOL amUtilGetAicaSampleRate(KTU32 realWorldSampleRate, KTS32 *aicaSampleRate);
KTBOOL amUtilGetSampleRate(KTU32 aicaSampleRate, KTU32 *sampleRate);
KTBOOL amUtilGetAicaSampleType(KTU32 bitDepth, AC_AUDIO_TYPE *aicaSampleType);
KTBOOL amUtilGetAicaVolume(KTU32 midiVolume, KTU32 *aicaVolume);
KTBOOL amUtilAlignNumber(KTU32 theNumber, KTU32 theAlignment, KTU32 *theResult);

// play type 0 SMF files from a katbank

KTBOOL amMidiLoadToneBank(KTSTRING fileName, KTS32 gmMode, KTU32 *buffer, KTU32 bankSize, KTU8 toneBankSlot);
KTBOOL amMidiTransferToneBank(KTU32 *destination, KTU32 *source, KTS32 gmMode, KTU32 bankSize, KTU8 toneBankSlot);

KTBOOL amMidiFetchSequence(AM_BANK_PTR theBank, KTU32 sequenceNumber, AM_SEQUENCE *theSequence);
KTBOOL amMidiFetchToneBank(AM_BANK_PTR theBank, KTU32 assetNumber, KTU8 toneBankSlot);

KTBOOL amMidiStop(AM_SEQUENCE *theSequence);
KTBOOL amMidiPlay(AM_SEQUENCE *theSequence);
KTBOOL amMidiResume(AM_SEQUENCE *theSequence);
KTBOOL amMidiPause(AM_SEQUENCE *theSequence);
KTBOOL amMidiAllocateSequencePort(AM_SEQUENCE *theSequence);
KTBOOL amMidiSetVolume(AM_SEQUENCE *theSequence, KTU32 newVolume);
KTBOOL amMidiInstallCallback(AM_SEQUENCE *theSequence, AM_MIDI_CALLBACK theCallback);
KTBOOL amMidiSetLoopFlag(AM_SEQUENCE *theSequence, KTBOOL onOrOff);
KTBOOL amMidiSetTempo(AM_SEQUENCE *theSequence, KTS32 percentOfChange);

KTBOOL amMidiNoteOff(KTU32 midiPort, KTU32 midiChannel, KTU8 midiNoteNumber);
KTBOOL amMidiNoteOn(KTU32 midiPort, KTU32 midiChannel, KTU8 midiNoteNumber, KTU32 midiNoteOnVelocity);
KTBOOL amMidiSetChannelProgram(KTU32 midiPort, KTU32 midiChannel, KTU32 midiProgramNumber);
KTBOOL amMidiSetChannelVolume(KTU32 midiPort, KTU32 midiChannel, KTU32 midiVolume);
KTBOOL amMidiSetChannelPan(KTU32 midiPort, KTU32 midiChannel, KTU32 midiPan);
KTBOOL amMidiAllocateSoundEffectPort(KTU32 *voiceChannel, KTU32 *midiPort);
KTBOOL amMidiPlayRaw(KTU32 midiPort, KTS32 gmMode, KTU32 ticksPQN, KTU32 loop, KTU32 sequenceSize, KTU32 *sequenceAddress, KTU32 midiVolume, AM_MIDI_CALLBACK callback);

// manage assets packed in katbanks

KTBOOL amBankGetSize(KTSTRING fileName, KTU32 *bankSize);
KTBOOL amBankLoad(KTSTRING fileName, AM_BANK_PTR buffer, KTU32 size);
KTBOOL amBankTransfer(KTU32 *target, AM_BANK_PTR source, KTU32 size);
KTBOOL amBankFetchAsset(AM_BANK_PTR theBank, AM_BANK_FILE_UNION_PTR parameters, KTU32 assetNumber, KTU32 **theAsset, KTU32 *assetSize);
KTBOOL amBankFetchAssetParameters(AM_BANK_PTR theBank, KTU32 assetNumber, AM_BANK_FILE_UNION_PTR parameters);
KTBOOL amBankFetchUnknownParameters(AM_BANK_PTR theBank, KTU32 assetNumber, KTU32 parameterNumber, KTS32 *parameterValue);
KTBOOL amBankFetchWaveBitDepth(AM_BANK_PTR theBank, KTU32 assetNumber, KTU32 *bitDepth);
KTBOOL amBankFetchWaveSampleRate(AM_BANK_PTR theBank, KTU32 assetNumber, KTU32 *sampleRate);
KTBOOL amBankFetchWaveRandomPitch(AM_BANK_PTR theBank, KTU32 assetNumber, KTU32 *randomPitchAmount);
KTBOOL amBankFetchWaveLoopFlag(AM_BANK_PTR theBank, KTU32 assetNumber, KTBOOL *loopFlag);
KTBOOL amBankFetchMidiGmModeFlag(AM_BANK_PTR theBank, KTU32 assetNumber, KTS32 *gmModeFlag);
KTBOOL amBankFetchMidiVolume(AM_BANK_PTR theBank, KTU32 assetNumber, KTU32 *masterVolume);
KTBOOL amBankFetchMidiPpqn(AM_BANK_PTR theBank, KTU32 assetNumber, KTU32 *ppqn);
KTBOOL amBankFetchMidiLoop(AM_BANK_PTR theBank, KTU32 assetNumber, KTU32 *loop);
KTBOOL amBankFetchMidiUspqn(AM_BANK_PTR theBank, KTU32 assetNumber, KTU32 *uspqn);
KTBOOL amBankGetAssetSize(AM_BANK_PTR theBank, KTU32 assetNumber, KTU32 *assetSize);
KTBOOL amBankGetHeaderSize(AM_BANK_PTR theBank, KTU32 *headerSize);
KTBOOL amBankGetNumberOfAssets(AM_BANK_PTR theBank, KTU32 *numberOfAssets);
KTBOOL amBankAssetTypeIs(AM_BANK_PTR theBank, KTU32 assetNumber, AM_BANK_ASSET_TYPE type);

#define amDmaMemCpy					amDmaMemCpy_obsolete	/* refer to acTransfer() */

// audio (AICA) memory management

KTBOOL amHeapInit(KTU32 *memoryStartAddress, KTU32 size);
void amHeapShutdown(void);
KTBOOL amHeapAlloc(KTU32 **buffer, KTU32 size, KTU32 alignment, AM_HEAP_MEMORY_TYPE memoryType, AM_MEMORY_CALLBACK callback);
KTBOOL amHeapFree(KTU32 *buffer);
KTBOOL amHeapClear(AM_HEAP_MEMORY_TYPE memoryType);
KTBOOL amHeapPurge(KTU32 sizeNeeded);
KTBOOL amHeapGetFree(KTU32 *freeMemory);
KTBOOL amHeapGetInfo(KTU32 **freeSoundMemory, KTU32 *size);
KTBOOL amHeapGetMaxPurgable(KTU32 *maxPurgable);
#ifdef DEBUG
KTBOOL _amHeapCheck(void);
#define amHeapCheck()		_amHeapCheck()
#else
#define amHeapCheck()
#endif

// DSP control
KTBOOL amDspFetchProgramBank(AM_BANK_PTR theBank, KTU32 assetNumber);
KTBOOL amDspFetchOutputBank(AM_BANK_PTR theBank, KTU32 assetNumber);

// initialization & shutdown
KTBOOL amInit(void);
void amShutdown(void);
#define amInitSelectDriver					amInitSelectDriver_obsolete
KTSTRING amInitGetDriverFileName(void);
void amSystemSetVolumeMode(KTBOOL mode);	// set am system to use linear or log (default) volume mapping

// voice management for MIDI and DA playback
void amVoiceInit(void);
KTBOOL amVoiceAllocate(KTU32 *voiceChannel, AM_VOICE_TYPE voiceType, void *owner);
KTBOOL amVoiceFree(KTU32 voiceChannel);
KTBOOL amVoiceInstallUserCallback(KTU32 voiceChannel, AM_USER_CALLBACK userCallbackProc);
KTBOOL amVoiceSetStreamIsr(KTU32 voiceChannel, AM_STREAM_ISR streamIsr);

#ifdef __cplusplus
}
#endif

#endif //	_AM_H_
