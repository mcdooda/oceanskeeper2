#include "../../engine/singleton.h"

#include "scoredigit.h"
#include "../score.h"

namespace game
{
    namespace effects
    {

        ScoreDigit::ScoreDigit(int digit, engine::Vector3d position) : Effect(S(Score)->getDigitPath(digit), 0.2, position, Effect::ABOVEALL)
        {

        }

        void ScoreDigit::show()
        {
            m_texture->show(m_position, engine::Vector3d(), engine::graphics::ColorRGBA(255, 255, 255, 255 - (float) 255 * getProgression()));
        }

    }
}
