/*++

Copyright (c) 1991-1997 Microsoft Corporation

Module Name:

    mclex.c

Abstract:

    This file contains the input lexer for the Win32 Message Compiler (MC)

--*/


#include "mc.h"

char LineBuffer[ 256 ];
char *CurrentChar;
BOOLEAN ReturnCurrentToken;

PNAME_INFO KeywordNames;

typedef struct _COMMENT_INFO {
    struct _COMMENT_INFO *Next;
    char Text[ 1 ];
} COMMENT_INFO, *PCOMMENT_INFO;

PCOMMENT_INFO Comments, CurrentComment;

/*++

Routine Description:

    This fills in the Key words associated with the Message file format

Return Value:

    TRUE

--*/



BOOLEAN
McInitLexer( void )
{
    ReturnCurrentToken = FALSE;
    McAddName( &KeywordNames, "MessageIdTypedef",   MCTOK_MSGIDTYPE_KEYWORD,  NULL );
    McAddName( &KeywordNames, "SeverityNames",      MCTOK_SEVNAMES_KEYWORD,   NULL );
    McAddName( &KeywordNames, "FacilityNames",      MCTOK_FACILITYNAMES_KEYWORD,  NULL );
    McAddName( &KeywordNames, "LanguageNames",      MCTOK_LANGNAMES_KEYWORD,  NULL );
    McAddName( &KeywordNames, "MessageId",          MCTOK_MESSAGEID_KEYWORD,  NULL );
    McAddName( &KeywordNames, "Severity",           MCTOK_SEVERITY_KEYWORD,   NULL );
    McAddName( &KeywordNames, "Facility",           MCTOK_FACILITY_KEYWORD,   NULL );
    McAddName( &KeywordNames, "SymbolicName",       MCTOK_SYMBOLNAME_KEYWORD, NULL );
    McAddName( &KeywordNames, "Language",           MCTOK_LANGUAGE_KEYWORD,   NULL );
    return( TRUE );
}



BOOLEAN
McOpenInputFile( void )
{
    char SavedChar, *s, *FileName;
    BOOLEAN Result;

    s = MessageFileName;
    FileName = s;
    SavedChar = '\0';
    while (*s) {
        if (*s == '.') {
            SavedChar = '.';
            *s = '\0';
            break;
            }

        if (*s == ':' || *s == '\\' || *s == '/') {
            FileName = s+1;
            }

        s = CharNext(s);
	}

    strcat( HeaderFileName, FileName );
    strcat( HeaderFileName, ".h" );
    strcat( RcInclFileName, FileName );
    strcat( RcInclFileName, ".rc" );

    if (SavedChar == '\0') {
        strcpy( s, ".mc" );
        }
    else {
        *s = SavedChar;
        }

    Result = FALSE;
    MessageFileLineNumber = 0;
    LineBuffer[ 0 ] = '\0';
    CurrentChar = NULL;

    MessageFile = fopen( MessageFileName, "rb" );
    if (MessageFile == NULL) {
        McInputError( "unable to open input file", TRUE, NULL );
        }
    else {
        HeaderFile = fopen( HeaderFileName, "wb" );
        if (HeaderFile == NULL) {
            McInputError( "unable to open output file - %s", TRUE, HeaderFileName );
            }
        else {
            RcInclFile = fopen( RcInclFileName, "wb" );
            if (RcInclFile == NULL) {
                McInputError( "unable to open output file - %s", TRUE, RcInclFileName );
                }
            else {
                Result = TRUE;
                }
            }
        }

    if (!Result) {
        McCloseInputFile();
        McCloseOutputFiles();
        }
    else {
        return( TRUE );
        }
}



void
McCloseInputFile( void )
{
    if (MessageFile != NULL) {
        fclose( MessageFile );
        MessageFile = NULL;
        CurrentChar = NULL;
        LineBuffer[ 0 ] = '\0';
        }
}



