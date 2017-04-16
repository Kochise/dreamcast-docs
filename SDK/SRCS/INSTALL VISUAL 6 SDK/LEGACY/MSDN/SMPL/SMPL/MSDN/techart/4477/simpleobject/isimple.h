#ifndef __ISimple__
#define __ISimple__

class ISimple : public IUnknown
{
public:
   virtual void __stdcall  SetCount(int count) = 0 ;
   virtual int __stdcall   GetCount() = 0 ;
   virtual void __stdcall  Inc() = 0 ;
};
#endif