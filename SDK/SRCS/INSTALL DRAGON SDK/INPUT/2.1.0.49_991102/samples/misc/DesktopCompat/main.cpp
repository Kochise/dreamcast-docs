/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

	
	main.cpp

Abstract:

 	This is the main module for the Desktop Compatibility Sample program.
    
-------------------------------------------------------------------*/
#include "DesktopCompat.hpp"



// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application
int g_imageX = 0, g_imageY= 0;                      // global coordinates of the Bitmap
HDC g_hNewDeviceEvent;


// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
LPDIRECTDRAWSURFACE g_pddsSample;                   // The sample bitmap to display
RECT rcWindow;                                      // the rectangle to blit the bitmap



// ++++ Local Functions +++++++++++++++++++++++++++++++++++++++++++++
static BOOL RenderSceneToBackBuffer();
static BOOL AppInit(HINSTANCE hPrev,int nCmdShow);



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    AppInit

Description:

    This function registers a window class, and creates a window for
    the application.  In addition, it calls the appropriate functions to
	initialize DirectDraw, DirectSound, and DirectInput.

Arguments:

    hPrev               - Hinstance of another process running the program

    nCmdShow            - Whether the app should be shown (ignored)

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
AppInit(HINSTANCE hPrev, int nCmdShow)
{
	TCHAR     tszAppName[] = TEXT("Desktop Compatibility Sample");            // The App's Name
    WNDCLASS  cls;          
	
	if (!hPrev)
    {
        //  Register a class for the main application window

#ifdef UNDER_CE
		cls.hCursor        = NULL;
		cls.style          = 0;

#else  // Desktop
		cls.hCursor        = LoadCursor(NULL, IDC_ARROW);
		cls.style          = CS_VREDRAW | CS_HREDRAW;

#endif	//UNDER_CE

		cls.hIcon          = NULL;
        cls.lpszMenuName   = NULL;
        cls.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
        cls.hInstance      = g_hinst;
        cls.lpszClassName  = tszAppName;
        cls.lpfnWndProc    = (WNDPROC)WndProc;
        
        cls.cbWndExtra     = 0;
        cls.cbClsExtra     = 0;

        if (!RegisterClass(&cls))
            return FALSE;
    }

#ifdef UNDER_CE
	g_hwndApp = CreateWindowEx (0, tszAppName, tszAppName, 
		WS_VISIBLE , 0, 0, WINWIDTH,
		WINHEIGHT,NULL, NULL, g_hinst, NULL);
    
#else // Desktop
	g_hwndApp = CreateWindowEx (0, tszAppName, tszAppName, 
		WS_VISIBLE | WS_POPUP | WS_SYSMENU | WS_CAPTION | WS_OVERLAPPEDWINDOW
		, 0, 0, WINWIDTH, WINHEIGHT, NULL, NULL, g_hinst, NULL);

#endif //UNDER_CE


    // Initialize DirectDraw
	if (!InitDirectDraw()){
        ErrorMessage( g_hwndApp, TEXT("Failed to initialize DirectDraw."));
		return 0;
	}

	// Initialize DirectInput
    if ( !InitDirectInput() ) {
        ErrorMessage( g_hwndApp, TEXT("Failed to initialize DirectInput."));
   	    return 0;
	}
	// Load the sample bitmap into an offscreen directdraw surface
	g_pddsSample = LoadBitmapToDDS(TEXT("DREAMCAST_BITMAP"));
	if (!g_pddsSample){
		ErrorMessage( g_hwndApp, TEXT("Could not load Sample Bitmap"));
        return 0;
	}
	// Initialize DirectSound
	if(!InitDirectSound()){
        ErrorMessage( g_hwndApp, TEXT("Failed to initialize DirectSound."));
		return 0;
	}
	// Load the Sound into the sound buffer

	g_pdsbuffer = LoadSoundBuffer(TEXT("SOUND1"));
	if(g_pdsbuffer == NULL){
		ErrorMessage(NULL, TEXT("Failed to load the sound buffer"));
		return 0;
	}
	g_pdsbuffer2 = LoadSoundBuffer(TEXT("SOUND2"));
	if(g_pdsbuffer2 == NULL){
		ErrorMessage(NULL, TEXT("Failed to load the sound buffer"));
		return 0;
	}
	
	return TRUE;

	


}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CleanUp

