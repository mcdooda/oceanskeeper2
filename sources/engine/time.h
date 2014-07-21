#ifndef ENGINE_TIME_H
 #define ENGINE_TIME_H

namespace engine
{
    namespace time
    {

        float getFrameTime();
        void reset();
        float getTime();
        float getRealTime();
        void pause();
        void resume();
        bool isPauseEnabled();
        void sleep(float time);
        void setFrameRate(unsigned int frameRate);

    }
}

#endif
