#ifndef ENGINE_GRAPHICS_GRAPHICS_H
 #define ENGINE_GRAPHICS_GRAPHICS_H

#include "../vector2d.h"
#include "texture.h"
#include "color.h"

namespace engine
{
    namespace graphics
    {

        void init(ColorRGBA c, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);
        void initDisplay();
        void endDisplay();
        void drawRectangle(Vector2d a, Vector2d b, ColorRGBA c);
        void drawRectangle(Vector2d a, Vector2d b, ColorRGBA c, Texture* texture);

    }
}

#endif
