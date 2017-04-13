////////////////////////////////////////////////////////////////////////////
//
//      CHSFLD.CPP
//
//
//  Copyright 1986-1996 Microsoft Corporation. All Rights Reserved.
///////////////////////////////////////////////////////////////////////


#define STRICT
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <mapix.h>
#include <mapiutil.h>
#include <mapidbg.h>
#include "chsfld.h"
#include "lasterr.h"
#include "tvdlg.h"
#include "resource.h"
#include "tvstack.h"



#define cImageHeight    16
#define cImageWidth     16
#define cImages         4

//globals
LPSTR g_szAllStores = "All Message Stores";
LPSTR g_szModuleName = "Choose Folder Dialog";

//functions used only in this file
BOOL CALLBACK
ChsFldDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

HRESULT HrGetNewName(HINSTANCE hInst, HWND hwParent, LPSTR * pszNewName);

BOOL CALLBACK
NewNameDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);


//
//  HrPickFolder
//
//  
STDAPI
HrPickFolder(HINSTANCE hInst, HWND hWnd, LPMAPISESSION pses, LPMAPIFOLDER * ppfld,
                LPMDB *ppmdb, ULONG * pcb, LPBYTE * ppb)
{
    HRESULT hr;
    
    //Assert(hInst);
    
    if((hWnd && !IsWindow(hWnd)) || (!pses) || (!ppfld) || (!ppmdb))
    { 
        DebugTraceResult(HrPickFolder, E_INVALIDARG);
        return E_INVALIDARG;
    }

    if(pcb && IsBadWritePtr(pcb, sizeof(ULONG)))
    {
        DebugTraceArg(HrPickFolder, "pcb not writable");
        return E_INVALIDARG;
    }

    if(pcb && (*pcb & 0x3))
    {
        DebugTraceArg(HrPickFolder, "pcb not multiple of 4");
        return E_INVALIDARG;
    }
    
    if(ppb && IsBadWritePtr(ppb, sizeof(LPBYTE)))
    {
        DebugTraceArg(HrPickFolder, "ppb not writable");
        return E_INVALIDARG;
    }

    if(ppb && pcb && IsBadWritePtr(*ppb, *pcb))
    {
        DebugTraceArg(HrPickFolder, "*pcb or *ppb");
        return E_INVALIDARG;
    }

    //////////////////////////////////////////////////////////////////////
    // if you incorporate this code into you app, remove this and pass in
    // the right hInst
    // Start remove
    hInst = GetModuleHandle("chsfld32.dll");
    if(!hInst)
    {
        DebugTrace("GetModuleHandel failed\n");
        DebugTraceResult(HrPickFolder, E_FAIL);
        return E_FAIL;
    }
    // End remove
    ///////////////////////////////////////////////////////////////////////

    //ULONG cb = 0;
    //LPBYTE pb = NULL;
    
    CChsFldDlg PickDlg(pses, hInst, pcb, ppb);

    InitCommonControls();

    hr = PickDlg.HrPick(MAKEINTRESOURCE(IDD_CFDIALOG), hWnd,
                        (DLGPROC)ChsFldDlgProc, ppfld, ppmdb);

/*  if(SUCCEEDED(hr))
    {
        (*ppfld)->Release();
        (*ppmdb)->Release();
    }
    
    CChsFldDlg PickDlg1(pses, hInst, pcb, ppb);

    hr = PickDlg1.HrPick(MAKEINTRESOURCE(IDD_CFDIALOG), hWnd,
                        (DLGPROC)ChsFldDlgProc, ppfld, ppmdb);*/

//  if(!hr)
    //  MAPIFreeBuffer(pb);
        
    DebugTraceResult(HrPickFolder, hr);
    return hr;
}


//
//  CChsFldDlg::CChsFldDlg
//
inline
CChsFldDlg::CChsFldDlg(LPMAPISESSION pses, HINSTANCE hInst, ULONG * pcb,
                        LPBYTE * ppb)   : m_lsterr(g_szModuleName)
{
    Assert(pses);
    Assert(hInst);
    
    m_pses = pses;
    pses->AddRef();

    m_hr = hrSuccess;
    m_pfld = NULL;
    m_pmdb = NULL;
    m_hiRoot = NULL;
    m_hInst = hInst;
    m_hIml = NULL;
    m_hDlg = NULL;
    m_hwTreeCtl = NULL;
    m_pcbState = pcb;
    m_ppbState = ppb;
}       

