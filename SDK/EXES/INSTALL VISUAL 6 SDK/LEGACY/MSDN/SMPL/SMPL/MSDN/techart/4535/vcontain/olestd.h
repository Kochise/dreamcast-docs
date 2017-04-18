/*************************************************************************
**
**    OLE 2.0 Utility Library
**
**    olestd.h
**
**    This file contains file contains data structure defintions,
**    function prototypes, constants, etc. for the common OLE 2.0
**    utilities.
**    These utilities include the following:
**          Debuging Assert/Verify macros
**          HIMETRIC conversion routines
**          reference counting debug support
**          OleStd API's for common compound-document app support
**
**    (c) Copyright Microsoft Corp. 1990 - 1992 All Rights Reserved
**
*************************************************************************/

#ifndef _OLESTD_H_
#define _OLESTD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <commdlg.h>    // needed for LPPRINTDLG
#include <shellapi.h>   // needed for HKEY

STDAPI_(void) OleStdInitialize(HINSTANCE hInstance, HINSTANCE hResInstance);

// string table defines...
#define  IDS_OLESTDNOCREATEFILE   700
#define  IDS_OLESTDNOOPENFILE     701
#define  IDS_OLESTDDISKFULL       702

// special case for 'C' code
#ifndef __cplusplus

typedef struct tagINTERFACEIMPL {
		IUnknownVtbl *       lpVtbl;
		LPVOID                  lpBack;
		int                     cRef;   // interface specific ref count.
} INTERFACEIMPL, * LPINTERFACEIMPL;

#define INIT_INTERFACEIMPL(lpIFace, pVtbl, pBack)   \
		((lpIFace)->lpVtbl = pVtbl, \
			((LPINTERFACEIMPL)(lpIFace))->lpBack = (LPVOID)pBack,   \
			((LPINTERFACEIMPL)(lpIFace))->cRef = 0  \
		)

#ifdef _DEBUG

#define OleDbgQueryInterfaceMethod(lpUnk)   \
		((lpUnk) != NULL ? ((LPINTERFACEIMPL)(lpUnk))->cRef++ : 0)
#define OleDbgAddRefMethod(lpThis, iface)   \
		((LPINTERFACEIMPL)(lpThis))->cRef++

#if _DEBUGLEVEL >= 2

#define OleDbgReleaseMethod(lpThis, iface) \
		(--((LPINTERFACEIMPL)(lpThis))->cRef == 0 ? \
			OleDbgOut("\t" iface "* RELEASED (cRef == 0)\r\n"),1 : \
			 (((LPINTERFACEIMPL)(lpThis))->cRef < 0) ? \
				( \
					DebugBreak(), \
					OleDbgOut(  \
						"\tERROR: " iface "* RELEASED TOO MANY TIMES\r\n") \
				),1 : \
				1)

#else       // if _DEBUGLEVEL < 2

#define OleDbgReleaseMethod(lpThis, iface) \
		(--((LPINTERFACEIMPL)(lpThis))->cRef == 0 ? \
			1 : \
			 (((LPINTERFACEIMPL)(lpThis))->cRef < 0) ? \
				( \
					OleDbgOut(  \
						"\tERROR: " iface "* RELEASED TOO MANY TIMES\r\n") \
		),1 : \
				1)

#endif      // if _DEBUGLEVEL < 2

#else       // !_DEBUG

#define OleDbgQueryInterfaceMethod(lpUnk)
#define OleDbgAddRefMethod(lpThis, iface)
#define OleDbgReleaseMethod(lpThis, iface)

#endif      // _DEBUG
#endif      // !_cplusplus


// docfile definitions
#define STGM_DFRALL (STGM_READWRITE | STGM_TRANSACTED | STGM_SHARE_DENY_WRITE)
#define STGM_DFALL (STGM_READWRITE | STGM_TRANSACTED | STGM_SHARE_EXCLUSIVE)
#define STGM_SALL (STGM_READWRITE | STGM_SHARE_EXCLUSIVE)

/* standard Delay (in msec) to wait before retrying an LRPC call.
**    this value is returned from IMessageFilter::RetryRejectedCall
*/
#define OLESTDRETRYDELAY    (DWORD)5000

/* Cancel the pending outgoing LRPC call.
**    this value is returned from IMessageFilter::RetryRejectedCall
*/
#define OLESTDCANCELRETRY   (DWORD)-1

