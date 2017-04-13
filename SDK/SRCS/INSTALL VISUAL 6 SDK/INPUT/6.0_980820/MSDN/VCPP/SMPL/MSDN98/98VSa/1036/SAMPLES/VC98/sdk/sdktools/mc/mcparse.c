/*++

Copyright (c) 1991-1997 Microsoft Corporation

Module Name:

    mcparse.c

Abstract:

    This file contains the parse logic for the Win32 Message Compiler (MC)


--*/

#include "mc.h"

BOOLEAN
McParseFile( void )
{
    unsigned int t;
    BOOLEAN FirstMessageDefinition = TRUE;
    PNAME_INFO p;

    if (!McOpenInputFile()) {
        fprintf( stderr, "MC: Unable to open %s for input\n", MessageFileName );
        return( FALSE );
        }

    fprintf( stderr, "MC: Compiling %s\n", MessageFileName );
    while ((t = McGetToken( TRUE )) != MCTOK_END_OF_FILE) {
        switch (t) {
        case MCTOK_MSGIDTYPE_KEYWORD:
            if ((t = McGetToken( FALSE )) == MCTOK_EQUAL) {
                if ((t = McGetToken( FALSE )) == MCTOK_NAME) {
                    MessageIdTypeName = McMakeString( TokenCharValue );
                    }
                else {
                    McInputError( "Symbol name must follow %s=", TRUE, TokenKeyword->Name );
                    return( FALSE );
                    }
                }
            else {
                McInputError( "Equal sign must follow %s", TRUE, TokenKeyword->Name );
                return( FALSE );
                }
            break;

        case MCTOK_SEVNAMES_KEYWORD:
            if ((t = McGetToken( FALSE )) == MCTOK_EQUAL) {
                if ((t = McGetToken( FALSE )) == MCTOK_LEFT_PAREN) {
                    if (!McParseNameList( &SeverityNames, FALSE, 0x3L )) {
                        return( FALSE );
                        }
                    }
                else {
                    McInputError( "Left parenthesis name must follow %s=", TRUE, TokenKeyword->Name );
                    return( FALSE );
                    }
                }
            else {
                McInputError( "Equal sign must follow %s", TRUE, TokenKeyword->Name );
                return( FALSE );
                }
            break;

        case MCTOK_FACILITYNAMES_KEYWORD:
            if ((t = McGetToken( FALSE )) == MCTOK_EQUAL) {
                if ((t = McGetToken( FALSE )) == MCTOK_LEFT_PAREN) {
                    if (!McParseNameList( &FacilityNames, FALSE, 0xFFFL )) {
                        return( FALSE );
                        }
                    }
                else {
                    McInputError( "Left parenthesis name must follow %s=", TRUE, TokenKeyword->Name );
                    return( FALSE );
                    }
                }
            else {
                McInputError( "Equal sign must follow %s", TRUE, TokenKeyword->Name );
                return( FALSE );
                }
            break;

        case MCTOK_LANGNAMES_KEYWORD:
            if ((t = McGetToken( FALSE )) == MCTOK_EQUAL) {
                if ((t = McGetToken( FALSE )) == MCTOK_LEFT_PAREN) {
                    if (!McParseNameList( &LanguageNames, TRUE, 0xFFFFL )) {
                        return( FALSE );
                        }
                    }
                else {
                    McInputError( "Left parenthesis name must follow %s=", TRUE, TokenKeyword->Name );
                    return( FALSE );
                    }
                }
            else {
                McInputError( "Equal sign must follow %s", TRUE, TokenKeyword->Name );
                return( FALSE );
                }
            break;

        case MCTOK_MESSAGEID_KEYWORD:
            McUnGetToken();
            if (FirstMessageDefinition) {
                FirstMessageDefinition = FALSE;
                McFlushComments();
                fprintf( HeaderFile, "//\r\n" );
                fprintf( HeaderFile, "//  Values are 32 bit values layed out as follows:\r\n" );
                fprintf( HeaderFile, "//\r\n" );
                fprintf( HeaderFile, "//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1\r\n" );
                fprintf( HeaderFile, "//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0\r\n" );
                fprintf( HeaderFile, "//  +---+-+-+-----------------------+-------------------------------+\r\n" );
                fprintf( HeaderFile, "//  |Sev|C|R|     Facility          |               Code            |\r\n" );
                fprintf( HeaderFile, "//  +---+-+-+-----------------------+-------------------------------+\r\n" );
                fprintf( HeaderFile, "//\r\n" );
                fprintf( HeaderFile, "//  where\r\n" );
                fprintf( HeaderFile, "//\r\n" );
                fprintf( HeaderFile, "//      Sev - is the severity code\r\n" );
                fprintf( HeaderFile, "//\r\n" );
                fprintf( HeaderFile, "//          00 - Success\r\n" );
                fprintf( HeaderFile, "//          01 - Informational\r\n" );
                fprintf( HeaderFile, "//          10 - Warning\r\n" );
                fprintf( HeaderFile, "//          11 - Error\r\n" );
                fprintf( HeaderFile, "//\r\n" );
                fprintf( HeaderFile, "//      C - is the Customer code flag\r\n" );
                fprintf( HeaderFile, "//\r\n" );
                fprintf( HeaderFile, "//      R - is a reserved bit\r\n" );
                fprintf( HeaderFile, "//\r\n" );
                fprintf( HeaderFile, "//      Facility - is the facility code\r\n" );
                fprintf( HeaderFile, "//\r\n" );
                fprintf( HeaderFile, "//      Code - is the facility's status code\r\n" );
                fprintf( HeaderFile, "//\r\n" );

                fprintf( HeaderFile, "//\r\n" );
                fprintf( HeaderFile, "// Define the facility codes\r\n" );
                fprintf( HeaderFile, "//\r\n" );
                p = FacilityNames;
                while( p ) {
                    if (p->Value) {
                        fprintf( HeaderFile, GenerateDecimalValues ?
                                             "#define %-32s %ld\r\n" :
                                             "#define %-32s 0x%lX\r\n",
                                 p->Value, p->Id
                               );
                        }

                    p = p->Next;
                    }
                fprintf( HeaderFile, "\r\n" );
                fprintf( HeaderFile, "\r\n" );

                fprintf( HeaderFile, "//\r\n" );
                fprintf( HeaderFile, "// Define the severity codes\r\n" );
                fprintf( HeaderFile, "//\r\n" );
                p = SeverityNames;
                while( p ) {
                    if (p->Value) {
                        fprintf( HeaderFile, GenerateDecimalValues ?
                                             "#define %-32s %ld\r\n" :
                                             "#define %-32s 0x%lX\r\n",
                                 p->Value, p->Id
                               );
                        }

                    p = p->Next;
                    }
                fprintf( HeaderFile, "\r\n" );
                fprintf( HeaderFile, "\r\n" );
                }

            if (!McParseMessageDefinition()) {
                return( FALSE );
                }
            break;

        default:
            McInputError( "Invalid message file token - '%s'", TRUE, TokenCharValue );
            return( FALSE );
            break;
        }
    }

    McFlushComments();
    return( TRUE );
}


