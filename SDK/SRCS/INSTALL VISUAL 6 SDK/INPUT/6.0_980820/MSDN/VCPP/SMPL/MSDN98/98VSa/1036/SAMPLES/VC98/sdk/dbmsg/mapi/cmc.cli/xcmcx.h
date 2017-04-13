/*
 -  X C M C X . H
 -
 *  Purpose:
 *      CMC return codes to be used by the string table in the resource file.
 *      This is necessary since the resource compiler can't process IDs with
 *      casts in them.
 *
 */

#define CMC_SUCCESS                         0
#define CMC_E_AMBIGUOUS_RECIPIENT           1
#define CMC_E_ATTACHMENT_NOT_FOUND          2
#define CMC_E_ATTACHMENT_OPEN_FAILURE       3
#define CMC_E_ATTACHMENT_READ_FAILURE       4
#define CMC_E_ATTACHMENT_WRITE_FAILURE      5
#define CMC_E_COUNTED_STRING_UNSUPPORTED    6
#define CMC_E_DISK_FULL                     7
#define CMC_E_FAILURE                       8
#define CMC_E_INSUFFICIENT_MEMORY           9
#define CMC_E_INVALID_CONFIGURATION         10
#define CMC_E_INVALID_ENUM                  11
#define CMC_E_INVALID_FLAG                  12
#define CMC_E_INVALID_MEMORY                13
#define CMC_E_INVALID_MESSAGE_PARAMETER     14
#define CMC_E_INVALID_MESSAGE_REFERENCE     15
#define CMC_E_INVALID_PARAMETER             16
#define CMC_E_INVALID_SESSION_ID            17
#define CMC_E_INVALID_UI_ID                 18
#define CMC_E_LOGON_FAILURE                 19
#define CMC_E_MESSAGE_IN_USE                20
#define CMC_E_NOT_SUPPORTED                 21
#define CMC_E_PASSWORD_REQUIRED             22
#define CMC_E_RECIPIENT_NOT_FOUND           23
#define CMC_E_SERVICE_UNAVAILABLE           24
#define CMC_E_TEXT_TOO_LARGE                25
#define CMC_E_TOO_MANY_FILES                26
#define CMC_E_TOO_MANY_RECIPIENTS           27
#define CMC_E_UNABLE_TO_NOT_MARK_AS_READ    28
#define CMC_E_UNRECOGNIZED_MESSAGE_TYPE     29
#define CMC_E_UNSUPPORTED_ACTION            30
#define CMC_E_UNSUPPORTED_CHARACTER_SET     31
#define CMC_E_UNSUPPORTED_DATA_EXT          32
#define CMC_E_UNSUPPORTED_FLAG              33
#define CMC_E_UNSUPPORTED_FUNCTION_EXT      34
#define CMC_E_UNSUPPORTED_VERSION           35
#define CMC_E_USER_CANCEL                   36
#define CMC_E_USER_NOT_LOGGED_ON            37
