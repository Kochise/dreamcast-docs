// **************************************************************************
// Copyright (C) 1995 by Microsoft Corporation.
//
//  File: status.inc
//
//  This file is included by most of the samples. It contains a single
//  function that translates an SMS status code into a string.
//
//  Author: Larry A. French
//
// **************************************************************************

// ====================================================================
//
// GetStatusName
//
// This function converts the numeric SMS return code value
// into its mnemonic form.
//
// Parameters:
//  SMS_STATUS stat
//      The SMS return status code.
//
// Returns:
//  const char*
//      A pointer to a constant string containing the memonic name
//      of the status value.
//
// ====================================================================
const char *GetStatusName( SMS_STATUS stat )
{
    // For any status codes not in the following switch
    // statement, the default cause converts it to a
    // decimal value and stores the converted value in
    // "szStatus".  Sixteen bytes should be enough to
    // hold any such value.
    // There should not be any such values.
    //===================================================
    static char szStatus[16];
    const char* pszStat;

    switch(stat) {
    case SMS_OK:
        pszStat = "SMS_OK";
        break;

    case SMS_MORE_DATA:
        pszStat = "SMS_MORE_DATA";
        break;

    case SMS_NO_MORE_DATA:
        pszStat = "SMS_NO_MORE_DATA";
        break;

    case SMS_FOLDER_NO_UPDATE:
        pszStat = "SMS_FOLDER_NO_UPDATE";
        break;

    case SMS_DUPLICATE_CONTAINER_ID:
        pszStat = "SMS_DUPLICATE_CONTAINER_ID";
        break;

    case SMS_DUPLICATE_FOLDER_ID:
        pszStat = "SMS_DUPLICATE_FOLDER_ID";
        break;

    case SMS_DUPLICATE_FILTER_ID:
        pszStat = "SMS_DUPLICATE_FILTER_ID";
        break;

    case SMS_DUPLICATE_FILTER:
        pszStat = "SMS_DUPLICATE_FILTER";
        break;

    case SMS_SCALAR_NO_UPDATE:
        pszStat = "SMS_SCALAR_NO_UPDATE";
        break;

    case SMS_SCALAR_WRONG_TYPE:
        pszStat = "SMS_SCALAR_WRONG_TYPE";
        break;

    case SMS_INVALID_CONTAINER_ID:
        pszStat = "SMS_INVALID_CONTAINER_ID";
        break;

    case SMS_INVALID_FOLDER_ID:
        pszStat = "SMS_INVALID_FOLDER_ID";
        break;

    case SMS_INVALID_FILTER_ID:
        pszStat = "SMS_INVALID_FILTER_ID";
        break;

    case SMS_CONTAINER_NO_UPDATE:
        pszStat = "SMS_CONTAINER_NO_UPDATE";
        break;

    case SMS_PARAMETER_ERROR:
        pszStat = "SMS_PARAMETER_ERROR";
        break;

    case SMS_UNSUPPORTED:
        pszStat = "SMS_UNSUPPORTED";
        break;

    case SMS_NOT_FOUND:
        pszStat = "SMS_NOT_FOUND";
        break;

    case SMS_PARENT_NOT_FOUND:
        pszStat = "SMS_PARENT_NOT_FOUND";
        break;

    case SMS_CANT_DELETE:
        pszStat = "SMS_CANT_DELETE";
        break;

    case SMS_NEW_FOLDER:
        pszStat = "SMS_NEW_FOLDER";
        break;

    case SMS_FOLDER_LINKED:
        pszStat = "SMS_FOLDER_LINKED";
        break;

    case SMS_RANGE_ERROR:
        pszStat = "SMS_RANGE_ERROR";
        break;

    case SMS_CONTAINER_NOT_POPULATED:
        pszStat = "SMS_CONTAINER_NOT_POPULATED";
        break;

    case SMS_CONTAINER_POPULATED:
        pszStat = "SMS_CONTAINER_POPULATED";
        break;

    case SMS_FILTER_NOT_PERSISTENT:
        pszStat = "SMS_FILTER_NOT_PERSISTENT";
        break;

    case SMS_INVALID_CONNECTION_HANDLE:
        pszStat = "SMS_FILTER_NOT_PERSISTENT";
        break;

    case SMS_INVALID_FILTER_TYPE:
        pszStat = "SMS_INVALID_FILTER_TYPE";
        break;

    case SMS_ERROR:
        pszStat = "SMS_ERROR";
        break;

    case SMS_SQL_ERROR:
        pszStat = "SMS_SQL_ERROR";
        break;

    case SMS_INVALID_DATASOURCE:
        pszStat = "SMS_INVALID_DATA_SOURCE";
        break;

    case SMS_INVALID_HANDLE:
        pszStat = "SMS_INVALID_HANDLE";
        break;

    case SMS_INVALID_FOLDER_TYPE:
        pszStat = "SMS_INVALID_FOLDER_TYPE";
        break;

    case SMS_CONNECT_FAILED:
        pszStat = "SMS_CONNECT_FAILED";
        break;

    case SMS_NO_CREATE:
        pszStat = "SMS_NO_CREATE";
        break;

    case SMS_FOLDER_NOT_MODIFIED:
        pszStat = "SMS_FOLDER_NOT_MODIFIED";
        break;

    case SMS_INCORRECT_FOLDER_TYPE:
        pszStat = "SMS_INCORRECT_FOLDER_TYPE";
        break;

    case SMS_INVALID_PARAMETER:
        pszStat = "SMS_INVALID_PARAMETER";
        break;

    case SMS_EMPTY:
        pszStat = "SMS_EMPTY";
        break;

    case SMS_NOT_READY:
        pszStat = "SMS_NOT_READY";
        break;

    case SMS_PARENT_ALREADY_COMMITTED:
        pszStat = "SMS_PARENT_ALREADY_COMMITTED";
        break;

    case SMS_FILTER_NO_MODIFY:
        pszStat = "SMS_FILTER_NO_MODIFY";
        break;

    case SMS_ALREADY_CONNECTED:
        pszStat = "SMS_ALREADY_CONNECTED";
        break;

    case SMS_COMMIT_FAILED:
        pszStat = "SMS_COMMIT_FAILED";
        break;

    case SMS_FOLDER_ALREADY_DELETED:
        pszStat = "SMS_FOLDER_ALREADY_DELETED";
        break;

    default:
        sprintf(szStatus, "%ld", stat);
        pszStat = szStatus;
        break;

    }

    return( pszStat );
}



// ====================================================================
// DisplaySmsError
//
// Convert the SMS status value to a human-readable form and display it
// along with an error message string.
//
// Input:
//      const char* pszMessage
//              Pointer to the error message string
//
//      SMS_STATUS stat
//              A value returned from the SMS api.
//
// Returns: Nothing.
//
// ====================================================================
void DisplaySmsError(const char* pszMessage, SMS_STATUS stat)
{
    const char* pszStat = GetStatusName(stat);
    printf("%s: (status = %ld :  %s)\n", pszMessage, stat, pszStat);
}

/* EOF: status.inc */

