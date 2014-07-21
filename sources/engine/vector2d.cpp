#include "vector2d.h"
#include <cmath>

namespace engine
{

    Vector2d::Vector2d(float x, float y) :
        x(x),
        y(y)
    {

    }

    Vector2d::Vector2d(float angle)
    {
        x = cos(angle);
        y = sin(angle);
    }

    Vector2d::Vector2d() :
        x(0),
        y(0)
    {

    }

    Vector2d Vector2d::normalize()
    {
        float d = distance();
        if (d != 0)
            return Vector2d(x / d, y / d);
        else
            return *this;
    }

    float Vector2d::distance()
    {
        return sqrt(x * x + y * y);
    }

    float Vector2d::distanceSquared()
    {
        return x * x + y * y;
    }

    float Vector2d::angle()
    {
        float angle = atan(y / x);
        if (x < 0)
            angle += M_PI;

        return angle;
    }

    void Vector2d::setMinX(float minX)
    {
        if (x < minX)
            x = minX;
    }

    void Vector2d::setMaxX(float maxX)
    {
        if (x > maxX)
            x = maxX;
    }

    void Vector2d::setMinY(float minY)
    {
        if (y < minY)
            y = minY;
    }

    void Vector2d::setMaxY(float maxY)
    {
        if (y > maxY)
            y = maxY;
    }

    Vector2d Vector2d::operator+(const Vector2d& v)
    {
        return Vector2d(x + v.x, y + v.y);
    }

    Vector2d Vector2d::operator-(const Vector2d& v)
    {
        return Vector2d(x - v.x, y - v.y);
    }

    Vector2d Vector2d::operator*(const float& f)
    {
        return Vector2d(x * f, y * f);
    }

    Vector2d Vector2d::operator/(const float& f)
    {
        return Vector2d(x / f, y / f);
    }

    void Vector2d::operator+=(const Vector2d& v)
    {
        x += v.x;
        y += v.y;
    }

    void Vector2d::operator-=(const Vector2d& v)
    {
        x -= v.x;
        y -= v.y;
    }

    void Vector2d::operator*=(const float& f)
    {
        x *= f;
        y *= f;
    }

    void Vector2d::operator/=(const float& f)
    {
        x /= f;
        y /= f;
    }

}
