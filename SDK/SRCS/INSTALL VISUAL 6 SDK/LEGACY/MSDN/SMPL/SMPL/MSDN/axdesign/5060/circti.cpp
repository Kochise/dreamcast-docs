//=--------------------------------------------------------------------------=
// CircTI.Cpp
//=--------------------------------------------------------------------------=
// contains some of the basic typeinfo stuff our base class will need to
// generate the runtime type info ..
//
// marcwan, 1.96
//
#include "IPServer.H"

#include "CirclCtl.H"
#include "Misc.H"
#include "Resource.H"
#include "Util.H"
#include "dispids.h"

// for ASSERT and FAIL
//
SZTHISFILE

// Version # of stdole2.tlb
DEFINE_OLEGUID(IID_StdOle,  0x00020430L, 0, 0);
#define STDOLE2_MAJORVERNUM     0x2
#define STDOLE2_MINORVERNUM     0x0
#define STDOLE2_LCID            0x0000

// can't start from zero [see GetTempFileName]
//
static int g_iTempFileName = 1;


//=--------------------------------------------------------------------------=
// private functions
//
HRESULT _GetIDispatchTypeInfo(ITypeInfo **);
HRESULT CopyDispinterfaceTypeInfo(ITypeInfo *, ICreateTypeInfo *);
HRESULT FixHrefTypeFuncDesc(ITypeInfo *, ICreateTypeInfo *, FUNCDESC *);
HRESULT FixHrefTypeVarDesc(ITypeInfo *, ICreateTypeInfo *, VARDESC *);
HRESULT _CopyHrefType(ITypeInfo *, ICreateTypeInfo *, HREFTYPE *);


//=--------------------------------------------------------------------------=
// CCircleCoControl::CreateRuntimeTypeInfo
//=--------------------------------------------------------------------------=
// create the initial type info that people will be using to compiler against.
// this typeinfo is dynamic, so other people will be changing it around a
// bunch.
//
// Parameters:
//    none
//
// Output:
//    HRESULT
//
// Notes:
//    - this is kinda blech.  we have to copy over our template dispinterface
//      because OA modifies all copies of an on-disk typeinfo.  in addition,
//      funky dispinterfaces can't be dynamic.  therefore, we have to create
//      a new dispinterface, and copy it over
//
HRESULT CCircleCoControl::CreateRuntimeTypeInfo
(
    void
)
{
    ICreateTypeInfo *pctiDispinterface = NULL;
    ICreateTypeInfo *pctiCoClass = NULL;
    ICreateTypeLib2 *pCreateTypeLib = NULL;
    ITypeInfo *ptiEvents = NULL, *ptiDispinterface;
    HREFTYPE hreftype;
    HRESULT  hr;
    char szTempName[MAX_PATH];
    char szTempDir[MAX_PATH];

    // if we've already created it, then there's not much to do.
    //
    if (m_state.pRuntimeDispinterface)
        return S_OK;

    // first, we have to create a new type library in which we can stuff
    // things
    //
    GetTempPath(sizeof(szTempDir), szTempDir);
    EnterCriticalSection(&g_CriticalSection);
    GetTempFileName(szTempDir, "QQ", g_iTempFileName++, szTempName);
    LeaveCriticalSection(&g_CriticalSection);

    MAKE_WIDEPTR_FROMANSI(pwszFile, szTempName);
    hr = CreateTypeLib2(SYS_WIN32, pwszFile, &pCreateTypeLib);
    CLEANUP_ON_FAILURE(hr);
    hr = pCreateTypeLib->SetGuid(m_state.guidTypeLib);
    CLEANUP_ON_FAILURE(hr);

    // create our dispinterface typeinfo and load our static source interface
    //
    hr = CreateInterfaces(pCreateTypeLib, &pctiDispinterface, &ptiEvents);
    CLEANUP_ON_FAILURE(hr);

    // go and create a blank typeinfo for the new coclass.
    //
    hr = pCreateTypeLib->CreateTypeInfo(L"MyCircleContainer", TKIND_COCLASS,
                                        &pctiCoClass);
    CLEANUP_ON_FAILURE(hr);

    // got the new typeinfo.  now we just need to add the typeinfos for the
    // interface and events

    // interface
    //
    hr = pctiDispinterface->QueryInterface(IID_ITypeInfo,
                                           (void **)&ptiDispinterface);
    CLEANUP_ON_FAILURE(hr);
    hr = pctiCoClass->AddRefTypeInfo(ptiDispinterface, &hreftype);
    ptiDispinterface->Release();
    CLEANUP_ON_FAILURE(hr);
    hr = pctiCoClass->AddImplType(0, hreftype);
    CLEANUP_ON_FAILURE(hr);

    // events
    //
    hr = pctiCoClass->AddRefTypeInfo(ptiEvents, &hreftype);
    CLEANUP_ON_FAILURE(hr);
    hr = pctiCoClass->AddImplType(1, hreftype);
    CLEANUP_ON_FAILURE(hr);

    // now set up the flags for these two guys.
    //
    hr = pctiCoClass->SetImplTypeFlags(0, IMPLTYPEFLAG_FDEFAULT);
    CLEANUP_ON_FAILURE(hr);
    hr = pctiCoClass->SetImplTypeFlags(1, IMPLTYPEFLAG_FDEFAULT
                                          | IMPLTYPEFLAG_FSOURCE);
    CLEANUP_ON_FAILURE(hr);

    // phew.  we've got the typeinfo for our final compileable coclass.  that
    // should be about it.  store it away as ICreateTypeInfo2, and store away
    // our new interface as such as well.
    //
    hr = pctiCoClass->QueryInterface(IID_ICreateTypeInfo2,
                                     (void **)&m_state.pctiCoClass);
    CLEANUP_ON_FAILURE(hr);

    hr = pctiDispinterface->QueryInterface(IID_ICreateTypeInfo2,
                                           (void **)&m_state.pRuntimeDispinterface);
    CLEANUP_ON_FAILURE(hr);

    // apparantly it's a good idea to always lay out your new typeinfo
    //
    hr = pctiDispinterface->LayOut();
    CLEANUP_ON_FAILURE(hr);

    // that's it!
    //
    hr = S_OK;

  CleanUp:
    // clean a few things up and call it a day.
    //
    QUICK_RELEASE(pctiDispinterface);
    QUICK_RELEASE(pctiCoClass);
    QUICK_RELEASE(pCreateTypeLib);
    QUICK_RELEASE(ptiEvents);

    return hr;
}

