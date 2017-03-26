/*
   Tiki

   plathid.cpp

   Copyright (C)2005 Sam Steele
*/

#include "pch.h"
#include "Tiki/glhdrs.h"
#include "Tiki/hid.h"
#include <dc/maple.h>
#include <dc/maple/controller.h>
#include <dc/maple/mouse.h>

using namespace Tiki::Hid;

class KbDevice : public Device {
public:
	KbDevice() { }
	virtual ~KbDevice() { }

	virtual Type getType() const { return TypeKeyboard; }
	virtual string getName() const { return "DC Keyboard"; }
};

class MouseDevice : public Device {
public:
	MouseDevice() { }
	virtual ~MouseDevice() { }

	virtual Type getType() const { return TypeMouse; }
	virtual string getName() const { return "DC Mouse"; }

	void moveXY(int x, int y) { abs_x += x; abs_y += y; }
	void setXY(int x, int y) { abs_x = x; abs_y = y; }
	void getXY(int *x, int *y) { *x = abs_x; *y = abs_y; }

protected:
	int abs_x, abs_y;
};

class JsDevice : public Device {
public:
	JsDevice() { }
	virtual ~JsDevice() { }

	virtual Type getType() const { return TypeJoystick; }
	virtual string getName() const { return "DC Controller"; }
};

class UnkDevice : public Device {
public:
	UnkDevice() { }
	virtual ~UnkDevice() { }

	virtual Type getType() const { return TypeOther; }
	virtual string getName() const { return "Unknown maple device"; }
};

static RefPtr<KbDevice> DCkb;
static RefPtr<MouseDevice> DCMouse;
static RefPtr<JsDevice> DCjs;
static RefPtr<UnkDevice> DCunk;

static int done = 0;

#define MOUSE_BUTTON_MAP(OLDSTATE, NEWSTATE, BUTTON, EVENT, PORT) \
			if((NEWSTATE & BUTTON) && !(OLDSTATE & BUTTON)) { \
				Event evt(Event::EvtBtnPress); \
				evt.dev = DCMouse; \
				evt.btn = EVENT; \
				evt.port = PORT; \
				sendEvent(evt); \
			} \
			if(!(NEWSTATE & BUTTON) && (OLDSTATE & BUTTON)) { \
				Event evt(Event::EvtBtnRelease); \
				evt.dev = DCMouse; \
				evt.btn = EVENT; \
				evt.port = PORT; \
				sendEvent(evt); \
			} 

#define CONTROLLER_AXIS_MAP(OLDSTATE, NEWSTATE, AXIS, PORT) \
			if(OLDSTATE != NEWSTATE) { \
				Event evt(Event::EvtAxis); \
				evt.dev = DCjs; \
				evt.axis = AXIS; \
				evt.axisValue = NEWSTATE; \
				evt.port = PORT; \
				sendEvent(evt); \
			}

#define CONTROLLER_BUTTON_MAP(OLDSTATE, NEWSTATE, BUTTON, EVENT, PORT) \
			if((NEWSTATE & BUTTON) && !(OLDSTATE & BUTTON)) { \
				Event evt(Event::EvtBtnPress); \
				evt.dev = DCjs; \
				evt.btn = EVENT; \
				evt.port = PORT; \
				sendEvent(evt); \
			} \
			if(!(NEWSTATE & BUTTON) && (OLDSTATE & BUTTON)) { \
				Event evt(Event::EvtBtnRelease); \
				evt.dev = DCjs; \
				evt.btn = EVENT; \
				evt.port = PORT; \
				sendEvent(evt); \
			} 

#define CONTROLLER_KEY_MAP(OLDSTATE, NEWSTATE, BUTTON, EVENT, PORT) \
			if((NEWSTATE & BUTTON) && !(OLDSTATE & BUTTON)) { \
				Event evtPress(Event::EvtKeypress); \
				evtPress.dev = DCjs; \
				evtPress.key = EVENT; \
				evtPress.port = PORT; \
				sendEvent(evtPress); \
				\
				Event evt(Event::EvtKeyDown); \
				evt.dev = DCjs; \
				evt.key = EVENT; \
				evt.port = PORT; \
				sendEvent(evt); \
			} \
			if(!(NEWSTATE & BUTTON) && (OLDSTATE & BUTTON)) { \
				Event evt(Event::EvtKeyUp); \
				evt.dev = DCjs; \
				evt.key = EVENT; \
				evt.port = PORT; \
				sendEvent(evt); \
			} 
			
