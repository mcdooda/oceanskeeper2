#ifndef ENGINE_SOUNDS_MUSIC_H
 #define ENGINE_SOUNDS_MUSIC_H

#include <SFML/Audio.hpp>

namespace engine
{
    namespace sounds
    {

        class Music : private sf::Music
        {
            public:
                Music(std::string filename);

                void play();
                void stop();
                void setVolume(float volume);
        };

        Music* getMusic(std::string filename);
        void freeMusics();

    }
}

#endif
