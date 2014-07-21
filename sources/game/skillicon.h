#ifndef GAME_SKILLICON_H
 #define GAME_SKILLICON_H

#include <string>

#include "../engine/graphics/texture.h"
#include "../engine/vector2d.h"

namespace game
{

    class SkillIcon
    {
        public:
            SkillIcon(std::string icon, std::string loadingIcon);

            void show(float loading, engine::Vector3d pos);

        private:

            engine::graphics::Texture* m_icon;
            engine::graphics::Texture* m_loadingIcon;
    };

}

#endif
