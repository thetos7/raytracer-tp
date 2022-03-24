#pragma once

#include <iosfwd>
#include <vector>

namespace vectors
{
    class Vector3i
    {
    public:
        int x;
        int y;
        int z;

        static Vector3i unit();
        static Vector3i zero();
        static Vector3i up();
        static Vector3i all(int value);
        static Vector3i from_vector(const std::vector<int> &);

        constexpr Vector3i()
            : Vector3i{ 0, 0, 0 }
        {}

        constexpr Vector3i(int x, int y, int z)
            : x{ x }
            , y{ y }
            , z{ z }
        {}

        int dot(const Vector3i &other) const;
        Vector3i cross(const Vector3i &other) const;
        Vector3i reflect(const Vector3i &normal) const;

        Vector3i &operator+=(const Vector3i &other);
        Vector3i &operator-=(const Vector3i &other);
        Vector3i &operator*=(const int &scalar);
        Vector3i &operator/=(const int &scalar);
        Vector3i &operator*=(const Vector3i &other);
        Vector3i &operator/=(const Vector3i &other);

        Vector3i operator+(const Vector3i &other) const;
        Vector3i operator-(const Vector3i &other) const;
        Vector3i operator*(const int &scalar) const;
        Vector3i operator/(const int &scalar) const;
        Vector3i operator*(const Vector3i &other) const;
        Vector3i operator/(const Vector3i &other) const;
    };

    Vector3i operator*(const int &scalar, const Vector3i vect);
    Vector3i operator-(const Vector3i &vect);

    std::ostream &operator<<(std::ostream &out, const Vector3i &vect);
} // namespace vectors
