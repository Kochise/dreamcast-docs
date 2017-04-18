// MI_Appliances.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "combase.h"
#include "MI_Appliances.h"

#include "combase.h"
#include "..\include\idrawing.h"
#include "..\include\ioutlet.h"
#include "CLightBulb.h"

#include "..\include\inotify.h"
#include "..\include\inotifysrc.h"
#include "CNotifyListObject.h"

#include "..\include\ibitmap.h"
#include "CBitmapObject.h"

#include "..\include\ilight.h"
#include "CStandardLamp.h"

#include "..\include\iapplianceui.h"
#include "CRadio.h"

#include "CTelevision.h"

#include "..\include\appliancesid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Globals for COMBASE
CFactoryTemplate g_Templates[] =
{
	{&CLSID_LightBulb, 			CLightBulb::CreateInstance},
	{&CLSID_NotifyListObject, 	CNotifyListObject::CreateInstance},
	{&CLSID_BitmapObject, 		CBitmapObject::CreateInstance},
	{&CLSID_StandardLamp, 		CStandardLamp::CreateInstance},
	{&CLSID_Television,			CTelevision::CreateInstance},
	{&CLSID_Radio,				CRadio::CreateInstance}
} ;
int g_cTemplates = sizeof(g_Templates) / sizeof(g_Templates[0]) ;



/////////////////////////////////////////////////////////////////////////////
// CMI_AppliancesApp

BEGIN_MESSAGE_MAP(CMI_AppliancesApp, CWinApp)
	//{{AFX_MSG_MAP(CMI_AppliancesApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

CMI_AppliancesApp::CMI_AppliancesApp()
{
}

/////////////////////////////////////////////////////////////////////////////

CMI_AppliancesApp theApp;

/////////////////////////////////////////////////////////////////////////////

BOOL CMI_AppliancesApp::InitInstance()
{
	// DER - COleObjectFactory::RegisterAll();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Special entry points required for inproc servers

#if (_MFC_VER >= 0x300)
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	//DER - return AfxDllGetClassObject(rclsid, riid, ppv);
	return CClassFactory::GetClassObject(rclsid, riid, ppv);
}

STDAPI DllCanUnloadNow(void)
{
	//DER - return AfxDllCanUnloadNow();
	return CClassFactory::CanUnloadNow();
}
#endif

#if 0 //DER

//DER -- REMOVE FROM THE DEF FILE !!!!!

// by exporting DllRegisterServer, you can use regsvr.exe
STDAPI DllRegisterServer(void)
{
	COleObjectFactory::UpdateRegistryAll();
	return S_OK;
}
#endif
