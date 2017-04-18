Option Explicit
'// **************************************************************************
'//
'//  File: SMSINFO.H
'//
'//  Copyright (c) 1995 Microsoft Corp.
'//
'//  This is an auxiliary header file for the SMS API.
'//  It contains manifests used in scalars and filters.
'//
'//  GFF@SEA          17-Mar-95   VBified.
'//
'// **************************************************************************
'
'#ifndef _SMSINFO_H_
'#define _SMSINFO_H_
'
'
'// ==========================================================================
'//
'//  Package folders.
'//
'// ==========================================================================
'
'//
'//  These defines are used in Share and Workstation permissions scalars.
'//  These scalars must be a combination of any (or none) of these defines.
'//
 Global Const PACKAGE_USER_READ = &H1&
 Global Const PACKAGE_USER_WRITE = &H2&
 Global Const PACKAGE_GUEST_READ = &H4&
 Global Const PACKAGE_GUEST_WRITE = &H8&
'
'
'//
'//  Values for scalar: 'Platforms'
'//  ----------------------------------------------
'// Both the Workstation Command Line folder and the Program Item folders
'// have a 'Platforms' scalar. The values are identical.
'// NOTE: This list may be periodically updated by Microsoft when new
'// versions of SMS are released.
'//
 Global Const PLTFRM_WIN16 = &H1&
 Global Const PLTFRM_WIN32_X86 = &H2&
 Global Const PLTFRM_WIN32_MIPS = &H4&
 Global Const PLTFRM_WIN32_ALPHA = &H8&
 Global Const PLTFRM_DOS5 = &H10&
 Global Const PLTFRM_DOS6 = &H20&
 Global Const PLTFRM_MACINTOSH = &H40&
 Global Const PLTFRM_WIN95 = &H80&
 Global Const PLTFRM_MSDOS = PLTFRM_DOS5 + PLTFRM_DOS6
'
'
'// ========================================================================
'// This is a list of the platforms that are supported for PDF files
'// in SMS 1.2. This list is for reference.
'//      "Macintosh"
'//      "MS-DOS 5.0"
'//      "MS-DOS 6.0"
'//      "MS-DOS 6.2"
'//      "MS-DOS 6.21"
'//      "MS-DOS 6.22"
'//      "Windows 3.1"
'//      "Windows NT 3.1 (Alpha)"
'//      "Windows NT 3.1 (MIPS)"
'//      "Windows NT 3.1 (x86)"
'//      "Windows NT 3.5 (Alpha)"
'//      "Windows NT 3.5 (MIPS)"
'//      "Windows NT 3.5 (x86)"
'//      "Windows NT 3.51 (Alpha)"
'//      "Windows NT 3.51 (MIPS)"
'//      "Windows NT 3.51 (x86)"
'//      "Windows NT 4.0 (Alpha)"
'//      "Windows NT 4.0 (MIPS)"
'//      "Windows NT 4.0 (x86)"
'//      "Windows95"
'// ========================================================================
'
'
'
'
'// ==========================================================================
'//
'//  Program Item folders.
'//
'// ==========================================================================
'
'//
'//  Values for scalar: 'Drive mode'.
'//  ----------------------------------------------
'// This scalar corresponds directly to the 'Drive Mode' group of radio
'// buttons in the 'Program Item Properties' dialogue (share package
'// job only). One of these must be selected.
'//
 Global Const PI_DRIVEMODE_UNC = 1
 Global Const PI_DRIVEMODE_ANY_LETTER = 2
 Global Const PI_DRIVEMODE_SPECIFIC_LETTER = 3
'
'
'
'// ==========================================================================
'//
'//  Workstation Command Line (WCL) Job folder.
'//  ------------------------------------------
'//
'// ==========================================================================
'
'
'//
'//  Scalar: Flags
'//  ----------------------------------------------
'// This scalar covers the 'Automated Command Line' and
'// 'System (Background) Task' check boxes in the Command Line
'// Properties dialogue.
'// Note that setting the flags to BACKGROUND_TASK also sets the
'// AUTOMATED_COMMAND_LINE bit.
'//
 Global Const WCL_AUTOMATED_COMMAND_LINE = &H1
 Global Const WCL_BACKGROUND_TASK = &H3
