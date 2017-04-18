// --edkmapi.h------------------------------------------------------------------
// 
//  Header file for module containing MAPI utility functions.
// 
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------
#ifndef _EDKMAPI_H
#define _EDKMAPI_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Flags for HrMAPIOpenCachedProp().
#define EDK_CACHE_READ  0x00000001L
#define EDK_CACHE_WRITE 0x00000002L

#define MODRECIP_EMPTY  (MODRECIP_ADD|MODRECIP_REMOVE)

/* Values of PR_NDR_REASON_CODE */

#define MAPI_REASON(_code)	((LONG) _code)

#define MAPI_REASON_TRANSFER_FAILED           MAPI_REASON( 0 )
#define MAPI_REASON_TRANSFER_IMPOSSIBLE       MAPI_REASON( 1 )
#define MAPI_REASON_CONVERSION_NOT_PERFORMED  MAPI_REASON( 2 )
#define MAPI_REASON_PHYSICAL_RENDITN_NOT_DONE MAPI_REASON( 3 )
#define MAPI_REASON_PHYSICAL_DELIV_NOT_DONE   MAPI_REASON( 4 )
#define MAPI_REASON_RESTRICTED_DELIVERY       MAPI_REASON( 5 )
#define MAPI_REASON_DIRECTORY_OPERATN_FAILED  MAPI_REASON( 6 )

#define CbSPropValue(_centries) \
	((_centries)*sizeof(SPropValue))

#define CbNewADRENTRY(_centries) \
	(offsetof(ADRENTRY,rgPropVals) + (_centries)*sizeof(LPSPropValue))
#define CbADRENTRY(_lpadrentry) \
	(offsetof(ADRENTRY,rgPropVals) + (UINT)(_lpadrentry)->cValues*sizeof(LPSPropValue))

#define VALID_RECIP_TYPE(ulRecipType) \
    (((ulRecipType & (~MAPI_SUBMITTED)) == MAPI_ORIG) ||            \
                ((ulRecipType & (~MAPI_SUBMITTED)) == MAPI_TO) ||   \
                ((ulRecipType & (~MAPI_SUBMITTED)) == MAPI_CC) ||   \
                ((ulRecipType & (~MAPI_SUBMITTED)) == MAPI_BCC))

#define VALID_RELOP_T(x)  \
    (((((ULONG)(x)) >= 0) && (((ULONG)(x)) < ((ULONG)RELOP_RE))) ? TRUE : FALSE)

#define VALID_ATTACH_METHOD(x)  \
    (((((ULONG)(x)) >= ((ULONG)NO_ATTACHMENT)) && \
    (((ULONG)(x)) < ((ULONG)ATTACH_OLE))) ? TRUE : FALSE)

//$--MSG_T----------------------------------------------------------------------
//  Type of message.
// -----------------------------------------------------------------------------
typedef enum _msg
{
    MSG_ENVELOPE = 0,                   // message envelope
    MSG_CONTENT,                        // message contents
    MSG_LAST                            // all values are less than this
} MSG_T;

#define VALID_MSG_T(x)  \
    (((((ULONG)(x)) >= 0) && (((ULONG)(x)) < ((ULONG)MSG_LAST))) ? TRUE : FALSE)

//$--MD_ACTION_T----------------------------------------------------------------
//  Type defining possible actions taken by an MD.
// -----------------------------------------------------------------------------
typedef enum _md_action
{
    MD_AC_EXPANDED = -2,                // Distribution list expanded
    MD_AC_REDIRECTED,                   // Recipient address changed
    MD_AC_RELAYED,                      // Normal action of a relay MTAE
    MD_AC_REROUTED,                     // Previous attempt to route message
    MD_AC_LAST                          // All values are less than this
} MD_ACTION_T;

#define VALID_MD_ACTION(x)  \
    ((((LONG)(x)) >= ((LONG)-2)) && (((LONG)(x)) < ((LONG)MD_AC_LAST)))

#define CbNewTRACEINFO(_centries) \
    (offsetof(TRACEINFO,rgtraceentry) + (_centries)*sizeof(TRACEENTRY))

#define CbTRACEINFO(_lptraceinfo) \
    (offsetof(TRACEINFO,rgtraceentry) + \
    ((_lptraceinfo)->cEntries*sizeof(TRACEENTRY)))

#define CbNewINTTRACEINFO(_centries) \
    (offsetof(INTTRACEINFO,rgIntTraceEntry) + (_centries)*sizeof(INTTRACEENTRY))

#define CbINTTRACEINFO(_lptraceinfo) \
    (offsetof(INTTRACEINFO,rgIntTraceEntry) + \
    ((_lptraceinfo)->cEntries*sizeof(INTTRACEENTRY)))

//******************************************************************************
//
// EDKMAPI.C function prototypes
//
//******************************************************************************

//$--HrMAPIGetFirstSRowSet------------------------------------------------------
//  Gets the first SRowSet from a table
// -----------------------------------------------------------------------------
HRESULT HrMAPIGetFirstSRowSet(           // RETURNS: return code
    IN LPMAPITABLE  lpTable,            // pointer to table address variable
    IN ULONG cRows,                     // count of number of rows in SRowSet
    IN LPSPropTagArray rgPropTags,      // array of property tags
    OUT LPSRowSet FAR *lppRows);        // pointer to address variable for
                                        // SRowSet

//$--HrMAPIGetNextSRowSet-------------------------------------------------------
//  Gets the next SRowSet from a table
// -----------------------------------------------------------------------------
HRESULT HrMAPIGetNextSRowSet(            // RETURNS: return code
    IN LPMAPITABLE lpTable,             // pointer to table
    IN ULONG cRows,                     // count of number of rows in SRowSet
    IN LPSPropTagArray rgPropTags,      // array of property tags
    OUT LPSRowSet FAR *lppRows);        // pointer to address variable for
                                        // SRowSet

