
//=============================================================================
//  Microsoft (R) Bloodhound (tm). Copyright (C) 1991-1993.
//
//  MODULE: list.h
//
//  Modification History
//
//  raypa           03/17/93    Created.
//=============================================================================

#if !defined(_LIST_)

#define _LIST_
#pragma pack(1)

//=============================================================================
//  The LINK structure is used to chain structures together into a list.
//=============================================================================

typedef struct _LINK *LPLINK;

typedef struct _LINK
{
    LPLINK     PrevLink;                    //... Previous or back pointer.
    LPLINK     NextLink;                    //... Next or forward pointer.
} LINK;

//=============================================================================
//  The LIST data structure.
//=============================================================================

typedef struct _LIST
{
    LPLINK      Tail;                       //... List Tail pointer.
    LPLINK      Head;                       //... List Head pointer.
    DWORD       Length;                     //... List Length.
} LIST;

typedef LIST *LPLIST;


#ifndef NO_INLINE

#ifndef INLINE
#define INLINE __inline
#endif

//=============================================================================
//  FUNCTIONS.
//=============================================================================

INLINE LPLINK WINAPI GetPrevLink(LPLINK Link)
{
    return Link->PrevLink;
}

INLINE LPLINK WINAPI GetNextLink(LPLINK Link)
{
    return Link->NextLink;
}

INLINE LPLINK WINAPI GetHeadOfList(LPLIST List)
{
    return List->Head;
}

INLINE LPLINK WINAPI GetTailOfList(LPLIST List)
{
    return List->Tail;
}

INLINE DWORD WINAPI GetListLength(LPLIST List)
{
    return List->Length;
}

//=============================================================================
//  FUNCTION: InitializeList()
//
//  Modification History
//                               
//  raypa           04/15/93        Created
//=============================================================================

INLINE LPLIST WINAPI InitializeList(LPLIST List)
{
    List->Head    = (LPLINK) 0L;
    List->Tail    = (LPLINK) 0L;
    List->Length  = 0;

    return List;
}

//=============================================================================
//  FUNCTION: AddLinkToLink()
//
//  Modification History
//                               
//  raypa           04/15/93        Created
//=============================================================================

INLINE VOID WINAPI AddLinkToLink(LPLINK DstLink, LPLINK SrcLink)
{
    //=========================================================================
    //  Make the source link point at the destination link.
    //=========================================================================

    SrcLink->PrevLink = DstLink;
    SrcLink->NextLink = DstLink->NextLink;

    //=========================================================================
    //  Make the destination link point at the source link.
    //=========================================================================

    DstLink->NextLink->PrevLink = SrcLink;
    DstLink->NextLink = SrcLink;
}

//=============================================================================
//  FUNCTION: AddToList()
//
//  Modification History
//                               
//  raypa           04/15/93        Created
//=============================================================================

INLINE LPLINK WINAPI AddToList(LPLIST List, LPLINK DstLink, LPLINK SrcLink)
{
    //=========================================================================
    //  Grow the list length by one.
    //=========================================================================

    List->Length++;

    //=========================================================================
    //  If SrcLink is NULL then add DstLink to the end of the list.
    //=========================================================================

    if ( SrcLink == (LPLINK) 0L )
    {
        //=====================================================================
        //  If the tail pointer is NULL then the list is empty.
        //=====================================================================

        if ( List->Tail != (LPLINK) 0L )
        {
            AddLinkToLink(List->Tail, DstLink);
        }
        else
        {
            DstLink->PrevLink = DstLink;
            DstLink->NextLink = DstLink;

            List->Head = DstLink;
        }

        return (List->Tail = DstLink);
    }

    //=========================================================================
    //  If DstLink is NULL then add SrcLink to the front of the list.
    //=========================================================================

    if ( DstLink == (LPLINK) 0L )
    {
        //=====================================================================
        //  If the head pointer is NULL then the list is empty.
        //=====================================================================

        if ( List->Head != (LPLINK) 0L )
        {
            AddLinkToLink(List->Head, SrcLink);
        }
        else
        {
            SrcLink->PrevLink = SrcLink;
            SrcLink->NextLink = SrcLink;

            List->Tail = SrcLink;
        }

        return (List->Head = SrcLink);
    }

    //=========================================================================
    //  Neither DstLink nor SrcLink is NULL so link them together.
    //=========================================================================

    AddLinkToLink(DstLink, SrcLink);

    return SrcLink;
}

//=============================================================================
//  FUNCTION: DeleteFromList()
//
//  Modification History
//                               
//  raypa           04/15/93        Created
//=============================================================================

INLINE LPLINK WINAPI DeleteFromList(LPLIST List, LPLINK Link)
{
    //=========================================================================
    //  If the list is empty then return NULL.
    //=========================================================================

    if ( List->Length != 0 )
    {
        //=====================================================================
        //  If the list length is not zero then we may need to fixup head and
        //  tail pointers in the event we delete the first or last link,
        //  respectively.
        //=====================================================================

        if ( --List->Length != 0 )
        {
            //=================================================================
            //  If we are deleting the front link then fixup the head pointer.
            //=================================================================

            if ( List->Head == Link )
            {
                List->Head = List->Head->NextLink;
            }

            //=================================================================
            //  If we are deleting the end link then fixup the tail pointer.
            //=================================================================

            if ( List->Tail == Link )
            {
                List->Tail = List->Tail->PrevLink;
            }

            //=================================================================
            //  Now we can unlink this link from the list.
            //=================================================================

            Link->NextLink->PrevLink = Link->PrevLink;
            Link->PrevLink->NextLink = Link->NextLink;
        }
        else
        {
            //=================================================================
            //  There is only one link on the list and we just deleted it.
            //=================================================================

            List->Head = (LPLINK) 0L;
            List->Tail = (LPLINK) 0L;
        }

        return Link;
    }

    return (LPLINK) 0L;
}

//=============================================================================
//  FUNCTION: AddToFrontOfList()
//
//  Modification History
//                               
//  raypa           04/15/93        Created
//=============================================================================

INLINE LPLINK WINAPI AddToFrontOfList(LPLIST List, LPLINK Link)
{
    return AddToList(List, (LPLINK) 0L, Link);
}

//=============================================================================
//  FUNCTION: AddToEndOfList()
//
//  Modification History
//                               
//  raypa           04/15/93        Created
//=============================================================================

INLINE LPLINK WINAPI AddToEndOfList(LPLIST List, LPLINK Link)
{
    return AddToList(List, Link, (LPLINK) 0L);
}

//=============================================================================
//  FUNCTION: DeleteFromFrontOfList()
//
//  Modification History
//                               
//  raypa           04/15/93        Created
//=============================================================================

INLINE LPLINK WINAPI DeleteFromFrontOfList(LPLIST List)
{
    return DeleteFromList(List, GetHeadOfList(List));
}

//=============================================================================
//  FUNCTION: DeleteFromEndOfList()
//
//  Modification History
//                               
//  raypa           04/15/93        Created
//=============================================================================

INLINE LPLINK WINAPI DeleteFromEndOfList(LPLIST List)
{
    return DeleteFromList(List, GetTailOfList(List));
}

#endif

#pragma pack()
#endif
