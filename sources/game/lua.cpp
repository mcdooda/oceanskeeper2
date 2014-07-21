#include "lua.h"
#include "models/entitymodel.h"

namespace game
{
    namespace lua
    {

        static const char entity_extra_data_index = ' ';
        static const char entity_model_ai_index = ' ';
        static const char entity_model_pop_index = ' ';
        static const char entity_id_index = ' ';

        void init(lua_State* L)
        {
            createTable(L, (void*) &entity_extra_data_index);
            createTable(L, (void*) &entity_model_ai_index);
            createTable(L, (void*) &entity_model_pop_index);
            createTable(L, (void*) &entity_id_index);
        }

        void saveAiFunction(lua_State* L, void* model)
        {
            pushKey(L, (void*) &entity_model_ai_index, model);
            lua_pushvalue(L, -3);
            lua_settable(L, -3);
        }

        void callAiFunction(lua_State* L, void* model, void* entity)
        {
            if (((EntityModel*) model)->hasAiFunction())
            {
                pushKey(L, (void*) &entity_model_ai_index, model);
                lua_gettable(L, -2);
                lua_pushlightuserdata(L, entity);
                lua_call(L, 1, 0);
                lua_pop(L, 1);
            }
        }

        void savePopFunction(lua_State* L, void* model)
        {
            pushKey(L, (void*) &entity_model_pop_index, model);
            lua_pushvalue(L, -3);
            lua_settable(L, -3);
        }

        void callPopFunction(lua_State* L, void* model, void* entity, int id, bool useParams)
        {
            if (((EntityModel*) model)->hasPopFunction())
            {
                pushKey(L, (void*) &entity_model_pop_index, model);
                lua_gettable(L, -2);
                lua_pushlightuserdata(L, entity);

                if (useParams)
                    lua_getfield(L, 1, "params");

                else
                    lua_pushnil(L);

                lua_pushinteger(L, id);

                lua_call(L, 3, 0);
                lua_pop(L, 1);
            }
        }

        void createExtraData(lua_State* L, void* entity)
        {
            pushKey(L, (void*) &entity_extra_data_index, entity);
            lua_newtable(L);
            lua_settable(L, -3);
            lua_pop(L, 1);
        }

        void deleteExtraData(lua_State* L, void* entity)
        {
            pushKey(L, (void*) &entity_extra_data_index, entity);
            lua_pushnil(L);
            lua_settable(L, -3);
            lua_pop(L, 1);
        }

        void pushExtraData(lua_State* L, void* entity)
        {
            pushKey(L, (void*) &entity_extra_data_index, entity);
            lua_gettable(L, -2);
        }


        void saveEntityId(lua_State* L, int id, void* entity)
        {
            pushKey(L, (void*) &entity_id_index, id);
            lua_pushlightuserdata(L, entity);
            lua_settable(L, -3);
            lua_pop(L, 1);
        }

        void deleteEntityId(lua_State* L, int id)
        {
            pushKey(L, (void*) &entity_id_index, id);
            lua_pushnil(L);
            lua_settable(L, -3);
            lua_pop(L, 1);
        }

        void pushEntityById(lua_State* L, int id)
        {
            pushKey(L, (void*) &entity_id_index, id);
            lua_gettable(L, -2);
        }

        void createTable(lua_State* L, void* key)
        {
            lua_pushlightuserdata(L, key);
            lua_newtable(L);
            lua_settable(L, LUA_REGISTRYINDEX);
        }

        void pushKey(lua_State* L, void* key, void* ud)
        {
            lua_pushlightuserdata(L, key);
            lua_gettable(L, LUA_REGISTRYINDEX);
            lua_pushlightuserdata(L, ud);
        }

        void pushKey(lua_State* L, void* key, int index)
        {
            lua_pushlightuserdata(L, key);
            lua_gettable(L, LUA_REGISTRYINDEX);
            lua_pushinteger(L, index);
        }

    }
}
