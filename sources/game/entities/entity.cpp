#include "../../engine/singleton.h"
#include "../../engine/lua/lua.h"

#include "entity.h"
#include "../field.h"
#include "../lua.h"

namespace game
{

    Entity::Entity(EntityModel* model, engine::Vector2d position, float angle, Entity::Side side)
    {
        m_position.x = position.x;
        m_position.y = position.y;
        m_position.z = ENTITY_ALTITUDE;
        
        m_rotation.z = angle;
        
        m_model = model;
        m_side = side;

        static int nextId = 1;
        m_id = nextId;
        nextId++;

        lua::createExtraData(engine::lua::getState(), (void*) this);
        lua::saveEntityId(engine::lua::getState(), m_id, this);
    }

    Entity::~Entity()
    {
        lua::deleteExtraData(engine::lua::getState(), (void*) this);
        lua::deleteEntityId(engine::lua::getState(), m_id);
    }

    void Entity::destroy()
    {
        delete this;
    }

    void Entity::setSpeed(float speed)
    {
        m_speed = speed;
    }

    void Entity::turn(float angle, float elapsedTime)
    {
        m_rotation.z += angle * elapsedTime;
    }

    void Entity::setAngle(float angle)
    {
        m_rotation.z = angle;
    }

    void Entity::lookAt(Entity* entity)
    {
        setDirection(entity->m_position);
    }

    void Entity::setDirection(engine::Vector2d direction)
    {
        m_rotation.z = (direction - m_position).angle();
    }

    float Entity::getAngle()
    {
        return m_rotation.z;
    }

    engine::Vector3d Entity::getPosition()
    {
        return m_position;
    }

    void Entity::setX(float x)
    {
        m_position.x = x;
    }

    void Entity::setY(float y)
    {
        m_position.y = y;
    }
    
    void Entity::setZ(float z)
    {
        m_position.z = z;
    }
    
    float Entity::getX()
    {
        return m_position.x;
    }
    
    float Entity::getY()
    {
        return m_position.y;
    }
    
    float Entity::getZ()
    {
        return m_position.z;
    }
    
    bool Entity::collides(Entity* entity)
    {
        if (!isOutOfScreen())
        {
            int minDist = getHitBoxHalfSize() + entity->getHitBoxHalfSize();
            bool collision = (m_position - entity->m_position).distanceSquared() <= minDist * minDist;
            if (collision)
            {
                notifyCollision(entity);
                entity->notifyCollision(this);
            }
            return collision;
        }
        else
            return false;
    }

    void Entity::notifyCollision(Entity* entity)
    {

    }

    int Entity::getHalfSize()
    {
        return m_halfSize;
    }

    int Entity::getHitBoxHalfSize()
    {
        return m_halfSize;
    }

    Entity::Side Entity::getSide()
    {
        return m_side;
    }

    int Entity::getId()
    {
        return m_id;
    }

    bool Entity::isOutOfField()
    {
        return (m_position.x < S(Field)->getMinX() - m_halfSize) || (m_position.x > S(Field)->getMaxX() + m_halfSize)
            || (m_position.y < S(Field)->getMinY() - m_halfSize) || (m_position.y > S(Field)->getMaxY() + m_halfSize);
    }

    bool Entity::isOutOfScreen()
    {
        return Entity::isOutOfField();
    }

    void Entity::moveForward(float elapsedTime)
    {
        engine::Vector2d direction(m_rotation.z);
        m_position += direction * m_speed * elapsedTime;
        game::lua::callAiFunction(engine::lua::getState(), m_model, this);
    }

    void Entity::setPosition(engine::Vector3d position)
    {
        m_position = position;
    }

    void Entity::show()
    {
        engine::graphics::ColorRGBA color(255, 255, 255, 255);
        
        float distanceToField = S(Field)->getDistanceToFieldX(m_position.x);

        static const float threshold = 50;

        if (distanceToField > threshold)
            return;

        else
            color.a *= (threshold - distanceToField) / threshold;

        getTexture()->show(m_position, m_rotation, color, 1);
    }

    void Entity::showShadow()
    {
        engine::graphics::ColorRGBA color(0, 0, 0, 64);
        
        float distanceToField = S(Field)->getDistanceToFieldX(m_position.x);

        static const float threshold = 50;

        if (distanceToField > threshold)
            return;

        else
            color.a *= (threshold - distanceToField) / threshold;
            
        engine::Vector3d position = m_position;
        position.z = 0;
        
        engine::Vector3d rotation = m_rotation;
        rotation.x = 0;
        
        getTexture()->showFlatten(position, rotation, color, 1);
    }

    engine::graphics::Texture* Entity::getTexture()
    {
        return m_model->getTexture();
    }

    void Entity::calcHalfSize()
    {
        int h = m_model->getTexture()->getSize().y;
        int w = m_model->getTexture()->getSize().x;
        if (h > w)
            m_halfSize = w / 2;
        else
            m_halfSize = h / 2;
    }

}
