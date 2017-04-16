// Helpers.cpp : Implementation of of object safety category helper functions
// Copied from ActiveX SDK

#include "stdafx.h"

#include "helpers.h"

/////////////////////////////////////////////////////////////////////////////
// CreateComponentCategory - Ensures component category exists in registry
// (Copied from ActiveX SDK docs)

HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription)
{

    ICatRegister* pcr = NULL ;	// interface pointer
    HRESULT hr = S_OK ;

    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
			NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
	if (FAILED(hr))
		return hr;

    // Make sure the HKCR\Component Categories\{..catid...}
    // key is registered
    CATEGORYINFO catinfo;
    catinfo.catid = catid;
    catinfo.lcid = 0x0409 ; // english

	// Make sure the provided description is not too long.
	// Only copy the first 127 characters if it is
	int len = wcslen(catDescription);
	if (len>127)
		len = 127;
    wcsncpy(catinfo.szDescription, catDescription, len);
	// Make sure the description is null terminated
	catinfo.szDescription[len] = '\0';

    hr = pcr->RegisterCategories(1, &catinfo);
	pcr->Release();

	return hr;
}



/////////////////////////////////////////////////////////////////////////////
// RegisterCLSIDInCategory - Registers class clsid as implementing category catid
// (Copied from ActiveX SDK docs)

HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
// Register your component categories information.
    ICatRegister* pcr = NULL ;
    HRESULT hr = S_OK ;
    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
			NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
    if (SUCCEEDED(hr))
    {
       // Register this category as being "implemented" by
       // the class.
       CATID rgcatid[1] ;
       rgcatid[0] = catid;
       hr = pcr->RegisterClassImplCategories(clsid, 1, rgcatid);
    }

    if (pcr != NULL)
        pcr->Release();
  
	return hr;
}
