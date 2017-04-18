/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          DataObj.h
   
   Description:   CDataObject and CEnumForamtEtc definitions.

**************************************************************************/

#ifndef DATAOBJECT_H
#define DATAOBJECT_H

/**************************************************************************
   #include statements
**************************************************************************/

#include "DOServer.h"

#define CF_EMBEDSOURCE      TEXT("Embed Source")

/**************************************************************************

   CDataObject class defintion

**************************************************************************/

class COleDocument;

class CDataObject : public IDataObject
{
private:
	COleDocument         *m_pOleDoc;
   LPDATAADVISEHOLDER   m_pDataAdviseHolder;
   UINT                 m_cfEmbedSource;

public:
	CDataObject::CDataObject(COleDocument*);
	CDataObject::~CDataObject(void);

	//IUnknown methods
	STDMETHODIMP QueryInterface(REFIID, LPVOID*);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();

	//IDataObject methods
	STDMETHODIMP DAdvise(LPFORMATETC, DWORD, LPADVISESINK, LPDWORD);
	STDMETHODIMP DUnadvise(DWORD);
	STDMETHODIMP EnumDAdvise(LPENUMSTATDATA*);
	STDMETHODIMP EnumFormatEtc(DWORD, LPENUMFORMATETC*);
	STDMETHODIMP GetCanonicalFormatEtc(LPFORMATETC, LPFORMATETC);
	STDMETHODIMP GetData(LPFORMATETC, LPSTGMEDIUM);
	STDMETHODIMP GetDataHere(LPFORMATETC, LPSTGMEDIUM);
	STDMETHODIMP QueryGetData(LPFORMATETC);
	STDMETHODIMP SetData(LPFORMATETC, LPSTGMEDIUM, BOOL);

};

/**************************************************************************

   CEnumFormatEtc class defintion

**************************************************************************/

class CEnumFormatEtc : public IEnumFORMATETC
{
private: 
	ULONG 		m_ObjRefCount; // Object reference count
	ULONG		   m_iCur;        // Current element
   UINT        m_cfEmbedSource;

public: 
	CEnumFormatEtc(void);
	~CEnumFormatEtc(void);

	// IUnknown members that delegate to m_pUnkOuter
	STDMETHODIMP         QueryInterface(REFIID, LPVOID*);
	STDMETHODIMP_(ULONG) AddRef(void);
	STDMETHODIMP_(ULONG) Release(void);

	// IEnumFORMATETC members
	STDMETHODIMP Next(ULONG, LPFORMATETC, ULONG*);
	STDMETHODIMP Skip(ULONG);
	STDMETHODIMP Reset(void);
	STDMETHODIMP Clone(LPENUMFORMATETC*);
};

#endif   //DATAOBJECT_H
