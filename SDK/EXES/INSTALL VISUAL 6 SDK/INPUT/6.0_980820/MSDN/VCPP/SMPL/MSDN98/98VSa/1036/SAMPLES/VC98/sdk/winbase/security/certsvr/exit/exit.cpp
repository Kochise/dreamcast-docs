//+--------------------------------------------------------------------------
//
// Microsoft Windows
// Copyright (C) Microsoft Corporation, 1996-1997
//
// File:        exit.cpp
//
// Contents:    CCertExit implementation
//
//---------------------------------------------------------------------------

#include "pch.cpp"
#pragma hdrstop

#include <stdio.h>
#include "exit.h"

#define myEXITEVENTS \
	EXITEVENT_CERTISSUED | \
	EXITEVENT_CERTPENDING | \
	EXITEVENT_CERTDENIED | \
	EXITEVENT_CERTREVOKED | \
	EXITEVENT_CERTRETRIEVEPENDING | \
	EXITEVENT_CRLISSUED | \
	EXITEVENT_SHUTDOWN

#ifndef DBG_CERTSRV
#error -- DBG_CERTSRV not defined!
#endif
BOOL fDebug = DBG_CERTSRV;

#define wszDESCRIPTION	L"Sample Exit Module"


//+--------------------------------------------------------------------------
// CCertExit::~CCertExit -- destructor
//
// free memory associated with this instance
//+--------------------------------------------------------------------------

CCertExit::~CCertExit()
{
    if (NULL != m_strConfig)
    {
	SysFreeString(m_strConfig);
    }
}


//+--------------------------------------------------------------------------
// CCertExit::Initialize -- initialize for a CA & return interesting Event Mask
//
// Returns S_OK on success.
//+--------------------------------------------------------------------------

STDMETHODIMP
CCertExit::Initialize(
    /* [in] */ BSTR const strConfig,
    /* [retval][out] */ LONG __RPC_FAR *pEventMask)
{
    HRESULT hr = S_OK;

    m_strConfig = SysAllocString(strConfig);
    if (NULL == m_strConfig)
    {
	hr = E_OUTOFMEMORY;
    }
    else
    {
	*pEventMask = myEXITEVENTS;
	printf("Exit::Initialize(%ws) ==> %x\n", m_strConfig, *pEventMask);
    }
    return(hr);
}


HRESULT
EnumerateExtensions(
    IN ICertServerExit *pServer)
{
    HRESULT hr;
    HRESULT hr2;
    BSTR strName = NULL;
    LONG ExtFlags;
    VARIANT varValue;
    BOOL fClose = FALSE;

    VariantInit(&varValue);
    hr = pServer->EnumerateExtensionsSetup(0);
    if (S_OK != hr)
    {
	if (fDebug)
	{
	    printf("Exit:EnumerateExtensionsSetup: %x", hr);
	}
	goto error;
    }
    fClose = TRUE;
    while (TRUE)
    {
	hr = pServer->EnumerateExtensions(&strName);
	if (S_OK != hr)
	{
	    if (S_FALSE == hr)
	    {
		hr = S_OK;
		break;
	    }
	    if (fDebug)
	    {
		printf("Exit:EnumerateExtensions: %x", hr);
	    }
	    goto error;
	}
	hr = pServer->GetCertificateExtension(
					strName,
					PROPTYPE_BINARY,
					&varValue);
	if (S_OK != hr)
	{
	    if (fDebug)
	    {
		printf("Exit:GetCertificateExtension: %x", hr);
	    }
	    goto error;
	}
	hr = pServer->GetCertificateExtensionFlags(&ExtFlags);
	if (S_OK != hr)
	{
	    if (fDebug)
	    {
		printf("Exit:GetCertificateExtensionFlags: %x", hr);
	    }
	    goto error;
	}
	if (fDebug)
	{
	    printf(
		"Exit:EnumerateExtensions(%ws, Flags=%x, %x bytes)\n",
		strName,
		ExtFlags,
		SysStringByteLen(varValue.bstrVal));
	}
	VariantClear(&varValue);
    }

error:
    if (fClose)
    {
	hr2 = pServer->EnumerateExtensionsClose();
	if (S_OK != hr2)
	{
	    if (fDebug)
	    {
		printf("Exit:EnumerateExtensionsClose: %x", hr2);
	    }
	    if (S_OK == hr)
	    {
		hr = hr2;
	    }
	    goto error;
	}
    }
    if (NULL != strName)
    {
	SysFreeString(strName);
    }
    VariantClear(&varValue);
    return(hr);
}


