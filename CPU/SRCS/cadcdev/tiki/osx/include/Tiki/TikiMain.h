//
//  TikiMain.h
//  TikiTest
//
//  Created by Dan Potter on 1/15/05.
//  Copyright 2005 Cryptic Allusion, LLC. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <pthread.h>

@interface TikiMain : NSObject
{
    unsigned int  width, height;
    unsigned int  colorBits;
    unsigned int  depthBits;
    
    NSWindow	* mainWindow;
    NSView	* mainView;
    pthread_t	glThreadHnd;
    void	(*mainFunc)(int, char**);
		NSString * openFile;
}

- (void) doMainWithWindow: (NSWindow *)mainWindow andView: (NSView *)mainView
	andMainFunc: (void (*)(int, char**))mainFunc;

- (void) doMainWithWindow: (NSWindow *)mainWindow andView: (NSView *)mainView
	andMainFunc: (void (*)(int, char**))mainFunc andOpenFile: (NSString *)openFile;

- (void) quitSoon;

@end
