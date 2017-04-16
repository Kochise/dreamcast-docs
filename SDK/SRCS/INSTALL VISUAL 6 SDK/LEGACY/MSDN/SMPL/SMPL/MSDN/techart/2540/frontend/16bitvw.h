// 16bitvw.h : interface of the C16bitView class
//
/////////////////////////////////////////////////////////////////////////////

/*
 *  SYS_CRITICAL_INIT is a device init call.  Devices that have a
 *  critical function that needs initializing before interrupts are
 *  enabled should do it at Sys_Critical_Init.	Devices which REQUIRE a
 *  certain range of V86 pages to operate (such as the VDD video memory)
 *  should claim them at Sys_Critical_Init.  SYS VM Simulate_Int,
 *  Exec_Int ACTIVITY IS NOT ALLOWED.  Returning carry aborts device
 *  load only.
 */
#define SYS_CRITICAL_INIT	0x0000		/* Devices req'd for virt mode */

/*
 *  DEVICE_INIT is where most devices do the bulk of their initialization.
 *  SYS VM Simulate_Int, Exec_Int activity is allowed. Returning carry
 *  aborts device load only.
 */
#define DEVICE_INIT		0x0001		/* All other devices init */

/*
 *  INIT_COMPLETE is the final phase of device init called just before the
 *  WIN386 INIT pages are released and the Instance snapshot is taken.
 *  Devices which wish to search for a region of V86 pages >= A0h to use
 *  should do it at INIT_COMPLETE.
 *  SYS VM Simulate_Int, Exec_Int activity is allowed.	Returning carry
 *  aborts device load only.
 */
#define INIT_COMPLETE		0x0002		/* All devices initialized */

/* --------------- INITIALIZATION CODE AND DATA DISCARDED ------------------ */

/*
 *  Same as VM_Init, except for SYS VM.
 */
#define SYS_VM_INIT		0x0003		/* Execute the system VM */

/*
 *  Same as VM_Terminate, except for SYS VM (Normal WIN386 exit ONLY, on a crash
 *  exit this call is not made).  SYS VM Simulate_Int, Exec_Int activity is
 *  allowed.
 */
#define SYS_VM_TERMINATE	0x0004		/* System VM terminated */

/*
 *  System_Exit call is made when WIN386 is exiting either normally or via
 *  a crash.  INTERRUPTS ARE ENABLED.  Instance snapshot has been restored.
 *  SYS VM Simulate_Int, Exec_Int ACTIVITY IS NOT ALLOWED.
 */
#define SYSTEM_EXIT		0x0005		/* Devices prepare to exit */

/*
 *  SYS_CRITICAL_EXIT call is made when WIN386 is exiting either normally or via
 *  a crash.  INTERRUPTS ARE DISABLED.	SYS VM Simulate_Int, Exec_Int ACTIVITY
 *   IS NOT ALLOWED.
 */
#define SYS_CRITICAL_EXIT	0x0006		/* System critical devices reset */


/*
 *  Create_VM creates a new VM.  EBX = VM handle of new VM.  Returning
 *  Carry will fail the Create_VM.
 */
#define CREATE_VM		0x0007

/*
 *  Second phase of Create_VM.	EBX = VM handle of new VM.  Returning
 *  Carry will cause the VM to go Not_Executeable, then be destroyed.
 *  VM Simulate_Int, Exec_Int activity is NOT allowed.
 */
#define VM_CRITICAL_INIT	0x0008

/*
 *  Third phase of Create_VM.  EBX = VM handle of new VM.  Returning
 *  Carry will cause the VM to go Not_Executeable, then be destroyed.
 *  VM Simulate_Int, Exec_Int activity is allowed.
 */
#define VM_INIT 		0x0009

/*
 *  NORMAL (First phase) of Destroy_VM.  EBX = VM Hanlde.  This occurs
 *  on normal termination of the VM.  Call cannot be failed.  VM
 *  Simulate_Int, Exec_Int activity is allowed.
 */
#define VM_TERMINATE		0x000A		/* Still in VM -- About to die */

/*
 *  Second phase of Destroy_VM.  EBX = VM Handle, EDX = Flags (see
 *  below).  Note that in the case of destroying a running VM, this is
 *  the first call made (VM_Terminate call does not occur).  Call cannot
 *  be failed.	VM Simulate_Int, Exec_Int activity is NOT allowed.
 */