//
//  CChsFldDlg::~CChsFldDlg
//
CChsFldDlg::~CChsFldDlg()
{
    UlRelease(m_pses);
    UlRelease(m_pfld);
    UlRelease(m_pmdb);

    if(m_hIml)
        ImageList_Destroy(m_hIml);
}


//
//  CChsFldDlg::SetFolder
//
//  Store the folder chosen by the user
//
inline void CChsFldDlg::SetFolder(LPMAPIFOLDER pfld, LPMDB pmdb)
{
    UlRelease(m_pfld);

    m_pfld = pfld;
    
    if(pfld)
        pfld->AddRef();

    UlRelease(m_pmdb);

    m_pmdb = pmdb;
    if(pmdb)
        pmdb->AddRef();
}


//
//  CChsFldDlg::HrPick
//
// The outmost method.
//
HRESULT CChsFldDlg::HrPick(LPCTSTR lpTemplateName, HWND hWnd,
                DLGPROC pfnDlgProc, LPMAPIFOLDER * ppfld, LPMDB *ppmdb)
{
    if(-1 == DialogBoxParam(m_hInst, lpTemplateName, hWnd, pfnDlgProc, (LPARAM) this))
    {
        DebugTraceSc(CChsDldDlg::HrPick, MAPI_E_NOT_ENOUGH_MEMORY);
        return MAPI_E_NOT_ENOUGH_MEMORY;
    }

    //m_hr is set inside the dialog
    if(HR_SUCCEEDED(m_hr))
    {
        Assert(m_pfld);
        m_pfld->AddRef();
        *ppfld = m_pfld;

        Assert(m_pmdb);
        m_pmdb->AddRef();
        *ppmdb = m_pmdb;
    }

    return m_hr;
}

//
//  CChsFldDlg::HrInitTree
//
// Called from WM_INITDIALOG. Opens all message stores in the profile and
// puts the IPM subtrees in the tree control
//
HRESULT CChsFldDlg::HrInitTree(HWND hDlg, HWND hwTreeCtl)
{
    HRESULT     hr;
    LPSPropValue pval = NULL;
    LPTVNODE    pNode = NULL;
    HTREEITEM   hiRoot = NULL;
    HICON       hIcon = NULL;
    
    Assert(hDlg);
    Assert(hwTreeCtl);

    m_hwTreeCtl = hwTreeCtl;
    m_hDlg      = hDlg;
    

    //
    // Set up the image list
    //
    m_hIml = ImageList_Create(cImageWidth, cImageHeight, ILC_MASK, 
                            cImages, 0);
    if(!m_hIml)
    {
        hr = MAPI_E_NOT_ENOUGH_MEMORY;
        goto err;
    }

    hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ALLSTORES));
    m_iIconAllStores = ImageList_AddIcon(m_hIml, hIcon);
    
    hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ROOTFLD));
    m_iIconRootFld = ImageList_AddIcon(m_hIml, hIcon);
    
    hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_OPENFLD));
    m_iIconOpenFld = ImageList_AddIcon(m_hIml, hIcon);
    
    hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_CLSDFLD));
    m_iIconClsdFld = ImageList_AddIcon(m_hIml, hIcon);

    if(ImageList_GetImageCount(m_hIml) < cImages)
    {
        hr = MAPI_E_NOT_ENOUGH_MEMORY;
        goto err;
    }


    TreeView_SetImageList(hwTreeCtl, m_hIml, TVSIL_NORMAL);
    
    //
    // create the root tree node
    // (fake a GetProps)
    //
    hr = MAPIAllocateBuffer(nhtProps * sizeof(SPropValue),
                        (LPVOID *)&pval);
    if(hr)
    {
        m_lsterr.HrSetLastError(hr);
        m_lsterr.ShowError(hDlg);
            
        goto err;
    }
    

    ZeroMemory(pval, nhtProps * sizeof(SPropValue));

    //Set  proptags to make CNode constructor happy
    pval[iEID].ulPropTag = PR_ENTRYID;
    pval[iDispName].ulPropTag = PR_DISPLAY_NAME;
    pval[iDispName].Value.lpszA = g_szAllStores;
    pval[iSubfldrs].ulPropTag = PR_SUBFOLDERS;

    hr = HrCreateNode(pval, nhtProps, NULL, &pNode);
    if(hr)
        goto err;

    Assert(pNode);
    
    pval = NULL; //will be freed in ~CTVNode

    hiRoot = AddOneItem(NULL, TVI_ROOT, m_iIconAllStores, m_iIconAllStores,
                            hwTreeCtl, pNode, 1);
    if(!hiRoot)
    {
        hr = MAPI_E_NOT_ENOUGH_MEMORY;
        goto err;
    }
    
    pNode->SetKidsLoaded(TRUE);
    
    m_hiRoot = hiRoot;
    
    //
    //  Put the IPM subtrees of all the message stores in
    //
    hr = HrLoadRoots();
    if(HR_FAILED(hr))
        goto err;

    (void)HrRestoreTreeState();
        
