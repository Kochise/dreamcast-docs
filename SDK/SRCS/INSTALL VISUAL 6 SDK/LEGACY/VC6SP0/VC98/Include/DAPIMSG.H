/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) Microsoft Corp. 1986-1996. All Rights Reserved.

Abstract:

    This file contains the message definitions for the Microsoft Exchange DAPI.DLL.

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
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_MASK             0x3
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: BERR_SUCCESS
//
// MessageText:
//
//  No error encountered.
//
#define BERR_SUCCESS                     0x00000000L

//
// MessageId: DAPI_FUNCTION_DAPI
//
// MessageText:
//
//  Directory API%0
//
#define DAPI_FUNCTION_DAPI               0x00000001L

//
// MessageId: DAPI_FUNCTION_BIMPORT
//
// MessageText:
//
//  Directory Import%0
//
#define DAPI_FUNCTION_BIMPORT            0x00000002L

//
// MessageId: DAPI_FUNCTION_BEXPORT
//
// MessageText:
//
//  Directory Export%0
//
#define DAPI_FUNCTION_BEXPORT            0x00000003L

//
// MessageId: DAPI_FUNCTION_NTEXPORT
//
// MessageText:
//
//  NT User Extractor%0
//
#define DAPI_FUNCTION_NTEXPORT           0x00000004L

//
// MessageId: DAPI_FUNCTION_NWEXPORT
//
// MessageText:
//
//  NetWare User Extractor%0
//
#define DAPI_FUNCTION_NWEXPORT           0x00000005L

// Progress-bar stuff
//
// MessageId: DAPIMSG_DISPLAY_CURRENT
//
// MessageText:
//
//  Currently processing:  %1%0
//
#define DAPIMSG_DISPLAY_CURRENT          0x00000006L

//
// MessageId: DAPIMSG_DISPLAY_CREATE
//
// MessageText:
//
//  Creating %2:  %1%0
//
#define DAPIMSG_DISPLAY_CREATE           0x00000007L

//
// MessageId: DAPIMSG_DISPLAY_MODIFY
//
// MessageText:
//
//  Modifying %2:  %1%0
//
#define DAPIMSG_DISPLAY_MODIFY           0x00000008L

//
// MessageId: DAPIMSG_DISPLAY_DELETE
//
// MessageText:
//
//  Deleting %2:  %1%0
//
#define DAPIMSG_DISPLAY_DELETE           0x00000009L

//
// MessageId: DAPIMSG_DISPLAY_EXPORTING
//
// MessageText:
//
//  Exporting %2:  %1%0
//
#define DAPIMSG_DISPLAY_EXPORTING        0x0000000AL

//
// MessageId: DAPIMSG_DISPLAY_EXTRACTING
//
// MessageText:
//
//  Extracting user account:  %1%0
//
#define DAPIMSG_DISPLAY_EXTRACTING       0x0000000BL

//
// MessageId: BIMPMSG_INITIALIZING
//
// MessageText:
//
//  Initializing -- Please wait...%0
//
#define BIMPMSG_INITIALIZING             0x0000000CL

//
// MessageId: DAPIMSG_READING
//
// MessageText:
//
//  Reading Users -- Please wait...%0
//
#define DAPIMSG_READING                  0x0000000DL

//
// MessageId: DAPIMSG_PROGRESS_TITLE
//
// MessageText:
//
//  Directory API%0
//
#define DAPIMSG_PROGRESS_TITLE           0x0000000EL

//
// MessageId: BIMPMSG_PROGRESS_TITLE
//
// MessageText:
//
//  Directory Import from %1%0
//
#define BIMPMSG_PROGRESS_TITLE           0x0000000FL

//
// MessageId: BEXPMSG_PROGRESS_TITLE
//
// MessageText:
//
//  Directory Export to %1%0
//
#define BEXPMSG_PROGRESS_TITLE           0x00000010L

//
// MessageId: NTEXPMSG_PROGRESS_TITLE
//
// MessageText:
//
//  Windows NT User Extraction to %1%0
//
#define NTEXPMSG_PROGRESS_TITLE          0x00000011L

//
// MessageId: NWEXPMSG_PROGRESS_TITLE
//
// MessageText:
//
//  NetWare User Extraction to %1%0
//
#define NWEXPMSG_PROGRESS_TITLE          0x00000012L

// >>> The following group of messages are used for start/stop logging and
// >>> for posting completion-notification message boxes for ALL bimport
// >>> processes (bimport, bexport, ntexport, nwexport).
// >>> NOTE:  !!!!PLEASE PLEASE PLEASE be VERY careful about rearranging
// >>>        ANY of the messages in this group.  
// Common strings
//
// MessageId: DAPI_MSG_COMPLETE_TITLE
//
// MessageText:
//
//  %1 Complete%0
//
#define DAPI_MSG_COMPLETE_TITLE          0x00000013L

//
// MessageId: DAPI_MSG_ONE_WARNING
//
// MessageText:
//
//  One warning event was encountered but not logged.
//
#define DAPI_MSG_ONE_WARNING             0x00000014L

//
// MessageId: DAPI_MSG_ONE_WARNING_REPORTED
//
// MessageText:
//
//  One warning description was recorded in the system's application event log.
//
#define DAPI_MSG_ONE_WARNING_REPORTED    0x00000015L

//
// MessageId: DAPI_MSG_WARNINGS
//
// MessageText:
//
//  %1!lu! warning events were encountered but not logged.
//
#define DAPI_MSG_WARNINGS                0x00000016L

//
// MessageId: DAPI_MSG_WARNINGS_REPORTED
//
// MessageText:
//
//  %1!lu! warning descriptions were recorded in the system's application event log.
//
#define DAPI_MSG_WARNINGS_REPORTED       0x00000017L

//
// MessageId: DAPI_MSG_NOERRORS
//
// MessageText:
//
//  No errors were encountered.
//
#define DAPI_MSG_NOERRORS                0x00000018L

//
// MessageId: DAPI_MSG_ONE_ERROR
//
// MessageText:
//
//  One error event was encountered but not logged.
//
#define DAPI_MSG_ONE_ERROR               0x00000019L

//
// MessageId: DAPI_MSG_ONE_ERROR_REPORTED
//
// MessageText:
//
//  One error description was recorded in the system's application event log.
//
#define DAPI_MSG_ONE_ERROR_REPORTED      0x0000001AL

//
// MessageId: DAPI_MSG_ERRORS
//
// MessageText:
//
//  %1!lu! error events were encountered but not logged.
//
#define DAPI_MSG_ERRORS                  0x0000001BL

//
// MessageId: DAPI_MSG_ERRORS_REPORTED
//
// MessageText:
//
//  %1!lu! error descriptions were recorded in the system's application event log.
//
#define DAPI_MSG_ERRORS_REPORTED         0x0000001CL

//
// MessageId: DAPI_MSG_ERRORS_COPIED
//
// MessageText:
//
//  The file %1 contains copies of all object descriptions containing errors.
//
#define DAPI_MSG_ERRORS_COPIED           0x0000001DL

//
// MessageId: DAPI_MSG_PASSWORD_FILE
//
// MessageText:
//
//  %nPlease see %1 for a list of created Windows NT Accounts.
//
#define DAPI_MSG_PASSWORD_FILE           0x0000001EL

// Directory Import start/stop messages
//
// MessageId: BIMPORT_STARTED
//
// MessageText:
//
//  Starting directory import from import file %1.
//
#define BIMPORT_STARTED                  0x4000001FL

//
// MessageId: BIMPORT_COMPLETE
//
// MessageText:
//
//  The directory import from file %1 is complete.
//
#define BIMPORT_COMPLETE                 0x40000020L

//
// MessageId: BIMPORT_COMPLETE_NOFILE
//
// MessageText:
//
//  The directory import is complete.
//
#define BIMPORT_COMPLETE_NOFILE          0x40000021L

//
// MessageId: BIMPORT_CANCELLED
//
// MessageText:
//
//  The directory import from file %1 was canceled by user request.
//
#define BIMPORT_CANCELLED                0x80000022L

//
// MessageId: BIMPORT_CANCELLED_NOFILE
//
// MessageText:
//
//  The directory import was canceled by user request.
//
#define BIMPORT_CANCELLED_NOFILE         0x80000023L

// Directory Export start/stop messages
//
// MessageId: BEXPORT_STARTED
//
// MessageText:
//
//  Starting the directory export to file %1.
//
#define BEXPORT_STARTED                  0x40000024L

//
// MessageId: BEXPORT_COMPLETE
//
// MessageText:
//
//  The directory export to file %1 is complete.
//
#define BEXPORT_COMPLETE                 0x40000025L

//
// MessageId: BEXPORT_COMPLETE_NOFILE
//
// MessageText:
//
//  The directory export is complete.
//
#define BEXPORT_COMPLETE_NOFILE          0x40000026L

//
// MessageId: BEXPORT_CANCELLED
//
// MessageText:
//
//  The directory export to file %1 was canceled by user request.
//
#define BEXPORT_CANCELLED                0x80000027L

//
// MessageId: BEXPORT_CANCELLED_NOFILE
//
// MessageText:
//
//  The directory export was canceled by user request.
//
#define BEXPORT_CANCELLED_NOFILE         0x80000028L

//
// MessageId: BEXPORT_STARTED_NOFILE
//
// MessageText:
//
//  Starting the directory export.
//
#define BEXPORT_STARTED_NOFILE           0x40000029L

// NTExport start/stop/completion messages
//
// MessageId: NTEXPORT_STARTED
//
// MessageText:
//
//  Starting the extraction of Windows NT user account information to file %1.
//
#define NTEXPORT_STARTED                 0x4000002AL

//
// MessageId: NTEXPORT_COMPLETE
//
// MessageText:
//
//  Extraction of Windows NT user account information to file %1 is complete.
//
#define NTEXPORT_COMPLETE                0x4000002BL

//
// MessageId: NTEXPORT_COMPLETE_NOFILE
//
// MessageText:
//
//  Extraction of Windows NT user account information is complete.
//
#define NTEXPORT_COMPLETE_NOFILE         0x4000002CL

//
// MessageId: NTEXPORT_CANCELLED
//
// MessageText:
//
//  Extraction of Windows NT user account information to file %1 was canceled by user request.
//
#define NTEXPORT_CANCELLED               0x8000002DL

//
// MessageId: NTEXPORT_CANCELLED_NOFILE
//
// MessageText:
//
//  Extraction of Windows NT user account information was canceled by user request.
//
#define NTEXPORT_CANCELLED_NOFILE        0x8000002EL

