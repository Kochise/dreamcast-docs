// --msgemit.h--------------------------------------------------------------
//
// API entry points for the msgemit static link library.
// Contains helper functions for converting MAPI messages to 
// 822-style headers and 822-style ASCII headers to MAPI messages.
//
// Copyright (C) Microsoft Corp., 1986-1996.  All rights reserved.
//
// ---------------------------------------------------------------------------

#ifndef _MSGEMIT_H
#define _MSGEMIT_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Constants for the binary encode and decode functions.
const ULONG nBytesEncodePerLine     =   24; // # of bytes encoded per line
const ULONG nCharsPerEncodedByte    =   3;  // # of chars written per encoded byte

// Convenient macro for determining the number of data bytes (not
// counting the null terminator) in a string.
static __inline ULONG cbStrBytes(
    IN LPCSTR pszString)     // string pointer
{
    return (lstrlenA(pszString));
}

//$--HrCreateDateTimeString@-------------------------------------------------
//
// DESCRIPTION: Builds a date & time (UT) created string for a MAPI message file time
//
// INPUT:       lpFileTime  --  file time structure pointer (UT)
//
// OUTPUT:      lppTimeString   --  Pointer to time string output buffer
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if bad input,
//                              E_OUTOFMEMORY if memory problems,
//                              E_FAIL otherwise
//
// ---------------------------------------------------------------------------

HRESULT HrCreateDateTimeStringW(
    IN LPFILETIME lpFileTime,      // file time structure pointer
    OUT LPWSTR * lppTimeString);   // pointer to time string buffer

HRESULT HrCreateDateTimeStringA(
    IN LPFILETIME lpFileTime,      // file time structure pointer
    OUT LPSTR * lppTimeString);    // pointer to time string buffer

#ifdef UNICODE
#define HrCreateDateTimeString  HrCreateDateTimeStringW
#else
#define HrCreateDateTimeString  HrCreateDateTimeStringA
#endif

//$--HrCreateImportanceString------------------------------------------------
//
// DESCRIPTION: Creates an message importance string from a MAPI message importance value
//
// INPUT:       ulImportance    --  message's PR_IMPORTANCE value
//              
// OUTPUT:      lppImportance --  Pointer to importance string buffer
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if invalid parameter,
//                              E_OUTOFMEMORY if memory problems,
//                              E_FAIL otherwise.
//
// ---------------------------------------------------------------------------

HRESULT HrCreateImportanceString(                   //  RETURNS:    HRESULT
                    IN ULONG ulImportance,            // message's PR_IMPORTANCE value
                    OUT LPSTR * lppImportance);  // pointer to importance string buffer

//$--HrEmitTagDataLine-------------------------------------------------------
//
// DESCRIPTION: Emits a line constructed from a static tag and dynamic
//              data to the specified stream.
//
// INPUT:       lpszTag --  tag portion of line
//              lpData      --  data portion of line    (may be "")
//              lpStream    --  stream to write line to
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if invalid parameter,d
//                              E_FAIL otherwise
//
// ---------------------------------------------------------------------------

HRESULT HrEmitTagDataLine(   
        IN LPCSTR lpszTag,      // static portion of line
        IN LPSTR lpData,        // dynamic portion of line
        IN LPSTREAM lpStream);  // stream to write line to

//$--HrCreatePriorityString-------------------------------------------------------
//
// DESCRIPTION: Creates message priority data string from a MAPI priority value
//
// INPUT:       ulPriority  --  message's PR_PRIORITY value
//
// OUTPUT:      lppPriorityString --  message priority data string pointer
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if invalid parameter,
//                              E_OUTOFMEMORY if memory problems
//                              E_FAIL otherwise
//
// ---------------------------------------------------------------------------

HRESULT HrCreatePriorityString(   
        IN ULONG ulPriority,            // message's PR_PRIORITY value
        OUT LPSTR * lppPriorityString); // message priority data string pointer

//$--HrEDKEncodeBinaryStreamDataToStream-----------------------------------------------
//
// DESCRIPTION: Copies binary data from an input stream or
//              specified output stream,
//              encoding each byte as a two-character
//              hexadecimal ASCII representation of the byte.
//              E.g. 255 becomes 'FF'.
//
// INPUT:       
//              lpStreamIn  --  input stream pointer
//              lpStreamOut --  output stream pointer
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if invalid parameter,
//                              E_FAIL otherwise
//
// ---------------------------------------------------------------------------
HRESULT HrEDKEncodeBinaryStreamDataToStream(               
                    IN LPSTREAM lpStreamIn,     // input stream pointer
                    IN LPSTREAM lpStreamOut);   // output stream pointer

