/*
 * OBJECTS.H
 * File and Item Objects for Link Source, Chapter 9
 *
 * Classes to define the file and item objects supplied by
 * this server as well as their interfaces.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#define CHAPTER9
#include <inole.h>
#include <idescrip.h>

//Shared implementations
class CImpIOleItemContainer;
typedef CImpIOleItemContainer *PCImpIOleItemContainer;

class CImpIDescription;
typedef CImpIDescription *PCImpIDescription;


//FILEOBJ.CPP

class CImpIPersistFile;
typedef CImpIPersistFile *PCImpIPersistFile;


class CFileObject : public IUnknown
    {
    friend class CImpIPersistFile;
    friend class CImpIOleItemContainer;
    friend class CImpIDescription;

    protected:
        ULONG           m_cRef;         //Object reference count
        LPUNKNOWN       m_pUnkOuter;    //Controlling unknown
        PFNDESTROYED    m_pfnDestroy;   //To call on closure

        CLSID           m_clsID;        //Object identity
        OLECHAR         m_szFile[512];  //Current filename
        IStorage       *m_pIStorage;    //Opened file
        IMoniker       *m_pmk;          //Our name
        DWORD           m_dwRegROT;     //ROT registration

        //Interfaces
        PCImpIPersistFile         m_pImpIPersistFile;
        PCImpIOleItemContainer    m_pImpIOleItemContainer;
        PCImpIDescription         m_pImpIDescription;

    public:
        CFileObject(LPUNKNOWN, PFNDESTROYED);
        ~CFileObject(void);

        BOOL Init(void);

        //Non-delegating object IUnknown
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);
    };

typedef CFileObject *PCFileObject;


class CImpIPersistFile : public IPersistFile
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        PCFileObject    m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIPersistFile(PCFileObject, LPUNKNOWN);
        ~CImpIPersistFile(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetClassID(LPCLSID);
        STDMETHODIMP IsDirty(void);
        STDMETHODIMP Load(LPCOLESTR, DWORD);
        STDMETHODIMP Save(LPCOLESTR, BOOL);
        STDMETHODIMP SaveCompleted(LPCOLESTR);
        STDMETHODIMP GetCurFile(LPOLESTR *);
    };



//CONTITEM.CPP

/*
 * Implementation of an item object that itself contains other
 * items, thus it implements IOleItemContainer.  IDescription is
 * added only for reason of this sample.
 */


class CContainerItem : public IUnknown
    {
    friend class CImpIOleItemContainer;
    friend class CImpIDescription;

    protected:
        ULONG           m_cRef;         //Object reference count
        LPUNKNOWN       m_pUnkParent;   //CFileObject's pointer
        PFNDESTROYED    m_pfnDestroy;   //To call on closure
        IStorage       *m_pIStorage;    //Our storage
        IMoniker       *m_pmk;          //Our name
        DWORD           m_dwRegROT;     //ROT Registration

        //Interfaces
        PCImpIOleItemContainer    m_pImpIOleItemContainer;
        PCImpIDescription         m_pImpIDescription;

    public:
        CContainerItem(LPUNKNOWN, PFNDESTROYED);
        ~CContainerItem(void);

        BOOL Init(IMoniker *, IBindCtx *, LPOLESTR, IStorage *);

        //Non-delegating object IUnknown
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);
    };

typedef CContainerItem *PCContainerItem;



//SIMPITEM.CPP

/*
 * Implementation of a simple item object with only IDescription.
 */

class CSimpleItem : public IUnknown
    {
    friend class CImpIDescription;

    protected:
        ULONG           m_cRef;         //Object reference count
        LPUNKNOWN       m_pUnkParent;   //CContainerItems's pointer
        PFNDESTROYED    m_pfnDestroy;   //To call on closure
        IStorage       *m_pIStorage;    //Our storage
        IMoniker       *m_pmk;          //Our name
        DWORD           m_dwRegROT;     //ROT Registration

        //Interfaces
        PCImpIDescription         m_pImpIDescription;

    public:
        CSimpleItem(LPUNKNOWN, PFNDESTROYED);
        ~CSimpleItem(void);

        BOOL Init(IMoniker *, IBindCtx *, LPOLESTR, IStorage *);

        //Non-delegating object IUnknown
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);
    };

typedef CSimpleItem *PCSimpleItem;




//IOLECONT.CPP
/*
 * IOleItemContainer implementation that is shared between
 * CFileObject and CContainerItem.  The flag to the constructor
 * indicates which object exposes any given instantiation.
 */

class CImpIOleItemContainer : public IOleItemContainer
    {
    protected:
        ULONG               m_cRef;
        LPUNKNOWN           m_pUnkOuter;

        BOOL                m_fFileObj;
        PCFileObject        m_pObjFile;
        PCContainerItem     m_pObjCont;

    public:
        CImpIOleItemContainer(LPVOID, LPUNKNOWN, BOOL);
        ~CImpIOleItemContainer(void);

        HRESULT GetRunning(LPOLESTR, IBindCtx *, REFIID, void **
            , BOOL);

        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP ParseDisplayName(LPBC, LPOLESTR, ULONG *
                         , LPMONIKER *);
        STDMETHODIMP EnumObjects(DWORD, LPENUMUNKNOWN *);
        STDMETHODIMP LockContainer(BOOL);
        STDMETHODIMP GetObject(LPOLESTR, DWORD, LPBINDCTX, REFIID
                         , PPVOID);
        STDMETHODIMP GetObjectStorage(LPOLESTR, LPBINDCTX, REFIID
                         , PPVOID);
        STDMETHODIMP IsRunning(LPOLESTR);
    };


#define SZOPENSTORAGE  OLETEXT("OpenStorage")


//IDESCRIP.CPP
/*
 * IDescription implementation that is shared between
 * CFileObject, CContainerItem, and CSimpleItem.  The
 * IStorage argument to the constructor is all that this
 * implementation needs, so there's no backpointer.
 */

class CImpIDescription : public IDescription
    {
    protected:
        ULONG               m_cRef;
        LPUNKNOWN           m_pUnkOuter;
        IStorage           *m_pIStorage;

    public:
        CImpIDescription(LPUNKNOWN);
        ~CImpIDescription(void);

        void SetStorage(IStorage *);

        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetText(LPOLESTR, ULONG);
    };


#endif //_OBJECTS_H_
