#ifndef GAME_LUAFUNCTIONS_EFFECT_H
 #define GAME_LUAFUNCTIONS_EFFECT_H

#include <lua5.1/lua.hpp>
#include "../effects/luaeffect.h"

namespace game
{
    namespace luafunctions
    {
        namespace effect
        {

            void init(lua_State* L);

            effects::LuaEffect* getEffect(lua_State* L);

            int add(lua_State* L);

            int getX(lua_State* L);
            int getY(lua_State* L);
            int getZ(lua_State* L);
            int getPosition(lua_State* L);

            int setX(lua_State* L);
            int setY(lua_State* L);
            int setZ(lua_State* L);
            int setPosition(lua_State* L);

            int setAlpha(lua_State* L);
            int setScale(lua_State* L);

            int setRotationX(lua_State* L);
            int setRotationY(lua_State* L);
            int setRotationZ(lua_State* L);

        }
    }
}

#endif
