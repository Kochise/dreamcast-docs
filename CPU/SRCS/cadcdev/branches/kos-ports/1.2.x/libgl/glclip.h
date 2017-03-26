/* KallistiGL for KOS ##version##
 	
	Near Z Clipper
	(c) Trilinear
	Trilinear@hotmail.com
	
   $Id: glclip.h,v 1.2 2002/06/28 04:47:02 axlen Exp $
*/

#ifndef __GLCLIP_H
#define __GLCLIP_H

#include <GL/gl.h>
#include "glinternal.h"

#define MAXZ 0.0001f /* if z is negative, it is behind the camera */

inline void CopyV(gl_vertex_t *vertold, gl_vertex_t *vertnew) {
	
/*	memcpy(vertnew, vertold, sizeof(gl_vertex_t)); */

	vertnew->flags = vertold->flags;
	vertnew->x = vertold->x; 
	vertnew->y = vertold->y; 
	vertnew->z = vertold->z; 
	vertnew->w = vertold->w; 
	vertnew->u = vertold->u;
	vertnew->v = vertold->v;
	vertnew->argb = vertold->argb;
	vertnew->oargb = vertold->oargb;

}

inline void FindZ(gl_vertex_t *vertnew, gl_vertex_t *vert1, gl_vertex_t *vert2) {

	float diffz;
	/* z is indp variable because we know it changes, thus no div 0 error */
	vertnew->z = gl_frustum.znear;
	vertnew->w = vert1->w + (gl_frustum.znear-vert1->z)*(vert1->w - vert2->w)/(vert1->z - vert2->z);
	vertnew->x = vert1->x + (gl_frustum.znear-vert1->z)*(vert1->x - vert2->x)/(vert1->z - vert2->z);
	vertnew->y = vert1->y + (gl_frustum.znear-vert1->z)*(vert1->y - vert2->y)/(vert1->z - vert2->z);

	diffz = (vert1->z-vertnew->z)/(vert1->z-vert2->z);
	vertnew->u = (diffz)*vert2->u + (1.0f-diffz)*vert1->u;
	vertnew->v = (diffz)*vert2->v + (1.0f-diffz)*vert1->v;
}

inline int ZClipTex(gl_vertex_t *vert) 
	/* returns 0 for full clip, 3 for triangle output and 4 for quad output
	   based on sutherland-hodgeman clip algorithm */
{
		int i,j;
	gl_vertex_t tempvert[4];

	if (vert[0].z < gl_frustum.znear || vert[1].z < gl_frustum.znear || vert[2].z < gl_frustum.znear) {/* one or more parts behind camera */
		j=0;
		CopyV(&vert[0],&vert[3]);/* copy first to next after last to make cyclic */
		for(i=0; i<3; i++) {
			if (vert[i].z >= gl_frustum.znear && vert[i+1].z >= gl_frustum.znear) { /* both in */
				CopyV(&vert[i],&tempvert[j]);
				j++;
			}else if (vert[i].z < gl_frustum.znear && vert[i+1].z >= gl_frustum.znear) {/* this out, next in */
				CopyV(&vert[i],&tempvert[j]);
				FindZ(&tempvert[j],&vert[i],&vert[i+1]);
				j++;
			}else if (vert[i].z >= gl_frustum.znear && vert[i+1].z < gl_frustum.znear) {/* this in, next out */
				CopyV(&vert[i],&tempvert[j]);
				CopyV(&vert[i+1],&tempvert[j+1]);
				FindZ(&tempvert[j+1],&vert[i],&vert[i+1]);
				j+=2;
			}/* both out, ignore */
		}


		switch (j) {
			case 3:
				CopyV(&tempvert[0],&vert[0]);
				CopyV(&tempvert[1],&vert[1]);
				CopyV(&tempvert[2],&vert[2]);
				return 3;
			case 4:
				CopyV(&tempvert[0],&vert[0]);
				CopyV(&tempvert[1],&vert[1]);
				CopyV(&tempvert[2],&vert[3]);
				CopyV(&tempvert[3],&vert[2]);
				return 4;
		}/* if j==0 we return 0 which we are about to do anyway */

	}else{/* is all in front of camera */
		return 3;
	}

	return 0;/* if it isn't one of the above it is an invalid poly or completely behind camera */
}

#endif	/* __GLCLIP_H */

