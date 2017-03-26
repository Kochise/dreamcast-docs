#ifndef _KGL_features_h_
#define _KGL_features_h_

/* It is possible to manipulate (at compile time) features in this
   header file. */


/* max. number of Displaylists */

#define MAX_DISPLAY_LISTS 512

/* max. opcode sizes of one Displaylist */

#define OP_BUFFER_MAX_SIZE 512


/* Size of max verticies in a glBegin()...glEnd() block */

#define VBUF_SIZE (1024*8)

#endif /* _KGL_features_h_ */
