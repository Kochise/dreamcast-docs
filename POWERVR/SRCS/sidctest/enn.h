/* enn.h - test TDOject class
** (c)2001 Paul Boese
*/

#ifndef __ENN_H__
#define __ENN_H__

#include "TDObject.h"

class Enn : public TDObject
	{
	public:
		Enn(GLuint tex) : TDObject(tex)
			{
			printf("[Enn] tex at %08x\r\n", texture);
			}

		void draw();

	};

#endif /* __ENN_H__ */

/* vi:tabstop=4
*/
