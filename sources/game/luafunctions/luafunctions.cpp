#include "../../engine/time.h"
#include "../../engine/singleton.h"
#include "../../engine/lua/lua.h"

#include "luafunctions.h"
#include "../entities/unit.h"
#include "../entities/missile.h"
#include "../models/unitmodel.h"
#include "../livingentities.h"
#include "../models/missilemodel.h"
#include "../models/lasermodel.h"
#include "../field.h"
#include "../entities/ship.h"
#include "../lua.h"
#include "../score.h"

#include <iostream>

namespace game
{
    namespace luafunctions
    {

        void init(lua_State* L)
        {
            static luaL_reg global[] = {
                {"newUnitModel", newUnitModel},
                {"popUnit", popUnit},

                {"newMissileModel", newMissileModel},
                {"popMissile", popMissile},

                {"getNumEnemies", getNumEnemies},
                {"getNumAllies", getNumAllies},

                {"getOldestEnemy", getOldestEnemy},

                {"getShip", getShip},

                {"getTime", getTime},
                {"getFrameTime", getFrameTime},

                {"addLevelUpScore", addLevelUpScore},

                {NULL, NULL}
            };
            luaL_register(L, "_G", global);

            using namespace engine::lua;

            Field* field = S(Field);

            FakePair* consts[] = {
                new Pair<int>("CENTER_X", field->getCenterX()),
                new Pair<int>("CENTER_Y", field->getCenterY()),
                new Pair<int>("MIN_X", field->getMinX()),
                new Pair<int>("MIN_Y", field->getMinY()),
                new Pair<int>("MAX_X", field->getMaxX()),
                new Pair<int>("MAX_Y", field->getMaxY()),

                new Pair<int>("ENEMY", Entity::ENEMY),
                new Pair<int>("ALLY", Entity::ALLY),

                NULL
            };
            for (int i = 0; consts[i] != NULL; i++)
                consts[i]->setField(L);

            lua_pop(L, 1);
        }

        int newUnitModel(lua_State* L)
        {
            luaL_checktype(L, 1, LUA_TTABLE);
            luaL_checktype(L, 1, LUA_TTABLE);

            lua_getfield(L, 1, "name");
            const char* name = luaL_checkstring(L, -1);

            lua_getfield(L, 1, "missile");
            const char* missile = luaL_checkstring(L, -1);

            lua_getfield(L, 1, "health");
            float health = luaL_checkint(L, -1);

            lua_getfield(L, 1, "speed");
            float speed = luaL_checknumber(L, -1);

            lua_getfield(L, 1, "texture");
            const char* texture = luaL_checkstring(L, -1);

            lua_getfield(L, 1, "ai");
            bool hasAiFunction = lua_isfunction(L, -1);

            lua_getfield(L, 1, "pop");
            bool hasPopFunction = lua_isfunction(L, -1);

            UnitModel* unitmodel = new UnitModel(name, missile, health, speed, texture, hasAiFunction, hasPopFunction);

            if (hasAiFunction || hasPopFunction)
            {
                using namespace engine::lua;

                if (hasAiFunction)
                {
                    lua_getfield(L, 1, "ai");
                    lua::saveAiFunction(engine::lua::getState(), unitmodel);
                }

                if (hasPopFunction)
                {
                    lua_getfield(L, 1, "pop");
                    lua::savePopFunction(engine::lua::getState(), unitmodel);
                }
            }

            return 0;
        }

        int popUnit(lua_State* L)
        {
            luaL_checktype(L, 1, LUA_TTABLE);

            lua_getfield(L, 1, "model");
            UnitModel* model = getUnitModel(luaL_checkstring(L, -1));

            lua_getfield(L, 1, "position");
            luaL_checktype(L, -1, LUA_TTABLE);
            lua_pushinteger(L, 1);
            lua_gettable(L, -2);
            float x = luaL_checknumber(L, -1);
            lua_pushinteger(L, 2);
            lua_gettable(L, -3);
            float y = luaL_checknumber(L, -1);

            lua_getfield(L, 1, "angle");
            float angle = luaL_checknumber(L, -1);

            lua_getfield(L, 1, "side");
            Entity::Side side = (Entity::Side) luaL_checkint(L, -1);
            if (side != Entity::ALLY && side != Entity::ENEMY)
                return luaL_error(L, "units' side must be ALLY or ENEMY");

            lua_getfield(L, 1, "invincible");
            bool invincible = lua_toboolean(L, -1);

            Unit* unit = new Unit(model, engine::Vector2d(x, y), angle, side, invincible);

            S(LivingUnits)->addAfterMoving(unit);

            lua::callPopFunction(L, model, unit, 0, true);

            lua_pushlightuserdata(L, (void*) unit); // return unit

            return 1;
        }