//$--HrMAPICreateEntryList------------------------------------------------------
//  Creates an ENTRYLIST. 
// -----------------------------------------------------------------------------
HRESULT HrMAPICreateEntryList(           // RETURNS: return code
    IN ULONG cbeid,                     // count of bytes in Entry ID
    IN LPENTRYID lpeid,                 // pointer to Entry ID
    OUT LPENTRYLIST FAR *lppEntryList); // pointer to address variable of Entry
                                        // list

//$--HrMAPIAppendEntryList------------------------------------------------------
//  Appends to an ENTRYLIST.
// -----------------------------------------------------------------------------
HRESULT HrMAPIAppendEntryList(           // RETURNS: return code
    IN ULONG cbeid,                     // count of bytes in Entry ID
    IN LPENTRYID lpeid,                 // pointer to Entry ID
    OUT LPENTRYLIST FAR lpEntryList);   // pointer to address variable of Entry
                                        // list

//$--HrMAPIDestroyEntryList-----------------------------------------------------
//  Frees an ENTRYLIST. 
// -----------------------------------------------------------------------------
HRESULT HrMAPIDestroyEntryList(               // RETURNS: return code
    IN OUT LPENTRYLIST FAR *lppEntryList);// pointer to address variable of Entry
                                          // list

//$--HrMAPIWriteStreamToFile----------------------------------------------------
//  Write stream to a file given a file handle.
// -----------------------------------------------------------------------------
HRESULT HrMAPIWriteStreamToFile(        // RETURNS: return code
    IN LPSTREAM lpStream,               // Pointer to stream
    OUT HANDLE hFile);                  // Handle to file

//$--HrMAPIWriteFileToStream----------------------------------------------------
//  Write file to a stream given a stream pointer.
// -----------------------------------------------------------------------------
HRESULT HrMAPIWriteFileToStream(        // RETURNS: return code
    IN HANDLE hFile,                    // Handle to file
    OUT LPSTREAM lpStream);             // Pointer to stream

//$--HrMAPIWriteAttachmentToFile------------------------------------------------
//  Write the identified message attachment to a file.
// -----------------------------------------------------------------------------
HRESULT HrMAPIWriteAttachmentToFile(   // RETURNS: return code
    IN LPMESSAGE pMessage,              // Message containing the attachments
    IN ULONG iAttach,                   // Attachment identifier
    OUT HANDLE  hFile);                 // Handle to file

//$--HrMAPIGotoSRow-------------------------------------------------------------
//  Goto the specified SRow in an SRowSet.
//------------------------------------------------------------------------------
HRESULT HrMAPIGotoSRow(                  // RETURNS: return code
    IN LPSRowSet FAR lpRows,            // pointer to SRowSet
    IN ULONG ulRow,                     // index of SRow in SRowSet
    OUT LPSRow *lppRow);                // pointer to SRow

//$--HrMAPIGotoFirstSRow--------------------------------------------------------
//  Goto the first SRow in an SRowSet.
//------------------------------------------------------------------------------
HRESULT HrMAPIGotoFirstSRow(             // RETURNS: return code
    IN LPSRowSet FAR lpRows,            // pointer to SRowSet
    OUT ULONG *lpulRow,                 // index of SRow in SRowSet
    OUT LPSRow *lppRow);                // pointer to SRow

//$--HrMAPIGotoNextSRow---------------------------------------------------------
//  Goto the next SRow in an SRowSet.
//------------------------------------------------------------------------------
HRESULT HrMAPIGotoNextSRow(              // RETURNS: return code
    IN LPSRowSet FAR lpRows,            // pointer to SRowSet
    IN OUT ULONG *lpulRow,              // index of SRow in SRowSet
    OUT LPSRow *lppRow);                // pointer to SRow

//$--HrMAPIWriteStreamToMemory--------------------------------------------------
//  Reads a given number of bytes from a stream to a block of memory.
// -----------------------------------------------------------------------------
HRESULT HrMAPIWriteStreamToMemory(        // RETURNS: return code
    IN LPSTREAM lpStream,               // pointer to stream
    IN ULONG cBytes,                    // count of bytes in memory
    IN LPBYTE lpbBytes,                 // pointer to memory
    OUT ULONG *lpcBytesRead);           // count of bytes read from stream

//$--HrMAPIWriteMemoryToStream--------------------------------------------------
//  Writes a given number of bytes from a block of memory to a stream
// -----------------------------------------------------------------------------
HRESULT HrMAPIWriteMemoryToStream(       // RETURNS: return code
    IN LPSTREAM lpStream,               // pointer to stream
    IN ULONG cBytes,                    // count of bytes in memory
    IN LPBYTE lpbBytes,                 // pointer to memory
    OUT ULONG *lpcBytesWritten);        // count of bytes written from stream

//$--HrMAPISetStreamSize--------------------------------------------------------
//  Sets the size of the given stream.
// -----------------------------------------------------------------------------
HRESULT HrMAPISetStreamSize(             // RETURNS: return code
    IN LPSTREAM lpStream,               // pointer to stream
    IN ULONG cBytes);                   // count of bytes in stream

//******************************************************************************
//
// IADDRESS.C function prototypes
//
//******************************************************************************

//$--HrMAPICreateAddressList----------------------------------------------------
//  Create an address list.
// -----------------------------------------------------------------------------
HRESULT HrMAPICreateAddressList(             // RETURNS: return code
    IN ULONG cProps,                        // count of values in address list
                                            // entry
    IN LPSPropValue lpPropValues,           // pointer to address list entry
    OUT LPADRLIST *lppAdrList);             // pointer to address list pointer

//$--HrMAPIAppendAddressList----------------------------------------------------
//  Append to an address list.
// -----------------------------------------------------------------------------
HRESULT HrMAPIAppendAddressList(             // RETURNS: return code
    IN ULONG cProps,                        // count of values in address list
                                            // entry
    IN LPSPropValue lpPropValues,           // pointer to address list entry
    IN OUT LPADRLIST *lppAdrList);          // pointer to address list pointer

