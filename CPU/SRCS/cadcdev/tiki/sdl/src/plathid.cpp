#include "pch.h"
#include "Tiki/glhdrs.h"
#include "Tiki/hid.h"

#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

using namespace Tiki::Hid;

class KbDevice : public Device {
public:
	KbDevice() { }
	virtual ~KbDevice() { }

	virtual Type getType() const { return TypeKeyboard; }
	virtual string getName() const { return "SDL Keyboard"; }
};

class MouseDevice : public Device {
public:
	MouseDevice() { }
	virtual ~MouseDevice() { }

	virtual Type getType() const { return TypeMouse; }
	virtual string getName() const { return "SDL Mouse"; }

	void moveXY(int x, int y) { abs_x += x; abs_y += y; }
	void setXY(int x, int y) { abs_x = x; abs_y = y; }
	void getXY(int *x, int *y) { *x = abs_x; *y = abs_y; }

protected:
	int abs_x, abs_y;
};

static RefPtr<KbDevice> SDLkb;
static RefPtr<MouseDevice> SDLMouse;

int HandleMouse(void *unused);
int HandleKeyboard(void *unused);
int HandleWM(void *unused);

static int done = 0;
SDL_Thread *mouse_thread;
SDL_Thread *keybd_thread;
SDL_Thread *wm_thread;

bool Hid::platInit() {
	SDLkb = new KbDevice();
	SDLMouse = new MouseDevice();
	SDLMouse->setXY(0, 0);

	Event evtKB(Event::EvtAttach);
	evtKB.dev = SDLkb;
	sendEvent(evtKB);

	Event evtMouse(Event::EvtAttach);
	evtMouse.dev = SDLMouse;
	sendEvent(evtMouse);

	if(SDL_SetVideoMode(640, 480, 16, SDL_OPENGL) == NULL)
	{
		fprintf(stderr, "Unable to Create OpenGL Window: %s\n", SDL_GetError());
		return false;
	}

	SDL_WarpMouse(0, 0);

	char junk = '0';

	mouse_thread = SDL_CreateThread(HandleMouse, &junk);
	keybd_thread = SDL_CreateThread(HandleKeyboard, &junk);	
	wm_thread = SDL_CreateThread(HandleWM, &junk);	

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);              // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black Background
	glClearDepth(1.0f);                   // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);              // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);               // The Type Of Depth Testing To Do

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations

	return true;
}

void Hid::platShutdown() {
	done = 1;
	SDL_Delay(20);
	SDL_WaitThread(mouse_thread, NULL);
	SDL_WaitThread(keybd_thread, NULL);
	SDL_WaitThread(wm_thread, NULL);

	Event evtKB(Event::EvtDetach);
	evtKB.dev = SDLkb;
	sendEvent(evtKB);

	Event evtMouse(Event::EvtDetach);
	evtMouse.dev = SDLMouse;
	sendEvent(evtMouse);

	SDL_Quit();
}

extern "C" void TikiRecvQuit() {
	done = 1;
	Event evt(Event::EvtQuit);
	sendEvent(evt);
}

int HandleMouse(void *unused)
{
	SDL_Event events[10];
	int i, found;
	Uint32 mask;

	/* Handle mouse events here */
	mask = (SDL_MOUSEMOTIONMASK|SDL_MOUSEBUTTONDOWNMASK|SDL_MOUSEBUTTONUPMASK);
	while ( ! done ) {
		found = SDL_PeepEvents(events, 10, SDL_GETEVENT, mask);
		for ( i=0; i<found; ++i ) {
			switch(events[i].type) {
				case SDL_MOUSEBUTTONDOWN:
					{
						Event evt(Event::EvtBtnPress);
						evt.port = 0;
						evt.dev = SDLMouse;
						evt.btn = Event::MouseFirst + events[i].button.button - 1;
						SDLMouse->getXY(&evt.x, &evt.y);
						sendEvent(evt);
					}
					break;
				case SDL_MOUSEBUTTONUP:
					{
						Event evt(Event::EvtBtnRelease);
						evt.port = 0;
						evt.dev = SDLMouse;
						evt.btn = Event::MouseFirst + events[i].button.button - 1;
						SDLMouse->getXY(&evt.x, &evt.y);
						sendEvent(evt);
					}
					break;
				case SDL_MOUSEMOTION:
					{
						SDLMouse->moveXY(events[i].motion.xrel, events[i].motion.yrel);
						Event evt(Event::EvtMouseMove);
						evt.port = 0;
						evt.dev = SDLMouse;
						SDLMouse->getXY(&evt.x, &evt.y);
						sendEvent(evt);
					}
					break;
			}
		}
		/* Give up some CPU to allow events to arrive */
		SDL_Delay(20);
	}
	return(0);
}

