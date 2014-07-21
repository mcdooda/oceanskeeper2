#ifndef GAME_EFFECTS_SCOREDIGIT_H
 #define GAME_EFFECTS_SCOREDIGIT_H

#include "effect.h"

namespace game
{
    namespace effects
    {

        class ScoreDigit : public Effect
        {
            public:
                ScoreDigit(int digit, engine::Vector3d position);

                void show();
        };

    }
}

#endif

