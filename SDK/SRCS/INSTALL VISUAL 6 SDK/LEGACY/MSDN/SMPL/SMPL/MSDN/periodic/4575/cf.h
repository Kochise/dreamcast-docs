#ifndef _CF_H
#define _CF_H

extern const BOOL bIsDll;
extern void SvcLock();
extern void SvcUnlock();

class CoClassFactoryBase : public IClassFactory
{
public:
    STDMETHODIMP QueryInterface(REFIID riid, void**ppv)
    {
        if (*ppv = (riid == IID_IUnknown || riid == IID_IClassFactory) 
            ? (IClassFactory*)this : 0)
            AddRef();
        return *ppv ? S_OK : E_NOINTERFACE;
    }

    STDMETHODIMP_(ULONG) AddRef()
    {
        if (bIsDll)
            LockServer(TRUE);
        return 2;
    }

    STDMETHODIMP_(ULONG) Release()
    {
        if (bIsDll)
            LockServer(FALSE);
        return 1;
    }

    STDMETHODIMP LockServer(BOOL bLock)
    {
        if (bLock)
            SvcLock();
        else
            SvcUnlock();
        return S_OK;
    }
};


template<class CoClass>
class CoClassFactory : public CoClassFactoryBase 
{
public:
    STDMETHODIMP CreateInstance(IUnknown *pUnkOuter,
                                REFIID riid,
                                void** ppv)
    {
        *ppv = 0;
        if (pUnkOuter)
            return CLASS_E_NOAGGREGATION;
        CoClass *p = new CoClass;
        if (p == 0)
            return E_OUTOFMEMORY;
        HRESULT result = p->QueryInterface(riid, ppv);
        if (FAILED(result))
            delete p;
        return result;
    }
};

class CoSingletonClassFactory : public CoClassFactoryBase 
{
    IUnknown *m_punk;
public:
    CoSingletonClassFactory(IUnknown *punk)
    : m_punk(punk)
    {
    }

    void SetObject(IUnknown *punk)
    {
        m_punk = punk;
    }
    
    STDMETHODIMP CreateInstance(IUnknown *pUnkOuter,
                                REFIID riid,
                                void** ppv)
    {
        *ppv = 0;
        if (pUnkOuter)
            return CLASS_E_NOAGGREGATION;
        
        if (m_punk == 0)
            return E_OUTOFMEMORY;
        return m_punk->QueryInterface(riid, ppv);
    }
};

#endif