Description:

    Cleans up after the application is done.  Frees allocated memory

Arguments:

    None 
  
Return Value:

    None

-------------------------------------------------------------------*/
void
CleanUp()
{

    // Release the primary surface.
    if (g_pddsPrimary)        
        g_pddsPrimary->Release();


	// Release the DD object
    if (g_pdd)                
        g_pdd->Release();  
    
#ifdef UNDER_CE
	// Close the handle to the New Device Event.	
	if (g_hNewDeviceEvent != NULL)
        CloseHandle(g_hNewDeviceEvent);

#endif //ndef UNDER_CE


	// Release the DI Object	
	if(g_pdi)
		g_pdi->Release();

	// Release the Sound buffers.
	if(g_pdsbuffer)
		g_pdsbuffer->Release();
	
	if(g_pdsbuffer2)
		g_pdsbuffer2->Release();
	
	//Release the Sound Object
	if(g_pds)
		g_pds->Release();


	     
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WndProc

Description:

    Window message processing routine for the main application window.
    The main purpose of this function is to exit the app when the user
    presses <Escape> and to pull out the device selection box when the
	user presses <F1> if he is not on UNDER_CE mode.

Arguments:

    HWND hWnd           - Window handle

    UINT uMessage       - Message identifier
  
    WPARAM wParam       - First message parameter
    
    LPARAM lParam       - Second message parameter
  
Return Value:

    Zero if the message was processed.  The return value from 
    DefWindowProc otherwise.

-------------------------------------------------------------------*/
LRESULT CALLBACK
WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
    {


		// The move and Size messages are not defined under the DreamCast.

#ifndef UNDER_CE
	case WM_MOVE:
	case WM_SIZE:
		// Our window position has changed, so
		// get the client (drawing) rectangle.
		GetClientRect( hWnd, &rcWindow );
		// Convert the coordinates from client relative
		// to screen relative.
		ClientToScreen( hWnd, ( LPPOINT )&rcWindow );
		ClientToScreen( hWnd, ( LPPOINT )&rcWindow + 1 );
		return 0;
		break;
#endif //ndef UNDER_CE
	
	case WM_KEYDOWN:
        {
			switch (wParam){
			case VK_ESCAPE:
			case VK_F12:
				DestroyWindow(hWnd);
				return 0;
				break;
			} // switch (wParam)
			break;
		}
	case WM_DESTROY:
		{
			// Cleanup DirectX structures
			CleanUp();
			
			PostQuitMessage(0);
			return 0L;
			break;	
		}
	} // switch (message)
	
    return DefWindowProc (hWnd, uMessage, wParam, lParam);
}



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    UpdateFrame

Description:

    This function is called whenever the CPU is idle.  The application
    should update it's state and rerender to the screen if appropriate.

Return Value:

    None.

-------------------------------------------------------------------*/
void 
UpdateFrame ()
{
	RECT s_rcDest = {g_imageX, g_imageY, g_imageX + ImageWidth , g_imageY + ImageHeight};
	RECT temp = {0, 0, WINWIDTH,WINHEIGHT};
    DDBLTFX     ddbltfx;

    // Clear the back buffer.
    memset(&ddbltfx,0,sizeof(DDBLTFX));
    ddbltfx.dwSize = sizeof(DDBLTFX);
    ddbltfx.dwFillColor = 0;
    
    g_pddsSecondary->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
	// Draw the sample bitmap to the back buffer
    
	g_pddsSecondary->Blt(&s_rcDest, g_pddsSample, NULL, DDBLT_WAIT, NULL);


	// Under the Desktop windowed mode, blt the secondary surface into the primary, 
	// Under the DreamCast, Use Flip .

#ifdef UNDER_CE
	g_pddsPrimary->Flip(NULL, DDFLIP_WAIT);
	
#else // Desktop
	g_pddsPrimary->Blt(&rcWindow, g_pddsSecondary, &temp, DDBLTFAST_WAIT, NULL);

#endif //UNDER_CE



}    


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WinMain

Description:

    This is the entrypoint for this sample app.  It creates an app
    window and then enters a message loop.

Arguments:

    hInstance           - HInstance of the process

    hPrev               - HInstance of another process running the program

    LPTSTR lpCmdLine    - Pointer to command line string

    nCmdShow            - Whether the app should be shown (ignored)

