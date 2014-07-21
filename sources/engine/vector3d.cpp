#include "vector3d.h"

namespace engine
{
    Vector3d::Vector3d(float x, float y, float z) :
        Vector2d(x, y),
        z(z)
    {

    }
    
    Vector3d::Vector3d() :
        Vector2d(),
        z(0)
    {
        
    }

    Vector3d Vector3d::operator+(const Vector3d& v)
    {
        return Vector3d(x + v.x, y + v.y, z + v.z);
    }
    
    Vector3d Vector3d::operator-(const Vector3d& v)
    {
        return Vector3d(x - v.x, y - v.y, z - v.z);
    }
    
    Vector3d Vector3d::operator+(const Vector2d& v)
    {
        return Vector3d(x + v.x, y + v.y, z);
    }
    
    Vector3d Vector3d::operator-(const Vector2d& v)
    {
        return Vector3d(x - v.x, y - v.y, z);
    }
    
    Vector3d Vector3d::operator*(const float& f)
    {
        return Vector3d(x * f, y * f, z * f);
    }
    
    Vector3d Vector3d::operator/(const float& f)
    {
        return Vector3d(x / f, y / f, z / f);
    }

    void Vector3d::operator+=(const Vector3d& v)
    {
        x += v.x;
        y += v.y;
    }
    
    void Vector3d::operator-=(const Vector3d& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }
    
    void Vector3d::operator+=(const Vector2d& v)
    {
        x += v.x;
        y += v.y;
    }
    
    void Vector3d::operator-=(const Vector2d& v)
    {
        x -= v.x;
        y -= v.y;
    }
    
    void Vector3d::operator*=(const float& f)
    {
        x *= f;
        y *= f;
        z *= f;
    }
    
    void Vector3d::operator/=(const float& f)
    {
        x /= f;
        y /= f;
        z /= f;
    }
    
}