err:
    MAPIFreeBuffer(pval);

    DebugTraceResult(CChsFldDlg::HrInitTree, hr);
    return hr;
}


//
//  CChsFldDlg::HrLoadRoots
//
HRESULT CChsFldDlg::HrLoadRoots(void)
{
    HRESULT hr;
    LPMAPITABLE ptblMStrs = NULL;
    UINT ind;
    LPSRowSet pRows = NULL;
    static SSortOrderSet sosName;

    sosName.cSorts = 1;
    sosName.cCategories = 0;
    sosName.cExpanded = 0;
    sosName.aSort[0].ulPropTag = PR_DISPLAY_NAME;
    sosName.aSort[0].ulOrder = TABLE_SORT_ASCEND;

        
    //Get Message Store Table
    hr = m_pses->GetMsgStoresTable(0, &ptblMStrs);
    if(hr)
    {
        m_lsterr.HrSetLastError(hr, m_pses);
        m_lsterr.ShowError(m_hDlg);

        goto err;
    }

    //For each msg store insert a node corresponding to PR_IPM_SUBTREE

    hr = HrQueryAllRows(ptblMStrs, (LPSPropTagArray) &spthtProps, NULL,
                        &sosName, 0, &pRows);
                        
    if(HR_FAILED(hr))
        goto err;

    if(0 ==  pRows->cRows)  //$ No stores
    {
        MessageBox(m_hDlg,
                    "No message stores in the profile",
                    g_szModuleName,
                    MB_OK);
        hr = E_FAIL;
    }
    
    for(ind = 0; ind < pRows->cRows; ++ind)
    {
        LPSPropValue pval = pRows->aRow[ind].lpProps;
        Assert(pRows->aRow[ind].cValues == nhtProps);
        Assert(pval[iEID].ulPropTag == PR_ENTRYID);

        pval[iSubfldrs].ulPropTag = PR_SUBFOLDERS;
        pval[iSubfldrs].Value.b = TRUE;

        //pval is consumed by this function
        hr = HrInsertRoot(pval);
        pRows->aRow[ind].cValues = 0;
        pRows->aRow[ind].lpProps = NULL;
        if(FAILED(hr))
            goto err;
        
    }

    
        
err:
    FreeProws(pRows);
    UlRelease(ptblMStrs);

    DebugTraceResult(CChsFldDlg::HrLoadRoots, hr);
    return hr;
}

//
//  CChsFldDlg::HrInsertRoot
//
// Put the IPM subtree of the msg store in the tree control
//  pval is consumed
//
HRESULT CChsFldDlg::HrInsertRoot(LPSPropValue pval)
{
    HRESULT hr;
    HTREEITEM hItem;


    Assert(m_hiRoot);
    
    
    LPTVNODE pNode = NULL;
    hr = HrCreateNode(pval, nhtProps, NULL, &pNode);
    if(hr)
    {
        MAPIFreeBuffer(pval);
        goto err;
    }

    Assert(pNode);
    pval = NULL;

        
    hItem = AddOneItem(m_hiRoot, TVI_LAST, m_iIconRootFld, m_iIconRootFld,
                            m_hwTreeCtl, pNode, 1);
    if(!hItem)
    {
        hr = MAPI_E_NOT_ENOUGH_MEMORY;
        goto err;
    }
            
        
err:

    DebugTraceResult(CChsFldDlg::HrInsertRoots, hr);
    return hr;
}


