/*+==========================================================================
  File:      FACTORY.H

  Summary:   Include file for the class factory COM objects: CFCar,
             CFUtilityCar, and CFCruiseCar. These constitute the APTSERVE
             server's Class Factories for those COM components.

             The multiple interface COM Object Classes are achieved via
             the technique of nested classes: the implementation of the
             IClassFactory interfaces are nested inside of the class
             factory COM object classes.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial APTSERVE.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source code.

  Classes:   CFCar, CFUtilityCar, CFCruiseCar.

  Functions: .

  Origin:    3-20-96: atrent - Editor-inheritance from FACTORY.H in
               the LOCSERVE Tutorial Code Sample.

----------------------------------------------------------------------------
  This file is part of the Microsoft COM Tutorial Code Samples.

  Copyright (C) Microsoft Corporation, 1997.  All rights reserved.

  This source code is intended only as a supplement to Microsoft
  Development Tools and/or on-line documentation.  See these other
  materials for detailed information regarding Microsoft code samples.

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
==========================================================================+*/

#if !defined(FACTORY_H)
#define FACTORY_H

#ifdef __cplusplus

/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: CFCar

  Summary:     Class Factory COM Object Class for Car COM components.
               Used to manufacture COCar COM objects.  The mulitple
               interfaces on this COM object class are constructed via
               the nested interface classes technique.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               IClassFactory
                 Standard interface providing COM Class Factory features.

  Aggregation: Yes, CFCar COM objects are aggregatable by
               passing a non-NULL pUnkOuter IUnknown pointer into the
               constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class CFCar : public IUnknown
{
  public:
    // Main Object Constructor & Destructor.
    CFCar(IUnknown* pUnkOuter, CServer* pServer);
    ~CFCar(void);

    // IUnknown methods. Main object, non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

  private:
    // We declare nested class interface implementations here.

    // We implement the IClassFactory interface (ofcourse) in this class
    // factory COM object class.
    class CImpIClassFactory : public IClassFactory
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIClassFactory(
          CFCar* pBackObj,
          IUnknown* pUnkOuter,
          CServer* pServer);
        ~CImpIClassFactory(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // IClassFactory methods.
        STDMETHODIMP         CreateInstance(IUnknown*, REFIID, PPVOID);
        STDMETHODIMP         LockServer(BOOL);

      private:
        // Data private to this interface implementation of IClassFactory.
        ULONG         m_cRefI;       // Interface Ref Count (for debugging).
        CFCar*        m_pBackObj;    // Parent Object back pointer.
        IUnknown*     m_pUnkOuter;   // Outer unknown for Delegation.
        CServer*      m_pServer;     // Server's control object.
    };

    // Make the otherwise private and nested IClassFactory interface
    // implementation a friend to COM object instantiations of this
    // selfsame CFCar COM object class.
    friend CImpIClassFactory;

    // Private data of CFCar COM objects.

    // Nested IClassFactory implementation instantiation.
    CImpIClassFactory m_ImpIClassFactory;

    // Main Object reference count.
    ULONG             m_cRefs;

    // Outer unknown (aggregation & delegation). Used when this
    // CFCar object is being aggregated.  Otherwise it is used
    // for delegation if this object is reused via containment.
    IUnknown*         m_pUnkOuter;

    // Pointer to this component server's control object.
    CServer*          m_pServer;
};

typedef CFCar* PCFCar;


