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

        double dot(const Vector3 &other);
        double norm();
        Vector3 normalized();

        Vector3 operator+(const Vector3 &other);
        Vector3 operator-(const Vector3 &other);
        Vector3 operator*(const double &scalar);
        Vector3 operator/(const double &scalar);
        Vector3 operator*(const Vector3 &other);
        Vector3 operator/(const Vector3 &other);
    };
    std::ostream &operator<<(std::ostream &out, Vector3 &vect);
} // namespace vectors