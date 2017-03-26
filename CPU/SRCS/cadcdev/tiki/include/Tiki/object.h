/*
   Tiki

   refcnt.h

   Copyright (C)2002 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_OBJECT_H
#define __TIKI_OBJECT_H

/// \file The base object class for all Tiki objects. This includes a
/// simple reference counting system for managing shared data objects.

#include "refcnt.h"

#include <map>

namespace Tiki {

/// All objects in Tiki should be derived from this base class. It inherits
/// the RefCnt functionality and adds some extra stuff, like basic introspection
/// and dynamically bound message passing. These are inspired by a combination
/// of Objective-C, Qt moc, and C# delegates.
///
/// The method this uses for message passing (pointer-to-method on subclass
/// methods) should probably be considered criminally evil and non-standard,
/// but it does work in both GCC and VC++. So what can I say.
class Object : public RefCnt {
public:
	Object();
	virtual ~Object();

	// The type of message/event selectors.
	typedef string	Selector;
	
	// A selector/target pair, used for outlets.
	typedef std::pair<Object*, Selector>	OutletTarget;
	
	// The method pointer type for message/event receivers.
	typedef int (Object::* Receiver)(Object * sender, Object * arg);
	
	// Receive a message from another object. This just handles the
	// processing once it gets to its target, it doesn't do any sort
	// of routing or anything.
	virtual int perform(Selector sel, Object * sender, Object * arg);

	// Causes this object to emit a message to the marked target outlet.
	// If there is nothing there, then this is a NO-OP. If the target
	// doesn't understand the message, it will also be a NO-OP.
	virtual int emit(Selector sel, Object * arg);

	// Connects this object's outlet, named by the selector, to the
	// given target object. Returns true if the outlet exists on this
	// object. This can be used to connect both message outputs and
	// other-object references. For a message output, a target selector
	// should also be given.
	bool connect(Selector sel, Object * target, Selector targetsel = "");

	// Retrieve the target object for outlet named by the selector.
	// Returns non-NULL if the outlet exists and it's filled.
	Object * getTarget(Selector sel);
	
	// Retrieve the target selector for the outlet named by the selector.
	// Returns non-blank if the outlet exists and it's filled with a
	// selector value.
	Selector getTargetSelector(Selector sel);

	// Returns the name of the class.
	const string & getClassName();
	
	// Returns the name of the instance object (if any).
	const string & getObjectName();

protected:
	// This maps incoming messages to method handlers.
	typedef std::map<Selector, Receiver> ReceiverMap;
	
	// This maps outgoing messages to targets and connections
	// from this object to other objects in general.
	typedef std::map<Selector, OutletTarget> OutletMap;

	// Called whenever we need access to the subclass-setup
	// maps. This has to be done because in our base-class
	// constructor, the vtbl isn't valid yet.
	void setupIfNotSetup();

	// Accessors for these items, to make sure they're set up.
	OutletMap & getOutletMap();
	ReceiverMap & getReceiverMap();

	// Called from the subclass' setup methods, to do the initial
	// map population.
	void addReceiver(Selector sel, Receiver recv);
	void addOutlet(Selector sel);

	// These will be overridden by Object subclasses.
	virtual void setupName(const char * name);
	virtual void setupEvents(bool final = true);
	
	// These generally will not, but can be.
	virtual void setupEventsStart();
	virtual void setupEventsFinish();

private:
	// Have we been fully initialized yet?
	bool		m_setup;

	// The name of this class, and instance (if applicable).
	string		m_className, m_objName;

	// The map of outlets from this class. This includes both message
	// emission outlets and general connections to other objects.
	OutletMap	m_outlets;

	// The map of messages/events this class can receive, and how to
	// process them as they come in.
	ReceiverMap	m_receivers;
};

// This goes in your object's class definition.
#define TIKI_OBJECT_DECLS(classname) \
	virtual void setupName(const char *); \
	virtual void setupEvents(bool final = true);
#define TIKI_OBJECT_EMITS(sel)
#define TIKI_OBJECT_ACCEPTS(sel)

// These go in your class implementation file.
#define TIKI_OBJECT_NAME(classname) \
	void classname::setupName(const char *) { Object::setupName(#classname); }
#define TIKI_OBJECT_BEGIN(superclass, classname) \
	void classname::setupEvents(bool final) { \
		if (final) \
			Object::setupEventsStart(); \
		if (string(#superclass) != "Object") \
			superclass::setupEvents(false);
#define TIKI_OBJECT_RECEIVER(sel, recv) \
		addReceiver(sel, (Receiver)&recv);
#define TIKI_OBJECT_OUTLET(sel) \
		addOutlet(sel);
#define TIKI_OBJECT_END(classname) \
		if (final) \
			Object::setupEventsFinish(); \
	}

}

#endif	// __TIKI_OBJECT_H