//
//  CChsFldDlg::HrSaveTreeState
//
// Save expand - collapse state of the tree control
//
HRESULT CChsFldDlg::HrSaveTreeState(void)
{
    HRESULT hr;

    if(!m_pcbState || !m_ppbState)
        return hrSuccess;

    MAPIFreeBuffer(*m_ppbState);
    *m_ppbState = NULL;
    *m_pcbState = 0;
    
    hr = HrSaveTreeStateEx(FALSE, m_pcbState, NULL);
    if(hr)
        goto err;

    DebugTrace("ChsFld: size of state data: %ld\n", *m_pcbState);
    
    hr = HrSaveTreeStateEx(TRUE, m_pcbState, m_ppbState);
    
err:
    DebugTraceResult(CChsFldDlg::HrSaveTreeState, hr);
    return hr;
}

//
//  CChsFldDlg::HrSaveTreeStateEx
//
// Save expand - collapse state of the tree control
//
HRESULT CChsFldDlg::HrSaveTreeStateEx(BOOL fWrite, ULONG * pcb, LPBYTE * ppb)
{
    HRESULT hr = hrSuccess;
    CTIStack tiStack;
    HTREEITEM hti;
    LPBYTE pb = NULL;
    LPBYTE pBuffer = NULL;
    LONG iLevel;

    if(fWrite)
    {
        if(*pcb == 0)
        {
            *ppb = NULL;
            return hrSuccess;
        }
        else
        {
            hr = MAPIAllocateBuffer(*pcb, (LPVOID *) &pBuffer);
            if (hr)
            {
                *pcb = 0;
                return hr;
            }
            pb = pBuffer;
        }
    }

    hti = TreeView_GetRoot(m_hwTreeCtl);
    iLevel = 0;
    tiStack.Push(NULL);

    while(hti)
    {
        Assert(iLevel >= 0);
        
        while(hti)
        {
            TV_ITEM tvi;
            
            tvi.hItem = hti;
            tvi.mask = TVIF_STATE | TVIF_PARAM;
            tvi.lParam = 0;
            tvi.state = 0;
            tvi.stateMask = TVIS_EXPANDED;

            if(!TreeView_GetItem(m_hwTreeCtl, &tvi))
            {
                hr = E_FAIL;
                goto err;
            }

            if(tvi.state & TVIS_EXPANDED)
            {
                HTREEITEM htiChild = TreeView_GetChild(m_hwTreeCtl, hti);

                if(htiChild)
                {
                    LPTVNODE pNode = (LPTVNODE) tvi.lParam;
                    Assert(pNode);

                    pNode->Write(fWrite, iLevel, &pb);

                    HTREEITEM htiNextSibl = TreeView_GetNextSibling(m_hwTreeCtl, hti);

                    tiStack.Push(htiNextSibl);

                    hti = htiChild;
                    ++iLevel;

                    continue;
                }

            }

            hti = TreeView_GetNextSibling(m_hwTreeCtl, hti);
        }

        do
        {
            hti = tiStack.Pop();
            --iLevel;
            
        }while(!tiStack.IsEmpty() && hti == NULL);
    }

    Assert(iLevel == -1);

    *pcb = pb - pBuffer;
    if(pBuffer)
        *ppb = pBuffer;
    
err:
    DebugTraceResult(CChsFldDlg::HrSaveTreeStateEx, hr);
    return hr;
}

inline LONG GetLevel(LPBYTE * ppb)
{
    LONG level = *((LONG *) *ppb);

    *ppb += sizeof(LONG);

    return level;
}

inline ULONG GetCb(LPBYTE * ppb)
{
    ULONG cb = *((ULONG *) *ppb);

    *ppb += sizeof(ULONG);

    return cb;
}

