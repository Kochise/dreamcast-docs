/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.01.75 */
/* at Thu Sep 11 16:03:07 1997
 */
/* Compiler settings for mtsgrp.idl:
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

const IID IID_IMtsGrp = {0x4B2E958C,0x0393,0x11D1,{0xB1,0xAB,0x00,0xAA,0x00,0xBA,0x32,0x58}};


const IID LIBID_MTSGRPLib = {0x4B2E957D,0x0393,0x11D1,{0xB1,0xAB,0x00,0xAA,0x00,0xBA,0x32,0x58}};


const CLSID CLSID_MtsGrp = {0x4B2E958D,0x0393,0x11D1,{0xB1,0xAB,0x00,0xAA,0x00,0xBA,0x32,0x58}};


#ifdef __cplusplus
}
#endif

