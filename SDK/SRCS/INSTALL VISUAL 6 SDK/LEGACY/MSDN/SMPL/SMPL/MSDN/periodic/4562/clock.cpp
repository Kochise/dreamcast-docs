/***********************************************************************
Clock.Cpp - Code to quickly demo voice commands and voice-text doing
	 a clock application.

Copyright c. 1995 by Microsoft Corporation

THE INFORMATION AND CODE PROVIDED HEREUNDER (COLLECTIVELY REFERRED TO
AS "SOFTWARE") IS PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND, EITHER
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. IN
NO EVENT SHALL MICROSOFT CORPORATION OR ITS SUPPLIERS BE LIABLE FOR
ANY DAMAGES WHATSOEVER INCLUDING DIRECT, INDIRECT, INCIDENTAL,
CONSEQUENTIAL, LOSS OF BUSINESS PROFITS OR SPECIAL DAMAGES, EVEN IF
MICROSOFT CORPORATION OR ITS SUPPLIERS HAVE BEEN ADVISED OF THE
POSSIBILITY OF SUCH DAMAGES. SOME STATES DO NOT ALLOW THE EXCLUSION OR
LIMITATION OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES SO THE
FOREGOING LIMITATION MAY NOT APPLY.

This Software may be copied and distributed royalty-free subject to
the following conditions:

1. You must copy all Software without modification and must include
   all pages, if the Software is distributed without inclusion in your
   software product. If you are incorporating the Software in
   conjunction with and as a part of your software product which adds
   substantial value, you may modify and include portions of the
   Software.

2. You must place all copyright notices and other protective
   disclaimers and notices contained on the Software on all copies of
   the Software and your software product.

3. Unless the Software is incorporated in your software product which
   adds substantial value, you may not distribute this Software for
   profit.

4. You may not use Microsoft's name, logo, or trademarks to market
   your software product.

5. You agree to indemnify, hold harmless, and defend Microsoft and its
   suppliers from and against any claims or lawsuits, including
   attorneys' fees, that arise or result from the use or distribution
   of your software product and any modifications to the Software.
*/

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <mmsystem.h>
#include <initguid.h>
#include <objbase.h>
#include <objerror.h>
#include <ole2ver.h>

#include <speech.h>
#include "resource.h"

/* defines */
#define  IDC_WHATTIMEISIT        1
#define  IDC_WHATDAYISIT         2
#define  IDC_STOPRUNNING         3

/* classes */

// Voice Command notifications
class CIVCmdNotifySink : public IVCmdNotifySink {
    public:
    CIVCmdNotifySink(void);
    ~CIVCmdNotifySink(void);

    // IUnkown members that delegate to m_punkOuter
    // Non-delegating object IUnknown
    STDMETHODIMP         QueryInterface (REFIID, LPVOID FAR *);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

    // IVCmdNotifySink members
    STDMETHODIMP CommandRecognize (DWORD, PVCMDNAME, DWORD, DWORD, PVOID, 
                                   DWORD,PSTR, PSTR);
    STDMETHODIMP CommandOther     (PVCMDNAME, PSTR);
    STDMETHODIMP MenuActivate     (PVCMDNAME, BOOL);
    STDMETHODIMP UtteranceBegin   (void);
    STDMETHODIMP UtteranceEnd     (void);
    STDMETHODIMP CommandStart     (void);
    STDMETHODIMP VUMeter          (WORD);
    STDMETHODIMP AttribChanged    (DWORD);
    STDMETHODIMP Interference     (DWORD);
};
typedef CIVCmdNotifySink * PCIVCmdNotifySink;

/*************************************************************************
Globals */

HINSTANCE         ghInstance;                // instance handle
TCHAR             gszName[] = "Talking Clock";
BOOL              gfTTSInitialized = FALSE;
PIVOICETEXT       gpIVTxt = NULL;
CIVCmdNotifySink  gVCmdNotifySink;
PIVOICECMD        gpIVoiceCommand = NULL;
PIVCMDMENU        gpIVCmdMenu = NULL;
HWND              ghWndMain = NULL;

/************************************************************
	AddCommand - This adds a command to the menu.

	inputs
		PIVCMDMENU     pIVCmdMenu - Menu to add to
		LPCTSTR        pszCommand - command to add
		DWORD          dwValue - command ID
	returns
		HRESULT - error
*/
HRESULT AddCommand(PIVCMDMENU pIVCmdMenu, LPCTSTR pszCommand, DWORD dwValue)
{
   BYTE     bMem[512];  // this is an arbitrarily large value
   PVCMDCOMMAND   pVCmd = (PVCMDCOMMAND) bMem;
   TCHAR    *pTemp = (TCHAR*) (pVCmd + 1);
   DWORD    dwLen;

   // blank out the header
   memset (pVCmd, 0, sizeof(*pVCmd));
   pVCmd->dwID = dwValue;

   // copy over the name, one for command, once for category
   strcpy (pTemp, pszCommand);
   dwLen = (strlen(pszCommand) + 1) * sizeof(TCHAR);
   dwLen = (dwLen + 3) & (~3);   // DWORD align
   pVCmd->dwCommand = (DWORD) ((BYTE*)pTemp - bMem); 
   pTemp += (dwLen / sizeof(TCHAR));

   strcpy (pTemp, pszCommand);
   dwLen = (strlen(pszCommand) + 1) * sizeof(TCHAR);
   dwLen = (dwLen + 3) & (~3);   // DWORD align
   pVCmd->dwCategory = (DWORD) ((BYTE*)pTemp - bMem); 
   pTemp += (dwLen / sizeof(TCHAR));

   pVCmd->dwSize = (DWORD) ((BYTE*)pTemp - bMem);

   DWORD dwStart;
   SDATA data;
   data.pData = pVCmd;
   data.dwSize = pVCmd->dwSize;
   return (pIVCmdMenu->Add (1, data, &dwStart));
}

