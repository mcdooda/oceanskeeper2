#include <vector>

#include "../../engine/singleton.h"
#include "../../engine/time.h"
#include "../../engine/sounds/sample.h"

#include "text.h"
#include "../field.h"

namespace game
{
    namespace effects
    {

        std::vector<Text*> texts;

        Text::Text(std::string texture) : Effect(texture, 3, engine::Vector3d(S(Field)->getCenterX(), S(Field)->getCenterY(), 0), Effect::ABOVEALL)
        {
            addText(this);
        }

        Text::~Text()
        {
            removeText(this);
        }

        void Text::show()
        {
            if (m_resetting)
            {
                float progression = engine::time::getTime() - m_resetTime;
                m_position.y = m_resetY + (m_directionY - m_resetY) * progression;
                if (progression > 1)
                    m_resetting = false;
            }
            m_texture->show(m_position, engine::Vector3d(), engine::graphics::ColorRGBA(255, 255, 255, 255 - (float) 255 * getProgression()));
        }

        void Text::addText(Text* text)
        {
            texts.push_back(text);
            resetTextsPosition();
        }

        void Text::removeText(Text* text)
        {
            std::vector<Text*>::iterator it = find(texts.end(), texts.begin(), text);
            texts.erase(it);
            resetTextsPosition();
        }

        void Text::resetTextsPosition()
        {
            int numTexts = texts.size();
            int textHeight = 80;
            std::vector<Text*>::iterator end = texts.end();
            int i = 0;
            for (std::vector<Text*>::iterator it = texts.begin(); it != end; it++)
            {
                float y = S(Field)->getCenterY() - (numTexts - 1) * textHeight / 2 + textHeight * i;
                (*it)->setDirectionY(y);
                i++;
            }
        }

        void Text::setDirectionY(float y)
        {
            m_resetY = m_position.y;
            m_directionY = y;
            m_resetTime = engine::time::getTime();
            m_resetting = true;
        }

        namespace text
        {
            End::End() : Text("texts/end.png") {}
            Pause::Pause() : Text("texts/pause.png") {}
            LevelUp::LevelUp() : Text("texts/levelup.png") { engine::sounds::getSample("lvlup.ogg")->play(engine::Vector2d(S(Field)->getCenterX(), S(Field)->getCenterY())); }
            BossInc::BossInc() : Text("texts/bossinc.png") {}
            MissionFailed::MissionFailed() : Text("texts/missionfailed.png") {}
        }

    }
}
