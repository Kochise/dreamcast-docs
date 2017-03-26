/*
   Tiki

   drawable.cpp

   Copyright (C)2002,2003,2004 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/drawable.h"
#include "Tiki/matrix.h"
#include "Tiki/plxcompat.h"

using namespace Tiki::GL;

TIKI_OBJECT_NAME(Drawable)
TIKI_OBJECT_BEGIN(Object, Drawable)
TIKI_OBJECT_END(Drawable)

// Constructor / Destructor
Drawable::Drawable() {
	m_trans.zero();
	m_rotate.zero();
	m_scale = Vector(1.0f, 1.0f, 1.0f, 1.0f);
	m_alpha = 1.0f;
	m_lastUpdate = 0;

	m_t_prelative = true;
	m_r_prelative = true;
	m_s_prelative = true;
	m_a_prelative = true;
	
	m_finished = false;
	m_subs_finished = false;

	m_parent = NULL;
}
	
Drawable::~Drawable() {
}

void Drawable::animAdd(Animation * ani) {
	m_anims.insertHead(ani);
}

void Drawable::animRemove(Animation * ani) {
	m_anims.del(ani);
}

void Drawable::animRemoveAll() {
	m_anims.delAll();
}

bool Drawable::isFinished() {
	if (m_subs_finished)
		return m_finished;

	ListNode<Drawable> * t;
	t = m_subs.getHead();
	while (t) {
		if (!(*t)->isFinished())
			return false;
		t = t->getNext();
	}

	m_subs_finished = true;
	return m_finished;
}

void Drawable::setFinished() {
	m_finished = true;

	ListNode<Drawable> * t;
	t = m_subs.getHead();
	while (t) {
		(*t)->setFinished();
		t = t->getNext();
	}
}

void Drawable::subDraw(ObjType l) {
	ListNode<Drawable> * t;
	t = m_subs.getHead();
	while (t) {
		if (!(*t)->isFinished())
			(*t)->draw(l);
		t = t->getNext();
	}
}

void Drawable::drawAll(ObjType t) {
	draw(t);
	subDraw(t);
}

void Drawable::subNextFrame(uint64 tm) {
	ListNode<Drawable> * t, * n;
	t = m_subs.getHead();
	while (t) {
		// We do getNext() first here in case a drawable
		// decides to remove itself from the scene.
		n = t->getNext();
		if (!(*t)->isFinished())
			(*t)->nextFrame(tm);
		t = n;
	}
}

void Drawable::subAdd(Drawable *t) {
	assert( t->m_parent == NULL );
	t->m_parent = this;
	m_subs.insertTail(t);
}

void Drawable::subRemove(Drawable *t) {
	assert( t->m_parent == this );
	t->m_parent = NULL;
	m_subs.del(t);
}

void Drawable::subRemoveFinished() {
	ListNode<Drawable> * t, * tn;
	t = m_subs.getHead();
	while (t) {
		tn = t->getNext();
		if ((*t)->isFinished()) {
			assert( (*t)->m_parent == this );
			(*t)->m_parent = NULL;
			t->remove();
			delete t;
		}
		t = tn;
	}
}

void Drawable::subRemoveAll() {
	ListNode<Drawable> * t;
	t = m_subs.getHead();
	while (t) {
		assert( (*t)->m_parent == this );
		(*t)->m_parent = NULL;
		t = t->getNext();
	}
	m_subs.delAll();
}

void Drawable::draw(ObjType t) {
}

void Drawable::nextFrame(uint64 tm) {
	// This prevents us from being deleted while processing
	// triggers and such further down, since in theory it could
	// trigger a deletion.
	RefPtr<Drawable> keepMe(this);

	ListNode<Animation> * t, * n;
	t = m_anims.getHead();
	while (t) {
		// We do getNext() first here in case an animation
		// decides to remove itself from the list.
		n = t->getNext();
		(*t)->nextFrame(this, tm);
		t = n;
	}
	subNextFrame(tm);
	
	m_lastUpdate = tm;
}

// This is pretty madly inefficient, all things considered...
void Drawable::createSceneList(Drawable * root) {
	// Are we the top of the chain?
	if (root == NULL) {
		destroySceneList();
		root = this;
	}
	
	// Cache our position and add us into the sorted list.
	getPosition();
	root->m_sceneList.insertSorted(this);
	
	// DANGER WILL ROBINSON. The above line just created a circular reference
	// loop. Unless you destroySceneList() manually before losing your reference
	// to this object, it will leak!!
	
	// Add all of our sub-drawables (and theirs) to the list.
	ListNode<Drawable> * t;
	t = m_subs.getHead();
	while (t) {
		(*t)->createSceneList(root);
		t = t->getNext();
	}
}

void Drawable::destroySceneList() {
	m_sceneList.delAll();
}

void Drawable::drawScene(ObjType l) {
	ListNode<Drawable> * t;
	if (l == Opaque)
		t = m_sceneList.getTail();
	else
		t = m_sceneList.getHead();
	while(t) {
		(*t)->draw(l);
		if (l == Opaque)
			t = t->getPrev();
		else
			t = t->getNext();
	}
}

Vector Drawable::getPosition() const {
	Vector pos = getTranslate();
	if (m_parent && m_t_prelative)
		pos += m_parent->getPosition();

	// This value will be used during sorting for scene drawing.
	m_posCache = pos;

	return pos;
}

Color Drawable::getColor() const {
	Color tint = getTint();
	if (m_parent)
		tint *= m_parent->getColor();

	return tint;
}

void Drawable::pushTransformMatrix() const {
	const Vector & pos = getTranslate();
	const Vector & rot = getRotate();
	const Vector & scale = getScale();

	Plxcompat::plx_mat3d_push();
	Plxcompat::plx_mat3d_translate(pos.x, pos.y, pos.z);
	Plxcompat::plx_mat3d_rotate(rot.w, rot.x, rot.y, rot.z);
	Plxcompat::plx_mat3d_scale(scale.x, scale.y, scale.z);
}

void Drawable::popTransformMatrix() const {
	Plxcompat::plx_mat3d_pop();
}

