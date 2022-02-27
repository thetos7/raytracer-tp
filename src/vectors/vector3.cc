#include "vector3.hh"

#include <cmath>
#include <ostream>
#include <string>

namespace vectors
{
    Vector3 Vector3::unit()
    {
        return Vector3{ 1, 1, 1 };
    }

    Vector3 Vector3::zero()
    {
        return Vector3{ 0, 0, 0 };
    }

    Vector3::Vector3(double x, double y, double z)
        : x{ x }
        , y{ y }
        , z{ z }
    {}

    double Vector3::norm()
    {
        return sqrt(x * x + y * y + z * z);
    }

    Vector3 Vector3::normalized()
    {
        auto norm_ = norm();
        if (norm_ != 0.)
        {
            return *this / norm_;
        }
        else
        {
            return zero();
        }
    }

    double Vector3::dot(const Vector3 &other)
    {
        return this->x * other.x + this->y * other.y + this->z * other.z;
    }

    Vector3 Vector3::operator*(const double &scalar)
    {
        return Vector3{ this->x * scalar, this->y * scalar, this->z * scalar };
    }

    Vector3 Vector3::operator/(const double &scalar)
    {
        return Vector3{ x / scalar, y / scalar, z / scalar };
    }

    Vector3 Vector3::operator*(const Vector3 &other)
    {
        return Vector3{ x * other.x, y * other.y, z * other.z };
    }

    Vector3 Vector3::operator/(const Vector3 &other)
    {
        return Vector3{ x / other.x, y / other.y, z / other.z };
    }

    Vector3 Vector3::operator+(const Vector3 &other)
    {
        return Vector3{ this->x + other.x, this->y + other.y,
                        this->z + other.z };
    }

    Vector3 Vector3::operator-(const Vector3 &other)
    {
        return Vector3{ this->x - other.x, this->y - other.y,
                        this->z - other.z };
    }

    std::ostream &operator<<(std::ostream &out, Vector3 &vect)
    {
        return out << "Vector3{" << vect.x << ", " << vect.y << ", " << vect.z
                   << "}";
    }

} // namespace vectors