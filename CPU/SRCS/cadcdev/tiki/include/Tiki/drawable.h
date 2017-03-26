/*
   Tiki

   drawable.h

   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_DRAWABLE_H
#define __TIKI_DRAWABLE_H

#include "animation.h"

#include "list.h"
#include "vector.h"
#include "color.h"
#include "object.h"

namespace Tiki {
namespace GL {

class Drawable : public Object {
public:
	TIKI_OBJECT_DECLS(Drawable)

	/// List types. These things must be drawn in separate passes, so we call
	/// down to each object N times to cover all the lists.
	enum ObjType {
		Opaque = 0,
		Trans		// Translucent (aka alpha-blended)
	};

	/// Constructor / Destructor
	Drawable();
	virtual ~Drawable();

	/// Retrieves the last time nextFrame() was last called.
	uint64 lastUpdate() const { return m_lastUpdate; }

	/// Retrieves the number of microseconds since nextFrame() was last called.
	uint64 timeElapsed(uint64 tm) const { return tm - m_lastUpdate; }

	/// Add an animation object to us
	void animAdd(Animation * ani);

	/// Remove an animation object from us
	void animRemove(Animation * ani);

	/// Remove all animation objects from us
	void animRemoveAll();

	/// Checks to see if this object is still not finished (for screen
	/// closing type stuff). Returns true if this object and all 
	/// sub-objects are finished.
	bool isFinished();

	/// Set this object to be finished
	virtual void setFinished();

	/// Draw this drawable and all sub-drawables for the given list
	void drawAll(ObjType t);

	/// Draw all sub-drawables (if any)
	void subDraw(ObjType t);

	/// Move to all sub-drawables to the next frame (if any)
	void subNextFrame(uint64 tm);

	/// Add a new object to our sub-drawables
	void subAdd(Drawable *t);

	/// Remove an object from our sub-drawables
	void subRemove(Drawable * t);

	/// Remove any sub-drawables that are marked finished
	void subRemoveFinished();

	/// Remove all objects from our sub-drawables
	void subRemoveAll();

	/// Draw this drawable for the given list (only this one, not the subs)
	/// Default: Do nothing.
	virtual void draw(ObjType t);

	/// Move to the next frame of animation
	/// Default: Do all sub-drawables too.
	virtual void nextFrame(uint64 tm);

	/// Go through and produce the sorted scene list. This will traverse
	/// all sub-drawables and put them into a single list sorted by
	/// ascending Z (into the screen). Any previous scene list is freed.
	void createSceneList(Drawable * root = NULL);
	
	/// Free any previously created scene list. You should do this once
	/// you're done, to avoid accidentally holding references.
	void destroySceneList();

	/// Draw this drawable for the given list, using the sorted
	/// scene list.
	void drawScene(ObjType t);

	/// Modify the drawn position of this drawable
	void setTranslate(const Vector & v) { m_trans = v; }

	/// Get the drawn position of this drawable
	const Vector & getTranslate() const { return m_trans; }

	/// Move this drawable relative to where it is now
	void translate(const Vector & v) { m_trans += v; }

	/// Get the absolute position of this drawable (figuring prelative)
	Vector getPosition() const;

	/// Modify the rotation of this drawable; the angle is
	/// stored as the w value.
	void setRotate(const Vector & r) { m_rotate = r; }

	/// Get the rotation of this drawable; the angle is 
	/// stored as the w value.
	const Vector & getRotate() const { return m_rotate; }

	/// Modify the scaling of this drawable
	void setScale(const Vector & s) { m_scale = s; }

	/// Get the scaling of this drawable
	const Vector & getScale() const { return m_scale; }

	/// Set the color tint value of this drawable
	void setTint(const Color & tint) { m_tint = tint; }

	/// Get the color tint value of this drawable
	const Color & getTint() const { return m_tint; }

	/// Shortcut to set the alpha value of the tint
	void setAlpha(float a) { m_tint.a = a; }

	/// Shortcut to get the alpha value of the tint
	float getAlpha() const { return m_tint.a; }

	/// Get the absolute tint value of this drawable (figuring prelative)
	Color getColor() const;

	/// Get our parent object (if any)
	Drawable * getParent() const { return m_parent; }

	/// This is used only for sorting.. you have to have called getPosition() some time
	/// recently before this will work.
	bool operator<(const Drawable & other) const {
		return m_posCache.z < other.m_posCache.z;
	}

protected:
	/// Setup a transform matrix, taking into account the
	/// parent relative rotation and scaling parameters. Pushes the old
	/// matrix onto the stack.
	void pushTransformMatrix() const;

	/// Pops the old matrix off the stack.
	void popTransformMatrix() const;
	
	bool		m_t_prelative;		///< Is translation parent-relative?
	bool		m_r_prelative;		///< Is rotation parent-relative?
	bool		m_s_prelative;		///< Is scaling parent-relative?
	bool		m_a_prelative;		///< Is alpha parent-relative?
	
private:
	uint64		m_lastUpdate;		///< Last microsecond we updated our animations

	Vector		m_trans;		///< Translation
	Vector		m_rotate;		///< Rotation (w is the angle)
	Vector		m_scale;		///< Scaling (about center)
	float		m_alpha;		///< Alpha value
	Color		m_tint;			///< Color tint value

	bool		m_finished;		///< Is it "finished" (i.e., can safely be removed from scene)
	bool		m_subs_finished;	///< Cached resultes if all sub-drawables are finished

	Drawable	* m_parent;		///< Our parent object

mutable	Vector		m_posCache;		///< Cache of getPosition(), for sorting
	List<Drawable>	m_sceneList;		///< Cache of sorted sub-objects, for drawing

	List<Animation>	m_anims;		///< Animation objects
	List<Drawable>	m_subs;			///< Our sub-drawable list
};

}
}

#endif	// __TIKI_DRAWABLE_H

