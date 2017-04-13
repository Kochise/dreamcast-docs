//-----------------------------------------------------------------------------
// Microsoft OLE DB TABLECOPY Sample
// Copyright (C) 1995-1998 Microsoft Corporation
//
// @doc
//
// @module SPY.CPP
//
//-----------------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// Includes
//
/////////////////////////////////////////////////////////////////////////////
#include "common.h"
#include "spy.h"
		 

/////////////////////////////////////////////////////////////////////////////
// Defines
//
/////////////////////////////////////////////////////////////////////////////

// HEADER + BUFFER + FOOTER
// HEADER = HEADSIGNITURE + BUFFERSIZE + BUFFERID
// FOOTER = TAILSIGNITURE

//All the header info must be ULONGs,
//so that the user buffer falls on a word boundary
//The tail must be a byte, since if it was a ULONG it would
//also require a word boundary, but the users buffer could
//be an odd number of bytes, so instead of rounding up, just use BYTE

const ULONG HEADSIZE	= sizeof(ULONG);  //HEADSIGNITURE
const ULONG LENGTHSIZE	= sizeof(ULONG);  //BUFFERSIZE
const ULONG IDSIZE		= sizeof(ULONG);  //BUFFERIF
const ULONG TAILSIZE	= sizeof(BYTE);	  //TAILSIGNITURE

const ULONG HEADERSIZE = ROUNDUP(HEADSIZE + LENGTHSIZE + IDSIZE);
const ULONG FOOTERSIZE = TAILSIZE;

const BYTE  HEADSIGN = '{';
const BYTE  TAILSIGN = '}';

const BYTE  ALLOCSIGN = '$';
const BYTE  FREESIGN  = 'Z';

#define HEAD_OFFSET(pActual)		((BYTE*)pActual)
#define TAIL_OFFSET(pActual)		(USERS_OFFSET(pActual)+BUFFER_LENGTH(pActual))

#define USERS_OFFSET(pActual)		(HEAD_OFFSET(pActual) + HEADERSIZE)
#define HEADER_OFFSET(pRequest) 	((BYTE*)(pRequest) - HEADERSIZE)	

#define LENGTH_OFFSET(pActual)		(HEAD_OFFSET(pActual) + HEADSIZE)	
#define BUFFER_LENGTH(pActual)		(*(ULONG*)LENGTH_OFFSET(pActual))

#define ID_OFFSET(pActual)			(LENGTH_OFFSET(pActual) + LENGTHSIZE)
#define BUFFER_ID(pActual)			(*(ULONG*)ID_OFFSET(pActual))

#define HEAD_SIGNITURE(pActual)		(*(ULONG*)HEAD_OFFSET(pActual))
#define TAIL_SIGNITURE(pActual)		(*(BYTE*)TAIL_OFFSET(pActual))


/////////////////////////////////////////////////////////////////////////////
// CMallocSpy::CMallocSpy()
//
/////////////////////////////////////////////////////////////////////////////
CMallocSpy::CMallocSpy()
{
    m_cRef = 0;
	m_cbRequest = 0;

	//Have constructor AddRef, so ref count is init 1
	//Release() is required
	AddRef();
}

/////////////////////////////////////////////////////////////////////////////
// CMallocSpy::~CMallocSpy()
//
/////////////////////////////////////////////////////////////////////////////
CMallocSpy::~CMallocSpy()
{
	//Remove all the elements of the list
	CAllocList.RemoveAll();
}