BOOLEAN
McParseMessageDefinition( void )
{
    unsigned int t;
    PMESSAGE_INFO MessageInfo;
    BOOLEAN MessageIdSeen;
    PMESSAGE_INFO MessageInfoTemp;

    McFlushComments();

    MessageInfo = malloc( sizeof( *MessageInfo ) );
    MessageInfo->Next = NULL;
    MessageInfo->Id = 0;
    MessageInfo->Method = MSG_PLUS_ONE;
    MessageInfo->SymbolicName = NULL;
    MessageInfo->EndOfLineComment = NULL;
    MessageInfo->MessageText = NULL;
    MessageIdSeen = FALSE;

    while ((t = McGetToken( TRUE )) != MCTOK_END_OF_FILE) {
        switch (t) {
        case MCTOK_MESSAGEID_KEYWORD:
            if (MessageIdSeen) {
                McInputError( "Invalid message definition - text missing.", TRUE, NULL );
                return( FALSE );
                }

            MessageIdSeen = TRUE;
            if ((t = McGetToken( FALSE )) == MCTOK_EQUAL) {
                if ((t = McGetToken( FALSE )) == MCTOK_NUMBER) {
                    MessageInfo->Id = TokenNumericValue;
                    MessageInfo->Method = MSG_ABSOLUTE;
                    }
                else
                if (t == MCTOK_PLUS) {
                    if ((t = McGetToken( FALSE )) == MCTOK_NUMBER) {
                        MessageInfo->Id = TokenNumericValue;
                        MessageInfo->Method = MSG_PLUS_VALUE;
                        }
                    else {
                        McInputError( "Number must follow %s=+", TRUE, TokenKeyword->Name );
                        return( FALSE );
                        }
                    }
                else {
                    McUnGetToken();
                    }

                }
            else {
                McInputError( "Equal sign must follow %s", TRUE, TokenKeyword->Name );
                return( FALSE );
                }
            break;

        case MCTOK_SEVERITY_KEYWORD:
            if ((t = McGetToken( FALSE )) == MCTOK_EQUAL) {
                if (!McParseName( SeverityNames, &CurrentSeverityName )) {
                    return( FALSE );
                    }
                }
            else {
                McInputError( "Equal sign must follow %s", TRUE, TokenKeyword->Name );
                return( FALSE );
                }
            break;

        case MCTOK_FACILITY_KEYWORD:
            if ((t = McGetToken( FALSE )) == MCTOK_EQUAL) {
                if (!McParseName( FacilityNames, &CurrentFacilityName )) {
                    return( FALSE );
                    }
                }
            else {
                McInputError( "Equal sign must follow %s", TRUE, TokenKeyword->Name );
                return( FALSE );
                }
            break;

        case MCTOK_SYMBOLNAME_KEYWORD:
            if ((t = McGetToken( FALSE )) == MCTOK_EQUAL) {
                if ((t = McGetToken( FALSE )) == MCTOK_NAME) {
                    MessageInfo->SymbolicName = McMakeString( TokenCharValue );
                    }
                else {
                    McInputError( "Symbol name must follow %s=+", TRUE, TokenKeyword->Name );
                    return( FALSE );
                    }
                }
            else {
                McInputError( "Equal sign must follow %s", TRUE, TokenKeyword->Name );
                return( FALSE );
                }
            break;


        case MCTOK_END_OF_LINE_COMMENT:
            MessageInfo->EndOfLineComment = McMakeString( TokenCharValue );
            break;

        case MCTOK_LANGUAGE_KEYWORD:
            McUnGetToken();


            if (MessageInfo->Method == MSG_PLUS_ONE) {
                MessageInfo->Id = CurrentFacilityName->LastId + 1;
                }
            else
            if (MessageInfo->Method == MSG_PLUS_VALUE) {
                MessageInfo->Id = CurrentFacilityName->LastId + MessageInfo->Id;
                }

            if (MessageInfo->Id > 0xFFFFL) {
                McInputError( "Message Id value (%lx) too large", TRUE, (PVOID)MessageInfo->Id );
                return( FALSE );
                }

            MessageInfo->Id |= (CurrentSeverityName->Id << 30) |
                               CustomerMsgIdBit |
                               (CurrentFacilityName->Id << 16);

            fprintf( HeaderFile, "//\r\n" );
            if (MessageInfo->SymbolicName) {
                fprintf( HeaderFile, "// MessageId: %s\r\n",
                                     MessageInfo->SymbolicName
                       );
                }
            else {
                fprintf( HeaderFile, "// MessageId: 0x%08lXL (No symbolic name defined)\r\n",
                                     MessageInfo->Id
                       );
                }

            fprintf( HeaderFile, "//\r\n" );
            fprintf( HeaderFile, "// MessageText:\r\n" );
            fprintf( HeaderFile, "//\r\n" );

            if (McParseMessageText( MessageInfo )) {
                fprintf( HeaderFile, "//\r\n" );
                if (MessageInfo->SymbolicName) {

                    if (MessageIdTypeName != NULL) {
                        fprintf( HeaderFile, GenerateDecimalValues ?
                                             "#define %-32s ((%s)%ldL)" :
                                             "#define %-32s ((%s)0x%08lXL)",
                                             MessageInfo->SymbolicName,
                                             MessageIdTypeName,
                                             MessageInfo->Id
                               );
                        }
                    else {
                        fprintf( HeaderFile, GenerateDecimalValues ?
                                             "#define %-32s %ldL" :
                                             "#define %-32s 0x%08lXL",
                                             MessageInfo->SymbolicName,
                                             MessageInfo->Id
                               );
                        }
                    }

                if (MessageInfo->EndOfLineComment) {
                    fprintf( HeaderFile, "    %s", MessageInfo->EndOfLineComment );
                    }
                else {
                    fprintf( HeaderFile, "\r\n" );
                    }
                fprintf( HeaderFile, "\r\n" );

                if (Messages == NULL) {
                    Messages = MessageInfo;
                    }
                else {
                    MessageInfoTemp = Messages;

                    //
                    //  Scan the existing messages to see if this message
                    //  exists in the message file.
                    //
                    //  If it does, generate and error for the user.
                    //

                    while (MessageInfoTemp != NULL) {

                        if (MessageInfoTemp->Id == MessageInfo->Id) {
                            McInputError( "Duplicate message ID - 0x%lx", FALSE, (PVOID)MessageInfo->Id );
                            }

                        MessageInfoTemp = MessageInfoTemp->Next;
                        }

                    CurrentMessage->Next = MessageInfo;
                    }

                CurrentMessage = MessageInfo;
                CurrentFacilityName->LastId = MessageInfo->Id & 0xFFFF;
                return( TRUE );
                }
            else {
                return( FALSE );
                }

        default:
            McInputError( "Invalid message definition token - '%s'", TRUE, TokenCharValue );
            return( FALSE );
            }
        }

    return( FALSE );
}


