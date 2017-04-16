/***************************************************************************************
	Include file section
***************************************************************************************/
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <sql.h>
#include <sqlext.h>
#include <odbcinst.h>

/***************************************************************************************
	ODBC Environmental variables
***************************************************************************************/
HENV henv1;
HDBC hdbc1;
HSTMT hstmt1;
RETCODE rc1;

/***************************************************************************************
	Program function declarations
***************************************************************************************/
void logon(void);					// database logon function
void logoff(void);					// database logoff function
void menu_screen(void);				// menu screen display function
void logon_screen(void);			// menu screen for logging on to program
void error_dump(void);				// fatal ODBC sql error handler function
void warning_dump(void);			// non-fatal ODBC sql error handler function
void list_students(void);			// Student listing function
void list_enrollments(void);		// Student Enrollment listing function
void list_classes(void);			// Class listing function
void list_departments(void);		// Department listing function
void list_gpa(void);				// Student Grade Point Average listing function
void list_student_by_class(void);	// Listing of Students in Each Class
void reluctant_students(void);		// Listing of students not enrolled in any classes
void enroll_in_entry_classes(void);	// Function used to enroll student in entry level classes
void needed_classes(void);			// Listing of classes needed to graduate
void empty_classes(void);			// Listing of empty classes
void insert_student(void);			// Function used to insert a new student
void delete_student(void);			// Function used to delete student from database
void enroll_in_class(void);			// Function used to enroll student in a class
void remove_from_class(void);		// Function used to remove a student from a class
void delete_dept(void);				// Function used to delete a department
void insert_dept(void);				// Function used to insert a new department
void delete_class(void);			// Function used to delete a class
void insert_class(void);			// Function used to insert a new class
void rowcount_and_commit(void);		// Function used to check rowcount and commit
void select_database(void);			// Function used to select SQL Server database

/***************************************************************************************
	student row structure for output operations (student_db.dbo.student)
***************************************************************************************/
typedef struct {
	char ssn[10];				// student_db.dbo.student.ssn
	char lname[21];				// student_db.dbo.student.lname
	char fname[13];				// student_db.dbo.student.fname
	char name[33];				// concatenated fname and lname (including seperator space)
	char gender[8];				// student_db.dbo.student.gender (using case function to define female or male)
	char major[5];				// student_db.dbo.student.major
	char birth_date[31];		// student_db.dbo.student.birth_date (allowing for format conversions)
	float tuition_paid;			// student_db.dbo.student.tuition_paid
	float tuition_total;		// student_db.dbo.student.tuition_total
	char start_date[31];		// student_db.dbo.student.start_date (allowing for format conversions)
	char grad_date[31];			// student_db.dbo.student.grad_date (allowing for format conversions)
	float loan_amount;			// student_db.dbo.student.loan_amount
	char degree_program[15];	// student_db.dbo.student.degree_program (using case function to redefine degree program)
	float gpa;					// calculated using case function (using student_db.dbo.grade)
	float amount_owed;			// calculated (tuition_total - tuition_paid)
	float age_at_graduation;	// calculated (using birth_date and grad_date)
	SQLINTEGER cbssn;			// output length for ssn
	SQLINTEGER cblname;			// output length for lname
	SQLINTEGER cbfname;			// output length for fname
	SQLINTEGER cbname;			// output length for name
	SQLINTEGER cbgender;		// output length for gender
	SQLINTEGER cbmajor;			// output length for major
	SQLINTEGER cbbirth_date;	// output length for birth_date
	SQLINTEGER cbtuition_paid;	// output length for tuition_paid
	SQLINTEGER cbtuition_total;	// output length for tuition_total
	SQLINTEGER cbstart_date;	// output length for start_date
	SQLINTEGER cbgrad_date;		// output length for grad_date
	SQLINTEGER cbloan_amount;	// output length for loan_amount
	SQLINTEGER cbdegree_program;	// output length for degree_program
	SQLINTEGER cbgpa;			// output length for gpa
	SQLINTEGER cbamount_owed;	// output length for amount_owed
	SQLINTEGER cbage_at_graduation;	// output length for age_at_graduation
} STUDENTREC;					// student output record
STUDENTREC studentrec;

/***************************************************************************************
	grade row structure for output operations (student_db.dbo.grade)
***************************************************************************************/
struct {
	char ssn[10];				// student_db.dbo.grade.ssn
	char ccode[5];				// student_db.dbo.grade.ccode
	char grade[3];				// student_db.dbo.grade.grade
	SQLINTEGER cbssn;			// output length for ssn
	SQLINTEGER cbccode;			// output length for ccode
	SQLINTEGER cbgrade;			// output length for grade
} graderec;						// grade output record


/***************************************************************************************
	dept row structure for output operations (dept_db.dbo.dept)
***************************************************************************************/
struct {
	char dept[5];				// dept_db.dbo.dept
	char dname[31];				// dept_db.dbo.dname
	SQLINTEGER cbdept;			// output length for dept
	SQLINTEGER cbdname;			// output length for dname
} deptrec;						// dept output record


/***************************************************************************************
	class row structure for output operations (dept_db.dbo.class)
***************************************************************************************/
struct {
	char ccode[5];				// dept_db.dbo.grade.ccode
	char cname[31];				// dept_db.dbo.grade.cname
	char dept[5];				// dept_db.dbo.grade.dept
	char room[7];				// dept_db.dbo.grade.room
	char prereq[5];				// dept_db.dbo.grade.prereq
	SQLINTEGER cbccode;			// output length for ccode
	SQLINTEGER cbcname;			// output length for cname
	SQLINTEGER cbdept;			// output length for dept
	SQLINTEGER cbroom;			// output length for room
	SQLINTEGER cbprereq;		// output length for prereq
} classrec;						// class output record


/***************************************************************************************
	Miscellaneous input variables
***************************************************************************************/
SDWORD rowcount;				// SQL row count
SDWORD cbrowcount;				// input length of rowcount variable
char inssn[10];					// input ssn variable
SDWORD cbinssn=SQL_NTS;			// input length of inssn variable
char inlname[21];				// input lname variable
SDWORD cbinlname=SQL_NTS;		// input length of inlname variable
char infname[13];				// input fname variable
SDWORD cbinfname=SQL_NTS;		// input length of infname variable
char ingender[2];				// input gender variable
SDWORD cbingender=SQL_NTS;		// input length of ingender variable
char inmajor[5];				// input major variable
SDWORD cbinmajor=SQL_NTS;		// input length of inmajor variable
char inbirth_date[31];			// input birth_date variable
SDWORD cbinbirth_date=SQL_NTS;	// input length of inbirth_date variable
char intuition_paid[21];		// input tuition_paid variable (use char to eliminate rounding)
SDWORD cbintuition_paid=SQL_NTS;	// input length of intuition_paid variable
char intuition_total[21];		// input tuition_total variable (use char to eliminate rounding)
SDWORD cbintuition_total=SQL_NTS;	// input length of intuition_total variable
char instart_date[31];			// input start_date variable
SDWORD cbinstart_date=SQL_NTS;	// input length of instart_date variable
char ingrad_date[31];			// input grad_date variable
SDWORD cbingrad_date=SQL_NTS;	// input length of ingrad_date variable
char inloan_amount[21];			// input loan_amount variable (use char to eliminate rounding)
SDWORD cbinloan_amount=SQL_NTS;	// input length of inloan_amount variable
char indegree_program[2];		// input degree_program variable
SDWORD cbindegree_program=SQL_NTS;	// input length of indegree_program variable

char inccode[5];				// input ccode variable
SDWORD cbinccode=SQL_NTS;		// input length of inccode variable
char indept[5];					// input dept variable
SDWORD cbindept=SQL_NTS;		// input length of indept variable
char indname[31];				// input dname variable
SDWORD cbindname=SQL_NTS;		// input length of indname variable
char incname[31];				// input cname variable
SDWORD cbincname=SQL_NTS;		// input length of incname variable
char inroom[7];					// input room variable
SDWORD cbinroom=SQL_NTS;		// input length of inroom variable
char inprereq[5];				// input prereq variable
SDWORD cbinprereq=SQL_NTS;		// input length of inprereq variable
char reluctant_student[81];		// output variable used for character string
SQLINTEGER cbreluctant_student;	// output length of reluctant_student variable

char oldssn[10];				// old ssn variable, used for break reports
char oldccode[5];				// old ccode variable, used for break reports
char olddept[5];				// old dept variable, used for break reports
char press_any_key[101];		// used for gets statement when key press is needed
int menuoption = 0;				// used for main menu screen
char entered_value[3];			// used for main menu screen
char user_name[31];				// database user name
char user_password[31];			// database user password
char dbms_name[81];				// dbms name
char odbc_dsn[81];				// allow user to pick the ODBC data source name


/***************************************************************************************
	main
***************************************************************************************/
void main(void)
{
	logon_screen();				// select database user to log on as
	logon();					// log on to the SQL Server database
	select_database();			// Use the student_db training database
	menu_screen();				// Display the menu screen
	logoff();					// Log off of SQL Server
	exit(0);					// Exit program with 0 (success) return code
} /* end of main */


