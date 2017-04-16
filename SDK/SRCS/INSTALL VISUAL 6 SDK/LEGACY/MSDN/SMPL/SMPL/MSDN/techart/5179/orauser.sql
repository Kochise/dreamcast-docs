/*************************************************************************
	Oracle 7 Database - Account Creation Script
	Tablespace - USER_DATA
	
	The following script creates the Oracle user accounts and database
	roles required for the sample Oracle program.

	NOTE:	These sample scripts assume that the USER_DATA and
		TEMPORARY_DATA tablespaces exist.  They are created during
		a default Oracle 7 database installation.  If these tablespaces
		do not exist, you must either add them or modify these scripts
		to use other tablespaces.
*************************************************************************/

/*************************************************************************
	Log on the Oracle 7 database as the SYSTEM account (if your password
	has been changed from MANAGER (default), change it here
	The name WILBUR is the name for the SQL*Net V2 connection string
	found in the tnsnames.ora file.
*************************************************************************/
CONNECT SYSTEM/MANAGER@WILBUR

/*************************************************************************
	CREATE DATA_ADMIN (ADMINISTRATIVE) ROLE, ASSIGN PRIVILEGES
*************************************************************************/
DROP ROLE DATA_ADMIN
/

CREATE ROLE DATA_ADMIN
/

GRANT CREATE CLUSTER, CREATE PROCEDURE, CREATE PUBLIC SYNONYM,
CREATE ROLE, CREATE SEQUENCE, CREATE SNAPSHOT, CREATE SYNONYM,
CREATE TABLE, CREATE TRIGGER, CREATE VIEW, DROP PUBLIC SYNONYM
TO DATA_ADMIN
/

/*************************************************************************
	CREATE USER_LOGON (QUERY) ROLE, ASSIGN PRIVILEGES
*************************************************************************/
DROP ROLE USER_LOGON
/

CREATE ROLE USER_LOGON
/

GRANT CREATE SESSION, ALTER SESSION TO USER_LOGON
/

/*************************************************************************
	CREATE ADMINISTRATIVE ACCOUNT FOR STUDENT AND GRADE TABLES
*************************************************************************/
DROP USER STUDENT_ADMIN CASCADE
/

CREATE USER STUDENT_ADMIN IDENTIFIED BY STUDENT_ADMIN
DEFAULT TABLESPACE USER_DATA
TEMPORARY TABLESPACE TEMPORARY_DATA
QUOTA UNLIMITED ON USER_DATA
/

/*************************************************************************
	CREATE ADMINISTRATIVE ACCOUNT FOR DEPT AND CLASS TABLES
*************************************************************************/
DROP USER DEPT_ADMIN CASCADE
/

CREATE USER DEPT_ADMIN IDENTIFIED BY DEPT_ADMIN
DEFAULT TABLESPACE USER_DATA
TEMPORARY TABLESPACE TEMPORARY_DATA
QUOTA UNLIMITED ON USER_DATA
/

/*************************************************************************
	CREATE USER ACCOUNT TO QUERY TABLES
*************************************************************************/
DROP USER ENDUSER1 CASCADE
/

CREATE USER ENDUSER1 IDENTIFIED BY ENDUSER1
DEFAULT TABLESPACE USER_DATA
TEMPORARY TABLESPACE TEMPORARY_DATA
QUOTA UNLIMITED ON USER_DATA
/

/*************************************************************************
	GRANT ROLES TO ORACLE ACCOUNTS
*************************************************************************/
GRANT DATA_ADMIN TO STUDENT_ADMIN, DEPT_ADMIN
/

GRANT USER_LOGON TO STUDENT_ADMIN, DEPT_ADMIN, ENDUSER1
/

/*************************************************************************
	SET DEFAULT ROLES FOR EACH ORACLE ACCOUNT
*************************************************************************/
ALTER USER STUDENT_ADMIN
DEFAULT ROLE DATA_ADMIN, USER_LOGON
/

ALTER USER DEPT_ADMIN
DEFAULT ROLE DATA_ADMIN, USER_LOGON
/

ALTER USER ENDUSER1
DEFAULT ROLE USER_LOGON
/