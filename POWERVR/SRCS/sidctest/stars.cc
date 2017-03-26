/* Stars.cc
** (c)2001 Paul Boese
*/

#include "stars.h"
extern "C" {
    }
    
void Stars::draw()
	{
	int i;
	glBegin(GL_QUADS);
	glEnable(GL_KOS_AUTO_UV);
	glBindTexture( GL_TEXTURE_2D, texture);
	glColor3f(red, green, blue);
	
	/* Front face */
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	
	glEnd();
	}

/* vi:tabstop=4
*/
