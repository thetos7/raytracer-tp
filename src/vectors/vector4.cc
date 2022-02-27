#include "vector4.hh"

#include <ostream>
#include <string>

namespace vectors
{
    Vector4 Vector4::unit()
    {
        return Vector4{ 1, 1, 1, 1 };
    }

    Vector4 Vector4::zero()
    {
        return Vector4{ 0, 0, 0, 0 };
    }

    Vector4::Vector4(double x, double y, double z, double w)
        : x{ x }
        , y{ y }
        , z{ z }
        , w{ w }
    {}

    double Vector4::dot(const Vector4 &other)
    {
        return this->x * other.x + this->y * other.y + this->z * other.z
            + this->w * other.w;
    }

    Vector4 Vector4::operator*(const double &scalar)
    {
        return Vector4{ this->x * scalar, this->y * scalar, this->z * scalar,
                        this->w * scalar };
    }

    Vector4 Vector4::operator/(const double &scalar)
    {
        return Vector4{ x / scalar, y / scalar, z / scalar, w / scalar };
    }

    Vector4 Vector4::operator+(const Vector4 &other)
    {
        return Vector4{ this->x + other.x, this->y + other.y, this->z + other.z,
                        this->w + other.w };
    }

    Vector4 Vector4::operator-(const Vector4 &other)
    {
        return Vector4{ this->x - other.x, this->y - other.y, this->z - other.z,
                        this->w - other.w };
    }

    std::ostream &operator<<(std::ostream &out, Vector4 &vect)
    {
        return out << "Vector4{" << vect.x << ", " << vect.y << ", " << vect.z
                   << ", " << vect.w << "}";
    }

} // namespace vectors