//$--HrMAPICreateSizedAddressList-----------------------------------------------
//  Create a sized address list.
// -----------------------------------------------------------------------------
HRESULT HrMAPICreateSizedAddressList(        // RETURNS: return code
    IN ULONG cEntries,                      // count of entries in address list
    OUT LPADRLIST *lppAdrList);             // pointer to address list pointer

//$--HrMAPISetAddressList-------------------------------------------------------
//  Set an address list.
// -----------------------------------------------------------------------------
HRESULT HrMAPISetAddressList(                // RETURNS: return code
    IN ULONG iEntry,                        // index of address list entry
    IN ULONG cProps,                        // count of values in address list
                                            // entry
    IN LPSPropValue lpPropValues,           // pointer to address list entry
    IN OUT LPADRLIST lpAdrList);            // pointer to address list pointer

//******************************************************************************
//
// IFOLDER.C function prototypes
//
//******************************************************************************

//$--HrMAPIFindInbox------------------------------------------------------------
//  Find IPM inbox folder.
// -----------------------------------------------------------------------------
HRESULT HrMAPIFindInbox(              // RETURNS: return code
    IN LPMDB lpMdb,                     // pointer to message store
    OUT ULONG *lpcbeid,                 // count of bytes in entry ID
    OUT LPENTRYID *lppeid);             // Entry ID of IPM inbox

//$--HrMAPIFindOutbox-----------------------------------------------------------
//  Find IPM outbox folder.
// -----------------------------------------------------------------------------
HRESULT HrMAPIFindOutbox(             // RETURNS: return code
    IN LPMDB lpMdb,                     // pointer to message store
    OUT ULONG *lpcbeid,                 // count of bytes in entry ID
    OUT LPENTRYID *lppeid);             // Entry ID of IPM outbox

//$--HrMAPIFindIPMSubtree-------------------------------------------------------
//  Find IPM subtree folder.
// -----------------------------------------------------------------------------
HRESULT HrMAPIFindIPMSubtree(            // RETURNS: return code
    IN LPMDB lpMdb,                     // pointer to message store
    OUT ULONG *lpcbeid,                 // count of bytes in entry ID
    OUT LPENTRYID *lppeid);             // entry ID of IPM subtree

//$--HrGWFindMtsOutFolder-------------------------------------------------------
//  Find MTS-OUT folder.
// -----------------------------------------------------------------------------
HRESULT HrGWFindMtsOutFolder(                // RETURNS: return code
    IN LPMDB lpMdb,                     // pointer to message store
    OUT ULONG *lpcbeid,                 // count of bytes in entry ID
    OUT LPENTRYID *lppeid);             // entry ID of MTS-OUT

//$--HrGWFindMtsInFolder--------------------------------------------------------
//  Find MTS-IN folder.
// -----------------------------------------------------------------------------
HRESULT HrGWFindMtsInFolder(                 // RETURNS: return code
    IN LPMDB lpMdb,                     // pointer to message store
    OUT ULONG *lpcbeid,                 // count of bytes in entry ID
    OUT LPENTRYID *lppeid);             // entry ID of MTS-IN

//$--HrFindExchangePublicStore--------------------------------------------------
//  Find public store root folder.
// -----------------------------------------------------------------------------
HRESULT HrFindExchangePublicStore(           // RETURNS: return code
    IN LPMDB lpMdb,                     // pointer to message store
    OUT ULONG *lpcbeid,                 // count of bytes in entry ID
    OUT LPENTRYID *lppeid);             // entry ID of public store

//$--HrMAPIFindFolder@----------------------------------------------------------
//  Find a folder by name.
// -----------------------------------------------------------------------------
HRESULT HrMAPIFindFolderW(         // RETURNS: return code
    IN LPMAPIFOLDER lpFolder,           // pointer to folder
    IN LPCWSTR lpszName,                // name of folder to find
    OUT ULONG *lpcbeid,                 // pointer to count of bytes in entry ID
    OUT LPENTRYID *lppeid);             // pointer to entry ID pointer

HRESULT HrMAPIFindFolderA(         // RETURNS: return code
    IN LPMAPIFOLDER lpFolder,           // pointer to folder
    IN LPCSTR lpszName,                 // name of folder to find
    OUT ULONG *lpcbeid,                 // pointer to count of bytes in entry ID
    OUT LPENTRYID *lppeid);             // pointer to entry ID pointer

#ifdef UNICODE
#define HrMAPIFindFolder   HrMAPIFindFolderW
#else
#define HrMAPIFindFolder   HrMAPIFindFolderA
#endif

//$--HrMAPIFindSubfolderEx@-----------------------------------------------------
//  Find a folder by name.
// -----------------------------------------------------------------------------
HRESULT HrMAPIFindSubfolderExW(
    IN LPMAPIFOLDER lpRootFolder,       // open root folder
    IN WCHAR chSep,                     // folder path separator
    IN LPCWSTR lpszName,                // folder path
    OUT ULONG *lpcbeid,                 // pointer to count of bytes in entry ID
    OUT LPENTRYID *lppeid);             // pointer to entry ID pointer

HRESULT HrMAPIFindSubfolderExA(
    IN LPMAPIFOLDER lpFolder,           // open root folder
    IN CHAR chSep,                      // folder path separator
    IN LPCSTR lpszName,                 // folder path
    OUT ULONG *lpcbeid,                 // pointer to count of bytes in entry ID
    OUT LPENTRYID *lppeid);             // pointer to entry ID pointer

#ifdef UNICODE
#define HrMAPIFindSubfolderEx   HrMAPIFindSubfolderExW
#else
#define HrMAPIFindSubfolderEx   HrMAPIFindSubfolderExA
#endif

//$--HrMAPIFindFolderEx@--------------------------------------------------------
//  Finds an arbitrarily nested folder in the indicated store given its 
//  path name.
//------------------------------------------------------------------------------
HRESULT HrMAPIFindFolderExW(
    IN LPMDB lpMdb,                     // Open message store
    IN WCHAR  chSep,                    // folder path separator character
    IN LPCWSTR lpszFolderPath,          // folder path
    OUT ULONG *lpcbeid,                 // pointer to count of bytes in entry ID
    OUT LPENTRYID *lppeid);             // pointer to entry ID pointer

