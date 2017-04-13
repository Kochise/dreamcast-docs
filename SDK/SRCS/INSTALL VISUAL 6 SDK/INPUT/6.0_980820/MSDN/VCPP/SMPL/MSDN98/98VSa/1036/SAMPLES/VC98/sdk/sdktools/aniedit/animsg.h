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
// MessageId: MSG_INVALIDCURSORFILE
//
// MessageText:
//
//  %1 is not a valid animated cursor file.
//
#define MSG_INVALIDCURSORFILE            0x00000000L

//
// MessageId: MSG_OUTOFMEM
//
// MessageText:
//
//  There is not enough free memory for this operation.
//
#define MSG_OUTOFMEM                     0x00000001L

//
// MessageId: MSG_OUTOFRESOUCES
//
// MessageText:
//
//  There are not enough system resources to continue.  Try closing some
//  applications and trying again.
//
#define MSG_OUTOFRESOUCES                0x00000002L

//
// MessageId: MSG_CANTOPENFILE
//
// MessageText:
//
//  The file %1 can not be opened.  Please verify that you have permission
//  to access the file.
//
#define MSG_CANTOPENFILE                 0x00000003L

//
// MessageId: MSG_CANTCREATEFILE
//
// MessageText:
//
//  The file %1 can not be created.  Please verify that there is free
//  space on the drive and that you have write permission.
//
#define MSG_CANTCREATEFILE               0x00000004L

//
// MessageId: MSG_MUSTEQONEFAME
//
// MessageText:
//
//  You must have one and only one frame selected to use this function.
//
#define MSG_MUSTEQONEFAME                0x00000005L

//
// MessageId: MSG_LESSEQONEFRAME
//
// MessageText:
//
//  You must have no more than one frame selected to use this function.
//
#define MSG_LESSEQONEFRAME               0x00000006L

//
// MessageId: MSG_FILEWRITEERR
//
// MessageText:
//
//  An error occured while writing file: %1.  Please make sure there is
//  free space on the drive and that you have write permission.
//
#define MSG_FILEWRITEERR                 0x00000007L

//
// MessageId: MSG_RATERANGE
//
// MessageText:
//
//  You must specify a number greater than zero.
//
#define MSG_RATERANGE                    0x00000008L

//
// MessageId: MSG_LITERAL
//
// MessageText:
//
//  %1
//
#define MSG_LITERAL                      0x00000009L

//
// MessageId: MSG_FRAMESSELECTED
//
// MessageText:
//
//  %1!d! frames selected
//
#define MSG_FRAMESSELECTED               0x0000000AL

//
// MessageId: MSG_FRAMEOFSEL
//
// MessageText:
//
//  Frame %1!d! of %2!d! selected
//
#define MSG_FRAMEOFSEL                   0x0000000BL

//
// MessageId: MSG_ALLFRAMES
//
// MessageText:
//
//  All frames selected
//
#define MSG_ALLFRAMES                    0x0000000CL

//
// MessageId: MSG_NOFRAMESSEL
//
// MessageText:
//
//  No frames selected
//
#define MSG_NOFRAMESSEL                  0x0000000DL

//
// MessageId: MSG_SAVEFILEQUEST
//
// MessageText:
//
//  Save current file %1?
//
#define MSG_SAVEFILEQUEST                0x0000000EL

//
// MessageId: MSG_PASTEERR
//
// MessageText:
//
//  One of the frames in the clipboard could not be copied to the animation
//  sequence.  Press OK to continue pasting with the next frame, or Cancel to
//  abort the operation.
//
#define MSG_PASTEERR                     0x0000000FL

//
// MessageId: MSG_NOIMAGEDIT
//
// MessageText:
//
//  You must have the Image Editor ('%1') on your path to use this function.
//
#define MSG_NOIMAGEDIT                   0x00000010L

