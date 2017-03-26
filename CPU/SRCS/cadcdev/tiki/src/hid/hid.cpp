/*
   Tiki

   hid.cpp

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/hid.h"

#include <list>

using namespace Hid;

bool Hid::init() {
	if (!platInit())
		return false;

	return true;
}

void Hid::shutdown() {
	platShutdown();
}

/////////////////////////////////////////////////////////////////////////////////////////////

struct OneCallback {
	void (*func)(const Event &, void *);
	void	* data;
	int	cookie;
};

typedef std::list<OneCallback> CbList;
static CbList callbacks;
static int cbCookieHi = 0;

int Hid::callbackReg(void (*func)(const Event &, void *), void * data) {
	OneCallback cb;
	cb.func = func;
	cb.data = data;
	cb.cookie = ++cbCookieHi;
	callbacks.push_back(cb);
	return cb.cookie;
}

void Hid::callbackUnreg(int cookie) {
	for (CbList::iterator i=callbacks.begin(); i!=callbacks.end(); i++) {
		if (i->cookie == cookie) {
			callbacks.erase(i);
			return;
		}
	}
}

void Hid::sendEvent(const Event & evt) {
	for (CbList::iterator i=callbacks.begin(); i!=callbacks.end(); i++) {
		i->func(evt, i->data);
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////

Device::Device() {
}

Device::~Device() {
}

Device::Type Device::getType() const {
	return TypeNone;
}

string Device::getName() const {
	return "<unnamed device>";
}

