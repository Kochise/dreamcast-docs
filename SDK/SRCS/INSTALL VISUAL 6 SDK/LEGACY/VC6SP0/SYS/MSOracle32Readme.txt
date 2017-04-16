-----------------------------------
Release Notes

Microsoft(R) ODBC Driver for Oracle
-----------------------------------

(c) 1998 Microsoft Corporation
	  
------------------------
How to Use This Document
------------------------

To view the Readme file in Windows Notepad, maximize the Notepad window and click Word Wrap on the Edit menu. To print the ReadMe file, open it in Notepad or another word processor, and then use the Print command on the File menu.

For changes from earlier version of this driver, see the "What's New" section of this file.

--------
Overview
--------

The Microsoft ODBC Driver for Oracle conforms to the Open Database Connectivity (ODBC) specification described in the ODBC Programmer's Reference (Version 2.0) for your platform. The Oracle driver allows you to connect your ODBC-compliant application to an Oracle database.


-------------------
System Requirements
-------------------

To use the Microsoft ODBC Driver for Oracle, you must have Oracle Client Software, version 7.3 or higher, installed on your Windows system. The Microsoft Oracle ODBC Driver supports only SQL*Net 2.3 or later. For more information on Oracle products, refer to your Oracle documentation set.

----------
What’s New
----------

This version of the Microsoft ODBC Driver for Oracle includes several improvements to performance and stability. You should find that the driver has greater functionality and speed due to the following additions:

   · Improved configuration control through additions to the ODBC Data Source Administrator, 
     including Translation, Performance, and Customization options.

   · Extended Help file.

This version also includes the features of the previous version, including:

   · Improved Extended Fetch with support for row-wise binding. 
	See "Level 2 Functions" in Help.
	For specific details, see the Microsoft ODBC 3.0 Programmer’s References and SDK Guide. 
   · Integration with Microsoft® Transaction Server for distributed transactions.
	See "Using Microsoft Transaction Server" in Help.
   · Support for Oracle Packaged Procedure syntax in catalog functions. 
	See "Returning Array Parameters from Stored Procedures" in Help.
   · Implementation of SQLDescribeParam to provide more accuracy in parameter descriptions for SQL statements. 
	See "Level 2 Functions" in Help.
   · Ability to return arrays from Stored Procedures. 
	See "Returning Array Parameters from Stored Procedures" in Help.
   · Support for Bookmarks. 
	See "Level 2 Functions" and "Statement Options Table" in Help.
   · Extended Help file.

This version of the Microsoft ODBC Driver for Oracle has greater stability through testing against more environments like Microsoft Transaction Server and Internet Information Server.
