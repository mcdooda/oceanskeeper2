#ifndef GAME_STATES_STATE_H
 #define GAME_STATES_STATE_H

namespace game
{
    namespace states
    {

        class State
        {
            public:
                virtual void loop() = 0;
        };

    }
}

#endif
