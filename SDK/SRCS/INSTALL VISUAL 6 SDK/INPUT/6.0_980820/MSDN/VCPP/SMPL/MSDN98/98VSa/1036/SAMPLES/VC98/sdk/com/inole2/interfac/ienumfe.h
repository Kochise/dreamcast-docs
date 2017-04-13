/*
 * IENUMFE.H
 *
 * Definitions of a FORMATETC enumerator.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IENUMFE_H_
#define _IENUMFE_H_

#include <inole.h>

/*
 * IEnumFORMATETC object that is created from
 * IDataObject::EnumFormatEtc.  This object lives on its own,
 * that is, QueryInterface only knows IUnknown and IEnumFormatEtc,
 * nothing more.  We still use an outer unknown for reference
 * counting, because as long as this enumerator lives, the data
 * object should live, thereby keeping the application up.
 */

class CEnumFormatEtc;
typedef class CEnumFormatEtc *PCEnumFormatEtc;

class CEnumFormatEtc : public IEnumFORMATETC
    {
    private:
        ULONG           m_cRef;     //Object reference count
        ULONG           m_iCur;     //Current element
        ULONG           m_cfe;      //Number of FORMATETCs in us
        LPFORMATETC     m_prgfe;    //Source of FORMATETCs

    public:
        CEnumFormatEtc(ULONG, LPFORMATETC);
        ~CEnumFormatEtc(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IEnumFORMATETC members
        STDMETHODIMP Next(ULONG, LPFORMATETC, ULONG *);
        STDMETHODIMP Skip(ULONG);
        STDMETHODIMP Reset(void);
        STDMETHODIMP Clone(IEnumFORMATETC **);
    };


#endif //_IENUMFE_H_
