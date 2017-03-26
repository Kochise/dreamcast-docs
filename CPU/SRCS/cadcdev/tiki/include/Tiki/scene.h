/*
   Tiki

   scene.h

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_SCENE_H
#define __TIKI_SCENE_H

#include "list.h"
#include "object.h"

namespace Tiki {

/*

A Scene is a complete container for everything related to a Tiki universe
in progress. This includes any drawables, animations, timelines, assets,
etc. It's also transitive -- objects contained in the scene can own
objects of their own. But in general if e.g. you had two scenes, nothing in
one scene should reference the other one.

A Scene also manages basic outside event management. This includes things like
keypresses and mouse clicks.

(Not written yet)

*/

class Timeline;

class Scene : public Object {
public:
	TIKI_OBJECT_DECLS(Scene)
	TIKI_OBJECT_EMITS("userInput:")

	/// Constructor / Destructor
	Scene();
	virtual ~Scene();

	/// Gets the main timeline for this Scene.
	Timeline * getTimeline();

	/// Adds an object to the Scene. If the object has a name, then
	/// you can use it to look it up within the Scene. This will cause
	/// us to retain a reference to the item as well.
	void add(Object * item);

	/// Removes an object from the Scene.
	void remove(Object * item);

	/// This should be called periodically to allow us to update all sub-objects.
	void periodic();

	/// Finds an object by name. Returns NULL if we can't find one. If there
	/// is more than one object with the same name, the results are undefined.
	Object * find(string name);

protected:
	List<Object>		m_objects;		// All the objects we contain
	RefPtr<Timeline>	m_timeline;		// The global timeline
};

}

#endif	// __TIKI_SCENE_H

