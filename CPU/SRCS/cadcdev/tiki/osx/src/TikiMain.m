//
//  TikiMain.m
//  TikiTest
//
//  Created by Dan Potter on 1/15/05.
//  Copyright 2005 Cryptic Allusion, LLC. All rights reserved.
//

#import "TikiMain.h"
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>
#import <OpenGL/glext.h>

#include <unistd.h>
#include <sys/time.h>

@interface TikiMain (PrivateAPI)
- (NSOpenGLPixelFormat *)createPixelFormat;
- (void)glThread;
+ (void)becomeThreadedStatic: (id)obj;
@end

void * glThreadStatic(void *);
void tiki_wait_if_needed();
void TikiRecvQuit();
void TikiRecvEvent(NSEvent * evt);
void TikiRecvMouseEvent(NSEvent * event, NSPoint *point);

static volatile NSOpenGLContext * g_view = NULL;
static NSWindow * g_wnd = NULL;
static int frames = 0;

static void waitgview() {
	while (!g_view) {
		NSLog(@"waiting for view...");
		usleep(1000*1000);
	}
}

static int targetW = 640, targetH = 480;
int tikiShowMouse = 1;

void tiki_set_show_cursor(int visible) {
	tikiShowMouse=visible;
	
	if(visible) {
		[NSCursor unhide];
	} else {
		[NSCursor hide];
	}
}

void tiki_set_window_name(NSString *windowName) {
	[g_wnd setTitle: windowName];
}

void tiki_scene_begin_hook() {
	waitgview();
	[g_view makeCurrentContext];

	tiki_wait_if_needed();
	frames++;
}

void tiki_scene_finish_hook() {
	waitgview();
	[g_view flushBuffer];
}

@implementation TikiMain
- (void) doMainWithWindow: (NSWindow *)iMainWindow andView: (NSView *)iMainView
							andMainFunc: (void (*)(int, char**))iMainFunc
{
	
	[self doMainWithWindow:iMainWindow andView:iMainView andMainFunc:iMainFunc andOpenFile: nil];
}

- (void) doMainWithWindow: (NSWindow *)iMainWindow andView: (NSView *)iMainView
	andMainFunc: (void (*)(int, char**))iMainFunc andOpenFile: (NSString *)iOpenFile
{
	width = targetW;
	height = targetH;
	mainWindow = iMainWindow;
	mainView = iMainView;
	mainFunc = iMainFunc;
	openFile = iOpenFile;
	
	[mainWindow makeKeyAndOrderFront:nil];
	[mainWindow makeFirstResponder:mainView];
	[mainWindow setAcceptsMouseMovedEvents:true]; 
	
	NSDictionary * originalDisplayMode = (NSDictionary *)
		CGDisplayCurrentMode(kCGDirectMainDisplay);
	// depthBits = colorBits = [[originalDisplayMode objectForKey: (id)kCGDisplayBitsPerPixel] intValue];
	depthBits = colorBits = 32;
	NSDictionary * displayMode = (NSDictionary *)CGDisplayBestModeForParameters(
		kCGDirectMainDisplay, colorBits, width, height, NULL);

	NSOpenGLPixelFormat * pixelFormat = [self createPixelFormat];
	NSOpenGLContext * context = [[NSOpenGLContext alloc]
		initWithFormat: pixelFormat shareContext: nil];
	[pixelFormat release];

	// Attach the GL context to the content of the window
	[context setView: mainView];
	g_view = context;

	// Make the context we created be the current GL context
	[context makeCurrentContext];

	// Set the refresh sync on the context
	{
		// Get the underlying CGL context
		CGLContextObj cglContext = CGLGetCurrentContext();
    		long param = 0;
		CGLSetParameter(cglContext, kCGLCPSwapInterval, &param);
	}

	[mainView addTrackingRect:[mainView bounds] owner:mainView userData:nil assumeInside:true];
	
	//// [MapleEventReceiver init];

	// Force us to become threaded.
	[NSThread detachNewThreadSelector:@selector(becomeThreadedStatic:)
		toTarget:[TikiMain class] withObject:self];
		
	// Now start the actual GL thread using pthreads, so we can control its life cycle.
	glThreadHnd = NULL;
	pthread_create(&glThreadHnd, NULL, glThreadStatic, (void *)self);
	
	NSDate * distantPast = [[NSDate distantPast] retain];
	NSDate * distantFuture = [[NSDate distantFuture] retain];
	BOOL done = NO;
	NSAutoreleasePool * pool = nil;
	unsigned int kbNewFlags, kbPreviousFlags = 0, kbChanged, down;
	
	// XXX 'done' is never set to YES!
	// Process events
	while (!done) {
		NSEvent * event;
		NSEventType type;
        
		if (pool)
			[pool release];
		pool = [[NSAutoreleasePool alloc] init];
        
		// This polls for an event.  If there isn't an event read immediately, it will return nil.  In a real game, we would loop until we had processed all pending events and would then go about our normal game processing
		event = [NSApp nextEventMatchingMask:NSAnyEventMask untilDate:distantFuture inMode:NSDefaultRunLoopMode dequeue:YES];
		if (!event) {
			[pool release];
			pool = nil;

			// We'd break out of this loop instead of continuing in a real game (as mentioned above).
			continue;
		}

		// Is the event for us?
		if ([event window] != mainWindow) {
			//NSLog([NSString stringWithFormat: @"Ignoring event not for us: %@", event]);
			[NSApp sendEvent: event];
			continue;
		}
		//NSLog([NSString stringWithFormat: @"%@", event]);

		// Handle the event we got
		type = [event type];
		switch (type) {
		case NSMouseEntered:
			if(!tikiShowMouse) [NSCursor hide];
			break;
		case NSMouseExited:
			[NSCursor unhide];
			break;
		case NSMouseMoved:
		case NSLeftMouseDown:
		case NSLeftMouseUp:		
		case NSRightMouseDown:
		case NSRightMouseUp:
		case NSScrollWheel:
		{
			NSPoint point = [event locationInWindow];
			// make Y start in top left vs bottom left
			NSRect windowSize = [mainWindow frame];
			point.y -= windowSize.size.height;
			point.y *= -1;
			//NSLog([NSString stringWithFormat:@"MouseMove (%f, %f)\n",point.x,point.y]);
			TikiRecvMouseEvent(event, &point);
			
			// give the mouse event up to the app, we will also process it though
			[NSApp sendEvent: event];
		}
			break;
		case NSKeyDown:
		case NSKeyUp:
			/* // Ignore key repeats (we don't turn them off because doing
			// so is risky in case of a program crash).
			if ([event isARepeat])
				break; */
				
			// If Command or Ctrl is down, pass this on to NSApp.
			if (([event modifierFlags] & NSCommandKeyMask) ||
				([event modifierFlags] & NSControlKeyMask))
			{
				[NSApp sendEvent: event];
				break;
			}
			TikiRecvEvent(event);
			//// [MapleEventReceiver processEvent: event];
			// NSLog([NSString stringWithFormat: @"%@", event]);
			break;

		case NSFlagsChanged:
			kbNewFlags = [event modifierFlags];
			kbChanged = kbNewFlags ^ kbPreviousFlags;
                
			/* if (kbChanged & NSControlKeyMask) {
				down = kbNewFlags & NSControlKeyMask;
			}
                
			if (kbChanged & NSCommandKeyMask) {
				down = kbNewFlags & NSCommandKeyMask;
			} */
                
			kbPreviousFlags = kbNewFlags;
                
			break;

		// Any other random events probably need to be passed on!
		default:
			[NSApp sendEvent: event];
			break;
		}
	}
	//// [MapleEventReceiver shutdown];
	if (pool)
		[pool release];

	// Tear down GL
	/* [NSOpenGLContext clearCurrentContext];
	[context clearDrawable];
	[context release];
	[window release]; */
}

