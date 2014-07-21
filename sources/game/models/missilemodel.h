#ifndef GAME_MODELS_MISSILEMODEL_H
 #define GAME_MODELS_MISSILEMODEL_H

#include <string>

#include "../../engine/vector2d.h"
#include "../../engine/sounds/sample.h"

#include "../entities/entity.h"
#include "entitymodel.h"
#include "../lua.h"
#include "../entities/missile.h"

namespace game
{

    class Missile;

    class MissileModel : public EntityModel
    {
        public:
            MissileModel(std::string modelName, int damage, float firePeriod, float angle, int numMissiles, float speed, std::string texture, std::string sample, bool hasAiFunction, bool hasPopFunction);

            int getDamage();
            float getFirePeriod();
            int getNumMissiles();
            float getAngle();

            virtual bool isLaser();

            virtual std::vector<Missile*> fire(lua_State* L, engine::Vector2d position, float angle, Entity::Side side, bool useParams = false, bool playSample = true, Entity* shooter = NULL);

        protected:
            int m_damage;
            float m_firePeriod;
            float m_angle;
            int m_numMissiles;
            engine::sounds::Sample* m_sample;
    };

    void registerMissileModel(std::string modelName, MissileModel* model);
    MissileModel* getMissileModel(std::string modelName);
    void freeMissileModels();
}

#endif