HRESULT
EnumerateAttributes(
    IN ICertServerExit *pServer)
{
    HRESULT hr;
    HRESULT hr2;
    BSTR strName = NULL;
    BOOL fClose = FALSE;
    BSTR strValue = NULL;

    hr = pServer->EnumerateAttributesSetup(0);
    if (S_OK != hr)
    {
	if (fDebug)
	{
	    printf("Exit:EnumerateAttributesSetup: %x", hr);
	}
	goto error;
    }
    fClose = TRUE;
    while (TRUE)
    {
	hr = pServer->EnumerateAttributes(&strName);
	if (S_OK != hr)
	{
	    if (S_FALSE == hr)
	    {
		hr = S_OK;
		break;
	    }
	    if (fDebug)
	    {
		printf("Exit:EnumerateAttributes: %x", hr);
	    }
	    goto error;
	}
	hr = pServer->GetRequestAttribute(strName, &strValue);
	if (S_OK != hr)
	{
	    if (fDebug)
	    {
		printf("Exit:GetRequestAttribute: %x", hr);
	    }
	    goto error;
	}
	if (fDebug)
	{
	    printf("Exit:EnumerateAttributes(%ws = %ws)\n", strName, strValue);
	}
	if (NULL != strValue)
	{
	    SysFreeString(strValue);
	    strValue = NULL;
	}
    }

error:
    if (fClose)
    {
	hr2 = pServer->EnumerateAttributesClose();
	if (S_OK != hr2)
	{
	    if (fDebug)
	    {
		printf("Exit:EnumerateAttributesClose: %x", hr2);
	    }
	    if (S_OK == hr)
	    {
		hr = hr2;
	    }
	    goto error;
	}
    }

    if (NULL != strName)
    {
	SysFreeString(strName);
    }
    if (NULL != strValue)
    {
	SysFreeString(strValue);
    }
    return(hr);
}


HRESULT
CheckRequestProperties(
    IN ICertServerExit *pServer)
{
    HRESULT hr;
    VARIANT varValue;
    BSTR strName = NULL;

    VariantInit(&varValue);

    strName = SysAllocString(wszPROPREQUESTREQUESTID);
    if (NULL == strName)
    {
	hr = E_OUTOFMEMORY;
	goto error;
    }

    hr = pServer->GetRequestProperty(strName, PROPTYPE_LONG, &varValue);
    if (S_OK != hr)
    {
	if (fDebug)
	{
	    printf("Exit:GetRequestProperty: %x", hr);
	}
	goto error;
    }
    if (fDebug)
    {
	printf(
	    "Exit:CheckRequestProperties(%ws = %x)\n",
	    strName,
	    varValue.lVal);
    }
    VariantClear(&varValue);

error:
    if (NULL != strName)
    {
	SysFreeString(strName);
    }
    return(hr);
}


HRESULT
CheckCert(
    LONG Context)
{
    HRESULT hr;
    ICertServerExit *pServer = NULL;

    hr = CoCreateInstance(
		    CLSID_CCertServerExit,
		    NULL,		// pUnkOuter
		    CLSCTX_INPROC_SERVER,
		    IID_ICertServerExit,
		    (VOID **) &pServer);
    if (S_OK != hr)
    {
	goto exit;
    }

    hr = pServer->SetContext(Context);
    if (S_OK != hr)
    {
	goto exit;
    }
    hr = EnumerateExtensions(pServer);
    if (S_OK != hr)
    {
	goto exit;
    }

    hr = EnumerateAttributes(pServer);
    if (S_OK != hr)
    {
	goto exit;
    }

    hr = CheckRequestProperties(pServer);
    if (S_OK != hr)
    {
	goto exit;
    }

exit:
    if (NULL != pServer)
    {
	pServer->Release();
    }
    return(hr);
}


//+--------------------------------------------------------------------------
// CCertExit::Notify -- Notify the exit module of an event
//
// Returns S_OK.
//+--------------------------------------------------------------------------

STDMETHODIMP
CCertExit::Notify(
    /* [in] */ LONG Event,
    /* [in] */ LONG Context)
{
    HRESULT hr = S_OK;
    char *psz = "UNKNOWN EVENT";

    switch (Event)
    {
	case EXITEVENT_CERTISSUED:
	    psz = "certissued";
	    break;

	case EXITEVENT_CERTPENDING:
	    psz = "certpending";
	    break;

	case EXITEVENT_CERTDENIED:
	    psz = "certdenied";
	    break;

	case EXITEVENT_CERTREVOKED:
	    psz = "certrevoked";
	    break;

	case EXITEVENT_CERTRETRIEVEPENDING:
	    psz = "retrievepending";
	    break;

	case EXITEVENT_CRLISSUED:
	    psz = "crlissued";
	    break;

	case EXITEVENT_SHUTDOWN:
	    psz = "shutdown";
	    break;
    }
    printf("Exit::Notify(%s=%x, ctx=%u)\n", psz, Event, Context);

    if (EXITEVENT_CERTISSUED == Event)
    {
	hr = CheckCert(Context);
    }
    return(hr);
}


STDMETHODIMP
CCertExit::GetDescription(
    /* [retval][out] */ BSTR *pstrDescription)
{
    HRESULT hr = S_OK;

    *pstrDescription = SysAllocString(wszDESCRIPTION);
    if (NULL == *pstrDescription)
    {
	hr = E_OUTOFMEMORY;
    }
    return(hr);
}


/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP
CCertExit::InterfaceSupportsErrorInfo(REFIID riid)
{
    int i;
    static const IID *arr[] =
    {
	&IID_ICertExit,
    };

    for (i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
    {
	if (InlineIsEqualGUID(*arr[i],riid))
	{
	    return(S_OK);
	}
    }
    return(S_FALSE);
}
