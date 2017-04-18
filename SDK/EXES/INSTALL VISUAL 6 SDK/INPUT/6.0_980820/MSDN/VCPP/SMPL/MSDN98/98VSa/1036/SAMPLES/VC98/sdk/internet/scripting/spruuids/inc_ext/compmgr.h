//---------------------------------------------------------------------------
// CompMgr.h
//---------------------------------------------------------------------------
// This file contains the exported interfaces and declarations for 
// Component Manager Interfaces.
//---------------------------------------------------------------------------
// Copyright (c) 1995-1997 Microsoft Corporation
//---------------------------------------------------------------------------


#ifdef INITGUID
    #define DEFINE_GUID2(name, bCategory, bIndex) \
        EXTERN_C const GUID name = {0x000C0000 | MAKEWORD(bIndex, bCategory),}
#else
    #define DEFINE_GUID2(name, bCategory, bIndex) \
        EXTERN_C const GUID name
#endif

DEFINE_GUID2(IID_IOleComponent,        0x06, 0x00);
DEFINE_GUID2(IID_IOleComponentManager, 0x06, 0x01);



//***************************************************************************
// Component integration structures and constants
//***************************************************************************

//---------------------------------------------------------------------------
// Component registration flags
//---------------------------------------------------------------------------
enum
    {
    cmgrrfNeedIdleTime         = 1,  // needs idle time
    cmgrrfNeedPeriodicIdleTime = 2,  // needs idle time every N milliseconds
    cmgrrfPreTranslateKeys     = 4,  // must process keyboard msgs 
	                             // before translation
    cmgrrfPreTranslateAll      = 8,  // must process all msgs 
	                             // before translation
    };


//---------------------------------------------------------------------------
// Component registration advise flags (see cmgrstate enumeration)
//---------------------------------------------------------------------------
enum
    {
    cmgradvfModal              = 1,  // needs modal state change notification
	                             // (must be registered by components
	                             // managing a toplevel window)												
    cmgradvfRedrawOff          = 2,  // needs redrawOff state change notif
    cmgradvfWarningsOff        = 4,  // needs warningsOff state change notif
    cmgradvfRecording          = 8,  // needs Recording state change notif
    cmgradvfExclusiveActive    = 16, // needs ExclusiveActive change notif
	                             // (must be registered by components
	                             //  managing a window with UI).
    };


//---------------------------------------------------------------------------
// Component registration information
//---------------------------------------------------------------------------
typedef struct _CMGRRINFO
    {
    ULONG cbSize;             // size of CMGRRINFO structure in bytes.
    ULONG uIdleTimeInterval;  // If cmgrrfNeedPeriodicIdleTime is registered
	                      // in grfcrf, component needs to perform
	                      // periodic idle time tasks during an idle phase
	                      // every uIdleTimeInterval milliseconds.
    DWORD grfcrf;             // bit flags taken from cmgrrf values (above)
    DWORD grfcadvf;           // bit flags taken from cmgradvf values (above)
    } CMGRRINFO;


//---------------------------------------------------------------------------
// Idle flags, passed to IOleComponent::FDoIdle and 
// IOleStdComponentMgr::FDoIdle.
//---------------------------------------------------------------------------
enum
    {
    cmgridlefPeriodic    = 1,  // periodic idle tasks
    cmgridlefNonPeriodic = 2,  // any nonperiodic idle task
    cmgridlefPriority    = 4,  // high priority, nonperiodic idle tasks
    cmgridlefAll         = -1  // all idle tasks
    };


//---------------------------------------------------------------------------
// Reasons for pushing a message loop, passed to 
// IOleComponentHost::FPushMessageLoop.  The host should remain in message
// loop until IOleComponent::FContinueMessageLoop returns FALSE.
//---------------------------------------------------------------------------
enum
    {
    cmgrloopFocusWait = 1,  // component is activating host 
    cmgrloopDoEvents  = 2,  // component is asking host to process messages
    cmgrloopDebug     = 3,  // component has entered debug mode
    cmgrloopModalForm = 4   // component is displaying a modal form  
    };