//
// MessageId: NTEXPORT_STARTED_NOFILE
//
// MessageText:
//
//  Starting the extraction of Windows NT user account information.
//
#define NTEXPORT_STARTED_NOFILE          0x4000002FL

// NWExport start/stop/completion messages
//
// MessageId: NWEXPORT_STARTED
//
// MessageText:
//
//  Starting the extraction of NetWare user account information to file %1.
//
#define NWEXPORT_STARTED                 0x40000030L

//
// MessageId: NWEXPORT_COMPLETE
//
// MessageText:
//
//  Extraction of NetWare user account information to file %1 is complete.
//
#define NWEXPORT_COMPLETE                0x40000031L

//
// MessageId: NWEXPORT_COMPLETE_NOFILE
//
// MessageText:
//
//  Extraction of NetWare user account information is complete.
//
#define NWEXPORT_COMPLETE_NOFILE         0x40000032L

//
// MessageId: NWEXPORT_CANCELLED
//
// MessageText:
//
//  Extraction of NetWare user account information to file %1 was canceled by user request.
//
#define NWEXPORT_CANCELLED               0x80000033L

//
// MessageId: NWEXPORT_CANCELLED_NOFILE
//
// MessageText:
//
//  Extraction of NetWare user account information was canceled by user request.
//
#define NWEXPORT_CANCELLED_NOFILE        0x80000034L

//
// MessageId: NWEXPORT_STARTED_NOFILE
//
// MessageText:
//
//  Starting the extraction of NetWare user account information.
//
#define NWEXPORT_STARTED_NOFILE          0x40000035L

// <<<< End of block containing start/stop/completion messages
// -------------------     DAPI Errors              -----------------------
//
// MessageId: BERR_GENERAL_FAILURE
//
// MessageText:
//
//  A general failure occurred.
//
#define BERR_GENERAL_FAILURE             0xC0000080L

//
// MessageId: DAPI_E_BAD_HANDLE
//
// MessageText:
//
//  A bad DAPI handle supplied to call.
//
#define DAPI_E_BAD_HANDLE                0xC0000081L    

//
// MessageId: DAPI_E_HEADER_MUST_BE_TEXT
//
// MessageText:
//
//  Header values must be specified as text strings.
//
#define DAPI_E_HEADER_MUST_BE_TEXT       0xC0000082L    

//
// MessageId: PDC_NOT_FOUND
//
// MessageText:
//
//  Unable to find the primary domain controller for domain %1.
//
#define PDC_NOT_FOUND                    0xC0000083L

//
// MessageId: PDC_NOT_RESPONDING
//
// MessageText:
//
//  Primary domain controller %1 is not responding.
//
#define PDC_NOT_RESPONDING               0xC0000084L

// -------------------     messages for BIMPORT     -----------------------
//
// MessageId: BIMPMSG_PROMPT_LOG_FULL
//
// MessageText:
//
//  The application event log is full. If you continue, you should increase the maximum log size or additional error information may not be written to the log. If you cancel, existing operations will not be undone.%n%nDo you want to continue with the %1?
//
#define BIMPMSG_PROMPT_LOG_FULL          0x00000085L

//
// MessageId: BIMPMSG_PROMPT_LOG_ERROR
//
// MessageText:
//
//  The following error was encountered when attempting to log an event in the application event log:
//  %2
//  
//  If you continue, additional error information may not be written to the log. 
//  If you cancel, existing operations will not be undone.
//  
//  Do you wish to continue with the %1?
//
#define BIMPMSG_PROMPT_LOG_ERROR         0x00000086L

//
// MessageId: BIMPMSG_PROMPT_LOG_FILE_ERROR
//
// MessageText:
//
//  An error was encountered when writing to the log file %1. If you continue, additional error information will not be written to the log file. If you cancel, completed operations will not be undone. %n%nDo you want to continue with the %2?
//
#define BIMPMSG_PROMPT_LOG_FILE_ERROR    0x00000087L

//
// MessageId: BWARN_ACCNT_EXISTS
//
// MessageText:
//
//  A Windows NT account for user %1 already exists.
//
#define BWARN_ACCNT_EXISTS               0x80000088L

//
// MessageId: BWARN_OVERRIDE_PDC_NOT_FOUND
//
// MessageText:
//
//  Windows NT account %1 could not be created because the primary domain controller (PDC) could not be found for domain %2.
//
#define BWARN_OVERRIDE_PDC_NOT_FOUND     0x80000089L

//
// MessageId: BWARN_DELETE_TARGET_DOES_NOT_EXIST
//
// MessageText:
//
//  Object %1 that was specified for deletion does not exist.
//
#define BWARN_DELETE_TARGET_DOES_NOT_EXIST 0x8000008AL

//
// MessageId: BWARN_DELETE_ACCOUNT_NOT_FOUND
//
// MessageText:
//
//  The Windows NT security account, %1\%2, was not found and could not be deleted.
//
#define BWARN_DELETE_ACCOUNT_NOT_FOUND   0x8000008BL

//
// MessageId: BWARN_DELETE_DOMAIN_NOT_FOUND
//
// MessageText:
//
//  The Windows NT security account, %1\%2, could not be deleted because the NT security domain controller could not be found.
//
#define BWARN_DELETE_DOMAIN_NOT_FOUND    0x8000008CL

//
// MessageId: BWARN_ASSOC_ACCOUNT_NOT_FOUND
//
// MessageText:
//
//  The Assoc-NT-Account value %2 specified for mailbox %1 could not be found.
//
#define BWARN_ASSOC_ACCOUNT_NOT_FOUND    0x8000008DL

//
// MessageId: BWARN_NO_OBJ_PERM_ADMIN_ACCOUNT
//
// MessageText:
//
//  Obj-Perm-Admin value %3 specified for %2 %1 was not found. This user could not be granted permissions administrator privileges on the %2.
//
#define BWARN_NO_OBJ_PERM_ADMIN_ACCOUNT  0x8000008EL

//
// MessageId: BWARN_NO_OBJ_ADMIN_ACCOUNT
//
// MessageText:
//
//  Obj-Admin value %3 specified for %2 %1 was not found. This user could not be granted administrator privileges on the %2.
//
#define BWARN_NO_OBJ_ADMIN_ACCOUNT       0x8000008FL

//
// MessageId: BWARN_NO_OBJ_USER_ACCOUNT
//
// MessageText:
//
//  Obj-User value %3 specified for %2 %1 was not found. This user will not have access to the %2.
//
#define BWARN_NO_OBJ_USER_ACCOUNT        0x80000090L

//
// MessageId: BWARN_NO_DEFAULT_ACCOUNT
//
// MessageText:
//
//  User access privileges could not be assigned to %2 %1. No user accounts were specified, and the default Windows NT account, %3, could not be found.
//
#define BWARN_NO_DEFAULT_ACCOUNT         0x80000091L

//
// MessageId: BWARN_COULD_NOT_CREATE_SD
//
// MessageText:
//
//  Microsoft Windows error %2 was encountered while attempting to create a Windows NT security descriptor for mailbox object %1.
//
#define BWARN_COULD_NOT_CREATE_SD        0x80000092L

//
// MessageId: DAPI_MISSING_EXCHANGE_CP
//
// MessageText:
//
//  Missing a code page (20261 or 1252) required for proper character translation when reading and writing objects in the directory.  Some characters may not map properly. Verify that these are installed on your system.
//
#define DAPI_MISSING_EXCHANGE_CP         0x40000093L

//
// MessageId: BWARN_RENAMED_OUTPUT_FILE
//
// MessageText:
//
//  File %1 already existed and was renamed to %2.
//
#define BWARN_RENAMED_OUTPUT_FILE        0x40000094L

//
// MessageId: BWARN_RENAMED_IMPORT_FILE
//
// MessageText:
//
//  The specified import file, %1, conflicts with a constructed output file and was renamed to %2.
//
#define BWARN_RENAMED_IMPORT_FILE        0x80000095L

//
// MessageId: BWARN_DEL_ATTR
//
// MessageText:
//
//  Entry %1 did not contain property %2 so the property could not be deleted.
//
#define BWARN_DEL_ATTR                   0x80000096L

//
// MessageId: BWARN_THREAD_FAILED
//
// MessageText:
//
//  Microsoft Windows error %1 occurred when attempting to create a processing thread.
//
#define BWARN_THREAD_FAILED              0x80000097L

//
// MessageId: BWARN_ATTRIBUTE_DUPLICATE
//
// MessageText:
//
//  %1 has been specified more than once in the attribute list. Only the first instance will be used when writing to the directory.
//
#define BWARN_ATTRIBUTE_DUPLICATE        0x80000098L

//
// MessageId: BWARN_ATTRIBUTE_READONLY
//
// MessageText:
//
//  The attribute %1 is read-only. Values specified for this attribute will be ignored when writing to the Directory.
//
#define BWARN_ATTRIBUTE_READONLY         0x80000099L

//
// MessageId: BWARN_ATTRIBUTE_NOT_IMPORTABLE
//
// MessageText:
//
//  The attribute %1 is not directly importable.
//
#define BWARN_ATTRIBUTE_NOT_IMPORTABLE   0xC000009AL

//
// MessageId: BWARN_NO_RAW_MODE_TEMPLATE
//
// MessageText:
//
//  Template objects do not apply when in raw mode.
//
#define BWARN_NO_RAW_MODE_TEMPLATE       0x8000009BL

//
// MessageId: BWARN_OVERSIZE_ATT_FILE
//
// MessageText:
//
//  The attribute value data length exceeded the Microsoft Excel limit of 255 characters. The data was written to file %1.
//
#define BWARN_OVERSIZE_ATT_FILE          0x8000009CL

//
// MessageId: DAPI_ERR_WRONG_SYNTAX
//
// MessageText:
//
//  The value type specified for attribute %1 is incorrect.
//
#define DAPI_ERR_WRONG_SYNTAX            0xC000009DL

//
// MessageId: DAPI_E_INVALID_CODEPAGE
//
// MessageText:
//
//  The specified code page has not been installed on the system.
//
#define DAPI_E_INVALID_CODEPAGE          0xC000009EL

//
// MessageId: DAPI_E_OBJECT_NOT_FOUND
//
// MessageText:
//
//  Unable to find object %1.
//
#define DAPI_E_OBJECT_NOT_FOUND          0xC000009FL

//
// MessageId: DAPI_E_NO_OBJECT
//
// MessageText:
//
//  No object specified.
//
#define DAPI_E_NO_OBJECT                 0xC00000A0L

