/*++ BUILD Version: 0093     Increment this if a change has global effects

Copyright (c) 1990-1998  Microsoft Corporation

Module Name:

    winnt.h

Abstract:

    This module defines the 32-Bit Windows types and constants that are
    defined by NT, but exposed through the Win32 API.

Revision History:

--*/

#ifndef _WINNT_
#define _WINNT_

#include <ctype.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* These two are not in the Win95 winnt.h */
typedef unsigned int size_t;
#define offsetof(s,m) ((size_t)&(((s*)0)->m))

#define ANYSIZE_ARRAY 1
#if !defined(_M_IX86)
#define UNALIGNED __unaligned
#else
#define UNALIGNED
#endif

#if (defined(_M_MRX000) || defined(_M_IX86) || defined(_M_ALPHA) || defined(_M_PPC)) && !defined(MIDL_PASS)
#	define DECLSPEC_IMPORT __declspec(dllimport)
#else
#	define DECLSPEC_IMPORT
#endif

typedef void *PVOID;

#if (_MSC_VER >= 800)
#define NTAPI __stdcall
#else
#define _cdecl
#define NTAPI
#endif

//
// Define API decoration for direct importing system DLL references.
//

#if !defined(_NTSYSTEM_)
#define NTSYSAPI DECLSPEC_IMPORT
#else
#define NTSYSAPI
#endif

//
// Basics
//

#ifndef VOID
#define VOID void
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
#endif

typedef LONG HRESULT;

//
// UNICODE (Wide Character) types
//

typedef wchar_t WCHAR;    // wc,   16-bit UNICODE character

typedef WCHAR *PWCHAR;
typedef WCHAR *LPWCH, *PWCH;
typedef CONST WCHAR *LPCWCH, *PCWCH;
typedef WCHAR *NWPSTR;
typedef WCHAR *LPWSTR, *PWSTR;

typedef CONST WCHAR *LPCWSTR, *PCWSTR;

//
// ANSI (Multi-byte Character) types
//
typedef CHAR *PCHAR;
typedef CHAR *LPCH, *PCH;

typedef CONST CHAR *LPCCH, *PCCH;
typedef CHAR *NPSTR;
typedef CHAR *LPSTR, *PSTR;
typedef CONST CHAR *LPCSTR, *PCSTR;

//
// Neutral ANSI/UNICODE types and macros
//
#ifdef  UNICODE

#ifndef _TCHAR_DEFINED
typedef WCHAR TCHAR, *PTCHAR;
typedef WCHAR TBYTE , *PTBYTE ;
#define _TCHAR_DEFINED
#endif /* !_TCHAR_DEFINED */

typedef LPWSTR LPTCH, PTCH;
typedef LPWSTR PTSTR, LPTSTR;
typedef LPCWSTR LPCTSTR;
typedef LPWSTR LP;
#define __TEXT(quote) L##quote

#else   /* UNICODE */

#ifndef _TCHAR_DEFINED
typedef char TCHAR, *PTCHAR;
typedef unsigned char TBYTE , *PTBYTE ;
#define _TCHAR_DEFINED
#endif /* !_TCHAR_DEFINED */

typedef LPSTR LPTCH, PTCH;
typedef LPSTR PTSTR, LPTSTR;
typedef LPCSTR LPCTSTR;
#define __TEXT(quote) quote

#endif /* UNICODE */
#define TEXT(quote) __TEXT(quote)


typedef SHORT *PSHORT;
typedef LONG *PLONG;

#ifdef STRICT
typedef void *HANDLE;
#define DECLARE_HANDLE(name) struct name##__ { int unused; }; typedef struct name##__ *name
#else
typedef PVOID HANDLE;
#define DECLARE_HANDLE(name) typedef HANDLE name
#endif
typedef HANDLE *PHANDLE;

typedef char CCHAR;
typedef DWORD LCID;
typedef PDWORD PLCID;
typedef WORD   LANGID;
/*lint -e624 */
/*lint +e624 */
#define APPLICATION_ERROR_MASK       0x20000000
#define ERROR_SEVERITY_SUCCESS       0x00000000
#define ERROR_SEVERITY_INFORMATIONAL 0x40000000
#define ERROR_SEVERITY_WARNING       0x80000000
#define ERROR_SEVERITY_ERROR         0xC0000000

//
// __int64 is only supported by 2.0 and later midl.
// __midl is set by the 2.0 midl and not by 1.0 midl.
//

#if (!defined(MIDL_PASS) || defined(__midl)) && (!defined(_M_IX86) || (defined(_INTEGRAL_MAX_BITS) && _INTEGRAL_MAX_BITS >= 64))
typedef __int64 LONGLONG;
typedef unsigned __int64 DWORDLONG;
#else
typedef double LONGLONG;
typedef double DWORDLONG;
#endif

typedef LONGLONG *PLONGLONG;
typedef DWORDLONG *PDWORDLONG;

#if defined(MIDL_PASS)
typedef struct _LARGE_INTEGER {
#else // MIDL_PASS
typedef union _LARGE_INTEGER {
    struct {
        DWORD LowPart;
        LONG HighPart;
    };
    struct {
        DWORD LowPart;
        LONG HighPart;
    } u;
#endif //MIDL_PASS
    LONGLONG QuadPart;
} LARGE_INTEGER;

typedef LARGE_INTEGER *PLARGE_INTEGER;


#if defined(MIDL_PASS)
typedef struct _ULARGE_INTEGER {
#else // MIDL_PASS
typedef union _ULARGE_INTEGER {
    struct {
        DWORD LowPart;
        DWORD HighPart;
    };
    struct {
        DWORD LowPart;
        DWORD HighPart;
    } u;
#endif //MIDL_PASS
    DWORDLONG QuadPart;
} ULARGE_INTEGER;

typedef ULARGE_INTEGER *PULARGE_INTEGER;

// end_ntminiport end_ntndis

//
// Locally Unique Identifier
//

typedef LARGE_INTEGER LUID, *PLUID;


#define UNICODE_NULL ((WCHAR)0)
typedef BYTE  BOOLEAN;
typedef BOOLEAN *PBOOLEAN;
//
//  Doubly linked list structure.  Can be used as either a list head, or
//  as link words.
//

typedef struct _LIST_ENTRY {
   struct _LIST_ENTRY *Flink;
   struct _LIST_ENTRY *Blink;
} LIST_ENTRY;
typedef LIST_ENTRY *PLIST_ENTRY;

//
//  Singly linked list structure. Can be used as either a list head, or
//  as link words.
//

typedef struct _SINGLE_LIST_ENTRY {
    struct _SINGLE_LIST_ENTRY *Next;
} SINGLE_LIST_ENTRY, *PSINGLE_LIST_ENTRY;
#define MINCHAR     0x80
#define MAXCHAR     0x7f
#define MINSHORT    0x8000
#define MAXSHORT    0x7fff
#define MINLONG     0x80000000
#define MAXLONG     0x7fffffff
#define MAXBYTE     0xff
#define MAXWORD     0xffff
#define MAXDWORD    0xffffffff
//
// Calculate the byte offset of a field in a structure of type type.
//

#define FIELD_OFFSET(type, field)    ((LONG)&(((type *)0)->field))


//
// Calculate the address of the base of the structure given its type, and an
// address of a field within the structure.
//

#define CONTAINING_RECORD(address, type, field) ((type *)( \
                                                  (PCHAR)(address) - \
                                                  (PCHAR)(&((type *)0)->field)))

#define HEAP_NO_SERIALIZE               0x00000001      
#define HEAP_GENERATE_EXCEPTIONS        0x00000004      
#define HEAP_ZERO_MEMORY                0x00000008
#define HEAP_REALLOC_IN_PLACE_ONLY		0x00000010

/*
 *  Language IDs.
 *
 *  The following two combinations of primary language ID and
 *  sublanguage ID have special semantics:
 *
 *    Primary Language ID   Sublanguage ID      Result
 *    -------------------   ---------------     ------------------------
 *    LANG_NEUTRAL          SUBLANG_NEUTRAL     Language neutral
 *    LANG_NEUTRAL          SUBLANG_DEFAULT     User default language
 *    LANG_NEUTRAL          SUBLANG_SYS_DEFAULT System default language
 */

/*
 *  Primary language IDs.
 */
#define LANG_NEUTRAL                     0x00