HRESULT HrMAPIFindFolderExA(
    IN LPMDB lpMdb,                     // Open message store
    IN CHAR  chSep,                     // folder path separator character
    IN LPCSTR lpszFolderPath,           // folder path
    OUT ULONG *lpcbeid,                 // pointer to count of bytes in entry ID
    OUT LPENTRYID *lppeid);             // pointer to entry ID pointer

#ifdef UNICODE
#define HrMAPIFindFolderEx HrMAPIFindFolderExW
#else
#define HrMAPIFindFolderEx HrMAPIFindFolderExA
#endif

//$--HrMAPIOpenFolderEx@--------------------------------------------------------
//  Opens an arbitrarily nested folder in the indicated store given its 
//  path name.
//------------------------------------------------------------------------------
HRESULT HrMAPIOpenFolderExW(
    IN LPMDB lpMdb,                     // Open message store
    IN WCHAR chSep,                     // folder path separator character
    IN LPCWSTR lpszFolderPath,          // folder path
    OUT LPMAPIFOLDER * lppFolder);      // pointer to folder opened

HRESULT HrMAPIOpenFolderExA(
    IN LPMDB lpMdb,                     // Open message store
    IN CHAR chSep,                      // folder path separator character
    IN LPCSTR lpszFolderPath,           // folder path
    OUT LPMAPIFOLDER * lppFolder);      // pointer to folder opened

#ifdef UNICODE
#define HrMAPIOpenFolderEx HrMAPIOpenFolderExW
#else
#define HrMAPIOpenFolderEx HrMAPIOpenFolderExA
#endif

//$--HrMAPIOpenSubfolderEx@-----------------------------------------------------
//  Opens an arbitrarily nested folder in the indicated folder given its 
//  path name.
//------------------------------------------------------------------------------
HRESULT HrMAPIOpenSubfolderExW(
    IN LPMAPIFOLDER lpRootFolder,       // open root folder
    IN WCHAR chSep,                     // folder path separator character
    IN LPCWSTR lpszFolderPath,          // folder path
    OUT LPMAPIFOLDER * lppFolder);      // pointer to folder opened

HRESULT HrMAPIOpenSubfolderExA(
    IN LPMAPIFOLDER lpRootFolder,       // open root folder
    IN CHAR chSep,                      // folder path separator character
    IN LPCSTR lpszFolderPath,           // folder path
    OUT LPMAPIFOLDER * lppFolder);      // pointer to folder opened

#ifdef UNICODE
#define HrMAPIOpenSubfolderEx HrMAPIOpenSubfolderExW
#else
#define HrMAPIOpenSubfolderEx HrMAPIOpenSubfolderExA
#endif

//$--HrOpenExchangePublicFolders------------------------------------------------
//  Opens the root of the public folder hierarchy in the public message store.
//------------------------------------------------------------------------------
HRESULT HrOpenExchangePublicFolders(
    IN LPMDB lpPubStore,
    OUT LPMAPIFOLDER *lppRootFolder);

//******************************************************************************
//
// IMESSAGE.C function prototypes
//
//******************************************************************************

//$--HrMAPIFindMsgByProp--------------------------------------------------------
//  Find the entry ID of a message given a property.
// -----------------------------------------------------------------------------
HRESULT HrMAPIFindMsgByProp(         // RETURNS: return code
    IN LPMAPIFOLDER lpFolder,       // pointer to folder
    IN LPSPropValue lpSPropValue,   // property value
    OUT LPENTRYLIST *lppMsgList);   // list of matching messages

//$--HrMAPIMoveMessage----------------------------------------------------------
//  Move one message from one folder to another.
// -----------------------------------------------------------------------------
HRESULT HrMAPIMoveMessage(            // RETURNS: return code
    IN LPMAPIFOLDER lpSrcFolder,        // pointer to source folder
    IN LPMAPIFOLDER lpDstFolder,        // pointer to destination folder
    IN ULONG cbeid,                     // count of bytes in entry ID
    IN LPENTRYID lpeid);                // pointer to entry ID

//$--HrMAPICopyMessage----------------------------------------------------------
//  Copy one message from one folder to another.
// -----------------------------------------------------------------------------
HRESULT HrMAPICopyMessage(            // RETURNS: return code
    IN LPMAPIFOLDER lpSrcFolder,        // pointer to source folder
    IN LPMAPIFOLDER lpDstFolder,        // pointer to destination folder
    IN ULONG cbeid,                     // count of bytes in entry ID
    IN LPENTRYID lpeid);                // pointer to entry ID

//$--HrMAPIDeleteMessage--------------------------------------------------------
//  Delete one message from one folder to another.
// -----------------------------------------------------------------------------
HRESULT HrMAPIDeleteMessage(          // RETURNS: return code
    IN LPMAPIFOLDER lpFolder,           // pointer to folder
    IN ULONG cbeid,                     // count of bytes in entry ID
    IN LPENTRYID lpeid);                // pointer to entry ID

//******************************************************************************
//
// IPROP.C function prototypes
//
//******************************************************************************

//$--HrMAPIOpenCachedProp-------------------------------------------------------
//
//  DESCRIPTION: Create a new (local) IPropData object in which the original
//  object properties are cached.  The local cached can be created for
//  reading (for use with GetProp calls) for for writing (for use with
//  SetProp calls).  The purpose of this function and HrMAPICloseCachedProp
//  is to reduce the number of remote procedure calls made by code
//  which performs many GetProp or SetProp calls on an object.
//
//  INPUT:  lpObj   --  property object to cache
//          lpPropList  --  list of properties to cache (for reading)
//                          defaults to all properties if NULL.
//          ulFlags --  read OR write access flag (EDK_CACHE_READ
//                      or EDK_CACHE_WRITE)
//          
//  OUTPUT: lppCachedObj    --  cached property object
//
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//                          E_FAIL otherwise.
//
//  NOTE:   This function creates a cached object for reading only
//          or for writing only.  It does not support and object
//          for both reading and writing.
//
// -----------------------------------------------------------------------------
HRESULT HrMAPIOpenCachedProp(            // RETURNS: return code
    IN LPMAPIPROP lpObj,                // source object
    IN LPSPropTagArray lpPropList,      // list of properties to cache
    IN ULONG ulFlags,                   // open for reading only or for writing only
	OUT LPPROPDATA FAR * lppCachedObj); // cached version of source object

