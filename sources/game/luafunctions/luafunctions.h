#ifndef GAME_LUAFUNCTIONS_LUAFUNCTIONS_H
 #define GAME_LUAFUNCTIONS_LUAFUNCTIONS_H

#include <lua5.1/lua.hpp>

namespace game
{
    namespace luafunctions
    {

        void init(lua_State* L);

        int newUnitModel(lua_State* L);
        int popUnit(lua_State* L);

        int newMissileModel(lua_State* L);
        int popMissile(lua_State* L);

        int getNumEnemies(lua_State* L);
        int getNumAllies(lua_State* L);

        int getOldestEnemy(lua_State* L);

        int getShip(lua_State* L);

        int getTime(lua_State* L);
        int getFrameTime(lua_State* L);

        int addLevelUpScore(lua_State* L);

    }
}

#endif