/***************************************************************************************
	menu_screen
***************************************************************************************/
void menu_screen(void)
{
	// initialize variables
	menuoption = 0;
	strcpy(entered_value,"99");
	
	// Continue to display menu screen until user selects option "0"
	while (1)
	{
		printf("\n\nPress ENTER to view Menu ...");
		gets(entered_value);
		system("cls");
		printf("\nDBMS: <<%s>>\t\tLogon Name <<%s>>\n", dbms_name, user_name);
		printf("\nPick any Option:");
		printf("\n\t0 - Exit System");
		printf("\n\t1 - List Students");
		printf("\n\t2 - List Classes Each Student is Enrolled In");
		printf("\n\t3 - List Classes Offered By Departments");
		printf("\n\t4 - List Departments Offered by University");
		printf("\n\t5 - List Student Grade Point Average");
		printf("\n\t6 - List Students within each Class");
		printf("\n\t7 - Find Students Not Enrolled In Any Classes");
		printf("\n\t8 - Enroll Student in All Entry Level Classes For Their Major");
		printf("\n\t9 - Show Classes Needed to Graduate");
		printf("\n\t10 - Show Empty Classes");
		printf("\n\t11 - Insert a New Student");
		printf("\n\t12 - Delete a Student");
		printf("\n\t13 - Enroll a Student in a Class");
		printf("\n\t14 - Remove a Student from a Class");
		printf("\n\t15 - Insert a New Department");
		printf("\n\t16 - Delete a Department");
		printf("\n\t17 - Insert a New Class");
		printf("\n\t18 - Delete a Class");
		printf("\n\nOption: ");
		gets(entered_value);
		if (strlen(entered_value) == 0)
		{
			strcpy(entered_value,"99");
		}

		system("cls");
		switch((menuoption=atoi(entered_value)))
		{
		case 99:					// whoops, picked an invalid option
			break;
		case 0:						// Log off and exit program
			logoff();
			break;
		case 1:						// Provide a student listing
			list_students();
			break;
		case 2:						// Provide a listing of each class a student is enrolled in
			list_enrollments();
			break;
		case 3:						// Provide a listing of classes sorted by department
			list_classes();
			break;
		case 4:						// Provide a listing of all departments in university
			list_departments();
			break;
		case 5:						// Display the grade point average for a student
			list_gpa();
			break;
		case 6:						// Display a listing of classes and students in each class
			list_student_by_class();
			break;
		case 7:						// Display a listing of non-enrolled students
			reluctant_students();;
			break;
		case 8:						// Enroll a student in every entry level class for their major
			enroll_in_entry_classes();
			break;
		case 9:						// Display a list of classes a student needs in order to graduate
			needed_classes();
			break;
		case 10:					// Display a listing of empty classes (no enrollments)
			empty_classes();
			break;
		case 11:					// Insert a new student into the student table
			insert_student();
			break;
		case 12:					// Delete a student from the student table
			delete_student();
			break;
		case 13:					// Enroll a student in a selected class
			enroll_in_class();
			break;
		case 14:					// Remove a student from a class
			remove_from_class();
			break;
		case 15:					// Insert a new department into the department table
			insert_dept();
			break;
		case 16:					// Delete a department from the department table
			delete_dept();
			break;
		case 17:					// Insert a new class into the class table
			insert_class();
			break;
		case 18:					// Remove a class from the class table
			delete_class();
			break;
		default:					// Whoops, pressed the wrong key ...
			printf("\nInvalid Option - Please Try Again!\n");
			menuoption = 0;
		}
	}
} /* end of menu_screen */



/***************************************************************************************
	logon_screen
***************************************************************************************/
void logon_screen(void)
{
	// initialize variables
	menuoption = 0;
	strcpy(entered_value,"99");
	
	// request the ODBC Data Source Name for the DBMS connection
	system("cls");
	printf("\nWelcome to the Sample University Application\n");
	printf("\nPlease enter the ODBC Data Source Name (DSN) for your DBMS: ");
	gets(odbc_dsn);

	// if no DSN entered, exit program
	if (strlen(odbc_dsn) == 0)
	{
		printf("\nNo ODBC Data Source Name was entered, program will exit ...\n");
		exit(0);
	}
	
	// Continue to display menu screen until user selects option "0"
	while (1)
	{
		system("cls");
		printf("\nPick any Option:");
		printf("\n\t0 - Exit System");
		printf("\n\t1 - Log on as the STUDENT_ADMIN account.");
		printf("\n\t2 - Log on as the DEPT_ADMIN account.");
		printf("\n\t3 - Log on as the ENDUSER1 account.");
		printf("\n\nOption: ");
		gets(entered_value);
		if (strlen(entered_value) == 0)
		{
			strcpy(entered_value,"99");
		}

		system("cls");
		switch((menuoption=atoi(entered_value)))
		{
		case 99:					// whoops, picked an invalid option
			break;
		case 0:						// exit program
			exit(0);				
			break;
		case 1:						// Log on as the STUDENT_ADMIN account
			strcpy(user_name,"STUDENT_ADMIN");
			strcpy(user_password, "STUDENT_ADMIN");
			return;
			break;
		case 2:						// Log on as the DEPT_ADMIN account
			strcpy(user_name,"DEPT_ADMIN");
			strcpy(user_password, "DEPT_ADMIN");
			return;
			break;
		case 3:						// Log on as the ENDUSER1 account
			strcpy(user_name,"ENDUSER1");
			strcpy(user_password, "ENDUSER1");
			return;
			break;
		default:					// Whoops, pressed the wrong key ...
			printf("\nInvalid Option - Please Try Again!\n");
			menuoption = 0;
		}
	}
} /* end of logon_screen */


/***************************************************************************************
	select_database
	This function is used to select the STUDENT_DB SQL Server database
***************************************************************************************/
void select_database(void)
{
	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);
	
	// Use the SQL Server database STUDENT_DB for this program
	rc1 = SQLExecDirect(hstmt1,
			(SQLCHAR *)"USE STUDENT_DB", SQL_NTS);
	
	// If unable to use the student_db database, return an error message
	if ( (rc1 != SQL_SUCCESS) && (rc1 != SQL_SUCCESS_WITH_INFO) )
	{
		printf("\nUnable to access the STUDENT_DATABASE.");
		error_dump();
	}
	else printf("\nSuccessfully logged on to the STUDENT_DATABASE.");

	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);

} /* end of select_database */


