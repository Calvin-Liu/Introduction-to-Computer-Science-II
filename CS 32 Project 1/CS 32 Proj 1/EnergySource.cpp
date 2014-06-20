//
//  File.cpp
//  CS 32 Proj 1
//
//  Created by Calvin Liu on 1/10/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#include "EnergySource.h"

///////////////////////////////////////////////////////////////////////////
//  EnergySource implementation
///////////////////////////////////////////////////////////////////////////

EnergySource::EnergySource(int r, int c)
: m_row(r), m_col(c)
{
    if (r < 0  ||  c < 0)
    {
        cout << "***** EnergySource created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
}

int EnergySource::row() const
{
    return m_row;
}

int EnergySource::col() const
{
    return m_col;
}