/*************************************************************************
	Initialize - This:
		1) Initialized OLE
		2) Creates a voice command object
		3) Creates a voice commands menu from the object
		4) Adds two commands, "What time is it?" and "What day is it?"
			to the menu.
		5) Initializes voice text.

	inputs
		none
	returns
		HRESULT - Error value
*/
HRESULT Initialize(void)
{
   HRESULT  hRes = NOERROR;

   // Initialize OLE
   hRes = CoInitialize(NULL);
   if (hRes)
      return hRes;

   // Create the voice commands object
   if (hRes = CoCreateInstance(CLSID_VCmd,
      NULL, 
      CLSCTX_LOCAL_SERVER, 
      IID_IVoiceCmd, 
      (LPVOID *)&gpIVoiceCommand) != S_OK)
         goto fail;

   hRes = gpIVoiceCommand->Register("", &gVCmdNotifySink,
         IID_IVCmdNotifySink, 0, NULL);
   if (hRes)
      goto fail;

   // Create  a temporary menu given the window's text
   VCMDNAME    VcmdName;
   LANGUAGE    Language;
   lstrcpy (VcmdName.szApplication, gszName);
   lstrcpy (VcmdName.szState, "Global");
   Language.LanguageID = LANG_ENGLISH;
   lstrcpy (Language.szDialect, "");
   hRes = gpIVoiceCommand->MenuCreate( &VcmdName,
        &Language,
        VCMDMC_CREATE_TEMP,
        &gpIVCmdMenu
		  );
   if (hRes)
      goto fail;     // error

   // Add commands
   hRes = AddCommand (gpIVCmdMenu, "What time is it?", IDC_WHATTIMEISIT);
   if (hRes)
      goto fail;
   AddCommand (gpIVCmdMenu, "What day is it?", IDC_WHATDAYISIT);
   if (hRes)
      goto fail;
   AddCommand (gpIVCmdMenu, "Stop running Talking Clock.", IDC_STOPRUNNING);
   if (hRes)
      goto fail;

   // activate the menu
   hRes = gpIVCmdMenu->Activate(NULL, 0);
   if (hRes)
      goto fail;

   // Create a voice text object...
   if(hRes = CoCreateInstance(CLSID_VTxt, NULL, 
		CLSCTX_LOCAL_SERVER, IID_IVoiceText, (LPVOID *)&gpIVTxt) != S_OK)
   	goto fail;
   if (hRes = gpIVTxt->Register( "", gszName, NULL, 
		IID_IVTxtNotifySink, NULL, NULL ))
      goto fail;

   return hRes;

	// else failed
fail:
	if (gpIVCmdMenu)
		gpIVCmdMenu->Release();
	gpIVCmdMenu = NULL;
	if (gpIVoiceCommand)
		gpIVoiceCommand->Release();
	gpIVoiceCommand = NULL;
	if (gpIVTxt)
		gpIVTxt->Release();
	gpIVTxt = NULL;

	return hRes;
}

/*************************************************************************
	ShutDown - This closes up the OLE and frees everything else.

	inputs
		none
	returns
		HRESULT - Error value
*/
HRESULT ShutDown (void)
{
   // Free the interfaces
   if (gpIVCmdMenu)
      gpIVCmdMenu->Release();
   gpIVCmdMenu = NULL;
   if (gpIVoiceCommand)
      gpIVoiceCommand->Release();
   gpIVoiceCommand = NULL;
   if (gpIVTxt)
      gpIVTxt->Release();
   gpIVTxt = NULL;

   CoUninitialize ();

   return NOERROR;
}

/**************************************************************************
 *  Voice Command notification object
 **************************************************************************/

CIVCmdNotifySink::CIVCmdNotifySink (void)
{
}

CIVCmdNotifySink::~CIVCmdNotifySink (void)
{
}

STDMETHODIMP CIVCmdNotifySink::QueryInterface (REFIID riid, LPVOID *ppv)
{
    *ppv = NULL;

    /* always return our IUnkown for IID_IUnknown */
    if (IsEqualIID (riid, IID_IUnknown) || 
		 IsEqualIID(riid,IID_IVCmdNotifySink)) {
        *ppv = (LPVOID) this;
        return NOERROR;
    }
    // otherwise, cant find
    return ResultFromScode (E_NOINTERFACE);
}

