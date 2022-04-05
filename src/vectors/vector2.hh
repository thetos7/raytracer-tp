#pragma once

#include <iosfwd>
#include <vector>

namespace vectors
{
    class Vector2
    {
    public:
        double x;
        double y;

        static Vector2 unit();
        static Vector2 zero();
        static Vector2 up();
        static Vector2 all(double value);
        static Vector2 from_vector(const std::vector<double> &);

        constexpr Vector2()
            : Vector2{ 0, 0 }
        {}

        constexpr Vector2(double x, double y)
            : x{ x }
            , y{ y }
        {}

        double dot(const Vector2 &other) const;
        double norm() const;
        double square_norm() const;
        Vector2 normalized() const;
        Vector2 lerp_to(const Vector2 &other, double factor) const;

        Vector2 &operator+=(const Vector2 &other);
        Vector2 &operator-=(const Vector2 &other);
        Vector2 &operator*=(const double &scalar);
        Vector2 &operator/=(const double &scalar);
        Vector2 &operator*=(const Vector2 &other);
        Vector2 &operator/=(const Vector2 &other);

        Vector2 operator+(const Vector2 &other) const;
        Vector2 operator-(const Vector2 &other) const;
        Vector2 operator*(const double &scalar) const;
        Vector2 operator/(const double &scalar) const;
        Vector2 operator*(const Vector2 &other) const;
        Vector2 operator/(const Vector2 &other) const;
    };

    Vector2 operator*(const double &scalar, const Vector2 vect);
    Vector2 operator-(const Vector2 &vect);

    std::ostream &operator<<(std::ostream &out, const Vector2 &vect);
} // namespace vectors
