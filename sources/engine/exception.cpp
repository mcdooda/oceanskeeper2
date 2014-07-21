#include <iostream>
#include "exception.h"

namespace engine
{

    Exception::Exception(const char* str) :
        m_str(str)
    {

    }

    void Exception::print()
    {
        std::cerr << m_str << std::endl;
    }

}
