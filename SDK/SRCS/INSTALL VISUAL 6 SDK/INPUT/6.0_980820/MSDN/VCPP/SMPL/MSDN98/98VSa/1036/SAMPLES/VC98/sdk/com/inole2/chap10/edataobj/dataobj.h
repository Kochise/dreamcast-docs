/*
 * DATAOBJ.H
 * Data Object Chapter 10
 *
 * Classes that implement the Data Object independent of whether
 * we live in a DLL or EXE.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _DATAOBJ_H_
#define _DATAOBJ_H_

#define INC_OLE2
#define CHAPTER10
#include <inole.h>

//Data size types
#define DOSIZE_SMALL        0
#define DOSIZE_MEDIUM       1
#define DOSIZE_LARGE        2
#define DOSIZE_CSIZES       3

//Data sizes
#define CCHTEXTSMALL        64      //Text grows * 16 charactrs
#define CCHTEXTMEDIUM       1024
#define CCHTEXTLARGE        16384

#define CXYBITMAPSMALL      16      //Bitmaps grow * 4 pixels
#define CXYBITMAPMEDIUM     64
#define CXYBITMAPLARGE      256

#define CRECMETAFILESMALL   4       //Metafiles grows * 9 records;
#define CRECMETAFILEMEDIUM  12      //the number of actual records
#define CRECMETAFILELARGE   36      //is the square of these


//Resources for this data object.
#define IDB_MIN             1       //Keep this DOSIZE_SMALL+1
#define IDB_16BY16          1
#define IDB_64BY64          2
#define IDB_256BY256        3
#define IDB_MAX             3


#define IDR_MENU                        1
#define IDR_ADVISORICON                 1

#define IDM_ADVISEITERATIONSMIN         100
#define IDM_ADVISEITERATIONS16          100
#define IDM_ADVISEITERATIONS64          101
#define IDM_ADVISEITERATIONS144         102
#define IDM_ADVISEITERATIONS256         103
#define IDM_ADVISEITERATIONS400         104
#define IDM_ADVISEITERATIONS572         105




/*
 * The DataObject object is implemented in its own class with its
 * own IUnknown to support aggregation.  It contains one
 * CImpIDataObject object that we use to implement the externally
 * exposed interfaces.
 */

#define CFORMATETCGET       3


//DATAOBJ.CPP
LRESULT APIENTRY AdvisorWndProc(HWND, UINT, WPARAM, LPARAM);

class CImpIDataObject;
typedef class CImpIDataObject *PCImpIDataObject;


class CDataObject : public IUnknown
    {
    friend class CImpIDataObject;
    friend LRESULT APIENTRY AdvisorWndProc(HWND, UINT
        , WPARAM, LPARAM);

    protected:
        ULONG               m_cRef;
        LPUNKNOWN           m_pUnkOuter;
        PFNDESTROYED        m_pfnDestroy;

        UINT                m_iSize;        //Data size for Render*
        HBITMAP             m_rghBmp[DOSIZE_CSIZES]; //Cache bitmaps

        HWND                m_hWndAdvise;   //Popup with Advise menu
        DWORD               m_dwAdvFlags;   //Notification flags

        //Contained interface implemetation
        PCImpIDataObject    m_pImpIDataObject;

        //Other interfaces used, implemented elsewhere
        LPDATAADVISEHOLDER  m_pIDataAdviseHolder;

        //Arrays for IDataObject::EnumFormatEtc
        ULONG               m_cfeGet;
        FORMATETC           m_rgfeGet[CFORMATETCGET];

    protected:
        //Functions for use from IDataObject::GetData
        HRESULT     RenderText(LPSTGMEDIUM);
        HRESULT     RenderBitmap(LPSTGMEDIUM);
        HRESULT     RenderMetafilePict(LPSTGMEDIUM);

    public:
        CDataObject(LPUNKNOWN, PFNDESTROYED, UINT);
        ~CDataObject(void);

        BOOL Init(void);

        //Non-delegating object IUnknown
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);
    };

typedef CDataObject *PCDataObject;



/*
 * Interface implementations for the CDataObject object.
 */

class CImpIDataObject : public IDataObject
    {
    private:
        ULONG           m_cRef;
        PCDataObject    m_pObj;
        LPUNKNOWN       m_pUnkOuter;

    public:
        CImpIDataObject(PCDataObject, LPUNKNOWN);
        ~CImpIDataObject(void);

        //IUnknown members that delegate to m_pUnkOuter.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IDataObject members
        STDMETHODIMP GetData(LPFORMATETC, LPSTGMEDIUM);
        STDMETHODIMP GetDataHere(LPFORMATETC, LPSTGMEDIUM);
        STDMETHODIMP QueryGetData(LPFORMATETC);
        STDMETHODIMP GetCanonicalFormatEtc(LPFORMATETC,LPFORMATETC);
        STDMETHODIMP SetData(LPFORMATETC, LPSTGMEDIUM, BOOL);
        STDMETHODIMP EnumFormatEtc(DWORD, LPENUMFORMATETC *);
        STDMETHODIMP DAdvise(LPFORMATETC, DWORD,  LPADVISESINK
            , DWORD *);
        STDMETHODIMP DUnadvise(DWORD);
        STDMETHODIMP EnumDAdvise(LPENUMSTATDATA *);
    };



/*
 * IEnumFORMATETC object that is created from
 * IDataObject::EnumFormatEtc.  This object lives on its own.
 */

class CEnumFormatEtc : public IEnumFORMATETC
    {
    private:
        ULONG           m_cRef;         //Object reference count
        ULONG           m_iCur;         //Current element.
        ULONG           m_cfe;          //Number of FORMATETCs in us
        LPFORMATETC     m_prgfe;        //Source of FORMATETCs

    public:
        CEnumFormatEtc(ULONG, LPFORMATETC);
        ~CEnumFormatEtc(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IEnumFORMATETC members
        STDMETHODIMP Next(ULONG, LPFORMATETC, ULONG *);
        STDMETHODIMP Skip(ULONG);
        STDMETHODIMP Reset(void);
        STDMETHODIMP Clone(IEnumFORMATETC **);
    };


typedef CEnumFormatEtc *PCEnumFormatEtc;

#endif //_DATAOBJ_H_
