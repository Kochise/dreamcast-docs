/*
 *	R T F L I B . H
 *
 *	Definitions for RTF library.
 *
 *  Copyright 1986-1996 Microsoft Corporation. All Rights Reserved.
 */

#ifndef RTFLIB_H
#define RTFLIB_H

#if defined (WIN32) && !defined (_WIN32)
#define _WIN32
#endif

#if defined (_WIN32)
#ifndef _OBJBASE_H_
#include <objbase.h>
#endif
#endif

#if defined (WIN16) || defined (DOS) || defined (DOS16)
#ifndef _COMPOBJ_H_
#include <compobj.h>
#endif
#endif


/*
 * RTFLIB only looks at the first cchBodyTagMax characters of the body tag.
 */
#define cchBodyTagMax	100

typedef struct _RTFSYNCINFO
{
	LONG lBodyCRC;
	LONG lBodyCount;
	LONG lPrefixCount;
	LONG lTrailingCount;
	char szBodyTag[cchBodyTagMax + 2];
} RTFSYNCINFO;

// header for compressed stream
typedef struct _lzfuhdr
{
	ULONG cbSize;		// total number of bytes following this field
	ULONG cbRawSize;	// size before compression
	DWORD dwMagic;		// identifies this as a compressed stream
	DWORD dwCRC;		// CRC-32 of the compressed data for error checking
} LZFUHDR;

// magic number that identifies the stream as a compressed stream
#define dwMagicCompressedRTF 0x75465a4c

// magic number that identifies the stream as a uncompressed stream
#define dwMagicUncompressedRTF 0x414c454d

// array used for CRC calculations
extern const DWORD rgdwCRC[];

/* IMPORTED FUNCTIONS */

/* 
 * LogInvalidCpid
 *
 * Imported callback function for logging code page conversion
 * errors. A stub function is provided if a function is
 * not provided by the project linking with RTFLIB
 *
 * The cpid parameter is the unsupported code page ID.
 *
 */

STDAPI_(void) LogInvalidCpid( ULONG cpid );


/* MAIN RTF ROUTINES */

/*
 * HrTextFromCompressedRTFStream
 *
 * Takes compressed RTF stream (pstmRTF) and returns a wrapper
 * stream (*ppstmText) giving access to the plain text. The text
 * stream supports Read and CopyTo methods.
 * 
 * The pointer psi must be valid until *ppstmText is released.
 * It is updated as *ppstmText is read and is not accurate until
 * all of the text has been read.
 *
 * cpid is the code page for the text stream. It can be any code page
 * INCLUDING unicode. cpid=0 means current system code page. If	the
 * requested code page is not supported, S_FALSE warning may be
 * returned during Read or CopyTo operation.
 */

STDAPI_(HRESULT) HrTextFromCompressedRTFStream(LPSTREAM pstmCompressed,
			LPSTREAM FAR *ppstmText, RTFSYNCINFO FAR *psi, ULONG cpid);


/*
 * HrTextFromCompressedRTFStreamEx()
 *
 * Takes compressed RTF stream (pstmRTF) and returns a wrapper
 * stream (*ppstmText) giving access to the plain text. The text
 * stream supports Read and CopyTo methods.
 * 
 * The pointer psi must be valid until *ppstmText is released.
 * It is updated as *ppstmText is read and is not accurate until
 * all of the text has been read.
 *
 * rgAttachPos is an array of attachment positions. It must be 
 * initialized to the current attachment positions before 
 * HrTextFromCompressedRTFStreamEx() is called. 
 *
 * cAttach must contain the number of elements in rgAttachPos
 *
 * The pointer to rgAttachPos must be valid until *ppstmText is 
 * released. It is updated as *ppstmText is read with the new 
 * attachment positions and is not accurate until all of the text
 * has been read.
 *
 * cpid is the code page for the text stream. It can be any code page
 * INCLUDING unicode. cpid=0 means current system code page. If	the
 * requested code page is not supported, S_FALSE warning may be
 * returned during Read or CopyTo operation.
 */

STDAPI_(HRESULT) HrTextFromCompressedRTFStreamEx( LPSTREAM pstmCompressed,
			LPSTREAM FAR *ppstmText, RTFSYNCINFO FAR *psi, ULONG cpid,
            ULONG cAttach, ULONG FAR *rgAttachPos );

/*
 * HrRTFFromTextStream
 *
 * This function takes a text stream and returns a wrapper 
 * stream interface that converts the text to RTF. The 
 * stream wrapper is read only and only supports  
 * a minimum stream interface.
 *
 * The pointer to rgAttachPos must be valid until *ppstmRTF is 
 * released. This array is used to allow the insertion of 
 * attachment tags in the RTF. 
 *
 * cpid is the code page for the text stream. It is used to 
 * set the charset and font in the RTF. No code page conversion
 * is currently done inside this function.
 */

STDAPI_(HRESULT) HrRTFFromTextStream( LPSTREAM pstmText,
										LPSTREAM *ppstmRTF,										
										ULONG cpid,
										ULONG cAttach,
										ULONG FAR *rgAttachPos );