/*
 * Icon support:
 *
 * The following API's are now OBSOLETE because equivalent API's have been
 * added to the OLE2.DLL library
 *      GetIconOfFile       superceeded by OleGetIconOfFile
 *      GetIconOfClass      superceeded by OleGetIconOfClass
 *      OleUIMetafilePictFromIconAndLabel
 *                          superceeded by OleMetafilePictFromIconAndLabel
 *
 * The following macros are defined for backward compatibility with previous
 * versions of the OLE2UI library. It is recommended that the new Ole* API's
 * should be used instead.
 */
#define GetIconOfFile(hInst, lpszFileName, fUseFileAsLabel) \
	OleGetIconOfFile(lpszFileName, fUseFileAsLabel)

#define GetIconOfClass(hInst, rclsid, lpszLabel, fUseTypeAsLabel) \
	OleGetIconOfClass(rclsid, lpszLabel, fUseTypeAsLabel)

#define OleUIMetafilePictFromIconAndLabel(hIcon,pszLabel,pszSourceFile,iIcon)\
	OleMetafilePictFromIconAndLabel(hIcon, pszLabel, pszSourceFile, iIcon)

// Clipboard Copy/Paste & Drag/Drop support support

//Macro to set all FormatEtc fields
#define SETFORMATETC(fe, cf, asp, td, med, li)   \
	((fe).cfFormat=cf, \
	 (fe).dwAspect=asp, \
	 (fe).ptd=td, \
	 (fe).tymed=med, \
	 (fe).lindex=li)

//Macro to set interesting FormatEtc fields defaulting the others.
#define SETDEFAULTFORMATETC(fe, cf, med)  \
	((fe).cfFormat=cf, \
	 (fe).dwAspect=DVASPECT_CONTENT, \
	 (fe).ptd=NULL, \
	 (fe).tymed=med, \
	 (fe).lindex=-1)

// Macro to test if two FormatEtc structures are an exact match
#define IsEqualFORMATETC(fe1, fe2)  \
	(OleStdCompareFormatEtc(&(fe1), &(fe2)) == 0)

// Clipboard format strings
#define CF_EMBEDSOURCE          TEXT("Embed Source")
#define CF_EMBEDDEDOBJECT       TEXT("Embedded Object")
#define CF_LINKSOURCE           TEXT("Link Source")
#define CF_CUSTOMLINKSOURCE     TEXT("Custom Link Source")
#define CF_OBJECTDESCRIPTOR     TEXT("Object Descriptor")
#define CF_LINKSRCDESCRIPTOR    TEXT("Link Source Descriptor")
#define CF_OWNERLINK            TEXT("OwnerLink")
#define CF_FILENAME             TEXT("FileName")

#define OleStdQueryOleObjectData(lpformatetc)   \
	(((lpformatetc)->tymed & TYMED_ISTORAGE) ?    \
			NOERROR : ( HRESULT )  DV_E_FORMATETC )

#define OleStdQueryLinkSourceData(lpformatetc)   \
	(((lpformatetc)->tymed & TYMED_ISTREAM) ?    \
			NOERROR : ( HRESULT )  DV_E_FORMATETC )

#define OleStdQueryObjectDescriptorData(lpformatetc)    \
	(((lpformatetc)->tymed & TYMED_HGLOBAL) ?    \
			NOERROR : ( HRESULT )  DV_E_FORMATETC )

#define OleStdQueryFormatMedium(lpformatetc, tymd)  \
	(((lpformatetc)->tymed & tymd) ?    \
			NOERROR : ( HRESULT )  DV_E_FORMATETC )

// Make an independent copy of a MetafilePict
#define OleStdCopyMetafilePict(hpictin, phpictout)  \
	(*(phpictout) = OleDuplicateData(hpictin, CF_METAFILEPICT, GHND|GMEM_SHARE))


