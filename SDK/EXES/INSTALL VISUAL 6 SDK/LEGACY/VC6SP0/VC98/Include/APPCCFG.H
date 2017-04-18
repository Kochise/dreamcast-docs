/*****************************************************************************/
/*                                                                           */
/* Header: appccfg.h                                                         */
/*                                                                           */
/* (C) COPYRIGHT Data Connection Ltd 1993                                    */
/* (C) COPYRIGHT Microsoft Corp.     1993                                    */
/*                                                                           */
/* Header for appccfg.c                                                      */
/*                                                                           */
/*****************************************************************************/
/*  ----  14/05/93  CD  Initial coding                                       */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/* HANDLE WINAPI GetAppcConfig( HANDLE hWnd, LPSTR pLocalLu, LPSTR pMode,    */
/*                              LPINT pNumRemLu, INT iMaxRemLu, LPSTR pRemLu,*/
/*                              LPINT pAsyncRetCode)                         */
/*                                                                           */
/* Parameters                                                                */
/* ----------                                                                */
/*                                                                           */
/*  IN      hWnd      Handle of window to which completion is to be posted.  */
/*                    If NULL no completion message will be posted but       */
/*                    pAsyncRetCode must be valid. If hWnd is non-NULL it    */
/*                    must be valid & pAsyncRetCode must be NULL.            */
/*                                                                           */
/*  IN      pLocalLU  Pointer to max 8 byte ASCII local LU name (should be 8 */
/*                    ASCII blanks to request info on Remote LUs partnered   */
/*                    to the default Local LU for this user. If none is      */
/*                    configured then APPC_CFG_ERROR_NO_DEFAULT_LOCAL will   */
/*                    be returned in the LPARAM).                            */
/*                                                                           */
/*  IN      pMode     Pointer to max 8 byte ASCII mode name (usually         */
/*                    "QPCSUPP" for a 5250 emulator)                         */
/*                                                                           */
/*  IN/OUT  pNumRemLu Pointer to int to receive the number of Remote LUs     */
/*                    available. (If more than MaxRemLu then only the first  */
/*                    MaxRemLu of them will have been copied)                */
/*                                                                           */
/*  IN      iMaxRemLu Int giving the max number of Remote LU names the       */
/*                    buffer can hold. (size of buffer in bytes / 9)         */
/*                                                                           */
/*  IN/OUT  pRemLu    Pointer to buffer to receive Remote LUs                */
/*                    The data will be returned as an array of max 8 byte    */
/*                    ASCII strings each followed by a terminating NULL      */
/*                                                                           */
/*  IN/OUT  pAsyncRetCode                                                    */
/*                    Optional pointer to int to take the RetCode on         */
/*                    completion of the async part of the call. Only         */
/*                    required if hWnd is NULL. If the request is not        */
/*                    accepted the value in AsyncRetCode is undefined.       */
/*                    It the request was accepted then until the request is  */
/*                    completed AsyncRetCode will contain the value          */
/*                    APPC_CFG_PENDING. Final values are as in the LPARAM of */
/*                    the completion message. If hWnd != NULL, pAsyncRetCode */
/*                    must be NULL.                                          */
/*                                                                           */
/*                                                                           */
/* Returns                                                                   */
/* -------                                                                   */
/*                                                                           */
/* On Call                                                                   */
/* -------                                                                   */
/*  HANDLE  This VerbId will be returned in the WPARAM of any completion     */
/*          message. (VerbId & APPC_CFG_SUCCESS) evaluates to TRUE if the    */
/*          request was accepted.                                            */
/*                                                                           */
/*          If the above expression evaluates to FALSE then VerbId will      */
/*          have one of the following values:                                */
/*                                                                           */
/*             APPC_CFG_ERROR_NO_APPC_INIT                                   */
/*             APPC_CFG_ERROR_INVALID_HWND                                   */
/*             APPC_CFG_ERROR_BAD_POINTER                                    */
/*             APPC_CFG_ERROR_UNCLEAR_COMPLETION_MODE                        */
/*             APPC_CFG_ERROR_TOO_MANY_REQUESTS                              */
/*             APPC_CFG_ERROR_GENERAL_FAILURE                                */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* On Receipt of completion message                                          */
/* --------------------------------                                          */
/*  MSG     Equal to return from RegisterWindowMessage with                  */
/*          WIN_APPC_CFG_COMPLETION_MSG passed as message name.              */
/*                                                                           */
/*  WPARAM  VerbId returned on the initiating call.                          */
/*                                                                           */
/*  LPARAM  Retcode which will be one of the following:                      */
/*                                                                           */
/*             APPC_CFG_SUCCESS_NO_DEFAULT_REMOTE                            */
/*             APPC_CFG_SUCCESS_DEFAULT_REMOTE                               */
/*                                                                           */
/*             APPC_CFG_ERROR_NO_DEFAULT_LOCAL_LU                            */
/*             APPC_CFG_ERROR_BAD_LOCAL_LU                                   */
/*             APPC_CFG_ERROR_GENERAL_FAILURE                                */
/*                                                                           */
/*  (Retcode & APPC_CFG_ERROR)   evaluates to TRUE for an error retcode      */
/*  (Retcode & APPC_CFG_SUCCESS) evaluates to TRUE for a success retcode     */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* Comments                                                                  */
/* --------                                                                  */
/*  This call attempts to get all the remote systems (partner LUs) which can */
/*  be accessed by the logged on user with the given local LU and mode name. */
/*  The final retcode also indicates if there is a default remote system     */
/*  configured.                                                              */
/*                                                                           */
/*  Completion will either be signified by the posting of a completion       */
/*  message or by the change of *pAsyncRetCode to a value other than         */
/*  APPC_CFG_PENDING. The latter mechanism is intended for use by console    */
/*  apps with no windows or on non-Windows platforms. Completion can then    */
/*  be tested by code similar to the below:                                  */
/*                                                                           */
/*                while (*pAsyncRetCode == APPC_CFG_PENDING)                 */
/*                {                                                          */
/*                  sleep(250);                                              */
/*                }                                                          */
/*                                                                           */
/*  Note that one of hWnd & pAsyncRetCode must be NULL and the other valid.  */
/*  If this isn't the case APPC_CFG_ERROR_UNCLEAR_COMPLETION_MODE will be    */
/*  returned.                                                                */
/*                                                                           */
/*  All strings are null terminated and are NOT space padded                 */
/*                                                                           */
/*  If the buffer is too short, the reported number of remote LU's available */
/*  MAY be GREATER than the actual number. (This will only be the case where */
/*  a particular Local Lu is configured at multiple nodes, and has the       */
/*  remote on multiple nodes.) When the call is made again which a buffer    */
/*  large enough to take all the remote LU, the reported number will be      */
/*  correct.                                                                 */
/*                                                                           */
/*  ALL MEMORY TO WHICH POINTERS ARE PASSED MUST REMAIN VALID TILL A         */
/*  COMPLETION MESSAGE IS RECEIVED                                           */
/*                                                                           */
/*  WinAPPCStartup MUST be called first                                      */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/* Entry point prototype                                                     */
/*****************************************************************************/
extern HANDLE WINAPI GetAppcConfig( HANDLE hWnd, LPSTR pLocalLu, LPSTR pMode,
                                 LPINT pNumRemLu, INT iMaxRemLu, LPSTR pRemLu,
                                 LPINT pAsyncRetCode);

