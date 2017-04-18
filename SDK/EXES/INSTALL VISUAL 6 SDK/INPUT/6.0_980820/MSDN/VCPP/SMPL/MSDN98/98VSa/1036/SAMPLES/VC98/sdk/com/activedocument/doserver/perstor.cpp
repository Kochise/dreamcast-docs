/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          PerStor.cpp
   
   Description:   CPersistStorage implementation.

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "PerStor.h"

/**************************************************************************

   CPersistStorage::CPersistStorage()
   
**************************************************************************/

CPersistStorage::CPersistStorage(COleDocument *pOleDoc)
{
OutputDebugString(TEXT("CPersistStorage's constructor\n"));

m_pOleDoc = pOleDoc;

m_pStorage = NULL;
m_pColorStream = NULL;
m_fSameAsLoad = FALSE;
}

/**************************************************************************

   CPersistStorage::~CPersistStorage()
   
**************************************************************************/

CPersistStorage::~CPersistStorage()
{
OutputDebugString(TEXT("CPersistStorage's destructor\n"));
}

/**************************************************************************

   CPersistStorage::QueryInterface()
   
**************************************************************************/

STDMETHODIMP CPersistStorage::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
OutputDebugString(TEXT("CPersistStorage::QueryInterface\n"));

return m_pOleDoc->QueryInterface(riid, ppReturn);
}

/**************************************************************************

   CPersistStorage::AddRef()
   
**************************************************************************/

STDMETHODIMP_(ULONG) CPersistStorage::AddRef()
{
OutputDebugString(TEXT("CPersistStorage::AddRef\n"));

return m_pOleDoc->AddRef();
}

/**************************************************************************

   CPersistStorage::Release()
   
**************************************************************************/

STDMETHODIMP_(ULONG) CPersistStorage::Release()
{
OutputDebugString(TEXT("CPersistStorage::Release\n"));

return m_pOleDoc->Release();
}

/**************************************************************************

   CPersistStorage::InitNew()
   
**************************************************************************/

STDMETHODIMP CPersistStorage::InitNew(LPSTORAGE pStg)
{
OutputDebugString(TEXT("CPersistStorage::InitNew\n"));

// release any streams and storages that may be open
ReleaseStreamsAndStorage();

m_pStorage = pStg;

// AddRef the new Storage
if (m_pStorage)
   m_pStorage->AddRef();

CreateStreams(m_pStorage);

return S_OK;
}

/**************************************************************************

   CPersistStorage::GetClassID()
   
**************************************************************************/

STDMETHODIMP CPersistStorage::GetClassID(LPCLSID pClassID)
{
OutputDebugString(TEXT("CPersistStorage::GetClassID\n"));

*pClassID = CLSID_SimpleDocObject;

return S_OK;
}

/**************************************************************************

   CPersistStorage::Save()
   
**************************************************************************/

STDMETHODIMP CPersistStorage::Save(LPSTORAGE pStg, BOOL fSameAsLoad)
{
OutputDebugString(TEXT("CPersistStorage::Save\n"));

m_pOleDoc->m_fNoScribbleMode = TRUE;

// save the data
LPSTREAM pTempColor;

if(!fSameAsLoad)
   {
   if(!pStg)
      return E_FAIL;

   CreateStreams(pStg, &pTempColor);
   }
else
   {
   pStg = m_pStorage;

   if(!pStg)
      return E_FAIL;
   
   pTempColor = m_pColorStream;
   pTempColor->AddRef();
   }

//write our class ID into the storage
CLSID clsid;
GetClassID(&clsid);
WriteClassStg(pStg, clsid);

ULARGE_INTEGER uli;

uli.LowPart = 0;
uli.HighPart = 0;

pTempColor->SetSize(uli);

LARGE_INTEGER li;

li.LowPart = 0;
li.HighPart = 0;

pTempColor->Seek(li, STREAM_SEEK_SET, NULL);

// write the color to the stream
pTempColor->Write(&m_pOleDoc->m_Color, sizeof(m_pOleDoc->m_Color), NULL);

pTempColor->Release();

m_fSameAsLoad = fSameAsLoad;

m_pOleDoc->m_fDirty = FALSE;

return S_OK;
}

