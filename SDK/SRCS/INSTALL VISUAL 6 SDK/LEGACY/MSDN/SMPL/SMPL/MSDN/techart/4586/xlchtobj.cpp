// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "xlchtobj.h"


/////////////////////////////////////////////////////////////////////////////
// ChartObject properties

VARIANT ChartObject::GetBorder()
{
	VARIANT result;
	GetProperty(0x80, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetBorder(const VARIANT& propVal)
{
	SetProperty(0x80, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetBottomRightCell()
{
	VARIANT result;
	GetProperty(0x267, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetBottomRightCell(const VARIANT& propVal)
{
	SetProperty(0x267, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetChart()
{
	VARIANT result;
	GetProperty(0x7, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetChart(const VARIANT& propVal)
{
	SetProperty(0x7, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetCreator()
{
	VARIANT result;
	GetProperty(0x95, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetCreator(const VARIANT& propVal)
{
	SetProperty(0x95, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetEnabled()
{
	VARIANT result;
	GetProperty(0x258, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetEnabled(const VARIANT& propVal)
{
	SetProperty(0x258, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetHeight()
{
	VARIANT result;
	GetProperty(0x7b, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetHeight(const VARIANT& propVal)
{
	SetProperty(0x7b, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetIndex()
{
	VARIANT result;
	GetProperty(0x1e6, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetIndex(const VARIANT& propVal)
{
	SetProperty(0x1e6, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetInterior()
{
	VARIANT result;
	GetProperty(0x81, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetInterior(const VARIANT& propVal)
{
	SetProperty(0x81, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetLeft()
{
	VARIANT result;
	GetProperty(0x7f, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetLeft(const VARIANT& propVal)
{
	SetProperty(0x7f, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetLocked()
{
	VARIANT result;
	GetProperty(0x10d, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetLocked(const VARIANT& propVal)
{
	SetProperty(0x10d, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetName()
{
	VARIANT result;
	GetProperty(0x6e, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetName(const VARIANT& propVal)
{
	SetProperty(0x6e, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetOnAction()
{
	VARIANT result;
	GetProperty(0x254, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetOnAction(const VARIANT& propVal)
{
	SetProperty(0x254, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetParent()
{
	VARIANT result;
	GetProperty(0x96, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetParent(const VARIANT& propVal)
{
	SetProperty(0x96, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetPlacement()
{
	VARIANT result;
	GetProperty(0x269, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetPlacement(const VARIANT& propVal)
{
	SetProperty(0x269, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetPrintObject()
{
	VARIANT result;
	GetProperty(0x26a, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetPrintObject(const VARIANT& propVal)
{
	SetProperty(0x26a, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetRoundedCorners()
{
	VARIANT result;
	GetProperty(0x26b, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetRoundedCorners(const VARIANT& propVal)
{
	SetProperty(0x26b, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetShadow()
{
	VARIANT result;
	GetProperty(0x67, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetShadow(const VARIANT& propVal)
{
	SetProperty(0x67, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetTop()
{
	VARIANT result;
	GetProperty(0x7e, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetTop(const VARIANT& propVal)
{
	SetProperty(0x7e, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetTopLeftCell()
{
	VARIANT result;
	GetProperty(0x26c, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetTopLeftCell(const VARIANT& propVal)
{
	SetProperty(0x26c, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetVisible()
{
	VARIANT result;
	GetProperty(0x22e, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetVisible(const VARIANT& propVal)
{
	SetProperty(0x22e, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetWidth()
{
	VARIANT result;
	GetProperty(0x7a, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetWidth(const VARIANT& propVal)
{
	SetProperty(0x7a, VT_VARIANT, &propVal);
}

VARIANT ChartObject::GetZOrder()
{
	VARIANT result;
	GetProperty(0x26e, VT_VARIANT, (void*)&result);
	return result;
}

void ChartObject::SetZOrder(const VARIANT& propVal)
{
	SetProperty(0x26e, VT_VARIANT, &propVal);
}

/////////////////////////////////////////////////////////////////////////////
// ChartObject operations

VARIANT ChartObject::Activate()
{
	VARIANT result;
	InvokeHelper(0x130, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ChartObject::Application()
{
	VARIANT result;
	InvokeHelper(0x94, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ChartObject::BringToFront()
{
	VARIANT result;
	InvokeHelper(0x25a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ChartObject::Copy()
{
	VARIANT result;
	InvokeHelper(0x227, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ChartObject::CopyPicture(const VARIANT& Appearance, const VARIANT& Format)
{
	VARIANT result;
	static BYTE BASED_CODE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Appearance, &Format);
	return result;
}

VARIANT ChartObject::Cut()
{
	VARIANT result;
	InvokeHelper(0x235, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ChartObject::Delete()
{
	VARIANT result;
	InvokeHelper(0x75, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ChartObject::Duplicate()
{
	VARIANT result;
	InvokeHelper(0x40f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT ChartObject::Select(const VARIANT& Replace)
{
	VARIANT result;
	static BYTE BASED_CODE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xeb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Replace);
	return result;
}

VARIANT ChartObject::SendToBack()
{
	VARIANT result;
	InvokeHelper(0x25d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}
