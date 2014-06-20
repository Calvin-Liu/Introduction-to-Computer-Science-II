#ifndef _SOUNDFX_H_
#define _SOUNDFX_H_

#ifndef NOSOUND

#if defined(__APPLE__)
#include "irrKlang/irrKlang.h"
#elif !defined(unix)
#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
#endif

#else // forget about using sound library

#include <string>

namespace irrklang
{
	struct ISoundEngine
	{
		void play2D(std::string, bool) {}
		void stopAllSounds() {}
		void drop() {}
	};

	inline ISoundEngine* createIrrKlangDevice()
	{
		static ISoundEngine instance;
		return &instance;
	}
}

#endif // NOSOUND

#include <iostream>
#include <string>

class SoundFXController
{
  public:

    void playClip(std::string soundFile)
    {
        if (m_engine != NULL)
            m_engine->play2D(soundFile.c_str(), false);
    }

    void abortClip()
    {
        if (m_engine != NULL)
            m_engine->stopAllSounds();
    }

      // Meyers singleton pattern
    static SoundFXController& getInstance()
    {
        static SoundFXController instance;
        return instance;
    }

  private:
    SoundFXController()
    {
        m_engine = irrklang::createIrrKlangDevice();
        if (m_engine == NULL)
            std::cout << "Cannot create sound engine!  Game will be silent."
                      << std::endl;
    }

    ~SoundFXController()
    {
        if (m_engine != NULL)
            m_engine->drop();
    }

    SoundFXController(const SoundFXController&);
    SoundFXController& operator=(const SoundFXController&);

    irrklang::ISoundEngine* m_engine;
};

inline SoundFXController& SoundFX()
{
    return SoundFXController::getInstance();
}

#endif // _SOUNDFX_H_
