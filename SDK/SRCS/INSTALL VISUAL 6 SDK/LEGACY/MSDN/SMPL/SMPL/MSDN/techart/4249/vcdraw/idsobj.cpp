// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "idsobj.h"


/////////////////////////////////////////////////////////////////////////////
// IDrawSurfObj properties

long IDrawSurfObj::GetWidth()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

void IDrawSurfObj::SetWidth(long propVal)
{
	SetProperty(0x1, VT_I4, propVal);
}

long IDrawSurfObj::GetHeight()
{
	long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}

void IDrawSurfObj::SetHeight(long propVal)
{
	SetProperty(0x2, VT_I4, propVal);
}

long IDrawSurfObj::GetHDC()
{
	long result;
	GetProperty(0x3, VT_I4, (void*)&result);
	return result;
}

void IDrawSurfObj::SetHDC(long propVal)
{
	SetProperty(0x3, VT_I4, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// IDrawSurfObj operations

BOOL IDrawSurfObj::LoadFile(LPCTSTR pszFile)
{
	BOOL result;
	static BYTE BASED_CODE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		pszFile);
	return result;
}

void IDrawSurfObj::Draw(long hDC, long x, long y)
{
	static BYTE BASED_CODE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 hDC, x, y);
}

BOOL IDrawSurfObj::MapToPalette(long hPal)
{
	BOOL result;
	static BYTE BASED_CODE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		hPal);
	return result;
}

long IDrawSurfObj::GetBitmapInfo()
{
	long result;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL IDrawSurfObj::CreateNew(long width, long height, long hPal)
{
	BOOL result;
	static BYTE BASED_CODE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		width, height, hPal);
	return result;
}

void IDrawSurfObj::CopyWithTransparency(LPDISPATCH ds, long x, long y)
{
	static BYTE BASED_CODE parms[] =
		VTS_DISPATCH VTS_I4 VTS_I4;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ds, x, y);
}

long IDrawSurfObj::GetDIBSurface()
{
	long result;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}
