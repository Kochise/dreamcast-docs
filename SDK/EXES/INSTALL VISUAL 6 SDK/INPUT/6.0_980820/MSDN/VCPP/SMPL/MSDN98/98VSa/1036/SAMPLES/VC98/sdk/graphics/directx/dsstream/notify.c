// ===============================================================
// notify.c
// ===============================================================
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>

#include <dsound.h>
#include "dsstream.h"

// externs 
extern LPDIRECTSOUNDBUFFER lpDSBStreamBuffer;
extern LPDIRECTSOUNDNOTIFY lpDirectSoundNotify;
extern WAVEINFOCA wiWave;
extern HWND  hWndMain;
 
// function prototypes
void UpdateProgressBar(void);

// ===============================================================
// HandleNotifications
//	Deals with the notification events.
//	Two events have been defined in SetNotifications().
//	The first (index 0) handles position notifications, triggered
//	after wiWave.dwNotifySize bytes and the second event deals with
//	the stop notification.
//	Initally, the entire buffer is filled with the FillDataBuffer()
//	call, when the user asks the stream to play. With each subsequent
//	notification, handled by this function, the rest of the file 
//	is read into the buffer.
// ===============================================================
DWORD HandleNotifications(LPVOID lpvoid)
{
	DWORD hr = DS_OK;
#ifdef DEBUG
	DWORD dwPlayPos, dwWritePos;
#endif
	DWORD hRet = 0;

	while((hRet = WaitForMultipleObjects(2, hNotifyEvent, FALSE, INFINITE))!= WAIT_FAILED)
	{
		if (wiWave.bDonePlaying == TRUE)
		{
			DPF(0, "Posting stop message");
			UpdateProgressBar();
			SendMessage( hWndMain, WM_DSSTREAM_DONE, (WPARAM)0, (LPARAM)0 );
			break; //quit while loop.
		}

		// Deal with the event that got signalled.
		switch(hRet-WAIT_OBJECT_0)
		{
		case 0:
			{	// A play notification has been received.
				LPBYTE lpWrite1;
				DWORD dwWrite1;
				UINT cbActual = 0;
				// update the progress slider and wiWave.dwProgress.
				UpdateProgressBar();

				// If the entire file has been read into the buffer, bFoundEnd will be TRUE.
				if (!wiWave.bFoundEnd)
				{	// read in more of the file.
					DPF(0, "Received a notify event with FoundEnd = FALSE. NR = %lu", wiWave.dwNextWriteOffset );
#ifdef DEBUG
					hr = lpDSBStreamBuffer->lpVtbl->GetCurrentPosition(lpDSBStreamBuffer, &dwPlayPos, &dwWritePos);
					DPF(1, "dwPlayPos = %lu and dwWritePos = %lu", dwPlayPos, dwWritePos);
#endif					
					// Lock the buffer.
					hr = lpDSBStreamBuffer->lpVtbl->Lock(lpDSBStreamBuffer, 
														wiWave.dwNextWriteOffset, 
														wiWave.dwNotifySize, 
														&lpWrite1, &dwWrite1,
														NULL, NULL, 0);
					if (hr != DS_OK)
					{
						DPF(0, "couldn't lock buffer with hr = %lu", hr);
						return hr;
					}

					if (dwWrite1 < wiWave.dwNotifySize)
					{
						DPF(0, "Lock returned number of bytes and requested size differ");
					}
					
					// now read the file. 
					hr = WaveReadFile(wiWave.hmmio, dwWrite1, lpWrite1, &wiWave.mmck, &cbActual);

					//	if cbActual is less than the amount asked for, we may have
					//	reached end of file. If we are looping, we will simply read the 
					//	file in again until we have written dwWrite1 bytes into the buffer.
					//	If not looping we fill with silence.
					if ((DWORD)cbActual < dwWrite1)
					{
						DPF(3, "ReadFile read less than what we asked for. less by %lu", dwWrite1-(DWORD)cbActual);
						if (!wiWave.bLoopFile)
						{
							wiWave.bFoundEnd = TRUE;
							// fill up the rest of the buffer with silence.
							DPF(0, "Filling in silence");
							FillMemory( lpWrite1+cbActual, (UINT)dwWrite1-cbActual, 
										(BYTE)(wiWave.pwfx->wBitsPerSample == 8 ? 128 : 0));
						}
						else
						{	// we're looping. Read in the file again.
							int nChkErr = 0;
							UINT cbWritten = cbActual;	// from previous call above.
							DPF(0, "Looping so read in file again");
							while (cbWritten < (UINT)dwWrite1)	// write only one notification worth.
							{	// this will keep reading in until the buffer is full. For very short files.
								nChkErr = WaveStartDataRead( &wiWave.hmmio, &wiWave.mmck, &wiWave.mmckInRIFF );
								ASSERT(nChkErr == 0);	// we've already this before so shouldn't fail.
								nChkErr = WaveReadFile(wiWave.hmmio, (UINT)dwWrite1-cbWritten, 
														lpWrite1 + cbWritten, &wiWave.mmck, &cbActual);
								ASSERT(nChkErr == 0);	// we've already this before so shouldn't fail.
								cbWritten += cbActual;
							} // while
							ASSERT(wiWave.bFoundEnd == FALSE);
						}// if or not looping
					}

					//unlock now
					hr = lpDSBStreamBuffer->lpVtbl->Unlock(lpDSBStreamBuffer, (LPVOID)lpWrite1, dwWrite1,  NULL, 0 );
					// setup the nextwrite offset.
					wiWave.dwNextWriteOffset += dwWrite1;
					if (wiWave.dwNextWriteOffset >= wiWave.dwBufferSize)
						wiWave.dwNextWriteOffset -= wiWave.dwBufferSize;
				}// if !bFoundEnd.
				else
				{	
					// We have read in the whole file. We will keep filling in silence
					// in the buffer to allow the remaining sound bytes filled earlier 
					// to be played. 
					DPF(1, "Received a notify event and bFoundEnd = TRUE");
					ASSERT(wiWave.bLoopFile == FALSE);
#ifdef DEBUG					
					// if we've read all the file and we're not looping, 
					hr = lpDSBStreamBuffer->lpVtbl->GetCurrentPosition(lpDSBStreamBuffer, &dwPlayPos, &dwWritePos);
					DPF(1, "dwPlayPos = %lu and dwWritePos = %lu", dwPlayPos, dwWritePos);
#endif
					// Allow the rest of the bytes to be played and fill here
					// with silence. The next notification will quit the while loop.
					hr = lpDSBStreamBuffer->lpVtbl->Lock(lpDSBStreamBuffer, 
													wiWave.dwNextWriteOffset, 
													wiWave.dwNotifySize, 
													&lpWrite1, &dwWrite1,
													NULL, NULL, 0);
					DPF(0, "Filling in silence");
					FillMemory(lpWrite1, dwWrite1,(BYTE)(wiWave.pwfx->wBitsPerSample == 8 ? 128 : 0));

					hr = lpDSBStreamBuffer->lpVtbl->Unlock(lpDSBStreamBuffer, (LPVOID)lpWrite1, dwWrite1,  NULL, 0 );

					// We don't want to cut off the sound before it's done playing.
					// If doneplaying is set, the next notification event will post a stop message.
					if (wiWave.mmckInRIFF.cksize > wiWave.dwNotifySize &&
							wiWave.dwProgress >= wiWave.mmckInRIFF.cksize - wiWave.dwNotifySize)
					{
						wiWave.bDonePlaying = TRUE;
					}
					else	// for short files.
						if (wiWave.dwProgress >= wiWave.mmckInRIFF.cksize)
							wiWave.bDonePlaying = TRUE;
				}// else
			}
			break;

		case 1:
			{	// A stop notification has been received.
				DPF(0, "Received the stop event");
				// update ui.
				//UpdateProgressBar();
#ifdef DEBUG
				hr = lpDSBStreamBuffer->lpVtbl->GetCurrentPosition(lpDSBStreamBuffer, &dwPlayPos, &dwWritePos);
				DPF(1, "dwPlayPos = %lu and dwWritePos = %lu", dwPlayPos, dwWritePos);
#endif
				// Set bDonePlaying to True. 
				wiWave.bDonePlaying = TRUE;
				// call stop.
				if (lpDSBStreamBuffer)
				{
					hr = lpDSBStreamBuffer->lpVtbl->Stop(lpDSBStreamBuffer);
					ASSERT(hr == DS_OK);	// why would this fail in tis app?
				}
				CloseHandle(hNotifyEvent[0]);
				CloseHandle(hNotifyEvent[1]);
				hNotifyEvent[0] = hNotifyEvent[1] = (HANDLE)NULL;
				break;
			}

		default:
			ASSERT(FALSE);	// we should never fall in here.
			break;

		}// end switch

	} // while

	//UpdateProgressBar();
	DPF(0, "Exiting thread");
	return TRUE;
} //handlenotifications()

