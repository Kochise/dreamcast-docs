/*
   Tiki

   imgjpg.h

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_IMGJPG_H
#define __TIKI_IMGJPG_H

#include "Tiki/tikitypes.h"
#include "Tiki/image.h"

namespace Tiki {

// Always returns an RGBA8888 image.
bool jpgToImage(const string & filename, int scale, RefPtr<Image> & img);

}

#endif	// __TIKI_IMGJPG_H

