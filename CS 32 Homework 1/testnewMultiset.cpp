//
//  testnewMultiset.cpp
//  CS 32 Hwk 1
//
//  Created by Calvin Liu on 1/20/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//



#include "newMultiset.h"

int main()
{
    Multiset a(1000);   // a can hold at most 1000 distinct items
    Multiset b(5);      // b can hold at most 5 distinct items
    Multiset c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
    ItemType v[6] = { 1, 2, 3, 4, 5, 6 };
    // No failures inserting 5 distinct items twice each into b
    for (int k = 0; k < 5; k++)
    {
        assert(b.insert(v[k]));
        assert(b.insert(v[k]));
    }
    assert(b.size() == 10);
    assert(b.uniqueSize() == 5);
    assert(b.count(v[0]) == 2);
    // Failure if we try to insert a sixth distinct item into b
    assert(!b.insert(v[5]));
    
    // When two Multisets' contents are swapped, their capacities are swapped
    // as well:
    a.swap(b);
    assert(!a.insert(v[5])  &&  b.insert(v[5]));
    
    return 1;
}

//Might need to make a copy constructor or something for part 4

//Swap function part 5 says that it needs to swap a fixed number of times
//It says that the for loop would not work because it swaps
//depending on how many items are in the set


