// --edkdebug.h-----------------------------------------------------------------
//
//  Functions to log debugging information in DEBUG builds.
// 
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------
#if !defined(_EDKDEBUG_H)
#define _EDKDEBUG_H

#include <stdio.h>
#include <stdarg.h>

// Default prefix for EDK debug log files.  By default, these files
// will be written to the temporary directory.  The name and path of the
// log files, can, however, be overriden by setting the EDK_DEBUG_FILE
// environment variable.
#define EDK_LOG_FILE_PREFIX		"edk"
#define EDK_LOG_FILE_SUFFIX		"log"

//$--DebugLevel-----------------------------------------------------------------
//  Available levels of debug.
// -----------------------------------------------------------------------------
typedef enum __DEBUGLEVEL
{
    D_PUBLIC = 0,   // log interface functions
    D_PRIVATE,      // log implementation functions
    D_ERROR,        // log errors
    D_WARNING,      // log warnings
    D_STATUS,       // log status
    D_ACTION,       // log starting/completed action
    D_OTHER,        // log other information
    D_LAST          // all debug levels are less than this 
} DEBUGLEVEL;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//------------------------------------------------------------------------------
//
// EDKLOG.C Functions
//
//------------------------------------------------------------------------------

//$--_WriteDebugString----------------------------------------------------------
//
//  Write a string to the debugger output window.
//  
// -----------------------------------------------------------------------------
void _WriteDebugString(                 // RETURNS: nothing
    IN LPSTR lpszFormat,                // format string
    ...);                               // arguments

//$--_StatusShowAssert----------------------------------------------------------
//
//  Status of the assert prompt.
//  
// -----------------------------------------------------------------------------
BOOL _StatusShowAssert(             // RETURNS: TRUE if assert prompt
    void);                          // no arguments

//$--_StatusDebugFile-----------------------------------------------------------
//
//  Status of the debug log file.
//  
// -----------------------------------------------------------------------------
BOOL _StatusDebugFile(              // RETURNS: nothing
    void);                          // no arguments

//$--_StatusDebugLevel----------------------------------------------------------
//
//  Status of the debug level.
//  
// -----------------------------------------------------------------------------
BOOL _StatusDebugLevel(             // RETURNS: nothing
    IN DEBUGLEVEL level);           // debug level

//$--_LockDebugFile-------------------------------------------------------------
//
//  Lock the debug log file.
//  
// -----------------------------------------------------------------------------
void _LockDebugFile(                // RETURNS: nothing
    void);                          // no arguments

//$--_UnlockDebugFile-----------------------------------------------------------
//
//  Unlock the debug log file.
//  
// -----------------------------------------------------------------------------
void _UnlockDebugFile(              // RETURNS: nothing
    void);                          // no arguments

//$--_WriteDebugFile------------------------------------------------------------
//
//  Write to the debug log file.
//  
// -----------------------------------------------------------------------------
void _WriteDebugFile(               // RETURNS: nothing
    IN LPSTR lpszFormat,            // format string
    ...);                           // arguments

//$--_InitDebugFile-------------------------------------------------------------
//
//  Initialize the debug log file.
//  
// -----------------------------------------------------------------------------
void _InitDebugFile(                // RETURNS: nothing
    void);                          // no arguments


//------------------------------------------------------------------------------
//
// EDKDEBUG.C Functions
//
//------------------------------------------------------------------------------

//$--_Assert--------------------------------------------------------------------
//  
//  Write to the debug log file and/or evaluate assertion.
//  
// -----------------------------------------------------------------------------
void _Assert(                   // RETURNS: nothing
    IN LPSTR lpszTag,           // tag name
    IN LPSTR lpszFile,          // source file name
    IN ULONG ulLine,            // source line number
    IN DEBUGLEVEL Level,        // assertion level
    IN BOOL fValue,             // assertion value
    IN LPSTR lpszFormat,        // format string
    ...);                       // arguments

//------------------------------------------------------------------------------
//
// MEMORY.C Functions
//
//------------------------------------------------------------------------------

#ifndef _PRIVATE_EDKDEBUG_H

