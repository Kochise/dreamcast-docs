// LevelGetter.cpp : Implementation of CFishTankLevelGetterApp and DLL registration.

#include "stdafx.h"
#include "FishTankLevelGetter.h"
#include "LevelGetter.h"

/////////////////////////////////////////////////////////////////////////////
//

//-----------------------------------------------------------------------------
STDMETHODIMP LevelGetter::GetLowestPossibleSafeLevel(long* plLowestSafeLevel)
{
	*plLowestSafeLevel = 70;
	return S_OK;;
}

//-----------------------------------------------------------------------------
STDMETHODIMP LevelGetter::GetHighestPossibleSafeLevel(long* plHighestSafeLevel)
{
	*plHighestSafeLevel = 98;
	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP LevelGetter::GetCurrentLevel(long* plCurrentLevel)
{
	*plCurrentLevel = 94;
	return S_OK;
}

//-----------------------------------------------------------------------------
STDMETHODIMP LevelGetter::GetTextMessage(BSTR* ppbstrMessage)
{
	*ppbstrMessage = ::SysAllocString(L"All clear, water level is fine");
	return S_OK;
}