#define LANG_ARABIC							  0x01
#define LANG_BULGARIAN                   0x02
#define LANG_CHINESE                     0x04
#define LANG_CROATIAN                    0x1a
#define LANG_CZECH                       0x05
#define LANG_DANISH                      0x06
#define LANG_DUTCH                       0x13
#define LANG_ENGLISH                     0x09
#define LANG_FINNISH                     0x0b
#define LANG_FRENCH                      0x0c
#define LANG_GERMAN                      0x07
#define LANG_GREEK                       0x08
#define LANG_HEBREW							  0x0D
#define LANG_HUNGARIAN                   0x0e
#define LANG_ICELANDIC                   0x0f
#define LANG_ITALIAN                     0x10
#define LANG_JAPANESE                    0x11
#define LANG_KOREAN                      0x12
#define LANG_NORWEGIAN                   0x14
#define LANG_POLISH                      0x15
#define LANG_PORTUGUESE                  0x16
#define LANG_ROMANIAN                    0x18
#define LANG_RUSSIAN                     0x19
#define LANG_SLOVAK                      0x1b
#define LANG_SLOVENIAN                   0x24
#define LANG_SPANISH                     0x0a
#define LANG_SWEDISH                     0x1d
#define LANG_TURKISH                     0x1f

/*
 *  Sublanguage IDs.
 *
 *  The name immediately following SUBLANG_ dictates which primary
 *  language ID that sublanguage ID can be combined with to form a
 *  valid language ID.
 */
#define SUBLANG_NEUTRAL                  0x00    /* language neutral */
#define SUBLANG_DEFAULT                  0x01    /* user default */
#define SUBLANG_SYS_DEFAULT              0x02    /* system default */

#define SUBLANG_CHINESE_TRADITIONAL      0x01    /* Chinese (Taiwan) */
#define SUBLANG_CHINESE_SIMPLIFIED       0x02    /* Chinese (PR China) */
#define SUBLANG_CHINESE_HONGKONG         0x03    /* Chinese (Hong Kong) */
#define SUBLANG_CHINESE_SINGAPORE        0x04    /* Chinese (Singapore) */
#define SUBLANG_DUTCH                    0x01    /* Dutch */
#define SUBLANG_DUTCH_BELGIAN            0x02    /* Dutch (Belgian) */
#define SUBLANG_ENGLISH_US               0x01    /* English (USA) */
#define SUBLANG_ENGLISH_UK               0x02    /* English (UK) */
#define SUBLANG_ENGLISH_AUS              0x03    /* English (Australian) */
#define SUBLANG_ENGLISH_CAN              0x04    /* English (Canadian) */
#define SUBLANG_ENGLISH_NZ               0x05    /* English (New Zealand) */
#define SUBLANG_ENGLISH_EIRE             0x06    /* English (Irish) */
#define SUBLANG_FRENCH                   0x01    /* French */
#define SUBLANG_FRENCH_BELGIAN           0x02    /* French (Belgian) */
#define SUBLANG_FRENCH_CANADIAN          0x03    /* French (Canadian) */
#define SUBLANG_FRENCH_SWISS             0x04    /* French (Swiss) */
#define SUBLANG_GERMAN                   0x01    /* German */
#define SUBLANG_GERMAN_SWISS             0x02    /* German (Swiss) */
#define SUBLANG_GERMAN_AUSTRIAN          0x03    /* German (Austrian) */
#define SUBLANG_ITALIAN                  0x01    /* Italian */
#define SUBLANG_ITALIAN_SWISS            0x02    /* Italian (Swiss) */
#define SUBLANG_NORWEGIAN_BOKMAL         0x01    /* Norwegian (Bokmal) */
#define SUBLANG_NORWEGIAN_NYNORSK        0x02    /* Norwegian (Nynorsk) */
#define SUBLANG_PORTUGUESE               0x02    /* Portuguese */
#define SUBLANG_PORTUGUESE_BRAZILIAN     0x01    /* Portuguese (Brazilian) */
#define SUBLANG_SPANISH                  0x01    /* Spanish (Castilian) */
#define SUBLANG_SPANISH_MEXICAN          0x02    /* Spanish (Mexican) */
#define SUBLANG_SPANISH_MODERN           0x03    /* Spanish (Modern) */

/*
 *  Sorting IDs.
 *
 */
#define SORT_DEFAULT                     0x0     /* sorting default */

#define SORT_JAPANESE_XJIS               0x0     /* Japanese XJIS order */
#define SORT_JAPANESE_UNICODE            0x1     /* Japanese Unicode order */

#define SORT_CHINESE_BIG5                0x0     /* Chinese BIG5 order */
#define SORT_CHINESE_UNICODE             0x1     /* Chinese Unicode order */
#define SORT_CHINESE_PRC                 0x2     // PRC Chinese Stroke Count order

#define SORT_KOREAN_KSC                  0x0     /* Korean KSC order */
#define SORT_KOREAN_UNICODE              0x1     /* Korean Unicode order */


/*
 *  A language ID is a 16 bit value which is the combination of a
 *  primary language ID and a secondary language ID.  The bits are
 *  allocated as follows:
 *
 *       +-----------------------+-------------------------+
 *       |     Sublanguage ID    |   Primary Language ID   |
 *       +-----------------------+-------------------------+
 *        15                   10 9                       0   bit
 *
 *
 *  Language ID creation/extraction macros:
 *
 *    MAKELANGID    - construct language id from a primary language id and
 *                    a sublanguage id.
 *    PRIMARYLANGID - extract primary language id from a language id.
 *    SUBLANGID     - extract sublanguage id from a language id.
 */
#define MAKELANGID(p, s)       ((((WORD  )(s)) << 10) | (WORD  )(p))
#define PRIMARYLANGID(lgid)    ((WORD  )(lgid) & 0x3ff)
#define SUBLANGID(lgid)        ((WORD  )(lgid) >> 10)

/*
 *  A locale ID is a 32 bit value which is the combination of a
 *  language ID, a sort ID, and a reserved area.  The bits are
 *  allocated as follows:
 *
 *       +-------------+---------+-------------------------+
 *       |   Reserved  | Sort ID |      Language ID        |
 *       +-------------+---------+-------------------------+
 *        31         20 19     16 15                      0   bit
 *
 *
 *  Locale ID creation/extraction macros:
 *
 *    MAKELCID       - construct locale id from a language id and a sort id.
 *    LANGIDFROMLCID - extract language id from a locale id.
 *    SORTIDFROMLCID - extract sort id from a locale id.
 */
#define NLS_VALID_LOCALE_MASK  0x000fffff

#define MAKELCID(lgid, srtid)  ((DWORD)((((DWORD)((WORD  )(srtid))) << 16) |  \
                                         ((DWORD)((WORD  )(lgid)))))
#define LANGIDFROMLCID(lcid)   ((WORD  )(lcid))
#define SORTIDFROMLCID(lcid)   ((WORD  )((((DWORD)(lcid)) & NLS_VALID_LOCALE_MASK) >> 16))

/*
 *  Default System and User IDs for language and locale.
 */
#define LANG_SYSTEM_DEFAULT    (MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT))
#define LANG_USER_DEFAULT      (MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT))

#define LOCALE_SYSTEM_DEFAULT  (MAKELCID(LANG_SYSTEM_DEFAULT, SORT_DEFAULT))
#define LOCALE_USER_DEFAULT    (MAKELCID(LANG_USER_DEFAULT, SORT_DEFAULT))

#define LOCALE_NEUTRAL (MAKELCID(MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), SORT_DEFAULT))

// begin_ntminiport begin_ntndis

//
// Macros used to eliminate compiler warning generated when formal
// parameters or local variables are not declared.
//
// Use DBG_UNREFERENCED_PARAMETER() when a parameter is not yet
// referenced but will be once the module is completely developed.
//
// Use DBG_UNREFERENCED_LOCAL_VARIABLE() when a local variable is not yet
// referenced but will be once the module is completely developed.
//
// Use UNREFERENCED_PARAMETER() if a parameter will never be referenced.
//
// DBG_UNREFERENCED_PARAMETER and DBG_UNREFERENCED_LOCAL_VARIABLE will
// eventually be made into a null macro to help determine whether there
// is unfinished work.
//