char MessageTextBuffer[ 8192 ];

BOOLEAN
McParseMessageText(
    PMESSAGE_INFO MessageInfo
    )
{
    PLANGUAGE_INFO MessageText, *pp;
    char *src, *dst;
    unsigned int t, n;
    BOOLEAN FirstLanguageProcessed;

    pp = &MessageInfo->MessageText;

    FirstLanguageProcessed = FALSE;
    while ((t = McGetToken( TRUE )) != MCTOK_END_OF_FILE) {
        if (t == MCTOK_LANGUAGE_KEYWORD) {
            if ((t = McGetToken( FALSE )) == MCTOK_EQUAL) {
                if (!McParseName( LanguageNames, &CurrentLanguageName )) {
                    return( FALSE );
                    }
                }
            else {
                McInputError( "Equal sign must follow %s", TRUE, TokenKeyword->Name );
                return( FALSE );
                }
            }
        else {
            McUnGetToken();
            break;
            }

        MessageText = malloc( sizeof( *MessageText ) );
        MessageText->Next = NULL;
        MessageText->Id = CurrentLanguageName->Id;
        MessageText->Length = 0;
        MessageText->Text = NULL;

        dst = MessageTextBuffer;
        while (src = McGetLine()) {
            if (!strcmp( src, ".\r\n" )) {
                if (MessageText->Length == 0) {
                    if (MessageInfo->SymbolicName) {
                        strcpy( dst, MessageInfo->SymbolicName );
                        }
                    else {
                        sprintf( dst, "No symbolic name defined for0x%08lXL" );
                        }

                    strcat( dst, "\r\n" );
                    if (!FirstLanguageProcessed) {
                        fprintf( HeaderFile, "//  %s", dst );
                        }

                    n = strlen( dst );
                    dst += n;
                    MessageText->Length += n;
                    }

                McSkipLine();
                break;
                }
            else
            if (!strnicmp( src, "LanguageId=", 11 ) ||
                !strnicmp( src, "MessageId=", 10 )
               ) {
                McInputError( "Unterminated message definition", TRUE, NULL );
                return( FALSE );
                }

            if (!FirstLanguageProcessed) {
                fprintf( HeaderFile, "//  %s", src );
                }

            n = strlen( src );
            if (MessageText->Length + n > sizeof( MessageTextBuffer )) {
                McInputError( "Message text too long - > %ld", TRUE,
                              (PVOID)(ULONG)sizeof( MessageTextBuffer )
                            );
                return( FALSE );
                }

            strcpy( dst, src );
            dst += n;
            MessageText->Length += n;
            }
        *dst = '\0';

        n = ((USHORT)MessageText->Length)+1;
        MessageText->Text = malloc( n );
        memcpy( MessageText->Text, MessageTextBuffer, n );
        *pp = MessageText;
        pp = &MessageText->Next;
        FirstLanguageProcessed = TRUE;
        }

    return( TRUE );
}


