#include "stdafx.h"
#include "combase.h"
#include "..\include\inotify.h"
#include "..\include\inotifysrc.h"
#include "resource.h"
#include "CNotifyListObject.h"


//
// Constructor
//
CNotifyListObject::CNotifyListObject(IUnknown* pUnk, HRESULT* phr)
	: CUnknown(pUnk, phr) 
{

}

//
// Destructor
//
CNotifyListObject::~CNotifyListObject()
{
    // Make sure the notification list has all its
    // entires removed
    while (!m_NotifyList.IsEmpty())
    {
        CUserInfo* pInfo = m_NotifyList.RemoveHead();
        ASSERT(pInfo);
        pInfo->pNotify->Release();
        delete pInfo;
    }
}

//
// CreateInstance is called by CClassFactory
//
CUnknown* CNotifyListObject::CreateInstance(IUnknown* pUnk, HRESULT* phr)
{
	CNotifyListObject* pNewObject = new CNotifyListObject(pUnk, phr) ;
	if (pNewObject == NULL)
		*phr = E_OUTOFMEMORY ;

	return pNewObject ;
}

// Overload To support INotifySrc
HRESULT CNotifyListObject::NonDelegatingQueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_INotifySrc)
		return GetInterface((INotifySrc*)this, ppv) ;
	else
		return CUnknown::NonDelegatingQueryInterface(riid, ppv) ;
}

//
//
// INotifySrc Interface Implementation
//
//

//
// AddUser
//
STDMETHODIMP CNotifyListObject::AddUser(INotify* pNotify, LPVOID pUserInfo)
{
    if (!pNotify) return E_INVALIDARG;

    // Save the user's INotify interface and info
    pNotify->AddRef();
    CUserInfo* pInfo = new CUserInfo;
    ASSERT(pInfo);
    pInfo->pNotify = pNotify;
    pInfo->pUserInfo = pUserInfo;
    m_NotifyList.AddTail(pInfo);

    return NOERROR;
} 

//
// RemoveUser
//
STDMETHODIMP CNotifyListObject::RemoveUser(INotify* pNotify)
{
    if (!pNotify) return E_INVALIDARG;

    // Find this one in the list
    POSITION pos = m_NotifyList.GetHeadPosition();
    POSITION pfnd = NULL;
    CUserInfo* pInfo = NULL;
    while (pos) {
        pfnd = pos;
        pInfo = m_NotifyList.GetNext(pos);
        if (pInfo->pNotify == pNotify) break;
    }
    if (!pfnd) return E_INVALIDARG; // not found

    // remove it from the list and delete the info object
    m_NotifyList.RemoveAt(pfnd);
    delete pInfo;

    // Say we're done with the users interface now
    pNotify->Release();

    return NOERROR;
}

//
// NotifyAll
//
STDMETHODIMP CNotifyListObject::NotifyAll()
{
    // Walk the notification list
    POSITION pos = m_NotifyList.GetHeadPosition();
    while(pos) {
        CUserInfo* pInfo = m_NotifyList.GetNext(pos);
        ASSERT(pInfo && pInfo->pNotify);

        // Report the change of state
        pInfo->pNotify->Change(pInfo->pUserInfo);
    }

    return NOERROR;
}
