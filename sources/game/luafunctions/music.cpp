#include "music.h"

namespace game
{
    namespace luafunctions
    {
        namespace music
        {

            void init(lua_State* L)
            {
                static luaL_reg musiclib[] = {
                    {"get", get},

                    {"play", play},
                    {"stop", stop},
                    {"setVolume", setVolume},

                    {NULL, NULL}
                };
                luaL_register(L, "Music", musiclib);
                lua_pop(L, 1);
            }

            engine::sounds::Music* getMusic(lua_State* L, int index)
            {
                luaL_checktype(L, index, LUA_TLIGHTUSERDATA);
                return (engine::sounds::Music*) lua_touserdata(L, index);
            }

            int get(lua_State* L)
            {
                const char* filename = luaL_checkstring(L, 1);
                lua_pushlightuserdata(L, engine::sounds::getMusic(filename));
                return 1;
            }

            int play(lua_State* L)
            {
                getMusic(L)->play();
                return 0;
            }

            int stop(lua_State* L)
            {
                getMusic(L)->stop();
                return 0;
            }

            int setVolume(lua_State* L)
            {
                getMusic(L)->setVolume(luaL_checknumber(L, 2));
                return 0;
            }

        }
    }
}