/***************************************************************************************
	list_students
	This function provides a detailed student listing
***************************************************************************************/
void list_students(void)
{
#define ROWS 5   // row buffer size, usually would be larger
	UDWORD    crow, irow;
	UWORD     rgfRowStatus[ROWS];
	STUDENTREC rstudentrec[ROWS];
	int ch1 = '%';
	int ch2 = '_';

	// set rowcounter to 0
	rowcount = 0;
	
	// request a social security number
	system("cls");
	printf("\nSTUDENT LISTING SCREEN\n");
	printf("\nPlease enter a Social Security Number (use '%%' for All Students): ");
	gets(inssn);
	
	// if no social security number entered, request all students
	if (strlen(inssn) == 0)
	{
		printf("\nNo social security number was entered, all students will be returned!");
		strcpy(inssn,"%");
	}

			
	// set length of social security number
	if (strlen(inssn) == 0) cbinssn=SQL_NULL_DATA;
	else cbinssn=SQL_NTS;
	
	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);

	if (!(strchr(inssn, ch1)==NULL) || !(strchr(inssn, ch2)==NULL))
	{
		// if ssn contains a wildcard character, you might get back more than one row. 
		// if so, use a server cursor for incremental fetching
		SQLSetStmtOption(hstmt1,SQL_CURSOR_TYPE,SQL_CURSOR_KEYSET_DRIVEN);
	}


	// bind social security number as input argument
	SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 9, 0, inssn, 10, &cbinssn);

	// execute SQL statement
	if (SQLExecDirect(hstmt1,
		(SQLCHAR *)"SELECT SSN,	FNAME+' '+LNAME AS NAME, \
		CASE GENDER \
			WHEN 'M' THEN 'Male' \
			WHEN 'F' THEN 'Female' \
		ELSE 'Unknown' END AS GENDER, \
		SUBSTRING(DATENAME(MM, BIRTH_DATE)+' '+DATENAME(DD, BIRTH_DATE)+', '+DATENAME(YY, BIRTH_DATE),1,20) AS BIRTH_DATE, \
		MAJOR, CASE DEGREE_PROGRAM \
		WHEN 'U' THEN 'Undergraduate' \
		WHEN 'M' THEN 'Masters' \
		WHEN 'P' THEN 'PhD.' \
		ELSE 'Unknown' \
	END AS DEGREE_PROGRAM, \
	ISNULL(TUITION_PAID,0) AS TUITION_PAID, \
	ISNULL(TUITION_TOTAL,0) AS TUITION_TOTAL, \
	ISNULL(TUITION_TOTAL,0) - ISNULL(TUITION_PAID,0) AS AMOUNT_OWED, \
	ISNULL(LOAN_AMOUNT,0) AS LOAN_AMOUNT, \
	SUBSTRING(DATENAME(MM, START_DATE)+' '+DATENAME(DD, START_DATE)+', '+DATENAME(YY, START_DATE),1,20) AS START_DATE, \
	SUBSTRING(DATENAME(MM, GRAD_DATE)+' '+DATENAME(DD, GRAD_DATE)+', '+DATENAME(YY, GRAD_DATE),1,20) AS GRAD_DATE, \
	ISNULL(DATEDIFF(YY, BIRTH_DATE, GRAD_DATE),0) AS AGE_AT_GRADUATION \
	FROM STUDENT_DB.DBO.STUDENT WHERE SSN LIKE ? ORDER BY SSN",
		SQL_NTS) != SQL_SUCCESS)
	{
		// if SQL statement fails, display message and return
		warning_dump();
		return;
	}
	
	// after execution, can set rowset size and bind type so both default result set 
	// for the single row case and and server cursors for the multi-row case
	// can be fetched using row-wise binding
	SQLSetStmtOption(hstmt1, SQL_BIND_TYPE, sizeof(studentrec));
	SQLSetStmtOption(hstmt1, SQL_ROWSET_SIZE, ROWS);

	// bind output columns of SQL select statement to program variables
	SQLBindCol(hstmt1, 1, SQL_C_CHAR, rstudentrec[0].ssn,10,&rstudentrec[0].cbssn);
	SQLBindCol(hstmt1, 2, SQL_C_CHAR, rstudentrec[0].name, 33, &rstudentrec[0].cbname);
	SQLBindCol(hstmt1, 3, SQL_C_CHAR, rstudentrec[0].gender, 7, &rstudentrec[0].cbgender);
	SQLBindCol(hstmt1, 4, SQL_C_CHAR, rstudentrec[0].birth_date, 31, &rstudentrec[0].cbbirth_date);
	SQLBindCol(hstmt1, 5, SQL_C_CHAR, rstudentrec[0].major, 5, &rstudentrec[0].cbmajor);
	SQLBindCol(hstmt1, 6, SQL_C_CHAR, rstudentrec[0].degree_program, 15, &rstudentrec[0].cbdegree_program);
	SQLBindCol(hstmt1, 7, SQL_C_FLOAT, &rstudentrec[0].tuition_paid, 0, &rstudentrec[0].cbtuition_paid);
	SQLBindCol(hstmt1, 8, SQL_C_FLOAT, &rstudentrec[0].tuition_total, 0, &rstudentrec[0].cbtuition_total);
	SQLBindCol(hstmt1, 9, SQL_C_FLOAT, &rstudentrec[0].amount_owed, 0, &rstudentrec[0].cbamount_owed);	
	SQLBindCol(hstmt1, 10, SQL_C_FLOAT, &rstudentrec[0].loan_amount, 0, &rstudentrec[0].cbloan_amount);
	SQLBindCol(hstmt1, 11, SQL_C_CHAR, rstudentrec[0].start_date, 31, &rstudentrec[0].cbstart_date);
	SQLBindCol(hstmt1, 12, SQL_C_CHAR, rstudentrec[0].grad_date, 31, &rstudentrec[0].cbgrad_date);
	SQLBindCol(hstmt1, 13, SQL_C_FLOAT, &rstudentrec[0].age_at_graduation, 0, &rstudentrec[0].cbage_at_graduation);
	
	// retrieve all rows as queried by the select statement
	while (TRUE)
	{
		rc1 = SQLExtendedFetch(hstmt1, SQL_FETCH_NEXT, 1, &crow, rgfRowStatus);
		if (rc1 == SQL_ERROR)
		{
			// if a fetch (read) fails, display error message and stop program
			error_dump();
		}

		if ((rc1 == SQL_SUCCESS) || (rc1 == SQL_SUCCESS_WITH_INFO))
		{
			for (irow = 0; irow < crow; irow++) 
			{
				// display each row of data, ignoring "holes"
				if (rgfRowStatus[irow] != SQL_ROW_DELETED && rgfRowStatus[irow] != SQL_ROW_ERROR)
				{
					rowcount++;

					printf("\n\nPress ENTER to view next data record...");
					gets(press_any_key);
					system("cls");

					printf("\nStudent Social Security Number: %s \tName: %s",
						studentrec.ssn, rstudentrec[irow].name);
					printf("\n\tGender: %-6s\tBirth Date: %s \n\tMajor: %-4s  Degree Program: %s",
						rstudentrec[irow].gender, rstudentrec[irow].birth_date, rstudentrec[irow].major,
						rstudentrec[irow].degree_program);
					printf("\n\tTuition Amount: %.2f \tTuition Paid: %.2f",
							rstudentrec[irow].tuition_total, rstudentrec[irow].tuition_paid);
					printf("\n\tTuition Owed: %.2f \tLoan Amount: %.2f",
							rstudentrec[irow].amount_owed, rstudentrec[irow].loan_amount);
					printf("\n\tDate Started at School: %s", rstudentrec[irow].start_date);
					printf("\n\tExpected Graduation Date: %s", rstudentrec[irow].grad_date);
					printf("\n\tExpected Age at Graduation: %.0f\n\n", rstudentrec[irow].age_at_graduation);
				}
			}
		} else {
			// we got a "NO_DATA_FOUND" return
			break;
		}
		
	}

	// if no rows were returned, display message
	if (rowcount == 0)
	{
		printf("\nNo students were found, no rows returned ...\n");
	}
	
	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);

} /* end of list_students */


/***************************************************************************************
	list_enrollments
	This function displays a list of enrollments by student
***************************************************************************************/
void list_enrollments(void)
{
	// initialize variables
	strset(oldssn,'\0');
	rowcount = 0;
	
	// request a social security number
	system("cls");
	printf("\nSTUDENT ENROLLMENT LISTING SCREEN\n");
	printf("\nPlease enter a Social Security Number (use '%%' for All Students): ");
	gets(inssn);
	
	// if no social security number is entered, select all students
	if (strlen(inssn) == 0)
	{
		printf("\nNo social security number was entered, all students will be returned!");
		strcpy(inssn,"%");
	}
	
	// set length of social security number
	if (strlen(inssn) == 0) cbinssn=SQL_NULL_DATA;
	else cbinssn=SQL_NTS;
	
	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);

	// set statement to use a server cursor, for incremental fetching
	SQLSetStmtOption(hstmt1,SQL_CURSOR_TYPE,SQL_CURSOR_STATIC);

	// bind social security number as input argument
	SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 9, 0, inssn, 10, &cbinssn);

	// execute SQL select statement
	if (SQLExecDirect(hstmt1,
			(SQLCHAR *)"SELECT S.SSN, FNAME+' '+LNAME AS NAME, \
				ISNULL(G.CCODE,'****') AS CCODE, \
				ISNULL(C.CNAME,'****') AS CNAME, ISNULL(GRADE,'**') AS GRADE \
			FROM STUDENT_DB.DBO.GRADE G \
				RIGHT OUTER JOIN STUDENT_DB.DBO.STUDENT S ON G.SSN = S.SSN \
				LEFT OUTER JOIN DEPT_DB.DBO.CLASS C ON G.CCODE = C.CCODE \
			WHERE S.SSN LIKE ? ORDER BY S.SSN, C.CCODE", SQL_NTS) != SQL_SUCCESS)

	{
		// if SQL statement fails, display message and return
		warning_dump();
		return;
	}

	// bind output columns of SQL select statement to program variables
	SQLBindCol(hstmt1, 1, SQL_C_CHAR, studentrec.ssn,10,&studentrec.cbssn);
	SQLBindCol(hstmt1, 2, SQL_C_CHAR, studentrec.name, 33, &studentrec.cbname);
	SQLBindCol(hstmt1, 3, SQL_C_CHAR, graderec.ccode, 5, &graderec.cbccode);
	SQLBindCol(hstmt1, 4, SQL_C_CHAR, classrec.cname, 31, &classrec.cbcname);
	SQLBindCol(hstmt1, 5, SQL_C_CHAR, graderec.grade, 3, &graderec.cbgrade);

	// retrieve all rows as queried by the select statement
	while (TRUE)
	{
		rc1 = SQLFetch(hstmt1);
		if (rc1 == SQL_ERROR)
		{
			// if a fetch (read) fails, display error message and stop program
			error_dump();
		}
		
		// display each row of data
		if ((rc1 == SQL_SUCCESS) || (rc1 == SQL_SUCCESS_WITH_INFO))
		{
			rowcount++;
			if (strcmp(studentrec.ssn,oldssn) != 0)
			{
				printf("\n\nPress ENTER to view next page of data ...");
				gets(press_any_key);
				system("cls");

				printf("\nStudent Social Security Number: %s\tName: %s",
					studentrec.ssn, studentrec.name);
			}
			printf("\n\tCourse Code: %s,\tCourse Name: %s\n\tGrade: %s\n",
				graderec.ccode, classrec.cname, graderec.grade);
			strcpy(oldssn,studentrec.ssn);
		}
		else
		{
			break;
		}
	}

	// if no rows were returned, display message
	if (rowcount == 0)
	{
		printf("\nNo students were found, no rows returned ...\n");
	}

	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);

} /* end of list_enrollments */


