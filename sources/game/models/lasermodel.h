#ifndef GAME_MODELS_LASER_H
 #define GAME_MODELS_LASER_H

#include "missilemodel.h"

namespace game
{

    class LaserModel : public MissileModel
    {
        public:
            LaserModel(std::string modelName, int damage, float firePeriod, float angle, int numMissiles, float speed, std::string texture, std::string texture2, std::string texture3, std::string sample, bool hasAiFunction, bool hasPopFunction);

            virtual bool isLaser();

            virtual std::vector<Missile*> fire(lua_State* L, engine::Vector2d position, float angle, Entity::Side side, bool useParams = false, bool playSample = true, Entity* shooter = NULL);

            engine::graphics::Texture* getTexture2();
            engine::graphics::Texture* getTexture3();

        private:
            engine::graphics::Texture* m_texture2;
            engine::graphics::Texture* m_texture3;
    };

}

#endif



