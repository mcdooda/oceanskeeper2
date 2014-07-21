#include "nomissilemodel.h"

namespace game
{

    NoMissileModel::NoMissileModel() : MissileModel("NoMissile", 0, 0, 0, 0, 0, "blank.png", "", false, false)
    {

    }

    Missile* NoMissileModel::fire(lua_State* L, engine::Vector2d position, float angle, Entity::Side side, bool useParams)
    {
        return NULL;
    }

}