HTREEITEM HtiFindChild(HWND hwTreeCtl, HTREEITEM hti, ULONG cb,
                    LPENTRYID pbEID, CChsFldDlg *pCFDlg, LPTVNODE *ppNode)
{
    HRESULT hr;
    HTREEITEM htiChild;

    htiChild = TreeView_GetChild(hwTreeCtl, hti);
    
    while(htiChild)
    {
        TV_ITEM tvi;
        
        tvi.hItem = htiChild;
        tvi.mask = TVIF_PARAM;
        tvi.lParam = 0;

        if(!TreeView_GetItem(hwTreeCtl, &tvi))
            return NULL;

        LPTVNODE pNode = (LPTVNODE) tvi.lParam;
        Assert(pNode);

        ULONG ulMatch = 0;
        hr = pCFDlg->Session()->CompareEntryIDs(cb, pbEID,
                            pNode->m_pval[iEID].Value.bin.cb,
                            (LPENTRYID)pNode->m_pval[iEID].Value.bin.lpb,
                            0, &ulMatch);
        if(SUCCEEDED(hr))
        {
            if(ulMatch)
            {
                *ppNode = pNode;
                return htiChild;
            }
        }

        htiChild = TreeView_GetNextSibling(hwTreeCtl, htiChild);
    }

    return htiChild;
}

//
//  CChsFldDlg::HrRestoreTreeState
//
HRESULT CChsFldDlg::HrRestoreTreeState(void)
{
    HRESULT hr = hrSuccess;
    LPBYTE pb;
    LPBYTE pbMax;
    CTIStack tiStack;
    HTREEITEM hti;
    LONG iLevel = 0;
    BOOL fNodeMissing = FALSE;

    if(!m_pcbState  || *m_pcbState == 0)
        return hrSuccess;

    try //protect ourself from callers who mess with the state data
    {
    Assert(m_hwTreeCtl);

    Assert(m_ppbState);
    pb = *m_ppbState;

    pbMax = pb + *m_pcbState;
    
    hti = TreeView_GetRoot(m_hwTreeCtl);

    iLevel = GetLevel(&pb);
    Assert(iLevel == 0);

    TreeView_Expand(m_hwTreeCtl, hti, TVE_EXPAND);
    
    while(hti)
    {
        if(pb >= pbMax)
            break; //done
            
        LONG iNewLevel = GetLevel(&pb);

        if(iNewLevel <= iLevel)
        {
            do
            {
                hti = tiStack.Pop();
                --iLevel;
            }while(iLevel >= iNewLevel);

            Assert(hti);
        }

        if(iNewLevel > iLevel)
        {
            if(!fNodeMissing)
                Assert(iNewLevel == iLevel + 1);

            ULONG cbEID = GetCb(&pb);
            LPENTRYID pbEID = (LPENTRYID)pb;
            pb += Align4(cbEID);

            if(iNewLevel != iLevel +1)
                continue;
                
            LPTVNODE pNodeChild = NULL;
            HTREEITEM htiChild = HtiFindChild(m_hwTreeCtl, hti, cbEID, pbEID,
                                            this, &pNodeChild);
            if(htiChild)
            {
                fNodeMissing = FALSE;
                
                hr = pNodeChild->HrExpand(this);
                if(FAILED(hr))
                    goto err;

                TreeView_Expand(m_hwTreeCtl, htiChild, TVE_EXPAND);
                
                tiStack.Push(hti);

                hti = htiChild;
                ++iLevel;

                continue;
            }
            else
            {
                //Assert(FALSE); //$ handle
                fNodeMissing = TRUE;
            }

        }
        /*else
        {
            do
            {
                hti = tiStack.Pop();
                --iLevel;
            }while(iLevel >= iNewLevel);
        }*/
    }
    }

    catch(...)
    {
        DebugTrace("chsfld: Exception caught in HrRestoreTreeState\n");
        hr = E_FAIL;
    }
    
err:

    /*MAPIFreeBuffer(*m_ppbState);
    *m_ppbState = NULL;
    *m_pcbState = 0;*/
    
    
    DebugTraceResult(CChsFldDlg::HrRestoreTreeState, hr);
    return hr;
}


