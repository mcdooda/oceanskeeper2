#include "effect.h"

namespace game
{
    namespace luafunctions
    {
        namespace effect
        {

            void init(lua_State* L)
            {
                static luaL_reg effectlib[] = {
                    {"add", add},
                    {"getX", getX},
                    {"getY", getY},
                    {"getZ", getZ},
                    {"getPosition", getPosition},
                    {"setX", setX},
                    {"setY", setY},
                    {"setZ", setZ},
                    {"setPosition", setPosition},
                    {"setAlpha", setAlpha},
                    {"setScale", setScale},
                    {"setRotationX", setRotationX},
                    {"setRotationY", setRotationY},
                    {"setRotationZ", setRotationZ},
                    {NULL, NULL}
                };
                luaL_register(L, "Effect", effectlib);

                engine::lua::FakePair* consts[] = {
                    new engine::lua::Pair<int>("ABOVEALL", effects::Effect::ABOVEALL),
                    new engine::lua::Pair<int>("ABOVE", effects::Effect::ABOVE),
                    new engine::lua::Pair<int>("BELOWALL", effects::Effect::BELOWALL),
                    new engine::lua::Pair<int>("BELOW", effects::Effect::BELOW),
                    NULL
                };
                for (int i = 0; consts[i] != NULL; i++)
                    consts[i]->setField(L);

                lua_pop(L, 1);
            }

            effects::LuaEffect* getEffect(lua_State* L)
            {
                luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
                return (effects::LuaEffect*) lua_touserdata(L, 1);
            }

            int add(lua_State* L)
            {
                std::string texture = luaL_checkstring(L, 1);
                float duration = luaL_checknumber(L, 2);
                engine::Vector3d position;
                position.x = luaL_checknumber(L, 3);
                position.y = luaL_checknumber(L, 4);
                position.z = luaL_checknumber(L, 5);
                effects::Effect::Layer layer = (effects::Effect::Layer) luaL_checkint(L, 6);
                luaL_argcheck(L, layer == effects::Effect::BELOWALL || layer == effects::Effect::BELOW || layer == effects::Effect::ABOVE || layer == effects::Effect::ABOVEALL, 5, "Invalid effect layer");

                new effects::LuaEffect(L, texture, duration, position, layer);
                return 1;
            }

            int getX(lua_State* L)
            {
                lua_pushnumber(L, getEffect(L)->getX());
                return 1;
            }

            int getY(lua_State* L)
            {
                lua_pushnumber(L, getEffect(L)->getY());
                return 1;
            }

            int getZ(lua_State* L)
            {
                lua_pushnumber(L, getEffect(L)->getZ());
                return 1;
            }

            int getPosition(lua_State* L)
            {
                engine::Vector3d position = getEffect(L)->getPosition();
                lua_pushnumber(L, position.x);
                lua_pushnumber(L, position.y);
                lua_pushnumber(L, position.z);
                return 3;
            }

            int setX(lua_State* L)
            {
                getEffect(L)->setX(luaL_checknumber(L, 2));
                return 0;
            }

            int setY(lua_State* L)
            {
                getEffect(L)->setY(luaL_checknumber(L, 2));
                return 0;
            }

            int setZ(lua_State* L)
            {
                getEffect(L)->setZ(luaL_checknumber(L, 2));
                return 0;
            }

            int setPosition(lua_State* L)
            {
                getEffect(L)->setPosition(engine::Vector3d(luaL_checknumber(L, 2), luaL_checknumber(L, 3), luaL_checknumber(L, 4)));
                return 0;
            }

            int setAlpha(lua_State* L)
            {
                getEffect(L)->setAlpha(luaL_checknumber(L, 2));
                return 0;
            }

            int setScale(lua_State* L)
            {
                getEffect(L)->setScale(luaL_checknumber(L, 2));
                return 0;
            }

            int setRotationX(lua_State* L)
            {
                getEffect(L)->setRotationX(luaL_checknumber(L, 2));
                return 0;
            }

            int setRotationY(lua_State* L)
            {
                getEffect(L)->setRotationY(luaL_checknumber(L, 2));
                return 0;
            }

            int setRotationZ(lua_State* L)
            {
                getEffect(L)->setRotationZ(luaL_checknumber(L, 2));
                return 0;
            }

        }
    }
}
