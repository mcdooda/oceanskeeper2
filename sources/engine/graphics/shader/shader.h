#ifndef ENGINE_GRAPHICS_SHADER_SHADER_H
 #define ENGINE_GRAPHICS_SHADER_SHADER_H

#include <GL/glew.h>

namespace engine
{
    namespace graphics
    {
        namespace shader
        {

            class Shader
            {
                public:
                    Shader(GLenum type, const char* filename);
                    ~Shader();

                    void compile();

                    inline GLuint getId() const { return m_id; }

                private:

                    void readSource(const char* filename);

                    GLuint m_id;
                    GLchar* m_source;
                    bool m_compiled;
            };

        }
    }
}

#endif


