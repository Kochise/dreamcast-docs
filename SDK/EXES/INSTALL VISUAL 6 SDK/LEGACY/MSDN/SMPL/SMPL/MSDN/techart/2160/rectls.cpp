// rectls.cpp : implementation file
//

#include "stdafx.h"
#include "anim32.h" // for debug stuff only
#include "rectls.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRectList

CRectList::CRectList()
{
}

CRectList::~CRectList()
{
}

/////////////////////////////////////////////////////////////////////////////
// CRectList commands

// Remove everything from the list deleting all the rects we remove
void CRectList::RemoveAll()
{
    dprintf2("CRectList::RemoveAll()");
    // Walk down the list deleting objects as we go.
    // We need to do this here because the base class
    // simply deletes the pointers.
    POSITION pos;
    CRect *pRect;
    for (pos = GetHeadPosition(); pos != NULL;) {
        pRect = GetNext(pos); // inc pos
        if (pRect) {
            delete pRect;
        }
    }
    // now call the base class to remove the pointers
    CObList::RemoveAll();
}

// Merge any overlapping rectangles in the list
void CRectList::Merge()
{
    dprintf2("CRectList::Merge()");
    if (IsEmpty()) return;
    top_of_loop:    // ah ha! a label! that means we'll use a goto!
    POSITION pos1 = GetHeadPosition();
    while (pos1) {
        CRect *prc1 = GetNext(pos1); // get the one at the top
        // compare each one with all those after it
        POSITION pos2 = pos1;
        while (pos2) {
            POSITION posThis = pos2;
            CRect *prc2 = GetNext(pos2);
            CRect rcTest;
            if (rcTest.IntersectRect(prc1, prc2)) {
                // merge together
                prc1->UnionRect(prc1, prc2);
                // delete the second one
                RemoveAt(posThis);
                // and do it all over again
                goto top_of_loop;
            }
        }
    }
}

// Add a new rectangle to the list.  New rectangles are
// tested for intersection with the one at the top of the
// list.  If the new one and the top one intersect then the top one 
// is replaced by the union of the top one and the new one
// This helps with the merge problem later by reducing
// the overall number of rectangles in the list.  We could walk the 
// list and test for intersection with any rectangle in the list
// but my guess is that this would slow things down not speed them up.
void CRectList::Add(CRect *prcNew)
{
    dprintf4("CRectList::Add(%u,%u %u,%u)",
             prcNew->left, prcNew->top, prcNew->right, prcNew->bottom);
    // get the rectangle currently at the top of the list
    POSITION pos = GetHeadPosition();
    if (pos) {
        CRect *prcTop = GetNext(pos);
        CRect rcTest;
        if (rcTest.IntersectRect(prcTop, prcNew)) {
            prcTop->UnionRect(prcTop, prcNew);
            dprintf4(" merged");
            return;
        }
    }
    // list is empty or there was no intersection
    CRect *prc = new CRect;
    *prc = *prcNew; // copy the data
    dprintf4(" new");
    CObList::AddHead((CObject *)prc);
}