//$--HrMAPICloseCachedProp------------------------------------------------------
//
//  DESCRIPTION: If object was created as a write cache,
//               copy properties in local cached object
//               back to original remote object.
//
//  INPUT:  lpCachedObj --  cached property object
//          lpOriginalObj   --  original property object
//          ulFlags --  read cache or write cache flag (EDK_CACHE_READ
//                      or EDK_CACHE_WRITE)
//
//  OUTPUT: lppProblems --  set to the property problem array returned
//          by if there were problems setting properties on the original
//          object
//
//  NOTES:  lppProblems:  It may be set, even though overall call
//          is successful.  This is because all of the SetProps have been "deferred" on the
//          original object until this call, the user will need to evaluate
//          the contents of the lppProblems buffer pointer based on which
//          properties he/or she actually tried to set.  
//
//  RETURNS:    HRESULT --  NOERROR if successful,
//                          E_INVALIDARG if bad input
//                          E_FAIL otherwise
//
//                          lppProblems will only be valid if return code
//                          is NOERROR.
//
// -----------------------------------------------------------------------------
HRESULT HrMAPICloseCachedProp(           // RETURNS: return code
    IN LPPROPDATA lpCachedObj,          // cached property object
    IN LPMAPIPROP lpOriginalObj,        // original object
    IN ULONG ulFlags,                   // cache type (EDK_CACHE_READ or EDK_CACHE_WRITE)
    OUT LPSPropProblemArray FAR * lppProblems); // pointer to property problems array if problems setting properties

//$--HrMAPIGetPropString--------------------------------------------------------
//  Get a string property. 
// -----------------------------------------------------------------------------
HRESULT HrMAPIGetPropString(             // RETURNS: return code
    IN LPMAPIPROP lpObj,                // pointer to object
    IN ULONG ulPropTag,                 // property tag
    OUT ULONG *lpcbProp,                // count of bytes in property
    OUT LPVOID *lppvProp);              // pointer to property address variable

//$--HrMAPISetPropString--------------------------------------------------------
//  Set a string property. 
// -----------------------------------------------------------------------------
HRESULT HrMAPISetPropString(             // RETURNS: return code
    IN LPMAPIPROP lpObj,                // pointer to object
    IN ULONG ulPropTag,                 // property tag
    IN LPVOID lpvProp);                 // pointer to property

//$--HrMAPIGetPropBinary--------------------------------------------------------
//  Get a binary property.
// -----------------------------------------------------------------------------
HRESULT HrMAPIGetPropBinary(             // RETURNS: return code
    IN LPMAPIPROP lpObj,                // pointer to object
    IN ULONG ulPropTag,                 // property tag
    OUT ULONG *lpcbProp,                // count of bytes in property
    OUT LPVOID *lppvProp);              // pointer to property address variable

//$--HrMAPISetPropBinary--------------------------------------------------------
//  Set a binary property.
// -----------------------------------------------------------------------------
HRESULT HrMAPISetPropBinary(             // RETURNS: return code
    IN LPMAPIPROP lpObj,                // pointer to object
    IN ULONG ulPropTag,                 // property tag
    IN ULONG cbProp,                    // count of bytes in property
    IN LPVOID lpvProp);                 // pointer to property

//$--HrMAPIGetPropBoolean-------------------------------------------------------
//  Get a boolean property.
// -----------------------------------------------------------------------------
HRESULT HrMAPIGetPropBoolean(            // RETURNS: return code
    IN LPMAPIPROP lpObj,                // pointer to object
    IN ULONG ulPropTag,                 // property tag
    OUT BOOL *lpfProp);                 // pointer to property variable

//$--HrMAPISetPropBoolean-------------------------------------------------------
//  Set a boolean property.
// -----------------------------------------------------------------------------
HRESULT HrMAPISetPropBoolean(            // RETURNS: return code
    IN LPMAPIPROP lpObj,                // pointer to object
    IN ULONG ulPropTag,                 // property tag
    IN BOOL fProp);                     // property

//$--HrMAPIGetPropLong----------------------------------------------------------
//  Get a long property.
// -----------------------------------------------------------------------------
HRESULT HrMAPIGetPropLong(               // RETURNS: return code
    IN LPMAPIPROP lpObj,                // pointer to object
    IN ULONG ulPropTag,                 // property tag
    OUT ULONG *lpulProp);               // pointer to property variable

//$--HrMAPISetPropLong----------------------------------------------------------
//  Set a long property.
// -----------------------------------------------------------------------------
HRESULT HrMAPISetPropLong(               // RETURNS: return code
    IN LPMAPIPROP lpObj,                // pointer to object
    IN ULONG ulPropTag,                 // property tag
    IN ULONG ulProp);                   // property

//$--HrMAPIGetPropSystime-------------------------------------------------------
//  Get a systime property.
// -----------------------------------------------------------------------------
HRESULT HrMAPIGetPropSystime(            // RETURNS: return code
    IN LPMAPIPROP lpObj,                // pointer to object
    IN ULONG ulPropTag,                 // property tag
    OUT LPFILETIME lpSystime);          // pointer to property variable

//$--HrMAPISetPropSystime-------------------------------------------------------
//  Set a systime property.
// -----------------------------------------------------------------------------
HRESULT HrMAPISetPropSystime(            // RETURNS: return code
    IN LPMAPIPROP lpObj,                // pointer to object
    IN ULONG ulPropTag,                 // property tag
    IN LPFILETIME lpSystime);           // pointer to property

