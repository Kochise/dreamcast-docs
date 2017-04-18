/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:02:38 1998
 */
/* Compiler settings for wpspi.idl:
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

const IID IID_IWPSiteW = {0x5261F720,0x6C4C,0x11CF,{0x86,0xB1,0x00,0xAA,0x00,0x60,0xF8,0x6C}};


const IID IID_IWPProvider = {0xCB1D5316,0x30F6,0x11D0,{0xAD,0x03,0x00,0xAA,0x00,0xA2,0x19,0xAA}};


#ifdef __cplusplus
}
#endif

