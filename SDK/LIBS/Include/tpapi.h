#ifndef _truapi_h
#define _truapi_h

#include <duck_hfb.h>
#include <duck_dxl.h>

#if defined(__KATANA__)
#include <shinobi.h>
#include <sg_sd.h>
#endif

#if !defined(USERSCAN_ALLOWED)
#define USERSCAN_ALLOWED 1
#endif

/* Multiple Avi's FWG 1-15-99 */
#define TRUEMOTION_MULTAVIS_HACK	-19
#define TM_MA_HACK	TRUEMOTION_MULTAVIS_HACK
typedef struct MULT_AVI 
{
	unsigned long beginOfFile;
	char * cmdLine;
} MultAviStruct, *MultAviHandle;
/* Multiple Avi's FWG 1-15-99 */

#define SCAN_DATA_SIZE (128*1024*USERSCAN_ALLOWED)

#define VCR_PLAY		0
#define VCR_BACKWARD	1
#define VCR_FORWARD		2
#define VCR_FINISH		4
#define VCR_PAUSE		8
#define VCR_BACKSTEP	16
#define VCR_FORSTEP		32
#define VCR_LAST_FRAME	64
#define VCR_FIRST_FRAME	128
#define VCR_DUMMY		256

#define VCR_INIT        512
#define VCR_SHUTDOWN    1024

#define NUM_BUFFERS		3

typedef enum PLAYER_STATUS_CODE_temp 
{ 
    /* Must be the first (min in the list)! */
    TP_MIN = -2000,    

    TP_ERR_FINDINGCLUT,				/* 1999 */
    TP_ERR_CREATINGVSCREEN,			/* 1998 */
    TP_ERR_INITVIDEO,				/* 1997 */
    TP_ERR_VESAMODE,				/* 1996 */
    TP_ERR_INVALIDVBEVERSION,		/* 1995 */

    TP_FRAME_EXCEEDS_BOUND,			/* 1994 */
    TP_FILE_OPEN_FAILED,			/* 1993 */
	TP_BUFFER_ERROR,				/* 1992 */
	TP_INVALID_BLITTER,				/* 1991 */
	TP_OVERLAY_UNSUPPORTED,			/* 1990 */
	TP_UNSUPPORTED_FOURCC_MODE,		/* 1989 */
 	TP_UNKNOWN_ERROR,				/* 1988 */
	TP_BAD_VIDEO_MODE, 
    TP_DXL_ERROR,
    TP_HFB_ERROR,
	TP_COMMANDLINE_ERROR,
	TP_AUDIO_INIT_ERROR,
    TP_ERROR,
	TP_ERR_CANT_HOLD_FRAMERATE,

	TP_OK						= 0,
	TP_QUIT						= 2000,
	TP_INITIALIZING,
	TP_PLAYING,
	TP_PAUSED,
	TP_FASTFORWARDING,
	TP_REWINDING,
	TP_READY,
	
	TP_AT_LAST_FRAME,
	TP_AT_FIRST_FRAME,
	TP_STEPPING,
	TP_SCANNING,
    TP_INITIALIZED,
    TP_FINISHED,
    TP_SHUTDOWN,
    TP_EOF,
	TP_STARTED,
	TP_SKIPPED,

	/* Must be the max in the list */
	TP_MAX
	
} PLAYER_STATUS_CODE;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MACPPC
#include "tpapiplt.h"   /* sound specific glue related to DXA and Trueplay */
#endif

