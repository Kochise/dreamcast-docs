/*-----------------------------------------------------------------------------
|
|	undump.c    BiffView external file converter.
|
| 
| 
|
-----------------------------------------------------------------------------*/

#include "undump.h"
#include <stdlib.h>
#include <string.h>

FARPROC lpfnCallBack;

BYTE FAR *lprgb;
BYTE FAR *lpbCur;
int cbCur;
int cbCurMax;
int cRtEOF;  // Count of EOF's pending...
unsigned long lcbFile;
unsigned long lcbCur;
WORD cbRecordCur;
BYTE FAR *lprgbRecordData;

char szBIFF5[] = "XLStorage file" ;
char szOther[] = "00000: [BOF]" ;

// "Peek" at the next character without advancing...
#define ChPeekNext() (*lpbCur)

/*-----------------------------------------------------------------------------
|	FFillBuffer
|	
|	Fill the local buffer -- we're using a local buffer and grabbing a chunk of
|	data at a time rather than calling back to XL for EACH character...
|
|	Arguments:
|	
|	Returns: TRUE if buffer was filled
|	
|	Keywords:
|	
-----------------------------------------------------------------------------*/
BOOL FFillBuffer()
{
	unsigned long lcbLeft = lcbFile - lcbCur;
	
	cbCurMax = CbFromFile(lprgb, (unsigned)min(cbBufSize, lcbLeft));
	if (cbCurMax)
		{
		lpbCur = lprgb;
		cbCur = 0;
		return(fTrue);
		}
	return(fFalse);
}


/*-----------------------------------------------------------------------------
|	ChGetNext
|	
|	Get the next character from the buffer, advancing the current position and
|	refilling the buffer if necessary.
|
|	Arguments:
|	
|	Returns: the character
|	
|	Keywords:
|	
-----------------------------------------------------------------------------*/
char ChGetNext()
{
	char chT;

	chT = *lpbCur++;
	cbCur++;
	lcbCur++;
	if (cbCur == cbCurMax && lcbCur < lcbFile)
		{
		if (!FFillBuffer())
			return 0;
		}
	
	return chT;
}


/*-----------------------------------------------------------------------------
|	BGetNext
|	
|	Get the next "byte" in the buffer (converting from Hex-ASCII to the actual
|	value)
|
|	Arguments:
|	
|	Returns: the byte
|	
|	Keywords:
|	
-----------------------------------------------------------------------------*/
BYTE BGetNext()
{
	char chT;
	char bVal;
	
	if ((chT = ChGetNext()) == 0)
		{
		return(0);
		}
	
	if (!IsXDigit(chT))
		{
		return(0);
		}
	
	bVal = BFromXDigit(chT) << 4;
	chT = ChGetNext();
	if (!IsXDigit(chT))
		{
		return(0);
		}

	bVal |= BFromXDigit(chT);

	// Skip the space after...
	if (ChGetNext() != ' ')
		return(0);

	return(bVal);
}


/*-----------------------------------------------------------------------------
|	WGetNext
|	
|	Get the next "word" in the buffer (converting from Hex-ASCII to the actual
|	value)
|
|	Arguments:
|	
|	Returns: the word
|	
|	Keywords:
|	
-----------------------------------------------------------------------------*/
WORD WGetNext()
{
	int wVal;

	wVal = BGetNext();
	return (wVal | (BGetNext() << 8));
}


/*-----------------------------------------------------------------------------
|	SkipLine
|	
|	Skip to the beginning of the next "line" in the buffer
|
|	Arguments:
|	
|	Returns:
|	
|	Keywords:
|	
-----------------------------------------------------------------------------*/
void SkipLine()
{
	char chT;

	chT = ChGetNext();
	while (chT != 0 && chT != 13)
		{
		chT = ChGetNext();
		}
	if (ChPeekNext() == 10)
		ChGetNext();
}


/*-----------------------------------------------------------------------------
|	SkipOffset
|	
|	Skip "offset" marker at beginning of line
|
|	Arguments:
|	
|	Returns:
|	
|	Keywords:
|	
-----------------------------------------------------------------------------*/
void SkipOffset()
{
	int cch;

	for (cch = 0; cch < cbOffset; cch++, ChGetNext()) ;
}


/*-----------------------------------------------------------------------------
|	FlprgbEqrgb
|	
|	Compares the file recognition strings
|
|	Arguments:
|		lprgb - pointer to string
|		rgb	  - pointer to comparison string
|		cb	  - length of strings
|	
|	Returns: TRUE if the strings are identical
|	
|	Keywords:
|	
-----------------------------------------------------------------------------*/
BOOL FlprgbEqrgb(lprgb, rgb, cb)
BYTE FAR *lprgb;
BYTE *rgb;
int cb;
{
	int cbCur;
	
	for (cbCur = 0; cbCur < cb; cbCur++, lprgb++, rgb++)
		{
		if (*lprgb != *rgb)
			{
			return fFalse;
			}
		}
	return fTrue;
}


