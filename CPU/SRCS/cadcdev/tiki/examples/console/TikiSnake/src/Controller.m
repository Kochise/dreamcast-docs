#import "Controller.h"
#import <Tiki/TikiMain.h>
#import <assert.h>

void tiki_main();

@implementation Controller

- (void) applicationDidFinishLaunching: (NSNotification *) note
{
	NSString * resPath = [[NSBundle mainBundle] resourcePath];
	chdir([resPath cString]);
	TikiMain * otm = [[TikiMain alloc] retain];
	tm = otm;
	[tm doMainWithWindow: mainWindow andView: mainView andMainFunc: tiki_main];
	tm = nil;
	[otm release];
}

- (NSApplicationTerminateReply) applicationShouldTerminate: (NSApplication *)sender
{
	assert( tm );
	[tm quitSoon];
	return NSTerminateNow;
}

- (BOOL) applicationShouldTerminateAfterLastWindowClosed: (NSApplication *)theApplication
{
        return YES;
}

@end
