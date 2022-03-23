#include "int_vector3.hh"

#include <cmath>
#include <ostream>
#include <string>

#include "utils/utils.hh"
namespace vectors
{
    Vector3i Vector3i::unit()
    {
        return Vector3i{ 1, 1, 1 };
    }

    Vector3i Vector3i::zero()
    {
        return Vector3i{ 0, 0, 0 };
    }

    Vector3i Vector3i::up()
    {
        return Vector3i{ 0, 0, 1 };
    }

    Vector3i Vector3i::all(int value)
    {
        return Vector3i{ value, value, value };
    }

    Vector3i Vector3i::from_vector(const std::vector<int> &v)
    {
        return Vector3i{ v[0], v[1], v[2] };
    }

    int Vector3i::dot(const Vector3i &other) const
    {
        return this->x * other.x + this->y * other.y + this->z * other.z;
    }

    Vector3i Vector3i::cross(const Vector3i &other) const
    {
        return Vector3i{ y * other.z - z * other.y, z * other.x - x * other.z,
                         x * other.y - y * other.x };
    }

    Vector3i Vector3i::reflect(const Vector3i &normal) const
    {
        return *this - 2 * normal * dot(normal);
    }

    Vector3i &Vector3i::operator+=(const Vector3i &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3i &Vector3i::operator-=(const Vector3i &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vector3i &Vector3i::operator*=(const int &scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector3i &Vector3i::operator/=(const int &scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    Vector3i &Vector3i::operator*=(const Vector3i &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    Vector3i &Vector3i::operator/=(const Vector3i &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    Vector3i Vector3i::operator*(const int &scalar) const
    {
        Vector3i copy = *this;
        copy *= scalar;
        return copy;
    }

    Vector3i Vector3i::operator/(const int &scalar) const
    {
        Vector3i copy = *this;
        copy /= scalar;
        return copy;
    }

    Vector3i Vector3i::operator*(const Vector3i &other) const
    {
        Vector3i copy = *this;
        copy *= other;
        return copy;
    }

    Vector3i Vector3i::operator/(const Vector3i &other) const
    {
        Vector3i copy = *this;
        copy /= other;
        return copy;
    }

    Vector3i Vector3i::operator+(const Vector3i &other) const
    {
        Vector3i copy = *this;
        copy += other;
        return copy;
    }

    Vector3i Vector3i::operator-(const Vector3i &other) const
    {
        Vector3i copy = *this;
        copy -= other;
        return copy;
    }

    Vector3i operator*(const int &scalar, const Vector3i vect)
    {
        return vect * scalar;
    }

    Vector3i operator-(const Vector3i &vect)
    {
        return Vector3i{ -vect.x, -vect.y, -vect.z };
    }

    std::ostream &operator<<(std::ostream &out, const Vector3i &vect)
    {
        if (utils::compact_enabled(out))
        {
            return out << "(" << vect.x << ", " << vect.y << ", " << vect.z
                       << ")";
        }
        return out << "Vector3i(" << vect.x << ", " << vect.y << ", " << vect.z
                   << ")";
    }

} // namespace vectors
