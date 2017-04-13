/*++

Copyright (c) 1991-1997 Microsoft Corporation

Module Name:

    mc.h

Abstract:

    This is the main include file for the Win32 Message Compiler (MC)

Author:

    Steve Wood (stevewo) 21-Aug-1991

Revision History:

--*/

#if 0
#include <nt.h>
#include <ntrtl.h>
#include <nturtl.h>
#endif

#include <process.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <malloc.h>
#include <errno.h>
#include <ctype.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <sys\types.h>
#include <sys\stat.h>

#ifdef TOOL

#define MAX_PATH 265

#else

#include <windows.h>

#endif

//
// Global constants
//

#define MCCHAR_END_OF_LINE_COMMENT    ';'

#define MCTOK_END_OF_FILE             0x00

#define MCTOK_NUMBER                  0x01
#define MCTOK_NAME                    0x02
#define MCTOK_EQUAL                   0x03
#define MCTOK_LEFT_PAREN              0x04
#define MCTOK_RIGHT_PAREN             0x05
#define MCTOK_COLON                   0x06
#define MCTOK_PLUS                    0x07
#define MCTOK_END_OF_LINE_COMMENT     0x08

#define MCTOK_MSGIDTYPE_KEYWORD       0x11
#define MCTOK_SEVNAMES_KEYWORD        0x12
#define MCTOK_FACILITYNAMES_KEYWORD   0x13
#define MCTOK_LANGNAMES_KEYWORD       0x14
#define MCTOK_MESSAGEID_KEYWORD       0x15
#define MCTOK_SEVERITY_KEYWORD        0x16
#define MCTOK_FACILITY_KEYWORD        0x17
#define MCTOK_SYMBOLNAME_KEYWORD      0x18
#define MCTOK_LANGUAGE_KEYWORD        0x19


//
// Global data types
//

typedef struct _LANGUAGE_INFO {
    struct _LANGUAGE_INFO *Next;
    ULONG Id;
    ULONG Length;
    PCHAR Text;
} LANGUAGE_INFO, *PLANGUAGE_INFO;

typedef struct _MESSAGE_INFO {
    struct _MESSAGE_INFO *Next;
    ULONG Id;
    ULONG Method;
    PCHAR SymbolicName;
    PCHAR EndOfLineComment;
    PLANGUAGE_INFO MessageText;
} MESSAGE_INFO, *PMESSAGE_INFO;

#define MSG_PLUS_ONE 0
#define MSG_PLUS_VALUE 1
#define MSG_ABSOLUTE 2

typedef struct _MESSAGE_BLOCK {
    struct _MESSAGE_BLOCK *Next;
    ULONG LowId;
    ULONG HighId;
    ULONG InfoLength;
    PMESSAGE_INFO LowInfo;
} MESSAGE_BLOCK, *PMESSAGE_BLOCK;

typedef struct _NAME_INFO {
    struct _NAME_INFO *Next;
    ULONG LastId;
    ULONG Id;
    PVOID Value;
    BOOLEAN Used;
    char Name[ 1 ];
} NAME_INFO, *PNAME_INFO;


//
// Global variables
//

int VerboseOutput;
int WarnOs2Compatible;
int InsertSymbolicName;
int GenerateDecimalValues;
int ResultCode;
ULONG CustomerMsgIdBit;

FILE *MessageFile;
char MessageFileName[ MAX_PATH ];
unsigned int MessageFileLineNumber;
unsigned int Token;
char TokenCharValue[ 256 ];
ULONG TokenNumericValue;
PNAME_INFO TokenKeyword;

FILE *HeaderFile;
char HeaderFileName[ MAX_PATH ];
FILE *RcInclFile;
char RcInclFileName[ MAX_PATH ];
FILE *BinaryMessageFile;
char BinaryMessageFileName[ MAX_PATH ];

char *MessageIdTypeName;

PNAME_INFO FacilityNames;
PNAME_INFO CurrentFacilityName;
PNAME_INFO SeverityNames;
PNAME_INFO CurrentSeverityName;
PNAME_INFO LanguageNames;
PNAME_INFO CurrentLanguageName;

PMESSAGE_INFO Messages;
PMESSAGE_INFO CurrentMessage;

//
// Functions defined in mc.c
//

void
McPrintUsage( void );


//
// Functions defined in mcparse.c
//

BOOLEAN
McParseFile( void );

BOOLEAN
McParseMessageDefinition( void );

BOOLEAN
McParseMessageText(
    PMESSAGE_INFO MessageInfo
    );

BOOLEAN
McParseNameList(
    PNAME_INFO *NameListHead,
    BOOLEAN ValueRequired,
    ULONG MaximumValue
    );

BOOLEAN
McParseName(
    PNAME_INFO NameListHead,
    PNAME_INFO *Result
    );


//
// Functions defined in mcout.c
//

BOOLEAN
McBlockMessages( void );


BOOLEAN
McWriteBinaryFiles( void );



//
// Functions defined in mclex.c
//

BOOLEAN
McInitLexer( void );

BOOLEAN
McOpenInputFile( void );

void
McFlushComments( void );

void
McCloseInputFile( void );

void
McCloseOutputFiles( void );

void
McInputError(
    char *Message,
    BOOLEAN Error,
    PVOID Argument
    );

char *
McGetLine( void );

void
McSkipLine( void );

char
McGetChar(
    BOOLEAN SkipWhiteSpace
    );

void
McUnGetChar(
    char c
    );

unsigned int
McGetToken(
    BOOLEAN KeywordExpected
    );

void
McUnGetToken( void );

char *
McSkipWhiteSpace(
    char *s
    );

//
// Functions defined in mcutil.c
//

PNAME_INFO
McAddName(
    PNAME_INFO *NameListHead,
    char *Name,
    ULONG Id,
    PVOID Value
    );


PNAME_INFO
McFindName(
    PNAME_INFO NameListHead,
    char *Name
    );


BOOLEAN
McCharToInteger(
    PCHAR String,
    int Base,
    PULONG Value
    );

char *
McMakeString(
    char *String
    );
