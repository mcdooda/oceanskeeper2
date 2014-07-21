#include "../../engine/time.h"
#include "../../engine/pi.h"

#include "shield.h"

namespace game
{

    Shield::Shield(Unit* unit, float health) : Unit(getUnitModel("Shield"), engine::Vector2d(0, 0), -M_PI / 2, Entity::ALLY, false)
    {
        m_unit = unit;
        m_side = unit->getSide();
        m_health = health;
        m_maxHealth = health;
        m_lastHit = -10;
        unit->addShield();
    }

    Shield::~Shield()
    {
        m_unit->removeShield();
    }

    int Shield::getHitBoxHalfSize()
    {
        return (float) m_unit->Entity::getHitBoxHalfSize() * 1.3 + 10;
    }

    void Shield::notifyCollision(Entity* entity)
    {
        setDirection(entity->getPosition());
    }

    void Shield::moveForward(float elapsedTime)
    {
        m_position = m_unit->getPosition();
    }

    bool Shield::loseHealth(float health)
    {
        m_lastHit = engine::time::getTime();
        return Unit::loseHealth(health);
    }

    void Shield::show()
    {
        float time = engine::time::getTime();
        static const float visibleDuration = 0.35;

        float alpha;

        if (m_lastHit > time - visibleDuration)
            alpha = (1 - (time - m_lastHit) / visibleDuration);

        else
            alpha = 0;

        if (alpha > 0)
        {
            alpha *= (float) m_health / m_maxHealth;
            float scale = (float) m_unit->getTexture()->getSize().x / getTexture()->getSize().x * 1.5;
            getTexture()->show(m_position, m_rotation, engine::graphics::ColorRGBA(255, 255, 255, alpha * 255), scale);
        }
    }
    
    void Shield::showShadow()
    {
        
    }

}
