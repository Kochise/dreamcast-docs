/* Kallistios ##version##

   menu.h
   (c)2001,2002 Paul Boese a.k.a. Axlen

   A cheap little menu class

   $Id: menu.h,v 1.1 2002/03/04 02:57:32 axlen Exp $
*/

#ifndef __MENU_H
#define __MENU_H

#ifndef NULL
#define NULL 0
#endif
#define FLOAT_T 0
#define INTEGER_T 1

typedef struct Menuitem_t {
	int type;
	int min;
	int max;
	int amt;
	int* pvalue;
	char* pformat;
	Menuitem_t* prev;
	Menuitem_t* next;
};

union uf2i_t {
	int i;
	float f;
};

class Menu {

	protected:

	static Menuitem_t* mlist;
	static Menuitem_t* mtail;
	static Menuitem_t* mcur;
	static union uf2i_t uf2i;

	public:

	Menu () {
		mlist = mtail = mcur = NULL;
	}

	void add(int min, int max, int amt, int* pval, char *pformat);

	void add(float min, float max, float amt, float* pval, char *pformat);
	
	void next();

	void prev();

	void inc();

	void dec();

	void draw(int x, int y, int yinc);
};

#endif /* __MENU_H */
