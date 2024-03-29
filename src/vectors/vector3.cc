#include "vector3.hh"

#include <cmath>
#include <ostream>
#include <string>

#include "utils/utils.hh"
namespace vectors
{
    Vector3 Vector3::from_vector(const std::vector<double> &v)
    {
        return Vector3{ v[0], v[1], v[2] };
    }

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

    Vector3 Vector3::lerp_to(const Vector3 &other, double factor) const
    {
        return Vector3{
            utils::lerp(x, other.x, factor),
            utils::lerp(y, other.y, factor),
            utils::lerp(z, other.z, factor),
        };
    }

    double Vector3::dot(const Vector3 &other) const
    {
        return this->x * other.x + this->y * other.y + this->z * other.z;
    }

    Vector3 Vector3::cross(const Vector3 &other) const
    {
        return Vector3{ y * other.z - z * other.y, z * other.x - x * other.z,
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
        if (utils::compact_enabled(out))
        {
            return out << "(" << vect.x << ", " << vect.y << ", " << vect.z
                       << ")";
        }
        return out << "Vector3(" << vect.x << ", " << vect.y << ", " << vect.z
                   << ")";
    }

} // namespace vectors
