#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "GraphObject.h"
#include "GameWorld.h"

// Students:  Add code to this file, actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor : public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, StudentWorld* object);
    virtual void doSomething();
    virtual ~Actor();
    StudentWorld* getWorld();
private:
    StudentWorld* key;
};


class Ship : public Actor
{
public:
    Ship(StudentWorld* object);
    virtual ~Ship();
    virtual void doSomething();
    int currenthitpoints();
private:
    int m_hitpoints;
};


class Star : public Actor
{
public:
    Star(StudentWorld* object);
    virtual ~Star();
    virtual void doSomething();
private:
};

#endif // _ACTOR_H_