//$--_DebugHeapCheck------------------------------------------------------------
//  Writes an entry in the debug log. This function is only called in
//  DEBUG builds through the DebugHeapCheck() macro.
// -----------------------------------------------------------------------------
void _DebugHeapCheck(                   // RETURNS: return code
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile);                 // file name

//$--_DebugDumpHeap-------------------------------------------------------------
//  Writes an entry in the debug log. This function is only called in
//  DEBUG builds through the DebugDumpHeap() macro.
// -----------------------------------------------------------------------------
void _DebugDumpHeap(                    // RETURNS: nothing
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile);                 // file name

//$--EDKDBG_MAPIAllocateBuffer--------------------------------------------------
//  Wrapper for MAPIAllocateBuffer().
// -----------------------------------------------------------------------------
SCODE EDKDBG_MAPIAllocateBuffer(        // RETURNS: status code
    IN  ULONG ulLine,                   // line number
    IN  LPSTR lpszFile,                 // file name
    IN  ULONG ulSize,                   // size of memory block
    OUT LPVOID *lppv);                  // pointer to memory block address
                                        // variable

//$--EDKDBG_MAPIAllocateMore----------------------------------------------------
//  Wrapper for MAPIAllocateMore().
// -----------------------------------------------------------------------------
SCODE EDKDBG_MAPIAllocateMore(          // RETURNS: status code
    IN  ULONG ulLine,                   // line number
    IN  LPSTR lpszFile,                 // file name
    IN  ULONG ulSize,                   // size of memory block
    IN  LPVOID lpvOriginal,             // pointer to original memory block
    OUT LPVOID *lppvData);              // pointer to memory block address
                                        // variable

//$--EDKDBG_MAPIFreeBuffer------------------------------------------------------
//  Wrapper for MAPIFreeBuffer().
// -----------------------------------------------------------------------------
SCODE EDKDBG_MAPIFreeBuffer(            // RETURNS: status code
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN LPVOID lpv);                     // pointer to memory block

//$--EDKDBG_malloc--------------------------------------------------------------
//  Wrapper for malloc().
// -----------------------------------------------------------------------------
LPVOID EDKDBG_malloc(                   // RETURNS: pointer to memory block
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN ULONG ulSize);                   // size of memory block

//$--EDKDBG_calloc--------------------------------------------------------------
//  Wrapper for calloc().
// -----------------------------------------------------------------------------
LPVOID EDKDBG_calloc(                   // RETURNS: pointer to memory block
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN ULONG ulNum,                     // number of elements
    IN ULONG ulSize);                   // size of element

//$--EDKDBG_realloc-------------------------------------------------------------
//  Wrapper for realloc().
// -----------------------------------------------------------------------------
LPVOID EDKDBG_realloc(                  // RETURNS: pointer to memory block
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN LPVOID lpvBlock,                 // pointer to memory block
    IN ULONG ulSize);                   // new size of memory block

//$--EDKDBG_strdup--------------------------------------------------------------
//  Wrapper for strdup().
// -----------------------------------------------------------------------------
char* EDKDBG_strdup(                    // RETURNS: pointer to allocated string
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN const char *lpsz);               // pointer to string

//$--EDKDBG_wcsdup--------------------------------------------------------------
//  Wrapper for wcsdup().
// -----------------------------------------------------------------------------
wchar_t* EDKDBG_wcsdup(                 // RETURNS: pointer to allocated string
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN const wchar_t *lpsz);            // pointer to string

//$--EDKDBG_free----------------------------------------------------------------
//  Wrapper for free().
// -----------------------------------------------------------------------------
void EDKDBG_free(                       // RETURNS: nothing
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN LPVOID lpv);                     // pointer to memory block

//$--EDKDBG_GlobalAlloc---------------------------------------------------------
//  Wrapper for GlobalAlloc().
// -----------------------------------------------------------------------------
HGLOBAL EDKDBG_GlobalAlloc(             // RETURNS: pointer to memory block
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN UINT  fuFlags,                   // allocation flags
    IN DWORD dwSize);                   // size of memory block

