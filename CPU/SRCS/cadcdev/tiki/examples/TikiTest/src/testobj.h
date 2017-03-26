#ifndef __TESTOBJ_H
#define __TESTOBJ_H

#include <Tiki/object.h>
#include <string>

class TestObject : public Tiki::Object {
public:
	TestObject(std::string name);
	virtual ~TestObject();
	int testMessage(Object * sender, Object * arg);
	int anotherMessage(Object * sender, Object * arg);
	int testEvent(Object * sender, Object * arg);

protected:
	TIKI_OBJECT_DECLS(TestObject)
	
	std::string	m_name;
};


#endif














