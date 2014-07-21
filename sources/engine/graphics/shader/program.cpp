#include <string>
#include "program.h"
#include "../../exception.h"

namespace engine
{
    namespace graphics
    {
        namespace shader
        {

            Program::Program()
            {
                m_active = false;
                m_id = glCreateProgram();

                if (m_id == 0)
                    throw Exception((const char*) glGetString(glGetError()));
            }

            Program::~Program()
            {
                glDeleteProgram(m_id);
            }

            void Program::link()
            {
                glLinkProgram(m_id);
            }

            void Program::use()
            {
                glUseProgram(m_id);

                restoreUniforms();

                Program** current = getCurrent();

                if (*current != NULL)
                    (*current)->m_active = false;

                *current = this;
                m_active = true;
            }

            void Program::setUniform(const char* name, Uniform* uniform)
            {
                if (!m_active)
                    storeUniform(name, uniform);

                else
                    applyUniform(name, uniform);
            }

            void Program::disable()
            {
                glUseProgram(0);
            }

            void Program::attachShader(Shader* shader)
            {
                shader->compile();
                glAttachShader(m_id, shader->getId());
            }

            void Program::detachShader(Shader* shader)
            {
                glDetachShader(m_id, shader->getId());
            }

            void Program::restoreUniforms()
            {
                if (m_storedUniforms.size() > 0)
                {
                    for (std::map<const char*, Uniform*>::iterator it = m_storedUniforms.begin(); it != m_storedUniforms.end(); it++)
                    {
                        const char* name = it->first;
                        Uniform* uniform = it->second;
                        applyUniform(name, uniform);
                    }
                    m_storedUniforms.clear();
                }
            }

            void Program::storeUniform(const char* name, Uniform* uniform)
            {
                m_storedUniforms[name] = uniform;
            }

            void Program::applyUniform(const char* name, Uniform* uniform)
            {
                GLint location = glGetUniformLocation(m_id, name);
                uniform->setValue(location);
                delete uniform;
            }

            Program** Program::getCurrent()
            {
                static Program* current = NULL;
                return &current;
            }

        }
    }
}