//=--------------------------------------------------------------------------=
// CCircleCoControl::CreateInterfaces
//=--------------------------------------------------------------------------=
// creates thedispinterface that inerhits [via copying] from an
// out static dispinterface
//
// Parameters:
//    ICreateTypeLib *              - [in]   working type library
//    ICreateTypeInfo **            - [out]  created dispinterface
//    ITypeInfo **                  - [out]  loaded event interface
//
// Output:
//    HRESULT
//
// Notes:
//
HRESULT CCircleCoControl::CreateInterfaces
(
    ICreateTypeLib   *pTypeLib,
    ICreateTypeInfo **ppDispinterface,
    ITypeInfo       **ppTypeInfo
)
{
    ITypeLib *pTypeLibStatic;
    ITypeInfo *ptiDispatch = NULL;
    ICreateTypeInfo *pctiDispinterface = NULL;
    ITypeInfo *ptiDispinterface;
    HREFTYPE hreftype;
    HRESULT hr;

    // get the dispinterface  we'll be templating off of.
    //
    hr = LoadRegTypeLib(*g_pLibid, (USHORT)VERSIONOFOBJECT(m_ObjectType),0,
			LANG_NEUTRAL, &pTypeLibStatic);
    RETURN_ON_FAILURE(hr);

    hr = pTypeLibStatic->GetTypeInfoOfGuid(DIID_DCircleCo,
                                           &ptiDispinterface);
    if (SUCCEEDED(hr)) {
	// also get the typeinfo of our event interface
	hr = pTypeLibStatic->GetTypeInfoOfGuid(DIID_DCircleCoEvents,ppTypeInfo);
	if (SUCCEEDED(hr)) {
	    // also get the typeinfo of a circle
	    hr = pTypeLibStatic->GetTypeInfoOfGuid(CLSID_Circle,&m_state.pCircleTI);
	}
    }
    
    pTypeLibStatic->Release();
    RETURN_ON_FAILURE(hr);

    // great.  now create a new dispinterface typeinfo
    //
    hr = pTypeLib->CreateTypeInfo(L"DMyCircleContainer", TKIND_DISPATCH,
                                  &pctiDispinterface);
    CLEANUP_ON_FAILURE(hr);
    hr = pctiDispinterface->SetGuid(m_state.guidTypeInfo);
    CLEANUP_ON_FAILURE(hr);

    // Since we're a DISPinterface,
    // we have to manually make the typeinfo inherit from IDispatch's
    // typeinfo.
    //
    hr = _GetIDispatchTypeInfo(&ptiDispatch);
    CLEANUP_ON_FAILURE(hr);
    hr = pctiDispinterface->AddRefTypeInfo(ptiDispatch, &hreftype);
    CLEANUP_ON_FAILURE(hr);
    hr = pctiDispinterface->AddImplType(0, hreftype);
    CLEANUP_ON_FAILURE(hr);

    // make the new interface inherit from our static interface [via copy]
    //
    hr = CopyDispinterfaceTypeInfo(ptiDispinterface, pctiDispinterface);
    CLEANUP_ON_FAILURE(hr);

    // great.  created the interface.  pass it out!
    //
    *ppDispinterface = pctiDispinterface;
    pctiDispinterface->AddRef();
    hr = S_OK;

  CleanUp:
    ptiDispinterface->Release();
    QUICK_RELEASE(pctiDispinterface);
    QUICK_RELEASE(ptiDispatch);
    return hr;
}

