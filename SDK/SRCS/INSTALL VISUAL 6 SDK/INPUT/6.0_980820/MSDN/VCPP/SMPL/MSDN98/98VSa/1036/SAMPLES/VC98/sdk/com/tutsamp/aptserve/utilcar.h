/*+==========================================================================
  File:      UTILCAR.H

  Summary:   Include file for the aggregatable COUtilityCar COM object class.

             UTILCAR showcases the construction of the COUtilityCar COM
             object class with the IUnknown, ICar, and IUtility
             interfaces. This is done through Containment reuse of COCar's
             ICar interface features.

             This multiple interface COM Object Class is achieved via the
             technique of nested classes: the implementation of the ICar
             and IUtility interfaces are nested inside of the COUtilityCar
             COM object class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial APTSERVE.HTM
             file. For more specific technical details on the internal
             workings see the comments dispersed throughout the module's
             source code.

  Classes:   COUtilityCar

  Functions: .

  Origin:    3-20-96: atrent - Editor-inheritance from UTILCAR.H in
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

#if !defined(UTILCAR_H)
#define UTILCAR_H

#ifdef __cplusplus

/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: COUtilityCar

  Summary:     COM Object Class for COUtilityCar COM Objects.  COM objects
               of this class augment COCar COM objects (which offer ICar
               interface features of Shift, Clutch, Speed, and Steer) with
               IUtility interface features (Offroad and Winch).  This
               COUtilityCar COM object class is constructed by containment
               reuse of the COCar COM object class.  The mulitple
               interfaces on this COM object class are constructed via
               the nested interface classes technique.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               ICar
                 Basic Car operation features.
               IUtility
                 Sport-utility vehicle offroad features.

  Aggregation: Yes, COUtilityCar COM objects are aggregatable by passing
               a non-NULL pUnkOuter IUnknown pointer into the constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class COUtilityCar : public IUnknown
{
  public:
    // Main Object Constructor & Destructor.
    COUtilityCar(IUnknown* pUnkOuter, CServer* pServer);
    ~COUtilityCar(void);

    // A general method for initializing a newly created COUtilityCar.
    HRESULT Init(void);

    // IUnknown methods. Main object, non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

    // We get this ICar interface pointer via containment reuse of the
    // ICar interface in an instantiated COCar.
    ICar*           m_pICar;

  private:
    // We show nested interface class implementations here.

    // We implement the basic ICar interface in this COUtilityCar
    // COM object class.
    class CImpICar : public ICar
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpICar(COUtilityCar* pBackObj, IUnknown* pUnkOuter);
        ~CImpICar(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // ICar methods.
        STDMETHODIMP Shift(short nGear);
        STDMETHODIMP Clutch(short nEngaged);
        STDMETHODIMP Speed(short nMph);
        STDMETHODIMP Steer(short nAngle);

      private:
        // Data private to this COUtilityCar interface implementation of ICar.
        ULONG         m_cRefI;       // Interface Ref Count (for debugging).
        COUtilityCar* m_pBackObj;    // Parent Object back pointer.
        IUnknown*     m_pUnkOuter;   // Outer unknown for Delegation.
    };

    // We implement the IUtility interface (ofcourse) in this COUtilityCar
    // COM object class.  This is the native interface that we are using
    // as an augmentation to the existing COCar COM object class.
    class CImpIUtility : public IUtility
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIUtility(COUtilityCar* pBackObj, IUnknown* pUnkOuter);
        ~CImpIUtility(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // IUtility methods.
        STDMETHODIMP Offroad(short nGear);
        STDMETHODIMP Winch(short nRpm);

      private:
        // Data private to this interface implementation of IUtility.
        ULONG         m_cRefI;       // Interface Ref Count (for debugging).
        COUtilityCar* m_pBackObj;    // Parent Object back pointer.
        IUnknown*     m_pUnkOuter;   // Outer unknown for Delegation.
    };

    // Make the otherwise private and nested ICar and IUtility interface
    // implementations a friend to COM object instantiations of this
    // selfsame COUtilityCar COM object class.
    friend CImpICar;
    friend CImpIUtility;

    // Private data of COUtilityCar COM objects.

    // Nested ICar implementation instantiation.
    CImpICar        m_ImpICar;

    // Nested IUtility implementation instantiation.  This IUtility interface
    // is implemented inside this COUtilityCar object as a native interface.
    CImpIUtility    m_ImpIUtility;

    // Main Object reference count.
    ULONG           m_cRefs;

    // Outer unknown (aggregation & delegation). Used when this COCruiseCar
    // object is being aggregated.  Otherwise it is used for delegation
    // if this object is reused via containment.
    IUnknown*       m_pUnkOuter;

    // Pointer to this component server's control object.
    CServer*        m_pServer;
};

typedef COUtilityCar* PCOUtilityCar;

#endif // __cplusplus


#endif // UTILCAR_H
