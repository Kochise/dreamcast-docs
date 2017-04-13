/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/******************************************************************************

   File:          PerStor.h
   
   Description:   CPersistStorage definitions.

******************************************************************************/

#ifndef PERSISTSTORAGE_H
#define PERSISTSTORAGE_H

/**************************************************************************
   #include statements
**************************************************************************/

#include "DOServer.h"

/**************************************************************************

   CPersistStorage class definition

**************************************************************************/

class COleDocument;

class CPersistStorage : public IPersistStorage
{
friend class CPersistFile;

private:
   COleDocument   *m_pOleDoc;
   LPSTORAGE      m_pStorage;
   LPSTREAM       m_pColorStream;
   BOOL           m_fSameAsLoad;

public:
   CPersistStorage(COleDocument*);
   ~CPersistStorage();

   //IUnknown methods
   STDMETHODIMP QueryInterface(REFIID, LPVOID*);
   STDMETHODIMP_(DWORD) AddRef();
   STDMETHODIMP_(DWORD) Release();

   //IPersistStorage methods
	STDMETHODIMP InitNew(LPSTORAGE);
	STDMETHODIMP GetClassID(LPCLSID);
	STDMETHODIMP Save(LPSTORAGE, BOOL);
	STDMETHODIMP SaveCompleted(LPSTORAGE);
	STDMETHODIMP Load(LPSTORAGE);
	STDMETHODIMP IsDirty();
	STDMETHODIMP HandsOffStorage();
   
private:
	void ReleaseStreamsAndStorage();
	void OpenStreams(LPSTORAGE);
	void CreateStreams(LPSTORAGE);
	void CreateStreams(LPSTORAGE, LPSTREAM*);

};

#endif   //PERSISTSTORAGE_H