/////////////////////////////////////////////////////////////////////////////
// HRESULT CMallocSpy::AddToList
//
/////////////////////////////////////////////////////////////////////////////
HRESULT CMallocSpy::AddToList(void* pv)
{
	ASSERT(pv);

	//Add this element to the list
	CAllocList.AddTail(pv);
	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// HRESULT CMallocSpy::RemoveFromList
//
/////////////////////////////////////////////////////////////////////////////
HRESULT CMallocSpy::RemoveFromList(void* pv)
{
	ASSERT(pv);
	
	//Remove this element from the list
	LISTPOS pos = CAllocList.Find(pv);
	if(pos)
		CAllocList.RemoveAt(pos);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// HRESULT CMallocSpy::DumpLeaks
//
/////////////////////////////////////////////////////////////////////////////
HRESULT CMallocSpy::DumpLeaks()
{
	ULONG ulTotalLeaked = 0;

	//Display Leaks to the Output Window
	while(!CAllocList.IsEmpty())
	{	
		//Obtain the pointer to the leaked memory
		void* pRequest = CAllocList.RemoveHead();
		ASSERT(pRequest);
		
		void* pActual = HEADER_OFFSET(pRequest);
		ASSERT(pActual);

		//Make sure that the head/tail signitures are intact
		if(HEAD_SIGNITURE(pActual) != HEADSIGN)
			TRACE(L"-- IMallocSpy HeadSigniture Corrupted! - 0x%08x, ID=%08lu, %lu bytes\n", pRequest, BUFFER_ID(pActual), BUFFER_LENGTH(pActual));

		if(TAIL_SIGNITURE(pActual) != TAILSIGN)
			TRACE(L"-- IMallocSpy TailSigniture Corrupted! - 0x%08x, ID=%08lu, %lu bytes\n", pRequest, BUFFER_ID(pActual), BUFFER_LENGTH(pActual));

		ULONG ulSize = BUFFER_LENGTH(pActual);
		ULONG ulID	 = BUFFER_ID(pActual);
		
		TRACE(L"-- IMallocSpy LEAK! - 0x%08x, ID=%08lu, %lu bytes\n", pRequest, ulID, ulSize);
		ulTotalLeaked += ulSize;

		//Free the Leak
		//You really cant free the leak since the app could be potentially still
		//using it.  Or the DLL may still be in use or have attached threads...
		//SAFE_FREE(pActual);
	}

	if(ulTotalLeaked)
		TRACE(L"-- IMallocSpy Total LEAKED! - %lu bytes\n", ulTotalLeaked);

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// HRESULT CMallocSpy::QueryInterface
//
/////////////////////////////////////////////////////////////////////////////
HRESULT CMallocSpy::QueryInterface(REFIID riid, void** ppIUnknown)
{
	if(!ppIUnknown)
		return E_INVALIDARG;
	
	*ppIUnknown = NULL;

	//IID_IUnknown
    if(riid == IID_IUnknown)
		*ppIUnknown = this;
    //IDD_IMallocSpy
	else if(riid == IID_IMallocSpy)
         *ppIUnknown =  this;
    
	if(*ppIUnknown)
    {
        ((IUnknown*)*ppIUnknown)->AddRef();
        return S_OK;
	}

	return E_NOINTERFACE;
}

/////////////////////////////////////////////////////////////////////////////
// ULONG CMallocSpy::AddRef
//
/////////////////////////////////////////////////////////////////////////////
ULONG CMallocSpy::AddRef()
{
    return ++m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
// ULONG CMallocSpy::Release
//
/////////////////////////////////////////////////////////////////////////////
ULONG CMallocSpy::Release()
{
    if(--m_cRef)
    	return m_cRef;

	TRACE(L"Releasing IMallocSpy\n");

    delete this;
    return 0;
}


/////////////////////////////////////////////////////////////////////////////
// ULONG CMallocSpy::PreAlloc
//
/////////////////////////////////////////////////////////////////////////////
ULONG CMallocSpy::PreAlloc(ULONG cbRequest)
{
	//cbRequest is the orginal number of bytes requested by the user
	//Store the users requested size
    m_cbRequest = cbRequest;

	//Return the total size requested, plus extra for header/footer
	return (m_cbRequest + HEADERSIZE + FOOTERSIZE);
}

/////////////////////////////////////////////////////////////////////////////
// void* CMallocSpy::PostAlloc
//
/////////////////////////////////////////////////////////////////////////////
void* CMallocSpy::PostAlloc(void* pActual)
{
	//pActual is the pointer to the head of the buffer, including the header
	//Add the users pointer to the list
	AddToList(USERS_OFFSET(pActual));

	//Place the HeadSigniture in the HEADER
	HEAD_SIGNITURE(pActual) = HEADSIGN;
	
	//Place the Size in the HEADER
	BUFFER_LENGTH(pActual) = m_cbRequest;

	//Place the ID in the HEADER
	static ULONG ulID = 0;
	BUFFER_ID(pActual) = ++ulID;

	//Set the UsersBuffer to a known char
    memset(USERS_OFFSET(pActual), ALLOCSIGN, m_cbRequest);

	//Place the TailSigniture in the HEADER
	TAIL_SIGNITURE(pActual) = TAILSIGN;

#ifdef FINDLEAKS
	TRACE(L"-- IMallocSpy Alloc - 0x%08x, ID=%08lu, %lu bytes\n", USERS_OFFSET(pActual), ulID, m_cbRequest);
#endif // FINDLEAKS

	// Return the actual users buffer
    return USERS_OFFSET(pActual);
}

/////////////////////////////////////////////////////////////////////////////
// void* CMallocSpy::PreFree
//
/////////////////////////////////////////////////////////////////////////////
void* CMallocSpy::PreFree(void* pRequest, BOOL fSpyed)
{
	//pRequest is the users pointer to thier buffer, not the header

	// Check for NULL
    if(pRequest == NULL)
        return NULL;

    //If this memory was alloced under IMallocSpy, need to remove it
    if(fSpyed)
	{
		//Remove this pointer from the list
		RemoveFromList(pRequest);
	
		void* pActual = HEADER_OFFSET(pRequest);
		
		//Make sure that the head/tail signitures are intact
		if(HEAD_SIGNITURE(pActual) != HEADSIGN)
			TRACE(L"-- IMallocSpy HeadSigniture Corrupted! - 0x%08x, ID=%08lu, %lu bytes\n", pRequest, BUFFER_ID(pActual), BUFFER_LENGTH(pActual));

		if(TAIL_SIGNITURE(pActual) != TAILSIGN)
			TRACE(L"-- IMallocSpy TailSigniture Corrupted! - 0x%08x, ID=%08lu, %lu bytes\n", pRequest, BUFFER_ID(pActual), BUFFER_LENGTH(pActual));

		//Set the UsersBuffer to a known char
		memset(pRequest, FREESIGN, BUFFER_LENGTH(pActual));

		//Need to return the actual header pointer to
		//free the entire buffer including the heading
		return pActual;
	}

	//else
	return pRequest;
}


/////////////////////////////////////////////////////////////////////////////
// void CMallocSpy::PostFree
//
/////////////////////////////////////////////////////////////////////////////
void CMallocSpy::PostFree(BOOL fSpyed)
{
    // Note the free or whatever
    return;
}


/////////////////////////////////////////////////////////////////////////////
// ULONG CMallocSpy::PreRealloc
//
/////////////////////////////////////////////////////////////////////////////
ULONG CMallocSpy::PreRealloc(void* pRequest, ULONG cbRequest,
                             void** ppNewRequest, BOOL fSpyed)
{
	ASSERT(pRequest && ppNewRequest);
    
	//If this was alloced under IMallocSpy we need to adjust
	//the size stored in the header
    if(fSpyed)
    {
		//Remove the original pRequest pointer from the list
		//Since Realloc could change the original pointer
		RemoveFromList(pRequest);
	
        //Find the start 
		*ppNewRequest = HEADER_OFFSET(pRequest);
		
		//Store the new desired size
		m_cbRequest = cbRequest;
		
		//Return the total size, including extra
		return (m_cbRequest + HEADERSIZE + FOOTERSIZE);
    }

	//else
	*ppNewRequest = pRequest;
    return cbRequest;
}


/////////////////////////////////////////////////////////////////////////////
// void* CMallocSpy::PostRealloc
//
/////////////////////////////////////////////////////////////////////////////
void* CMallocSpy::PostRealloc(void* pActual, BOOL fSpyed)
{
    //If this buffer was alloced under IMallocSpy
    if(fSpyed)
    {
		//pActual is the pointer to header
		//Add the new pointer to the list
		AddToList(USERS_OFFSET(pActual));

		//HeadSigniture should still be intact
		if(HEAD_SIGNITURE(pActual) != HEADSIGN)
			TRACE(L"-- IMallocSpy HeadSigniture Corrupted! - 0x%08x, ID=%08lu, %lu bytes\n", USERS_OFFSET(pActual), BUFFER_ID(pActual), BUFFER_LENGTH(pActual));
		
		//ID should still be intact

		//Place the new Size in the HEADER
		BUFFER_LENGTH(pActual) = m_cbRequest;

        //Need to place the tail signiture again, 
		//since it will be over written by the realloc
		TAIL_SIGNITURE(pActual) = TAILSIGN;

#ifdef FINDLEAKS
		TRACE(L"-- IMallocSpy Realloc - 0x%08x, ID=%08lu, %lu bytes\n", USERS_OFFSET(pActual), BUFFER_ID(pActual), m_cbRequest);
#endif // FINDLEAKS

		//Return the actual "user" buffer
		return USERS_OFFSET(pActual);
    }
    
	//else
    return pActual;
}


/////////////////////////////////////////////////////////////////////////////
// void* CMallocSpy::PreGetSize
//
/////////////////////////////////////////////////////////////////////////////
void* CMallocSpy::PreGetSize(void* pRequest, BOOL fSpyed)
{
    if (fSpyed)
        return HEADER_OFFSET(pRequest);

    return pRequest;
}



/////////////////////////////////////////////////////////////////////////////
// ULONG CMallocSpy::PostGetSize
//
/////////////////////////////////////////////////////////////////////////////
ULONG CMallocSpy::PostGetSize(ULONG cbActual, BOOL fSpyed)
{
    if (fSpyed)
        return cbActual - HEADERSIZE - FOOTERSIZE;

    return cbActual;
}




/////////////////////////////////////////////////////////////////////////////
// void* CMallocSpy::PreDidAlloc
//
/////////////////////////////////////////////////////////////////////////////
void* CMallocSpy::PreDidAlloc(void* pRequest, BOOL fSpyed)
{
    if (fSpyed)
        return HEADER_OFFSET(pRequest);

	return pRequest;
}


/////////////////////////////////////////////////////////////////////////////
// BOOL CMallocSpy::PostDidAlloc
//
/////////////////////////////////////////////////////////////////////////////
BOOL CMallocSpy::PostDidAlloc(void* pRequest, BOOL fSpyed, BOOL fActual)
{
    return fActual;
}



/////////////////////////////////////////////////////////////////////////////
// void CMallocSpy::PreHeapMinimize
//
/////////////////////////////////////////////////////////////////////////////
void CMallocSpy::PreHeapMinimize()
{
    // We don't do anything here
    return;
}


/////////////////////////////////////////////////////////////////////////////
// void CMallocSpy::PostHeapMinimize
//
/////////////////////////////////////////////////////////////////////////////
void CMallocSpy::PostHeapMinimize()
{
    // We don't do anything here
    return;
}

/////////////////////////////////////////////////////////////////////////////
// Resgistration
//
/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
HRESULT MallocSpyRegister(CMallocSpy** ppCMallocSpy)
{
	ASSERT(ppCMallocSpy);
	
	//Allocate Interface
	*ppCMallocSpy = new CMallocSpy(); //Constructor AddRef's
	
	//Regisiter Interface
	return CoRegisterMallocSpy(*ppCMallocSpy); // Does an AddRef on Object
}

HRESULT MallocSpyUnRegister(CMallocSpy* pCMallocSpy)
{
	ASSERT(pCMallocSpy);
	return CoRevokeMallocSpy(); //Does a Release on Object
}

HRESULT MallocSpyDump(CMallocSpy* pCMallocSpy)
{
	ASSERT(pCMallocSpy);
	return pCMallocSpy->DumpLeaks(); 
}

#else
HRESULT MallocSpyRegister(CMallocSpy** ppCMallocSpy) {	return S_OK; };
HRESULT MallocSpyUnRegister(CMallocSpy* pCMallocSpy) {	return S_OK; };
HRESULT MallocSpyDump(CMallocSpy* pCMallocSpy)		  { return S_OK; };
#endif //DEBUG