#if ! (defined(lint) || defined(_lint))
#define UNREFERENCED_PARAMETER(P)          (P)
#define DBG_UNREFERENCED_PARAMETER(P)      (P)
#define DBG_UNREFERENCED_LOCAL_VARIABLE(V) (V)

#else // lint or _lint

// Note: lint -e530 says don't complain about uninitialized variables for
// this.  line +e530 turns that checking back on.  Error 527 has to do with
// unreachable code.

#define UNREFERENCED_PARAMETER(P)          \
    /*lint -e527 -e530 */ \
    { \
        (P) = (P); \
    } \
    /*lint +e527 +e530 */
#define DBG_UNREFERENCED_PARAMETER(P)      \
    /*lint -e527 -e530 */ \
    { \
        (P) = (P); \
    } \
    /*lint +e527 +e530 */
#define DBG_UNREFERENCED_LOCAL_VARIABLE(V) \
    /*lint -e527 -e530 */ \
    { \
        (V) = (V); \
    } \
    /*lint +e527 +e530 */

#endif // lint or _lint


/*lint -save -e767 */
#define STATUS_SUCCESS                   ((DWORD   )0x00000000L)
#define STATUS_UNSUCCESSFUL              ((DWORD   )0xC0000001L)
#define STATUS_WAIT_0                    ((DWORD   )0x00000000L)
#define STATUS_ABANDONED_WAIT_0          ((DWORD   )0x00000080L)
#define STATUS_USER_APC                  ((DWORD   )0x000000C0L)
#define STATUS_TIMEOUT                   ((DWORD   )0x00000102L)
#define STATUS_PENDING                   ((DWORD   )0x00000103L)
#define STATUS_GUARD_PAGE_VIOLATION      ((DWORD   )0x80000001L)
#define STATUS_DATATYPE_MISALIGNMENT     ((DWORD   )0x80000002L)
#define STATUS_BREAKPOINT                ((DWORD   )0x80000003L)
#define STATUS_SINGLE_STEP               ((DWORD   )0x80000004L)
#define STATUS_ACCESS_VIOLATION          ((DWORD   )0xC0000005L)
#define STATUS_IN_PAGE_ERROR             ((DWORD   )0xC0000006L)
#define STATUS_INVALID_PARAMETER         ((DWORD   )0xC000000DL)
#define STATUS_NO_MEMORY                 ((DWORD   )0xC0000017L)
#define STATUS_INVALID_SYSTEM_SERVICE 	 ((DWORD   )0xC000001CL)
#define STATUS_ILLEGAL_INSTRUCTION       ((DWORD   )0xC000001DL)
#define STATUS_NONCONTINUABLE_EXCEPTION  ((DWORD   )0xC0000025L)
#define STATUS_INVALID_DISPOSITION       ((DWORD   )0xC0000026L)
#define STATUS_ARRAY_BOUNDS_EXCEEDED     ((DWORD   )0xC000008CL)
#define STATUS_FLOAT_DENORMAL_OPERAND    ((DWORD   )0xC000008DL)
#define STATUS_FLOAT_DIVIDE_BY_ZERO      ((DWORD   )0xC000008EL)
#define STATUS_FLOAT_INEXACT_RESULT      ((DWORD   )0xC000008FL)
#define STATUS_FLOAT_INVALID_OPERATION   ((DWORD   )0xC0000090L)
#define STATUS_FLOAT_OVERFLOW            ((DWORD   )0xC0000091L)
#define STATUS_FLOAT_STACK_CHECK         ((DWORD   )0xC0000092L)
#define STATUS_FLOAT_UNDERFLOW           ((DWORD   )0xC0000093L)
#define STATUS_INTEGER_DIVIDE_BY_ZERO    ((DWORD   )0xC0000094L)
#define STATUS_INTEGER_OVERFLOW          ((DWORD   )0xC0000095L)
#define STATUS_PRIVILEGED_INSTRUCTION    ((DWORD   )0xC0000096L)
#define STATUS_STACK_OVERFLOW            ((DWORD   )0xC00000FDL)
#define STATUS_USER_BREAK                ((DWORD   )0x80000113L)
#define STATUS_CONTROL_C_EXIT            ((DWORD   )0xC000013AL)
#define STATUS_INSTRUCTION_MISALIGNMENT  ((DWORD   )0xC00000AAL)
/*lint -restore */
#define MAXIMUM_WAIT_OBJECTS 64     // Maximum number of wait objects

#define MAXIMUM_SUSPEND_COUNT MAXCHAR // Maximum times thread can be suspended
typedef DWORD KSPIN_LOCK;

#ifdef x86

//
// Disable these two pramas that evaluate to "sti" "cli" on x86 so that driver
// writers to not leave them inadvertantly in their code.
//

#if !defined(MIDL_PASS)
#if !defined(RC_INVOKED)

#pragma warning(disable:4164)   // disable C4164 warning so that apps that
                                // build with /Od don't get weird errors !
#ifdef _M_IX86
#pragma function(_enable)
#pragma function(_disable)
#endif

#pragma warning(default:4164)   // reenable C4164 warning

#endif
#endif


//
//  Define the size of the 80387 save area, which is in the context frame.
//

#define SIZE_OF_80387_REGISTERS      80

//
// The following flags control the contents of the CONTEXT structure.
//

#define CONTEXT_i386    0x00010000    // this assumes that i386 and
#define CONTEXT_i486    0x00010000    // i486 have identical context records

#define CONTEXT_CONTROL         (CONTEXT_i386 | 0x00000001L) // SS:SP, CS:IP, FLAGS, BP
#define CONTEXT_INTEGER         (CONTEXT_i386 | 0x00000002L) // AX, BX, CX, DX, SI, DI
#define CONTEXT_SEGMENTS        (CONTEXT_i386 | 0x00000004L) // DS, ES, FS, GS
#define CONTEXT_FLOATING_POINT  (CONTEXT_i386 | 0x00000008L) // 387 state
#define CONTEXT_DEBUG_REGISTERS (CONTEXT_i386 | 0x00000010L) // DB 0-3,6,7

#define CONTEXT_FULL (CONTEXT_CONTROL | CONTEXT_INTEGER |\
                      CONTEXT_SEGMENTS)

typedef struct _FLOATING_SAVE_AREA {
    DWORD   ControlWord;
    DWORD   StatusWord;
    DWORD   TagWord;
    DWORD   ErrorOffset;
    DWORD   ErrorSelector;
    DWORD   DataOffset;
    DWORD   DataSelector;
    BYTE    RegisterArea[SIZE_OF_80387_REGISTERS];
    DWORD   Cr0NpxState;
} FLOATING_SAVE_AREA;

typedef FLOATING_SAVE_AREA *PFLOATING_SAVE_AREA;

//
// Context Frame
//
//  This frame has a several purposes: 1) it is used as an argument to
//  NtContinue, 2) is is used to constuct a call frame for APC delivery,
//  and 3) it is used in the user level thread creation routines.
//
//  The layout of the record conforms to a standard call frame.
//

typedef struct _CONTEXT {

    //
    // The flags values within this flag control the contents of
    // a CONTEXT record.
    //
    // If the context record is used as an input parameter, then
    // for each portion of the context record controlled by a flag
    // whose value is set, it is assumed that that portion of the
    // context record contains valid context. If the context record
    // is being used to modify a threads context, then only that
    // portion of the threads context will be modified.
    //
    // If the context record is used as an IN OUT parameter to capture
    // the context of a thread, then only those portions of the thread's
    // context corresponding to set flags will be returned.
    //
    // The context record is never used as an OUT only parameter.
    //

    DWORD ContextFlags;

    //
    // This section is specified/returned if CONTEXT_DEBUG_REGISTERS is
    // set in ContextFlags.  Note that CONTEXT_DEBUG_REGISTERS is NOT
    // included in CONTEXT_FULL.
    //

    DWORD   Dr0;
    DWORD   Dr1;
    DWORD   Dr2;
    DWORD   Dr3;
    DWORD   Dr6;
    DWORD   Dr7;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_FLOATING_POINT.
    //

    FLOATING_SAVE_AREA FloatSave;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_SEGMENTS.
    //

    DWORD   SegGs;
    DWORD   SegFs;
    DWORD   SegEs;
    DWORD   SegDs;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_INTEGER.
    //

    DWORD   Edi;
    DWORD   Esi;
    DWORD   Ebx;
    DWORD   Edx;
    DWORD   Ecx;
    DWORD   Eax;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_CONTROL.
    //

    DWORD   Ebp;
    DWORD   Eip;
    DWORD   SegCs;              // MUST BE SANITIZED
    DWORD   EFlags;             // MUST BE SANITIZED
    DWORD   Esp;
    DWORD   SegSs;

} CONTEXT;



