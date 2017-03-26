#ifndef _duck_hfb_h
#define _duck_hfb_h
/******************************************************************************\
*                                                                              *
* duck_hfb.h  -   TrueMotion include file for buffering/streaming libraries    *
*                                                                              *
*                 Version:      6.0.0                                          *
*                 Created:      3/3/98                                         *
*                 Copyright (c) 1994-98, The Duck Corp. All rights reserved.   * 
*                                                                              *
\******************************************************************************/


#if defined(_DLL)
#define libFunc __declspec( dllexport )
#else
#define libFunc
#endif

#if defined(__cplusplus)
extern "C" {
#endif

#include "duck_bmp.h"
#include "duck_wav.h"

typedef enum dukDirect {     /* direction to move within stream */
    DUK_BACKWARD=-1,         /* move backward from current position */
    DUK_ABSOLUTE=0,          /* move to an absolute position */
    DUK_FORWARD=1,            /* move forward from current position */
    DUK_RESET=2              /* reset stream according to file position */
} hfbDirection;

typedef enum HFB_FileType {  /* type of file opened */
    DUK_NULFILE = 0,         /* not a TrueMotion "S" A/V file */
    DUK_DUKFILE = 1,         /* TrueMotion "S" duk file */
    DUK_AVIFILE = 2,         /* TrueMotion "S" Video for Windows AVI compatible file */ 
    DUK_QTFILE = 3           /* TrueMotion "S" Quicktime MOV compatible file */
} hfbFileType;

typedef enum HFB_StreamType {/* stream types */ 
    DUK_UNDEFINED = 0,       /* indeterminate or uninitialized stream */
    DUK_AUDSTREAM = 1,       /* audio stream */
    DUK_VIDSTREAM = 2,       /* video stream */
    DUK_TXTSTREAM = 3        /* text stream */
} hfbStreamType;

typedef enum HFB_Modes {     /* HFB buffering modes */
    HFBMODE_NORMAL = 0,      /* normal play once mode */
    HFBMODE_FORWARDLOOP = 1, /* forward looping mode (loop back to start) */
    HFBMODE_REVERSE = 2,     /* reverse play once mode (not yet implemented)*/
    HFBMODE_REVERSELOOP = 3, /* reverse looping mode (not yet implemented)*/
    HFBMODE_QUEUE = 4        /* file queue mode (not yet implemented)*/
} hfbBufferMode;

typedef enum BUFFERSTATUS { 
	HFB_BUSY = 0, 
	HFB_COMPLETE 
} hfbBufferStatus;

typedef enum PRELOADSPEC {
	HFB_FULL = -2,
	HFB_THREEQUARTERS = -1,
	HFB_NONE = 0
} hfbPreloadSpec;

#define HFB_USE_DEFAULT		0L
#define HFB_RESET_COUNT		-1L
#define HFB_IGNORE_COUNT	-2L

#define HFB_DATA_READ		0x01
#define HFB_DATA_RELEASED	0x02
#define HFB_DATA_KEYFRAME	0x08

typedef struct tHFB_STREAM_INFO{
	hfbStreamType streamType;
	int streamNum;
	long lSampleRate;
	long lStart;
	long lLength;
	char szName[24];
	union { 
		DKWAVEFORM WaveformInfo; 
		DKBITMAP BitmapInfo;
	} a;
} HFB_STREAM_INFO, MFP_STREAM_INFO;

typedef struct tHFB_FILE_INFO{
	long lFileSize;
	long lNumStreams;
	char sName[96];
	long lNumFrames;
} HFB_FILE_INFO, MFP_FILE_INFO;

typedef struct tHFBFile *HFB_FILE_HANDLE;
typedef struct tHFBStream *HFB_STREAM_HANDLE;
typedef struct tHFBBuffer *HFB_BUFFER_HANDLE;

typedef int HFB_DATA_HANDLE;

#define DCK_DEFAULT_READSIZE 0
#define DCK_DEFAULT_BUFFSIZE 0

/* main HFB initialization and exit routines */

libFunc int HFB_Init(int ,int ,int );
libFunc void HFB_Exit(void);

/* open specified file, parse its header(s) and load the index */
libFunc HFB_FILE_HANDLE HFB_OpenFile(
	const char *fileName,
	HFB_BUFFER_HANDLE bufferHandle
	);

/* the following three functions, findfile, parsefile and loadindex,
	are encapsulated by openfile, they are provided as a convenience
    for use on systems with asynchronous i/o */

libFunc HFB_FILE_HANDLE HFB_FindFile(const char *fileName);

libFunc int HFB_ParseFile(
	HFB_FILE_HANDLE fileHandle,
	HFB_BUFFER_HANDLE bufferHandle
	);

libFunc void HFB_LoadIndex(
	HFB_FILE_HANDLE fileHandle,
	HFB_BUFFER_HANDLE bufferHandle
	);

libFunc void HFB_CloseFile(HFB_FILE_HANDLE fHnd);

libFunc HFB_FILE_INFO *HFB_GetFileInfo(HFB_FILE_HANDLE fileHandle);

libFunc HFB_BUFFER_HANDLE HFB_CreateBuffer(
	long sizeOfBuffer,
	long reserved
	);

libFunc void HFB_InitBuffer(
	HFB_BUFFER_HANDLE bufferHandle,
	HFB_FILE_HANDLE fileToLoad,
	int startFrame,
	int initialReadSize
	);

libFunc int HFB_FillBuffer(
	HFB_BUFFER_HANDLE bufferHandle,
	long maxToRead,
	long frameSyncCounter
	);

libFunc void HFB_DestroyBuffer(HFB_BUFFER_HANDLE bufferHandle);

libFunc void HFB_ResetStreams(HFB_BUFFER_HANDLE bufferHandle);

libFunc int HFB_SetBufferMode(
	HFB_BUFFER_HANDLE ,
	hfbBufferMode mode 
	);

libFunc long HFB_GetBufferPerCentFull(HFB_BUFFER_HANDLE );
libFunc long HFB_GetmovieSize(HFB_BUFFER_HANDLE );
libFunc long HFB_GetBufferSpace(HFB_BUFFER_HANDLE );
libFunc hfbBufferStatus HFB_GetBufferStatus(HFB_BUFFER_HANDLE );

libFunc int HFB_ConditionBuffer(
	HFB_BUFFER_HANDLE bufferHandle,
	long bufferSize,
	long reserved);

#define HFB_ResetBuffer HFB_ConditionBuffer

/* get a stream reference handle */
libFunc HFB_STREAM_HANDLE HFB_GetStream(
	HFB_FILE_HANDLE fileHandle,
	const char *StreamNameOrNull,
	int streamNumber,
	unsigned long streamType);

/* relinquish reference to stream */
libFunc void HFB_ReleaseStream(HFB_STREAM_HANDLE streamHandle);

/* get a pointer to stream info struct */
libFunc HFB_STREAM_INFO *HFB_GetStreamInfo(HFB_STREAM_HANDLE );

#define HFB_GetStreamLength(strmh) \
	HFB_GetStreamInfo(strmh)->lLength

#define HFB_GetStreamName(strmh) \
	HFB_GetStreamInfo(strmh)->szName

/* get pointer to buffered record and length */
libFunc HFB_DATA_HANDLE HFB_GetStreamingData(
	HFB_STREAM_HANDLE streamHandle,
	void **ptrToPtr,
	long *ptrToLength,
	hfbDirection directionToMove,
	int framesToMove
	);

/* release buffer space occupied by record */
libFunc void HFB_ReleaseStreamingData(
	HFB_BUFFER_HANDLE bufferHandle,
	HFB_DATA_HANDLE recordToRelease);

/* read data directly from a file into a 
	supplied buffer, limit is set by initial value
	of *ptrToLength */
libFunc int HFB_ReadData(
	HFB_STREAM_HANDLE streamHandle,
	void *ptrToBuffer,
	long *ptrToLength,
	hfbDirection directionToMove,
	int framesToMove);

libFunc int HFB_FramestoNextKeyFrame(
	HFB_STREAM_HANDLE streamHandle,
	int recordHandle,
	int *numberOfRecordsSpanned
	);

libFunc int HFB_FrameToChunk(
	HFB_STREAM_HANDLE streamHandle,
	int frameNumber
	);

/* get the frameNumber of the keyframe 
	at or prior to the specified frameNumber */
libFunc int HFB_PreviousKeyFrame(
	HFB_STREAM_HANDLE streamHandle,
	int frameNumber
	);

typedef enum FTYPE { 
	HFB_FRAMENUM = 0, 
	HFB_INDEXNUM = 1
} hfbFrameNumber;

/* get the HFB index flags for the specified record/frame */

libFunc int HFB_GetIndexFlags(
	HFB_STREAM_HANDLE ,
	hfbFrameNumber frameNumberType,
	int recordHandleOrFrameNumber);

/* get current data position
   video - frameNumber
   audio - sampleCount */
libFunc long HFB_GetDataPosition(
	HFB_STREAM_HANDLE streamHandle,
	HFB_DATA_HANDLE dataRecordHandle
	);

/* get information about audio stream */
libFunc DKWAVEFORM *HFB_GetAudioInfo(
	HFB_STREAM_HANDLE nStream, 
	int *NumChannels, 
	int *SamplesPerSec, 
	int *BytesPerSec, 
	int *wFormat);

/* get the amount of audio skew 
	expressed in records */
libFunc int HFB_GetInitialFrames(
	HFB_STREAM_HANDLE videoStream,
	HFB_STREAM_HANDLE audioStream
	);

/* get the number of audio frames elapsed 
   during a single video frame */
libFunc int HFB_GetSamplesPerFrame(
	HFB_STREAM_HANDLE videoStream,
	HFB_STREAM_HANDLE audioStream
	);

/* get video frame rate and 
   calculated audio skew (in audio samples) */
libFunc void HFB_GetFrameRates(
	HFB_STREAM_HANDLE videoStream,
	HFB_STREAM_HANDLE audioStream,
	int *ptrToIntegerFrameRate,
	int *ptrToEstimatedAudioSampleSkew);

/*get pointer to stream information streuct */
libFunc HFB_STREAM_INFO *HFB_GetStreamInfo(HFB_STREAM_HANDLE );

/* functions to retrieve parent buffer 
   and file of a given stream*/
libFunc HFB_BUFFER_HANDLE HFB_GetStreamParentBuffer(HFB_STREAM_HANDLE );
libFunc HFB_FILE_HANDLE HFB_GetStreamParentFile(HFB_STREAM_HANDLE);

/* used to precisely calculate rational frame rates 
   for a specific stream */
libFunc void HFB_GetStreamRateAndScale(
	HFB_STREAM_HANDLE xStream,
	long *rate, long *scale
	);

/* get stream type and handler fourCC codes, 
   returns type (not handler) */
libFunc unsigned long HFB_GetStreamFCCs(
	HFB_STREAM_HANDLE xStream,
	unsigned long *type, 
	unsigned long *handler
	);

/* get streamSampleSize, <= 0 means variable */
libFunc int HFB_GetStreamSampleSize(HFB_STREAM_HANDLE xStream);

libFunc int HFB_WhatsAhead(HFB_STREAM_HANDLE ,int ,int *);

/* windows 95 dll system abstraction functions */

libFunc void HFB_Setmalloc(
	void *(*mallocFuncPtr)(unsigned int size)
	);

libFunc void HFB_Setcalloc(
	void *(*callocFuncPtr)(unsigned int size, unsigned int number)
	);

libFunc void HFB_Setfree(
	void (*freeFuncPtr)(void *)
	);

libFunc void HFB_Setopen(
	int (*openFuncPtr)(const char *, int,...)
	);

libFunc void HFB_Setclose(
	int (*closeFuncPtr)(int)
	);

libFunc void HFB_Setread(
	int (*readFuncPtr)(int,void *, unsigned int)
	);

libFunc void HFB_Setseek(
	long (*seekFuncPtr)(int,long,int)
	);

#if defined(__cplusplus)
}
#endif

#undef libFunc

#endif 
