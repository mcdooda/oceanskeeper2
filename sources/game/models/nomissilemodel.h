#ifndef GAME_MODELS_NOMISSILEMODEL_H
 #define GAME_MODELS_NOMISSILEMODEL_H

#include "missilemodel.h"

namespace game
{

    class NoMissileModel : public MissileModel
    {
        public:
            NoMissileModel();

            virtual Missile* fire(lua_State* L, engine::Vector2d position, float angle, Entity::Side side, bool useParams = false);
    };

}

#endif