Return Value:

    We normally return the wParam value from the WM_QUIT message.  If
    there's a failure upon initialization, we just return 0.

-------------------------------------------------------------------*/
extern "C" int APIENTRY 
_tWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    MSG msg;

    // Store Instance handle for use later...
    g_hinst = hInstance;

    // Call initialization procedure
    if (!AppInit(hPrevInstance,nCmdShow))
        return 0L;



    // Main Message loop
    while (TRUE)
    {
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            // There's a message waiting in the queue for us.  Retrieve
            // it and dispatch it, unless it's a WM_QUIT.

            if (msg.message == WM_QUIT) 
               return msg.wParam;

            TranslateMessage(&msg); 
            DispatchMessage(&msg);
        }
        else
        {
            // If no messages pending, then update the frame, and 
			// get the user's Input.
           
			PollDevices();

            // Now, while the poll is happening in the background, 
            // Render the frame
            UpdateFrame();

            // After a reasonable amount of time the data should be ready.  If it's not ready yet, GetData will block until it is.
            GetDeviceData();

            // Check for new devices plugged in.
            CheckNewDevices();

		}
    }

    return msg.wParam;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function:
		MoveImage
	
	Description:
  
		Moves the image by altering the values of g_imageX and g_imageY.  The function
		checks if the image is still inside the display surface.

	Arguments:
		
		value - an integer: the value to be moved in either directions

		direction - a bool: false implies moving in the x direction, 		
							true implies moving in the y direction.

	Return Value:

		The function returns true on success

 -------------------------------------------------------------------*/

int  MoveImage(int MoveValue, bool direction){
	
	
	if(!direction){
		
		int NewX = g_imageX + MoveValue;
		
		// If passed the border from the left.
		if(NewX < 0) {
			g_pdsbuffer->Play(0, 0, 0);
			NewX = 0;
		}
		// If passed the border from the Right.
		else if(NewX + ImageWidth > WINWIDTH) {
			g_pdsbuffer->Play(0, 0, 0);
			NewX = WINWIDTH - ImageWidth;
		}
		g_imageX = NewX;	
	}
	else {
		
		int NewY = g_imageY + MoveValue;
		
		// If passed the border from the top.
		if(NewY < 0) {
			g_pdsbuffer->Play(0, 0, 0);
			NewY = 0;
		}
		// If passed the border from the Bottom.
		else if(NewY+  ImageHeight > WINHEIGHT) {
			g_pdsbuffer->Play(0, 0, 0);
			NewY= WINHEIGHT - ImageHeight;
		}
		g_imageY = NewY;	
	}
	return true;
}
	



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
	Function:
	
		Error Message
	
	Description:
  
		Displays an error message. if runnning under the  desktop environment
		a MessageBox is displayed, else textout is used to display the text 
		on the DreamCast
		
	Arguments:
		
		hWnd   - a handle to a window on which to display the error message if uding MessageBox
		
		lpText - The text of the error message


	Return Value:
		
		None
-------------------------------------------------------------------*/

void ErrorMessage(HWND hWnd, LPTSTR lpText)
{

#ifdef UNDER_CE
	HDC hdc;
	if (FAILED(g_pddsPrimary->GetDC(&hdc)))
		return ;
	ExtTextOut( hdc, 0, 0, 0, NULL, lpText, _tcslen(lpText), NULL);
	g_pddsPrimary->ReleaseDC(hdc);
	OutputDebugString(lpText);
	
#else //Desktop
	MessageBox(hWnd, lpText, "Error", MB_ICONERROR | MB_OK);

#endif //UNDER_CE

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    DebugOutput

Description:

    Simple Debug Output mechanism.  If DEBUG is TRUE, then the function
    outputs the passed-in String and variables to the debug output
    Stream.  Otherwise, the function does nothing

Arguments:

    TCHAR *tszDest       - TEXT String to output if an error occurred

    ... (variable arg)   - List of variable arguments to embed in output
                           (similar to printf format)

Return Value:

    None

-------------------------------------------------------------------*/

void DebugOutput(TCHAR *tszErr, ...)
{

    TCHAR tszErrOut[256];
    va_list valist;

    va_start (valist,tszErr);
    wvsprintf (tszErrOut, tszErr, valist);
    OutputDebugString (tszErrOut);

    va_end (valist);

}


