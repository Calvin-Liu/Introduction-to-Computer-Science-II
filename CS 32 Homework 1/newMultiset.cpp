//
//  newMultiset.cpp
//  CS 32 Hwk 1
//
//  Created by Calvin Liu on 1/20/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//


#include "newMultiset.h"

Multiset::Multiset()
{
    m_numberOfItems = 0;
    m_uniqueCount = 0;
    m_instancesremoved = 0;
    m_cell = new arrayofN[DEFAULT_MAX_ITEMS];
    m_initial = DEFAULT_MAX_ITEMS;
}

Multiset::Multiset(int n)
{
    if(n < 0)
    {
        cout << "The array must have a positive size" << endl;
        exit (1);
    }
    m_numberOfItems = 0;
    m_uniqueCount = 0;
    m_instancesremoved = 0;
    m_cell = new arrayofN[n];
    m_initial = n;
}

Multiset::~Multiset()
{
    delete [] m_cell;
}

Multiset::Multiset(const Multiset& other)
{
    //copy constructor
    m_numberOfItems = other.m_numberOfItems;
    m_uniqueCount = other.m_uniqueCount;
    m_instancesremoved = other.m_instancesremoved;
    
    arrayofN* m_cell = new arrayofN[other.uniqueSize()];
    for(int k = 0; k < uniqueSize(); k++)
    {
        m_cell[k] = other.m_cell[k];
    }
}

Multiset& Multiset::operator=(const Multiset& rhs)
{
    if(this != &rhs)
    {
        delete [] m_cell;
        m_numberOfItems = rhs.m_numberOfItems;
        m_uniqueCount = rhs.m_uniqueCount;
        m_instancesremoved = rhs.m_instancesremoved;
        
        arrayofN* m_cell = new arrayofN[rhs.uniqueSize()];
        for(int k = 0; k < uniqueSize(); k++)
        {
            m_cell[k] = rhs.m_cell[k];
        }
    }
    return *this;
}

bool Multiset::empty() const
{
    if(m_numberOfItems == 0)
    {
        return true;
    }
    return false;
}

int Multiset::size() const
{
    return m_numberOfItems;
}

int Multiset::uniqueSize() const
{
    return m_uniqueCount;
}

bool Multiset::insert(const ItemType& value)
{
    if (m_uniqueCount != m_initial)
    {
        for(int k = 0; k < m_uniqueCount; k++)
        {
            if(value == m_cell[k].thing)
            {
                m_numberOfItems++;
                m_cell[k].count++;
                return true;
            }
        }
        m_cell[m_uniqueCount].thing = value;
        m_cell[m_uniqueCount].count++;
        m_uniqueCount++;
        m_numberOfItems++;
        return true;
    }
    else
    {
        for(int j = 0; j < m_initial; j++)
        {
            if(value == m_cell[j].thing)
            {
                m_numberOfItems++;
                m_cell[j].count++;
                return true;
            }
        }
        
    }
    return false;
}

int Multiset::erase(const ItemType& value)
{
    for(int k = 0; k < m_uniqueCount; k++)
        if (m_cell[k].thing == value)
        {
            m_cell[k].count--;
            m_numberOfItems--;
            if(m_cell[k].count == 0)
            {
                for(int i = k; i < DEFAULT_MAX_ITEMS; i++)
                {
                    m_cell[i] = m_cell[i+1];
                }
                m_uniqueCount--;
            }
            return 1;
        }
    return 0;
}

int Multiset::eraseAll(const ItemType& value)
{
    for(int k = 0; k < m_uniqueCount; k++)
    {
        if (m_cell[k].thing == value)
        {
            for(int i = m_cell[k].count; i < 0; i--)
            {
                m_cell[k].count--;
                m_numberOfItems--;
                m_instancesremoved++;
            }
            for(int j = k; j < DEFAULT_MAX_ITEMS; j++)
            {
                m_cell[j] = m_cell[j+1];
            }
            m_uniqueCount--;
            return m_instancesremoved;
        }
    }
    return 0;
}

bool Multiset::contains(const ItemType& value) const
{
    for(int k = 0; k < m_uniqueCount; k++)
        if (value == m_cell[k].thing)
        {
            return true;
        }
    return false;
}

int Multiset::count(const ItemType& value) const
{
    for(int k = 0; k < m_uniqueCount; k++)
        if(value == m_cell[k].thing)
        {
            return m_cell[k].count;
        }
    return 0;
}

int Multiset::get(int i, ItemType& value) const
{
    if(0 <= i && i < uniqueSize())
    {
        value = m_cell[i].thing;
        return m_cell[i].count;
    }
    return 0;
}

void Multiset::swap(Multiset& other)
{
    int temp = m_numberOfItems;
    m_numberOfItems = other.size();
    other.m_numberOfItems = temp;
    
    int temp1 = m_uniqueCount;
    m_uniqueCount = other.uniqueSize();
    other.m_uniqueCount = temp1;
    
    int temp2 = m_instancesremoved;
    m_instancesremoved = other.m_instancesremoved;
    other.m_instancesremoved = temp2;
    
    //    int higher = 0;
    //    if(m_uniqueCount > other.m_uniqueCount)
    //    {
    //        higher = m_uniqueCount;
    //    }
    //    else
    //    {
    //        higher = other.m_uniqueCount;
    //    }
    
    arrayofN* temp3 = m_cell;
    m_cell = other.m_cell;
    other.m_cell = temp3;
    
    int temp4 = m_initial;
    m_initial = other.m_initial;
    other.m_initial = temp4;
}



