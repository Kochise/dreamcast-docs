/*************************************************************************
**
**  This is a part of the Microsoft Source Code Samples.
**
**  Copyright (C) 1992-1997 Microsoft Corporation. All rights reserved.
**
**  This source code is only intended as a supplement to Microsoft Development
**  Tools and/or WinHelp documentation.  See these sources for detailed
**  information regarding the Microsoft samples programs.
**
**  OLE Automation TypeLibrary Browse Helper Sample
**
**  function.cpp
**
**  CFunction implementation
**
**  Written by Microsoft Product Support Services, Windows Developer Support
**
*************************************************************************/

#include <windows.h>
#include <windowsx.h>
#ifdef WIN16   
  #include <ole2.h>
  #include <compobj.h>    
  #include <dispatch.h> 
  #include <variant.h>
  #include <olenls.h>  
#endif 
#include "browseh.h"  

/*
 * CFunction::Create
 *
 * Purpose:
 *  Creates an instance of the Function automation object and initializes it.
 *
 * Parameters:       
 *  ptinfo        TypeInfo of which this Function is an element of.
 *  nIndex	      Index of function in containing TypeInfo.
 *  ppFunction    Returns Function automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CFunction::Create(LPTYPEINFO ptinfo, unsigned short nIndex, CFunction FAR* FAR* ppFunction) 
{   
    HRESULT hr;
    CFunction FAR* pFunction = NULL;      
    CTypeDesc FAR* pTypeDesc = NULL;
     
    *ppFunction = NULL;
    
    // Create object.
    pFunction = new CFunction();
    if (pFunction == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }    
    
    // Load type information for the application object from type library. 
    hr = pFunction->LoadTypeInfo(IID_IFunction);
    if (FAILED(hr))
        goto error; 
    
    hr = ptinfo->GetFuncDesc(nIndex, &pFunction->m_pfuncdesc);   
    if (FAILED(hr))
        goto error;
    // Function return type.
    hr = CTypeDesc::Create(ptinfo, &pFunction->m_pfuncdesc->elemdescFunc.tdesc, &pTypeDesc);
    if (FAILED(hr))
        goto error;
    pTypeDesc->QueryInterface(IID_IDispatch, (LPVOID FAR*)&pFunction->m_pdispTypeDesc);
    
    hr = ptinfo->GetDocumentation(pFunction->m_pfuncdesc->memid, &pFunction->m_bstrName, &pFunction->m_bstrDocumentation,
             &pFunction->m_ulHelpContext, &pFunction->m_bstrHelpFile); 
    if (FAILED(hr))
        goto error;   
        
    ptinfo->AddRef();
    pFunction->m_ptinfoFunction = ptinfo;

#ifdef _DEBUG  
    lstrcpyn(pFunction->m_szClassName, TEXT("Function"), 100);
#endif 
        
    *ppFunction = pFunction;
    return NOERROR;
    
error:                        
    if (pFunction == NULL) return E_OUTOFMEMORY;
    if (pFunction->m_pfuncdesc) ptinfo->ReleaseFuncDesc(pFunction->m_pfuncdesc);    
    if (pFunction->m_ptinfoFunction) pFunction->m_ptinfoFunction->Release();
    if (pFunction->m_bstrName) SysFreeString(pFunction->m_bstrName);
    if (pFunction->m_bstrDocumentation) SysFreeString(pFunction->m_bstrDocumentation);
    if (pFunction->m_bstrHelpFile) SysFreeString(pFunction->m_bstrHelpFile);
         
    // Set to NULL to prevent destructor from attempting to free again  
    pFunction->m_ptinfoFunction = NULL;
    pFunction->m_pfuncdesc = NULL;
    pFunction->m_bstrName = NULL;
    pFunction->m_bstrDocumentation = NULL;
    pFunction->m_bstrHelpFile = NULL;
    
    delete pFunction;
    return hr;
}

/*
 * CFunction::CFunction
 *
 * Purpose:
 *  Constructor for CFunction object. Initializes members to NULL.
 *
 */
CFunction::CFunction()
{
    m_bstrName = NULL;
    m_bstrDocumentation = NULL;
    m_bstrHelpFile = NULL;
    m_pdispParameters = NULL;    
    m_ptinfoFunction = NULL;
    m_pfuncdesc = NULL;  
    m_pdispTypeDesc = NULL;
}

/*
 * CFunction::~CFunction
 *
 * Purpose:
 *  Destructor for CFunction object. 
 *
 */
CFunction::~CFunction()
{    
     if (m_bstrName) SysFreeString(m_bstrName);
     if (m_bstrDocumentation) SysFreeString(m_bstrDocumentation);
     if (m_bstrHelpFile) SysFreeString(m_bstrHelpFile);
     if (m_pdispParameters) m_pdispParameters->Release();        
     if (m_pfuncdesc && m_ptinfoFunction) m_ptinfoFunction->ReleaseFuncDesc(m_pfuncdesc);
     if (m_ptinfoFunction) m_ptinfoFunction->Release();      
     if (m_pdispTypeDesc) m_pdispTypeDesc->Release();
}

