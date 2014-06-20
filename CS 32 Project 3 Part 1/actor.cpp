#include "actor.h"
#include "StudentWorld.h"
#include <cstdlib>

// Students:  Add code to this file (if you wish), actor.h, StudentWorld.h, and StudentWorld.cpp


Actor::Actor(int imageID, int startX, int startY, StudentWorld* object)
:GraphObject(imageID, startX, startY)
{
    key = object;
    setVisible(true);
}

Actor::~Actor()
{}

void Actor::doSomething()
{}

StudentWorld* Actor::getWorld()
{
    return key;
}




Star::Star(StudentWorld* object)
:Actor(IID_STAR, (rand() % VIEW_WIDTH), VIEW_HEIGHT-1, object)
{}

Star::~Star()
{}

void Star::doSomething()
{
    moveTo(getX(),getY()-1);
}







Ship::Ship(StudentWorld* object)
:Actor(IID_PLAYER_SHIP, VIEW_WIDTH/2, 1, object), m_hitpoints(50)
{}

Ship::~Ship()
{
    if(m_hitpoints < 0)
    {
        delete this;
    }
}

void Ship::doSomething()
{
    int value;
    if(getWorld()->getKey(value))
    {
        switch(value)
        {
            case KEY_PRESS_LEFT:
                if(getX() > 0)
                    moveTo(getX()-1,getY());
                break;
            case KEY_PRESS_RIGHT:
                if(getX() < VIEW_WIDTH-1)
                    moveTo(getX()+1,getY());
                break;
            case KEY_PRESS_UP:
                if(getY() < VIEW_HEIGHT-1)
                    moveTo(getX(),getY()+1);
                break;
            case KEY_PRESS_DOWN:
                if(getY() > 0)
                    moveTo(getX(),getY()-1);
                break;
        }
    }
}