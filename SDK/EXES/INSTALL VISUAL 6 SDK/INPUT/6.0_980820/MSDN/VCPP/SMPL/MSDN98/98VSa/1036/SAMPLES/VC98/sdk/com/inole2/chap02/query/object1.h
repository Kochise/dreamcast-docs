/*
 * OBJECT1.H
 *
 * Definition of the CObject1 class that uses interface
 * implementations to provide ISampleOne and ISampleTwo.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _OBJECT1_H_
#define _OBJECT1_H_


//Creation function
BOOL CreateObject1(IUnknown **);


/*
 * The object we want to provide in OLE supports the IUnknown,
 * ISampleOne, and ISampleTwo interfaces.
 *
 * The C++ class, CObject1, implements these interfaces with
 * "interface implementations" where the C++ class itself inherits
 * from and implements IUnknown members and then contains
 * other C++ classes that each separately inherit from the other
 * interfaces.  The other classes are the "interface implementations."
 */


/*
 * In this technique you'll generally need forward references
 * like this for use in declaring the object class.
 */
class CImpISampleOne;
typedef CImpISampleOne *PCImpISampleOne;

class CImpISampleTwo;
typedef CImpISampleTwo *PCImpISampleTwo;

//The C++ class that manages the actual object.
class CObject1 : public IUnknown
    {
    /*
     * Usually interface implementations will need back pointers
     * to the object itself since this object usually manages
     * the important data members.  In that case, make the
     * interface implementation classes friends of the object.
     */

    friend CImpISampleOne;
    friend CImpISampleTwo;


    private:
        DWORD           m_cRef;         //Object reference count

        /*
         * I use "m_pImpI" as a prefix to differentiate interface
         * implementations for this object from other interface
         * pointer variables I might hold to other objects, whic
         * would be prefixed with "m_pI".
         */
        PCImpISampleOne  m_pImpISampleOne;
        PCImpISampleTwo  m_pImpISampleTwo;

    public:
        CObject1(void);
        ~CObject1(void);

        BOOL Init(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(DWORD) AddRef(void);
        STDMETHODIMP_(DWORD) Release(void);
    };


typedef CObject1 *PCObject1;


/*
 * Interface implementation classes are C++ classes that
 * each singly inherit from an interface.  Their IUnknown
 * members delegate calls to CObject1's IUnknown members--
 * since IUnknown members affect the entire *object*, and
 * since these interfaces are not the object itself, we must
 * delegate to implement the correct behavior.
 */

class CImpISampleOne : public ISampleOne
    {
    private:
        DWORD       m_cRef;         //For debugging
        PCObject1   m_pObj;         //Back pointer for delegation

    public:
        CImpISampleOne(PCObject1);
        ~CImpISampleOne(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(DWORD) AddRef(void);
        STDMETHODIMP_(DWORD) Release(void);

        //ISampleOne members
        STDMETHODIMP         GetMessage(LPTSTR, UINT);
    };



class CImpISampleTwo : public ISampleTwo
    {
    private:
        DWORD       m_cRef;         //For debugging
        PCObject1   m_pObj;         //Back pointer for delegation

    public:
        CImpISampleTwo(PCObject1);
        ~CImpISampleTwo(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(DWORD) AddRef(void);
        STDMETHODIMP_(DWORD) Release(void);

        //ISampleTwo members
        STDMETHODIMP         GetString(LPTSTR, UINT);
    };


#endif _OBJECT1_H_