//////////////////////////////////////////////////////////////////////////
// CTVNodeFactory

//
//  CTVNodeFactory::CTVNodeFactory
//
inline CTVNodeFactory::CTVNodeFactory()
{
    m_pHead = NULL;
}

//
//  CTVNodeFactory::~CTVNodeFactory
//
//  Destroy all created CTVNode s
CTVNodeFactory::~CTVNodeFactory()
{
    while(m_pHead)
    {
        LPTVNODE ptemp = m_pHead;

        m_pHead = m_pHead->m_pNext;

        delete ptemp;
    }
}


//
//  CTVNodeFactory::HrCreateNode
//
// All instances of CTVNode are created through this method
//
HRESULT CTVNodeFactory::HrCreateNode(LPSPropValue pval, ULONG cVals, LPMDB pmdb,
                                        LPTVNODE * pptvNode)
{
    HRESULT hr = hrSuccess;

    LPTVNODE pNode = new CTVNode(pval, cVals, pmdb);
    
    if(!pNode)
    {
        hr = MAPI_E_NOT_ENOUGH_MEMORY;
        goto err;
    }

    Insert(pNode);

    *pptvNode = pNode;
            
err:

    DebugTraceResult(CTVNodeFactory::HrCreateNode, hr);
    return hr;
}


//
//  CTVNodeFactory::Insert
//
// Store all created CTVNode s so that we can destroy them when we are done
//
void CTVNodeFactory::Insert(LPTVNODE pNode)
{
    pNode->m_pNext = m_pHead;
    m_pHead = pNode;
}


