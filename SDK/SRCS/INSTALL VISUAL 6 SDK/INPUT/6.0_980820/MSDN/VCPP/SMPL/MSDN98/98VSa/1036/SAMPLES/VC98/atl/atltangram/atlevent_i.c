/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.01.76 */
/* at Mon Dec 08 20:38:21 1997
 */
/* Compiler settings for D:\ATL25\samples\ATLTangram\AtlEvent_i.idl:
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

const IID IID_IATLTangramModelEvent = {0x4A6E83B0,0xB0F4,0x11d0,{0xB6,0x9F,0x00,0xA0,0xC9,0x03,0x48,0x7A}};


#ifdef __cplusplus
}
#endif

