/* Controller */

#import <Cocoa/Cocoa.h>
#import <Tiki/TikiMain.h>

@interface Controller : NSObject
{
    IBOutlet NSView *mainView;
    IBOutlet NSWindow *mainWindow;
    
    TikiMain * tm;
}
@end
