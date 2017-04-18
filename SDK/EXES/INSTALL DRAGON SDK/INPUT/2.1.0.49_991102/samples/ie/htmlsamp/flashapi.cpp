#ifdef USE_FLASH

#include <windows.h>

#define MIDL_INTERFACE(x)   struct __declspec(uuid(x)) __declspec(novtable)		// missed definition from rpcndr.h

#include "FlashAPI.h"
#include "CEFlash.h"
#include "CEFlash_i.c"

IDCFlashPlayer *g_pDCFlashPlayer = NULL;

enum {
	FLASHAPI_NOT_LOADED		= 0,
	FLASHAPI_LOADED			= 1,
	FLASHAPI_ERROR			= 2
} g_FlashAPIState = FLASHAPI_NOT_LOADED;

typedef DWORD (WINAPI *REGISTERPROC)();

BOOL InitFlashAPI()
{
	if (g_FlashAPIState == FLASHAPI_LOADED) {
		return TRUE;
	}

	if (g_FlashAPIState == FLASHAPI_ERROR) {
		return FALSE;
	}

	HMODULE hModule = LoadLibrary(_T("CEFLASH.DLL"));
	if (!hModule) {
		g_FlashAPIState = FLASHAPI_ERROR;
		FreeLibrary(hModule);
		return FALSE;
	}

	REGISTERPROC pRegisterProc = (REGISTERPROC) GetProcAddress(hModule, _T("DllRegisterServer"));
	if (!pRegisterProc) {
		g_FlashAPIState = FLASHAPI_ERROR;
		FreeLibrary(hModule);
		return FALSE;
	}

	if (FAILED(pRegisterProc())) {
		g_FlashAPIState = FLASHAPI_ERROR;
		FreeLibrary(hModule);
		return FALSE;
	}

	if (FAILED(CoCreateInstance(CLSID_DCFlashPlayer,
								NULL,
								CLSCTX_INPROC_SERVER,
								IID_IDCFlashPlayer,
								(void**) &g_pDCFlashPlayer))) {
		g_FlashAPIState = FLASHAPI_ERROR;
		FreeLibrary(hModule);
		return FALSE;
	}

	FreeLibrary(hModule);
	g_FlashAPIState = FLASHAPI_LOADED;

	return TRUE;
}

void FlashSetDirectSound(IDirectSound *pDS)
{
	if (InitFlashAPI()) {
		g_pDCFlashPlayer->SetDirectSound((LPUNKNOWN) pDS);
	}
}

void FlashIdle()
{
	if (InitFlashAPI()) {
		g_pDCFlashPlayer->Idle();
	}
}

void FlashMouseDown(int x, int y)
{
	if (InitFlashAPI()) {
		g_pDCFlashPlayer->MouseDown(x, y);
	}
}
void FlashMouseMove(int x, int y)
{
	if (InitFlashAPI()) {
		g_pDCFlashPlayer->MouseMove(x, y);
	}
}

void FlashMouseUp(int x, int y)
{
	if (InitFlashAPI()) {
		g_pDCFlashPlayer->MouseUp(x, y);
	}
}

void ShutdownFlashAPI()
{
	if (g_FlashAPIState == FLASHAPI_LOADED) {
		g_pDCFlashPlayer->Release();
		g_pDCFlashPlayer = NULL;
		g_FlashAPIState = FLASHAPI_NOT_LOADED;
	}
}

#endif // USE_FLASH
