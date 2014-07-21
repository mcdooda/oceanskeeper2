#ifndef ENGINE_SINGLETON_H
 #define ENGINE_SINGLETON_H

#define S(T) engine::singleton<game::T>()

namespace engine
{

    template<class T> inline T* singleton()
    {
        static T instance;
        return &instance;
    }

}

#endif
