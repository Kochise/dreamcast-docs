// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "xlchtobs.h"


/////////////////////////////////////////////////////////////////////////////
// ChartObjects properties

VARIANT ChartObjects::GetBorder()
{
	VARIANT result;
	GetProperty(0x80, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObjects::SetBorder(const VARIANT& propVal)
{
	SetProperty(0x80, VT_VARIANT, &propVal);
}

VARIANT ChartObjects::GetCount()
{
	VARIANT result;
	GetProperty(0x76, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObjects::SetCount(const VARIANT& propVal)
{
	SetProperty(0x76, VT_VARIANT, &propVal);
}

VARIANT ChartObjects::GetCreator()
{
	VARIANT result;
	GetProperty(0x95, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObjects::SetCreator(const VARIANT& propVal)
{
	SetProperty(0x95, VT_VARIANT, &propVal);
}

VARIANT ChartObjects::GetEnabled()
{
	VARIANT result;
	GetProperty(0x258, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObjects::SetEnabled(const VARIANT& propVal)
{
	SetProperty(0x258, VT_VARIANT, &propVal);
}

VARIANT ChartObjects::GetHeight()
{
	VARIANT result;
	GetProperty(0x7b, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObjects::SetHeight(const VARIANT& propVal)
{
	SetProperty(0x7b, VT_VARIANT, &propVal);
}

VARIANT ChartObjects::GetInterior()
{
	VARIANT result;
	GetProperty(0x81, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObjects::SetInterior(const VARIANT& propVal)
{
	SetProperty(0x81, VT_VARIANT, &propVal);
}

VARIANT ChartObjects::GetLeft()
{
	VARIANT result;
	GetProperty(0x7f, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObjects::SetLeft(const VARIANT& propVal)
{
	SetProperty(0x7f, VT_VARIANT, &propVal);
}

VARIANT ChartObjects::GetLocked()
{
	VARIANT result;
	GetProperty(0x10d, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObjects::SetLocked(const VARIANT& propVal)
{
	SetProperty(0x10d, VT_VARIANT, &propVal);
}

VARIANT ChartObjects::GetOnAction()
{
	VARIANT result;
	GetProperty(0x254, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObjects::SetOnAction(const VARIANT& propVal)
{
	SetProperty(0x254, VT_VARIANT, &propVal);
}

VARIANT ChartObjects::GetParent()
{
	VARIANT result;
	GetProperty(0x96, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObjects::SetParent(const VARIANT& propVal)
{
	SetProperty(0x96, VT_VARIANT, &propVal);
}

VARIANT ChartObjects::GetPlacement()
{
	VARIANT result;
	GetProperty(0x269, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObjects::SetPlacement(const VARIANT& propVal)
{
	SetProperty(0x269, VT_VARIANT, &propVal);
}

VARIANT ChartObjects::GetPrintObject()
{
	VARIANT result;
	GetProperty(0x26a, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObjects::SetPrintObject(const VARIANT& propVal)
{
	SetProperty(0x26a, VT_VARIANT, &propVal);
}

VARIANT ChartObjects::GetRoundedCorners()
{
	VARIANT result;
	GetProperty(0x26b, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObjects::SetRoundedCorners(const VARIANT& propVal)
{
	SetProperty(0x26b, VT_VARIANT, &propVal);
}

VARIANT ChartObjects::GetShadow()
{
	VARIANT result;
	GetProperty(0x67, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObjects::SetShadow(const VARIANT& propVal)
{
	SetProperty(0x67, VT_VARIANT, &propVal);
}

VARIANT ChartObjects::GetTop()
{
	VARIANT result;
	GetProperty(0x7e, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObjects::SetTop(const VARIANT& propVal)
{
	SetProperty(0x7e, VT_VARIANT, &propVal);
}

VARIANT ChartObjects::GetVisible()
{
	VARIANT result;
	GetProperty(0x22e, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObjects::SetVisible(const VARIANT& propVal)
{
	SetProperty(0x22e, VT_VARIANT, &propVal);
}

VARIANT ChartObjects::GetWidth()
{
	VARIANT result;
	GetProperty(0x7a, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObjects::SetWidth(const VARIANT& propVal)
{
	SetProperty(0x7a, VT_VARIANT, &propVal);
}

VARIANT ChartObjects::GetZOrder()
{
	VARIANT result;
	GetProperty(0x26e, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObjects::SetZOrder(const VARIANT& propVal)
{
	SetProperty(0x26e, VT_VARIANT, &propVal);
}

/////////////////////////////////////////////////////////////////////////////
// ChartObjects operations

VARIANT ChartObjects::_NewEnum()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ChartObjects::Add(const VARIANT& Left, const VARIANT& Top, const VARIANT& Width, const VARIANT& Height)
{
	VARIANT result;
	static BYTE BASED_CODE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xb5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Left, &Top, &Width, &Height);
	return result;
}

VARIANT ChartObjects::Application()
{
	VARIANT result;
	InvokeHelper(0x94, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ChartObjects::BringToFront()
{
	VARIANT result;
	InvokeHelper(0x25a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ChartObjects::Copy()
{
	VARIANT result;
	InvokeHelper(0x227, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ChartObjects::CopyPicture(const VARIANT& Appearance, const VARIANT& Format)
{
	VARIANT result;
	static BYTE BASED_CODE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Appearance, &Format);
	return result;
}

VARIANT ChartObjects::Cut()
{
	VARIANT result;
	InvokeHelper(0x235, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ChartObjects::Delete()
{
	VARIANT result;
	InvokeHelper(0x75, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ChartObjects::Duplicate()
{
	VARIANT result;
	InvokeHelper(0x40f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ChartObjects::Group()
{
	VARIANT result;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ChartObjects::Item(const VARIANT& Index)
{
	VARIANT result;
	static BYTE BASED_CODE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xaa, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT ChartObjects::Select(const VARIANT& Replace)
{
	VARIANT result;
	static BYTE BASED_CODE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xeb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Replace);
	return result;
}

VARIANT ChartObjects::SendToBack()
{
	VARIANT result;
	InvokeHelper(0x25d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}
