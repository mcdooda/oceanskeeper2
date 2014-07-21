#ifndef GAME_STATEMACHINE_H
 #define GAME_STATEMACHINE_H

#include "states/state.h"

namespace game
{

    class StateMachine
    {
        public:
            StateMachine();
            ~StateMachine();

            states::State* getState();
            void setState(states::State* state);
            void loop();

        private:
            states::State* m_state;
    };

}

#endif
