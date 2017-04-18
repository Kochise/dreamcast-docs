//-----------------------------------------------------------------------------
//
//	FILE:		bpamstream.c
//
//	DESC:		Boilerplate for Audio64 AM layer streaming.
//
//	HISTORY:	2000.01.xx	Reworked samples/boilerplates for R10 release.
//
//-----------------------------------------------------------------------------
//	COPYRIGHT (C) SEGA OF AMERICA DREAMCAST, INC. 1998, 1999, 2000
//	All rights reserved.
//
//	Information and source code samples contained herein are provided "as-is",
//	without representations or warranties, and are subject to change without
//	notice.
//
//	SEGA OF AMERICA DREAMCAST, INC. cannot support modifications or derivative
//	works created from the sample source code provided. Developers may use,
//	reproduce, and modify portions or entire sections of the sample source
//	code for the purposes of creating Dreamcast applications.
//
//	Sample source code contained herein may not be appropriate for use under
//	all circumstances. Please consult Developer documentation provided along
//	with your Dreamcast unit for additional information and suggestions.
//-----------------------------------------------------------------------------

#include "bpamstream.h"
#include "bpprintf.h"

//-----------------------------------------------------------------------------

typedef struct
{
	KTBOOL allocated;
	AM_STREAM stream;
} BPAM_STREAM;

BPAM_STREAM streamInstances[A64_FILE_MAX_HANDLES + 1] =
{
	{KTFALSE, { 0 }},
	{KTFALSE, { 0 }},
	{KTFALSE, { 0 }},
	{KTFALSE, { 0 }},
	{KTFALSE, { 0 }},
	{KTFALSE, { 0 }},
	{KTFALSE, { 0 }},
	{KTFALSE, { 0 }},
	{KTFALSE, { 0 }}
};

AM_STREAM *activeList[A64_FILE_MAX_HANDLES + 1] = { KTNULL };

//-----------------------------------------------------------------------------

static KTBOOL bpAmStreamInstanceToIndex(AM_STREAM *theStream,
	KTU32 *index);

//	add an instance to the active list
static KTBOOL bpAmStreamAddInstance(AM_STREAM *theStream);
//	remove an instance from the active list
static KTBOOL bpAmStreamRemoveInstance(AM_STREAM *theStream);
//	free a instance
static KTBOOL bpAmStreamFreeInstance(AM_STREAM *theStream);
//	allocate an instance
static KTBOOL bpAmStreamAllocateInstance(AM_STREAM **theStream);

//-----------------------------------------------------------------------------
//	KTBOOL bpAmStreamDone(AM_STREAM *theStream)
//
//	is it done?
//-----------------------------------------------------------------------------

KTBOOL bpAmStreamDone(AM_STREAM *theStream)
{
	KTBOOL isDone = KTFALSE;
	return (amStreamIsDone(theStream, &isDone) && isDone);
}

//-----------------------------------------------------------------------------
//	KTBOOL bpAmStreamIdle(AM_STREAM *theStream)
//
//	is it idle?
//-----------------------------------------------------------------------------

KTBOOL bpAmStreamIdle(AM_STREAM *theStream)
{
	KTBOOL isIdle = KTFALSE;
	return (amStreamIsIdle(theStream, &isIdle) && isIdle);
}

//-----------------------------------------------------------------------------
//	KTBOOL bpAmStreamPlaying(AM_STREAM *theStream)
//
//	is it playing?
//-----------------------------------------------------------------------------

KTBOOL bpAmStreamPlaying(AM_STREAM *theStream)
{
	KTBOOL isPlaying = KTFALSE;
	return (amStreamIsPlaying(theStream, &isPlaying) && isPlaying);
}

//-----------------------------------------------------------------------------
//	KTBOOL bpAmStreamStop(AM_STREAM *theStream)
//
//	Stop a stream.
//-----------------------------------------------------------------------------

