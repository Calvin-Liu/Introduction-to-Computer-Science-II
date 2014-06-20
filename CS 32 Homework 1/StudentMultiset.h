//
//  File.h
//  CS 32 Hwk 1
//
//  Created by Calvin Liu on 1/20/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#ifndef STUDENT_INCLUDED
#define STUDENT_INCLUDED

#include "Multiset.h"

class StudentMultiset
{
public:
    StudentMultiset();       // Create an empty student multiset.
    
    bool add(unsigned long id);
    // Add a student id to the StudentMultiset.  Return true if and only
    // if the id was actually added.
    
    int size() const;
    // Return the number of items in the StudentMultiset.  If an id was
    // added n times, it contributes n to the size.
    
    void print() const;
    // Print every student id in the StudentMultiset one per line; print
    // as many lines for each id as it occurs in the StudentMultiset.
    
private:
    Multiset m_studentIDs;
};

#endif