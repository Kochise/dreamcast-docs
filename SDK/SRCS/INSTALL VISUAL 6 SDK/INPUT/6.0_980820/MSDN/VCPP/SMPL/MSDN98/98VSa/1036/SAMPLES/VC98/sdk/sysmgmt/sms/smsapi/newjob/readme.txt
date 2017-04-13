
Sample: newjob
==============

This sample illustrates the use of the SMS APIs in order to view,
create, and delete job folders.
There are four types of job folders:
        Run command on Workstation job
        Share package on Server job
        Remove package from Server job
        System job
All of these except system jobs can be created and deleted.


After logging on to a datasource, a job container is opened and populated.
No filtering is done since we want to see all the jobs that exist in the
system.
The program then enters a loop asking whether the user wants to view the
next job folder, delete the currently viewed folder, or create a new folder.

Both deletion and creation are two-stage processes. Only when the
SmsCommitFolder API is called will the folder be either deleted from or
inserted into the datasource.

Folder creation is handled in the CreateNewFolder function.
This creates an empty folder in the context of the parent which in this
case is the job container. The function then retrieves a description of
the folder via the SmsDescribeFolder API. This returns a FOLDER_INFO
structure which describes the folder in terms of its capabilities, see
the objectty.h header file (or the help file) for a full description of
this structure.

Included in FOLDER_INFO is a pointer to an array of SCALAR_INFO structures.
Each SCALAR_INFO describes one of the folder's scalars. The information
contained here is:
        the scalar's name,
        its type,
        its access mode.
CreateNewFolder loops through this array, for each scalar that has modify or
create access, it displays the name and asks the user to fill in the value.
Only nominal checking is done on the values, a real application would have
to go into much greater detail since job creation is a non-trivial task.
If there are any errors in the date/time fields they are set to the current
date and time.

This is a sample of a created workstation install job:


JS200009 (Workstation install job) contains 33 scalars
                           Job ID: JS200009
                         Job type: microsoft\SMS\workstation_script
                      Job comment: a descriptive comment
                    Activate time: Thu Jun 22 15:12:00 1995
                        Left icon: Package
                      Center icon: Machinegroup
                       Right icon: Site
                         Priority: 1
                      Repeat mode: 1
                      Cancel mode: 0
                       Job status: 1
                   Sending status: 1
                   Working status: 1
                    Cancel status: 1
                       Package ID: JS200049
                       Job target: 2
                 Distribute phase: 1
                       Send phase: 1
                   Limit to sites: 2
                 Include subsites: 1
                  Site limit name: jonshu2site
             Distribution servers: me
                         WCL name: Audit software
                         Query ID:
               Machine group name: My machine group
                     Machine path: *|*|*
                       Offer time: Thu Jun 22 15:15:00 1995
                   Mandatory time: Thu Jun 22 15:15:00 1995
               Use mandatory time: 0
             Force over slow link: 0
                      Expire time: Thu Jun 22 15:15:00 1995
                  Use expire time: 0
          Run workstation command: 1
============== JS200009 ===========

