/***************************************************************************/
/*                 File: classes.cpp (contains C++ class declarations)     */
/***************************************************************************/


/***************************************************************************/
/*                 INCLUDES                                                */
/***************************************************************************/

#define CLASSES

#include "classes.hpp"

/***************************************************************************/
/*                 stub function -- see article text                       */
/***************************************************************************/


long WINAPI ObjectThreadRoutine(animated_object *fpObj)
{
  return (fpObj->MoveAndDraw());
}

/***************************************************************************/
/*                 The pond object                                         */
/***************************************************************************/



pond::pond(const HWND hWnd,const HINSTANCE hI)		/* constructor */
{
  hWndApplication = hWnd;
  hInst = hI;
  Initialize();
  iFrogIndex = -1;
};

void pond::Initialize(void)
{
  if (iObjectCount[FROG_TYPE] || iObjectCount[FLY_TYPE])
  {
   MessageBox(GetFocus(),"You must stop the ongoing simulation first",
  			 "Can't restart simulation", MB_OK);
   return;
  };
  iCurrentPointer = 0;
};

pond::~pond(void)     		/* destructor */
{
};

/***************************************************************************/
/*  The following two functions register and unregister new objects        */
/***************************************************************************/

void pond::Remove(const int iHandle)
{ EnterCriticalSection(&csSerializeDraw);
  if (iHandle == iFrogIndex) iFrogIndex = -1;
  delete (obArray[iHandle].ptObject);
  iObjectCount[obArray[iHandle].type]--;
  LeaveCriticalSection(&csSerializeDraw);
};

int pond::ReturnObjectCount(const short sType)
{
  return (iObjectCount[sType]);
};

/***************************************************************************/
/* This member function does all of the collision detection and penalizing */
/* work. Currently, it is fairly dumb -- if it is called from within a fly */
/* object, it checks the new fly coordinates with the frog's coordinates   */
/* and returns FALSE if they only differ by the CLOSENESS constant,        */
/* therebye killing the fly and awarding the frog FLY_NUTRITION_VALUE      */
/* calories. All "intelligence" in collision detection needs to go here.   */
/***************************************************************************/


BOOL pond::NewCoordinates(const int iHandle,const int x,const int y)
{
  BOOL status;
  if (iFrogIndex<0) return(FALSE);
  if (iHandle == iFrogIndex)
     return TRUE;
  status = !(abs(x-obArray[iFrogIndex].ptObject->iX) <= CLOSENESS &&
             abs(y-obArray[iFrogIndex].ptObject->iY) <= CLOSENESS &&
             obArray[iFrogIndex].ptObject->AddCalories(FLY_NUTRITION_VALUE));
  return(status);
};

/***************************************************************************/
/* This is the interface that the pond exports to access the frog.         */
/***************************************************************************/

/***************************************************************************/
/* The implementation of CreateObject can be improved, for example by      */
/* recycling the array entries that belong to objects that have died.      */
/* This would imply adding linked list structures to the array that link   */
/* the free elements together -- I leave the implemenation as an exercise  */
/* to the reader...                                                        */
/***************************************************************************/


BOOL pond::CreateObject(const short iType)
{ if (iCurrentPointer>= MAX_OBJECTS) return FALSE;
  if (iType == FROG_TYPE)
  {
    frog *pObject;
    if (iFrogIndex != -1) return FALSE;
    Initialize();
    pObject = new frog(iCurrentPointer);
    if (!pObject->iStatus)
      {
        delete (pObject);
        return (FALSE);
      };
    iFrogIndex = iCurrentPointer;
    obArray[iCurrentPointer].ptObject=pObject;
  }
  else  /* type must be FLY_TYPE */
  {
    fly *pObject;
    pObject = new fly(iCurrentPointer);
    if (!pObject->iStatus)
      {
        delete (pObject);
        return (FALSE);
      };
    obArray[iCurrentPointer].ptObject=pObject;
  };
  obArray[iCurrentPointer].type=iType;
  iCurrentPointer++;
  iObjectCount[iType]++;
  return(TRUE);

}

void pond::KillFrog(void)
{
  if (iFrogIndex >=0)
    ((frog *)obArray[iFrogIndex].ptObject)->iKilling=STATUS_DEAD;
};

void pond::SetFrogVelocity(const int iX,const int iY)
{
  if (iFrogIndex != -1)
    obArray[iFrogIndex].ptObject->SetVelocity(iX, iY);
};

int pond::RetrieveFrogCalories(void)
{
  if (iFrogIndex != -1)
     return obArray[iFrogIndex].ptObject->RetrieveCalories();
  else
     return -1;
};

/***************************************************************************/
/*                 The animated_object base class definition               */
/***************************************************************************/

