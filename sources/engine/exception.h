#ifndef ENGINE_EXCEPTION_H
 #define ENGINE_EXCEPTION_H

namespace engine
{

    class Exception
    {
        public:
            Exception(const char* str);

            void print();

        private:
            const char* m_str;
    };

}

#endif