typedef CONTEXT *PCONTEXT;

// begin_ntminiport

#endif //_X86_

typedef struct _LDT_ENTRY {
    WORD    LimitLow;
    WORD    BaseLow;
    union {
        struct {
            BYTE    BaseMid;
            BYTE    Flags1;     // Declare as bytes to avoid alignment
            BYTE    Flags2;     // Problems.
            BYTE    BaseHi;
        } Bytes;
        struct {
            DWORD   BaseMid : 8;
            DWORD   Type : 5;
            DWORD   Dpl : 2;
            DWORD   Pres : 1;
            DWORD   LimitHi : 4;
            DWORD   Sys : 1;
            DWORD   Reserved_0 : 1;
            DWORD   Default_Big : 1;
            DWORD   Granularity : 1;
            DWORD   BaseHi : 8;
        } Bits;
    } HighWord;
} LDT_ENTRY, *PLDT_ENTRY;


#if defined(SHx)

//These are the debug or break registers on the SH3
typedef struct _DEBUG_REGISTERS {
    ULONG  BarA;
    UCHAR  BasrA;
    UCHAR  BamrA;
    USHORT BbrA;
    ULONG  BarB;
    UCHAR  BasrB;
    UCHAR  BamrB;
    USHORT BbrB;
    ULONG  BdrB;
    ULONG  BdmrB;
    USHORT Brcr;
    USHORT Align;
} DEBUG_REGISTERS, *PDEBUG_REGISTERS;

//
// The following flags control the contents of the CONTEXT structure.
//

#define CONTEXT_SH3		0x00000040
#define CONTEXT_SH4		0x000000c0	// CONTEXT_SH3 | 0x80 - must contain the SH3 bits

#ifdef SH3
#define CONTEXT_CONTROL         (CONTEXT_SH3 | 0x00000001L)
#define CONTEXT_INTEGER         (CONTEXT_SH3 | 0x00000002L)
#define CONTEXT_DEBUG_REGISTERS (CONTEXT_SH3 | 0x00000008L)
#define CONTEXT_FULL (CONTEXT_CONTROL | CONTEXT_INTEGER | CONTEXT_DEBUG_REGISTERS)
#else	// SH4
#define CONTEXT_CONTROL         (CONTEXT_SH4 | 0x00000001L)
#define CONTEXT_INTEGER         (CONTEXT_SH4 | 0x00000002L)
#define CONTEXT_DEBUG_REGISTERS (CONTEXT_SH4 | 0x00000008L)
#define CONTEXT_FLOATING_POINT  (CONTEXT_SH4 | 0x00000004L)
#define CONTEXT_FULL (CONTEXT_CONTROL | CONTEXT_INTEGER | CONTEXT_DEBUG_REGISTERS | CONTEXT_FLOATING_POINT)
#endif
//
// Context Frame
//
//  This frame is used to store a limited processor context into the
// Thread structure for CPUs which have no floating point support.
//

typedef struct _CONTEXT {
    //
    // The flags values within this flag control the contents of
    // a CONTEXT record.
    //
    // If the context record is used as an input parameter, then
    // for each portion of the context record controlled by a flag
    // whose value is set, it is assumed that that portion of the
    // context record contains valid context. If the context record
    // is being used to modify a thread's context, then only that
    // portion of the threads context will be modified.
    //
    // If the context record is used as an IN OUT parameter to capture
    // the context of a thread, then only those portions of the thread's
    // context corresponding to set flags will be returned.
    //
    // The context record is never used as an OUT only parameter.
    //

    ULONG ContextFlags;

    //
    // This section is specified/returned if the ContextFlags word contains
    // the flag CONTEXT_INTEGER.
    //
    // N.B. The registers RA and R15 are defined in this section, but are
    //  considered part of the control context rather than part of the integer
    //  context.
    //

	ULONG PR;
	ULONG MACH;
	ULONG MACL;
	ULONG GBR;
	ULONG R0;
	ULONG R1;
	ULONG R2;
	ULONG R3;
	ULONG R4;
	ULONG R5;
	ULONG R6;
	ULONG R7;
	ULONG R8;
	ULONG R9;
	ULONG R10;
	ULONG R11;
	ULONG R12;
	ULONG R13;
	ULONG R14;
	ULONG R15;

    //
    // This section is specified/returned if the ContextFlags word contains
    // the flag CONTEXT_CONTROL.
    //
    // N.B. The registers r15 and ra are defined in the integer section,
    //   but are considered part of the control context rather than part of
    //   the integer context.
    //

    ULONG Fir;
    ULONG Psr;

#if !defined(SH3e) && !defined(SH4)
	ULONG	OldStuff[2];
    DEBUG_REGISTERS DebugRegisters;
#else
	ULONG	Fpscr;
	ULONG	Fpul;
	ULONG	FRegs[16];
#if defined(SH4)
	ULONG	xFRegs[16];
#endif
#endif
} CONTEXT;

typedef CONTEXT *PCONTEXT;

#endif // SHx


#if defined(MIPS)

// begin_ntddk begin_nthal
//
// The following flags control the contents of the CONTEXT structure.
//

#define CONTEXT_R4000   0x00010000    // r4000 context

#define CONTEXT_CONTROL         (CONTEXT_R4000 | 0x00000001L)
#define CONTEXT_FLOATING_POINT  (CONTEXT_R4000 | 0x00000002L)
#define CONTEXT_INTEGER         (CONTEXT_R4000 | 0x00000004L)

#define CONTEXT_FULL (CONTEXT_CONTROL | CONTEXT_FLOATING_POINT | CONTEXT_INTEGER)

//
// Context Frame
//
//  N.B. This frame must be exactly a multiple of 16 bytes in length.
//
//  This frame has a several purposes: 1) it is used as an argument to
//  NtContinue, 2) it is used to constuct a call frame for APC delivery,
//  3) it is used to construct a call frame for exception dispatching
//  in user mode, and 4) it is used in the user level thread creation
//  routines.
//
//  The layout of the record conforms to a standard call frame.
//

typedef struct _CONTEXT {

    //
    // This section is always present and is used as an argument build
    // area.
    //

    DWORD Argument[4];

    //
    // This section is specified/returned if the ContextFlags word contains
    // the flag CONTEXT_FLOATING_POINT.
    //

    DWORD FltF0;
    DWORD FltF1;
    DWORD FltF2;
    DWORD FltF3;
    DWORD FltF4;
    DWORD FltF5;
    DWORD FltF6;
    DWORD FltF7;
    DWORD FltF8;
    DWORD FltF9;
    DWORD FltF10;
    DWORD FltF11;
    DWORD FltF12;
    DWORD FltF13;
    DWORD FltF14;
    DWORD FltF15;
    DWORD FltF16;
    DWORD FltF17;
    DWORD FltF18;
    DWORD FltF19;
    DWORD FltF20;
    DWORD FltF21;
    DWORD FltF22;
    DWORD FltF23;
    DWORD FltF24;
    DWORD FltF25;
    DWORD FltF26;
    DWORD FltF27;
    DWORD FltF28;
    DWORD FltF29;
    DWORD FltF30;
    DWORD FltF31;

    //
    // This section is specified/returned if the ContextFlags word contains
    // the flag CONTEXT_INTEGER.
    //
    // N.B. The registers gp, sp, and ra are defined in this section, but are
    //  considered part of the control context rather than part of the integer
    //  context.
    //
    // N.B. Register zero is not stored in the frame.
    //

    DWORD IntZero;
    DWORD IntAt;
    DWORD IntV0;
    DWORD IntV1;
    DWORD IntA0;
    DWORD IntA1;
    DWORD IntA2;
    DWORD IntA3;
    DWORD IntT0;
    DWORD IntT1;
    DWORD IntT2;
    DWORD IntT3;
    DWORD IntT4;
    DWORD IntT5;
    DWORD IntT6;
    DWORD IntT7;
    DWORD IntS0;
    DWORD IntS1;
    DWORD IntS2;
    DWORD IntS3;
    DWORD IntS4;
    DWORD IntS5;
    DWORD IntS6;
    DWORD IntS7;
    DWORD IntT8;
    DWORD IntT9;
    DWORD IntK0;
    DWORD IntK1;
    DWORD IntGp;
    DWORD IntSp;
    DWORD IntS8;
    DWORD IntRa;
    DWORD IntLo;
    DWORD IntHi;

    //
    // This section is specified/returned if the ContextFlags word contains
    // the flag CONTEXT_FLOATING_POINT.
    //

    DWORD Fsr;

    //
    // This section is specified/returned if the ContextFlags word contains
    // the flag CONTEXT_CONTROL.
    //
    // N.B. The registers gp, sp, and ra are defined in the integer section,
    //   but are considered part of the control context rather than part of
    //   the integer context.
    //

    DWORD Fir;
    DWORD Psr;

    //
    // The flags values within this flag control the contents of
    // a CONTEXT record.
    //
    // If the context record is used as an input parameter, then
    // for each portion of the context record controlled by a flag
    // whose value is set, it is assumed that that portion of the
    // context record contains valid context. If the context record
    // is being used to modify a thread's context, then only that
    // portion of the threads context will be modified.
    //
    // If the context record is used as an IN OUT parameter to capture
    // the context of a thread, then only those portions of the thread's
    // context corresponding to set flags will be returned.
    //
    // The context record is never used as an OUT only parameter.
    //

    DWORD ContextFlags;

    DWORD Fill[2];
} CONTEXT, *PCONTEXT;

