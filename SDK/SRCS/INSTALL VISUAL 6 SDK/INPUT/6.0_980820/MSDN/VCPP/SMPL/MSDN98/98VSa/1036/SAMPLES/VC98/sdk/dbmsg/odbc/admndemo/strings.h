//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//|   Title:   STRINGS.H
//|      This file contains the defines for the string table error and
//|      information messages.  Load these strings using the GetidsString
//|      function.
//*---------------------------------------------------------------------------------
#ifndef strings_DEFS
#define strings_DEFS


//*---------------------------------------------------------------------------------
//|   Macros and Defines
//*---------------------------------------------------------------------------------
#define idsFileClosed                        8000
#define idsSuccessConnect                    8001
#define idsDisconnectSuccess                 8002
#define idsErrorString                       8003
#define idsMsgErrorString                    8004
#define idsCloseFile                         8005
#define idsOpenFileFailed                    8006
#define idsSaveFileFailed                    8007
#define idsSQLAllocHandleFailed              8008
#define idsMaxRecords                        8009
#define idsStmtProcessed                     8010
#define idsAffectedRows                      8011
#define idsNoDataFound                       8012
#define idsNumTooSmall                       8013
#define idsTerminatorNotFound                8014
#define idsExecutingFile                     8015
#define idsInvalidTerminator                 8016
#define idsPipeNotFound                      8017
#define idsInvalidParamValue                 8018
#define idsOutOfMemory                       8019
#define idsInvalidCmdLine                    8020
#define idsCmdLineTooBig                     8021
#define idsDftFileFilter                     8022
#define idsExpression                        8023
#define idsInvalidInt                        8024
#define idsTooManyParms                      8025
#define idsInvalidName                       8026
#define idsTooManyConnects                   8027

#endif
