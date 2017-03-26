/* 
   Tsunami for KallistiOS ##version##

   drawable.cpp
   
   (c)2002 Dan Potter
*/

#include <tsu/drawable.h>
#include <plx/matrix.h>

CVSID("$Id: drawable.cpp,v 1.3 2003/04/24 02:57:20 bardtx Exp $");

// Constructor / Destructor
Drawable::Drawable() {
	m_scale = Vector(1.0f, 1.0f, 1.0f, 1.0f);
	m_alpha = 1.0f;

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

void Drawable::subDraw(int list) {
	ListNode<Drawable> * t;
	t = m_subs.getHead();
	while (t) {
		if (!(*t)->isFinished())
			(*t)->draw(list);
		t = t->getNext();
	}
}

void Drawable::subNextFrame() {
	ListNode<Drawable> * t, * n;
	t = m_subs.getHead();
	while (t) {
		// We do getNext() first here in case a drawable
		// decides to remove itself from the scene.
		n = t->getNext();
		if (!(*t)->isFinished())
			(*t)->nextFrame();
		t = n;
	}
}

void Drawable::subAdd(Drawable *t) {
	assert( t->m_parent == NULL );
	t->m_parent = this;
	m_subs.insertHead(t);
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

void Drawable::draw(int list) {
	subDraw(list);
}

void Drawable::nextFrame() {
	ListNode<Animation> * t, * n;
	t = m_anims.getHead();
	while (t) {
		// We do getNext() first here in case an animation
		// decides to remove itself from the list.
		n = t->getNext();
		(*t)->nextFrame(this);
		t = n;
	}
	subNextFrame();
}

Vector Drawable::getPosition() const {
	Vector pos = getTranslate();
	if (m_parent)
		pos += m_parent->getPosition();

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

	plx_mat3d_push();
	plx_mat3d_translate(pos.x, pos.y, pos.z);
	plx_mat3d_rotate(rot.w, rot.x, rot.y, rot.z);
	plx_mat3d_scale(scale.x, scale.y, scale.z);
}

void Drawable::popTransformMatrix() const {
	plx_mat3d_pop();
}

