#include <iostream>

#include "../../engine/singleton.h"
#include "../../engine/pi.h"

#include "../entities/laser.h"
#include "missilemodel.h"
#include "../livingentities.h"

namespace game
{

    MissileModel::MissileModel(std::string modelName, int damage, float firePeriod, float angle, int numMissiles, float speed, std::string texture, std::string sample, bool hasAiFunction, bool hasPopFunction) : EntityModel(speed, texture, hasAiFunction, hasPopFunction)
    {
        m_damage = damage;
        m_firePeriod = firePeriod;
        m_angle = angle;
        m_numMissiles = numMissiles;
        m_sample = engine::sounds::getSample(sample);
        registerMissileModel(modelName, this);
    }

    int MissileModel::getDamage()
    {
        return m_damage;
    }

    float MissileModel::getFirePeriod()
    {
        return m_firePeriod;
    }

    int MissileModel::getNumMissiles()
    {
        return m_numMissiles;
    }

    float MissileModel::getAngle()
    {
        return m_angle;
    }

    bool MissileModel::isLaser()
    {
        return false;
    }

    std::vector<Missile*> MissileModel::fire(lua_State* L, engine::Vector2d position, float angle, Entity::Side side, bool useParams, bool playSample, Entity* shooter)
    {
        if (m_sample != NULL && playSample)
            m_sample->play(position);

        std::vector<Missile*> missiles;

        if (m_numMissiles > 1)
        {
            if (m_angle > 0)
            {
                for (int i = 0; i < m_numMissiles; i++)
                {
                    float missileAngle = angle - m_angle / 2 + m_angle / (m_numMissiles - 1) * i;
                    Missile* m = new Missile(this, position, missileAngle, side);

                    if (shooter != NULL)
                        m->setShooterId(shooter->getId());

                    lua::callPopFunction(L, this, m, i, useParams);
                    S(LivingMissiles)->addAfterMoving(m);
                    missiles.push_back(m);
                }
            }
            else
            {
                for (int i = 0; i < m_numMissiles; i++)
                {
                    Missile* m = new Missile(this, position + engine::Vector2d(angle - M_PI / 2) * (i + 0.5 - (float) m_numMissiles / 2) * 8, angle, side);

                    if (shooter != NULL)
                        m->setShooterId(shooter->getId());

                    lua::callPopFunction(L, this, m, i, useParams);
                    S(LivingMissiles)->addAfterMoving(m);
                    missiles.push_back(m);
                }
            }
        }
        else if (m_numMissiles == 1)
        {
            Missile* m = new Missile(this, position, angle, side);

            if (shooter != NULL)
                m->setShooterId(shooter->getId());

            lua::callPopFunction(L, this, m, 0, useParams);
            S(LivingMissiles)->addAfterMoving(m);
            missiles.push_back(m);
        }
        return missiles;
    }

    std::map<std::string, MissileModel*> missileModels;

    void registerMissileModel(std::string modelName, MissileModel* model)
    {
        missileModels[modelName] = model;
    }

    MissileModel* getMissileModel(std::string modelName)
    {
        return missileModels[modelName];
    }

    void freeMissileModels()
    {
        for (std::map<std::string, MissileModel*>::iterator it = missileModels.begin(); it != missileModels.end(); it++)
            delete it->second;

        missileModels.clear();
    }

}