/***************************************************************************************
	list_classes
	This function displays a listing of classes by department
***************************************************************************************/
void list_classes(void)
{
	// initialize variables
	strset(olddept,'\0');
	rowcount = 0;
	
	// request a department code
	system("cls");
	printf("\nDEPARTMENT CLASS LISTING SCREEN\n");
	printf("\nPlease enter a Department Code (use '%%' for All Departments): ");
	gets(indept);
	
	// if no department code is entered, select all departments
	if (strlen(indept) == 0)
	{
		printf("\nNo department code was entered, all departments will be returned!");
		strcpy(indept,"%");
	}
		
	// set length of department code
	if (strlen(indept) == 0) cbindept=SQL_NULL_DATA;
	else cbindept=SQL_NTS;
	
	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);

	// set statement to use a server cursor, for incremental fetching
	SQLSetStmtOption(hstmt1,SQL_CURSOR_TYPE,SQL_CURSOR_STATIC);

	// bind department code as input argument
	SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 4, 0, indept, 5, &cbindept);

	// execute SQL select statement
	if (SQLExecDirect(hstmt1,
			(SQLCHAR *)"SELECT ISNULL(CCODE,'****') AS CCODE, \
			ISNULL(CNAME,'****') AS CNAME, \
			D.DEPT, \
			ISNULL(ROOM,'****') AS ROOM, \
			ISNULL(PREREQ,'****') AS PREREQ, \
			ISNULL(D.DNAME,'****') AS DNAME \
			FROM DEPT_DB.DBO.DEPT D, DEPT_DB.DBO.CLASS C \
			WHERE D.DEPT *= C.DEPT \
			AND UPPER(D.DEPT) LIKE UPPER(?) ORDER BY D.DEPT, CCODE",
				SQL_NTS) != SQL_SUCCESS)
	{
		// if SQL statement fails, display error message and return
		warning_dump();
		return;
	}

	// bind output columns of SQL select statement to program variables
	SQLBindCol(hstmt1, 1, SQL_C_CHAR, classrec.ccode, 5, &classrec.cbccode);
	SQLBindCol(hstmt1, 2, SQL_C_CHAR, classrec.cname, 31, &classrec.cbcname);
	SQLBindCol(hstmt1, 3, SQL_C_CHAR, classrec.dept, 5, &classrec.cbdept);
	SQLBindCol(hstmt1, 4, SQL_C_CHAR, classrec.room, 7, &classrec.cbroom);
	SQLBindCol(hstmt1, 5, SQL_C_CHAR, classrec.prereq, 5, &classrec.cbprereq);
	SQLBindCol(hstmt1, 6, SQL_C_CHAR, deptrec.dname, 31, &deptrec.cbdname);

	// retrieve all rows as queried by the select statement
	while (TRUE)
	{
		rc1 = SQLFetch(hstmt1);
		if (rc1 == SQL_ERROR)
		{
			// if a fetch (read) fails, display error message and stop program
			error_dump();
		}
		
		// display each row of data
		if ((rc1 == SQL_SUCCESS) || (rc1 == SQL_SUCCESS_WITH_INFO))
		{
			rowcount++;
			if (strcmp(classrec.dept,olddept) != 0)
			{
				printf("\n\nPress ENTER to view next page of data ...");
				gets(press_any_key);
				system("cls");

				printf("\n\nDepartment Code: %s\tName: %s",
					classrec.dept, deptrec.dname);
				printf("\n\n\t%-4s %-30s %-6s %-6s",
				"CODE", "COURSE NAME", "ROOM", "PREREQ");
			}
			printf("\n\t%-4s %-30s %-6s %-4s",
				classrec.ccode, classrec.cname, classrec.room, classrec.prereq);
			strcpy(olddept,classrec.dept);
		}
		else
		{
			break;
		}
	}

	// if no rows were returned, display message
	if (rowcount == 0)
	{
		printf("\nNo classes were found, no rows returned ...\n");
	}

	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);

} /* end of list_classes */


/***************************************************************************************
	list_departments
	This function displays a listing of departments within the university
***************************************************************************************/
void list_departments(void)
{
	// initialize variables
	strset(olddept,'\0');
	rowcount = 0;
	
	// request a department code
	system("cls");
	printf("\nDEPARTMENT LISTING SCREEN\n");
	printf("\nPlease enter a Department Code (use '%%' for All Departments): ");
	gets(indept);
	
	// if no department code was entered, select all departments
	if (strlen(indept) == 0)
	{
		printf("\nNo department code was entered, all departments will be returned!");
		strcpy(indept,"%");
	}
	
	// set length of department code
	if (strlen(indept) == 0) cbindept=SQL_NULL_DATA;
	else cbindept=SQL_NTS;
	
	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);

	// set statement to use a server cursor, for incremental fetching
	SQLSetStmtOption(hstmt1,SQL_CURSOR_TYPE,SQL_CURSOR_STATIC);

	// bind department code as the first input argument to the SQL statement
	SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 4, 0, indept, 5, &cbindept);
	
	// execute the SQL select statement
	if (SQLExecDirect(hstmt1,
			(SQLCHAR *)"SELECT DEPT, DNAME FROM DEPT_DB.DBO.DEPT \
						WHERE UPPER(DEPT) LIKE (?) ORDER BY DEPT",
				SQL_NTS) != SQL_SUCCESS)
	{
		// if the SQL statement fails, display error message and exit
		warning_dump();
		return;
	}

	// bind variables to output columns of select statement
	SQLBindCol(hstmt1, 1, SQL_C_CHAR, deptrec.dept, 5, &deptrec.cbdept);
	SQLBindCol(hstmt1, 2, SQL_C_CHAR, deptrec.dname, 31, &deptrec.cbdname);

	printf("\n\nPress ENTER to view next page of data ...");
	gets(press_any_key);
	system("cls");
	printf("\n%-15s\t%-30s", "DEPARTMENT CODE", "DEPARTMENT NAME\n");

	// display data
	while (TRUE)
	{
		
		rc1 = SQLFetch(hstmt1);
		if (rc1 == SQL_ERROR)
		{
			// if a fetch (read) fails, display error message and exit
			error_dump();
		}
		
		if ((rc1 == SQL_SUCCESS) || (rc1 == SQL_SUCCESS_WITH_INFO))
		{
			rowcount++;
			printf("\n%-15s\t%-30s", deptrec.dept, deptrec.dname);
		}
		else
		{
			break;
		}
	}

	//  if no rows were returned, display a message
	if (rowcount == 0)
	{
		printf("\nNo Departments were found, no rows returned ...\n");
	}

	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);
} /* end of list_departments */


/***************************************************************************************
	list_gpa
	This function provides a listing of student grade point averages
***************************************************************************************/
void list_gpa(void)
{
	// initialize variables
	rowcount = 0;

	// request a social security number
	system("cls");
	printf("\nSTUDENT GRADE POINT AVERAGE LISTING SCREEN\n");
	printf("\nPlease enter a Social Security Number (use '%%' for All Students): ");
	gets(inssn);
	
	// if no social security number entered, return all students
	if (strlen(inssn) == 0)
	{
		printf("\nNo social security number was entered, all students will be returned!");
		strcpy(inssn,"%");
	}
	
	// set length of social security number
	if (strlen(inssn) == 0) cbinssn=SQL_NULL_DATA;
	else cbinssn=SQL_NTS;
	
	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);

	// set statement to use a server cursor, for incremental fetching
	SQLSetStmtOption(hstmt1,SQL_CURSOR_TYPE,SQL_CURSOR_STATIC);

	// bind social security number as first argument to SQL statement
	SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 9, 0, inssn, 10, &cbinssn);
	
	// execute the SQL select statement
	if (SQLExecDirect(hstmt1,
			(SQLCHAR *)"SELECT S.SSN, S.FNAME+' '+LNAME, ISNULL(GPA,0) GPA \
						FROM STUDENT_DB.DBO.STUDENT_GPA G, STUDENT_DB.DBO.STUDENT S \
						WHERE S.SSN *= G.SSN AND S.SSN LIKE ? ORDER BY S.SSN",
				SQL_NTS) != SQL_SUCCESS)
	{
		// if the SQL statement fails, display error message and return
		warning_dump();
		return;
	}
	
	// bind output of select statement columns to program variables
	SQLBindCol(hstmt1, 1, SQL_C_CHAR, studentrec.ssn,10,&studentrec.cbssn);
	SQLBindCol(hstmt1, 2, SQL_C_CHAR, studentrec.name,33,&studentrec.cbname);
	SQLBindCol(hstmt1, 3, SQL_C_FLOAT, &studentrec.gpa, 0, &studentrec.cbgpa);
	
	printf("\n\nPress ENTER to view next page of data ...");
	gets(press_any_key);
	system("cls");

	// return rows of data
	while (TRUE)
	{
		rc1 = SQLFetch(hstmt1);
		if (rc1 == SQL_ERROR)
		{
			// if a fetch (read) fails, display error message, exit program
			error_dump();
		}
		
		if ((rc1 == SQL_SUCCESS) || (rc1 == SQL_SUCCESS_WITH_INFO))
		{
			rowcount++;
			printf("\nSSN: %s\tName: %-32s\tGPA: %.2f",
				studentrec.ssn, studentrec.name, studentrec.gpa);
		}
		else
		{
			break;
		}
	}

	// if no students were returned, display message
	if (rowcount == 0)
	{
		printf("\nNo students were found, no rows returned ...\n");
	}

	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);
} /* end of list_gpa */