/*****************************************************************************/
/* Completion Message Name                                                   */
/*****************************************************************************/
#define  WIN_APPC_CFG_COMPLETION_MSG "WinAppcCfg"

/*****************************************************************************/
/* Test values                                                               */
/*****************************************************************************/
#define  APPC_CFG_SUCCESS                      0x1000
#define  APPC_CFG_ERROR                        0x2000
#define  APPC_CFG_PENDING                      0xFFFF

/*****************************************************************************/
/* Retcodes                                                                  */
/*****************************************************************************/
#define  APPC_CFG_SUCCESS_NO_DEFAULT_REMOTE     (APPC_CFG_SUCCESS + 1)
#define  APPC_CFG_SUCCESS_DEFAULT_REMOTE        (APPC_CFG_SUCCESS + 2)

#define  APPC_CFG_ERROR_NO_DEFAULT_LOCAL_LU     (APPC_CFG_ERROR + 1)
#define  APPC_CFG_ERROR_BAD_LOCAL_LU            (APPC_CFG_ERROR + 2)
#define  APPC_CFG_ERROR_GENERAL_FAILURE         (APPC_CFG_ERROR + 3)
#define  APPC_CFG_ERROR_INVALID_HWND            (APPC_CFG_ERROR + 4)
#define  APPC_CFG_ERROR_BAD_POINTER             (APPC_CFG_ERROR + 5)
#define  APPC_CFG_ERROR_TOO_MANY_REQUESTS       (APPC_CFG_ERROR + 6)
#define  APPC_CFG_ERROR_NO_APPC_INIT            (APPC_CFG_ERROR + 7)
#define  APPC_CFG_ERROR_UNCLEAR_COMPLETION_MODE (APPC_CFG_ERROR + 8)
