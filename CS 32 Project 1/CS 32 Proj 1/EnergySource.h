//
//  File.h
//  CS 32 Proj 1
//
//  Created by Calvin Liu on 1/10/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#ifndef ENERGY_INCLUDED
#define ENERGY_INCLUDED
#include <iostream>
using namespace std;

class EnergySource
{
public:
    // Constructor
    EnergySource(int r, int c);
    
    // Accessors
    int row() const;
    int col() const;
    
private:
    int m_row;
    int m_col;
};

#endif