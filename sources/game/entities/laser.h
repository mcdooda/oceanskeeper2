#ifndef GAME_ENTITIES_LASER_H
 #define GAME_ENTITIES_LASER_H

#include "missile.h"
#include "../models/lasermodel.h"

namespace game
{

    class Laser : public Missile
    {
        public:
            Laser(LaserModel* model, engine::Vector2d position, float angle, Side side);

            virtual bool isOutOfField();

            virtual void show();
            virtual void showShadow();

            virtual bool collides(Entity* entity);

            void setLength(float length);

            void checkTarget(Entity* entity);

            Entity* getTarget();
            void setTarget(Entity* target);

            void grow();

        private:
            float m_length;
            float m_animationSpeed;

            float m_vertices[8];
            float m_texCoords[8];

            Entity* m_target;
    };

}

#endif
