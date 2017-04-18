///////////////////////////////////////////////////////////////////////
//
//  TVNODE.CPP
//
//
//  Copyright 1986-1996 Microsoft Corporation. All Rights Reserved.
///////////////////////////////////////////////////////////////////////


#define STRICT
#include <windows.h>
#include <commctrl.h>
#include <mapix.h>
#include <mapiutil.h>
#include <mapidbg.h>
#include "lasterr.h"
#include "tvdlg.h"


LPSTR g_szNoFolderName = "<No Name>";

//
//  CTVNode::CTVNode
//
CTVNode::CTVNode(LPSPropValue pval, ULONG cProps, LPMDB pmdb)
{
    Assert(cProps == nhtProps);
    Assert(pval);

    m_pval = pval;

    m_htiMe = NULL;
        
    m_fKidsLoaded = FALSE;

    m_pfld = NULL;

    m_pNext = NULL;

    m_pmdb = pmdb;
    if(pmdb)
        pmdb->AddRef();

}

//
//  CTVNode::~CTVNode
//
CTVNode::~CTVNode()
{
    MAPIFreeBuffer(m_pval);
    UlRelease(m_pfld);
    UlRelease(m_pmdb);
}


//
//  CTVNode::HrExpand
//
//  Put all kids of the given folder in the tree control
//
HRESULT CTVNode::HrExpand(CChsFldDlg * pCFDlg)
{
    HRESULT hr;
    LPMAPITABLE ptblHier = NULL;
    LPSRowSet pRowSet = NULL;
    UINT ind;
    
    static SSortOrderSet sosName;

    sosName.cSorts = 1;
    sosName.cCategories = 0;
    sosName.cExpanded = 0;
    sosName.aSort[0].ulPropTag = PR_DISPLAY_NAME;
    sosName.aSort[0].ulOrder = TABLE_SORT_ASCEND;


    Assert(m_htiMe);
    
    if(m_fKidsLoaded || !m_pval[iSubfldrs].Value.b)
        return hrSuccess;

    if(!m_pmdb)
    {
    // this node corresponds to the top level of a message store which has
    // not been opend yet.
    // m_pval[iEID] contains entry ID of the message store
    // 
        hr = HrOpenMDB(pCFDlg);
        if(FAILED(hr))
            goto err;
    }
    
    Assert(m_pmdb);     
    
    if(!m_pfld)
    {
        hr = HrOpenFolder(pCFDlg);
        if(FAILED(hr))
            goto err;
    }

    Assert(m_pfld); 
    
    hr = m_pfld->GetHierarchyTable(MAPI_DEFERRED_ERRORS, &ptblHier);
    if(HR_FAILED(hr))
    {
        pCFDlg->m_lsterr.HrSetLastError(hr, m_pfld);
        pCFDlg->m_lsterr.ShowError(pCFDlg->hwDialog());
        
        goto err;
    }

    hr = HrQueryAllRows(ptblHier, (LPSPropTagArray)&spthtProps, NULL, &sosName,
                        0, &pRowSet);
    if(HR_FAILED(hr))
        goto err;

    if(0 == pRowSet->cRows)
    {
        m_pval[iSubfldrs].Value.b = FALSE;
        goto err;
    }

    for(ind = 0; ind < pRowSet->cRows; ++ind)
    {
        LPSPropValue pval = pRowSet->aRow[ind].lpProps;
        
        Assert(pRowSet->aRow[ind].cValues == nhtProps);
        Assert(pval[iEID].ulPropTag == PR_ENTRYID);
        Assert(pval[iDispName].ulPropTag == PR_DISPLAY_NAME);
        Assert(pval[iSubfldrs].ulPropTag == PR_SUBFOLDERS);

        LPTVNODE pNode = NULL;

        hr = pCFDlg->HrCreateNode(pval, nhtProps, m_pmdb, &pNode);
        if(hr)
            goto err;
    
        //this row will be freed in ~CTVNode
        pRowSet->aRow[ind].cValues = 0;
        pRowSet->aRow[ind].lpProps = NULL;

        HTREEITEM hItem;
        
        hItem = AddOneItem(m_htiMe,  TVI_LAST, pCFDlg->IndClsdFld(),
                            pCFDlg->IndOpenFld(), pCFDlg->hwTreeCtl(), pNode,
                            pval[iSubfldrs].Value.b? 1: 0);
        if(!hItem)
        {
            hr = ResultFromScode(MAPI_E_NOT_ENOUGH_MEMORY);
            goto err;
        }
            
    }

    m_fKidsLoaded = TRUE;

err:
    UlRelease(ptblHier);
    FreeProws(pRowSet);

    DebugTraceResult(CTVNode::HrExpand, hr);
    return hr;
}

