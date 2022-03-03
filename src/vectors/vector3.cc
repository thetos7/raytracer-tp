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

    Vector3 Vector3::up()
    {
        return Vector3{ 0, 0, 1 };
    }

    Vector3 Vector3::all(double value)
    {
        return Vector3{ value, value, value };
    }

    Vector3::Vector3(double x, double y, double z)
        : x{ x }
        , y{ y }
        , z{ z }
    {}

    double Vector3::square_norm() const
    {
        return this->dot(*this);
    }

    double Vector3::norm() const
    {
        return sqrt(square_norm());
    }

    Vector3 Vector3::normalized() const
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

    double Vector3::dot(const Vector3 &other) const
    {
        return this->x * other.x + this->y * other.y + this->z * other.z;
    }

    Vector3 Vector3::cross(const Vector3 &other) const
    {
        return Vector3{ y * other.z - z * other.y, z * other.x - x * other.y,
                        x * other.y - y * other.x };
    }

    Vector3 Vector3::reflect(const Vector3 &normal) const
    {
        return *this - 2 * normal * dot(normal);
    }

    Vector3 &Vector3::operator+=(const Vector3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3 &Vector3::operator-=(const Vector3 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vector3 &Vector3::operator*=(const double &scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector3 &Vector3::operator/=(const double &scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    Vector3 &Vector3::operator*=(const Vector3 &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    Vector3 &Vector3::operator/=(const Vector3 &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    Vector3 Vector3::operator*(const double &scalar) const
    {
        Vector3 copy = *this;
        copy *= scalar;
        return copy;
    }

    Vector3 Vector3::operator/(const double &scalar) const
    {
        Vector3 copy = *this;
        copy /= scalar;
        return copy;
    }

    Vector3 Vector3::operator*(const Vector3 &other) const
    {
        Vector3 copy = *this;
        copy *= other;
        return copy;
    }

    Vector3 Vector3::operator/(const Vector3 &other) const
    {
        Vector3 copy = *this;
        copy /= other;
        return copy;
    }

    Vector3 Vector3::operator+(const Vector3 &other) const
    {
        Vector3 copy = *this;
        copy += other;
        return copy;
    }

    Vector3 Vector3::operator-(const Vector3 &other) const
    {
        Vector3 copy = *this;
        copy -= other;
        return copy;
    }

    Vector3 operator*(const double &scalar, const Vector3 vect)
    {
        return vect * scalar;
    }

    Vector3 operator-(const Vector3 &vect)
    {
        return Vector3{ -vect.x, -vect.y, -vect.z };
    }

    std::ostream &operator<<(std::ostream &out, const Vector3 &vect)
    {
        return out << "Vector3(" << vect.x << ", " << vect.y << ", " << vect.z
                   << ")";
    }

} // namespace vectors