//$--HrMAPIGetPropToFile--------------------------------------------------------
//  Get a property and put in a given file.
// -----------------------------------------------------------------------------
HRESULT HrMAPIGetPropToFile(             // RETURNS: return code
    IN LPMAPIPROP lpObj,                // pointer to object
    IN ULONG ulPropTag,                 // property tag
    IN LPSTR lpszFilename,             // pointer to destination file name
    OUT ULONG *lpcbProp);               // pointer to count of bytes address
                                        // variable

//$--HrMAPISetPropFromFile------------------------------------------------------
//  Set a property from a given file.
// -----------------------------------------------------------------------------
HRESULT HrMAPISetPropFromFile(          // RETURNS: return code
    IN LPMAPIPROP lpObj,                // pointer to object
    IN ULONG ulPropTag,                 // property tag
    IN LPSTR lpszFilename,              // pointer to source file name
    OUT ULONG *lpcbProp);               // pointer to count of bytes address
                                        // variable

//$--HrMAPIOpenStreamOnProperty-------------------------------------------------
//  Open a stream on a given property.
// -----------------------------------------------------------------------------
HRESULT HrMAPIOpenStreamOnProperty(     // RETURNS: return code
    IN LPMAPIPROP lpObj,                // pointer to object
    IN ULONG ulPropTag,                 // property tag
    IN ULONG ulFlags,                   // flags (MAPI_CREATE and/or MAPI_MODIFY)
    OUT LPSTREAM *lppStream);           // pointer to stream address variable

//$--HrMAPIAppendSPropValues----------------------------------------------------
//  Append one set of SPropValue's to another.
// -----------------------------------------------------------------------------
HRESULT HrMAPIAppendSPropValues(        // RETURNS: return code
    IN ULONG cHeadProps,                // count of property values in head
    IN LPSPropValue lpHeadProps,        // pointer to property values in
                                        // head
    IN ULONG cTailProps,                // count of property values in tail
    IN LPSPropValue lpTailProps,        // pointer to property values in
                                        // tail
    OUT ULONG *lpcNewProps,             // pointer to count of property
                                        // values
    OUT LPSPropValue *lppNewProps);     // pointer to property values 

//$--HrMAPIMoveOneProp----------------------------------------------------------
//  Move one property from a source object to a destination object.
// -----------------------------------------------------------------------------
HRESULT HrMAPIMoveOneProp(               // RETURNS: return code
    IN LPMAPIPROP lpSrcObj,             // pointer to source object
    IN ULONG ulSrcPropTag,              // source property tag
    IN ULONG ulDstPropTag,              // destination property tag
    IN BOOL IsMust,                     // TRUE if a required property
    IN BOOL IsReplace,                  // TRUE if existing destination
                                        // property can be replaced
    IN OUT LPMAPIPROP lpDstObj);        // pointer to destination object

//******************************************************************************
//
// ISTORE.C function prototypes
//
//******************************************************************************


// $--HrMAPIFindStore-----------------------------------------------------------
// Find an MDB store based on a string.
//-----------------------------------------------------------------------------
HRESULT HrMAPIFindStoreW(
	IN	LPMAPISESSION	lpSession,  // MAPI session ptr
	IN	LPCWSTR			lpszStore,  // store name
	OUT	ULONG FAR *		lpcbentryid,// ptr to # bytes in entry ID
	OUT	LPENTRYID FAR *	lppentryid);// ptr to entry ID buffer

HRESULT HrMAPIFindStoreA(
	IN	LPMAPISESSION	lpSession,  // MAPI session ptr
	IN	LPCSTR			lpszStore,  // store name
	OUT	ULONG FAR *		lpcbentryid,// ptr to # bytes in entry ID
	OUT	LPENTRYID FAR *	lppentryid);// ptr to entry ID buffer

#ifdef UNICODE
#define HrMAPIFindStore  HrMAPIFindStoreW
#else
#define HrMAPIFindStore  HrMAPIFindStoreA
#endif

//$--HrMAPIFindDefaultMsgStore--------------------------------------------------
//  Get the entry ID of the default message store.
// -----------------------------------------------------------------------------
HRESULT HrMAPIFindDefaultMsgStore(    // RETURNS: return code
    IN LPMAPISESSION lplhSession,   // session pointer
    OUT ULONG *lpcbeid,             // count of bytes in entry ID
    OUT LPENTRYID *lppeid);         // entry ID of default store

//$--FIsPublicStore-------------------------------------------------------------
//  Returns TRUE if the MDB is a public store.
// -----------------------------------------------------------------------------
BOOL FIsPublicStore(
    IN LPMDB lpmdb);                // pointer to message store

//$--_HrOpenStoreFromGuid-------------------------------------------------------
//  Helper function to encapsulate the nuts and bolts of opening stores by GUID.
//  Used by HrOpenExchangePublicStore(), and HrOpenExchangePrivateStore().
//------------------------------------------------------------------------------
HRESULT _HrOpenStoreFromGuid(
    IN  LPMAPISESSION,
    IN  LPGUID,
    OUT LPMDB *);

//$--HrOpenExchangePublicStore--------------------------------------------------
//  Locates the public store provider (first matching if there are multiple)
//  and returns a pointer to it.
//------------------------------------------------------------------------------
__inline HRESULT HrOpenExchangePublicStore(
    IN LPMAPISESSION lphSession,    // open session handle
    OUT LPMDB * lppMDB)             // ptr to store opened
{
    return( _HrOpenStoreFromGuid( lphSession,
        (LPGUID)pbExchangeProviderPublicGuid,
        lppMDB));
}

//$--HrOpenExchangePrivateStore--------------------------------------------------
//  Locates the primary user store provider (first matching if there are multiple)
//  and returns a pointer to it.
//------------------------------------------------------------------------------
__inline HRESULT HrOpenExchangePrivateStore(
    IN LPMAPISESSION lphSession,    // open session handle
    OUT LPMDB * lppMDB)             // ptr to store opened
{
    return( _HrOpenStoreFromGuid( lphSession,
        (LPGUID)pbExchangeProviderPrimaryUserGuid,
        lppMDB));
}

