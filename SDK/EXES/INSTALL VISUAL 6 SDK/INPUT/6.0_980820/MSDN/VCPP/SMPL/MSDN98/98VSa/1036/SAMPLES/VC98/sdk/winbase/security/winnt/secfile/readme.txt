File Security


The SECFILE sample demonstrates the following security-related activities:

 - Constructing well-known security identifiers (SIDs)
 - Obtaining the current user's SID
 - Building a discretionary access control list (DACL)
 - Building a security descriptor (SD)

You should use this sample in conjunction with the Win32 Programmer's Reference.
Looking at the documentation and an example function call should make both 
the documentation and the sample clearer.

This sample only works on an NTFS partition. No other file system supports 
security. You can use File Manager or the Windows Explorer to check the 
security on the file after you run the sample. One thing you may notice is 
that the user "Everyone" has "Special" access instead of "Read" access. 
That's because the system considers "Read" access to include both read and 
execute rights. To modify the sample to give "Everyone" "Read" access, 
change the statement:

    #define WORLD_ACCESS  GENERIC_READ

to the following:

    #define WORLD_ACCESS  (GENERIC_READ | GENERIC_EXECUTE)
