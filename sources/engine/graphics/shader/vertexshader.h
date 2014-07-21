#ifndef ENGINE_GRAPHICS_SHADER_VERTEXSHADER_H
 #define ENGINE_GRAPHICS_SHADER_VERTEXSHADER_H

#include "shader.h"

namespace engine
{
    namespace graphics
    {
        namespace shader
        {

            class VertexShader : public Shader
            {
                public:
                    VertexShader(const char* filename);
            };

        }
    }
}

#endif

