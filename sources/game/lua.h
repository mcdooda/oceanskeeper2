#ifndef GAME_LUA_H
 #define GAME_LUA_H

#include "../engine/lua/lua.h"
#include "../engine/lua/pair.h"

namespace game
{
    namespace lua
    {

        void init(lua_State* L);

        void saveAiFunction(lua_State* L, void* model);
        void callAiFunction(lua_State* L, void* model, void* entity);

        void savePopFunction(lua_State* L, void* model);
        void callPopFunction(lua_State* L, void* model, void* entity, int id, bool useParams = false);

        void createExtraData(lua_State* L, void* entity);
        void deleteExtraData(lua_State* L, void* entity);
        void pushExtraData(lua_State* L, void* entity);

        void saveEntityId(lua_State* L, int id, void* entity);
        void deleteEntityId(lua_State* L, int id);
        void pushEntityById(lua_State* L, int id);

        void createTable(lua_State* L, void* key);
        void pushKey(lua_State* L, void* key, void* ud);
        void pushKey(lua_State* L, void* key, int index);

    }
}

#endif
