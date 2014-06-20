//
//  main.cpp
//  Project 2
//
//  Created by Calvin Liu on 1/25/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#include "Multiset.h"

Multiset::Multiset()
{
    m_uniqueSize = 0;
    m_size = 0;
    m_head = new Node;
    m_head->next = m_head;  //create a new node that is the dummy node
    m_head->prev = m_head;
}

Multiset::~Multiset()
{
    Node* m_storageptr = m_head->next;
    while(m_storageptr != m_head)
    {
        m_head->next = m_storageptr->next;  //delete all the nodes
        delete m_storageptr;
        m_storageptr = m_head->next;
    }
    delete m_head;
}

Multiset::Multiset(const Multiset& other)
{
    m_size = other.m_size;
    m_uniqueSize = other.m_uniqueSize;      //copy the data members that are ints

    m_head = new Node;
    m_head->next = m_head;
    m_head->prev = m_head;                      //dummy node
    
    Node* ptr = m_head;
    Node* otherptr = other.m_head->next;
    
    while(otherptr != other.m_head)
    {
        ptr->next = new Node;
        ptr->next->data = otherptr->next->data;         //start copying value
        ptr->next->count = otherptr->next->count;
        ptr->next->prev = ptr;
        otherptr = otherptr->next;
        ptr = ptr->next;
    }
    ptr->next = m_head;
    m_head->prev = ptr;
}

Multiset& Multiset::operator=(const Multiset& rhs)
{
    if(this != &rhs)
    {
        //deletion part incase you are copying into something of bigger size
        
        Node* m_storageptr = m_head->next;
        while(m_storageptr != m_head)
        {
            m_head->next = m_storageptr->next;
            delete m_storageptr;
            m_storageptr = m_head->next;
        }
        delete m_head;
        
        //now it wil copy everything over
        m_size = rhs.m_size;
        m_uniqueSize = rhs.m_uniqueSize;
        
        m_head = new Node;
        m_head->next = m_head;      //creating new node (dummy)
        m_head->prev = m_head;
        
        Node* ptr = m_head;
        Node* otherptr = rhs.m_head->next;
        
        while(otherptr != rhs.m_head)
        {
            ptr->next = new Node;
            ptr->next->data = otherptr->data;
            ptr->next->count = otherptr->count;
            ptr->next->prev = ptr;
            otherptr = otherptr->next;
            ptr = ptr->next;
        }
        ptr->next = m_head;
        m_head->prev = ptr;
    }
    return *this;
}

int Multiset::size() const
{
    return m_size;        
}

int Multiset::uniqueSize() const
{
    return m_uniqueSize;
}

bool Multiset::empty() const
{
    return size() == 0;
}

bool Multiset::insert(const ItemType& value)
{
    Node* ptrnow;
    for(ptrnow = m_head->next; ptrnow != m_head; ptrnow = ptrnow->next)
    {
        if(value == ptrnow->data)
        {
            ptrnow->count++;
            m_size++;
            return true;
        }
    }                                   //loop to see if there is already a value
    
    if(m_size == 0)
    {
        Node* firstnode = new Node;
        firstnode->data = value;
        firstnode->next = m_head;
        m_head->next = firstnode;
        m_head->prev = firstnode;           //create the first node
        firstnode->prev = m_head;
        firstnode->count++;
        m_uniqueSize++;
        m_size++;
        return true;
    }
    else
    {
        Node * m_tmp = new Node;
        m_tmp->data = value;
        m_tmp->count++;
        m_tmp->next = m_head;
        m_tmp->prev = m_head->prev;             //create the next nodes
        m_head->prev->next = m_tmp;
        m_head->prev = m_tmp;
        m_uniqueSize++;
        m_size++;
        return true;
    }
}

int Multiset::erase(const ItemType& value)
{
    Node* ptrnow;
    for(ptrnow = m_head->next; ptrnow != m_head; ptrnow = ptrnow->next)
    {
        if(ptrnow->data == value)
        {
            ptrnow->count--;            //just decrease the count and size
            m_size--;
            if(ptrnow->count == 0)          //it got to 0, delete the node
            {
                Node* m_storageptr = ptrnow;
                ptrnow->prev->next = ptrnow->next;
                ptrnow->next->prev = ptrnow->prev;
                
                delete m_storageptr;
                m_uniqueSize--;
            }
            return 1;
        }
    }
    return 0;
}

int Multiset::eraseAll(const ItemType& value)
{
    Node* ptrnow;
    for(ptrnow = m_head->next; ptrnow != m_head; ptrnow = ptrnow->next)
    {
        if(ptrnow->data == value)               //interate through, find the value
        {                                       //erase everything 
            int m_instancesremoved = ptrnow->count;
            Node* m_storageptr = ptrnow;
            
            ptrnow->prev->next = ptrnow->next;
            ptrnow->next->prev = ptrnow->prev;
            ptrnow = ptrnow->next;
            
            delete m_storageptr;
            m_uniqueSize--;
            m_size -= m_instancesremoved;
            return m_instancesremoved;              //adjust the size
        }
    }
    return 0;
}

bool Multiset::contains(const ItemType& value) const
{
    Node* ptr = m_head->next;
    while(ptr != m_head)
    {
        if(ptr->data == value)              //loop through
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

int Multiset::count(const ItemType& value) const
{
    Node* ptrnow = m_head->next;
    while(ptrnow != m_head)
    {
        if(ptrnow->data == value)           //loop through
        {
            return ptrnow->count;
        }
        ptrnow = ptrnow->next;
    }
    return 0;
}

int Multiset::get(int i, ItemType& value) const
{
    //Node 1 has to be 0
    int position = 0;
    
    if(0 <= i && i < uniqueSize())
    {
        for(Node* ptrnow = m_head->next; ptrnow != m_head; position++, ptrnow = ptrnow->next)
        {
            if(position == i)           //update position so you know which node you are at
            {                           //if the position is = to the one you want to copy
                value = ptrnow->data;
                return ptrnow->count;
            }
        }
    }
    return 0;
}

void Multiset::swap(Multiset& other)
{
    int temp = m_size;
    m_size = other.size();
    other.m_size = temp;
    
    int temp1 = m_uniqueSize;
    m_uniqueSize = other.uniqueSize();      //swap the ints
    other.m_uniqueSize = temp1;
    
    Node* switchhead = m_head;
    m_head = other.m_head;
    other.m_head = switchhead;         //just swap the heads
}

void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
    //result has to have all the values of the 2 multisets in a linked list
    //probably have to do something like ms1.ptr->data and copy it into a new node from
    //results
    
    result = ms2;           //override result with one of the multiset
    ItemType copiedvalue;
    
    for(int i = 0; i < ms1.uniqueSize(); i++)   //number of items in one multiset
    {
        ms1.get(i, copiedvalue);                   
        for(int j = 0; j < ms1.count(copiedvalue);j++) //insert the count many times
        {
            result.insert(copiedvalue);
        }
    }
}

void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
    result = ms1;
    ItemType copiedvalue;
    
    for(int i = 0; i < ms2.uniqueSize(); i++)
    {
        for(int k = 0; k < ms2.get(i, copiedvalue); k++)
        {
            result.erase(copiedvalue);
        }
    }
}