- (void) quitSoon
{
	TikiRecvQuit();
	if (glThreadHnd) {
		pthread_join(glThreadHnd, NULL);
		glThreadHnd = NULL;
	}
}

@end

@implementation TikiMain(PrivateAPI)

- (void)glThread
{
	// We need our own autorelease pool for Cocoa.
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	NSLog(@"glThread started");

	// Make sure we've selected our context and have a view.
	tiki_scene_begin_hook();
	
	// We have to do this at least once to make sure Quartz Extreme
	// garbage doesn't sully the display for a bit.
	glClearColor(0,0,0,0);
	glClearDepth(0.0f);
	glClear(GL_COLOR_BUFFER_BIT+GL_DEPTH_BUFFER_BIT+GL_STENCIL_BUFFER_BIT);
	
	tiki_scene_finish_hook();

	assert( mainFunc );

	NSArray *args;
	if(openFile != nil) 
		args = [[[NSProcessInfo processInfo] arguments] arrayByAddingObject:openFile];
	else
		args = [[NSProcessInfo processInfo] arguments];
	
	int argc = [args count];
	
	if(argc > 0) {
		char ** argv = malloc(sizeof(char*) * argc);
		NSString *arg;
		
		for(int i = 0; i < argc; i++) {
			arg = [args objectAtIndex: i];
			argv[i] = malloc([arg length] + 2);
			strncpy(argv[i],[arg cString],[arg cStringLength]);
			argv[i][[arg cStringLength]] = '\0';
		}
		mainFunc(argc, argv);
	} else {
		mainFunc(0, NULL);
	}
	

	NSLog(@"glThread exiting");
	
	[NSApp terminate: self];
	[pool release];
}

void * glThreadStatic(void * anObject) {
	TikiMain * us = (TikiMain *)anObject;
	[us glThread];
}

+ (void)becomeThreadedStatic: (id)obj
{
	/* Do nothing */
}

- (NSOpenGLPixelFormat *) createPixelFormat
{
	NSOpenGLPixelFormatAttribute attributes[] = {
		NSOpenGLPFAColorSize, colorBits,
		NSOpenGLPFADepthSize, depthBits,
		NSOpenGLPFAStencilSize, 8,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAAccelerated,
		NSOpenGLPFAScreenMask, CGDisplayIDToOpenGLDisplayMask(kCGDirectMainDisplay),
		0
	};
	unsigned int attributeCount = sizeof(attributes) / sizeof(attributes[0]);
	return [[NSOpenGLPixelFormat alloc] initWithAttributes: attributes];
}

@end
















