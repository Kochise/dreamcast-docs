//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.
//////////////////////////////////////////////////////////////////////////////
// CProxyIStockEvents
template <class T>
class CProxyIStockEvents : public IConnectionPointImpl<T, &IID_IStockEvents, CComDynamicUnkArray>
{
public:

//IStockEvents
public:
	void Fire_InfoUpdate()
	{
		T* pT = (T*)this;
		pT->Lock();
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IStockEvents* pIStockEvents = reinterpret_cast<IStockEvents*>(*pp);
				pIStockEvents->InfoUpdate();
			}
			pp++;
		}
		pT->Unlock();
	}
};