KTBOOL bpAmStreamStop(AM_STREAM *theStream)
{
	return (amStreamStop(theStream));
}
 
//-----------------------------------------------------------------------------
//	KTBOOL bpAmStreamDestroy(AM_STREAM *theStream)
//
//	stop, close, release all assets, and remove from server queue.
//-----------------------------------------------------------------------------

KTBOOL bpAmStreamDestroy(AM_STREAM *theStream)
{
	amStreamStop(theStream);

	//	if voices are left due to an application programming error we MUST
	//	release them or lose them. they should be gone by this point but a
	//	call to release voices where none are allocated does no harm.
	amStreamReleaseVoiceChannels(theStream);

	amStreamClose(theStream);

	//	remove the instance from the server queue.
	if (!bpAmStreamRemoveInstance(theStream))
	{
		return (KTFALSE);
	}

	//	free the instance.
	if (!bpAmStreamFreeInstance(theStream))
	{
		return (KTFALSE);
	}
	
	return (KTTRUE);
}

//-----------------------------------------------------------------------------
//	KTBOOL bpAmStreamSetVolume(AM_STREAM_PTR theStream, KTU32 volume)
// 
//	set the volume on a stream.
//-----------------------------------------------------------------------------

KTBOOL bpAmStreamSetVolume(AM_STREAM *theStream, KTU32 volume)
{
	return (amStreamSetVolume(theStream, volume, 0));
}

//-----------------------------------------------------------------------------
//	KTBOOL bpAmStreamInstanceToIndex(AM_STREAM *theStream,
//		KTU32 *index)
//
//	get the pool index based on the instance address.
//-----------------------------------------------------------------------------

static KTBOOL bpAmStreamInstanceToIndex(AM_STREAM *theStream,
	KTU32 *index)
{
	KTU32 i;
	for (i = 0; i < A64_FILE_MAX_HANDLES; i++)
	{
		if (theStream == &streamInstances[i].stream)
		{
			*index = i;
			return (KTTRUE);
		}
	}
	return (KTFALSE);
}

//-----------------------------------------------------------------------------
//	KTBOOL bpAmStreamAllocateInstance(AM_STREAM **theStream)
//
//	get a new stream instance from the pool.
//-----------------------------------------------------------------------------

static KTBOOL bpAmStreamAllocateInstance(AM_STREAM **theStream)
{
	KTU32 i;
	for (i = 0; i < A64_FILE_MAX_HANDLES; i++)
	{
		if (!streamInstances[i].allocated)
		{
			streamInstances[i].allocated = KTTRUE;
			memset(&streamInstances[i].stream, 0,
										sizeof(streamInstances[i].stream));
			*theStream = &streamInstances[i].stream;
			return (KTTRUE);
		}
	}
	return (KTFALSE);
}

//-----------------------------------------------------------------------------
//	KTBOOL bpAmStreamFreeInstance(AM_STREAM *theStream)
// 
//	release the instance memory back to the pool.
//-----------------------------------------------------------------------------

KTBOOL bpAmStreamFreeInstance(AM_STREAM *theStream)
{
	KTU32 index;
	if (bpAmStreamInstanceToIndex(theStream, &index))
	{
		streamInstances[index].allocated = KTFALSE;
		return (KTTRUE);
	}
	return KTFALSE;
}

//-----------------------------------------------------------------------------
//	KTBOOL bpAmStreamAddInstance(AM_STREAM *theStream)
//
//	add an instance to the active list.
//-----------------------------------------------------------------------------

KTBOOL bpAmStreamAddInstance(AM_STREAM *theStream)
{
	KTU32 i;
	for (i = 0; i < A64_FILE_MAX_HANDLES; i++)
	{
		if (!activeList[i])
		{
			activeList[i] = theStream;
			return (KTTRUE);
		}
	}
	return (KTFALSE);
}