//
//  ChsFldDlgProc
//
// Dialog proc for the choose folder dialog
//
//  Controls:
//          IDOK        "OK"
//          IDCANCEL    "Cancel"
//          IDC_NEWFLD  "New Folder"
//
BOOL CALLBACK
ChsFldDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HRESULT hr;
    CChsFldDlg * pCDlg = NULL;
    HWND hwTreeCtl = NULL;
    int wmId;
    int wmEvent;
    HTREEITEM hti = NULL;
    TV_ITEM tvi;
        
    switch(msg)
    {
    case WM_INITDIALOG:
        Assert(lParam);
        pCDlg = (CChsFldDlg *)lParam;

        hwTreeCtl = GetDlgItem(hDlg, IDC_TREEVIEW);
        Assert(hwTreeCtl);

        hr = pCDlg->HrInitTree(hDlg, hwTreeCtl);
        if(HR_FAILED(hr))
        {
            pCDlg->SetError(hr);
            EndDialog(hDlg, 1);
            break;
        }

        SetWindowLong(hDlg, DWL_USER, (LONG)pCDlg);

        break;

    case WM_COMMAND:
        wmId = GET_WM_COMMAND_ID(wParam, lParam);  
        wmEvent = GET_WM_COMMAND_CMD(wParam, lParam);

        hwTreeCtl = GetDlgItem(hDlg, IDC_TREEVIEW);
        Assert(hwTreeCtl);

        pCDlg = (CChsFldDlg *)GetWindowLong(hDlg, DWL_USER);
        Assert(pCDlg);


        switch(wmId)
        {
        case IDOK:
            switch (wmEvent)
            {
            case BN_CLICKED:
                        
                hti = TreeView_GetSelection(hwTreeCtl);
                AssertSz(hti, "No Selection?");

                tvi.hItem = hti;
                tvi.mask = TVIF_PARAM;

                if(TreeView_GetItem(hwTreeCtl, &tvi))
                {
                    LPTVNODE pNode = (LPTVNODE)tvi.lParam;
                    Assert(pNode);

                    LPMAPIFOLDER pfld = NULL;
                    LPMDB pmdb = NULL;

                    hr = pNode->HrGetFolder(pCDlg, &pfld, &pmdb);
                    if(HR_SUCCEEDED(hr))
                    {
                        pCDlg->SetFolder(pfld, pmdb);
                        pfld->Release();
                        pmdb->Release();

                        hr = pCDlg->HrSaveTreeState();                  
                    }
                    else
                    {
                        pCDlg->SetError(hr);
                    }
                }
                else
                {
                    pCDlg->SetError(E_FAIL);
                }

                EndDialog(hDlg, TRUE);

                break;

            default:
                return FALSE;
            }
            break;

        case IDC_NEWFLD:
            switch(wmEvent)
            {
            case BN_CLICKED:
                
                hti = TreeView_GetSelection(hwTreeCtl);
                AssertSz(hti, "No Selection?");

                tvi.hItem = hti;
                tvi.mask = TVIF_PARAM;

                if(TreeView_GetItem(hwTreeCtl, &tvi))
                {
                    LPTVNODE pNode = (LPTVNODE)tvi.lParam;
                    Assert(pNode);
                    LPSTR szName = NULL;
                    
                    do
                    {
                        hr = HrGetNewName(pCDlg->hInst(), hDlg, &szName);
                        if(HR_SUCCEEDED(hr))
                        {
                            hr = pNode->HrNewFolder(pCDlg, szName);
                        }
                    }while(hr == MAPI_E_COLLISION);

                    MAPIFreeBuffer(szName);
                    szName = NULL;

                }

                SetFocus(hwTreeCtl);

                break;

            default:
                return FALSE;
            }
            break;
    
        case IDCANCEL:
            switch(wmEvent)
            {
            case BN_CLICKED:

                pCDlg->SetError(MAPI_E_USER_CANCEL);

                EndDialog(hDlg, TRUE);
                break;

            default:
                return FALSE;
            }
            break;
        }
        break;
        
    case WM_NOTIFY:
        switch( ((LPNMHDR)lParam)->code)
        {
        case TVN_ITEMEXPANDING:
            {
            Assert(((LPNMHDR)lParam)->idFrom == IDC_TREEVIEW);

            NM_TREEVIEW * ptntv = (NM_TREEVIEW *)lParam;

            if(ptntv->action != TVE_EXPAND)
                return FALSE;

            //
            // If the kids of this node are not loaded, load'em 
            LPTVNODE pNode = (LPTVNODE)ptntv->itemNew.lParam;
            Assert(pNode);

            hwTreeCtl = ((LPNMHDR)lParam)->hwndFrom;
            
            pCDlg = (CChsFldDlg *)GetWindowLong(hDlg, DWL_USER);
            //Assert(pCDlg);

            hr = pNode->HrExpand(pCDlg);  
            if(HR_FAILED(hr))
            {
                return TRUE;
            }
                return FALSE;
            }   
            break;
        case TVN_GETDISPINFO:
            {
            Assert(((LPNMHDR)lParam)->idFrom == IDC_TREEVIEW);

            //
            // we don't give folder names to the tree control (to save space)
            // when it wants to display an item, it asks us for the name
            //
            TV_DISPINFO * pdi = (TV_DISPINFO *)lParam;

            if(pdi->item.mask & TVIF_TEXT)
            {
                pdi->item.pszText = ((LPTVNODE)pdi->item.lParam)->GetName();
                return TRUE;
            }
            else
            {
                return FALSE;
            }
            }

            break;
            
        case TVN_SELCHANGED:
            //
            //Enable "OK" and "New Folder" buttons only if it is not the 
            //root node
            //
            {Assert(((LPNMHDR)lParam)->idFrom == IDC_TREEVIEW);

            NM_TREEVIEW *ptntv = (NM_TREEVIEW *)lParam;

            pCDlg = (CChsFldDlg *)GetWindowLong(hDlg, DWL_USER);
            Assert(pCDlg);
    
            EnableWindow(GetDlgItem(hDlg, IDOK),
                        !pCDlg->IsTreeRoot(ptntv->itemNew.hItem));
            EnableWindow(GetDlgItem(hDlg, IDC_NEWFLD),
                        !pCDlg->IsTreeRoot(ptntv->itemNew.hItem));
            break;
            }
            
            break;
        }
        
        break;
        
    default:
        return FALSE;   
    }
    return TRUE;
}