typedef struct MOVIE {

#ifdef MOVIE_PLATFORM_INFO
	MOVIE_PLATFORM_INFO    /* see tpapiplt.h */
#endif

	/* TrueMotion objects */
	HFB_BUFFER_HANDLE xBuffer;
	HFB_FILE_HANDLE xFile;

	HFB_STREAM_HANDLE vStream;

    DXL_VSCREEN_HANDLE vScreen;
	DXL_XIMAGE_HANDLE xImage;

	HFB_STREAM_HANDLE aStream;

    DXL_AUDIODST_HANDLE audDst;
	DXL_XAUDIOSRC_HANDLE audSrc;
	
	/* video sub-system interface functions */

	PLAYER_STATUS_CODE (*setupDisplay)(struct MOVIE *);	/* function for initializing display */
	PLAYER_STATUS_CODE (*restoreDisplay)(struct MOVIE *);	/* restore screen to previous state */
	
	PLAYER_STATUS_CODE (*beforeDecompress)(struct MOVIE *); /* performed before decompression to vscreen */
	PLAYER_STATUS_CODE (*afterDecompress)(struct MOVIE *);	 /* performed after decompression to vscreen */

	PLAYER_STATUS_CODE (*centerScreen)(struct MOVIE *);	/* performed when image needs centering */

	/* audio sub-system interface functions */

	PLAYER_STATUS_CODE (*setupAudioDriver)(struct MOVIE *);
	PLAYER_STATUS_CODE (*shutdownAudioDriver)(struct MOVIE *);

	PLAYER_STATUS_CODE (*startDecompressingAudio)(struct MOVIE *);
	PLAYER_STATUS_CODE (*stopDecompressingAudio)(struct MOVIE *);

	PLAYER_STATUS_CODE (*decompressAudio)(struct MOVIE *,int limit);

	PLAYER_STATUS_CODE (*startAudioPlayback)(struct MOVIE *);
	PLAYER_STATUS_CODE (*stopAudioPlayback)(struct MOVIE *);

	long (*getSyncFrame)(struct MOVIE *);

	int BytesPerSample;
	int AudioSampleRate,numAudioChannels;

    unsigned char *audioLeftBuffer;
    long audioLeftBufferIndex;
    unsigned char *audioRightBuffer;
    long audioRightBufferIndex;

	int aIndex,vIndex;
	long aLength,vLength;
	unsigned char *aData,*vData;

	unsigned char *scanData;
	int scanDataLength;

	/* gathered/reported statistics */
	int skippedFrames;
	int samplesPerFrame;
	int scale,rate,frameRate;
	int width,height;
	int playedFrames;
	int autoDelay;
	dxvBlitQuality stretch;		/* -stretch[interp] */

	/* command parameters */
	unsigned play:1;			/* playing status */
	unsigned slaveCD:1;			/* if applicable, "thread" file i/o */
	unsigned slaveBlit:1;		/* if applicable, "thread" blitting */
	unsigned log:1;				/* -log[filename] */
	unsigned speedTest:1;		/* -speedTest */
	unsigned centerX:1;			/* -position[C,] */
	unsigned centerY:1;			/* -position[,C] */
	unsigned videoPreset:1;		/* -video[preset] */
	unsigned videoAutoset:1;	/* -video[autoset] */
	unsigned noAudio:1;			/* -sound[on/off] */
	unsigned loop:1;			/* -loop (as per -segment) */
	unsigned stayResident:1;	/* -stayResident */
	unsigned userExit:1;		/* -userexit - allow user exit */
	unsigned userScan:1;		/* -userscan - allow user scan */
	unsigned userPause:1;		/* -userpause - allow user pause/resume */
	unsigned appField1:1;
	unsigned appField2:1;
	unsigned appField3:1;
	unsigned appField4:1;
	unsigned appField5:1;
	unsigned showWhiteDots:1;   /* -showwhitedots - display bitdepth white dots */
	unsigned finishAtEOF:1;     /* stop playing movie when EOF */
	unsigned showSpeedMsg:1;    /* show frame rate message box */
	unsigned exitAppAtStop:1;   /* Exit controlling app at stop condition */
	unsigned catchUp:1;			/* TruePlay has fallen behind for what frame should be shown. */
	unsigned missedAFrame:1;

	char fileName[80];			/* [fileName] */
	char logName[80];			/* -log[FileName] */
	char cmdName[80];			/* @[commandFileName] */

	int xoff,yoff;				/* -position[xxx,yyy] */
	int from_frame,to_frame;	/* -segment[s,e] */
	int start_frame;
    
    long videoFrame;

    PLAYER_STATUS_CODE vcrState;

	int videoHRes;
	int videoVRes;				/* -video[vres,hres,color,buffers] */
	int videoCRes;
	int videoFrameBuffers;

	int HFB_readSize;			/* -readSize[#####] */
	int HFB_bufferSize;			/* -bufferSize[#####] */
	int HFB_preLoad;			/* -preLoad[#####/##%] */

	unsigned long appLong1;
	unsigned long appLong2;
	unsigned long appLong3;
	unsigned long appLong4;
	unsigned long appLong5;

	/* other platform specific information can follow */
	/* (i.e. texture coordinates, ddraw surfaces, etc. etc. */

	/* Multiple Avi's FWG 1-15-99 */
	/* Multiple Avi's in one file */
	unsigned long ma_numAvis;			/* Number of avis in multiple avi file. */
	MultAviStruct *ma_multAviInfo;		/* Pointer to info about avis in multiple avi file. */
	unsigned long ma_playNum;			/* Which avi file to play in a multiple avi file. */
	unsigned long ma_loop;				/* loop the avi file in a multiple avi file. */

	signed long skipToFrame;			/* Tell TruePlay which KeyFrame to skip to. */
	unsigned long jitterMax;			/* The maximum amount of jitter, where TruePlay won't play a frame of the movie. */

	unsigned char *scanDataAlgn;		/* Align the Scan Data Buffer to a 32byte boundry. */

#if defined(MACPPC)
	int macScreenHeight;
	int macScreenWidth;
#endif

#if defined(WIN32)
	void *mDirectSound;
	void *mAudioBuffer;
	void *mAudioPrimary;
	unsigned long milliseconds_at_start;/* Used in tpAudio.c */
	unsigned long numSamplesPlayed;		/* Number of samples played by the aduio card. */
	unsigned long oldPlayCursor;		/* Used by TruePlay to see how many samples have played since last sample change. */

	/* DirectDraw and DirectSound variables */
	int mDirectSoundOwner;
	void *lpDD;
	int lpDDOwner;
	void *lpDD2;
	int lpDD2Owner;

	unsigned long hWnd;					/* HWND used to set cooperative levels on DirectDraw and DirectSound, and for Debug Message Box's. */

	int repaint;						/* Flag to tell TruePlay when to repaint the window. */
	int movieActive;					/* Flag to tell TruePlay when we have a movie to play. */
	int captureMouse;					/* Flag to tell TruePlay DLL when to take control of mouse input. */
	int startPlaying;					/* Flag to tell TruePlay when the system is ready to play the movie. */
	
	unsigned long soundSyncToMilli;		/* Flag to tell TruePlay whether or not to sync audio to milliseconds from start. */
	unsigned long soundInterpTime;		/* Flag to tell TruePlay whether or not interpolate time between DirectSound sample changes. */
	unsigned long deltaFlipTime;		/* Used when timeGetTime counter overflows 32 bit number, to keep audio in sync. */

	/* Varibles used in the demo */
	int slowTest;
	int demoTrick;
	
	/* Varibles used in outputting debug numbers. */
	unsigned long g_numBufReads;
	unsigned long g_bufReadTotalTime;
	unsigned long g_bufEOF;
#endif

#if defined(__KATANA__)

	PLAYER_STATUS_CODE (*setOutVol)(struct MOVIE *, Sint32 vol);
	Sint32 (*getOutVol)(struct MOVIE *);
	PLAYER_STATUS_CODE (*setOutPan)(struct MOVIE *, Sint32 c, Sint32 p);
	Sint32 (*getOutPan)(struct MOVIE *, Sint32 c);
	
	int numSamples;
	int txBlock;
	unsigned char *alignedPtr[2];
	unsigned char *rawPtr[2];

	SDPSTM pcmStHndl;
	SDMEMBLK mem_blk;
	long counter;

	/* FWG 5-13-99 */
	/* These variables are used by tpMwRnaSnd.c */
	unsigned long * sjo[2];
	unsigned long *	rna;
	int				offset[2];
	/* FWG 5-13-99 */

	signed int  pcmStVolume;
	signed char pcmStVolumeSet;
	signed int  pcmStPanpotLeft;
	signed char pcmStPanpotLeftSet;
	signed int  pcmStPanpotRight;
	signed char pcmStPanpotRightSet;
	unsigned int  pcmStLastPauseNumSamples;

	int  pcmStExtraSamples;

	PLAYER_STATUS_CODE katanaMovieState;

#if defined(__AUDIO64__)
	unsigned long startOffset;
	unsigned long chainId;
	long leftChan;
	long rightChan;
	unsigned long rightOffset;
	
	unsigned long hwBlock;
	unsigned long transferCount;
	unsigned long totalSampPlayed;
	unsigned long bytesPerSample;
#endif

#endif
	
} MovieStruct, *MovieHandle;


