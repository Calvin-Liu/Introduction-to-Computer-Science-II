#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include <string>
#include <map>
#include <iostream>
#include <sstream>

enum GC_STATE {
	welcome, contgame, init, cleanup, makemove, animate, gameover, prompt, quit
};

const int INVALID_KEY = 0;

class GraphObject;
class GameWorld;

class GameController
{
  public:
	void run(GameWorld* gw, int testParams[], std::string windowTitle);

	bool getLastKey(int& value)
	{
		if (m_lastKeyHit != INVALID_KEY)
		{
			value = m_lastKeyHit;
			m_lastKeyHit = INVALID_KEY;
			return true;
		}
		return false;
	}

	void keyboardEvent(unsigned char key, int x, int y);
	void specialKeyboardEvent(int key, int x, int y);
    
	void playSound(int soundID);

	void setGameStatText(std::string text)
	{
		m_gameStatText = text;
	}

	void doSomething();
	void reshape(int w, int h);

	  // Meyers singleton pattern
	static GameController& getInstance()
	{
	    static GameController instance;
	    return instance;
	}

private:

	void initDrawersAndSounds();
    void displayGamePlay();

	GameWorld*	m_gw;
	GC_STATE	m_gameState;
	GC_STATE	m_nextStateAfterPrompt;
	int 		m_lastKeyHit;
    bool        m_singleStep;
	std::string	m_gameStatText;
	std::string	m_mainMessage;
	std::string	m_secondMessage;
	int         m_curIntraFrameTick;
	typedef std::map<int, std::string>           SoundMapType;
	typedef std::map<int, void(*)(GraphObject*)> DrawMapType;
	SoundMapType m_soundMap;
	DrawMapType  m_drawMap;
};

inline GameController& Game()
{
    return GameController::getInstance();
}

#endif // _GAMECONTROLLER_H_