//---------------------------------------------------------------------------
// cmgrstate values: state IDs passed to 
//  IOleComponent::OnEnterState, 
//  IOleComponentManager::OnComponentEnterState/FOnComponentExitState/FInState,
//
//  When the host or a component is notified through one of these methods that 
//  another entity (component or host) is entering or exiting a state 
//  identified by one of these state IDs, the host/component should take
//  appropriate action:
//      cmgrstateModal (modal state):
//	    If app is entering modal state, host/component should disable
//	    its toplevel windows, and reenable them when app exits this
//	    state.  Also, when this state is entered or exited, host/component
//	    should notify approprate inplace objects via 
//	    IOleInPlaceActiveObject::EnableModeless.
//	cmgrstateRedrawOff (redrawOff state):
//	    If app is entering redrawOff state, host/component should disable
//	    repainting of its windows, and reenable repainting when app exits
//	    this state.
//	cmgrstateWarningsOff (warningsOff state):
//	    If app is entering warningsOff state, host/component should disable
//	    the presentation of any user warnings, and reenable this when
//	    app exits this state.
//	cmgrstateRecording (Recording state):
//	    Used to notify host/component when Recording is turned on or off.
//	cmgrstateExclusiveActive (Exclusive Active state)
//	    TODO: add comments on what host/component should do.
//---------------------------------------------------------------------------
enum
    {
    cmgrstateModal       = 1,     // Modal state; disable toplevel windows
    cmgrstateRedrawOff   = 2,     // RedrawOff state; disable window repainting
    cmgrstateWarningsOff = 3,     // WarningsOff state; disable user warnings
    cmgrstateRecording   = 4,     // Recording state
    cmgrstateExclusiveActive = 5, // ExclusiveActive state; TODO: add brief
	                          // comment on what should be done here
    };


//---------------------------------------------------------------------------
// ** Comments on State Contexts **
//---------------------------------------------------------------------------
// IOleComponentManager::FCreateSubComponentManager allows one to create a 
// hierarchical tree of component managers.  This tree is used to maintain 
// multiple contexts with regard to cmgrstateXXX states.  These contexts are 
// referred to as 'state contexts'.
// Each component manager in the tree defines a state context.  The
// components registered with a particular component manager or any of its
// descendents live within that component manager's state context.  Calls
// to IOleComponentManager::OnComponentEnterState/FOnComponentExitState
// can be used to affect all components, only components within the component
// manager's state context, or only those components that are outside of the
// component manager's state context.  IOleComponentManager::FInState is used
// to query the state of the component manager's state context at its root.
//
// cmgrcontext values: context indicators passed to 
// IOleComponentManager::OnComponentEnterState/FOnComponentExitState.
// These values indicate the state context that is to be affected by the
// state change. 
// In IOleComponentManager::OnComponentEnterState/FOnComponentExitState,
// the comp mgr informs only those components/host that are within the
// specified state context.
//---------------------------------------------------------------------------
enum
    {
    cmgrcontextAll    = 0, // all state contexts in state context tree
    cmgrcontextMine   = 1, // component manager's state context
    cmgrcontextOthers = 2, // all other state contexts outside of comp mgr's
    };


//---------------------------------------------------------------------------
// Defines the IOleComponent interface
//---------------------------------------------------------------------------
// Any component that needs idle time, the ability to process messages before
// they are translated (for example, to call TranslateAccelerator() or
// IsDialogMessage), notification about modal states, or the ability push
// message loops must implement this interface and register with the
// Component Manager.
//---------------------------------------------------------------------------
#undef  INTERFACE
#define INTERFACE  IOleComponent

