/*
   Tiki

   init_shutdown.cpp

   Copyright (C)2005 Atani Software
*/

#include "pch.h"

#include "Tiki/sound.h"
#include "Tiki/stream.h"
#include "Tiki/plxcompat.h"
#include "Tiki/hid.h"

namespace Tiki {

bool init(int argc, char **argv) {
	return Hid::init();
}

void shutdown() {
	Hid::shutdown();
}

void setName(const char *windowName, const char *iconName)
{
}

namespace GL {
void showCursor(bool visible) {
}
}

}
