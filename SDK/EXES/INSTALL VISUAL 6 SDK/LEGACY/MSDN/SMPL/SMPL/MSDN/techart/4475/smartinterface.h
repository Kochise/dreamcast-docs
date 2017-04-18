#ifndef __CSmartInterface__
#define __CSmartInterface__

//#define Release DONT_CALL_RELEASE

template <class I>
class CSmartInterface
{
public:
   // Construction
   CSmartInterface(I* pI = NULL) ;

   // Copy Constructor
   CSmartInterface(const CSmartInterface<I>& rSI) ;
   
   // Destruction
   ~CSmartInterface() ;

   //
   // Assignment Operators
   //

   // from I*
   CSmartInterface<I>& operator=(I* pI) ;

   //
   // Operators
   //

   // Conversion
   operator I*() ;

   // Deref
   I* operator->() ;

   // Address of
   I** operator&() ;

   // Equality
   BOOL operator==(I* pI) const;

   // In-equality
   BOOL operator!=(I* pI) const;

   // Negation
   BOOL operator!() const ;

#if 0
   //
   // Release
   //
   ULONG Release() ;
#endif

protected:
   I* m_pI ;
};

//////////////////////////////////////////////////////////////////////////
//
// Inline Implementations
//

//
// Constructor
//
 
template <class I> inline
CSmartInterface<I>::CSmartInterface(I* pI /*=NULL*/)
   : m_pI(pI)
{
   TRACE0("SmartInterface Ctor\r\n") ;
   if (m_pI != NULL) 
   {
      // AddRef if we are copying an existing interface pointer.
      m_pI->AddRef() ;
   }
} 

//
// Copy Constructor
//
template <class I> inline
CSmartInterface<I>::CSmartInterface(const CSmartInterface<I>& rSI)
: m_pI(rSI.m_pI)
{
	if (m_pI != NULL)
		m_pI->AddRef() ;
}

//
// Destructor
//
template <class I> inline 
CSmartInterface<I>::~CSmartInterface()
{
   TRACE0("SmartInterface Dtor\r\n") ;
   if (m_pI != NULL)
   {
      m_pI->Release();
   }
}

//
// Assignment
//
template <class I> inline 
CSmartInterface<I>& CSmartInterface<I>::operator=(I* pI)
{
   TRACE0("Assignment from I*\r\n") ;
   if (m_pI != pI) //OPTOMIZE Only need to AddRef/Release if difference
   {
      if (m_pI != NULL)
         m_pI->Release() ; //Smart Pointers don't use smart pointers :-)
      
      m_pI = pI ;

      if (m_pI != NULL)
         m_pI->AddRef() ;
   }      
   return *this ;
}



//
// Conversion Operator -  Needed for cases like ASSERT(pIDrawing)
//
template <class I> inline 
CSmartInterface<I>::operator I*()
{ 
   TRACE0("Conversion operator\r\n") ;
   return m_pI;
} 

//
// Dereference : operator ->
//
template <class I> inline 
I* CSmartInterface<I>::operator->()
{
   TRACE0("operartor ->\r\n") ;
   ASSERT(m_pI != NULL) ;
   return m_pI ;
}

//
// Address : operator &
//
template <class I> inline 
I** CSmartInterface<I>::operator&()
{
   TRACE0("operator & \r\n") ;
   // The Address of a pointer is a pointer pointer
   return &m_pI ;
}

//
// Equality : operator ==
//
template <class I> inline 
BOOL CSmartInterface<I>::operator==(I* pI) const
{
   TRACE0("operator ==\r\n") ;
   return (m_pI == pI) ;
}

//
// In-equality : operator !=
//
template <class I> inline 
BOOL CSmartInterface<I>::operator!=(I* pI) const
{
   TRACE0("operator !=\r\n") ;
   return (m_pI != pI) ;
}

//
// Negation : operator !
//
template <class I> inline 
BOOL CSmartInterface<I>::operator!() const
{
   TRACE0("operator ! \r\n") ;
   return !m_pI ;
}

//
// Release
//
#if 0
/*
The following code doesn't prevent the user of the class
from calling release! This can cause problems when porting
old code!

*/
template <class I> inline 
ULONG CSmartInterface<I>::Release()
{
   // New rule don't call release :-)
   TRACE0("Calling release shouldn't be needed????\r\n") ;
   m_pI->Release() ;
   m_pI = NULL ;
}
#endif // 0

///////////////////////////////////////////////////////////////
//
//
#if 0
// from IUnknown
template <class I> inline 
CSmartInterface<I>& CSmartInterface<I>::operator=(IUnknown* pI) 
{
   // If its an IUnknown or other interface pointer, 
   // we need to do a QI to see if our interface is supported...
   TRACE0("Assignment from IUnknown*\r\n") ;
   if (m_pI != pI) //OPTOMIZE Only need to AddRef/Release if difference
   {
      if (m_pI != NULL)
         m_pI->Release() ; //Smart Pointers don't use smart pointers :-)
      
      if (pIUnknown != NULL)
         pI->QueryInteface( , (void*)&

      if (m_pI != NULL)
         m_pI->AddRef() ;
   }      
   return *this ;
}
#endif

#endif // CSmartInterface