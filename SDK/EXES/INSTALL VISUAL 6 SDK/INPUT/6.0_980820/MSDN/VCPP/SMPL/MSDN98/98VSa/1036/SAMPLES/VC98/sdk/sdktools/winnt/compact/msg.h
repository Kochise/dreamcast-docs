/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) 1994-1995  Microsoft Corporation

Module Name:

    msg.h

Abstract:

    This file contains the message definitions for the Win32 Compact
    utility.

Author:

    Gary Kimura        [garyki]        13-Jan-1994

Revision History:

--*/

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


//
// Define the severity codes
//


//
// MessageId: COMPACT_OK
//
// MessageText:
//
//  [OK]
//
#define COMPACT_OK                       0x00000001L

//
// MessageId: COMPACT_ERR
//
// MessageText:
//
//  [ERR]
//
#define COMPACT_ERR                      0x00000002L

//
// MessageId: COMPACT_LIST_CDIR
//
// MessageText:
//
//  
//   Listing %1
//   New files added to this directory will be compressed.
//  
//
#define COMPACT_LIST_CDIR                0x00000006L

//
// MessageId: COMPACT_LIST_UDIR
//
// MessageText:
//
//  
//   Listing %1
//   New files added to this directory will not be compressed.
//  
//
#define COMPACT_LIST_UDIR                0x00000007L

//
// MessageId: COMPACT_LIST_SUMMARY
//
// MessageText:
//
//  
//  Of %1 files within %2 directories
//  %3 are compressed and %4 are not compressed.
//  %5 total bytes of data are stored in %6 bytes.
//  The compression ratio is %7 to 1.
//  
//
#define COMPACT_LIST_SUMMARY             0x00000008L

//
// MessageId: COMPACT_COMPRESS_DIR
//
// MessageText:
//
//  
//   Setting the directory %1 to compress new files %0
//  
//
#define COMPACT_COMPRESS_DIR             0x00000009L

//
// MessageId: COMPACT_COMPRESS_CDIR
//
// MessageText:
//
//  
//   Compressing files in %1
//  
//
#define COMPACT_COMPRESS_CDIR            0x0000000AL

//
// MessageId: COMPACT_COMPRESS_UDIR
//
// MessageText:
//
//  
//   Compressing files in %1
//  
//
#define COMPACT_COMPRESS_UDIR            0x0000000BL

//
// MessageId: COMPACT_COMPRESS_SUMMARY
//
// MessageText:
//
//  
//  %1 files within %2 directories were compressed.
//  %3 total bytes of data are stored in %4 bytes.
//  The compression ratio is %5 to 1.
//
#define COMPACT_COMPRESS_SUMMARY         0x0000000CL

//
// MessageId: COMPACT_UNCOMPRESS_DIR
//
// MessageText:
//
//  
//   Setting the directory %1 not to compress new files %0
//  
//
#define COMPACT_UNCOMPRESS_DIR           0x0000000DL

//
// MessageId: COMPACT_UNCOMPRESS_CDIR
//
// MessageText:
//
//  
//   Uncompressing files in %1
//  
//
#define COMPACT_UNCOMPRESS_CDIR          0x0000000EL

//
// MessageId: COMPACT_UNCOMPRESS_UDIR
//
// MessageText:
//
//  
//   Uncompressing files in %1
//  
//
#define COMPACT_UNCOMPRESS_UDIR          0x0000000FL

//
// MessageId: COMPACT_UNCOMPRESS_SUMMARY
//
// MessageText:
//
//  
//  %1 files within %2 directories were uncompressed.
//  
//
#define COMPACT_UNCOMPRESS_SUMMARY       0x00000010L

//
// MessageId: COMPACT_NO_MEMORY
//
// MessageText:
//
//  Out of memory.
//
#define COMPACT_NO_MEMORY                0x00000013L

//
// MessageId: COMPACT_SKIPPING
//
// MessageText:
//
//  [Skipping %1]
//
#define COMPACT_SKIPPING                 0x00000014L

//
// MessageId: COMPACT_THROW
//
// MessageText:
//
//  %1%0
//
#define COMPACT_THROW                    0x00000015L

//
// MessageId: COMPACT_THROW_NL
//
// MessageText:
//
//  %1
//
#define COMPACT_THROW_NL                 0x00000016L

//
// MessageId: COMPACT_WRONG_FILE_SYSTEM
//
// MessageText:
//
//  %1: The file system does not support compression.
//
#define COMPACT_WRONG_FILE_SYSTEM        0x00000017L

//
// MessageId: COMPACT_TO_ONE
//
// MessageText:
//
//  to 1 %0
//
#define COMPACT_TO_ONE                   0x00000018L

//
// MessageId: COMPACT_INVALID_PATH
//
// MessageText:
//
//  Invalid drive specification: %1
//
#define COMPACT_INVALID_PATH             0x00000019L

//
// MessageId: COMPACT_WRONG_FILE_SYSTEM_OR_CLUSTER_SIZE
//
// MessageText:
//
//  %1: The file system does not support compression or
//  the cluster size of the volume is larger than 4096 bytes.
//
#define COMPACT_WRONG_FILE_SYSTEM_OR_CLUSTER_SIZE 0x0000001AL

//
// MessageId: COMPACT_USAGE
//
// MessageText:
//
//  Displays or alters the compression of files on NTFS partitions.
//  
//  COMPACT [/C | /U] [/S[:dir]] [/A] [/I] [/F] [/Q] [filename [...]]
//  
//    /C        Compresses the specified files.  Directories will be marked
//              so that files added afterward will be compressed.
//    /U        Uncompresses the specified files.  Directories will be marked
//              so that files added afterward will not be compressed.
//    /S        Performs the specified operation on files in the given
//              directory and all subdirectories.  Default "dir" is the
//              current directory.
//    /A        Displays files with the hidden or system attributes.  These
//              files are omitted by default.
//    /I        Continues performing the specified operation even after errors
//              have occurred.  By default, COMPACT stops when an error is
//              encountered.
//    /F        Forces the compress operation on all specified files, even
//              those which are already compressed.  Already-compressed files
//              are skipped by default.
//    /Q        Reports only the most essential information.
//    filename  Specifies a pattern, file, or directory.
//  
//    Used without parameters, COMPACT displays the compression state of
//    the current directory and any files it contains. You may use multiple
//    filenames and wildcards.  You must put spaces between multiple
//    parameters.
//
#define COMPACT_USAGE                    0x00000032L

