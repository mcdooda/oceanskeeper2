#include <SFML/Audio.hpp>
#include "sounds.h"

namespace engine
{
    namespace sounds
    {

        void init(Vector2d center)
        {
            sf::Listener::setPosition(center.x, 0, 0);
            sf::Listener::setDirection(0, 0, 1);
        }

    }
}
