FWATCH demonstrates the usage of the ReadDirectoryChangesW API.

The FWATCH sample will display changes to watched directories and files in
the command window. The directories and files to be watched are specified
in the FWATCH.INI file which can be left in the application directory. 

FWATCH.INI is set by default to look at 3 directories:
c:\dir1
c:\dir2
c:\dir3

and three files in each of these directories:
file1.txt
file2.txt
file3.txt

Once FWATCH.EXE is started, open any of the above text files with NOTEPAD, make 
some changes to the file, and then save it. You should see a notification in the 
FWATCH console window immediately. You will be advised of exactly which file 
changed, what the new (current) size is, and when the last write occured.

To exit the application, type "q".

FWATCH creates the directories and files mentioned above. Use File Manager or 
a similiar utility to remove the directories/files after using FWATCH.

FWATCH will work only on Windows NT version 3.51 SP3 or greater.