/***************************************************************************************
	list_student_by_class
	This function provides a listing of studentw within classes
***************************************************************************************/
void list_student_by_class(void)
{
	// initialize variables
	strset(olddept,'\0');
	strset(oldccode,'\0');
	rowcount = 0;

	// request a class code
	system("cls");
	printf("\nCLASS STUDENT LISTING SCREEN\n");
	printf("\nPlease enter a Class Code (use '%%' for All Classes): ");
	gets(inccode);
	
	// if no class code was entered, all classes will be returned
	if (strlen(inccode) == 0)
	{
		printf("\nNo Class Code was entered, all classes will be returned!");
		strcpy(inccode,"%");
	}
		
	// set the length of the class code variable
	if (strlen(inccode) == 0) cbinccode=SQL_NULL_DATA;
	else cbinccode=SQL_NTS;
	
	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);

	// set statement to use a server cursor, for incremental fetching
	SQLSetStmtOption(hstmt1,SQL_CURSOR_TYPE,SQL_CURSOR_STATIC);

	// bind the class code variable as the first argument to the SQL statement
	SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 4, 0, inccode, 5, &cbinccode);

	// execute the SQL select statement
	if (SQLExecDirect(hstmt1,
			(SQLCHAR *)"SELECT ISNULL(C.CCODE,'****') AS CCODE, ISNULL(CNAME,'****') AS CNAME, \
							C.DEPT, ISNULL(ROOM,'****') AS ROOM, ISNULL(PREREQ,'****') AS PREREQ, \
							ISNULL(D.DNAME,'****') AS DNAME, ISNULL(G.SSN,'*********') AS SSN, \
							ISNULL(G.GRADE,'**') AS GRADE \
							FROM DEPT_DB.DBO.DEPT D, DEPT_DB.DBO.CLASS C,STUDENT_DB.DBO.GRADE G \
							WHERE D.DEPT = C.DEPT AND C.CCODE *= G.CCODE \
							AND UPPER(C.CCODE) LIKE UPPER(?) ORDER BY C.DEPT, C.CCODE, G.SSN",
								SQL_NTS) != SQL_SUCCESS)
	{
		// if SQL statement fails, display error message and return
		warning_dump();
		return;
	}

	// bind the output of the select columns to program variables
	SQLBindCol(hstmt1, 1, SQL_C_CHAR, classrec.ccode, 5, &classrec.cbccode);
	SQLBindCol(hstmt1, 2, SQL_C_CHAR, classrec.cname, 31, &classrec.cbcname);
	SQLBindCol(hstmt1, 3, SQL_C_CHAR, classrec.dept, 5, &classrec.cbdept);
	SQLBindCol(hstmt1, 4, SQL_C_CHAR, classrec.room, 7, &classrec.cbroom);
	SQLBindCol(hstmt1, 5, SQL_C_CHAR, classrec.prereq, 5, &classrec.cbprereq);
	SQLBindCol(hstmt1, 6, SQL_C_CHAR, deptrec.dname, 31, &deptrec.cbdname);
	SQLBindCol(hstmt1, 7, SQL_C_CHAR, graderec.ssn, 10, &graderec.cbssn);
	SQLBindCol(hstmt1, 8, SQL_C_CHAR, graderec.grade, 3, &graderec.cbgrade);

	// display the rows from the select statement
	while (TRUE)
	{
		rc1 = SQLFetch(hstmt1);
		if (rc1 == SQL_ERROR)
		{
			// if a fetch (read) fails, display error message, exit program
			error_dump();
		}
		
		if ((rc1 == SQL_SUCCESS) || (rc1 == SQL_SUCCESS_WITH_INFO))
		{
			rowcount++;
			if (strcmp(classrec.dept,olddept) != 0)
			{
				printf("\n\nPress ENTER to view next page of data ...");
				gets(press_any_key);
				system("cls");

				printf("\n\nDEPARTMENT CODE: %s\tNAME: %s",
					classrec.dept, deptrec.dname);
				printf("\n\t%-4s %-30s %-6s %-6s",
				"CODE", "COURSE NAME", "ROOM", "PREREQ");
			}
			if (strcmp(classrec.ccode,oldccode) != 0)
			{
				printf("\n\t%-4s %-30s %-6s %-4s",
					classrec.ccode, classrec.cname, classrec.room, classrec.prereq);
				printf("\n\t\t%-22s\t%5s", "SOCIAL SECURITY NUMBER", "GRADE");
			}
			printf("\n\t\t%-22s\t%5s", graderec.ssn, graderec.grade);
			strcpy(olddept, classrec.dept);
			strcpy(oldccode, classrec.ccode);
		}
		else
		{
			break;
		}
	}

	// if no rows were returned, display error message
	if (rowcount == 0)
	{
		printf("\nNo classes were found, no rows returned ...\n");
	}

	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);

} /* end of list_student_by_class */


/***************************************************************************************
	reluctant_students
	This function displays a listing of student not enrolled in any classes
***************************************************************************************/
void reluctant_students(void)
{
	// initialize variables
	rowcount = 0;

	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);
	
	// set statement to use a server cursor, for incremental fetching
	SQLSetStmtOption(hstmt1,SQL_CURSOR_TYPE,SQL_CURSOR_STATIC);

	// bind rowcount as first argument to SQL statement (return value)
	SQLBindParameter(hstmt1, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT,
		SQL_SMALLINT, 0, 0, &rowcount, 0, &cbrowcount);

	// execute a stored procedure (show_reluctant_student)
	if (SQLExecDirect(hstmt1,
			(SQLCHAR *)"{?=call STUDENT_DB.DBO.SHOW_RELUCTANT_STUDENTS}", SQL_NTS) != SQL_SUCCESS)
	{
		// if execution of procedure fails, display error, return
		warning_dump();
		return;
	}

	// bind output of procedure to program variable
	SQLBindCol(hstmt1, 1, SQL_C_CHAR, reluctant_student, 81, &cbreluctant_student);

	printf("\n\nPress ENTER to view next page of data ...");
	gets(press_any_key);
	system("cls");
	printf("\nRELUCTANT STUDENT LISTING SCREEN\n");

	// display each row of procedure output data
	while (TRUE)
	{
		rc1 = SQLFetch(hstmt1);
		if (rc1 == SQL_ERROR)
		{
			// if a fetch (read) fails, display error message, exit program
			error_dump();
		}
		
		if ((rc1 == SQL_SUCCESS) || (rc1 == SQL_SUCCESS_WITH_INFO))
		{
			printf("\n%s", reluctant_student);
		}
		else
		{
			break;
		}
	}
	
	// display the number of retrieved rows
	printf("\nThere are %d reluctant students in this university!", rowcount);
	printf("\nTime to call some parents ...");

	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);

} /* end of reluctant_students */

/***************************************************************************************
	enroll_in_entry_classes
	This function will enroll a student in all entry level classes for their major
***************************************************************************************/
void enroll_in_entry_classes(void)
{
	// initialize variables
	rowcount = 0;

	// request a social security number
	system("cls");
	printf("\nENROLL STUDENT IN ENTRY LEVEL CLASS SCREEN\n");
	printf("\nPlease enter a Student Social Security Number: ");
	gets(inssn);
	
	// if no social security number is entered, return to menu
	if (strlen(inssn) == 0)
	{
		printf("\nA Student Social Security Number was not entered!");
		printf("\nThis operation has been terminated!\n");
		return;
	}
	
	// set the length of social security number variable
	if (strlen(inssn) == 0) cbinssn=SQL_NULL_DATA;
	else cbinssn=SQL_NTS;
	
	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);

	// bind social security number to two locations in SQL statement (not a mistake)
	SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 9, 0, inssn, 10, &cbinssn);
	SQLBindParameter(hstmt1, 2, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 9, 0, inssn, 10, &cbinssn);

	// execute the SQL insert statement
	if (SQLExecDirect(hstmt1,
		(SQLCHAR *)"INSERT INTO STUDENT_DB.DBO.GRADE (SSN, CCODE, GRADE) \
		SELECT ?, CCODE, NULL FROM DEPT_DB.DBO.CLASS \
		WHERE PREREQ IS NULL AND DEPT = ( \
			SELECT MAJOR FROM STUDENT_DB.DBO.STUDENT WHERE SSN = ?)", SQL_NTS) != SQL_SUCCESS)
	{
		// if insert fails, warning messages displayed, rollback transaction
		warning_dump();
	}
	else
	{
		// if insert statement is successful, commit and display number of rows inserted
		rowcount_and_commit();
	}

	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);

} /* end of enroll_in_entry_classes */