#define VM_NOT_EXECUTEABLE	0x000B		/* Most devices die (except VDD) */

/*
 *  Final phase of Destroy_VM.	EBX = VM Handle.  Note that considerable
 *  time can elaps between the VM_Not_Executeable call and this call.
 *  Call cannot be failed.  VM Simulate_Int, Exec_Int activity is NOT
 *  allowed.
 */
#define DESTROY_VM		0x000C		/* VM's control block about to go */


/*
 *  Flags for VM_Not_Executeable control call (passed in EDX)
 */
#define VNE_CRASHED_BIT 	0x00		/* VM was crashed */
#define VNE_CRASHED		(1 << VNE_CRASHED_BIT)
#define VNE_NUKED_BIT		0x01		/* VM was destroyed while active */
#define VNE_NUKED		(1 << VNE_NUKED_BIT)
#define VNE_CREATEFAIL_BIT	0x02		/* Some device failed Create_VM */
#define VNE_CREATEFAIL		(1 << VNE_CREATEFAIL_BIT)
#define VNE_CRINITFAIL_BIT	0x03		/* Some device failed VM_Critical_Init */
#define VNE_CRINITFAIL		(1 << VNE_CRINITFAIL_BIT)
#define VNE_INITFAIL_BIT	0x04		/* Some device failed VM_Init */
#define VNE_INITFAIL		(1 << VNE_INITFAIL_BIT)
#define VNE_CLOSED_BIT		0x05
#define VNE_CLOSED		(1 << VNE_CLOSED_BIT)


/*
 *  EBX = VM Handle. Call cannot be failed.
 */
#define VM_SUSPEND		0x000D		/* VM not runnable until resume */

/*
 *  EBX = VM Handle. Returning carry fails and backs out the resume.
 */
#define VM_RESUME		0x000E		/* VM is leaving suspended state */


/*
 *  EBX = VM Handle to set device focus to.  EDX = Device ID if device
 *  specific setfocus, == 0 if device critical setfocus (all devices).
 *  THIS CALL CANNOT BE FAILED.
 *
 *  NOTE: In case where EDX == 0, ESI is a FLAG word that indicates
 *  special functions.	Currently Bit 0 being set indicates that this
 *  Device critical set focus is also "VM critical".  It means that we
 *  do not want some other VM to take the focus from this app now.  This
 *  is primarily used when doing a device critical set focus to Windows
 *  (the SYS VM) it is interpreted by the SHELL to mean "if an old app
 *  currently has the Windows activation, set the activation to the
 *  Windows Shell, not back to the old app".  ALSO in the case where Bit
 *  0 is set, EDI = The VM handle of the VM that is "having trouble".
 *  Set this to 0 if there is no specific VM associated with the
 *  problem.
 */
#define SET_DEVICE_FOCUS	0x000F


/*
 *  EBX = VM Handle going into message mode.  THIS CALL CANNOT BE FAILED.
 */
#define BEGIN_MESSAGE_MODE	0x0010

/*
 *  EBX = VM Handle leaving message mode.  THIS CALL CANNOT BE FAILED.
 */
#define END_MESSAGE_MODE	0x0011


/* ----------------------- SPECIAL CONTROL CALLS --------------------------- */

/*
 *  Request for reboot.  Call cannot be failed.
 */
#define REBOOT_PROCESSOR	0x0012		/* Request a machine reboot */

/*
 *  Query_Destroy is an information call made by the SHELL device before
 *  an attempt is made to initiate a destroy VM sequence on a running VM
 *  which has not exited normally.  EBX = VM Handle.  Returning carry
 *  indicates that a device "has a problem" with allowing this.  THE
 *  DESTROY SEQUENCE CANNOT BE ABORTED HOWEVER, this decision is up to
 *  the user.  All this does is indicate that there is a "problem" with
 *  allowing the destroy.  The device which returns carry should call
 *  the SHELL_Message service to post an informational dialog about the
 *  reason for the problem.
 */
#define QUERY_DESTROY		0x0013		/* OK to destroy running VM? */


/* ----------------------- DEBUGGING CONTROL CALL -------------------------- */

/*
 *  Special call for device specific DEBUG information display and activity.
 */
#define DEBUG_QUERY		0x0014


