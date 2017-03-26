/*
   Tiki

   alphafader.h

   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_ANIMS_ALPHAFADER_H
#define __TIKI_ANIMS_ALPHAFADER_H

#include "Tiki/animation.h"

namespace Tiki {
namespace GL {

/// Fades the alpha value of an object
class AlphaFader : public Animation {
public:
	AlphaFader(float fade_to, float delta);
	virtual ~AlphaFader();

	virtual void nextFrame(Drawable *t, uint64 tm);

private:
	float	m_fade_to, m_delta;
};

};
};

#endif	// __TIKI_ANIMS_ALPHAFADER_H
