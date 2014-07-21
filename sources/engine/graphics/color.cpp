#include "color.h"

namespace engine
{
    namespace graphics
    {

        ColorRGB::ColorRGB(GLubyte r, GLubyte g, GLubyte b) : r(r), g(g), b(b)
        {

        }

        void ColorRGB::use()
        {
            glColor3ub(r, g, b);
        }

        void ColorRGB::useClearColor()
        {
            glClearColor((float) r / 255, (float) g / 255, (float) b / 255, 1);
        }

        ColorRGBA::ColorRGBA(GLubyte r, GLubyte g, GLubyte b, GLubyte a) : ColorRGB(r, g, b), a(a)
        {

        }

        void ColorRGBA::use()
        {
            glColor4ub(r, g, b, a);
        }

        void ColorRGBA::useClearColor()
        {
            glClearColor((float) r / 255, (float) g / 255, (float) b / 255, (float) a / 255);
        }

    }
}
