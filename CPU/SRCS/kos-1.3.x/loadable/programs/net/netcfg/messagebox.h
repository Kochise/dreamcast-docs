/*      
   Network Configurator
           
   messagebox.h

   Copyright (C)2003 Cryptic Allusion, LLC
   Donated from Feet of Fury

   $Id: messagebox.h,v 1.1 2003/07/15 07:55:06 bardtx Exp $
*/

#ifndef __MESSAGEBOX_H
#define __MESSAGEBOX_H

class MenuBox;
class TextDisplay;
class Font;

#include <tsu/drawable.h>

class MessageBox : public Drawable {
public:
	MessageBox(float ps, Font * fnt);
	virtual ~MessageBox();

	virtual void draw(int list);

	void setText(const char **text, int linecnt);
	void startExit();

private:
	// XXX shared between this and Popup
	class PopupBirth : public Animation {
	public:
		PopupBirth() { }
		virtual ~PopupBirth() { }
		
		virtual void nextFrame(Drawable *t) {
			MessageBox * p = (MessageBox *)t;

			if (p->m_scale < 1.0f) {
				p->m_scale += (1.0f - p->m_scale) / 2.0f;
				if (p->m_scale >= 0.99f) {
					p->m_scale = 1.0f;
				}
			}

			if (p->m_scale >= 1.0f) {
				p->m_txtalpha += 1.0f / (60/4);
				if (p->m_txtalpha >= 1.0f) {
					p->m_txtalpha = 1.0f;
					p->m_anim = NULL;
					complete(t);
				}
			}
		}
	};

	// XXX Ditto
	class PopupDeath : public Animation {
	public:
		PopupDeath() { }
		virtual ~PopupDeath() { }
		
		virtual void nextFrame(Drawable *t) {
			MessageBox * p = (MessageBox *)t;

			if (p->m_txtalpha > 0.0f) {
				p->m_txtalpha -= 1.0f / (60/4);
				if (p->m_txtalpha <= 0.0f) {
					p->m_txtalpha = 0.0f;
				}
			}

			if (p->m_txtalpha <= 0.0f) {
				if (p->m_scale > 0.01f) {
					p->m_scale -= p->m_scale / 2.0f;
					if (p->m_scale <= 0.01f) {
						p->m_scale = 0.01f;
						p->m_anim = NULL;
						complete(t);
					}
				}
			}
		}
	};

	// XXX Ditto
	class AutoRemove : public Trigger {
	public:
		AutoRemove() { }
		virtual ~AutoRemove() { }

		void trigger(Drawable *t, Animation *a) {
			Drawable * p = t->getParent();
			if (p) {
				p->subRemove(t);
			}

			Trigger::trigger(t, a);
		}
	};

	float		m_scale, m_txtalpha;
	float		m_width, m_height;

	RefPtr<MenuBox>		m_box;
	RefPtr<TextDisplay>	m_td;
	RefPtr<Animation>	m_anim;
};

#endif	/* __MESSAGEBOX_H */

