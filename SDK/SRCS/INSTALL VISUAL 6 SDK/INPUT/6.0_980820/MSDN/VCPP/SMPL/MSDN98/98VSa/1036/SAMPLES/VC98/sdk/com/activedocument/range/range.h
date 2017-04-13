/*===========================================================================
Copyright 1996 Microsoft Corporation.  All Rights Reserved.

THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

OVERVIEW OF INTERFACE

The client calls HttpReadRequest to specify the URL, a callback function, 
and an optional array of read ranges.  First, the callback will be notified
of the http response code, content length, last modified time, whether 
ranges are supported by the server, and whether the file is from the cache.  
Next, it may be called repeatedly with data which must be processed during the 
call.  Finally, it will indicate completion and an error if any.  Within the
callback, a client can initiate a new HttpReadRequest and/or return FALSE to
stop the current request.

All ActiveX controls can use this interface.  Other applications must satisfy
some requirements due to an implicit dependency on URL moniker.  The client
thread must have a message loop.  Before calling HttpReadRequest, the client
process must have called CoInitialize or OleInitialize.  After exiting the
message loop, the client process must call CoUninitialize or OleUninitialize.
===========================================================================*/

#ifndef _RANGE_
#define _RANGE_

#include <windows.h>
#include <objbase.h>

#ifdef __cplusplus
extern "C" {
#endif

// ===========================================================================
// Callback parameter structure and prototype
// ===========================================================================

// Callback Types:
typedef enum 
{
	REQUESTCB_STARTED  = 0,
	REQUESTCB_DATA     = 1,
	REQUESTCB_DONE     = 2,
}
	HTTP_REQUESTCB_TYPE;

// Callback parameters: valid only during the current call.
typedef struct
{
	DWORD  cbStruct;       // will be sizeof(HTTP_CALLBACK_PARAM)
    DWORD  dwRequestCtx;   // context passed in to HttpReadRequest
    HTTP_REQUESTCB_TYPE CallbackType;   // callback type as defined above
    
    union
    {
        struct // fields used if CallbackType == REQUESTCB_STARTED
		{
		    DWORD       fdwRequestFlags;  // fields as defined below
		    DWORD       dwResponseCode;   // status code (0 if unknown)
		    SYSTEMTIME* pstLastModified;  // last modified (NULL if unknown)
            DWORD       dwContentLength;  // content length (0 if unknown)
		};

        struct // fields used if CallbackType == REQUESTCB_DATA
        {
		    DWORD       dwDataOffset;     // offset of data
		    LPVOID      lpDataBuffer;     // pointer to data
		    DWORD       cbDataLength;     // amount of data
		};

		struct // fields used if CallbackType == REQUESTCB_DONE
		{
            HRESULT     hrRequest;        // values defined in urlmon.h
		};
	};
}
	HTTP_REQUESTCB_PARAM, *PHTTP_REQUESTCB_PARAM;

// Fields for HTTP_REQUESTCB_PARAM.fdwRequestFlags:
#define HTTP_REQUEST_FROM_CACHE       1
#define HTTP_REQUEST_ACCEPT_RANGES    2 

// Callback function supplied by client:
typedef BOOL (*PFN_REQUESTCB) (PHTTP_REQUESTCB_PARAM);

// ===========================================================================
// HttpReadRequest parameter structure and prototype
// ===========================================================================

// Structure for specifying a read range:
typedef struct
{
	DWORD dwOffset;     // offset of data within the URL
	DWORD dwSize;       // amount of data (0 means until end of file)
}
	HTTP_REQUEST_RANGE, *PHTTP_REQUEST_RANGE;

// Read request parameters must remain valid until REQUEST_COMPLETE:
typedef struct
{
	DWORD               cbStruct;        // must be sizeof(HTTP_REQUEST_PARAM)
 	LPVOID              punkOuter;       // controlling IUnknown (may be NULL)
    PCSTR               pszUrl;          // URL to request via http
	PFN_REQUESTCB       pfnRequestCB;    // request callback function
    DWORD               dwRequestCtx;    // context to pass to callback

    // Optional fields for specifying ranges, otherwise set all to 0:
    PHTTP_REQUEST_RANGE pRanges;                // array of read ranges
    DWORD               cRanges;                // number of ranges
    SYSTEMTIME*         pstUnlessModifiedSince; // unless-modified-since time
}
	HTTP_REQUEST_PARAM, *PHTTP_REQUEST_PARAM;

// Function called by client to initiate http read request.
BOOL HttpReadRequest    (PHTTP_REQUEST_PARAM); // try cache first
BOOL HttpReadFromServer (PHTTP_REQUEST_PARAM); // bypass cache

#ifdef __cplusplus
} // extern "C" {
#endif

#endif // _RANGE_
