////////////////////////////////////////////////////////////////////////////
//
//      TVDLG.H
//
//  Copyright 1986-1996 Microsoft Corporation. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////

#ifndef __TVDLG__H__
#define __TVDLG__H__


enum { iEID, iDispName, iSubfldrs, nhtProps};
static SizedSPropTagArray(nhtProps, spthtProps) =
{ nhtProps,
    {   PR_ENTRYID,
        PR_DISPLAY_NAME,
        PR_SUBFOLDERS
    }
};  

#define Align4(_cb) (((_cb) + 3) & ~3)

extern LPSTR g_szNoFolderName;
extern LPSTR g_szAllStores;

class CTVNodeFactory;
class CChsFldDlg;


/////////////////////////////////////////////////////////////////////////
// CTVNode

class CTVNode;
typedef CTVNode * LPTVNODE;

class CTVNode
{

friend CTVNodeFactory;
friend HTREEITEM HtiFindChild(HWND hwTreeCtl, HTREEITEM hti, ULONG cb,
                LPENTRYID pbEID, CChsFldDlg *pCFDlg, LPTVNODE *ppNode);


public:
    LPSTR GetName(void);
    HRESULT HrExpand(CChsFldDlg * pCFDlg);
    HRESULT HrGetFolder(CChsFldDlg * pCFDlg, LPMAPIFOLDER * ppfld,
                            LPMDB *ppmdb);

    void SetHandle(HTREEITEM hItem) { m_htiMe = hItem;}
    void SetKidsLoaded(BOOL fLoaded) { m_fKidsLoaded = fLoaded;}

    HRESULT HrNewFolder(CChsFldDlg * pCFDlg, LPSTR szFldName);

    static LPVOID operator new( size_t cb );
    static VOID   operator delete( LPVOID pv );

    void Write(BOOL fWrite, LONG iLevel, LPBYTE * ppb);
    
    ~CTVNode();

private:
    
    //can only be created in CTVNodeFactory::HrCreateNode
    CTVNode(LPSPropValue pvals, ULONG cprops, LPMDB pmdb);

    HRESULT HrOpenMDB(CChsFldDlg * pCFDlg);
    HRESULT HrOpenFolder(CChsFldDlg * pCFDlg);
    
    HTREEITEM       m_htiMe;
    LPSPropValue    m_pval;
    BOOL            m_fKidsLoaded;
    LPMAPIFOLDER    m_pfld;
    CTVNode         *m_pNext;
    LPMDB           m_pmdb;
};




//
//  CTVNode::GetName
//
inline LPSTR CTVNode::GetName(void)
{

    if(m_pval[iDispName].ulPropTag == PR_DISPLAY_NAME)
        return m_pval[iDispName].Value.lpszA;
    else
        return g_szNoFolderName;
}


////////////////////////////////////////////////////////////////////////
// CTVNodeFactory

class CTVNodeFactory
{
public:
    HRESULT HrCreateNode(LPSPropValue pval, ULONG cVals, LPMDB pmdb,
                            LPTVNODE * pptvnode);

    CTVNodeFactory();
    ~CTVNodeFactory();

private:
    void Insert(CTVNode * ptvnode);

    LPTVNODE    m_pHead;
};


////////////////////////////////////////////////////////////////////////
// CChsFldDlg

class CChsFldDlg
{
public:
    HRESULT HrPick(LPCTSTR lpTemplateName, HWND hWnd,
                DLGPROC pfnDlgProc, LPMAPIFOLDER * ppfld, LPMDB *ppmdb);
    HRESULT HrInitTree(HWND hDlg, HWND hwTreeCtl);
    HRESULT HrLoadRoots(void);
    HRESULT HrInsertRoot(LPSPropValue pval);
    BOOL    IsTreeRoot(HTREEITEM hti) { return (hti == m_hiRoot); }

    int     IndAllStores(void)  { return m_iIconAllStores; }
    int     IndRootFld(void)    { return m_iIconRootFld; }
    int     IndOpenFld(void)    { return m_iIconOpenFld; }
    int     IndClsdFld(void)    { return m_iIconClsdFld; }
    HWND    hwDialog(void)      { return m_hDlg; }
    HWND    hwTreeCtl(void)     { return m_hwTreeCtl; }

    LPMAPISESSION   Session(void) { return m_pses; }

    
    HINSTANCE hInst(void)   { return m_hInst; }

    HRESULT HrCreateNode(LPSPropValue pval, ULONG cvals, LPMDB pmdb,
                            LPTVNODE * ppNode)
        { return m_NodeFactory.HrCreateNode(pval, cvals, pmdb, ppNode);}

    void    SetFolder(LPMAPIFOLDER plfd, LPMDB pmdb);
    void    SetError(HRESULT hr)    { m_hr = hr;}

    HRESULT HrSaveTreeState(void);
    HRESULT HrRestoreTreeState(void);

    CChsFldDlg(LPMAPISESSION pses, HINSTANCE hInst, ULONG * pcb, LPBYTE * ppb);
    ~CChsFldDlg();

    CLastError      m_lsterr;
    
private:

    HRESULT HrSaveTreeStateEx(BOOL fWrite, ULONG * pcb, LPBYTE * ppb);
    HRESULT HrRestoreTreeState(ULONG cb, LPBYTE pb);
    
    LPMAPISESSION   m_pses;
    LPMAPIFOLDER    m_pfld;
    LPMDB           m_pmdb;
    HRESULT         m_hr;
    HTREEITEM       m_hiRoot;
    HINSTANCE       m_hInst;
    HWND            m_hDlg;
    HWND            m_hwTreeCtl;

    HIMAGELIST      m_hIml;
    int             m_iIconAllStores;
    int             m_iIconRootFld;
    int             m_iIconOpenFld;
    int             m_iIconClsdFld;
    
    ULONG           *m_pcbState;
    LPBYTE          *m_ppbState;
    
    CTVNodeFactory  m_NodeFactory;
    
};


HTREEITEM AddOneItem( HTREEITEM hParent, HTREEITEM hInsAfter, 
    int iImage, int iImageSel, HWND hwndTree, LPTVNODE pNode, int cKids);


#endif //__TVDLG__H__
