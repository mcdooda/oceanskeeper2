#ifndef GAME_LUAFUNCTIONS_ENTITY_H
 #define GAME_LUAFUNCTIONS_ENTITY_H

#include <lua5.1/lua.hpp>

#include "../entities/entity.h"

namespace game
{
    namespace luafunctions
    {
        namespace entity
        {

            void init(lua_State* L);

            Entity* getEntity(lua_State* L, int index = 1);

            int getX(lua_State* L);
            int getY(lua_State* L);
            int getZ(lua_State* L);
            int getPosition(lua_State* L);
            int getAngle(lua_State* L);

            int setX(lua_State* L);
            int setY(lua_State* L);
            int setZ(lua_State* L);
            int setPosition(lua_State* L);

            int getDistance(lua_State* L);
            int getDistanceSquared(lua_State* L);

            int setHealth(lua_State* L);
            int getHealth(lua_State* L);

            int setSpeed(lua_State* L);
            int turn(lua_State* L);
            int setAngle(lua_State* L);
            int lookAt(lua_State* L);
            int setDirection(lua_State* L);

            int killUnit(lua_State* L);
            int destroyUnit(lua_State* L);
            int destroyMissile(lua_State* L);

            int getMissileShooterId(lua_State* L);

            int newShield(lua_State* L);
            int isInvincibleUnit(lua_State* L);

            int getExtraData(lua_State* L);

            int getId(lua_State* L);
            int getById(lua_State* L);

        }
    }
}

#endif