'
'
'
'// ==========================================================================
'//
'//  Job folders.
'//
'//  General values that are common to all types of job folders
'//  ----------------------------------------------------------
'//
'// ==========================================================================
'
'
'// ==========================================================================
'//
'//      Job types as strings.
'//
'// ==========================================================================
'
 Global Const STR_JOBTYPE_INSTALL = "Install"
 Global Const STR_JOBTYPE_SERVER = "Server"
 Global Const STR_JOBTYPE_RMPKG = "Remove package"
 Global Const STR_JOBTYPE_SYSTEM = "System"
 Global Const STR_JOBTYPE_MINIJOB = "Minijob"
'
'
'// ==========================================================================
'//
'//      Job stati as strings.
'//
'// ==========================================================================
'
 Global Const STR_JOB_PENDING = "Pending"
 Global Const STR_JOB_ACTIVE = "Active"
 Global Const STR_JOB_CANCELLED = "Cancelled"
 Global Const STR_JOB_COMPLETE = "Complete"
 Global Const STR_JOB_FAILED = "Failed"
 Global Const STR_JOB_ACTIVE_FAILED = "Active failed"
 Global Const STR_JOB_ACTIVE_UNKNOWN = "Unknown"
'
'
'//
'//  Values for scalar: 'Limit to sites'
'//  ----------------------------------------------
'// This can be either JOBTGT_SITE or JOBTGT_SITEGROUP. If either of
'// these are set then the scalar 'Include subsites' can be set.
'// If neither site nor sitegroup limiting is required then this scalar
'// should be set to JOBTGT_NOSITELIMIT (default).
'//
 Global Const JOBTGT_NOSITELIMIT = 0
 Global Const JOBTGT_SITEGROUP = 1
 Global Const JOBTGT_SITE = 2
'
'
'//
'//  Values for scalar: 'Include subsites'
'//  ----------------------------------------------
'// This can be set to either 1 or 0. If the 'Limit to sites'
'// scalar is not set then this scalar will be ignored.
'//
 Global Const JOBTGT_NOSUBSITES = 0
 Global Const JOBTGT_INCLUDESUBSITES = 1
'
'
'//
'//  Values for scalar: 'Job status'
'//  ----------------------------------------------
'// This scalar corresponds to the 'Overall Status' display in
'// in the 'Job Status' dialogue. It is a read-only scalar, the values
'// are presented here for clarity.
'//
 Global Const JOBSTAT_PENDING = 1
 Global Const JOBSTAT_ACTIVE = 2
 Global Const JOBSTAT_CANCELLED = 3
 Global Const JOBSTAT_COMPLETE = 4
 Global Const JOBSTAT_FAILED = 5
 Global Const JOBSTAT_RETRYING = 6
'
'
'//
'//  Values for scalar: 'Priority'
'//  ----------------------------------------------
'// This scalar corresponds to the 'Priority' edit control in the
'// 'Job Schedule' dialogue box.
'//
 Global Const JOBPRI_HIGH = 1
 Global Const JOBPRI_MEDIUM = 2
 Global Const JOBPRI_LOW = 3
'
'//
'//  Values for scalar: 'Repeat mode'
'//  ----------------------------------------------
'// This scalar corresponds to the 'Repeat' edit control in the
'// 'Job Schedule' dialogue box.
'//
 Global Const JOBRPT_NEVER = 1
 Global Const JOBRPT_DAILY = 2
 Global Const JOBRPT_WEEKLY = 3
 Global Const JOBRPT_BIWEEKLY = 4
 Global Const JOBRPT_MONTHLY = 5
