/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.02.88 */
/* at Tue Jun 15 19:55:09 1999
 */
/* Compiler settings for .\ieceui.idl:
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

const IID IID_Iieui = {0xB048FC80,0x122D,0x11D3,{0x95,0x90,0x00,0xC0,0x4F,0xAE,0xA6,0xD4}};


const IID LIBID_IECEUILib = {0xB048FC72,0x122D,0x11D3,{0x95,0x90,0x00,0xC0,0x4F,0xAE,0xA6,0xD4}};


const CLSID CLSID_ieui = {0xB048FC81,0x122D,0x11D3,{0x95,0x90,0x00,0xC0,0x4F,0xAE,0xA6,0xD4}};


#ifdef __cplusplus
}
#endif

