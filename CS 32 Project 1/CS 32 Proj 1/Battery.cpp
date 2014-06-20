//
//  File.cpp
//  CS 32 Proj 1
//
//  Created by Calvin Liu on 1/10/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#include "Battery.h"

Battery::Battery(int initialLevel)
{
    m_levelNow = initialLevel;
}

int Battery::level() const
{
    return m_levelNow;
}

void Battery::decrease()
{
    if(m_levelNow > 0)
    {
        m_levelNow--;
    }
}