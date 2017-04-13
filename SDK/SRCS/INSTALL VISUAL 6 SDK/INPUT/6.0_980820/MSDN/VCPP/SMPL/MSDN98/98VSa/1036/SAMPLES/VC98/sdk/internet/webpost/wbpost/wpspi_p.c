/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:02:38 1998
 */
/* Compiler settings for wpspi.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "wpspi.h"

#define TYPE_FORMAT_STRING_SIZE   1                                 
#define PROC_FORMAT_STRING_SIZE   1                                 

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


/* Standard interface: __MIDL_itf_wpspi_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IWPSiteW, ver. 0.0,
   GUID={0x5261F720,0x6C4C,0x11CF,{0x86,0xB1,0x00,0xAA,0x00,0x60,0xF8,0x6C}} */


/* Object interface: IWPProvider, ver. 0.0,
   GUID={0xCB1D5316,0x30F6,0x11D0,{0xAD,0x03,0x00,0xAA,0x00,0xA2,0x19,0xAA}} */

#pragma data_seg(".rdata")

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   more than 32 methods in the interface.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {

			0x0
        }
    };

const CInterfaceProxyVtbl * _wpspi_ProxyVtblList[] = 
{
    0
};

const CInterfaceStubVtbl * _wpspi_StubVtblList[] = 
{
    0
};

PCInterfaceName const _wpspi_InterfaceNamesList[] = 
{
    0
};


#define _wpspi_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _wpspi, pIID, n)

int __stdcall _wpspi_IID_Lookup( const IID * pIID, int * pIndex )
{
    return 0;
}

const ExtendedProxyFileInfo wpspi_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _wpspi_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _wpspi_StubVtblList,
    (const PCInterfaceName * ) & _wpspi_InterfaceNamesList,
    0, // no delegation
    & _wpspi_IID_Lookup, 
    0,
    1
};
