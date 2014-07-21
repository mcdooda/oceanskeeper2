#include "../../engine/singleton.h"
#include "../../engine/pi.h"

#include "lasermodel.h"
#include "../entities/laser.h"
#include "../livingentities.h"

namespace game
{

    LaserModel::LaserModel(std::string modelName, int damage, float firePeriod, float angle, int numMissiles, float speed, std::string texture, std::string texture2, std::string texture3, std::string sample, bool hasAiFunction, bool hasPopFunction) : MissileModel(modelName, damage, firePeriod, angle, numMissiles, speed, texture, sample, hasAiFunction, hasPopFunction)
    {
        m_texture2 = engine::graphics::getTexture(texture2);
        m_texture3 = engine::graphics::getTexture(texture3);
    }

    bool LaserModel::isLaser()
    {
        return true;
    }

    std::vector<Missile*> LaserModel::fire(lua_State* L, engine::Vector2d position, float angle, Entity::Side side, bool useParams, bool playSample, Entity* shooter)
    {
        if (m_sample != NULL && playSample)
            m_sample->play(position);

        std::vector<Missile*> lasers;

        if (m_numMissiles > 1)
        {
            if (m_angle > 0)
            {
                for (int i = 0; i < m_numMissiles; i++)
                {
                    float missileAngle = angle - m_angle / 2 + m_angle / (m_numMissiles - 1) * i;
                    Missile* m = new Laser((LaserModel*) this, position, missileAngle, side);

                    if (shooter != NULL)
                        m->setShooterId(shooter->getId());

                    lua::callPopFunction(L, this, m, i, useParams);
                    S(LivingMissiles)->addAfterMoving(m);
                    lasers.push_back(m);
                }
            }
            else
            {
                for (int i = 0; i < m_numMissiles; i++)
                {
                    Missile* m = new Laser((LaserModel*) this, position + engine::Vector2d(angle - M_PI / 2) * (i + 0.5 - (float) m_numMissiles / 2) * 8, angle, side);

                    if (shooter != NULL)
                        m->setShooterId(shooter->getId());

                    lua::callPopFunction(L, this, m, i, useParams);
                    S(LivingMissiles)->addAfterMoving(m);
                    lasers.push_back(m);
                }
            }
        }
        else if (m_numMissiles == 1)
        {
            Missile* m = new Laser((LaserModel*) this, position, angle, side);

            if (shooter != NULL)
                m->setShooterId(shooter->getId());

            lua::callPopFunction(L, this, m, 0, useParams);
            S(LivingMissiles)->addAfterMoving(m);
            lasers.push_back(m);
        }
        return lasers;
    }

    engine::graphics::Texture* LaserModel::getTexture2()
    {
        return m_texture2;
    }

    engine::graphics::Texture* LaserModel::getTexture3()
    {
        return m_texture3;
    }

}