//$--EDKDBG_GlobalReAlloc-------------------------------------------------------
//  Wrapper for GlobalReAlloc().
// -----------------------------------------------------------------------------
HGLOBAL EDKDBG_GlobalReAlloc(           // RETURNS: pointer to memory block
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN HGLOBAL hglb,                    // pointer to memory block
    IN DWORD cbBytes,                   // new size of memory block
    IN UINT  fuFlags);                  // allocation flags

//$--EDKDBG_GlobalFree----------------------------------------------------------
//  Wrapper for GlobalFree().
// -----------------------------------------------------------------------------
HGLOBAL EDKDBG_GlobalFree(              // RETURNS: nothing
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN HGLOBAL hglb);                   // pointer to memory block

//$--EDKDBG_LocalAlloc---------------------------------------------------------
//  Wrapper for LocalAlloc().
// -----------------------------------------------------------------------------
HGLOBAL EDKDBG_LocalAlloc(              // RETURNS: pointer to memory block
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN UINT  fuFlags,                   // allocation flags
    IN DWORD dwSize);                   // size of memory block

//$--EDKDBG_LocalReAlloc-------------------------------------------------------
//  Wrapper for LocalReAlloc().
// -----------------------------------------------------------------------------
HGLOBAL EDKDBG_LocalReAlloc(            // RETURNS: pointer to memory block
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN HLOCAL hgbl,                     // pointer to memory block
    IN DWORD cbBytes,                   // new size of memory block
    IN UINT  fuFlags);                  // allocation flags

//$--EDKDBG_LocalFree----------------------------------------------------------
//  Wrapper for LocalFree().
// -----------------------------------------------------------------------------
HGLOBAL EDKDBG_LocalFree(               // RETURNS: nothing
    IN ULONG ulLine,                    // line number
    IN LPSTR lpszFile,                  // file name
    IN HGLOBAL hgbl);                   // pointer to memory block

//$--EDKDBG_HrLog---------------------------------------------------------------
//  Log an HRESULT (and the last Win32 error) to the debug log.
// -----------------------------------------------------------------------------
HRESULT EDKDBG_HrLog(                   // RETURNS: HRESULT
    IN LPSTR lpszFile,                  // file name
    IN ULONG ulLine,                    // line number
    IN HRESULT hr,                      // function return code
    IN DWORD dwLastError);              // last Win32 error

//$--EDKDBG_HrFailed------------------------------------------------------------
//  Log an HRESULT (and the last Win32 error) to the debug log.
// -----------------------------------------------------------------------------
BOOL EDKDBG_HrFailed(                   // RETURNS: HRESULT
    IN LPSTR lpszFile,                  // file name
    IN ULONG ulLine,                    // line number
    IN HRESULT hr,                      // function return code
    IN DWORD dwLastError);              // last Win32 error

#define _QUOTE(x) # x
#define QUOTE(x) _QUOTE(x)

// Use __FILE__LINE__ as a string containing "File.x(line#)" for example:
//     #pragma message( __FILE__LINE__ "Remove this line after testing.")
// The above example will display the file name and line number in the build window
// in such a way as to allow you to double click on it to go to the line.
#define __FILE__LINE__ __FILE__ "(" QUOTE(__LINE__) ") : "


#define TEST_STRING_PTR(x)        \
    (((x) != NULL) && (!IsBadStringPtr((x), (INFINITE))))
#define TEST_STRINGA_PTR(x)       \
    (((x) != NULL) && (!IsBadStringPtrA(x, (INFINITE))))
#define TEST_STRINGW_PTR(x)       \
    (((x) != NULL) && (!IsBadStringPtrW(x, (INFINITE))))
#define TEST_READ_PTR(x, y)    \
    (((x) != NULL) && (!IsBadReadPtr((x),(y))))
#define TEST_WRITE_PTR(x, y)   \
    (((x) != NULL) && (!IsBadWritePtr((x),(y))))
#define TEST_FUNCTION_PTR(x)   \
    (((x) != NULL) && (!IsBadCodePtr((x))))

#define TEST_STRING_PTR_OR_NULL(x)        \
    (((x) == NULL) || (!IsBadStringPtr((x), (INFINITE))))