//
// MessageId: DAPI_E_CREATE_FILE
//
// MessageText:
//
//  Unable to create the export file %1. %2
//
#define DAPI_E_CREATE_FILE               0xC00000A1L

//
// MessageId: DAPI_W_HIER_RECALC_FAILED
//
// MessageText:
//
//  Unable to recalculate the Address Book hierarchy after performing the %2 operation on the %1 container.
//
#define DAPI_W_HIER_RECALC_FAILED        0x800000A2L

//
// MessageId: DAPI_W_EXP_FILE_OVERWRITTEN
//
// MessageText:
//
//  The export file %1 already exists and is being overwritten.
//
#define DAPI_W_EXP_FILE_OVERWRITTEN      0x800000A3L

//
// MessageId: DAPI_W_NO_VALUES
//
// MessageText:
//
//  No values specified for DAPIWrite.
//
#define DAPI_W_NO_VALUES                 0x800000A4L

//
// MessageId: DAPI_W_RDN_MAPPED
//
// MessageText:
//
//  One or more characters specified for the %2 are not valid.  The object name was changed from %1 to %3.
//
#define DAPI_W_RDN_MAPPED                0x800000A5L

//
// MessageId: DAPI_W_IMP_VALUE_MAPPED
//
// MessageText:
//
//  One or more characters specified for the %2 attribute of object %1 are not valid.  The value was changed from %3 to %4.
//
#define DAPI_W_IMP_VALUE_MAPPED          0x800000A6L

//
// MessageId: DAPI_W_EXP_VALUE_MAPPED
//
// MessageText:
//
//  One or more characters in the %2 attribute of %1 could not be mapped to the export code page. The system default character was used.
//
#define DAPI_W_EXP_VALUE_MAPPED          0x800000A7L

//
// MessageId: DAPI_W_BACKSLASH_DROPPED
//
// MessageText:
//
//  One or more backslash characters specified in the %2 attribute of %1 were mapped out on import. The value was changed from %3 to %4. The backslash character may be specified by doubling it (i.e., \\).
//
#define DAPI_W_BACKSLASH_DROPPED         0x800000A8L

//
// MessageId: DAPI_W_STRING_TOO_LONG
//
// MessageText:
//
//  A value specified for the %2 attribute of object %1 exceeded the limit of %3 %4.  The string was truncated to fit.
//
#define DAPI_W_STRING_TOO_LONG           0x800000A9L

//
// MessageId: DAPI_W_NO_DL_OWNER_ACCOUNT
//
// MessageText:
//
//  There is no primary Windows NT Account associated with the object specified as the owner of distribution list %1.
//
#define DAPI_W_NO_DL_OWNER_ACCOUNT       0x800000AAL

//
// MessageId: DAPI_W_SERVER_SYNCH_IN_PROGRESS
//
// MessageText:
//
//  The Microsoft Exchange Directory server, %1, is currently synchronizing with other servers in the site.  Write operations are not recommended at this time.
//
#define DAPI_W_SERVER_SYNCH_IN_PROGRESS  0x800000ABL

//
// MessageId: BERR_SIGNATURE_MISMATCH
//
// MessageText:
//
//  A version mismatch was detected between DAPI.DLL and the program. %1 cannot proceed.
//
#define BERR_SIGNATURE_MISMATCH          0xC00000ACL

//
// MessageId: BERR_INVALID_BASEPOINT
//
// MessageText:
//
//  The object name specified for basepoint %1 is not valid.
//
#define BERR_INVALID_BASEPOINT           0xC00000ADL

//
// MessageId: BERR_NO_SUCH_BASEPOINT
//
// MessageText:
//
//  The basepoint object %1 does not exist in the directory.
//
#define BERR_NO_SUCH_BASEPOINT           0xC00000AEL

//
// MessageId: BERR_INVALID_CONTAINER
//
// MessageText:
//
//  The object name specified for the container %1 is not valid.
//
#define BERR_INVALID_CONTAINER           0xC00000AFL

//
// MessageId: BERR_NO_SUCH_CONTAINER
//
// MessageText:
//
//  The specified container %1 does not exist in the directory.
//
#define BERR_NO_SUCH_CONTAINER           0xC00000B0L

//
// MessageId: BERR_DEFAULT_USER_ERROR
//
// MessageText:
//
//  The object name specified for the create object template %1 is not valid.
//
#define BERR_DEFAULT_USER_ERROR          0xC00000B1L

//
// MessageId: BERR_NO_WORKSPACE
//
// MessageText:
//
//  No object management (OM) workspace is available.
//
#define BERR_NO_WORKSPACE                0xC00000B2L

//
// MessageId: BERR_DUA_UNAVAILABLE
//
// MessageText:
//
//  Unable to initialize directory user agent (DUA) workspace.
//
#define BERR_DUA_UNAVAILABLE             0xC00000B3L

//
// MessageId: BERR_NEGOTIATE_FAILURE
//
// MessageText:
//
//  Could not negotiate directory user agent (DUA) features. %1
//
#define BERR_NEGOTIATE_FAILURE           0xC00000B4L

//
// MessageId: BERR_DSA_BIND_FAILURE
//
// MessageText:
//
//  Could not bind to the Microsoft Exchange Directory server %2.  %1
//
#define BERR_DSA_BIND_FAILURE            0xC00000B5L

//
// MessageId: BERR_DEFAULT_BIND_FAILURE
//
// MessageText:
//
//  No Microsoft Exchange Directory server is available.
//
#define BERR_DEFAULT_BIND_FAILURE        0xC00000B6L

//
// MessageId: BERR_ILLEGAL_DSANAME
//
// MessageText:
//
//  The Microsoft Exchange Directory server Name, %1, is illegal.
//
#define BERR_ILLEGAL_DSANAME             0xC00000B7L

//
// MessageId: BERR_SERVER_NOT_WRITABLE
//
// MessageText:
//
//  The Microsoft Exchange Directory server, %1, is not currently writable.  Try the operation again later.
//
#define BERR_SERVER_NOT_WRITABLE         0xC00000B8L

//
// MessageId: BERR_DSA_UNBIND_FAILURE
//
// MessageText:
//
//  Could not unbind from the directory service. %1
//
#define BERR_DSA_UNBIND_FAILURE          0xC00000B9L

//
// MessageId: BERR_SCHEMA_LOAD_FAILED
//
// MessageText:
//
//  An initialization failure occurred. The directory schema could not be read from messaging site %1.
//
#define BERR_SCHEMA_LOAD_FAILED          0xC00000BAL

//
// MessageId: BERR_XOM_SCHEMA_READ
//
// MessageText:
//
//  An initialization failure occurred. Object management (OM) error %1 was encountered while attempting to read the schema.
//
#define BERR_XOM_SCHEMA_READ             0xC00000BBL

//
// MessageId: BERR_XDS_SCHEMA_READ
//
// MessageText:
//
//  An initialization failure occurred while attempting to read the schema.  %1
//
#define BERR_XDS_SCHEMA_READ             0xC00000BCL

//
// MessageId: BERR_ATTRIBUTES_UNAVAILABLE
//
// MessageText:
//
//  An initialization failure occurred. Unable to read attributes from the schema.
//
#define BERR_ATTRIBUTES_UNAVAILABLE      0xC00000BDL

//
// MessageId: BERR_ATTRIBUTE_PROPERTY_UNAVAILABLE
//
// MessageText:
//
//  An initialization failure occurred. The attribute-schema object %1 does not contain the %2 attribute.
//
#define BERR_ATTRIBUTE_PROPERTY_UNAVAILABLE 0xC00000BEL

//
// MessageId: BERR_INIT_ATTR_UNKNOWN
//
// MessageText:
//
//  Attribute %1 is not defined in the directory schema and so is not supported for import.
//
#define BERR_INIT_ATTR_UNKNOWN           0xC00000BFL

//
// MessageId: BERR_UNREC_OBJECT_TYPE
//
// MessageText:
//
//  An internal error occurred. The directory schema contained an unrecognized type value. Attribute %1.
//
#define BERR_UNREC_OBJECT_TYPE           0xC00000C0L

//
// MessageId: BERR_OBJECT_TYPE_NOT_IMPLEMENTED
//
// MessageText:
//
//  Attribute %1 cannot be processed because its object type is not yet implemented.
//
#define BERR_OBJECT_TYPE_NOT_IMPLEMENTED 0xC00000C1L

//
// MessageId: BERR_UNREC_ATTR_SYNTAX
//
// MessageText:
//
//  An internal error occurred. The directory schema contains an unrecognized syntax value. Attribute %1.
//
#define BERR_UNREC_ATTR_SYNTAX           0xC00000C2L

//
// MessageId: BERR_ATTR_SYNTAX_NOT_IMPLEMENTED
//
// MessageText:
//
//  An internal error occurred. Attribute %1 cannot be processed because its object management (OM) syntax is not yet implemented.
//
#define BERR_ATTR_SYNTAX_NOT_IMPLEMENTED 0xC00000C3L

//
// MessageId: BERR_VALUE_SYNTAX_NOT_IMPLEMENTED
//
// MessageText:
//
//  Unable to convert the attribute value to a string because syntax %1 is not yet implemented.
//
#define BERR_VALUE_SYNTAX_NOT_IMPLEMENTED 0xC00000C4L

//
// MessageId: BERR_UNREC_VALUE_SYNTAX
//
// MessageText:
//
//  Unable to convert the attribute value to a string because syntax %1 is not recognized.
//
#define BERR_UNREC_VALUE_SYNTAX          0xC00000C5L

//
// MessageId: BERR_VALUE_OBJECT_TYPE_NOT_IMPLEMENTED
//
// MessageText:
//
//  Unable to convert the attribute value to a string because object type %1 is not yet implemented.
//
#define BERR_VALUE_OBJECT_TYPE_NOT_IMPLEMENTED 0xC00000C6L

//
// MessageId: BERR_UNREC_VALUE_OBJECT_TYPE
//
// MessageText:
//
//  Unable to convert the attribute value to a string because the object type is not recognized.
//
#define BERR_UNREC_VALUE_OBJECT_TYPE     0xC00000C7L

//
// MessageId: BERR_INIT_CLASS_UNKNOWN
//
// MessageText:
//
//  Unable to initialize because class ID %1 was not found in the descriptors read from the schema.
//
#define BERR_INIT_CLASS_UNKNOWN          0xC00000C8L

//
// MessageId: BERR_CLASSES_UNAVAILABLE
//
// MessageText:
//
//  Unable to initialize because the object class descriptions could not be read from the schema.
//
#define BERR_CLASSES_UNAVAILABLE         0xC00000C9L