// end_ntddk end_nthal

#endif // MIPS


#if defined(MIPS)

VOID
__jump_unwind (
    PVOID Fp,
    PVOID TargetPc
    );

#endif // MIPS


#if defined(PPC)

// begin_ntddk begin_nthal
//
// The following flags control the contents of the CONTEXT structure.
//

#define CONTEXT_CONTROL         0x00000001L
#define CONTEXT_FLOATING_POINT  0x00000002L
#define CONTEXT_INTEGER         0x00000004L
#define CONTEXT_DEBUG_REGISTERS 0x00000008L

#define CONTEXT_FULL (CONTEXT_CONTROL | CONTEXT_FLOATING_POINT | CONTEXT_INTEGER)

//
// Context Frame
//
//  N.B. This frame must be exactly a multiple of 16 bytes in length.
//
//  This frame has a several purposes: 1) it is used as an argument to
//  NtContinue, 2) it is used to constuct a call frame for APC delivery,
//  3) it is used to construct a call frame for exception dispatching
//  in user mode, and 4) it is used in the user level thread creation
//  routines.
//
//  Requires at least 8-byte alignment (double)
//

typedef struct _CONTEXT {

    //
    // This section is specified/returned if the ContextFlags word contains
    // the flag CONTEXT_FLOATING_POINT.
    //

    double Fpr0;                        // Floating registers 0..31
    double Fpr1;
    double Fpr2;
    double Fpr3;
    double Fpr4;
    double Fpr5;
    double Fpr6;
    double Fpr7;
    double Fpr8;
    double Fpr9;
    double Fpr10;
    double Fpr11;
    double Fpr12;
    double Fpr13;
    double Fpr14;
    double Fpr15;
    double Fpr16;
    double Fpr17;
    double Fpr18;
    double Fpr19;
    double Fpr20;
    double Fpr21;
    double Fpr22;
    double Fpr23;
    double Fpr24;
    double Fpr25;
    double Fpr26;
    double Fpr27;
    double Fpr28;
    double Fpr29;
    double Fpr30;
    double Fpr31;
    double Fpscr;                       // Floating point status/control reg

    //
    // This section is specified/returned if the ContextFlags word contains
    // the flag CONTEXT_INTEGER.
    //

    DWORD Gpr0;                         // General registers 0..31
    DWORD Gpr1;
    DWORD Gpr2;
    DWORD Gpr3;
    DWORD Gpr4;
    DWORD Gpr5;
    DWORD Gpr6;
    DWORD Gpr7;
    DWORD Gpr8;
    DWORD Gpr9;
    DWORD Gpr10;
    DWORD Gpr11;
    DWORD Gpr12;
    DWORD Gpr13;
    DWORD Gpr14;
    DWORD Gpr15;
    DWORD Gpr16;
    DWORD Gpr17;
    DWORD Gpr18;
    DWORD Gpr19;
    DWORD Gpr20;
    DWORD Gpr21;
    DWORD Gpr22;
    DWORD Gpr23;
    DWORD Gpr24;
    DWORD Gpr25;
    DWORD Gpr26;
    DWORD Gpr27;
    DWORD Gpr28;
    DWORD Gpr29;
    DWORD Gpr30;
    DWORD Gpr31;

    DWORD Cr;                           // Condition register
    DWORD Xer;                          // Fixed point exception register

    //
    // This section is specified/returned if the ContextFlags word contains
    // the flag CONTEXT_CONTROL.
    //

    DWORD Msr;                          // Machine status register
    DWORD Iar;                          // Instruction address register
    DWORD Lr;                           // Link register
    DWORD Ctr;                          // Count register

    //
    // The flags values within this flag control the contents of
    // a CONTEXT record.
    //
    // If the context record is used as an input parameter, then
    // for each portion of the context record controlled by a flag
    // whose value is set, it is assumed that that portion of the
    // context record contains valid context. If the context record
    // is being used to modify a thread's context, then only that
    // portion of the threads context will be modified.
    //
    // If the context record is used as an IN OUT parameter to capture
    // the context of a thread, then only those portions of the thread's
    // context corresponding to set flags will be returned.
    //
    // The context record is never used as an OUT only parameter.
    //

    DWORD ContextFlags;

    DWORD Fill[3];                      // Pad out to multiple of 16 bytes

    //
    // This section is specified/returned if CONTEXT_DEBUG_REGISTERS is
    // set in ContextFlags.  Note that CONTEXT_DEBUG_REGISTERS is NOT
    // included in CONTEXT_FULL.
    //
    DWORD Dr0;                          // Breakpoint Register 1
    DWORD Dr1;                          // Breakpoint Register 2
    DWORD Dr2;                          // Breakpoint Register 3
    DWORD Dr3;                          // Breakpoint Register 4
    DWORD Dr4;                          // Breakpoint Register 5
    DWORD Dr5;                          // Breakpoint Register 6
    DWORD Dr6;                          // Debug Status Register
    DWORD Dr7;                          // Debug Control Register

} CONTEXT, *PCONTEXT;

// end_ntddk end_nthal


//
// Stack frame header
//
//   Order of appearance in stack frame:
//      Header (six words)
//      Parameters (at least eight words)
//      Local variables
//      Saved GPRs
//      Saved FPRs
//
//   Minimum alignment is 8 bytes

typedef struct _STACK_FRAME_HEADER {    // GPR 1 points here
    DWORD BackChain;                    // Addr of previous frame
    DWORD Reserved1;                    // Reserved

    DWORD Parameter0;                   // First 8 parameter words are
    DWORD Parameter1;                   //   always present
    DWORD Parameter2;
    DWORD Parameter3;
    DWORD Parameter4;
    DWORD Parameter5;
    DWORD Parameter6;
    DWORD Parameter7;

} STACK_FRAME_HEADER,*PSTACK_FRAME_HEADER;

#endif // PPC


#if defined(ARM)
//
// The following flags control the contents of the CONTEXT structure.
//

#define CONTEXT_ARM    0x0000040
#define CONTEXT_CONTROL         (CONTEXT_ARM | 0x00000001L)
#define CONTEXT_INTEGER         (CONTEXT_ARM | 0x00000002L)

#define CONTEXT_FULL (CONTEXT_CONTROL | CONTEXT_INTEGER)

//
// Context Frame
//
//  This frame is used to store a limited processor context into the
// Thread structure for CPUs which have no floating point support.
//

