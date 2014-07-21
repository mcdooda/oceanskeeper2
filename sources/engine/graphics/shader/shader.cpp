#include <cstdio>
#include <string>
#include "shader.h"
#include "../../exception.h"

namespace engine
{
    namespace graphics
    {
        namespace shader
        {

            Shader::Shader(GLenum type, const char* filename)
            {
                m_compiled = false;
                m_id = glCreateShader(type);

                if (m_id == 0)
                    throw Exception((const char*) glGetString(glGetError()));

                readSource(filename);
                glShaderSource(m_id, 1, (const GLchar**) &m_source, NULL);
            }

            Shader::~Shader()
            {
                glDeleteShader(m_id);

                if (!m_compiled)
                delete m_source;
            }

            void Shader::compile()
            {
                if (!m_compiled)
                {
                    m_compiled = true;
                    glCompileShader(m_id);

                    GLint compileStatus;
                    glGetShaderiv(m_id, GL_COMPILE_STATUS, &compileStatus);

                    if (compileStatus != GL_TRUE)
                    {
                        GLint logSize;
                        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &logSize);
                        GLchar* log = new GLchar[logSize + 1];
                        glGetShaderInfoLog(m_id, logSize, &logSize, log);
                        throw Exception(log);
                    }

                    delete m_source;
                }
            }

            void Shader::readSource(const char* filename)
            {
                FILE* f = fopen(filename, "r");

                if (f == NULL)
                    throw Exception((std::string("unable to open ")+filename).c_str());

                fseek(f, 0, SEEK_END);
                int length = ftell(f);
                m_source = new char[length + 1];
                rewind(f);

                for (int i = 0; i < length; i++)
                    m_source[i] = fgetc(f);

                m_source[length] = '\0';
                fclose(f);
            }

        }
    }
}