//
// MessageId: BERR_CLASS_PROPERTY_UNAVAILABLE
//
// MessageText:
//
//  Unable to initialize because the class schema object %1 does not contain the %2 attribute.
//
#define BERR_CLASS_PROPERTY_UNAVAILABLE  0xC00000CAL

//
// MessageId: BERR_CLASS_ATTRIBUTE_MISSING
//
// MessageText:
//
//  Unable to initialize because at least one of the schema attributes specified in the %2 attribute of the class schema object %1 is not defined.
//
#define BERR_CLASS_ATTRIBUTE_MISSING     0xC00000CBL

//
// MessageId: BERR_NO_IMPORT_FILE
//
// MessageText:
//
//  There is no file specified for directory import.
//
#define BERR_NO_IMPORT_FILE              0xC00000CCL

//
// MessageId: BERR_NO_EXPORT_FILE
//
// MessageText:
//
//  There is no file specified for the export operation.
//
#define BERR_NO_EXPORT_FILE              0xC00000CDL

//
// MessageId: BERR_INVALID_IMPORT_FILE
//
// MessageText:
//
//  Unable to open import file %1. %2
//
#define BERR_INVALID_IMPORT_FILE         0xC00000CEL

//
// MessageId: BERR_INVALID_EXPORT_FILE
//
// MessageText:
//
//  Unable to export to file %1. %2
//
#define BERR_INVALID_EXPORT_FILE         0xC00000CFL

//
// MessageId: BERR_FILE_IS_UNICODE
//
// MessageText:
//
//  The specified file is Unicode. Code page override is not valid.
//
#define BERR_FILE_IS_UNICODE             0xC00000D0L

//
// MessageId: BERR_FILE_IS_NOT_UNICODE
//
// MessageText:
//
//  The specified file is not Unicode.
//
#define BERR_FILE_IS_NOT_UNICODE         0xC00000D1L

//
// MessageId: BERR_INVALID_FILENAME
//
// MessageText:
//
//  The filename %1 is not valid.
//
#define BERR_INVALID_FILENAME            0xC00000D2L

//
// MessageId: BERR_CANT_RENAME_IMP_FILE
//
// MessageText:
//
//  The specified import file %1 conflicts with a constructed output filename, but could not be renamed for import.
//
#define BERR_CANT_RENAME_IMP_FILE        0xC00000D3L

//
// MessageId: BERR_CANT_RENAME_EXPORT_FILE
//
// MessageText:
//
//  The export file %1 could not be accessed. The file may be opened by another application or the path may not be valid.
//
#define BERR_CANT_RENAME_EXPORT_FILE     0xC00000D4L

//
// MessageId: BERR_FILE_IS_DIRECTORY
//
// MessageText:
//
//  The specified file %1 names a directory.
//
#define BERR_FILE_IS_DIRECTORY           0xC00000D5L

//
// MessageId: BERR_FILE_IS_READONLY
//
// MessageText:
//
//  Unable to create output file %1. The file exists and is read only.
//
#define BERR_FILE_IS_READONLY            0xC00000D6L

//
// MessageId: BERR_CREATE_LOG_FAILED
//
// MessageText:
//
//  Unable to create the directory import error log file %1.
//
#define BERR_CREATE_LOG_FAILED           0xC00000D7L

//
// MessageId: BERR_CREATE_PSW_FAILED
//
// MessageText:
//
//  Unable to create the directory import password file %1.
//
#define BERR_CREATE_PSW_FAILED           0xC00000D8L

//
// MessageId: BERR_WRITE_PSW_ERROR
//
// MessageText:
//
//  The system reported the following error while attempting to write to the created account file %1. %n%2
//
#define BERR_WRITE_PSW_ERROR             0xC00000D9L

//
// MessageId: BERR_MISSING_OBJ_CLASS
//
// MessageText:
//
//  The Obj-Class value must be specified on each import line.
//
#define BERR_MISSING_OBJ_CLASS           0xC00000DAL

//
// MessageId: BERR_RDN_MISSING
//
// MessageText:
//
//  The %1 attribute is required to identify %2 objects.
//
#define BERR_RDN_MISSING                 0xC00000DBL

//
// MessageId: BERR_MISQUOTED_IMPORT_LINE
//
// MessageText:
//
//  An incorrect use of the quotation mark delimiter was encountered on the import line.
//
#define BERR_MISQUOTED_IMPORT_LINE       0xC00000DCL

//
// MessageId: BERR_ILLEGAL_MODE
//
// MessageText:
//
//  %1 is not recognized as a legal import mode.
//
#define BERR_ILLEGAL_MODE                0xC00000DDL

//
// MessageId: BERR_MODE_COLUMN
//
// MessageText:
//
//  %1 can be specified only in the second column.
//
#define BERR_MODE_COLUMN                 0xC00000DEL

//
// MessageId: BERR_OUT_OF_MEMORY
//
// MessageText:
//
//  Out of memory error encountered.
//
#define BERR_OUT_OF_MEMORY               0xC00000DFL

//
// MessageId: BERR_FILE_READ_FAILURE
//
// MessageText:
//
//  The following error occurred while attempting to read from the import file:  %1
//
#define BERR_FILE_READ_FAILURE           0xC00000E0L

//
// MessageId: BERR_MISSING_COMMON_NAME_HEADER
//
// MessageText:
//
//  The import file %1 is not valid because the Common Name column is missing.
//
#define BERR_MISSING_COMMON_NAME_HEADER  0xC00000E1L

//
// MessageId: BERR_MISSING_OBJ_CLASS_HEADER
//
// MessageText:
//
//  The import file %1 is not valid. The first column header must be Obj-Class.  The first column header found was %2. Confirm that the column delimiter, '%3', is correct for the file.
//
#define BERR_MISSING_OBJ_CLASS_HEADER    0xC00000E2L

//
// MessageId: BERR_HEADER_MISQUOTED
//
// MessageText:
//
//  Import file %1 is not valid because quotation mark delimiters were used improperly in the header line.
//
#define BERR_HEADER_MISQUOTED            0xC00000E3L

//
// MessageId: BERR_INVALID_OBJ_CLASS
//
// MessageText:
//
//  %1 is not recognized as a legal Obj-Class value.
//
#define BERR_INVALID_OBJ_CLASS           0xC00000E4L

//
// MessageId: BERR_PROXY_INIT_ERROR
//
// MessageText:
//
//  The following error was reported while trying to initialize the e-mail address generating subsystem. %1
//
#define BERR_PROXY_INIT_ERROR            0xC00000E5L

//
// MessageId: BERR_NO_PROXY_SEPARATOR
//
// MessageText:
//
//  Import object %1 was not processed because the e-mail address type separator, :, was not found in the specified %3 value: %2.
//
#define BERR_NO_PROXY_SEPARATOR          0xC00000E6L

//
// MessageId: BERR_NO_PROXY_PREFIX
//
// MessageText:
//
//  Import object %1 was not processed because no e-mail address type was specified for %3 string: %2
//
#define BERR_NO_PROXY_PREFIX             0xC00000E7L

//
// MessageId: BERR_ILLEGAL_PROXY_PREFIX_LEN
//
// MessageText:
//
//  Unable to process import object %1. The e-mail address type must be eight characters or less. %2
//
#define BERR_ILLEGAL_PROXY_PREFIX_LEN    0xC00000E8L

//
// MessageId: BERR_DUPLICATE_PROXY
//
// MessageText:
//
//  Unable to process object %1 because the specified e-mail address %2 has the same type as one or more other e-mail addresses specified for the same object.
//
#define BERR_DUPLICATE_PROXY             0xC00000E9L

//
// MessageId: BERR_PROXY_GENERAL_FAILURE
//
// MessageText:
//
//  Unable to process object %1 because the Microsoft Exchange System Attendant encountered errors while attempting to generate or validate e-mail addresses. For more information, see the event log on server %2.
//
#define BERR_PROXY_GENERAL_FAILURE       0xC00000EAL

//
// MessageId: BERR_PROXY_TARGET_INVALID
//
// MessageText:
//
//  Unable to process custom recipient %1 because the target address is not valid. %2
//
#define BERR_PROXY_TARGET_INVALID        0xC00000EBL

//
// MessageId: BERR_PROXY_TARGET_NOT_UNIQUE
//
// MessageText:
//
//  Unable to process custom recipient %1 because target address %2 has already been assigned to Address Book entry %3.
//
#define BERR_PROXY_TARGET_NOT_UNIQUE     0xC00000ECL

//
// MessageId: BERR_PROXY_INVALID
//
// MessageText:
//
//  The e-mail address specified for import object %1 is not valid. %2
//
#define BERR_PROXY_INVALID               0xC00000EDL

//
// MessageId: BERR_PROXY_NOT_UNIQUE
//
// MessageText:
//
//  The e-mail address specified for import object %1 is not unique. %2 has already been assigned to Address Book entry %3.
//
#define BERR_PROXY_NOT_UNIQUE            0xC00000EEL

//
// MessageId: BERR_PROXY_GENERIC
//
// MessageText:
//
//  The Microsoft Exchange System Attendant reported %3 when attempting to generate or validate e-mail addresses for %1.  For more information, see the event log on server %2 for details.
//
#define BERR_PROXY_GENERIC               0xC00000EFL

//
// MessageId: BERR_PROXY_SYSTEM
//
// MessageText:
//
//  The following error was encountered when attempting to generate or validate e-mail addresses for %1. %2
//
#define BERR_PROXY_SYSTEM                0xC00000F0L

//
// MessageId: BERR_CREATE_DEL_ERROR
//
// MessageText:
//
//  Object %1 was not built because the string ~DEL may only be used with existing objects.
//
#define BERR_CREATE_DEL_ERROR            0xC00000F1L

//
// MessageId: BERR_OM_ERROR
//
// MessageText:
//
//  Object management (OM) error %1 was reported.
//
#define BERR_OM_ERROR                    0xC00000F2L

//
// MessageId: BERR_ATTRIBUTE_OR_VALUE_EXISTS
//
// MessageText:
//
//  A duplicate value was specified for attribute %2 on object %1.
//
#define BERR_ATTRIBUTE_OR_VALUE_EXISTS   0xC00000F3L

//
// MessageId: BERR_CONSTRAINT_VIOLATION
//
// MessageText:
//
//  Unable to complete the operation on object %1 because a value specified for attribute %2 is out of range.
//
#define BERR_CONSTRAINT_VIOLATION        0xC00000F4L

