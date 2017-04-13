/*++

Copyright (c) 1995  Microsoft Corporation

Module Name:

    net\ip\lookup\structs.h

Abstract:


Revision History:



--*/

#ifndef __LOOKUP_STRUCTS_H__
#define __LOOKUP_STRUCTS_H__

#define LEFT    0
#define RIGHT   1

//
//  BYTE
//  ComplementPosition(
//      IN BYTE byPos
//      )
//

#define ComplementPosition(X)   ((X)^0x01)

typedef struct _TRIE_KEY
{
    DWORD   dwAddr;
    DWORD   dwMask;
    BYTE    byPosition;
    BYTE    byLength;
}TRIE_KEY, *PTRIE_KEY;

//
//  ULONG
//  Length(
//      IN PTRIE_KEY ptkKey
//      )
//

#define Length(X)    (X)->byLength

typedef struct _TRIE_NODE TRIE_NODE *PTRIE_NODE;

struct _TRIE_NODE
{
    PTRIE_NODE  ptnParent;
    PTRIE_NODE  ptnTrie[2];
    PTRIE_KEY   ptkKey[2];
    BYTE        byPosition;
    BYTE        byIndex;
};

//
//  BYTE
//  Index(
//      IN PTRIE_NODE ptnNode
//      )
//

#define Index(X)    (X)->byIndex

//
//  PTRIE_NODE
//  Parent(
//      IN PTRIE_NODE ptnNode
//      )
//

#define Parent(X)   (X)->ptnParent

//
//  PTRIE_NODE
//  LeftTrie(
//      IN PTRIE_NODE ptnNode
//      )
//

#define LeftTrie(X) (X)->ptnTrie[LEFT]

//
//  PTRIE_NODE
//  RightTrie(
//      IN PTRIE_NODE ptnNode
//      )
//

#define RightTrie(X) (X)->ptnTrie[RIGHT]

//
//  PTRIE_NODE
//  LeftKey(
//      IN PTRIE_NODE ptnNode
//      )
//

#define LeftKey(X) (X)->rgptkKey[LEFT]

//
//  PTRIE_NODE
//  RightKey(
//      IN PTRIE_NODE ptnNode
//      )
//

#define RightKey(X) (X)->rgptkKey[RIGHT]

//
//  BOOL
//  IsLeafNode(
//      IN PTRIE_NODE ptnNode
//      )
//

#define IsLeafNode(X)   ((RightTrie((X)) == NULL) && (LeftTrie((X)) == NULL))

//
//  BOOL
//  IsSingleKeyNode(
//      IN PTRIE_NODE ptnNode
//      )
//

#define IsSingleKeyNode(X) ((RightKey((X)) && (LeftKey((X)) == NULL)) ||    \
                            (LeftKey((X)) && (RightKey((X)) == NULL)))

//
//  BOOL
//  IsSingleKeyLeafNode(
//      IN PTRIE_NODE ptnNode
//      )
//

#define IsSingleKeyLeafNode(X) (IsLeafNode((X)) && IsSingleKeyNode((X)))

//
//  PTRIE_KEY
//  GetKeyByPosition(
//      IN PTRIE_NODE ptnNode,
//      IN ULONG      ulPosition
//      )
//

#define GetKeyByPosition(X,Y)   ((X)->rgptkKey[(Y)])

//
//  PTRIE_NODE
//  GetSubTrieByPosition(
//      IN PTRIE_NODE ptnNode,
//      IN ULONG      ulPosition
//      )
//

#define GetSubTrieByPosition(X,Y)  ((X)->ptnNode[(Y)])








    

