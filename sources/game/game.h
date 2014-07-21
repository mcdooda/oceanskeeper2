#ifndef GAME_GAME_H
 #define GAME_GAME_H

#include "states/state.h"

namespace game
{

    void init();
    void initEngine();
    void preloadSamples();

    void free();
    void freeEngine();

    void loop();

}

#endif
