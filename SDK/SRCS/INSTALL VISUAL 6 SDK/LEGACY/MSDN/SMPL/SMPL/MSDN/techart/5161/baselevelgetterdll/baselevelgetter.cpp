// BaseLevelGetter.cpp : implementation file
//

#include "stdafx.h"
#include "BaseLevelGetterDLL.h"
#include "BaseLevelGetter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BaseLevelGetter

IMPLEMENT_DYNCREATE(BaseLevelGetter, CCmdTarget)

BEGIN_MESSAGE_MAP(BaseLevelGetter, CCmdTarget)
	//{{AFX_MSG_MAP(BaseLevelGetter)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(BaseLevelGetter, CCmdTarget)
	//{{AFX_DISPATCH_MAP(BaseLevelGetter)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

//Here is our CLSID
// {C20EA055-F61C-11D0-A25F-000000000000}
IMPLEMENT_OLECREATE(BaseLevelGetter, "BaseLevelGetterDLL.BaseLevelGetter", 0xc20ea055, 0xf61c, 0x11d0, 0xa2, 0x5f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0)

// Note: we add support for IID_IBaseLevelGetter to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {C20EA054-F61C-11D0-A25F-000000000000}
static const IID IID_IBaseLevelGetter =
{ 0xc20ea054, 0xf61c, 0x11d0, { 0xa2, 0x5f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } };


BEGIN_INTERFACE_MAP(BaseLevelGetter, CCmdTarget)
	INTERFACE_PART(BaseLevelGetter, IID_IBaseLevelGetter, Dispatch)
	INTERFACE_PART(BaseLevelGetter, IID_ILevelGetter, LevelGetter)
END_INTERFACE_MAP()

//-----------------------------------------------------------------------------
BaseLevelGetter::BaseLevelGetter()
{
	EnableAutomation();
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	m_xLevelGetter.SetOwner(this);
}

BaseLevelGetter::~BaseLevelGetter()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	AfxOleUnlockApp();
}

void BaseLevelGetter::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.
	CCmdTarget::OnFinalRelease();
}

//---------------------------------------------------------------------
HRESULT FAR EXPORT BaseLevelGetter::XLevelGetter::QueryInterface
(
	REFIID  iid, 
	LPVOID* ppvObj
)
{
	METHOD_PROLOGUE_EX_(BaseLevelGetter, LevelGetter)
	return (HRESULT) pThis->ExternalQueryInterface(&iid, ppvObj);
}


//---------------------------------------------------------------------
ULONG FAR EXPORT BaseLevelGetter::XLevelGetter::AddRef()
{
	METHOD_PROLOGUE_EX_(BaseLevelGetter, LevelGetter)
	return (ULONG) pThis->ExternalAddRef();
}

//---------------------------------------------------------------------
ULONG FAR EXPORT BaseLevelGetter::XLevelGetter::Release()
{
	METHOD_PROLOGUE_EX_(BaseLevelGetter, LevelGetter)
	return (ULONG) pThis->ExternalRelease();
}

//---------------------------------------------------------------------
STDMETHODIMP BaseLevelGetter::XLevelGetter::GetCurrentLevel
(
    long* plCurrentLevel
)
{
	METHOD_PROLOGUE_EX_(BaseLevelGetter, LevelGetter)
	//call outer object's GetCurrentLevel
	//whether this class or a derived class
	*plCurrentLevel = pThis->GetCurrentLevel();
    return S_OK;
}

//---------------------------------------------------------------------
STDMETHODIMP BaseLevelGetter::XLevelGetter::GetHighestPossibleSafeLevel
(
	long* plHighestSafeLevel
)
{
	METHOD_PROLOGUE_EX_(BaseLevelGetter, LevelGetter)
	//call outer object's GetHighestSafeLevel
	//whether this class or a derived class
	*plHighestSafeLevel = pThis->GetHighestSafeLevel();
    return S_OK;
}

//---------------------------------------------------------------------
STDMETHODIMP BaseLevelGetter::XLevelGetter::GetLowestPossibleSafeLevel
(
	long* plLowestSafeLevel
)
{
	METHOD_PROLOGUE_EX_(BaseLevelGetter, LevelGetter)
	//call outer object's GetLowestSafeLevel
	//whether this class or a derived class
	if( m_pOwner != NULL)
	{
		*plLowestSafeLevel = m_pOwner->GetHighestSafeLevel();
	}
	else
	{
		ASSERT(FALSE);
	}
    return S_OK;
}

//---------------------------------------------------------------------
STDMETHODIMP BaseLevelGetter::XLevelGetter::GetTextMessage
(
	BSTR* ppbstrMessage
)
{
	METHOD_PROLOGUE_EX_(BaseLevelGetter, LevelGetter)
	//call outer object's GetMessage
	//whether this class or a derived class
	CString sMessage;
	if( m_pOwner != NULL)
	{
		sMessage = m_pOwner->GetMessage();
	}
	else
	{
		ASSERT(FALSE);
	}

	*ppbstrMessage = sMessage.AllocSysString();
    return S_OK;
}

//---------------------------------------------------------------------
long BaseLevelGetter::GetCurrentLevel()
{
	TRACE("Derived classes should override!");
	return -1;
}

//---------------------------------------------------------------------
long BaseLevelGetter::GetHighestSafeLevel()
{
	TRACE("Derived classes should override!");
	return -1;
}

//---------------------------------------------------------------------
long BaseLevelGetter::GetLowestSafeLevel()
{
	TRACE("Derived classes should override!");
	return -1;
}

//---------------------------------------------------------------------
CString BaseLevelGetter::GetMessage()
{
	TRACE("Derived classes should override!");
	return "BaseLevelGetter";
}