//=--------------------------------------------------------------------------=
// _GetIDispatchTypeInfo
//=--------------------------------------------------------------------------=
// retrieves the IDispatch typeinfo.
//
// Parameters:
//    ITypeInfo **      - [out]
//
// Output:
//    HRESULT
//
// Notes:
//
HRESULT _GetIDispatchTypeInfo
(
    ITypeInfo **pptiDispatch
)
{
    ITypeLib *pTypeLib;
    HRESULT hr;

    hr = LoadRegTypeLib(IID_StdOle, STDOLE2_MAJORVERNUM,
                        STDOLE2_MINORVERNUM,
                        STDOLE2_LCID,
                        &pTypeLib);
    ASSERT(!FAILED(hr), "Couldn't load stdole2.tlb!");
    RETURN_ON_FAILURE(hr);

    hr = pTypeLib->GetTypeInfoOfGuid(IID_IDispatch, pptiDispatch);
    pTypeLib->Release();
    return hr;
}



//=--------------------------------------------------------------------------=
// CCircleCoControl::AddToTypeInfo
//=--------------------------------------------------------------------------=
// we've added a circle object to our instance.  now go and add the appropriate
// typeinfo for it to the main typeinfo.
//
// Parameters:
//    int                 - [in] index of circle
//
// Notes:
//
HRESULT CCircleCoControl::AddToTypeInfo
(
    int index
)
{
    FUNCDESC fd;                            // new item is a funcdesc
    TYPEDESC td;
    HRESULT hr;
    HREFTYPE href;
    LPWSTR *rgNames = NULL;
    BSTR bstrName = NULL;

    // first of all, set up the runtime type information ...
    //
    hr = CreateRuntimeTypeInfo();
    RETURN_ON_FAILURE(hr);
    
    // set up some initial values on the funcdesc.  we'll set up the others
    // later on as we get to them.
    //
    memset(&fd, 0, sizeof(fd));
    fd.memid = index + DISPID_CUSTOMOFFSET;
    fd.funckind = FUNC_DISPATCH;
    fd.invkind = INVOKE_PROPERTYGET;
    fd.callconv = CC_STDCALL;
    fd.wFuncFlags = FUNCFLAG_FSOURCE;

    hr = m_state.pRuntimeDispinterface->AddRefTypeInfo(m_state.pCircleTI, &href);
    CLEANUP_ON_FAILURE(hr);

    // set up the return value
    //
    
    // Note of interest: because this is a dispinterface, we structure the new
    // member as:
    // <someType> * FunctionName (void)
    // while, if this were an interface we would have to do:
    // HRESULT * FunctionName (<someType> ** <someName>)
    td.vt = VT_USERDEFINED;
    td.hreftype = href;
    fd.elemdescFunc.tdesc.lptdesc = &td;
    fd.elemdescFunc.tdesc.vt = VT_PTR;
    fd.elemdescFunc.idldesc.wIDLFlags = IDLFLAG_FOUT | IDLFLAG_FRETVAL;

    // set up the parameter information.  easy.
    //
    fd.cParams = 0;
    fd.cParamsOpt = 0;

    // set up the parameters.  count was set up by call above, and no params
    // are optional
    //
    // easy once again since we have no parameters
    
    fd.lprgelemdescParam = NULL;

    hr = m_state.pRuntimeDispinterface->AddFuncDesc(0, &fd);
    CLEANUP_ON_FAILURE(hr);

    bstrName = m_state.rgCircles[index].bstrName;
    // set the name
    
    // the &bstrName should really be an array of OLESTR, but since we are setting only
    // one name, we cheat to makes this simpler
    hr =  m_state.pRuntimeDispinterface->SetFuncAndParamNames(0, &bstrName, 1);
    CLEANUP_ON_FAILURE(hr);

    hr = m_state.pRuntimeDispinterface->LayOut();
    CLEANUP_ON_FAILURE(hr);

    // done.
    //
    hr = S_OK;

  CleanUp:
    
    return hr;

}