/*******************************************************************************************
	needed_classes
	This function provides a listing of classes which are needed for a student to graduate
********************************************************************************************/
void needed_classes(void)
{
	// initialize variables
	strset(oldssn,'\0');
	rowcount = 0;

	// request a social security number
	system("cls");
	printf("\nPlease enter a Social Security Number (use '%%' for All Students): ");
	gets(inssn);
	
	// if no social security number was entered, all students will be returned
	if (strlen(inssn) == 0)
	{
		printf("\nNo social security number was entered, all students will be returned!");
		strcpy(inssn,"%");
	}
	
	// set length of social security number variable
	if (strlen(inssn) == 0) cbinssn=SQL_NULL_DATA;
	else cbinssn=SQL_NTS;
	
	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);

	// set statement to use a server cursor, for incremental fetching
	SQLSetStmtOption(hstmt1,SQL_CURSOR_TYPE,SQL_CURSOR_STATIC);

	// bind the social security number as the first input argument to the SQL statement
	SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 9, 0, inssn, 10, &cbinssn);

	// execute the stored procedure classes_needed_to_graduate
	if (SQLExecDirect(hstmt1,
			(SQLCHAR *)"{call STUDENT_DB.DBO.CLASSES_NEEDED_TO_GRADUATE(?)}", SQL_NTS) != SQL_SUCCESS)
	{
		// if procedure fails, display error message, return
		warning_dump();
		return;
	}

	// bind output columns from procedure to program variables
	SQLBindCol(hstmt1, 1, SQL_C_CHAR, studentrec.ssn, 10, &studentrec.cbssn);
	SQLBindCol(hstmt1, 2, SQL_C_CHAR, studentrec.name, 33, &studentrec.cbname);
	SQLBindCol(hstmt1, 3, SQL_C_CHAR, studentrec.major, 5, &studentrec.cbmajor);
	SQLBindCol(hstmt1, 4, SQL_C_CHAR, classrec.ccode, 5, &classrec.cbccode);
	SQLBindCol(hstmt1, 5, SQL_C_CHAR, classrec.cname, 31, &classrec.cbcname);
	SQLBindCol(hstmt1, 6, SQL_C_CHAR, classrec.dept, 5, &classrec.cbdept);
	SQLBindCol(hstmt1, 7, SQL_C_CHAR, classrec.room, 7, &classrec.cbroom);
	SQLBindCol(hstmt1, 8, SQL_C_CHAR, classrec.prereq, 5, &classrec.cbprereq);

	printf("\nCLASSES NEEDED TO GRADUATE\n");
	
	// return all rows of data from procedure
	while (TRUE)
	{
		rc1 = SQLFetch(hstmt1);
		if (rc1 == SQL_ERROR)
		{
			// if a fetch (read) fails, display error message, exit program
			error_dump();
		}
		
		if ((rc1 == SQL_SUCCESS) || (rc1 == SQL_SUCCESS_WITH_INFO))
		{
			rowcount++;
			if (strcmp(studentrec.ssn,oldssn) != 0)
			{
				printf("\n\nPress ENTER to view next page of data ...");
				gets(press_any_key);
				system("cls");

				printf("\n\nSocial Security Number: %s\tName: %s\tMajor: %s",
					studentrec.ssn, studentrec.name, studentrec.major);
				printf("\n\t%-4s %-30s %-4s %-6s %-6s",
					"CODE", "COURSE NAME", "DEPT", "ROOM", "PREREQ");
			}
			printf("\n\t%-4s %-30s %-4s %-6s %-4s",
				classrec.ccode, classrec.cname, classrec.dept,
					classrec.room, classrec.prereq);
			strcpy(oldssn, studentrec.ssn);
		}
		else
		{
			break;
		}
	}

	// if no rows of data were returned, display message
	if (rowcount == 0)
	{
		printf("\nNo students were found, no rows returned ...\n");
	}

	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);

} /* end of needed_classes */


/***************************************************************************************
	empty_classes
	This function provides a listing of classes which have no students
***************************************************************************************/
void empty_classes(void)
{
	// print report heading
	printf("\nEMPTY CLASS LISTING SCREEN\n");
	
	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);
	
	// set statement to use a server cursor, for incremental fetching
	SQLSetStmtOption(hstmt1,SQL_CURSOR_TYPE,SQL_CURSOR_STATIC);

	// execute procedure show_empty_classes
	if (SQLExecDirect(hstmt1,
			(SQLCHAR *)"{call DEPT_DB.DBO.SHOW_EMPTY_CLASSES}", SQL_NTS) != SQL_SUCCESS)
	{
		// if procedure fails, display error message, return
		warning_dump();
		return;
	}

	// bind output columns of procedure to program variables
	SQLBindCol(hstmt1, 1, SQL_C_CHAR, classrec.ccode, 5, &classrec.cbccode);
	SQLBindCol(hstmt1, 2, SQL_C_CHAR, classrec.cname, 31, &classrec.cbcname);
	SQLBindCol(hstmt1, 3, SQL_C_CHAR, classrec.dept, 5, &classrec.cbdept);
	SQLBindCol(hstmt1, 4, SQL_C_CHAR, classrec.room, 7, &classrec.cbroom);
	SQLBindCol(hstmt1, 5, SQL_C_CHAR, classrec.prereq, 5, &classrec.cbprereq);

	printf("\n\nPress ENTER to view next page of data ...");
	gets(press_any_key);
	system("cls");
	printf("\n%-4s %-30s %-4s %-6s %-6s",
				"CODE", "COURSE NAME", "DEPT", "ROOM", "PREREQ");

	// display each row of data
	while (TRUE)
	{
		rc1 = SQLFetch(hstmt1);
		if (rc1 == SQL_ERROR)
		{
			// if a fetch (read) fails, display error message, exit program
			error_dump();
		}
		
		if ((rc1 == SQL_SUCCESS) || (rc1 == SQL_SUCCESS_WITH_INFO))
		{
			printf("\n%-4s %-30s %-4s %-6s %-4s",
				classrec.ccode, classrec.cname, classrec.dept,
					classrec.room, classrec.prereq);
		}
		else
		{
			break;
		}
	}

	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);

} /* end of empty_classes */


/***************************************************************************************
	insert_student
	This function allows a student to entered into the student table
***************************************************************************************/
void insert_student(void)
{
	// request student information
	system("cls");
	printf("\nSTUDENT ADDITION SCREEN\n\n");
	
	printf("\nPlease enter a Social Security Number (required): ");
		gets(inssn);
		if (strlen(inssn) == 0)
		{
			printf("\nA Social Security Number is required!");
			printf("\nThis operation has been terminated!");
			return;
		}
		else cbinssn=SQL_NTS;

	printf("\nPlease enter a Last Name (required): ");
		gets(inlname);
		if (strlen(inlname) == 0)
		{
			printf("\nA Last Name is required!");
			printf("\nThis operation has been terminated!");
			return;
		}
		else cbinlname=SQL_NTS;

	printf("\nPlease enter a First Name (optional): ");
		gets(infname);
		if (strlen(infname) == 0) cbinfname=SQL_NULL_DATA;
		else cbinfname=SQL_NTS;

	printf("\nPlease enter a Gender (required): ");
		gets(ingender);
		if (strlen(ingender) == 0)
		{
			printf("\nA Gender is required!");
			printf("\nThis operation has been terminated!");
			return;
		}
		else cbingender=SQL_NTS;

	printf("\nPlease enter a VALID Major (required): ");
		gets(inmajor);
		if (strlen(inmajor) == 0)
		{
			printf("\nA Major is required!");
			printf("\nThis operation has been terminated!");
			return;
		}
		else cbinmajor=SQL_NTS;

	printf("\nPlease enter the birth date (format is mm/dd/yyyy) (optional): ");
		gets(inbirth_date);
		if (strlen(inbirth_date) == 0) cbinbirth_date=SQL_NULL_DATA;
		else cbinbirth_date=SQL_NTS;

	printf("\nPlease enter the amount of tuition paid (optional): ");
		gets(intuition_paid);
		if (strlen(intuition_paid) == 0) cbintuition_paid=SQL_NULL_DATA;
		else cbintuition_paid=SQL_NTS;

	printf("\nPlease enter the amount of the total tuition (optional): ");
		gets(intuition_total);
		if (strlen(intuition_total) == 0) cbintuition_total=SQL_NULL_DATA;
		else cbintuition_total=SQL_NTS;

	printf("\nPlease enter the starting date (format is mm/dd/yyyy) (optional): ");
		gets(instart_date);
		if (strlen(instart_date) == 0) cbinstart_date=SQL_NULL_DATA;
		else cbinstart_date=SQL_NTS;

	printf("\nPlease enter the graduation date (format is mm/dd/yyyy) (optional): ");
		gets(ingrad_date);
		if (strlen(ingrad_date) == 0) cbingrad_date=SQL_NULL_DATA;
		else cbingrad_date=SQL_NTS;

	printf("\nPlease enter the loan amount provide to student (optional): ");
		gets(inloan_amount);
		if (strlen(inloan_amount) == 0) cbinloan_amount=SQL_NULL_DATA;
		else cbinloan_amount=SQL_NTS;

	printf("\nPlease enter the degree program (U,M,P, or D) (required): ");
		gets(indegree_program);
		if (strlen(indegree_program) == 0)
		{
			printf("\nA Degree Program is required!");
			printf("\nThis operation has been terminated!");
			return;
		}
		else cbindegree_program=SQL_NTS;
	
	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);

	// bind program variables to SQL statement
	SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 9, 0, inssn, 10, &cbinssn);
	SQLBindParameter(hstmt1, 2, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 12, 0, infname, 13, &cbinfname);
	SQLBindParameter(hstmt1, 3, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 20, 0, inlname, 21, &cbinlname);
	SQLBindParameter(hstmt1, 4, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 1, 0, ingender, 2, &cbingender);
	SQLBindParameter(hstmt1, 5, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 4, 0, inmajor, 5, &cbinmajor);
	SQLBindParameter(hstmt1, 6, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 30, 0, inbirth_date, 31, &cbinbirth_date);
	SQLBindParameter(hstmt1, 7, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 20, 0, intuition_paid, 21, &cbintuition_paid);
	SQLBindParameter(hstmt1, 8, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 20, 0, intuition_total, 21, &cbintuition_total);
	SQLBindParameter(hstmt1, 9, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 30, 0, instart_date, 31, &cbinstart_date);
	SQLBindParameter(hstmt1, 10, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 30, 0, ingrad_date, 31, &cbingrad_date);
	SQLBindParameter(hstmt1, 11, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 20, 0, inloan_amount, 21, &cbinloan_amount);
	SQLBindParameter(hstmt1, 12, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 1, 0, indegree_program, 2, &cbindegree_program);
	
	// execute SQL insert statement
	if (SQLExecDirect(hstmt1,
			(SQLCHAR *)"INSERT INTO STUDENT_DB.DBO.STUDENT (SSN,FNAME,LNAME,GENDER,MAJOR,BIRTH_DATE, \
						TUITION_PAID,TUITION_TOTAL,START_DATE,GRAD_DATE,LOAN_AMOUNT,DEGREE_PROGRAM) \
						VALUES (?, ?, ?, ?, ?, ?, \
							CONVERT(NUMERIC(12,2),?), CONVERT(NUMERIC(12,2),?), \
							?, ?, CONVERT(NUMERIC(12,2),?), ?)", SQL_NTS) != SQL_SUCCESS)
	{
		// if insert fails, display warning message, rollback transaction
		warning_dump();
	}
	else
	{
		// if insert is successful, display number of rows inserted and commit transaction
		rowcount_and_commit();
	}

	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);

} /* end of insert_student */


