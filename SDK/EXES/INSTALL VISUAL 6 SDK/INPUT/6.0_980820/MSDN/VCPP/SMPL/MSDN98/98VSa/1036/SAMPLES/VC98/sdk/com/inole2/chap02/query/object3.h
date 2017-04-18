/*
 * OBJECT3.H
 *
 * Definition of the CObject1 class that uses mutliple
 * inheritance to provide ISampleOne and ISampleTwo.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _OBJECT3_H_
#define _OBJECT3_H_


//Creation function
BOOL CreateObject3(IUnknown **);


/*
 * The object we want to provide in OLE supports the IUnknown,
 * ISampleOne, and ISampleTwo interfaces.
 *
 * The C++ class, CObject3, implements these interfaces through
 * multiple inheritance, so the implementation of all IUnknown
 * members is shared.  The trick to this implementation is that
 * we have to use explicit typecasts in the implementation of
 * QueryInterface in order to create the right vtables for each
 * interface.  See OBJECT3.CPP.
 */

//The C++ class that manages the actual object.
class CObject3 : public ISampleOne, public ISampleTwo
    {
    private:
        DWORD           m_cRef;         //Object reference count

    public:
        CObject3(void);
        ~CObject3(void);

        //Shared IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(DWORD) AddRef(void);
        STDMETHODIMP_(DWORD) Release(void);

        //ISampleOne members
        STDMETHODIMP         GetMessage(LPTSTR, UINT);

        //ISampleTwo members
        STDMETHODIMP         GetString(LPTSTR, UINT);
    };

typedef CObject3 *PCObject3;

#endif _OBJECT3_H_
