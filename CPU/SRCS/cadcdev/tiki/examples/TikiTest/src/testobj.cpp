/*
   Tiki

   object.cpp

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include <Tiki/tiki.h>
#include <Tiki/debug.h>

#include "testobj.h"

using namespace Tiki;
using std::string;

TIKI_OBJECT_NAME(TestObject)
TIKI_OBJECT_BEGIN(Object, TestObject)
	TIKI_OBJECT_RECEIVER("testmessage", TestObject::testMessage)
	TIKI_OBJECT_RECEIVER("anothermessage", TestObject::anotherMessage)
	TIKI_OBJECT_RECEIVER("testevent", TestObject::testEvent)
	TIKI_OBJECT_OUTLET("testevent")
TIKI_OBJECT_END(TestObject)


TestObject::TestObject(string name) {
	Debug::printf("TestObject::TestObject(%s)\n", name.c_str());
	m_name = name;
}
	
TestObject::~TestObject() {
}
	
int TestObject::testMessage(Object * sender, Object * arg) {
	Debug::printf("TestObject(%s)::testMessage(%p, %p)\n", m_name.c_str(), sender, arg);
	return 0;
}

int TestObject::anotherMessage(Object * sender, Object * arg) {
	Debug::printf("TestObject(%s)::anotherMessage(%p, %p)\n", m_name.c_str(), sender, arg);
	return emit("testevent", arg);
}
	
int TestObject::testEvent(Object * sender, Object * arg) {
	Debug::printf("TestObject(%s)::testEvent(%p, %p)\n", m_name.c_str(), sender, arg);
	return 0;
}