/***************************************************************************************
	delete_student
	This function deletes a student from the student table
***************************************************************************************/
void delete_student(void)
{
	// request a social security number
	system("cls");
	printf("\nSTUDENT DELETION SCREEN\n\n");
	printf("\nPlease enter a Social Security Number: ");
	gets(inssn);

	// if no social security number entered, terminate operaton
	if (strlen(inssn) == 0)
	{
		printf("\nA Student Social Security Number was not entered!");
		printf("\nThis operation has been terminated!\n");
		return;
	}
		
	// set length of social security number
	if (strlen(inssn) == 0) cbinssn=SQL_NULL_DATA;
	else cbinssn=SQL_NTS;

	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);

	// bind social security number as input argument to SQL statement
	SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 9, 0, inssn, 10, &cbinssn);
	
	// execute SQL delete statement
	if (SQLExecDirect(hstmt1,
			(SQLCHAR *)"DELETE FROM STUDENT_DB.DBO.STUDENT WHERE SSN = ?", SQL_NTS) != SQL_SUCCESS)
	{
		// if delete fails, display warning message, rollback transaction
		warning_dump();
	}
	else
	{
		// if delete successful, display number of rows affected, commit transaction
		rowcount_and_commit();
	}

	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);

} /* end of delete_student */


/***************************************************************************************
	enroll_in_class
	This funtion enrolls a student in a class
***************************************************************************************/
void enroll_in_class(void)
{
	// request a social security number and class code
	system("cls");
	printf("\nSTUDENT CLASS ENROLLMENT SCREEN\n");
	printf("\nPlease enter a Social Security Number: ");
	gets(inssn);
	printf("\nPlease enter a Class Code: ");
	gets(inccode);

	// if the social security number or class code is missing, exit and return to menu
	if ( strlen(inssn) == 0 || strlen(inccode) == 0 ) 
	{
		printf("\nA Social Security Number and a Class Code are both required!");
		printf("\nThis operation has been terminated!\n");
		return;
	}

	// set the length of social security number and class code
	if (strlen(inssn) == 0) cbinssn=SQL_NULL_DATA;
	else cbinssn=SQL_NTS;

	if (strlen(inccode) == 0) cbinccode=SQL_NULL_DATA;
	else cbinccode=SQL_NTS;

	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);

	// bind social security number and class code to SQL statement
	SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 9, 0, inssn, 10, &cbinssn);
	
	SQLBindParameter(hstmt1, 2, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 4, 0, inccode, 5, &cbinccode);

	// execute the SQL insert statement
	if (SQLExecDirect(hstmt1,
			(SQLCHAR *)"INSERT INTO STUDENT_DB.DBO.GRADE (SSN, CCODE, GRADE) \
						VALUES (?, ?, NULL)", SQL_NTS) != SQL_SUCCESS)
	{
		// if insert fails, display warning message, rollback transaction
		warning_dump();
	}
	else
	{
		// if insert successful, display number of rows affected, commit transaction
		rowcount_and_commit();
	}

	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);

} /* end of enroll_in_class */


/***************************************************************************************
	remove_from_class
	This function removes a student from a class
***************************************************************************************/
void remove_from_class(void)
{
	// request a social security number and class code
	system("cls");
	printf("\nSTUDENT CLASS DELETION SCREEN\n");
	printf("\nPlease enter a Social Security Number: ");
	gets(inssn);
	printf("\nPlease enter a Class Code: ");
	gets(inccode);

	// if either social security number or class code was not entered, return to menu
	if ( strlen(inssn) == 0 || strlen(inccode) == 0 ) 
	{
		printf("\nA Social Security Number and a Class Code are both required!");
		printf("\nThis operation has been terminated!\n");
		return;
	}

	// set length of social security number and class code variables
	if (strlen(inssn) == 0) cbinssn=SQL_NULL_DATA;
	else cbinssn=SQL_NTS;

	if (strlen(inccode) == 0) cbinccode=SQL_NULL_DATA;
	else cbinccode=SQL_NTS;

	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);

	// bind social security number and class code to the SQL statement
	SQLBindParameter(hstmt1, 1, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 9, 0, inssn, 10, &cbinssn);
	
	SQLBindParameter(hstmt1, 2, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 4, 0, inccode, 5, &cbinccode);

	// execute the SQL delete statement
	if (SQLExecDirect(hstmt1,
			(SQLCHAR *)"DELETE FROM STUDENT_DB.DBO.GRADE WHERE SSN = ? AND CCODE = ?",
				SQL_NTS) != SQL_SUCCESS)
	{
		// if the delete fails, display warning message, rollback transaction
		warning_dump();
	}
	else
	{
		// if the delete is successful, display number of rows affected, commit transaction
		rowcount_and_commit();
	}

	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);

} /* end of remove_from_class */


/***************************************************************************************
	delete_dept
	This function deletes a department from the department table
***************************************************************************************/
void delete_dept(void)
{
	// request a department code
	system("cls");
	printf("\nDEPARTMENT DELETION SCREEN\n\n");
	printf("\nPlease enter a Department Code: ");
	gets(indept);
	
	// if no department code entered, return to menu
	if (strlen(indept) == 0)
	{
		printf("\nA Department Code is required to continue!");
		printf("\nThis operation has been terminated!\n");
		return;
	}
	
	// set the length of department code variable
	if (strlen(indept) == 0) cbindept=SQL_NULL_DATA;
	else cbindept=SQL_NTS;

	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);

	// bind department code to SQL statement
	SQLBindParameter(hstmt1, 1, SQL_PARAM_OUTPUT, SQL_C_LONG,
		SQL_INTEGER, 0, 0, &rowcount, 0, &cbrowcount);
	SQLBindParameter(hstmt1, 2, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 4, 0, indept, 5, &cbindept);
	
	// execute the SQL delete statement
	if (SQLExecDirect(hstmt1,
			(SQLCHAR *)"{? = call DEPT_DB.DBO.DELETE_DEPT(?)}",
					SQL_NTS) != SQL_SUCCESS)
	{
		// if the delete statement fails, display warning message, rollback transaction
		warning_dump();
	}
	else
	{
		// let user know number of rows affected
		printf("\n%d rows were affected by this operation!", rowcount);
	}

	// commit the transaction
	if (SQLTransact(henv1, hdbc1, SQL_COMMIT) != SQL_SUCCESS)
	{
		// if unable to commit, display error message, exit program
		error_dump();
	}
	
	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);

} /* end of delete_dept */


/***************************************************************************************
	insert_dept
	This function inserts a department into the department table
***************************************************************************************/
void insert_dept(void)
{
	// request department code and department name
	system("cls");
	printf("\nDEPARTMENT ADDITION SCREEN\n\n");
	printf("\nPlease enter a Department Code (required): ");
	gets(indept);
	printf("\nPlease enter a Department Name (required): ");
	gets(indname);
	
	// if department code and department name not entered, return to menu
	if ( strlen(indept) == 0 || strlen(indname) == 0 ) 
	{
		printf("\nA Department Code and a Department Name are both required!");
		printf("\nThis operation has been terminated!\n");
		return;
	}
	
	// set length of department code and department name variables
	if (strlen(indept) == 0) cbindept=SQL_NULL_DATA;
	else cbindept=SQL_NTS;

	if (strlen(indname) == 0) cbindname=SQL_NULL_DATA;
	else cbindname=SQL_NTS;

	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);

	// bind variables to SQL statement
	SQLBindParameter(hstmt1, 1, SQL_PARAM_OUTPUT, SQL_C_LONG,
		SQL_INTEGER, 0, 0, &rowcount, 0, &cbrowcount);
	SQLBindParameter(hstmt1, 2, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 4, 0, indept, 5, &cbindept);
	SQLBindParameter(hstmt1, 3, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 30, 0, indname, 31, &cbindname);

	// execute the SQL insert statement	
	if (SQLExecDirect(hstmt1,
			(SQLCHAR *)"{? = call DEPT_DB.DBO.INSERT_DEPT(?,?)}", SQL_NTS) != SQL_SUCCESS)
	{
		// if the insert statement fails, display warning message, rollback transaction
		warning_dump();
	}
	else
	{
		// let user know number of rows affected
		printf("\n%d rows were affected by this operation!", rowcount);
	}

	// commit the transaction
	if (SQLTransact(henv1, hdbc1, SQL_COMMIT) != SQL_SUCCESS)
	{
		// if unable to commit, display error message, exit program
		error_dump();
	}

	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);

} /* end of insert_dept */