/* -------- CALLS FOR BEGIN/END OF PROTECTED MODE VM EXECUTION ------------- */

/*
 *   About to run a protected mode application.
 *   EBX = Current VM handle.
 *   EDX = Flags
 *   EDI -> Application Control Block
 *   Returning with carry set fails the call.
 */
#define BEGIN_PM_APP		0x0015

/*
 *  Flags for Begin_PM_App (passed in EDX)
 */
#define BPA_32_BIT		0x01
#define BPA_32_BIT_FLAG 	1

/*
 *  Protected mode application is terminating.
 *  EBX = Current VM handle.  THIS CALL CAN NOT FAIL.
 *  EDI -> Application Control Block
 */
#define END_PM_APP		0x0016

/*
 *  Called whenever system is about to be rebooted.  Allows VxDs to clean
 *  up in preperation for reboot.
 */
#define DEVICE_REBOOT_NOTIFY	0x0017
#define CRIT_REBOOT_NOTIFY	0x0018

/*
 *  Called when VM is about to be terminated using the Close_VM service
 *	EBX = Current VM handle (Handle of VM to close)
 *	EDX = Flags
 *	      CVNF_CRIT_CLOSE = 1 if VM is in critical section while closing
 */
#define CLOSE_VM_NOTIFY 	0x0019

#define CVNF_CRIT_CLOSE_BIT	0
#define CVNF_CRIT_CLOSE 	(1 << CVNF_CRIT_CLOSE_BIT)

/*
 *  Power management event notification.
 *  EBX = 0
 *  ESI = event notification message
 *  EDI -> DWORD return value; VxD's modify the DWORD to return info, not EDI
 *  EDX is reserved
 */
#define POWER_EVENT		0x001A

#define SYS_DYNAMIC_DEVICE_INIT 0x001B
#define SYS_DYNAMIC_DEVICE_EXIT 0x001C

/*
 *  Create_THREAD creates a new thread.  EDI = handle of new thread.
 *  Returning Carry will fail the Create_THREAD. Message is sent in the
 *  context of the creating thread.
 *
 */
#define  CREATE_THREAD	0x001D

/*
 *  Second phase of creating a thread.  EDI = handle of new thread.  Call cannot
 *  be failed. VM Simulate_Int, Exec_Int activity is not allowed (because
 *  never allowed in non-initial threads). Message is sent in the context
 *  of the newly created thread.
 *
 */
#define  THREAD_INIT	0x001E

/*
 *  Normal (first) phase of Destroy_THREAD. EDI = handle of thread.
 *  This occurs on normal termination of the thread.  Call cannot be failed.
 *  Simulate_Int, Exec_Int activity is allowed.
 */
#define  TERMINATE_THREAD  0x001F

/*
 *  Second phase of Destroy_THREAD.  EDI = Handle of thread,
 *  EDX = flags (see below).  Note that in the case of destroying a
 *  running thread, this is the first call made (THREAD_Terminate call
 *  does not occur).  Call cannot be failed.  VM Simulate_Int, Exec_Int
 *  activity is NOT allowed.
 *
 */
#define  THREAD_Not_Executeable  0x0020

/*
 *  Final phase of Destroy_THREAD.  EDI = Thread Handle.  Note that considerable
 *  time can elapse between the THREAD_Not_Executeable call and this call.
 *  Call cannot be failed.  VM Simulate_Int, Exec_Int activity is NOT
 *  allowed.
 *
 */
#define  DESTROY_THREAD    0x0021


//#define WM_USER 0x400
#define ID_CUSTOM WM_USER+0x7001

class linkstr;

class C16bitView : public CScrollView
{
private: long m_cbaddress;
         linkstr *lpStrings;
         CSize m_Sizes;

protected: // create from serialization only
	C16bitView();
	DECLARE_DYNCREATE(C16bitView)

// Attributes
public:
	C16bitDoc* GetDocument();

// Operations
public:

// Implementation
public:
	virtual ~C16bitView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnPrepareDC(CDC *pDC, CPrintInfo *pInfo);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(C16bitView)
	afx_msg LONG OnReceiveRegisterNotify(UINT,LONG);
	afx_msg void OnVxdLoaddiagnosticvxd();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnVxdUnloaddiagnosticvxd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 16bitvw.cpp
inline C16bitDoc* C16bitView::GetDocument()
   { return (C16bitDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
