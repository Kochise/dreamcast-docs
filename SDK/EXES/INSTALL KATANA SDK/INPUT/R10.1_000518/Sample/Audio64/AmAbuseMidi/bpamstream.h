//-----------------------------------------------------------------------------
//
//	FILE:		bpamstream.h
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

#if !defined(_BPAMSTREAM_H_)
#define _BPAMSTREAM_H_

#include <ac.h>
#include <a64thunk.h>
#include <am.h>

#ifdef __cplusplus
extern "C" {
#endif

void bpAmAsyncStreamServer(void);

AM_STREAM *bpAmStreamPrepareFile(KTSTRING filename,
	KTU32 volume, KTU32 pan, KTU32 *headerBuffer, KTU32 *transferBuffer,
	KTU32 transferBufferSize, KTU32 *playBuffer, KTU32 playBufferSize,
	AM_USER_CALLBACK userCallback);

KTBOOL bpAmStreamSetVolume(AM_STREAM *theStream, KTU32 volume);

KTBOOL bpAmStreamStart(AM_STREAM *theStream);
KTBOOL bpAmStreamStop(AM_STREAM *theStream);
KTBOOL bpAmStreamDestroy(AM_STREAM *theStream);

void bpAmStreamSetBufferSizes(KTU32 playBufferSize,
			KTU32 transferBufferSize);

KTBOOL bpAmStreamDone(AM_STREAM *theStream);
KTBOOL bpAmStreamIdle(AM_STREAM *theStream);
KTBOOL bpAmStreamPlaying(AM_STREAM *theStream);

#ifdef __cplusplus
}
#endif

#endif	//	_BPAMSTREAM_H_

