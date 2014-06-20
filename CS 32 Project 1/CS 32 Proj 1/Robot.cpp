//
//  File.cpp
//  CS 32 Proj 1
//
//  Created by Calvin Liu on 1/10/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#include "Robot.h"
#include "globals.h"
#include "Valley.h"
#include "Battery.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////
//  Robot implementation
///////////////////////////////////////////////////////////////////////////

// Constructor:  Create a Robot in the Valley pointed to by vp, with
//    name nm, location (r,c), and direction d.
Robot::Robot(string nm, Valley* vp, int r, int c, int d)
: m_name(nm), m_energy(FULL_ENERGY), m_row(r), m_col(c), m_dir(d), m_valley(vp), m_battery(FULL_BATTERY)
{
    // Since the first character of the Robot's name shows up in the
    // display, there had better be a first character.
    if (nm.size() == 0)
    {
        cout << "***** A robot must have a non-empty name!" << endl;
        exit(1);
    }
    if (vp == NULL)
    {
        cout << "***** A robot must be in some Valley!" << endl;
        exit(1);
    }
    if (r < 0  ||  r >= vp->rows()  ||  c < 0  ||  c >= vp->cols())
    {
        cout << "***** Robot created with invalid coordinates (" << r << ","
        << c << ") in valley of size " << vp->rows() << "x"
        << vp->cols() << "!" << endl;
        exit(1);
    }
    switch (d)
    {
        case NORTH: case EAST: case SOUTH: case WEST:
            break;
        default:
            cout << "**** Robot created with invalid direction code " << d
            << "!" << endl;
            exit(1);
    }
}

string Robot::name() const
{
    return m_name;
}

int Robot::energy() const
{
    return m_energy;
}

int Robot::row() const
{
    return m_row;
}

int Robot::col() const
{
    return m_col;
}

int Robot::dir() const
{
    return m_dir;
}

bool Robot::step()
{
    // If the robot has no energy left, return false
    if (m_energy == 0)
        return false;
    
    // Randomly change direction with probability 1/3
    if (rand() % 3 == 0)     // 1/3 probability to pick a direction
        m_dir = rand() % 4;  // pick a random direction (0 through 3)
    
    // Attempt to move one step in the direction we're currently facing.
    // If we can't move in that direction, turn around and take a step.
    // If the turn around and step fails, it still costs you an energy.
    switch (m_dir)
    {
        case NORTH:
            if (m_row == 0)                     //if it is at the top
            {
                if (m_valley->rows()-1 != 0)    //if it is not a 1 row map
                {
                    m_row++;
                    m_dir = 1;                  //do regular stuff
                    break;
                }
                m_dir = 1;                       //it is so just turn south
                break;
            }
            if (m_row > 0)
                m_row--;
            break;
        case SOUTH:
            if (m_row == m_valley->rows()-1)     //if it is at the bottom
            {
                if (m_valley->rows()-1 != 0)     //if it is not a 1 row map
                {
                    m_row--;
                    m_dir = 0;                      //do regular stuff
                    break;
                }
                m_dir = 0;                      //it is so just turn north
                break;
            }
            if (m_row < m_valley->rows()-1)
                m_row++;
            break;
        case WEST:
            if (m_col == 0)                     //if it is at the left
            {
                if (m_valley->cols()-1 != 0)    //if it is not a 1 col map
                {
                    m_col++;
                    m_dir = 2;                  //do regular stuff
                    break;
                }
                m_dir = 2;                       //it is so just turn east
                break;
            }
            if (m_col > 0)
                m_col--;
            break;
        case EAST:
            if (m_col == m_valley->cols()-1)    //if it is at the right
            {
                if(m_valley->cols()-1 != 0)    //if it is not a 1 col map
                {
                    m_col--;
                    m_dir = 3;                      //do regular stuff
                    break;
                }
                m_dir = 3;                            //it is so just turn west
                break;
            }
            if (m_col < m_valley->cols()-1)
                m_col++;
            break;
    }
    
    // The attempt to move consumes one unit of energy.
    m_energy--;
    
    // If as a result of the attempt to move, the robot is at an energy
    // source, it's recharged to the FULL_ENERGY level.
    if (m_valley->energySourceAt(m_row, m_col))
        m_energy = FULL_ENERGY;
    
    // If at this spot there's another robot whose energy level is 0,
    // and we have at least SHARE_THRESHOLD units of energy,
    // transfer SHARE_AMOUNT units to that other robot.
    if (m_energy >= SHARE_THRESHOLD)
    {
        Robot* rp = m_valley->otherRobotAt(this);
        if (rp != NULL  &&  rp->energy() == 0)
        {
            m_energy -= SHARE_AMOUNT;
            rp->m_energy += SHARE_AMOUNT;
        }
    }
    
    if(m_battery.level() != 0)
    {
        if (m_energy <= 0)
        {
            m_energy++;
            m_battery.decrease();
        }
    }
    return true;
}

int Robot::batteryLevel() const
{
    return m_battery.level();
}



