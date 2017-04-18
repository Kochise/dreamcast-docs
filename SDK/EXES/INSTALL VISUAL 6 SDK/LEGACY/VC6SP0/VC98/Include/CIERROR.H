#ifndef _CIERROR_H_
#define _CIERROR_H_
#ifndef FACILITY_WINDOWS
//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_WINDOWS                 0x8
#define FACILITY_NULL                    0x0
#define FACILITY_ITF                     0x4


//
// Define the severity codes
//
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_COFAIL           0x3
#define STATUS_SEVERITY_COERROR          0x2


//
// MessageId: NOT_AN_ERROR1
//
// MessageText:
//
//  NOTE:  This dummy error message is necessary to force MC to output
//         the above defines inside the FACILITY_WINDOWS guard instead
//         of leaving it empty.
//
#define NOT_AN_ERROR1                    ((HRESULT)0x00081600L)

#endif // FACILITY_WINDOWS
//
// Range 0x1600-0x1850 is reserved by Content Index.
//
//
// Codes 0x1600-0x164f are reserved for QUERY
//
//
// MessageId: QUERY_E_FAILED
//
// MessageText:
//
//  Call failed for unknown reason.
//
#define QUERY_E_FAILED                   ((HRESULT)0x80041600L)

//
// MessageId: QUERY_E_INVALIDQUERY
//
// MessageText:
//
//  Invalid parameter.
//
#define QUERY_E_INVALIDQUERY             ((HRESULT)0x80041601L)

//
// MessageId: QUERY_E_INVALIDRESTRICTION
//
// MessageText:
//
//  The query restriction could not be parsed.
//
#define QUERY_E_INVALIDRESTRICTION       ((HRESULT)0x80041602L)

//
// MessageId: QUERY_E_INVALIDSORT
//
// MessageText:
//
//  An invalid sort order was requested.
//
#define QUERY_E_INVALIDSORT              ((HRESULT)0x80041603L)

//
// MessageId: QUERY_E_INVALIDCATEGORIZE
//
// MessageText:
//
//  An invalid categorization order was requested.
//
#define QUERY_E_INVALIDCATEGORIZE        ((HRESULT)0x80041604L)

//
// MessageId: QUERY_E_ALLNOISE
//
// MessageText:
//
//  The query contained only ignored words.
//
#define QUERY_E_ALLNOISE                 ((HRESULT)0x80041605L)

//
// MessageId: QUERY_E_TOOCOMPLEX
//
// MessageText:
//
//  The query was too complex to be executed.
//
#define QUERY_E_TOOCOMPLEX               ((HRESULT)0x80041606L)

//
// MessageId: QUERY_E_TIMEDOUT
//
// MessageText:
//
//  The query exceeded its execution time limit.
//
#define QUERY_E_TIMEDOUT                 ((HRESULT)0x80041607L)

//
// MessageId: QUERY_E_DUPLICATE_OUTPUT_COLUMN
//
// MessageText:
//
//  One or more columns in the output column list is a duplicate.
//
#define QUERY_E_DUPLICATE_OUTPUT_COLUMN  ((HRESULT)0x80041608L)

//
// MessageId: QUERY_E_INVALID_OUTPUT_COLUMN
//
// MessageText:
//
//  One or more columns in the output column list is not valid.
//
#define QUERY_E_INVALID_OUTPUT_COLUMN    ((HRESULT)0x80041609L)

//
// Codes 0x1650-0x167f are reserved for QUERYLIB (see qutil\h\qutilerr.mc)
//
//
// 0x1680 - 0x169F are Filter daemon error codes
//
//
// MessageId: FDAEMON_W_WORDLISTFULL
//
// MessageText:
//
//  Wordlist has reached maximum size.  Additional documents should not be filtered.
//
#define FDAEMON_W_WORDLISTFULL           ((HRESULT)0x00041680L)

//
// MessageId: FDAEMON_E_LOWRESOURCE
//
// MessageText:
//
//  The system is running out of one of more resources needed for filtering, usually memory.
//
#define FDAEMON_E_LOWRESOURCE            ((HRESULT)0x80041681L)