/**************************************************************************

   CPersistStorage::SaveCompleted()
   
**************************************************************************/

STDMETHODIMP CPersistStorage::SaveCompleted(LPSTORAGE pStgNew)
{
OutputDebugString(TEXT("CPersistStorage::SaveCompleted\n"));

if(pStgNew)
   {
   ReleaseStreamsAndStorage();
   m_pStorage = pStgNew;
   m_pStorage->AddRef();
   OpenStreams(pStgNew);
   }

if(pStgNew || m_fSameAsLoad)
   {
   if(m_pOleDoc->m_fNoScribbleMode)
      {
      if(m_pOleDoc->m_pOleAdviseHolder)
         m_pOleDoc->m_pOleAdviseHolder->SendOnSave();
      }

   m_fSameAsLoad = FALSE;
   }

m_pOleDoc->m_fNoScribbleMode = FALSE;

return S_OK;
}

/**************************************************************************

   CPersistStorage::Load()
   
**************************************************************************/

STDMETHODIMP CPersistStorage::Load(LPSTORAGE pStg)
{
OutputDebugString(TEXT("CPersistStorage::Load\n"));

// remember the storage
if(m_pStorage)
   {
   m_pStorage->Release();
   m_pStorage = NULL;
   }

m_pStorage = pStg;

m_pStorage->AddRef();

//read our class ID from the storage
CLSID clsidStg;
ReadClassStg(m_pStorage, &clsidStg);

OpenStreams(m_pStorage);

// read the color
if(FAILED(m_pColorStream->Read(&m_pOleDoc->m_Color, sizeof(m_pOleDoc->m_Color), NULL)))
   {
   m_pOleDoc->m_Color = DEFAULT_COLOR;
   }

m_pOleDoc->m_fDirty = FALSE;

return S_OK;
}

/**************************************************************************

   CPersistStorage::IsDirty()
   
**************************************************************************/

STDMETHODIMP CPersistStorage::IsDirty()
{
OutputDebugString(TEXT("CPersistStorage::IsDirty\n"));

return (m_pOleDoc->m_fDirty ? S_OK : S_FALSE);
}

/**************************************************************************

   CPersistStorage::HandsOffStorage()
   
**************************************************************************/

STDMETHODIMP CPersistStorage::HandsOffStorage()
{
OutputDebugString(TEXT("CPersistStorage::HandsOffStorage\n"));

ReleaseStreamsAndStorage();

return S_OK;
}

/**************************************************************************

   CPersistStorage::CreateStreams()
   
**************************************************************************/

void CPersistStorage::CreateStreams(LPSTORAGE pStg)
{
if(m_pColorStream)
   m_pColorStream->Release();

// create a stream to save the color
pStg->CreateStream(  OLESTR("Color"),
                     STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE,
                     0,
                     0,
                     &m_pColorStream);

}

/**************************************************************************

   CPersistStorage::CreateStreams()
   
**************************************************************************/

void CPersistStorage::CreateStreams(   LPSTORAGE pStg, 
                                       LPSTREAM* ppNewColorStream)
{
LPSTREAM pTempColorStream;

//save the member streams
pTempColorStream = m_pColorStream;

//initialize the streams
m_pColorStream = *ppNewColorStream = NULL;

//create the streams
CreateStreams(pStg);

//copy the new streams
*ppNewColorStream = m_pColorStream;

//restore the member streams
m_pColorStream = pTempColorStream;
}

/**************************************************************************

   CPersistStorage::OpenStreams()
   
**************************************************************************/

void CPersistStorage::OpenStreams(LPSTORAGE pStg)
{
if(m_pColorStream)
   m_pColorStream->Release();

// open the color stream
pStg->OpenStream( OLESTR("Color"),
                  0,
                  STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
                  0,
                  &m_pColorStream);

}

/**************************************************************************

   CPersistStorage::ReleaseStreamsAndStorage()
   
**************************************************************************/

void CPersistStorage::ReleaseStreamsAndStorage()
{
if(m_pColorStream)
   {
   m_pColorStream->Release();
   m_pColorStream = NULL;
   }

if(m_pStorage)
   {
   m_pStorage->Release();
   m_pStorage = NULL;
   }
}

