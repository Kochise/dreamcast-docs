Check Security Descriptors (SD)


In the Win32 Programmer's Reference, if you go to the Security overview, then
choose the sub-topic "Allowing Access", you'll find the comment

   Note: It is fine to write code like this that builds security
   descriptors from scratch. It is, however, a good practice
   for people who write code that builds or manipulates
   security descriptors to first write code that explores the
   default security descriptors that Windows NT places on
   objects. For example, if Windows NT by default includes in
   a DACL an ACE granting the Local Logon SID certain access,
   it's good to know that, so that a decision not to grant any
   access to the Local Logon SID would be a conscious decision

This comment is accurate, however, to begin with, this task of examining the
SD is easier if there is sample code to start from. The purpose of the CHECK_SD
sample is to provide sample code you can start from as you examine an SD.
This sample only examines the SD on files, but the code can be modified to
examine the SD on other objects.

This sample is not a supported utility

To run
------

Type Check_sd to check the SD on the \\.\A: device

   Type Check_sd d:\a.fil to check the SD on the d:\a.fil
      file.  In this case d: must be formatted NTFS,
      because only NTFS files have SD(s)

Further notes
-------------

If you recompile with this define statement included:

  #define I_DO_NOT_WANT_THIS_CODE_TO_CLUTTER_THIS_PROGRAM_S_OUTPUT (1==0)

and re-run the program, the program will display more output, including
all the information you can access from the process Access Token, and the
SD's of some sample objects.

If you logon, run with the program built to produce the extra output as
mentioned, save that output to a file, log off and re-run the program,
and save the output of this second run to a different file, then you use
WinDiff to observe how the local logon SID changes values for each session.

Here is a sample test you could run to exercise DACLs involves using the
SD_FLPPY sample in conjunction with the CHECK_SD sample:

 - Log on to a machine as a local Administrator
 - Do
      check_sd \\.\A: >out_bef.a
      check_sd \\.\B: >out_bef.b
 - Logoff
 - Log on the same machine as Guest on the local machine domain
 - Do
      sd_flppy
 - Try
      dir a:    (observe access denied)
      dir b:    (observe access denied)
      copy config.sys a:\   (get device not found)
      copy config.sys b:\   (get device not found)
 - Logoff
 - Log on the same machine as a local Administrator
 - Do
      check_sd \\.\A: >out_aft.a
      check_sd \\.\B: >out_aft.b
 - Browse the differences between out_bef.* and out_aft.*

This test demonstrates that the ACLs that SD_FLPPY applies survive logoff.
To demonstrate that the DACLs do not survive logoff, simply reboot, log back
on as a local Administrator, and run the commands:

   check_sd \\.\A: >out_rbt.a
   check_sd \\.\B: >out_rbt.b

to see the DACLs are again as they were.
