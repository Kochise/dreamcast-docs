/*++

Copyright (c) 1991-1997 Microsoft Corporation

Module Name:

    mcout.c

Abstract:

    This file contains the output functions of the Win32 Message Compiler (MC)

--*/

#include "mc.h"

PMESSAGE_BLOCK MessageBlocks = NULL;
int NumberOfBlocks = 0;

/*++

Routine Description:

Arguments:


Return Value:


--*/


BOOLEAN
McBlockMessages( void )
{
    PMESSAGE_BLOCK p, *pp;
    PMESSAGE_INFO MessageInfo;

    pp = &MessageBlocks;
    p = NULL;

    MessageInfo = Messages;
    while (MessageInfo) {
        if (p) {
            if (p->HighId+1 == MessageInfo->Id) {
                p->HighId += 1;
                }
            else {
                pp = &p->Next;
                }
            }

        if (!*pp) {
            NumberOfBlocks += 1;
            p = malloc( sizeof( *p ) );
            p->Next = NULL;
            p->LowId = MessageInfo->Id;
            p->HighId = MessageInfo->Id;
            p->LowInfo = MessageInfo;
            *pp = p;
            }

        MessageInfo = MessageInfo->Next;
        }

    return( TRUE );
}

/*++

Routine Description:

Arguments:


Return Value:


--*/


BOOLEAN
McWriteBinaryFiles( void )
{
    PNAME_INFO LanguageName, *pp;
    PLANGUAGE_INFO LanguageInfo;
    PMESSAGE_INFO MessageInfo;
    PMESSAGE_BLOCK BlockInfo;
    char *FileName;
    ULONG cb;
    ULONG MessageOffset;
    MESSAGE_RESOURCE_ENTRY MessageEntry;
    MESSAGE_RESOURCE_BLOCK MessageBlock;
    MESSAGE_RESOURCE_DATA  MessageData;
    ULONG Zeroes = 0;
    ULONG NumberOfMessages;

    FileName = BinaryMessageFileName;
    FileName += strlen( FileName );

    pp = &LanguageNames;
    while (LanguageName = *pp) {
        pp = &LanguageName->Next;
        if (!LanguageName->Used) {
            continue;
            }

        strcpy( FileName, LanguageName->Value );
        strcat( FileName, ".bin" );
        if (!(BinaryMessageFile = fopen( BinaryMessageFileName, "wb" ))) {
            McInputError( "unable to open output file - %s", TRUE, BinaryMessageFileName );
            return( FALSE );
            }

        if (VerboseOutput) {
            fprintf( stderr, "Writing %s\n", BinaryMessageFileName );
            }

        fprintf( RcInclFile, "LANGUAGE 0x%x,0x%x\r\n",
                             PRIMARYLANGID( LanguageName->Id ),
                             SUBLANGID( LanguageName->Id )
               );

        fprintf( RcInclFile, "1 11 %s\r\n", FileName );

        NumberOfMessages = 0L;

        MessageData.NumberOfBlocks = NumberOfBlocks;
        MessageOffset = fwrite( &MessageData,
                                1,
                                (size_t)FIELD_OFFSET( MESSAGE_RESOURCE_DATA,
                                                      Blocks[ 0 ]
                                                    ),
                                BinaryMessageFile
                              );
        MessageOffset += NumberOfBlocks * sizeof( MessageBlock );

        BlockInfo = MessageBlocks;
        while (BlockInfo) {
            MessageBlock.LowId = BlockInfo->LowId;
            MessageBlock.HighId = BlockInfo->HighId;
            MessageBlock.OffsetToEntries = MessageOffset;
            fwrite( &MessageBlock, 1, sizeof( MessageBlock ), BinaryMessageFile );

            BlockInfo->InfoLength = 0;
            MessageInfo = BlockInfo->LowInfo;
            while (MessageInfo != NULL && MessageInfo->Id <= BlockInfo->HighId) {
                LanguageInfo = MessageInfo->MessageText;
                while (LanguageInfo) {
                    if (LanguageInfo->Id == LanguageName->Id) {
                        break;
                        }
                    else {
                        LanguageInfo = LanguageInfo->Next;
                        }
                    }

                if (LanguageInfo != NULL) {
                    cb = FIELD_OFFSET( MESSAGE_RESOURCE_ENTRY, Text[ 0 ] ) +
                         LanguageInfo->Length + 1;

                    cb = (cb + 3) & ~3;
                    BlockInfo->InfoLength += cb;
                    }
                else {
                    fprintf( stderr,
                             "MC: No %s language text for %s\n",
                             LanguageName->Name,
                             MessageInfo->SymbolicName
                           );
                    fclose( BinaryMessageFile );
                    return( FALSE );
                    }

                MessageInfo = MessageInfo->Next;
                }

            if (VerboseOutput) {
                fprintf( stderr, "    [%08lx .. %08lx] - %lu bytes\n",
                         BlockInfo->LowId,
                         BlockInfo->HighId,
                         BlockInfo->InfoLength
                       );
                }

            MessageOffset += BlockInfo->InfoLength;
            BlockInfo = BlockInfo->Next;
            }

        BlockInfo = MessageBlocks;
        while (BlockInfo) {
            MessageInfo = BlockInfo->LowInfo;
            while (MessageInfo != NULL && MessageInfo->Id <= BlockInfo->HighId) {
                LanguageInfo = MessageInfo->MessageText;
                while (LanguageInfo) {
                    if (LanguageInfo->Id == LanguageName->Id) {
                        break;
                        }
                    else {
                        LanguageInfo = LanguageInfo->Next;
                        }
                    }

                if (LanguageInfo != NULL) {
                    cb = FIELD_OFFSET( MESSAGE_RESOURCE_ENTRY, Text[ 0 ] ) +
                         LanguageInfo->Length + 1;

                    cb = (cb + 3) & ~3;

                    MessageEntry.Length = (USHORT)cb;
                    MessageEntry.Flags = 0;

                    cb = fwrite( &MessageEntry,
                                 1,
                                 (size_t)FIELD_OFFSET( MESSAGE_RESOURCE_ENTRY,
                                                       Text[ 0 ]
                                                     ),
                                 BinaryMessageFile
                               );
                    cb += fwrite( LanguageInfo->Text,
                                  1,
                                  (size_t)LanguageInfo->Length,
                                  BinaryMessageFile
                                );

                    NumberOfMessages++;

                    cb = MessageEntry.Length - cb;
                    if (cb) {
                        fwrite( &Zeroes,
                                1,
                                (size_t)cb,
                                BinaryMessageFile
                              );
                        }
                    }

                MessageInfo = MessageInfo->Next;
                }

            BlockInfo = BlockInfo->Next;
            }

        if (VerboseOutput) {
            fprintf( stderr, "    Total of %lu messages, %lu bytes\n",
                             NumberOfMessages,
                             ftell( BinaryMessageFile )
                   );
            }

        fclose( BinaryMessageFile );
        }

    return( TRUE );
}
