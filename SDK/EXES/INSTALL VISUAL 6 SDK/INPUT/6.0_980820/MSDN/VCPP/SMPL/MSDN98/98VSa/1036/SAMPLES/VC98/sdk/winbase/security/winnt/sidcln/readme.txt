Security Functions


SUMMARY
=======

The SIDCLN sample demonstrates some of the security functions. It
provides a sample utility that recovers on-disk resources that remain 
allocated to deleted user accounts.

MORE INFORMATION
================

The on-disk resources recovered are:

 - Files that are still owned by accounts that have been deleted are
   assigned ownership to the account logged on when this sample is run.

 - ACEs for deleted accounts are deleted from the ACLs of files to which
   the deleted accounts had been granted authorizations (such as Read
   access).

It may be that running this sample as a utility has no practical value in 
many environments, as the number of files belonging to deleted user accounts 
will often be quite small and the number of bytes recovered on disk by 
editing out ACEs for deleted accounts may not be worth the time it takes to 
run this sample. This time can be significant when processing an entire hard 
disk or partition.

Note: This sample is not a supported utility.

Usage
-----

You must log on using an account that has the privilege to take file
ownership and edit ACLs, such as Administrator.

The ACL editing part of this sample can only be exercised for files on an 
NTFS partition.

Typical test scenario
---------------------

Create a user account or two and log on as each of these accounts in turn. 
While logged on for each account, go to an NTFS partition and create a 
couple of files so the test accounts each own a few files. Use the File 
Manager or Windows Explorer to edit permissions for those files, so that 
each test user has some authorities (such as Read) explicitly granted for 
those files. Log on as Administrator and authorize each test user to a few 
Administrator-owned files. Delete the test accounts. Run the sample in the 
directories where you put the files that the test accounts own.
