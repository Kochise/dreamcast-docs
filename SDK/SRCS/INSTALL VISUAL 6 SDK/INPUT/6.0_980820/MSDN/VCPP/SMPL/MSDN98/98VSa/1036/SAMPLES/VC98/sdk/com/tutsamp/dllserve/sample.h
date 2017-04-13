/*+==========================================================================
  File:      SAMPLE.H

  Summary:   Declares a COCarSample utility COM object used to implement
             the server as a code sample (mainly with an Init method
             to enable setting up Trace logging of activity in the
             server to the logging facility in the Client).

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial DLLSERVE.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source code.

  Classes:   COCarSample.

  Functions: none

  Origin:    9-11-95: atrent - Editor-inheritance from CAR.H in
               the COMOBJ Tutorial Code Sample.

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

#if !defined(SAMPLE_H)
#define SAMPLE_H

#ifdef __cplusplus

/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: COCarSample

  Summary:     Utility CarSample COM Object Class for the DLLSERVE server
               as a code sample.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               ISample
                 Sample-specific Utility services for server as a whole.

  Aggregation: Yes, COCarSample COM objects are aggregatable by
               passing a non-NULL pUnkOuter IUnknown pointer into the
               constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class COCarSample : public IUnknown
{
  public:
    // Main Object Constructor & Destructor.
    COCarSample(IUnknown* pUnkOuter, CServer* pServer);
    ~COCarSample(void);

    // IUnknown methods. Main object, non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

  private:
    // We declare nested class interface implementations here.

    // We implement the ISample interface in this COCarSample
    // COM object class.
    class CImpISample : public ISample
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpISample(
          COCarSample* pBackObj,
          IUnknown* pUnkOuter,
          CServer* pServer);
        ~CImpISample(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // ISample methods.
        STDMETHODIMP         Init(HWND, PVOID);
        STDMETHODIMP         AboutBox(HWND);

      private:
        // Data private to this interface implementation of ISample.
        ULONG         m_cRefI;        // Interface Ref Count (for debugging).
        COCarSample*  m_pBackObj;     // Parent Object back pointer.
        IUnknown*     m_pUnkOuter;    // Outer unknown for Delegation.
        CServer*      m_pServer;      // Server Control object.
    };

    // Make the otherwise private and nested ISample interface
    // implementation a friend to COM object instantiations of this
    // selfsame COCarSample COM object class.
    friend CImpISample;

    // Private data of COCarSample COM objects.

    // Nested ISample implementation instantiation.
    CImpISample      m_ImpISample;

    // Main Object reference count.
    ULONG            m_cRefs;

    // Outer unknown (aggregation & delegation). Used when this
    // COCarSample object is being aggregated.  Otherwise it is used
    // for delegation if this object is reused via containment.
    IUnknown*        m_pUnkOuter;

    // Pointer to this component server's control object.
    CServer*         m_pServer;
};

typedef COCarSample* PCOCarSample;

#endif // __cplusplus


#endif // SAMPLE_H