typedef struct _CONTEXT {
    //
    // The flags values within this flag control the contents of
    // a CONTEXT record.
    //
    // If the context record is used as an input parameter, then
    // for each portion of the context record controlled by a flag
    // whose value is set, it is assumed that that portion of the
    // context record contains valid context. If the context record
    // is being used to modify a thread's context, then only that
    // portion of the threads context will be modified.
    //
    // If the context record is used as an IN OUT parameter to capture
    // the context of a thread, then only those portions of the thread's
    // context corresponding to set flags will be returned.
    //
    // The context record is never used as an OUT only parameter.
    //

    ULONG ContextFlags;

    //
    // This section is specified/returned if the ContextFlags word contains
    // the flag CONTEXT_INTEGER.
    //
    ULONG R0;
    ULONG R1;
    ULONG R2;
    ULONG R3;
    ULONG R4;
    ULONG R5;
    ULONG R6;
    ULONG R7;
    ULONG R8;
    ULONG R9;
    ULONG R10;
    ULONG R11;
    ULONG R12;

    //
    // This section is specified/returned if the ContextFlags word contains
    // the flag CONTEXT_CONTROL.
    //
    ULONG Sp;
    ULONG Lr;
    ULONG Pc;
    ULONG Psr;
} CONTEXT;

typedef CONTEXT *PCONTEXT;

#endif // ARM


#if defined(PPC)

// **FINISH** This may need alteration for PowerPC

VOID
__jump_unwind (
    PVOID Fp,
    PVOID TargetPc
    );

#endif // PPC

#if defined(_M_CEE)

#	if defined(_M_MRX000) || defined(_M_IX86) || defined(_M_ALPHA) || defined(_M_PPC) || defined(_M_ARM)
#		pragma message (__FILE__ "- error: _M_CEE defined as well as some CPU type")
#	endif

//	CPU specific structures are not available to portable programs.  We support context by allocating a
//		structure bigger than any context needed to date.  It is possible that we will be unable to support
//		get and set thread context on all future CPUs.  In such cases, the translator may fail.
//		Yes, this is really expensive.  MSIL programs that use must *really* need it.

typedef struct _CONTEXT {
	ULONG	m_rgWhatever [160];		// enough for 64 x 64bit registers, plus generous context
									// covers Alpha and SH4, but probably not the Merced!
} CONTEXT, *PCONTEXT;

#endif // _M_CEE


#define EXCEPTION_NONCONTINUABLE 0x1    // Noncontinuable exception
#define EXCEPTION_UNWINDING 0x2         // Unwind is in progress
#define EXCEPTION_EXIT_UNWIND 0x4       // Exit unwind is in progress
#define EXCEPTION_STACK_INVALID 0x8     // Stack out of limits or unaligned
#define EXCEPTION_NESTED_CALL 0x10      // Nested exception handler call
#define EXCEPTION_TARGET_UNWIND 0x20    // Target unwind in progress
#define EXCEPTION_COLLIDED_UNWIND 0x40  // Collided exception handler call

#define EXCEPTION_UNWIND (EXCEPTION_UNWINDING | EXCEPTION_EXIT_UNWIND | \
                          EXCEPTION_TARGET_UNWIND | EXCEPTION_COLLIDED_UNWIND)

#define IS_UNWINDING(Flag) ((Flag & EXCEPTION_UNWIND) != 0)
#define IS_DISPATCHING(Flag) ((Flag & EXCEPTION_UNWIND) == 0)
#define IS_TARGET_UNWIND(Flag) (Flag & EXCEPTION_TARGET_UNWIND)

#define EXCEPTION_MAXIMUM_PARAMETERS 15 // maximum number of exception parameters

//
// Exception record definition.
//

typedef struct _EXCEPTION_RECORD {
    /*lint -e18 */  // Don't complain about different definitions
    DWORD    ExceptionCode;
    /*lint +e18 */  // Resume checking for different definitions
    DWORD ExceptionFlags;
    struct _EXCEPTION_RECORD *ExceptionRecord;
    PVOID ExceptionAddress;
    DWORD NumberParameters;
    DWORD ExceptionInformation[EXCEPTION_MAXIMUM_PARAMETERS];
    } EXCEPTION_RECORD;

typedef EXCEPTION_RECORD *PEXCEPTION_RECORD;

//
// Typedef for pointer returned by exception_info()
//

typedef struct _EXCEPTION_POINTERS {
	PEXCEPTION_RECORD ExceptionRecord;
	PCONTEXT ContextRecord;
} EXCEPTION_POINTERS, *PEXCEPTION_POINTERS;

#define PROCESS_TERMINATE         (0x0001)
#define PROCESS_CREATE_THREAD     (0x0002)
#define PROCESS_VM_OPERATION      (0x0008)
#define PROCESS_VM_READ           (0x0010)
#define PROCESS_VM_WRITE          (0x0020)
#define PROCESS_DUP_HANDLE        (0x0040)
#define PROCESS_CREATE_PROCESS    (0x0080)
#define PROCESS_SET_QUOTA         (0x0100)
#define PROCESS_SET_INFORMATION   (0x0200)
#define PROCESS_QUERY_INFORMATION (0x0400)
#define PROCESS_ALL_ACCESS        (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | \
                                   0xFFF)

#define THREAD_TERMINATE               (0x0001)
#define THREAD_SUSPEND_RESUME          (0x0002)
#define THREAD_GET_CONTEXT             (0x0008)
#define THREAD_SET_CONTEXT             (0x0010)
#define THREAD_SET_INFORMATION         (0x0020)
#define THREAD_QUERY_INFORMATION       (0x0040)
#define THREAD_SET_THREAD_TOKEN        (0x0080)
#define THREAD_IMPERSONATE             (0x0100)
#define THREAD_DIRECT_IMPERSONATION    (0x0200)
// begin_ntddk

#define THREAD_ALL_ACCESS         (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | \
                                   0x3FF)

// end_ntddk
#define TLS_MINIMUM_AVAILABLE 64
#define THREAD_BASE_PRIORITY_LOWRT  15  // value that gets a thread to LowRealtime-1
#define THREAD_BASE_PRIORITY_MAX    2   // maximum thread base priority boost
#define THREAD_BASE_PRIORITY_MIN    -2  // minimum thread base priority boost
#define THREAD_BASE_PRIORITY_IDLE   -15 // value that gets a thread to idle
#define EVENT_MODIFY_STATE      0x0002
#define EVENT_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x3)
#define MUTANT_QUERY_STATE      0x0001

#define MUTANT_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|\
                          MUTANT_QUERY_STATE)
#define SEMAPHORE_MODIFY_STATE      0x0002
#define SEMAPHORE_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x3)
#define TIME_ZONE_ID_UNKNOWN  0
#define TIME_ZONE_ID_STANDARD 1
#define TIME_ZONE_ID_DAYLIGHT 2

#define PROCESSOR_ARCHITECTURE_INTEL 0
#define PROCESSOR_ARCHITECTURE_MIPS  1
#define PROCESSOR_ARCHITECTURE_ALPHA 2
#define PROCESSOR_ARCHITECTURE_PPC   3
#define PROCESSOR_ARCHITECTURE_SHx   4
#define PROCESSOR_ARCHITECTURE_ARM   5
#define PROCESSOR_ARCHITECTURE_IA64  6
#define PROCESSOR_ARCHITECTURE_ALPHA64 7
#define PROCESSOR_ARCHITECTURE_MSIL  8
#define PROCESSOR_ARCHITECTURE_UNKNOWN 0xFFFF

#define PROCESSOR_INTEL_386     386
#define PROCESSOR_INTEL_486     486
#define PROCESSOR_INTEL_PENTIUM 586
#define PROCESSOR_INTEL_860     860
#define PROCESSOR_MIPS_R2000    2000
#define PROCESSOR_MIPS_R3000    3000
#define PROCESSOR_MIPS_R4000    4000
#define PROCESSOR_HITACHI_SH3	10003
#define PROCESSOR_HITACHI_SH4	10005
#define PROCESSOR_ALPHA_21064   21064
#define PROCESSOR_PPC_403       403
#define PROCESSOR_PPC_601       601
#define PROCESSOR_PPC_603       603
#define PROCESSOR_PPC_604       604
#define PROCESSOR_PPC_620       620
#define PROCESSOR_PPC_821       821
#define PROCESSOR_SHx_SH3		103
#define PROCESSOR_SHx_SH4		104
#define PROCESSOR_STRONGARM		2577	// 0xA11
#define PROCESSOR_ARM720		1824	// 0x720
#define PROCESSOR_ARM820		2080	// 0x820
#define PROCESSOR_ARM920		2336	// 0x920
#define PROCESSOR_CEF			0x494f

