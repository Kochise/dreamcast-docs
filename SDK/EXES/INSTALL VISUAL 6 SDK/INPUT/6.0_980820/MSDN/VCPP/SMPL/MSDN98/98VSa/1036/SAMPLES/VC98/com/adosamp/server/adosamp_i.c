/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.03.0110 */
/* at Wed Feb 04 11:49:00 1998
 */
/* Compiler settings for .\ADOSamp.idl:
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

const IID IID_IADOTier = {0x7A319993,0x48C0,0x11D0,{0xAE,0x70,0x00,0xC0,0x4F,0xD7,0xD0,0x6E}};


const IID LIBID_ADOSAMPLib = {0x7A319991,0x48C0,0x11D0,{0xAE,0x70,0x00,0xC0,0x4F,0xD7,0xD0,0x6E}};


const CLSID CLSID_CADOTier = {0x7A319997,0x48C0,0x11D0,{0xAE,0x70,0x00,0xC0,0x4F,0xD7,0xD0,0x6E}};


#ifdef __cplusplus
}
#endif

