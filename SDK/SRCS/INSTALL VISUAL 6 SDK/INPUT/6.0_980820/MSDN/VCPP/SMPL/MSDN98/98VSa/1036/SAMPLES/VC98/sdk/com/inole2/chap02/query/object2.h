/*
 * OBJECT2.H
 *
 * Definition of the CObject1 class that uses contained
 * classes to provide ISampleOne and ISampleTwo.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _OBJECT2_H_
#define _OBJECT2_H_


//Creation function
BOOL CreateObject2(IUnknown **);


/*
 * The object we want to provide in OLE supports the IUnknown,
 * ISampleOne, and ISampleTwo interfaces.
 *
 * The C++ class, CObject2, implements these interfaces with
 * contained classes where each contained class inherits singly
 * from an interface.  This is a little different from interface
 * implementations shown in Object1 because contained classes
 * are automatically instantiated along with CObject2.
 */



//The C++ class that manages the actual object.
class CObject2 : public IUnknown
    {
    /*
     * Declare the contained classes, which should be friends.
     * As with interface implementations, these need back
     * pointers to the outer object as well as the IUnknown to
     * which to delegate, which are the constructor parameters.
     */
    class CImpISampleOne : public ISampleOne
        {
        private:
            DWORD       m_cRef;         //For debugging
            CObject2   *m_pObj;         //Back pointer for delegation

        public:
            CImpISampleOne(CObject2 *pObj)
                { m_cRef=0; m_pObj=pObj; }

            ~CImpISampleOne(void)
                { }

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
            CObject2   *m_pObj;         //Back pointer for delegation

        public:
            CImpISampleTwo(CObject2 *pObj)
                { m_cRef=0; m_pObj=pObj; }
            ~CImpISampleTwo(void)
                { }

            //IUnknown members
            STDMETHODIMP         QueryInterface(REFIID, PPVOID);
            STDMETHODIMP_(DWORD) AddRef(void);
            STDMETHODIMP_(DWORD) Release(void);

            //ISampleTwo members
            STDMETHODIMP         GetString(LPTSTR, UINT);
        };


    friend CImpISampleOne;
    friend CImpISampleTwo;


    private:
        DWORD           m_cRef;         //Object reference count

        /*
         * In this technique I still use "ImpI" prefixes to
         * differentiate contained classes.  The difference here
         * from Object1 is that we declare objects instead of
         * pointers to objects, so instantiating CObject2 will
         * automatically instantiate CImpI*.  Destroying CObject2
         * will automatically destroy CImp*.
         */
        CImpISampleOne  m_ImpISampleOne;
        CImpISampleTwo  m_ImpISampleTwo;

    public:
        CObject2(void);
        ~CObject2(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(DWORD) AddRef(void);
        STDMETHODIMP_(DWORD) Release(void);
    };


typedef CObject2 *PCObject2;


#endif _OBJECT2_H_
