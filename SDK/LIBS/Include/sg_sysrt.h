/********************************************************************
 *  Shinobi Library
 *  Copyright (c) 1998 SEGA
 *
 *  Library : call global constructor / destructor
 *  File    : sg_sysrt.h
 *  Date    : 1998-10-26
 *  Version : 1.00
 *
 ********************************************************************/

#ifndef _SG_SYSRT_H_
#define _SG_SYSRT_H_

#ifdef __cplusplus
extern "C"{                                 /* Only C++ Interface  */

void syStartGlobalConstructor( void ) ;
void syStartGlobalDestructor ( void ) ;

}
#endif /* __cplusplus  */
#endif /* _SG_SYCFG_H_ */
/****************************************** End of sg_sysrt.h *******/
