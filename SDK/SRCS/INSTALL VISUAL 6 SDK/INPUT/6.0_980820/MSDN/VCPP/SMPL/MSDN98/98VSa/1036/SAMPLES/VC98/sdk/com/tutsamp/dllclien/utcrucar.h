/*+==========================================================================
  File:      UTCRUCAR.H

  Summary:   Include file for the aggregatable COUtilityCruiseCar COM
             object class.

             UTCRUCAR showcases the construction of the COUtilityCruiseCar
             COM object class with the IUnknown, ICar, ICruise, and
             IUtility interfaces.  This is done through Aggregation reuse
             of a COCruiseCar COM object (specifically providing its ICar
             and ICruise interface features).  COUtilityCruiseCar adds its
             own native implementation of the IUtility interface.  The
             aggregated CruiseCar object is implemented and provided in an
             outside COMOBJ.DLL.

             This multiple interface COM Object Class is achieved via
             the technique of nested classes: the implementation of the
             IUtility interface is nested inside of the COUtilityCruiseCar
             COM object class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial DLLCLIEN.HTM
             file.  For more specific technical details on the internal
             workings see the comments dispersed throughout the
             module's source code.

  Classes:   COUtilityCruiseCar.

  Functions: .

  Origin:    9-20-95: atrent - Editor inheritance from COMUSER source.

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
               constructed by aggregation reuse of the COCruiseCar COM
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

  private:
    // We declare nested class interface implementations here.

    // We implement the IUtility interface (ofcourse) in this
    // COUtilityCruiseCar COM object class.  This is the native interface
    // that we are using as an augmentation to the existing COCruiseCar
    // COM object class.
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
        ULONG               m_cRefI;     // Interface Ref Count (debugging).
        COUtilityCruiseCar* m_pBackObj;  // Parent Object back pointer.
        IUnknown*           m_pUnkOuter; // Outer unknown for Delegation.
    };

    // Make the otherwise private and nested IUtility interface
    // implementation a friend to COM object instantiations of this
    // selfsame COUtilityCruiseCar COM object class.
    friend CImpIUtility;

    // Private data of COUtilityCruiseCar COM objects.

    // Nested IUtility implementation instantiation.  This IUtility
    // interface is instantiated inside this COUtilityCruiseCar object
    // as a native interface.
    CImpIUtility    m_ImpIUtility;

    // Main Object reference count.
    ULONG           m_cRefs;

    // Outer unknown (aggregation delegation). Used when this
    // COUtilityCruiseCar object is being aggregated.
    IUnknown*       m_pUnkOuter;

    // We need to save the IUnknown interface pointer on the COCruiseCar
    // object that we aggregate.  We use this when we need to delegate
    // IUnknown calls to this aggregated inner object.
    IUnknown*       m_pUnkCruiseCar;
};

typedef COUtilityCruiseCar* PCOUtilityCruiseCar;

// Here is a prototpye for the UtilityCruiseCar Creation function.
HRESULT CreateUtilityCruiseCar(
          IUnknown* pUnkOuter,
          REFIID riid,
          PPVOID ppv);

#endif // __cplusplus


#endif // UTCRUCAR_H
