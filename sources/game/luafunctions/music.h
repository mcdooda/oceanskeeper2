#ifndef GAME_LUAFUNCTIONS_SOUNDS_H
 #define GAME_LUAFUNCTIONS_SOUNDS_H

#include <lua5.1/lua.hpp>

#include "../../engine/sounds/music.h"

namespace game
{
    namespace luafunctions
    {
        namespace music
        {
            void init(lua_State* L);

            engine::sounds::Music* getMusic(lua_State* L, int index = 1);

            int get(lua_State* L);

            int play(lua_State* L);
            int stop(lua_State* L);
            int setVolume(lua_State* L);
        }
    }
}

#endif
