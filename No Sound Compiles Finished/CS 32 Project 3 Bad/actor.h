#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "GraphObject.h"
#include "GameWorld.h"
#include <string>
#include <iostream>
using namespace std;

// Students:  Add code to this file, actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor : public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, StudentWorld* object);
    virtual void doSomething() = 0;
    virtual ~Actor();
    StudentWorld* getWorld();
    bool isDead();
    void changetodead();
private:
    StudentWorld* key;
    bool m_status;
};













class Ship : public Actor
{
public:
    Ship(StudentWorld* object);
    virtual ~Ship();
    virtual void doSomething();
    int currenthitpoints();
    int damage(int k);
    bool didItFire();
    int shipEnergy();
    void addTorpedoes(int k);
    int numberOfTorpedoes();
    void heal();
private:
    int m_hitpoints;
    bool m_didItFire;
    int m_numberOfTorpedoes;
};













class Star : public Actor
{
public:
    Star(StudentWorld* object);
    virtual ~Star();
    virtual void doSomething();
private:
};












class Alien : public Actor
{
public:
    Alien(int imageID, int startX, int startY, StudentWorld* object, int health);
    virtual ~Alien();
    virtual void doSomething() = 0;
    void damage(int k);
    int alienhealth();
private:
    StudentWorld* m_ptrToWorld;
    int m_alienHealth;
};

class Nachling : public Alien
{
public:
    Nachling(StudentWorld* object, int HP);
    virtual ~Nachling();
    virtual void doSomething();
private:
    bool everyOther;
};

class WealthyNachling : public Nachling
{
public:
    WealthyNachling(StudentWorld* object, int HP);
    virtual ~WealthyNachling();
    virtual void doSomething();
private:
    int m_state;
    bool m_malfunctioning;
    bool m_stillmalfunctioning;
    int m_malfunctCount;
};

class Smallbots : public Alien
{
public:
    Smallbots(StudentWorld* object, int HP);
    virtual ~Smallbots();
    virtual void doSomething();
    bool justAttacked();
private:
    bool m_sEveryOther;
    bool m_justAttacked;
};












class Projectile : public Actor
{
public:
    Projectile(int imageID, int startX, int startY, StudentWorld* object, bool playerFired, int damagePoints);
    virtual ~Projectile();
    virtual void doSomething() = 0;
    bool getPlayerFired();
    bool didItFire();
    int damagePoint();
private:
    StudentWorld* m_ptrToWorld;
    bool m_playerFired;
    int m_damagePoints;
};

class Bullet : public Projectile
{
public:
    Bullet(StudentWorld* object, int startX, int startY, bool playerFired);
    virtual ~Bullet();
    virtual void doSomething();
private:
};

class Torpedo : public Projectile
{
public:
    Torpedo(StudentWorld* object, int startX, int startY, bool playerFired);
    virtual ~Torpedo();
    virtual void doSomething();
private:
};










class Goodies : public Actor
{
public:
    Goodies(int imageID, int startX, int startY, StudentWorld* object);
    ~Goodies();
    virtual void doSomething() = 0;
    int everythird();
    double goodieTickLifetime();
    double ticksLeftToLive();
    void resetthird();
    void decrementticks();
private:
    int m_everythird;
    double m_goodieTickLifetime;
    double m_ticksLeftToLive;
};

class FreeShipGoodie : public Goodies
{
public:
    FreeShipGoodie(StudentWorld* object, int startX, int startY);
    virtual ~FreeShipGoodie();
    virtual void doSomething();
private:
};

class EnergyGoodie : public Goodies
{
public:
    EnergyGoodie(StudentWorld* object, int startX, int startY);
    virtual ~EnergyGoodie();
    virtual void doSomething();
private:
};

class TorpedoGoodie : public Goodies
{
public:
    TorpedoGoodie(StudentWorld* object, int startX, int startY);
    virtual ~TorpedoGoodie();
    virtual void doSomething();
private:
};

#endif // _ACTOR_H_
