#include "stdafx.h"
#include "icopalob.h"


/////////////////////////////////////////////////////////////////////////////
// IColorPalObj properties

long IColorPalObj::GetHPal()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

void IColorPalObj::SetHPal(long propVal)
{
	SetProperty(0x1, VT_I4, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// IColorPalObj operations

BOOL IColorPalObj::CreateColorCube()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IColorPalObj::Draw(long hDC, long x1, long y1, long x2, long y2)
{
	static BYTE BASED_CODE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 hDC, x1, y1, x2, y2);
}

void IColorPalObj::MakeIdentity()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL IColorPalObj::CreateFromImage(LPDISPATCH pImage)
{
	BOOL result;
	static BYTE BASED_CODE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		pImage);
	return result;
}

void IColorPalObj::Apply(long hDC)
{
	static BYTE BASED_CODE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 hDC);
}

void IColorPalObj::Remove(long hDC)
{
	static BYTE BASED_CODE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 hDC);
}
