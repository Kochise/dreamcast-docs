// Timer -- Header File
//
// 
#ifndef __TIMER_H__
#define __TIMER_H__

class CTimer
{
	private:
		UINT id ;
		static CMapWordToPtr timerList ;
		static void stopTimer(int id) ;
		static void FAR PASCAL EXPORT
			timerProc(HWND hwnd, UINT wMsg, int timerId, DWORD dwTime) ;
		
   protected:
		virtual void timer(DWORD dwTime) = 0 ;
		
	public:
		//Constructor
			CTimer() : id(NULL) {};
		//Destructor
			virtual ~CTimer() { stop(); };
		//Use Functions
			BOOL start(UINT msec) ;
			void stop() ;
};

// Define Statics
CMapWordToPtr CTimer::timerList ;

///////////////////////////////////////////////////////////////////////////
//Implementation
//

//Public Member Functions
//
inline
BOOL CTimer::start (UINT msecs)
{
	id = SetTimer(NULL,0,msecs,(FARPROC)timerProc);
	if (id != NULL)
	{		
		timerList.SetAt(id, this);
		return TRUE ;
	}
	else
		return FALSE ;
}

inline
void CTimer::stop()
{
		if (id != NULL)
		{
			stopTimer(id) ;
			id = NULL ;
		}
}

// Private Member Functions
//

static void CTimer::stopTimer(int timerId)
{
	KillTimer(NULL, timerId) ;
	timerList.RemoveKey(timerId) ;
}

static void FAR PASCAL EXPORT
CTimer::timerProc(HWND hwnd, UINT wMsg, int timerId, DWORD dwTime)
{
	CTimer * pseudoThis ;
	if ( timerList.Lookup(timerId, (void*&)pseudoThis) )
	{
		if ( pseudoThis != (CTimer *)NULL )
			pseudoThis->timer(dwTime) ;
		else 
			stopTimer(timerId) ;	
   }
	else
		KillTimer(NULL,timerId) ;
}

#endif

