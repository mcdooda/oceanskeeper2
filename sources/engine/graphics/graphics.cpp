#include <iostream>
#include "graphics.h"
#include "color.h"
#include "../vector2d.h"
#include "../engine.h"
#include "../exception.h"

namespace engine
{
    namespace graphics
    {

        void init(ColorRGBA color, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
        {
            GLenum code = glewInit();
            
            if (code != GLEW_OK)
                throw Exception((std::string("glewInit failed ")+(const char*)glewGetErrorString(code)).c_str());
            
            glEnable(GL_VERTEX_ARRAY);
            glEnable(GL_TEXTURE_COORD_ARRAY);
            glEnable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            color.useClearColor();

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            GLsizei width = right - left;
            GLsizei height = top - bottom;
            gluPerspective(70.0f, (float) width / (float) height, 300.f, 2000.0f);
            glViewport(0, 0, width, height);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }

        void initDisplay()
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glLoadIdentity();
            gluLookAt(350,980,550, // eye
                      350,720,0,   // center
                      0,-1,0);     // up
        }

        void endDisplay()
        {
            getApplication()->display();
        }

        void drawRectangle(Vector2d a, Vector2d b, ColorRGBA c)
        {
            glDisable(GL_TEXTURE_2D);
            c.use();
            glBegin(GL_QUADS);
            glVertex2f(a.x, a.y);
            glVertex2f(a.x, b.y);
            glVertex2f(b.x, b.y);
            glVertex2f(b.x, a.y);
            glEnd();
            glEnable(GL_TEXTURE_2D);
        }
        
        void drawRectangle(Vector2d a, Vector2d b, ColorRGBA c, Texture* texture)
        {
            c.use();
            texture->bind();
            glBegin(GL_QUADS);
            
                glTexCoord2f(0, 0);
                glVertex2f(a.x, a.y);
                
                glTexCoord2f(0, 1);
                glVertex2f(a.x, b.y);
                
                glTexCoord2f(1, 1);
                glVertex2f(b.x, b.y);
                
                glTexCoord2f(1, 0);
                glVertex2f(b.x, a.y);
                
            glEnd();
        }

    }
}
