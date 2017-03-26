/*
   Tiki

   layer.h

   Copyright (C)2002 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_DRW_LAYER_H
#define __TIKI_DRW_LAYER_H

#include "Tiki/drawable.h"

namespace Tiki {
namespace GL {

/**
  Layer provides a container class which you can use as a top-level drawable
  in your scene setup. It doesn't draw anything itself, so its finishedness
  always depends on its sub-drawables.
 */
class Layer : public Drawable {
public:
	Layer() {
		// Scene is always finished itself, because it doesn't draw
		// anything. This will make it check its sub-drawables for
		// finishedness before acquiescing.
		setFinished();
	}
	virtual ~Layer() {
	}
};

};
};

#endif	// __TIKI_DRW_LAYER_H

