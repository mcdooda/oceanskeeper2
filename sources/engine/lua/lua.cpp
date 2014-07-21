#include "lua.h"

#include <iostream>

namespace engine
{
    namespace lua
    {
        static const char coroutine_resume_index = ' ';
        static const char coroutine_status_index = ' ';

        lua_State* L;

        void init()
        {
            L = luaL_newstate();
            luaL_openlibs(L);

            // remove os lib
            lua_pushnil(L);
            lua_setglobal(L, "os");

            // push coroutine.resume on the registry for faster access
            lua_getglobal(L, "coroutine");
            lua_getfield(L, -1, "resume");
            lua_pushlightuserdata(L, (void*) &coroutine_resume_index);
            lua_pushvalue(L, -2);
            lua_settable(L, LUA_REGISTRYINDEX);

            // push coroutine.status on the registry for faster access
            lua_getglobal(L, "coroutine");
            lua_getfield(L, -1, "status");
            lua_pushlightuserdata(L, (void*) &coroutine_status_index);
            lua_pushvalue(L, -2);
            lua_settable(L, LUA_REGISTRYINDEX);

            lua_settop(L, 0);

            lua_atpanic(L, panic);
        }

        lua_State* getState()
        {
            return L;
        }

        void doFile(const char* filename)
        {
            luaL_loadfile(L, filename);
            lua_call(L, 0, 0);
        }

        void saveCoroutine(const char* name, const char* filename)
        {
            luaL_loadfile(L, filename);
            lua_call(L, 0, 1);
            lua_setfield(L, LUA_REGISTRYINDEX, name);
        }

        void resumeCoroutine(const char* name)
        {
            lua_pushlightuserdata(L, (void*) &coroutine_resume_index);
            lua_gettable(L, LUA_REGISTRYINDEX);       // pushes coroutine.resume
            lua_getfield(L, LUA_REGISTRYINDEX, name); // pushes the argument
            //lua_call(L, 1, 0);

            lua_call(L, 1, 2);                        // calls the function
            if (!lua_toboolean(L, -2))
                lua_error(L);

            lua_pop(L, 2);
        }

        bool isCoroutineDead(const char* name)
        {
            lua_pushlightuserdata(L, (void*) &coroutine_status_index);
            lua_gettable(L, LUA_REGISTRYINDEX);       // pushes coroutine.status
            lua_getfield(L, LUA_REGISTRYINDEX, name); // pushes the argument
            lua_call(L, 1, 1);                        // calls the function
            lua_pushstring(L, "dead");
            bool dead = lua_rawequal(L, -2, -1);
            lua_pop(L, 2);
            return dead;
        }

        void dbg(lua_State* L1)
        {
            if (L1 == NULL)
                L1 = L;

            std::cout << std::endl << "--- Lua Debug (" << L1 << ((L == L1)? " [L == L1]" : "") << ") ==========" << std::endl;
            int top = lua_gettop(L1);
            std::cout << "top = " << top << std::endl;
            for (int i = 1; i <= top; i++)
            {
                std::cout << "#" << i << " : ";
                switch(lua_type(L1, i))
                {
                    case LUA_TLIGHTUSERDATA:
                    std::cout << "lightuserdata : " << lua_touserdata(L1, i);
                    break;

                    case LUA_TUSERDATA:
                    std::cout << "userdata ____ : " << lua_touserdata(L1, i);
                    break;

                    case LUA_TTABLE:
                    std::cout << "table _______ : " << lua_topointer(L1, i) << (lua_topointer(L1, i) == lua_topointer(L1, LUA_REGISTRYINDEX)? " (REGISTRY)" : "");
                    break;

                    case LUA_TNIL:
                    std::cout << "nil";
                    break;

                    case LUA_TFUNCTION:
                    std::cout << "function ____ : " << lua_topointer(L1, i);
                    break;

                    case LUA_TNUMBER:
                    std::cout << "number ______ : " << lua_tonumber(L1, i);
                    break;

                    case LUA_TBOOLEAN:
                    std::cout << "boolean _____ : " << (lua_toboolean(L1, i) ? "true" : "false");
                    break;

                    case LUA_TSTRING:
                    std::cout << "string ______ : " << lua_tostring(L1, i);
                    break;

                    case LUA_TTHREAD:
                    std::cout << "thread ______ : " << lua_topointer(L1, i);
                    break;

                    case LUA_TNONE:
                    std::cout << "none ________ : " << lua_topointer(L1, i);
                    break;

                    default:
                    std::cout << "unknown type  : " << lua_topointer(L1, i) << " (" << lua_typename(L1, i) << " ?)";
                    break;
                }
                std::cout << std::endl;
            }
            std::cout << "--- Lua Debug ======" << std::endl << std::endl;
        }

        int panic(lua_State* L)
        {
            std::cout << "~~~~ PANIC! ~~~~" << std::endl;
            dbg(L);
            std::cout << "~~~~ PANIC! ~~~~" << std::endl;
            return 0;
        }

    }
}
