#ifndef ENGINE_VECTOR3D_H
 #define ENGINE_VECTOR3D_H

#include "vector2d.h"

namespace engine
{

    class Vector3d : public Vector2d
    {
        public:
            Vector3d(float x, float y, float z);
            Vector3d();

            Vector3d operator+(const Vector3d& v);
            Vector3d operator-(const Vector3d& v);
            
            Vector3d operator+(const Vector2d& v);
            Vector3d operator-(const Vector2d& v);
            
            Vector3d operator*(const float& f);
            Vector3d operator/(const float& f);

            void operator+=(const Vector3d& v);
            void operator-=(const Vector3d& v);
            
            void operator+=(const Vector2d& v);
            void operator-=(const Vector2d& v);
            
            void operator*=(const float& f);
            void operator/=(const float& f);
            
            float z;
    };

}

#endif