static int translateSym(SDLKey key)
{
	switch(key)
	{
		case SDLK_UP:
			return Event::KeyUp;
		case SDLK_DOWN:
			return Event::KeyDown;
		case SDLK_LEFT:
			return Event::KeyLeft;
		case SDLK_RIGHT:
			return Event::KeyRight;
		case SDLK_INSERT:
			return Event::KeyInsert;
		case SDLK_DELETE:
			return Event::KeyDelete;
		case SDLK_HOME:
			return Event::KeyHome;
		case SDLK_END:
			return Event::KeyEnd;
		case SDLK_PAGEUP:
			return Event::KeyPgup;
		case SDLK_PAGEDOWN:
			return Event::KeyPgdn;
		case SDLK_ESCAPE:
			return Event::KeyEsc;
		case SDLK_F1:
			return Event::KeyF1;
		case SDLK_F2:
			return Event::KeyF2;
		case SDLK_F3:
			return Event::KeyF3;
		case SDLK_F4:
			return Event::KeyF4;
		case SDLK_F5:
			return Event::KeyF5;
		case SDLK_F6:
			return Event::KeyF6;
		case SDLK_F7:
			return Event::KeyF7;
		case SDLK_F8:
			return Event::KeyF8;
		case SDLK_F9:
			return Event::KeyF9;
		case SDLK_F10:
			return Event::KeyF10;
		case SDLK_F11:
			return Event::KeyF11;
		case SDLK_F12:
			return Event::KeyF12;
		default:
			return key;
	}
	return key;
}

int HandleKeyboard(void *unused)
{
	SDL_Event events[10];
	int i, found;
	Uint32 mask;
	int mod;
	SDL_keysym lastPressed; //Used to detect repeats

	/* Enable key repeat */
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);

	/* Handle mouse events here */
	mask = (SDL_KEYDOWNMASK|SDL_KEYUPMASK);
	while ( ! done ) {
		found = SDL_PeepEvents(events, 10, SDL_GETEVENT, mask);
		for ( i=0; i<found; ++i ) {
			if(events[i].type == SDL_KEYDOWN) {
				mod = 0;
				
				if(events[i].key.keysym.mod & KMOD_SHIFT) mod |= Event::KeyShift;
				if(events[i].key.keysym.mod & KMOD_CTRL) mod |= Event::KeyControl;
				if(events[i].key.keysym.mod & KMOD_ALT) mod |= Event::KeyAlt;

			    /* We want to toggle visibility on buttonpress */
			  
			  //Only keypress, not keydown, should repeat  
			  if(!(lastPressed.sym == events[i].key.keysym.sym && lastPressed.mod == events[i].key.keysym.mod)) {
					Event evt(Event::EvtKeyDown);
					evt.dev = SDLkb;
					evt.key = translateSym(events[i].key.keysym.sym);
					evt.mod = mod;
					sendEvent(evt);
					
					lastPressed.sym = events[i].key.keysym.sym;
					lastPressed.mod = events[i].key.keysym.mod;
				}
								
				Event evtPress(Event::EvtKeypress);
				evtPress.dev = SDLkb;
				evtPress.key = translateSym(events[i].key.keysym.sym);
				evtPress.mod = mod;
				sendEvent(evtPress);
				//Debug::printf("HID:KB: KEYDOWN: %d\n", evt.key);
			} else {
				Event evt(Event::EvtKeyUp);
				evt.dev = SDLkb;
				evt.key = translateSym(events[i].key.keysym.sym);
				evt.mod = mod;
				sendEvent(evt);
				//Debug::printf("HID:KB: KEYUP: %d\n", evt.key);
				
				lastPressed.sym = (SDLKey)0;
				lastPressed.mod = (SDLMod)0;
			}
		}
		/* Give up some CPU to allow events to arrive */
		SDL_Delay(20);
	}
	return(0);
}

int HandleWM(void *unused)
{
	SDL_Event events[10];
	int i, found;
	Uint32 mask;

	/* Handle mouse events here */
	mask = (SDL_ACTIVEEVENTMASK | SDL_QUITMASK | SDL_SYSWMEVENTMASK );
	while ( ! done ) {
		found = SDL_PeepEvents(events, 10, SDL_GETEVENT, mask);
		for ( i=0; i<found; ++i ) {
			switch(events[i].type) {
			    /* We want to toggle visibility on buttonpress */
			    case SDL_QUIT:
				done = 1;
				TikiRecvQuit();
			    	break;
			}
		}
		/* Give up some CPU to allow events to arrive */
		SDL_Delay(20);
	}
	return(0);
}

