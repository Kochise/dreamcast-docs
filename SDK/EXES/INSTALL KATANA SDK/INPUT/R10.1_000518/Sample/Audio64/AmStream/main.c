//-----------------------------------------------------------------------------
//
//	FILE:		main.c
//
//	DESC:		This has the main function for a AM layer multi-stream sample.
//
//	HISTORY:	2000.01.xx	Reworked samples/boilerplates for R10 release.
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

#include <shinobi.h>
#include <ac.h>
#include <a64thunk.h>
#include <am.h>

#include "bpamsetup.h"
#include "bpamstream.h"
#include "bpbuttons.h"
#include "bpprintf.h"

//-----------------------------------------------------------------------------

#ifdef __GNUC__
#define MAINFUNC						int main
#define RETURN							return (0)
#define ABORT							acASEBRK(1)
#define SHINOBI_WORKAROUND				shinobi_workaround()
#else
#define MAINFUNC						void main
#define RETURN							return
#define ABORT							acASEBRK(1)
#define SHINOBI_WORKAROUND
#endif

//-----------------------------------------------------------------------------

#define USE_ACTRANSFER_DMA

#if defined(USE_ACTRANSFER_DMA)
#define TRANSFER_MODE					AC_TRANSFER_DMA
#else
#define TRANSFER_MODE					AC_TRANSFER_CPU
#endif

#define STRM_FILENAME_1					"s_0drum.str"
#define STRM_FILENAME_2					"s_2sybass.str"
#define STRM_FILENAME_3					"s_3clguit.str"
#define STRM_FILENAME_4					"s_4fuzzgui.str"
#define STRM_FILENAME_5					"s_5wahgui.str"
#define STRM_FILENAME_6					"s_6rhodep.str"
#define STRM_FILENAME_7					"s_7vocal.str"
#define STRM_FILENAME_1M				"m_0drum.str"
#define STRM_FILENAME_2M				"m_2sybass.str"
#define STRM_FILENAME_3M				"m_3clguit.str"
#define STRM_FILENAME_4M				"m_4fuzzgui.str"
#define STRM_FILENAME_5M				"m_5wahgui.str"
#define STRM_FILENAME_6M				"m_6rhodep.str"
#define STRM_FILENAME_7M				"m_7vocal.str"
#define STRM_COUNT						4
#define STRM_MAX						7

#define STRM_VOLUME						127

#define STRM_HEADERBUFFER_SIZE			AM_FILE_BLOCK_SIZE
#define STRM_PLAYBUFFER_MONO_SIZE		16384
#define STRM_PLAYBUFFER_STEREO_SIZE		(STRM_PLAYBUFFER_MONO_SIZE * 2)
#define STRM_TRANSFERBUFFER_SIZE		STRM_PLAYBUFFER_STEREO_SIZE
#define STRM_TRANSFERBUFFER_COUNT		2
	
typedef struct
{
	KTBOOL play;
	KTU32 x;
	KTU32 y;
	KTS8 *fileName;
	KTU32 playCount;
	KTU32 failCount;
	KTU32 volume;
	AM_STREAM *stream;
	KTU32 *headBuffer;
	KTU32 headBufferSize;
	KTU32 *xferBuffer;
	KTU32 xferBufferSize;
	KTU32 *playBuffer;
	KTU32 playBufferSize;
} ASYNC_STREAM_STATE;

ASYNC_STREAM_STATE strm[STRM_MAX] =
{
	{
		KTTRUE, INFO_4_X, INFO_4_Y,
		STRM_FILENAME_2, 0, 0, STRM_VOLUME, KTNULL,
		KTNULL, STRM_HEADERBUFFER_SIZE,
		KTNULL, (STRM_TRANSFERBUFFER_SIZE * STRM_TRANSFERBUFFER_COUNT),
		KTNULL, STRM_PLAYBUFFER_STEREO_SIZE
	},
	{
		KTTRUE, INFO_5_X, INFO_5_Y,
		STRM_FILENAME_4, 0, 0, STRM_VOLUME, KTNULL,
		KTNULL, STRM_HEADERBUFFER_SIZE,
		KTNULL, (STRM_TRANSFERBUFFER_SIZE * STRM_TRANSFERBUFFER_COUNT),
		KTNULL, STRM_PLAYBUFFER_STEREO_SIZE
	},
	{
		KTTRUE, INFO_6_X, INFO_6_Y,
		STRM_FILENAME_5, 0, 0, STRM_VOLUME, KTNULL,
		KTNULL, STRM_HEADERBUFFER_SIZE,
		KTNULL, (STRM_TRANSFERBUFFER_SIZE * STRM_TRANSFERBUFFER_COUNT),
		KTNULL, STRM_PLAYBUFFER_STEREO_SIZE
	},
	{
		KTTRUE, INFO_7_X, INFO_7_Y,
		STRM_FILENAME_7, 0, 0, STRM_VOLUME, KTNULL,
		KTNULL, STRM_HEADERBUFFER_SIZE,
		KTNULL, (STRM_TRANSFERBUFFER_SIZE * STRM_TRANSFERBUFFER_COUNT),
		KTNULL, STRM_PLAYBUFFER_STEREO_SIZE
	}
};

