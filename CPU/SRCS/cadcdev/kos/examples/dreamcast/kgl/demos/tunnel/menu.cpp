/* Kallistios ##version##

   menu.cpp
   (c)2001,2002 Paul Boese a.k.a. Axlen

   A cheap little menu class
*/

#include <string.h>
#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "plprint.h"
#include "menu.h"

CVSID("$Id: menu.cpp,v 1.1 2002/03/04 02:57:32 axlen Exp $");

void Menu::add(int min, int max, int amt, int* pval, char *pformat) {
	Menuitem_t* madd;	
	if (mlist == NULL) {
		mlist = (Menuitem_t*) malloc(sizeof(Menuitem_t));
		mlist->prev = NULL;
		mlist->next = NULL;
		madd = mcur = mtail = mlist;
	} else {
		madd = (Menuitem_t*) malloc(sizeof(Menuitem_t));
		mtail->next = madd;
		madd->prev = mtail;
		madd->next = NULL;
		mtail = madd;
	}
	madd->type = INTEGER_T;
	madd->min = min;
	madd->max = max;
	madd->amt = amt;
	madd->pvalue = pval;
	madd->pformat = (char*) malloc(strlen(pformat)+1); 
	memcpy(madd->pformat, pformat, strlen(pformat)+1);
	printf("[i**]menu->add = %d\n", strlen(pformat)+1);
}

// lvalue cast fix for C++, as proposed by Jim Ursetto
// http://sourceforge.net/mailarchive/message.php?msg_id=9293303
template <typename T, typename X> inline T& lvalue_cast(X& x) {
        return *( reinterpret_cast<T*>(&x) );  // *((T *)& x)
}

void Menu::add(float min, float max, float amt, float* pval, char *pformat) {
	Menuitem_t* madd;
	if (mlist == NULL) {
		mlist = (Menuitem_t*) malloc(sizeof(Menuitem_t));
		mlist->prev = NULL;
		mlist->next = NULL;
		madd = mcur = mtail = mlist;
	} else {
		madd = (Menuitem_t*) malloc(sizeof(Menuitem_t));
		mtail->next = madd;
		madd->prev = mtail;
		madd->next = NULL;
		mtail = madd;
	}
	madd->type = FLOAT_T;
	uf2i.f = min; madd->min = uf2i.i;
	uf2i.f = max; madd->max = uf2i.i;
	uf2i.f = amt; madd->amt = uf2i.i;
	lvalue_cast<float *>(madd->pvalue) = pval;
	madd->pformat = (char*) malloc(strlen(pformat)+1); 
	memcpy(madd->pformat, pformat, strlen(pformat)+1);
	printf("[f**]menu->add = %d\n", strlen(pformat)+1);
}
void Menu::next() {
	if (mcur == NULL) return;
	if (mcur->next != NULL) {
		// point to next menu item
		mcur = mcur->next;
	} else {
		// wrap around to first menu item
		mcur = mlist;
	}
}

void Menu::prev() {
	if (mcur == NULL) return;
	if (mcur->prev != NULL) {
		// point to prev menu item
		mcur = mcur->prev;
	} else {
		// wrap around to last menu item
		mcur = mtail;
	}
}
	
void Menu::inc() {
	int tmp;
	float fmp;

	if (mcur == NULL) return;
	switch(mcur->type) {
	case INTEGER_T:
		tmp = *mcur->pvalue;
		tmp += mcur->amt;
		if (tmp > mcur->max)
			return;
		(*mcur->pvalue) = tmp;
		break;
	case FLOAT_T:
		fmp = (float)*(float *)mcur->pvalue;
		uf2i.i = mcur->amt; fmp += uf2i.f;
		uf2i.i = mcur->max;
		if (fmp > uf2i.f)
			return;
		(*(float *)mcur->pvalue) = fmp;
		break;
	}
}

void Menu::dec() {
	int tmp;
	float fmp;
	
	if (mcur == NULL) return;
	switch(mcur->type) {
	case INTEGER_T:
		tmp = *mcur->pvalue;
		tmp -= mcur->amt;
		if (tmp < mcur->min)
			return;
		(*mcur->pvalue) = tmp;
		break;
	case FLOAT_T:
		fmp = (float)*(float *)mcur->pvalue;
		uf2i.i = mcur->amt; fmp -= uf2i.f;
		uf2i.i = mcur->min;
		if (fmp < uf2i.f)
			return;
		(*(float *)mcur->pvalue) = fmp;
		break;
	}
}

void Menu::draw(int x, int y, int yinc) {
	Menuitem_t* pmi = mlist;
	int cy = y;
	char buf[80];
	
	while (pmi != NULL) {
		if(pmi->type == INTEGER_T)
			sprintf(buf, pmi->pformat, *pmi->pvalue);
		else
			sprintf(buf, pmi->pformat, (float)*(float*)pmi->pvalue);
		if (pmi == mcur) {
		    plprint(x,cy, 1.0f, 1.0f, 0.0f, buf, 1);
		} else {
		    plprint(x,cy, 0.8f, 0.8f, 0.8f, buf, 1);
		}
		cy += yinc;
		pmi = pmi->next;
	}
}

Menuitem_t* Menu::mlist = NULL;
Menuitem_t* Menu::mtail = NULL;
Menuitem_t* Menu::mcur = NULL;
union uf2i_t Menu::uf2i;
