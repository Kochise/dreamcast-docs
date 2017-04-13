Readme for Java support in Active Directory
===========================================
1) Install Active Directory

2) Build dsconn.dll in the dsconn directory with a C compiler

3) Copy dsconn.dll to your system directory (on Windows NT this would be
%SystemRoot%\System32 on Windows 95 this would be Windows\System)

4) cd to the system directory per above 

5) Run regsvr32 /s dsconn.dll

6) Run javatlb dsconn.dll

7) Run javatlb activeds.tlb

8) cd to "Program files\Common files\System\ADO" and 

9) run javatlb msado10.dll

10) Build the Bizcard applet in the bizcard directory with VJ++

Starting Point for the Java Sample
==================================
To obtain data from the Directory Service, a valid LDAP path must
be provided in the 'Starting Point' field. The following is an 
example of a valid LDAP path.

LDAP://NW09T5/C=US/O=NTMARST/OU=NW09T5DOM
 