/*-----------------------------------------------------------------------------
|	CleanUp
|	
|	Frees the buffer memory
|
|	Arguments:
|
|	Returns:
|	
|	Keywords:
|	
-----------------------------------------------------------------------------*/
void CleanUp()
{
	if (lprgb != NULL)
		FreeCb(lprgb, cbBufSize);
	if (lprgbRecordData != NULL)	
		FreeCb(lprgbRecordData, cbBiffMax);
}


/*-----------------------------------------------------------------------------
|	IsFormatOk
|	
|	Checks the file recognition strings	to determine if the file format
|	is correct. This is the first function that MS Excel calls.
|
|	Arguments:
|		lpefcp - pointer to EFCP structure
|	
|	Returns: TRUE if the converter recognizes the file format
|			 FALSE if converter does not recognize the format (in which
|					case MS Excel does not call the converter again)
|	
|	Keywords:
|	
-----------------------------------------------------------------------------*/
short FAR PASCAL IsFormatOk (lpefcp)
EFCP FAR *lpefcp;
{
	lpfnCallBack = lpefcp->lpfn;  // store the callback function pointer
    
	if (*lpefcp->lprgb == szBIFF5[0]) {
		return(FlprgbEqrgb(lpefcp->lprgb, (BYTE *)szBIFF5, cbSzBIFF5));
	}
	else {
		return(FlprgbEqrgb(lpefcp->lprgb, (BYTE *)szOther, cbSzOther));
	}
}


/*-----------------------------------------------------------------------------
|	RtGetNextRecord
|	
|	Get the next record	type (rt)
|
|	Arguments:
|	
|	Returns: rt if successful; -1 otherwise
|	
|	Keywords:
|	
-----------------------------------------------------------------------------*/
int RtGetNextRecord()
{
	WORD rt;
	WORD cb;
	BYTE FAR *lpbDataCur;

	// In theory we're currently at the beginning of a descriptive line...
	SkipLine();

	// Now skip the "offset" portion of the data line:
	SkipOffset();

	// Now, if the file isn't corrupt, we're looking at a word, and that
	// word is the RT...
	rt = WGetNext();
	if ((cb = cbRecordCur = WGetNext()) > cbBiffMax)
		{
		CleanUp();
		return(-1);
		}
		
	lpbDataCur = lprgbRecordData;

	while (cb--)
		{
		if (ChPeekNext() == ' ')
			{
			SkipLine();
			SkipOffset();
			}
		*lpbDataCur++ = BGetNext();
		}
	if (ChPeekNext() != ' ' && ChPeekNext() != '-')
		{
		CleanUp();
		return(-1);
		}
		
	SkipLine();
	return(rt);
}


/*-----------------------------------------------------------------------------
|	WSkipRecord
|	
|	Skips records that the converter does not handle
|
|	Arguments:
|		rt - record type
|	
|	Returns: 	wSkip if this is a record to skip
|				wKeep if this is a record to convert
|				wAbort is the conversion is finished
|	Keywords:
|	
-----------------------------------------------------------------------------*/
WORD WSkipRecord(rt)
WORD rt;
{
	rt &= wBiff2Mask;

#ifdef CRTSKIP
	// Check for embedded charts and skip them...
	if (rt == rtObj && *((WORD *)(lprgbRecordData + cbOToffset)) == otChart)
		{
		// Not only do we want to skip this, but the next object should be an
		// embedded chart and we should skip the whole thing...
		while (RtGetNextRecord() != rtEOF);
		return wSkip;
		}
#endif
		
	// Now we can skip entire ranges of rt... (seperate ifs for readability)
	if (rt >= rtToolBar && rt <= rtWriteAccess)
		return wSkip;

	if (rt >= rtUncalced && rt <= rtTemplate)
		return wSkip;

	if (rt >= rtFnProto && rt <= rtDocDim)
		return wSkip;

	if (rt >= rtChartColors && rt <= rtMaskImData)
		return wSkip;

	if (rt >= rtToolbarHdr && rt <= rtUDDesc)
		return wSkip;

	if (rt >= rtInterfaceHdr
#ifndef CRTSKIP
		&& rt < rtChartMin
#endif
		)
		return wSkip;

#ifndef CRTSKIP
	if (rt > rtDebugVers)
		return wSkip;
#endif
	
	// A few other miscellaneous rts we don't convert...
	// rtEOF and rtBundleSheet are special cases -- want to keep track of 
	// how many of them we've processed...
	switch(rt)
		{
#ifndef CRTSKIP
	case rtObj:
		if (*((WORD *)(lprgbRecordData + cbOToffset)) == otChart)
			cRtEOF++;
		break;
#endif
	case rtEOF:
		cRtEOF--;
		if (cRtEOF == 0)
			{
			CleanUp();  // We're done...
			if (cbRecordCur != 0)
				return(wAbort);
			}
		break;
	case rtBundleSheet:
		cRtEOF++;
		break;
	case rtFilePass:
		return wAbort;
	case rtProtect:
	case rtPassword:
	case rtWnProtect:
	case rtBackup:
	case rtWriteProt:
	case rtAddIn:
		return wSkip;
		}

	return wKeep;
}