//******************************************************************************
//
// ITRACE.C function prototypes
//
//******************************************************************************

//$--HrTraceGetEntryListSize----------------------------------------------------
//  Get the size of the hop trace information in bytes.
// -----------------------------------------------------------------------------
HRESULT HrTraceGetEntryListSize(      // RETURNS: return code
    IN LPTRACEINFO lpTraceInfo,         // Pointer to hop trace address variable
    OUT ULONG      *lpcbTraceInfo);     // Count of bytes in hop trace list

//$--HrTraceGetEntryList--------------------------------------------------------
//  Get the hop trace information for a given message.
// -----------------------------------------------------------------------------
HRESULT HrTraceGetEntryList(         // RETURNS: return code
    IN LPMESSAGE   lpMessage,           // Pointer to message.
    OUT LPTRACEINFO *lppTraceInfo);     // Pointer to hop trace address variable

//$--HrTraceSetEntryList--------------------------------------------------------
//  Set the hop trace information for a given message.
// -----------------------------------------------------------------------------
HRESULT HrTraceSetEntryList(         // RETURNS: return code
    IN LPMESSAGE   lpMessage,           // Pointer to message.
    IN LPTRACEINFO lpTraceInfo);        // Pointer to hop trace address variable

//$--HrTraceCopyEntry-----------------------------------------------------------
//  Copy trace entry information to a trace entry structure.
// -----------------------------------------------------------------------------
HRESULT HrTraceCopyEntry(            // RETURNS: return code
    IN LONG     lAction,                // The routing action the tracing site
                                        // took.
    IN FILETIME ftArrivalTime,          // The time at which the communique
                                        // entered the tracing site.
    IN FILETIME ftDeferredTime,         // The time are which the tracing site
                                        // released the message.
    IN LPSTR    lpszADMDName,           // ADMD Name
    IN LPSTR    lpszCountryName,        // Country Name
    IN LPSTR    lpszPRMDId,             // PRMD Identifier
    IN LPSTR    lpszAttADMDName,        // Attempted ADMD Name
    IN LPSTR    lpszAttCountryName,     // Attempted Country Name
    IN LPSTR    lpszAttPRMDId,          // Attempted PRMD Identifier
    OUT LPTRACEENTRY lpTraceEntry);     // Pointer to trace entry address
                                        // variable.

//$--HrTraceCreateEntryList-----------------------------------------------------
//  Create a hop trace information list.
// -----------------------------------------------------------------------------
HRESULT HrTraceCreateEntryList(      // RETURNS: return code
    IN LONG     lAction,                // The routing action the tracing site
                                        // took.
    IN FILETIME ftArrivalTime,          // The time at which the communique
                                        // entered the tracing site.
    IN FILETIME ftDeferredTime,         // The time are which the tracing site
                                        // released the message.
    IN LPSTR    lpszADMDName,           // ADMD Name
    IN LPSTR    lpszCountryName,        // Country Name
    IN LPSTR    lpszPRMDId,             // PRMD Identifier
    IN LPSTR    lpszAttADMDName,        // Attempted ADMD Name
    IN LPSTR    lpszAttCountryName,     // Attempted Country Name
    IN LPSTR    lpszAttPRMDId,          // Attempted PRMD Identifier
    OUT LPTRACEINFO *lppTraceInfo);     // Pointer to hop trace address variable

//$--HrTraceAppendEntryList-----------------------------------------------------
//  Append to an existing hop trace information list.
// -----------------------------------------------------------------------------
HRESULT HrTraceAppendEntryList(      // RETURNS: return code
    IN LONG     lAction,                // The routing action the tracing site
                                        // took.
    IN FILETIME ftArrivalTime,          // The time at which the communique
                                        // entered the tracing site.
    IN FILETIME ftDeferredTime,         // The time are which the tracing site
                                        // released the message.
    IN LPSTR    lpszADMDName,           // ADMD Name
    IN LPSTR    lpszCountryName,        // Country Name
    IN LPSTR    lpszPRMDId,             // PRMD Identifier
    IN LPSTR    lpszAttADMDName,        // Attempted ADMD Name
    IN LPSTR    lpszAttCountryName,     // Attempted Country Name
    IN LPSTR    lpszAttPRMDId,          // Attempted PRMD Identifier
    IN OUT LPTRACEINFO *lppTraceInfo);  // Pointer to hop trace address variable

//$--HrTraceGotoEntry-----------------------------------------------------------
//  Goto the specified TRACEENTRY in a TRACEINFO
// -----------------------------------------------------------------------------
HRESULT HrTraceGotoEntry(            // RETURNS: return code
    IN LPTRACEINFO lpTraceInfo,         // pointer to TRACEINFO
    IN ULONG ulIndex,                   // index of TRACEENTRY in TRACEINFO
    OUT LPTRACEENTRY *lppTraceEntry);   // pointer to TRACEENTRY

//$--HrTraceGotoFirstEntry------------------------------------------------------
//  Goto the first TRACEENTRY in a TRACEINFO
// -----------------------------------------------------------------------------
HRESULT HrTraceGotoFirstEntry(       // RETURNS: return code
    IN LPTRACEINFO lpTraceInfo,         // pointer to TRACEINFO
    OUT ULONG *lpulIndex,               // index of TRACEENTRY in TRACEINFO
    OUT LPTRACEENTRY *lppTraceEntry);   // pointer to TRACEENTRY

//$--HrTraceGotoNextEntry-------------------------------------------------------
//  Goto the next TRACEENTRY in a TRACEINFO
// -----------------------------------------------------------------------------
HRESULT HrTraceGotoNextEntry(        // RETURNS: return code
    IN LPTRACEINFO lpTraceInfo,         // pointer to TRACEINFO
    IN OUT ULONG *lpulIndex,            // index of TRACEENTRY in TRACEINFO
    OUT LPTRACEENTRY *lppTraceEntry);   // pointer to TRACEENTRY

