#ifndef ENGINE_GRAPHICS_SHADER_UNIFORM_H
 #define ENGINE_GRAPHICS_SHADER_UNIFORM_H

#include <GL/glew.h>

namespace engine
{
    namespace graphics
    {
        namespace shader
        {

            class Uniform
            {
                public:
                    virtual void setValue(GLint location) = 0;
            };


            class Uniform1i : public Uniform
            {
                public:
                    Uniform1i(GLint i) : m_int(i) {}

                    void setValue(GLint location);

                private:
                    GLint m_int;
            };


            class Uniform1f : public Uniform
            {
                public:
                    Uniform1f(GLfloat f) : m_float(f) {}

                    void setValue(GLint location);

                private:
                    GLfloat m_float;
            };

        }
    }
}

#endif
