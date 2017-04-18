// CpAtlModel.h: Declaration of CProxyIATLTangramModelEvent
//
// This is a part of the Active Template Library.
// Copyright (C) 1996-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

//////////////////////////////////////////////////////////////////////////////
// CProxyIATLTangramModelEvent
template <class T>
class CProxyIATLTangramModelEvent : public IConnectionPointImpl<T, &IID_IATLTangramModelEvent, CComDynamicUnkArray>
{
public:

//IATLTangramModelEvent : IUnknown
public:
	HRESULT Fire_OnModelChange()
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IATLTangramModelEvent* pIATLTangramModelEvent = reinterpret_cast<IATLTangramModelEvent*>(*pp);
				ret = pIATLTangramModelEvent->OnModelChange();
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};
