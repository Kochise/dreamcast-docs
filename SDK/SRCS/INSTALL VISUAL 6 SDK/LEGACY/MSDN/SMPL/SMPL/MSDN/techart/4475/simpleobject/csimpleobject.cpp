#include "stdafx.h"
#include "GUIDS.h"
#include "ISimple.h"
#include "CSimpleObject.h"

//
// Count of active objects. Use to determine if we can unload the DLL.
//
LONG CSimpleObject::m_ObjectCount = 0;

//
// CreateInstance is called by CClassFactory
//
CSimpleObject* CSimpleObject::CreateInstance(IUnknown* pUnk, HRESULT* phr)
{
   if (pUnk != NULL)
   {
      // Aggreation is not supported.
      *phr = CLASS_E_NOAGGREGATION ;
      return NULL;
   }

	CSimpleObject* pNewObject = new CSimpleObject(phr);
	if (pNewObject == NULL)
   {
		*phr = E_OUTOFMEMORY ;
   }

   return pNewObject ;
}

//
// Constructor
//
CSimpleObject::CSimpleObject(HRESULT* phr) 
{
	InterlockedIncrement(&m_ObjectCount) ;

	m_RefCount = 0 ;

   phr = NO_ERROR;
} 

//
// Destructor
//
CSimpleObject::~CSimpleObject()
{
	InterlockedDecrement(&m_ObjectCount) ;
}

//
// NonDelegatingIUnknown - Override to handle custom interfaces.
//
HRESULT __stdcall CSimpleObject::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
	{
      *ppv = (void*)this ;
	}	
   else if (riid == IID_ISimple)
   {
      *ppv = (void*)this ;
   }
	else
	{
		return E_NOINTERFACE ;
	}

   ((IUnknown*)*ppv)->AddRef() ;
   return NOERROR ;
}

//
// AddRef
//
ULONG __stdcall CSimpleObject::AddRef()
{
	LONG lRef = InterlockedIncrement(&m_RefCount) ;
	ASSERT(lRef > 0) ;
	return (ULONG)lRef ;
}

//
// Release
//
ULONG __stdcall CSimpleObject::Release()
{
	LONG lRef = InterlockedDecrement(&m_RefCount) ;
	ASSERT(lRef >= 0) ;
	if (lRef == 0)
	{
		delete this ;
		return (ULONG) 0 ;
	}
	else
	{
		return (ULONG) lRef ;
	}
}


