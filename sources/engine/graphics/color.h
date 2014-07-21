#ifndef ENGINE_GRAPHICS_COLOR_H
 #define ENGINE_GRAPHICS_COLOR_H

#include <GL/glew.h>

namespace engine
{
    namespace graphics
    {

        class ColorRGB
        {
            public:
                ColorRGB(GLubyte r, GLubyte g, GLubyte b);

                virtual void use();
                virtual void useClearColor();

                GLubyte r;
                GLubyte g;
                GLubyte b;
        };

        class ColorRGBA : public ColorRGB
        {
            public:
                ColorRGBA(GLubyte r, GLubyte g, GLubyte b, GLubyte a);

                virtual void use();
                virtual void useClearColor();

                GLubyte a;
        };

    }
}

#endif