//$--HrCreateExternalTraceString------------------------------------------------
//
// DESCRIPTION: Creates a string from a message's external trace information.
//
// INPUT:       lAction --  trace action
//              lpCountry   --  country
//              lpADMDName  --  ADMD name
//              lpPRMDId    --  PRMD identifier
//          
// OUTPUT:      lppTraceString  --  pointer to trace information string buffer
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if invalid parameter,
//                              E_OUTOFMEMORY if memory problems
//                              E_FAIL otherwise,
//
// -----------------------------------------------------------------------------

HRESULT HrCreateExternalTraceString(        
    IN LONG lAction,             // trace action
    IN LPSTR lpCountry,          // country name
    IN LPSTR lpADMDName,         // ADMD name
    IN LPSTR lpPRMDId,           // PRMD identifier    
    OUT LPSTR * lppTraceString); // trace information string pointer

//$--HrCreateInternalTraceString------------------------------------------------
//
// DESCRIPTION: Creates a string from a message's internal trace information.
//
// INPUT:       lAction		--  trace action
//              lpCountry   --  country
//              lpADMDName  --  ADMD name
//              lpPRMDId    --  PRMD identifier
//				lpMTAName	--  MTA name
//          
// OUTPUT:      lppTraceString  --  pointer to trace information string buffer
//
// RETURNS:     HRESULT     --  NOERROR if successful,
//                              E_INVALIDARG if invalid parameter,
//                              E_OUTOFMEMORY if memory problems
//                              E_FAIL otherwise,
//
// -----------------------------------------------------------------------------

HRESULT HrCreateInternalTraceString(        
    IN LONG lAction,             // trace action
    IN LPSTR lpCountry,          // country name
    IN LPSTR lpADMDName,         // ADMD name
    IN LPSTR lpPRMDId,           // PRMD identifier    
	IN LPSTR lpMTAName,			 // MTA name
    OUT LPSTR * lppTraceString); // trace information string pointer

//$--HrGetRecipientList------------------------------------------
//
// DESCRIPTION: Utility function which retrieves columns 
// desired from a MAPI recipient table.
//
// INPUT:   lpMessage   --  pointer to MAPI message
//          lpPropTags  --  list of columns (properties) to retrieve
//          
// OUTPUT:  lppRows --  pointer to array of rows returned pointer.
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input,
//                      E_FAIL otherwise
//
// -------------------------------------------------------------
HRESULT HrGetRecipientList(           
        IN LPMESSAGE lpMessage,         // MAPI message pointer
        IN LPSPropTagArray lpPropTags,  // properties (columns) desired
        OUT LPSRowSet * lppRows);       // pointer to rows returned

//$--HrParseTagAndData-------------------------------------------------------
//
// DESCRIPTION: Parse ASCII 822-style header line into
//              tag and data components.
//
// INPUT:       lpStream    --  stream pointer to read from
//
// OUTPUT:      pcbRead --  number of bytes read from stream
//              ppTag   --  pointer to tag buffer
//              ppData  --  pointer to data buffer
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//                          E_OUTOFMEMORY if memory problem
//                          E_EOF if end of stream
//                          E_FAIL otherwise
//
// ---------------------------------------------------------------------------
HRESULT HrParseTagAndData(
        IN LPSTREAM lpStream,   // stream pointer
        OUT ULONG * pcbRead,    // # of bytes read
        OUT LPSTR * lppTag,     // pointer to tag buffer
        OUT LPSTR * lppData);   // pointer to data buffer

//$--HrParseDateTimeString----------------------------------------------------
//
// DESCRIPTION: Parses a date and time string into a file time
//              structure.
//
// INPUT:       lpDateTimeString    --  date and time string
//
// OUTPUT:      pFileTime   --  file time pointer
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL otherwise
//
// ----------------------------------------------------------------------------
HRESULT HrParseDateTimeString(
    IN LPSTR lpDateTimeString,      // date and time string
    OUT FILETIME * pFileTime);      // file time pointer

//$--HrParsePriorityString----------------------------------------------------
//
// DESCRIPTION: Convert a priority string to its associated
//              integer value.
//
// INPUT:       lpPriority  --  priority string
//             
// OUTPUT:      pulPriority --  pointer to priority value
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL otherwise
//
// ----------------------------------------------------------------------------
HRESULT HrParsePriorityString(
    IN LPSTR lpPriority,        // Priority string
    OUT ULONG * pulPriority);   // priority value pointer

//$--HrParseImportanceString----------------------------------------------------
//
// DESCRIPTION: Convert an importance string to its associated
//              integer value.
//
// INPUT:       lpImportance  --  importance string
//             
// OUTPUT:      pulImportance --  pointer to importance value
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_FAIL otherwise
//
// ----------------------------------------------------------------------------
HRESULT HrParseImportanceString(
    IN LPSTR lpImportance,      // Importance string
    OUT ULONG * pulImportance); // importance value pointer

