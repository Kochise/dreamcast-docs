/*
 * OLEINST.C
 *
 * OLE-Specific installation data types and function prototypes.
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */

#ifdef WIN32
#include <winreg.h>
#else
#include <shellapi.h>
#endif


typedef struct
    {
    LPSTR       pszServerName;      //Full server name.
    LPSTR       pszServerClass;     //Short server class name.
    LPSTR       pszServerPath;      //Full path to server module.
    LPSTR       pszHandlerPath;     //Optional Full path to object handler DLL.
    LPSTR       pszExt;             //File extension for the server.
    LPSTR      *ppszVerbs;          //Pointer to array of LPSTRs to verbs.
    UINT        cVerbs;             //Number of verbs in array.
    LPSTR       pszSetFormats;      //Optional CSV list of accepted formats.
    LPSTR       pszRequestFormats;  //Optional CSV list of requestable formats.
    BOOL        fExecute;           //Is OleExecute supported?
    } REGINSTALL;

typedef REGINSTALL FAR *LPREGINSTALL;
#define CBREGINSTALL sizeof(REGINSTALL)


//Function prototypes
BOOL     WINAPI FRegDBInstall(void);
BOOL     WINAPI FOLEServerInstall(LPREGINSTALL);
BOOL     PASCAL FKeyCreate(LPSTR, LPSTR, LPSTR);


//Verbs
#define OBJVERB_EDIT    0
#define OBJVERB_PLAY    1
#define OBJVERB_MAX     1
