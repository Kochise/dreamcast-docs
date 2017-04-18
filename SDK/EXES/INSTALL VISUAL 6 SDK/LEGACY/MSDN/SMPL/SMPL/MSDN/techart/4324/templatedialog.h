template<class T> class CTemplateDialog : public CTheDialog
{
   public:
      void SetObjectPtr(T* ptr) {m_ptrObject = ptr; } 

      typedef CString& (T::*PtrMemFunc)() ;

      void SetMemFunctPtr(PtrMemFunc ptr) {m_MemFunctPtr = ptr; }

   protected:
      T* m_ptrObject ;
      PtrMemFunc m_MemFunctPtr ;

      virtual CString& CallMemberPtr() { return (m_ptrObject->*m_MemFunctPtr)() ; }
};
