//
//  File.h
//  CS 32 Proj 1
//
//  Created by Calvin Liu on 1/10/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#ifndef BATTERY_INCLUDED
#define BATTERY_INCLUDED

class Battery
{
public:
    Battery(int initialLevel);
    int level() const;
    void decrease();
private:
    int m_levelNow;
};

#endif