DECLARE_INTERFACE_(IOleComponent, IUnknown)
	{
	// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, void **ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS) PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

	// Give component a chance to process the message pMsg before it is
	// translated and dispatched. Component can do TranslateAccelerator,
	// do IsDialogMessage, modify pMsg, or take some other action.
	// Return TRUE if the message is consumed, FALSE otherwise.
	STDMETHOD_(BOOL, FPreTranslateMessage) (THIS_ MSG *pMsg) PURE;

#if MAC
	// Give Macintosh component a chance to process the event pEvt
	// before it is processed by the host. 
	// Return TRUE if the event is consumed, FALSE otherwise.
	// (WLM components can simply return FALSE.)
	STDMETHOD_(BOOL, FPreProcessMacEvent) (THIS_ EventRecord *pEvt) PURE;
#endif // MAC
	
	// Notify component when app enters or exits (as indicated by fEnter)
	// the state identified by uStateID (a value from cmgrstate enumeration).
	// Component should take action depending on value of uStateID
	// (see cmgrstate comments, above).
	// 	
	// Note: If n calls are made with TRUE fEnter, component should consider 
	// the state to be in effect until n calls are made with FALSE fEnter.
	// 	
	// Note: Components should be aware that it is possible for this method to
	// be called with FALSE fEnter more times than it was called with TRUE 
	// fEnter (so, for example, if component is maintaining a state counter
	// (incremented when this method is called with TRUE fEnter, decremented
	// when called with FALSE fEnter), the counter should not be decremented
	// for FALSE fEnter if it is already at zero.)
	STDMETHOD_(void, OnEnterState) (THIS_ ULONG uStateID, BOOL fEnter) PURE;

	// Notify component when the host application gains or loses activation.
	// If fActive is TRUE, the host app is being activated and dwOtherThreadID
	// is the ID of the thread owning the window being deactivated.
	// If fActive is FALSE, the host app is being deactivated and 
	// dwOtherThreadID is the ID of the thread owning the window being 
	// activated.
	// Note: this method is not called when both the window being activated
	// and the one being deactivated belong to the host app.
	STDMETHOD_(void, OnAppActivate) (THIS_ 
		BOOL fActive, DWORD dwOtherThreadID) PURE;
	
	// Notify the active component that it has lost its active status because
	// the host or another component has become active.
	STDMETHOD_(void, OnLoseActivation) (THIS) PURE;

	// Give component a chance to do idle time tasks.  grfidlef is a group of
	// bit flags taken from the enumeration of cmgridlef values (above),
	// indicating the type of idle tasks to perform.  
	// Component may periodically call IOleComponentManager::FContinueIdle; 
	// if this method returns FALSE, component should terminate its idle 
	// time processing and return.  
	// Return TRUE if more time is needed to perform the idle time tasks, 
	// FALSE otherwise.
	// Note: If a component reaches a point where it has no idle tasks
	// and does not need FDoIdle calls, it should remove its idle task
	// registration via IOleComponentManager::FUpdateComponentRegistration.
	// Note: If this method is called on while component is performing a 
	// tracking operation, component should only perform idle time tasks that
	// it deems are appropriate to perform during tracking.
	STDMETHOD_(BOOL, FDoIdle) (THIS_ DWORD grfidlef) PURE;
	
	// Called once per iteration of a message loop that the component pushed.
	// uReason and pvLoopData are the reason and the component private data
	// that were passed to IOleComponentManager::FPushMessageLoop.
	// Return TRUE if the message loop should continue, FALSE otherwise.
	STDMETHOD_(BOOL, FContinueMessageLoop) (THIS_ 
		ULONG uReason, void *pvLoopData) PURE;

	// Called when component manager wishes to know if the component is in a
	// state in which it can terminate.  If fPromptUser is FALSE, component
	// should simply return TRUE if it can terminate, FALSE otherwise.
	// If fPromptUser is TRUE, component should return TRUE if it can
	// terminate without prompting the user; otherwise it should prompt the
	// user, either 1.) asking user if it can terminate and returning TRUE
	// or FALSE appropriately, or 2.) giving an indication as to why it
	// cannot terminate and returning FALSE.
	STDMETHOD_(BOOL, FQueryTerminate) (THIS_ BOOL fPromptUser) PURE;
	
	// Called when component manager wishes to terminate the component's
	// registration.  Component should revoke its registration with component
	// manager, release references to component manager and perform any
	// necessary cleanup.
	STDMETHOD_(void, Terminate) (THIS) PURE;
	};



//---------------------------------------------------------------------------
// Defines the IOleComponentManager interface
//---------------------------------------------------------------------------
// A component manager is an object implementing the IOleComponentManager
// interface.  The component manager coordinates components with its message
// loop for proper distribution of idle time and pre-translation message
// processing.	
// It also coordinates modalities and the pushing of message loops.
//---------------------------------------------------------------------------
#undef  INTERFACE
#define INTERFACE  IOleComponentManager

