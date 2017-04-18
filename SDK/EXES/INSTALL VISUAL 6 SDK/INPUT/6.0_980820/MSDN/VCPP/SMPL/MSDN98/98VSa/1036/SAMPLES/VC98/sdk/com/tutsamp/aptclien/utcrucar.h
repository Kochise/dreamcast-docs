/*+==========================================================================
  File:      UTCRUCAR.H

  Summary:   Include file for the aggregatable COUtilityCruiseCar COM
             object class.

             UTCRUCAR showcases the construction of the COUtilityCruiseCar
             COM object class with the IUnknown, ICar, ICruise, and
             IUtility interfaces.  This is done through Containment reuse
             of a COCruiseCar COM object (specifically providing its ICar
             and ICruise interface features).  COUtilityCruiseCar adds its
             own native implementation of the IUtility interface.  The
             contained CruiseCar object is implemented in an outside
             APTSERVE.EXE local server.

             This multiple interface COM Object Class is achieved via
             the technique of nested classes: the implementation of the
             IUtility interface is nested inside of the COUtilityCruiseCar
             COM object class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial APTCLIEN.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source
             code.

  Classes:   COUtilityCruiseCar.

  Functions: .

  Origin:    3-20-96: atrent - Editor inheritance from LOCCLIEN source.

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

#if !defined(UTCRUCAR_H)
#define UTCRUCAR_H

#ifdef __cplusplus

/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: COUtilityCruiseCar

  Summary:     COM Object Class for COUtilityCruiseCar COM Objects.
               COM objects of this class augment COCruiseCar COM objects
               with the IUtility interface features of Offroad and Winch.
               COCruiseCar is reused to offer this COUtilityCruiseCar COM
               Object the ICar interface features of Shift, Clutch, Speed,
               Steer and the ICruise interface features of Engage and
               Adjust.  This COUtilityCruiseCar COM object class is
               constructed by containment reuse of the COCruiseCar COM
               object class.  The mulitple interfaces on this COM object
               class are constructed via the nested class interfaces
               technique.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               ICar
                 Basic car features.
               ICruise
                 Cruise control system features.
               IUtility
                 Sport-utility Car operation features.  Implemented in
                 this COM object.

  Aggregation: Yes, COUtilityCruiseCar COM objects are aggregatable by
               passing a non-NULL pUnkOuter IUnknown pointer into
               the constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class COUtilityCruiseCar : public IUnknown
{
  public:
    // Main Object Constructor & Destructor.
    COUtilityCruiseCar(IUnknown* pUnkOuter);
    ~COUtilityCruiseCar(void);

    // A general method for initializing a newly created UtilityCruiseCar.
    HRESULT Init(void);

    // IUnknown members. Main object, non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

    // We get this ICar interface pointer via containment reuse of the
    // ICar interface in an instantiated COCruiseCar.
    ICar*                m_pICar;

    // We get this ICruise interface pointer via containment reuse of the
    // ICruise interface in an instantiated COCruisecar.
    ICruise*             m_pICruise;

  private:
    // We declare nested class interface implementations here.

    // We implement the ICar interface in this COUtilityCruiseCar COM
    // object class.  This is a delegating interface for the one
    // in the contained COCruiseCar COM object.
    class CImpICar : public ICar
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpICar(COUtilityCruiseCar* pBackObj, IUnknown* pUnkOuter);
        ~CImpICar(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // ICar methods.
        STDMETHODIMP         Shift(short nGear);
        STDMETHODIMP         Clutch(short nEngaged);
        STDMETHODIMP         Speed(short nMph);
        STDMETHODIMP         Steer(short nAngle);

      private:
        // Data private to this COUtilityCar interface implementation of ICar.
        ULONG                m_cRefI;     // Interface Ref Count (debugging).
        COUtilityCruiseCar*  m_pBackObj;  // Parent Object back pointer.
        IUnknown*            m_pUnkOuter; // Outer unknown for Delegation.
    };

    // We implement the ICruise interface in this COUtilityCruiseCar COM
    // object class.  This ICruise implementation is a delegating
    // interface for the one provided in the contained COCruiseCar COM
    // object.
    class CImpICruise : public ICruise
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpICruise(COUtilityCruiseCar* pBackObj, IUnknown* pUnkOuter);
        ~CImpICruise(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // ICruise methods.
        STDMETHODIMP Engage(BOOL bOnOff);
        STDMETHODIMP Adjust(BOOL bUpDown);

      private:
        // Data private to this interface implementation of ICruise.
        ULONG                m_cRefI;     // Interface Ref Count (debugging).
        COUtilityCruiseCar*  m_pBackObj;  // Parent Object back pointer.
        IUnknown*            m_pUnkOuter; // Outer unknown for Delegation.
    };

    // We implement the IUtility interface in this COUtilityCruiseCar COM
    // object class.  This is the native interface that we are using as an
    // augmentation to the existing COCruiseCar COM object class.
    class CImpIUtility : public IUtility
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIUtility(COUtilityCruiseCar* pBackObj, IUnknown* pUnkOuter);
        ~CImpIUtility(void);

        // IUnknown members.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // IUtility members.
        STDMETHODIMP Offroad(short nGear);
        STDMETHODIMP Winch(short nRpm);

      private:
        // Data private to this interface implementation of IUtility.
        ULONG                m_cRefI;     // Interface Ref Count (debugging).
        COUtilityCruiseCar*  m_pBackObj;  // Parent Object back pointer.
        IUnknown*            m_pUnkOuter; // Outer unknown for Delegation.
    };

    // Make the otherwise private and nested IUtility, ICruise, and ICar
    // interface implementations friend instantiations of this class.
    friend CImpICar;
    friend CImpICruise;
    friend CImpIUtility;

    // Private data of COUtilityCruiseCar COM objects.

    // Nested ICar implementation instantiation.
    CImpICar        m_ImpICar;

    // Nested ICruise implementation instantiation.
    CImpICruise     m_ImpICruise;

    // Nested IUtility implementation instantiation.  This IUtility
    // interface is implemented inside this COUtilityCruiseCar object
    // as a native interface.
    CImpIUtility    m_ImpIUtility;

    // Main Object reference count.
    ULONG           m_cRefs;

    // Outer unknown (aggregation & delegation). Used when this
    // COUtilityCruiseCar object is being aggregated.
    IUnknown*       m_pUnkOuter;
};

typedef COUtilityCruiseCar* PCOUtilityCruiseCar;

// Here is a prototpye for the UtilityCruiseCar Creation function.
HRESULT CreateUtilityCruiseCar(
          IUnknown* pUnkOuter,
          REFIID riid,
          PPVOID ppv);

#endif // __cplusplus


#endif // UTCRUCAR_H
