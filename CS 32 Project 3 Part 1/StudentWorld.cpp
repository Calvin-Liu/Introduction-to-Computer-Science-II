#include "StudentWorld.h"
#include "actor.h"

GameWorld* createStudentWorld()
{
    return new StudentWorld();
}

// Students:  Add code to this file (if you wish), StudentWorld.h, actor.h and actor.cpp

StudentWorld::StudentWorld()
{
    m_ship = NULL;
}

StudentWorld::~StudentWorld()
{
    list <Actor*>::iterator iter;
    iter = m_Actor.begin();
    for(; iter != m_Actor.end(); iter++)
    {
        delete *iter;
    }
    
    delete m_ship;
}
