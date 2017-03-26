/* xxx.cc - Test 3dobject
** (c)2001 Paul Boese
*/

#include "xxx.h"
extern "C" {
    #include "data/xxx_data.h"
    }
    
void Xxx::draw()
	{
	int i;
	glBegin(GL_TRIANGLES);
	glRotatef(F_PI, 0.5f, 1.0f, 0.5f);
	glDisable(GL_KOS_AUTO_UV);
	glBindTexture( GL_TEXTURE_2D, texture);
	glColor3f(red, green, blue);
	
	/* Faces */
	for (i=0; i<XXX_FACE_IDXS; i+=4) {
		/* Note this is reading the face indexs backwards
		   so that the face vertices are output in clockwise
		   order. */
		glTexCoord2f(
			xxx_uv[i+2][0], 
			1-xxx_uv[i+2][1]); /* XXX Ugly Hack */
		glVertex3f(
			xxx_coords[xxx_face_idx[i+2]][0],
			xxx_coords[xxx_face_idx[i+2]][1],
			xxx_coords[xxx_face_idx[i+2]][2]);
		
		glTexCoord2f(
			xxx_uv[i+1][0],
			1-xxx_uv[i+1][1]); /* XXX Ugly Hack */
		glVertex3f(
			xxx_coords[xxx_face_idx[i+1]][0],
			xxx_coords[xxx_face_idx[i+1]][1],
			xxx_coords[xxx_face_idx[i+1]][2]);
		
		glTexCoord2f(
			xxx_uv[i][0],
			1-xxx_uv[i][1]); /* XXX Ugly Hack */
		glVertex3f(
			xxx_coords[xxx_face_idx[i]][0],
			xxx_coords[xxx_face_idx[i]][1],
			xxx_coords[xxx_face_idx[i]][2]);
		}
	glEnd();
	}

/* vi:tabstop=4
*/