#if defined(__KATANA__)

#define ASYNC_FILE_IO 1

#endif

/********
DirectDraw Specific Fields:
*********/

#define videoOverlay	appField1

#define overlayCRes		appLong1
#define overlayHRes		appLong2
#define overlayVRes		appLong3

/*********/
int duck_readFinished();

PLAYER_STATUS_CODE  tp_MovieStructInit(
	MovieHandle movie, 
	PLAYER_STATUS_CODE (*setupDisplay)(struct MOVIE *mv),
	PLAYER_STATUS_CODE (*setupAudioDriver)(struct MOVIE *mv)); 

/******** main playback control functions ********/
PLAYER_STATUS_CODE tp_MovieServerInit(MovieHandle movie);
PLAYER_STATUS_CODE tp_MovieServerExec(MovieHandle movie,int vcrNow);
PLAYER_STATUS_CODE tp_MovieServerShutDown(MovieHandle movie);

PLAYER_STATUS_CODE tp_MovieServerStartPlayback(MovieHandle movie);

int tp_MovieServerScan(MovieHandle movie,int vcrNow);

PLAYER_STATUS_CODE  tp_MovieInitAndPlay(MovieHandle);				/* do everything */
PLAYER_STATUS_CODE  tp_MoviePlay(MovieHandle);						/* do everything but init */

