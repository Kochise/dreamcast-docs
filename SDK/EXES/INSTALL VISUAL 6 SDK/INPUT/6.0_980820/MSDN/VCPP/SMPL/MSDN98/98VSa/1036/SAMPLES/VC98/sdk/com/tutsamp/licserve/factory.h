/*+==========================================================================
  File:      FACTORY.H

  Summary:   Include file for the class factory COM objects:
             CFLicCruiseCar, and CFLicCarSample.  These constitute the
             LICSERVE server's Class Factories for those COM components.

             The multiple interface COM Object Classes are achieved via
             the technique of nested classes: the implementation of the
             IClassFactory interfaces are nested inside of the class
             factory COM object classes.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial LICSERVE.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   CFLicCruiseCar, CFLicCarSample.

  Functions: .

  Origin:    10-5-95: atrent - Editor-inheritance from CRUCAR.H in
               the DLLSERVE Tutorial Code Sample.

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
  ObjectClass: CFLicCruiseCar

  Summary:     Class Factory COM Object Class for LicCruiseCar COM
               components.  Used to manufacture COLicCruiseCar COM objects.
               The mulitple interfaces on this COM object class are
               constructed via the nested interface classes technique.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               IClassFactory2
                 Standard interface providing COM Class Factory features
                 that support licensing of these Cruise Car COM components.

  Aggregation: Yes, CFLicCruiseCar COM objects are aggregatable by
               passing a non-NULL pUnkOuter IUnknown pointer into the
               constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class CFLicCruiseCar : public IUnknown
{
  public:
    // Main Object Constructor & Destructor.
    CFLicCruiseCar(IUnknown* pUnkOuter, CServer* pServer);
    ~CFLicCruiseCar(void);

    // A general method for initializing a newly created CFLicCruiseCar.
    HRESULT Init(void);

    // IUnknown methods. Main object, non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

  private:
    // A private unconditional create for LicCruiseCar.
    STDMETHODIMP CreateLicCruiseCar(IUnknown*, REFIID, PPVOID);

    // We declare nested class interface implementations here.

    // We implement the IClassFactory2 interface on this LicCruiseCar
    // Class Factory to license these COM objects.
    class CImpIClassFactory : public IClassFactory2
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIClassFactory(
          CFLicCruiseCar* pBackObj,
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

        // IClassFactory2 methods.
        STDMETHODIMP         GetLicInfo(LPLICINFO);
        STDMETHODIMP         RequestLicKey(DWORD, BSTR*);
        STDMETHODIMP         CreateInstanceLic(
                               IUnknown*,
                               IUnknown*,
                               REFIID,
                               BSTR,
                               PPVOID);

      private:
        // Data private to this interface implementation of IClassFactory.
        ULONG            m_cRefI;       // Interface Ref Count (debugging).
        CFLicCruiseCar*  m_pBackObj;    // Parent Object back pointer.
        IUnknown*        m_pUnkOuter;   // Outer unknown for Delegation.
        CServer*         m_pServer;     // Server Control Object.
    };

    // Make the otherwise private and nested IClassFactory interface
    // implementation a friend to COM object instantiations of this
    // selfsame CFLicCruiseCar COM object class.
    friend CImpIClassFactory;

    // Private data of CFLicCruiseCar COM objects.

    // Nested IClassFactory implementation instantiation.
    CImpIClassFactory m_ImpIClassFactory;

    // Main Object reference count.
    ULONG             m_cRefs;

    // Outer unknown (aggregation & delegation). Used when this
    // CFLicCruiseCar object is being aggregated.  Otherwise it is used
    // for delegation if this object is reused via containment.
    IUnknown*         m_pUnkOuter;

    // Pointer to this component server's control object.
    CServer*          m_pServer;
};

typedef CFLicCruiseCar* PCFLicCruiseCar;


/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: CFLicCarSample

  Summary:     Class Factory COM Object Class for LicCarSample COM
               components.  Used to manufacture COLicCarSample COM
               objects.  The mulitple interfaces on this COM object
               class are constructed via the nested interface classes
               technique.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               IClassFactory
                 Standard interface providing COM Class Factory features.

  Aggregation: Yes, CFLicCarSample COM objects are aggregatable by
               passing a non-NULL pUnkOuter IUnknown pointer into the
               constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class CFLicCarSample : public IUnknown
{
  public:
    // Main Object Constructor & Destructor.
    CFLicCarSample(IUnknown* pUnkOuter, CServer* pServer);
    ~CFLicCarSample(void);

    // A general method for initializing a newly created CFLicCarSample.
    HRESULT Init(void);

    // IUnknown methods. Main object, non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

  private:
    // We declare nested class interface implementations here.

    // We implement the IClassFactory interface (of course) in this Class
    // Factory COM object class.
    class CImpIClassFactory : public IClassFactory
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIClassFactory(
          CFLicCarSample* pBackObj,
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
        ULONG           m_cRefI;     // Interface Ref Count (for debugging).
        CFLicCarSample* m_pBackObj;  // Parent Object back pointer.
        IUnknown*       m_pUnkOuter; // Outer unknown for Delegation.
        CServer*        m_pServer;   // Server Control Object.
    };

    // Make the otherwise private and nested IClassFactory interface
    // implementation a friend to COM object instantiations of this
    // selfsame CFLicCarSample COM object class.
    friend CImpIClassFactory;

    // Private data of CFLicCarSample COM objects.

    // Nested IClassFactory implementation instantiation.
    CImpIClassFactory m_ImpIClassFactory;

    // Main Object reference count.
    ULONG             m_cRefs;

    // Outer unknown (aggregation & delegation). Used when this
    // CFLicCarSample object is being aggregated.  Otherwise it is used
    // for delegation if this object is reused via containment.
    IUnknown*         m_pUnkOuter;

    // Pointer to this component server's control object.
    CServer*          m_pServer;
};

typedef CFLicCarSample* PCFLicCarSample;

#endif // __cplusplus


#endif // FACTORY_H
