/*++

Copyright (c) 1995  Microsoft Corporation

Module Name:

    net\ip\lookup\algo.c

Abstract:


Revision History:



--*/

DWORD g_dwBitMask = {0x00000001,
                     0x00000002,
                     0x00000004,
                     0x00000008,
                     0x00000010,
                     0x00000020,
                     0x00000040,
                     0x00000080,
                     0x00000100,
                     0x00000200,
                     0x00000400,
                     0x00000800,
                     0x00001000,
                     0x00002000,
                     0x00004000,
                     0x00008000,
                     0x00010000,
                     0x00020000,
                     0x00040000,
                     0x00080000,
                     0x00100000,
                     0x00200000,
                     0x00400000,
                     0x00800000,
                     0x01000000,
                     0x02000000,
                     0x04000000,
                     0x08000000,
                     0x10000000,
                     0x20000000,
                     0x40000000,
                     0x80000000};


DWORD g_dwPrefixMask = {0x00000001,
                        0x00000003,
                        0x00000007,
                        0x0000000F,
                        0x0000001F,
                        0x0000003F,
                        0x0000007F,
                        0x000000FF,
                        0x000001FF,
                        0x000003FF,
                        0x000007FF,
                        0x00000FFF,
                        0x00001FFF,
                        0x00003FFF,
                        0x00007FFF,
                        0x0000FFFF,
                        0x0001FFFF,
                        0x0003FFFF,
                        0x0007FFFF,
                        0x000FFFFF,
                        0x001FFFFF,
                        0x003FFFFF,
                        0x007FFFFF,
                        0x00FFFFFF,
                        0x01FFFFFF,
                        0x03FFFFFF,
                        0x07FFFFFF,
                        0x0FFFFFFF,
                        0x1FFFFFFF,
                        0x3FFFFFFF,
                        0x7FFFFFFF,
                        0xFFFFFFFF}



BYTE
DistPos(
    IN  PTRIE_KEY   ptkKey1,
    IN  PTRIE_KEY   ptkKey2
    )
/*++
  Routine Description
      Returns the position of the distinguishing bit for two keys. This is
      the first bit that differs between the two keys.  If one key is a prefix
      of another (strict or non strict), then the dist bit is 1+width of the smaller
      key (== length of smaller key)
      
      Notationally:
      DistBit(K1, K2) = Min{i|K1[i] != K2[i]}
      DistBit(K1, K2) = Length(K1) iff K1 is a prefix of K2
      
      
  Arguments


  Return Value
      NO_ERROR

--*/
{
    BYTE    byLength;
    
    byLength = MAX(Length(ptkKey1),
                   Length(ptkKey2));
    
    for(i = 0; i < byLength; i++)
    {
        if(ptkKey1->dwAddr & g_dwBitMask[i] isnot
           ptkKey2->dwAddr & g_dwBitMask[i])
        {
            break;
        }
    }
    
    return i;
}





    
PTRIE_KEY
GetKey(
    IN  PTRIE_NODE  ptnNode,
    IN  PTRIE_KEY   ptkKey,
    OUT PBYTE       pbyPosition
    )
/*++
  Routine Description
      Given a input key and node, returns the stored key in the node
      whose index bit matches with the input key

  Arguments


  Return Value
      NO_ERROR

--*/
{
    
    if(Width(ptkKey) < Index(ptnNode))
    {
        return NULL;
    }

    *pbyPosition = GetRelevantBit(ptkKey->dwAddr, Index(ptnNode));
    
#if DBG

    //
    // A little consistency check here
    //
    
    if(LeftKey(ptnNode))
    {
        ASSERT(ptnNode->byPosition is LEFT);
    }

    if(RightKey(ptnNode))
    {
        ASSERT(ptnNode->byPosition is RIGHT);
    }
    
#endif
    
    return GetKeyByPosition(ptnNode,
                            *pbyPosition);
}

PTRIE_NODE
GetSubTrie(
    IN  PTRIE_NODE  ptnNode,
    IN  PTRIE_KEY   ptkKey,
    OUT PBYTE       pbyPosition
    )
/*++
  Routine Description


  Locks


  Arguments


  Return Value
      NO_ERROR

--*/
{
    
    if(Width(ptkKey) < Index(ptnNode))
    {
        return NULL;
    }

    *pbyPosition = GetRelevantBit(ptkKey->dwAddr, Index(ptnNode));

#if DBG

    //
    // A little consistency check here
    //
    
    if(LeftSubTrie(ptnNode))
    {
        ASSERT(ptnNode->ptnTrie[LEFT]->byPosition is LEFT);
    }

    if(RightSubTrie(ptnNode))
    {
        ASSERT(ptnNode->ptnTrie[RIGHT]->byPosition is RIGHT);
    }
    
#endif

    return GetSubTrieByPosition(ptnNode,
                                *pbyPosition);
    
}

PTRIE_KEY
GetClosestKey(
    PTRIE_NODE  ptnNode,
    PTRIE_KEY   ptkKey
    )
