#include "pch.h"
#include "Tiki/hid.h"
using namespace Tiki::Hid;

class KbDevice : public Device {
public:
	KbDevice() { }
	virtual ~KbDevice() { }

	virtual Type getType() const { return TypeKeyboard; }
	virtual string getName() const { return "Win32 Keyboard"; }
};

class MouseDevice : public Device {
public:
	MouseDevice() { }
	virtual ~MouseDevice() { }

	virtual Type getType() const { return TypeMouse; }
	virtual string getName() const { return "Win32 Mouse"; }
};

static RefPtr<KbDevice> win32kb;
static RefPtr<MouseDevice> win32mouse;

bool Hid::platInit() {
	win32kb = new KbDevice();
	win32mouse = new MouseDevice();

	Event evt(Event::EvtAttach);
	evt.dev = win32kb;
	sendEvent(evt);

	evt.dev = win32mouse;
	sendEvent(evt);
	return true;
}

void Hid::platShutdown() {
}

void Tiki::RecvQuit()
{
	Event evt(Event::EvtQuit);
	sendEvent(evt);
}

static int translateFn(WPARAM key, LPARAM lp) {
	int outkey;

	switch(key)
	{
		case VK_ESCAPE:
			outkey = Event::KeyEsc;
			break;
		case VK_HOME:
			outkey = Event::KeyHome;
			break;
		case VK_END:
			outkey = Event::KeyEnd;
			break;
		case VK_LEFT:
			outkey = Event::KeyLeft;
			break;
		case VK_RIGHT:
			outkey = Event::KeyRight;
			break;
		case VK_UP:
			outkey = Event::KeyUp;
			break;
		case VK_DOWN:
			outkey = Event::KeyDown;
			break;
		case VK_INSERT:
			outkey = Event::KeyInsert;
			break;
		case VK_DELETE:
			outkey = Event::KeyDelete;
			break;
		case VK_F1:
			outkey = Event::KeyF1;
			break;
		case VK_F2:
			outkey = Event::KeyF2;
			break;
		case VK_F3:
			outkey = Event::KeyF3;
			break;
		case VK_F4:
			outkey = Event::KeyF4;
			break;
		case VK_F5:
			outkey = Event::KeyF5;
			break;
		case VK_F6:
			outkey = Event::KeyF6;
			break;
		case VK_F7:
			outkey = Event::KeyF7;
			break;
		case VK_F8:
			outkey = Event::KeyF8;
			break;
		case VK_F9:
			outkey = Event::KeyF9;
			break;
		case VK_F10:
			outkey = Event::KeyF10;
			break;
		case VK_F11:
			outkey = Event::KeyF11;
			break;
		case VK_F12:
			outkey = Event::KeyF12;
			break;
		default:
			outkey = (int)MapVirtualKey((UINT)key, 2);
			if (outkey >= 'A' && outkey <= 'Z') {
				outkey = tolower(outkey);
			}
			break;
	}

	return outkey;
}

typedef struct {
	/* Layout these fields according to how they are stored in the LPARAM */
	unsigned int nRepeatCount		: 16;
	unsigned int nScanCode			: 8;
	unsigned int nExtended			: 1;
	unsigned int nReserved			: 4;
	unsigned int nContextCode		: 1;
	unsigned int nPrevKeyState		: 1;
	unsigned int nTransitionState	: 1;
} tKEYBOARD;

void Tiki::RecvEvent(UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	int mod = 0;
	tKEYBOARD event = {0};

	if(GetKeyState(VK_SHIFT) & 0x80) mod |= Event::KeyShift;
	if(GetKeyState(VK_CONTROL) & 0x80) mod |= Event::KeyControl;
	if(GetKeyState(VK_MENU) & 0x80) mod |= Event::KeyAlt;

	switch(iMsg)
	{
		case WM_KEYDOWN:
		{
			memcpy(&event,&lParam,sizeof(LPARAM));

			Event evt(Event::EvtKeyDown);
            evt.dev = win32kb;
			evt.key = translateFn(wParam, lParam);
			evt.mod = mod;
			
			if (!event.nPrevKeyState)
			{
				sendEvent(evt);
			}

			evt.type = Event::EvtKeypress;
			for (int i=0; i<event.nRepeatCount; i++)
				sendEvent(evt);
		}
		break;

		case WM_KEYUP:
		{
			Event evt(Event::EvtKeyUp);
			evt.dev = win32kb;
			evt.key = translateFn(wParam, lParam);
			evt.mod = mod;
			sendEvent(evt);
		}
		break;

		case WM_MOUSEMOVE:
		{
			Event evt(Event::EvtMouseMove);
			evt.dev = win32mouse;
			evt.x = LOWORD(lParam); 
			evt.y = HIWORD(lParam);
			sendEvent(evt);
		}
		break;

		case WM_LBUTTONUP:
		case WM_LBUTTONDOWN:
		{
			Event evt(iMsg==WM_LBUTTONDOWN?Event::EvtBtnPress:Event::EvtBtnRelease);
			evt.dev = win32mouse;
			evt.btn = Event::MouseLeftBtn;
			evt.x = LOWORD(lParam); 
			evt.y = HIWORD(lParam);
			sendEvent(evt);
		}
		break;

		case WM_MBUTTONUP:
		case WM_MBUTTONDOWN:
		{
			Event evt(iMsg==WM_MBUTTONDOWN?Event::EvtBtnPress:Event::EvtBtnRelease);
			evt.dev = win32mouse;
			evt.btn = Event::MouseMiddleBtn;
			evt.x = LOWORD(lParam); 
			evt.y = HIWORD(lParam);
			sendEvent(evt);
		}
		break;

		case WM_RBUTTONUP:
		case WM_RBUTTONDOWN:
		{
			Event evt(iMsg==WM_RBUTTONDOWN?Event::EvtBtnPress:Event::EvtBtnRelease);
			evt.dev = win32mouse;
			evt.btn = Event::MouseRightBtn;
			evt.x = LOWORD(lParam); 
			evt.y = HIWORD(lParam);
			sendEvent(evt);
		}
		break;
#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400) //WM_MOUSEWHEEL requires Windows 98 or above
		case WM_MOUSEWHEEL:
		{
			Event evt(Event::EvtBtnPress);
			evt.dev = win32mouse;
			evt.btn = (GET_WHEEL_DELTA_WPARAM(wParam) < 0) ? Event::MouseWheelDown : Event::MouseWheelUp;
			evt.x = LOWORD(lParam); 
			evt.y = HIWORD(lParam);
			sendEvent(evt);
		}
		break;
#endif
	}
}














