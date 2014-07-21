#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "sample.h"
#include "../exception.h"

namespace engine
{
    namespace sounds
    {

        Sample::Sample(std::string filename)
        {
            if (!loadFromFile(filename))
                throw Exception((std::string("Error loading ")+filename).c_str());
        }

        void Sample::play(engine::Vector2d pos)
        {
            sf::Sound* sound = new sf::Sound(*this);
            sound->setMinDistance(1);
            sound->setPosition(pos.x, 0, 0);
            sound->play();

            static std::vector<sf::Sound*> sounds;
            sounds.push_back(sound);
            std::vector<sf::Sound*> removedSounds;

            std::vector<sf::Sound*>::iterator end = sounds.end();
            for (std::vector<sf::Sound*>::iterator it = sounds.begin(); it != end; it++)
            {
                if ((*it)->getStatus() == sf::Sound::Stopped)
                    removedSounds.push_back(*it);
            }

            end = removedSounds.end();
            for (std::vector<sf::Sound*>::iterator it = removedSounds.begin(); it != end; it++)
            {
                std::vector<sf::Sound*>::iterator it2 = find(sounds.begin(), sounds.end(), *it);
                delete *it2;
                sounds.erase(it2);
            }
            removedSounds.clear();
        }

        std::map<std::string, Sample*> samples;

        Sample* getSample(std::string filename)
        {
            if (filename == "")
                return NULL;

            Sample* sample;
            std::map<std::string, Sample*>::iterator it = samples.find(filename);
            if (it != samples.end())
            {
                sample = it->second;
            }
            else
            {
                sample = new Sample("resources/sounds/" + filename);
                samples[filename] = sample;
            }
            return sample;
        }

        void freeSamples()
        {
            for (std::map<std::string, Sample*>::iterator it = samples.begin(); it != samples.end(); it++)
                delete it->second;

            samples.clear();
        }

    }
}
