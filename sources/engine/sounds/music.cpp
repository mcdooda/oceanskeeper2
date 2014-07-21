#include <iostream>
#include <map>
#include "music.h"
#include "../exception.h"

namespace engine
{
    namespace sounds
    {

        Music::Music(std::string filename)
        {
            if (!openFromFile(filename))
                throw Exception((std::string("Error loading ")+filename).c_str());
        }

        void Music::play()
        {
            setLoop(true);
            sf::Music::play();
        }

        void Music::stop()
        {
            sf::Music::stop();
        }

        void Music::setVolume(float volume)
        {
            sf::Music::setVolume(volume);
        }

        std::map<std::string, Music*> musics;

        Music* getMusic(std::string filename)
        {
            if (filename == "")
                return NULL;

            Music* music;
            std::map<std::string, Music*>::iterator it = musics.find(filename);
            if (it != musics.end())
            {
                music = it->second;
            }
            else
            {
                music = new Music("resources/sounds/" + filename);
                musics[filename] = music;
            }
            return music;
        }

        void freeMusics()
        {
            for (std::map<std::string, Music*>::iterator it = musics.begin(); it != musics.end(); it++)
                delete it->second;

            musics.clear();
        }

    }
}