//-----------------------------------------------------------------------------

void setupNinja(void);
void applyDelta(ASYNC_STREAM_STATE *strmState, KTBOOL toggleStop);
KTBOOL StreamSetup(ASYNC_STREAM_STATE *stateStream);
void ReplayStream(ASYNC_STREAM_STATE *stateStream);

// ----------------------------------------------------------------------------

MAINFUNC(void)
{
	KTU32 i;
	SYS_RTC_DATE start;
	SYS_RTC_DATE current;
	const PDS_PERIPHERAL *pad;

	SHINOBI_WORKAROUND;
	setupNinja();
	syRtcGetDate(&start);

	// ------------------------------------------------------------------------
	// Setup the AM component
	// ------------------------------------------------------------------------

	acASEBRK(!bpAmSetup(AC_DRIVER_DA, KTFALSE, KTNULL));

	acASEBRK(!acSetTransferMode(TRANSFER_MODE));

	acSystemDelay(500000);

	// ------------------------------------------------------------------------
	// Setup the filesystem
	// ------------------------------------------------------------------------

	acASEBRK(!a64FileInit());
	
	// ------------------------------------------------------------------------
	// Setup the stream(s)
	// ------------------------------------------------------------------------

	for (i = 0; i < STRM_COUNT; i++)
	{
		acASEBRK(!StreamSetup(&strm[i]));
	}

	// ------------------------------------------------------------------------
	// Start the stream(s)
	// ------------------------------------------------------------------------

	for (i = 0; i < STRM_COUNT; i++)
	{
		if (strm[i].play)
		{
			acASEBRK(!bpAmStreamStart(strm[i].stream));
		}
	}

	// ------------------------------------------------------------------------
	// Main loop
	// ------------------------------------------------------------------------

	while (KTTRUE)
	{
		KTU32 daCount;
		KTU32 midiCount;

		bpAmStreamServer();

		syRtcGetDate(&current);
		acDigiPortsAvailable(&daCount, &midiCount);

		bpPrintf(INFO_0_X, INFO_0_Y, "Audio64 AM Stream Sample");
		bpPrintf(INFO_1_X, INFO_1_Y, "Start:  %02d/%02d %02d:%02d:%02d",
										start.month,
										start.day,
										start.hour,
										start.minute,
										start.second);
		bpPrintf(INFO_2_X, INFO_2_Y, "Current:%02d/%02d %02d:%02d:%02d",
										current.month,
										current.day,
										current.hour,
										current.minute,
										current.second);
		bpPrintf(INFO_3_X, INFO_3_Y, "free:  da:%02u  midi:%02u", daCount, midiCount);
		for (i = 0; i < STRM_COUNT; i++)
		{
			bpPrintf(strm[i].x, strm[i].y,
				"mode:%02u  operation:%02u  transfer:%04u",
				strm[i].stream->mode, strm[i].stream->operation,
				strm[i].stream->transferCount);
		}
		bpPrintf(INFO_8_X,INFO_8_Y, "[MUTE/UNMUTE == <button>]");
		bpPrintf(INFO_9_X,INFO_9_Y, "[STOP/START == <LTRIGGER> + <button>]");
		
		pad = pdGetPeripheral(PDD_PORT_A0);
		if ((pad->on & PAD_SOFTRESET) == PAD_SOFTRESET)
		{
			break;
		}
		if (pad->press & PAD_A_BUTTON)
		{
			applyDelta(&strm[0], (KTBOOL)(pad->on & PAD_L_TRIGGER));
		}
		if (pad->press & PAD_B_BUTTON)
		{
			applyDelta(&strm[1], (KTBOOL)(pad->on & PAD_L_TRIGGER));
		}
		if (pad->press & PAD_X_BUTTON)
		{
			applyDelta(&strm[2], (KTBOOL)(pad->on & PAD_L_TRIGGER));
		}
		if (pad->press & PAD_Y_BUTTON)
		{
			applyDelta(&strm[3], (KTBOOL)(pad->on & PAD_L_TRIGGER));
		}
		for (i = 0; i < STRM_COUNT; i++)
		{
			if (bpAmStreamPlaying(strm[i].stream))
			{
				acASEBRK(!bpAmStreamSetVolume(strm[i].stream,
													strm[i].volume));
			}
		}

		for (i = 0; i < STRM_COUNT; i++)
		{
			if (strm[i].play && bpAmStreamDone(strm[i].stream))
			{
				ReplayStream(&strm[i]);
			}
		}

		njWaitVSync();
	}

	(void)acSetTransferMode(AC_TRANSFER_CPU);

	// ------------------------------------------------------------------------
	// Shutdown the AM component
	// ------------------------------------------------------------------------

	bpAmShutdown();

	// a chance for one last look around
	ABORT;
}

