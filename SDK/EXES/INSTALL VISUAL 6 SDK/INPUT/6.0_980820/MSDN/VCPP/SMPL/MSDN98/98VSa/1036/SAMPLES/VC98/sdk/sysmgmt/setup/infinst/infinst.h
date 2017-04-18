
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1995-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

//
// commands
//
#define ID_INSTALL     100

//
// icons
//
#define EXE_ICON        300

//
// typedefs
//
typedef struct tagINSTALLINFO
{
    HINSTANCE hInst;        // current instance
    int iWelcome;
    int iLicense;
    int iInstall_Type;
    int iCustom_Options1;
    int iCustom_Options2;
    int iCustom_Options3;
    int iCustom_Options4;
    int iInstall;
    char pszUserName[MAX_PATH];
    char pszCompany[MAX_PATH];
    char pszProductIdString[MAX_PATH];
    char pszEmailAddress[MAX_PATH];
    char pszDestPath[MAX_PATH];
} INSTALLINFO;

//
// globals
//
extern INSTALLINFO setupInfo;   // a structure containing the review information
extern HWND hwndEdit;           // handle to the main MLE
extern TCHAR lpReview[MAX_BUF]; // Buffer for the review
extern BOOL bCreated;           // Keep us minimized once we are created
extern BOOL bUninstallCommand;  // Is it an uninstall

//
// Function prototypes
//

long APIENTRY MainWndProc(HWND, UINT, UINT, LONG);
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
void RuntimeRegistration(INSTALLINFO*);

//
// simple win32 registry api wrappers
//
BOOL RegisterString(LPSTR pszKey, LPSTR pszValue, LPSTR pszData);
BOOL GetRegString(LPSTR pszKey, LPSTR pszValue, LPSTR pszData);

//
// Context for data needed in my callback routine
// This needs to include the context for the default callback
// since my callback calls the default
//

typedef struct tagMY_INSTALL_DATA{

   // TODO: Add other data here that you want to have 
   //       available to your callback function.
   //       For example, you may keep a counter that indicates
   //       your bill board if you are doing your own progress dialog

   PVOID pDefaultContext;

} MY_INSTALL_DATA;

//
// call back routine for setup api uses for
// progress and error messages
//
LRESULT WINAPI MyQueueCallback (
    IN MY_INSTALL_DATA* pMyInstallData,
    IN UINT Notification,
    IN UINT Param1,
    IN UINT Param2
    );

//
// Product Registry keys
// set by exe and not inf since these are runtime 
// values.  All registry information that is not determined at 
// runtime is in the inf file
//
#define USER_NAME_KEY       TEXT("UserName")
#define COMPANY_KEY         TEXT("CompanyName")
#define PRODUCT_ID_KEY      TEXT("ProductId")
#define EMAIL_KEY           TEXT("EmailAddress")

#define UNINSTALL_KEY       TEXT("SoftWare\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\MyProduct")
#define MYPRODUCT_KEY       TEXT("Software\\MyCompany\\MyProduct\\UserInfo\\")
