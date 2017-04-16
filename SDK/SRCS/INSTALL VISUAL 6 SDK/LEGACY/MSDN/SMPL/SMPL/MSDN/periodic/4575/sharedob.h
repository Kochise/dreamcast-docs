/////////////////////////////////////////////////////////////
//
// SharedObj.h - Copyright 1996, Don Box
//

#ifndef _SHAREDOBJ_H
#define _SHAREDOBJ_H

// we need the placement operator
#include <new.h>

// CoSharedObjectBase is a non-template base class that implements 
// most of the custom marshaling code to share a memory section in 
// a thread-safe fashion

class CoSharedObjectBase : private IMarshal {
// handle to mutex that protects the shared
// data members
    HANDLE m_hmutex;

// handle to section object that contains 
// shared data members
    HANDLE m_hsection;

// pointer to shared data member(s)
    void *m_pvData;

// unique GUID that "names" the 2 shared Win32
// kernel objects
    GUID m_guid;

// normal COM refcount
    ULONG m_cRef;

// helper function to attach to section object
    BOOL AttachToSection(DWORD dwTimeOut = INFINITE);

    struct SECTIONHEADER;
    SECTIONHEADER *GetSectionHeader();
    void *GetSectionData();

// Virtual upcalls that allow derived client to construct/destroy 
// shared data members
    virtual BOOL OnInitializeSection(void *pv) = 0;
    virtual void OnDestroySection(void *pv) = 0;

// Virtual upcalls that are used to find the size of the shared 
// data members and the CLSID of this class
    virtual DWORD OnGetSize() = 0;
    virtual const CLSID& OnGetCLSID() = 0;

// IMarshal members
    STDMETHODIMP GetUnmarshalClass( REFIID riid,	
                                    void * pv,	
                                    DWORD dwDestCtx,
                                    void * pvDestCtx,
                                    DWORD mshlflags,
                                    CLSID * pclsid);

    STDMETHODIMP GetMarshalSizeMax( REFIID riid,	
                                    void * pv,	
                                    DWORD dwDestCtx,
                                    void * pvDestCtx,
                                    DWORD mshlflags,
                                    ULONG *pcb);

    STDMETHODIMP MarshalInterface(  IStream *pStm,
                                    REFIID riid,
                                    void *pv,
                                    DWORD dwDestCtx,
                                    void *pvDestCtx,
                                    DWORD mshlflags);

    STDMETHODIMP UnmarshalInterface(IStream * pStm,
                                    REFIID riid,
                                    void ** ppv);

    STDMETHODIMP ReleaseMarshalData(IStream * pStm);

    STDMETHODIMP DisconnectObject(DWORD dwReserved);
protected:
// IUnknown members (protected to allow forwarding)
    STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

// Lock/Unlock the shared data
    void *AccessSharedData(DWORD dwTimeOut = INFINITE);
    void  ReleaseSharedData();

    CoSharedObjectBase();
    virtual ~CoSharedObjectBase();
};


// CoSharedObject is a template class that implements a handler
// that accesses a shared data structure (SharedState) and implements
// one COM interface (beyond IMarshal)

template <  class SharedState,     // the shared data
			const CLSID *pclsid,   // this CLSID
            interface IUser,       // Primary Interface
			const IID* PIID_IUser  // Primary IID
		 >
class CoSharedObject :  private CoSharedObjectBase, 
                        public  IUser {
private:
// default implementation uses placement version
// of new to construct the object "in place"
    virtual BOOL OnInitializeSection(void *pv) {
        new (pv) SharedState;
        return TRUE;
    }

// default implementation calls destructor explicitly
// to destruct the object "in place"
    virtual void OnDestroySection(void *pv)  {
        ((SharedState*)pv)->~SharedState();
    }

// default implementation returns the size of the 
// data members without chasing pointer members
    virtual DWORD OnGetSize() {
        return sizeof(SharedState);
    }
    
// simply return the template paramter
    virtual const CLSID& OnGetCLSID() {
        return *pclsid;
    }
    
protected:
// SharedThis is a helper class that aquires the mutex in
// an exception-safe fashion.  Declare an instance of SharedThis
// at the beginning of each member function of your derived class
// to access the shared data members of your object

    class SharedThis {
        CoSharedObject *m_phandler;
        SharedState *m_pthis;
    public:
        SharedThis(CoSharedObject *pt, DWORD dwTimeOut = INFINITE) 
        :   m_phandler(pt),
            m_pthis(0)
        {
            m_pthis = (SharedState*)pt->AccessSharedData(dwTimeOut);
        }

        ~SharedThis()
        {
			if (m_pthis)
				m_phandler->ReleaseSharedData();
        }

        operator SharedState * () { return m_pthis; }
        SharedState * operator -> () { return m_pthis; }
    };
    friend class SharedThis;

public:

// hook QI to expose the new interface
    STDMETHODIMP QueryInterface(REFIID riid, void**ppv) {
        if (riid == *PIID_IUser) {
            LPUNKNOWN(*ppv = (IUser*)this)->AddRef();
            return S_OK;
        }
        return CoSharedObjectBase::QueryInterface(riid, ppv);
    }
    
// use default AddRef and Release
    STDMETHODIMP_(ULONG) AddRef() {
        return CoSharedObjectBase::AddRef();
    }

    STDMETHODIMP_(ULONG) Release() {
        return CoSharedObjectBase::Release();
    }

};

#endif
