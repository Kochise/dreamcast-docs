/*
   Tiki

   tintfader.h

   Copyright (C)2002 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_ANIMS_TINTFADER_H
#define __TIKI_ANIMS_TINTFADER_H

#include "Tiki/animation.h"
#include "Tiki/color.h"

namespace Tiki {
namespace GL {

/// Fades the tint values of an object
class TintFader : public Animation {
public:
	TintFader(const Color & fade_to, const Color & delta);
	virtual ~TintFader();

	virtual void nextFrame(Drawable *t, uint64 tm);

private:
	bool	clamp(Color & col);

	Color	m_fade_to, m_delta;
};

};
};

#endif	// __TIKI_ANIMS_TINTFADER_H
