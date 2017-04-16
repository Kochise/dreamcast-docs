/***************************************************************************/
/*                 File: classes.h (contains C++ class declarations)       */
/***************************************************************************/


/***************************************************************************/
/*                 INCLUDES                                                */
/***************************************************************************/


#include <stdlib.h>
#include "stdafx.h"


/***************************************************************************/
/*                 Symbolic constants                                      */
/***************************************************************************/

// we do not only distinguish between places and transitions, but also 
// between places that hold critical resources and transitions that
// must be fired in response to them... that is why we test on &...

#define PLACE_TYPE 0x1
#define TRANSITION_TYPE 0x2
#define MARKED_TYPE 0x4

#define PLACEXEXTENSION 20
#define PLACEYEXTENSION 20
#define TRANSXEXTENSION 20
#define TRANSYEXTENSION 10

#define MAXNAME 20

#define DONTMOVESPACE 5

/***************************************************************************/
/*                 global variables                                        */
/***************************************************************************/


#ifdef CLASSES

// here add the variables that only the class declarations must see

#else

// here add the variables that only the application needs to see



#endif

/***************************************************************************/
/*                 data types                                              */
/***************************************************************************/


/***************************************************************************/
/*                 Class declarations                                      */
/***************************************************************************/

class TP;
class TPLIST;      // forward declaration
class CNetView;


/***************************************************************************/
/*                 The chained structure object                            */
/***************************************************************************/

class  ChainedStructure
{ protected:
  ChainedStructure *csNext;
  public:
  ChainedStructure();
  ~ChainedStructure();
  ChainedStructure *Succ(void);
  BOOL virtual AppendAtEnd(ChainedStructure *csNew);
  ChainedStructure *AppendUpFront(ChainedStructure *csNew);
};

inline ChainedStructure *ChainedStructure::Succ(void)
{
return csNext;
};


/***************************************************************************/
/*                 The TP object                                           */
/***************************************************************************/

class TP : public ChainedStructure
{ private:
  protected:
    BOOL bAlerted; 

  public:
    short iType;    // either TYPE_TRANSITION or TYPE_PLACE
	int iX,iY;		// current virtual coordinates
	int iOrdinal;
	CString szName;
    TP(int,int);      // creates a new object w/ initial coordinates 
	~TP();
	void Alert(BOOL);
	void Name(CString lpName);
	void virtual DrawYourself(CDC *hDC)=0;
	BOOL virtual Connect(TP *)=0;
	CRect virtual GetRect(CPoint)=0;
    BOOL Reposition(int ix, int iy);
	void SnapToGrid(int);
	TP *Hittest(int iCurrentX, int iCurrenty);
    TP *Succ(void);


};


inline TP *TP::Succ(void)
{
return (TP *) csNext;
};

/***************************************************************************/
/*                 Objects derived from the TP class                       */                   
/***************************************************************************/

class place: public TP
{ private:
	BOOL bMarkState;
  public:
    place(int,int);      // creates a new object w/ initial coordinates 
	~place(void);
	BOOL Connect(TP *whereto);
	void DrawYourself(CDC *hDC);
	void Mark(BOOL);
	CRect GetRect(CPoint);

	BOOL GetMark(void);
    place *Succ(void);

};


class transition: public TP
{ private:
  TPLIST *forwardlink;   // here we list all objects to which this one is
				       	 // connected.
  TPLIST *backwardlink;
  public:
    transition(int,int);      // creates a new object w/ initial coordinates 
	~transition(void);
    void DrawYourself(CDC *hDC);
	CRect GetRect(CPoint);
    BOOL Connect(TP *whereto);
    BOOL BackConnect (TPLIST *whereto);
	void DisConnect(place *wherefrom);
    TPLIST *GetConnections(BOOL);
    transition *Succ(void);

};

inline place *place::Succ(void)
{
return (place *) csNext;
};

inline transition *transition::Succ(void)
{
return (transition *) csNext;
};


/***************************************************************************/
/*                 TPLIST class                                            */
/***************************************************************************/


class TPLIST : public ChainedStructure
{ private:
  public:
    place *tpElement;
    TPLIST(place *tpEl);
	~TPLIST(void);

    TPLIST *Succ(void);
    BOOL AppendAtEnd(TPLIST *tpNew);

};

inline TPLIST *TPLIST::Succ(void)
{
return (TPLIST *) csNext;
};
