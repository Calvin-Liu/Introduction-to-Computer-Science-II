#include "StudentWorld.h"
#include "actor.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld()
{
    return new StudentWorld();
}

// Students:  Add code to this file (if you wish), StudentWorld.h, actor.h and actor.cpp

StudentWorld::StudentWorld()
{
    m_ship = NULL;
    m_aliencount = 0;
    m_roundNumber = 1;
    numKilledAliensThisRound = 0;
    m_didhit = false;
    m_numberprojectile = 0;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

void StudentWorld::decreaseRound()
{
    m_roundNumber--;
}

string StudentWorld::setDisplayText(int sc, int ro, double enerp, int torp, int lives)
{
    int score = sc;
    int round = ro;
    int energyPercent = enerp;
    int torpedoes = torp;
    int shipsLeft = lives;
    
    ostringstream oss;
    oss.setf(ios::fixed);
    oss << "Score:  " << setw(7) << setfill('0') << score;
    oss << "  Round:  " << setw(2) << setfill('0') << round;
    oss << "  Energy:  " << setw(3) << energyPercent << "%  ";
    oss << "  Torpedoes:  " << setw(3) << torpedoes;
    oss << "  Ships:  " << setw(2) << shipsLeft;
    
    return oss.str();
}

list <Actor*> &StudentWorld::getList()
{
    return m_Actor;
}

int StudentWorld::roundNumber()
{
    return m_roundNumber;
}


Ship* StudentWorld::getShipPtr()
{
    return m_ship;
}

int StudentWorld::getNumAlienFiredProjectiles() const
{
    return m_numberprojectile;
}

void StudentWorld::addprojectile()
{
    m_numberprojectile++;
}

void StudentWorld::decrementprojectile()
{
    m_numberprojectile--;
}
