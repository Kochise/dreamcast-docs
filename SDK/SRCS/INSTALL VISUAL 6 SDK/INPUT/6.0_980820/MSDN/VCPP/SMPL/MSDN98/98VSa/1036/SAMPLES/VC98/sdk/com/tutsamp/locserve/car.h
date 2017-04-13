/*+==========================================================================
  File:      CAR.H

  Summary:   Include file for the aggregatable COCar COM object class.

             COCar offers a main IUnknown interface and the ICar
             interface (Car-related features).  This multiple interface
             COM Object Class is achieved via the technique of nested
             classes.  The implementation of the ICar interface is
             nested inside of the COCar Class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial LOCSERVE.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source
             code.

  Classes:   COCar.

  Functions:

  Origin:    11-14-95: atrent - Editor-inheritance from CAR.H in
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

#if !defined(CAR_H)
#define CAR_H

#ifdef __cplusplus

/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: COCar

  Summary:     COM object class for COCar COM objects.  COM objects of
               this class offer ICar interface features (Shift, Clutch,
               Speed, and Steer).  The mulitple interfaces on this COM
               object are constructed via the nested interface classes
               technique.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               ICar
                 Basic Car operation features.

  Aggregation: Yes, COCar COM Objects are aggregatable by passing
               a non-NULL pUnkOuter IUnknown pointer into the constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class COCar : public IUnknown
{
  public:
    // Main Object Constructor & Destructor.
    COCar(IUnknown* pUnkOuter, CServer* pServer);
    ~COCar(void);

    // IUnknown methods. Main object, non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

  private:
    // We declare nested class interface implementations here.

    class CImpICar : public ICar
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpICar(COCar* pBackObj, IUnknown* pUnkOuter);
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
        // Data private to this COCar interface implementation of ICar.
        ULONG        m_cRefI;        // Interface Ref Count (for debugging).
        COCar*       m_pBackObj;     // Parent Object back pointer.
        IUnknown*    m_pUnkOuter;    // Outer unknown for Delegation.
    };

    // Make the otherwise private and nested ICar interface implementation
    // a friend to COM object instantiations of this selfsame COCar
    // COM object class.
    friend CImpICar;

    // Private data of COCar COM objects.

    // Nested ICar implementation instantiation.  This ICar interface
    // is instantiated inside this COCar object as a native interface.
    CImpICar         m_ImpICar;

    // Main Object reference count.
    ULONG            m_cRefs;

    // Outer unknown (aggregation & delegation).
    IUnknown*        m_pUnkOuter;

    // Pointer to this component server's control object.
    CServer*         m_pServer;
};

typedef COCar* PCOCar;

#endif // __cplusplus


#endif // CAR_H
