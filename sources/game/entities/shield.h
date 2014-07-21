#ifndef GAME_ENTITIES_SHIELD_H
 #define GAME_ENTITIES_SHIELD_H

#include "unit.h"

namespace game
{

    class Shield : public Unit
    {
        public:
            Shield(Unit* entity, float health);
            virtual ~Shield();

            virtual int getHitBoxHalfSize();

            virtual void notifyCollision(Entity* entity);

            virtual void moveForward(float elapsedTime);

            virtual bool loseHealth(float health);

            virtual void show();
            virtual void showShadow();

            bool isAlive();

        private:
            Unit* m_unit;
            float m_lastHit;
            float m_maxHealth;
    };

}

#endif