//
// MessageId: FDAEMON_E_FATALERROR
//
// MessageText:
//
//  A critical error occurred during document filtering.  Consult system administrator.
//
#define FDAEMON_E_FATALERROR             ((HRESULT)0x80041682L)

//
// MessageId: FDAEMON_E_PARTITIONDELETED
//
// MessageText:
//
//  Documents not stored in content index because partition has been deleted.
//
#define FDAEMON_E_PARTITIONDELETED       ((HRESULT)0x80041683L)

//
// MessageId: FDAEMON_E_CHANGEUPDATEFAILED
//
// MessageText:
//
//  Documents not stored in content index because update of changelist failed.
//
#define FDAEMON_E_CHANGEUPDATEFAILED     ((HRESULT)0x80041684L)

//
// MessageId: FDAEMON_W_EMPTYWORDLIST
//
// MessageText:
//
//  Final wordlist was empty.
//
#define FDAEMON_W_EMPTYWORDLIST          ((HRESULT)0x00041685L)

//
// MessageId: FDAEMON_E_WORDLISTCOMMITFAILED
//
// MessageText:
//
//  Commit of wordlist failed.  Data not available for query.
//
#define FDAEMON_E_WORDLISTCOMMITFAILED   ((HRESULT)0x80041686L)

//
// MessageId: FDAEMON_E_NOWORDLIST
//
// MessageText:
//
//  No wordlist is being constructed.  May happen after fatal filter error.
//
#define FDAEMON_E_NOWORDLIST             ((HRESULT)0x80041687L)

//
// MessageId: FDAEMON_E_TOOMANYFILTEREDBLOCKS
//
// MessageText:
//
//  During document filtering the limit on buffers has been exceeded.
//
#define FDAEMON_E_TOOMANYFILTEREDBLOCKS  ((HRESULT)0x80041688L)

//
// ISearch error codes
//
//
// MessageId: SEARCH_S_NOMOREHITS
//
// MessageText:
//
//  End of hits has been reached.
//
#define SEARCH_S_NOMOREHITS              ((HRESULT)0x000416A0L)

//
// MessageId: SEARCH_E_NOMONIKER
//
// MessageText:
//
//  Retrival of hits as monikers is not supported (by filter passed into Init).
//
#define SEARCH_E_NOMONIKER               ((HRESULT)0x800416A1L)

//
// MessageId: SEARCH_E_NOREGION
//
// MessageText:
//
//  Retrival of hits as filter regions is not supported (by filter passed into Init).
//
#define SEARCH_E_NOREGION                ((HRESULT)0x800416A2L)

//
// Filter error codes
//
//
// MessageId: FILTER_E_TOO_BIG
//
// MessageText:
//
//  File is too large to filter.
//
#define FILTER_E_TOO_BIG                 ((HRESULT)0x80041730L)

//
// MessageId: FILTER_S_PARTIAL_CONTENTSCAN_IMMEDIATE
//
// MessageText:
//
//  A partial content scan of the disk needs to be scheduled for immediate execution.
//
#define FILTER_S_PARTIAL_CONTENTSCAN_IMMEDIATE ((HRESULT)0x00041731L)

//
// MessageId: FILTER_S_FULL_CONTENTSCAN_IMMEDIATE
//
// MessageText:
//
//  A full content scan of the disk needs to be scheduled for immediate execution.
//
#define FILTER_S_FULL_CONTENTSCAN_IMMEDIATE ((HRESULT)0x00041732L)

//
// MessageId: FILTER_S_CONTENTSCAN_DELAYED
//
// MessageText:
//
//  A content scan of the disk needs to be scheduled for execution later.
//
#define FILTER_S_CONTENTSCAN_DELAYED     ((HRESULT)0x00041733L)

