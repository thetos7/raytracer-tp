#include "vector2.hh"

#include <cmath>
#include <ostream>
#include <string>

#include "utils/utils.hh"
namespace vectors
{
    Vector2 Vector2::unit()
    {
        return Vector2{ 1, 1 };
    }

    Vector2 Vector2::zero()
    {
        return Vector2{ 0, 0 };
    }

    Vector2 Vector2::up()
    {
        return Vector2{ 0, -1 };
    }

    Vector2 Vector2::all(double value)
    {
        return Vector2{ value, value };
    }

    Vector2 Vector2::from_vector(const std::vector<double> &v)
    {
        return Vector2{ v[0], v[1] };
    }

    double Vector2::square_norm() const
    {
        return this->dot(*this);
    }

    Vector2 Vector2::floor() const
    {
        return Vector2{
            std::floor(x),
            std::floor(y),
        };
    }

    Vector2 Vector2::fract() const
    {
        return Vector2{
            utils::fract(x),
            utils::fract(y),
        };
    }

    double Vector2::norm() const
    {
        return sqrt(square_norm());
    }

    Vector2 Vector2::normalized() const
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

    Vector2 Vector2::lerp_to(const Vector2 &other, double factor) const
    {
        return Vector2{
            utils::lerp(x, other.x, factor),
            utils::lerp(y, other.y, factor),
        };
    }

    double Vector2::dot(const Vector2 &other) const
    {
        return this->x * other.x + this->y * other.y;
    }

    Vector2 &Vector2::operator+=(const Vector2 &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2 &Vector2::operator-=(const Vector2 &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2 &Vector2::operator*=(const double &scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2 &Vector2::operator/=(const double &scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    Vector2 &Vector2::operator*=(const Vector2 &other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Vector2 &Vector2::operator/=(const Vector2 &other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    Vector2 Vector2::operator*(const double &scalar) const
    {
        Vector2 copy = *this;
        copy *= scalar;
        return copy;
    }

    Vector2 Vector2::operator/(const double &scalar) const
    {
        Vector2 copy = *this;
        copy /= scalar;
        return copy;
    }

    Vector2 Vector2::operator*(const Vector2 &other) const
    {
        Vector2 copy = *this;
        copy *= other;
        return copy;
    }

    Vector2 Vector2::operator/(const Vector2 &other) const
    {
        Vector2 copy = *this;
        copy /= other;
        return copy;
    }

    Vector2 Vector2::operator+(const Vector2 &other) const
    {
        Vector2 copy = *this;
        copy += other;
        return copy;
    }

    Vector2 Vector2::operator-(const Vector2 &other) const
    {
        Vector2 copy = *this;
        copy -= other;
        return copy;
    }

    Vector2 operator*(const double &scalar, const Vector2 vect)
    {
        return vect * scalar;
    }

    Vector2 operator-(const Vector2 &vect)
    {
        return Vector2{ -vect.x, -vect.y };
    }

    Vector2 operator-(const double &scalar, const Vector2 &vect)
    {
        return Vector2::all(scalar) - vect;
    }

    std::ostream &operator<<(std::ostream &out, const Vector2 &vect)
    {
        if (utils::compact_enabled(out))
        {
            return out << "(" << vect.x << ", " << vect.y << ")";
        }
        return out << "Vector2(" << vect.x << ", " << vect.y << ")";
    }

} // namespace vectors