void
McCloseOutputFiles( void )
{
    if (HeaderFile != NULL) {
        fclose( HeaderFile );
        }

    if (RcInclFile != NULL) {
        fclose( RcInclFile );
        }
}


void
McInputError(
    char *Message,
    BOOLEAN Error,
    PVOID Argument
    )
{
    fprintf( stderr,
             "%s (%d) : %s: ",
             MessageFileName,
             MessageFileLineNumber,
             Error ? "Error" : "Warning"
           );

    fprintf( stderr, Message, Argument );
    fprintf( stderr, "\n" );
}


/*++

Routine Description:

   This retrieves the current line then moves down to the
   next line in the message file.

Return Value:

   Returns the current line of in the file.

--*/


char *
McGetLine( void )
{
    char *s;

    if (MessageFile == NULL || feof( MessageFile )) {
        return( NULL );
        }

    if (fgets( LineBuffer, sizeof( LineBuffer ), MessageFile ) == NULL) {
        return( NULL );
        }

    s = LineBuffer + strlen( LineBuffer );
    if (s > LineBuffer && *--s == '\n') {
        if (s > LineBuffer && *--s != '\r') {
            *++s = '\r';
            *++s = '\n';
            *++s = '\0';
            }
        }

    MessageFileLineNumber++;
    return( CurrentChar = LineBuffer );
}


void
McSkipLine( void )
{
    CurrentChar = NULL;
}


/*++

Routine Description:

   This retrieves the character at the current position of the line
   buffer then advances to the next position. If the end of the line
   is reached another line is retrieve. If the end of the file is reached
   this returns with a NULL character. One is optionally able to flush
   the white space from the line.

Arguments:

   A boolean specifying whether whitespace should be consider significant.

Return Value:

   Returns the character in the current line.

--*/




char
McGetChar(
    BOOLEAN SkipWhiteSpace
    )
{
    BOOLEAN SawWhiteSpace;
    BOOLEAN SawNewLine;
    PCOMMENT_INFO p;

    SawWhiteSpace = FALSE;

tryagain:
    SawNewLine = FALSE;
    if (CurrentChar == NULL) {
        McGetLine();
        if (CurrentChar == NULL) {
            return( '\0' );
            }

        SawNewLine = TRUE;
        }

    if (SkipWhiteSpace) {
        while (*CurrentChar <= ' ') {
            SawWhiteSpace = TRUE;
            if (!*CurrentChar++) {
                CurrentChar = NULL;
                break;
                }
            }
        }

    if (SawNewLine) {
        if (CurrentChar != NULL && *CurrentChar == MCCHAR_END_OF_LINE_COMMENT) {
            p = malloc( sizeof( *p ) + strlen( ++CurrentChar ) );
            p->Next = NULL;
            strcpy( p->Text, CurrentChar );
            if (CurrentComment == NULL) {
                Comments = p;
                }
            else {
                CurrentComment->Next = p;
                }
            CurrentComment = p;

            CurrentChar = NULL;
            }
        }

    if (CurrentChar == NULL && SkipWhiteSpace) {
        goto tryagain;
        }

    if (SawWhiteSpace) {
        return( ' ' );
        }
    else {
        return( *CurrentChar++ );
        }
}


void
McFlushComments( void )
{
    PCOMMENT_INFO p;

    while (p = Comments) {
        fprintf( HeaderFile, "%s", p->Text );

        Comments = Comments->Next;
        free( p );
        }
    Comments = NULL;
    CurrentComment = NULL;

    fflush( HeaderFile );
    return;
}


void
McUnGetChar(
    char c
    )
{
    if (CurrentChar > LineBuffer) {
        *--CurrentChar = c;
        }
    else {
        LineBuffer[ 0 ] = c;
        LineBuffer[ 1 ] = '\0';
        CurrentChar = LineBuffer;
        }
}


/*++

Routine Description:

    Breaks input line into "tokens values" as defined in MC.H.

Arguments:

    A boolean designating whether keywords are required.

Return Value:

   Returns the the token corresponding to the "token value" For example
   with a token of type MCTOK_NUMBER the value would be a string
   representation of an integer.

--*/


