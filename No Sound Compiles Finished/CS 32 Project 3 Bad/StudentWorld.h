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
    int roundNumber();
    void decreaseRound();
    Ship* getShipPtr();
    int roundFactor();
    list<Actor*> &getList();
    string setDisplayText(int sc, int ro, double enerp, int torp, int lives);
    
    int getNumAlienFiredProjectiles() const;
    void addprojectile();
    void decrementprojectile();
    
	virtual void init()
    {
        m_ship = new Ship(this);
    }
    
	virtual int move()
    {
        string s = setDisplayText(getScore(), m_roundNumber, (getShipPtr()->shipEnergy()), (getShipPtr()->numberOfTorpedoes()), getLives());
        setGameStatText(s);
        
        list <Actor*>::iterator iter;
        
        if((rand() % 3) == 1)
        {
            m_Actor.push_front(new Star(this));
        }
        
        int numberofactivealiens = m_aliencount;    //# aliens pushed onto list
        int totalAliensOnScreen = (2+.5*m_roundNumber); //max # of aliens on screen @ same time
        int numAliensToKillForNextRound = (4*m_roundNumber);
        
        if(numberofactivealiens >= totalAliensOnScreen)
        {
            int p3 = (rand() % 100);
            if(p3 < 33)
            {
                m_Actor.push_front(new Star(this));
            }
        }
        else
        {
            if(numberofactivealiens >= numAliensToKillForNextRound)
            {
                int p3 = (rand() % 100);
                if(p3 < 33)
                {
                    m_Actor.push_front(new Star(this));
                }
            }
            else
            {
                double roundFactor = 0.9 + 0.1 * roundNumber();
                int randomAlienGenerator = (rand() % 100);
                if(randomAlienGenerator < 70)
                {
                    int wealthyNachOrNot = (rand() % 100);
                    if(wealthyNachOrNot < 20)
                    {
                        m_Actor.push_front(new WealthyNachling(this, int(8*roundFactor)));
                    }
                    else
                    {
                        m_Actor.push_front(new Nachling(this, int(5*roundFactor)));
                    }
                    m_aliencount++;
                }
                else
                {
                    m_Actor.push_front(new Smallbots(this, int(12*roundFactor)));
                    m_aliencount++;
                }
            }
        }
        
        
        for(iter = m_Actor.begin(); iter != m_Actor.end(); iter++)
        {
            (*iter)->doSomething();  //makes everything in the list doSomething()
        }
        
        
        
        for(iter = m_Actor.begin(); iter != m_Actor.end(); iter++)
        {
            if((!(*iter)->isDead()))
            {
                Alien* tempalienptr = dynamic_cast<Alien*>(*iter);
                if(tempalienptr != NULL)
                {
                    numAliensToKillForNextRound--;
                }

                Actor*statusptr = *iter;
                iter = m_Actor.erase(iter);
                list <Actor*>::iterator iter;
                delete statusptr;
            }
        }
        if(numAliensToKillForNextRound == 0)
        {
            m_roundNumber++;
            numAliensToKillForNextRound = (4*m_roundNumber);
        }
        
        
        
        m_ship->doSomething();
        
        if(m_ship->currenthitpoints() <= 0)
        {
            delete m_ship;
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
        
        
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
    int m_aliencount;
    int m_roundNumber;
    int numKilledAliensThisRound;
    bool m_didhit;
    int m_numberprojectile;
};

#endif // _STUDENTWORLD_H_
