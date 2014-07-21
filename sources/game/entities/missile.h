#ifndef GAME_ENTITIES_MISSILE_H
 #define GAME_ENTITIES_MISSILE_H

#include "entity.h"
#include "../models/missilemodel.h"

namespace game
{

    class MissileModel;

    class Missile : public Entity
    {
        public:
            Missile(MissileModel* model, engine::Vector2d position, float angle, Side side);

            int getDamage();

            bool isOutOfField();

            bool isLaser();

            int getShooterId();
            void setShooterId(int shooterId);

        protected:
            int m_shooterId;
    };

}

#endif