//
// MessageId: BERR_INVALID_SYNTAX
//
// MessageText:
//
//  Unable to complete the operation on object %1 because the syntax specified for a value for attribute %2 is not valid.
//
#define BERR_INVALID_SYNTAX              0xC00000F5L

//
// MessageId: BERR_NO_SUCH_ATTRIBUTE_OR_VALUE
//
// MessageText:
//
//  The attribute %2 is not defined on object %1 and could not be read.
//
#define BERR_NO_SUCH_ATTRIBUTE_OR_VALUE  0xC00000F6L

//
// MessageId: BERR_ACCNT_LM_INIT_ERROR
//
// MessageText:
//
//  Unable to create Windows NT accounts because network error %1 occurred while initializing.
//
#define BERR_ACCNT_LM_INIT_ERROR         0xC00000F7L

//
// MessageId: BERR_LM_INIT_ERROR
//
// MessageText:
//
//  Could not initialize -- Net error %1 reported during initialization.
//
#define BERR_LM_INIT_ERROR               0xC00000F8L

//
// MessageId: BERR_LM_ERROR
//
// MessageText:
//
//  Network error %1 occurred.
//
#define BERR_LM_ERROR                    0xC00000F9L

//
// MessageId: BERR_ACCNT_PDC_GONE
//
// MessageText:
//
//  The primary domain controller for domain %1 is no longer available.
//
#define BERR_ACCNT_PDC_GONE              0xC00000FAL

//
// MessageId: BERR_ACCNT_LM_ERROR
//
// MessageText:
//
//  Unable to create a Windows NT account for user %1. %2
//
#define BERR_ACCNT_LM_ERROR              0xC00000FBL

//
// MessageId: BERR_ACCNT_WIN_ERROR
//
// MessageText:
//
//  Unable to create a Windows NT account for user %1. %2
//
#define BERR_ACCNT_WIN_ERROR             0xC00000FCL

//
// MessageId: BERR_ACCNT_TOO_LONG
//
// MessageText:
//
//  Unable to create a Windows NT account %2 for mailbox %1 because Windows NT account names cannot exceed 20 characters.
//
#define BERR_ACCNT_TOO_LONG              0xC00000FDL

//
// MessageId: BERR_ILLEGAL_ACCNT_CHARS
//
// MessageText:
//
//  Unable to create Windows NT account %2 for mailbox %1 because it contains the illegal character(s) %3.
//
#define BERR_ILLEGAL_ACCNT_CHARS         0xC00000FEL

//
// MessageId: BERR_LM_DELETE_ACCOUNT
//
// MessageText:
//
//  A network error occurred when attempting to delete Windows NT security account %1.
//
#define BERR_LM_DELETE_ACCOUNT           0xC00000FFL

//
// MessageId: BERR_WIN_DELETE_ACCOUNT
//
// MessageText:
//
//  Unable to delete the Windows NT account for user %1. %2.
//
#define BERR_WIN_DELETE_ACCOUNT          0xC0000100L

//
// MessageId: BERR_DEL_ACCOUNT_LOOKUP_FAILED
//
// MessageText:
//
//  An error occurred while attempting to lookup the Assoc-NT-Account value for object %1. Neither the security account nor the object was deleted.
//
#define BERR_DEL_ACCOUNT_LOOKUP_FAILED   0xC0000101L

//
// MessageId: BERR_ACCOUNT_LOOKUP_FAILED
//
// MessageText:
//
//  An error occurred while attempting to lookup the Assoc-NT-Account value for object %1.
//
#define BERR_ACCOUNT_LOOKUP_FAILED       0x80000102L

//
// MessageId: BERR_ACCNT_WIN_INIT_ERROR
//
// MessageText:
//
//  Unable to create Windows NT accounts because Windows reports error %1.
//
#define BERR_ACCNT_WIN_INIT_ERROR        0xC0000103L

//
// MessageId: BERR_WIN_INIT_ERROR
//
// MessageText:
//
//  Unable to initialize because Windows reports error %1.
//
#define BERR_WIN_INIT_ERROR              0xC0000104L

//
// MessageId: BERR_REGISTER_ERROR
//
// MessageText:
//
//  Unable to initialize because Windows reports error %1 occurred while attempting to register with the system.
//
#define BERR_REGISTER_ERROR              0xC0000105L

//
// MessageId: BERR_WIN_ERROR
//
// MessageText:
//
//  Windows reports error %1.
//
#define BERR_WIN_ERROR                   0xC0000106L

//
// MessageId: BERR_NO_ATTRIBUTES_SPECIFIED
//
// MessageText:
//
//  No attributes are specified.
//
#define BERR_NO_ATTRIBUTES_SPECIFIED     0xC0000107L

//
// MessageId: BERR_ATTRIBUTE_UNKNOWN
//
// MessageText:
//
//  The attribute %1 is unknown.
//
#define BERR_ATTRIBUTE_UNKNOWN           0xC0000108L

//
// MessageId: BERR_ATTRIBUTE_NOT_IMPORTABLE
//
// MessageText:
//
//  Attribute %1 cannot be imported.
//
#define BERR_ATTRIBUTE_NOT_IMPORTABLE    0xC0000109L

//
// MessageId: BERR_CANT_DELETE_REQUIRED_ATTRIBUTE
//
// MessageText:
//
//  Unable to process object %1. The required attribute %2 may not be deleted.
//
#define BERR_CANT_DELETE_REQUIRED_ATTRIBUTE 0xC000010AL

//
// MessageId: BERR_CANT_DELETE_ATTRIBUTE
//
// MessageText:
//
//  Unable to process object %1. Attribute %2 may not be deleted.
//
#define BERR_CANT_DELETE_ATTRIBUTE       0xC000010BL

//
// MessageId: BERR_DELETE_KEY_MUST_BE_SINGLE
//
// MessageText:
//
//  Unable to process object %1. ~DEL may not be specified with other values for multi-valued attribute %2.
//
#define BERR_DELETE_KEY_MUST_BE_SINGLE   0xC000010CL

//
// MessageId: BERR_COULD_NOT_EMPTY_MAILBOX
//
// MessageText:
//
//  Error %2 occurred while attempting to throw away %1's mail.
//
#define BERR_COULD_NOT_EMPTY_MAILBOX     0xC000010DL

//
// MessageId: BERR_MALFORMED_OCTET_STRING
//
// MessageText:
//
//  Unable to process object %1 because the octet string specified for attribute %2 is incorrect.
//
#define BERR_MALFORMED_OCTET_STRING      0xC000010EL

//
// MessageId: BERR_ILLEGAL_CHAR_IN_NUMBER
//
// MessageText:
//
//  Unable to process object %1 because the character specified in value for attribute %2 is not valid.
//
#define BERR_ILLEGAL_CHAR_IN_NUMBER      0xC000010FL

//
// MessageId: BERR_ILLEGAL_CHAR_IN_HEX_NUMBER
//
// MessageText:
//
//  Unable to process object %1 because the character specified in value for attribute %2 is not valid.
//
#define BERR_ILLEGAL_CHAR_IN_HEX_NUMBER  0xC0000110L

//
// MessageId: BERR_CANNOT_BUILD_DN
//
// MessageText:
//
//  Could not build DN string from components:  BasePoint == %1, Container == %2, ObjName == %3.
//
#define BERR_CANNOT_BUILD_DN             0xC0000111L

//
// MessageId: BERR_MALFORMED_DN_STRING
//
// MessageText:
//
//  Unable to process object %1 because DN string %2 is not valid.
//
#define BERR_MALFORMED_DN_STRING         0xC0000112L

//
// MessageId: BERR_UNKNOWN_RDN
//
// MessageText:
//
//  Unable to process object %1 because RDN string %2 is not valid.
//
#define BERR_UNKNOWN_RDN                 0xC0000113L

//
// MessageId: BERR_BADLY_SPECIFIED_DN
//
// MessageText:
//
//  DN string %1 is not valid.
//
#define BERR_BADLY_SPECIFIED_DN          0xC0000114L

//
// MessageId: BERR_MALFORMED_DN_OBJECT
//
// MessageText:
//
//  The distinguished name (DN) object read from the directory information tree (DIT) is not valid.
//
#define BERR_MALFORMED_DN_OBJECT         0xC0000115L

//
// MessageId: BERR_ACCNT_PDC_DISAPPEARED
//
// MessageText:
//
//  Unable to create a Windows NT account for user %1. The primary domain controller for domain %2 is not responding.
//
#define BERR_ACCNT_PDC_DISAPPEARED       0xC0000116L

//
// MessageId: BERR_XOM_REVOKE_MEMBERSHIP
//
// MessageText:
//
//  Object management (OM) error %1 was encountered when attempting to remove object %2 from a distribution list.
//
#define BERR_XOM_REVOKE_MEMBERSHIP       0xC0000117L

//
// MessageId: BERR_XDS_ERROR
//
// MessageText:
//
//  The directory service reported the following error: %1
//
#define BERR_XDS_ERROR                   0xC0000118L

//
// MessageId: BERR_XDS_CREATE
//
// MessageText:
//
//  Could not create object %2 because the directory service reported the following error: %1
//
#define BERR_XDS_CREATE                  0xC0000119L

//
// MessageId: BERR_XDS_MODIFY
//
// MessageText:
//
//  Could not modify object %2 because the directory service reported the following error: %1
//
#define BERR_XDS_MODIFY                  0xC000011AL

//
// MessageId: BERR_XDS_REMOVE
//
// MessageText:
//
//  Could not remove object %2 because the directory service reported the following error: %1
//
#define BERR_XDS_REMOVE                  0xC000011BL

//
// MessageId: BERR_XDS_DL_MEMBERSHIP
//
// MessageText:
//
//  Could not modify the DL membership of object %2 because the directory service reported the following error:  %1
//
#define BERR_XDS_DL_MEMBERSHIP           0xC000011CL

//
// MessageId: BERR_OBJECT_MEMBERSHIP_ERROR
//
// MessageText:
//
//  Unable to add object %1 to distribution list %2.
//
#define BERR_OBJECT_MEMBERSHIP_ERROR     0xC000011DL

//
// MessageId: BERR_CREATE_PATH_NOT_FOUND
//
// MessageText:
//
//  Unable to create object %1 because one or more objects in the directory path %2 do not exist.
//
#define BERR_CREATE_PATH_NOT_FOUND       0xC000011EL

//
// MessageId: BERR_CREATE_TARGET_EXISTS
//
// MessageText:
//
//  Unable to create object %1 because it already exists.
//
#define BERR_CREATE_TARGET_EXISTS        0xC000011FL