/*-----------------------------------------------------------------------------
|	RtNextRecord
|	
|	Returns the record type (rt) of the next record
|
|	Arguments:
|	
|	Returns: 	wSkip if this is a record to skip
|				wKeep if this is a record to convert
|				wAbort is the conversion is finished
|	Keywords:
|	
-----------------------------------------------------------------------------*/
short FAR PASCAL RtNextRecord()
{
	WORD rtCur;
	WORD w;
	
	if (lprgbRecordData == NULL || lprgb == NULL)
		{
		CleanUp();
		return(-1);
		}
	do
		{
		rtCur = RtGetNextRecord();
		if ((w = WSkipRecord(rtCur)) == wAbort)
			return(-1);
		}
	while (w == wSkip);

	return(rtCur);
}


/*-----------------------------------------------------------------------------
|	CbNextRecord
|	
|	Returns the length of the next record
|
|	Arguments:
|	
|	Returns:	length (cb) of next record	
|
|	Keywords:
|	
-----------------------------------------------------------------------------*/
short FAR PASCAL CbNextRecord ()
{
	return(cbRecordCur);
}


/*-----------------------------------------------------------------------------
|	DataNextRecord
|	
|	Returns the record data	in lpefcp->lprgb
|
|	Arguments:
|		lpefcp - pointer to EFCP structure
|	
|	Returns:	percentage-complete integer (0 to 100 decimal)	
|
|	Keywords:
|	
-----------------------------------------------------------------------------*/
short FAR PASCAL DataNextRecord(lpefcp)
EFCP FAR *lpefcp;
{
	bltbh(lprgbRecordData, lpefcp->lprgb, cbRecordCur);
	return((short)((lcbCur * 100)/lcbFile));
}


/*-----------------------------------------------------------------------------
|	AbortLoad
|	
|	Terminates the file converter load
|
|	Arguments:
|	
|	Returns:	
|
|	Keywords:
|	
-----------------------------------------------------------------------------*/
short FAR PASCAL AbortLoad()
{
	CleanUp();
	return(fTrue);
}


/*-----------------------------------------------------------------------------
|	XlConverter
|	
|	File converter entry point
|
|	Arguments:
|		iAction - command ID (opcode)
|		lpefcp - pointer to EFCP structure
|
|	Returns:	depends on iAction	
|
|	Keywords:
|	
-----------------------------------------------------------------------------*/
short FAR PASCAL XlConverter(iAction, lpefcp)
short iAction;
EFCP FAR *lpefcp;
{
	switch(iAction)
		{
	default:
		break;
	case iActionIsFormatOk:
		return(IsFormatOk(lpefcp));
	case iActionInitLoad:
		return(InitLoad(lpefcp));
	case iActionRtNextRecord:
		return(RtNextRecord());
	case iActionCbNextRecord:
		return(CbNextRecord());
	case iActionDataNextRecord:
		return(DataNextRecord(lpefcp));
	case iActionAbortLoad:
		return(AbortLoad());
		}
}

/*-----------------------------------------------------------------------------
|	InitLoad
|	
|	File converter initialization
|
|	Arguments:
|		lpefcp - pointer to EFCP structure
|
|	Returns:
|		true is initialization is successful
|		false if a fatal error occurs (causes MS Excel to call
|				XlConverter function with am iActionAbortLoad opcode)
|
|	Keywords:
|	
-----------------------------------------------------------------------------*/
short FAR PASCAL InitLoad(lpefcp)
EFCP FAR * lpefcp;
{
	short cbBufSizeAlloc, cbRecDataAlloc;
	lcbFile = lpefcp->lcb;
	lcbCur = 0;
	cbBufSizeAlloc = AllocCb((BYTE FAR * FAR *)&lprgb, cbBufSize);
	cbRecDataAlloc = AllocCb((BYTE FAR * FAR *)&lprgbRecordData, cbBiffMax);
	
	if ((cbBufSizeAlloc != cbBufSize) || (cbRecDataAlloc != cbBiffMax))
		{
		return(fFalse);
		}

	// Just to make sure...
	StreamSetpos(0);
	// Fill buffer with first block...
	if (!FFillBuffer())
		return(fFalse);

	// Peek at first character to see if it's a BIFF5 or an earlier one...
	if (ChPeekNext() == szBIFF5[0])
		{
		// If it's BIFF5, skip the first 2 lines...
		SkipLine();
		SkipLine();
		}
	// We expect to see at least one of these...
	cRtEOF = 1;
	
	return(fTrue);
}
