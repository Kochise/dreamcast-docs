// -------------------------------------------------------------------------
// amstrhdr.h
//
// Author: Ralph "Cooksey" Thomas
//
// This contains the header for streamed audio files
//
// Tabs: 4
//
// Rev:	09/08/98	File Originated
//
//		11/16/98	Updated header format for multi track play...
//
//		12/03/98	Upped leadout size from 2 sectors to 4 sectors
//
//		02/04/99	renamed amstream.h and moved into the am lib tree
//
//		04/20/99	Added the interruptsTillEnd members to the header and 
//					the tracks.
//					The interruptsTillEnd in the track is how may irqs till 
//					the end of that tracks data, it includes the leadin but
//					not the leadout.
//					The global interruptsTillEnd includes the leadin and
//					leadout and is the length of the longest track.
// -------------------------------------------------------------------------

#ifndef _AM_STREAM_HEADER_H
#define _AM_STREAM_HEADER_H

#define AM_MAX_STREAMS					8					
#define AM_STREAM_MAX_TRACKS			16
#define AM_STREAM_BLOCK_SIZE			2048
#define AM_STREAM_EXTENDED_HEADER_SIZE	2048

#ifdef WIN32
typedef unsigned long	KTU32;
#endif

typedef struct
{
KTU32 size;
KTU32 channels;
KTU32 interruptsTillEnd;
}AM_STREAM_FILE_TRACK;

typedef struct
{
KTU32					numberOfTracks;
KTU32					sampleRate;
KTU32					bitDepth;
KTU32					halfPlayBufferSizeInBytes;
KTU32					interruptsTillEnd;
AM_STREAM_FILE_TRACK	track[AM_STREAM_MAX_TRACKS];
}AM_STREAM_FILE_HEADER;

typedef AM_STREAM_FILE_HEADER * AM_STREAM_FILE_HEADER_PTR;

#endif // end of _AM_STREAM_HEADER_H

// -------------------------------------------------------------------------------------------
// end of file: amstrhdr.h
// -------------------------------------------------------------------------------------------