        int newMissileModel(lua_State* L)
        {
            luaL_checktype(L, 1, LUA_TTABLE);

            lua_getfield(L, 1, "name");
            const char* name = luaL_checkstring(L, -1);

            lua_getfield(L, 1, "damage");
            int damage = luaL_checkint(L, -1);

            lua_getfield(L, 1, "firePeriod");
            float firePeriod = luaL_checknumber(L, -1);

            lua_getfield(L, 1, "numMissiles");
            int numMissiles = luaL_checknumber(L, -1);

            float angle = 0;
            if (numMissiles > 1)
            {
                lua_getfield(L, 1, "angle");
                angle = luaL_checknumber(L, -1);
            }

            lua_getfield(L, 1, "speed");
            float speed = luaL_checknumber(L, -1);

            lua_getfield(L, 1, "texture");
            const char* texture = luaL_checkstring(L, -1);

            lua_getfield(L, 1, "sample");
            const char* sample = luaL_optstring(L, -1, "");

            lua_getfield(L, 1, "ai");
            bool hasAiFunction = lua_isfunction(L, -1);

            lua_getfield(L, 1, "pop");
            bool hasPopFunction = lua_isfunction(L, -1);

            lua_getfield(L, 1, "laser");
            bool isLaser = lua_toboolean(L, -1);

            const char* texture2;
            const char* texture3;

            if (isLaser)
            {
                lua_getfield(L, 1, "texture2");
                texture2 = luaL_checkstring(L, -1);

                lua_getfield(L, 1, "texture3");
                texture3 = luaL_checkstring(L, -1);
            }

            MissileModel* missilemodel;

            if (!isLaser)
                missilemodel = new MissileModel(name, damage, firePeriod, angle, numMissiles, speed, texture, sample, hasAiFunction, hasPopFunction);

            else
                missilemodel = new LaserModel(name, damage, firePeriod, angle, numMissiles, speed, texture, texture2, texture3, sample, hasAiFunction, hasPopFunction);

            if (hasAiFunction || hasPopFunction)
            {
                using namespace engine::lua;

                if (hasAiFunction)
                {
                    lua_getfield(L, 1, "ai");
                    lua::saveAiFunction(engine::lua::getState(), missilemodel);
                }

                if (hasPopFunction)
                {
                    lua_getfield(L, 1, "pop");
                    lua::savePopFunction(engine::lua::getState(), missilemodel);
                }
            }

            return 0;
        }

        int popMissile(lua_State* L)
        {
            luaL_checktype(L, 1, LUA_TTABLE);

            lua_getfield(L, 1, "model");
            MissileModel* model = getMissileModel(luaL_checkstring(L, -1));

            lua_getfield(L, 1, "position");
            luaL_checktype(L, -1, LUA_TTABLE);
            lua_pushinteger(L, 1);
            lua_gettable(L, -2);
            float x = luaL_checknumber(L, -1);
            lua_pushinteger(L, 2);
            lua_gettable(L, -3);
            float y = luaL_checknumber(L, -1);

            lua_getfield(L, 1, "angle");
            float angle = luaL_checknumber(L, -1);

            lua_getfield(L, 1, "side");
            Entity::Side side = (Entity::Side) luaL_checkint(L, -1);
            if (side != Entity::ALLY && side != Entity::ENEMY)
                return luaL_error(L, "missiles' side must be ALLY or ENEMY");

            lua_getfield(L, 1, "playSample");
            bool playSample = lua_toboolean(L, -1);

            std::vector<Missile*> missiles = model->fire(L, engine::Vector2d(x, y), angle, side, true, playSample);
            std::vector<Missile*>::iterator end = missiles.end();

            lua_createtable(L, missiles.size(), 0);
            int i = 1;
            for (std::vector<Missile*>::iterator it = missiles.begin(); it != end; it++)
            {
                lua_pushinteger(L, i);
                lua_pushlightuserdata(L, (void*) *it);
                lua_settable(L, -3);
                i++;
            }

            return 1;
        }

        int getNumEnemies(lua_State* L)
        {
            lua_pushinteger(L, S(LivingUnits)->getNumBySide(Entity::ENEMY));
            return 1;
        }

        int getNumAllies(lua_State* L)
        {
            lua_pushinteger(L, S(LivingUnits)->getNumBySide(Entity::ALLY));
            return 1;
        }

        int getOldestEnemy(lua_State* L)
        {
            if (S(LivingUnits)->getNumBySide(Entity::ENEMY) > 0)
                lua_pushlightuserdata(L, S(LivingUnits)->getOldestBySide(Entity::ENEMY));

            else
                lua_pushnil(L);

            return 1;
        }

        int getShip(lua_State* L)
        {
            lua_pushlightuserdata(L, (void*) S(Ship));
            return 1;
        }

        int getTime(lua_State* L)
        {
            lua_pushnumber(L, engine::time::getTime());
            return 1;
        }

        int getFrameTime(lua_State* L)
        {
            lua_pushnumber(L, engine::time::getFrameTime());
            return 1;
        }

        int addLevelUpScore(lua_State* L)
        {
            S(Score)->addLevelUpScore(luaL_checkint(L, 1));
            return 0;
        }

    }
}
