#include "../../engine/vector2d.h"
#include "../../engine/graphics/graphics.h"
#include "../../engine/time.h"
#include "../../engine/pi.h"
#include "../../engine/singleton.h"

#include "ship.h"
#include "../models/shipmodel.h"
#include "../field.h"
#include "../effects/text.h"


#include "../../engine/graphics/heightmap.h"


namespace game
{

    Ship::Ship() : Unit(getUnitModel("Ship"), engine::Vector2d(0, 0), -M_PI / 2, Entity::ALLY, false), m_direction(0, 0)
    {
        m_numLives = 5;
        resetPosition();
        resetLastDeathTime();
        m_lastFire[(MissileModel*) ((ShipModel*) m_model)->getSpecialMissileModel()] = 0;
        m_level = 1;
        ((ShipModel*) m_model)->setLevel(m_level);
        m_rotation.y = 0;
        m_rotation.x = 0;
    }

    void Ship::destroy()
    {

    }

    int Ship::getHitBoxHalfSize()
    {
        return 10;
    }

    int Ship::getNumLives()
    {
        return m_numLives;
    }

    void Ship::move(engine::Vector2d direction)
    {
        m_direction = direction;

        m_position += direction * m_speed;
        int halfSize = getHalfSize();
        m_position.setMinX(S(Field)->getMinX() + halfSize);
        m_position.setMaxX(S(Field)->getMaxX() - halfSize);
        m_position.setMinY(S(Field)->getMinY() + halfSize);
        m_position.setMaxY(S(Field)->getMaxY() - halfSize);

        float frameTime = engine::time::getFrameTime();

        static const float pi8 = M_PI / 8;
        static const float pi6 = M_PI / 6;

        if (direction.x == 0)
        {
            if (m_rotation.y > 0.01)
            {
                m_rotation.y -= frameTime * 5;
                if (m_rotation.y < 0)
                    m_rotation.y = 0;
            }
            else if (m_rotation.y < -0.01)
            {
                m_rotation.y += frameTime * 5;
                if (m_rotation.y > 0)
                    m_rotation.y = 0;
            }
        }
        else
        {
            m_rotation.y -= direction.x * 15;
            if (m_rotation.y < -pi8)
                m_rotation.y = -pi8;
            else if (m_rotation.y > pi8)
                m_rotation.y = pi8;
        }

        if (direction.y == 0)
        {
            if (m_rotation.x > 0.01)
            {
                m_rotation.x -= frameTime * 12;
                if (m_rotation.x < 0)
                    m_rotation.x = 0;
            }
            else if (m_rotation.x < -0.01)
            {
                m_rotation.x += frameTime * 12;
                if (m_rotation.x > 0)
                    m_rotation.x = 0;
            }
        }
        else
        {
            m_rotation.x -= direction.y * 5;
            if (m_rotation.x < -pi6)
                m_rotation.x = -pi6;
            else if (m_rotation.x > pi6)
                m_rotation.x = pi6;
        }

    }

    void Ship::moveForward(float elapsedTime)
    {

    }

    bool Ship::loseHealth(float health)
    {
        if (!isInvincible())
            Unit::loseHealth(health);

        return !isAlive();
    }

    void Ship::kill()
    {
        m_numLives--;

        if (!isAlive())
            Unit::kill();

        resetPosition();
        resetLastDeathTime();
    }

    bool Ship::isAlive()
    {
        return m_numLives > 0;
    }

    void Ship::show()
    {
        engine::graphics::ColorRGBA color(255, 255, 255, 255);
        
        if (isInvincible())
            color.a = ((float) color.a / 255) * (160 + 85 * cos(engine::time::getTime() * 35));

        getTexture()->show(m_position, m_rotation, color, 1);
    }

    void Ship::fire()
    {

    }

    void Ship::shipFire()
    {
        Unit::fire();
    }

    void Ship::fireSpecial()
    {
        fireModel(((ShipModel*) m_model)->getSpecialMissileModel(), NULL, NULL);
    }

    float Ship::getSpecialLoading()
    {
        MissileModel* specialModel = ((ShipModel*) m_model)->getSpecialMissileModel();
        float lastFire = m_lastFire[specialModel];
        float firePeriod = specialModel->getFirePeriod();
        float loading = engine::time::getTime() - lastFire;
        return (loading < 0)? 0 : loading / firePeriod;
    }

    void Ship::levelUp()
    {
        new effects::text::LevelUp();
        m_level++;
        ((ShipModel*) m_model)->setLevel(m_level);
        removeLasers();
    }

    void Ship::resetPosition()
    {
        setPosition(
            engine::Vector3d(
                S(Field)->getCenterX(),
                S(Field)->getMaxY() - getHalfSize(),
                ENTITY_ALTITUDE
            )
        );
    }

    void Ship::resetLastDeathTime()
    {
        m_lastDeathTime = engine::time::getTime();
    }

    bool Ship::isInvincible()
    {
        return m_lastDeathTime > engine::time::getTime() - 1.5;
    }

}
