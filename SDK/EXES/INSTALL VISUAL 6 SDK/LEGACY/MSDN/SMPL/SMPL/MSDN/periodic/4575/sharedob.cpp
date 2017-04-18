/////////////////////////////////////////////////////////////
//
// SharedObj.cpp - Copyright 1996, Don Box
//

#include <windows.h>
#include "sharedobj.h"

// standard module lifetime functions (defined elsewhere)
extern void SvcLock();
extern void SvcUnlock();

// header for shared memory section
struct CoSharedObjectBase::SECTIONHEADER {
// shared ref count
    DWORD m_cRef;
// padding
    DWORD m_reserved;
};

// the header resides at the beginning of the section
inline CoSharedObjectBase::SECTIONHEADER *
CoSharedObjectBase::GetSectionHeader() {
    return (SECTIONHEADER*)m_pvData;
}

// the payload resides immediately after the header, so use 
// the magic of pointer arithmetic to find its address
inline void *
CoSharedObjectBase::GetSectionData() {
    return GetSectionHeader() + 1;
}

// initialize data members to null and lock the server module
CoSharedObjectBase::CoSharedObjectBase()
:   m_hmutex(0),
    m_hsection(0),
    m_pvData(0),
    m_cRef(0)
{
    SvcLock();
}

// close all handles and unlock the server module
CoSharedObjectBase::~CoSharedObjectBase() {
    if (m_hsection) {
        UnmapViewOfFile(m_pvData);
        CloseHandle(m_hsection);
    }

    if (m_hmutex)
        CloseHandle(m_hmutex);
    SvcUnlock();
}


// helper function to create or open section object and mutex
BOOL 
CoSharedObjectBase::AttachToSection(DWORD dwTimeOut)
{
// synthesize section and mutex name based on guid value,(e.g., 
// "{12345678-0000-0000-0000-DEAD00000000}_MTX" for the mutex
// "{12345678-0000-0000-0000-DEAD00000000}_SCT" and for the section

    TCHAR szSectionName[128];
    TCHAR szMutexName[128];
    OLECHAR szGUID[128];

// m_guid acts as the object ID in this usage
    StringFromGUID2(m_guid, szGUID, sizeof(szGUID));

#ifdef UNICODE
    lstrcpy(szSectionName, szGUID);
#else
    wcstombs(szSectionName, szGUID, sizeof(szSectionName));
#endif

    lstrcpy(szMutexName, szSectionName);
    lstrcat(szMutexName, TEXT("_MTX"));
    lstrcat(szSectionName, TEXT("_SCT"));

// Create/open the mutex, ascertain "firstness" and grab the mutex
    m_hmutex = CreateMutex(0, FALSE, szMutexName);
    BOOL bFirst = GetLastError() != ERROR_ALREADY_EXISTS;
    WaitForSingleObject(m_hmutex, dwTimeOut);

// create/open a section big enough to hold shared state and 
// header, then map it into address space
    m_hsection = CreateFileMapping(HANDLE(0xFFFFFFFF),
                                   0, 
                                   PAGE_READWRITE,
                                   0,
                                   sizeof(SECTIONHEADER) + OnGetSize(),
                                   szSectionName);

    m_pvData = MapViewOfFile(m_hsection,
                             FILE_MAP_ALL_ACCESS,
                             0,0,0);
        
	if (bFirst)
    {
// set shared ref count to one and initialize payload of section via
// the virtual function OnInitializeSection
        GetSectionHeader()->m_cRef = 1;
        OnInitializeSection(GetSectionData());
    }
    else
    {
// simply bump the shared ref count
        GetSectionHeader()->m_cRef++;
    }

    ReleaseMutex(m_hmutex);
    return TRUE;
}


// IUnknown members
STDMETHODIMP 
CoSharedObjectBase::QueryInterface(REFIID riid, void **ppv)
{
    if (riid == IID_IUnknown || riid == IID_IMarshal)
        LPUNKNOWN(*ppv = (IMarshal*)this)->AddRef();
    else
        *ppv = 0;
    return *ppv ? S_OK : E_NOINTERFACE;
}

STDMETHODIMP_(ULONG) 
CoSharedObjectBase::AddRef()
{
    return ++m_cRef;
}

