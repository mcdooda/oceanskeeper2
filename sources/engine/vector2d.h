#ifndef ENGINE_VECTOR2D_H
 #define ENGINE_VECTOR2D_H

namespace engine
{

    class Vector2d
    {
        public:
            Vector2d(float x, float y);
            Vector2d(float angle);
            Vector2d();

            Vector2d normalize();

            float distance();
            float distanceSquared();
            float angle();

            void setMinX(float minX);
            void setMaxX(float maxX);
            void setMinY(float minY);
            void setMaxY(float maxY);

            Vector2d operator+(const Vector2d& v);
            Vector2d operator-(const Vector2d& v);
            Vector2d operator*(const float& f);
            Vector2d operator/(const float& f);

            void operator+=(const Vector2d& v);
            void operator-=(const Vector2d& v);
            void operator*=(const float& f);
            void operator/=(const float& f);

            float x;
            float y;
    };

}

#endif
