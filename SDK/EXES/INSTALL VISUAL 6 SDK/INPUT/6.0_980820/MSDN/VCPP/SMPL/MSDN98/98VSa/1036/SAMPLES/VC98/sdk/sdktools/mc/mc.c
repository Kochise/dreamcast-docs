/*++

Copyright (c) 1991-1997 Microsoft Corporation

Module Name:

    mc.c

Abstract:

    This is the main source file for the Win32 Message Compiler (MC)

--*/

#include "mc.h"

#include "windows.h"


void
ConvertAppToOem( unsigned argc, char* argv[] )
/*++

Routine Description:

    Converts the command line from ANSI to OEM, and force the app
    to use OEM APIs

Arguments:

    argc - Standard C argument count.

    argv - Standard C argument strings.

Return Value:

    None.

--*/

{
    unsigned i;

    for( i=0; i<argc; i++ ) {
       CharToOem( argv[i], argv[i] );
    }
    SetFileApisToOEM();
}




void
McPrintUsage( void )
{
    fprintf( stderr, "usage: MC [-?vws] [-h dirspec] [-r dirspec] filename.mc\n" );
    fprintf( stderr, "       -? - displays this message\n" );
    fprintf( stderr, "       -v - gives verbose output.\n" );
    fprintf( stderr, "       -c - sets the Customer bit in all the message Ids.\n" );
    fprintf( stderr, "       -d - numeric values in header file in decimal.\n" );
    fprintf( stderr, "       -w - warns if message text contains non-OS/2 compatible inserts.\n" );
    fprintf( stderr, "       -s - insert symbolic name as first line of each message.\n" );
    fprintf( stderr, "       -h pathspec - gives the path of where to create the C include file\n" );
    fprintf( stderr, "                     Default is .\\\n" );
    fprintf( stderr, "       -r pathspec - gives the path of where to create the RC include file\n" );
    fprintf( stderr, "                     and the binary message resource files it includes.\n" );
    fprintf( stderr, "                     Default is .\\\n" );
    fprintf( stderr, "       filename.mc - gives the names of a message text file\n" );
    fprintf( stderr, "                     to compile.\n" );
}


int
_CRTAPI1 main(
    int argc,
    char *argv[]
    )
{
    char c, *s, *s1;
    int ShowUsage;


    ConvertAppToOem( argc, argv );
    FacilityNames = NULL;
    SeverityNames = NULL;
    LanguageNames = NULL;

    MessageIdTypeName = NULL;

    CurrentFacilityName =
    McAddName( &FacilityNames, "Application",  0x0, NULL );
    CurrentSeverityName =
    McAddName( &SeverityNames, "Success",       0x0, NULL );

    McAddName( &SeverityNames, "Informational", 0x1, NULL );
    McAddName( &SeverityNames, "Warning",       0x2, NULL );
    McAddName( &SeverityNames, "Error",         0x3, NULL );

    McAddName( &LanguageNames,
               "English",
               MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
               "MSG00001"
             );

    strcpy( HeaderFileName, ".\\" );
    strcpy( RcInclFileName, ".\\" );
    strcpy( BinaryMessageFileName, ".\\" );
    MessageFileName[ 0 ] = '\0';

    McInitLexer();

    VerboseOutput = FALSE;
    WarnOs2Compatible = FALSE;
    GenerateDecimalValues = FALSE;
    ShowUsage = FALSE;
    while (--argc) {
        s = *++argv;
        if (*s == '-' || *s == '/') {
            while (c = *++s) {
                switch( c ) {
                case '?':
                    McPrintUsage();
                    exit( 0 );
                    break;

                case 'c':
                    CustomerMsgIdBit = 0x1 << 29;
                    break;

                case 'v':
                    VerboseOutput = TRUE;
                    break;

                case 'd':
                    GenerateDecimalValues = TRUE;
                    break;

                case 'w':
                    WarnOs2Compatible = TRUE;
                    break;

                case 's':
                    InsertSymbolicName = TRUE;
                    break;

                case 'h':
                    if (--argc) {
                        strcpy( s1 = HeaderFileName, *++argv );
			s1 += strlen( s1 );
                        s1 = CharPrev( HeaderFileName, s1 );
                        if (*s1 != '\\' && *s1 != '/') {
                            s1 = CharNext( s1 );
                            *s1 = '\\';
                            *++s1 = '\0';
			    }
			}
                    else {
                        argc++;
                        fprintf( stderr, "MC: missing argument for -%c switch\n", (USHORT)c );
                        ShowUsage = TRUE;
                        }
                    break;

                case 'r':
                    if (--argc) {
			strcpy( s1 = RcInclFileName, *++argv );
                        s1 += strlen( s1 );
                        s1 = CharPrev( HeaderFileName, s1 );
                        if (*s1 != '\\' && *s1 != '/') {
                            s1 = CharNext( s1 );
                            *s1 = '\\';
                            *++s1 = '\0';
                        }
			strcpy( BinaryMessageFileName, RcInclFileName );
                        }
                    else {
                        argc++;
                        fprintf( stderr, "MC: missing argument for -%c switch\n", (USHORT)c );
                        ShowUsage = TRUE;
                        }
                    break;

                default:
                    fprintf( stderr, "MC: Invalid switch: %c\n", (USHORT)c );
                    ShowUsage = TRUE;
                    break;
                    }
                }
            }
        else
        if (strlen( MessageFileName )) {
            fprintf( stderr, "MC: may only specify one message file to compile.\n" );
            ShowUsage = TRUE;
            }
        else {
            strcpy( MessageFileName, s );
            }
        }

    if (ShowUsage) {
        McPrintUsage();
        exit( 1 );
        }

    ResultCode = 1;
    if (McParseFile() && McBlockMessages() && McWriteBinaryFiles()) {
        ResultCode = 0;
        }
    else {
        McCloseInputFile();
        McCloseOutputFiles();
        }

    return( ResultCode );
}
