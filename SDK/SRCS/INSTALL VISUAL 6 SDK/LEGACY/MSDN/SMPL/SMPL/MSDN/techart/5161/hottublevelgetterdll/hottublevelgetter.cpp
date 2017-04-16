// HotTubLevelGetter.cpp : implementation file
//

#include "stdafx.h"
#include "HotTubLevelGetterDLL.h"
#include "HotTubLevelGetter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// HotTubLevelGetter

IMPLEMENT_DYNCREATE(HotTubLevelGetter, BaseLevelGetter)

HotTubLevelGetter::HotTubLevelGetter()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

HotTubLevelGetter::~HotTubLevelGetter()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}


void HotTubLevelGetter::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	BaseLevelGetter::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(HotTubLevelGetter, BaseLevelGetter)
	//{{AFX_MSG_MAP(HotTubLevelGetter)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(HotTubLevelGetter, BaseLevelGetter)
	//{{AFX_DISPATCH_MAP(HotTubLevelGetter)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IHotTubLevelGetter to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {34CA0A51-F81C-11D0-8FE8-00409500EFA8}
static const IID IID_IHotTubLevelGetter =
{ 0x34ca0a51, 0xf81c, 0x11d0, { 0x8f, 0xe8, 0x0, 0x40, 0x95, 0x0, 0xef, 0xa8 } };

BEGIN_INTERFACE_MAP(HotTubLevelGetter, BaseLevelGetter)
	INTERFACE_PART(HotTubLevelGetter, IID_IHotTubLevelGetter, Dispatch)
END_INTERFACE_MAP()

// {34CA0A52-F81C-11D0-8FE8-00409500EFA8}
IMPLEMENT_OLECREATE(HotTubLevelGetter, "HotTubLevelGetterDLL.HotTubLevelGetter", 0x34ca0a52, 0xf81c, 0x11d0, 0x8f, 0xe8, 0x0, 0x40, 0x95, 0x0, 0xef, 0xa8)

/////////////////////////////////////////////////////////////////////////////
// HotTubLevelGetter message handlers
