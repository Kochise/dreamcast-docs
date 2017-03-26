#import "Controller.h"
#import <Tiki/TikiMain.h>
#import <assert.h>

void tiki_main();

@implementation Controller
- (BOOL)application:(NSApplication *)theApplication openFile:(NSString *)filename
{
	openFileName = filename;
}

- (void) applicationDidFinishLaunching: (NSNotification *) note
{
	TikiMain * otm = [[TikiMain alloc] retain];
	tm = otm;
	[tm doMainWithWindow: mainWindow andView: mainView andMainFunc: tiki_main andOpenFile:openFileName];
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