//
//  CTVNode::HrOpenMDB
//
HRESULT CTVNode::HrOpenMDB(CChsFldDlg * pCFDlg)
{
    HRESULT hr;
    LPMDB pmdb = NULL;
    LPSPropValue pvalIPM = NULL;
    ULONG ulObjType;
    
    Assert(m_pval[iEID].ulPropTag == PR_ENTRYID);

    DebugTrace("ChsFld: Openning Msg Store: %s\n", GetName());
    
    hr = pCFDlg->Session()->OpenMsgStore(0L, m_pval[iEID].Value.bin.cb,
                                (LPENTRYID)m_pval[iEID].Value.bin.lpb,
                                NULL, MAPI_BEST_ACCESS, &pmdb);
    if(hr) //Display warning messages too
    {
        pCFDlg->m_lsterr.HrSetLastError(hr, pCFDlg->Session());
        pCFDlg->m_lsterr.ShowError(pCFDlg->hwDialog());
    }

    if(HR_FAILED(hr))
        goto err;

    hr = HrGetOneProp(pmdb, PR_IPM_SUBTREE_ENTRYID, &pvalIPM);
    if(hr)
    {
        pCFDlg->m_lsterr.HrSetLastError(hr, pmdb);
        pCFDlg->m_lsterr.ShowError(pCFDlg->hwDialog());

        goto err;
    }

    hr = pmdb->OpenEntry(pvalIPM->Value.bin.cb,
                (LPENTRYID)pvalIPM->Value.bin.lpb,
                NULL, MAPI_BEST_ACCESS | MAPI_DEFERRED_ERRORS,
                 &ulObjType, (LPUNKNOWN *) &m_pfld);
    if(HR_FAILED(hr))
    {
        pCFDlg->m_lsterr.HrSetLastError(hr, pmdb);
        pCFDlg->m_lsterr.ShowError(pCFDlg->hwDialog());
        
        goto err;
    }
    
    Assert(MAPI_FOLDER == ulObjType);

/*  if(pvalIPM->Value.bin.cb > m_pval[iEID].Value.bin.cb)
    {
        if(hr = MAPIAllocateMore(pvalIPM->Value.bin.cb,
                        m_pval, (LPVOID *)&m_pval[iEID].Value.bin.lpb))
            goto err;
                
    }

    CopyMemory(m_pval[iEID].Value.bin.lpb, pvalIPM->Value.bin.lpb,
                                        pvalIPM->Value.bin.cb);
    m_pval[iEID].Value.bin.cb = pvalIPM->Value.bin.cb;*/

err:
    if(HR_FAILED(hr))
    {
        UlRelease(pmdb);
        UlRelease(m_pfld);
        m_pfld = NULL;
    }
    else
    {
        m_pmdb = pmdb;
        hr = hrSuccess; //don't return warnings
    }

    MAPIFreeBuffer(pvalIPM);

    DebugTraceResult(CTVNode::HrOpenMDB, hr);
    return hr;
}

//
//  CTVNode::HrOpenFolder
//
HRESULT CTVNode::HrOpenFolder(CChsFldDlg * pCFDlg)
{
    HRESULT hr;
    ULONG ulObjType;

    Assert(m_pval[iEID].ulPropTag == PR_ENTRYID);
    Assert(m_pmdb);
    
    // MAPI_MODIFY flag affects only IMAPIProp interface of the object.
    // It does not guarantee permission to create subfolders.
    hr = m_pmdb->OpenEntry(m_pval[iEID].Value.bin.cb,
                (LPENTRYID)m_pval[iEID].Value.bin.lpb,
                NULL, MAPI_BEST_ACCESS | MAPI_DEFERRED_ERRORS,
                 &ulObjType, (LPUNKNOWN *) &m_pfld);
    if(HR_FAILED(hr))
    {
        pCFDlg->m_lsterr.HrSetLastError(hr, m_pmdb);
        pCFDlg->m_lsterr.ShowError(pCFDlg->hwDialog());
        
        goto err;
    }
    
    Assert(MAPI_FOLDER == ulObjType);
err:

    DebugTraceResult(CTVNode::HrOpenFolder, hr);
    return hr;

}

//
//  CTVNode::HrGetFolder
//
//  return folder interface for the node
HRESULT CTVNode::HrGetFolder(CChsFldDlg * pCFDlg,
                            LPMAPIFOLDER * ppfld, LPMDB *ppmdb)
{
    HRESULT hr = hrSuccess;
    
    Assert(pCFDlg);
    Assert(ppfld);
    Assert(ppmdb);


    if(!m_pmdb)
    {
        hr = HrOpenMDB(pCFDlg);
        if(FAILED(hr))
            goto err;
    }
    Assert(m_pmdb);
    
    if(!m_pfld)
    {
        Assert(!m_fKidsLoaded);
        
        hr = HrOpenFolder(pCFDlg);
        if(FAILED(hr))
            goto err;

    }
    Assert(m_pfld);

    *ppfld = m_pfld;
    m_pfld->AddRef();

    m_pmdb->AddRef();
    *ppmdb = m_pmdb;            

err:

    DebugTraceResult(CTVNode::HrGetFolder, hr);
    return hr;
}