//=--------------------------------------------------------------------------=
// CCircleCoControl::DeleteFromTypeInfo
//=--------------------------------------------------------------------------=
// we've removed a circle.  we have to go and remove object from our type info.
//
// Parameters:
//    index            - [in]  the index of the circle to remove
//
// Output:
//
// Notes:

void CCircleCoControl::DeleteFromTypeInfo
(
    int index
)
{

    // We ignore errors
    
    HRESULT hr;

    hr = m_state.pRuntimeDispinterface->DeleteFuncDescByMemId(index+DISPID_CUSTOMOFFSET, 
							INVOKE_PROPERTYGET);
    CLEANUP_ON_FAILURE(hr);

    //
    hr = m_state.pRuntimeDispinterface->LayOut();
    CLEANUP_ON_FAILURE(hr);

  CleanUp:;
    
}

//=--------------------------------------------------------------------------=
// CopyDispinterfaceTypeInfo
//=--------------------------------------------------------------------------=
// given a dispinterface typeinfo, copy it into a new one
//
// Parameters:
//    ITypeInfo *           - [in]  dude to copy
//    ICreateTypeInfo *     - [in]  guy to copy to.  should be blank
//
// Output:
//    HRESULT
//
// Notes:
//
//  This is used to copy our static template to our dynamic dispinterface
//
HRESULT CopyDispinterfaceTypeInfo
(
    ITypeInfo       *pTypeInfo,
    ICreateTypeInfo *pcti
)
{
    HRESULT hr;
    USHORT cFuncs, cVars, x, y;
    TYPEATTR *pTypeAttr;
    FUNCDESC *pFuncDesc;
    VARDESC  *pVarDesc;
    MEMBERID  memid;
    BSTR      rgNames[16];
    UINT      cNames;

    // get some information about the interface we're going to copy:
    //
    hr = pTypeInfo->GetTypeAttr(&pTypeAttr);
    CLEANUP_ON_FAILURE(hr);

    cFuncs = pTypeAttr->cFuncs;
    cVars = pTypeAttr->cVars;
    pTypeInfo->ReleaseTypeAttr(pTypeAttr);

    // iterate through the funcdescs and copy them over
    //
    for (x = 0; x < cFuncs; x++) {
        // copy the fundesc
        //
        hr = pTypeInfo->GetFuncDesc(x, &pFuncDesc);
        CLEANUP_ON_FAILURE(hr);
        hr = FixHrefTypeFuncDesc(pTypeInfo, pcti, pFuncDesc);
        if (FAILED(hr)) {
            pTypeInfo->ReleaseFuncDesc(pFuncDesc);
            goto CleanUp;
        }
        hr = pcti->AddFuncDesc(x, pFuncDesc);
        memid = pFuncDesc->memid;
        pTypeInfo->ReleaseFuncDesc(pFuncDesc);
        CLEANUP_ON_FAILURE(hr);

        // then copy the names for it.
        //
        memset(rgNames, 0, sizeof(rgNames));
        hr = pTypeInfo->GetNames(memid, rgNames, 16, &cNames);
        CLEANUP_ON_FAILURE(hr);

        hr = pcti->SetFuncAndParamNames(x, rgNames, cNames);
        CLEANUP_ON_FAILURE(hr);

        // free up the array of BSTRs
        //
        for (y = 0; y < sizeof(rgNames) / sizeof(BSTR); y++)
            if (rgNames[y]) SysFreeString(rgNames[y]);
    }

    // okay, now copy over the vardescs
    //
    for (x = 0; x < cVars; x++) {

        hr = pTypeInfo->GetVarDesc(x, &pVarDesc);
        CLEANUP_ON_FAILURE(hr);
        hr = FixHrefTypeVarDesc(pTypeInfo, pcti, pVarDesc);
        if (FAILED(hr)) {
            pTypeInfo->ReleaseVarDesc(pVarDesc);
            goto CleanUp;
        }
        hr = pcti->AddVarDesc(x, pVarDesc);
        memid = pVarDesc->memid;
        pTypeInfo->ReleaseVarDesc(pVarDesc);
        CLEANUP_ON_FAILURE(hr);

        // copy the name!
        //
        rgNames[0] = NULL;
        hr = pTypeInfo->GetNames(memid, rgNames, 1, &cNames);
        CLEANUP_ON_FAILURE(hr);
  
        hr = pcti->SetVarName(x, rgNames[0]);
        SysFreeString(rgNames[0]);
        CLEANUP_ON_FAILURE(hr);
    }

    // that should do it.
    //
    hr = S_OK;

  CleanUp:
    return hr;
}

