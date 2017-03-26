/* TDObject.h
** ThreeD Object Class - SIDC
** (c)2001 Paul Boese
** Extremely simple for now...
*/

#include "headers.h"

#ifndef __TDOBJECT_H__
#define __TDOBJECT_H__

/* abstract TDObject class */
class TDObject
	{
	protected:
		GLuint texture;
		GLfloat red, green, blue, alpha;
		
	public:
		TDObject(GLuint tex)
			{
			texture = tex;
			red = green = blue = alpha = 1.0f;
			}

		TDObject()
			{
			texture = NULL;
			red = green = blue = alpha = 1.0f;
			}

		virtual void draw()
			{
			}

		void setColor(float r, float g, float b)
			{
			red = r;
			green = g;
			blue = b;
			}

		void setAlpha(float a)
			{
			alpha = a;
			}
				
	};

#endif /* __TDOBJECT_H__ */

/* vi:tabstop=4
*/
