#pragma once

#include <iosfwd>
#include <vector>

namespace vectors
{
    class Vector3
    {
    public:
        double x;
        double y;
        double z;

        static constexpr Vector3 unit()
        {
            return Vector3{ 1, 1, 1 };
        }

        static constexpr Vector3 zero()
        {
            return Vector3{ 0, 0, 0 };
        }

        static constexpr Vector3 up()
        {
            return Vector3{ 0, 0, 1 };
        }

        static constexpr Vector3 all(double value)
        {
            return Vector3{ value, value, value };
        }

        static Vector3 from_vector(const std::vector<double> &);

        constexpr Vector3()
            : Vector3{ 0, 0, 0 }
        {}

        constexpr Vector3(double x, double y, double z)
            : x{ x }
            , y{ y }
            , z{ z }
        {}

        double dot(const Vector3 &other) const;
        Vector3 cross(const Vector3 &other) const;
        Vector3 reflect(const Vector3 &normal) const;
        double norm() const;
        double square_norm() const;
        Vector3 normalized() const;
        Vector3 lerp_to(const Vector3 &other, double factor) const;

        Vector3 &operator+=(const Vector3 &other);
        Vector3 &operator-=(const Vector3 &other);
        Vector3 &operator*=(const double &scalar);
        Vector3 &operator/=(const double &scalar);
        Vector3 &operator*=(const Vector3 &other);
        Vector3 &operator/=(const Vector3 &other);

        Vector3 operator+(const Vector3 &other) const;
        Vector3 operator-(const Vector3 &other) const;
        Vector3 operator*(const double &scalar) const;
        Vector3 operator/(const double &scalar) const;
        Vector3 operator*(const Vector3 &other) const;
        Vector3 operator/(const Vector3 &other) const;
    };

    Vector3 operator*(const double &scalar, const Vector3 vect);
    Vector3 operator-(const Vector3 &vect);

    std::ostream &operator<<(std::ostream &out, const Vector3 &vect);
} // namespace vectors
