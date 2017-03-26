/*
   Tiki

   imgpng.h

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_IMGPNG_H
#define __TIKI_IMGPNG_H

#include "Tiki/tikitypes.h"
#include "Tiki/image.h"

namespace Tiki {

// Always returns an RGBA8888 image.
bool pngToImage(const string & filename, RefPtr<Image> & img);

}

#endif	// __TIKI_IMGJPG_H

