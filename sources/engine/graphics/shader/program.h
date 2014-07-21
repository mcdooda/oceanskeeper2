#ifndef ENGINE_GRAPHICS_SHADER_PROGRAM_H
 #define ENGINE_GRAPHICS_SHADER_PROGRAM_H

#include <GL/glew.h>
#include <map>
#include "shader.h"
#include "uniform.h"

#include "vertexshader.h"
#include "fragmentshader.h"

namespace engine
{
    namespace graphics
    {
        namespace shader
        {

            class Program
            {
                public:
                    Program();
                    ~Program();

                    void link();
                    void use();

                    void setUniform(const char* name, Uniform* uniform);

                    static void disable();

                    void attachShader(Shader* shader);
                    void detachShader(Shader* shader);

                private:
                    GLuint m_id;
                    bool m_active;
                    std::map<const char*, Uniform*> m_storedUniforms;

                    void restoreUniforms();
                    void storeUniform(const char* name, Uniform* uniform);
                    void applyUniform(const char* name, Uniform* uniform);
                    static Program** getCurrent();
            };

        }
    }
}

#endif


