#ifndef GAME_EFFECTS_LUAEFFECT_H
 #define GAME_EFFECTS_LUAEFFECT_H

#include "effect.h"
#include "../../engine/lua/lua.h"

namespace game
{
    namespace effects
    {

        class LuaEffect : public Effect
        {
            public:
                LuaEffect(lua_State* L, std::string texture, float duration, engine::Vector3d position, Layer layer);
                ~LuaEffect();

                void show();

                float getX();
                float getY();
                float getZ();
                engine::Vector3d getPosition();

                void setX(float x);
                void setY(float y);
                void setZ(float z);
                void setPosition(engine::Vector3d position);

                void setAlpha(float alpha);
                void setScale(float scale);
                void setRotationX(float rotationX);
                void setRotationY(float rotationY);
                void setRotationZ(float rotationZ);

                static void add(const char* name, engine::Vector3d position);

            private:
                engine::Vector3d m_rotation;
                float m_scale;
                float m_alpha;

        };

    }
}

#endif

