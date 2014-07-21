#ifndef ENGINE_LUA_LUA_H
 #define ENGINE_LUA_LUA_H

#include <string>
#include <lua5.1/lua.hpp>
#include "pair.h"

namespace engine
{
    namespace lua
    {

        void init();
        lua_State* getState();

        void doFile(const char* filename);

        void saveCoroutine(const char* name, const char* filename);
        void resumeCoroutine(const char* name);
        bool isCoroutineDead(const char* name);

        void dbg(lua_State* L1 = NULL);

        int panic(lua_State* L);

    }
}

#endif
