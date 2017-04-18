// notifyob.cpp : implementation file
//

#include "stdafx.h"
#include "appliances.h"
#include "..\include\impiunk.h"
#include "..\include\inotify.h"
#include "..\include\inotifysrc.h"
#include "notifyob.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNotifyListObject

IMPLEMENT_DYNCREATE(CNotifyListObject, CCmdTarget)

CNotifyListObject::CNotifyListObject()
{
	EnableAutomation();

    // Make this object aggregatable
    EnableAggregation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

CNotifyListObject::~CNotifyListObject()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}

void CNotifyListObject::OnFinalRelease()
{
    // Make sure the notification list has all its
    // entires removed
    while (!m_NotifyList.IsEmpty()) {
        CUserInfo* pInfo = (CUserInfo*)m_NotifyList.RemoveHead();
        ASSERT(pInfo);
        pInfo->pNotify->Release();
        delete pInfo;
    }

	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}


BEGIN_MESSAGE_MAP(CNotifyListObject, CCmdTarget)
	//{{AFX_MSG_MAP(CNotifyListObject)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CNotifyListObject, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CNotifyListObject)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_OLECREATE(CNotifyListObject, "NotifyListObject", 0xe6a59af0, 0x532e, 0x11ce, 0x9e, 0xf1, 0x0, 0xaa, 0x0, 0x42, 0x31, 0xbf)

BEGIN_INTERFACE_MAP(CNotifyListObject, CCmdTarget)
    INTERFACE_PART(CNotifyListObject, IID_INotifySrc, NotifySrc)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////
// INotifySrc interface

// IUnknown for INotifySrc
    IMPLEMENT_IUNKNOWN(CNotifyListObject, NotifySrc)

// INotifySrc methods
STDMETHODIMP CNotifyListObject::XNotifySrc::AddUser(INotify* pNotify,
                                                    LPVOID pUserInfo)
{
    METHOD_PROLOGUE(CNotifyListObject, NotifySrc);
    if (!pNotify) return E_INVALIDARG;

    // Save the user's INotify interface and info
    pNotify->AddRef();
    CUserInfo* pInfo = new CUserInfo;
    ASSERT(pInfo);
    pInfo->pNotify = pNotify;
    pInfo->pUserInfo = pUserInfo;
    pThis->m_NotifyList.AddTail((CObject*)pInfo);

    return NOERROR;
}

STDMETHODIMP CNotifyListObject::XNotifySrc::RemoveUser(INotify* pNotify)
{
    METHOD_PROLOGUE(CNotifyListObject, NotifySrc);
    if (!pNotify) return E_INVALIDARG;

    // Find this one in the list
    POSITION pos = pThis->m_NotifyList.GetHeadPosition();
    POSITION pfnd = NULL;
    CUserInfo* pInfo = NULL;
    while (pos) {
        pfnd = pos;
        pInfo = (CUserInfo*)pThis->m_NotifyList.GetNext(pos);
        if (pInfo->pNotify == pNotify) break;
    }
    if (!pfnd) return E_INVALIDARG; // not found

    // remove it from the list and delete the info object
    pThis->m_NotifyList.RemoveAt(pfnd);
    delete pInfo;

    // Say we're done with the users interface now
    pNotify->Release();

    return NOERROR;
}

STDMETHODIMP CNotifyListObject::XNotifySrc::NotifyAll()
{
    METHOD_PROLOGUE(CNotifyListObject, NotifySrc);

    // Walk the notification list
    POSITION pos = pThis->m_NotifyList.GetHeadPosition();
    while(pos) {
        CUserInfo* pInfo = (CUserInfo*)pThis->m_NotifyList.GetNext(pos);
        ASSERT(pInfo && pInfo->pNotify);

        // Report the change of state
        pInfo->pNotify->Change(pInfo->pUserInfo);
    }

    return NOERROR;
}