int tp_MovieOpen(MovieHandle);										/* open AVI file and allocate structures */
void tp_MovieClose(MovieHandle );									/* close and deallocate */

PLAYER_STATUS_CODE tp_MovieStart(MovieHandle movie);								/* initialize buffers at start of playback */
int tp_MovieContinue(MovieHandle movie);							/* initialize buffers after interrupted playback */

int  tp_MovieScan(MovieHandle);										/* fastforward/rewind */
int  tp_MovieStep(MovieHandle movie,int vcrNow);					/* forestep/backstep */
void tp_MovieFirstFrame(MovieHandle movie);							/* show first frame */
void tp_MovieLastFrame(MovieHandle movie);							/* show last frame */
int  tp_MovieShowFrame(MovieHandle movie);							/* blit one frame & pause */

long tp_SyncFrame(MovieHandle);

void tp_SyncFrameSet(long frame);

/******** video playback/control functions ********/

PLAYER_STATUS_CODE tp_setupDisplay(MovieHandle movie);
PLAYER_STATUS_CODE tp_VideoSetup(MovieHandle movie);				/* do once, allocate vScreen(s) */

PLAYER_STATUS_CODE tp_VideoStart(MovieHandle movie);				/* turn on the video display */
void tp_VideoStop(MovieHandle movie);								/* turn off the display */

void tp_VideoShutDown(MovieHandle movie);							/* do once, destroy vScreen(s) */

void tp_VideoCenter(MovieHandle movie);				                /* center the video */
PLAYER_STATUS_CODE tp_VideoProcess(MovieHandle movie, int blitFlag);/* process the next frame */
PLAYER_STATUS_CODE tp_VideoBestFit(MovieHandle movie);				/* Get a video mode for autoset */
PLAYER_STATUS_CODE tp_VideoModeCheck(MovieHandle movie);			/* See if the computer can handle the video mode requested */

/******** audio playback/control functions ********/

PLAYER_STATUS_CODE tp_setupAudioDriver(MovieHandle movie);								/* do once, allocate audio destination(s) */
PLAYER_STATUS_CODE tp_AudioStart(MovieHandle movie);								/* start audio playback */
PLAYER_STATUS_CODE tp_AudioStop(MovieHandle movie);								/* stop audio playback */
PLAYER_STATUS_CODE tp_AudioShutDown(MovieHandle movie);							/* do once, destroy audio destination(s) */

PLAYER_STATUS_CODE tp_MovieAudioSetup(MovieHandle movie);			/* configure dest(s)/preload audio */
PLAYER_STATUS_CODE tp_AudioProcess(MovieHandle movie,int limit);							/* process up to "limit" samples */
PLAYER_STATUS_CODE tp_MovieAudioShutDown(MovieHandle movie);						/* destroy audio source(s) */

void tp_AudioSetup(MovieHandle movie);

/****** command parsing/reporting functions *******/

PLAYER_STATUS_CODE tp_MovieReset(MovieHandle movie);				/* Reset the movie structure */




PLAYER_STATUS_CODE tp_MoviePlatformReset(MovieHandle movie);	


PLAYER_STATUS_CODE tp_CommandLineParse(MovieHandle movie,const char *m_lpCmdLine);
int tp_Cmd(MovieHandle movie, char *command);
int	tp_platformCmd(MovieHandle movie, char *command);

void tp_LogPrint(MovieHandle movie);

char *tp_StatusDecode(PLAYER_STATUS_CODE c,char *decode);

/* system specific profiling wrappers ! */
int tp_ProfilerInit(void);
int tp_ProfilerTerm(void);
int tp_ProfilerDump(char *filename);

void set_memfuncs(void);
void set_iofuncs(void);

/******** user input functions ********/

int tp_VCRKeyboardGet(MovieHandle movie);

int tp_VCRControlGet(MovieHandle movie);
void tp_VCRControlSet(int controlCode);

PLAYER_STATUS_CODE tp_StatusGet(MovieHandle movie);
PLAYER_STATUS_CODE tp_StatusSet(MovieHandle movie,PLAYER_STATUS_CODE controlCode);

void tp_VCRWaitWhilePaused(MovieHandle movie);

void tp_MoviePrint(MovieHandle movie, const char *fileName, const char * flags);
void tp_ErrorMessage(PLAYER_STATUS_CODE num, char * str, char * file, char * flags);

#ifdef __cplusplus
}
#endif

#endif /* _truapi_h */