//
// MessageId: BERR_MOD_TARGET_NOT_FOUND
//
// MessageText:
//
//  Unable to modify object %1 because it could not be found.
//
#define BERR_MOD_TARGET_NOT_FOUND        0xC0000120L

//
// MessageId: BERR_MOD_CLASS_MISMATCH
//
// MessageText:
//
//  Entry %1 could not be modified as a %2 because it already exists as a %3 object.
//
#define BERR_MOD_CLASS_MISMATCH          0xC0000121L

//
// MessageId: BERR_DEL_CLASS_MISMATCH
//
// MessageText:
//
//  Unable to delete the %3 %1 because the entry already exists as a %2 in the directory.
//
#define BERR_DEL_CLASS_MISMATCH          0xC0000122L

//
// MessageId: BERR_INCORRECT_FIELD_COUNT
//
// MessageText:
//
//  Unable to process object %1 because the import line must contain the same number of fields as the header line. %2 were expected. %3 were found.
//
#define BERR_INCORRECT_FIELD_COUNT       0xC0000123L

//
// MessageId: BERR_MISSING_REQUIRED_ATTRIBUTE
//
// MessageText:
//
//  Unable to create %3 %1 because the required %2 attribute was not specified.
//
#define BERR_MISSING_REQUIRED_ATTRIBUTE  0xC0000124L

//
// MessageId: BERR_ONLY_SINGLE_CONTAINER
//
// MessageText:
//
//  Only a single container can be specified for the import object %1.
//
#define BERR_ONLY_SINGLE_CONTAINER       0xC0000125L

//
// MessageId: BERR_CANNOT_LOG_ERROR
//
// MessageText:
//
//  The directory import encountered Windows Error %2!lu! when attempting to record the following message in the system event log: %1
//
#define BERR_CANNOT_LOG_ERROR            0xC0000126L

//
// MessageId: BERR_INCLUDE_FAIL
//
// MessageText:
//
//  Unable to open or read the attribute value include file %1.
//
#define BERR_INCLUDE_FAIL                0xC0000127L

//
// MessageId: BERR_BAD_FILE_PTR
//
// MessageText:
//
//  The attribute value file pointer %1 was not specified correctly.
//
#define BERR_BAD_FILE_PTR                0xC0000128L

//
// MessageId: BERR_HOME_SERVER_UNKNOWN
//
// MessageText:
//
//  Unable to process object %1 because the specified home server %2 does not exist.
//
#define BERR_HOME_SERVER_UNKNOWN         0xC0000129L

//
// MessageId: BERR_HOME_SERVER_NO_MTA
//
// MessageText:
//
//  Unable to process object %1 because there is no Microsoft Exchange MTA installed on the specified home server %2.
//
#define BERR_HOME_SERVER_NO_MTA          0xC000012AL

//
// MessageId: BERR_HOME_SERVER_NO_PRIVATE_STORE
//
// MessageText:
//
//  Unable to process object %1 because there is no Microsoft Exchange private information store installed on the specified home server %2.
//
#define BERR_HOME_SERVER_NO_PRIVATE_STORE 0xC000012BL

// -------------------     messages for BEXPORT     -----------------------
//
// MessageId: BEXPORT_WRITE_ERROR
//
// MessageText:
//
//  The directory export was stopped because the following error occurred when attempting to write an object description to the file: %n%1
//
#define BEXPORT_WRITE_ERROR              0xC000012CL

//
// MessageId: BEXPORT_UNKNOWN_CLASS
//
// MessageText:
//
//  The class %1 is not known and could not be exported.
//
#define BEXPORT_UNKNOWN_CLASS            0xC000012DL

//
// MessageId: BEXPORT_NOSEARCHINFO_WARN
//
// MessageText:
//
//  No entries were found for the specified object class %1.
//
#define BEXPORT_NOSEARCHINFO_WARN        0x8000012EL

// -------------------     messages for NTEXPORT     -----------------------
//
// MessageId: NTEXPORT_DC_NOT_FOUND
//
// MessageText:
//
//  The domain controller could not be found for domain %1.
//
#define NTEXPORT_DC_NOT_FOUND            0xC000012FL

//
// MessageId: NTEXPORT_USER_ENUM_ERROR
//
// MessageText:
//
//  The following error occurred when attempting to read Windows NT user accounts from server %1. %2
//
#define NTEXPORT_USER_ENUM_ERROR         0xC0000130L

//
// MessageId: NTEXPORT_SERVER_NOT_FOUND
//
// MessageText:
//
//  NTExport could not find specified server, %1.
//
#define NTEXPORT_SERVER_NOT_FOUND        0xC0000131L

//
// MessageId: NETEXPORT_WRITE_ERROR
//
// MessageText:
//
//  The user extraction was halted because the following error occurred when attempting to write a user account description to the file:%n  %1
//
#define NETEXPORT_WRITE_ERROR            0xC0000132L

// -------------------     messages for NWExport     -----------------------
//
// MessageId: NWEXPORT_NWDLL_LOAD_FAILED
//
// MessageText:
//
//  Unable to load the Netware DLL %1.
//
#define NWEXPORT_NWDLL_LOAD_FAILED       0xC0000133L

//
// MessageId: NWEXPORT_LOGIN_FAILED
//
// MessageText:
//
//  NWExport could not log user %2 onto the file server %1.
//
#define NWEXPORT_LOGIN_FAILED            0xC0000134L

//
// MessageId: NWEXPORT_ATTACH_FAILED
//
// MessageText:
//
//  NWExport encountered an error attaching to the file server %1.
//
#define NWEXPORT_ATTACH_FAILED           0xC0000135L

//
// MessageId: NWEXPORT_LOGOUT_FAILED
//
// MessageText:
//
//  NWExport encountered an error logging out from the file server.
//
#define NWEXPORT_LOGOUT_FAILED           0xC0000136L

//
// MessageId: NWEXPORT_DETACHED_FAILED
//
// MessageText:
//
//  NWExport encountered an error detaching from the file server.
//
#define NWEXPORT_DETACHED_FAILED         0xC0000137L

//
// MessageId: NWEXPORT_NO_USER
//
// MessageText:
//
//  NetWare user extract could not continue because no user was specified for log on to the file server.
//
#define NWEXPORT_NO_USER                 0xC0000138L

// MessageIDs added with Exchange 4.0a
//
// MessageId: DAPI_E_ANR_MULTIPLE_MATCH
//
// MessageText:
//
//  More than one object was found matching the specified search name %1.
//
#define DAPI_E_ANR_MULTIPLE_MATCH        0xC0001000L

//
// MessageId: DAPI_E_ANR_NO_MATCH
//
// MessageText:
//
//  No objects were found matching the specified search name %1.
//
#define DAPI_E_ANR_NO_MATCH              0xC0001001L

//
// MessageId: DAPI_E_MULTIPLE_MATCH_ON_ATT
//
// MessageText:
//
//  More than one object was found matching the alias %3 specified for the %4 attribute on %2 %1.
//
#define DAPI_E_MULTIPLE_MATCH_ON_ATT     0xC0001002L

//
// MessageId: DAPI_E_NO_MATCH_ON_ATT
//
// MessageText:
//
//  No objects were found matching the alias %3 specified for the %4 attribute on %2 %1.
//
#define DAPI_E_NO_MATCH_ON_ATT           0xC0001003L

// ----------------------------     Substitutions ----------------------------
// From this point on, all messages are substitutions for use in other messages
//
// MessageId: IDS_SPACE
//
// MessageText:
//
//  <space>%0
//
#define IDS_SPACE                        0x0000F000L

//
// MessageId: IDS_TAB
//
// MessageText:
//
//  <tab>%0
//
#define IDS_TAB                          0x0000F001L

//
// MessageId: IDS_CHARACTERS
//
// MessageText:
//
//  characters%0
//
#define IDS_CHARACTERS                   0x0000F002L

//
// MessageId: IDS_OCTETS
//
// MessageText:
//
//  octets%0
//
#define IDS_OCTETS                       0x0000F003L

// -------------------     substitutions for Proxy rrors     ----------------------
// Messages w/ ID in range from 0xf080-0xf0ff are assumed to be substitution strings
// used to fill the %3 position of the BERR_PROXY_GENERIC message

//
// MessageId: PROXY_SUBST_GENERAL_FAILURE
//
// MessageText:
//
//  GENERAL_FAILURE%0
//
#define PROXY_SUBST_GENERAL_FAILURE      0x4000F080L

//
// MessageId: PROXY_SUBST_FAILURES
//
// MessageText:
//
//  SOME_PROXIES_FAILED%0
//
#define PROXY_SUBST_FAILURES             0x4000F081L

//
// MessageId: PROXY_SUBST_TARGET_INVALID
//
// MessageText:
//
//  TARGET_ADDRESS_NOT_VALID%0
//
#define PROXY_SUBST_TARGET_INVALID       0x4000F082L

//
// MessageId: PROXY_SUBST_TARGET_NOT_UNIQUE
//
// MessageText:
//
//  TARGET_ADDRESS_NOT_UNIQUE%0
//
#define PROXY_SUBST_TARGET_NOT_UNIQUE    0x4000F083L

//
// MessageId: PROXY_SUBST_DLL_NOT_IMPLEMENTED
//
// MessageText:
//
//  DLL_NOT_IMPLEMENTED%0
//
#define PROXY_SUBST_DLL_NOT_IMPLEMENTED  0x4000F084L

//
// MessageId: PROXY_SUBST_OOM
//
// MessageText:
//
//  OUT_OF_MEMORY%0
//
#define PROXY_SUBST_OOM                  0x4000F085L

//
// MessageId: PROXY_SUBST_DLL_ERROR
//
// MessageText:
//
//  GENERAL_FAILURE%0
//
#define PROXY_SUBST_DLL_ERROR            0x4000F086L

//
// MessageId: PROXY_SUBST_DLL_PROTOCOL
//
// MessageText:
//
//  PROTOCOL_ERROR%0
//
#define PROXY_SUBST_DLL_PROTOCOL         0x4000F087L

//
// MessageId: PROXY_SUBST_SYNTAX
//
// MessageText:
//
//  SYNTAX_ERROR%0
//
#define PROXY_SUBST_SYNTAX               0x4000F088L

//
// MessageId: PROXY_SUBST_EOF
//
// MessageText:
//
//  END_OF_FILE%0
//
#define PROXY_SUBST_EOF                  0x4000F089L

//
// MessageId: PROXY_SUBST_SOFTWARE
//
// MessageText:
//
//  SOFTWARE_ERROR%0
//
#define PROXY_SUBST_SOFTWARE             0x4000F08AL

