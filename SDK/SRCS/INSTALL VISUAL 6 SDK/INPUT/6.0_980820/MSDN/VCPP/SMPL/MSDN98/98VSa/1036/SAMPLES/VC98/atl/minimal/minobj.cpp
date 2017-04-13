// MinObj.cpp : Implementation of CminimalApp and DLL registration.
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

#include "premin.h"
#include "minimal.h"
#include "MinObj.h"

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CMinObj::Hello()
{
	return S_OK;
}
