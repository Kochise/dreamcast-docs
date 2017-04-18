/*+==========================================================================
  File:      SINK.H

  Summary:   Include file for the COBallSink COM object class.

             COBallSink offers a main IUnknown interface and the IBallSink
             interface (outgoing connection events from moving COBall
             objects). This multiple interface COM Object Class is
             achieved via the technique of nested classes.  The
             implementation of the IBallSink interface is nested inside of
             the COBallSink Class.

             For a comprehensive tutorial code tour of this module's
             contents and offerings see the tutorial CONCLIEN.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the module's source code.

  Functions:

  Classes:   COBallSink.

  Origin:    6-3-96: atrent - Editor-inheritance from BALL.H in the
             CONSERVE Tutorial Code Sample.

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

#if !defined(SINK_H)
#define SINK_H

#ifdef __cplusplus


/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: COBallSink

  Summary:     The main Sink COM object class for COBallSink COM objects.
               COM objects of this class offer the IBallSink sink
               interface supporting various ball bounce events. The
               mulitple interfaces on this COM object are constructed via
               the nested interface classes technique.

  Interfaces:  IUnknown
                 Standard interface providing COM object features.
               IBallSink
                 Sink interface for Ball events.

  Aggregation: Yes, COBall COM Objects are aggregatable by passing
               a non-NULL pUnkOuter IUnknown pointer into the constructor.
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/
class COBallSink : public IUnknown
{
  public:
    // Main Object Constructor & Destructor.
    COBallSink(IUnknown* pUnkOuter, CGuiBall* pGuiBall);
    ~COBallSink(void);

    // IUnknown methods. Main object, non-delegating.
    STDMETHODIMP         QueryInterface(REFIID, PPVOID);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

  private:
    // We declare nested class interface implementations here.

    class CImpIBallSink : public IBallSink
    {
      public:
        // Interface Implementation Constructor & Destructor.
        CImpIBallSink(COBallSink* pBackObj, IUnknown* pUnkOuter);
        ~CImpIBallSink(void);

        // IUnknown methods.
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        // IBallSink methods.
        STDMETHODIMP         BounceBottom(void);
        STDMETHODIMP         BounceLeft(void);
        STDMETHODIMP         BounceRight(void);
        STDMETHODIMP         BounceTop(void);

      private:
        // Data private to this interface implementation of IBallSink.
        COBallSink*  m_pBackObj;     // Parent Object back pointer.
        IUnknown*    m_pUnkOuter;    // Outer unknown for Delegation.
    };

    // Make the otherwise private and nested IBallSink interface
    // implementation a friend to COM object instantiations of this
    // COBallSink COM object class.
    friend CImpIBallSink;

    // Private data of COBallSink COM objects.

    // Nested IBallSink implementation instantiation.  This IBallSink
    // interface is instantiated inside this COBallSink object as a
    // native interface.
    CImpIBallSink    m_ImpIBallSink;

    // Main Object reference count.
    ULONG            m_cRefs;

    // Outer unknown (aggregation delegation). Used when this COM object
    // is being aggregated.
    IUnknown*        m_pUnkOuter;

    // Pointer to the main object that can service the Sink events.
    CGuiBall*        m_pGuiBall;
};

typedef COBallSink* PCOBallSink;

#endif // __cplusplus


#endif // SINK_H
