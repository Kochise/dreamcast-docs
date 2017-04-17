#ifndef __CRITSECT_H            // guard against multiple inclusion
#define __CRITSECT_H

/********************************************************************
 * critsec.h
 *
 * Description
 *    CCriticalSection
 ********************************************************************/

/********************************************************************
 * class CCritcalSectoin
 *
 * Description
 *    Wrapper class for CRITICAL_SECTION functionality of Windows CE.
 *    See Windows documentation on CRITICAL_SECTION for more 
 *    information.
 ********************************************************************/
class CCriticalSection
{
    public:
        // Constructor/Destructor (initialize/delete critical section)
        CCriticalSection(void)   
            { InitializeCriticalSection(&_cs); }
        ~CCriticalSection(void)  
            { DeleteCriticalSection(&_cs);     }

        // Enter/Leave
        void Enter(void)         
            { EnterCriticalSection(&_cs);      }
        void Leave(void)         
            { LeaveCriticalSection(&_cs);      }
 
    private:
        CRITICAL_SECTION _cs;   // Windows CRITICAL_SECTION instance
};

#endif // __CRITSECT_H
