/*
    dataform.c

    This module deals with the various data formats we can handle.

*/

#include "global.h"


#define MAXFORMATS 10       // max number of formats

//
// global data
//

FORMATETC gSingleObjGetFmts[MAXFORMATS];
int giSingleObjGetFmts;
UINT gcfEmbeddedObject;
UINT gcfObjectDescriptor;

//
// Initialize all the data format info we need to support
// clipboard and drag-drop
//

void InitDataFormats()
{
    //
    // Register any clipboard formats we need
    // Note: CF_... defined in olestd.h (from ole2ui)
    //

    gcfEmbeddedObject = RegisterClipboardFormat(CF_EMBEDDEDOBJECT);
    gcfObjectDescriptor = RegisterClipboardFormat(CF_OBJECTDESCRIPTOR);

    //
    // Set up the array of formats
    //

    gSingleObjGetFmts[0].cfFormat = gcfEmbeddedObject;
    gSingleObjGetFmts[0].ptd      = NULL;
    gSingleObjGetFmts[0].dwAspect = DVASPECT_CONTENT;
    gSingleObjGetFmts[0].tymed    = TYMED_ISTORAGE;
    gSingleObjGetFmts[0].lindex   = -1;

    gSingleObjGetFmts[1].cfFormat = gcfObjectDescriptor;
    gSingleObjGetFmts[1].ptd      = NULL;
    gSingleObjGetFmts[1].dwAspect = DVASPECT_CONTENT;
    gSingleObjGetFmts[1].tymed    = TYMED_HGLOBAL;
    gSingleObjGetFmts[1].lindex   = -1;

    gSingleObjGetFmts[2].cfFormat = CF_METAFILEPICT;
    gSingleObjGetFmts[2].ptd      = NULL;
    gSingleObjGetFmts[2].dwAspect = DVASPECT_CONTENT;
    gSingleObjGetFmts[2].tymed    = TYMED_MFPICT;
    gSingleObjGetFmts[2].lindex   = -1;

    gSingleObjGetFmts[3].cfFormat = CF_TEXT;
    gSingleObjGetFmts[3].ptd      = NULL;
    gSingleObjGetFmts[3].dwAspect = DVASPECT_CONTENT;
    gSingleObjGetFmts[3].tymed    = TYMED_HGLOBAL;
    gSingleObjGetFmts[3].lindex   = -1;

    giSingleObjGetFmts = 4;

}

//
// Test a format to see if we support it
//

BOOL IsValidDataFormat(POBJECT pObj, LPFORMATETC pFmt)
{
    int i;
    LPDATAOBJECT pDataObj;
    HRESULT hResult;

    // 
    // see if we have it in our list
    //

    for (i=0; i<giSingleObjGetFmts; i++) {
        if (gSingleObjGetFmts[i].cfFormat == pFmt->cfFormat) {
            return TRUE;
        }
    }

    //
    // see if our OLE object supports it
    //

    pDataObj = (LPDATAOBJECT)OleStdQueryInterface(
	                (LPUNKNOWN) (pObj->pOleObj),
                    &IID_IDataObject);
    if (pDataObj) {

        hResult = pDataObj->lpVtbl->QueryGetData(pDataObj,
                                                 pFmt);
        if (SUCCEEDED(hResult)) return TRUE;

    }

    return FALSE;
}