//=--------------------------------------------------------------------------=
// FixHrefTypeFuncDesc
//=--------------------------------------------------------------------------=
// We are copying over the funcdesc from the first TI to the second.
// Since the funcdesc probably refers to some TIs itself, it does so
// by reference (using HREFTYPE)  The HREFTYPE value is only valid within
// the context of the containing typeinfo (ie the original one) and since
// we need the funcdesc in the destination typeinfo, that typeinfo needs to
// have valid references to the funcdesc items.  So we need to get all the
// items and register new HREFTYPEs in the destination TI.
//
// Parameters:
//    ITypeInfo *               - [in]  ti we're copying from
//    ICreateTypeInfo *         - [in]  ti we're copying to
//    FUNCDESC *                - [in]  funcdesc we want to copy.
//
// Output:
//    HRESULT
//
// Notes:
//
HRESULT FixHrefTypeFuncDesc
(
    ITypeInfo *pTypeInfo,
    ICreateTypeInfo *pcti,
    FUNCDESC *pFuncDesc
)
{
    HRESULT hr;
    TYPEDESC *ptd;
    short x;

    // got it.  now look through the funcdesc to see if there a userdefined
    // type any where.  first, try the return value
    //
    ptd = &(pFuncDesc->elemdescFunc.tdesc);
    while (ptd->vt == VT_PTR)
        ptd = ptd->lptdesc;

    // if it's a userdefined type, copy over the hreftype
    //
    if (ptd->vt == VT_USERDEFINED) {
        hr = _CopyHrefType(pTypeInfo, pcti, &(ptd->hreftype));
        CLEANUP_ON_FAILURE(hr);
    }

    // okay, now whip through the parameters:
    //
    for (x = 0; x < pFuncDesc->cParams; x++) {
        ptd = &(pFuncDesc->lprgelemdescParam[x].tdesc);
        while (ptd->vt == VT_PTR)
            ptd = ptd->lptdesc;

        // if it's a userdefined type, copy over the hreftype
        //
        if (ptd->vt == VT_USERDEFINED) {
            hr = _CopyHrefType(pTypeInfo, pcti, &(ptd->hreftype));
            CLEANUP_ON_FAILURE(hr);
        }
    }

    hr = S_OK;

  CleanUp:
    return hr;
}

//=--------------------------------------------------------------------------=
// FixHrefTypeVarDesc
//=--------------------------------------------------------------------------=
// check out the comment for FixHrefTypeFuncDesc.
//
// Parameters:
//    ITypeInfo *               - [in]
//    ICreateTypeInfo *         - [in]
//    VARDESC *                 - [in]
//
// Output:
//    HRESULT
//
// Notes:
//
HRESULT FixHrefTypeVarDesc
(
    ITypeInfo *pTypeInfo,
    ICreateTypeInfo *pcti,
    VARDESC   *pVarDesc
)
{
    HRESULT hr;
    TYPEDESC *ptd;

    // okay, look in the vardesc for VT_USERDEFINED
    //
    ptd = &(pVarDesc->elemdescVar.tdesc);
    while (ptd->vt == VT_PTR)
        ptd = ptd->lptdesc;

    if (ptd->vt == VT_USERDEFINED) {
        hr = _CopyHrefType(pTypeInfo, pcti, &(ptd->hreftype));
        CLEANUP_ON_FAILURE(hr);
    }

    hr = S_OK;

  CleanUp:
    return hr;
}

//=--------------------------------------------------------------------------=
// _CopyHrefType
//=--------------------------------------------------------------------------=
// Copies the reference from the source to the destination
//
// Parameters:
//    ITypeInfo *           - [in]     source ti
//    ICreateTypeInfo *     - [in]     dest ti
//    HREFTYPE *            - [in/out] hreftype from old typeinfo
//
// Output:
//    HRESULT
//
// Notes:
//
HRESULT _CopyHrefType
(
    ITypeInfo       *ptiSource,
    ICreateTypeInfo *pctiDest,
    HREFTYPE        *phreftype
)
{

    ITypeInfo *ptiRef;
    HRESULT hr;

    hr = ptiSource->GetRefTypeInfo(*phreftype, &ptiRef);
    RETURN_ON_FAILURE(hr);

    hr = pctiDest->AddRefTypeInfo(ptiRef, phreftype);
    ptiRef->Release();
    return hr;
}