//
// MessageId: FILTER_E_CONTENTINDEXCORRUPT
//
// MessageText:
//
//  The content index is corrupt. A content scan will to be scheduled after chkdsk or autochk is run.
//
#define FILTER_E_CONTENTINDEXCORRUPT     ((HRESULT)0xC0041734L)

//
// MessageId: FILTER_S_DISK_FULL
//
// MessageText:
//
//  The disk is getting full.
//
#define FILTER_S_DISK_FULL               ((HRESULT)0x00041735L)

//
// MessageId: FILTER_E_ALREADY_OPEN
//
// MessageText:
//
//  A file is already open. Cannot open another one while a file is open.
//
#define FILTER_E_ALREADY_OPEN            ((HRESULT)0x80041736L)

//
// MessageId: FILTER_E_UNREACHABLE
//
// MessageText:
//
//  The file is not reachable.
//
#define FILTER_E_UNREACHABLE             ((HRESULT)0x80041737L)

//
// MessageId: FILTER_E_IN_USE
//
// MessageText:
//
//  The document is in use by another process.
//
#define FILTER_E_IN_USE                  ((HRESULT)0x80041738L)

//
// MessageId: FILTER_E_NOT_OPEN
//
// MessageText:
//
//  The document is not opened.
//
#define FILTER_E_NOT_OPEN                ((HRESULT)0x80041739L)

//
// MessageId: FILTER_S_NO_PROPSETS
//
// MessageText:
//
//  The document has no property sets.
//
#define FILTER_S_NO_PROPSETS             ((HRESULT)0x0004173AL)

//
// MessageId: FILTER_E_NO_SUCH_PROPERTY
//
// MessageText:
//
//  There is no property with the given GUID.
//
#define FILTER_E_NO_SUCH_PROPERTY        ((HRESULT)0x8004173BL)

//
// MessageId: FILTER_S_NO_SECURITY_DESCRIPTOR
//
// MessageText:
//
//  The document has no security descriptor.
//
#define FILTER_S_NO_SECURITY_DESCRIPTOR  ((HRESULT)0x0004173CL)

//
// Word breaker error codes
//
//
// MessageId: WBREAK_E_END_OF_TEXT
//
// MessageText:
//
//  End of text reached in text source.
//
#define WBREAK_E_END_OF_TEXT             ((HRESULT)0x80041780L)

//
// MessageId: LANGUAGE_S_LARGE_WORD
//
// MessageText:
//
//  Word larger than maximum length.  May be truncated by word sink.
//
#define LANGUAGE_S_LARGE_WORD            ((HRESULT)0x00041781L)

//
// MessageId: WBREAK_E_QUERY_ONLY
//
// MessageText:
//
//  Feature only available in query mode.
//
#define WBREAK_E_QUERY_ONLY              ((HRESULT)0x80041782L)

//
// MessageId: WBREAK_E_BUFFER_TOO_SMALL
//
// MessageText:
//
//  Buffer too small to hold composed phrase.
//
#define WBREAK_E_BUFFER_TOO_SMALL        ((HRESULT)0x80041783L)

//
// MessageId: LANGUAGE_E_DATABASE_NOT_FOUND
//
// MessageText:
//
//  Langauge database/cache file could not be found.
//
#define LANGUAGE_E_DATABASE_NOT_FOUND    ((HRESULT)0x80041784L)

//
// MessageId: WBREAK_E_INIT_FAILED
//
// MessageText:
//
//  Initialization of word breaker failed.
//
#define WBREAK_E_INIT_FAILED             ((HRESULT)0x80041785L)

//
// MessageId: PSINK_E_QUERY_ONLY
//
// MessageText:
//
//  Feature only available in query mode.
//
#define PSINK_E_QUERY_ONLY               ((HRESULT)0x80041790L)

//
// MessageId: PSINK_E_INDEX_ONLY
//
// MessageText:
//
//  Feature only available in index mode.
//
#define PSINK_E_INDEX_ONLY               ((HRESULT)0x80041791L)

//
// MessageId: PSINK_E_LARGE_ATTACHMENT
//
// MessageText:
//
//  Attachment type beyond valid range.
//
#define PSINK_E_LARGE_ATTACHMENT         ((HRESULT)0x80041792L)

