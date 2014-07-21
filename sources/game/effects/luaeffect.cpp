#include "luaeffect.h"

namespace game
{
    namespace effects
    {

        LuaEffect::LuaEffect(lua_State* L, std::string texture, float duration, engine::Vector3d position, Layer layer) :
            Effect(texture, duration, position, layer)
        {
            luaL_checktype(L, -1, LUA_TFUNCTION);
            lua_pushlightuserdata(L, this);
            lua_pushvalue(L, -2);
            lua_settable(L, LUA_REGISTRYINDEX);
            Effect::addStep(duration, true);
            m_scale = 1;
            m_alpha = 1;
        }

        LuaEffect::~LuaEffect()
        {
            lua_State* L = engine::lua::getState();
            //engine::lua::dbg(L);
            lua_pushlightuserdata(L, this);
            lua_pushvalue(L, -1);
            lua_gettable(L, LUA_REGISTRYINDEX);
            lua_pushvalue(L, -2);
            lua_pushnumber(L, 1);
            lua_pushinteger(L, m_steps.size() - 1);
            lua_pushnumber(L, 1);
            lua_call(L, 4, 0);
            //engine::lua::dbg(L);
            lua_pop(L, 1);

            lua_pushlightuserdata(L, this);
            lua_pushnil(L);
            lua_settable(L, LUA_REGISTRYINDEX);
        }

        void LuaEffect::show()
        {
            lua_State* L = engine::lua::getState();
            //engine::lua::dbg(L);
            lua_pushlightuserdata(L, this);
            lua_pushvalue(L, -1);
            lua_gettable(L, LUA_REGISTRYINDEX);
            lua_pushvalue(L, -2);
            lua_pushnumber(L, getProgression());
            calcCurrentStep();
            lua_pushinteger(L, m_currentStepIndex);
            lua_pushnumber(L, getStepProgression());
            lua_call(L, 4, 0);
            //engine::lua::dbg(L);
            lua_pop(L, 1);
            m_texture->show(m_position, m_rotation, engine::graphics::ColorRGBA(255, 255, 255, m_alpha * 255), m_scale);
        }

        float LuaEffect::getX()
        {
            return m_position.x;
        }

        float LuaEffect::getY()
        {
            return m_position.y;
        }

        float LuaEffect::getZ()
        {
            return m_position.z;
        }

        engine::Vector3d LuaEffect::getPosition()
        {
            return m_position;
        }

        void LuaEffect::setX(float x)
        {
            m_position.x = x;
        }

        void LuaEffect::setY(float y)
        {
            m_position.y = y;
        }

        void LuaEffect::setZ(float z)
        {
            m_position.z = z;
        }

        void LuaEffect::setPosition(engine::Vector3d position)
        {
            m_position = position;
        }

        void LuaEffect::setAlpha(float alpha)
        {
            m_alpha = alpha;
        }

        void LuaEffect::setScale(float scale)
        {
            m_scale = scale;
        }

        void LuaEffect::setRotationX(float rotationX)
        {
            m_rotation.x = rotationX;
        }

        void LuaEffect::setRotationY(float rotationY)
        {
            m_rotation.y = rotationY;
        }

        void LuaEffect::setRotationZ(float rotationZ)
        {
            m_rotation.z = rotationZ;
        }

        void LuaEffect::add(const char* name, engine::Vector3d position)
        {
            lua_State* L = engine::lua::getState();
            lua_getglobal(L, "Effect");
            lua_pushstring(L, "models");
            lua_gettable(L, -2);
            lua_pushstring(L, name);
            lua_gettable(L, -2);
            lua_pushnumber(L, position.x);
            lua_pushnumber(L, position.y);
            lua_pushnumber(L, position.z);
            lua_call(L, 3, 0);
            lua_pop(L, 2);
        }

    }
}
