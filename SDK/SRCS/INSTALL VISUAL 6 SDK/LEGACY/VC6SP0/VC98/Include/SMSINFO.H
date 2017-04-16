// **************************************************************************
//
//  File: SMSINFO.H
//
//  Copyright (c) 1995 Microsoft Corp.
//
//  This is an auxiliary header file for the SMS API.
//  It contains manifests used in scalars and filters.
//
//
// **************************************************************************


#ifndef _SMSINFO_H_
#define _SMSINFO_H_


// ==========================================================================
//
//  Package folders.
//
// ==========================================================================

//
//  These defines are used in Share and Workstation permissions scalars.
//  These scalars must be a combination of any (or none) of these defines.
//
#define PACKAGE_USER_READ           0x00000001
#define PACKAGE_USER_WRITE          0x00000002
#define PACKAGE_GUEST_READ          0x00000004
#define PACKAGE_GUEST_WRITE         0x00000008


//
//  Values for scalar: 'Platforms'
//  ----------------------------------------------
// Both the Workstation Command Line folder and the Program Item folders
// have a 'Platforms' scalar. The values are identical.
//
#define PLTFRM_WIN16                0x00000001
#define PLTFRM_WIN32_X86            0x00000002
#define PLTFRM_WIN32_MIPS           0x00000004
#define PLTFRM_WIN32_ALPHA          0x00000008
#define PLTFRM_DOS5                 0x00000010
#define PLTFRM_DOS6                 0x00000020
#define PLTFRM_MACINTOSH            0x00000040
#define PLTFRM_WIN95                0x00000080
#define PLTFRM_MSDOS                PLTFRM_DOS5|PLTFRM_DOS6




// ==========================================================================
//
//  Program Item folders.
//
// ==========================================================================

//
//  Values for scalar: 'Drive mode'.
//  ----------------------------------------------
// This scalar corresponds directly to the 'Drive Mode' group of radio
// buttons in the 'Program Item Properties' dialogue (share package
// job only). One of these must be selected.
//
#define PI_DRIVEMODE_UNC                1
#define PI_DRIVEMODE_ANY_LETTER         2
#define PI_DRIVEMODE_SPECIFIC_LETTER    3



// ==========================================================================
//
//  Workstation Command Line (WCL) folders.
//
// ==========================================================================


//
//  Scalar: Flags
//  ----------------------------------------------
// This scalar covers the 'Automated Command Line' and
// 'System (Background) Task' check boxes in the Command Line
// Properties dialogue.
// Note that setting the flags to BACKGROUND_TASK also sets the
// AUTOMATED_COMMAND_LINE bit.
//
#define WCL_AUTOMATED_COMMAND_LINE  0x01
#define WCL_BACKGROUND_TASK         0x03



// ==========================================================================
//
//  Job folders.
//
//  General values that are common to all types of job folders
//  ----------------------------------------------------------
//
// ==========================================================================



// ==========================================================================
//
//      Job types as strings.
//
// ==========================================================================

#define STR_JOBTYPE_INSTALL         "Install"
#define STR_JOBTYPE_SERVER          "Server"
#define STR_JOBTYPE_RMPKG           "Remove package"
#define STR_JOBTYPE_SYSTEM          "System"
#define STR_JOBTYPE_MINIJOB         "Minijob"


// ==========================================================================
//
//      Job stati as strings.
//
// ==========================================================================

#define STR_JOB_PENDING             "Pending"
#define STR_JOB_ACTIVE              "Active"
#define STR_JOB_CANCELLED           "Cancelled"
#define STR_JOB_COMPLETE            "Complete"
#define STR_JOB_FAILED              "Failed"
#define STR_JOB_ACTIVE_FAILED       "Active failed"
#define STR_JOB_ACTIVE_UNKNOWN      "Unknown"


//
//  Values for scalar: 'Limit to sites'
//  ----------------------------------------------
// This can be either JOBTGT_SITE or JOBTGT_SITEGROUP. If either of
// these are set then the scalar 'Include subsites' can be set.
// If neither site nor sitegroup limiting is required then this scalar
// should be set to JOBTGT_NOSITELIMIT (default).
//
#define JOBTGT_NOSITELIMIT          0
#define JOBTGT_SITEGROUP            1
#define JOBTGT_SITE                 2


//
//  Values for scalar: 'Include subsites'
//  ----------------------------------------------
// This can be set to either 1 or 0. If the 'Limit to sites'
// scalar is not set then this scalar will be ignored.
//
#define JOBTGT_NOSUBSITES           0
#define JOBTGT_INCLUDESUBSITES      1


