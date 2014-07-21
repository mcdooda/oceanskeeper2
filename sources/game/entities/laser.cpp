#include <iostream>

#include "laser.h"
#include "../../engine/time.h"
#include "../../engine/pi.h"

#define HEAD_SIZE 35

namespace game
{

    Laser::Laser(LaserModel* model, engine::Vector2d position, float angle, Side side) : Missile(model, position, angle, side)
    {
        m_animationSpeed = m_speed;
        m_speed = 0;

        m_length = 0;

        float halfWidth = getTexture()->getSize().x / 2;

        m_vertices[0] = 0; m_vertices[1] = -halfWidth;
        m_vertices[2] = 0; m_vertices[3] =  halfWidth;
        m_vertices[4] = 0; m_vertices[5] =  halfWidth;
        m_vertices[6] = 0; m_vertices[7] = -halfWidth;

        m_texCoords[0] = 0; m_texCoords[1] = 0;
        m_texCoords[2] = 0; m_texCoords[3] = 1;
        m_texCoords[4] = 1; m_texCoords[5] = 1;
        m_texCoords[6] = 1; m_texCoords[7] = 0;

        m_target = NULL;

        setLength(0);
    }

    bool Laser::isOutOfField()
    {
        return false;
    }

    void Laser::show()
    {
        static const float f = 180 / M_PI;
        glPushMatrix();
        glTranslated(m_position.x, m_position.y, m_position.z);
        glRotated(m_rotation.z * f, 0, 0, 1);
        getTexture()->bind();

        float height = getTexture()->getSize().y;

        float minX = engine::time::getTime() * -m_animationSpeed / 1000;
        float maxX = m_length / height + minX;

        m_texCoords[0] = minX;
        m_texCoords[2] = minX;
        m_texCoords[4] = maxX;
        m_texCoords[6] = maxX;
        
        glColor4ub(255, 255, 255, 255);

        glVertexPointer(2, GL_FLOAT, 0, m_vertices);
        glTexCoordPointer(2, GL_FLOAT, 0, m_texCoords);
        glDrawArrays(GL_QUADS, 0, 4);

        glPopMatrix();

        LaserModel* model = (LaserModel*) m_model;

        model->getTexture2()->show(m_position, m_rotation);
        model->getTexture3()->show(m_position + engine::Vector2d(m_rotation.z) * (m_length - HEAD_SIZE), m_rotation);
    }

    void Laser::showShadow()
    {

    }

    bool Laser::collides(Entity* entity)
    {
        return m_target == entity;
    }

    void Laser::setLength(float length)
    {
        m_length = length;
        m_vertices[4] = length - HEAD_SIZE;
        m_vertices[6] = m_vertices[4];
    }

    void Laser::checkTarget(Entity* entity)
    {
        engine::Vector2d diff = entity->getPosition() - m_position;
        float distance = diff.distance();
        engine::Vector2d localPos = engine::Vector2d(m_rotation.z - diff.angle()) * distance;
        float radius = entity->getHitBoxHalfSize();
        localPos.x -= sqrt(radius * radius - localPos.y * localPos.y);
        if (localPos.x < m_length && localPos.x >= 0 && (unsigned int) abs(localPos.y) < getTexture()->getSize().x / 8 + entity->getHitBoxHalfSize())
        {
            setLength(localPos.x);
            m_target = entity;
        }
    }

    Entity* Laser::getTarget()
    {
        return m_target;
    }

    void Laser::setTarget(Entity* target)
    {
        m_target = target;
    }

    void Laser::grow()
    {
        float length = m_length + engine::time::getFrameTime() * m_animationSpeed;
        if (length > 2000)
            length = 2000;

        setLength(length);
    }

}


