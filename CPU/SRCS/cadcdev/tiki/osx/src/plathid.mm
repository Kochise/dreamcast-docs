/*
   Tiki

   plathid.mm

   Copyright (C)2005 Cryptic Allusion, LLC
*/

#include "pch.h"
#include "Tiki/hid.h"

#include <Cocoa/Cocoa.h>

using namespace Hid;

class KbDevice : public Device {
public:
	KbDevice() { }
	virtual ~KbDevice() { }
	
	virtual Type getType() const { return TypeKeyboard; }
	virtual string getName() const { return "Cocoa Keyboard"; }
};

static RefPtr<KbDevice> cocoaKb;

class MouseDevice : public Device {
public:
	MouseDevice() { }
	virtual ~MouseDevice() { }
	
	virtual Type getType() const { return TypeMouse; }
	virtual string getName() const { return "Cocoa Mouse"; }
};

static RefPtr<MouseDevice> cocoaMouse;

bool Hid::platInit() {
	cocoaKb = new KbDevice();
	cocoaMouse = new MouseDevice();
	
	Event evt(Event::EvtAttach);
	evt.dev = cocoaKb;
	sendEvent(evt);

	Event evt2(Event::EvtAttach);
	evt2.dev = cocoaMouse;
	sendEvent(evt2);

	return true;
}

void Hid::platShutdown() {
	Event evt(Event::EvtDetach);
	evt.dev = cocoaKb;
	sendEvent(evt);

	Event evt2(Event::EvtDetach);
	evt2.dev = cocoaMouse;
	sendEvent(evt2);
}

static int translateFn(unichar c) {
	switch(c) {
	case 27:
		return Event::KeyEsc;
	case NSUpArrowFunctionKey:
		return Event::KeyUp;
	case NSDownArrowFunctionKey:
		return Event::KeyDown;
	case NSLeftArrowFunctionKey:
		return Event::KeyLeft;
	case NSRightArrowFunctionKey:
		return Event::KeyRight;
	case NSInsertFunctionKey:
		return Event::KeyInsert;
	case NSDeleteFunctionKey:
		return Event::KeyDelete;
	case NSHomeFunctionKey:
		return Event::KeyHome;
	case NSEndFunctionKey:
		return Event::KeyEnd;
	case NSPageUpFunctionKey:
		return Event::KeyPgup;
	case NSPageDownFunctionKey:
		return Event::KeyPgdn;
	case NSF1FunctionKey:
		return Event::KeyF1;
	case NSF2FunctionKey:
		return Event::KeyF2;
	case NSF3FunctionKey:
		return Event::KeyF3;
	case NSF4FunctionKey:
		return Event::KeyF4;
	case NSF5FunctionKey:
		return Event::KeyF5;
	case NSF6FunctionKey:
		return Event::KeyF6;
	case NSF7FunctionKey:
		return Event::KeyF7;
	case NSF8FunctionKey:
		return Event::KeyF8;
	case NSF9FunctionKey:
		return Event::KeyF9;
	case NSF10FunctionKey:
		return Event::KeyF10;
	case NSF11FunctionKey:
		return Event::KeyF11;
	case NSF12FunctionKey:
		return Event::KeyF12;
	default:
		return -1;
	}
}

extern "C" void TikiRecvQuit() {
	Event evt(Event::EvtQuit);
	sendEvent(evt);
}

extern "C" void TikiRecvMouseEvent(NSEvent * event, NSPoint *point) {
	// We only handle key up and down events right now.
	NSEventType type = [event type];
	switch(type) {
		case NSMouseMoved:
		{
			Event evt(Event::EvtMouseMove);
			evt.port = 0;
			evt.dev = cocoaMouse;
			evt.x = (int)point->x;
			evt.y = (int)point->y;
			sendEvent(evt);
		}
			break;
		case NSLeftMouseDown:
		{
			Event evt(Event::EvtBtnPress);
			evt.port = 0;
			evt.dev = cocoaMouse;
			evt.x = (int)point->x;
			evt.y = (int)point->y;
			evt.btn = Event::MouseLeftBtn;
			sendEvent(evt);
		}
			break;
		case NSLeftMouseUp:
		{
			Event evt(Event::EvtBtnRelease);
			evt.port = 0;
			evt.dev = cocoaMouse;
			evt.x = (int)point->x;
			evt.y = (int)point->y;
			evt.btn = Event::MouseLeftBtn;
			sendEvent(evt);
		}
			break;
		case NSRightMouseDown:
		{
			Event evt(Event::EvtBtnPress);
			evt.port = 0;
			evt.dev = cocoaMouse;
			evt.x = (int)point->x;
			evt.y = (int)point->y;
			evt.btn = Event::MouseRightBtn;
			sendEvent(evt);
		}
			break;
		case NSRightMouseUp:
		{
			Event evt(Event::EvtBtnRelease);
			evt.port = 0;
			evt.dev = cocoaMouse;
			evt.x = (int)point->x;
			evt.y = (int)point->y;
			evt.btn = Event::MouseRightBtn;
			sendEvent(evt);
		}
			break;
		case NSScrollWheel:
		{
			if([event deltaY] != 0) { //only handle up and down for now
				Event evt(Event::EvtBtnPress);
				evt.port = 0;
				evt.dev = cocoaMouse;
				evt.x = (int)point->x;
				evt.y = (int)point->y;
				evt.btn = ([event deltaY] < 0) ? Event::MouseWheelDown : Event::MouseWheelUp;
				sendEvent(evt);
			}
		}
			break;
	}
}

extern "C" void TikiRecvEvent(NSEvent * evt) {
	// We only handle key up and down events right now.
	NSEventType type = [evt type];
	if (type != NSKeyDown && type != NSKeyUp) {
		NSLog([NSString stringWithFormat:@"maple: unhandled event: %@", evt]);
		return;
	}
	
	// NSLog([NSString stringWithFormat:@"%@", evt]);

	// We can get multiples per event, and they may be upper case.
	NSString * chs = [evt charactersIgnoringModifiers];
	int cnt = [chs length];
	int mod = 0;
	
	if([evt modifierFlags] & NSShiftKeyMask) mod |= Event::KeyShift;
	if([evt modifierFlags] & NSAlternateKeyMask) mod |= Event::KeyAlt;
	if([evt modifierFlags] & NSControlKeyMask) mod |= Event::KeyControl;
	
	for (int i=0; i<cnt; i++) {
		unichar c = [chs characterAtIndex: i];
		int ch;
		
		if ((c & 0xff00) == (NSUpArrowFunctionKey & 0xff00) || c == 27 || (c >= NSF1FunctionKey && c <= NSF12FunctionKey)) {
			ch = translateFn(c);
			if (ch < 0)
				return;
		} else {
			ch = tolower((char)c);
		}
		if (type == NSKeyDown) {
			if (![evt isARepeat]) {
				Event evt(Event::EvtKeyDown);
				evt.dev = cocoaKb;
				evt.key = ch;
				evt.mod = mod;
				sendEvent(evt);
			}
			
			Event evt(Event::EvtKeypress);
			evt.dev = cocoaKb;
			evt.key = ch;
			evt.mod = mod;
			sendEvent(evt);
		} else {
			Event evt(Event::EvtKeyUp);
			evt.dev = cocoaKb;
			evt.key = ch;
			evt.mod = mod;
			sendEvent(evt);
		}
	}
}














