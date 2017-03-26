/*      
   Network Configurator

   popup.h

   Copyright (C)2003 Cryptic Allusion, LLC
   Donated from Feet of Fury

   $Id: popup.h,v 1.1 2003/07/15 07:55:06 bardtx Exp $
*/

#ifndef __POPUP_H
#define __POPUP_H

#include <stdlib.h>
#include "widget.h"

class MenuBox;
class SelBar;
class Sound;
class Font;
class Texture;

class Popup : public Drawable, public Widget {
public:
	Popup(const char * title, bool autoRemove, Font * fnt, Sound * cursor, Sound * select, Sound * abort);
	virtual ~Popup();

	virtual void draw(int list);
	virtual void nextFrame();

	virtual void inputEvent(const GenericMenu::Event & evt);

	// Adds either text or graphical options. Add at least one
	// option before attempting to draw the box.
	void	addOption(const char *str);
	void	addOption(Texture * txr);

	// Returns the string associated with an indexed option
	const char * getOptionString(int idx);

	// Returns the number of options
	int	getOptionCount();

	// Returns the final option if we're finished, -1 if we're
	// not finished, or -2 if we aborted.
	int	getResult() const { return m_result; }

	// Sets whether the user can cancel the menu with B
	void	setCancellable(bool i) { m_cancellable = i; }

	// Force us to exit immediately (timeout or similar)
	void	exitNow() { startExit(); }

private:
	class Item : public RefCnt {
	public:
		Item() { text = NULL; texture = NULL; x = y = 0; }
		Item(const char *ch, Texture * txr)
			: text(strdup(ch)), texture(txr) { x = y = 0; }
		virtual ~Item() { if (text) free((void *)text); }

		char			* text;
		RefPtr<Texture>		texture;
		float			x, y;
	};

	class PopupBirth : public Animation {
	public:
		PopupBirth() { }
		virtual ~PopupBirth() { }
		
		virtual void nextFrame(Drawable *t) {
			Popup * p = (Popup *)t;

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

	class PopupDeath : public Animation {
	public:
		PopupDeath() { }
		virtual ~PopupDeath() { }
		
		virtual void nextFrame(Drawable *t) {
			Popup * p = (Popup *)t;

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

	void	startExit();
	void	calcSize();

	int		m_frame;
	int		m_result;
	int		m_selected;
	float		m_width, m_height;
	int		m_optcnt;
	bool		m_autoRemove;

	bool		m_cancellable;
	
	float		m_scale, m_txtalpha;

	Item		m_title;
	List<Item>	m_options;
	
	RefPtr<Font>	m_font;
	RefPtr<Sound>	m_cursor, m_select, m_abort;

	RefPtr<MenuBox>	m_box;
	RefPtr<SelBar>	m_selbar;

	RefPtr<Animation>	m_anim;
};

#endif	/* __POPUP_H */