/* OleStdGetDropEffect
** -------------------
**
** Convert a keyboard state into a DROPEFFECT.
**
** returns the DROPEFFECT value derived from the key state.
**    the following is the standard interpretation:
**          no modifier -- Default Drop     (NULL is returned)
**          CTRL        -- DROPEFFECT_COPY
**          SHIFT       -- DROPEFFECT_MOVE
**          CTRL-SHIFT  -- DROPEFFECT_LINK
**
**    Default Drop: this depends on the type of the target application.
**    this is re-interpretable by each target application. a typical
**    interpretation is if the drag is local to the same document
**    (which is source of the drag) then a MOVE operation is
**    performed. if the drag is not local, then a COPY operation is
**    performed.
*/
#define OleStdGetDropEffect(grfKeyState)    \
	( (grfKeyState & MK_CONTROL) ?          \
		( (grfKeyState & MK_SHIFT) ? DROPEFFECT_LINK : DROPEFFECT_COPY ) :  \
		( (grfKeyState & MK_SHIFT) ? DROPEFFECT_MOVE : 0 ) )

#define OLESTDDROP_NONE         0
#define OLESTDDROP_DEFAULT      1
#define OLESTDDROP_NONDEFAULT   2

// Other useful defines
#define EMBEDDINGFLAG "Embedding"     // Cmd line switch for launching a srvr

#define HIMETRIC_PER_INCH   2540      // number HIMETRIC units per inch
#define PTS_PER_INCH        72        // number points (font size) per inch

#define MAP_PIX_TO_LOGHIM(x,ppli)   MulDiv(HIMETRIC_PER_INCH, (x), (ppli))
#define MAP_LOGHIM_TO_PIX(x,ppli)   MulDiv((ppli), (x), HIMETRIC_PER_INCH)

// Returns TRUE if all fields of the two Rect's are equal, else FALSE.
#define AreRectsEqual(lprc1, lprc2)     \
	(((lprc1->top == lprc2->top) &&     \
	  (lprc1->left == lprc2->left) &&   \
	  (lprc1->right == lprc2->right) && \
	  (lprc1->bottom == lprc2->bottom)) ? TRUE : FALSE)

/****** DEBUG Support *****************************************************/

#ifdef _DEBUG

#ifndef _DBGTRACE
	#define _DEBUGLEVEL 2
#else
	#define _DEBUGLEVEL _DBGTRACE
#endif


#ifdef NOASSERT

#define OLEDBGASSERTDATA
#define OleDbgAssert(a)
#define OleDbgAssertSz(a, b)
#define OleDbgVerify(a)
#define OleDbgVerifySz(a, b)

#else   // ! NOASSERT

STDAPI OleStdAssert(LPOLESTR lpstrExpr, LPOLESTR lpstrMsg,
	LPOLESTR lpstrFileName, UINT iLine);

#define OLEDBGASSERTDATA    \
		static TCHAR _szAssertFile[]= TEXT(__FILE__);

