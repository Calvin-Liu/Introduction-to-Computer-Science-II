//
//  main.cpp
//  CS 32 Hwk 1
//
//  Created by Calvin Liu on 1/20/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#include "Multiset.h"

Multiset::Multiset()
{
    m_numberOfItems = 0;
    m_uniqueCount = 0;
    m_instancesremoved = 0;
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
    if (m_uniqueCount != DEFAULT_MAX_ITEMS)
    {
        for(int k = 0; k < m_uniqueCount; k++)
        {
            if(value == m_set[k].thing)
            {
                m_numberOfItems++;
                m_set[k].count++;
                return true;
            }
        }
        m_set[m_uniqueCount].thing = value;
        m_uniqueCount++;
        m_numberOfItems++;
        return true;
    }
    return false;
}

int Multiset::erase(const ItemType& value)
{
    for(int k = 0; k < m_uniqueCount; k++)
        if (m_set[k].thing == value)
        {
            m_set[k].count--;
            m_numberOfItems--;
            return 1;
            if(m_set[k].count == 0)
            {
                for(int i = k; i < DEFAULT_MAX_ITEMS; i++)
                {
                    m_set[i] = m_set[i+1];
                }
                m_uniqueCount--;
            }
        }
    return 0;
}

int Multiset::eraseAll(const ItemType& value)
{
    for(int k = 0; k < m_uniqueCount; k++)
    {
        if (m_set[k].thing == value)
        {
            for(int i = m_set[k].count; i < 0; i--)
            {
                m_set[k].count--;
                m_numberOfItems--;
                m_instancesremoved++;
            }
            for(int j = k; j < DEFAULT_MAX_ITEMS; j++)
            {
                m_set[j] = m_set[j+1];
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
        if (value == m_set[k].thing)
        {
            return true;
        }
    return false;
}

int Multiset::count(const ItemType& value) const
{
    for(int k = 0; k < m_uniqueCount; k++)
        if(value == m_set[k].thing)
        {
            return m_set[k].count;
        }
    return 0;
}

int Multiset::get(int i, ItemType& value) const
{
    if(0 <= i && i < uniqueSize())
    {
        value = m_set[i].thing;
        return m_set[i].count;
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
    
    for(int k = 0; k < DEFAULT_MAX_ITEMS; k++)
    {
        arrayofN temp3 = m_set[k];
        m_set[k] = other.m_set[k];
        other.m_set[k] = temp3;
    }
}