//-----------------------------------------------------------------------------
//	KTBOOL bpAmStreamRemoveInstance(AM_STREAM *theStream)
//
//	remove an instance from the active list.
//-----------------------------------------------------------------------------

KTBOOL bpAmStreamRemoveInstance(AM_STREAM *theStream)
{
	KTU32 i;
	for (i = 0; i < A64_FILE_MAX_HANDLES; i++)
	{
		if ((activeList[i] == theStream) && theStream)
		{
			activeList[i] = KTNULL;
			return (KTTRUE);
		}
	}
	return (KTFALSE);
}

//-----------------------------------------------------------------------------
//	void bpAmStreamServer(void)
//
//	service the stream transfer/play buffers.
//-----------------------------------------------------------------------------

volatile KTU32 gWaitStreamCount = 0;

void bpAmStreamServer(void)
{
	KTU32 i;
	for (i = 0; i < A64_FILE_MAX_HANDLES; i++)
	{
		if (activeList[i])
		{
			//	TODO:	You might want to at least add some form of minimal
			//			error handling here.
			if (!amStreamServer(activeList[i]))
			{
				gWaitStreamCount++;
			}
		}
	}
}

//-----------------------------------------------------------------------------
//	AM_STREAM *bpAmStreamPrepareFile(KTSTRING filename,
//		KTU32 volume, KTU32 pan, KTU32 *headerBuffer, KTU32 *transferBuffer,
//		KTU32 transferBufferSize, KTU32 *playBuffer, KTU32 playBufferSize,
//		AM_USER_CALLBACK userCallback)
//
//	prepare stream for activation
//-----------------------------------------------------------------------------

AM_STREAM *bpAmStreamPrepareFile(KTSTRING filename,
	KTU32 volume, KTU32 pan, KTU32 *headerBuffer, KTU32 *transferBuffer,
	KTU32 transferBufferSize, KTU32 *playBuffer, KTU32 playBufferSize,
	AM_USER_CALLBACK userCallback)
{
	AM_STREAM *theStream;
	KTU32 index;

	//	setup an instance
	if (!bpAmStreamAllocateInstance(&theStream))
	{
		return (KTNULL);
	}

	if (!bpAmStreamInstanceToIndex(theStream, &index))
	{
		return (KTNULL);
	}

	//	initialize the stream object for a file
	if (!amStreamInitFile(theStream, filename))
	{
		bpDebugf("amStreamInitFile(theStream, ...) failed\n");
		return (KTNULL);
	}

	//	set the transfer/play buffers and sizes
	if (!amStreamSetBuffers(theStream, transferBuffer, transferBufferSize,
			playBuffer, playBufferSize))
	{
		bpDebugf("amStreamSetBuffers(theStream, ...) failed\n");
		return (KTNULL);
	}

	//	set the header buffer (fixed size of SECTOR_SIZE or 2048 bytes)
	if (!amStreamSetHeaderBuffer(theStream, (KTU8*)headerBuffer))
	{
		bpDebugf("amStreamSetHeaderBuffer(theStream, ...) failed\n");
		return (KTNULL);
	}

	//	add the instance to the active list
	if (!bpAmStreamAddInstance(theStream))
	{
		bpDebugf("bpAsyncStreamAddInstance(theStream) failed\n");
		return (KTNULL);
	}
		
	return (theStream);
}

//-----------------------------------------------------------------------------
//	KTBOOL bpAmStreamStart(AM_STREAM *theStream)
//
//	start a stream playing
//-----------------------------------------------------------------------------

KTBOOL bpAmStreamStart(AM_STREAM *theStream)
{
	//	calling bpDebugf while stream is playing causes severe audio artifacts.
	bpDebugf("amStreamStart(theStream) // start the stream\n");

	if (!amStreamStart(theStream))
	{
		bpDebugf("amStreamStart(theStream) failed\n");
		return (KTFALSE);
	}

	return (KTTRUE);
}