//
//  CTVNode::HrNewFolder
//
// Create subfolder szFldName
//
HRESULT CTVNode::HrNewFolder(CChsFldDlg * pCFDlg,
                                     LPSTR szFldName)
{
    HRESULT hr;
    LPMAPIFOLDER pfldNew = NULL;
    LPTVNODE pNode = NULL;
    LPSPropValue pval = NULL;
    HTREEITEM hItem;

    Assert(szFldName);
    Assert(pCFDlg);
    

    if(!m_pmdb)
    {
        hr = HrOpenMDB(pCFDlg);
        if(FAILED(hr))
            goto err;
    }

    Assert(m_pmdb);
    
    if(!m_pfld)
    {
        hr = HrOpenFolder(pCFDlg);
        if(FAILED(hr))
            goto err;
    }

    Assert(m_pmdb);
    
    hr = m_pfld->CreateFolder(FOLDER_GENERIC, szFldName, NULL,
                                NULL, 0, &pfldNew);
    if(HR_FAILED(hr))
    {
        pCFDlg->m_lsterr.HrSetLastError(hr, m_pfld);
        pCFDlg->m_lsterr.ShowError(pCFDlg->hwDialog());

        goto err;
    }

    if(!m_pval[iSubfldrs].Value.b)
    {
        m_pval[iSubfldrs].Value.b = TRUE;

        TV_ITEM tvI;

        tvI.hItem           = m_htiMe;
        tvI.mask            = TVIF_CHILDREN;
        tvI.cChildren       = 1;

        TreeView_SetItem(pCFDlg->hwTreeCtl(), &tvI);
    }

    if(m_fKidsLoaded)
    {
        hr = MAPIAllocateBuffer(sizeof(SPropValue)* nhtProps, (LPVOID *)&pval);
        if(hr)
            goto err;

        ZeroMemory(pval, sizeof(SPropValue) * nhtProps );

        pval[iEID].ulPropTag = PR_ENTRYID;
        pval[iDispName].ulPropTag = PR_DISPLAY_NAME;
        pval[iSubfldrs].ulPropTag = PR_SUBFOLDERS;

        pval[iSubfldrs].Value.b = FALSE;

        int cb = lstrlen(szFldName) + 1;
        hr = MAPIAllocateMore(cb, pval, (LPVOID *)&pval[iDispName].Value.lpszA);
        if(hr) 
            goto err;

        lstrcpy(pval[iDispName].Value.lpszA, szFldName);

        hr = pCFDlg->HrCreateNode(pval, nhtProps, m_pmdb, &pNode);
        if(HR_FAILED(hr))
            goto err;

        pval = NULL;

        hItem = AddOneItem(m_htiMe,  TVI_SORT, pCFDlg->IndClsdFld(),
                        pCFDlg->IndOpenFld(), pCFDlg->hwTreeCtl(), pNode, 0);
        if(!hItem)
        {
            hr = ResultFromScode(MAPI_E_NOT_ENOUGH_MEMORY);
            goto err;
        }
            
        pNode->m_pfld = pfldNew;
        pfldNew = NULL;
        
    }

err:
    MAPIFreeBuffer(pval);
    UlRelease(pfldNew);

    DebugTraceResult(CTVNode::HrNewFolder, hr);
    return hr;
}

//
//  CTVNode::Write
//
// Used in CChsFldDlg::HrSaveTreeState
void CTVNode::Write(BOOL fWrite, LONG iLevel, LPBYTE * ppb)
{
    if(fWrite)
        *((LONG *)*ppb) = iLevel;
    *ppb += sizeof(LONG);

    if(iLevel != 0)
    {
        ULONG cb = m_pval[iEID].Value.bin.cb;
        
        if(fWrite)
            *((ULONG *)*ppb) = cb;
        *ppb += sizeof(ULONG);

        if(fWrite)
            CopyMemory(*ppb, m_pval[iEID].Value.bin.lpb, cb);
        *ppb += Align4(cb);
    }
    else
    {
        Assert(m_pval[iDispName].Value.lpszA == g_szAllStores);
    }

}

LPVOID CTVNode::operator new( size_t cb )
{
    LPVOID pv;

    if ( MAPIAllocateBuffer( (ULONG)cb, &pv ) )
        pv = NULL;

    return pv; 
}

void CTVNode::operator delete( LPVOID pv )
{
    MAPIFreeBuffer( pv );
}

