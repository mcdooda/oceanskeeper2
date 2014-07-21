#ifndef ENGINE_SOUNDS_SAMPLE_H
 #define ENGINE_SOUNDS_SAMPLE_H

#include <SFML/Audio.hpp>

#include "../vector2d.h"

namespace engine
{
    namespace sounds
    {

        class Sample : private sf::SoundBuffer
        {
            public:
                Sample(std::string filename);

                void play(engine::Vector2d pos);
        };

        Sample* getSample(std::string filename);
        void freeSamples();

    }
}


#endif
