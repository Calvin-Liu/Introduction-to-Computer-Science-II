
//
//  File.cpp
//  CS 32 Hwk 1
//
//  Created by Calvin Liu on 1/20/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//


#include "StudentMultiset.h"

StudentMultiset::StudentMultiset()
{
    
}

bool StudentMultiset::add(unsigned long id)
{
    return m_studentIDs.insert(id);
}

int StudentMultiset::size() const
{
    return m_studentIDs.size();
}

void StudentMultiset::print() const
{
    ItemType x;
    for (int k = 0; k < m_studentIDs.uniqueSize(); k++)
    {
        int n = m_studentIDs.get(k, x);
        for(int i = 0; i < n; i++)
        {
            cout << x << endl;
        }
    }
}