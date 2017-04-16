/***************************************************************************/
/*                 File: classes.h (contains C++ class declarations)       */
/***************************************************************************/


/***************************************************************************/
/*                 INCLUDES                                                */
/***************************************************************************/


#include <windows.h>
#include <stdlib.h>
#include "frogfly.h"


/***************************************************************************/
/*                 global variables                                        */
/***************************************************************************/

class pond;

#ifdef CLASSES

CRITICAL_SECTION csSerializeDraw;
pond *the_pond;

#else

char szAppName[] = "frogfly";   // The name of this application
char szTitle[]   = "No simulation in progress"; // The title bar text

extern CRITICAL_SECTION csSerializeDraw;
extern pond *the_pond;

#endif

/***************************************************************************/
/*                 data types                                              */
/***************************************************************************/

class animated_object;

typedef struct _A_OBJECTS
{ animated_object *ptObject;
  short type;
} A_OBJECTS;

/***************************************************************************/
/*                 Class declarations                                      */
/***************************************************************************/



class pond
{ private:
    int iFrogIndex;
    A_OBJECTS obArray[MAX_OBJECTS];
    short iCurrentPointer;
    int iObjectCount[2];
  public:
    pond(const HWND,const HINSTANCE);
    ~pond(void);
    void Initialize(void);
    void Remove(const int iHandle);
    BOOL NewCoordinates(const int,const int,const int);
    int ReturnObjectCount(const short);
    BOOL CreateObject(const short);
    void KillFrog(void);
    int RetrieveFrogCalories(void);
    void SetFrogVelocity(const int,const int);
    int iPondWidth;
    int iPondHeight;
    HWND hWndApplication;
    HINSTANCE hInst;

};

/* animated_object: base class for frogs and flies */

class animated_object
{ private: 		        /* PRIVATE MEMBERS FOLLOW HERE */
    long MoveAndDraw(void);
    virtual BOOL ObjectSpecificThreadRoutine(const HDC) = 0;
    long friend WINAPI ObjectThreadRoutine(animated_object *);
    int iImageWidth,iImageHeight; /* describe the extensions of the object's */
                                  /* visible image */
    HBITMAP hImage;   	/* handle to the image (brush or bitmap) that represents */
                        /* the object on the screen */
    HANDLE hThread;     /* Thread associated with the object */
    int dwIDThread;     /* needed by the CreateThread() function */
    BOOL bFinished;     /* when set to TRUE, the object will die */
  protected:		    /* PROTECTED MEMBERS FOLLOW HERE */
    int iCalories;      /* to keep track of the object's health */
    signed int iTempXVel, iTempYVel;
    signed int iXVelocity, iYVelocity;  /* current x/y velocity */
  public:               /* PUBLIC MEMBERS FOLLOW HERE */
    int iHandle;
    int iX, iY;         /* current object's coordinated */
    BOOL iStatus;       /* TRUE if the object could be created successfully */
    void SetVelocity(const int,const int);
    animated_object(const LPSTR,const short,const int); 	/* constructor */
    ~animated_object(void);       /* destructor  */
    int RetrieveCalories(void);	  /* retrieves calorie count */
    BOOL AddCalories(const int);  /* changes calorie count */
};


/***************************************************************************/
/*                 derived class declarations                              */
/***************************************************************************/


class frog: public animated_object
{ private:
  public :
    int iKilling;
    frog(const int);
    BOOL ObjectSpecificThreadRoutine(const HDC);
};


class fly: public animated_object
{ private:
  public :
    fly(const int);
    BOOL ObjectSpecificThreadRoutine(const HDC);
};
