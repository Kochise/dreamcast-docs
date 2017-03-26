/* xxx.h - test TDOject class
** (c)2001 Paul Boese
*/

#ifndef __XXX_H__
#define __XXX_H__

#include "TDObject.h"

class Xxx : public TDObject
	{
	public:
		Xxx(GLuint tex) : TDObject(tex)
			{
			printf("[Xxx] tex at %08x\r\n", texture);
			}

		void draw();

	};

#endif /* __XXX_H__ */

/* vi:tabstop=4
*/
