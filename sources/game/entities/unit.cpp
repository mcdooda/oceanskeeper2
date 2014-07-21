#include "../../engine/graphics/graphics.h"
#include "../../engine/graphics/color.h"
#include "../../engine/graphics/texture.h"
#include "../../engine/time.h"
#include "../../engine/random.h"
#include "../../engine/pi.h"
#include "../../engine/singleton.h"

#include "unit.h"
#include "../field.h"
#include "../livingentities.h"
#include "missile.h"
#include "../score.h"
#include "../effects/luaeffect.h"

namespace game
{

    Unit::Unit(UnitModel* model, engine::Vector2d position, float angle, Side side, bool isInvincible) : Entity(model, position, angle, side)
    {
        calcHalfSize();
        m_speed = m_model->getSpeed();
        m_health = ((UnitModel*) m_model)->getMaxHealth();
        m_lastFire[(MissileModel*) ((UnitModel*) m_model)->getMissileModel()] = 0;
        m_lastHealthLoss = -10;
        m_isKilled = false;
        m_numShields = 0;
        m_isInvincible = isInvincible;
    }

    Unit::~Unit()
    {
        removeLasers();
    }

    bool Unit::isOutOfField()
    {
        return (m_position.x < S(Field)->getMinX() - m_halfSize) || (m_position.x > S(Field)->getMaxX() + m_halfSize)
            || (m_position.y < S(Field)->getMinY() - 200) || (m_position.y > S(Field)->getMaxY() + m_halfSize);
    }

    float Unit::getHealth()
    {
        return m_health;
    }

    void Unit::setHealth(float health)
    {
        m_health = health;
    }

    bool Unit::loseHealth(float health)
    {
        if (m_isInvincible)
            return false;

        if (m_numShields == 0)
        {
            m_health -= health;
            m_lastHealthLoss = engine::time::getTime();
            if (m_health <= 0)
                kill();
        }

        return m_health <= 0;
    }

    void Unit::kill()
    {
        if (!m_isKilled)
        {
            m_isKilled = true;

            int hitBoxHalfSize = getHitBoxHalfSize();
            int numExplosions = ceil((float) hitBoxHalfSize * hitBoxHalfSize * M_PI / (64 * 64)) * 2;
            for (int i = 0; i < numExplosions; i++)
                effects::LuaEffect::add("explosion", m_position + engine::Vector2d(engine::random::rfloat(0, 2 * M_PI)) * engine::random::rint(0, hitBoxHalfSize));

            if (m_side == ENEMY)
                S(Score)->addScore(((UnitModel*) m_model)->getMaxHealth());

            removeLasers();
        }
    }

    void Unit::fire()
    {
        MissileModel* missileModel = ((UnitModel*) m_model)->getMissileModel();
        if (m_lasers.empty() || !missileModel->isLaser())
        {
            std::vector<Missile*> firedMissiles;
            bool fired;
            fireModel(missileModel, &firedMissiles, &fired);
            if (fired && missileModel->isLaser())
                m_lasers = firedMissiles;
        }
    }

    void Unit::addShield()
    {
        m_numShields++;
    }

    void Unit::removeShield()
    {
        m_numShields--;
    }

    void Unit::removeLasers()
    {
        if (!m_lasers.empty())
        {
            std::vector<Missile*>::iterator end = m_lasers.end();
            for (std::vector<Missile*>::iterator it = m_lasers.begin(); it != end; it++)
                S(LivingMissiles)->remove(*it);

            m_lasers.clear();
        }
    }

    void Unit::show()
    {
        float time = engine::time::getTime();
        static const float blinkDuration = 0.1;
        engine::graphics::ColorRGBA color(255, 255, 255, 255);
        if (m_lastHealthLoss > time - blinkDuration)
        {
            GLubyte c = (float) 128 + 127 * (time - m_lastHealthLoss) / blinkDuration;
            color.r = c;
            color.g = c;
            color.b = c;
        }
        getTexture()->show(m_position, m_rotation, color, 1);
    }

    bool Unit::isInvincible()
    {
        return m_isInvincible;
    }

    void Unit::fireModel(MissileModel* missileModel, std::vector<Missile*>* firedMissiles, bool* fired)
    {
        float time = engine::time::getTime();
        float& lastFire = m_lastFire[missileModel];
        if (lastFire < time - missileModel->getFirePeriod())
        {
            if (fired != NULL)
            {
                *firedMissiles = missileModel->fire(engine::lua::getState(), m_position + engine::Vector2d(m_rotation.z) * getHalfSize(), m_rotation.z, m_side, false, true, this);
                *fired = true;
            }
            else
                missileModel->fire(engine::lua::getState(), m_position + engine::Vector2d(m_rotation.z) * getHalfSize(), m_rotation.z, m_side, false, true, this);

            lastFire = time;
        }
        else if (fired != NULL)
            *fired = false;
    }

}