//
// MessageId: PROXY_SUBST_CONFIGURATION
//
// MessageText:
//
//  CONFIGURATION_ERROR%0
//
#define PROXY_SUBST_CONFIGURATION        0x4000F08BL

//
// MessageId: PROXY_SUBST_CONTENTION
//
// MessageText:
//
//  CONTENTION_ERROR%0
//
#define PROXY_SUBST_CONTENTION           0x4000F08CL

//
// MessageId: PROXY_SUBST_NOT_FOUND
//
// MessageText:
//
//  DLL_NOT_FOUND%0
//
#define PROXY_SUBST_NOT_FOUND            0x4000F08DL

//
// MessageId: PROXY_SUBST_
//
// MessageText:
//
//  OUT_OF_DISK_SPACE%0
//
#define PROXY_SUBST_                     0x4000F08EL

//
// MessageId: PROXY_SUBST_EXCEPTION
//
// MessageText:
//
//  EXCEPTION_ENCOUNTERED%0
//
#define PROXY_SUBST_EXCEPTION            0x4000F08FL

//
// MessageId: PROXY_SUBST_DEFAULT
//
// MessageText:
//
//  GENERAL_FAILURE%0
//
#define PROXY_SUBST_DEFAULT              0x4000F090L

//
// MessageId: PROXY_SUBST_INVALID
//
// MessageText:
//
//  PROXY_NOT_VALID%0
//
#define PROXY_SUBST_INVALID              0x4000F091L

//
// MessageId: PROXY_SUBST_NOT_UNIQUE
//
// MessageText:
//
//  PROXY_NOT_UNIQUE%0
//
#define PROXY_SUBST_NOT_UNIQUE           0x4000F092L

//
// MessageId: PROXY_SUBST_DUPLICATE
//
// MessageText:
//
//  DUPLICATE_PROXY_SPECIFIED%0
//
#define PROXY_SUBST_DUPLICATE            0x4000F093L

// -------------------     messages for OM Errors     ----------------------
// Messages w/ ID in range from 0xf100-0xf1ff are assumed to be OM problem descriptions
// used as substitutions into other event messages

//
// MessageId: XOM_ERRORS
//
// MessageText:
//
//  OM_ERRORS%0
//
#define XOM_ERRORS                       0x4000F100L

//
// MessageId: ENCODING_INVALID
//
// MessageText:
//
//  ENCODING_INVALID%0
//
#define ENCODING_INVALID                 0x4000F101L

//
// MessageId: FUNCTION_DECLINED
//
// MessageText:
//
//  FUNCTION_DECLINED%0
//
#define FUNCTION_DECLINED                0x4000F102L

//
// MessageId: FUNCTION_INTERRUPTED
//
// MessageText:
//
//  FUNCTION_INTERRUPTED%0
//
#define FUNCTION_INTERRUPTED             0x4000F103L

//
// MessageId: MEMORY_INSUFFICIENT
//
// MessageText:
//
//  MEMORY_INSUFFICIENT%0
//
#define MEMORY_INSUFFICIENT              0x4000F104L

//
// MessageId: NETWORK_ERROR
//
// MessageText:
//
//  NETWORK_ERROR%0
//
#define NETWORK_ERROR                    0x4000F105L

//
// MessageId: NO_SUCH_CLASS
//
// MessageText:
//
//  NO_SUCH_CLASS%0
//
#define NO_SUCH_CLASS                    0x4000F106L

//
// MessageId: NO_SUCH_EXCLUSION
//
// MessageText:
//
//  NO_SUCH_EXCLUSION%0
//
#define NO_SUCH_EXCLUSION                0x4000F107L

//
// MessageId: NO_SUCH_MODIFICATION
//
// MessageText:
//
//  NO_SUCH_MODIFICATION%0
//
#define NO_SUCH_MODIFICATION             0x4000F108L

//
// MessageId: NO_SUCH_RULES
//
// MessageText:
//
//  NO_SUCH_RULES%0
//
#define NO_SUCH_RULES                    0x4000F109L

//
// MessageId: NO_SUCH_SYNTAX
//
// MessageText:
//
//  NO_SUCH_SYNTAX%0
//
#define NO_SUCH_SYNTAX                   0x4000F10AL

//
// MessageId: NO_SUCH_TYPE
//
// MessageText:
//
//  NO_SUCH_TYPE%0
//
#define NO_SUCH_TYPE                     0x4000F10BL

//
// MessageId: NO_SUCH_WORKSPACE
//
// MessageText:
//
//  NO_SUCH_WORKSPACE%0
//
#define NO_SUCH_WORKSPACE                0x4000F10CL

//
// MessageId: NOT_AN_ENCODING
//
// MessageText:
//
//  NOT_AN_ENCODING%0
//
#define NOT_AN_ENCODING                  0x4000F10DL

//
// MessageId: NOT_CONCRETE
//
// MessageText:
//
//  NOT_CONCRETE%0
//
#define NOT_CONCRETE                     0x4000F10EL

//
// MessageId: NOT_PRESENT
//
// MessageText:
//
//  NOT_PRESENT%0
//
#define NOT_PRESENT                      0x4000F10FL

//
// MessageId: NOT_PRIVATE
//
// MessageText:
//
//  NOT_PRIVATE%0
//
#define NOT_PRIVATE                      0x4000F110L

//
// MessageId: NOT_THE_SERVICES
//
// MessageText:
//
//  NOT_THE_SERVICES%0
//
#define NOT_THE_SERVICES                 0x4000F111L

//
// MessageId: PERMANENT_ERROR
//
// MessageText:
//
//  PERMANENT_ERROR%0
//
#define PERMANENT_ERROR                  0x4000F112L

//
// MessageId: POINTER_INVALID
//
// MessageText:
//
//  POINTER_INVALID%0
//
#define POINTER_INVALID                  0x4000F113L

//
// MessageId: SYSTEM_ERROR
//
// MessageText:
//
//  SYSTEM_ERROR%0
//
#define SYSTEM_ERROR                     0x4000F114L

//
// MessageId: TEMPORARY_ERROR
//
// MessageText:
//
//  TEMPORARY_ERROR%0
//
#define TEMPORARY_ERROR                  0x4000F115L

//
// MessageId: TOO_MANY_VALUES
//
// MessageText:
//
//  TOO_MANY_VALUES%0
//
#define TOO_MANY_VALUES                  0x4000F116L

//
// MessageId: VALUES_NOT_ADJACENT
//
// MessageText:
//
//  VALUES_NOT_ADJACENT%0
//
#define VALUES_NOT_ADJACENT              0x4000F117L

//
// MessageId: WRONG_VALUE_LENGTH
//
// MessageText:
//
//  WRONG_VALUE_LENGTH%0
//
#define WRONG_VALUE_LENGTH               0x4000F118L

//
// MessageId: WRONG_VALUE_MAKEUP
//
// MessageText:
//
//  WRONG_VALUE_MAKEUP%0
//
#define WRONG_VALUE_MAKEUP               0x4000F119L

//
// MessageId: WRONG_VALUE_NUMBER
//
// MessageText:
//
//  WRONG_VALUE_NUMBER%0
//
#define WRONG_VALUE_NUMBER               0x4000F11AL

//
// MessageId: WRONG_VALUE_POSITION
//
// MessageText:
//
//  WRONG_VALUE_POSITION%0
//
#define WRONG_VALUE_POSITION             0x4000F11BL

//
// MessageId: WRONG_VALUE_SYNTAX
//
// MessageText:
//
//  WRONG_VALUE_SYNTAX%0
//
#define WRONG_VALUE_SYNTAX               0x4000F11CL

//
// MessageId: WRONG_VALUE_TYPE
//
// MessageText:
//
//  WRONG_VALUE_TYPE%0
//
#define WRONG_VALUE_TYPE                 0x4000F11DL

//
// MessageId: BEYOND_LAST_OM_ERROR
//
// MessageText:
//
//  one beyond the last XOM problem%0
//
#define BEYOND_LAST_OM_ERROR             0x4000F11EL

// -------------------     messages for DS errors     ----------------------
// Messages w/ ID in range from 0xf200-0xf2ff are assumed to be XDS problems

//
// MessageId: XDS_PROBLEMS
//
// MessageText:
//
//  DS_SUCCESS%0
//
#define XDS_PROBLEMS                     0x4000F200L

//
// MessageId: DS_PROBLEM_ADMIN_LIMIT_EXCEEDED
//
// MessageText:
//
//  The maximum number of administrative connections to the server has been exceeded. Try again later or connect to a different server.
//
#define DS_PROBLEM_ADMIN_LIMIT_EXCEEDED  0x4000F201L

//
// MessageId: DS_PROBLEM_AFFECTS_MULTIPLE_DSAS
//
// MessageText:
//
//  This change affects more than one directory.
//
#define DS_PROBLEM_AFFECTS_MULTIPLE_DSAS 0x4000F202L

//
// MessageId: DS_PROBLEM_ALIAS_DEREFERENCING_PROBLEM
//
// MessageText:
//
//  The object referenced by this alias is not available.
//
#define DS_PROBLEM_ALIAS_DEREFERENCING_PROBLEM 0x4000F203L

//
// MessageId: DS_PROBLEM_ALIAS_PROBLEM
//
// MessageText:
//
//  There is a problem with the object referenced by this alias.
//
#define DS_PROBLEM_ALIAS_PROBLEM         0x4000F204L

//
// MessageId: DS_PROBLEM_ATTRIBUTE_OR_VALUE_EXISTS
//
// MessageText:
//
//  An internal processing error has occurred: the attribute or value exists. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_ATTRIBUTE_OR_VALUE_EXISTS 0x4000F205L

//
// MessageId: DS_PROBLEM_BAD_ARGUMENT
//
// MessageText:
//
//  An internal processing error has occurred: invalid argument. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_BAD_ARGUMENT          0x4000F206L

//
// MessageId: DS_PROBLEM_BAD_CLASS
//
// MessageText:
//
//  An internal processing error has occurred: invalid object class. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_BAD_CLASS             0x4000F207L

//
// MessageId: DS_PROBLEM_BAD_CONTEXT
//
// MessageText:
//
//  An internal processing error has occurred: invalid context. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_BAD_CONTEXT           0x4000F208L

//
// MessageId: DS_PROBLEM_BAD_NAME
//
// MessageText:
//
//  An internal processing error has occurred: invalid name. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_BAD_NAME              0x4000F209L