#define TEST_STRINGA_PTR_OR_NULL(x)        \
    (((x) == NULL) || (!IsBadStringPtrA((x), (INFINITE))))
#define TEST_STRINGW_PTR_OR_NULL(x)        \
    (((x) == NULL) || (!IsBadStringPtrW((x), (INFINITE))))
#define TEST_READ_PTR_OR_NULL(x, y)    \
    (((x) == NULL) || (!IsBadReadPtr((x),(y))))
#define TEST_WRITE_PTR_OR_NULL(x, y)   \
    (((x) == NULL) || (!IsBadWritePtr((x),(y))))
#define TEST_FUNCTION_PTR_OR_NULL(x)   \
    (((x) == NULL) || (!IsBadCodePtr((x))))
#define TEST_IUNKNOWN_PTR(x) \
    (((x) != NULL) && !FBadUnknown((x)))

#ifdef DEBUG

#define HR_LOG(_hr) EDKDBG_HrLog(__FILE__, __LINE__, (_hr), GetLastError())

#ifdef FAILED
#undef FAILED
#endif
#define FAILED(_hr) EDKDBG_HrFailed(__FILE__, __LINE__, (_hr), GetLastError())

#ifdef SUCCEEDED
#undef SUCCEEDED
#endif
#define SUCCEEDED(_hr) (!EDKDBG_HrFailed(__FILE__, __LINE__, (_hr), GetLastError()))

#ifdef HR_FAILED
#undef HR_FAILED
#endif
#define HR_FAILED(_hr) FAILED(_hr)

#ifdef HR_SUCCEEDED
#undef HR_SUCCEEDED
#endif
#define HR_SUCCEEDED(_hr) SUCCEEDED(_hr)

#define RETURN(_hr) return(EDKDBG_HrLog(__FILE__, __LINE__, (_hr), GetLastError()))

#define DEBUGPUBLIC(x) \
    { _Assert("DEBUG", __FILE__, __LINE__, D_PUBLIC, TRUE, "%s\n", (x)); }

#define DEBUGPRIVATE(x) \
    { _Assert("DEBUG", __FILE__, __LINE__, D_PRIVATE, TRUE, "%s\n", (x)); }

#define DEBUGACTION(x) \
    { _Assert("DEBUG", __FILE__, __LINE__, D_ACTION, TRUE, "%s\n", (x)); }


#define MODULE_ERROR(x) \
    { _Assert("ASSERT", __FILE__, __LINE__, D_ERROR, FALSE, "%s\n", (x)); }

#define MODULE_WARNING(x) \
    { _Assert("ASSERT", __FILE__, __LINE__, D_WARNING, FALSE, "%s\n", (x)); }

#define MODULE_STATUS(x) \
    { _Assert("ASSERT", __FILE__, __LINE__, D_STATUS, FALSE, "%s\n", (x)); }

#define MODULE_ERROR1(x, y) \
    { _Assert("ASSERT", __FILE__, __LINE__, D_ERROR, FALSE, (x"\n"), (y)); }

#define MODULE_ERROR2(x, y, z) \
    { _Assert("ASSERT", __FILE__, __LINE__, D_ERROR, FALSE, (x"\n"), (y), (z)); }

#define MODULE_WARNING1(x, y) \
    { _Assert("ASSERT", __FILE__, __LINE__, D_WARNING, FALSE, (x"\n"), (y)); }

#define MODULE_WARNING2(x, y, z) \
    { _Assert("ASSERT", __FILE__, __LINE__, D_WARNING, FALSE, (x"\n"), (y), (z)); }

#define MODULE_STATUS1(x, y) \
    { _Assert("ASSERT", __FILE__, __LINE__, D_STATUS, FALSE, (x"\n"), (y)); }

#define MODULE_STATUS2(x, y, z) \
    { _Assert("ASSERT", __FILE__, __LINE__, D_STATUS, FALSE, (x"\n"), (y), (z)); }


#define ASSERTERROR(x, y) \
    { _Assert("ASSERT", __FILE__, __LINE__, D_ERROR, (x), (y"\n")); }

#define ASSERTWARNING(x, y) \
    { _Assert("ASSERT", __FILE__, __LINE__, D_WARNING, (x), (y"\n")); }