BOOLEAN
McParseNameList(
    PNAME_INFO *NameListHead,
    BOOLEAN ValueRequired,
    ULONG MaximumValue
    )
{
    unsigned int t;
    PNAME_INFO p;
    char *Name;
    ULONG Id;
    PVOID Value;

    while ((t = McGetToken( FALSE )) != MCTOK_END_OF_FILE) {
        if (t == MCTOK_RIGHT_PAREN) {
            return( TRUE );
            }

        if (t == MCTOK_NAME) {
            Name = McMakeString( TokenCharValue );
            Id = 0;
            Value = NULL;
            if ((t = McGetToken( FALSE )) == MCTOK_EQUAL) {
                if ((t = McGetToken( FALSE )) == MCTOK_NUMBER) {
                    Id = TokenNumericValue;
                    if ((t = McGetToken( FALSE )) == MCTOK_COLON) {
                        if ((t = McGetToken( FALSE )) == MCTOK_NAME) {
                            Value = McMakeString( TokenCharValue );
                            }
                        else {
                            McInputError( "File name must follow =%ld:", TRUE, (PVOID)Id );
                            return( FALSE );
                            }
                        }
                    else {
                        if (ValueRequired) {
                            McInputError( "Colon must follow =%ld", TRUE, (PVOID)Id );
                            return( FALSE );
                            }

                        McUnGetToken();
                        }
                    }
                else {
                    McInputError( "Number must follow %s=", TRUE, Name );
                    return( FALSE );
                    }
                }
            else {
                McInputError( "Equal sign name must follow %s", TRUE, Name );
                return( FALSE );
                }

            if (Id > MaximumValue) {
                McInputError( "Value is too large (> %lx)", TRUE, (PVOID)MaximumValue );
                return( FALSE );
                }

            p = McAddName( NameListHead, Name, Id, Value );
            free( Name );
            }
        }

    return( FALSE );
}

BOOLEAN
McParseName(
    PNAME_INFO NameListHead,
    PNAME_INFO *Result
    )
{
    unsigned int t;
    PNAME_INFO p;

    if ((t = McGetToken( FALSE )) == MCTOK_NAME) {
        p = McFindName( NameListHead, TokenCharValue );
        if (p != NULL) {
            *Result = p;
            return( TRUE );
            }
        else {
            McInputError( "Invalid name - %s", TRUE, TokenCharValue );
            }
        }
    else {
        McInputError( "Missing name after %s=", TRUE, TokenKeyword->Name );
        }

    return( FALSE );
}
