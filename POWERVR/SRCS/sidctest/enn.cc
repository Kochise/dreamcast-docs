/* enn.cc - Test 3dobject
** (c)2001 Paul Boese
*/

#include "enn.h"
extern "C" {
    #include "data/enn_data.h"
    }
    
void Enn::draw()
	{
	int i;
	glBegin(GL_TRIANGLES);
	glRotatef(F_PI, 0.0f, 0.0f, 1.0f);
	glDisable(GL_KOS_AUTO_UV);
	glBindTexture( GL_TEXTURE_2D, texture);
	glColor3f(red, green, blue);
	
	/* Faces */
	for (i=0; i<ENN_FACE_IDXS; i+=4) {
		/* Note this is reading the face indexs backwards
		   so that the face vertices are output in clockwise
		   order. */
		glTexCoord2f(
			enn_uv[i+2][0], 
			1-enn_uv[i+2][1]); /* XXX Ugly Hack ???*/
		glVertex3f(
			enn_coords[enn_face_idx[i+2]][0],
			enn_coords[enn_face_idx[i+2]][1],
			enn_coords[enn_face_idx[i+2]][2]);
		
		glTexCoord2f(
			enn_uv[i+1][0],
			1-enn_uv[i+1][1]); /* XXX Ugly Hack ???*/
		glVertex3f(
			enn_coords[enn_face_idx[i+1]][0],
			enn_coords[enn_face_idx[i+1]][1],
			enn_coords[enn_face_idx[i+1]][2]);
		
		glTexCoord2f(
			enn_uv[i][0],
			1-enn_uv[i][1]); /* XXX Ugly Hack ???*/
		glVertex3f(
			enn_coords[enn_face_idx[i]][0],
			enn_coords[enn_face_idx[i]][1],
			enn_coords[enn_face_idx[i]][2]);
		}
	glEnd();
	}

/* vi:tabstop=4
*/
