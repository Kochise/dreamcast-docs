/*+==========================================================================
  File:      FACTORY.H

  Summary:   Include file for the class factory COM object: CFPaper. This
             constitutes the DCDSERVE server's class factory for the
             SharePaper COM component.

             The multiple interface COM Object Class is achieved via the
             technique of nested classes: the implementation of the
             standard IClassFactory interface is nested inside of the
             class factory COM object class. APPUTIL's CThreaded OwnThis
             mechanism is used to ensure mutually exclusive access to the
             class factory by contending multiple threads.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial DCDSERVE.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   CFPaper.

  Functions: .

  Origin:    8-23-97: atrent - Editor-inheritance from FACTORY.H in
               the CONSERVE Tutorial Code Sample. [Revised]

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
  ObjectClass: CFPaper

  Summary:     Class Factory COM Object Class for SharePaper COM
               components. Used to manufacture COPaper COM objects.  The
               mulitple interfaces on this COM object class are
               constructed via the nested interface classes technique.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               IClassFactory
                 Standard interface providing COM Class Factory features.

  Aggregation: Yes, CFPaper COM objects are aggregatable by
               passing a non-NULL pUnkOuter IUnknown pointer into the
               constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class CFPaper : public IUnknown, public CThreaded
{
  public:
    // Main Object Constructor & Destructor.
    CFPaper(IUnknown* pUnkOuter, CServer* pServer);
    ~CFPaper(void);

    // IUnknown methods. Main object, non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

    // We declare nested class interface implementations here.

    // We implement the IClassFactory interface in this class
    // factory COM object class. Derive also from abstract CThreaded
    // to provide the OwnThis/UnownThis thread-safety mechanism.
    class CImpIClassFactory : public IClassFactory, public CThreaded
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIClassFactory(
          CFPaper* pCO,
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
        CFPaper*      m_pCO;         // Parent Object back pointer.
        IUnknown*     m_pUnkOuter;   // Outer unknown for Delegation.
        CServer*      m_pServer;     // Server's control object.
    };

    // Make the otherwise private and nested IClassFactory interface
    // implementation a friend to COM object instantiations of this
    // CFPaper COM object class.
    friend CImpIClassFactory;

  private:
    // Private data of CFPaper COM objects.

    // Nested IClassFactory implementation instantiation.
    CImpIClassFactory m_ImpIClassFactory;

    // Main Object reference count.
    ULONG             m_cRefs;

    // Outer unknown (aggregation & delegation). Used when this
    // CFPaper object is being aggregated.  Otherwise it is used
    // for delegation if this object is reused via containment.
    IUnknown*         m_pUnkOuter;

    // Pointer to this component server's control object.
    CServer*          m_pServer;
};


#endif // __cplusplus


#endif // FACTORY_H