STDMETHODIMP_(ULONG) 
CoSharedObjectBase::Release()
{
    ULONG result = --m_cRef;
    if (result == 0)
    {
// We must detach from section prior to destruction
// in order to get the appropriate virtual function
// called (we can't call OnDestroySection in our destructor)

        WaitForSingleObject(m_hmutex, INFINITE);
        if (--GetSectionHeader()->m_cRef == 0)
            OnDestroySection(GetSectionData()); 
        ReleaseMutex(m_hmutex);

        delete this;
    }
    return result;
}

// IMarshal members

// GetUnmarshalClass uses the virtual upcall OnGetCLSID to
// ascertain the classname of the handler.  Marshaling contexts
// that do not support shared memory simply fail

STDMETHODIMP 
CoSharedObjectBase::GetUnmarshalClass(  REFIID riid,	
                                        void * pv,	
                                        DWORD dwDestCtx,
                                        void * pvDestCtx,
                                        DWORD mshlflags,
                                        CLSID * pclsid)
{
    SCODE result = E_FAIL;
    if (dwDestCtx == MSHCTX_LOCAL ||
        dwDestCtx == MSHCTX_INPROC)
    {
        *pclsid = OnGetCLSID();
        result = S_OK;
    }
    return result;
}

// Since we only send the object ID (m_guid) in the marshaling
// packet, we hard code the size to sizeof(GUID) 

STDMETHODIMP 
CoSharedObjectBase::GetMarshalSizeMax( REFIID riid,	
                                        void * pv,	
                                        DWORD dwDestCtx,
                                        void * pvDestCtx,
                                        DWORD mshlflags,
                                        ULONG *pcb)
{
    SCODE result = E_FAIL;
    if (dwDestCtx == MSHCTX_LOCAL ||
        dwDestCtx == MSHCTX_INPROC)
    {
        *pcb = sizeof(GUID);
        result = S_OK;
    }
    return result;
}


// We transmit the object ID (m_guid) through the stream
// using WriteClassStm

STDMETHODIMP 
CoSharedObjectBase::MarshalInterface(  IStream *pStm,
                                        REFIID riid,
                                        void *pv,
                                        DWORD dwDestCtx,
                                        void *pvDestCtx,
                                        DWORD mshlflags)
{
    SCODE result = E_FAIL;
    if (dwDestCtx == MSHCTX_LOCAL ||
        dwDestCtx == MSHCTX_INPROC)
    {
        WriteClassStm(pStm, m_guid);
        result = S_OK;
    }
    return result;
}

// We receive the object ID (m_guid) from the stream
// using ReadClassStm and attach to the shared section
// that the object ID names

STDMETHODIMP 
CoSharedObjectBase::UnmarshalInterface(IStream * pStm,
                                        REFIID riid,
                                        void ** ppv)
{
    *ppv = 0;
    ReadClassStm(pStm, &m_guid);
    if (AttachToSection())
        return this->QueryInterface(riid, ppv);
    else
        return E_FAIL;
}

// since we allocate no new resources in our marshaling code,
// there is no need to implement anything interesting 
// in this function

STDMETHODIMP 
CoSharedObjectBase::ReleaseMarshalData(IStream * pStm)
{
// seek past our portion of the marshaling packet
    LARGE_INTEGER li;
    LISet32(li, sizeof(m_guid));
    pStm->Seek(li, STREAM_SEEK_CUR, 0);
    return S_OK;
}

// For the simple case, we do not want the handler to disconnect

STDMETHODIMP 
CoSharedObjectBase::DisconnectObject(DWORD dwReserved)
{
    return S_OK;
}


// AccessSharedData allows derived clients to acquire the mutex. If the
// section has not been mapped, then this is the first access to the object
// and causes the object ID to be generated using CoCreateGuid
// This function and AttachToSection perform most of the work of this class.

void *
CoSharedObjectBase::AccessSharedData(DWORD dwTimeOut)
{
// test for first access to first handler
    if (m_pvData == 0)
    {
        CoCreateGuid(&m_guid);
        if (!AttachToSection(dwTimeOut))
            return 0;
    }

    if (WaitForSingleObject(m_hmutex, dwTimeOut) == WAIT_OBJECT_0)
        return GetSectionData();
    else
        return 0;
}

// simply release the mutex

void  
CoSharedObjectBase::ReleaseSharedData()
{
    ReleaseMutex(m_hmutex);
}