STDMETHODIMP_(REFCLSID)
CFunction::GetInterfaceID()
{
    return IID_IFunction;
}

STDMETHODIMP_(BSTR)
CFunction::get_Name()
{
    return SysAllocString(m_bstrName);
} 

STDMETHODIMP_(BSTR)
CFunction::get_Documentation()     
{
    return SysAllocString(m_bstrDocumentation);
}  

STDMETHODIMP_(long)
CFunction::get_HelpContext()     
{
    return (long)m_ulHelpContext;
}

STDMETHODIMP_(BSTR)
CFunction::get_HelpFile()     
{
    return SysAllocString(m_bstrHelpFile);
}   


STDMETHODIMP_(ITypeDesc FAR*)
CFunction::get_ReturnType()
{   
    m_pdispTypeDesc->AddRef();
    return (ITypeDesc FAR*)m_pdispTypeDesc;
}


STDMETHODIMP_(ICollection FAR*)
CFunction::get_Parameters()
{   
    HRESULT hr;        
    CParameter FAR* pParameter;
    CCollection FAR* pCollection = NULL;
    LPDISPATCH pdisp;
    BSTR FAR* rgbstrNames = NULL;  
    unsigned int cNames;       
    unsigned short n = 0;
    
	// Create a collection of parameters and return it.
    if (m_pdispParameters == NULL)
    {   
        rgbstrNames = new BSTR[m_pfuncdesc->cParams+1];
        if (rgbstrNames == NULL)
            {RaiseException(IDS_OutOfMemory); return NULL;}  
		
		// Get the name of the function and its parameters
        hr = m_ptinfoFunction->GetNames(m_pfuncdesc->memid, rgbstrNames, 
			                  m_pfuncdesc->cParams+1, &cNames);
        if (FAILED(hr))
            {RaiseException(IDS_Unexpected); goto error;}     
        SysFreeString(rgbstrNames[0]);
        
		// Create a parameter collection
        hr = CCollection::Create(m_pfuncdesc->cParams, 0, &pCollection);  
        if (FAILED(hr))
            {RaiseException(IDS_Unexpected); goto error;}        
        
		// The value being assigned to a property does not have a name. Call it 'Value'
		if (m_pfuncdesc->invkind & INVOKE_PROPERTYPUT)
            rgbstrNames[n+1] = SysAllocString(OLESTR("Value"));
		// Add parameters to the parameter collection
        for (n=0; n<m_pfuncdesc->cParams; n++)
        {
            hr = CParameter::Create(m_ptinfoFunction, 
				   rgbstrNames[n+1], 
                   &m_pfuncdesc->lprgelemdescParam[n].tdesc, 
                   &m_pfuncdesc->lprgelemdescParam[n].idldesc,
                   &pParameter);
            if (FAILED(hr))
                {RaiseException(IDS_Unexpected); goto error;}     
            SysFreeString(rgbstrNames[n+1]);
            pParameter->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
            pCollection->Add(pdisp);
            pdisp->Release();  
        }
        pCollection->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
        m_pdispParameters = pdisp;   
        delete rgbstrNames;
    }    
    m_pdispParameters->AddRef();
    return (ICollection FAR*)m_pdispParameters;       
    
error:  
    if (pCollection) delete pCollection;  
    if (rgbstrNames) 
        for (; n<m_pfuncdesc->cParams; n++)
            SysFreeString(rgbstrNames[n+1]);     
    return NULL;
} 

STDMETHODIMP_(MEMBERID)
CFunction::get_Memberid()
{
    return m_pfuncdesc->memid;
}

STDMETHODIMP_(CALLCONV)
CFunction::get_CallConvention()
{ 
    return m_pfuncdesc->callconv;
}

STDMETHODIMP_(FUNCKIND)
CFunction::get_FuncKind()
{ 
    return m_pfuncdesc->funckind;
}

STDMETHODIMP_(INVOKEKIND)
CFunction::get_InvocationKind()
{ 
    return m_pfuncdesc->invkind;
}

STDMETHODIMP_(short)
CFunction::get_NumberOfOptionalParams()
{
	return m_pfuncdesc->cParamsOpt;
}

STDMETHODIMP_(short)
CFunction::get_OffsetInVtbl()
{
	return m_pfuncdesc->oVft;
}

STDMETHODIMP_(unsigned short)
CFunction::get_FuncFlags()
{
	return m_pfuncdesc->wFuncFlags;
}

STDMETHODIMP_(OBJTYPE)
CFunction::get_Kind()
{   
    return TYPE_FUNCTION;
}