/*++
  Routine Description
      If the length of the key is greater than or equal to the index, return
      any Key.
      else
         If a key with matching relevant bit is found, return that, else
         return the other key

  Locks


  Arguments


  Return Value
      NO_ERROR

--*/
{
    PTRIE_KEY   ptkTemp;
    BYTE        byPos;
    
    if(Width(ptkKey) >= Index(ptnNode))
    {
        ptkTemp = GetKey(ptnNode,
                         ptkKey,
                         &byPos);
        
        if(ptkTemp isnot NULL)
        {
            return ptkTemp;
        }
        else
        {
            return GetKeyByPosition(ptnNode,
                                    ComplementPosition(byPos))
        }
    }
    else
    {
        //
        // For now we return the left key first
        //

        ptkTemp = GetKeyByPosition(ptnNode,
                                   LEFT);
        
        if(ptkTemp)
        {
            return ptkTemp;
        }
        else
        {
            return GetKeyByPosition(ptnNode,
                                    RIGHT);
        }
    }
}

PTRIE_NODE
GetClosestSubTrie(
    PTRIE_NODE  ptnNode,
    PTRIE_KEY   ptkKey
    )
/*++
  Routine Description
      If the length of the key is greater than or equal to the index, return
      any sub trie.
      else
         If a trie with matching relevant bit is found, return that, else
         return the other trie

  Locks


  Arguments


  Return Value
      NO_ERROR

--*/
{
    PTRIE_NODE  ptnTemp;
    BYTE        byPos;

    
    if(Width(ptkKey) >= Index(ptnNode))
    {
        ptnTemp = GetSubTrie(ptnNode,
                             ptkKey,
                             &byPos);
        
        if(ptnTemp isnot NULL)
        {
            return ptnTemp;
        }
        else
        {
            return GetSubTrieByPosition(ptnNode,
                                        ComplementPosition(byPos))
        }
    }
    else
    {
        //
        // For now we return the left trie first
        //

        ptkTemp = GetSubTrieByPosition(ptnNode,
                                       LEFT);
        
        if(ptkTemp)
        {
            return ptkTemp;
        }
        else
        {
            return GetSubTrieByPosition(ptnNode,
                                        RIGHT);
        }
    }
}

PTRIE_NODE
CreateNode(
    IN  BYTE        byIndex,
    IN  PTRIE_KEY   ptkKey
    )
/*++
  Routine Description


  Locks


  Arguments


  Return Value
      NO_ERROR

--*/
{
    PTRIE_NODE  ptnNode;

    ptnNode = HeapAlloc(g_hPrivateHeap,
                        0,
                        sizeof(TRIE_NODE));

    if(ptnNode is NULL)
    {
        printf("Unable to allocate node. Error %d\n",
               GetLastError());

        return NULL;
    }
    
    ptnNode->ptnTrie[LEFT]  = NULL;
    ptnNode->ptnTrie[RIGHT] = NULL;
    
    ptnNode->ptnParent      = NULL;

    ptnNode->byIndex        = byIndex;

    //
    // See where the key would go into the allocated node
    //
    
    GetKey(ptnNode,
           ptkKey,
           &byPos);

    //
    // Since we are going to be inserting the key here, set
    // its position field also
    //

    ptkKey->byPos = byPos;
    
    ptnNode->rgptkKey[byPos]  = ptkKey;
    
    ptnNode->rgptkKey[ComplementPosition(byPos)] = NULL;

    return ptnNode;
}

DWORD
InsertKey(
    PTRIE_NODE  *pptnRoot,
    PTRIE_KEY   ptkKey
    )
/*++
  Routine Description


  Locks


  Arguments


  Return Value
      NO_ERROR

--*/
{
    PTRIE_NODE  ptnTempNode;

    if(*pptnRoot is NULL)
    {
        *pptnRoot = AllocateNode(Width(ptkKey),
                                 ptkKey);

        if(*pptnRoot is NULL)
        {
            return ERROR_NOT_ENOUGH_MEMORY;
        }

        return NO_ERROR;
    }

    ptnTempNode = *pptnRoot;

    //
    // Descend the tree, branching according to the Index bit
    // Stop when the node is a leaf OR
    // when the index is greater than the width of the key OR
    // when the prefix of the node is not the same as the key
    //
    // The prefix is found by (ptkKey->dwAddr & g_dwPrefixMask[Index])
    //
    
    while(!IsLeafNode(ptnTempNode) and
          (Width(ptkKey) > Index(ptnTempNode)) and
          (ptnTempNode->rgptkKey[ptnTempNode->byNonNullKey] & g_dwPrefixMask[Index(ptnTempNode)] is
           ptkKey[
    {
        ptnTempNode = ClosestSubTrie(ptnTempNode,
                                     ptkKey);
    }

    byDistPost = DistPos(key,
                         ClosestKey(ptnNode,ptkKey));

    byIndex = MIN(Lenght(Key), byDistPos);

    if(ptnTempNode is *pptnRoot)
    {
        InsertInOrAbove(pptnRoot,
                        ptnTempNode,
                        ptkKey,
                        byDistPos);
    }
    else
    {
        if(GetSubTrie(ptnNode, ptkKey) is NULL)
        {
            InsertWithEmptySubTrie(ptnNode,
                                   ptkKey,
                                   byDistPos);
        }
        else
        {
            InsertWithNonEmptySubTrie(ptnNode,
                                      ptkKey,
                                      byDistPos);
        }
    }

    return NO_ERROR;
}
    
DWORD
InsertInOrAbove(
    PTRIE_NODE  *pptnRoot,
    PTRIE_NODE  ptnNode,
    PTRIE_KEY   ptkKey,
    BYTE        byDistPos
    )
/*++
  Routine Description


  Locks


  Arguments


  Return Value
      NO_ERROR

--*/
{
    if(
