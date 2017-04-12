//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This source code is a part of BCGControlBar library.
// You may use, compile or redistribute it as part of your application 
// for free. You cannot redistribute it as a part of a software development 
// library without the agreement of the author. If the sources are 
// distributed along with the application, you should leave the original 
// copyright notes in the source code without any changes.
// This code can be used WITHOUT ANY WARRANTIES on your own risk.
// 
// For the latest updates to this library, check my site:
// http://welcome.to/bcgsoft
// 
// Stas Levin <bcgsoft@yahoo.com>
//*******************************************************************************

#ifndef __BCGSOUND_H
#define __BCGSOUND_H

#define BCGSOUND_NOT_STARTED	(-2)
#define BCGSOUND_TERMINATE		(-1)
#define BCGSOUND_IDLE			0
#define BCGSOUND_MENU_COMMAND	1
#define BCGSOUND_MENU_POPUP		2

void BCGPlaySystemSound (int nSound);

#endif // __BCGSOUND_H
