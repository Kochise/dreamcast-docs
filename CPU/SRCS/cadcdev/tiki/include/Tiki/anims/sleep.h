/*
   Tiki

   alpharotate.h

   Copyright (C)2005 Atani Software
*/

#ifndef __TIKI_ANIMS_SLEEP_H
#define __TIKI_ANIMS_SLEEP_H

#include "Tiki/animation.h"

namespace Tiki {
namespace GL {

/// Fades the alpha value of an object
class Sleep : public Animation {
	public:
		Sleep(int frames) { assert(frames > 0); _frames = frames; }
		virtual void nextFrame(Drawable *t, uint64 tm)
		{
			--_frames;
			if(_frames <= 0)
			{
				complete(t);
			}
		}
	private:
		int _frames;
};

};
};

#endif	// __TIKI_ANIMS_ALPHAFADER_H
