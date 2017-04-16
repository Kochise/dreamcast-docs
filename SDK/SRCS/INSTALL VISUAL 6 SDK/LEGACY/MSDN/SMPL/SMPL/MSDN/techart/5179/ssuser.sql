/*************************************************************************
	SQL Server Database - Account Creation Script
	Database:	MASTER
			USER_DB
	The following script creates the SQL Server user accounts and database
	groups required for the sample SQL Server program.

	NOTE:	You must create a database (named USER_DB) in order for these
		Scripts and the sample SQL Server program to work.  It can be
		Easily created using the SQL Server Enterprise Manager tool.
*************************************************************************/

/*************************************************************************
	YOU MUST BE LOGGED ON AS 'SA' TO RUN THIS SCRIPT
*************************************************************************/

/*************************************************************************
	USING THE MASTER DATABASE
*************************************************************************/
USE MASTER
GO

/*************************************************************************
	CREATE SQL SERVER LOGIN ACCOUNTS
*************************************************************************/
SP_ADDLOGIN STUDENT_ADMIN, STUDENT_ADMIN, USER_DB
GO

SP_ADDLOGIN DEPT_ADMIN, DEPT_ADMIN, USER_DB
GO

SP_ADDLOGIN ENDUSER1, ENDUSER1, USER_DB
GO

/*************************************************************************
	USING THE USER_DB DATABASE
*************************************************************************/
USE USER_DB
GO

/*************************************************************************
	ADD GROUPS AND ADD USER ACCOUNTS
*************************************************************************/
SP_ADDGROUP DATA_ADMIN
GO

SP_ADDGROUP USER_LOGON
GO

SP_ADDUSER ENDUSER1, ENDUSER1, USER_LOGON
GO

SP_ADDUSER DEPT_ADMIN, DEPT_ADMIN, DATA_ADMIN
GO

SP_ADDUSER STUDENT_ADMIN, STUDENT_ADMIN, DATA_ADMIN
GO