DECLARE_INTERFACE_(IOleComponentManager, IUnknown)
	{
	// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, void **ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS) PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

	// Return in *ppvObj an implementation of interface iid for service
	// guidService (same as IServiceProvider::QueryService).
	// Return NOERROR if the requested service is supported, otherwise return
	// NULL in *ppvObj and an appropriate error (eg E_FAIL, E_NOINTERFACE).
	STDMETHOD(QueryService) (THIS_
		REFGUID guidService, REFIID iid, void **ppvObj) PURE;

	// Register component piComponent and its registration info pcrinfo with
	// this component manager.  Return in *pdwComponentID a cookie which will
	// identify the component when it calls other IOleComponentManager
	// methods.
	// Return TRUE if successful, FALSE otherwise.
	STDMETHOD_(BOOL, FRegisterComponent) (THIS_
		IOleComponent *piComponent, const CMGRRINFO *pcrinfo, 
		DWORD *pdwComponentID) PURE;
	
	// Undo the registration of the component identified by dwComponentID
	// (the cookie returned from the FRegisterComponent method).
	// Return TRUE if successful, FALSE otherwise.
	STDMETHOD_(BOOL, FRevokeComponent) (THIS_ DWORD dwComponentID) PURE;
	
	// Update the registration info of the component identified by
	// dwComponentID (the cookie returned from FRegisterComponent) with the
	// new registration information pcrinfo.
	// Typically this is used to update the idle time registration data, but
	// can be used to update other registration data as well.
	// Return TRUE if successful, FALSE otherwise.
	STDMETHOD_(BOOL, FUpdateComponentRegistration) (THIS_ 
		DWORD dwComponentID, const CMGRRINFO *pcrinfo) PURE;
	
	// Notify component manager that component identified by dwComponentID
	// (cookie returned from FRegisterComponent) has been activated.
	// The active component gets the chance to process messages before they
	// are dispatched (via IOleComponent::FPreTranslateMessage) and typically
	// gets first crack at idle time after the host.
	STDMETHOD_(void, OnComponentActivate) (THIS_ DWORD dwComponentID) PURE;
	
	// Called to inform component manager that  component identified by 
	// dwComponentID (cookie returned from FRegisterComponent) wishes
	// to perform a tracking operation (such as mouse tracking).
	// The component calls this method with fTrack == TRUE to begin the
	// tracking operation and with fTrack == FALSE to end the operation.
	// During the tracking operation the component manager routes messages
	// to the tracking component (via IOleComponent::FPreTranslateMessage)
	// rather than to the active component.  When the tracking operation ends,
	// the component manager should resume routing messages to the active
	// component.  
	// Note: component manager should perform no idle time processing during a
	// tracking operation other than give the tracking component idle
	// time via IOleComponent::FDoIdle.
	// Note: there can only be one tracking component at a time.
	// Return TRUE if successful, FALSE otherwise.
	STDMETHOD_(BOOL, FSetTrackingComponent) (THIS_ 
		DWORD dwComponentID, BOOL fTrack) PURE;

	// Notify component manager that component identified by dwComponentID
	// (cookie returned from FRegisterComponent) is entering the state
	// identified by uStateID (cmgrstateXXX value).  (For convenience when
	// dealing with sub CompMgrs, the host can call this method passing 0 for
	// dwComponentID.)  
	// Component manager should notify all other interested components within
	// the state context indicated by uContext (a cmgrcontextXXX value),
	// excluding those within the state context of a CompMgr in rgpicmExclude,
	// via IOleComponent::OnEnterState (see "Comments on State Contexts", 
	// above).
	// Component Manager should also take appropriate action depending on the 
	// value of uStateID (see cmgrstate comments, above).
	// dwReserved is reserved for future use and should be zero.
        // 
	// rgpicmExclude (can be NULL) is an array of cpicmExclude CompMgrs (can
	// include root CompMgr and/or sub CompMgrs); components within the state
	// context of a CompMgr appearing in this	array should NOT be notified of 
	// the state change (note: if uContext	is cmgrcontextMine, the only 
	// CompMgrs in rgpicmExclude that are checked for exclusion are those that 
	// are sub CompMgrs of this Component Manager, since all other CompMgrs 
	// are outside of this Component Manager's state context anyway.)
        // 
	// Note: Calls to this method are symmetric with calls to 
	// FOnComponentExitState. 
	// That is, if n OnComponentEnterState calls are made, the component is
	// considered to be in the state until n FOnComponentExitState calls are
	// made.  Before revoking its registration a component must make a 
	// sufficient number of FOnComponentExitState calls to offset any
	// outstanding OnComponentEnterState calls it has made.
        // 
	// Note: inplace objects should not call this method with
	// uStateID == cmgrstateModal when entering modal state. Such objects
	// should call IOleInPlaceFrame::EnableModeless instead.
	STDMETHOD_(void, OnComponentEnterState) (THIS_ 
		DWORD dwComponentID, 
		ULONG uStateID, 
		ULONG uContext,
		ULONG cpicmExclude,
		IOleComponentManager **rgpicmExclude, 
		DWORD dwReserved) PURE;
	
	// Notify component manager that component identified by dwComponentID
	// (cookie returned from FRegisterComponent) is exiting the state
	// identified by uStateID (a cmgrstateXXX value).  (For convenience when
	// dealing with sub CompMgrs, the host can call this method passing 0 for
	// dwComponentID.)
	// uContext, cpicmExclude, and rgpicmExclude are as they are in 
	// OnComponentEnterState.
	// Component manager	should notify all appropriate interested components
	// (taking into account uContext, cpicmExclude, rgpicmExclude) via
	// IOleComponent::OnEnterState (see "Comments on State Contexts", above). 
	// Component Manager should also take appropriate action depending on
	// the value of uStateID (see cmgrstate comments, above).
	// Return TRUE if, at the end of this call, the state is still in effect
	// at the root of this component manager's state context
	// (because the host or some other component is still in the state),
	// otherwise return FALSE (ie. return what FInState would return).
	// Caller can normally ignore the return value.
	// 
	// Note: n calls to this method are symmetric with n calls to 
	// OnComponentEnterState (see OnComponentEnterState comments, above).
	STDMETHOD_(BOOL, FOnComponentExitState) (THIS_ 
		DWORD dwComponentID, 
		ULONG uStateID, 
		ULONG uContext,
		ULONG cpicmExclude,
		IOleComponentManager **rgpicmExclude) PURE;

	// Return TRUE if the state identified by uStateID (a cmgrstateXXX value)
	// is in effect at the root of this component manager's state context, 
	// FALSE otherwise (see "Comments on State Contexts", above).
	// pvoid is reserved for future use and should be NULL.
	STDMETHOD_(BOOL, FInState) (THIS_ ULONG uStateID, void *pvoid) PURE;
	
	// Called periodically by a component during IOleComponent::FDoIdle.
	// Return TRUE if component can continue its idle time processing, 
	// FALSE if not (in which case component returns from FDoIdle.)
	STDMETHOD_(BOOL, FContinueIdle) (THIS) PURE;

	// Component identified by dwComponentID (cookie returned from 
	// FRegisterComponent) wishes to push a message loop for reason uReason.
	// uReason is one the values from the cmgrloop enumeration (above).
	// pvLoopData is data private to the component.
	// The host should push its message loop, 
	// calling IOleComponent::FContinueMessageLoop(uReason, pvLoopData)
	// once per loop iteration.  When IOleComponent::FContinueMessageLoop
	// returns FALSE, the host should terminate the loop.
	STDMETHOD_(BOOL, FPushMessageLoop) (THIS_ 
		DWORD dwComponentID, ULONG uReason, void *pvLoopData) PURE;

	// Cause the component manager to create a "sub" component manager, which
	// will be one of its children in the hierarchical tree of component
	// managers used to maintiain state contexts (see "Comments on State
	// Contexts", above).
	// piunkOuter is the controlling unknown (can be NULL), riid is the
	// desired IID, and *ppvObj returns the created sub component manager.
	// piunkServProv (can be NULL) is a ptr to an object supporting
	// IServiceProvider interface to which the created sub component manager
	// will delegate its IOleComponentManager::QueryService calls. 
	// (see objext.h or docobj.h for definition of IServiceProvider).
	// Returns TRUE if successful.
	STDMETHOD_(BOOL, FCreateSubComponentManager) (THIS_ 
		IUnknown *piunkOuter, 
		IUnknown *piunkServProv,
		REFIID riid, 
		void **ppvObj) PURE;

	// Return in *ppicm an AddRef'ed ptr to this component manager's parent
	// in the hierarchical tree of component managers used to maintain state
	// contexts (see "Comments on State Contexts", above).
	// Returns TRUE if the parent is returned, FALSE if no parent exists or
	// some error occurred.
	STDMETHOD_(BOOL, FGetParentComponentManager) (THIS_ 
		IOleComponentManager **ppicm) PURE;

	// Return in *ppic an AddRef'ed ptr to the current active component.
	// Returns TRUE if the active component is returned, FALSE if no component
	// is active or some error occurred.
	// dwReserved is reserved for future use and should be zero.
	STDMETHOD_(BOOL, FGetActiveComponent) (THIS_ 
		DWORD dwReserved, IOleComponent **ppic) PURE;
	};

//--- EOF -------------------------------------------------------------------
