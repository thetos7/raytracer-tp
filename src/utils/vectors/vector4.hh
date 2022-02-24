#pragma once
#include <ostream>

namespace vectors
{
    class Vector4
    {
    public:
    double w;
        double x;
        double y;
        double z;

        static Vector4 unit();
        static Vector4 zero();

        Vector4(double x, double y, double z, double w);

        double dot(const Vector4 &other);

        Vector4 operator+(const Vector4 &other);
        Vector4 operator-(const Vector4 &other);
        Vector4 operator*(const double &scalar);

    };
    std::ostream& operator<<(std::ostream& out, Vector4 &vect);
} // namespace vectors