/***************************************************************************************
	delete_class
	This function deletes a class from the class table
***************************************************************************************/
void delete_class(void)
{
	// request a class code
	system("cls");
	printf("\nCLASS DELETION SCREEN\n\n");
	printf("\nPlease enter a Class Code: ");
	gets(inccode);

	// if no class code is entered, return to the menu
	if (strlen(inccode) == 0)
	{
		printf("\nA Class Code is required to continue!");
		printf("\nThis operation has been terminated!\n");
		return;
	}

	// set the length of the class code variable
	if (strlen(inccode) == 0) cbinccode=SQL_NULL_DATA;
	else cbinccode=SQL_NTS;
	
	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);

	// bind the variables to the SQL statement
	SQLBindParameter(hstmt1, 1, SQL_PARAM_OUTPUT, SQL_C_LONG,
		SQL_INTEGER, 0, 0, &rowcount, 0, &cbrowcount);
	SQLBindParameter(hstmt1, 2, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 4, 0, inccode, 5, &cbinccode);
	
	// execute the SQL delete statement
	if (SQLExecDirect(hstmt1,
			(SQLCHAR *)"{? = call DEPT_DB.DBO.DELETE_CLASS(?)}",
					SQL_NTS) != SQL_SUCCESS)
	{
		// if the delete statement fails, display warning message, rollback transaction
		warning_dump();
	}
	else
	{
		// let user know number of rows affected
		printf("\n%d rows were affected by this operation!", rowcount);
	}

	// commit the transaction
	if (SQLTransact(henv1, hdbc1, SQL_COMMIT) != SQL_SUCCESS)
	{
		// if unable to commit, display error message, exit program
		error_dump();
	}

	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);

} /* end of delete_class */


/***************************************************************************************
	insert_class
	This function inserts a class into the class table
***************************************************************************************/
void insert_class(void)
{
	// request class information
	system("cls");
	printf("\nCLASS ADDITION SCREEN\n\n");
	printf("\nPlease enter a Class Code (required): ");
	gets(inccode);
	printf("\nPlease enter a Class Name (required): ");
	gets(incname);
	printf("\nPlease enter a Department Code (required): ");
	gets(indept);
	printf("\nPlease enter a room number for the class (optional): ");
	gets(inroom);
	printf("\nPlease enter a prerequisite Class Code for the class (optional): ");
	gets(inprereq);
	
	// if class code, class name, or department code are not entered, return to menu
	if ( strlen(inccode) == 0 || strlen(incname) == 0 || strlen(indept) == 0 )
	{
		printf("\nA Class Code, Class Name, and Department Code are all required!");
		printf("\nThis operation has been terminated!\n");
		return;
	}
	
	// set length of class variables
	if (strlen(inccode) == 0) cbinccode=SQL_NULL_DATA;
	else cbinccode=SQL_NTS;

	if (strlen(incname) == 0) cbincname=SQL_NULL_DATA;
	else cbincname=SQL_NTS;

	if (strlen(indept) == 0) cbindept=SQL_NULL_DATA;
	else cbindept=SQL_NTS;

	if (strlen(inroom) == 0) cbinroom=SQL_NULL_DATA;
	else cbinroom=SQL_NTS;

	if (strlen(inprereq) == 0) cbinprereq=SQL_NULL_DATA;
	else cbinprereq=SQL_NTS;
	
	// allocate ODBC statement handle
	SQLAllocStmt(hdbc1, &hstmt1);

	// bind variables to SQL statement
	SQLBindParameter(hstmt1, 1, SQL_PARAM_OUTPUT, SQL_C_LONG,
		SQL_INTEGER, 0, 0, &rowcount, 0, &cbrowcount);
	SQLBindParameter(hstmt1, 2, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 4, 0, inccode, 5, &cbinccode);
	SQLBindParameter(hstmt1, 3, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 30, 0, incname, 31, &cbincname);
	SQLBindParameter(hstmt1, 4, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 4, 0, indept, 5, &cbindept);
	SQLBindParameter(hstmt1, 5, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 6, 0, inroom, 7, &cbinroom);
	SQLBindParameter(hstmt1, 6, SQL_PARAM_INPUT, SQL_C_CHAR,
		SQL_VARCHAR, 4, 0, inprereq, 5, &cbinprereq);

	// execute the SQL insert statement
	if (SQLExecDirect(hstmt1,
			(SQLCHAR *)"{? = call DEPT_DB.DBO.INSERT_CLASS(?,?,?,?,?)}", SQL_NTS) != SQL_SUCCESS)
	{
		// if the statement fails, display warning message, rollback transaction
		warning_dump();
	}
	else
	{
		// let user know number of rows affected
		printf("\n%d rows were affected by this operation!", rowcount);
	}

	// commit the transaction
	if (SQLTransact(henv1, hdbc1, SQL_COMMIT) != SQL_SUCCESS)
	{
		// if unable to commit, display error message, exit program
		error_dump();
	}

	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);

} /* end of insert_class */


/***************************************************************************************
	logon
	This function logs on to the database
***************************************************************************************/

void logon(void)
{
	// allocate an ODBC enviroment handle for a SQL Server connection
	SQLAllocEnv(&henv1);

	// obtain an ODBC connection handle
	SQLAllocConnect(henv1,&hdbc1);

	// connect to the requested SQL Server database driver (student data)
	rc1 = SQLConnect(hdbc1,
				(SQLCHAR *) odbc_dsn, (SQLSMALLINT) SQL_NTS,
				(SQLCHAR *) user_name, (SQLSMALLINT) SQL_NTS,
				(SQLCHAR *) user_password, (SQLSMALLINT) SQL_NTS);
	
	// if unable to connect, display error message and exit program
	if (rc1 != SQL_SUCCESS && rc1 != SQL_SUCCESS_WITH_INFO)
	{
		printf("\nUnable to log on to SQL Server ...");
		error_dump();
	}
	else
	{
		if ( SQLGetInfo(hdbc1, SQL_DBMS_NAME, dbms_name, 81, NULL) != SQL_SUCCESS )
		{
			// if this fails, display error message, exit program
			error_dump();
		}
		printf("\nYou have successfully logged on to %s", dbms_name);
	}
	
	// turn off autocommit, all transactions must be explicitly commited or rolled back
	if (SQLSetConnectOption(hdbc1, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF) != SQL_SUCCESS)
	{
		// if this is not possible, display error message, exit program
		error_dump();
	}


} /* end of logon */


/***************************************************************************************
	logoff
	This function logs off of the database
***************************************************************************************/

void logoff(void)
{
	// logs off of database
	printf("\nLogging off and releasing resources ...\n");
	SQLFreeStmt(hstmt1,SQL_DROP);	/* Free statement handle */
	SQLDisconnect(hdbc1);			/* Disconnect from SQL Server */
	SQLFreeConnect(hdbc1);			/* Free connection handle */
	SQLFreeEnv(henv1);				/* Free environment handle */
	exit(0);
} /* end of logoff */


/***************************************************************************************
	error_dump
	This is the fatal error handler function
***************************************************************************************/
void error_dump(void)
{
	// error message variables
	UCHAR szSqlState[6];
	UCHAR szErrorMsg[SQL_MAX_MESSAGE_LENGTH];
	SDWORD ErrorCode;
	SWORD ErrMsgLen;

	// call ODBC error message function
	SQLError(henv1, hdbc1, hstmt1, szSqlState, &ErrorCode, szErrorMsg,
				SQL_MAX_MESSAGE_LENGTH-1, &ErrMsgLen);

	// display error messages
	printf("\nA SQL Server error occured, please review below:\n");
	printf("\nSQLState: %s\n", szSqlState);
	printf("\nErrorCode: %d\n", ErrorCode);
	printf("\nMessage: %s\n", szErrorMsg);

	// rollback any outstanding transactions
	SQLTransact(henv1, hdbc1, SQL_ROLLBACK);

	// logoff of the database
	logoff();

} /* end of error_dump */


/***************************************************************************************
	warning_dump
	This is the non-fatal error handler function
***************************************************************************************/
void warning_dump(void)
{
	// error message variables
	UCHAR szSqlState[6];
	UCHAR szErrorMsg[SQL_MAX_MESSAGE_LENGTH];
	SDWORD ErrorCode;
	SWORD ErrMsgLen;

	// call ODBC error message function
	SQLError(henv1, hdbc1, hstmt1, szSqlState, &ErrorCode, szErrorMsg,
				SQL_MAX_MESSAGE_LENGTH-1, &ErrMsgLen);

	// display error messages
	printf("\nA SQL Server error occured, please review below:\n");
	printf("\nSQLState: %s\n", szSqlState);
	printf("\nErrorCode: %d\n", ErrorCode);
	printf("\nMessage: %s\n", szErrorMsg);

	// rollback any outstanding transactions
	if (SQLTransact(henv1, hdbc1, SQL_ROLLBACK) != SQL_SUCCESS)
	{
		// if the rollback fails, display error message, exit program
		error_dump();

	}

	// release the ODBC statement handle
	SQLFreeStmt(hstmt1,SQL_DROP);
} /* warning_dump */



/***************************************************************************************
	rowcount_and_commit
	This function counts number of rows affected by dml and commits transactions
***************************************************************************************/
void rowcount_and_commit(void)
{
	// find number of rows affected by insert, update, or delete
	if (SQLRowCount(hstmt1,&rowcount) != SQL_SUCCESS)
	{
		// if this fails, display error message, exit program
		error_dump();
	}
	else
	{
		// if no rows were affected, let user know
		if (rowcount == 0)
			{
			printf("\nNo rows were affected by this operation!");
		}
		else
		{
			// let user know number of rows affected
			printf("\n%d rows were affected by this operation!", rowcount);
		}
	}

	// commit the transaction
	if (SQLTransact(henv1, hdbc1, SQL_COMMIT) != SQL_SUCCESS)
	{
		// if unable to commit, display error message, exit program
		error_dump();
	}
} /* end of rowcount_and_commit */