//$--HrParseExternalTraceString-------------------------------------------------
//
// DESCRIPTION: Parse External-Received-By or 
//              External-Attempted-By trace string into a
//              its separate components.
//
// INPUT:       lpTraceString   --  External-Received/Attempted-By trace string
//
// OUTPUT:      plAction   --  trace action
//              pCountry  --  country name
//              pADMDName --  ADMD name
//              pPRMDId   --  PRMD identifier
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input
//                      E_FAIL otherwise
//
// ----------------------------------------------------------------------------
HRESULT HrParseExternalTraceString(
    IN LPSTR lpTraceString,      // trace information string
    OUT LONG * plAction,         // trace action pointer
    OUT CHAR * pCountry,         // country name
    OUT CHAR * pADMDName,        // ADMD name
    OUT CHAR * pPRMDId);         // PRMD identifier

//$--HrParseInternalTraceString-------------------------------------------------
//
// DESCRIPTION: Parse Internal-Received-By or 
//              Internal-Attempted-By trace string into 
//              its separate components.
//
// INPUT:       lpTraceString   --  Internal-Received/Attempted-By trace string
//
// OUTPUT:      plAction  --  trace action
//              pCountry  --  country name
//              pADMDName --  ADMD name
//              pPRMDId   --  PRMD identifier
//              pMTAName  --  MTA name
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input
//                      E_FAIL otherwise
//
// -----------------------------------------------------------------------------
HRESULT HrParseInternalTraceString(
    IN LPSTR lpTraceString,      // trace information string
    OUT LONG * plAction,         // trace action pointer
    OUT CHAR * pCountry,         // country name
    OUT CHAR * pADMDName,        // ADMD name
    OUT CHAR * pPRMDId,          // PRMD identifier
    OUT CHAR * pMTAName);        // MTA name

//$--HrParseAttachmentHeader--------------------------------------------------
//
// DESCRIPTION: Parse attachment header data into its file name
//              and file size components.
//
// INPUT:   lpHeader    --  attachment header data string
//
// OUTPUT:  lppFileName --  attachment file name
//          pcb         --  pointer to # of bytes in attachment
//
// RETURNS: HRESULT --  NOERROR if successful,
//                      E_INVALIDARG if bad input,
//                      E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT HrParseAttachmentHeader(
    IN LPSTR lpHeader,         // attachment header data string
    OUT LPSTR * lppFileName,   // attachment file name
    OUT ULONG * pcb);          // pointer to number of bytes in file name

//$--HrEDKDecodeBinaryStreamDataToStream-----------------------------------------------
//
// DESCRIPTION: Read attachment hexadecimal encoding from input
//              stream to attachment.
//
// INPUT:       cb  --  number of bytes in binary attachment.
//              lpStream    --  stream pointer
//              lpAttach    --  attachment pointer
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//                          E_FAIL otherwise.
//
// ----------------------------------------------------------------------------

HRESULT HrEDKDecodeBinaryStreamDataToStream(
    IN LPSTREAM lpStreamIn,     // input stream
    IN ULONG cb,                // number of bytes in original binary data
    IN LPSTREAM lpStreamOut);   // output stream

//$--HrEDKParseSubjectPrefix---------------------------------------------------
//
// DESCRIPTION: Break a subject into its prefix component & its
//              original subject component.  (The prefix is everything
//              up to and including the first colon and the first space
//              after the colon, if any.
//
// INPUT:       pszSubject --  subject text
//
// OUTPUT       ppszPrefix  --  prefix string pointer
//              ppszOrigSub --  original subject pointer
//
// RETURNS:     HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input,
//                          E_OUTOFMEMORY if memory propblems,
//                          E_FAIL otherwise.
//
// ----------------------------------------------------------------------------
HRESULT HrEDKParseSubjectPrefix(
            IN LPSTR pszSubject,       // subject text
            OUT LPSTR * ppszPrefix,    // subject prefix
            OUT LPSTR * ppszOrigSub);  // original subject text

//$--nEDKEncodedBytes-------------------------------------------------------------
//
// DESCRIPTION: Returns the number of encoded bytes based on the number of 
//              un-encoded bytes.
//
// INPUT:       cbUnencoded --  # of un-encoded bytes
//
// RETURNS:     ULONG   --  # of encoded bytes
//
// NOTE:        This is implemented as a static __inline macro for 
//              efficiency and because it is so simple.
//
//-----------------------------------------------------------------------------
static __inline ULONG nEDKEncodedBytes(
            IN ULONG cbUnencoded)   // # of un-encoded bytes
{
    ASSERTERROR(cbUnencoded != 0, "Bad cbUnencoded");   // debug check

    if ( (cbUnencoded % nBytesEncodePerLine) == 0 )
    {
        return ( (nCharsPerEncodedByte * cbUnencoded) + 
                 (cbUnencoded/nBytesEncodePerLine) );
    }
    else
    {
        return ( (nCharsPerEncodedByte * cbUnencoded) + 
                 (cbUnencoded/nBytesEncodePerLine) + 1 );
    }
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
