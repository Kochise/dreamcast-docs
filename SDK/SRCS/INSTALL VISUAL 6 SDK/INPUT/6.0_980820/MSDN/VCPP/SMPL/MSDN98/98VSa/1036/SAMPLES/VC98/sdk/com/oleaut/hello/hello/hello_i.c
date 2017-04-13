/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 02:37:13 1998
 */
/* Compiler settings for hello.odl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
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

const IID LIBID_Hello = {0xF37C8060,0x4AD5,0x101B,{0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1}};


const IID IID_IHello = {0xF37C8062,0x4AD5,0x101B,{0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1}};


const CLSID CLSID_Hello = {0xF37C8061,0x4AD5,0x101B,{0xB8,0x26,0x00,0xDD,0x01,0x10,0x3D,0xE1}};


#ifdef __cplusplus
}
#endif

