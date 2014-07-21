#ifndef GAME_STATES_GAME_H
 #define GAME_STATES_GAME_H

#include "state.h"
#include "../../engine/graphics/shader/program.h"

namespace game
{
    namespace states
    {

        class Game : public State
        {
            public:
                Game();
                virtual ~Game();

                void loop();

            private:
                void initGame();
                void handleEvents();

                engine::graphics::shader::Program m_program;

                bool m_endShown;
                bool m_missionFailed;
                bool m_missionFailedShown;
        };

    }
}

#endif