//$--HrTraceOpenEntry-----------------------------------------------------------
//  Open a TRACEENTRY.
// -----------------------------------------------------------------------------
HRESULT HrTraceOpenEntry(            // RETURNS: return code
    IN LPTRACEENTRY lpTraceEntry,       // pointer to TRACEENTRY
    OUT LONG     *plAction,             // The routing action the tracing site
                                        // took.
    OUT FILETIME *pftArrivalTime,       // The time at which the communique
                                        // entered the tracing site.
    OUT FILETIME *pftDeferredTime,      // The time are which the tracing site
                                        // released the message.
    OUT LPSTR    *lppszADMDName,        // ADMD Name
    OUT LPSTR    *lppszCountryName,     // Country Name
    OUT LPSTR    *lppszPRMDId,          // PRMD Identifier
    OUT LPSTR    *lppszAttADMDName,     // Attempted ADMD Name
    OUT LPSTR    *lppszAttCountryName,  // Attempted Country Name
    OUT LPSTR    *lppszAttPRMDId);      // Attempted PRMD Identifier

//$--HrTraceSetInfo-------------------------------------------------------------
//  Set the trace-info on a message.
// -----------------------------------------------------------------------------
HRESULT HrTraceSetInfo(              // RETURNS: return code
    IN LONG lAction,                    // pointer to action
    IN FILETIME *lpftArrivalTime,       // pointer to arrival time
    IN FILETIME *lpftDeferredTime,      // pointer to deferred time
    IN LPSTR lpszCountry,              // pointer to country
    IN LPSTR lpszADMD,                 // pointer to ADMD
    IN LPSTR lpszPRMD,                 // pointer to PRMD
    IN OUT LPMESSAGE lpMessage);        // pointer to message

//$--HrTraceUpdateInfo----------------------------------------------------------
//  Update the trace-info on a message.
// -----------------------------------------------------------------------------
HRESULT HrTraceUpdateInfo(              // RETURNS: return code
    IN LONG lAction,                    // pointer to action
    IN FILETIME *lpftArrivalTime,       // pointer to arrival time
    IN FILETIME *lpftDeferredTime,      // pointer to deferred time
    IN LPSTR lpszCountry,               // pointer to country
    IN LPSTR lpszADMD,                  // pointer to ADMD
    IN LPSTR lpszPRMD,                  // pointer to PRMD
    IN OUT LPMESSAGE lpMessage);        // pointer to message

//$--HrInternalTraceCopyEntry---------------------------------------------------
//  Copy internal trace entry information to an internal trace entry structure.
// -----------------------------------------------------------------------------
HRESULT HrInternalTraceCopyEntry(       // RETURNS: return code
    IN LONG     lAction,                // The routing action the tracing site
                                        // took.
    IN FILETIME ftArrivalTime,          // The time at which the communique
                                        // entered the tracing site.
    IN FILETIME ftDeferredTime,         // The time are which the tracing site
                                        // released the message.
    IN LPSTR    lpszADMDName,           // ADMD Name
    IN LPSTR    lpszCountryName,        // Country Name
    IN LPSTR    lpszPRMDId,             // PRMD Identifier
    IN LPSTR    lpszMTAName,            // MTA Name
    IN LPSTR    lpszAttADMDName,        // Attempted ADMD Name
    IN LPSTR    lpszAttCountryName,     // Attempted Country Name
    IN LPSTR    lpszAttPRMDId,          // Attempted PRMD Identifier
    IN LPSTR    lpszAttMTAName,         // Attempted MTA Name
    OUT PINTTRACEENTRY lpTraceEntry);   // Pointer to trace entry address
                                        // variable.

//$--HrInternalTraceCreateEntryList---------------------------------------------
//  Create an internal hop trace information list.
// -----------------------------------------------------------------------------
HRESULT HrInternalTraceCreateEntryList( // RETURNS: return code
    IN LONG     lAction,                // The routing action the tracing site
                                        // took.
    IN FILETIME ftArrivalTime,          // The time at which the communique
                                        // entered the tracing site.
    IN FILETIME ftDeferredTime,         // The time are which the tracing site
                                        // released the message.
    IN LPSTR    lpszADMDName,           // ADMD Name
    IN LPSTR    lpszCountryName,        // Country Name
    IN LPSTR    lpszPRMDId,             // PRMD Identifier
    IN LPSTR    lpszMTAName,            // MTA Name
    IN LPSTR    lpszAttADMDName,        // Attempted ADMD Name
    IN LPSTR    lpszAttCountryName,     // Attempted Country Name
    IN LPSTR    lpszAttPRMDId,          // Attempted PRMD Identifier
    IN LPSTR    lpszAttMTAName,         // Attempted MTA Name
    OUT PINTTRACEINFO *lppTraceInfo);   // Pointer to hop trace address variable

//$--HrInternalTraceAppendEntryList---------------------------------------------
//  Append to an existing internal hop trace information list.
// -----------------------------------------------------------------------------
HRESULT HrInternalTraceAppendEntryList( // RETURNS: return code
    IN LONG     lAction,                // The routing action the tracing site
                                        // took.
    IN FILETIME ftArrivalTime,          // The time at which the communique
                                        // entered the tracing site.
    IN FILETIME ftDeferredTime,         // The time are which the tracing site
                                        // released the message.
    IN LPSTR    lpszADMDName,           // ADMD Name
    IN LPSTR    lpszCountryName,        // Country Name
    IN LPSTR    lpszPRMDId,             // PRMD Identifier
    IN LPSTR    lpszMTAName,            // MTA Name
    IN LPSTR    lpszAttADMDName,        // Attempted ADMD Name
    IN LPSTR    lpszAttCountryName,     // Attempted Country Name
    IN LPSTR    lpszAttPRMDId,          // Attempted PRMD Identifier
    IN LPSTR    lpszAttMTAName,         // Attempted MTA Name
    IN OUT PINTTRACEINFO *lppTraceInfo);// Pointer to hop trace address variable

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
