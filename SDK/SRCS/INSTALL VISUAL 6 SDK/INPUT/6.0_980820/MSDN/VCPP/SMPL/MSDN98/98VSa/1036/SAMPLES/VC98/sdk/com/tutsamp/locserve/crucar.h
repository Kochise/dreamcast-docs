/*+==========================================================================
  File:      CRUCAR.H

  Summary:   Include file for the aggregatable COCruiseCar COM object class.

             CRUCAR showcases the construction of the COCruiseCar COM
             object class with the IUnknown, ICar, and ICruise interfaces.
             This is done through Aggregation reuse of a COCar COM
             object (specifically providing its ICar interface features).

             This multiple interface COM Object Class is achieved via
             the technique of nested classes: the implementation of the
             ICar and ICruise interfaces are nested inside of the
             COCruiseCar COM object class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial LOCSERVE.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source code.

  Classes:   COCruiseCar.

  Functions: .

  Origin:    11-14-95: atrent - Editor-inheritance from CRUCAR.H in
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

#if !defined(CRUCAR_H)
#define CRUCAR_H

#ifdef __cplusplus

/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: COCruiseCar

  Summary:     COM Object Class for COCruiseCar COM Objects.  COM objects
               of this class augment COCar COM objects (which offer ICar
               interface features of Shift, Clutch, Speed, and Steer) with
               ICruise interface features (Engage and Adjust).  This
               COCruiseCar COM object class is constructed by aggregation
               reuse of the COCar COM object class.  The mulitple
               interfaces on this COM object class are constructed via
               the nested interface classes technique.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               ICar
                 Basic Car operation features.
               ICruise
                 Cruise control features.

  Aggregation: Yes, COCruiseCar COM objects are aggregatable by passing
               a non-NULL pUnkOuter IUnknown pointer into the constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class COCruiseCar : public IUnknown
{
  public:
    // Main Object Constructor & Destructor.
    COCruiseCar(IUnknown* pUnkOuter, CServer* pServer);
    ~COCruiseCar(void);

    // A general method for initializing a newly created COCruiseCar.
    HRESULT Init(void);

    // IUnknown methods. Main object, non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

  private:
    // We declare nested class interface implementations here.

    // We implement the ICruise interface (of-course) in this COCruiseCar
    // COM object class.  This is the interface that we are using as an
    // augmentation to the existing COCar COM object class.
    class CImpICruise : public ICruise
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpICruise(COCruiseCar* pBackObj, IUnknown* pUnkOuter);
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
        ULONG         m_cRefI;       // Interface Ref Count (for debugging).
        COCruiseCar*  m_pBackObj;    // Parent Object back pointer.
        IUnknown*     m_pUnkOuter;   // Outer unknown for Delegation.
    };

    // Make the otherwise private and nested ICar interface implementation
    // a friend to COM object instantiations of this selfsame COCruiseCar
    // COM object class.
    friend CImpICruise;

    // Private data of COCruiseCar COM objects.

    // Nested ICruise implementation instantiation.  This ICruise interface
    // is implemented inside this COCruiseCar object as a native interface.
    CImpICruise     m_ImpICruise;

    // Main Object reference count.
    ULONG           m_cRefs;

    // Outer unknown (aggregation & delegation). Used when this COCruiseCar
    // object is being aggregated.  Otherwise it is used for delegation
    // if this object is reused via containment.
    IUnknown*       m_pUnkOuter;

    // We need to save the IUnknown interface pointer on the COCar
    // object that we aggregate.  We use this when we need to delegate
    // IUnknown calls to this aggregated inner object.
    IUnknown*       m_pUnkCar;

    // Pointer to this component server's control object.
    CServer*        m_pServer;
};

typedef COCruiseCar* PCOCruiseCar;

#endif // __cplusplus


#endif // CRUCAR_H