/*
 * WrapCompressedRTFStream
 *
 * Takes compressed RTF stream (pstmCompressed) and returns a wrapper
 * stream (*ppstmRTF) giving access to uncompressed RTF. The RTF
 * stream can support both Read and Write operations, but to get
 * write access the flag ulFlags must have MAPI_MODIFY bit set.
 *
 * This function also supports reading and writing uncompressed
 * RTF through the use of the STORE_UNCOMPRESSED_RTF flag. For reading,
 * uncompressed RTF streams are detected automatically and thus the 
 * STORE_UNCOMPRESSED_RTF flag only has meaning if MAPI_MODIFY is set.
 * If this flag is used, the data will be written in uncompressed form.
 */

STDAPI_(HRESULT) WrapCompressedRTFStream(LPSTREAM pstmCompressed,
			ULONG ulFlags, LPSTREAM FAR *ppstmRTF);

/*
 * RTFSync
 * RTFSyncCpid
 *
 * Perforts body and RTF synchronization.
 * 
 * If synchronization cannot be performed, RTF properties are removed.
 * It is up to the caller to create new RTF from PR_BODY.
 *
 * cpid is the code page for the body property. It can be any code page
 * EXCLUDING unicode. cpid=0 means current system code page. If	the
 * requested code page is not supported, S_FALSE warning is returned.
 * RTFSync is the same as RTFSyncCpid(cpid=0).
 */

STDAPI_(HRESULT) RTFSync(LPMESSAGE lpMessage, ULONG ulFlags,
			BOOL FAR *pfMessageUpdated);

STDAPI_(HRESULT) RTFSyncCpid(LPMESSAGE lpMessage, ULONG ulFlags,
			BOOL FAR *pfMessageUpdated, ULONG cpid);

/* ulFlags for RTFSync */
#define RTF_SYNC_RTF_CHANGED	((ULONG) 0x00000001)
#define RTF_SYNC_BODY_CHANGED	((ULONG) 0x00000002)

/*
 * ScUpdateRTFAux
 *
 * Calculates and updates RTF auxiliary properties.
 */

STDAPI_(SCODE) ScUpdateRTFAux(LPMESSAGE lpMessage,
			BOOL FAR *lpfMessageUpdated);

STDAPI_(SCODE) ScUpdateRTFAuxCpid(LPMESSAGE lpMessage,
			BOOL FAR *lpfMessageUpdated, ULONG cpid);

/*
 * HrAppendTextToCompressedRTF
 *
 * Takes a text buffer (pbText, cchText) and appends it to the compressed
 * RTF property of the message (lpMessage) appying default text formatting.
 *
 * The text can be added either at the beginning of the message
 * (RTF_APPEND_BEGIN) or at the end (RTF_APPEND_END).
 * The text can be treated as a plain text (RTF_APPEND_PLAIN_TEXT)
 * or as a piece of text with some RTF formatting in it
 * (RTF_APPEND_RTF_TEXT).
 *
 * If case of RTF text, cchText is the number of plain text characters.
 *
 * cpid is the code page for the text stream. It should be one of
 * Windows code pages EXCLUDING unicode. cpid=0 means current system
 * code page. If the requested code page is not supported,
 * S_FALSE warning is returned.
 */

STDAPI_(HRESULT) HrAppendTextToCompressedRTF(LPMESSAGE lpMessage,
			LPSTR strText, ULONG cchText, ULONG ulFlags, ULONG cpid);

/* ulFlags for HrAppendTextToCompressedRTF */
	/* text properties (mutually exclusive) */
#define RTF_APPEND_RTF_TEXT	((ULONG) 0x00000001)
#define RTF_APPEND_PLAIN_TEXT ((ULONG) 0x00000000)
	/* append position (mutually exclusive) */
#define RTF_APPEND_BEGIN ((ULONG) 0x00000002)
#define RTF_APPEND_END ((ULONG) 0x00000000)

/* ATTACHMENT TABLE HANDLING ROUTINES */

/*
 * ScGetAttachTable()
 *
 * Takes a message and returns a pointer to the set of rows in
 * the attachment table (ppRowSet), the number of attachments 
 * (pcAttach), and a pointer to an array of ULONGs containing
 * the PR_RENDERING_POSITIONs for the attachments in sorted
 * order.
 *
 */

STDAPI_(SCODE) ScGetAttachTable(LPMESSAGE pmsg, LPSRowSet *ppRowSet,
				UINT *pcAttach, ULONG **prgAttachPos);

/*
 * ScUpdateAttachTable()
 *
 * Takes a message, a rowset for the attachment table, the 
 * number of attachments, and an array of rendering positions
 * to update the attachment table with. This function is 
 * designed to be used in conjunction with ScGetAttachTable().
 * The BOOLEAN pointed to by pfUpdated will be set to TRUE if
 * the attachment table was modified.
 *
 */

STDAPI_(SCODE) ScUpdateAttachTable(LPMESSAGE pmsg, LPSRowSet pRowSet,
				UINT cAttach, ULONG *rgAttachPos, BOOL *pfUpdated);


/* CPID CONVERSION ROUTINES */

/*
 * These functions are in a separate object file (cpmap.obj),
 * since on the store side they are linked into a different DLL.
 */

STDAPI_(ULONG) WinCpidFromCpid (ULONG cpid);
STDAPI_(ULONG) CharsetFromCpid (ULONG cpid);
STDAPI_(ULONG) CpidFromCharset (ULONG charset);
STDAPI_(CHAR FAR*) SzDefFontFmtFromCpid (ULONG cpid);


#endif /* RTFLIB_H */
