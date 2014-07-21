#ifndef ENGINE_GRAPHICS_TEXT_H
 #define ENGINE_GRAPHICS_TEXT_H

#include <string>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "../vector2d.h"

namespace engine
{
    namespace graphics
    {

        class Text
        {
            public:
                Text(std::string text, int size);

                void show(Vector2d pos);

            private:
                sf::String m_text;
        };

    }
}

#endif
