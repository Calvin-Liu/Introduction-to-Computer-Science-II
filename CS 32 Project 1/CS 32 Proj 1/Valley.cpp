//
//  File.cpp
//  CS 32 Proj 1
//
//  Created by Calvin Liu on 1/10/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

#include "Valley.h"
#include "Robot.h"
#include "EnergySource.h"
using namespace std;


///////////////////////////////////////////////////////////////////////////
//  Valley implementation
///////////////////////////////////////////////////////////////////////////

Valley::Valley(int nr, int nc)
: m_rows(nr), m_cols(nc), m_nRobots(0), m_nSources(0), m_nSteps(0)
{
    if (nr <= 0  ||  nr > MAXROWS  ||  nc <= 0  ||  nc > MAXCOLS)
    {
        cout << "**** Valley created with invalid size " << nr << "x" << nc
        << "!" << endl;
        exit(1);
    }
}

Valley::~Valley()
{
    for (int k = 0; k < m_nRobots; k++)
        delete m_robots[k];
    for (int k = 0; k < m_nSources; k++)
        delete m_sources[k];
}

int Valley::rows() const
{
    return m_rows;
}

int Valley::cols() const
{
    return m_cols;
}

void Valley::display() const
{
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // fill the grid with dots
    for (r = 0; r < m_rows; r++)
        for (c = 0; c < m_cols; c++)
            grid[r][c] = '.';
    
    // Mark each energy source with a star
    for (int k = 0; k < m_nSources; k++)
    {
        const EnergySource* esp = m_sources[k];
        if (esp->row() < m_rows  &&  esp->col() < m_cols)
            grid[esp->row()][esp->col()] = '*';
    }
    
    // Indicate each robot's position
    for (int k = 0; k < m_nRobots; k++)
    {
        const Robot* rp = m_robots[k];
        grid[rp->row()][rp->col()] = rp->name()[0];
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < m_rows; r++)
    {
        for (c = 0; c < m_cols; c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    
    // Write robot energy info
    for (int k = 0; k < m_nRobots; k++)
    {
        const Robot* rp = m_robots[k];
        cout << rp->name() << " has " << rp->energy()
        << " energy units left; battery level is " << rp->batteryLevel() << endl;
    }
    
    cout << endl << m_nSteps << " steps taken" << endl;
}

bool Valley::energySourceAt(int r, int c) const
{
    for (int k = 0; k < m_nSources; k++)
    {
        const EnergySource* esp = m_sources[k];
        if (esp->row() == r  &&  esp->col() == c)
            return true;
    }
    return false;
}

Robot* Valley::otherRobotAt(Robot* rp) const
{
    int minEnergy = FULL_ENERGY+1; // +1 so that even a fully charged robot's
    // energy is less than this amount
    Robot* minRobot = NULL;
    
    // Find a robot at the same place that's different from rp and has
    // less energy than the smallest such robot so far.
    for (int k = 0; k < m_nRobots; k++)
    {
        Robot* rp2 = m_robots[k];
        if (rp2 != rp  &&  rp2->row() == rp->row()  &&  rp2->col() == rp->col()
            &&  rp2->energy() < minEnergy)
        {
            minRobot = rp2;
            minEnergy = rp2->energy();
        }
    }
    return minRobot;
}

Robot* Valley::getRobotByName(string name) const
{
    for (int k = 0; k < m_nRobots; k++)
    {
        if (m_robots[k]->name() == name)
            return m_robots[k];
    }
    return NULL;
}

bool Valley::addRobot(string name, int r, int c, int d)
{
    if (r < 0  ||  r >= m_rows  ||  c < 0  ||  c >= m_cols  ||
        m_nRobots == MAXROBOTS)
        return false;
    m_robots[m_nRobots] = new Robot(name, this, r, c, d);
    m_nRobots++;
    return true;
}

bool Valley::addEnergySource(int r, int c)
{
    if (r < 0  ||  r >= m_rows  ||  c < 0  ||  c >= m_cols  ||
        energySourceAt(r, c)  ||  m_nSources == MAXSOURCES)
        return false;
    m_sources[m_nSources] = new EnergySource(r, c);
    m_nSources++;
    return true;
}

bool Valley::step()
{
    m_nSteps++;
    
    bool anyAlive = false;
    for (int k = 0; k < m_nRobots; k++)
    {
        if (m_robots[k]->step())
            anyAlive = true;
    }
    return anyAlive;
}

