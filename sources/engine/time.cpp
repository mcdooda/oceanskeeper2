#include <SFML/System.hpp>
#include "engine.h"
#include "time.h"

namespace engine
{
    namespace time
    {

        bool pauseEnabled = false;
        float pauseTime;
        float pauseRealTime;
        float pauseElapsedTime;

        float getFrameTime()
        {
            return pauseEnabled ? 0 : getApplication()->getFrameTime();
        }

        sf::Clock clock;

        void reset()
        {
            clock.restart();
            pauseElapsedTime = 0;
        }

        void pause()
        {
            if (!pauseEnabled)
            {
                pauseTime = getTime();
                pauseRealTime = getRealTime();
                pauseEnabled = true;
            }
        }

        void resume()
        {
            pauseEnabled = false;
            pauseElapsedTime += getRealTime() - pauseRealTime;
        }

        bool isPauseEnabled()
        {
            return pauseEnabled;
        }

        float getTime()
        {
            return pauseEnabled ? pauseTime : clock.getElapsedTime().asSeconds() - pauseElapsedTime;
        }

        float getRealTime()
        {
            return clock.getElapsedTime().asSeconds();
        }

        void sleep(float time)
        {
            sf::sleep(sf::seconds(time));
        }

        void setFrameRate(unsigned int frameRate)
        {
            getApplication()->setFramerateLimit(frameRate);
        }

    }
}
