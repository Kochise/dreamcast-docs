/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 02:34:57 1998
 */
/* Compiler settings for psperf.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_ICOMPerformance = {0xDDC68871,0xE08E,0x11cf,{0xA5,0x35,0x00,0xAA,0x00,0x61,0x5B,0x03}};


const CLSID CLSID_TestCOMPerformance = {0xDDC68870,0xE08E,0x11cf,{0xA5,0x35,0x00,0xAA,0x00,0x61,0x5B,0x03}};


#ifdef __cplusplus
}
#endif

