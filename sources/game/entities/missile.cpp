#include <iostream>

#include "../../engine/singleton.h"

#include "missile.h"
#include "../models/missilemodel.h"
#include "../field.h"

namespace game
{

    Missile::Missile(MissileModel* model, engine::Vector2d position, float angle, Side side) : Entity(model, position, angle, side)
    {
        calcHalfSize();
        m_speed = m_model->getSpeed();
        m_shooterId = INVALID_ID;
    }

    int Missile::getDamage()
    {
        return ((MissileModel*) m_model)->getDamage();
    }

    bool Missile::isOutOfField()
    {
        static const int threshold = 600;
        return (m_position.x < S(Field)->getMinX() - threshold) || (m_position.x > S(Field)->getMaxX() + threshold)
            || (m_position.y < S(Field)->getMinY() - threshold) || (m_position.y > S(Field)->getMaxY() + threshold);
    }

    bool Missile::isLaser()
    {
        return ((MissileModel*) m_model)->isLaser();
    }

    int Missile::getShooterId()
    {
        return m_shooterId;
    }

    void Missile::setShooterId(int shooterId)
    {
        m_shooterId = shooterId;
    }

}
