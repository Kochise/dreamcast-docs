#ifndef __CSimpleWrap_H__
#define __CSimpleWrap_H__

#include "SimpleObject\GUIDS.h"
#include "SimpleObject\ISimple.h"
#include "CInterfaceWrap.h"

typedef CInterfaceWrap<ISimple, &IID_ISimple> CSimpleWrapBase ;

class CSimpleWrap : public CSimpleWrapBase
{
public:
   CSimpleWrap() {}

   void SetCount(int count)
	   {ASSERT(m_pI); m_pI->SetCount(count) ;}
   int GetCount()
      {ASSERT(m_pI); return m_pI->GetCount() ;}
   void Inc()  
      {ASSERT(m_pI); m_pI->Inc();}
};
#endif