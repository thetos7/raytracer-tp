#pragma once

#include <ostream>

namespace vectors
{
    class Vector3
    {
    public:
        double x;
        double y;
        double z;

        static Vector3 unit();
        static Vector3 zero();

        Vector3(double x, double y, double z);

        double dot(const Vector3 &other) const;
        double norm() const;
        double square_norm() const;
        Vector3 normalized() const;

        Vector3 operator+(const Vector3 &other) const;
        Vector3 operator-(const Vector3 &other) const;
        Vector3 operator*(const double &scalar) const;
        Vector3 operator/(const double &scalar) const;
        Vector3 operator*(const Vector3 &other) const;
        Vector3 operator/(const Vector3 &other) const;
    };

    Vector3 operator*(const double &scalar, const Vector3 vect);

    std::ostream &operator<<(std::ostream &out, const Vector3 &vect);
} // namespace vectors
