#include "uniform.h"

namespace engine
{
    namespace graphics
    {
        namespace shader
        {

            void Uniform1i::setValue(GLint location)
            {
                glUniform1i(location, m_int);
            }

            void Uniform1f::setValue(GLint location)
            {
                glUniform1f(location, m_float);
            }

        }
    }
}


