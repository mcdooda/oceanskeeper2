#ifndef GAME_ENTITIES_SHIP_H
 #define GAME_ENTITIES_SHIP_H

#include <string>
#include "../../engine/vector2d.h"
#include "../../engine/graphics/texture.h"
#include "unit.h"

namespace game
{

    class Ship : public Unit
    {
        public:
            Ship();

            virtual void destroy();

            int getHitBoxHalfSize();
            int getNumLives();

            void move(engine::Vector2d direction);

            virtual void moveForward(float elapsedTime);

            virtual bool loseHealth(float health);
            virtual void kill();
            bool isAlive();

            virtual void show();

            virtual void fire();
            void shipFire();
            void fireSpecial();
            float getSpecialLoading();

            void levelUp();

        private:
            void resetPosition();
            void resetLastDeathTime();

            bool isInvincible();

            engine::Vector2d m_direction;

            int m_numLives;
            float m_lastDeathTime;
            engine::graphics::Texture* m_texture;

            int m_level;
    };

}

#endif
