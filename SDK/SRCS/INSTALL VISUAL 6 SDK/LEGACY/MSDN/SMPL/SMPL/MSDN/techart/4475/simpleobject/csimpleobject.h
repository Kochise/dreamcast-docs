#ifndef __CSimpleObject__
#define __CSimpleObject__

class CSimpleObject : public ISimple
{
public:
	// IUnknown
    STDMETHODIMP QueryInterface(REFIID riid, void** ppv);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

   // ISimple
   virtual void __stdcall  SetCount(int count)  {m_theSimpleCount = count;}
   virtual int __stdcall   GetCount() {return m_theSimpleCount ;}
   virtual void __stdcall  Inc() {m_theSimpleCount++ ; }

  	// Constructor
	CSimpleObject(HRESULT* phr) ;

	// Destructor
	virtual ~CSimpleObject() ;

	// Support for delegation
	IUnknown* GetOwner() const
		{ return m_pUnkOwner; }

	// CreateInstance --- Define in derived classes 
	static CSimpleObject* CreateInstance(IUnknown* pUnk, HRESULT* phr);

	static LONG ObjectsActive() 
		{return m_ObjectCount;}

	
private:
	IUnknown* m_pUnkOwner ;
	static LONG m_ObjectCount ; // Count of active objects.

   int m_theSimpleCount ;

protected:
	LONG m_RefCount ;
};
#endif