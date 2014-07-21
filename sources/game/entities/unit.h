#ifndef GAME_ENTITIES_UNIT_H
 #define GAME_ENTITIES_UNIT_H

#include <string>
#include <map>

#include "../../engine/vector2d.h"
#include "../../engine/graphics/texture.h"

#include "../models/unitmodel.h"
#include "entity.h"

namespace game
{
    class Unit : public Entity
    {
        public:
            Unit(UnitModel* model, engine::Vector2d position, float angle, Side side, bool invincible);
            ~Unit();

            virtual bool isOutOfField();

            float getHealth();
            void setHealth(float health);
            virtual bool loseHealth(float health);
            virtual void kill();

            virtual void fire();

            void addShield();
            void removeShield();
            
            void removeLasers();

            virtual void show();

            bool isInvincible();

        protected:
            void fireModel(MissileModel* missileModel, std::vector<Missile*>* firedMissiles, bool* fired);

            int m_numShields;
            bool m_isInvincible;
            float m_health;
            float m_lastHealthLoss;
            bool m_isKilled;
            std::map<MissileModel*, float> m_lastFire;
            
            std::vector<Missile*> m_lasers;
    };

}

#endif