STDMETHODIMP_ (ULONG) CIVCmdNotifySink::AddRef (void)
{
    // normally this increases a reference count, but this object
    // is going to be freed as soon as the app is freed, so it doesn't
    // matter
    return 1;
}

STDMETHODIMP_(ULONG) CIVCmdNotifySink::Release (void)
{
    // normally this releases a reference count, but this object
    // is going to be freed when the application is freed so it doesnt
    // matter
    return 1;
};

STDMETHODIMP CIVCmdNotifySink::CommandRecognize(DWORD dwID, PVCMDNAME pName,
   DWORD dwFlags, DWORD dwActionSize, PVOID pAction, DWORD dwNumLists,
   PSTR pszListValues, PSTR pszCommand)
{
   // We only care about dwID for this case
   SYSTEMTIME  st;
   TCHAR       szTemp[128];

   switch (dwID){
	case IDC_WHATTIMEISIT:
		strcpy (szTemp, "The time is ");
		GetLocalTime (&st);
		GetTimeFormat (0, TIME_NOSECONDS, &st, NULL,
			szTemp + strlen(szTemp), sizeof(szTemp) - strlen(szTemp));
		gpIVTxt->Speak( szTemp, VTXTSP_NORMAL, NULL );
		break;

	case IDC_WHATDAYISIT:
		strcpy (szTemp, "The day is ");
		GetLocalTime (&st);
		GetDateFormat (0, DATE_LONGDATE	, &st, NULL,
			szTemp + strlen(szTemp), sizeof(szTemp) - strlen(szTemp));
		gpIVTxt->Speak( szTemp, VTXTSP_NORMAL, NULL );
		break;

	case IDC_STOPRUNNING:
		DestroyWindow (ghWndMain);
		break;
	};

	return NOERROR;
}

STDMETHODIMP CIVCmdNotifySink::CommandOther(PVCMDNAME pName, PSTR pszCommand)
{
   // This is called when a recognition occurs for another application,
   // or an unknown recognition occurs
   return NOERROR;
}

STDMETHODIMP CIVCmdNotifySink::MenuActivate(PVCMDNAME pName, BOOL bActive)
{
   // Called when a menu is activated or deactivated. We don't care
   return NOERROR;
}

STDMETHODIMP CIVCmdNotifySink::AttribChanged(DWORD dwAttribute)
{
   // Called when an attribute changes.
   return NOERROR;
}

STDMETHODIMP CIVCmdNotifySink::Interference(DWORD dwType)
{
   // Called when audio interference is happening. We don't care.
   return NOERROR;
}

STDMETHODIMP CIVCmdNotifySink::CommandStart(void)
{
   // Called when SR starts processing a command. We don't care.
   return NOERROR;
}

STDMETHODIMP CIVCmdNotifySink::UtteranceBegin(void)
{
   // Called when an utterance begins. We don't care.
   return NOERROR;
}

STDMETHODIMP CIVCmdNotifySink::UtteranceEnd()
{
   // Called when an utterance finishes. We don't care
   return NOERROR;
}

STDMETHODIMP CIVCmdNotifySink::VUMeter(WORD wLevel)
{
   // Called for VU meter notifications. We don't care
   return NOERROR;
}

/******************************************************
   HiddenWndProc - Hidden window procedure
*/
LRESULT CALLBACK HiddenWndProc (HWND hWnd, UINT Message,
	WPARAM wParam, LPARAM lParam)
{                     
   switch (Message){
	case WM_DESTROY:
		PostQuitMessage (0);
		break;
	};
    
   return DefWindowProc (hWnd, Message, wParam, lParam);
}

/*************************************************************************
   WinMain - Windows main code.
*/
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine, int nCmdShow)
{
   HRESULT  hRes;
   ghInstance = hInstance;
   hRes = Initialize();
   if (FAILED(hRes)){
      MessageBox (NULL, "Talking Clock cannot initialize.",
         NULL, MB_OK);
      return -1;
	};

   WNDCLASS        wndclass;             
   memset(&wndclass, 0x00, sizeof(WNDCLASS));
   wndclass.lpfnWndProc = HiddenWndProc;
   wndclass.hInstance = hInstance;
   wndclass.lpszClassName = gszName; /* Class Name is App Name */
   RegisterClass(&wndclass);

   ghWndMain = CreateWindow ( 
       gszName,
       gszName,
       0,
       0, 0,
       0, 0,
       NULL, NULL, hInstance, NULL);    
   if (!ghWndMain){
      MessageBox (NULL, "Talking Clock cannot initialize.",
         NULL, MB_OK);
      return -2;
	};

   MSG msg;						/* MSG structure to store your messages        */
   while (GetMessage(&msg, NULL, 0, 0)) {     /* Until WM_QUIT message    */
      TranslateMessage(&msg);
      DispatchMessage(&msg);
	};

   ShutDown();

   return 0;
}

