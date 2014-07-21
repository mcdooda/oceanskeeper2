#ifndef ENGINE_LUA_PAIR_H
 #define ENGINE_LUA_PAIR_H

#include <string>
#include <lua5.1/lua.hpp>

namespace engine
{
    namespace lua
    {

        class FakePair
        {
            public:
                FakePair(const char* key) : m_key(key) {}

                virtual void setField(lua_State* L) = 0;
                virtual void setGlobalField(lua_State* L) = 0;

            protected:
                const char* m_key;
        };

        template<typename T>
        class Pair : public FakePair
        {
            public:
                Pair(const char* key, T value) : FakePair(key), m_value(value)
                {

                }

                void setField(lua_State* L)
                {
                    lua_pushstring(L, m_key);
                    pushValue(L);
                    lua_settable(L, -3);
                }

                void setGlobalField(lua_State* L)
                {
                    lua_pushstring(L, m_key);
                    pushValue(L);
                    lua_gettable(L, LUA_GLOBALSINDEX);
                    lua_settable(L, -3);
                }

            private:
                void pushValue(lua_State* L);

                T m_value;
        };

        template class Pair<const char*>;
        template class Pair<int>;
        template class Pair<float>;
        template class Pair<lua_CFunction>;


        template<>
        void Pair<const char*>::pushValue(lua_State* L)
        {
            lua_pushstring(L, m_value);
        }

        template<>
        void Pair<int>::pushValue(lua_State* L)
        {
            lua_pushinteger(L, m_value);
        }

        template<>
        void Pair<float>::pushValue(lua_State* L)
        {
            lua_pushnumber(L, m_value);
        }

        template<>
        void Pair<lua_CFunction>::pushValue(lua_State* L)
        {
            lua_pushcfunction(L, m_value);
        }

    }
}

#endif
