/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.03.0110 */
/* at Wed Feb 11 11:57:34 1998
 */
/* Compiler settings for AtlCont.idl:
    Oic (OptLev=i1), W1, Zp8, env=Win32, ms_ext, c_ext
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

const IID IID_IAtlCont = {0xBFD466C3,0x376C,0x11D0,{0x96,0xB5,0x00,0xA0,0xC9,0x0D,0xC9,0x4B}};


const IID LIBID_ATLCONTLib = {0x8F3C5551,0x376C,0x11D0,{0x96,0xB5,0x00,0xA0,0xC9,0x0D,0xC9,0x4B}};


const CLSID CLSID_CAtlCont = {0xBFD466C2,0x376C,0x11D0,{0x96,0xB5,0x00,0xA0,0xC9,0x0D,0xC9,0x4B}};


#ifdef __cplusplus
}
#endif

