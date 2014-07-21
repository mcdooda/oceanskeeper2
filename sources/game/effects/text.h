#ifndef GAME_EFFECTS_TEXTS_H
 #define GAME_EFFECTS_TEXTS_H

#include "effect.h"

namespace game
{
    namespace effects
    {

        class Text : public Effect
        {
            public:
                Text(std::string texture);
                ~Text();

                void show();

            private:
                void addText(Text* text);
                void removeText(Text* text);
                void resetTextsPosition();
                void setDirectionY(float y);

                float m_resetY;
                float m_directionY;
                float m_resetTime;
                bool m_resetting;
        };

        namespace text
        {
            class End : public Text
            {
                public:
                    End();
            };
            class Pause : public Text
            {
                public:
                    Pause();
            };
            class LevelUp : public Text
            {
                public:
                    LevelUp();
            };
            class BossInc : public Text
            {
                public:
                    BossInc();
            };
            class MissionFailed : public Text
            {
                public:
                    MissionFailed();
            };
        }

    }
}

#endif
