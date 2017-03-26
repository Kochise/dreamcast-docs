/* stars.h - stars class
** (c)2001 Paul Boese
*/

#ifndef __STARS_H__
#define __STARS_H__

#include "TDObject.h"

class Stars : public TDObject
	{
	public:
		Stars(GLuint tex) : TDObject(tex)
			{
			printf("[Stars] tex at %08x\r\n", texture);
			}

		void draw();

	};

#endif /* __STARS_H__ */

/* vi:tabstop=4
*/
