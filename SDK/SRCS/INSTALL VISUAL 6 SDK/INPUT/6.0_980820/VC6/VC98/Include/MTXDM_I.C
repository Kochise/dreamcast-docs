/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.01.75 */
/* at Thu Sep 11 16:03:06 1997
 */
/* Compiler settings for mtxdm.idl:
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

const IID IID_IDispenserManager = {0x5cb31e10,0x2b5f,0x11cf,{0xbe,0x10,0x00,0xaa,0x00,0xa2,0xfa,0x25}};


const IID IID_IHolder = {0xbf6a1850,0x2b45,0x11cf,{0xbe,0x10,0x00,0xaa,0x00,0xa2,0xfa,0x25}};


const IID IID_IDispenserDriver = {0x208b3651,0x2b48,0x11cf,{0xbe,0x10,0x00,0xaa,0x00,0xa2,0xfa,0x25}};


#ifdef __cplusplus
}
#endif