//
// MessageId: DS_PROBLEM_BAD_SESSION
//
// MessageText:
//
//  An internal processing error has occurred: invalid session. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_BAD_SESSION           0x4000F20AL

//
// MessageId: DS_PROBLEM_BAD_WORKSPACE
//
// MessageText:
//
//  An internal processing error has occurred: invalid workspace. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_BAD_WORKSPACE         0x4000F20BL

//
// MessageId: DS_PROBLEM_BUSY
//
// MessageText:
//
//  The directory is busy. Wait a few minutes and try again.
//
#define DS_PROBLEM_BUSY                  0x4000F20CL

//
// MessageId: DS_PROBLEM_CANNOT_ABANDON
//
// MessageText:
//
//  An internal processing error has occurred: cannot abandon the operation. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_CANNOT_ABANDON        0x4000F20DL

//
// MessageId: DS_PROBLEM_CHAINING_REQUIRED
//
// MessageText:
//
//  You must make a connection to the Microsoft Exchange Server computer.
//
#define DS_PROBLEM_CHAINING_REQUIRED     0x4000F20EL

//
// MessageId: DS_PROBLEM_COMMUNICATIONS_PROBLEM
//
// MessageText:
//
//  The Microsoft Exchange Server computer does not respond.
//
#define DS_PROBLEM_COMMUNICATIONS_PROBLEM 0x4000F20FL

//
// MessageId: DS_PROBLEM_CONSTRAINT_VIOLATION
//
// MessageText:
//
//  The value specified for an attribute is either too big, too small, or not valid.
//
#define DS_PROBLEM_CONSTRAINT_VIOLATION  0x4000F210L

//
// MessageId: DS_PROBLEM_DIT_ERROR
//
// MessageText:
//
//  An internal processing error has occurred: directory information tree error. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_DIT_ERROR             0x4000F211L

//
// MessageId: DS_PROBLEM_ENTRY_EXISTS
//
// MessageText:
//
//  This entry already exists. You can modify the existing entry.
//
#define DS_PROBLEM_ENTRY_EXISTS          0x4000F212L

//
// MessageId: DS_PROBLEM_INAPPROP_AUTHENTICATION
//
// MessageText:
//
//  An internal processing error has occurred: inappropriate authentication. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_INAPPROP_AUTHENTICATION 0x4000F213L

//
// MessageId: DS_PROBLEM_INAPPROP_MATCHING
//
// MessageText:
//
//  An internal processing error has occurred: inappropriate matching. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_INAPPROP_MATCHING     0x4000F214L

//
// MessageId: DS_PROBLEM_INSUFFICIENT_ACCESS_RIGHTS
//
// MessageText:
//
//  You do not have the permissions required to complete the operation.
//
#define DS_PROBLEM_INSUFFICIENT_ACCESS_RIGHTS 0x4000F215L

//
// MessageId: DS_PROBLEM_INVALID_ATTRIBUTE_SYNTAX
//
// MessageText:
//
//  An internal processing error has occurred: invalid attribute syntax. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_INVALID_ATTRIBUTE_SYNTAX 0x4000F216L

//
// MessageId: DS_PROBLEM_INVALID_ATTRIBUTE_VALUE
//
// MessageText:
//
//  An internal processing error has occurred: invalid attribute value. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_INVALID_ATTRIBUTE_VALUE 0x4000F217L

//
// MessageId: DS_PROBLEM_INVALID_CREDENTIALS
//
// MessageText:
//
//  An internal processing error has occurred: invalid credentials. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_INVALID_CREDENTIALS   0x4000F218L

//
// MessageId: DS_PROBLEM_INVALID_REF
//
// MessageText:
//
//  An internal processing error has occurred: invalid reference. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_INVALID_REF           0x4000F219L

//
// MessageId: DS_PROBLEM_INVALID_SIGNATURE
//
// MessageText:
//
//  An internal processing error has occurred: invalid object signature. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_INVALID_SIGNATURE     0x4000F21AL

//
// MessageId: DS_PROBLEM_LOOP_DETECTED
//
// MessageText:
//
//  An internal processing error has occurred: loop detected. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_LOOP_DETECTED         0x4000F21BL

//
// MessageId: DS_PROBLEM_MISCELLANEOUS
//
// MessageText:
//
//  An internal processing error has occurred: unknown directory error. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_MISCELLANEOUS         0x4000F21CL

//
// MessageId: DS_PROBLEM_MISSING_TYPE
//
// MessageText:
//
//  An internal processing error has occurred: missing type. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_MISSING_TYPE          0x4000F21DL

//
// MessageId: DS_PROBLEM_MIXED_SYNCHRONOUS
//
// MessageText:
//
//  The directory is currently performing a replication operation which prevents completion of this operation. Wait a few minutes and then try again.
//
#define DS_PROBLEM_MIXED_SYNCHRONOUS     0x4000F21EL

//
// MessageId: DS_PROBLEM_NAMING_VIOLATION
//
// MessageText:
//
//  An internal processing error has occurred: naming violation. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_NAMING_VIOLATION      0x4000F21FL

//
// MessageId: DS_PROBLEM_NO_INFORMATION
//
// MessageText:
//
//  An internal processing error has occurred: required information is not available. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_NO_INFORMATION        0x4000F220L

//
// MessageId: DS_PROBLEM_NO_SUCH_ATTRIBUTE_OR_VALUE
//
// MessageText:
//
//  The attribute does not exist.
//
#define DS_PROBLEM_NO_SUCH_ATTRIBUTE_OR_VALUE 0x4000F221L

//
// MessageId: DS_PROBLEM_NO_SUCH_OBJECT
//
// MessageText:
//
//  The object does not exist.
//
#define DS_PROBLEM_NO_SUCH_OBJECT        0x4000F222L

//
// MessageId: DS_PROBLEM_NO_SUCH_OPERATION
//
// MessageText:
//
//  An internal processing error has occurred: invalid operation. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_NO_SUCH_OPERATION     0x4000F223L

//
// MessageId: DS_PROBLEM_NOT_ALLOWED_ON_NON_LEAF
//
// MessageText:
//
//  The operation is not valid on a non-leaf node.
//
#define DS_PROBLEM_NOT_ALLOWED_ON_NON_LEAF 0x4000F224L

//
// MessageId: DS_PROBLEM_NOT_ALLOWED_ON_RDN
//
// MessageText:
//
//  The operation is not allowed on a relative distinguished name.
//
#define DS_PROBLEM_NOT_ALLOWED_ON_RDN    0x4000F225L

//
// MessageId: DS_PROBLEM_NOT_SUPPORTED
//
// MessageText:
//
//  An internal processing error has occurred: operation is not supported. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_NOT_SUPPORTED         0x4000F226L

//
// MessageId: DS_PROBLEM_OBJECT_CLASS_MOD_PROHIB
//
// MessageText:
//
//  An internal processing error has occurred: object classes cannot be modified. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_OBJECT_CLASS_MOD_PROHIB 0x4000F227L

//
// MessageId: DS_PROBLEM_OBJECT_CLASS_VIOLATION
//
// MessageText:
//
//  An internal processing error has occurred: object class violation. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_OBJECT_CLASS_VIOLATION 0x4000F228L

//
// MessageId: DS_PROBLEM_OUT_OF_SCOPE
//
// MessageText:
//
//  An internal processing error has occurred: out of scope. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_OUT_OF_SCOPE          0x4000F229L

//
// MessageId: DS_PROBLEM_PROTECTION_REQUIRED
//
// MessageText:
//
//  An internal processing error has occurred: protection required. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_PROTECTION_REQUIRED   0x4000F22AL

//
// MessageId: DS_PROBLEM_TIME_LIMIT_EXCEEDED
//
// MessageText:
//
//  An internal processing error has occurred: time limit exceeded. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_TIME_LIMIT_EXCEEDED   0x4000F22BL

//
// MessageId: DS_PROBLEM_TOO_LATE
//
// MessageText:
//
//  An internal processing error has occurred: time exceeded. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_TOO_LATE              0x4000F22CL

//
// MessageId: DS_PROBLEM_TOO_MANY_OPERATIONS
//
// MessageText:
//
//  The maximum number of operations has been reached.
//
#define DS_PROBLEM_TOO_MANY_OPERATIONS   0x4000F22DL

//
// MessageId: DS_PROBLEM_TOO_MANY_SESSIONS
//
// MessageText:
//
//  The maximum number of sessions has been reached.
//
#define DS_PROBLEM_TOO_MANY_SESSIONS     0x4000F22EL

//
// MessageId: DS_PROBLEM_UNABLE_TO_PROCEED
//
// MessageText:
//
//  An internal processing error has occurred: directory unable to proceed. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_UNABLE_TO_PROCEED     0x4000F22FL

//
// MessageId: DS_PROBLEM_UNAVAILABLE
//
// MessageText:
//
//  An internal processing error has occurred: information not available. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_UNAVAILABLE           0x4000F230L

//
// MessageId: DS_PROBLEM_UNAVAILABLE_CRIT_EXT
//
// MessageText:
//
//  An internal processing error has occurred: unavailable Crit. Ext. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_UNAVAILABLE_CRIT_EXT  0x4000F231L

//
// MessageId: DS_PROBLEM_UNDEFINED_ATTRIBUTE_TYPE
//
// MessageText:
//
//  An internal processing error has occurred: undefined attribute type. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_UNDEFINED_ATTRIBUTE_TYPE 0x4000F232L

//
// MessageId: DS_PROBLEM_UNWILLING_TO_PERFORM
//
// MessageText:
//
//  An internal processing error has occurred: cannot perform operation. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_PROBLEM_UNWILLING_TO_PERFORM  0x4000F233L

//
// MessageId: DS_PROBLEM_NOT_ON_CURRENT_SITE
//
// MessageText:
//
//  Changes cannot be written to this directory object. Try connecting to a Microsoft Exchange Server computer in the same site as this object.
//
#define DS_PROBLEM_NOT_ON_CURRENT_SITE   0x4000F234L

//
// MessageId: DS_FULL_DRIVE
//
// MessageText:
//
//  There is not enough space on the device.
//
#define DS_FULL_DRIVE                    0x4000F235L

//
// MessageId: DS_OUT_OF_MEMORY
//
// MessageText:
//
//  The server does not have enough memory.
//
#define DS_OUT_OF_MEMORY                 0x4000F236L

//
// MessageId: DS_SYSTEM_ERROR
//
// MessageText:
//
//  An internal processing error has occurred: system error. Try restarting the application or the Microsoft Exchange Server computer, or both.
//
#define DS_SYSTEM_ERROR                  0x4000F237L