// ===========================================================
// UpdateProgressBar
// Gets the current play position and updates the progress
// bar accordingly.
// ===========================================================
void UpdateProgressBar(void)
{
	DWORD dwPlayPos, dwWritePos;
	int hr = 0; 
	DWORD dwPlayed = 0;

	hr = lpDSBStreamBuffer->lpVtbl->GetCurrentPosition(lpDSBStreamBuffer, &dwPlayPos, &dwWritePos);
	if (hr != DS_OK)
	{
		DPF(0, "getCurrentPos returned failure");
	}

	DPF(1, "CurrentPos = %lu and LastPos = %lu", dwPlayPos, wiWave.dwLastPos);

	if (dwPlayPos < wiWave.dwLastPos)
	{
		dwPlayed = wiWave.dwBufferSize - wiWave.dwLastPos + dwPlayPos;
	}
	else
	{
		dwPlayed = dwPlayPos - wiWave.dwLastPos;
	}

	wiWave.dwProgress += dwPlayed;

	wiWave.dwLastPos = dwPlayPos;

	DPF(1, "wiWave.dwProgress =  %lu", wiWave.dwProgress);
	DPF(1, "Posting %lu", wiWave.dwProgress); 
	PostMessage( hWndMain, WM_DSSTREAM_PROGRESS, 0L, wiWave.dwProgress );
}
