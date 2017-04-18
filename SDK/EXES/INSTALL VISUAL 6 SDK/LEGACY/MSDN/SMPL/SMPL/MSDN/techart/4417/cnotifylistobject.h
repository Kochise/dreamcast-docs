#ifndef __CNotifyListObject_H__
#define __CNotifyListObject_H__

class CNotifyListObject : 	public CUnknown,
							      public INotifySrc
{
public:
	// Delegating IUnknown
	DECLARE_IUNKNOWN ;

	// Called by ClassFactory
	static CUnknown* CreateInstance(IUnknown* pUnk, HRESULT* phr) ;

	// Overload To support INotifySrc
	virtual HRESULT __stdcall NonDelegatingQueryInterface(REFIID riid, void** ppv) ;

	// INotifySrc Interface Implementation
    STDMETHODIMP AddUser(INotify* pNotify, LPVOID pUserInfo);
    STDMETHODIMP RemoveUser(INotify* pNotify);
    STDMETHODIMP NotifyAll() ;

protected:
	// Constructor
	CNotifyListObject(IUnknown* pUnk, HRESULT* phr) ;

	// Destructor
	virtual ~CNotifyListObject() ;

protected:	
	// Notification info class
	class CUserInfo
	{
	public:
		INotify* pNotify;
		LPVOID pUserInfo;
	};

	// List Object
    CTypedPtrList<CPtrList, CUserInfo*> m_NotifyList;
};

#endif //__CNotifyListObject_H__