// ----------------------------------------------------------------------------

void applyDelta(ASYNC_STREAM_STATE *strmState, KTBOOL toggleStop)
{
	if (toggleStop)
	{
		KTBOOL update = KTTRUE;
		if (strmState->play)
		{
			update = bpAmStreamPlaying(strmState->stream);
			if (update)
			{
				acASEBRK(!amStreamStop(strmState->stream));
			}
		}
		if (update)
		{
			strmState->play = (strmState->play) ? KTFALSE : KTTRUE;
		}
	}
	else
	{
		strmState->volume = (strmState->volume) ? 0 : STRM_VOLUME;
	}
}

// ----------------------------------------------------------------------------

void ReplayStream(ASYNC_STREAM_STATE *stateStream)
{
	if (!bpAmStreamDestroy(stateStream->stream))
	{
		++stateStream->failCount;
	}
	else
	{
		stateStream->stream = bpAmStreamPrepareFile(stateStream->fileName,
			stateStream->volume, AM_PAN_CENTER, stateStream->headBuffer,
			stateStream->xferBuffer, stateStream->xferBufferSize,
			stateStream->playBuffer, stateStream->playBufferSize, KTNULL);

		if (!stateStream->stream)
		{
			++stateStream->failCount;
		}
		else if (!bpAmStreamStart(stateStream->stream))
		{
			++stateStream->failCount;
		}
		else
		{
			++stateStream->playCount;
		}
	}
}

// ----------------------------------------------------------------------------

KTBOOL StreamSetup(ASYNC_STREAM_STATE *stateStream)
{
	// ------------------------------------------------------------------------
	// get the necessary buffers lined up for the stream
	//
	// allocate memory for the play buffers.
	//
	// transfer buffer MUST! be in aica memory and 32 byte aligned or file
	// reads will fail with the GDFS file system.
	// ------------------------------------------------------------------------

	if (!amHeapAlloc(&stateStream->playBuffer,stateStream->playBufferSize,
			32, AM_PURGABLE_MEMORY, KTNULL))
	{
		return (KTFALSE);
	}

	// ------------------------------------------------------------------------
	// allocate memory for the transfer buffers.
	//
	// transfer buffer MUST! be in sh4 memory and 32 byte aligned or file reads
	// will fail with the GDFS file system.
	// ------------------------------------------------------------------------

	stateStream->xferBuffer =
				(volatile KTU32 *)syMalloc(stateStream->xferBufferSize);
	if (!stateStream->xferBuffer)
	{
		return (KTFALSE);
	}

	// ----------------------------------------------------------------------------------------------
	// allocate memory for the header buffers.
	//
	// header buffer MUST! be in sh4 memory and 32 byte aligned or file reads
	// will fail with the GDFS file system.
	// ----------------------------------------------------------------------------------------------

	stateStream->headBuffer =
				(volatile KTU32 *)syMalloc(stateStream->headBufferSize);
	if (!stateStream->headBuffer)
	{
		return (KTFALSE);
	}

	// ------------------------------------------------------------------------
	// prepare the stream
	// ------------------------------------------------------------------------

	stateStream->stream = bpAmStreamPrepareFile(stateStream->fileName,
		stateStream->volume, AM_PAN_CENTER, stateStream->headBuffer,
		stateStream->xferBuffer, stateStream->xferBufferSize,
		stateStream->playBuffer, stateStream->playBufferSize, KTNULL);
	if(!stateStream->stream)
	{
		return (KTFALSE);
	}

	return (KTTRUE);
}

//-----------------------------------------------------------------------------

void setupNinja(void)
{
	njSetBorderColor(0x00000000);
	switch (syCblCheckCable())
	{
		case SYE_CBL_CABLE_VGA:
			sbInitSystem(NJD_RESOLUTION_VGA, NJD_FRAMEBUFFER_MODE_RGB565, 1);
			break;
		default:
		case SYE_CBL_CABLE_NTSC:
			sbInitSystem(NJD_RESOLUTION_640x480_NTSCNI,
											NJD_FRAMEBUFFER_MODE_RGB565, 1);
			break;
	}
	njInitVertexBuffer(20000, 0, 20000, 0, 0);
	njInitPrint(NULL, 0, NJD_TEXFMT_ARGB_1555);
	njSetBackColor(0x00000000, 0x00000000, 0x000000FF);
	njPrintSize(12);	
}