#define ASSERT_STRING_PTR(x, y)     ASSERTERROR(TEST_STRING_PTR(x), y)
#define ASSERT_STRINGA_PTR(x, y)    ASSERTERROR(TEST_STRINGA_PTR(x), y)
#define ASSERT_STRINGW_PTR(x, y)    ASSERTERROR(TEST_STRINGW_PTR(x), y)
#define ASSERT_READ_PTR(x, y, z)    ASSERTERROR(TEST_READ_PTR(x, y), z)
#define ASSERT_WRITE_PTR(x, y, z)   ASSERTERROR(TEST_WRITE_PTR(x, y), z)
#define ASSERT_FUNCTION_PTR(x, y)   ASSERTERROR(TEST_FUNCTION_PTR(x), y)

#define ASSERT_IUNKNOWN_PTR(x, y)   ASSERTERROR(TEST_IUNKNOWN_PTR(x), y)

#define ASSERT_STRING_PTR_OR_NULL(x, y)   \
    ASSERTERROR(TEST_STRING_PTR_OR_NULL(x), y)
#define ASSERT_STRINGA_PTR_OR_NULL(x, y)  \
    ASSERTERROR(TEST_STRINGA_PTR_OR_NULL(x), y)
#define ASSERT_STRINGW_PTR_OR_NULL(x, y)  \
    ASSERTERROR(TEST_STRINGW_PTR_OR_NULL(x), y)
#define ASSERT_READ_PTR_OR_NULL(x, y, z)  \
    ASSERTERROR(TEST_READ_PTR_OR_NULL(x, y), z)
#define ASSERT_WRITE_PTR_OR_NULL(x, y, z) \
    ASSERTERROR(TEST_WRITE_PTR_OR_NULL(x, y), z)
#define ASSERT_FUNCTION_PTR_OR_NULL(x, y) \
    ASSERTERROR(TEST_FUNCTION_PTR_OR_NULL(x), y)

#define OUTPUTDEBUGSTRING(_sz) \
    OutputDebugString("error: " __FILE__ ", " QUOTE(__LINE__) ", " _sz "\n");

#else

#define HR_LOG(_hr)                         (_hr)

#define RETURN(_hr)                         return((_hr))

#define DEBUGPUBLIC(x)                      ((void)0)

#define DEBUGPRIVATE(x)                     ((void)0)

#define DEBUGACTION(x)                      ((void)0)


#define MODULE_ERROR(x)                     ((void)0)

#define MODULE_WARNING(x)                   ((void)0)

#define MODULE_STATUS(x)                    ((void)0)

#define MODULE_ERROR1(x, y)                 ((void)0)

#define MODULE_ERROR2(x, y, z)              ((void)0)

#define MODULE_WARNING1(x, y)               ((void)0)

#define MODULE_WARNING2(x, y, z)            ((void)0)

#define MODULE_STATUS1(x, y)                ((void)0)

#define MODULE_STATUS2(x, y, z)             ((void)0)


#define ASSERTERROR(x, y)                   ((void)0)

#define ASSERTWARNING(x, y)                 ((void)0)

#define ASSERT_STRING_PTR(x, y)             ((void)0)

#define ASSERT_STRINGA_PTR(x, y)            ((void)0)

#define ASSERT_STRINGW_PTR(x, y)            ((void)0)

#define ASSERT_READ_PTR(x, y, z)            ((void)0)

#define ASSERT_WRITE_PTR(x, y, z)           ((void)0)

#define ASSERT_FUNCTION_PTR(x, y)           ((void)0)

#define ASSERT_IUNKNOWN_PTR(x, y)           ((void)0)

#define ASSERT_STRING_PTR_OR_NULL(x, y)     ((void)0)

#define ASSERT_STRINGA_PTR_OR_NULL(x, y)    ((void)0)
                                            
#define ASSERT_STRINGW_PTR_OR_NULL(x, y)    ((void)0)

#define ASSERT_READ_PTR_OR_NULL(x, y, z)    ((void)0)

#define ASSERT_WRITE_PTR_OR_NULL(x, y, z)   ((void)0)

