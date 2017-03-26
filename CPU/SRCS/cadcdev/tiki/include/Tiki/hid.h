/*
   Tiki

   hid.h

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_HID_H
#define __TIKI_HID_H

#include "Tiki/refcnt.h"

namespace Tiki {
namespace Hid {

// Basic setup/shutdown.
bool init();
void shutdown();

// Platform-specific setup/shutdown.
bool platInit();
void platShutdown();

// Every device recognized by the system will have one of these floating
// around somewhere.
class Device : public RefCnt {
public:
	Device();
	virtual ~Device();
	
	enum Type {
		TypeKeyboard = 0,	// Standard PC-style keyboard
		TypeMouse,		// Mouse cursor
		TypeJoystick,		// Joystick, adapter, etc
		TypeOther,		// Some other type
		TypeNone
	};
	
	// What type of device is this?
	virtual Type getType() const;
	
	// What's the human-readable name of it?
	virtual string getName() const;
};

// Any time something happens, we'll get one of these events pushed
// through the system.
class Event {
public:
	// Event types.
	enum Type {
		EvtKeypress = 0,	// Key was pressed (may auto-repeat)
		EvtKeyDown,		// Key was physically pushed down
		EvtKeyUp,		// Key was physically released
		EvtBtnPress,		// Non-keyboard button was pressed
		EvtBtnRelease,		// Non-keyboard button was released
		EvtMouseMove,		// Movement of mouse
		EvtAxis,		// Device analog axis was moved
		EvtAttach,		// New device was recognized
		EvtDetach,		// Old device was removed
		EvtQuit,		// Request for the app to quit
		EvtUser			// Some user-defined event
	};

	// Keyboard constants. If the key value is < KeyFirst, then the key
	// value is an ASCII literal.
	enum KeyConstant {
		KeyFirst = 0x100,
		KeyLeft = KeyFirst,
		KeyRight,
		KeyUp,
		KeyDown,
		KeyEsc,
		KeyHome,
		KeyEnd,
		KeyInsert,
		KeyDelete,
		KeyPgup,
		KeyPgdn,
		KeyF1,
		KeyF2,
		KeyF3,
		KeyF4,
		KeyF5,
		KeyF6,
		KeyF7,
		KeyF8,
		KeyF9,
		KeyF10,
		KeyF11,
		KeyF12,		
		KeyUnknown,
		KeySentinel
	};
	
	enum KeyModifierConstants {
		KeyShift = 1,
		KeyControl = 2,
		KeyAlt = 4
	};
	
	enum MouseConstants {
		MouseFirst = 0x200,
		MouseLeftBtn = MouseFirst,
		MouseMiddleBtn,
		MouseRightBtn,
		MouseWheelUp,
		MouseWheelDown,
	};

	enum ButtonConstants {
		BtnUp = 0x300,
		BtnDown,
		BtnLeft,
		BtnRight,
		BtnA,
		BtnB,
		BtnC,
		BtnX,
		BtnY,
		BtnZ,
		BtnStart
	};

	enum AxisConstants {
		AxisX = 0x400,
		AxisY,
		AxisLeft, //Dreamcast left trigger
		AxisRight //Dreamcast right trigger
	};
	Event() : port(0), key(0), btn(0), axis(0), axisValue(0), userCode(0), x(0), y(0), mod(0) {}
	Event(Type t) : type(t), port(0), key(0), btn(0), axis(0), axisValue(0), userCode(0), x(0), y(0), mod(0) { }
	virtual ~Event() { }

	Type		type;		// All: the type of event
	RefPtr<Device>	dev;		// All: the device that caused the event
	uint64		tm;		// All: the time of the event
	int		port;		// Joystick: Which port the event occured on
	int		key;		// Keypress
	int		btn;		// Btnpress: which button
	int		axis;		// Axis: which axis
	float		axisValue;	// Axis: the new value
	int		userCode;	// User: what is the event?
	int		x, y;		// MouseMove: x,y position
	int		mod; // Key modifier
};

// If the app wants to receive event notifications, it should call this
// to add a callback.
int callbackReg(void (*)(const Event & evt, void * data), void * data);

// Unregister a previously registered callback. Pass the cookie value returned
// from callbackRegister.
void callbackUnreg(int cookie);

// Submit an event. This is generally used by the plat code to submit
// events pulled from the window system.
void sendEvent(const Event & evt);


}
}

#endif	// __TIKI_HID_H

