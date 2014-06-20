//
//  File.h
//  CS 32 Proj 1
//
//  Created by Calvin Liu on 1/10/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#ifndef ROBOT_INCLUDED
#define ROBOT_INCLUDED
#include "Battery.h"
#include <iostream>

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Valley;  // This is needed to let compiler know that Valley is a type
//   name, since it's mentioned in the Robot declaration.
//class Battery;

class Robot
{
public:
    // Constructor
    Robot(std::string nm, Valley* vp, int r, int c, int d);
    
    // Accessors
    std::string name() const;
    int         energy() const;
    int         row() const;
    int         col() const;
    int         dir() const;
    int         batteryLevel() const;
    
    // Mutators
    bool        step();
    
private:
    std::string  m_name;
    int          m_energy;
    int          m_row;
    int          m_col;
    int          m_dir;
    Valley*      m_valley;
    Battery      m_battery;
};

#endif