// NT related defines (used in original NT port)
//
typedef DWORD						THREAD; 
#define SRV_INDEFINITE_WAIT 	-1
#define SEL                 	char
#define HSEM                	char

// define constants
//
#define DEFAULT_SERVER_NAME "Server"

// Values for TDSVERSION - 4.2.0.0
//
#define SRV_TDSV1   4
#define SRV_TDSV2   2
#define SRV_TDSV3   0
#define SRV_TDSV4   0

// Values for PROGVERSION - 0.6.0.0
//
#define SRV_SRVV1   0
#define SRV_SRVV2   6
#define SRV_SRVV3   0
#define SRV_SRVV4   0

// Sizes of fields in loginrec
#define SRV_MAXNAME 30	// maximum login names
#define SRV_MAXREM  255 // maximum length of remote password name
#define SRV_MAXFILENAME 64 // maximum size of filename
#define SRV_PKTLEN  6   // maximum size of packet size string
#define SRV_HOSTIDLEN	8	// maximum size of host id field

// define model
//
#if !defined( FAR )

#define FAR far

#endif

#if !defined( CDECL )

#define CDECL   cdecl

#endif

#define SRVAPI  FAR CDECL

typedef int SRVRETCODE;        // SUCCEED or FAIL

// values for linterface type

#define LDEFSQL     0
#define LXSQL       1
#define LSQL        2
#define LSQL2_1     3
#define LSQL2_2     4

// values for ltype field

#define LSERVER     0x1
#define LREMUSER    0x2
#define LSECURE 	  0x8

// possible storage types
//
#define INT4_LSB_HI    0   // LSB is hi byte (e.g. 68000)
#define INT4_LSB_LO    1   // LSB is low byte (e.g. Intel)
#define INT2_LSB_HI    2   // LSB is hi byte (e.g. 68000)
#define INT2_LSB_LO    3   // LSB is low byte (e.g. Intel)
#define FLT_IEEE       4   // IEEE 754 floating point
#define FLT_VAXD       5   // VAX 'D' floating point format
#define CHAR_ASCII     6   // ASCII character set
#define CHAR_EBCDID    7   // EBCDIC character set
#define TWO_I4_LSB_HI  8   // LSB is hi byte (e.g. 68000)
#define TWO_I4_LSB_LO  9   // LSB is low byte (e.g. Intel)
#define FLT_IEEE_LO	10  // LSB is low byte (e.g. MSDOS)
#define FLT_ND5000		11  // ND5000 float format
#define FLT4_IEEE_HI	12  // IEEE 4-byte floating point, LSB is hi byte
#define FLT4_IEEE_LO	13  // IEEE 4-byte floating point, LSB is lo byte
#define FLT4_VAXF		14  // VAX "F" floating point format
#define FLT4_ND50004	15  // ND5000 4-byte float format
#define TWO_I2_LSB_HI	16  // LSB is hi byte
#define TWO_I2_LSB_LO	17  // LSB is lo byte
#define MAX_REQUEST    17

/* values for Sun
** lint2 = INT2_LSB_HI
** lint4 = int4_LSB_HI
** lchar = CHAR_ASCII
** lflt  = FLT_IEEE
** ldate = TWO_I4_LSB_HI
*/

/* values for VAX
** lint2 = INT2_LSB_LO
** lint4 = int4_LSB_LO
** lchar = CHAR_ASCII
** lflt  = FLT_VAXD
** ldate = TWO_I4_LSB_LO
*/

/* values for Intel
** lint2 = INT2_LSB_LO
** lint4 = int4_LSB_LO
** lchar = CHAR_ASCII
** lflt  = FLT_IEEE
** ldate = TWO_I4_LSB_LO
*/

// DBMS type for dbwhichDBMS
//
#define DB2            1
#define SQL_SERVER     2
#define GDK_SERVER     3
#define DBASE          4
#define SQLDS          5
#define EEDM           6
#define AS400          7
#define SQLBASE        8
#define ORACLE         9
#define INGRES         10
#define CL1            11
#define BLUEPRINT      12
#define RDB            13
#define NONSTOP_SQL    14
#define TERADATA       15
#define INFORMIX       16
#define XDB            17
#define IDMS_R         18
#define HPIMAGE        19
#define BRITTON_LEE    20
#define VSAM           21

