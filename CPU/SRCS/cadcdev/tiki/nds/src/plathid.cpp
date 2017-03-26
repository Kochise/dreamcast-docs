#include "pch.h"
#include "Tiki/glhdrs.h"
#include "Tiki/hid.h"

namespace Tiki {
namespace Hid {
bool platInit() {
	return true;
}

void platShutdown() {
}

}

}

extern "C" void TikiRecvQuit() {
	Tiki::Hid::Event evt(Tiki::Hid::Event::EvtQuit);
	sendEvent(evt);
}