typedef struct _MEMORY_BASIC_INFORMATION {
    PVOID BaseAddress;
    PVOID AllocationBase;
    DWORD AllocationProtect;
    DWORD RegionSize;
    DWORD State;
    DWORD Protect;
    DWORD Type;
} MEMORY_BASIC_INFORMATION, *PMEMORY_BASIC_INFORMATION;
#define SECTION_QUERY       0x0001
#define SECTION_MAP_WRITE   0x0002
#define SECTION_MAP_READ    0x0004
#define SECTION_MAP_EXECUTE 0x0008
#define SECTION_EXTEND_SIZE 0x0010

#define SECTION_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|SECTION_QUERY|\
                            SECTION_MAP_WRITE |      \
                            SECTION_MAP_READ |       \
                            SECTION_MAP_EXECUTE |    \
                            SECTION_EXTEND_SIZE)
#define PAGE_NOACCESS          0x01
#define PAGE_READONLY          0x02
#define PAGE_READWRITE         0x04
#define PAGE_WRITECOPY         0x08
#define PAGE_EXECUTE           0x10
#define PAGE_EXECUTE_READ      0x20
#define PAGE_EXECUTE_READWRITE 0x40
#define PAGE_EXECUTE_WRITECOPY 0x80
#define PAGE_GUARD            0x100
#define PAGE_NOCACHE          0x200
#define PAGE_PHYSICAL		  0x400
#define MEM_COMMIT           0x1000
#define MEM_RESERVE          0x2000
#define MEM_DECOMMIT         0x4000
#define MEM_RELEASE          0x8000
#define MEM_FREE            0x10000
#define MEM_PRIVATE         0x20000
#define MEM_MAPPED          0x40000
#define MEM_TOP_DOWN       0x100000
#define MEM_AUTO_COMMIT    0x200000
#define SEC_FILE           0x800000
#define SEC_IMAGE         0x1000000
#define SEC_RESERVE       0x4000000
#define SEC_COMMIT        0x8000000
#define SEC_NOCACHE      0x10000000
#define MEM_IMAGE         SEC_IMAGE

// Subsystem Values

#define IMAGE_SUBSYSTEM_UNKNOWN              0   // Unknown subsystem.
#define IMAGE_SUBSYSTEM_NATIVE               1   // Image doesn't require a subsystem.
#define IMAGE_SUBSYSTEM_WINDOWS_GUI          2   // Image runs in the Windows GUI subsystem.
#define IMAGE_SUBSYSTEM_WINDOWS_CUI          3   // Image runs in the Windows character subsystem.
#define IMAGE_SUBSYSTEM_WINDOWS_OLD_CE_GUI   4   // Image runs in the Windows CE GUI subsystem (obsolete).
#define IMAGE_SUBSYSTEM_OS2_CUI              5   // image runs in the OS/2 character subsystem.
#define IMAGE_SUBSYSTEM_POSIX_CUI            7   // image run  in the Posix character subsystem.
#define IMAGE_SUBSYSTEM_WINDOWS_CE_GUI		 9	 // Image runs in the Windows CE GUI subsystem.

//
// Define access rights to files and directories
//

//
// The FILE_READ_DATA and FILE_WRITE_DATA constants are also defined in
// devioctl.h as FILE_READ_ACCESS and FILE_WRITE_ACCESS. The values for these
// constants *MUST* always be in sync.
// The values are redefined in devioctl.h because they must be available to
// both DOS and NT.
//

#define FILE_READ_DATA            ( 0x0001 )    // file & pipe
#define FILE_LIST_DIRECTORY       ( 0x0001 )    // directory

#define FILE_WRITE_DATA           ( 0x0002 )    // file & pipe
#define FILE_ADD_FILE             ( 0x0002 )    // directory

#define FILE_APPEND_DATA          ( 0x0004 )    // file
#define FILE_ADD_SUBDIRECTORY     ( 0x0004 )    // directory
#define FILE_CREATE_PIPE_INSTANCE ( 0x0004 )    // named pipe

#define FILE_READ_EA              ( 0x0008 )    // file & directory
#define FILE_READ_PROPERTIES      FILE_READ_EA

#define FILE_WRITE_EA             ( 0x0010 )    // file & directory
#define FILE_WRITE_PROPERTIES     FILE_WRITE_EA

#define FILE_EXECUTE              ( 0x0020 )    // file
#define FILE_TRAVERSE             ( 0x0020 )    // directory

#define FILE_DELETE_CHILD         ( 0x0040 )    // directory

#define FILE_READ_ATTRIBUTES      ( 0x0080 )    // all

#define FILE_WRITE_ATTRIBUTES     ( 0x0100 )    // all

#define FILE_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x1FF)

#define FILE_GENERIC_READ         (STANDARD_RIGHTS_READ     |\
                                   FILE_READ_DATA           |\
                                   FILE_READ_ATTRIBUTES     |\
                                   FILE_READ_EA             |\
                                   SYNCHRONIZE)


#define FILE_GENERIC_WRITE        (STANDARD_RIGHTS_WRITE    |\
                                   FILE_WRITE_DATA          |\
                                   FILE_WRITE_ATTRIBUTES    |\
                                   FILE_WRITE_EA            |\
                                   FILE_APPEND_DATA         |\
                                   SYNCHRONIZE)


#define FILE_GENERIC_EXECUTE      (STANDARD_RIGHTS_EXECUTE  |\
                                   FILE_READ_ATTRIBUTES     |\
                                   FILE_EXECUTE             |\
                                   SYNCHRONIZE)

#define FILE_SHARE_READ                 0x00000001
#define FILE_SHARE_WRITE                0x00000002
#define FILE_ATTRIBUTE_READONLY         0x00000001
#define FILE_ATTRIBUTE_HIDDEN           0x00000002
#define FILE_ATTRIBUTE_SYSTEM           0x00000004
#define FILE_ATTRIBUTE_DIRECTORY        0x00000010
#define FILE_ATTRIBUTE_ARCHIVE          0x00000020
#define FILE_ATTRIBUTE_INROM			0x00000040
#define FILE_ATTRIBUTE_NORMAL           0x00000080
#define FILE_ATTRIBUTE_TEMPORARY        0x00000100
#define FILE_ATTRIBUTE_ATOMIC_WRITE     0x00000200
#define FILE_ATTRIBUTE_XACTION_WRITE    0x00000400
#define FILE_ATTRIBUTE_COMPRESSED       0x00000800
#define FILE_ATTRIBUTE_ROMSTATICREF		0x00001000
#define FILE_ATTRIBUTE_ROMMODULE		0x00002000
#define FILE_NOTIFY_CHANGE_FILE_NAME    0x00000001
#define FILE_NOTIFY_CHANGE_DIR_NAME     0x00000002
#define FILE_NOTIFY_CHANGE_ATTRIBUTES   0x00000004
#define FILE_NOTIFY_CHANGE_SIZE         0x00000008
#define FILE_NOTIFY_CHANGE_LAST_WRITE   0x00000010
#define FILE_NOTIFY_CHANGE_SECURITY     0x00000100
#define MAILSLOT_NO_MESSAGE             ((DWORD)-1)
#define MAILSLOT_WAIT_FOREVER           ((DWORD)-1)
#define FILE_CASE_SENSITIVE_SEARCH      0x00000001
#define FILE_CASE_PRESERVED_NAMES       0x00000002
#define FILE_UNICODE_ON_DISK            0x00000004
#define FILE_PERSISTENT_ACLS            0x00000008
#define FILE_FILE_COMPRESSION           0x00000010
#define FILE_VOLUME_IS_COMPRESSED       0x00008000
#define IO_COMPLETION_MODIFY_STATE  0x0002
#define IO_COMPLETION_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED|SYNCHRONIZE|0x3)
#define DUPLICATE_CLOSE_SOURCE      0x00000001
#define DUPLICATE_SAME_ACCESS       0x00000002
typedef PVOID PACCESS_TOKEN;
typedef PVOID PSECURITY_DESCRIPTOR;
typedef PVOID PSID;


////////////////////////////////////////////////////////////////////////
//                                                                    //
//                             ACCESS MASK                            //
//                                                                    //
////////////////////////////////////////////////////////////////////////

