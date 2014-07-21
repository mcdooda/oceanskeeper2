#ifndef GAME_ENTITIES_ENTITY_H
 #define GAME_ENTITIES_ENTITY_H

#include "../../engine/vector2d.h"
#include "../../engine/graphics/graphics.h"
#include "../../engine/graphics/texture.h"

#include "../models/entitymodel.h"

#define ENTITY_ALTITUDE 40

namespace game
{

    class Entity
    {
        public:
            enum Side
            {
                ENEMY,
                ALLY
            };

            static const int INVALID_ID = 0;

        public:
            Entity(EntityModel* model, engine::Vector2d position, float angle, Entity::Side side);
            virtual ~Entity();

            virtual void destroy();

            void setSpeed(float speed);
            void turn(float angle, float elapsedTime);
            void setAngle(float angle);
            void lookAt(Entity* entity);
            void setDirection(engine::Vector2d direction);

            float getAngle();
            engine::Vector3d getPosition();
            void setX(float x);
            void setY(float y);
            void setZ(float z);
            
            float getX();
            float getY();
            float getZ();

            virtual bool collides(Entity* entity);
            virtual void notifyCollision(Entity* entity);

            int getHalfSize();
            virtual int getHitBoxHalfSize();

            Side getSide();

            int getId();

            virtual bool isOutOfField();
            bool isOutOfScreen();

            virtual void moveForward(float elapsedTime);
            void setPosition(engine::Vector3d position);

            virtual void show();
            virtual void showShadow();

            virtual engine::graphics::Texture* getTexture();
            
        protected:
            void calcHalfSize();

            int m_halfSize;
            engine::Vector3d m_position;
            engine::Vector3d m_rotation;
            float m_speed;
            Side m_side;
            int m_id;

            EntityModel* m_model;
    };

}

#endif
