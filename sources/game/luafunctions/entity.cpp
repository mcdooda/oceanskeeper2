#include "../../engine/time.h"
#include "../../engine/singleton.h"

#include "../lua.h"
#include "../livingentities.h"
#include "../entities/unit.h"
#include "../entities/shield.h"
#include "entity.h"

namespace game
{
    namespace luafunctions
    {
        namespace entity
        {

            void init(lua_State* L)
            {
                static luaL_reg entitylib[] = {
                    {"getX", getX},
                    {"getY", getY},
                    {"getZ", getZ},
                    {"getPosition", getPosition},
                    {"getAngle", getAngle},

                    {"setX", setX},
                    {"setY", setY},
                    {"setZ", setZ},
                    {"setPosition", setPosition},

                    {"getDistance", getDistance},
                    {"getDistanceSquared", getDistanceSquared},

                    {"getHealth", getHealth},
                    {"setHealth", setHealth},

                    {"setSpeed", setSpeed},
                    {"setAngle", setAngle},
                    {"turn", turn},
                    {"lookAt", lookAt},
                    {"setDirection", setDirection},

                    {"killUnit", killUnit},
                    {"destroyUnit", destroyUnit},
                    {"destroyMissile", destroyMissile},

                    {"getMissileShooterId", getMissileShooterId},

                    {"newShield", newShield},
                    {"isInvincibleUnit", isInvincibleUnit},

                    {"getExtraData", getExtraData},

                    {"getId", getId},
                    {"getById", getById},

                    {NULL, NULL}
                };
                luaL_register(L, "Entity", entitylib);
                lua_pop(L, 1);
            }

            Entity* getEntity(lua_State* L, int index)
            {
                luaL_checktype(L, index, LUA_TLIGHTUSERDATA);
                return (Entity*) lua_touserdata(L, index);
            }

            int getX(lua_State* L)
            {
                lua_pushnumber(L, getEntity(L)->getPosition().x);
                return 1;
            }

            int getY(lua_State* L)
            {
                lua_pushnumber(L, getEntity(L)->getPosition().y);
                return 1;
            }
            
            int getZ(lua_State* L)
            {
                lua_pushnumber(L, getEntity(L)->getPosition().z);
                return 1;
            }

            int getPosition(lua_State* L)
            {
                Entity* entity = getEntity(L);
                lua_pushnumber(L, entity->getPosition().x);
                lua_pushnumber(L, entity->getPosition().y);
                //lua_pushnumber(L, entity->getPosition().z);
                return 2;
            }

            int getAngle(lua_State* L)
            {
                lua_pushnumber(L, getEntity(L)->getAngle());
                return 1;
            }

            int setX(lua_State* L)
            {
                getEntity(L)->setX(luaL_checknumber(L, 2));
                return 0;
            }

            int setY(lua_State* L)
            {
                getEntity(L)->setY(luaL_checknumber(L, 2));
                return 0;
            }
            
            int setZ(lua_State* L)
            {
                getEntity(L)->setZ(luaL_checknumber(L, 2));
                return 0;
            }

            int setPosition(lua_State* L)
            {
                Entity* entity = getEntity(L);
                entity->setX(luaL_checknumber(L, 2));
                entity->setY(luaL_checknumber(L, 3));
                return 0;
            }

            int getDistance(lua_State* L)
            {
                lua_pushnumber(L, (getEntity(L)->getPosition() - getEntity(L, 2)->getPosition()).distance());
                return 1;
            }

            int getDistanceSquared(lua_State* L)
            {
                lua_pushnumber(L, (getEntity(L)->getPosition() - getEntity(L, 2)->getPosition()).distanceSquared());
                return 1;
            }

            int setHealth(lua_State* L)
            {
                ((Unit*) getEntity(L))->setHealth(luaL_checknumber(L, 2));
                return 0;
            }

            int getHealth(lua_State* L)
            {
                lua_pushnumber(L, ((Unit*) getEntity(L))->getHealth());
                return 1;
            }

            int setSpeed(lua_State* L)
            {
                float speed = luaL_checknumber(L, 2);
                getEntity(L)->setSpeed(speed);
                return 0;
            }

            int turn(lua_State* L)
            {
                float angle = luaL_checknumber(L, 2);
                getEntity(L)->turn(angle, engine::time::getFrameTime());
                return 0;
            }

            int setAngle(lua_State* L)
            {
                float angle = luaL_checknumber(L, 2);
                getEntity(L)->setAngle(angle);
                return 0;
            }

            int lookAt(lua_State* L)
            {
                getEntity(L)->lookAt(getEntity(L, 2));
                return 0;
            }

            int setDirection(lua_State* L)
            {
                float x = luaL_checknumber(L, 2);
                float y = luaL_checknumber(L, 3);
                getEntity(L)->setDirection(engine::Vector2d(x, y));
                return 0;
            }

            int killUnit(lua_State* L)
            {
                Unit* unit = (Unit*) getEntity(L);
                unit->kill();
                S(LivingUnits)->remove(unit);
                return 0;
            }

            int destroyUnit(lua_State* L)
            {
                S(LivingUnits)->remove(getEntity(L));
                return 0;
            }

            int destroyMissile(lua_State* L)
            {
                S(LivingMissiles)->remove(getEntity(L));
                return 0;
            }

            int getMissileShooterId(lua_State* L)
            {
                Missile* missile = (Missile*) getEntity(L);
                lua_pushinteger(L, missile->getShooterId());
                return 1;
            }

            int newShield(lua_State* L)
            {
                float shieldHealth = luaL_checkint(L, 2);
                Shield* s = new Shield((Unit*) getEntity(L), shieldHealth);
                S(LivingUnits)->addAfterMoving(s);
                return 0;
            }

            int isInvincibleUnit(lua_State* L)
            {
                lua_pushboolean(L, ((Unit*) getEntity(L))->isInvincible());
                return 1;
            }

            int getExtraData(lua_State* L)
            {
                lua::pushExtraData(L, getEntity(L));
                return 1;
            }

            int getId(lua_State* L)
            {
                lua_pushinteger(L, getEntity(L)->getId());
                return 1;
            }

            int getById(lua_State* L)
            {
                if (lua_isnil(L, 1))
                    lua_pushnil(L);

                else
                    lua::pushEntityById(L, luaL_checkint(L, 1));

                return 1;
            }

        }
    }
}