animated_object::animated_object(const LPSTR lpImageName,const short sType,const int iObjectHandle)
{
  BITMAP bmpImage;
  bFinished = FALSE;
  iX = rand()%the_pond->iPondWidth;
  iY = rand()%the_pond->iPondHeight;
  iXVelocity=(XVARIATION/2)-rand()%XVARIATION;
  iYVelocity=(YVARIATION/2)-rand()%YVARIATION;
  hImage = LoadBitmap(the_pond->hInst,lpImageName);
  GetObject(hImage,sizeof(BITMAP),&bmpImage);
  iImageWidth=bmpImage.bmWidth;
  iImageHeight=bmpImage.bmHeight;
  iHandle = iObjectHandle;
  hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ObjectThreadRoutine,this,
			 0,(LPDWORD)&dwIDThread);
  iStatus = (hThread != (HANDLE)NULL);
};

animated_object::~animated_object(void)
{
  if (iStatus)
  {
   WaitForSingleObject(hThread,INFINITE);
   CloseHandle(hThread);
  };
  DeleteObject(hImage);
  MessageBeep(-1);
};

int animated_object::RetrieveCalories(void)
{
  return iCalories;
};

BOOL animated_object::AddCalories(const int i)
{ iCalories+= i;
  return (TRUE);
};

void animated_object::SetVelocity(const int iX,const int iY)
{
  iTempXVel = iX;
  iTempYVel = iY;
}


/* this routine is the object-specific thread routine. In a big while
   loop, it constantly recomputes the object's poition and redraws the
   object. */

long animated_object::MoveAndDraw(void)
{ int iTempX, iTempY;
  HDC hDC;
  while(!bFinished)
    {
      iTempX = iX+iXVelocity;
      iTempY = iY+iYVelocity;

/* The next four IF statements check if a wall has been hit after a move.
   If yes, the position is reset to the wall, the direction reversed
   and a random value added. */

      if(iTempX <= 0)    				        /* hit left wall? */
        {
         iTempX =0;
         iXVelocity=(XVARIATION/2)-rand()%XVARIATION;
        };
      if(iTempX >= the_pond->iPondWidth-iImageWidth)	/* hit right wall? */
       {
        iTempX = the_pond->iPondWidth-iImageWidth;
        iXVelocity=0-((XVARIATION/2)-rand()%XVARIATION);
       };
      if(iTempY <= 0) 					/* hit upper wall? */
       {
        iTempY =0;
        iYVelocity=(YVARIATION/2)-rand()%YVARIATION;
       };
      if(iTempY >= the_pond->iPondHeight-iImageHeight)	/* hit lower wall? */
       {
        iTempY = the_pond->iPondHeight-iImageHeight;
        iYVelocity=0-((YVARIATION/2)-rand()%YVARIATION);
       };

      EnterCriticalSection(&csSerializeDraw);
      hDC=GetDC(the_pond->hWndApplication);
      BitBlt(hDC,iX,iY,iImageWidth,iImageHeight,NULL,0,0,WHITENESS);
      iX = iTempX;
      iY = iTempY;
      iCalories-=MOVE_DEDUCTION;
/* determine if we have enough fuel left to survive... */

      if (!ObjectSpecificThreadRoutine(hDC) ||
          iCalories < 0 ||
          !the_pond->NewCoordinates(iHandle,iX,iY))
        bFinished=TRUE;
      else
/* redraw the object */
      { HBRUSH hDefaultBitmap;
        HDC hDCMem;
        hDCMem = CreateCompatibleDC(hDC);
        hDefaultBitmap = SelectObject(hDCMem,hImage);
        BitBlt(hDC,iX,iY,iImageWidth,iImageHeight,hDCMem,0,0,SRCCOPY);
        SelectObject(hDCMem,hDefaultBitmap);
        DeleteDC(hDCMem);
      };

      ReleaseDC(the_pond->hWndApplication,hDC);
      LeaveCriticalSection(&csSerializeDraw);
/* delay the object before moving on. */
      Sleep(DELAY);
    };   // end of while loop. Going past here means we are dead...
/*  Inform the window that the thread has terminated so it can clean up the object. */

  PostMessage(the_pond->hWndApplication,WM_OBJECT_DIED,(WPARAM)iHandle,NULL);
  return(TRUE);
};


/***************************************************************************/
/*                 derived class declarations                              */
/***************************************************************************/


frog::frog(const int i): animated_object("frog",FROG_TYPE,i)
{
  iCalories=INITIAL_FROG_CALORIES;
  iKilling = STATUS_ALIVE;
};

BOOL frog::ObjectSpecificThreadRoutine(const HDC hDC)
{ iXVelocity += iTempXVel;
  iYVelocity += iTempYVel;
  iTempXVel = iTempYVel = 0;
  return (iKilling == STATUS_ALIVE);
};

fly::fly(const int i): animated_object("fly",FLY_TYPE,i)
{
  iCalories=INITIAL_FLY_CALORIES;
};

BOOL fly::ObjectSpecificThreadRoutine(const HDC hDC)
{
  if (GetPixel(hDC,iX,iY) == KETCHUP_COLOR)
    iCalories+=KETCHUP_NUTRITION_VALUE;
  if (iCalories > FLY_MULTIPLY_CALORIES)
    {
     PostMessage(the_pond->hWndApplication,WM_COMMAND,IDM_ADDFLY,NULL);
     iCalories-=(FLY_MULTIPLY_CALORIES/2);
    };
    return (TRUE);
};