//
// MessageId: PSINK_S_LARGE_WORD
//
// MessageText:
//
//  Word larger than maximum length.  May be truncated by phrase sink.
//
#define PSINK_S_LARGE_WORD               ((HRESULT)0x00041793L)

//
// Content Index Framework Error Codes
//
//
// MessageId: CI_CORRUPT_DATABASE
//
// MessageText:
//
//  The content index is corrupt.
//
#define CI_CORRUPT_DATABASE              ((HRESULT)0xC0041800L)

//
// MessageId: CI_CORRUPT_CATALOG
//
// MessageText:
//
//  The content index meta data is corrupt.
//
#define CI_CORRUPT_CATALOG               ((HRESULT)0xC0041801L)

//
// MessageId: CI_INVALID_PARTITION
//
// MessageText:
//
//  The content index partition is invalid.
//
#define CI_INVALID_PARTITION             ((HRESULT)0xC0041802L)

//
// MessageId: CI_INVALID_PRIORITY
//
// MessageText:
//
//  The priority is invalid.
//
#define CI_INVALID_PRIORITY              ((HRESULT)0xC0041803L)

//
// MessageId: CI_NO_STARTING_KEY
//
// MessageText:
//
//  There is no starting key.
//
#define CI_NO_STARTING_KEY               ((HRESULT)0xC0041804L)

//
// MessageId: CI_OUT_OF_INDEX_IDS
//
// MessageText:
//
//  The content index is out of index ids.
//
#define CI_OUT_OF_INDEX_IDS              ((HRESULT)0xC0041805L)

//
// MessageId: CI_NO_CATALOG
//
// MessageText:
//
//  There is no catalog.
//
#define CI_NO_CATALOG                    ((HRESULT)0xC0041806L)

//
// MessageId: CI_CORRUPT_FILTER_BUFFER
//
// MessageText:
//
//  The filter buffer is corrupt.
//
#define CI_CORRUPT_FILTER_BUFFER         ((HRESULT)0xC0041807L)

//
// MessageId: CI_INVALID_INDEX
//
// MessageText:
//
//  The index is invalid.
//
#define CI_INVALID_INDEX                 ((HRESULT)0xC0041808L)

//
// MessageId: CI_PROPSTORE_INCONSISTENCY
//
// MessageText:
//
//  Inconsistency in property store detected.
//
#define CI_PROPSTORE_INCONSISTENCY       ((HRESULT)0xC0041809L)

//
// MessageId: CI_E_ALREADY_INITIALIZED
//
// MessageText:
//
//  The object is already initialzed.
//
#define CI_E_ALREADY_INITIALIZED         ((HRESULT)0x8004180AL)

//
// MessageId: CI_E_NOT_INITIALIZED
//
// MessageText:
//
//  The object is not initialzed.
//
#define CI_E_NOT_INITIALIZED             ((HRESULT)0x8004180BL)

//
// MessageId: CI_E_BUFFERTOOSMALL
//
// MessageText:
//
//  The buffer is too small.
//
#define CI_E_BUFFERTOOSMALL              ((HRESULT)0x8004180CL)

//
// MessageId: CI_E_PROPERTY_NOT_CACHED
//
// MessageText:
//
//  The given property is not cached.
//
#define CI_E_PROPERTY_NOT_CACHED         ((HRESULT)0x8004180DL)

//
// MessageId: CI_S_WORKID_DELETED
//
// MessageText:
//
//  The workid is deleted.
//
#define CI_S_WORKID_DELETED              ((HRESULT)0x0004180EL)

//
// MessageId: CI_E_INVALID_STATE
//
// MessageText:
//
//  The object is not in a valid state.
//
#define CI_E_INVALID_STATE               ((HRESULT)0x8004180FL)

//
// MessageId: CI_E_FILTERING_DISABLED
//
// MessageText:
//
//  Filtering is disabled in this content index.
//
#define CI_E_FILTERING_DISABLED          ((HRESULT)0x80041810L)