#define OleDbgAssert(a) \
		(!(a) ? OleStdAssert(TEXT(#a), NULL, _szAssertFile, __LINE__) : (HRESULT)1)

#define OleDbgAssertSz(a, b)    \
		(!(a) ? OleStdAssert(TEXT(#a), b, _szAssertFile, __LINE__) : (HRESULT)1)

#endif

#define OleDbgVerify(a) \
		OleDbgAssert(a)

#define OleDbgVerifySz(a, b)    \
		OleDbgAssertSz(a, b)

#define OLEDBGDATA_MAIN(szPrefix)   \
		TCHAR g_szDbgPrefix[] = szPrefix;    \
		OLEDBGASSERTDATA
#define OLEDBGDATA  \
		extern TCHAR g_szDbgPrefix[];    \
		OLEDBGASSERTDATA

#define OLEDBG_BEGIN(lpsz) \
		OleDbgPrintAlways(g_szDbgPrefix,lpsz,1);

#define OLEDBG_END  \
		OleDbgPrintAlways(g_szDbgPrefix,TEXT("End\r\n"),-1);

#define OleDbgOut(lpsz) \
		OleDbgPrintAlways(g_szDbgPrefix,lpsz,0)

#define OleDbgOutNoPrefix(lpsz) \
		OleDbgPrintAlways(TEXT(""),lpsz,0)

#define OleDbgOutRefCnt(lpsz,lpObj,refcnt)      \
		OleDbgPrintRefCntAlways(g_szDbgPrefix,lpsz,lpObj,(ULONG)refcnt)

#define OleDbgOutRect(lpsz,lpRect)      \
		OleDbgPrintRectAlways(g_szDbgPrefix,lpsz,lpRect)

#define OleDbgOutHResult(lpsz,hr)   \
		OleDbgPrintScodeAlways(g_szDbgPrefix,lpsz,GetScode(hr))

#define OleDbgOutScode(lpsz,sc) \
		OleDbgPrintScodeAlways(g_szDbgPrefix,lpsz,sc)

#define OleDbgOut1(lpsz)    \
		OleDbgPrint(1,g_szDbgPrefix,lpsz,0)

#define OleDbgOutNoPrefix1(lpsz)    \
		OleDbgPrint(1,TEXT(""),lpsz,0)

#define OLEDBG_BEGIN1(lpsz)    \
		OleDbgPrint(1,g_szDbgPrefix,lpsz,1);

#define OLEDBG_END1 \
		OleDbgPrint(1,g_szDbgPrefix,TEXT("End\r\n"),-1);

#define OleDbgOutRefCnt1(lpsz,lpObj,refcnt)     \
		OleDbgPrintRefCnt(1,g_szDbgPrefix,lpsz,lpObj,(ULONG)refcnt)

#define OleDbgOutRect1(lpsz,lpRect)     \
		OleDbgPrintRect(1,g_szDbgPrefix,lpsz,lpRect)

#define OleDbgOut2(lpsz)    \
		OleDbgPrint(2,g_szDbgPrefix,lpsz,0)

#define OleDbgOutNoPrefix2(lpsz)    \
		OleDbgPrint(2,TEXT(""),lpsz,0)

#define OLEDBG_BEGIN2(lpsz)    \
		OleDbgPrint(2,g_szDbgPrefix,lpsz,1);

#define OLEDBG_END2 \
		OleDbgPrint(2,g_szDbgPrefix, TEXT("End\r\n"),-1);

#define OleDbgOutRefCnt2(lpsz,lpObj,refcnt)     \
		OleDbgPrintRefCnt(2,g_szDbgPrefix,lpsz,lpObj,(ULONG)refcnt)

#define OleDbgOutRect2(lpsz,lpRect)     \
		OleDbgPrintRect(2,g_szDbgPrefix,lpsz,lpRect)

#define OleDbgOut3(lpsz)    \
		OleDbgPrint(3,g_szDbgPrefix,lpsz,0)

#define OleDbgOutNoPrefix3(lpsz)    \
		OleDbgPrint(3,TEXT(""),lpsz,0)

#define OLEDBG_BEGIN3(lpsz)    \
		OleDbgPrint(3,g_szDbgPrefix,lpsz,1);

#define OLEDBG_END3 \
		OleDbgPrint(3,g_szDbgPrefix,TEXT("End\r\n"),-1);

#define OleDbgOutRefCnt3(lpsz,lpObj,refcnt)     \
		OleDbgPrintRefCnt(3,g_szDbgPrefix,lpsz,lpObj,(ULONG)refcnt)

#define OleDbgOutRect3(lpsz,lpRect)     \
		OleDbgPrintRect(3,g_szDbgPrefix,lpsz,lpRect)

#define OleDbgOut4(lpsz)    \
		OleDbgPrint(4,g_szDbgPrefix,lpsz,0)

#define OleDbgOutNoPrefix4(lpsz)    \
		OleDbgPrint(4,TEXT(""),lpsz,0)

#define OLEDBG_BEGIN4(lpsz)    \
		OleDbgPrint(4,g_szDbgPrefix,lpsz,1);

#define OLEDBG_END4 \
		OleDbgPrint(4,g_szDbgPrefix,TEXT("End\r\n"),-1);

#define OleDbgOutRefCnt4(lpsz,lpObj,refcnt)     \
		OleDbgPrintRefCnt(4,g_szDbgPrefix,lpsz,lpObj,(ULONG)refcnt)

#define OleDbgOutRect4(lpsz,lpRect)     \
		OleDbgPrintRect(4,g_szDbgPrefix,lpsz,lpRect)

#else   //  !_DEBUG

#define OLEDBGDATA_MAIN(szPrefix)
#define OLEDBGDATA
#define OleDbgAssert(a)
#define OleDbgAssertSz(a, b)
#define OleDbgVerify(a)         (a)
#define OleDbgVerifySz(a, b)    (a)
#define OleDbgOutHResult(lpsz,hr)
#define OleDbgOutScode(lpsz,sc)
#define OLEDBG_BEGIN(lpsz)
#define OLEDBG_END
#define OleDbgOut(lpsz)
#define OleDbgOut1(lpsz)
#define OleDbgOut2(lpsz)
#define OleDbgOut3(lpsz)
#define OleDbgOut4(lpsz)
#define OleDbgOutNoPrefix(lpsz)
#define OleDbgOutNoPrefix1(lpsz)
#define OleDbgOutNoPrefix2(lpsz)
#define OleDbgOutNoPrefix3(lpsz)
#define OleDbgOutNoPrefix4(lpsz)
#define OLEDBG_BEGIN1(lpsz)
#define OLEDBG_BEGIN2(lpsz)
#define OLEDBG_BEGIN3(lpsz)
#define OLEDBG_BEGIN4(lpsz)
#define OLEDBG_END1
#define OLEDBG_END2
#define OLEDBG_END3
#define OLEDBG_END4
#define OleDbgOutRefCnt(lpsz,lpObj,refcnt)
#define OleDbgOutRefCnt1(lpsz,lpObj,refcnt)
#define OleDbgOutRefCnt2(lpsz,lpObj,refcnt)
#define OleDbgOutRefCnt3(lpsz,lpObj,refcnt)
#define OleDbgOutRefCnt4(lpsz,lpObj,refcnt)
#define OleDbgOutRect(lpsz,lpRect)
#define OleDbgOutRect1(lpsz,lpRect)
#define OleDbgOutRect2(lpsz,lpRect)
#define OleDbgOutRect3(lpsz,lpRect)
#define OleDbgOutRect4(lpsz,lpRect)

#endif  //  _DEBUG

/*************************************************************************
** Function prototypes
*************************************************************************/

//OLESTD.C
STDAPI_(int) SetDCToAnisotropic(HDC hDC, LPRECT lprcPhysical, LPRECT lprcLogical, LPRECT lprcWindowOld, LPRECT lprcViewportOld);
STDAPI_(int) SetDCToDrawInHimetricRect(HDC, LPRECT, LPRECT, LPRECT, LPRECT);
STDAPI_(int) ResetOrigDC(HDC, int, LPRECT, LPRECT);

STDAPI_(int) XformWidthInHimetricToPixels(HDC, int);
STDAPI_(int) XformWidthInPixelsToHimetric(HDC, int);
STDAPI_(int) XformHeightInHimetricToPixels(HDC, int);
STDAPI_(int) XformHeightInPixelsToHimetric(HDC, int);

STDAPI_(void) XformRectInPixelsToHimetric(HDC, LPRECT, LPRECT);
STDAPI_(void) XformRectInHimetricToPixels(HDC, LPRECT, LPRECT);
STDAPI_(void) XformSizeInPixelsToHimetric(HDC, LPSIZEL, LPSIZEL);
STDAPI_(void) XformSizeInHimetricToPixels(HDC, LPSIZEL, LPSIZEL);
STDAPI_(int) XformWidthInHimetricToPixels(HDC, int);
STDAPI_(int) XformWidthInPixelsToHimetric(HDC, int);
STDAPI_(int) XformHeightInHimetricToPixels(HDC, int);
STDAPI_(int) XformHeightInPixelsToHimetric(HDC, int);

STDAPI_(void) ParseCmdLine(LPSTR, BOOL  *, LPSTR);

STDAPI_(BOOL) OleStdIsOleLink(LPUNKNOWN lpUnk);
STDAPI_(LPUNKNOWN) OleStdQueryInterface(LPUNKNOWN lpUnk, REFIID riid);
STDAPI_(LPSTORAGE) OleStdCreateRootStorage(LPTSTR lpszStgName, DWORD grfMode);
STDAPI_(LPSTORAGE) OleStdOpenRootStorage(LPTSTR lpszStgName, DWORD grfMode);
STDAPI_(LPSTORAGE) OleStdOpenOrCreateRootStorage(LPTSTR lpszStgName, DWORD grfMode);
STDAPI_(LPSTORAGE) OleStdCreateChildStorage(LPSTORAGE lpStg, LPTSTR lpszStgName);
STDAPI_(LPSTORAGE) OleStdOpenChildStorage(LPSTORAGE lpStg, LPTSTR lpszStgName, DWORD grfMode);
STDAPI_(BOOL) OleStdCommitStorage(LPSTORAGE lpStg);
STDAPI OleStdDestroyAllElements(LPSTORAGE lpStg);

STDAPI_(LPSTORAGE) OleStdCreateStorageOnHGlobal(
		HANDLE hGlobal,
		BOOL fDeleteOnRelease,
		DWORD dwgrfMode
);
STDAPI_(LPSTORAGE) OleStdCreateTempStorage(BOOL fUseMemory, DWORD grfMode);
STDAPI OleStdDoConvert(LPSTORAGE lpStg, REFCLSID rClsidNew);
STDAPI_(BOOL) OleStdGetTreatAsFmtUserType(
		REFCLSID        rClsidApp,
		LPSTORAGE       lpStg,
		CLSID *      lpclsid,
		CLIPFORMAT * lpcfFmt,
		LPTSTR *      lplpszType
);
STDAPI OleStdDoTreatAsClass(LPCTSTR lpszUserType, REFCLSID rclsid, REFCLSID rclsidNew);
STDAPI_(BOOL) OleStdSetupAdvises(LPOLEOBJECT lpOleObject, DWORD dwDrawAspect,
					LPTSTR lpszContainerApp, LPTSTR lpszContainerObj,
					LPADVISESINK lpAdviseSink, BOOL fCreate);
STDAPI OleStdSwitchDisplayAspect(
		LPOLEOBJECT             lpOleObj,
		LPDWORD                 lpdwCurAspect,
		DWORD                   dwNewAspect,
		HGLOBAL                 hMetaPict,
		BOOL                    fDeleteOldAspect,
		BOOL                    fSetupViewAdvise,
		LPADVISESINK            lpAdviseSink,
		BOOL *               lpfMustUpdate
);
STDAPI OleStdSetIconInCache(LPOLEOBJECT lpOleObj, HGLOBAL hMetaPict);
STDAPI_(HGLOBAL) OleStdGetData(
		LPDATAOBJECT        lpDataObj,
		CLIPFORMAT          cfFormat,
		DVTARGETDEVICE * lpTargetDevice,
		DWORD               dwAspect,
		LPSTGMEDIUM         lpMedium
);
STDAPI_(void) OleStdMarkPasteEntryList(
		LPDATAOBJECT        lpSrcDataObj,
		LPOLEUIPASTEENTRY   lpPriorityList,
		int                 cEntries
);
STDAPI_(int) OleStdGetPriorityClipboardFormat(
		LPDATAOBJECT        lpSrcDataObj,
		LPOLEUIPASTEENTRY   lpPriorityList,
		int                 cEntries
);
STDAPI_(BOOL) OleStdIsDuplicateFormat(
		LPFORMATETC         lpFmtEtc,
		LPFORMATETC         arrFmtEtc,
		int                 nFmtEtc
);
STDAPI_(void) OleStdRegisterAsRunning(LPUNKNOWN lpUnk, LPMONIKER lpmkFull, DWORD * lpdwRegister);
STDAPI_(void) OleStdRevokeAsRunning(DWORD * lpdwRegister);
STDAPI_(void) OleStdNoteFileChangeTime(LPTSTR lpszFileName, DWORD dwRegister);
STDAPI_(void) OleStdNoteObjectChangeTime(DWORD dwRegister);
STDAPI OleStdGetOleObjectData(
		LPPERSISTSTORAGE    lpPStg,
		LPFORMATETC         lpformatetc,
		LPSTGMEDIUM         lpMedium,
		BOOL                fUseMemory
);
STDAPI OleStdGetLinkSourceData(
		LPMONIKER           lpmk,
		LPCLSID             lpClsID,
		LPFORMATETC         lpformatetc,
		LPSTGMEDIUM         lpMedium
);
STDAPI_(HGLOBAL) OleStdGetObjectDescriptorData(
		CLSID               clsid,
		DWORD               dwAspect,
		SIZEL               sizel,
		POINTL              pointl,
		DWORD               dwStatus,
		LPTSTR               lpszFullUserTypeName,
		LPTSTR               lpszSrcOfCopy
);
STDAPI_(HGLOBAL) OleStdGetObjectDescriptorDataFromOleObject(
		LPOLEOBJECT         lpOleObj,
		LPTSTR               lpszSrcOfCopy,
		DWORD               dwAspect,
		POINTL              pointl,
		LPSIZEL             lpSizelHim
);
STDAPI_(HGLOBAL) OleStdFillObjectDescriptorFromData(
		LPDATAOBJECT       lpDataObject,
		LPSTGMEDIUM        lpmedium,
		CLIPFORMAT *    lpcfFmt
);
STDAPI_(HANDLE) OleStdGetMetafilePictFromOleObject(
		LPOLEOBJECT         lpOleObj,
		DWORD               dwDrawAspect,
		LPSIZEL             lpSizelHim,
		DVTARGETDEVICE * ptd
);

STDAPI_(void) OleStdCreateTempFileMoniker(LPTSTR lpszPrefixString, UINT * lpuUnique, LPTSTR lpszName, LPMONIKER * lplpmk);
STDAPI_(LPMONIKER) OleStdGetFirstMoniker(LPMONIKER lpmk);
STDAPI_(ULONG) OleStdGetLenFilePrefixOfMoniker(LPMONIKER lpmk);
STDAPI OleStdMkParseDisplayName(
		REFCLSID        rClsid,
		LPBC            lpbc,
		LPTSTR          lpszUserName,
		ULONG *      lpchEaten,
		LPMONIKER *  lplpmk
);
STDAPI_(LPVOID) OleStdMalloc(ULONG ulSize);
STDAPI_(LPVOID) OleStdRealloc(LPVOID pmem, ULONG ulSize);
STDAPI_(void) OleStdFree(LPVOID pmem);
STDAPI_(ULONG) OleStdGetSize(LPVOID pmem);
STDAPI_(void) OleStdFreeString(LPTSTR lpsz, LPMALLOC lpMalloc);
STDAPI_(LPTSTR) OleStdCopyString(LPTSTR lpszSrc, LPMALLOC lpMalloc);
STDAPI_(ULONG) OleStdGetItemToken(LPTSTR lpszSrc, LPTSTR lpszDst,int nMaxChars);

STDAPI_(UINT)     OleStdIconLabelTextOut(HDC        hDC,
										 HFONT      hFont,
										 int        nXStart,
										 int        nYStart,
										 UINT       fuOptions,
										 RECT  * lpRect,
										 LPTSTR      lpszString,
										 UINT       cchString,
										 int  *  lpDX);

// registration database query functions
STDAPI_(UINT)     OleStdGetAuxUserType(REFCLSID rclsid,
									  WORD   wAuxUserType,
									  LPTSTR  lpszAuxUserType,
									  int    cch,
									  HKEY   hKey);

STDAPI_(UINT)     OleStdGetUserTypeOfClass(REFCLSID rclsid,
										   LPTSTR lpszUserType,
										   UINT cch,
										   HKEY hKey);

STDAPI_(BOOL) OleStdGetMiscStatusOfClass(REFCLSID, HKEY, DWORD  *);
STDAPI_(CLIPFORMAT) OleStdGetDefaultFileFormatOfClass(
		REFCLSID        rclsid,
		HKEY            hKey
);

STDAPI_(void) OleStdInitVtbl(LPVOID lpVtbl, UINT nSizeOfVtbl);
STDMETHODIMP OleStdNullMethod(LPUNKNOWN lpThis);
STDAPI_(BOOL) OleStdCheckVtbl(LPVOID lpVtbl, UINT nSizeOfVtbl, LPTSTR lpszIface);
STDAPI_(ULONG) OleStdVerifyRelease(LPUNKNOWN lpUnk, LPTSTR lpszMsg);
STDAPI_(ULONG) OleStdRelease(LPUNKNOWN lpUnk);

STDAPI_(HDC) OleStdCreateDC(DVTARGETDEVICE * ptd);
STDAPI_(HDC) OleStdCreateIC(DVTARGETDEVICE * ptd);
STDAPI_(DVTARGETDEVICE *) OleStdCreateTargetDevice(LPPRINTDLG lpPrintDlg);
STDAPI_(BOOL) OleStdDeleteTargetDevice(DVTARGETDEVICE * ptd);
STDAPI_(DVTARGETDEVICE *) OleStdCopyTargetDevice(DVTARGETDEVICE * ptdSrc);
STDAPI_(BOOL) OleStdCopyFormatEtc(LPFORMATETC petcDest, LPFORMATETC petcSrc);
STDAPI_(int) OleStdCompareFormatEtc(FORMATETC * pFetcLeft, FORMATETC * pFetcRight);
STDAPI_(BOOL) OleStdCompareTargetDevice
	(DVTARGETDEVICE * ptdLeft, DVTARGETDEVICE * ptdRight);

STDAPI_(void) OleDbgPrint(
		int     nDbgLvl,
		LPTSTR   lpszPrefix,
		LPTSTR   lpszMsg,
		int     nIndent
);
STDAPI_(void) OleDbgPrintAlways(LPTSTR lpszPrefix, LPTSTR lpszMsg, int nIndent);
STDAPI_(void) OleDbgSetDbgLevel(int nDbgLvl);
STDAPI_(int) OleDbgGetDbgLevel( void );
STDAPI_(void) OleDbgIndent(int n);
STDAPI_(void) OleDbgPrintRefCnt(
		int         nDbgLvl,
		LPTSTR       lpszPrefix,
		LPTSTR       lpszMsg,
		LPVOID      lpObj,
		ULONG       refcnt
);
STDAPI_(void) OleDbgPrintRefCntAlways(
		LPTSTR       lpszPrefix,
		LPTSTR       lpszMsg,
		LPVOID      lpObj,
		ULONG       refcnt
);
STDAPI_(void) OleDbgPrintRect(
		int         nDbgLvl,
		LPTSTR       lpszPrefix,
		LPTSTR       lpszMsg,
		LPRECT      lpRect
);
STDAPI_(void) OleDbgPrintRectAlways(
		LPTSTR       lpszPrefix,
		LPTSTR       lpszMsg,
		LPRECT      lpRect
);
STDAPI_(void) OleDbgPrintScodeAlways(LPTSTR lpszPrefix, LPTSTR lpszMsg, SCODE sc);

// debug implementation of the IMalloc interface.
STDAPI OleStdCreateDbAlloc(ULONG reserved, IMalloc ** ppmalloc);

STDAPI_(LPENUMFORMATETC)OleStdEnumFmtEtc_Create(ULONG nCount, LPFORMATETC lpEtc);
STDAPI_(LPENUMSTATDATA) OleStdEnumStatData_Create(ULONG nCount, LPSTATDATA lpStat);
STDAPI_(BOOL) OleStdCopyStatData(LPSTATDATA pDest, LPSTATDATA pSrc);
STDAPI_(HPALETTE) OleStdCreateStandardPalette(void);


/*************************************************************************
** OLE OBJECT FEEDBACK EFFECTS
*************************************************************************/

#define OLEUI_HANDLES_USEINVERSE    0x00000001L
#define OLEUI_HANDLES_NOBORDER      0x00000002L
#define OLEUI_HANDLES_INSIDE        0x00000004L
#define OLEUI_HANDLES_OUTSIDE       0x00000008L

#define OLEUI_SHADE_FULLRECT        1
#define OLEUI_SHADE_BORDERIN        2
#define OLEUI_SHADE_BORDEROUT       3

/* objfdbk.c function prototypes */
STDAPI_(void) OleUIDrawHandles(LPCRECT lpRect, HDC hdc, DWORD dwFlags, UINT cSize, BOOL fDraw);
STDAPI_(void) OleUIDrawShading(LPCRECT lpRect, HDC hdc, DWORD dwFlags, UINT cWidth);
STDAPI_(void) OleUIShowObject(LPCRECT lprc, HDC hdc, BOOL fIsLink);

/*************************************************************************
** Hatch window definitions and prototypes                              **
*************************************************************************/

#define DEFAULT_HATCHBORDER_WIDTH   4

STDAPI_(BOOL) RegisterHatchWindowClass(HINSTANCE hInst);
STDAPI_(HWND) CreateHatchWindow(HWND hWndParent, HINSTANCE hInst);
STDAPI_(UINT) GetHatchWidth(HWND hWndHatch);
STDAPI_(void) GetHatchRect(HWND hWndHatch, LPRECT lpHatchRect);
STDAPI_(void) SetHatchRect(HWND hWndHatch, LPCRECT lprcHatchRect);
STDAPI_(void) SetHatchWindowSize(
		HWND        hWndHatch,
		LPCRECT     lprcIPObjRect,
		LPCRECT     lprcClipRect,
		LPPOINT     lpptOffset
);

#ifdef __cplusplus
}
#endif

#endif // _OLESTD_H_
