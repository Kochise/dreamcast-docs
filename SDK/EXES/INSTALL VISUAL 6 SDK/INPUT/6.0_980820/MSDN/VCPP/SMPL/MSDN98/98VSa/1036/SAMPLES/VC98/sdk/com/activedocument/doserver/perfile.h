/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          PerFile.h
   
   Description:   CPersistFile definitions.

**************************************************************************/

#ifndef PERSISTFILE_H
#define PERSISTFILE_H

/**************************************************************************
   #include statements
**************************************************************************/

#include "DOServer.h"

/**************************************************************************

   CPersistFile class definition

**************************************************************************/

class COleDocument;
class CPersistStorage;

class CPersistFile : IPersistFile
{
private:
	LPSTORAGE         m_pStorage;
	COleDocument      *m_pOleDoc;
   CPersistStorage   *m_pPersistStorage;
   LPOLESTR          m_pwszFile;

public:
	CPersistFile::CPersistFile(COleDocument *, CPersistStorage *);
	CPersistFile::~CPersistFile();

	STDMETHODIMP QueryInterface(REFIID, LPVOID*);
	STDMETHODIMP_(ULONG)AddRef();
	STDMETHODIMP_(ULONG)Release();

	STDMETHODIMP GetClassID(LPCLSID);
	STDMETHODIMP Save(LPCOLESTR, BOOL);
	STDMETHODIMP SaveCompleted(LPCOLESTR);
	STDMETHODIMP Load(LPCOLESTR, DWORD);
	STDMETHODIMP IsDirty(void);
	STDMETHODIMP GetCurFile(LPOLESTR*);

};

#endif   //PERSISTFILE_H