void handle_maple(void *unusued) {
	uint32 buttons[4];
	int x_axis[4];
	int y_axis[4];
	int l_axis[4];
	int r_axis[4];
	bool attached[4];
	cont_state_t *cst;
	mouse_state_t *mst;
	maple_device_t *devaddr;
	
	DCkb = new KbDevice;
	DCjs = new JsDevice;
	DCMouse = new MouseDevice;
	DCunk = new UnkDevice;
	
	//Initialize our status values
	for(int x=0; x<4; x++) {
		attached[x]=0;
	}

	while(!done) {
		//Enumerate all the Dreamcast's ports
		for(int port=0; port<MAPLE_PORT_COUNT; port++) {
			devaddr=maple_enum_dev(port,0);
			
			if(devaddr) { //If there's a device attached
				if(attached[port]==0) { //If it wasn't here last time
					Event evtAttach(Event::EvtAttach); //Send an attach message
					if(devaddr->info.functions & MAPLE_FUNC_CONTROLLER) {
						evtAttach.dev = DCjs;
					} else if(devaddr->info.functions & MAPLE_FUNC_KEYBOARD) {
						evtAttach.dev = DCkb;
					} else if(devaddr->info.functions & MAPLE_FUNC_MOUSE) {
						evtAttach.dev = DCMouse;
					} else {
						evtAttach.dev = DCunk;
					} 
					evtAttach.port = port;
					sendEvent(evtAttach);
					attached[port]=1;
					
					//Reset our status values
					buttons[port]=0;
					x_axis[port]=0;
					y_axis[port]=0;
					l_axis[port]=0;
					r_axis[port]=0;
				}

				if(devaddr->info.functions & MAPLE_FUNC_MOUSE) { //And it's a mouse
					mst=(mouse_state_t*)maple_dev_status(devaddr); //Get the mouse state

					//Mouse motion
					if(mst->dx!=0 || mst->dy!=0) {
						x_axis[port] += mst->dx;
						y_axis[port] += mst->dy;
						
						if(x_axis[port] < 0) x_axis[port] = 0;
						if(y_axis[port] < 0) y_axis[port] = 0;
						if(x_axis[port] > 640) x_axis[port] = 640;
						if(y_axis[port] > 480) y_axis[port] = 480;
		
						Event evt(Event::EvtMouseMove);
						evt.dev = DCMouse;
						evt.x = x_axis[port];
						evt.y = y_axis[port];
						evt.port = port;
						sendEvent(evt);
					}
					
					//Mouse wheel
					if(mst->dz != 0) {
						Event evt(Event::EvtBtnPress);
						evt.dev = DCMouse;
						evt.btn = (mst->dz < 0) ? Event::MouseWheelUp : Event::MouseWheelDown;
						evt.port = port;
						sendEvent(evt);
					} 
					
					//Mouse buttons
					MOUSE_BUTTON_MAP(buttons[port],mst->buttons,MOUSE_LEFTBUTTON,Event::MouseLeftBtn,port);
					MOUSE_BUTTON_MAP(buttons[port],mst->buttons,MOUSE_RIGHTBUTTON,Event::MouseRightBtn,port);
					MOUSE_BUTTON_MAP(buttons[port],mst->buttons,MOUSE_SIDEBUTTON,Event::MouseMiddleBtn,port);

					//Store the current state
					buttons[port] = mst->buttons;
				}
				if(devaddr->info.functions & MAPLE_FUNC_CONTROLLER) { //And it's a controller
					cst=(cont_state_t*)maple_dev_status(devaddr); //Get the controller state

					//Analog stick and triggers
					CONTROLLER_AXIS_MAP(x_axis[port],cst->joyx,Event::AxisX,port);					
					CONTROLLER_AXIS_MAP(y_axis[port],cst->joyy,Event::AxisY,port);					
					CONTROLLER_AXIS_MAP(l_axis[port],cst->ltrig,Event::AxisLeft,port);					
					CONTROLLER_AXIS_MAP(r_axis[port],cst->rtrig,Event::AxisRight,port);					

					//Buttons
					CONTROLLER_BUTTON_MAP(buttons[port],cst->buttons,CONT_A,Event::BtnA,port);
					CONTROLLER_BUTTON_MAP(buttons[port],cst->buttons,CONT_B,Event::BtnB,port);
					CONTROLLER_BUTTON_MAP(buttons[port],cst->buttons,CONT_C,Event::BtnC,port);
					CONTROLLER_BUTTON_MAP(buttons[port],cst->buttons,CONT_X,Event::BtnX,port);
					CONTROLLER_BUTTON_MAP(buttons[port],cst->buttons,CONT_Y,Event::BtnY,port);
					CONTROLLER_BUTTON_MAP(buttons[port],cst->buttons,CONT_Z,Event::BtnZ,port);
					CONTROLLER_BUTTON_MAP(buttons[port],cst->buttons,CONT_START,Event::BtnStart,port);
		
					//DPad
					CONTROLLER_BUTTON_MAP(buttons[port],cst->buttons,CONT_DPAD_UP,Event::BtnUp,port);
					CONTROLLER_BUTTON_MAP(buttons[port],cst->buttons,CONT_DPAD_DOWN,Event::BtnDown,port);
					CONTROLLER_BUTTON_MAP(buttons[port],cst->buttons,CONT_DPAD_LEFT,Event::BtnLeft,port);
					CONTROLLER_BUTTON_MAP(buttons[port],cst->buttons,CONT_DPAD_RIGHT,Event::BtnRight,port);
					
					//Keyboard emulation
					CONTROLLER_KEY_MAP(buttons[port],cst->buttons,CONT_DPAD_UP,Event::KeyUp,port);
					CONTROLLER_KEY_MAP(buttons[port],cst->buttons,CONT_DPAD_DOWN,Event::KeyDown,port);
					CONTROLLER_KEY_MAP(buttons[port],cst->buttons,CONT_DPAD_LEFT,Event::KeyLeft,port);
					CONTROLLER_KEY_MAP(buttons[port],cst->buttons,CONT_DPAD_RIGHT,Event::KeyRight,port);
					CONTROLLER_KEY_MAP(buttons[port],cst->buttons,CONT_START,13,port);
					CONTROLLER_KEY_MAP(buttons[port],cst->buttons,CONT_A,32,port);
					CONTROLLER_KEY_MAP(buttons[port],cst->buttons,CONT_B,Event::KeyEsc,port);

					//Store the current state
					buttons[port] = cst->buttons;
					x_axis[port] = cst->joyx;
					y_axis[port] = cst->joyy;
					l_axis[port] = cst->ltrig;
					r_axis[port] = cst->rtrig;
				}
			} else {
				if(attached[port]==1) { //If it was here last time
					Event evtDetach(Event::EvtDetach); //Send a detach message
					if(devaddr->info.functions & MAPLE_FUNC_CONTROLLER) {
						evtDetach.dev = DCjs;
					} else if(devaddr->info.functions & MAPLE_FUNC_KEYBOARD) {
						evtDetach.dev = DCkb;
					} else if(devaddr->info.functions & MAPLE_FUNC_MOUSE) {
						evtDetach.dev = DCMouse;
					} else {
						evtDetach.dev = DCunk;
					} 
					evtDetach.port = port;
					sendEvent(evtDetach);
					attached[port]=0;
					
					//Reset our status values
					buttons[port]=0;
					x_axis[port]=0;
					y_axis[port]=0;
				}
			}
		}
		thd_sleep(20);
	}
}

bool Hid::platInit() {
	thd_create(handle_maple,0);
	return true;
}

void Hid::platShutdown() {
	done = 1;
}

extern "C" void TikiRecvQuit() {
	done = 1;
	Event evt(Event::EvtQuit);
	sendEvent(evt);
}