'
'
'//
'//  Values for scalar: 'Cancel mode'
'//  ----------------------------------------------
'// This scalar has no direct equivalent in any dialogue box. It corresponds
'// instead to the 'Cancel Job' menu selection in the Edit menu when the
'// focus is on the Jobs window.
'//
 Global Const JOBCANCEL_DONT_CANCEL = 0
 Global Const JOBCANCEL_CANCEL = 1
'
'// ==========================================================================
'//
'//  Job folders: Remove package job.
'//  --------------------------------
'//
'// ==========================================================================
'
'//
'//  Scalar: Package type
'//  ----------------------------------------------
'//  This scalar is either workstation, server, or both as below.
'//
 Global Const RMPKGJOB_PKGTYPE_WKSTA = &H1                               '*/
 Global Const RMPKGJOB_PKGTYPE_SERVER = &H2                              '*/
 Global Const RMPKGJOB_PKGTYPE_BOTH = RMPKGJOB_PKGTYPE_WKSTA + RMPKGJOB_PKGTYPE_SERVER '*/
'
'//
'//  Scalar: Job tasks
'//  ----------------------------------------------
'//
 Global Const RMPKGJOB_TASKS_RM_ALL = 1
 Global Const RMPKGJOB_TASKS_RM_SELECTED = 2
'
'//  Setting 'Job tasks' to TASKS_RM_SELECTED means that the user
'//  must set the 'Site group' scalar to a valid name.
'
'
'//  Setting the 'Job target' scalar to TGT_SITEGROUP means that the user
'//  must provide, in the 'Site limit name' scalar, a name of a machine group.
'//  The TGT_INCLUDESUBSITES flag is only valid if TGT_SITEGROUP has also
'//  been specified.
'
'
'
'// ==========================================================================
'//
'//  Job folders: Run command on workstation job.
'//  --------------------------------------------
'//
'// ==========================================================================
'
'//
'//  Scalar: Job target
'//  ----------------------------------------------
'// Select from one of the following values. These correspond directly
'// to the radio buttons in the 'Job Target' group in the Job Details
'// dialogue for a run command on workstation job.
'//
 Global Const WKSTAJOB_TGT_QUERY = 1
 Global Const WKSTAJOB_TGT_MACHGROUP = 2
 Global Const WKSTAJOB_TGT_MACHPATH = 3
'
'//
'//  Scalar: Distribute phase
'//  ----------------------------------------------
'// This scalar corresponds to the 'Distribute Phase' group.
'// The value can be either, both, or neither of the following values,
'// ie 0, 1, 2, or 3.
'//
 Global Const WKSTAJOB_DIST_EXISTING = &H1
 Global Const WKSTAJOB_DIST_SPECIFIED = &H2
'
'//
'//  Scalar: Send phase
'//  ----------------------------------------------
'// These values correspond to the 'Only if not previously sent' and
'// 'Even if previously sent' radio buttons in the SMS Admin for the
'// send phase group for a Run Command on Workstation job.
'//
 Global Const WKSTAJOB_SEND_IF_NOT_SENT = 1
 Global Const WKSTAJOB_SEND_ALWAYS = 2
'
'
'
'// ==========================================================================
'//
'//  Job folders: Share package job.
'//  -------------------------------
'//
'// ==========================================================================
'
'
'//
'//  Scalar: Send phase
'//  ----------------------------------------------
'// These values correspond to the 'Only if not previously sent' and
'// 'Even if previously sent' radio buttons in the SMS Admin for the
'// send phase group for a Share package job.
'//
 Global Const SHAREJOB_SEND_IF_NOT_SENT = 1
 Global Const SHAREJOB_SEND_ALWAYS = 2
'
'
'//
'//  Scalar: Distribute phase
'//  ----------------------------------------------
'// This scalar corresponds to the 'Distribute Phase' group.
'// The value can be either, both, or neither of the following values,
'// ie 0, 1, 2, or 3.
'//
 Global Const SHAREJOB_DIST_EXISTING = &H1
 Global Const SHAREJOB_DIST_SPECIFIED = &H2
'
'
'
'
'
'#endif  // _SMSINFO_H_
'
'/* EOF: smsinfo.h */
