#pragma once

#include <iosfwd>

#include "vectors/fwd.hh"

namespace points
{

    class Point4
    {
    public:
        double x;
        double y;
        double z;
        double w;

        static Point4 origin();

        Point4(double x, double y, double z, double w);

        Point4 operator+(const vectors::Vector4 &vect);
        Point4 operator-(const vectors::Vector4 &vect);
    };

    std::ostream &operator<<(std::ostream &out, Point4 &point);
} // namespace points