unsigned int
McGetToken(
    BOOLEAN KeywordExpected
    )
{
    char c, *dst;

    if (ReturnCurrentToken) {
        ReturnCurrentToken = FALSE;
        if (Token == MCTOK_NAME && KeywordExpected) {
            TokenKeyword = McFindName( KeywordNames, TokenCharValue );
            if (TokenKeyword == NULL) {
                McInputError( "expected keyword - %s", TRUE, TokenCharValue );
                Token = MCTOK_END_OF_FILE;
                }
            else {
                Token = (unsigned int)TokenKeyword->Id;
                }
            }

        return( Token );
        }

    Token = MCTOK_END_OF_FILE;
    dst = TokenCharValue;
    *dst = '\0';
    TokenNumericValue = 0L;

    while (TRUE) {
        c = McGetChar( (BOOLEAN)(Token == MCTOK_END_OF_FILE) );
        if (Token == MCTOK_NUMBER) {
            if (isdigit( c ) ||
                c == 'x' ||
                (c >= 'a' && c <= 'f') ||
                (c >= 'A' && c <= 'F')
               ) {
                *dst++ = c;
                }
            else {
                McUnGetChar( c );
                *dst = '\0';

                if (!McCharToInteger( TokenCharValue, 0, &TokenNumericValue )) {
                    McInputError( "invalid number - %s", TRUE, TokenCharValue );
                    Token = MCTOK_END_OF_FILE;
                    }
                else {
                    return( Token );
                    }
                }
            }
        else
        if (Token == MCTOK_NAME) {
            if (iscsym( c )) {
                *dst++ = c;
                }
            else {
                McUnGetChar( c );
                *dst = '\0';

                if (KeywordExpected) {
                    TokenKeyword = McFindName( KeywordNames, TokenCharValue );
                    if (TokenKeyword == NULL) {
                        McInputError( "expected keyword - %s", TRUE, TokenCharValue );
                        Token = MCTOK_END_OF_FILE;
                        }
                    else {
                        Token = (unsigned int)TokenKeyword->Id;
                        }
                    }
                return( Token );
                }
            }
        else
        if (isdigit( c )) {
            *dst++ = c;
            Token = MCTOK_NUMBER;
            }
        else
        if (iscsymf( c )) {
            *dst++ = c;
            Token = MCTOK_NAME;
            }
        else
        if (c == '=') {
            *dst++ = c;
            *dst = '\0';
            Token = MCTOK_EQUAL;
            return( Token );
            }
        else
        if (c == '(') {
            *dst++ = c;
            *dst = '\0';
            Token = MCTOK_LEFT_PAREN;
            return( Token );
            }
        else
        if (c == ')') {
            *dst++ = c;
            *dst = '\0';
            Token = MCTOK_RIGHT_PAREN;
            return( Token );
            }
        else
        if (c == ':') {
            *dst++ = c;
            *dst = '\0';
            Token = MCTOK_COLON;
            return( Token );
            }
        else
        if (c == '+') {
            *dst++ = c;
            *dst = '\0';
            Token = MCTOK_PLUS;
            return( Token );
            }
        else
        if (c == ' ') {
            }
        else
        if (c == MCCHAR_END_OF_LINE_COMMENT) {
            Token = MCTOK_END_OF_LINE_COMMENT;
            strcpy( TokenCharValue, CurrentChar );
            CurrentChar = NULL;
            return( Token );
            }
        else
        if (c == '\0') {
            return( Token );
            }
        else {
            McInputError( "invalid character '%c'", TRUE, (PVOID)(ULONG)(UCHAR)c );
            }
        }
}


void
McUnGetToken( void )
{
    ReturnCurrentToken = TRUE;
}

char *
McSkipWhiteSpace(
    char *s
    )
{
    while (*s <= ' ') {
        if (!*s++) {
            s = NULL;
            break;
            }
        }

    return( s );
}
