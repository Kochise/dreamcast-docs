/* KallistiOS 1.1.6

   precompiler.h
   (c)2000 Dan Potter

   $Id: precompiler.h,v 1.2 2002/01/05 07:23:32 bardtx Exp $
*/


#ifndef __PRECOMPILER_H
#define __PRECOMPILER_H

#include <sys/cdefs.h>
__BEGIN_DECLS

/* Resets the precompiler for another scene/object */
void pc_reset(int size);

/* Appends a vertex to the scene buffer */
void pc_append(const void *data);

/* Transforms all verteces in the scene buffer */
void pc_transform_all();

/* Submits all verteces in the scene buffer to the TA */
void pc_submit_all();

/* Init */
void pc_init();

/* Shutdown */
void pc_shutdown();

__END_DECLS

#endif	/* __PRECOMPILER_H */

