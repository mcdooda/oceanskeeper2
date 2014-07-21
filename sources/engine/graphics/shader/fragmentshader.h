#ifndef ENGINE_GRAPHICS_SHADER_FRAGMENTSHADER_H
 #define ENGINE_GRAPHICS_SHADER_FRAGMENTSHADER_H

#include "shader.h"

namespace engine
{
    namespace graphics
    {
        namespace shader
        {

            class FragmentShader : public Shader
            {
                public:
                    FragmentShader(const char* filename);
            };

        }
    }
}

#endif


