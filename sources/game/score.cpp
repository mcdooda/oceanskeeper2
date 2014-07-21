#include <sstream>

#include "../engine/vector2d.h"
#include "../engine/singleton.h"

#include "score.h"
#include "entities/ship.h"
#include "field.h"
#include "effects/scoredigit.h"

namespace game
{

    Score::Score()
    {
        m_score = 0;
        m_currentScore = 0;

        m_lastShownScore = "0";

        for (int i = 0; i <= 9; i++)
            m_digitTextures[i] = engine::graphics::getTexture(getDigitPath(i));
    }

    void Score::addScore(int score)
    {
        setCurrentScore(m_currentScore + score);
    }

    void Score::addLevelUpScore(int score)
    {
        m_levelUpScores.push_back(score);
        m_nextLevelScore = m_levelUpScores.begin();
        m_endLevelUpScore = m_levelUpScores.end();
    }

    void Score::show()
    {
        std::string textScore;
        std::stringstream ss;
        ss << m_score;
        ss >> textScore;
        int lastShownNumDigits = m_lastShownScore.size();
        int numDigits = textScore.size();
        engine::Vector3d pos(S(Field)->getMaxX() + 32, S(Field)->getCenterY(), 0);
        for (int i = 0; i < numDigits; i++)
        {
            int digit = textScore[i] - '0';
            engine::graphics::Texture* digitTexture = m_digitTextures[digit];
            digitTexture->show(pos);

            if (i < lastShownNumDigits)
            {
                int lastShownDigit = m_lastShownScore[i] - '0';
                if (lastShownDigit != digit)
                    new effects::ScoreDigit(lastShownDigit, pos);
            }

            pos.x += 44;
        }
        m_lastShownScore = textScore;
    }

    std::string Score::getDigitPath(int digit)
    {
        std::string texture;
        std::stringstream ss;
        ss << "digits/" << digit << ".png";
        ss >> texture;
        return texture;
    }

    int Score::getScore()
    {
        return m_score;
    }

    void Score::setCurrentScore(int currentScore)
    {
        m_currentScore = currentScore;
        if (m_currentScore > m_score)
            setScore(m_currentScore);
    }

    void Score::setScore(int score)
    {
        m_score = score;
        while (m_nextLevelScore != m_endLevelUpScore && score >= *m_nextLevelScore)
        {
            S(Ship)->levelUp();
            m_nextLevelScore++;
        }
    }

}
