#ifndef GAME_SCORE_H
 #define GAME_SCORE_H

#include <vector>

#include "../engine/graphics/texture.h"

namespace game
{
    class Score
    {
        public:
            Score();

            int getScore();

            void addScore(int score);

            void addLevelUpScore(int score);

            void show();

            std::string getDigitPath(int digit);

        private:
            void setCurrentScore(int currentScore);
            void setScore(int score);

            int m_currentScore;
            int m_score;

            std::string m_lastShownScore;

            std::vector<int> m_levelUpScores;
            std::vector<int>::iterator m_nextLevelScore;
            std::vector<int>::iterator m_endLevelUpScore;

            engine::graphics::Texture* m_digitTextures[10];
    };
}

#endif