#define ASSERT_FUNCTION_PTR_OR_NULL(x, y)   ((void)0)

#define OUTPUTDEBUGSTRING(x)                ((void)0)

#endif

//
// Memory allocation function wrappers
//

#ifndef _PRIVATE_MEMORY_H

#ifdef DEBUG

#define DEBUG_HEAP_CHECK    _DebugHeapCheck(__LINE__,__FILE__)

#define DEBUG_DUMP_HEAP     _DebugDumpHeap(__LINE__,__FILE__)

#define MAPIAllocateBuffer(x, y)    \
    EDKDBG_MAPIAllocateBuffer(__LINE__,__FILE__,(x),(y))

#define MAPIAllocateMore(x, y, z)   \
    EDKDBG_MAPIAllocateMore(__LINE__,__FILE__,(x),(y),(z))

#define MAPIFreeBuffer(x)           \
    EDKDBG_MAPIFreeBuffer(__LINE__,__FILE__,(x))

#define malloc(x)                   \
    EDKDBG_malloc(__LINE__,__FILE__,(x))

#define calloc(x, y)                \
    EDKDBG_calloc(__LINE__,__FILE__,(x),(y))

#define realloc(x, y)                \
    EDKDBG_realloc(__LINE__,__FILE__,(x),(y))

#define GlobalAlloc(x, y)            \
    EDKDBG_GlobalAlloc(__LINE__,__FILE__,(x),(y))

#define GlobalReAlloc(x, y, z)       \
    EDKDBG_GlobalReAlloc(__LINE__,__FILE__,(x),(y),(z))

#ifdef GlobalDiscard
#undef GlobalDiscard
#endif
#define GlobalDiscard(x)             \
    EDKDBG_GlobalReAlloc(__LINE__,__FILE__,(x),0,GMEM_MOVEABLE)

#define GlobalFree(x)                \
    EDKDBG_GlobalFree(__LINE__,__FILE__,(x))

#define LocalAlloc(x, y)            \
    EDKDBG_LocalAlloc(__LINE__,__FILE__,(x),(y))

#define LocalReAlloc(x, y, z)       \
    EDKDBG_LocalReAlloc(__LINE__,__FILE__,(x),(y),(z))

#ifdef LocalDiscard
#undef LocalDiscard
#endif
#define LocalDiscard(x)             \
    EDKDBG_LocalReAlloc(__LINE__,__FILE__,(x),0,GMEM_MOVEABLE)

#define LocalFree(x)                \
    EDKDBG_LocalFree(__LINE__,__FILE__,(x))

#ifdef strdup
#undef strdup
#endif
#define strdup(x)                    \
    EDKDBG_strdup(__LINE__,__FILE__,(x))

#define _strdup(x)                   \
    EDKDBG_strdup(__LINE__,__FILE__,(x))

#define _wcsdup(x)                   \
    EDKDBG_wcsdup(__LINE__,__FILE__,(x))

#define free(x)                     \
    EDKDBG_free(__LINE__,__FILE__,(x))

#else

#define DEBUG_HEAP_CHECK              ((void)0)

#define DEBUG_DUMP_HEAP               ((void)0)

#endif

#endif // _PRIVATE_MEMORY_H


//------------------------------------------------------------------------------
//
// Inline parameter checking functions
//
//------------------------------------------------------------------------------

//$--CHK_main-------------------------------------------------------------------
//  Check the parameters for main() functions.
// -----------------------------------------------------------------------------
__inline static HRESULT CHK_main(		// RETURNS: HRESULT
	IN int argc,						// number of arguments on command line
	IN char *argv[])					// array of command line arguments
{
	HRESULT		hr		= NOERROR;
	int			i		= 0;

	if (argc < 0)
	{
		hr = HR_LOG(E_INVALIDARG);
		goto cleanup;
	}

	for (i = 0; i < argc; i++)
	{
		if (!TEST_STRINGA_PTR(argv[i]))
		{
			hr = HR_LOG(E_INVALIDARG);
			goto cleanup;
		}
	}

cleanup:
	return(hr);
}


#endif // _PRIVATE_EDKDEBUG_H

#ifdef __cplusplus
}
#endif

#endif
