#ifndef _STUDENTWORLD_H_
#define _STUDENTWORLD_H_

#include <list>
#include "actor.h"
#include "GameWorld.h"
#include "GameConstants.h"
#include <cstdlib>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, actor.h, and actor.cpp

class StudentWorld;

class StudentWorld : public GameWorld
{
public:
    StudentWorld();
    ~StudentWorld();

	virtual void init()
    {
        m_ship = new Ship(this);
    }

	virtual int move()
    {
        list <Actor*>::iterator iter;
        
        if((rand() % 3) == 1)
        {
            m_Actor.push_front(new Star(this));
        }
        
        for(iter = m_Actor.begin(); iter != m_Actor.end(); iter++)
        {
            if((*iter)->getY() < 0)
            {
                Actor* ptr = *iter;
                iter = m_Actor.erase(iter);
                delete ptr;
            }
        }
        
        
        for(iter = m_Actor.begin(); iter != m_Actor.end(); iter++)
        {
            (*iter)->doSomething();  //makes everything in the list doSomething()
        }
        
        m_ship->doSomething();
        
        
        
        
        
        
        
        
        
        //decLives();
        //return GWSTATUS_PLAYER_DIED;
        return GWSTATUS_CONTINUE_GAME;
    }

	virtual void cleanUp()
    {
        list <Actor*>::iterator iter;
        iter = m_Actor.begin();
        for(; iter != m_Actor.end(); iter++)
        {
            delete *iter;
        }

        delete m_ship;
    }

private:
    list <Actor*> m_Actor;
    Ship* m_ship;
};

#endif // _STUDENTWORLD_H_