//
// MessageId: CI_E_DISK_FULL
//
// MessageText:
//
//  The disk is full and the specified operation cannot be done.
//
#define CI_E_DISK_FULL                   ((HRESULT)0x80041811L)

//
// MessageId: CI_E_SHUTDOWN
//
// MessageText:
//
//  Content Index has been shutdown.
//
#define CI_E_SHUTDOWN                    ((HRESULT)0x80041812L)

//
// MessageId: CI_E_WORKID_NOTVALID
//
// MessageText:
//
//  The workid is not valid.
//
#define CI_E_WORKID_NOTVALID             ((HRESULT)0x80041813L)

//
// MessageId: CI_S_END_OF_ENUMERATION
//
// MessageText:
//
//  There are no more documents to enumerate.
//
#define CI_S_END_OF_ENUMERATION          ((HRESULT)0x00041814L)    

//
// MessageId: CI_E_NOT_FOUND
//
// MessageText:
//
//  The object was not found.
//
#define CI_E_NOT_FOUND                   ((HRESULT)0x80041815L)

//
// MessageId: CI_E_USE_DEFAULT_PID
//
// MessageText:
//
//  The passed-in property id is not supported.
//
#define CI_E_USE_DEFAULT_PID             ((HRESULT)0x80041816L)

//
// MessageId: CI_E_DUPLICATE_NOTIFICATION
//
// MessageText:
//
//  There were two notifications for the same workid.
//
#define CI_E_DUPLICATE_NOTIFICATION      ((HRESULT)0x80041817L)

//
// MessageId: CI_E_UPDATES_DISABLED
//
// MessageText:
//
//  A document update was rejected because updates were disabled.
//
#define CI_E_UPDATES_DISABLED            ((HRESULT)0x80041818L)

//
// MessageId: CI_E_INVALID_FLAGS_COMBINATION
//
// MessageText:
//
//  The combination of flags specified is invalid.
//
#define CI_E_INVALID_FLAGS_COMBINATION   ((HRESULT)0x80041819L)

//
// MessageId: CI_E_OUTOFSEQ_INCREMENT_DATA
//
// MessageText:
//
//  The incremental data given to Load is not valid. It may be out of sequence.
//
#define CI_E_OUTOFSEQ_INCREMENT_DATA     ((HRESULT)0x8004181AL)

//
// MessageId: CI_E_SHARING_VIOLATION
//
// MessageText:
//
//  A sharing or locking violation caused a failure.
//
#define CI_E_SHARING_VIOLATION           ((HRESULT)0x8004181BL)

//
// MessageId: CI_E_LOGON_FAILURE
//
// MessageText:
//
//  A logon permission violation caused a failure.
//
#define CI_E_LOGON_FAILURE               ((HRESULT)0x8004181CL)

//
// MessageId: CI_E_NO_CATALOG
//
// MessageText:
//
//  There is no catalog.
//
#define CI_E_NO_CATALOG                  ((HRESULT)0x8004181DL)

//
// MessageId: CI_E_STRANGE_PAGEORSECTOR_SIZE
//
// MessageText:
//
//  Page size is not an integral multiple of the sector size of the volume where index is located.
//
#define CI_E_STRANGE_PAGEORSECTOR_SIZE   ((HRESULT)0x8004181EL)

//
// MessageId: CI_E_TIMEOUT
//
// MessageText:
//
//  Service is too busy.
//
#define CI_E_TIMEOUT                     ((HRESULT)0x8004181FL)

//
// MessageId: CI_E_NOT_RUNNING
//
// MessageText:
//
//  Service is not running.
//
#define CI_E_NOT_RUNNING                 ((HRESULT)0x80041820L)

//
// MessageId: CI_INCORRECT_VERSION
//
// MessageText:
//
//  The content index data on disk is for the wrong version.
//
#define CI_INCORRECT_VERSION             ((HRESULT)0xC0041821L)

#endif // _CIERROR_H_
