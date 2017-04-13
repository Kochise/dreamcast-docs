/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          OIPAObj.h
   
   Description:   COleInPlaceActiveObect definitions.

**************************************************************************/

#ifndef INPLACEACTIVEOBJECT_H
#define INPLACEACTIVEOBJECT_H

/**************************************************************************
   #include statements
**************************************************************************/

#include "DOServer.h"

/**************************************************************************

   COleInPlaceActiveObject class definition

**************************************************************************/

class COleDocument;

class COleInPlaceActiveObject : public IOleInPlaceActiveObject
{
private:
	COleDocument   *m_pOleDoc;
   BOOL           m_fEnableModeless;

public:
	COleInPlaceActiveObject::COleInPlaceActiveObject(COleDocument*);
	COleInPlaceActiveObject::~COleInPlaceActiveObject();

   // IUnknown methods
	STDMETHODIMP QueryInterface(REFIID, LPVOID*);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();

	//IOleInPlaceActiveObject methods
	STDMETHODIMP OnDocWindowActivate(BOOL);
	STDMETHODIMP OnFrameWindowActivate(BOOL);
	STDMETHODIMP GetWindow(HWND*);
	STDMETHODIMP ContextSensitiveHelp(BOOL);
	STDMETHODIMP TranslateAccelerator(LPMSG);
	STDMETHODIMP ResizeBorder(LPCRECT, LPOLEINPLACEUIWINDOW, BOOL);
	STDMETHODIMP EnableModeless(BOOL);

};

#endif   //INPLACEACTIVEOBJECT_H