//
//  Values for scalar: 'Job status'
//  ----------------------------------------------
// This scalar corresponds to the 'Overall Status' display in
// in the 'Job Status' dialogue. It is a read-only scalar, the values
// are presented here for clarity.
//
#define JOBSTAT_PENDING             1
#define JOBSTAT_ACTIVE              2
#define JOBSTAT_CANCELLED           3
#define JOBSTAT_COMPLETE            4
#define JOBSTAT_FAILED              5
#define JOBSTAT_RETRYING            6


//
//  Values for scalar: 'Priority'
//  ----------------------------------------------
// This scalar corresponds to the 'Priority' edit control in the
// 'Job Schedule' dialogue box.
//
#define JOBPRI_HIGH                 1
#define JOBPRI_MEDIUM               2
#define JOBPRI_LOW                  3

//
//  Values for scalar: 'Repeat mode'
//  ----------------------------------------------
// This scalar corresponds to the 'Repeat' edit control in the
// 'Job Schedule' dialogue box.
//
#define JOBRPT_NEVER                1
#define JOBRPT_DAILY                2
#define JOBRPT_WEEKLY               3
#define JOBRPT_BIWEEKLY             4
#define JOBRPT_MONTHLY              5


//
//  Values for scalar: 'Cancel mode'
//  ----------------------------------------------
// This scalar has no direct equivalent in any dialogue box. It corresponds
// instead to the 'Cancel Job' menu selection in the Edit menu when the
// focus is on the Jobs window.
//
#define JOBCANCEL_DONT_CANCEL       0
#define JOBCANCEL_CANCEL            1

// ==========================================================================
//
//  Job folders: Remove package job.
//  --------------------------------
//
// ==========================================================================

//
//  Scalar: Package type
//  ----------------------------------------------
//  This scalar is either workstation, server, or both as below.
//
#define RMPKGJOB_PKGTYPE_WKSTA      0x01
#define RMPKGJOB_PKGTYPE_SERVER     0x02
#define RMPKGJOB_PKGTYPE_BOTH       (RMPKGJOB_PKGTYPE_WKSTA | RMPKGJOB_PKGTYPE_SERVER)

//
//  Scalar: Job tasks
//  ----------------------------------------------
//
#define RMPKGJOB_TASKS_RM_ALL       1
#define RMPKGJOB_TASKS_RM_SELECTED  2

//  Setting 'Job tasks' to RMPKGJOB_TASKS_RM_SELECTED means that the user
//  must set the 'Site group' scalar to a valid name.


//  Setting the 'Job target' scalar to JOBTGT_SITEGROUP means that the user
//  must provide, in the 'Site limit name' scalar, a name of a machine group.
//  The JOBTGT_INCLUDESUBSITES flag is only valid if JOBTGT_SITEGROUP has also
//  been specified.



// ==========================================================================
//
//  Job folders: Run command on workstation job.
//  --------------------------------------------
//
// ==========================================================================

//
//  Scalar: Job target
//  ----------------------------------------------
// Select from one of the following values. These correspond directly
// to the radio buttons in the 'Job Target' group in the Job Details
// dialogue for a run command on workstation job.
//
#define WKSTAJOB_TGT_QUERY          1
#define WKSTAJOB_TGT_MACHGROUP      2
#define WKSTAJOB_TGT_MACHPATH       3

//
//  Scalar: Distribute phase
//  ----------------------------------------------
// This scalar corresponds to the 'Distribute Phase' group.
// The value can be either, both, or neither of the following values,
// ie 0, 1, 2, or 3.
//
#define WKSTAJOB_DIST_EXISTING      0x01
#define WKSTAJOB_DIST_SPECIFIED     0x02

//
//  Scalar: Send phase
//  ----------------------------------------------
// These values correspond to the 'Only if not previously sent' and
// 'Even if previously sent' radio buttons in the SMS Admin for the
// send phase group for a Run Command on Workstation job.
//
#define WKSTAJOB_SEND_IF_NOT_SENT   1
#define WKSTAJOB_SEND_ALWAYS        2



// ==========================================================================
//
//  Job folders: Share package job.
//  -------------------------------
//
// ==========================================================================


//
//  Scalar: Send phase
//  ----------------------------------------------
// These values correspond to the 'Only if not previously sent' and
// 'Even if previously sent' radio buttons in the SMS Admin for the
// send phase group for a Share package job.
//
#define SHAREJOB_SEND_IF_NOT_SENT   1
#define SHAREJOB_SEND_ALWAYS        2


//
//  Scalar: Distribute phase
//  ----------------------------------------------
// This scalar corresponds to the 'Distribute Phase' group.
// The value can be either, both, or neither of the following values,
// ie 0, 1, 2, or 3.
//
#define SHAREJOB_DIST_EXISTING      0x01
#define SHAREJOB_DIST_SPECIFIED     0x02





#endif  // _SMSINFO_H_

/* EOF: smsinfo.h */