/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: CFUtilityCar

  Summary:     Class Factory COM Object Class for UtilityCar COM
               components.  Used to manufacture COUtilityCar COM
               objects.  The mulitple interfaces on this COM object
               class are constructed via the nested interface
               classes technique.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               IClassFactory
                 Standard interface providing COM Class Factory features.

  Aggregation: Yes, CFUtilityCar COM objects are aggregatable by
               passing a non-NULL pUnkOuter IUnknown pointer into the
               constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class CFUtilityCar : public IUnknown
{
  public:
    // Main Object Constructor & Destructor.
    CFUtilityCar(IUnknown* pUnkOuter, CServer* pServer);
    ~CFUtilityCar(void);

    // A general method for initializing a newly created CFUtilityCar.
    HRESULT Init(void);

    // IUnknown methods. Main object, non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

  private:
    // We declare nested class interface implementations here.

    // We implement the IClassFactory interface (ofcourse) in this class
    // factory COM object class.
    class CImpIClassFactory : public IClassFactory
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIClassFactory(
          CFUtilityCar* pBackObj,
          IUnknown* pUnkOuter,
          CServer* pServer);
        ~CImpIClassFactory(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // IClassFactory methods.
        STDMETHODIMP         CreateInstance(IUnknown*, REFIID, PPVOID);
        STDMETHODIMP         LockServer(BOOL);

      private:
        // Data private to this interface implementation of IClassFactory.
        ULONG            m_cRefI;       // Interface Ref Count (debugging).
        CFUtilityCar*    m_pBackObj;    // Parent Object back pointer.
        IUnknown*        m_pUnkOuter;   // Outer unknown for Delegation.
        CServer*         m_pServer;     // Server Control Object.
    };

    // Make the otherwise private and nested IClassFactory interface
    // implementation a friend to COM object instantiations of this
    // selfsame CFUtilityCar COM object class.
    friend CImpIClassFactory;

    // Private data of CFUtilityCar COM objects.

    // Nested IClassFactory implementation instantiation.
    CImpIClassFactory m_ImpIClassFactory;

    // Main Object reference count.
    ULONG             m_cRefs;

    // Outer unknown (aggregation & delegation). Used when this
    // CFUtilityCar object is being aggregated.  Otherwise it is used
    // for delegation if this object is reused via containment.
    IUnknown*         m_pUnkOuter;

    // Pointer to this component server's control object.
    CServer*          m_pServer;
};

typedef CFUtilityCar* PCFUtilityCar;


/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: CFCruiseCar

  Summary:     Class Factory COM Object Class for CruiseCar COM
               components.  Used to manufacture COCruiseCar COM objects.
               The mulitple interfaces on this COM object class are
               constructed via the nested interface classes technique.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               IClassFactory
                 Standard interface providing COM Class Factory features.

  Aggregation: Yes, CFCruiseCar COM objects are aggregatable by
               passing a non-NULL pUnkOuter IUnknown pointer into the
               constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class CFCruiseCar : public IUnknown
{
  public:
    // Main Object Constructor & Destructor.
    CFCruiseCar(IUnknown* pUnkOuter, CServer* pServer);
    ~CFCruiseCar(void);

    // A general method for initializing a newly created CFCruiseCar.
    HRESULT Init(void);

    // IUnknown methods. Main object, non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

  private:
    // We declare nested class interface implementations here.

    // We implement the IClassFactory interface (ofcourse) in this class
    // factory COM object class.
    class CImpIClassFactory : public IClassFactory
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIClassFactory(
          CFCruiseCar* pBackObj,
          IUnknown* pUnkOuter,
          CServer* pServer);
        ~CImpIClassFactory(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // IClassFactory methods.
        STDMETHODIMP         CreateInstance(IUnknown*, REFIID, PPVOID);
        STDMETHODIMP         LockServer(BOOL);

      private:
        // Data private to this interface implementation of IClassFactory.
        ULONG            m_cRefI;       // Interface Ref Count (debugging).
        CFCruiseCar*     m_pBackObj;    // Parent Object back pointer.
        IUnknown*        m_pUnkOuter;   // Outer unknown for Delegation.
        CServer*         m_pServer;     // Server Control Object.
    };

    // Make the otherwise private and nested IClassFactory interface
    // implementation a friend to COM object instantiations of this
    // selfsame CFCruiseCar COM object class.
    friend CImpIClassFactory;

    // Private data of CFCruiseCar COM objects.

    // Nested IClassFactory implementation instantiation.
    CImpIClassFactory m_ImpIClassFactory;

    // Main Object reference count.
    ULONG             m_cRefs;

    // Outer unknown (aggregation & delegation). Used when this
    // CFCruiseCar object is being aggregated.  Otherwise it is used
    // for delegation if this object is reused via containment.
    IUnknown*         m_pUnkOuter;

    // Pointer to this component server's control object.
    CServer*          m_pServer;
};

typedef CFCruiseCar* PCFCruiseCar;

#endif // __cplusplus


#endif // FACTORY_H