//
//  AddOneItem
//
// Add a node to the tree control
//
HTREEITEM AddOneItem( HTREEITEM hParent, HTREEITEM hInsAfter, 
    int iImage, int iImageSel, HWND hwndTree, LPTVNODE pNode, int cKids)
{
    HTREEITEM hItem;
    TV_INSERTSTRUCT tvIns;

    tvIns.item.mask             = TVIF_CHILDREN | TVIF_PARAM |TVIF_TEXT |
                                    TVIF_IMAGE | TVIF_SELECTEDIMAGE;
    tvIns.item.pszText          = LPSTR_TEXTCALLBACK;
    tvIns.item.cchTextMax       = 0;
    tvIns.item.lParam           = (LPARAM)pNode;
    tvIns.item.cChildren        = cKids;
    tvIns.item.iImage           = iImage;
    tvIns.item.iSelectedImage   = iImageSel;

    tvIns.hInsertAfter = hInsAfter;
    tvIns.hParent = hParent;
    
    // Insert the item into the tree.
    hItem = TreeView_InsertItem(hwndTree, &tvIns);

    pNode->SetHandle(hItem);

    return (hItem);
}


//
//  HrGetNewName
//
//  Display dialog asking the user for a new folder name 
//
//  If *pszNewName is not NULL, it has to be a string allocated with
//  MAPIAllocateBuffer. It will be displayed in the dialog.
//  The returned string has to be freed with MAPIFreeBuffer.
//
HRESULT HrGetNewName(HINSTANCE hInst, HWND hwParent, LPSTR * pszNewName)
{
    Assert(pszNewName);
    
    int nRes = DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_NEWNAME), hwParent,
                        NewNameDlgProc, (LPARAM)pszNewName);
    if(nRes == 1)
    {
        return hrSuccess;
    }
    else
    {
        DebugTraceSc(HrGetNewName, E_FAIL);
        return E_FAIL;
    }
}


//
// NewNameDlgProc
//
// Dlg proc for the "New Name" dialog;
// If user chooses OK, return 1 from EndDialog.
//
BOOL CALLBACK
NewNameDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int wmId;
    int wmEvent;

    switch(msg)
    {
    case WM_INITDIALOG:
        {
        Assert(lParam);

        LPSTR * pszName = (LPSTR *)lParam;

        if(*pszName)
        {
            SetWindowText(GetDlgItem(hDlg, IDC_NAME), *pszName);
            MAPIFreeBuffer(*pszName);
            *pszName = NULL;

        }
        
        SetWindowLong(hDlg, DWL_USER, (LONG)lParam);
        SetFocus(GetDlgItem(hDlg, IDC_NAME));
        return FALSE;
        }
        break;

    case WM_COMMAND:
        wmId = GET_WM_COMMAND_ID(wParam, lParam);  
        wmEvent = GET_WM_COMMAND_CMD(wParam, lParam);

        switch(wmId)
        {
        case IDOK:
            switch (wmEvent)
            {
            case BN_CLICKED:
                {
                HWND hwName = GetDlgItem(hDlg, IDC_NAME);
                
                int cb = Edit_GetTextLength(hwName);
                Assert(cb); //OK is disabled when edit control is empty

                LPSTR szName = NULL;
                if(!MAPIAllocateBuffer(cb + 1, (LPVOID *)&szName))
                {
                    GetWindowText(hwName, szName, cb+1);

                    LPSTR * pszName = (LPSTR *)GetWindowLong(hDlg, DWL_USER);

                    *pszName = szName;

                    EndDialog(hDlg, 1);
                }
                else
                {
                    EndDialog(hDlg, FALSE);
                    break;
                }
                }
                break;

            default:
                return FALSE;
            }
            
            break;

        case IDCANCEL:
            switch (wmEvent)
            {
            case BN_CLICKED:
                EndDialog(hDlg, FALSE);
                break;

            default:
                return FALSE;
            }
            
            break;

        case IDC_NAME:
            switch(wmEvent)
            {
            case EN_CHANGE:
                Assert((HWND)lParam == GetDlgItem(hDlg, IDC_NAME));

                EnableWindow(GetDlgItem(hDlg, IDOK),
                            Edit_GetTextLength((HWND)lParam));

                break;

            default:
                return FALSE;
            }
                
            break;
        }
    default:
        return FALSE;
    }   
        
    return TRUE;
}

