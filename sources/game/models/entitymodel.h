#ifndef GAME_MODELS_ENTITYMODEL_H
 #define GAME_MODELS_ENTITYMODEL_H

#include <string>

#include "../../engine/graphics/texture.h"

namespace game
{

    class EntityModel
    {
        public:
            EntityModel(float speed, std::string texture, bool hasAiFunction, bool hasPopFunction);

            float getSpeed();
            virtual engine::graphics::Texture* getTexture();
            bool hasAiFunction();
            bool hasPopFunction();

        protected:
            float m_speed;
            engine::graphics::Texture* m_texture;
            bool m_hasAiFunction;
            bool m_hasPopFunction;
    };

}

#endif
