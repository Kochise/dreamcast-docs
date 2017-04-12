#if !defined( DBTYPEDEFS )  // So we don't conflict with DBLIB definitions
//
// define data types
//
typedef unsigned char DBBOOL;
typedef unsigned char DBBYTE;
typedef unsigned char DBTINYINT;
typedef short DBSMALLINT;
typedef unsigned short DBUSMALLINT;
typedef long DBINT;
typedef char DBCHAR;
typedef unsigned char DBBINARY;
typedef unsigned char DBBIT;
typedef double DBFLT8;

#ifndef ODBCVER
typedef int RETCODE;        // SUCCEED or FAIL
#endif

typedef struct srv_datetime { // DataServer datetime type 
    long dtdays;            // number of days since 1/1/1900
    unsigned long dttime;   // number 300th second since mid

} DBDATETIME;

typedef struct srv_money {   // DataServer money type 
    long mnyhigh;
    unsigned long mnylow;

} DBMONEY;

#ifdef _OS2
typedef unsigned short BOOL;
#else
typedef int     	BOOL;
#endif
typedef unsigned char BYTE;

// These are version 4.2 additions                                      
//
typedef float DBFLT4;
typedef long DBMONEY4;

#define DBREAL  DBFLT4
typedef struct dbdatetime4 {
    unsigned short numdays; // No of days since Jan-1-1900             
    unsigned short nummins; // No. of minutes since midnight           
} DBDATETIM4;

/* DBDATEREC structure used by dbdatecrack. This is a version 4.2 addition */
typedef struct dbdaterec
{
    int     year;	    /* 1753 - 9999 */
    int     quarter;	    /* 1 - 4 */
    int     month;	    /* 1 - 12 */
    int     dayofyear;	    /* 1 - 366 */
    int     day;	    /* 1 - 31 */
    int     week;	    /* 1 - 54 (for leap years) */
    int     weekday;	    /* 1 - 7  (Mon - Sun) */
    int     hour;	    /* 0 - 23 */
    int     minute;	    /* 0 - 59 */
    int     second;	    /* 0 - 59 */
    int     millisecond;    /* 0 - 999 */
} DBDATEREC;

#define MAXNUMERICLEN	16

// These are version 6.0 additions
//

// Defined identically in OLE-DB header. If OLE-DB header previously included
// skip redefinition.
//
#if !defined (__oledb_h__)
typedef struct dbnumeric
{
	BYTE precision;
	BYTE scale;
	BYTE sign;
	BYTE val[MAXNUMERICLEN];
} DBNUMERIC;
#endif // !defined (__oledb_h__)

typedef DBNUMERIC DBDECIMAL;


#endif  // #if !defined( DBTYPEDEFS )

#if !defined( DBPROGNLEN )

#define DBPROGNLEN  10

#endif
