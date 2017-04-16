/* this ALWAYS GENERATED file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 2.00.0102 */
/* at Wed Oct 18 18:02:19 1995
 */
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef IID_DEFINED
#define IID_DEFINED

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // IID_DEFINED

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IDB = {0x30DF3432,0x0266,0x11cf,{0xBA,0xA6,0x00,0xAA,0x00,0x3E,0x0E,0xED}};


const IID IID_IDBAccess = {0x30DF3433,0x0266,0x11cf,{0xBA,0xA6,0x00,0xAA,0x00,0x3E,0x0E,0xED}};


const IID IID_IDBManage = {0x30DF3434,0x0266,0x11cf,{0xBA,0xA6,0x00,0xAA,0x00,0x3E,0x0E,0xED}};


const IID IID_IDBInfo = {0x30DF3435,0x0266,0x11cf,{0xBA,0xA6,0x00,0xAA,0x00,0x3E,0x0E,0xED}};


#ifdef __cplusplus
}
#endif