//
//  Define the access mask as a longword sized structure divided up as
//  follows:
//
//       3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//       1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//      +---------------+---------------+-------------------------------+
//      |G|G|G|G|Res'd|A| StandardRights|         SpecificRights        |
//      |R|W|E|A|     |S|               |                               |
//      +-+-------------+---------------+-------------------------------+
//
//      typedef struct _ACCESS_MASK {
//          WORD   SpecificRights;
//          BYTE  StandardRights;
//          BYTE  AccessSystemAcl : 1;
//          BYTE  Reserved : 3;
//          BYTE  GenericAll : 1;
//          BYTE  GenericExecute : 1;
//          BYTE  GenericWrite : 1;
//          BYTE  GenericRead : 1;
//      } ACCESS_MASK;
//      typedef ACCESS_MASK *PACCESS_MASK;
//
//  but to make life simple for programmer's we'll allow them to specify
//  a desired access mask by simply OR'ing together mulitple single rights
//  and treat an access mask as a DWORD.  For example
//
//      DesiredAccess = DELETE | READ_CONTROL
//
//  So we'll declare ACCESS_MASK as DWORD
//

// begin_ntddk begin_nthal begin_ntifs
typedef DWORD ACCESS_MASK;
typedef ACCESS_MASK *PACCESS_MASK;


////////////////////////////////////////////////////////////////////////
//                                                                    //
//                             ACCESS TYPES                           //
//                                                                    //
////////////////////////////////////////////////////////////////////////


// begin_ntddk begin_nthal begin_ntifs
//
//  The following are masks for the predefined standard access types
//

#define DELETE                           (0x00010000L)
#define READ_CONTROL                     (0x00020000L)
#define WRITE_DAC                        (0x00040000L)
#define WRITE_OWNER                      (0x00080000L)
#define SYNCHRONIZE                      (0x00100000L)

#define STANDARD_RIGHTS_REQUIRED         (0x000F0000L)

#define STANDARD_RIGHTS_READ             (READ_CONTROL)
#define STANDARD_RIGHTS_WRITE            (READ_CONTROL)
#define STANDARD_RIGHTS_EXECUTE          (READ_CONTROL)

#define STANDARD_RIGHTS_ALL              (0x001F0000L)

#define SPECIFIC_RIGHTS_ALL              (0x0000FFFFL)

//
// AccessSystemAcl access type
//

#define ACCESS_SYSTEM_SECURITY           (0x01000000L)

//
// MaximumAllowed access type
//

#define MAXIMUM_ALLOWED                  (0x02000000L)

//
//  These are the generic rights.
//

#define GENERIC_READ                     (0x80000000L)
#define GENERIC_WRITE                    (0x40000000L)
#define GENERIC_EXECUTE                  (0x20000000L)
#define GENERIC_ALL                      (0x10000000L)


//
//  Define the generic mapping array.  This is used to denote the
//  mapping of each generic access right to a specific access mask.
//

typedef struct _GENERIC_MAPPING {
    ACCESS_MASK GenericRead;
    ACCESS_MASK GenericWrite;
    ACCESS_MASK GenericExecute;
    ACCESS_MASK GenericAll;
} GENERIC_MAPPING;
typedef GENERIC_MAPPING *PGENERIC_MAPPING;

#define DLL_PROCESS_ATTACH 1
#define DLL_THREAD_ATTACH  2
#define DLL_THREAD_DETACH  3
#define DLL_PROCESS_DETACH 0
#define DLL_PROCESS_EXITING 4
#define DLL_SYSTEM_STARTED 5
#define DLL_MEMORY_LOW 6

#define DBG_CONTINUE                    ((DWORD   )0x00010002L) 
#define DBG_EXCEPTION_NOT_HANDLED       ((DWORD   )0x80010001L) 

// begin_ntddk begin_nthal
//
// Registry Specific Access Rights.
//

#define KEY_QUERY_VALUE         (0x0001)
#define KEY_SET_VALUE           (0x0002)
#define KEY_CREATE_SUB_KEY      (0x0004)
#define KEY_ENUMERATE_SUB_KEYS  (0x0008)
#define KEY_NOTIFY              (0x0010)
#define KEY_CREATE_LINK         (0x0020)

#define KEY_READ                ((STANDARD_RIGHTS_READ       |\
                                  KEY_QUERY_VALUE            |\
                                  KEY_ENUMERATE_SUB_KEYS     |\
                                  KEY_NOTIFY)                 \
                                  &                           \
                                 (~SYNCHRONIZE))


#define KEY_WRITE               ((STANDARD_RIGHTS_WRITE      |\
                                  KEY_SET_VALUE              |\
                                  KEY_CREATE_SUB_KEY)         \
                                  &                           \
                                 (~SYNCHRONIZE))

#define KEY_EXECUTE             ((KEY_READ)                   \
                                  &                           \
                                 (~SYNCHRONIZE))

#define KEY_ALL_ACCESS          ((STANDARD_RIGHTS_ALL        |\
                                  KEY_QUERY_VALUE            |\
                                  KEY_SET_VALUE              |\
                                  KEY_CREATE_SUB_KEY         |\
                                  KEY_ENUMERATE_SUB_KEYS     |\
                                  KEY_NOTIFY                 |\
                                  KEY_CREATE_LINK)            \
                                  &                           \
                                 (~SYNCHRONIZE))

//
// Open/Create Options
//

#define REG_OPTION_RESERVED         (0x00000000L)   // Parameter is reserved

#define REG_OPTION_NON_VOLATILE     (0x00000000L)   // Key is preserved
                                                    // when system is rebooted

#define REG_OPTION_VOLATILE         (0x00000001L)   // Key is not preserved
                                                    // when system is rebooted

#define REG_OPTION_CREATE_LINK      (0x00000002L)   // Created key is a
                                                    // symbolic link

#define REG_OPTION_BACKUP_RESTORE   (0x00000004L)   // open for backup or restore
                                                    // special access rules
                                                    // privilege required

#define REG_LEGAL_OPTION            \
                (REG_OPTION_RESERVED            |\
                 REG_OPTION_NON_VOLATILE        |\
                 REG_OPTION_VOLATILE            |\
                 REG_OPTION_CREATE_LINK         |\
                 REG_OPTION_BACKUP_RESTORE)

//
// Key creation/open disposition
//

#define REG_CREATED_NEW_KEY         (0x00000001L)   // New Registry Key created
#define REG_OPENED_EXISTING_KEY     (0x00000002L)   // Existing Key opened

//
// Key restore flags
//

#define REG_WHOLE_HIVE_VOLATILE     (0x00000001L)   // Restore whole hive volatile
#define REG_REFRESH_HIVE            (0x00000002L)   // Unwind changes to last flush

// end_ntddk end_nthal

//
// Notify filter values
//
#define REG_NOTIFY_CHANGE_NAME          (0x00000001L) // Create or delete (child)
#define REG_NOTIFY_CHANGE_ATTRIBUTES    (0x00000002L)
#define REG_NOTIFY_CHANGE_LAST_SET      (0x00000004L) // time stamp
#define REG_NOTIFY_CHANGE_SECURITY      (0x00000008L)

#define REG_LEGAL_CHANGE_FILTER                 \
                (REG_NOTIFY_CHANGE_NAME          |\
                 REG_NOTIFY_CHANGE_ATTRIBUTES    |\
                 REG_NOTIFY_CHANGE_LAST_SET      |\
                 REG_NOTIFY_CHANGE_SECURITY)

//
//
// Predefined Value Types.
//

#define REG_NONE                    ( 0 )   // No value type
#define REG_SZ                      ( 1 )   // Unicode nul terminated string
#define REG_EXPAND_SZ               ( 2 )   // Unicode nul terminated string
                                            // (with environment variable references)
#define REG_BINARY                  ( 3 )   // Free form binary
#define REG_DWORD                   ( 4 )   // 32-bit number
#define REG_DWORD_LITTLE_ENDIAN     ( 4 )   // 32-bit number (same as REG_DWORD)
#define REG_DWORD_BIG_ENDIAN        ( 5 )   // 32-bit number
#define REG_LINK                    ( 6 )   // Symbolic Link (unicode)
#define REG_MULTI_SZ                ( 7 )   // Multiple Unicode strings
#define REG_RESOURCE_LIST           ( 8 )   // Resource list in the resource map
#define REG_FULL_RESOURCE_DESCRIPTOR ( 9 )  // Resource list in the hardware description
#define REG_RESOURCE_REQUIREMENTS_LIST ( 10 )

#ifdef __cplusplus
}
#endif

#endif /* _WINNT_ */

