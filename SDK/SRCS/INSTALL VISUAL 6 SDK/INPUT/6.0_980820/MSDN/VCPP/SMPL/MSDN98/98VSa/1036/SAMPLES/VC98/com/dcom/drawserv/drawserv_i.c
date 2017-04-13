/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.03.0110 */
/* at Wed Feb 11 11:54:06 1998
 */
/* Compiler settings for DrawServ.idl:
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

const IID IID_IDrawServ = {0x330E9E75,0xDF48,0x11CF,{0x8E,0x2C,0x00,0xA0,0xC9,0x0D,0xC9,0x4B}};


const IID LIBID_DRAWSERVLib = {0x330E9E73,0xDF48,0x11CF,{0x8E,0x2C,0x00,0xA0,0xC9,0x0D,0xC9,0x4B}};


const CLSID CLSID_CDrawServ = {0x330E9E79,0xDF48,0x11CF,{0x8E,0x2C,0x00,0xA0,0xC9,0x0D,0xC9,0x4B}};


#ifdef __cplusplus
}
#endif

