#ifndef __CInterfaceWrap_H__
#define __CInterfaceWrap_H__

///////////////////////////////////////////////////////
//
// Definition of CUnknownWrap class
//
class CUnknownWrap
{
public:
	CUnknownWrap() ;
	~CUnknownWrap() ;

   HRESULT CreateObject(const CLSID& rCLSID);
   
   operator IUnknown*() ;

   void Attach(IUnknown* pI) ;

   void Detach() ;

   BOOL IsOK() const { return m_pI != NULL ;}

protected:
	IUnknown* m_pI ;

};


///////////////////////////////////////////////////////
//
// Definition of CInterfaceWrap class
//
template <class I, const IID* pIID>
class CInterfaceWrap 
{
public:
	CInterfaceWrap(); 
	~CInterfaceWrap();

   HRESULT CreateObject(const CLSID& rCLSID);

   operator I*() ;

   void Attach(IUnknown* pI) ;
   void Attach(I* pI) ;

   void Detach() ;

   BOOL IsOK() const { return m_pI != NULL; }

protected:
	I* m_pI ;

};

///////////////////////////////////////////////////////
//
// Implementation of CInterfaceWrap class
//

//
// Constructor
//
inline
CUnknownWrap::CUnknownWrap()
: m_pI(NULL)
{
	// Empty
}

//
// Destructor
//
inline
CUnknownWrap::~CUnknownWrap()
{
	Detach() ;
}


//
// Conversion operator - converts to IUnknown
//
inline
CUnknownWrap::operator IUnknown*()
{
   return m_pI ;
}

//
// CreateObject
//
inline
HRESULT CUnknownWrap::CreateObject(const CLSID& rCLSID )
{
   Detach() ;
   HRESULT hr = ::CoCreateInstance(rCLSID,
                                   NULL, 
                                   CLSCTX_INPROC_SERVER,
                                   IID_IUnknown,
                                   (void**)&m_pI);
  if (FAILED(hr))
  {
     TRACE("Failed to create object. SCODE: %8.8lXH (%lu)\n",
            GetScode(hr),
            GetScode(hr) & 0x0000FFFF);
  }
  return hr ;
}

//
// Attach
//

// From a generic IUnknown
inline
void CUnknownWrap::Attach(IUnknown* pI)
{
   if (m_pI != pI) // Optimization
   {
      Detach() ;
      if (pI != NULL)
      {
         // Get Controlling Unknown 
         pI->QueryInterface(IID_IUnknown, (void**)&m_pI) ;
      }
      else
      {
         m_pI = NULL ;
      }
   }
}

//
// Detach
//
inline
void CUnknownWrap::Detach()
{
   if (m_pI != NULL)
   {
      m_pI->Release() ;
      m_pI = NULL ;
   }
}


///////////////////////////////////////////////////////
//
// Implemetation of CInterfaceWrap class
//

//
// Constructor
//
template <class I, const IID* pIID> inline
CInterfaceWrap<I,pIID>::CInterfaceWrap()
: m_pI(NULL)
{
	//Empty
}

//
// Destructor
//
template <class I, const IID* pIID> inline
CInterfaceWrap<I,pIID>::~CInterfaceWrap()
{
   Detach();
}

//
// Conversion operator - converts to IUnknown
//
template <class I, const IID* pIID> inline
CInterfaceWrap<I,pIID>::operator I*()
{
   return m_pI ;
}

//
// CreateObject
//
template <class I, const IID* pIID> inline
HRESULT CInterfaceWrap<I,pIID>::CreateObject(const CLSID& rCLSID )
{
   Detach() ;
   HRESULT hr = ::CoCreateInstance(rCLSID,
                                   NULL, 
                                   CLSCTX_INPROC_SERVER,
                                   *pIID,
                                   (void**)&m_pI);
   if (FAILED(hr))
   {
      TRACE("Failed to create object. SCODE: %8.8lXH (%lu)\n",
             GetScode(hr),
             GetScode(hr) & 0x0000FFFF);
   }
   return hr ;
}

//
// Attach
//

// From a generic IUnknown
template <class I, const IID* pIID> inline
void CInterfaceWrap<I,pIID>::Attach(IUnknown* pI)
{
   if (m_pI != pI) // Optimization
   {
      Detach() ;
      if (pI != NULL)
      {
         // Get Controlling Unknown 
         pI->QueryInterface(*pIID, (void**)&m_pI) ;
      }
      else
      {
         m_pI = NULL ;
      }
   }
}

// From with same interface
template <class I, const IID* pIID> inline
void CInterfaceWrap<I,pIID>::Attach(I* pI)
{
   if (m_pI != pI) // Optimization
   {
      Detach() ;
      m_pI = pI ;

      if (m_pI != NULL)
         m_pI->AddRef() ;
   }
}


//
// Detach
//
template <class I, const IID* pIID> inline
void CInterfaceWrap<I,pIID>::Detach()
{
   if (m_pI != NULL)
   {
      m_pI->Release() ;
      m_pI = NULL ;
   }
}

#endif;